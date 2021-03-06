#include "stdio.h"

#define ARGS 3
#define DATAPOINTS 4

typedef enum { false, true } bool;

int instructions();
int exit_program(int);
int selection_sort(int * data);
int insertion_sort(int * data);
int check_sorted(int * data);
void print_array(int * data);
int quicksort(int * data, int left, int right);
int partition(int * data, int left, int right, int pindex);

// take arguments for sort number and data file
int main(int argc, char *argv[]) {
 
  if (argc != ARGS)
    return instructions();

  int i;
  int sortnum = atoi(argv[1]);
  FILE * filein = fopen(argv[2],"r");
  if (filein == NULL) {
    printf("File did not open properly! Does it exist?\n");
    exit_program(1);
    return 0;
  }

  printf("======================================\n");
  printf("\tALL SORTS OF SORTS\n");
  printf("======================================\n\n");
  printf("Initial Array: \n");

  int data_array[DATAPOINTS];
  for (i = 0; i < DATAPOINTS; i++) {
    fscanf(filein, "%d,", &data_array[i]);
  }
  print_array(data_array);

  switch(sortnum) {
    case 1:
      printf("#1 - Selection Sort\n");
      selection_sort(data_array);
      break;
    case 2:
      printf("#2 - Insertion Sort\n");
      insertion_sort(data_array);
      break;
    case 3:
      printf("#3 - Quick Sort\n");
      int left = 0;
      int right = sizeof(data_array)/4;
      while (check_sorted(data_array) == 1)
        quicksort(data_array, left, right);
      break;
    case 4:
      printf("#4 - Merge Sort\n");
      break;
    case 5:
      printf("#5 - Heap Sort\n");
      break;
    case 6:
      printf("#6 - Radix Sort (LSD)\n");
      break;
    case 7:
      printf("#7 - Radix Sort (MSD)\n");
      break;
    case 8:
      printf("#8 - std_sort (gcc)\n");
      break;
    case 9:
      printf("#9 - std_stable_sort (gcc)\n");
      break;
    case 10:
      printf("#10 - Shell Sort\n");
      break;
    case 11:
      printf("#11 - Bubble Sort\n");
      break;
    case 12:
      printf("#12 - Cocktail Shaker Sort\n");
      break;
    case 13:
      printf("#13 - Gnome Sort\n");
      break;
    case 14:
      printf("#14 - Bitonic Sort\n");
      break;
    case 15:
      printf("#15 - Bogo Sort\n");
      break;
    default:
      printf("Improper sort number. Range 1-15.\n");
  }
  printf("\nFinal Sorted Array:\n");
  print_array(data_array);
  exit_program(check_sorted(data_array));
}

int selection_sort(int * data) {
  int i;
  int p = 0;  // p is placed location
  int fa = 0; // fa is found at location
  int min = data[0];

  for (p = 0; p < DATAPOINTS; p++) {
    // get the min
    min = data[p];
    for (i = p; i < DATAPOINTS; i++) {
      if (min > data[i]) {
        min = data[i];
        fa = i;
      }
    }
    
    // swap the min
    data[fa] = data[p];
    data[p] = min;
  }

  return min;
}

int insertion_sort(int * data) {
  int i,min;
  for (i = 1; i < DATAPOINTS; i++) {
    min = data[i];
    while (data[i] < data[i-1]) {
      data[i] = data[i-1];      
      data[i-1] = min;
      i--;
    }
  }
}

int quicksort(int * data, int left, int right) {
  int pindex = 0;
  printf("left: %d right: %d\n",left,right);
  if (left < right) {
    pindex = (right - left)/2;
    pindex = partition(data, left, right, pindex);
    quicksort(data, left, pindex-1);
    quicksort(data, pindex+1, right);
  printf("quicksort reporting.\n");
  print_array(data);
  }
}

// pivot index = pindex
// store index = stindex
int partition(int * data, int left, int right, int pindex) {
  int i,s,t, stindex;

  // move the pivot to the end of the partition
  t = data[pindex];
  data[pindex] = data[right];
  data[right] = t;

  // store the left index
  stindex = left;

  // step through each element of the partition
  for (i = left; i < right; i++) {
    // if the element contains a value smaller than the pivot element,
    // swap it for the stored index and increment the stored index
    if (data[i] <= t) {
      t = data[i];
      data[i] = data[stindex];
      data[stindex] = t;
      stindex++;
    }
  }

  s = data[stindex];
  data[stindex] = data[right];
  data[right] = s;
  printf("partition reporting.\n");
  print_array(data);
  return stindex;
}

int check_sorted(int * data) {
  int p;
  for (p = 0; p < DATAPOINTS-1; p++) {
    if (data[p] > data[p+1]) {
      printf("Array is not sorted correctly. This algorithm failed.\n");
      return 1;
    }
  }
  printf("Array sorted correctly! This algorithm did its job.\n");
  return 0;
}

void print_array(int * data) {
  int i;
  for (i = 0; i < DATAPOINTS; i++) {
    printf("%d ",data[i]);
  }
  printf("\n\n");
}

int exit_program(int result) {
  if (result == 1)
    printf("Program was not successful. My bad!\n\n");
  if (result == 0)
    printf("Program successfully completed.\n\n");
    printf("======================================\n");
  return 0;
}

int instructions() {
  printf("\n \
  Usage: ./main <sort> <data file>\n \
  Choose a sort from the following list:\n \
  1 - Selection sort\n \
  2 - Insertion \n \
  3 - Quick \n \
  4 - Merge \n \
  5 - Heap \n \
  6 - Radix sort (LSD)\n \
  7 - Radis sort (MSD)\n \
  8 - std_sort (gcc)\n \
  9 - std_stable_sort (gcc)\n \
  10 - Shell \n \
  11 - Bubble \n \
  12 - Cocktail Shaker \n \
  13 - Gnome \n \
  14 - Bitonic \n \
  15 - Bogo \n\n");
}

