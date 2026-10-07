#include <wisdom/wisdom.h>
#include <wisdom/wisdom.hpp>

extern "C" int metal_consumer_c()
{
    WisInstance instance{};
    auto result = wisCreateInstance(nullptr, nullptr, 0, &instance);
    wisDestroyInstance(&instance);
    return result.status != WisStatusFail || instance.opaque[0] != 0;
}
