#include <wisdom/generated/c_api.h>

int metal_headeronly_peer(void);
int metal_headeronly_c(void)
{
    /* C parses the same public types; C++ supplies the header-only implementation. */
    WisMTLInstance empty = {{0}};
    return empty.opaque[0] != 0 || metal_headeronly_peer();
}
