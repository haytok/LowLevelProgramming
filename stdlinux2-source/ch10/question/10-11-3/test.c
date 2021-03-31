#include <string.h>
#include <stdio.h>

int main(void)
{
	char str[] = "abcdefghijklmnabcdefghijklmn", *p;
	int c;

	printf("検索文字を入力してください。");
	c = getchar();
	
	p = strrchr(str, c);
	if (p != NULL) {
		printf("%cは文字列の%ld番目にあります。\n", c, p-str);
        // この処理を呼び出すと、str が書き換わる。
        // The strchr() function returns a pointer to the first occurrence of the character c in the string s.
        // 対象の文字列のポインタを返す。
        *p = 'H';
		printf("以降の文字列は%sです。\n", p);
	}
	else
		printf("%cは見つかりませんでした\n", c);
		
	return 0;
}
