#include <vector>
#include <ctime>
#include <json/json.hpp>
#include <cqs/util/timer.hpp>

#include <hyperL/hyperl.hpp>

int main()
{
    cqs::util::Timer timer;
    dev::Secret wallet = dev::Secret("your api_secret");
    /*
    nlohmann::json action = {
        {"type", "order"},
        {"orders",
            {
            {"a", 150},
            {"b", true},
            {"p", "10"}, 
            {"s", "0.01"},
            {"r", false},
            {"t", {"limit", {"tif", "Gtc"}}},
            }},
        {"grouping", "na"},
    };
    dev::bytes nonce = dev::fromHex("0x0000000000000000000000000000000000000000000000000000000000000000");
    dev::bytes connection_id = hyperl::action_hash(action, vault_address, nonce);
    上面的代码可以得到的connection_id就是0xde6c4037798a4434ca03cd05f00e3b803126221375cd1e7eaaaf041768be06eb。
    */


    dev::bytes connection_id = dev::fromHex("0xde6c4037798a4434ca03cd05f00e3b803126221375cd1e7eaaaf041768be06eb");

    std::string sig = hyperl::sign_l1_action(connection_id,wallet);
    std::cout << "signature_cpp   : " << sig<< std::endl;
    return 0;
}
