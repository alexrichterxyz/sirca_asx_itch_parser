#ifndef TIME_HPP
#define TIME_HPP
#include <chrono>
namespace asxitch {

template <class T>
inline void get_datetime(const T &timestamp_str, const std::tm &datetime);

template <class T>
inline std::chrono::nanoseconds get_nanoseconds(const T &timestamp_str);

template <class T>
inline std::chrono::nanoseconds get_ns_timestamp(const T &timestamp_str);

} // namespace asxitch

#include <charconv>

template <class T>
void asxitch::get_datetime(const T &timestamp_str, std::tm &datetime) {
	// parse 2024-01-04 00:00:00.000000000
	int year, month;
	std::from_chars(timestamp_str.data(), timestamp_str.data() + 4, year);
	std::from_chars(
	    timestamp_str.data() + 5, timestamp_str.data() + 7, month);
	datetime.tm_year = year - 1900; // year since 1900
	datetime.tm_mon = month - 1; // month, from 0 (January) to 11 (December)
	std::from_chars(timestamp_str.data() + 8, timestamp_str.data() + 10,
	    datetime.tm_mday);
	std::from_chars(timestamp_str.data() + 11, timestamp_str.data() + 13,
	    datetime.tm_hour);
	std::from_chars(timestamp_str.data() + 14, timestamp_str.data() + 16,
	    datetime.tm_min);
	std::from_chars(timestamp_str.data() + 17, timestamp_str.data() + 19,
	    datetime.tm_sec);
}

template <class T>
std::chrono::nanoseconds asxitch::get_nanoseconds(const T &timestamp_str) {
	int nanosecond = 0;
	std::from_chars(
	    timestamp_str.data() + 20, timestamp_str.data() + 29, nanosecond);
	return std::chrono::nanoseconds(nanosecond);
}

template <class T>
std::chrono::nanoseconds asxitch::get_ns_timestamp(const T &timestamp_str) {
	// parse 2024-01-04 00:00:00.000000000
	std::tm datetime = {};
	asxitch::get_datetime(timestamp_str, datetime);
	return std::chrono::seconds(std::mktime(&datetime)) +
	       asxitch::get_nanoseconds(timestamp_str);
}

#endif // TIME_HPP