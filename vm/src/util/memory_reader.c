/*
** EPITECH PROJECT, 2021
** memory
** File description:
** reader
*/

#include <corewar/vm.h>
#include <unistd.h>
#include <stddef.h>
#include <stdint.h>
#include <erty/string/ecstring.h>
#include <erty/eprintf.h>

bool read_memory_byte(const int fd, void *mem, const size_t size)
{
    ssize_t read_ret = -1;
    size_t readed = 0;

    do {
        read_ret = read(fd, (char *)mem + readed, size);
        readed += read_ret;
    } while (read_ret > 0 && readed != size);
    return (read_ret != -1 && readed == size);
}

union mem_u16 {
    u16_t vi;
    BYTE vmem[sizeof(u16_t)];
};

static bool swap_memory_u16(const int fd, void *mem)
{
    union mem_u16 mem_ptr;

    if (read_memory_byte(fd, mem_ptr.vmem, sizeof(u16_t)) == false)
        return (false);
    mem_ptr.vi = u16_swap_endian(mem_ptr.vi);
    ememcpy(mem, mem_ptr.vmem, sizeof(mem_ptr.vmem));
    return (true);
}

union mem_u32 {
    u32_t vi;
    BYTE vmem[sizeof(u32_t)];
};

static bool swap_memory_u32(const int fd, void *mem)
{
    union mem_u32 mem_ptr;

    if (read_memory_byte(fd, mem_ptr.vmem, sizeof(u32_t)) == false)
        return (false);
    mem_ptr.vi = u32_swap_endian(mem_ptr.vi);
    ememcpy(mem, mem_ptr.vmem, sizeof(u32_t));
    return (true);
}

union mem_u64 {
    u64_t vi;
    BYTE vmem[sizeof(u64_t)];
};

static bool swap_memory_u64(const int fd, void *mem)
{
    union mem_u64 mem_ptr;

    if (read_memory_byte(fd, mem_ptr.vmem, sizeof(u64_t)) == false)
        return (false);
    mem_ptr.vi = u64_swap_endian(mem_ptr.vi);
    ememcpy(mem, mem_ptr.vmem, sizeof(u64_t));
    return (true);
}

bool read_memory_uint(const int fd, void *mem, size_t size)
{
    switch (size) {
        case sizeof(u16_t):
            return (swap_memory_u16(fd, mem));
        case sizeof(u32_t):
            return (swap_memory_u32(fd, mem));
        case sizeof(u64_t):
            return (swap_memory_u64(fd, mem));
        default:
            efprintf(stderr, "Invalid size give to read uint: %ld\n", size);
            return (false);
    }
}
