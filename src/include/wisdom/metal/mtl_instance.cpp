#ifndef WIS_MTL_INSTANCE_CPP
#define WIS_MTL_INSTANCE_CPP

#include <wisdom/generated/cpp_api.hpp>

namespace wis::detail {
inline constexpr WisResult metal_instance_not_implemented{WisStatusFail, 0, "Metal instance creation is not implemented"};
} // namespace wis::detail

//----------------------------------------------------------------------------------------------------------------------
WIS_EXTERN_C WISDOM_API void wisMTLDestroyInstance(WisMTLInstance* self)
{
    if (self) {
        *self = {};
    }
}

//----------------------------------------------------------------------------------------------------------------------
WIS_EXTERN_C WISDOM_API WisResult wisMTLCreateInstance(
    const WisDebugDesc*,
    WisMTLInstanceExtensionHeader**,
    size_t,
    WisMTLInstance* instance
)
{
    if (instance) {
        *instance = {};
    }
    return wis::detail::metal_instance_not_implemented;
}

#endif // WIS_MTL_INSTANCE_CPP
