#include <stdio.h>
void take_input(int r, int c, int arr[100][100]){
 
  printf("Input the elements of the sparse matrix.\n");
  for(int i=0; i < r; i++){
       for(int j=0; j < c; j++){
           scanf("%d", &arr[i][j]);
       }
 
  }
}
void print_trip_matrix(int r, int c, int arr[100][3]){

  printf("The triplet form of matrix is: \n");

  for(int i=0; i <= r; i++){
       for(int j=0; j < c; j++){
           printf("%d ", arr[i][j]);
       }
       printf("\n");
  }
   
}
int triplet_form(int r, int c, int arr[100][100], int tri_arr[100][3]){
   
   int row=0;
   
   
   for(int i=0; i < r; i++){
       for(int j=0; j < c; j++){
           if(arr[i][j] != 0){
               tri_arr[row][0] = i;
               tri_arr[row][1] = j;
               tri_arr[row][2] = arr[i][j];
               row++;
               
             }
       }
       
  }
  return row;
}
void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void simple_transpose(int arr[100][3], int non_zero_count, int original_rows, int original_cols){
    int transposed[100][3];
   
    // Create transpose by swapping row and column indices
    for(int i = 0; i < non_zero_count; i++){
        transposed[i][0] = arr[i][1];  // new row = old column
        transposed[i][1] = arr[i][0];  // new column = old row
        transposed[i][2] = arr[i][2];  // value remains same
    }
   
    // Sort the transposed matrix by row index, then by column index
    // Simple bubble sort for demonstration
    for(int i = 0; i < non_zero_count - 1; i++){
        for(int j = 0; j < non_zero_count - i - 1; j++){
            if(transposed[j][0] > transposed[j+1][0] ||
               (transposed[j][0] == transposed[j+1][0] && transposed[j][1] > transposed[j+1][1])){
                // Swap entire rows
                int temp[3];
                for(int k = 0; k < 3; k++){
                    temp[k] = transposed[j][k];
                    transposed[j][k] = transposed[j+1][k];
                    transposed[j+1][k] = temp[k];
                }
            }
        }
    }
   
    printf("\nThe simple transpose of the sparse matrix is:\n");
    printf("Row Col Value\n");
    for(int i=0; i < non_zero_count; i++){
        for(int j=0; j < 3; j++){
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
}

void fast_transpose(int original[100][3], int transposed[100][3], int non_zero_count, int original_cols){
    int count[100] = {0};
    int start_pos[100] = {0};
   
    // Count elements in each column
    for(int i = 0; i < non_zero_count; i++){
        count[original[i][1]]++;
    }
   
    // Calculate starting positions
    start_pos[0] = 0;
    for(int i = 1; i < original_cols; i++){
        start_pos[i] = start_pos[i-1] + count[i-1];
    }
   
    // Place elements directly
    for(int i = 0; i < non_zero_count; i++){
        int col = original[i][1];
        int pos = start_pos[col];
       
        transposed[pos][0] = original[i][1]; // new row = old column
        transposed[pos][1] = original[i][0]; // new column = old row
        transposed[pos][2] = original[i][2]; // value unchanged
       
        start_pos[col]++;
    }
   
    printf("\nThe Fast transpose of the sparse matrix is:\n");
    printf("Row Col Value\n");
    for(int i=0; i < non_zero_count; i++){
        for(int j=0; j < 3; j++){
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int r, c;

    printf("Enter the dimension of sparse matrix.\n");
    scanf("%d %d", &r, &c);
   
    int sparse_mat[100][100];
    int tri_arr[100][3];
    int fast_trans[100][3];

    take_input(r, c, sparse_mat);
   
    int row = triplet_form(r, c, sparse_mat, tri_arr);
   
    print_trip_matrix(row - 1, 3, tri_arr);
   
    simple_transpose(tri_arr, row, r, c);
   
    fast_transpose(tri_arr, fast_trans, row, c);

    return 0;
}