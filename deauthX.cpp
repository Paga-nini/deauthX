#include "generic.h"
#include "bgp.h"
#include "bgp_update.h"
#include "bgp_attributes.h"

unsigned char origin[4] = { 0x40, 0x01, 0x01, 0x00};
unsigned char as_path[17] = { 0x40, 0x02, 0x0e, 0x02, 0x03, 0x00, 0x00,
    0x78, 0x7c, 0x00, 0x00, 0x12, 0x1d, 0x00, 0x00, 0x09, 0xd7 };
unsigned char local_pref[8] = { 0x40, 0x05, 0x04, 0x00, 0x00, 0x00, 0x69 };

#define INCREMENT(x) ({ ptr+=(x); (*mp_length)+=(x); header->length+=(x); (*attr_len)+=(x); })
#define INCREMENT_T(x) ({ ptr+=(x); (*mp_length)+=(x); header->length+=(x); (*attr_len)+=(x); (*tun_len)+=x; })
#define ADD_U8(y) ({ *ptr = (y); INCREMENT(1); })
#define ADD_U8_T(y) ({ *ptr = (y); INCREMENT_T(1); })
#define ADD_U16(y) ({ *(__u16*)ptr = htons(y); INCREMENT(2); })
#define ADD_U16_T(y) ({ *(__u16*)ptr = htons(y); INCREMENT_T(2); })
#define ADD_U32(y) ({ *(__u32*)ptr = htonl(y); INCREMENT(4); })
#define ADD_U32_T(y) ({ *(__u32*)ptr = htonl(y); INCREMENT_T(4); })

int main() {
    struct mp_bgp_header *mp_bgp;
    char buffer[4096] = {0};
    struct bgp_header *header = (void*)&buffer[0];
    char *ptr = (void*)(header+1);
    __u16 *withdrawn_len = (void *)ptr;
    __u16 *attr_len = (void *)(ptr+2);
    header->head[0] = ~(__u64)0;
    header->head[1] = ~(__u64)0;
    header->type = BGP_UPDATE;
    header->length = 19;
    // Skip the withdrawn section
    ptr+=4; header->length+=4;
    memcpy(ptr, origin, 4);
    ptr+=4; header->length+=4; *attr_len+=4;
    memcpy(ptr, as_path, 17);
    ptr += 17; header->length+=17; *attr_len+=17;
    struct attrib_code_flag *mp_code_flag = (void *)ptr;
    mp_code_flag->flags = 0x90;
    mp_code_flag->code = 0x0e;
    __u16 *mp_length = (void*)(ptr+2);
    ptr+=4; header->length+=4; (*attr_len)+=4;
    // Set the AFI
    ADD_U16(0x01);
    // Set the SAFI
    ADD_U8(73);
    // Set the NLRI length (as per RFC9830)
    ADD_U8(0);
    // Skip the reserved byte
    ADD_U8(4);
    ADD_U32(0x0a0a0a0a);
    ADD_U8(96);
    // Set the distinguisher
    ADD_U32(10);
    // Set the colour
    ADD_U32(10);
    // Set the end point
    ADD_U32(0x0a0a0a0a);
    // Add the tunnel encap attribute
    header->length = htons(header->length);
    *attr_len = htons(*attr_len);
    *mp_length = htons(*mp_length);
    dump_buffer(buffer, htons(header->length));
}
