#include <corewar/vm.h>

int getindex(int pc, int offset)
{
    int index = pc + offset;

    if (index < 0)
        return (MEM_SIZE + index);
    return ((pc + offset) % MEM_SIZE);
}

struct memory getmem(int pc, int offset, struct memory *mem)
{
    return (mem[getindex(pc, offset)]);
}

BYTE getmem_byte(int pc, int offset, struct memory *mem)
{
    return (getmem(pc, offset, mem).byte);
}

int8_t getmem_player(int pc, int offset, struct memory *mem)
{
    return (getmem(pc, offset, mem).player);
}

void setmem(int pc, int offset, struct memory *mem, int16_t byte)
{
    mem[getindex(pc, offset)].byte = (byte & 0xff);
    mem[getindex(pc, offset)].player = (byte & (0xff << 8)) >> 8;
}
