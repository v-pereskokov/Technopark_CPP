#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

typedef enum { false, true } bool;
typedef unsigned long long u_long;

const int MAX_SIZE = 65;

u_long *myCalloc(size_t size)
{
  u_long *array = (u_long *) malloc(size * sizeof(u_long));
  if (!array) {
    printf("[error]\n");
    return NULL;
  }
  for (size_t i = 0; i < size; ++i)
    array[i] = 1;
  return array;
}

void myFree(u_long *array)
{
  if (array)
    free(array);
}

void transport(u_long *lhs, const u_long *rhs, const size_t size)
{
  memcpy(lhs, rhs, size * sizeof(*lhs));
}

u_long *trivialFactor(u_long target)
{
  u_long *result = NULL;
  if (target == 1) {
    result = myCalloc(2);
    result[1] = 0;
    return result;
  } else {
    u_long *tmp = myCalloc(MAX_SIZE);
    size_t i = 1;
    for (size_t j = 2; j * j <= target; ++j) {
      while (target % j == 0) {
        tmp[i] = j;
        target /= j;
        ++i;
      }
    }
    if (target > 1)
      tmp[i] = target;
    if (tmp[i] != 1)
      ++i;
    tmp[i] = 0;
    result = myCalloc(i + 1);
    transport(result, tmp, i + 1);
    myFree(tmp);
  }
  return result;
}

u_long *factor(u_long target)
{
  return trivialFactor(target);
}

void print(u_long *array)
{
  size_t i = 0;
  while (array[i] != 0)
    printf("%llu ", array[i++]);
  printf("\n");
}

bool check(const char *target)
{
  size_t i = 0;
  while (target[i] != '\0') {
    if (!isdigit(target[i++]))
      return false;
  }
  return true;
}

int main()
{
  char string[MAX_SIZE];
  if (scanf("%s", string) == 1 && check(string) == true) {
    u_long target = atol(string);
    if (target > 0 && target <= LLONG_MAX) {
      u_long *result = factor(target);
      if (result != NULL) {
        print(result);
        myFree(result);
      } else {
        printf("[error]\n");
        return 0;
      }
    } else {
      printf("[error]\n");
      return 0;
    }
  } else {
    printf("[error]\n");
    return 0;
  }
  return 0;
}
