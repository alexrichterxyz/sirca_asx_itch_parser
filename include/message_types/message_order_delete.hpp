#ifndef MESSAGE_ORDER_DELETE_HPP
#define MESSAGE_ORDER_DELETE_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_order_delete : public message<T> {
	public:
	inline message_order_delete(const T &message_str);
	inline std::int64_t order_id() const;
	inline std::int32_t order_book_id() const;
	inline side_t side() const;
	inline const T &symbol() const;
};
} // namespace asxitch

#include "../hex.hpp"

template <class T>
asxitch::message_order_delete<T>::message_order_delete(const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T> std::int64_t asxitch::message_order_delete<T>::order_id() const {
	return asxitch::hex8toull(asxitch::message<T>::component_at(2));
}

template <class T>
std::int32_t asxitch::message_order_delete<T>::order_book_id() const {
	return std::stoul(asxitch::message<T>::component_at(3).data());
}

template <class T>
asxitch::side_t asxitch::message_order_delete<T>::side() const {
	return static_cast<asxitch::side_t>(
	    asxitch::message<T>::component_at(4)[0]);
}

template <class T> const T &asxitch::message_order_delete<T>::symbol() const {
	return asxitch::message<T>::component_at_back(1);
}

#endif // MESSAGE_ORDER_DELETE_HPP