#include <stdio.h>
#include <stdlib.h>

const int MAX_LENGTH = 255;

typedef char symbol;
typedef symbol* string;
typedef double data_t;
typedef int index;
typedef index* index_ptr;

data_t number(string, index_ptr);
data_t factor(string, index_ptr);
data_t calculation(string, index_ptr);
data_t brackets(string, index_ptr);

int main() {
  symbol target[255];
  fgets(target, sizeof(target), stdin);
  index i = 0;
  data_t n = calculation(target, &i);
  printf("%.2f\n", n);
  return 0;
}

data_t number(string target, index_ptr i) {
  data_t result = 0.0;
  data_t k = 10.0;
  int sign = 1;
  symbol c;
  c = target[*i];
  ++(*i);
  while (c == ' ') {
    c = target[*i];
    ++(*i);
  }
  if (c == '-') {
    sign = -1;
  } else {
    --(*i);
  }
  while (1) {
    c = target[*i];
    ++(*i);
    while (c == ' ') {
      c = target[*i];
      ++(*i);
    }
    if (c >= '0' && c <= '9') {
      result = result * 10.0 + (c - '0');
    } else {
      --(*i);
      break;
    }
  }
  c = target[*i];
  ++(*i);
  if (c == '.') {
    while (1) {
      c = target[*i];
      ++(*i);
      if (c >= '0' && c <= '9') {
        result += (c - '0') / k;
        k *= 10.0;
      } else {
        --(*i);
        break;
      }
    }
  } else {
    --(*i);
  }
  return sign * result;
}

data_t factor(string target, index_ptr i) {
  data_t result = brackets(target, i);
  data_t temp;
  symbol c;
  while (1) {
    c = target[*i];
    ++(*i);
    while (c == ' ') {
      c = target[*i];
      ++(*i);
    }
    switch (c) {
      case '*':
        result *= brackets(target, i);
        break;
      case '/':
        temp = brackets(target, i);
        if (temp == 0.0) {
          printf("[error]");
          exit(0);
        }
        result /= temp;
        break;
      default:
        --(*i);
        return result;
    }
  }
}

data_t calculation(string target, index_ptr i) {
  data_t result = factor(target, i);
  symbol c;
  while (1) {
    c = target[*i];
    ++(*i);
    while (c == ' ') {
      c = target[*i];
      ++(*i);
    }
    switch (c) {
      case '+':
        result += factor(target, i);
        break;
      case '-':
        result -= factor(target, i);
        break;
      default:
        --(*i);
        return result;
    }
  }
}

data_t brackets(string target, index_ptr i) {
  data_t result;
  int sign = 1;
  symbol c;
  c = target[*i];
  ++(*i);
  while (c == ' ') {
    c = target[*i];
    ++(*i);
  }
  if (c == '-') {
    sign = -1;
    c = target[*i];
    ++(*i);
  }
  while (c == ' ') {
    c = target[*i];
    ++(*i);
  }
  if (c == '(') {
    result = sign * calculation(target, i);
    c = target[*i];
    ++(*i);
    if (c != ')') {
      printf("[error]");
      exit(0);
    }
    return result;
  } else {
    --(*i);
    return sign * number(target, i);
  }
}
