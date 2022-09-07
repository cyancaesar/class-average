#include <stdio.h>
#include <stdlib.h>

struct Student {
  int id;
  int *grade;
  int avg;
  char grade_score;
};

FILE *fPtr;

void get_grading_metadata(int *std_size, int *test_size);
void initialize_student_structure(struct Student **std, int std_size, int test_size);
void set_students_information(struct Student **std, int std_size, int test_size);
void compute_student_average(struct Student **std, int std_size, int test_size);
char compute_grade(int avg);
void print_students_information(struct Student **std, int std_size, int test_size);
void class_average(struct Student **std, int std_size, int test_size);

int main(void) {
  struct Student *std;
  int student_size, test_size;
  char file_path[100];

  printf("Enter a file path to save the results: ");
  scanf("%80s", file_path);

  fPtr = fopen(file_path, "w");
  if (fPtr == NULL) {
    printf("Error in file pointer.. exiting\n");
    exit(1);
  }

  get_grading_metadata(&student_size, &test_size);
  initialize_student_structure(&std, student_size, test_size);
  set_students_information(&std, student_size, test_size);
  compute_student_average(&std, student_size, test_size);
  print_students_information(&std, student_size, test_size);
  class_average(&std, student_size, test_size);

  fclose(fPtr);
  printf("Saved result at %s\n", file_path);
  return 0;
}

void get_grading_metadata(int *std_size, int *test_size) {
  printf("Enter the number of students: ");
  scanf("%d", std_size);

  printf("Good, you have %d students to grade..\nNow enter the number of tests: ", *std_size);
  scanf("%d", test_size);
  printf("Fancy, you have to grade %d tests for %d students..\n\n", *test_size, *std_size);
}

void initialize_student_structure(struct Student **std, int std_size, int test_size) {
  *std = (struct Student*)malloc(std_size * sizeof(struct Student));
  for (int i = 0; i < std_size; ++i) {
    (*std)[i].grade = (int*)malloc(test_size * sizeof(int));
  }
}

void set_students_information(struct Student **std, int std_size, int test_size) {
  for (int i = 0; i < std_size; ++i) {
    printf("Enter Student %d ID: ", i+1);
    scanf("%d", &(((*std)[i]).id));
    for (int j = 0; j < test_size; ++j) {
      printf("Enter Test %d grade: ", j+1);
      scanf("%d", &((*std)[i].grade[j]));
    }
    puts("");
  }
}

void compute_student_average(struct Student **std, int std_size, int test_size) {
  int sum = 0;
  for (int i = 0; i < std_size; ++i) {
    for (int j = 0; j < test_size; ++j) {
      sum += (*std)[i].grade[j];
    }
    (*std)[i].avg = sum / test_size;
    (*std)[i].grade_score = compute_grade((*std)[i].avg);
    sum = 0;
  }
}

char compute_grade(int avg) {
  switch (avg / 10) {
    case 10:
    case 9:
      return 'A';
      break;
    case 8:
      return 'B';
      break;
    case 7:
      return 'C';
      break;
    default:
      return 'D';
  }
}

void print_students_information(struct Student **std, int std_size, int test_size) {
  for (int i = 0; i < std_size; ++i) {
    //printf("-------------------------\n");
    printf("STUDENT %d\n", i+1);
    fprintf(fPtr, "STUDENT %d\n", i+1);
    printf("   │──────ID     : %d\n", (*std)[i].id);
    fprintf(fPtr, "   │──────ID     : %d\n", (*std)[i].id);
    for (int j = 0; j < test_size; ++j) {
      printf("   │──────TEST %d : %d\n", i+1, (*std)[i].grade[j]);
      fprintf(fPtr, "   │──────TEST %d : %d\n", i+1, (*std)[i].grade[j]);
    }
    printf("   │──────AVERAGE: %d\n", (*std)[i].avg);
    fprintf(fPtr, "   │──────AVERAGE: %d\n", (*std)[i].avg);
    printf("   └──────GRADE  : %c\n", (*std)[i].grade_score);
    fprintf(fPtr, "   └──────GRADE  : %c\n", (*std)[i].grade_score);
  }
}

void class_average(struct Student **std, int std_size, int test_size) {
  int class_avg, class_sum = 0;
  char class_grade;
  for (int i = 0; i < std_size; ++i) {
    class_sum += (*std)[i].avg;
  }
  class_avg = class_sum / std_size;
  class_grade = compute_grade(class_avg);

  printf("CLASS\n");
  fprintf(fPtr, "CLASS\n");
  printf("   │──────AVERAGE: %d\n", class_avg);
  fprintf(fPtr, "   │──────AVERAGE: %d\n", class_avg);
  printf("   └──────GRADE  : %c\n\n", class_grade);
  fprintf(fPtr, "   └──────GRADE  : %c\n", class_grade);
}

