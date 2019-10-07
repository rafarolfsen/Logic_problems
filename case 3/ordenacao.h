#ifndef ORDENACAO_H
#define ORDENACAO_H

int* bubble_sort(int* vector, int size);            // método de ordenação simples tempo médio Big O(n²) e memória Big O(1)

void quick_sort(int* vector, int left, int right);  // método de ordenação complexo tempo médio Big O(n*log(n)) e memória Big O(n)

#endif