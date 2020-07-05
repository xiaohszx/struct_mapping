#ifndef STRUCT_MAPPING_F_ARRAY_H
#define STRUCT_MAPPING_F_ARRAY_H

#include <functional>
#include <limits>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "f.h"
#include "f_struct.h"

namespace struct_mapping::detail {
					
template<typename T>
class F<T, true, false> {
public:
	template<typename V>
	using Member_ptr = V T::*;

	using Iterator = typename T::iterator;

	template<typename V>
	using ValueType = typename V::value_type;

	static void finish(T & o) {
		for (auto & v : o) {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) F<ValueType<T>>::finish(v);
		}
	}

	static void init(T &) {}

	static void iterate_over(T & o, const std::string & name) {
		F_iterate_over::start_array(name);
		
		for (auto & v : o) {
			if constexpr (std::is_same_v<ValueType<T>, bool>) F_iterate_over::set_bool("", v);
			else if constexpr (std::is_integral_v<ValueType<T>>) F_iterate_over::set_integral("", v);
			else if constexpr (std::is_floating_point_v<ValueType<T>>) F_iterate_over::set_floating_point("", v);
			else if constexpr (std::is_same_v<ValueType<T>, std::string>) F_iterate_over::set_string("", v);
			else F<ValueType<T>>::iterate_over(v, "");
		}

		F_iterate_over::end_array();
	}

	static bool release(T &) {
		if (!used) {
			return true;
		}	else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				if (F<ValueType<T>>::release(get_last_inserted())) {
					used = false;
				}
				return false;
			}
		}
		return false;
	}

	static void reset() {
		used = false;
	}

	static void set_bool(T & o, const std::string & name, bool value) {
		if (!used) {
			if constexpr (std::is_same_v<ValueType<T>, bool>) {
				last_inserted = insert(o, value);
			} else throw StructMappingException("bad type (bool) '" + (value ? std::string("true") : std::string("false")) + "' in array_like at index " + std::to_string(o.size()));
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_bool(get_last_inserted(), name, value);
			}
		}
	}

	static void set_floating_point(T & o, const std::string & name, double value) {
		if (!used) {
			if constexpr (std::is_floating_point_v<ValueType<T>>) {
				if (!detail::in_limits<ValueType<T>>(value)) {
					throw StructMappingException(
						"bad value '" + std::to_string(value) + "' in array_like at index " + std::to_string(o.size()) + " is out of limits of type [" +
						std::to_string(std::numeric_limits<ValueType<T>>::lowest()) +
						" : " +
						std::to_string(std::numeric_limits<ValueType<T>>::max()) + "]");
				}
				last_inserted = insert(o, static_cast<ValueType<T>>(value));
			} else throw StructMappingException("bad type (floating point) '" + std::to_string(value) + "' in array_like at index " + std::to_string(o.size()));
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_floating_point(get_last_inserted(), name, value);
			}
		}
	}

	static void set_integral(T & o, const std::string & name, long long value) {
		if (!used) {
			if constexpr (detail::is_integer_or_floating_point_v<ValueType<T>>) {
				if (!detail::in_limits<ValueType<T>>(value)) {
					throw StructMappingException(
						"bad value '" + std::to_string(value) + "' in array_like at index " + std::to_string(o.size()) + " is out of limits of type [" +
						std::to_string(std::numeric_limits<ValueType<T>>::lowest()) +
						" : " +
						std::to_string(std::numeric_limits<ValueType<T>>::max()) + "]");
				}
				last_inserted = insert(o, static_cast<ValueType<T>>(value));
			} else throw StructMappingException("bad type (integer) '" + std::to_string(value) + "' in array_like at index " + std::to_string(o.size()));
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_integral(get_last_inserted(), name, value);
			}
		}
	}

	static void set_string(T & o, const std::string & name, const std::string & value) {
		if (!used) {
			if constexpr (std::is_same_v<ValueType<T>, std::string>) {
				last_inserted = insert(o, value);
			} else throw StructMappingException("bad type (string) '" + value + "' in array_like at index " + std::to_string(o.size()));
		} else {
			if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
				F<ValueType<T>>::set_string(get_last_inserted(), name, value);
			}
		}
	}

	static void use(T & o, const std::string & name) {
		if constexpr (!is_integral_or_floating_point_or_string_v<ValueType<T>>) {
			if (!used) {
				used = true;
				last_inserted = insert(o, ValueType<T>{});
				F<ValueType<T>>::init(*last_inserted);
			}	else {
				F<ValueType<T>>::use(get_last_inserted(), name);
			}
		}
	}

private:
	static inline Iterator last_inserted;
	static inline bool used = false;

	static auto & get_last_inserted() {
		if constexpr (has_mapped_type_v<T>) return last_inserted->second;
		else return *last_inserted;
	}

	template<typename V>
	static Iterator insert(T & o, const V & value) {
		if constexpr (has_key_type_v<T>) {
			if constexpr (std::is_same_v<decltype(std::declval<T>().insert(typename T::key_type())), std::pair<Iterator, bool>>) {
				auto [it, ok] = o.insert(value);
				return it;
			} else {
				return o.insert(value);
			}
		} else {
			return o.insert(o.end(), value);
		}
	}
};

}

#endif
