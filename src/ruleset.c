#include "ruleset.h"

RULESET* init_ruleset(
    char* rulestring)
{
    RULESET* new_ruleset = (RULESET*) malloc(sizeof(RULESET));

    // Initialize values
    new_ruleset->birth_flags = 0;
    new_ruleset->survive_flags = 0;

    parse_rulestring(new_ruleset, rulestring);

    return new_ruleset;
}

void parse_rulestring(
    RULESET* ruleset,
    char* rulestring)
{
    char* token;
    int i;

    token = strtok(rulestring, "/");
    while (token != NULL)
    {
        switch (toupper(token[0]))
        {
        case 'B':
            for (i = 1; i < strlen(token); i++)
            {
                set_birth_flag(ruleset, token[i] - '0');
            }

            break;
        case 'S':
            for (i = 1; i < strlen(token); i++)
            {
                set_survive_flag(ruleset, token[i] - '0');
            }

            break;
        default:
            break;
        }

        token = strtok(NULL, "/");
    }
}

void set_birth_flag(
    RULESET* ruleset,
    const uint8_t n)
{
    ruleset->birth_flags |= 1 << n;
}

bool get_birth_flag(
    const RULESET* ruleset,
    const uint8_t n)
{
    return (ruleset->birth_flags >> n) & 1;
}

void set_survive_flag(
    RULESET* ruleset,
    const uint8_t n)
{
    ruleset->survive_flags |= 1 << n;
}

bool get_survive_flag(
    const RULESET* ruleset,
    const uint8_t n)
{
    return (ruleset->survive_flags >> n) & 1;
}

void reverse(RULESET* ruleset)
{
    uint16_t temp_flags = ruleset->birth_flags;
    ruleset->birth_flags = reverse_bits(~ruleset->survive_flags) >> 7;
    ruleset->survive_flags = reverse_bits(~temp_flags) >> 7;
}

static uint16_t reverse_bits(uint16_t num)
{
    uint16_t count = sizeof(num) * 8 - 1;
    uint16_t reverse_num = num;

    num >>= 1;
    while (num) {
        reverse_num <<= 1;
        reverse_num |= num & 1;
        num >>= 1;
        count--;
    }
    reverse_num <<= count;
    return reverse_num;
}
