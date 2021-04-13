#include "grade_school.h"

static roster_t roster = { 0 };

bool add_student(char *name, uint8_t grade) {
    roster.students[roster.count] = (student_t) {grade, name};
    roster.count++;
    return true;
}

// 生徒の名前順に roster をソートする
roster_t get_roster() {
    // 名前でソート
    sort_by_name(&roster);
    // 学年でソート
    sort_by_grade(&roster);
    return roster;
}

roster_t get_grade(uint8_t desired_grade) {
    static roster_t ans = { 0 };
    int count = roster.count;
    for (int i = 0; i < count; i++) {
        if (roster.students[i].grade == desired_grade) {
            ans.students[i] = (student_t) {roster.students[i].grade, roster.students[i].name};
            ans.count++;
        }
    }
    // 名前でソート
    sort_by_name(&ans);
    return ans;
}

void sort_item(roster_t *ans, int index) {
    uint8_t tmp_grade = 0;
    char *tmp_name = malloc(sizeof(char *) * 1024);

    tmp_grade = ans->students[index-1].grade;
    strcpy(tmp_name, ans->students[index-1].name);

    ans->students[index-1].grade = ans->students[index].grade;
    ans->students[index-1].name = ans->students[index].name;

    ans->students[index].grade = tmp_grade;
    ans->students[index].name = tmp_name;
}

void sort_by_name(roster_t *roster) {
    int count = roster->count;
    for (int i = 1; i < count; i++) {
        for (int j = 1; j < count; j++) {
            if (strcmp(roster->students[j-1].name, roster->students[j].name) > 0) {
                sort_item(roster, j);
            }
        }
    }
}

void sort_by_grade(roster_t *roster) {
    int count = roster->count;
    for (int i = 1; i < count; i++) {
        for (int j = 1; j < count; j++) {
            if (roster->students[j-1].grade > roster->students[j].grade) {
                sort_item(roster, j);
            }
        }
    }
}

void clear_roster() {
    int count = roster.count;
    memset(roster.students, 0, count);
    roster.count = 0;
}

// Exercism を解く時は以下の手順を意識すると良い。
// 1. コンパイルが通る状態 (Compiling tests.out) を目指す。
// そのために、ヘッダーファイルやメインファイルにテストに必要な関数を定義する。
// 2. 定義した関数を実装していく。

// memset を使って配列を初期化する。
// strcmp を使ってソートする。
// 値渡しと参照渡しを実践してみた。上手い具合にソート系の関数を分割できて嬉しい。
