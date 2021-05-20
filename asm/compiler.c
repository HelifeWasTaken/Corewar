/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** compiler
*/

#include "corewar/asm.h"
#include <erty/estdio.h>
#include <erty/eendian.h>

static void compiler_internal_write_parameters(int fd,
        int16_t type, int32_t value)
{
    char buf[4] = {0};

    if (type == T_DIR) {
/*        buf[0] = ((value & 0xFF) << 8) >> 8;
        buf[1] = ((value & 0xFF) << 16) >> 16;
        */
        value = u16_swap_endian((int16_t)value);
        write(fd, &value, DIR_SIZE);
    } else if (type == T_IND) {
/*        buf[0] = ((value & 0xFF) << 24) >> 24;
        buf[1] = ((value & 0xFF) << 16) >> 16;
        buf[2] = ((value & 0xFF) << 8) >> 8;
        buf[3] = value & 0xFF;
        */
        value = u32_swap_endian(value);
        write(fd, &value, IND_SIZE);
    } else {
        buf[0] = value;
        write(fd, buf, 1);
    }
}

static void compiler_internal_write_parameters_layout(int fd,
        instruction_t *ins)
{
    int32_t value = 0;
    int index = 3;

    for (uint8_t i = 0; i < 3; i++, index--) {
        switch (ins->param[i].type) {
            case T_IND:
                value |= 0b11 << (index * 2);
                break;
            case T_REG:
                value |= 0b01 << (index * 2);
                break;
            case T_DIR:
                value |= 0b10 << (index * 2);
                break;
            default:
                value |= 0b00 << (index * 2);
                break;
        }
    }
    edputchar(fd, value);
}

static void compiler_write_header(int fd, struct header_s *header)
{
    header->magic = u32_swap_endian(header->magic);
    header->prog_size = u32_swap_endian(header->prog_size);
    write(fd, header, sizeof(struct header_s));
}

void compiler_internal(parser_t *parser, int fd)
{
    compiler_write_header(fd, &parser->header);
    for (instruction_t *ins = parser->instruction; ins; ins = ins->next) {
        edputchar(fd, ins->opcode);
        if (is_special_opcode(ins->opcode)) {
            write(fd, &ins->param[0].iv, 4);
            continue;
        }
        compiler_internal_write_parameters_layout(fd, ins);
        for (uint8_t i = 0; i < ins->arg_count; i++) {
            compiler_internal_write_parameters(fd, ins->param[i].type,
                    ins->param[i].iv);
        }
    }
}
