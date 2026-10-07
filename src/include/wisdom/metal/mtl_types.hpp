#ifndef WIS_MTL_TYPES_HPP
#define WIS_MTL_TYPES_HPP
#ifndef __cplusplus
#    error "This header requires C++"
#endif // __cplusplus

namespace wis {
//----------------------------------------------------------------------------------------------------------------------
namespace impl {

struct MTLInstanceState;

// Reserved instance state pointer; the runtime implementation is not available yet.
struct MTLInstanceImpl {
    MTLInstanceState* state;
};

} // namespace impl

struct MTLInstanceExtensionHeader {
    const void* opaque;
};
} // namespace wis

#ifdef WISDOM_HEADER_ONLY
#    include "mtl_instance.cpp"
#endif // WISDOM_HEADER_ONLY
#endif // WIS_MTL_TYPES_HPP
