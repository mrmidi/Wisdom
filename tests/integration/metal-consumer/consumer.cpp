#include <wisdom/wisdom.hpp>

extern "C" int metal_consumer_c();

int main()
{
    wis::Result result{};
    auto instance = wis::CreateInstance(nullptr, {}, result);
    return result.status != wis::Status::Fail || instance || metal_consumer_c();
}
