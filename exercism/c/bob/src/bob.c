#include "bob.h"

char *hey_bob(char *greeting) {
    bool is_question = false;
    bool is_lower = false;
    bool is_alpha = false;
    bool is_silence = true;
    while (*greeting) {
        if (isalpha(*greeting)) {
            is_alpha = true;
        }
        if (islower(*greeting)) {
            is_lower = true;
        }
        if (!isspace(*greeting)) {
            is_silence = false;
            is_question = false;
        }
        if (*greeting == '?') {
            is_question = true;
        }
        greeting++;
    }
    if (is_alpha && !is_lower && is_question) {
        return "Calm down, I know what I'm doing!";
    }
    if (is_alpha && !is_lower) {
        return "Whoa, chill out!";
    }
    if (is_question) {
        return "Sure.";
    }
    if (is_silence) {
        return "Fine. Be that way!";
    }
    return "Whatever.";
}
