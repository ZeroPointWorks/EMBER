#ifndef EMBER_REWARD_H
#define EMBER_REWARD_H

#include <cstdint>
#include <vector>
#include "blockchain.h"
#include "cryptonote_basic/cryptonote_basic.h"

namespace cryptonote {

class EmberRewardCurve {
public:
    static constexpr size_t LOOKBACK_BLOCKS = 144;

    // Calculates the miner's share of the last LOOKBACK_BLOCKS blocks.
    // Returns a double between 0.0 and 1.0.
    static double get_miner_share(const Blockchain& blockchain, const account_public_address& miner_address);

    // Applies the asymptotic reward curve formula.
    // base_reward: The original block reward before applying the curve.
    // share: The miner's share (0.0 to 1.0).
    // Returns the effective reward after applying the curve.
    static uint64_t apply_curve(uint64_t base_reward, double share);

    // Combines get_miner_share and apply_curve to get the final effective reward.
    static uint64_t get_effective_reward(const Blockchain& blockchain, uint64_t base_reward, const account_public_address& miner_address);
};

} // namespace cryptonote

#endif // EMBER_REWARD_H
