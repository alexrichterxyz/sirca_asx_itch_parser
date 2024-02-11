#ifndef MESSAGE_TRADE_MESSAGE_IDENTIFIER_HPP
#define MESSAGE_TRADE_MESSAGE_IDENTIFIER_HPP
#include "../message.hpp"
#include <optional>
#include <cstdint>

namespace asxitch {
template <class T> class message_trade_message_identifier : public message<T> {
	public:
	inline  message_trade_message_identifier(const T &message_str);
    inline const T &match_id() const;
    inline std::optional<side_t> side() const;
    inline std::int64_t quantity() const;
    inline std::int32_t order_book_id() const;
    inline std::int32_t trade_price() const;
    inline const T &participant_id_owner() const;
    inline const T &participant_id_counterparty() const;
    inline bool printable() const;
    inline bool occured_at_cross() const;
    inline const T &symbol() const;
};
} // namespace asxitch

template <class T>
asxitch::message_trade_message_identifier<T>::message_trade_message_identifier(
    const T &message_str)
    : asxitch::message<T>(message_str) {}


    template <class T> const T &asxitch::message_trade_message_identifier<T>::match_id() const {
        return asxitch::message<T>::component_at(2);
    }

    template <class T> std::optional<asxitch::side_t> asxitch::message_trade_message_identifier<T>::side() const {
        const T &side = asxitch::message<T>::component_at(3);
        return side == "" ? std::nullopt : static_cast<asxitch::side_t>(side[0]);
    }

    template <class T> std::int64_t asxitch::message_trade_message_identifier<T>::quantity() const {
        return std::stoull(asxitch::message<T>::component_at(4).data());
    }

    template <class T> std::int32_t asxitch::message_trade_message_identifier<T>::order_book_id() const {
        return std::stoul(asxitch::message<T>::component_at(5).data());
    }

    template <class T> std::int32_t asxitch::message_trade_message_identifier<T>::trade_price() const {
        return std::stoi(asxitch::message<T>::component_at(6).data());
    }

    template <class T> const T &asxitch::message_trade_message_identifier<T>::participant_id_owner() const {
        return asxitch::message<T>::component_at(7);
    }

    template <class T> const T &asxitch::message_trade_message_identifier<T>::participant_id_counterparty() const {
        return asxitch::message<T>::component_at(8);
    }

    template <class T> bool asxitch::message_trade_message_identifier<T>::printable() const{
        return asxitch::message<T>::component_at(9)[0] == 'Y';
    }

    template <class T> bool asxitch::message_trade_message_identifier<T>::occured_at_cross() const {
        return asxitch::message<T>::component_at(10)[0] == 'Y';
    }

    template <class T> const T &asxitch::message_trade_message_identifier<T>::symbol() const {
        return asxitch::message<T>::component_at_back(1);
    }

#endif // MESSAGE_TRADE_MESSAGE_IDENTIFIER_HPP