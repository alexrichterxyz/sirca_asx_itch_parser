#ifndef MESSAGE_COMBINATION_ORDER_BOOK_DIRECTORY_HPP
#define MESSAGE_COMBINATION_ORDER_BOOK_DIRECTORY_HPP
#include "message_order_book_directory.hpp"

namespace asxitch {
template <class T>
class message_combination_order_book_directory : public message<T> {
	public:
	inline message_combination_order_book_directory(const T &message_str);
	inline const T &leg_symbol(const std::size_t leg_idx) const;
	inline side_t leg_side(
	    const std::size_t leg_idx) const; // todo: sell is C not S
	inline std::int32_t leg_ratio(const size_t leg_idx) const;
};
} // namespace asxitch

template <class T>
asxitch::message_combination_order_book_directory<
    T>::message_combination_order_book_directory(const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
const T &asxitch::message_combination_order_book_directory<T>::leg_symbol(
    const std::size_t leg_idx) const {
	return asxitch::message<T>::component_at(14 + leg_idx * 3);
}

template <class T>
asxitch::side_t asxitch::message_combination_order_book_directory<T>::leg_side(
    const std::size_t leg_idx) const {
	const char b_or_c =
	    asxitch::message<T>::component_at(15 + leg_idx * 3)[0];
	return b_or_c == 'B' ? asxitch::side_t::BUY : asxitch::side_t::SELL;
}

template <class T>
std::int32_t asxitch::message_combination_order_book_directory<T>::leg_ratio(
    const size_t leg_idx) const {
	return asxitch::message<T>::component_at(16 + leg_idx * 3);
}

#endif // MESSAGE_COMBINATION_ORDER_BOOK_DIRECTORY_HPP