#include <cstdint>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "struct_mapping/struct_mapping.h"

using ::testing::ElementsAre;
using ::testing::Pair;
using ::testing::UnorderedElementsAre;

namespace {

struct Struct_empty {
};

TEST(struct_mapping_map_json_to_struct, empty) {
	Struct_empty result_struct;
	std::istringstream json_data(R"json(
	{
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);
}

struct Struct_bool_integer_floating_point_string {
	bool member_bool;
	char member_char;
	unsigned char member_unsigned_char;
	short member_short;
	unsigned short member_unsigned_short;
	int member_int;
	unsigned int member_unsigned_int;
	long member_long;
	long long member_long_long;
	float member_float;
	double member_double;
	std::string member_string;
};

TEST(struct_mapping_map_json_to_struct, bool_integer_floating_point_string) {
	Struct_bool_integer_floating_point_string result_struct;
	
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_bool, "member_bool");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_char, "member_char");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_unsigned_char, "member_unsigned_char");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_short, "member_short");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_unsigned_short, "member_unsigned_short");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_int, "member_int");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_unsigned_int, "member_unsigned_int");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_long, "member_long");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_long_long, "member_long_long");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_float, "member_float");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_double, "member_double");
	struct_mapping::reg(&Struct_bool_integer_floating_point_string::member_string, "member_string");

	std::istringstream json_data(R"json(
	{
		"member_bool": true,
		"member_char": -1,
		"member_unsigned_char": 2,
		"member_short": -3,
		"member_unsigned_short": 4,
		"member_int": -5,
		"member_unsigned_int": 6,
		"member_long": -7,
		"member_long_long": 8,
		"member_float": -9.1,
		"member_double": 10.0,
		"member_string": "String"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_bool, true);
	ASSERT_EQ(result_struct.member_char, -1);
	ASSERT_EQ(result_struct.member_unsigned_char, 2);
	ASSERT_EQ(result_struct.member_short, -3);
	ASSERT_EQ(result_struct.member_unsigned_short, 4);
	ASSERT_EQ(result_struct.member_int, -5);
	ASSERT_EQ(result_struct.member_unsigned_int, 6);
	ASSERT_EQ(result_struct.member_long, -7);
	ASSERT_EQ(result_struct.member_long_long, 8);
	ASSERT_EQ(result_struct.member_float, -9.1f);
	ASSERT_EQ(result_struct.member_double, 10.0);
	ASSERT_EQ(result_struct.member_string, "String");
}

struct Struct_list {
	std::list<int> member_list_int;
	std::list<float> member_list_float;
	std::list<std::string> member_list_string;
};

TEST(struct_mapping_map_json_to_struct, member_list) {
	Struct_list result_struct;

	struct_mapping::reg(&Struct_list::member_list_int, "member_list_int");
	struct_mapping::reg(&Struct_list::member_list_float, "member_list_float");
	struct_mapping::reg(&Struct_list::member_list_string, "member_list_string");

	std::istringstream json_data(R"json(
	{
		"member_list_int": [-10, -1, 0, 1, 10],
		"member_list_float": [-10.5, -1, 0, 1, 10.5],
		"member_list_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_list_int, ElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_list_float, ElementsAre(-10.5, -1, 0, 1, 10.5));
	ASSERT_THAT(result_struct.member_list_string, ElementsAre("first", "second"));
}

struct Struct_vector {
	std::vector<int> member_vector_int;
	std::vector<float> member_vector_float;
	std::vector<std::string> member_vector_string;
};

TEST(struct_mapping_map_json_to_struct, member_vector) {
	Struct_vector result_struct;

	struct_mapping::reg(&Struct_vector::member_vector_int, "member_vector_int");
	struct_mapping::reg(&Struct_vector::member_vector_float, "member_vector_float");
	struct_mapping::reg(&Struct_vector::member_vector_string, "member_vector_string");

	std::istringstream json_data(R"json(
	{
		"member_vector_int": [-10, -1, 0, 1, 10],
		"member_vector_float": [-10.5, -1, 0, 1, 10.5],
		"member_vector_string": ["first", "second"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_vector_int, ElementsAre(-10, -1, 0, 1, 10));
	ASSERT_THAT(result_struct.member_vector_float, ElementsAre(-10.5, -1, 0, 1, 10.5));
	ASSERT_THAT(result_struct.member_vector_string, ElementsAre("first", "second"));
}

struct Struct_map {
	std::map<std::string, int> member_map_int;
	std::map<std::string, float> member_map_float;
	std::map<std::string, std::string> member_map_string;
};

TEST(struct_mapping_map_json_to_struct, member_map) {
	Struct_map result_struct;

	struct_mapping::reg(&Struct_map::member_map_int, "member_map_int");
	struct_mapping::reg(&Struct_map::member_map_float, "member_map_float");
	struct_mapping::reg(&Struct_map::member_map_string, "member_map_string");

	std::istringstream json_data(R"json(
	{
		"member_map_int": {
			"first": -10,
			"second": 0,
			"third": 10
		},
		"member_map_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_map_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_map_int, ElementsAre(Pair("first", -10), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(result_struct.member_map_float, ElementsAre(Pair("first", -10.5), Pair("second", 1), Pair("third", 10.5)));
	ASSERT_THAT(result_struct.member_map_string, ElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

struct Struct_unordered_map {
	std::unordered_map<std::string, int> member_unordered_map_int;
	std::unordered_map<std::string, float> member_unordered_map_float;
	std::unordered_map<std::string, std::string> member_unordered_map_string;
};

TEST(struct_mapping_map_json_to_struct, member_unordered_map) {
	Struct_unordered_map result_struct;

	struct_mapping::reg(&Struct_unordered_map::member_unordered_map_int, "member_unordered_map_int");
	struct_mapping::reg(&Struct_unordered_map::member_unordered_map_float, "member_unordered_map_float");
	struct_mapping::reg(&Struct_unordered_map::member_unordered_map_string, "member_unordered_map_string");

	std::istringstream json_data(R"json(
	{
		"member_unordered_map_int": {
			"first": -10,
			"second": 0,
			"third": 10
		},
		"member_unordered_map_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_unordered_map_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_unordered_map_int, UnorderedElementsAre(Pair("first", -10), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(result_struct.member_unordered_map_float, UnorderedElementsAre(Pair("first", -10.5), Pair("second", 1), Pair("third", 10.5)));
	ASSERT_THAT(result_struct.member_unordered_map_string, UnorderedElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

struct Struct_multimap {
	std::multimap<std::string, int> member_multimap_int;
	std::multimap<std::string, float> member_multimap_float;
	std::multimap<std::string, std::string> member_multimap_string;
};

TEST(struct_mapping_map_json_to_struct, member_multimap) {
	Struct_multimap result_struct;

	struct_mapping::reg(&Struct_multimap::member_multimap_int, "member_multimap_int");
	struct_mapping::reg(&Struct_multimap::member_multimap_float, "member_multimap_float");
	struct_mapping::reg(&Struct_multimap::member_multimap_string, "member_multimap_string");

	std::istringstream json_data(R"json(
	{
		"member_multimap_int": {
			"first": -10,
			"first": 20,
			"second": 0,
			"third": 10
		},
		"member_multimap_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_multimap_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_multimap_int, ElementsAre(Pair("first", -10), Pair("first", 20), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(result_struct.member_multimap_float, ElementsAre(Pair("first", -10.5), Pair("second", 1), Pair("third", 10.5)));
	ASSERT_THAT(result_struct.member_multimap_string, ElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

struct Struct_unordered_multimap {
	std::unordered_multimap<std::string, int> member_unordered_multimap_int;
	std::unordered_multimap<std::string, float> member_unordered_multimap_float;
	std::unordered_multimap<std::string, std::string> member_unordered_multimap_string;
};

TEST(struct_mapping_map_json_to_struct, member_unordered_multimap) {
	Struct_unordered_multimap result_struct;

	struct_mapping::reg(&Struct_unordered_multimap::member_unordered_multimap_int, "member_unordered_multimap_int");
	struct_mapping::reg(&Struct_unordered_multimap::member_unordered_multimap_float, "member_unordered_multimap_float");
	struct_mapping::reg(&Struct_unordered_multimap::member_unordered_multimap_string, "member_unordered_multimap_string");

	std::istringstream json_data(R"json(
	{
		"member_unordered_multimap_int": {
			"first": -10,
			"first": 20,
			"second": 0,
			"third": 10
		},
		"member_unordered_multimap_float": {
			"first": -10.5,
			"second": 1,
			"third": 10.5
		},
		"member_unordered_multimap_string": {
			"first": "first_string",
			"second": "second_string",
			"third": "third_string"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.member_unordered_multimap_int, UnorderedElementsAre(Pair("first", -10), Pair("first", 20), Pair("second", 0), Pair("third", 10)));
	ASSERT_THAT(result_struct.member_unordered_multimap_float, UnorderedElementsAre(Pair("first", -10.5), Pair("second", 1), Pair("third", 10.5)));
	ASSERT_THAT(result_struct.member_unordered_multimap_string, UnorderedElementsAre(Pair("first", "first_string"), Pair("second", "second_string"), Pair("third", "third_string")));
}

struct Struct_struct_A {
	std::string member_string;
};

struct Struct_struct_B {
	Struct_struct_A member_a;
};

TEST(struct_mapping_map_json_to_struct, member_struct) {
	Struct_struct_B result_struct;
	
	struct_mapping::reg(&Struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_struct_B::member_a, "member_a");

	std::istringstream json_data(R"json(
	{
		"member_a": {
			"member_string": "String"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_a.member_string, "String");
}

struct Struct_struct_struct_A {
	std::string member_string;
};

struct Struct_struct_struct_B {
	Struct_struct_struct_A member_a;
};

struct Struct_struct_struct_C {
	Struct_struct_struct_B member_b;
};

TEST(struct_mapping_map_json_to_struct, member_struct_struct) {
	Struct_struct_struct_C result_struct;
	
	struct_mapping::reg(&Struct_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_struct_struct_B::member_a, "member_a");
	struct_mapping::reg(&Struct_struct_struct_C::member_b, "member_b");

	std::istringstream json_data(R"json(
	{
		"member_b": {
			"member_a": {
				"member_string": "String"
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_b.member_a.member_string, "String");
}

struct Struct_vector_struct_A {
	std::string member_string;
};

struct Struct_vector_struct_B {
	std::vector<Struct_vector_struct_A> member_vector_a;
};

TEST(struct_mapping_map_json_to_struct, member_vector_struct) {
	Struct_vector_struct_B result_struct;
	
	struct_mapping::reg(&Struct_vector_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_vector_struct_B::member_vector_a, "member_vector_a");

	std::istringstream json_data(R"json(
	{
		"member_vector_a": [
			{
				"member_string": "first"
			},
			{
				"member_string": "second"
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_vector_a.size(), 2);
	ASSERT_EQ(result_struct.member_vector_a[0].member_string, "first");
	ASSERT_EQ(result_struct.member_vector_a[1].member_string, "second");
}

struct Struct_vector_struct_struct_A {
	std::string member_string;
};

struct Struct_vector_struct_struct_B {
	Struct_vector_struct_struct_A member_struct_a;
};

struct Struct_vector_struct_struct_C {
	std::vector<Struct_vector_struct_struct_B> member_vector_struct_b;
};

TEST(struct_mapping_map_json_to_struct, member_vector_struct_struct) {
	Struct_vector_struct_struct_C result_struct;
	
	struct_mapping::reg(&Struct_vector_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_vector_struct_struct_B::member_struct_a, "member_struct_a");
	struct_mapping::reg(&Struct_vector_struct_struct_C::member_vector_struct_b, "member_vector_struct_b");

	std::istringstream json_data(R"json(
	{
		"member_vector_struct_b": [
			{
				"member_struct_a": {
					"member_string": "first"
				}
			},
			{
				"member_struct_a": {
					"member_string": "second"
				}
			}
		]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_vector_struct_b.size(), 2);
	ASSERT_EQ(result_struct.member_vector_struct_b[0].member_struct_a.member_string, "first");
	ASSERT_EQ(result_struct.member_vector_struct_b[1].member_struct_a.member_string, "second");
}

struct Struct_map_struct_A {
	std::string member_string;
};

struct Struct_map_struct_B {
	std::map<std::string, Struct_map_struct_A> member_map_a;
};

TEST(struct_mapping_map_json_to_struct, member_map_struct) {
	Struct_map_struct_B result_struct;
	
	struct_mapping::reg(&Struct_map_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_map_struct_B::member_map_a, "member_map_a");

	std::istringstream json_data(R"json(
	{
		"member_map_a": {
			"1": {
				"member_string": "first"
			},
			"2": {
				"member_string": "second"
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_map_a.size(), 2);
	ASSERT_EQ(result_struct.member_map_a["1"].member_string, "first");
	ASSERT_EQ(result_struct.member_map_a["2"].member_string, "second");
}

struct Struct_map_struct_struct_A {
	std::string member_string;
};

struct Struct_map_struct_struct_B {
	Struct_map_struct_struct_A member_struct_a;
};

struct Struct_map_struct_struct_C {
	std::map<std::string, Struct_map_struct_struct_B> member_map_struct_b;
};

TEST(struct_mapping_map_json_to_struct, member_map_struct_struct) {
	Struct_map_struct_struct_C result_struct;
	
	struct_mapping::reg(&Struct_map_struct_struct_A::member_string, "member_string");
	struct_mapping::reg(&Struct_map_struct_struct_B::member_struct_a, "member_struct_a");
	struct_mapping::reg(&Struct_map_struct_struct_C::member_map_struct_b, "member_map_struct_b");

	std::istringstream json_data(R"json(
	{
		"member_map_struct_b": {
			"1": {
				"member_struct_a": {
					"member_string": "first"
				}
			},
			"2": {
				"member_struct_a": {
					"member_string": "second"
				}
			}
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.member_map_struct_b.size(), 2);
	ASSERT_EQ(result_struct.member_map_struct_b["1"].member_struct_a.member_string, "first");
	ASSERT_EQ(result_struct.member_map_struct_b["2"].member_struct_a.member_string, "second");
}

enum Enum {
	Enum_v1,
	Enum_v2,
	Enum_v3
};

struct Struct_enum {
	Enum value;
};

TEST(struct_mapping_map_json_to_struct, enum) {
	struct_mapping::MemberString<Enum>::set([] (const std::string & value) {
		if (value == "Enum_v1") return Enum_v1;
		if (value == "Enum_v2") return Enum_v2;
		if (value == "Enum_v3") return Enum_v3;

		throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum");
	},
	[] (Enum value) {
		switch (value) {
		case Enum_v1: return "Enum_v1";
		case Enum_v2: return "Enum_v2";
		case Enum_v3: return "Enum_v3";
		}

		throw struct_mapping::StructMappingException("bad convert Enum '" + std::to_string(value) + "' to string");
	});

	Struct_enum result_struct;

	struct_mapping::reg(&Struct_enum::value, "value");

	std::istringstream json_data(R"json(
	{
		"value": "Enum_v2"
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_EQ(result_struct.value, Enum_v2);
}

enum class Enum_list {
	v1,
	v2,
	v3
};

struct Struct_enum_list {
	std::list<Enum_list> values;
};

TEST(struct_mapping_map_json_to_struct, enum_list) {
	struct_mapping::MemberString<Enum_list>::set([] (const std::string & value) {
		if (value == "v1") return Enum_list::v1;
		if (value == "v2") return Enum_list::v2;
		if (value == "v3") return Enum_list::v3;

		throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_list");
	},
	[] (Enum_list value) {
		switch (value) {
		case Enum_list::v1: return "v1";
		case Enum_list::v2: return "v2";
		default: return "v3";
		}
	});

	Struct_enum_list result_struct;

	struct_mapping::reg(&Struct_enum_list::values, "values");

	std::istringstream json_data(R"json(
	{
		"values": ["v2", "v1", "v2"]
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(Enum_list::v2, Enum_list::v1, Enum_list::v2));
}

enum class Enum_map {
	v1,
	v2,
	v3
};

struct Struct_enum_map {
	std::map<std::string, Enum_map> values;
};

TEST(struct_mapping_map_json_to_struct, enum_map) {
	struct_mapping::MemberString<Enum_map>::set([] (const std::string & value) {
		if (value == "v1") return Enum_map::v1;
		if (value == "v2") return Enum_map::v2;
		if (value == "v3") return Enum_map::v3;

		throw struct_mapping::StructMappingException("bad convert '" + value + "' to Enum_map");
	},
	[] (Enum_map value) {
		switch (value) {
		case Enum_map::v1: return "v1";
		case Enum_map::v2: return "v2";
		default: return "v3";
		}
	});

	Struct_enum_map result_struct;

	struct_mapping::reg(&Struct_enum_map::values, "values");

	std::istringstream json_data(R"json(
	{
		"values": {
			"first": "v2",
			"second": "v3",
			"third": "v2"
		}
	}
	)json");

	struct_mapping::map_json_to_struct(result_struct, json_data);

	ASSERT_THAT(result_struct.values, ElementsAre(Pair("first", Enum_map::v2), Pair("second", Enum_map::v3), Pair("third", Enum_map::v2)));
}

}
