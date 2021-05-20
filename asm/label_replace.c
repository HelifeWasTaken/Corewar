/*
** EPITECH PROJECT, 2021
** label
** File description:
** replace
*/

#include <corewar/asm.h>

static bool label_replacement_internal(parser_t *parser, instruction_t *ins,
        uint32_t offset)
{
    struct label *tmp = NULL;

    for (uint8_t i = 0; i < ins->arg_count; i++) {
        if (ins->param[i].is_jump_not_complete == true) {
            tmp = get_label(parser->label, ins->param[i].is);
            if (tmp == NULL) {
                efprintf(stderr, "No reference found for [%s] label\n",
                        ins->param[i].is);
                return (false);
            }
            efree(ins->param[i].is);
            ins->param[i].iv = tmp->index - offset;
        }
    }
    return (true);
}

bool label_replacement(parser_t *parser)
{
    uint32_t offset = 0;

    for (instruction_t *ins = parser->instruction; ins; ins = ins->next) {
        if (label_replacement_internal(parser, ins, offset) == false)
            return (false);
        offset += count_byte_instruction_size(ins);
    }
    return (true);
}
