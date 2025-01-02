

/*
 bool add_order(const cqs::types::exchange_symbol_t& symbol,
                   int64_t seqnum, 
                   double px, 
                   double size, 
                   const std::string& type) 
    
    {
        // Construct order message
        int64_t  epoch_us = cqs::util::epoch_us();

        nlohmann::json order_action;
        order_action["type"] = "order";

        nlohmann::json order;
        if(_symbol2assetid.find(symbol) != _symbol2assetid.end())
        {
            order["a"] = _symbol2assetid[symbol];         // assetid
        }
        else
        {
            LOG(FATAL) << " [symbol] " << symbol << " not subscribed!";
            return false;
        }
        order["b"] = size>0;                          // true: buy, false: sell
        char buf_px[32];
        std::sprintf(buf_px, "%.8g", px);
        char buf_sz[32];
        std::sprintf(buf_sz, "%.8g", std::fabs(size)); // "%.8g"格式说明符会自动去掉尾随零，同时保持合适的精度,确保80000转成“80000”而不是“80000.000000”
        order["p"] = std::string(buf_px);              // price
        order["s"] = std::string(buf_sz);              // size
        order["r"] = false;                           // reduce only

        nlohmann::json limit;
        limit["tif"] = "Gtc";
        order["t"]["limit"] = limit;                  // time in force
        order_action["orders"] = nlohmann::json::array({order});

        order_action["grouping"] = "na";

        int64_t timestamp = cqs::util::epoch_us()/1000;
        auto ts1 = cqs::util::epoch_us();
        dev::bytes connection_id = hyperl::action_hash_order(order_action, _vault_address, timestamp);
        auto ts2 = cqs::util::epoch_us();
        auto signature = hyperl::sign_l1_action(connection_id, _wallet);
        auto ts3 = cqs::util::epoch_us();

        // std::cout << "connection_id: " << hyperl::BinaryWriter::bytes_to_hex(connection_id) << "\nsignature: " << signature.dump() << std::endl;

        nlohmann::json payload;
        payload["action"] = order_action;
        payload["nonce"] = timestamp;
        payload["signature"] = signature;
        payload["vaultAddress"] = dev::toHex(_vault_address);
        auto ts4 = cqs::util::epoch_us();
        std::string payload_str = payload.dump();
        // std::cout << "payload_str: " << payload_str << std::endl;

        add_request(_host.c_str(),"443","/exchange",payload_str.c_str(),boost::beast::http::verb::post,seqnum);
        auto ts5 = cqs::util::epoch_us();
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            _request2lo_rest[seqnum] = cqs::types::LO(symbol,px,size,seqnum);
            // _oid2request[seqnum] = seqnum;
            // _request2event[seqnum] = 'A';
        }
        auto ts6 = cqs::util::epoch_us();

        LOG(INFO) << " [ts0] " << epoch_us << " [ts1] " << ts1 << " [ts2] " << ts2 << " [ts3] " << ts3 << " [ts4] " << ts4 << " [ts5] " << ts5 << " [ts6] " << ts6;

        return true;
    }

    void del_order(const exchange_symbol_t& symbol, int64_t clientOrderId)
    {
        nlohmann::json cancel_action;
        cancel_action["type"] = "cancel";
        nlohmann::json cancel;
        cancel["a"] = _symbol2assetid[symbol];
        cancel["o"] = _oid2exchangeoid[clientOrderId];
        cancel_action["cancels"] = nlohmann::json::array({cancel});


        int64_t timestamp = cqs::util::epoch_us()/1000;
        dev::bytes connection_id = hyperl::action_hash_cancel(cancel_action, _vault_address, timestamp);
        auto signature = hyperl::sign_l1_action(connection_id, _wallet);

        nlohmann::json payload;
        payload["action"] = cancel_action;
        payload["nonce"] = timestamp;
        payload["signature"] = signature;
        payload["vaultAddress"] = dev::toHex(_vault_address);
        std::string payload_str = payload.dump();

        add_request(_host.c_str(),"443","/exchange",payload_str.c_str(),boost::beast::http::verb::post,clientOrderId);

    }

*/