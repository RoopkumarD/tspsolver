#include "utils.h"

int nxt_neighbour(int *arr, Py_ssize_t length, PyObject *nodes_weight) {
  int swap1 = 0;
  int swap2 = 0;
  int current_delta_cost = 0;

  for (int i = 0; i < length - 1; i++) {
    int max_combine = length - 3;
    if (length - (i + 2) < max_combine) {
      max_combine = length;
    } else {
      max_combine = (i + 2) + max_combine;
    }

    for (int j = i + 2; j < max_combine; j++) {
      int o_i = (i + 1) % length;
      int o_j = (j + 1) % length;

      int delta_cost = get_elem(nodes_weight, arr[i], arr[j]) +
                       get_elem(nodes_weight, arr[o_i], arr[o_j]) -
                       get_elem(nodes_weight, arr[i], arr[o_i]) -
                       get_elem(nodes_weight, arr[j], arr[o_j]);

      if (delta_cost < 0 && delta_cost < current_delta_cost) {
        swap1 = i;
        swap2 = j;
        current_delta_cost = delta_cost;
      }
    }
  }

  if (current_delta_cost < 0) {
    swap1 += 1;
    int width = swap2 - swap1;
    int end_elem = 0;

    if (width % 2 == 0) {
      end_elem = swap1 + (int)(width / 2);
    } else {
      end_elem = swap2 - (int)(width / 2);
    }

    for (int i = swap1; i < end_elem; i++) {
      int temp = arr[swap2 - (i - swap1)];
      arr[swap2 - (i - swap1)] = arr[i];
      arr[i] = temp;
    }
  }

  return current_delta_cost;
}

void hill_climb(int *arr, Py_ssize_t length, PyObject *nodes_weight) {
  random_walk(arr, length);
  int changed = 1;

  while (changed == 1) {
    changed = 0;
    int current_delta_cost = nxt_neighbour(arr, length, nodes_weight);
    if (current_delta_cost < 0) {
      changed = 1;
    }
  }

  return;
}
