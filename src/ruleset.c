#include "ruleset.h"

RULESET* init_ruleset(char* rulestring)
{
    RULESET* new_ruleset = (RULESET*) malloc(sizeof(RULESET));

    // Initialize values
    new_ruleset->birth_flags = 0;
    new_ruleset->survival_flags = 0;

    parse_rulestring(new_ruleset, rulestring);

    return new_ruleset;
}

void parse_rulestring(RULESET* rules, char* rulestring)
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
                set_birth_flag(rules, token[i] - '0');
            }

            break;
        case 'S':
            for (i = 1; i < strlen(token); i++)
            {
                set_survival_flag(rules, token[i] - '0');
            }

            break;
        default:
            break;
        }

        token = strtok(NULL, "/");
    }
}

void set_birth_flag(RULESET* rules, const uint8_t n)
{
    rules->birth_flags |= 1 << n;
}

bool get_birth_flag(const RULESET* rules, const uint8_t n)
{
    return (rules->birth_flags >> n) & 1;
}

void set_survival_flag(RULESET* rules, const uint8_t n)
{
    rules->survival_flags |= 1 << n;
}

bool get_survival_flag(const RULESET* rules, const uint8_t n)
{
    return (rules->survival_flags >> n) & 1;
}


