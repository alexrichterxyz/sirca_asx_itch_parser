#ifndef MESSAGE_EQUILIBRIUM_PRICE_UPDATE
#define MESSAGE_EQUILIBRIUM_PRICE_UPDATE
#include "../message.hpp"

namespace asxitch {
template <class T> class message_equilibrium_price_update : public message<T> {
	public:
	inline message_equilibrium_price_update(const T &message_str);
	inline std::int32_t order_book_id() const;
	inline std::int64_t bid_quantity() const;
	inline std::int64_t ask_quantity() const;
	inline std::int32_t equilibrium_price() const;
	inline std::int32_t bid_price() const;
	inline std::int32_t ask_price() const;
	inline std::int64_t best_bid_quantity() const;
	inline std::int64_t best_ask_quantity() const;
	inline const T &symbol() const;
};
} // namespace asxitch

template <class T>
asxitch::message_equilibrium_price_update<T>::message_equilibrium_price_update(
    const T &message_str)
    : asxitch::message<T>(message_str) {}

template <class T>
std::int32_t
asxitch::message_equilibrium_price_update<T>::order_book_id() const {
	return std::stoul(asxitch::message<T>::component_at(2).data());
}

template <class T>
std::int64_t
asxitch::message_equilibrium_price_update<T>::bid_quantity() const {
	return std::stoull(asxitch::message<T>::component_at(3).data());
}

template <class T>
std::int64_t
asxitch::message_equilibrium_price_update<T>::ask_quantity() const {
	return std::stoull(asxitch::message<T>::component_at(4).data());
}

template <class T>
std::int32_t asxitch::message_equilibrium_price_update<T>::equilibrium_price() const {
	return std::stoi(asxitch::message<T>::component_at(5).data());
}

template <class T>
std::int32_t asxitch::message_equilibrium_price_update<T>::bid_price() const {
	return std::stoi(asxitch::message<T>::component_at(6).data());
}
template <class T>
std::int32_t asxitch::message_equilibrium_price_update<T>::ask_price() const {
	return std::stoi(asxitch::message<T>::component_at(7).data());
}
template <class T>
std::int64_t
asxitch::message_equilibrium_price_update<T>::best_bid_quantity() const {
	return std::stoull(asxitch::message<T>::component_at(8).data());
}
template <class T>
std::int64_t
asxitch::message_equilibrium_price_update<T>::best_ask_quantity() const {
	return std::stoull(asxitch::message<T>::component_at(9).data());
}

template <class T>
const T &asxitch::message_equilibrium_price_update<T>::symbol() const {
	return asxitch::message<T>::component_at_bacl(1);
}

#endif // MESSAGE_EQUILIBRIUM_PRICE_UPDATE