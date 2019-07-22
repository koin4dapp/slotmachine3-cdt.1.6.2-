/*
created by koin4dapp.appspot.com
(bettors community token)
warning, this is only for learning purpose, use it as your own risk
*/

#include <eosio/transaction.hpp>
#include <eosio/crypto.hpp>
#include <string>

using namespace eosio;

class random {
private:
    uint64_t seed;

public:
    void init(uint64_t initseed) {
        auto s = read_transaction(nullptr,0);
        char *tx = (char *)malloc(s);
        read_transaction(tx, s);  //packed_trx
        checksum256 result;
        result = sha256(tx, s);   //txid
        
        auto hash=result.extract_as_byte_array();
        
        seed = (hash[7]<<8 || hash[6] << 8 || hash[5] << 8 || hash[4] << 8 || hash[3] << 8 || hash[2] << 8 || hash[1] << 8 || hash[0]) 
          ^ initseed
          ^ (tapos_block_prefix()*tapos_block_num()); //current block
    }
    
    void randraw() { 
        checksum256 result; //32bytes of 8 chunks of uint_32
        result = sha256((char *)&seed, sizeof(seed));
        auto hash=result.extract_as_byte_array();
        
        seed = (hash[7]<<8 || hash[6] << 8 || hash[5] << 8 || hash[4] << 8 || hash[3] << 8 || hash[2] << 8 || hash[1] << 8 || hash[0]);
    }
    
    uint64_t rand(uint64_t to) { //generate random 1 - to
        randraw();
        return (seed % to) + 1;
    }
    
    uint64_t getseed() {
      return (seed>>8);
    }
};
