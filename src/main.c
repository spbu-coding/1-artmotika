#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define error(...) (fprintf(stderr, __VA_ARGS__))

struct interval_t {
    double left_border;
    double right_border;
};

double Calculate_RectangleFormula(struct interval_t interval, unsigned int n){
    double number = n;
    double h = (interval.right_border - interval.left_border)/number;
    double area = 0;
    for (int i = 1; i <= n; ++i){
        area += h * sin(interval.left_border + h*i);
    }
    return area;
}

double Calculate_SimpsonFormula(struct interval_t interval, unsigned int n){
    if (n % 2 != 0) ++n;
    double number = n;
    double h = (interval.right_border - interval.left_border)/number;
    double h2 = h * 2.;
    double x = interval.left_border;
    double area = 0;
    for (int i = 0; i < n; i+=2, x+= h2){
        area += (sin(x) + 4.*(sin(x + h)) + sin(x + h*2))/3. * h;
    }
    return area;
}

int read_interval(struct interval_t *interval) {
    if (printf("Enter interval's left border: ") < 0) {
        error("Cannot wtite to stdout to stdout");
        return -1;
    }
    if (scanf("%lf", &(interval->left_border)) != 1) {
        error("Cannot read interval's left border");
    }
    if (interval->left_border < 0) {
        error("Left border of the interval must be greater than or equal to 0");
        return -1;
    }
    if (interval->left_border > M_PI) {
        error("Left border of the interval must be less than or equal to pi");
        return -1;
    }
    if (printf("Enter interval's right border: ") < 0) {
        error("Cannot wtite to stdout");
        return -1;
    }
    if (scanf("%lf", &(interval->right_border)) != 1) {
        error("Cannot read interval's right border");
    }
    if (interval->right_border > M_PI) {
        error("Right border of the interval must be less than or equal to pi");
        return -1;
    }
    if (interval->right_border < 0) {
        error("Right border of the interval must be greater than or equal to 0");
        return -1;
    }
    if (interval->left_border > interval->right_border) {
        error("Right border of the interval must be greater than left");
        return -1;
    }
    return 0;
}

void output_answers(struct interval_t interval, unsigned int partition_sizes[], int length_array){
    char* array_answers = (char*) malloc(80 * sizeof(char));


    double answer_sympson[length_array]; double answer_rectangles[length_array];

    for (int i = 0; i < length_array; ++i){
        answer_sympson[i] = Calculate_RectangleFormula(interval, partition_sizes[i]);
        answer_rectangles[i] = Calculate_SimpsonFormula(interval, partition_sizes[i]);
        sprintf(array_answers, "%d %.5lf %.5lf", partition_sizes[i], answer_sympson[i], answer_rectangles[i]);
        printf("%s\n", array_answers);
    }
}

int main() {
    struct interval_t interval = {0.0, 0.0};

    if (read_interval(&interval)) {
        return 1;
    }

    unsigned int partition_sizes[] = {6, 10, 20, 100, 500, 1000};
    int length_array = sizeof(partition_sizes)/ sizeof(partition_sizes[0]);
    output_answers(interval, partition_sizes, length_array);

    return 0;
}
