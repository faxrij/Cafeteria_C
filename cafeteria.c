#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define SIZE get_size("cafeteria_march_menu.csv")

//Ümmü Zeynep BEKTAŞ
//270201070

//Fakhri JAFAROV
//280201110

typedef struct Menu {
    char* date;
    char* soup;
    char* main_dish;
    char* side_dish;
    char* extra;
    int sale_count[3];
} Menu;


typedef struct Cafeteria {
    char* month;
    Menu* normal_menu_array_ptr;
    Menu* vegan_menu_array_ptr;
    Menu* vegetarian_menu_array_ptr;
} Cafeteria;


int get_size(char *csv_file_name) {
    FILE *fptr = fopen(csv_file_name, "r");
    char line[120];
    int count = 0;
    
    while (fgets(line, 120, fptr)) {
        count++;
    }
    
    fclose(fptr);
    
    return (count/3);
}


void read_file_record_menus(char *csv_file_name, Menu* normalArray, Menu* veganArray, Menu* vegetarianArray) {

    FILE *fptr;
    char line[120];

    fptr = fopen(csv_file_name, "r");

    int i = 0;
    char* menu_type = malloc(sizeof(char) * 20);

    while (fgets(line, 120, fptr) != NULL) {

        char* splitted;
        splitted = strtok(line, ",");

        menu_type = strdup(splitted);

        struct Menu* menu = (Menu*) malloc(sizeof(Menu));

        menu->date = strdup(strtok(NULL, ","));
        menu->soup = strdup(strtok(NULL, ","));
        menu->main_dish = strdup(strtok(NULL, ","));
        menu->side_dish = strdup(strtok(NULL, ","));
        menu->extra = strtok(strdup(strtok(NULL, ",")), "\n");
        
        
        if (strcmp(menu_type, "\"Normal\"") == 0) {
            normalArray[i] = *menu;

        } else if (strcmp(menu_type, "\"Vegan\"") == 0) {
            veganArray[i] = *menu;

        } else if (strcmp(menu_type, "\"Vegetarian\"") == 0) {
            vegetarianArray[i] = *menu;

        }


        i++;
        if (i == SIZE) {
            i = 0;
        }
    }

    fclose(fptr);
}


void record_customer_counts(Cafeteria *cafeteria) {

    srand(time(NULL));
    int num;

    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < 3; i++) {
            num = rand();
            num = num % 50; 
            (cafeteria->normal_menu_array_ptr)[j].sale_count[i] = num;

            num = rand();
            num = num % 50; 
            (cafeteria->vegan_menu_array_ptr)[j].sale_count[i] = num;

            num = rand();
            num = num % 50; 
            (cafeteria->vegetarian_menu_array_ptr)[j].sale_count[i] = num;
        }
    }
}

void initialize_menus(Cafeteria *cafeteria, char *csv_file_name) {

    Menu* normal_menu_array_ptr = (Menu*) malloc(23 * sizeof(Menu));
    Menu* vegan_menu_array_ptr = (Menu*) malloc(23 * sizeof(Menu));
    Menu* vegetarian_menu_array_ptr = (Menu*) malloc(23 * sizeof(Menu));

    char month_name[10];
    sscanf(csv_file_name, "%*[^_ ]_%9[^_]", month_name);
    
    cafeteria->month = month_name;
    cafeteria->normal_menu_array_ptr = normal_menu_array_ptr;
    cafeteria->vegan_menu_array_ptr = vegan_menu_array_ptr;
    cafeteria->vegetarian_menu_array_ptr = vegetarian_menu_array_ptr;

    read_file_record_menus(csv_file_name, normal_menu_array_ptr, vegan_menu_array_ptr, vegetarian_menu_array_ptr);

    record_customer_counts(cafeteria);
}


void calc_and_show_income(Cafeteria* cafeteria) {

    int student_income = 0;
    int academic_income = 0;
    int administrative_income = 0;


    for (int i = 0; i < SIZE; i++){

        student_income += (cafeteria->normal_menu_array_ptr)[i].sale_count[0] * 6;
        student_income += (cafeteria->vegan_menu_array_ptr)[i].sale_count[0] * 6;
        student_income += (cafeteria->vegetarian_menu_array_ptr)[i].sale_count[0] * 6;

        academic_income += cafeteria->normal_menu_array_ptr[i].sale_count[1] * 16;
        academic_income += cafeteria->vegan_menu_array_ptr[i].sale_count[1] * 16;
        academic_income += cafeteria->vegetarian_menu_array_ptr[i].sale_count[1] * 16;

        administrative_income += cafeteria->normal_menu_array_ptr[i].sale_count[2] * 12;
        administrative_income += cafeteria->vegan_menu_array_ptr[i].sale_count[2] * 12;
        administrative_income += cafeteria->vegetarian_menu_array_ptr[i].sale_count[2] * 12;
    }

    int normal_menu_sales = 0;
    int vegan_menu_sales = 0;
    int vegetarian_menu_sales = 0;
    
    for (int i = 0; i < SIZE; i++){

        normal_menu_sales += cafeteria->normal_menu_array_ptr[i].sale_count[0] * 6;
        normal_menu_sales += cafeteria->normal_menu_array_ptr[i].sale_count[1] * 16;
        normal_menu_sales += cafeteria->normal_menu_array_ptr[i].sale_count[2] * 12;

        vegan_menu_sales += cafeteria->vegan_menu_array_ptr[i].sale_count[0] * 6;
        vegan_menu_sales += cafeteria->vegan_menu_array_ptr[i].sale_count[1] * 16;
        vegan_menu_sales += cafeteria->vegan_menu_array_ptr[i].sale_count[2] * 12;

        vegetarian_menu_sales += cafeteria->vegetarian_menu_array_ptr[i].sale_count[0] * 6;
        vegetarian_menu_sales += cafeteria->vegetarian_menu_array_ptr[i].sale_count[1] * 16;
        vegetarian_menu_sales += cafeteria->vegetarian_menu_array_ptr[i].sale_count[2] * 12;
        
    }

    int total = normal_menu_sales + vegan_menu_sales + vegetarian_menu_sales;

    printf("\n************ The Sales Results ************\n");
    printf("Normal menu sales: %d TL, Vegan menu sales: %d TL, Vegetarian menu sales:%d TL\n", normal_menu_sales,vegan_menu_sales,vegetarian_menu_sales);

    printf("Student sales: %d TL, Academic personel sales: %d TL, Administrative personel sales: %d TL\n", student_income, academic_income, administrative_income);

    printf("Total sale income: %d TL\n", total);
}


void display_menu(Menu* menu_ptr, int index) {

    printf("Date: %s\n", menu_ptr[index].date);
    printf("Soup: %s\n", menu_ptr[index].soup);
    printf("Main Dish: %s\n", menu_ptr[index].main_dish);
    printf("Side Dish: %s\n", menu_ptr[index].side_dish);
    printf("Extra: %s\n", menu_ptr[index].extra);
}

void output_menu(Menu* menu_ptr, int index) {

    printf("%s|%s|%s|%s|%s\n", menu_ptr[index].date,menu_ptr[index].soup,
    menu_ptr[index].main_dish, menu_ptr[index].side_dish, menu_ptr[index].extra);
}

void display_counts(Menu* menu_ptr, int index) {

    printf("Student:%d, Academic:%d, Administrative:%d\n", 
    menu_ptr[index].sale_count[0], menu_ptr[index].sale_count[1], menu_ptr[index].sale_count[2]);
}

int main(){

    Cafeteria* cafeteria = (Cafeteria*) malloc(sizeof(Cafeteria));

    initialize_menus(cafeteria, "cafeteria_march_menu.csv");

    printf("~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    display_menu(cafeteria->normal_menu_array_ptr, 0);
    printf("\n~ ~ ~ ~ Normal menu for the first and last days of the month:\n");
    display_menu(cafeteria->normal_menu_array_ptr, (SIZE - 1));

    printf("\n~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    display_menu(cafeteria->vegan_menu_array_ptr, 0);
    printf("\n~ ~ ~ ~ Vegan menu for the first and last days of the month:\n");
    display_menu(cafeteria->vegan_menu_array_ptr, (SIZE - 1));

    printf("\n~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    display_menu(cafeteria->vegetarian_menu_array_ptr, 0);
    printf("\n~ ~ ~ ~ Vegetarian menu for the first and last days of the month:\n");
    display_menu(cafeteria->vegetarian_menu_array_ptr, (SIZE - 1));


    printf("\nOutput for normal menu ====> ");
    output_menu(cafeteria->normal_menu_array_ptr, 2);
    
    printf("\nOutput for vegan menu ====> ");
    output_menu(cafeteria->vegan_menu_array_ptr, 7);

    printf("\nOutput for vegetarian menu ====> ");
    output_menu(cafeteria->vegetarian_menu_array_ptr, 13);

    printf("\nCounts for the normal menu output of March 3rd ====> ");
    display_counts(cafeteria->normal_menu_array_ptr, 2);

    printf("\nCounts for the vegan menu output of March 10th ====> ");
    display_counts(cafeteria->vegan_menu_array_ptr, 7);

    printf("\nCounts for the vegetarian menu output of March 20th ====> ");
    display_counts(cafeteria->vegetarian_menu_array_ptr, 13);

    calc_and_show_income(cafeteria);

    return 0;
}