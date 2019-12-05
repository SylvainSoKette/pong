#include "utils.h"

int get_bit_at_index(u32 number, u8 index)
{
    return (number & (1 << index) ) >> index;
}
