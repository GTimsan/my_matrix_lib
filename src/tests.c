#include <check.h>

#include "s21_matrix.h"

START_TEST(test_s21_create) {
  matrix_t result;
  int test = s21_create_matrix(0, 0, &result);
  ck_assert_int_eq(test, 1);

  test = s21_create_matrix(10, 20, &result);
  ck_assert_int_eq(test, 0);
  s21_remove_matrix(&result);

  test = s21_create_matrix(-2, 2, &result);
  ck_assert_int_eq(test, 1);

  test = s21_create_matrix(0, 200, &result);
  ck_assert_int_eq(test, 1);
}
END_TEST

START_TEST(test_s21_eq) {
  matrix_t test1, test2;

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  test1.matrix[0][0] = 1;
  int code = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  code = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(code, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(1, 2, &test1);
  s21_create_matrix(1, 1, &test2);
  code = s21_eq_matrix(&test1, &test2);
  ck_assert_int_eq(code, FAILURE);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
}
END_TEST

START_TEST(test_s21_matrix_sum) {
  matrix_t test1, test2, result1, result2;

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  s21_create_matrix(1, 1, &result2);
  test1.matrix[0][0] = 1;
  result2.matrix[0][0] = 1;
  int code1 = s21_sum_matrix(&test1, &test2, &result1);
  int code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  test1.rows = -1;
  code1 = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_sum_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);
}
END_TEST

START_TEST(test_s21_matrix_sub) {
  matrix_t test1, test2, result1, result2;
  int code1, code2;
  test1.rows = -1;
  code1 = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_sub_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);

  s21_create_matrix(1, 1, &test1);
  s21_create_matrix(1, 1, &test2);
  s21_create_matrix(1, 1, &result2);
  test1.matrix[0][0] = 1;
  test2.matrix[0][0] = 1;
  code1 = s21_sub_matrix(&test1, &test2, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(test_s21_matrix_mult_number) {
  matrix_t test1, result1, result2;
  int number = 5;
  s21_create_matrix(1, 1, &test1);
  test1.matrix[0][0] = 1;
  s21_create_matrix(1, 1, &result2);
  result2.matrix[0][0] = 5;
  int code1 = s21_mult_number(&test1, number, &result1);
  int code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  test1.rows = -1;
  code1 = s21_mult_number(&test1, number, &result1);
  ck_assert_int_eq(code1, 1);
}
END_TEST
START_TEST(test_s21_matrix_mult_matrix) {
  matrix_t test1, test2, result1, result2;
  int code1, code2;
  s21_create_matrix(4, 3, &test1);
  s21_create_matrix(1, 2, &test2);
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);

  s21_create_matrix(2, 1, &test1);
  s21_create_matrix(1, 2, &test2);
  s21_create_matrix(2, 2, &result2);
  test1.matrix[0][0] = 2;
  test1.matrix[1][0] = 4;
  test2.matrix[0][0] = 1;
  test2.matrix[0][1] = 3;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 6;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = 12;
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&test2);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  test1.rows = -1;
  code1 = s21_mult_matrix(&test1, &test2, &result1);
  ck_assert_int_eq(code1, 1);
}
END_TEST

START_TEST(test_s21_transpose) {
  matrix_t test1, result1, result2;
  int code1, code2;
  test1.rows = -1;
  code1 = s21_transpose(&test1, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(1, 3, &test1);
  s21_create_matrix(3, 1, &result2);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 2;
  test1.matrix[0][2] = 3;
  result2.matrix[0][0] = 1;
  result2.matrix[1][0] = 2;
  result2.matrix[2][0] = 3;
  code1 = s21_transpose(&test1, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(2, 2, &test1);
  s21_create_matrix(2, 2, &result2);
  test1.matrix[0][0] = 1;
  test1.matrix[0][1] = 2;
  test1.matrix[1][0] = 3;
  test1.matrix[1][1] = 4;
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = 3;
  result2.matrix[1][0] = 2;
  result2.matrix[1][1] = 4;
  code1 = s21_transpose(&test1, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test1);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(test_s21_calc_complements) {
  matrix_t test, result1, result2;
  int code1, code2;
  test.rows = -1;
  code1 = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(2, 4, &test);
  s21_create_matrix(2, 2, &result1);
  code1 = s21_calc_complements(&test, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test);

  s21_create_matrix(1, 1, &test);
  s21_create_matrix(1, 1, &result2);
  test.matrix[0][0] = 5;
  result2.matrix[0][0] = 1;
  code1 = s21_calc_complements(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 2);
  ck_assert_int_eq(code2, FAILURE);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(3, 3, &test);
  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 0;
  test.matrix[1][1] = 4;
  test.matrix[1][2] = 2;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = 2;
  test.matrix[2][2] = 1;
  result2.matrix[0][0] = 0;
  result2.matrix[0][1] = 10;
  result2.matrix[0][2] = -20;
  result2.matrix[1][0] = 4;
  result2.matrix[1][1] = -14;
  result2.matrix[1][2] = 8;
  result2.matrix[2][0] = -8;
  result2.matrix[2][1] = -2;
  result2.matrix[2][2] = 4;
  code1 = s21_calc_complements(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(test_s21_determinant) {
  matrix_t test;
  double result;
  int code;
  test.rows = -1;
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 1);

  s21_create_matrix(2, 4, &test);
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&test);

  s21_create_matrix(1, 1, &test);
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&test);

  s21_create_matrix(2, 2, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[1][0] = 3;
  test.matrix[1][1] = 4;
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, -2);
  s21_remove_matrix(&test);

  s21_create_matrix(3, 3, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[1][0] = 4;
  test.matrix[1][1] = 5;
  test.matrix[1][2] = 6;
  test.matrix[2][0] = 7;
  test.matrix[2][1] = 8;
  test.matrix[2][2] = 9;
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&test);

  s21_create_matrix(4, 4, &test);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[0][2] = 3;
  test.matrix[0][3] = 4;
  test.matrix[1][0] = 5;
  test.matrix[1][1] = 6;
  test.matrix[1][2] = 7;
  test.matrix[1][3] = 8;
  test.matrix[2][0] = 9;
  test.matrix[2][1] = 10;
  test.matrix[2][2] = 11;
  test.matrix[2][3] = 12;
  test.matrix[3][0] = 13;
  test.matrix[3][1] = 14;
  test.matrix[3][2] = 15;
  test.matrix[3][3] = 16;
  code = s21_determinant(&test, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result, 0);
  s21_remove_matrix(&test);
}
END_TEST

START_TEST(test_s21_inverse) {
  matrix_t test, result1, result2;
  int code1, code2;
  test.rows = -1;
  code1 = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(code1, 1);

  s21_create_matrix(1, 1, &test);
  code1 = s21_inverse_matrix(&test, &result1);
  ck_assert_int_eq(code1, 2);
  s21_remove_matrix(&test);

  s21_create_matrix(2, 2, &test);
  s21_create_matrix(2, 2, &result2);
  test.matrix[0][0] = 1;
  test.matrix[0][1] = 2;
  test.matrix[1][0] = -1;
  test.matrix[1][1] = 2;
  result2.matrix[0][0] = 0.5;
  result2.matrix[0][1] = -0.5;
  result2.matrix[1][0] = 0.25;
  result2.matrix[1][1] = 0.25;

  code1 = s21_inverse_matrix(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);

  s21_create_matrix(3, 3, &test);
  s21_create_matrix(3, 3, &result2);
  test.matrix[0][0] = 2;
  test.matrix[0][1] = 5;
  test.matrix[0][2] = 7;
  test.matrix[1][0] = 6;
  test.matrix[1][1] = 3;
  test.matrix[1][2] = 4;
  test.matrix[2][0] = 5;
  test.matrix[2][1] = -2;
  test.matrix[2][2] = -3;
  result2.matrix[0][0] = 1;
  result2.matrix[0][1] = -1;
  result2.matrix[0][2] = 1;
  result2.matrix[1][0] = -38;
  result2.matrix[1][1] = 41;
  result2.matrix[1][2] = -34;
  result2.matrix[2][0] = 27;
  result2.matrix[2][1] = -29;
  result2.matrix[2][2] = 24;
  code1 = s21_inverse_matrix(&test, &result1);
  code2 = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(code1, 0);
  ck_assert_int_eq(code2, SUCCESS);
  s21_remove_matrix(&test);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

Suite *s21_matrix_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_matrix.h_tests");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_create);
  tcase_add_test(tc_core, test_s21_eq);
  tcase_add_test(tc_core, test_s21_matrix_sum);
  tcase_add_test(tc_core, test_s21_matrix_sub);
  tcase_add_test(tc_core, test_s21_matrix_mult_matrix);
  tcase_add_test(tc_core, test_s21_matrix_mult_number);
  tcase_add_test(tc_core, test_s21_transpose);
  tcase_add_test(tc_core, test_s21_calc_complements);
  tcase_add_test(tc_core, test_s21_determinant);
  tcase_add_test(tc_core, test_s21_inverse);

  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = s21_matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
