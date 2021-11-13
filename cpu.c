#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
int FLAG = 0;
// Матрица задается рандомно.
void randMatrix(double* matrix, int n)
{
srand(time(NULL));
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
matrix[i * n + j] = (double)(rand() % 31 + (-15));
}
}
}
// Выводим на экран матрицу
void print_both(double* matrix, int n)
{
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
printf("%7.3f ", matrix[i * n + j]);
}
printf("\n");
}
printf("\n");
getchar();
}
// Обмен строк в матрице
void swap_lines(double *matrix, int n, int i, int j)
{
double temp;
for (int k = 0; k < n; k++)
{
temp = -matrix[i * n + k];
matrix[i * n + k] = matrix[j * n + k];
matrix[j * n + k] = temp;
}
}
// Поставить на место row строку с наибольшим ведущим коэффициентом
void pivotize(double *matrix, int n, int row)
{
int max_index = row;
double max_value = fabs(matrix[row * n + row]);
double current_value;
for (int i = row + 1; i < n; i++)
{
current_value = fabs(matrix[i * n + row]);
if (current_value > max_value)
{
max_index = i;
max_value = current_value;
}
}
if (max_value == 0) { FLAG = 1; return; }
if (row != max_index)
{
swap_lines(matrix, n, row, max_index);
}
}
// Обнуление элементов под ведущим элементом в строке x
void subtract_below(double *matrix, int n, int x)
{
double coeff;
for (int i = x + 1; i < n; i++)
{
coeff = matrix[i * n + x] / matrix[x * n + x];
for (int j = x; j < n; j++)
{
matrix[i * n + j] -= coeff * matrix[x * n + j];
}
}
}
// Обращение матрицы методом Гаусса-Жордана
void Gauss_cpu(double *matrix, int n)
{
// Прямой ход
for (int i = 0; i < n - 1; i++)
{
// Обмен строк
pivotize(matrix, n, i);
if (FLAG == 1) return;
// Обнулить элементы ниже ведущего
subtract_below(matrix, n, i);
}
}
int main()
{
setlocale(LC_ALL, "Russian");
int n;
do
{
printf("Введите размерность матрицы (не менее 2)'n:'\n");
scanf("%d", &n);
} while (n < 2);
int f = n*n;
double* matrix = (double*)malloc(f * sizeof(double));
int m = sizeof(matrix);
randMatrix(matrix, n);
clock_t start, stop;
//print_both(matrix, n);
start = clock();
Gauss_cpu(matrix, n);
//print_both(matrix, n);
stop = clock();
double time = (stop - start) / (double)CLOCKS_PER_SEC;
printf("\nЗавершено\n");
printf(" %f seconds\n", time);
long double my_res = 1;
if (FLAG == 0)
{
for (int i = 0; i < n; i++)
{
my_res *= matrix[i*n + i];
}
}
else my_res = 0;
printf("DET=%f\n", my_res);
getchar();
free(matrix);
return 0;
}