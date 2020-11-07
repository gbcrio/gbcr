// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2020 GBCR Developers
// Copyright (c) 2009-2019 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <consensus/consensus.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>
#include "arith_uint256.h"

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "2020-10-22 Turks rush to buy gold over weak currency, inflation";
    const CScript genesisOutputScript = CScript() << ParseHex("04afab89b3670736e72d7d8a2426081782329142bdfe1c42405c470f54d6e635ee5c6ba66fe3128f7eaf1bcce92b4440a14a6199a40d2f8bb79c452d889b89c3e5") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.nSubsidyHalvingInterval = 30000 * 50; // every 8 years 4 months
        consensus.BIP16Exception = uint256S("0x000004e2fbc8efd8702b9b8287f3e714b72e4c93e2bde71cbcf3372a43a8b548");
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x000004799eb95011b7723cb7a592ad2914c794107af31d1665a08ffcc66d3716");
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.BPSDiffAdjHeight = 4500;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 3 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 3 * 60;   // 3 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 200; // 95% of 2016
        consensus.nMinerConfirmationWindow = 1; // nPowTargetimespan (180) / nPowTargetSpacing (1800)
        consensus.nLastPOWBlock = 5000;
        consensus.nMPoSRewardRecipients = 10;  // During the proof of stake phase, maximum of 10 accounts
	/** consensus.nLastPOWBlock + 
                      consensus.nMPoSRewardRecipients + 
                      COINBASE_MATURITY; **/
	consensus.nFirstMPoSBlock = 5248;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00000000000000000000000000000000000000000000000000eaf912c8c4d3c4");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000004e2fbc8efd8702b9b8287f3e714b72e4c93e2bde71cbcf3372a43a8b548");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x47; // G
        pchMessageStart[1] = 0x62; // b
        pchMessageStart[2] = 0x63; // c
        pchMessageStart[3] = 0x72; // r
        nDefaultPort = 62357;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 4;
        m_assumed_chain_state_size = 2;


       genesis = CreateGenesisBlock(1603774373, 803643, 0x1e0fffff, 1, 50 * COIN);          

       consensus.hashGenesisBlock = genesis.GetHash();
       assert(consensus.hashGenesisBlock == uint256S("0x000004e2fbc8efd8702b9b8287f3e714b72e4c93e2bde71cbcf3372a43a8b548"));
       assert(genesis.hashMerkleRoot == uint256S("0x18d46f5b051c836ea142af82c57b25c1cfd4bd50e970deb344f3808f204aa19b"));  


       /* Activate Later */
       vSeeds.emplace_back("nodea.goldbcr.io");
       vSeeds.emplace_back("nodeb.goldbcr.io");
       vSeeds.emplace_back("nodec.goldbcr.io");
       vSeeds.emplace_back("noded.goldbcr.io");
       vSeeds.emplace_back("nodee.goldbcr.io");
       vSeeds.emplace_back("nodef.goldbcr.io"); 


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);  // starts with 'G'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,148); //  starts with 'L'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x06, 0x90, 0xB4, 0x1F};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x86, 0xAB, 0xE5};

        bech32_hrp = "gbcr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x000004e2fbc8efd8702b9b8287f3e714b72e4c93e2bde71cbcf3372a43a8b548")},
                { 333, uint256S("0x000000c96ed11c5d26d08aaa99a9eda1bb1e7cfdbb9731134e9ebb9be4f71325")},
		{ 1598, uint256S("0x00000004366205f75ee66c777c55e2693eb376b2b3befd52ceed6b857bdc0082")},
		{ 2416, uint256S("0x000000013ec4fdbdb3a78f2a48a3d4c3f09d2560051f8628cec4587a61ccc156")},
		{ 3682, uint256S("0x00000005bc1dfea265300159779dac0ea87d57ca5e5bd92f59f505fafab4aa1e")},
		{ 4141, uint256S("0x00000d968d36e9c0c79f532ddff0c50c6a9068ff3b6696b1a1c835e43f1e1546")},
		{ 5247, uint256S("0x3984aaf807535581745ce6817dd2e1a952be65142e3882d66464bf8acbfde08e")},
		{ 5248, uint256S("0xff3844a403709b7fd3e3edc8012ba645759ac128c13e85ecb0c53f3db1ea5948")},
		{ 5793, uint256S("0xb791e095248a435c8d306df63223498108b535596e6a1efb2b22a4b39c3113bd")}

            }
        };

        chainTxData = ChainTxData{
            /* nTime    */ 1604647152,
            /* nTxCount */ 6740,
            /* dTxRate  */ 0.01052274853317133
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.nSubsidyHalvingInterval = 30000;
        consensus.BIP16Exception = uint256S("0x000003ec08824c0b7ea2cd8ef656c2dd9d2bacae620f1a4e0b93cbb4db28288f");
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00");
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.BPSDiffAdjHeight = 1500;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 1 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nLastPOWBlock = 501;
        consensus.nMPoSRewardRecipients = 1;
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    COINBASE_MATURITY;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000003ec08824c0b7ea2cd8ef656c2dd9d2bacae620f1a4e0b93cbb4db28288f"); // 0

        pchMessageStart[0] = 0x67; // g
        pchMessageStart[1] = 0x62; // b
        pchMessageStart[2] = 0x63; // c
        pchMessageStart[3] = 0x72; // r
        nDefaultPort = 7235;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 40;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1603335541, 92776, 0x1e0fffff, 1, 50 * COIN); 
        
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000003ec08824c0b7ea2cd8ef656c2dd9d2bacae620f1a4e0b93cbb4db28288f"));
        assert(genesis.hashMerkleRoot == uint256S("0x18d46f5b051c836ea142af82c57b25c1cfd4bd50e970deb344f3808f204aa19b"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.emplace_back("test-nodea.goldbcr.io");
        vSeeds.emplace_back("test-nodeb.goldbcr.io");
        vSeeds.emplace_back("test-nodec.goldbcr.io");
        vSeeds.emplace_back("test-noded.goldbcr.io");

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,130);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tgbcr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {0, uint256S("0x000003ec08824c0b7ea2cd8ef656c2dd9d2bacae620f1a4e0b93cbb4db28288f")},
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000000000b7ab6ce61eb6d571003fbe5fe892da4c9b740c49a07542462d
            /* nTime    */ 1603335541,
            /* nTxCount */ 0,
            /* dTxRate  */ 0.0,
        };
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 500; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 432; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.BPSDiffAdjHeight = 1500;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 3 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 3 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.nLastPOWBlock = 0x7fffffff;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = 5000;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 48934;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1603339141, 129088, 0x1e0fffff, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000009e876c8ef41dc9a53f415c52a54b4a0e81e0f7069faa791c8fca0aedae5"));
        assert(genesis.hashMerkleRoot == uint256S("0x18d46f5b051c836ea142af82c57b25c1cfd4bd50e970deb344f3808f204aa19b"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x000009e876c8ef41dc9a53f415c52a54b4a0e81e0f7069faa791c8fca0aedae5")},
            }
        };

        chainTxData = ChainTxData{
            1603339141,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,130);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rgbcr";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {  
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);;
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

