# EMBER - CPU-Only Cryptocurrency with Asymptotic Reward Curve

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![GitHub release](https://img.shields.io/github/release/ZeroPointWorks/EMBER.svg)](https://github.com/ZeroPointWorks/EMBER/releases)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

EMBER is a privacy-focused cryptocurrency that solves mining centralization through an **asymptotic reward curve mechanism**. Unlike traditional cryptocurrencies where mining farms have economies of scale, EMBER makes mining farms economically irrational by capping total earnings regardless of hash power invested.

## 🔥 What Makes EMBER Different

### The Problem
Traditional cryptocurrencies suffer from mining centralization because large mining farms have economies of scale:
- A farm with 100 CPUs earns 100× more than a solo miner
- This incentivizes consolidation into massive industrial operations
- Decentralization is compromised

### The Solution: Asymptotic Reward Curve
EMBER implements a protocol-level economic mechanism that **destroys economies of scale**:

```
effective_reward = base_reward × min(1.0, 0.01 / miner_share)
```

**How it works:**
- Miner with 0.5% of network → 100% reward per block
- Miner with 1% of network → 100% reward per block
- Miner with 2% of network → 50% reward per block
- Miner with 10% of network → 10% reward per block
- Miner with 50% of network → 2% reward per block

**Result:** Total earnings plateau. A farm with 100 CPUs earns the same as 1 home miner.

### Key Features
✅ **Fair Mining** — One CPU, one fair reward (no economies of scale)
✅ **Full Privacy** — Ring Signatures, Stealth Addresses, RingCT
✅ **ASIC-Resistant** — RandomX algorithm (CPU-optimized)
✅ **No Premine** — Fair launch, no dev tax, no ICO
✅ **Decentralized** — Anyone can run a node and mine
✅ **144-Block Lookback** — Reward curve uses recent block history

---

## 🚀 Quick Start

### System Requirements
- **CPU:** Modern multi-core processor (2+ cores)
- **RAM:** 4 GB minimum (8 GB recommended)
- **Disk:** 50 GB for blockchain (SSD recommended)
- **Network:** 10+ Mbps connection

### Build from Source

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install -y build-essential cmake git libboost-all-dev \
  libssl-dev libzmq3-dev libpgm-dev libunbound-dev libsodium-dev \
  miniupnpc libminiupnpc-dev

# Clone repository
git clone https://github.com/ZeroPointWorks/EMBER.git
cd EMBER

# Build
mkdir build && cd build
cmake ..
make -j$(nproc)

# Run daemon
./bin/emberd
```

#### macOS
```bash
# Install dependencies via Homebrew
brew install cmake boost openssl zmq libpgm unbound libsodium miniupnpc

# Clone and build
git clone https://github.com/ZeroPointWorks/EMBER.git
cd EMBER
mkdir build && cd build
cmake ..
make -j$(sysctl -n hw.ncpu)

# Run daemon
./bin/emberd
```

#### Windows (MSYS2)
```bash
# Install MSYS2 from https://www.msys2.org/
# Open MSYS2 MinGW 64-bit terminal

# Install dependencies
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake \
  mingw-w64-x86_64-boost mingw-w64-x86_64-openssl \
  mingw-w64-x86_64-zeromq mingw-w64-x86_64-libsodium

# Clone and build
git clone https://github.com/ZeroPointWorks/EMBER.git
cd EMBER
mkdir build && cd build
cmake -G "Unix Makefiles" ..
make -j$(nproc)

# Run daemon
./bin/emberd.exe
```

---

## 📋 Dependencies

### Required
| Package | Version | Purpose |
|---------|---------|---------|
| CMake | 3.10+ | Build system |
| Boost | 1.70+ | C++ libraries |
| OpenSSL | 1.1+ | Cryptography |
| ZMQ | 4.3+ | Networking |
| libsodium | 1.0+ | Cryptographic primitives |

### Optional
| Package | Purpose |
|---------|---------|
| libpgm | PGM protocol support |
| unbound | DNS resolution |
| miniupnpc | UPnP support |

### Installation by OS

**Ubuntu/Debian:**
```bash
sudo apt-get install build-essential cmake git libboost-all-dev \
  libssl-dev libzmq3-dev libpgm-dev libunbound-dev libsodium-dev \
  miniupnpc libminiupnpc-dev
```

**Fedora/RHEL:**
```bash
sudo dnf install gcc-c++ cmake git boost-devel openssl-devel \
  zeromq-devel libpgm-devel unbound-devel libsodium-devel miniupnpc-devel
```

**macOS:**
```bash
brew install cmake boost openssl zmq libpgm unbound libsodium miniupnpc
```

---

## 🛠️ Building

### Standard Build
```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
```

### Build with Tests
```bash
mkdir build
cd build
cmake -DBUILD_TESTS=ON ..
make -j$(nproc)
make test
```

### Build with Debug Symbols
```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

### Build Options
```bash
cmake -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_TESTS=ON \
      -DBUILD_DOCUMENTATION=ON \
      -DSTATIC=ON \
      ..
```

---

## 🚀 Running EMBER

### Start the Daemon
```bash
./bin/emberd
```

### Common Options
```bash
# Run on testnet
./bin/emberd --testnet

# Run on stagenet
./bin/emberd --stagenet

# Specify data directory
./bin/emberd --data-dir /path/to/data

# Enable mining
./bin/emberd --start-mining <wallet_address> --mining-threads 4

# Set custom RPC port
./bin/emberd --rpc-bind-port 19371

# Sync from specific node
./bin/emberd --add-peer node.example.com:19370
```

### RPC Interface
The daemon exposes a JSON-RPC interface on port 19371:

```bash
# Get network info
curl http://localhost:19371/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_info","params":{}}'

# Get block count
curl http://localhost:19371/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"get_block_count","params":{}}'

# Get mining status
curl http://localhost:19371/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"mining_status","params":{}}'
```

---

## ⛏️ Mining

### CPU Mining
EMBER uses RandomX algorithm which is CPU-optimized:

```bash
# Start mining with 4 threads
./bin/emberd --start-mining <your_wallet_address> --mining-threads 4
```

### Pool Mining
Connect to a mining pool:

```bash
# Using xmrig (compatible with EMBER)
./xmrig -o pool.example.com:3333 -u <wallet_address> -p x -t 4
```

### Mining Reward Calculation
Your effective reward depends on your share of the network:

```
effective_reward = base_reward × min(1.0, 0.01 / your_share)
```

**Example:**
- You have 1 MH/s
- Network has 100 MH/s (you have 1% share)
- Base reward: 0.6 EMB per block
- Your reward: 0.6 × min(1.0, 0.01/0.01) = 0.6 EMB

---

## 📊 Network Parameters

| Parameter | Value |
|-----------|-------|
| **Block Time** | 2 minutes |
| **Block Reward** | 0.6 EMB (adjusts with difficulty) |
| **Reward Curve Lookback** | 144 blocks (~4.8 hours) |
| **Network ID** | Random 16 bytes (per fork) |
| **Address Prefix** | 512 (mainnet) |
| **RPC Port** | 19371 (mainnet), 29371 (testnet) |
| **P2P Port** | 19370 (mainnet), 29370 (testnet) |
| **Difficulty Adjustment** | Every block |

---

## 🔐 Security

### Cryptographic Primitives
- **Hashing:** Keccak-256 (SHA-3)
- **Signatures:** Ed25519
- **Encryption:** ChaCha20-Poly1305
- **Key Derivation:** Argon2

### Privacy Features
- **Ring Signatures:** Hides transaction sender (default ring size: 11)
- **Stealth Addresses:** Recipient privacy
- **RingCT:** Hides transaction amounts
- **Kovri Integration:** Optional (future)

### Consensus
- **Algorithm:** Proof-of-Work (RandomX)
- **Difficulty Adjustment:** Dynamic per block
- **Reward Curve:** Asymptotic (anti-centralization)

---

## 📝 Project Structure

```
EMBER/
├── src/                    # C++ source code
│   ├── cryptonote_core/   # Core blockchain logic
│   ├── cryptonote_basic/  # Basic types and utilities
│   ├── crypto/            # Cryptographic functions
│   ├── ringct/            # RingCT implementation
│   ├── device/            # Hardware wallet support
│   ├── p2p/               # P2P networking
│   ├── rpc/               # RPC interface
│   ├── daemon/            # Daemon executable
│   └── common/            # Common utilities
├── include/               # Header files
├── cmake/                 # CMake modules
├── scripts/               # Build and utility scripts
├── docs/                  # Technical documentation
├── tests/                 # Unit tests
├── CMakeLists.txt         # Main CMake configuration
├── README.md              # This file
├── LICENSE                # MIT License
└── .gitignore             # Git ignore rules
```

---

## 🧪 Testing

### Run Unit Tests
```bash
cd build
make test
```

### Run Specific Test
```bash
./tests/unit_tests --gtest_filter="TestName"
```

### Performance Testing
```bash
./tests/performance_tests
```

---

## 📚 Documentation

- **Technical Whitepaper:** See `/docs/EMBER_Whitepaper.md`
- **Mining Guide:** See `/docs/MINING.md`
- **RPC Documentation:** See `/docs/RPC.md`
- **Protocol Specification:** See `/docs/PROTOCOL.md`
- **Reward Curve Analysis:** See `/docs/REWARD_CURVE.md`

---

## 🤝 Contributing

We welcome contributions! Please:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

### Development Guidelines
- Follow C++17 standards
- Write tests for new features
- Update documentation
- Use meaningful commit messages
- Keep commits atomic

---

## 🐛 Bug Reports

Found a bug? Please report it on [GitHub Issues](https://github.com/ZeroPointWorks/EMBER/issues) with:

1. **Description:** What's the bug?
2. **Steps to Reproduce:** How to trigger it?
3. **Expected Behavior:** What should happen?
4. **Actual Behavior:** What actually happens?
5. **Environment:** OS, version, hardware specs
6. **Logs:** Relevant error messages

---

## 📄 License

EMBER is released under the MIT License. See [LICENSE](LICENSE) file for details.

---

## 🔗 Links

- **Website:** https://embercrypto.github.io
- **Discord:** https://discord.gg/XXXXX
- **Twitter:** https://twitter.com/emberchain
- **GitHub:** https://github.com/ZeroPointWorks/EMBER
- **Whitepaper:** https://embercrypto.github.io/whitepaper.pdf

---

## 📞 Support

- **Discord:** Join our community server for help
- **GitHub Issues:** Report bugs and request features
- **Email:** support@embercrypto.github.io

---

## 🙏 Acknowledgments

EMBER is built on the Monero codebase (v0.18.3.4) with significant modifications to implement the asymptotic reward curve mechanism. We thank the Monero project for the excellent foundation.

**Key Innovations:**
- Asymptotic reward curve (EMBER original)
- 144-block lookback window (EMBER original)
- Network parameter customization (EMBER original)

---

## 📊 Version History

| Version | Date | Changes |
|---------|------|---------|
| 0.1.0 | 2026-05-25 | Initial release |

---

**One CPU, one fair reward.** 🔥
