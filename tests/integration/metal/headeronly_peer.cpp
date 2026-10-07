#include <wisdom/generated/cpp_api.hpp>

extern "C" int metal_headeronly_peer()
{
    wis::Result result{};
    auto instance = wis::MTLCreateInstance(nullptr, {}, result);
    return result.status == wis::Status::Fail && !instance ? 0 : 1;
}
