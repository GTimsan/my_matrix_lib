#include "s21_matrix.h"

int checker_two(matrix_t *a, matrix_t *b) {
    int error = 0;
    if ((checker_one(a) || checker_one(b))) {
        error = 1;
    } else if (!(a->rows == b->rows && a->columns == b->columns)) {
        error = 2;
    }
    return error;
}

int checker_one(matrix_t *a) {
    int error = 0;
    if (a == NULL || (a->rows < 1 || a->columns < 1)) {
        error = 1;
    }
    return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int error = checker_one(A);
    if (A->columns == 1 && A->rows == 1) {
        error = 2;
    } else if (!error && A->columns == A->rows) {
        double res = 0.0;
        s21_determinant(A, &res);
        if (result != 0) {
            matrix_t tmp;
            s21_calc_complements(A, &tmp);
            s21_transpose(&tmp, result);
            for (int i = 0; i < result->rows; i++) {
                for (int j = 0; j < result->columns; j++) {
                    result->matrix[i][j] = result->matrix[i][j] / res;
                }
            }
            s21_remove_matrix(&tmp);
            error = 0;
        }
    }
    return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int error = checker_one(A);
    if (!error) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] * number;
            }
        }
    }
    return error;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int error = checker_two(A, B);
    if (!error) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
                    error = FAILURE;
                    break;
                }
                error = SUCCESS;
            }
        }
    } else {
        error = FAILURE;
    }
    return error;
}

int slicer(matrix_t *main, int i_val, int j_val, matrix_t *minor) {
    int a = 0, b = 0;
    for (int i = 0; i < main->rows; i++) {
        if (i_val != i) {
            for (int j = 0; j < main->columns; j++) {
                if (j_val != j) {
                    minor->matrix[a][b] = main->matrix[i][j];
                    b++;
                }
            }
            b = 0;
            a++;
        }
    }
    return 0;
}


double minor_finder(matrix_t *m) {
    return m->matrix[0][0] * m->matrix[1][1] - m->matrix[0][1] * m->matrix[1][0];
}

double deter(matrix_t *m) {
    double val = 0;
    if (m->rows == 2 && m->columns == 2) {
        val = minor_finder(m);
    } else {
        for (int j = 0; j < m->columns; j++) {
            matrix_t tmp;
            s21_create_matrix(m->rows - 1, m->columns - 1, &tmp);
            slicer(m, 0, j, &tmp);
            int x = j % 2 == 0 ? 1 : -1;
            if (tmp.rows == 2) {
                val += x * m->matrix[0][j] * minor_finder(&tmp);
            } else {
                val += x * m->matrix[0][j] * deter(&tmp);
            }
            s21_remove_matrix(&tmp);
        }
    }
    return val;
}

int s21_determinant(matrix_t *A, double *result) {
    int error = checker_one(A);
    if (A->rows == 1 && A->columns == 1) {
        *result = A->matrix[0][0];
    } else if (!error && A->columns == A->rows) {
        *result = deter(A);
    } else if (!error && (A->columns > A->rows || A->columns < A->rows)) {
        error = 2;
    }
    return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int error = checker_one(A);
    if (!error && A->rows >= 2 && A->columns >= 2 && A->columns == A->rows) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                matrix_t m;
                s21_create_matrix(A->rows - 1, A->columns - 1, &m);
                slicer(A, i, j, &m);
                if (m.rows >= 2 && m.columns >= 2) {
                    result->matrix[i][j] = deter(&m) * pow(-1, i + j);
                } else if (m.rows == 1 && m.columns == 1) {
                    result->matrix[i][j] = m.matrix[0][0] * pow(-1, i + j);
                }
                s21_remove_matrix(&m);
            }
        }
    } else if ((!error && (A->rows < 2 || A->columns < 2)) || (A->columns != A->rows && !error)) {
        error = 2;
    }
    return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int error = checker_one(A);
    if (!error) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[j][i];
            }
        }
    }
    return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error = 0;
    if (checker_one(A) || checker_one(B)) {
        error = 1;
    } else if (A->rows > 0 && B->columns > 0 && A->columns == B->rows) {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = 0;
                for (int k = 0; k < A->columns; k++) {
                    result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                }
            }
        }
    } else {
        error = 2;
    }
    return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error = checker_two(A, B);
    if (!error) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    }
    return error;
}


int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int error = checker_two(A, B);
    if (!error) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    }
    return error;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int error = 1;
    if (result != NULL) {
        result->columns = columns;
        result->rows = rows;

        if (rows > 0 && columns > 0) {
            result->matrix = (double **) calloc(rows, sizeof(double *));
            for (int i = 0; i < result->rows; i++) {
                result->matrix[i] = (double *) calloc(result->columns, sizeof(double));
            }
            error = 0;
        }
    }
    return error;
}

void s21_remove_matrix(matrix_t *A) {
    if (A != NULL) {
        if (A->rows > 0 && A->columns > 0) {
            if (A->matrix != NULL) {
                for (int i = 0; i < A->rows; i++) {
                    free(A->matrix[i]);
                }
                free(A->matrix);
            }
        }
        A->matrix = NULL;
        A->columns = 0;
        A->rows = 0;
    }
}
