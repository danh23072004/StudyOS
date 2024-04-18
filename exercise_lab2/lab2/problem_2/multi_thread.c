#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct student_t
{
    char* name;
    int sid;
};

void* print_info(void* input)
{
    printf("Name: %s\n", ((struct student_t*)input)->name);
    printf("Student ID: %d\n", ((struct student_t*)input)->sid);
}

struct two_ints
{
    int a;
    int b;
};

int sum(int a, int b)
{

}

int main (int argc, char *argv[])
{
    struct student_t* John = (struct student_t *)malloc(sizeof(struct student_t));
    char jname[] = "John";
    John->name = jname;
    John->sid = 1122;

    pthread_t tid;
    pthread_create(&tid, NULL, print_info, (void*)John);
    pthread_join(tid, NULL);

    pthread_t tid_2;
    struct two_ints* twoNums = (struct two_ints *)malloc(sizeof(struct two_ints));
    twoNums->a = 10;
    twoNums->b = 20;
    

    return 0;
}