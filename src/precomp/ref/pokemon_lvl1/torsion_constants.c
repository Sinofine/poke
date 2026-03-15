#include <stddef.h>
#include <stdint.h>
#include <torsion_constants.h>
#if 0
#elif 8*DIGIT_LEN == 16
const uint64_t TORSION_PLUS_EVEN_POWER = 0x80;
const uint64_t TORSION_ODD_PRIMES[2] = {0x3, 0x13};
const uint64_t TORSION_ODD_POWERS[2] = {0x18, 0x1};
const uint64_t TORSION_PLUS_ODD_PRIMES[2] = {0x3, 0x13};
const size_t TORSION_PLUS_ODD_POWERS[2] = {0x18, 0x1};
const size_t DEGREE_COMMITMENT_POWERS[2] = {0x18, 0x1};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 19, ._mp_d = (mp_limb_t[]) {0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0x2fff,0x1b8b,0x1682,0x4e}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0xb8b3,0x6821,0x4e1}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[2] = {{{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0xb8e1,0xc21c,0x41}}}, {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x13}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0xb8b3,0x6821,0x4e1}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 9, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 17, ._mp_d = (mp_limb_t[]) {0x7c89,0xf8db,0x65,0x786c,0x5dc0,0x95d0,0xc941,0x5cc1,0x7cba,0xa798,0x8182,0xd6fd,0x4d09,0x278b,0xf77a,0xb2b6,0x1}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 25, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7c89,0xf8db,0x65,0x786c,0x5dc0,0x95d0,0xc941,0x5cc1,0x7cba,0xa798,0x8182,0xd6fd,0x4d09,0x278b,0xf77a,0xb2b6,0x1}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0xb8b3,0x6821,0x4e1}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0xb8b3,0x6821,0x4e1}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 16, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1000}}};
#elif 8*DIGIT_LEN == 32
const uint64_t TORSION_PLUS_EVEN_POWER = 0x80;
const uint64_t TORSION_ODD_PRIMES[2] = {0x3, 0x13};
const uint64_t TORSION_ODD_POWERS[2] = {0x18, 0x1};
const uint64_t TORSION_PLUS_ODD_PRIMES[2] = {0x3, 0x13};
const size_t TORSION_PLUS_ODD_POWERS[2] = {0x18, 0x1};
const size_t DEGREE_COMMITMENT_POWERS[2] = {0x18, 0x1};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 10, ._mp_d = (mp_limb_t[]) {0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x2fffffff,0x16821b8b,0x4e}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0x6821b8b3,0x4e1}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[2] = {{{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xc21cb8e1,0x41}}}, {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x13}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0x6821b8b3,0x4e1}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 9, ._mp_d = (mp_limb_t[]) {0xf8db7c89,0x786c0065,0x95d05dc0,0x5cc1c941,0xa7987cba,0xd6fd8182,0x278b4d09,0xb2b6f77a,0x1}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 13, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0xf8db7c89,0x786c0065,0x95d05dc0,0x5cc1c941,0xa7987cba,0xd6fd8182,0x278b4d09,0xb2b6f77a,0x1}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0x6821b8b3,0x4e1}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0x6821b8b3,0x4e1}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 8, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x10000000}}};
#elif 8*DIGIT_LEN == 64
const uint64_t TORSION_PLUS_EVEN_POWER = 0x80;
const uint64_t TORSION_ODD_PRIMES[2] = {0x3, 0x13};
const uint64_t TORSION_ODD_POWERS[2] = {0x18, 0x1};
const uint64_t TORSION_PLUS_ODD_PRIMES[2] = {0x3, 0x13};
const size_t TORSION_PLUS_ODD_POWERS[2] = {0x18, 0x1};
const size_t DEGREE_COMMITMENT_POWERS[2] = {0x18, 0x1};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0x2fffffffffffffff,0x4e16821b8b}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x4e16821b8b3}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[2] = {{{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x41c21cb8e1}}}, {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x13}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x4e16821b8b3}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0x786c0065f8db7c89,0x5cc1c94195d05dc0,0xd6fd8182a7987cba,0xb2b6f77a278b4d09,0x1}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 7, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x786c0065f8db7c89,0x5cc1c94195d05dc0,0xd6fd8182a7987cba,0xb2b6f77a278b4d09,0x1}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x4e16821b8b3}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x4e16821b8b3}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 4, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x1000000000000000}}};
#endif
