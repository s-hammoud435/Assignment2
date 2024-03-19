#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define NUM_THREADS 4 
#define NUM_BUCKETS 10
#define NUM_ELEMENTS 1000

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);
void merge_buckets(int buckets[][NUM_ELEMENTS], int arr[]);
void bucket_sort(int arr[]);
void * runner(void * args);


typedef struct ThreadArgs{
    int (*arr)[NUM_ELEMENTS];
    int left;
    int right;
} thread_args;


int main() {

    double time_taken;
    clock_t start, end;
    srand(time(NULL));
      
        int numbers_array[NUM_ELEMENTS];
        
        start = clock();
        
        for (int i = 0; i < NUM_ELEMENTS; i++) {
            numbers_array[i] = rand() % 100; 
        }

        bucket_sort(numbers_array);
       
        end = clock();

        time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
  
    printf("Time taken: %f seconds\n", time_taken);

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
    
    pthread_t threads[NUM_THREADS];
    
    thread_args t_args[NUM_THREADS];
    
    int buckett_for_thread = NUM_BUCKETS / NUM_THREADS;

    for (int i = 0; i < NUM_BUCKETS; i++) {
    
        for (int j = 0; j < NUM_ELEMENTS; j++) {
        
            buckett[i][j] = -1; 
        }
    }

   
       for (int i = 0; i < NUM_ELEMENTS; i++) {
       
        int element = array[i];
        
        int bucket_id = element / (100 / NUM_BUCKETS); 

        
        for (int j = 0; j < NUM_ELEMENTS; j++) {
        
            if (buckett[bucket_id][j] == -1) {
                buckett[bucket_id][j] = element;
                break; 
                
            }
        }
    }

    for(int i=0;i<NUM_THREADS;i++){
    
        t_args[i].array = buckett;
        t_args[i].left = i * buckett_for_thread;
        t_args[i].right = (i + 1) * buckett_for_thread;

        
        if (i == NUM_THREADS - 1) {
        
            t_args[i].right = NUM_BUCKETS;
        }
        
        
        pthread_create(&threads[i], NULL, runner,(void*) &t_args[i]);
    }
    
     for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL); 
    }
   
    merge_buckets(buckett, array);
}


void * runner(void * args){
    thread_args * t_args = (thread_args *) args;
   
    for (int i = t_args->left; i < t_args->right; i++) {
        if (t_args->array[i][0] != -1) {
 
            merge_sort(t_args->array[i], 0, NUM_ELEMENTS - 1);
        }
    }
    pthread_exit(0);
}
