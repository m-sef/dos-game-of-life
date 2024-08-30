#ifndef RULESET_H
#define RULESET_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    uint16_t birth_flags;
    uint16_t survive_flags;
} RULESET;

RULESET* init_ruleset(char* rulestring);
void parse_rulestring(RULESET* ruleset, char* rulestring);

void set_birth_flag(RULESET* ruleset, const uint8_t n);
bool get_birth_flag(const RULESET* ruleset, const uint8_t n);
void set_survive_flag(RULESET* ruleset, const uint8_t n);
bool get_survive_flag(const RULESET* ruleset, const uint8_t n);

void reverse(RULESET* ruleset);
static uint16_t reverse_bits(uint16_t val);

#endif
