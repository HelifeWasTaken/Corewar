/*
** EPITECH PROJECT, 2021
** pre
** File description:
** parsing
*/

#include <corewar/asm.h>

bool check_opcode_and_instruction(uint32_t line, instruction_t *ins)
{
    const struct op_s *op = &OP_TAB[ins->opcode - 1];

    if (op->nbr_args != ins->arg_count) {
        efprintf(stderr, "Invalid number of arguments at line: %d\n", line);
        return (false);
    }
    for (uint8_t i = 0; i < ins->arg_count; i++) {
        if ((op->type[i] & ins->param[i].type) == 0) {
            efprintf(stderr,
                    "The argument n°%d is invalid at line: %d\n", i, line);
            return (false);
        }
    }
    return (true);
}

bool pre_parsing(parser_t *parser, int fd)
{
    instruction_t tmp = {0};
    char *buffer = NULL;
    int ret = 0;

    while (egetline(&buffer, fd) > 0) {
        parser->col = 0;
        parser->line++;
        if ((ret = parse_line(parser, buffer, &tmp)) == false)
            return (false);
        if (ret == ONLY_LABEL || ret == EMPTY_LINE)
            continue;
        if (check_opcode_and_instruction(parser->line, &tmp) == false)
            return (false);
        instruction_push_back(&parser->instruction, &tmp);
        parser->mem_index += count_byte_instruction_size(&tmp);
        printf("%ld\n", parser->mem_index);
    }
    parser->header.prog_size = parser->mem_index;
    FREE(buffer);
    return (true);
}
