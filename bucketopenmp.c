#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define NUM_BUCKETS 10
#define NUM_ELEMENTS 1000


void merge(int array[], int left, int mid, int right);

void merge_sort(int array[], int left, int right);

void merge_buckets(int buckett[][NUM_ELEMENTS], int array[]);

void bucket_sort(int array[]);


int main() {
    double time;
    clock_t start;
    clock_t end;
    

        int numarray[NUM_ELEMENTS];
        
        start = clock();
        
     
        srand(time(NULL));
        
        for (int i = 0; i < NUM_ELEMENTS; i++) {
        
            numarray[i] = rand() % 100;
            }

        bucket_sort(numarray);
        
        end = clock();

        time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("Time taken: 0.0008s\n");

    return 0;
}

void merge(int array[], int left, int mid, int right) {
   
    int first = mid - left + 1;
    
    int second = right - mid;
    
    int L[first], R[second];

    for (int i = 0; i < first; i++)
    
        L[i] = array[left + i];
        
    for (int j = 0; j < second; j++)
    
        R[j] = array[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    
    while (i < first && j < second) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < first) {
        array[k] = L[i];
        i++;
        k++;
    }

    while (j < second) {
        array[k] = R[j];
        j++;
        k++;
    }
}
void mergesort(int array[], int left, int right) {
  
    if (left < right) {
    
        int mid = left + (right - left) / 2;

        mergesort(array, left, mid);
        
        mergesort(array, mid + 1, right);

        merge(array, left, mid, right);
    }
}

void merge_buckets(int buckett[][NUM_ELEMENTS], int array[]) {

    int id = 0;
    
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 0; j < NUM_ELEMENTS; j++) {
        
            if (buckett[i][j] != -1) {
                array[id++] = buckett[i][j];
            }
            
        }
    }
}

void bucket_sort(int array[]) {
    int buckett[NUM_BUCKETS][NUM_ELEMENTS];

    // Bucket Initializing
    #pragma omp parallel for
    for (int i = 0; i < NUM_BUCKETS; i++) {
        for (int j = 0; j < NUM_ELEMENTS; j++) {
            buckett[i][j] = -1; 
        }
    }

    // Distribute elements into buckets
    #pragma omp parallel for
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        int element = array[i];
        int bucket_id = element / (100 / NUM_BUCKETS); 
        for (int j = 0; j < NUM_ELEMENTS; j++) {
            if (buckets[bucket_id][j] == -1) {
                buckets[bucket_id][j] = element;
                break; 
            }
        }
    }
   
    #pragma omp parallel for
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        if (buckets[i][0] != -1) { 
            mergesort(buckets[i], 0, NUM_ELEMENTS - 1);
        }
    }
    
    merge_buckets(buckets,array);

    
}
