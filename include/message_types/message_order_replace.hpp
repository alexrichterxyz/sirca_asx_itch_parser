#ifndef MESSAGE_ORDER_REPLACE_HPP
#define MESSAGE_ORDER_REPLACE_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_order_replace : public message<T> {
	public:
	inline message_order_replace(const T &message_str);
	inline std::int64_t order_id() const;
	inline std::int32_t order_book_id() const;
	inline side_t side() const;
	inline std::int32_t order_book_position() const;
	inline std::int64_t quantity() const;
	inline std::int32_t price() const;
	inline int exchange_order_type() const;
	inline lot_type_t lot_type() const;
	inline const T &symbol() const;
	inline bool is_snapshot() const;
};
} // namespace asxitch

#include "../hex.hpp"

template <class T>
asxitch::message_order_replace<T>::message_order_replace(const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
std::int64_t asxitch::message_order_replace<T>::order_id() const {
	return asxitch::hex8toull(asxitch::message<T>::component_at(2));
}

template <class T>
std::int32_t asxitch::message_order_replace<T>::order_book_id() const {
	return std::stoul(asxitch::message<T>::component_at(3).data());
}

template <class T>
asxitch::side_t asxitch::message_order_replace<T>::side() const {
	return static_cast<asxitch::side_t>(
	    asxitch::message<T>::component_at(4)[0]);
}

template <class T>
std::int32_t asxitch::message_order_replace<T>::order_book_position() const {
	return std::stoul(asxitch::message<T>::component_at(5).data());
}

template <class T>
std::int64_t asxitch::message_order_replace<T>::quantity() const {
	return std::stoull(asxitch::message<T>::component_at(6).data());
}

template <class T>
std::int32_t asxitch::message_order_replace<T>::price() const {
	return std::stoul(asxitch::message<T>::component_at(7).data());
}

template <class T>
int asxitch::message_order_replace<T>::exchange_order_type() const {
	return std::stoi(asxitch::message<T>::component_at(8).data());
}

template <class T> const T &asxitch::message_order_replace<T>::symbol() const {
	return asxitch::message<T>::component_at_back(1);
}

template <class T> bool asxitch::message_order_replace<T>::is_snapshot() const {
	return asxitch::message<T>::component_at(0).substr(11) ==
	       "00:00:00.000000000";
}

#endif // MESSAGE_ORDER_REPLACE_HPP