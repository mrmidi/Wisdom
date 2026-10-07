#include <wisdom/wisdom.h>
#include <stdio.h>

int main(void)
{
    WisInstance instance = {{1}};
    WisResult result = wisCreateInstance(NULL, NULL, 0, &instance);
    if (result.status != WisStatusFail || instance.opaque[0] != 0) {
        return 1;
    }
    result = wisCreateInstance(NULL, NULL, 0, NULL);
    if (result.status != WisStatusFail) {
        return 2;
    }
    wisDestroyInstance(&instance);
    wisDestroyInstance(NULL);
    if (instance.opaque[0] != 0) {
        return 3;
    }
    puts("Metal C instance: failure and empty handle verified");
    return 0;
}
