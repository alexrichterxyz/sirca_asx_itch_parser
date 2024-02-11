#ifndef CSV_HPP
#define CSV_HPP
#include <string>
#include <string_view>
#include <vector>

namespace asxitch {

template <class T> T value_at(const T &str, const std::size_t at);

template <class T> T rvalue_at(const T &str, const std::size_t at);

template <class T>
std::vector<T> split_string(const T &str, const char delimiter = ',');

} // namespace asxitch

template <class T> T asxitch::value_at(const T &str, const std::size_t at) {
	std::size_t start = 0;
	std::size_t end = str.find(',', start);
	std::size_t current_at = 0;

	while (current_at < at) {
		start = end + 1;
		end = str.find(',', start);
		current_at++;
	}

	return str.substr(start, end - start);
}

template <class T> T asxitch::rvalue_at(const T &str, const std::size_t at) {
	std::size_t end = str.length();
	std::size_t start = str.rfind(',', end);
	std::size_t current_at = 0;

	while (current_at < at) {
		end = start - 1;
		start = str.rfind(',', end);
		current_at++;
	}

	return str.substr(start + 1, end - start);
}

template <class T>
std::vector<T> asxitch::split_string(const T &str, const char delimiter) {
	std::vector<T> components;
	components.reserve(27); // max number of components for combination for
				// order book directory messages
	std::size_t start = 0;
	std::size_t end;

	while ((end = str.find(delimiter, start)) != std::string_view::npos) {
		components.emplace_back(str.substr(start, end - start));
		start = end + 1;
	}

	components.emplace_back(str.substr(start));
	return components;
}

#endif // #ifndef CSV_HPP