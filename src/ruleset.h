#ifndef RULESET_H
#define RULESET_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    uint16_t birth_flags;
    uint16_t survival_flags;
} RULESET;

/* RULESET */

RULESET* init_ruleset(char* rulestring);
void parse_rulestring(RULESET* ruleset, char* rulestring);
void set_birth_flag(RULESET* ruleset, const uint8_t n);
bool get_birth_flag(const RULESET* ruleset, const uint8_t n);
void set_survival_flag(RULESET* ruleset, const uint8_t n);
bool get_survival_flag(const RULESET* ruleset, const uint8_t n);

#endif
