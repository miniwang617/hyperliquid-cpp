
#include <cqs/driver/realtime_driver.hpp>
#include <cqs/types/stringlet.hpp>
#include <cqs/util/initialize.hpp>
#include <cqs/util/timer.hpp>
#include <json/json.hpp>

#include <cqs/crypto_trade_api/HyperLiquidTradeApi.hpp>




int main(int argc, char* argv[]) 
{
    std::cout << "*******************************************************" << std::endl;    
    std::cout << "usage:  ./hltdapi 'SWAP_HYPEUSD@HYPERL' 25 0.5        " << std::endl;    
    std::cout << "*******************************************************" << std::endl;
    cqs::util::initialize(argv[0],true,1,"./logs",2);
    auto& driver = cqs::driver::realtime_driver;
    auto symbol = cqs::types::exchange_symbol_t(argv[1]);
    double px = cqs::util::parse_double(argv[2]);
    double sz = cqs::util::parse_double(argv[3]);
    cqs::crypto_trade_api::HyperLiquidTradeApi api0(driver,
                                                   "api.hyperliquid.xyz", // api url  !! host 不要加https://
                                                   "account_id",
                                                   "your vault_address", // vault_address
                                                   "your api_secret", // api_secret
                                                   0);
    api0.initialize();
    api0.subscribe({symbol});

    driver.add_poller([&](int64_t epoch_us){
        static cqs::util::IntervalCounter counter(5);
        if(counter.on_interval())
        {
            cqs::types::LO lo(symbol, px,sz,cqs::util::seqnum++,true);
            LOG(INFO) << " [epoch_us] " << epoch_us << " [evt] ADD " << lo;
            api0.add_order(lo.symbol,lo.oid,lo.px,lo.sz,"LIMIT");
        }
    });

    driver.register_event<cqs::types::Ack>([&](const cqs::types::Ack& ack, int64_t epoch_us){
        LOG(INFO) << " [epoch_us] " << epoch_us << " [evt] ACK " << ack;
        api0.del_order(ack.symbol,ack.oid);
    });

    driver.register_event<cqs::types::Cancel>([](const cqs::types::Cancel& can, int64_t epoch_us){
        LOG(INFO) << " [epoch_us] " << epoch_us << " [evt] CXL " << can;
    });
    
    driver.register_event<cqs::types::Reject>([](const cqs::types::Reject& rej, int64_t epoch_us){
        LOG(INFO) << " [epoch_us] " << epoch_us << " [evt] REJ " << rej;
    });

    driver.run(0); 

    return 0;
}
    