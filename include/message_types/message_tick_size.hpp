#ifndef MESSAGE_TICK_SIZE_HPP
#define MESSAGE_TICK_SIZE_HPP
#include "../message.hpp"
#include <cstdint>

namespace asxitch {
template <class T> class message_tick_size : public message<T> {
	protected:
	public:
	inline message_tick_size(const T &message_str);
	inline std::int32_t order_book_id() const;
	inline std::int64_t tick_size() const;
	inline std::int32_t price_from() const;
	inline std::int32_t price_to() const;
	inline const T &symbol() const;
};
} // namespace asxitch

template <class T>
asxitch::message_tick_size<T>::message_tick_size(const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
std::int32_t asxitch::message_tick_size<T>::order_book_id() const {
    return std::stoul(asxitch::message<T>::component_at(2).data());
}

template <class T>
std::int64_t asxitch::message_tick_size<T>::tick_size() const {
    return std::stoull(asxitch::message<T>::component_at(3).data());
}

template <class T>
std::int32_t asxitch::message_tick_size<T>::price_from() const {
    return std::stoul(asxitch::message<T>::component_at(4).data());
}
template <class T>
std::int32_t asxitch::message_tick_size<T>::price_to() const {
    return std::stoul(asxitch::message<T>::component_at(5).data());
}

template <class T> const T &asxitch::message_tick_size<T>::symbol() const {
    return std::stoul(asxitch::message<T>::component_at_back(1).data());
}

#endif // MESSAGE_TICK_SIZE_HPP