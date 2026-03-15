#include <stddef.h>
#include <stdint.h>
#include <torsion_constants.h>
#if 0
#elif 8*DIGIT_LEN == 16
const uint64_t TORSION_PLUS_EVEN_POWER = 0xc0;
const uint64_t TORSION_ODD_PRIMES[1] = {0x3};
const uint64_t TORSION_ODD_POWERS[1] = {0x29};
const uint64_t TORSION_PLUS_ODD_PRIMES[1] = {0x3};
const size_t TORSION_PLUS_ODD_POWERS[1] = {0x29};
const size_t DEGREE_COMMITMENT_POWERS[1] = {0x29};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 29, ._mp_d = (mp_limb_t[]) {0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xffff,0xb862,0x7b5f,0x1cf6,0xfa2a,0x1}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xb863,0x7b5f,0x1cf6,0xfa2a,0x1}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[1] = {{{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xb863,0x7b5f,0x1cf6,0xfa2a,0x1}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xb863,0x7b5f,0x1cf6,0xfa2a,0x1}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 13, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 25, ._mp_d = (mp_limb_t[]) {0x385b,0xe2d7,0xc679,0xba02,0xe1dd,0x7b19,0x516,0x6134,0xb295,0x48d9,0xb00a,0xe38d,0xaa0d,0xd9dc,0x1546,0xb466,0x343,0xfbc7,0xf021,0xfc27,0x73d,0xf2fe,0x879d,0x367b,0x2}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 37, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x385b,0xe2d7,0xc679,0xba02,0xe1dd,0x7b19,0x516,0x6134,0xb295,0x48d9,0xb00a,0xe38d,0xaa0d,0xd9dc,0x1546,0xb466,0x343,0xfbc7,0xf021,0xfc27,0x73d,0xf2fe,0x879d,0x367b,0x2}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xb863,0x7b5f,0x1cf6,0xfa2a,0x1}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 5, ._mp_d = (mp_limb_t[]) {0xb863,0x7b5f,0x1cf6,0xfa2a,0x1}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 25, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
#elif 8*DIGIT_LEN == 32
const uint64_t TORSION_PLUS_EVEN_POWER = 0xc0;
const uint64_t TORSION_ODD_PRIMES[1] = {0x3};
const uint64_t TORSION_ODD_POWERS[1] = {0x29};
const uint64_t TORSION_PLUS_ODD_PRIMES[1] = {0x3};
const size_t TORSION_PLUS_ODD_POWERS[1] = {0x29};
const size_t DEGREE_COMMITMENT_POWERS[1] = {0x29};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 15, ._mp_d = (mp_limb_t[]) {0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0xffffffff,0x7b5fb862,0xfa2a1cf6,0x1}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x7b5fb863,0xfa2a1cf6,0x1}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[1] = {{{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x7b5fb863,0xfa2a1cf6,0x1}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x7b5fb863,0xfa2a1cf6,0x1}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 7, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 13, ._mp_d = (mp_limb_t[]) {0xe2d7385b,0xba02c679,0x7b19e1dd,0x61340516,0x48d9b295,0xe38db00a,0xd9dcaa0d,0xb4661546,0xfbc70343,0xfc27f021,0xf2fe073d,0x367b879d,0x2}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 19, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0xe2d7385b,0xba02c679,0x7b19e1dd,0x61340516,0x48d9b295,0xe38db00a,0xd9dcaa0d,0xb4661546,0xfbc70343,0xfc27f021,0xf2fe073d,0x367b879d,0x2}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x7b5fb863,0xfa2a1cf6,0x1}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 3, ._mp_d = (mp_limb_t[]) {0x7b5fb863,0xfa2a1cf6,0x1}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 13, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
#elif 8*DIGIT_LEN == 64
const uint64_t TORSION_PLUS_EVEN_POWER = 0xc0;
const uint64_t TORSION_ODD_PRIMES[1] = {0x3};
const uint64_t TORSION_ODD_POWERS[1] = {0x29};
const uint64_t TORSION_PLUS_ODD_PRIMES[1] = {0x3};
const size_t TORSION_PLUS_ODD_POWERS[1] = {0x29};
const size_t DEGREE_COMMITMENT_POWERS[1] = {0x29};
const ibz_t CHARACTERISTIC = {{._mp_alloc = 0, ._mp_size = 8, ._mp_d = (mp_limb_t[]) {0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xffffffffffffffff,0xfa2a1cf67b5fb862,0x1}}};
const ibz_t TORSION_ODD = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xfa2a1cf67b5fb863,0x1}}};
const ibz_t TORSION_ODD_PRIMEPOWERS[1] = {{{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xfa2a1cf67b5fb863,0x1}}}};
const ibz_t TORSION_ODD_PLUS = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xfa2a1cf67b5fb863,0x1}}};
const ibz_t TORSION_ODD_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t TORSION_PLUS_2POWER = {{._mp_alloc = 0, ._mp_size = 4, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x1}}};
const ibz_t TORSION_PLUS_3POWER = {{._mp_alloc = 0, ._mp_size = 7, ._mp_d = (mp_limb_t[]) {0xba02c679e2d7385b,0x613405167b19e1dd,0xe38db00a48d9b295,0xb4661546d9dcaa0d,0xfc27f021fbc70343,0x367b879df2fe073d,0x2}}};
const ibz_t TORSION_PLUS_23POWER = {{._mp_alloc = 0, ._mp_size = 10, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0xba02c679e2d7385b,0x613405167b19e1dd,0xe38db00a48d9b295,0xb4661546d9dcaa0d,0xfc27f021fbc70343,0x367b879df2fe073d,0x2}}};
const ibz_t DEGREE_COMMITMENT = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xfa2a1cf67b5fb863,0x1}}};
const ibz_t DEGREE_COMMITMENT_PLUS = {{._mp_alloc = 0, ._mp_size = 2, ._mp_d = (mp_limb_t[]) {0xfa2a1cf67b5fb863,0x1}}};
const ibz_t DEGREE_COMMITMENT_MINUS = {{._mp_alloc = 0, ._mp_size = 1, ._mp_d = (mp_limb_t[]) {0x1}}};
const ibz_t DEGREE_CHALLENGE = {{._mp_alloc = 0, ._mp_size = 7, ._mp_d = (mp_limb_t[]) {0x0,0x0,0x0,0x0,0x0,0x0,0x1}}};
#endif
