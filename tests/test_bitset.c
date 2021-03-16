/*
 * Copyright (c) 2020 Adil Benhlal <adil.benhlal@outlook.fr>
 *
 * bitset is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */
#include <assert.h>
#include <stdio.h>

#include "bitset.h"

void test_bitset_new() {
  // test 0
  
  bitset_t *bs_null = bitset_new(0);
  assert(bs_null->array != NULL);
  assert(bs_null->count == 0);
  assert(bs_null->flip == false);
  assert(bs_null->size == 0);
  bitset_delete(bs_null);

  // test multiple de 2
  bitset_t *bs_pow2 = bitset_new(1024);
  assert(bs_pow2->count == 0);
  assert(bs_pow2->array != NULL);
  assert(bs_pow2->flip == false);
  assert(bs_pow2->size == 1024);
  bitset_delete(bs_pow2);

  // test non multiple de 2
  bitset_t *bs_not_pow2 = bitset_new(45);
  assert(bs_not_pow2->array != NULL);
  assert(bs_not_pow2->count == 0);
  assert(bs_not_pow2->flip == false);
  assert(bs_not_pow2->size == 45);
  bitset_delete(bs_not_pow2);
}

void test_bitset_delete() {
  bitset_t *bs = bitset_new(100);
  assert(bs != NULL);
  bitset_delete(bs);
}

void test_bitset_count() {
  bitset_t *bs = bitset_new(100);
  assert(bitset_count(bs) == 0);

  // Test si le count change bien
  bitset_set(bs, 5, true);
  assert(bitset_count(bs) == 1);
  // Test set 2x si le count reste à la même valeur
  bitset_set(bs, 5, true);
  assert(bitset_count(bs) == 1);
  // Test si le count change avec une valeur false
  bitset_set(bs, 1, false);
  assert(bitset_count(bs) == 1);
  // changer la valeur de 5 -> count == 0
  bitset_set(bs, 5, false);
  assert(bitset_count(bs) == 0);
  // On remet le 5eme bit a vrai
  bitset_set(bs, 5, true);
  assert(bitset_count(bs) == 1);

  // Test si le flip fonctionne au niveau du count
  bitset_flip(bs);
  // bs->count doit être égale à 1
  assert(bs->count == 1);
  // mais le count retourner par la fonction change à 99
  assert(bitset_count(bs) == 99);

  bitset_delete(bs);
}

void test_bitset_size() {
  bitset_t *bs_null = bitset_new(0);
  assert(bs_null->size == 0);
  assert(bitset_size(bs_null) == 0);
  bitset_delete(bs_null);

  bitset_t *bs_pow2 = bitset_new(1024);
  assert(bs_pow2->size == 1024);
  assert(bitset_size(bs_pow2) == 1024);
  bitset_delete(bs_pow2);

  bitset_t *bs_not_pow2 = bitset_new(45);
  assert(bs_not_pow2->size == 45);
  assert(bitset_size(bs_not_pow2) == 45);
  bitset_delete(bs_not_pow2);
}

void test_bitset_test() {
  bitset_t *bs = bitset_new(8);
  uint8_t *array = (uint8_t *)bs->array;

  for (size_t i = 0; i < 8; i++) {
    assert(bitset_test(bs, i) == false);
  }
  assert(array[0] == 0);

  bitset_flip(bs);
  for (size_t i = 0; i < 8; i++) {
    assert(bitset_test(bs, i) == true);
  }
  assert(array[0] == 0);

  for (size_t i = 0; i < 8; i++) {
    bitset_set(bs, i, false);
  }

  for (size_t i = 0; i < 8; i++) {
    assert(bitset_test(bs, i) == false);
  }
  assert(array[0] == UINT8_MAX);

  bitset_flip(bs);
  for (size_t i = 0; i < 8; i++) {
    assert(bitset_test(bs, i) == true);
  }
  assert(array[0] == UINT8_MAX);

  bitset_set(bs, 4, false);
  assert(bitset_test(bs, 4) == false);
  assert(array[0] == 0xEF);

  bitset_flip(bs);
  assert(bitset_test(bs, 4) == true);
  assert(array[0] == 0xEF);

  bitset_delete(bs);
}

void test_bitset_any() {
  bitset_t *bs = bitset_new(8);
  uint8_t *array = (uint8_t *)bs->array;

  assert(bitset_any(bs) == false);
  assert(array[0] == 0);

  bitset_flip(bs);
  assert(bitset_any(bs) == true);
  assert(array[0] == 0);

  for (size_t i = 0; i < 8; i++) {
    bitset_set(bs, i, false);
  }

  assert(bitset_any(bs) == false);
  assert(array[0] == UINT8_MAX);

  bitset_flip(bs);
  assert(bitset_any(bs) == true);
  assert(array[0] == UINT8_MAX);

  bitset_set(bs, 0, false);
  assert(bitset_any(bs) == true);
  assert(array[0] == 0xFE);

  bitset_flip(bs);
  assert(bitset_any(bs) == true);
  assert(array[0] == 0xFE);

  bitset_delete(bs);
}

void test_bitset_none() {
  bitset_t *bs = bitset_new(8);
  uint8_t *array = (uint8_t *)bs->array;

  assert(bitset_none(bs) == true);
  assert(array[0] == 0);

  bitset_flip(bs);
  assert(bitset_none(bs) == false);
  assert(array[0] == 0);

  for (size_t i = 0; i < 8; i++) {
    bitset_set(bs, i, false);
  }

  assert(bitset_none(bs) == true);
  assert(array[0] == UINT8_MAX);

  bitset_flip(bs);
  assert(bitset_none(bs) == false);
  assert(array[0] == UINT8_MAX);

  bitset_set(bs, 0, false);
  assert(bitset_none(bs) == false);
  assert(array[0] == 0xFE);

  bitset_flip(bs);
  assert(bitset_none(bs) == false);
  assert(array[0] == 0xFE);

  bitset_delete(bs);
}

void test_bitset_all() {
  bitset_t *bs = bitset_new(8);
  uint8_t *array = (uint8_t *)bs->array;

  assert(bitset_all(bs) == false);
  assert(array[0] == 0);

  bitset_flip(bs);
  assert(bitset_all(bs) == true);
  assert(array[0] == 0);

  for (size_t i = 0; i < 8; i++) {
    bitset_set(bs, i, false);
  }

  assert(bitset_all(bs) == false);
  assert(array[0] == UINT8_MAX);

  bitset_flip(bs);
  assert(bitset_all(bs) == true);
  assert(array[0] == UINT8_MAX);

  bitset_set(bs, 0, false);
  assert(bitset_all(bs) == false);
  assert(array[0] == 0xFE);

  bitset_flip(bs);
  assert(bitset_all(bs) == false);
  assert(array[0] == 0xFE);

  bitset_delete(bs);
}

void test_bitset_set() {
  bitset_t *bs = bitset_new(100);
  uint8_t *array = (uint8_t *)bs->array;

  bitset_set(bs, 0, true);
  assert(bs->count == 1);
  assert((array[0] & 1) == 1);

  bitset_set(bs, 0, false);
  assert(bs->count == 0);
  assert((array[0] & 1) == 0);

  bitset_flip(bs);

  bitset_set(bs, 0, true);
  assert(bs->count == 0);
  assert((array[0] & 1) == 0);

  bitset_set(bs, 0, false);
  assert(bs->count == 1);
  assert((array[0] & 1) == 1);

  bitset_delete(bs);
}

void test_bitset_reset() {
  bitset_t *bs = bitset_new(100);
  for (size_t idx = 0; idx < 50; idx = idx + 2) {
    bitset_set(bs, idx, true);
  }
  bitset_flip(bs);

  bitset_reset(bs);

  uint8_t *array = (uint8_t *)bs->array;
  for (size_t i = 0; i < ((100 / 8) + 1); i++) {
    assert(array[i] == 0);
  }
  assert(bs->flip == false);
  assert(bs->count == 0);

  bitset_delete(bs);
}

void test_bitset_flip() {
  bitset_t *bs = bitset_new(100);
  assert(bs->flip == false);

  bitset_flip(bs);
  assert(bs->flip == true);
  bitset_flip(bs);
  assert(bs->flip == false);

  bitset_delete(bs);
}

void test_bitset_to_string() {
  bitset_t *bs = bitset_new(32);
  bitset_set(bs, 9, true);
  char *bs_string = bitset_to_string(bs);
  for (size_t i = 0; i < bitset_size(bs); i++) {
    if (i != 9) {
      assert(bs_string[i] == '0');
    } else {
      assert(bs_string[i] == '1');
    }
  }

  bitset_flip(bs);
  char *bs_string_flip = bitset_to_string(bs);
  for (size_t i = 0; i < bitset_size(bs); i++) {
    if (i != 9) {
      assert(bs_string_flip[i] == '1');
    } else {
      assert(bs_string_flip[i] == '0');
    }
  }
  bitset_delete(bs);
  free(bs_string_flip);
  free(bs_string);
}

void test_bitset_read_write() {
  // WRITE
  bitset_t *bsw = bitset_new(32);
  bitset_set(bsw, 9, true);
  bitset_set(bsw, 31, true);
  bitset_flip(bsw);
  bitset_write(bsw, "./bitset.bs");
  // READ
  bitset_t *bsr = bitset_read("./bitset.bs");
  assert(bsr->flip == bsw->flip);
  assert(bsr->size == bsw->size);
  assert(bsr->count == bsw->count);
  assert(memcmp(bsw->array, bsr->array, __bitset_size(bsw->size)) == 0);
  bitset_delete(bsw);
  bitset_delete(bsr);
}

int main() {
  test_bitset_new();
  test_bitset_delete();
  test_bitset_count();
  test_bitset_size();
  test_bitset_test();
  test_bitset_any();
  test_bitset_none();
  test_bitset_all();
  test_bitset_set();
  test_bitset_reset();
  test_bitset_flip();
  test_bitset_to_string();
  test_bitset_read_write();
  return EXIT_SUCCESS;
}
