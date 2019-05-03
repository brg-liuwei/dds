#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dll.h"
#include "hands.h"

#define LINE_SIZE 256

int main()
{
    ddTableDealPBN tableDealPBN;
    ddTableResults table;

    int res, cnt;
    bool match;
    char *line;
    size_t buf_len;
    ssize_t line_len;

#if defined(__linux) || defined(__APPLE__)
    SetMaxThreads(0);
#endif

    line = static_cast<char *>(malloc(sizeof(char) * LINE_SIZE));
    if (line == NULL) {
        printf("allocate memory failed\n");
        return -1;
    }
    buf_len = LINE_SIZE - 1;

    cnt = 0;
    while ((line_len = getline(&line, &buf_len, stdin)) != -1) {
        cnt++;
        if (line_len >= LINE_SIZE) {
            printf("line size overflow: %lu\n", buf_len);
            continue;
        }
        line[buf_len] = '\0';
        strncpy(tableDealPBN.cards, line, static_cast<size_t>(line_len));
        res = CalcDDtablePBN(tableDealPBN, &table);
        if (res != RETURN_NO_FAULT) {
            ErrorMessage(res, line);
            printf("DDS error: %s\n", line);
        }
        line[line_len] = '\0';
        printf("hands[%d]: %s", cnt, line);
        PrintTable(&table);
    }

    if (line != NULL) {
        free(line);
    }

    return 0;
}
