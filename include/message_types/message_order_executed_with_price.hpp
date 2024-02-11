#ifndef MESSAGE_ORDER_EXECUTED_WITH_PRICE_HPP
#define MESSAGE_ORDER_EXECUTED_WITH_PRICE_HPP
#include "message_order_executed.hpp"
#include <cstdint>

namespace asxitch {
template <class T>
class message_order_executed_with_price : public message_order_executed<T> {
	public:
	inline message_order_executed_with_price(const T &message_str);
	inline std::int32_t trade_price() const;
	inline bool occured_at_cross() const;
	inline bool printable() const;
};
} // namespace asxitch

template <class T>
asxitch::message_order_executed_with_price<
    T>::message_order_executed_with_price(const T &message_str)
    : asxitch::message_order_executed<T>(message_str) {}

template <class T>
std::int32_t
asxitch::message_order_executed_with_price<T>::trade_price() const {
	return std::stoul(asxitch::message<T>::component_at(9).data());
}

template <class T>
bool asxitch::message_order_executed_with_price<T>::occured_at_cross() const {
	return asxitch::message<T>::component_at(10)[0] == 'Y';
}

template <class T>
bool asxitch::message_order_executed_with_price<T>::printable() const {
	return asxitch::message<T>::component_at(11)[0] == 'Y';
}

#endif // MESSAGE_ORDER_EXECUTED_WITH_PRICE_HPP