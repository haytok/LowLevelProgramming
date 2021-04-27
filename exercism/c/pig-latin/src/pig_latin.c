#include "pig_latin.h"

char *translate_word(const char *phrase) {
    char *ans;
    ans = malloc(sizeof(char) * 1024);
    if (
        is_vowel(phrase[0])
        || strncmp(phrase, "xr", 2) == 0
        || strncmp(phrase, "yt", 2) == 0
    ) {
        sprintf(ans, "%s%s", phrase, "ay");
        return ans;
    } else {
        // 子音のケース
        char *buf_1, *buf_2;
        buf_1 = malloc(sizeof(char) * 1024);
        buf_2 = malloc(sizeof(char) * 1024);
        int offset = 0;

        if (
            strncmp(phrase, "ch", 2) == 0
            || strncmp(phrase, "qu", 2) == 0
        ) {
            offset = 2;
        } else if (strstr(&phrase[1], "qu") == &phrase[1]) {
            offset = 3;
        } else if (strncmp(phrase, "y", 1) == 0) {
            offset = 1;
        } else {
            while (phrase[offset] != 'y' && !is_vowel(phrase[offset])) {
                offset++;
            }
            // offset = 1;
            // printf("buf %s, head %c\n", buf, *phrase);
        }
        strcpy(buf_1, phrase + offset);
        strncpy(buf_2, phrase, offset);
        sprintf(ans, "%s%s%s", buf_1, buf_2, "ay");
        return ans;
    }
    return ans;
}

// 母音かどうかを判定
bool is_vowel(char string) {
    if (isalpha(string)) {
        return (bool)strchr("aiueo", string);
    }
    return false;
}

// strdup 文字列を複製する。
// strtok NULL を第一引数に入れるてループを回すと、分解できるトークンへのポインタを返す。
char *translate(const char *phrase) {
    char *ans;
    ans = malloc(sizeof(char) * 1024);

    char *input_copy = strdup(phrase);
    char *word = strtok(input_copy, " ");
    while (word != NULL) {
        strcat(ans, translate_word(word));
        strcat(ans, " ");
        word = strtok(NULL, " ");
    }
    ans[strlen(ans) - 1] = '\0';
    return ans;
}

// ルール1：単語が母音で始まる場合は、単語の最後に「ay」の音を加える。
// なお、単語の先頭にある「xr」や「yt」は母音になるので注意してください
// （例：「xray」→「xrayay」、「yttria」→「yttriaay」）。
// ルール2：子音で始まる単語の場合、その子音を単語の最後に移動させ、さらに「ay」の音を加える。
// 子音は複数の子音で構成されることがあり、子音クラスターと呼ばれています
// （例："chair"→"airchay"）。
// ルール3：単語の先頭に "qu "に続く子音がある場合、その子音を単語の最後に移動させる。
// さらに "ay "の音を追加します（例："square" → "aresquay"）。
// ルール4：子音群の後や2文字の単語の2文字目に「y」が含まれる場合は、母音になります
// （例：「rhythm」→「ysmrhay」、「my」→「ymay」）。
