#pragma once

#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

using namespace eosio;
using std::string;

class [[eosio::contract("nft")]] nft : public contract {
    public:
        using contract::contract;

        [[eosio::action]] void createcol(const name& author, uint16_t royalty, const string& data);
        [[eosio::action]] void createasset(uint64_t collection_id, uint64_t supply, uint64_t max_supply, const string& data);

        [[eosio::action]] void mint(const name& to, uint64_t asset_id, int64_t amount, const string& memo);
        [[eosio::action]] void burn(uint64_t asset_id, int64_t amount, const string& memo);
        [[eosio::action]] void transfer(const name& from, const name& to, uint64_t asset_id, int64_t amount, const string& memo);

        // events
        [[eosio::action]] void collog(uint64_t collection_id, name author, uint16_t royalty, const string& data) { require_auth(_self); }
        [[eosio::action]] void assetlog(uint64_t asset_id, uint64_t collection_id, uint64_t max_supply, const string& data) { require_auth(_self); }
        [[eosio::action]] void transferlog(const name& from, const name& to, uint64_t asset_id, int64_t amount, int64_t from_balance, int64_t to_balance, const string& memo) { require_auth(_self); }

    private:
        const permission_level self_perm = permission_level{_self, "active"_n};

        struct [[eosio::table]] nft_collection {
            uint64_t  collection_id;
            name    author;
            uint16_t    royalty;
            string     data;
            uint64_t primary_key()const { return collection_id; }
        };

        struct [[eosio::table]] nft_asset {
            uint64_t  asset_id;
            uint64_t  collection_id;
            uint64_t    supply;
            uint64_t    max_supply;
            string     data;
            uint64_t primary_key()const { return asset_id; }
        };

        struct [[eosio::table]] nft_balance {
            uint64_t    asset_id;
            int64_t    balance;

            uint64_t primary_key()const { return asset_id; }
        };

        typedef eosio::multi_index< "collections"_n, nft_collection> collections;
        typedef eosio::multi_index< "assets"_n, nft_asset> assets;
        typedef eosio::multi_index< "balances"_n, nft_balance > balances;

        int64_t sub_balance( const name& owner, uint64_t asset_id, int64_t amount );
        int64_t add_balance( const name& owner, uint64_t asset_id, int64_t amount, const name& ram_payer );
        
};