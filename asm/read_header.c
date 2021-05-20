/*
** EPITECH PROJECT, 2021
** read
** File description:
** header
*/

#include "corewar/asm.h"
#include <erty/eregex.h>

static bool read_name_program(parser_t *parser, char *buffer,
        bool *was_readed)
{
    char *buf = NULL;

    if (*was_readed) {
        efprintf(stderr, "You cannot define the name of the program twice\n");
        return (false);
    }
    *was_readed = true;
    if ((buf = read_quotes(parser, buffer, true)) == NULL)
        return (false);
    if (estrlen(buf) > PROG_NAME_LENGTH) {
        efprintf(stderr, "Program name exceed the maximum length\n");
        return (false);
    }
    ememset(parser->header.prog_name, 0, PROG_NAME_LENGTH);
    estrcpy(parser->header.prog_name, buf);
    return (true);
}

static bool read_comment_program(parser_t *parser, char *buffer,
        bool *was_readed)
{
    char *buf = NULL;

    if (*was_readed) {
        efprintf(stderr, "You cannot define the comment"
                " of the program twice\n");
        return (false);
    }
    *was_readed = true;
    buf = read_quotes(parser, buffer, false);
    if (buf == NULL) {
        efprintf(stderr, "Could not parse the comment of the program\n");
        return (false);
    }
    if (estrlen(buf) > COMMENT_LENGTH) {
        efprintf(stderr, "Program comment exceed the maximum length\n");
        return (false);
    }
    ememset(parser->header.comment, 0, COMMENT_LENGTH);
    estrcpy(parser->header.comment, buf);
    return (true);
}

int read_header_line(parser_t *parser, char *buffer, bool *comment_readed,
        bool *name_readed)
{
    parser->line++;
    skip_spaces(parser, buffer);
    if (*buffer == '\0' || *buffer == '#')
        return (1);
    if (estrncmp(COMMENT_CMD_STRING, buffer + parser->col, 8) == 0)
        return (read_comment_program(parser, buffer, comment_readed) ? 0 : 2);
    if (estrncmp(NAME_CMD_STRING, buffer + parser->col, 5) == 0)
        return (read_name_program(parser, buffer, name_readed) ? 0 : 2);
    efprintf(stderr, "The start of the program must start "
            "with the name and the comment\n");
    return (2);
}

bool read_header(parser_t *parser, int fd)
{
    char *buffer = NULL;
    bool comment_readed = false;
    bool name_readed = false;

    parser->header.magic = MAGIC_NUMBER;
    while (egetline(&buffer, fd) > 0) {
        parser->col = 0;
        if (read_header_line(parser, buffer,
                    &comment_readed, &name_readed) == 2)
            return (false);
        if (comment_readed && name_readed)
            break;
    }
    if ((comment_readed && name_readed) == false) {
        efprintf(stderr, "The start of the program must start "
                "with the name and the comment\n");
        return (false);
    }
    FREE(buffer);
    return (true);
}
