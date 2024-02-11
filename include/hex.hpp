#ifndef HEX_HPP
#define HEX_HPP

namespace asxitch {

typedef struct {
	std::int32_t v[3];
} int96_t;

// convert hex strings like "00000000:00000000" to std::int64_t
template <class T> std::int64_t hex8toull(const T &hex);

// convert hex strings like "00000000:00000000:00000000" to asxitch::int96_t
template <class T> void hex12toint96(const T &hex, int96_t &val);

} // namespace asxitch

#include <iostream>

std::ostream& operator<<(std::ostream& os, const asxitch::int96_t &val) {
	// todo: make this print a proper decimal number
    return os << val.v[0] << ':' << val.v[1] << ':' << val.v[2];
}

template <class T> std::int64_t asxitch::hex8toull(const T &hex) {
	const std::string_view hex_view(hex);
	const auto hex_view1 = hex_view.substr(0, 8);
	const auto hex_view2 = hex_view.substr(9, 8);

	const std::int64_t num1 =
	    std::stoull(hex_view1.data(), nullptr, 16);
	const std::int64_t num2 =
	    std::stoull(hex_view2.data(), nullptr, 16);

	return num1 << 32 | num2;
}

template <class T>
asxitch::int96_t asxitch::hex12toint96(const T &hex) {
	const std::string_view hex_view(hex);
	const auto hex_view1 = hex_view.substr(0, 8);
	const auto hex_view2 = hex_view.substr(9, 8);
	const auto hex_view3 = hex_view.substr(18, 8);
	
    asxitch::int96_t val;
	val.v[0] = std::stoul(hex_view1.data(), nullptr, 16);
	val.v[1] = std::stoul(hex_view2.data(), nullptr, 16);
	val.v[2] = std::stoul(hex_view3.data(), nullptr, 16);
    return val;
}

#endif // #ifndef HEX_HPP