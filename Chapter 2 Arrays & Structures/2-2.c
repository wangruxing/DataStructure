#include <stdio.h>
#include <stdlib.h> /* 亂數相關函數 */
#include <time.h>   /* 時間相關函數 */
#include <string.h>

// Implementation structure and unions
typedef struct {
    // enum http://karosesblog.blogspot.com/2013/04/c-enum.html
    enum tag_field {female, male} sex;
    union {
        int children;
        int beard;
    } u;
} sex_type;

typedef struct {
    char name[10];
    int age;
    float salary;
    sex_type sex_info;
} human_being;
// Structural relationship
// human_being -> 型別為char的name
//             -> 型別為int的age
//             -> 型別為float的salary
//             -> 型別為結構sex_type的sex_info -> 型別為enum的sex
//                                            -> 型別為結構union的u -> 型別為int的children
//                                                                 -> 型別為int的beard
human_being person1, person2;
int main(void) {
    strcpy(person1.name, "james");
    person1.age=10;
    person1.salary=35000;
    person1.sex_info.sex = female;
    person1.sex_info.u.children = 2;

    strcpy(person2.name, "Alex");
    person2.age=20;
    person2.salary=85000;
    person2.sex_info.sex = male;
    person2.sex_info.u.beard = 1; 

    printf("person1: name=%s, age=%d, salary=%.2f, sex=%d, children=%d\n", 
    person1.name, person1.age, person1.salary, person1.sex_info.sex, person1.sex_info.u.children);
    printf("person2: name=%s, age=%d, salary=%.2f, sex=%d, beard=%d\n", 
    person2.name, person2.age, person2.salary, person2.sex_info.sex, person2.sex_info.u.beard);
    return 0;
}