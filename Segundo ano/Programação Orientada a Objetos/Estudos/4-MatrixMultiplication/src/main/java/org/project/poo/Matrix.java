/* Using "only" imperative programming yet. */

package org.project.poo;
import java.util.Scanner;

public class Matrix {
        private static Scanner read = new Scanner(System.in);

        public static void main(String[] args) {
                int column_A = 0, line_A = 0;
                int column_B = 0, line_B = 0;

                line_A   = read.nextInt();
                column_A = read.nextInt();
                line_B   = read.nextInt();
                column_B = read.nextInt();
                
                int[][] matrix_A = new int[line_A][column_A];
                int[][] matrix_B = new int[line_B][column_B];
                int[][] matrix_C = new int[line_A][column_B];

                scanMatrix(matrix_A);
                scanMatrix(matrix_B);
               
                multiplyMatrix(matrix_A, matrix_B, matrix_C);
                showMatrix(matrix_C);
                read.close();
        }

        public static void scanMatrix(int[][] matrix) {
                for(int i = 0, j; i < matrix.length; i++) {
                        for(j = 0; j < matrix[0].length; j++) {
                                System.out.printf("[%d][%d]: ", i, j);
                                matrix[i][j] = read.nextInt();
                        }
                }
        }

        public static void showMatrix(int[][] matrix) {
                for(int i = 0, j; i < matrix.length; i++) {
                        for(j = 0; j < matrix[0].length; j++)
                                System.out.print(matrix[i][j] + " ");

                        System.out.println("");
                }
        }

        public static void multiplyMatrix(int[][] A, int[][] B, int[][] C) {
                for(int i = 0, j, k; i < A.length; i++) {
                        for(j = 0; j < B[0].length; j++) {
                                for(k = 0; k < B.length; k++)
                                        C[i][j] += A[i][k] * B[k][j];
                        }
                }
        }
}
