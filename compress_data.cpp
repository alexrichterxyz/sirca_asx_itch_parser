#include <fstream>
#include <iostream>
#include <cstdint>
#include "include/asxitch.hpp"

#pragma pack(push, 1)
struct order_delete_t {
    char message_type;
    long int timestamp;
	std::int64_t order_id;
    std::int32_t order_book_id;
    bool is_buy : 8;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct order_t {
    char message_type;
    long int timestamp;
	std::int64_t order_id;
    std::int32_t order_book_id;
    bool is_buy : 8;
    std::int32_t price;
    std::int64_t quantity;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct execution_t {
    char message_type;
    long int timestamp;
	std::int64_t order_id;
    std::int32_t order_book_id;
    bool is_buy : 8;
    std::int64_t quantity;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct execution_with_price_t {
    char message_type;
    long int timestamp;
	std::int64_t order_id;
    std::int32_t order_book_id;
    bool is_buy : 8;
    std::int32_t price;
    std::int64_t quantity;
};
#pragma pack(pop)

template <class T>
void write_to_file(std::fstream &fs, const T &data) {
    fs.write(reinterpret_cast<const char *>(&data), sizeof(T));
}

int main() {
    std::ifstream in_file("sample.csv");
    std::fstream out_file("compressed_sample.data", std::fstream::out | std::fstream::binary);


    if (!in_file.is_open() || !out_file.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    // string to hold message contents
    std::string message_str;
    
    // loop through each line
    while(std::getline(in_file, message_str)) { 

        // ignore all irrelevant messages
        switch(asxitch::get_message_type(message_str)) {
            case asxitch::message_type_t::ADD_ORDER_NO_PARTICIPANT: {
                const std::string_view message_view(message_str);
                const asxitch::message_add_order_no_participant message(message_view);
                order_t order {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY,
                    message.price(),
                    message.quantity()
                };
                write_to_file(out_file, order);
                break;
            }
            case asxitch::message_type_t::ADD_ORDER_WITH_PARTICIPANT: {
                const std::string_view message_view(message_str);
                const asxitch::message_add_order_with_participant message(message_view);
                order_t order {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY,
                    message.price(),
                    message.quantity()
                };
                write_to_file(out_file, order);
                break;
            }
            case asxitch::message_type_t::ORDER_EXECUTED: {
                const std::string_view message_view(message_str);
                const asxitch::message_order_executed message(message_view);
                execution_t execution {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY,
                    message.executed_quantity()
                };

                write_to_file(out_file, execution);
                break;
            }
            case asxitch::message_type_t::ORDER_EXECUTED_WITH_PRICE: {
                const std::string_view message_view(message_str);
                const asxitch::message_order_executed_with_price message(message_view);
                execution_with_price_t execution {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY,
                    message.trade_price(),
                    message.executed_quantity()
                };

                write_to_file(out_file, execution);

                break;
            }
            case asxitch::message_type_t::ORDER_REPLACE: {
                const std::string_view message_view(message_str);
                const asxitch::message_order_replace message(message_view);
                order_t order {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY,
                    message.price(),
                    message.quantity()
                };
                write_to_file(out_file, order);
                break;
            }
            case asxitch::message_type_t::ORDER_DELETE: {
                const std::string_view message_view(message_str);
                const asxitch::message_order_delete message(message_view);
                order_delete_t order_delete {
                    static_cast<char>(message.type()),
                    message.timestamp().count(),
                    message.order_id(),
                    message.order_book_id(),
                    message.side() == asxitch::side_t::BUY
                };
                write_to_file(out_file, order_delete);
                break;
            }
            default:
                break;
        }        
    }

    in_file.close();
    out_file.close();

    return 0;
}