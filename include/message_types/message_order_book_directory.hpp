#ifndef MESSAGE_ORDER_BOOK_DIRECTORY_HPP
#define MESSAGE_ORDER_BOOK_DIRECTORY_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {

enum class financial_product_t {
	OPTION = 1,
	FUTURE = 3,
	CASH = 5,
	STANDARD_COMBINATION = 11
};

template <class T> class message_order_book_directory : public message<T> {
	public:
	inline message_order_book_directory(const T &message_str);
	inline std::int32_t &order_book_id() const;
	inline const T &symbol() const;
	inline const T &long_name() const;
	inline const T &isin() const;
	inline financial_product_t financial_product() const;
	inline const T &currency() const;
	inline std::int32_t price_decimals() const;
	inline std::int32_t nominal_value_decimals() const;
	inline std::int32_t odd_lot_size() const;
	inline std::int32_t round_lot_size() const;
	inline std::int32_t block_lot_size() const;
	inline std::int64_t nominal_value() const;
};
} // namespace asxitch

template <class T>
asxitch::message_order_book_directory<T>::message_order_book_directory(
    const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
std::int32_t &asxitch::message_order_book_directory<T>::order_book_id() const {
    return std::stoul(message<T>::component_at(2).data());
}

template <class T>
const T &asxitch::message_order_book_directory<T>::symbol() const {
    return message<T>::component_at(3);
}

template <class T>
const T &asxitch::message_order_book_directory<T>::long_name() const {
    return message<T>::component_at(4);
}

template <class T>
const T &asxitch::message_order_book_directory<T>::isin() const {
    return message<T>::component_at(5);
}

template <class T>
asxitch::financial_product_t
asxitch::message_order_book_directory<T>::financial_product() const {
    return static_cast<asxitch::financial_product_t>(std::stoi(message<T>::component_at(6)));
}

template <class T>
const T &asxitch::message_order_book_directory<T>::currency() const {
    return message<T>::component_at(7);
}

template <class T>
std::int32_t asxitch::message_order_book_directory<T>::price_decimals() const {
    return std::stoul(message<T>::component_at(8).data());
}

template <class T>
std::int32_t
asxitch::message_order_book_directory<T>::nominal_value_decimals() const {
    return std::stoul(message<T>::component_at(9).data());
}

template <class T>
std::int32_t asxitch::message_order_book_directory<T>::odd_lot_size() const {
    return std::stoul(message<T>::component_at(10).data());
}

template <class T>
std::int32_t asxitch::message_order_book_directory<T>::round_lot_size() const {
    return std::stoul(message<T>::component_at(11).data());
}

template <class T>
std::int32_t asxitch::message_order_book_directory<T>::block_lot_size() const {
    return std::stoul(message<T>::component_at(12).data());
}

template <class T>
std::int64_t asxitch::message_order_book_directory<T>::nominal_value() const {
    return std::stoull(message<T>::component_at(13).data());
}

#endif // MESSAGE_ORDER_BOOK_DIRECTORY_HPP