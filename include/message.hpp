#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include <ctime>

namespace asxitch {

enum class side_t : char { BUY = 'B', SELL = 'S' };

enum class exchange_order_type_t {
	MARKET_BID = 4,
	PRICE_STABILIZATION = 8,
	UNDISCLOSED = 32
};

enum class lot_type_t {
	UNDEFINED = 0,
	ODD_LOT = 1,
	ROUND_LOT = 2,
	BLOCK_LOT = 3,
	ALL_OR_NONE_LOT = 4
};

enum class message_type_t : char {
	ADD_ORDER_NO_PARTICIPANT = 'A',
	ORDER_EXECUTED_WITH_PRICE = 'C',
	ORDER_DELETE = 'D',
	ORDER_EXECUTED = 'E',
	ADD_ORDER_WITH_PARTICIPANT = 'F',
	TICK_SIZE = 'L',
	COMBINATION_ORDER_BOOK_DIRECTORY = 'M',
	ORDER_BOOK_STATE = 'O',
	TRADE_MESSAGE_IDENTIFIER = 'P',
	ORDER_BOOK_DIRECTORY = 'R',
	SYSTEM_EVENT = 'S',
	SECONDS = 'T',
	ORDER_REPLACE = 'U',
	EQUILIBRIUM_PRICE_UPDATE = 'Z',
};

template <class T> inline message_type_t get_message_type(const T &message);

template <class T>
inline std::chrono::nanoseconds get_message_timestamp(const T &message);

template <class T>
inline void get_message_datetime(const T &message, std::tm &datetime);


template <class T> inline std::optional<T> get_symbol(const T &message);

template <class T> class message {
	protected:
	const std::vector<T> m_components;
	inline const T &component_at(const std::size_t idx) const;
	inline const T &component_at_back(const std::size_t idx) const;

	public:
	inline message(const T &message);
	inline message_type_t type() const;
	inline void datetime(std::tm &datetime) const;
	inline std::chrono::nanoseconds timestamp() const;
	inline std::size_t sequence_number() const;
};

template <class T> std::unique_ptr<message<T>> make_message(const T &message);
} // namespace asxitch

#include "csv.hpp"
#include "time.hpp"
#include <string_view>

template <class T>
asxitch::message_type_t asxitch::get_message_type(const T &message) {
	return static_cast<message_type_t>(message[30]);
}

template <class T>
std::chrono::nanoseconds asxitch::get_message_timestamp(const T &message) {
	const std::string_view timestamp_str(message.data(), 29);
	return asxitch::get_ns_timestamp(timestamp_str);
}

template <class T>
void asxitch::get_message_datetime(const T &message, std::tm &datetime) {
	const std::string_view timestamp_str(message.data(), 29);
	asxitch::get_datetime(timestamp_str, datetime);
}

template <class T>
asxitch::message<T>::message(const T &message_str)
    : m_components(asxitch::split_string(message_str)) {}

template <class T>
const T &asxitch::message<T>::component_at(const std::size_t idx) const {
	return m_components[idx];
}

template <class T>
const T &asxitch::message<T>::component_at_back(const std::size_t idx) const {
	return m_components[m_components.size() - idx - 1];
}

template <class T> asxitch::message_type_t asxitch::message<T>::type() const {
	return static_cast<asxitch::message_type_t>(m_components[1][0]);
}

template <class T> std::chrono::nanoseconds asxitch::message<T>::timestamp() const {
	return asxitch::get_ns_timestamp(m_components[0]);
}

template <class T> void asxitch::message<T>::datetime(std::tm &datetime) const {
	asxitch::get_datetime(m_components[0], datetime);
}

template <class T> std::size_t asxitch::message<T>::sequence_number() const {
	return std::stoull(asxitch::message<T>::component_at_back(0).data());
}

template <class T> std::optional<T> asxitch::get_symbol(const T &message) {

	switch (get_message_type(message)) {
	case asxitch::message_type_t::TICK_SIZE:
	case asxitch::message_type_t::ORDER_BOOK_STATE:
	case asxitch::message_type_t::ADD_ORDER_NO_PARTICIPANT:
	case asxitch::message_type_t::ADD_ORDER_WITH_PARTICIPANT:
	case asxitch::message_type_t::ORDER_DELETE:
	case asxitch::message_type_t::EQUILIBRIUM_PRICE_UPDATE:
	case asxitch::message_type_t::ORDER_EXECUTED:
	case asxitch::message_type_t::ORDER_EXECUTED_WITH_PRICE:
	case asxitch::message_type_t::TRADE_MESSAGE_IDENTIFIER:
		return asxitch::rvalue_at(message, 1);
	default:
		return std::nullopt;
	}
}

#include "message_types/message_add_order_no_participant.hpp"
#include "message_types/message_add_order_with_participant.hpp"
#include "message_types/message_combination_order_book_directory.hpp"
#include "message_types/message_equilibrium_price_update.hpp"
#include "message_types/message_order_book_directory.hpp"
#include "message_types/message_order_book_state.hpp"
#include "message_types/message_order_delete.hpp"
#include "message_types/message_order_executed.hpp"
#include "message_types/message_order_executed_with_price.hpp"
#include "message_types/message_order_replace.hpp"
#include "message_types/message_seconds.hpp"
#include "message_types/message_system_event.hpp"
#include "message_types/message_tick_size.hpp"
#include "message_types/message_trade_message_identifier.hpp"

template <class T>
std::unique_ptr<asxitch::message<T>> asxitch::make_message(const T &message) {
	std::unique_ptr<asxitch::message<T>> message_ptr = nullptr;

	switch (asxitch::get_message_type(message)) {
	case asxitch::message_type_t::SECONDS:
		message_ptr =
		    std::make_unique<asxitch::message_seconds<T>>(message);
		break;
	case asxitch::message_type_t::SYSTEM_EVENT:
		message_ptr =
		    std::make_unique<asxitch::message_system_event<T>>(message);
		break;
	case asxitch::message_type_t::ORDER_BOOK_DIRECTORY:
		message_ptr =
		    std::make_unique<asxitch::message_order_book_directory<T>>(
			message);
		break;
	case asxitch::message_type_t::TICK_SIZE:
		message_ptr =
		    std::make_unique<asxitch::message_tick_size<T>>(message);
		break;
	case asxitch::message_type_t::ORDER_BOOK_STATE:
		message_ptr =
		    std::make_unique<asxitch::message_order_book_state<T>>(
			message);
		break;
	case asxitch::message_type_t::ADD_ORDER_NO_PARTICIPANT:
		message_ptr = std::make_unique<
		    asxitch::message_add_order_no_participant<T>>(message);
		break;
	case asxitch::message_type_t::ADD_ORDER_WITH_PARTICIPANT:
		message_ptr = std::make_unique<
		    asxitch::message_add_order_with_participant<T>>(message);
		break;
	case asxitch::message_type_t::ORDER_DELETE:
		message_ptr =
		    std::make_unique<asxitch::message_order_delete<T>>(message);
		break;
	case asxitch::message_type_t::EQUILIBRIUM_PRICE_UPDATE:
		message_ptr = std::make_unique<
		    asxitch::message_equilibrium_price_update<T>>(message);
		break;
	case asxitch::message_type_t::ORDER_EXECUTED:
		message_ptr =
		    std::make_unique<asxitch::message_order_executed<T>>(
			message);
		break;
	case asxitch::message_type_t::ORDER_EXECUTED_WITH_PRICE:
		message_ptr = std::make_unique<
		    asxitch::message_order_executed_with_price<T>>(message);
		break;
	case asxitch::message_type_t::COMBINATION_ORDER_BOOK_DIRECTORY:
		message_ptr = std::make_unique<
		    asxitch::message_combination_order_book_directory<T>>(
		    message);
		break;
	case asxitch::message_type_t::TRADE_MESSAGE_IDENTIFIER:
		message_ptr = std::make_unique<
		    asxitch::message_trade_message_identifier<T>>(message);
		break;
	case asxitch::message_type_t::ORDER_REPLACE:
		message_ptr =
		    std::make_unique<asxitch::message_order_replace<T>>(
			message);
		break;
	default:
		break;
	}

	return message_ptr;
}

#endif // MESSAGE_HPP