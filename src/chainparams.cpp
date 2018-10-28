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
        pchMessageStart[0] = 0xac;
        pchMessageStart[1] = 0xcd;
        pchMessageStart[2] = 0xdf;
        pchMessageStart[3] = 0xdc;
	    vAlertPubKey = ParseHex("4104b437c52883287d86546a3ace0a6758be3b6561442a1ef62b55a418c9028063a94bb302454bcb14b736853d1e1fed46892c23cf254bd0c43f1a3a2165930976f4ac");
       // vAlertPubKey = ParseHex("0424d4d59ad30c33510d2597aef881965e079ca1d42778199bb20ac40f1a19e7e28db32422464e51c35fc41672f2d64ff5aba85f573fefc351515d5b3b4e6143ee");
				
	
        nDefaultPort = 27005;
        nRPCPort = 27006;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        const char* pszTimestamp = "https://www.cnbc.com/2018/10/25/if-you-put-1000-dollars-in-bitcoin-5-years-ago-heres-what-youd-have-now.html - Crypt0N1nj4";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
	    CTransaction txNew(1, 1514031852, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
	    genesis.nTime    = 1540576314;
	    genesis.nBits    = 0x1e0ffff1;
	    genesis.nNonce   = 330899;

	    hashGenesisBlock = genesis.GetHash();

	    assert(hashGenesisBlock == uint256("00000b7f4681c5b06a477a6d7848ad3cb0ab5492e2500aaa10ab6be8bf897eef"));
	    assert(genesis.hashMerkleRoot == uint256("d7ca10a17be21459dfa93e16161f0eee84348ff5873f3b9aa4585afc58fb9fb6"));

        
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,76);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,85);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,153);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

	    vSeeds.push_back(CDNSSeedData("1", "bitrewards.io"));
	    vSeeds.push_back(CDNSSeedData("144.202.71.115", "144.202.71.115"));  //SINGLE NODE ADDRESS
	    vSeeds.push_back(CDNSSeedData("207.246.73.35", "207.246.73.35")); //SINGLE NODE ADDRESS
	    vSeeds.push_back(CDNSSeedData("45.32.249.54", "45.32.249.54")); //SINGLE NODE ADDRESS
		
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;
        strDarksendPoolDummyAddress = "VBuJBEiwMTaPu89DaTDk4GAffYEWYCMjjM";
        nLastPOWBlock = 300;
        nPOSStartBlock = 2;
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
        pchMessageStart[0] = 0xdc;
        pchMessageStart[1] = 0xcd;
        pchMessageStart[2] = 0xfc;
        pchMessageStart[3] = 0xdc;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
	    vAlertPubKey = ParseHex("4104b4d1d9550ac6ccdd9c4c8e6c2027fedc55d7efd94f69e77e77c2baf412aa0cce6fd8c052bd53590c8f71e772f685d73fbedaf19e5aea7280d9dfa505577bea26ac");
        nDefaultPort = 17001;
        nRPCPort = 17002;
        strDataDir = "testnet";

        const char* pszTimestamp = "Bitrewards MN Testnet - Crypt0N1nj4";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
	    CTransaction txNew(1, 1513113407, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
	    genesis.nTime    = 1540576334;
	    genesis.nBits    = 0x1e0ffff0;
	    genesis.nNonce   = 413780;
  

		       hashGenesisBlock = genesis.GetHash();
	
  
	    assert(hashGenesisBlock == uint256("000002fd1f6faf3c58e00357ee2dc37f53276e197676330e100d2c81c83eb992"));
	    assert(genesis.hashMerkleRoot == uint256("32cf850f16580aef9316c2f428e1b8c503da6a2f3623d01c45534bffe7b9646a"));


				
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,239);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,40);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
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
