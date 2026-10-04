#include <wisdom/wisdom.hpp>
#include <catch2/catch_test_macros.hpp>
#include <utility>

#ifdef WISDOM_HEADER_ONLY
extern "C" int metal_headeronly_c();
#endif

TEST_CASE("Unimplemented Metal instance creation returns an empty handle")
{
#ifdef WISDOM_HEADER_ONLY
    REQUIRE(metal_headeronly_c() == 0);
#endif
    wis::Result result{};
    auto instance = wis::CreateInstance(nullptr, {}, result);
    REQUIRE(result.status == wis::Status::Fail);
    REQUIRE_FALSE(instance);
    auto moved = std::move(instance);
    REQUIRE_FALSE(moved);
    REQUIRE_FALSE(instance);
}
