#include <wisdom/wisdom.h>

int metal_consumer_c(void)
{
    WisInstance instance = {{1}};
    WisResult result = wisCreateInstance(NULL, NULL, 0, &instance);
    wisDestroyInstance(&instance);
    return result.status != WisStatusFail || instance.opaque[0] != 0;
}
