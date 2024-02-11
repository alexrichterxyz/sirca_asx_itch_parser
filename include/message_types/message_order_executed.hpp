#ifndef MESSAGE_ORDER_EXECUTED_HPP
#define MESSAGE_ORDER_EXECUTED_HPP
#include "../message.hpp"
#include "../hex.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_order_executed : public message<T> {
	public:
	inline message_order_executed(const T &message_str);
	inline std::int64_t order_id() const;
	inline std::int32_t order_book_id() const;
	inline side_t side() const;
	inline std::int64_t executed_quantity() const;
	inline int96_t match_id() const;
	inline const T &participant_id_owner() const;
	inline const T &participant_id_coutnerparty() const;
	inline const T &symbol() const;
};
} // namespace asxitch

#include <string>

template <class T>
asxitch::message_order_executed<T>::message_order_executed(const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
std::int64_t asxitch::message_order_executed<T>::order_id() const {
	return asxitch::hex8toull(asxitch::message<T>::component_at(2));
}

template <class T>
std::int32_t asxitch::message_order_executed<T>::order_book_id() const {
	return std::stoul(asxitch::message<T>::component_at(3).data());
}

template <class T>
asxitch::side_t asxitch::message_order_executed<T>::side() const {
	return static_cast<asxitch::side_t>(
	    asxitch::message<T>::component_at(4)[0]);
}

template <class T>
std::int64_t asxitch::message_order_executed<T>::executed_quantity() const {
	return std::stoull(asxitch::message<T>::component_at(5).data());
}

template <class T>
asxitch::int96_t asxitch::message_order_executed<T>::match_id() const {
	return asxitch::hex12toint96(asxitch::message<T>::component_at(6));
}

template <class T>
const T &asxitch::message_order_executed<T>::participant_id_owner() const {
	return asxitch::message<T>::component_at(7);
}

template <class T>
const T &
asxitch::message_order_executed<T>::participant_id_coutnerparty() const {
	return asxitch::message<T>::component_at(8);
}

template <class T> const T &asxitch::message_order_executed<T>::symbol() const {
	return asxitch::message<T>::component_at_back(1);
}

#endif // MESSAGE_ORDER_EXECUTED_HPP