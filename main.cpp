#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <conio.h>
#define CLEAR "cls"
#else
#define CLEAR "clear"
#define getch() getchar()
#endif

typedef struct {
    char name[15];
    int code;
    double rate;
} product;

void add();
void by_rate();
void by_name();
void by_code();
void viewBYname();
void viewBYcode();
void viewBYrate();
void dltByName();
void dltByCode();

int main() {
    int choice;
    do {
        system(CLEAR);
        printf("\n==================== INVENTORY MANAGEMENT ====================\n");
        printf("[1] Add item\n");
        printf("[2] Buy (delete) by name\n");
        printf("[3] Buy (delete) by code\n");
        printf("[4] Search by name\n");
        printf("[5] Search by code\n");
        printf("[6] Search by rate\n");
        printf("[7] View by name\n");
        printf("[8] View by code\n");
        printf("[9] View by rate\n");
        printf("[0] Exit\n");
        printf("==============================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline

        switch(choice) {
            case 1: add(); break;
            case 2: dltByName(); break;
            case 3: dltByCode(); break;
            case 4: by_name(); break;
            case 5: by_code(); break;
            case 6: by_rate(); break;
            case 7: viewBYname(); break;
            case 8: viewBYcode(); break;
            case 9: viewBYrate(); break;
            case 0: printf("\nExiting...\n"); break;
            default: printf("Invalid choice!\n"); getch(); break;
        }
    } while (choice != 0);

    return 0;
}

void add() {
    FILE *f = fopen("list.txt", "a");
    product p;
    printf("Enter item code: ");
    scanf("%d", &p.code);
    printf("Enter item name: ");
    scanf("%s", p.name);
    printf("Enter item rate: ");
    scanf("%lf", &p.rate);
    fprintf(f, "%d %s %.2lf\n", p.code, p.name, p.rate);
    fclose(f);
    printf("Item added successfully!\n");
    getch();
}

void by_code() {
    FILE *f = fopen("list.txt", "r");
    int code, found = 0;
    product p;
    printf("Enter code to search: ");
    scanf("%d", &code);
    while (fscanf(f, "%d %s %lf", &p.code, p.name, &p.rate) == 3) {
        if (p.code == code) {
            printf("\nFound: %d %s %.2lf\n", p.code, p.name, p.rate);
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found!\n");
    fclose(f);
    getch();
}

void by_name() {
    FILE *f = fopen("list.txt", "r");
    char name[15];
    int found = 0;
    product p;
    printf("Enter name to search: ");
    scanf("%s", name);
    while (fscanf(f, "%d %s %lf", &p.code, p.name, &p.rate) == 3) {
        if (strcmp(p.name, name) == 0) {
            printf("\nFound: %d %s %.2lf\n", p.code, p.name, p.rate);
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found!\n");
    fclose(f);
    getch();
}

void by_rate() {
    FILE *f = fopen("list.txt", "r");
    double rate;
    int found = 0;
    product p;
    printf("Enter rate to search: ");
    scanf("%lf", &rate);
    while (fscanf(f, "%d %s %lf", &p.code, p.name, &p.rate) == 3) {
        if (p.rate == rate) {
            printf("\nFound: %d %s %.2lf\n", p.code, p.name, p.rate);
            found = 1;
            break;
        }
    }
    if (!found) printf("Item not found!\n");
    fclose(f);
    getch();
}

void viewBYname() {
    FILE *f = fopen("list.txt", "r");
    product list[100], temp;
    int n = 0;
    while (fscanf(f, "%d %s %lf", &list[n].code, list[n].name, &list[n].rate) == 3)
        n++;
    fclose(f);

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (strcmp(list[i].name, list[j].name) > 0) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }

    printf("\nCode\tName\tRate\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.2lf\n", list[i].code, list[i].name, list[i].rate);
    getch();
}

void viewBYcode() {
    FILE *f = fopen("list.txt", "r");
    product list[100], temp;
    int n = 0;
    while (fscanf(f, "%d %s %lf", &list[n].code, list[n].name, &list[n].rate) == 3)
        n++;
    fclose(f);

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (list[i].code > list[j].code) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }

    printf("\nCode\tName\tRate\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.2lf\n", list[i].code, list[i].name, list[i].rate);
    getch();
}

void viewBYrate() {
    FILE *f = fopen("list.txt", "r");
    product list[100], temp;
    int n = 0;
    while (fscanf(f, "%d %s %lf", &list[n].code, list[n].name, &list[n].rate) == 3)
        n++;
    fclose(f);

    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (list[i].rate > list[j].rate) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }

    printf("\nCode\tName\tRate\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%s\t%.2lf\n", list[i].code, list[i].name, list[i].rate);
    getch();
}

void dltByName() {
    FILE *f = fopen("list.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char name[15];
    product p;
    int found = 0;

    printf("Enter name to delete: ");
    scanf("%s", name);

    while (fscanf(f, "%d %s %lf", &p.code, p.name, &p.rate) == 3) {
        if (strcmp(p.name, name) != 0) {
            fprintf(temp, "%d %s %.2lf\n", p.code, p.name, p.rate);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("list.txt");
    rename("temp.txt", "list.txt");

    if (found)
        printf("Item deleted.\n");
    else
        printf("Item not found.\n");
    getch();
}

void dltByCode() {
    FILE *f = fopen("list.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int code;
    product p;
    int found = 0;

    printf("Enter code to delete: ");
    scanf("%d", &code);

    while (fscanf(f, "%d %s %lf", &p.code, p.name, &p.rate) == 3) {
        if (p.code != code) {
            fprintf(temp, "%d %s %.2lf\n", p.code, p.name, p.rate);
        } else {
            found = 1;
        }
    }

    fclose(f);
    fclose(temp);
    remove("list.txt");
    rename("temp.txt", "list.txt");

    if (found)
        printf("Item deleted.\n");
    else
        printf("Item not found.\n");
    getch();
}
