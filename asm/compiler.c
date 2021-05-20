/*
** EPITECH PROJECT, 2021
** corewar
** File description:
** compiler
*/

#include "corewar/asm.h"
#include <erty/estdio.h>
#include <erty/eendian.h>

static void write_nbyte_big_endian(int fd, int32_t value, uint8_t size)
{
    char buf[4] = {0};

    for (size_t i = 0; i < size; i++)
        buf[i] = (value & (0xFF << (8 * (size - 1 - i)))) >>
            ((size - 1 - i) * 8);
    write(fd, buf, size);
}

static void compiler_internal_write_parameters(int fd,
        int16_t type, int32_t value, bool has_index)
{
    if ((type != T_REG && has_index) || type == T_IND)
        write_nbyte_big_endian(fd, value, IND_SIZE);
    else
        write_nbyte_big_endian(fd, value, type == T_DIR ? DIR_SIZE : 1);
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
        if (is_special_opcode(ins->opcode) == false)
            compiler_internal_write_parameters_layout(fd, ins);
        for (uint8_t i = 0; i < ins->arg_count; i++) {
            compiler_internal_write_parameters(fd, ins->param[i].type,
                    ins->param[i].iv, OP_TAB[ins->opcode - 1].type[i] & T_IDX);
        }
    }
}
