#include "ember_reward.h"
#include "blockchain_db/blockchain_db.h"
#include "int-util.h"
#include "cryptonote_basic/cryptonote_format_utils.h"
#include "cryptonote_basic/miner.h"

#include <algorithm>
#include <cmath>

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "blockchain.reward"

namespace cryptonote {

double EmberRewardCurve::get_miner_share(const Blockchain& blockchain, const account_public_address& miner_address) {
    uint64_t total_blocks_found = 0;
    uint64_t miner_blocks_found = 0;

    uint64_t current_height = blockchain.get_current_blockchain_height();
    uint64_t start_height = (current_height > LOOKBACK_BLOCKS) ? current_height - LOOKBACK_BLOCKS : 0;

    MDEBUG("Calculating miner share for address: " << cryptonote::get_account_address_as_str(blockchain.get_nettype(), false, miner_address) << " from height " << start_height << " to " << current_height);

    for (uint64_t h = start_height; h < current_height; ++h) {
        block b = blockchain.get_db().get_block_from_height(h);
        if (b.miner_tx.vout.empty()) continue;

        // In Monero, the miner reward is in the outputs of the miner_tx.
        // The outputs are derived using the miner's public keys and the tx ephemeral key.
        // To verify if an output belongs to a miner, we'd normally need the view secret key.
        // However, for this fork, we'll use a simplified check: 
        // We'll look for a specific tag or just assume the first output's derived key
        // can be matched if we had the derivation. 
        // Since we only have the public address, we'll implement a heuristic or 
        // a simplified version for this project.
        
        // Match the public spend key from the address against 
        // the derived public key in the output. This requires the tx_pub_key from extra.
        crypto::public_key tx_pub_key = get_tx_pub_key_from_extra(b.miner_tx);
        if (memcmp(&tx_pub_key, &crypto::null_hash, sizeof(crypto::hash)) != 0) {
            // For EMBER, we'll assume a simplified miner_tx where the spend key is 
            // used directly or we use a deterministic derivation that can be 
            // checked by anyone. For this project's logic, we'll use a heuristic:
            // Check if the first output's key matches the miner's spend public key.
            if (b.miner_tx.vout[0].target.type() == typeid(txout_to_key)) {
                if (memcmp(&boost::get<txout_to_key>(b.miner_tx.vout[0].target).key, &miner_address.m_spend_public_key, sizeof(crypto::public_key)) == 0) {
                    miner_blocks_found++;
                }
            }
        }
        total_blocks_found++;
    }

    if (total_blocks_found == 0) return 0.0;
    return static_cast<double>(miner_blocks_found) / total_blocks_found;
}

uint64_t EmberRewardCurve::apply_curve(uint64_t base_reward, double share) {
    if (share <= 0.01) return base_reward;
    return static_cast<uint64_t>(base_reward * (0.01 / share));
}

uint64_t EmberRewardCurve::get_effective_reward(const Blockchain& blockchain, uint64_t base_reward, const account_public_address& miner_address) {
    double share = get_miner_share(blockchain, miner_address);
    return apply_curve(base_reward, share);
}

} // namespace cryptonote
