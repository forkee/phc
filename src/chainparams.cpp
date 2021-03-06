// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;
        
        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;
        
        memcpy(&ip, &t, sizeof(ip));
        
        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x25;
        pchMessageStart[3] = 0x88;
        vAlertPubKey = ParseHex("045ae8e09a456a2ae88f9a2fdb99122612cd26f9da329731b1b8335f650978c9d21df0a0543ba1179d05a081c3c1ec389ce2bb55e36565b50ab40dde6b19d136e1");
        nDefaultPort = 20060;
        nRPCPort = 20061;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //

        /*
        mainnet.genesis : 
        CBlock(hash=0000b587d86da35102be091d9d303851d53130a70375a2ae6b8827ca18feb00d, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4, nTime=1514844000, nBits=1f00ffff, nNonce=1006718, vtx=1, vchBlockSig=)
        Coinbase(hash=10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4, nTime=1514844000, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24426974636f696e202e2e2e20616e6f746865722062696720626f6f7374202d20434e4243)
        CTxOut(nValue=0.00, scriptPubKey=045ae8e09a456a2ae88f9a2fdb9912)

        vMerkleTree:  10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4

        mainnet.genesis.GetHash(): 0000b587d86da35102be091d9d303851d53130a70375a2ae6b8827ca18feb00d
        mainnet.genesis.hashMerkleRoot: 10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4
        mainnet.genesis.nTime: 1514844000
        mainnet.genesis.nNonce: 1006718
        */

        const char* pszTimestamp = "Bitcoin ... another big boost - CNBC";
        CTransaction txNew;
        txNew.nTime = 1514844000; // GMT: Monday, January 1, 2018 10:00:00 PM
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << 42 << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("045ae8e09a456a2ae88f9a2fdb9912");
        txNew.vout[0].nValue = 0;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1514844000; // GMT: Monday, January 1, 2018 10:00:00 PM
        genesis.nBits    = 520159231;
        genesis.nNonce   = 1006718;

        /*
        hashGenesisBlock = uint256("0x01");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    ++genesis.nTime;
                }
            }

        }

        hashGenesisBlock = genesis.GetHash();

        cout << "mainnet.genesis : \n" << genesis.ToString() << endl;
        cout << "mainnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
        cout << "mainnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
        cout << "mainnet.genesis.nTime: " << genesis.nTime << endl;
        cout << "mainnet.genesis.nNonce: " << genesis.nNonce << endl;
        */
       
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0000b587d86da35102be091d9d303851d53130a70375a2ae6b8827ca18feb00d"));
        assert(genesis.hashMerkleRoot == uint256("10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,55);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,152);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();;

        vSeeds.push_back(CDNSSeedData("0",  "54.37.233.45"));
        vSeeds.push_back(CDNSSeedData("1",  "142.44.246.195"));
	    //vSeeds.push_back(CDNSSeedData("2",  ""));
	    //vSeeds.push_back(CDNSSeedData("3",  ""));
        //vSeeds.push_back(CDNSSeedData("4",  ""));
        //vSeeds.push_back(CDNSSeedData("5",  ""));
        //vSeeds.push_back(CDNSSeedData("6",  ""));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        //strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        //strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "PXeU4EGgDEnFJHuNptvqsWHs4qsdYg3Ypu";
        nLastPOWBlock = 5184000;
        nPOSStartBlock = 10000;
        //nStakeMaxAge = 9999; // 9999 days
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x6b;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0x25;
        pchMessageStart[3] = 0x75;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("04344278bdac5f6e1e1711a3672a5002e54369b984c97df9d36e5aa2123dec228e85da0b88f3a38ba62746a1ca20726dd73a806767620c830ffb99ab1e6c45a778");
        nDefaultPort = 20062;
        nRPCPort = 20063;
        strDataDir = "testnet";

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //

        /*
        testnet.genesis : 
        CBlock(hash=0000171a86f5d5a6d2038d0cfd270f065cbecaa8ea3b78cc3912b90468df386e, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4, nTime=1514844000, nBits=1f00ffff, nNonce=300106, vtx=1, vchBlockSig=)
        Coinbase(hash=10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4, nTime=1514844000, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24426974636f696e202e2e2e20616e6f746865722062696720626f6f7374202d20434e4243)
        CTxOut(nValue=0.00, scriptPubKey=045ae8e09a456a2ae88f9a2fdb9912)

        vMerkleTree:  10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4

        testnet.genesis.GetHash(): 0000171a86f5d5a6d2038d0cfd270f065cbecaa8ea3b78cc3912b90468df386e
        testnet.genesis.hashMerkleRoot: 10a0a2b5415e856e2920e10add027cf52aa801a046fc466285555c3c7603dff4
        testnet.genesis.nTime: 1514844000
        testnet.genesis.nNonce: 300106
        */

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1514844000; // GMT: Monday, January 1, 2018 10:00:00 PM
        genesis.nBits  = 520159231;
        genesis.nNonce = 300106;

        /*
        hashGenesisBlock = uint256("0x01");
        if (true && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    ++genesis.nTime;
                }
            }

        }

        hashGenesisBlock = genesis.GetHash();

        cout << "testnet.genesis : \n" << genesis.ToString() << endl;
        cout << "testnet.genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
        cout << "testnet.genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
        cout << "testnet.genesis.nTime: " << genesis.nTime << endl;
        cout << "testnet.genesis.nNonce: " << genesis.nNonce << endl;
        */

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0000171a86f5d5a6d2038d0cfd270f065cbecaa8ea3b78cc3912b90468df386e"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();;
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();;

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 5184000;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
