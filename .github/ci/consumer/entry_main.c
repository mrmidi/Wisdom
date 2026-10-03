#include <wisdom/wisdom.h>

int main(void)
{
    WisInstance instance = {0};
    WisResult result = wisCreateInstance(NULL, NULL, 0, &instance);
    if (result.status == WisStatusOk) {
        wisDestroyInstance(&instance);
    }
    return 0;
}
