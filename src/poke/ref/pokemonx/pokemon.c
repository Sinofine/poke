#include "pokemon.h"
#include <biextension.h>
#include <ec.h>
#include <endomorphism_action.h>
#include <fips202.h>
#include <gmp.h>
#include <hd.h>
#include <id2iso.h>
#include <intbig.h>
#include <klpt.h>
#include <quaternion.h>
#include <rng.h>
#include <stdio.h>
#include <torsion_constants.h>

int ibz_random_matrix(ibz_mat_2x2_t mat22, const ibz_t *modulus,
                      shake256ctx *state) {
  ibz_t gcd, det;
  ibz_init(&gcd);
  ibz_init(&det);
  while (1) {
    if (state != NULL) {
      ibz_rand_interval_with_state(&mat22[0][0], &ibz_const_zero, modulus,
                                   state);
      ibz_rand_interval_with_state(&mat22[0][1], &ibz_const_zero, modulus,
                                   state);
      ibz_rand_interval_with_state(&mat22[1][0], &ibz_const_zero, modulus,
                                   state);
      ibz_rand_interval_with_state(&mat22[1][1], &ibz_const_zero, modulus,
                                   state);
    } else {
      ibz_rand_interval(&mat22[0][0], &ibz_const_zero, modulus);
      ibz_rand_interval(&mat22[0][1], &ibz_const_zero, modulus);
      ibz_rand_interval(&mat22[1][0], &ibz_const_zero, modulus);
      ibz_rand_interval(&mat22[1][1], &ibz_const_zero, modulus);
    }
    ibz_mul(&det, &mat22[0][0], &mat22[1][1]);
    ibz_mul(&gcd, &mat22[0][1], &mat22[1][0]);
    ibz_sub(&det, &det, &gcd);
    ibz_gcd(&gcd, &det, modulus);
    if (ibz_is_one(&gcd)) {
      break;
    }
  }
  ibz_finalize(&gcd);
  ibz_finalize(&det);
  return 1;
}

int ibz_random_unit(ibz_t *q, const ibz_t *modulus, shake256ctx *state) {
  ibz_t gcd;
  ibz_init(&gcd);
  while (1) {
    if (state != NULL) {
      ibz_rand_interval_with_state(q, &ibz_const_zero, modulus, state);
    } else {
      ibz_rand_interval(q, &ibz_const_zero, modulus);
    }
    ibz_gcd(&gcd, q, modulus);
    if (ibz_is_one(&gcd)) {
      break;
    }
  }
  ibz_finalize(&gcd);
  return 1;
}

int keygen(pokemon_sk_t *sk, pokemon_pk_t *pk) {
  ibz_t q, alpha, beta, rhs, deg;
  ibz_t A, two_to_a, tempx, tempy, Adiv4;
  ec_point_t pointT;

  ibz_init(&q);
  ibz_init(&alpha);
  ibz_init(&beta);
  ibz_init(&rhs);
  ibz_init(&deg);
  ibz_init(&A);
  ibz_init(&Adiv4);
  ibz_init(&two_to_a);
  ibz_init(&tempx);
  ibz_init(&tempy);

  ibz_copy(&A, &TORSION_PLUS_2POWER);
  gmp_printf("A: %Zd\n", A);
  ibz_div_2exp(&two_to_a, &A, TORSION_PLUS_EVEN_POWER / 2);

  for (int i = 0; i < 10000; i++) {
    ibz_t x_bound;
    ibz_init(&x_bound);
    ibz_sqrt(&x_bound, &two_to_a);
    ibz_add(&x_bound, &x_bound, &ibz_const_one);

    ibz_rand_interval(&tempx, &ibz_const_one, &x_bound);
    ibz_div_2exp(&tempx, &tempx, 1);
    ibz_mul_2exp(&tempx, &tempx, 1);

    ibz_rand_interval(&tempy, &ibz_const_one, &x_bound);
    ibz_div_2exp(&tempy, &tempy, 1);
    ibz_mul_2exp(&tempy, &tempy, 1);
    ibz_add(&tempy, &tempy, &ibz_const_one);

    ibz_mul(&deg, &tempx, &tempx);
    ibz_mul(&rhs, &tempy, &tempy);
    ibz_add(&deg, &deg, &rhs);
    ibz_sub(&q, &two_to_a, &deg);

    if (ibz_cmp(&q, &ibz_const_zero) > 0 &&
        ibz_divides(&q, &ibz_const_three) == 0) {
      ibz_finalize(&x_bound);
      break;
    }
    ibz_finalize(&x_bound);
  }
  gmp_printf("two_to_a: %Zd, A: %Zd, q: %Zd, 3^b: %Zd\n", two_to_a, A, q, TORSION_PLUS_3POWER);
  // A = 2^2a, TORSION_PLUS_3POWER = 3^b
  ibz_div_2exp(&Adiv4, &A, 2);
  ibz_sub(&deg, &Adiv4, &q);
  ibz_mul(&rhs, &deg, &q);
  ibz_mul(&rhs, &rhs, &TORSION_PLUS_3POWER);

  ibz_random_unit(&alpha, &A, NULL);
  ibz_random_unit(&beta, &TORSION_PLUS_3POWER, NULL);

  ibz_to_digits(sk->deg, &q);
  ibz_to_digits(sk->alpha, &alpha);
  ibz_to_digits(sk->beta, &beta);
  ibz_to_digits(sk->tempx, &tempx);
  ibz_to_digits(sk->tempy, &tempy);

  ec_curve_t curve = CURVE_E0;
  quat_alg_elem_t tau;
  quat_alg_elem_init(&tau);
  represent_integer(&tau, &rhs, &QUATALG_PINFTY);

  ec_basis_t E0_two, E0_three;
  copy_point(&E0_two.P, &BASIS_EVEN.P);
  copy_point(&E0_two.Q, &BASIS_EVEN.Q);
  copy_point(&E0_two.PmQ, &BASIS_EVEN.PmQ);
  copy_point(&E0_three.P, &BASIS_THREE.P);
  copy_point(&E0_three.Q, &BASIS_THREE.Q);
  copy_point(&E0_three.PmQ, &BASIS_THREE.PmQ);

  endomorphism_application_three_basis(&E0_three, &curve, &tau,
                                       TORSION_PLUS_ODD_POWERS[0]);
  endomorphism_application_even_basis(&E0_two, &curve, &tau,
                                      TORSION_PLUS_EVEN_POWER);
  quat_alg_elem_finalize(&tau);

  ec_isog_odd_t isog;
  isog.curve = curve;
  ibz_t three_m1_order, remainder;
  ibz_init(&three_m1_order);
  ibz_init(&remainder);
  ibz_div(&three_m1_order, &remainder, &TORSION_PLUS_3POWER, &ibz_const_three);
  // test ord P = 3^b
  ec_point_t test_point;
  ec_mul_ibz(&test_point, &curve, &three_m1_order, &E0_three.P);
  if (ec_is_zero(&test_point)) {
    copy_point(&isog.ker_plus, &E0_three.Q);
  } else {
    copy_point(&isog.ker_plus, &E0_three.P);
  }
  ec_set_zero(&isog.ker_minus);
  isog.degree[0] = TORSION_PLUS_ODD_POWERS[0];
  for(int i = 1; i < P_LEN + M_LEN; i++) {
        isog.degree[i] = 0;
    }

  ec_curve_t E1;
  ec_eval_three(&E1, &isog, (ec_point_t *)&E0_two, 3);

  theta_couple_curve_t E01;
  theta_couple_point_t T1, T2, T1m2;
  theta_chain_t hd_isog;
  E01.E1 = curve;
  E01.E2 = E1;

  copy_point(&T1.P1, &BASIS_EVEN.P);
  copy_point(&T2.P1, &BASIS_EVEN.Q);
  copy_point(&T1m2.P1, &BASIS_EVEN.PmQ);
  ec_mul_ibz(&T1.P1, &curve, &q, &T1.P1);
  ec_mul_ibz(&T2.P1, &curve, &q, &T2.P1);
  ec_mul_ibz(&T1m2.P1, &curve, &q, &T1m2.P1);

  ibz_t inverse;
  ibz_init(&inverse);
  ibz_invmod(&inverse, &TORSION_PLUS_3POWER, &TORSION_PLUS_2POWER);
  ec_mul_ibz(&E0_two.P, &E1, &inverse, &E0_two.P);
  ec_mul_ibz(&E0_two.Q, &E1, &inverse, &E0_two.Q);
  ec_mul_ibz(&E0_two.PmQ, &E1, &inverse, &E0_two.PmQ);

  T1.P2 = E0_two.P;
  T2.P2 = E0_two.Q;
  T1m2.P2 = E0_two.PmQ;
  

  theta_chain_comput_strategy(&hd_isog, TORSION_PLUS_EVEN_POWER - 2, &E01, &T1,
                              &T2, &T1m2, strategies[2], 1);

  theta_couple_point_t P0_out, Q0_out, PmQ0_out;
  P0_out.P1 = BASIS_EVEN.P;
  ec_set_zero(&P0_out.P2);
  Q0_out.P1 = BASIS_EVEN.Q;
  ec_set_zero(&Q0_out.P2);
  PmQ0_out.P1 = BASIS_EVEN.PmQ;
  ec_set_zero(&PmQ0_out.P2);
  theta_chain_eval_special_case(&P0_out, &hd_isog, &P0_out, &E01);
  theta_chain_eval_special_case(&Q0_out, &hd_isog, &Q0_out, &E01);
  theta_chain_eval_special_case(&PmQ0_out, &hd_isog, &PmQ0_out, &E01);

  fp2_t e_P0Q0, e_P2Q2, e_P3Q3, target_pairing;

  ec_basis_t B_E2, B_E3;
  B_E2.P = P0_out.P1;
  B_E2.Q = Q0_out.P1;
  B_E2.PmQ = PmQ0_out.P1;
  B_E3.P = P0_out.P2;
  B_E3.Q = Q0_out.P2;
  B_E3.PmQ = PmQ0_out.P2;

  digit_t q_digits[NWORDS_ORDER];
  ibz_to_digits(q_digits, &q);
  point_print("P:", BASIS_EVEN.P);
  point_print("Q:", BASIS_EVEN.Q);
  point_print("PmQ:", BASIS_EVEN.PmQ);
  // weil() normalizes (modifies) its point arguments in-place via to_cubical_i(),
  // so we must copy from the read-only BASIS_EVEN constant into local variables.
  // Also, cubicalDBL requires A24 to be normalized (z=1), so compute it via A24_from_AC.
  ec_point_t basis_P = BASIS_EVEN.P;
  ec_point_t basis_Q = BASIS_EVEN.Q;
  ec_point_t basis_PmQ = BASIS_EVEN.PmQ;
  ec_curve_normalize_A24(&curve);
  weil(&e_P0Q0, TORSION_PLUS_EVEN_POWER, &basis_P, &basis_Q, &basis_PmQ, &curve.A24);
  fp2_pow_vartime(&target_pairing, &e_P0Q0, q_digits, NWORDS_ORDER);
  ec_curve_normalize_A24(&hd_isog.codomain.E1);
  ec_curve_normalize_A24(&hd_isog.codomain.E2);
  weil(&e_P2Q2, TORSION_PLUS_EVEN_POWER, &B_E2.P, &B_E2.Q, &B_E2.PmQ, &hd_isog.codomain.E1.A24);

  int use_E2 = 0;
  if (fp2_is_equal(&e_P2Q2, &target_pairing)) {
    pk->EA = hd_isog.codomain.E1;
    use_E2 = 1;
  } else {
    weil(&e_P3Q3, TORSION_PLUS_EVEN_POWER, &B_E3.P, &B_E3.Q, &B_E3.PmQ, &hd_isog.codomain.E2.A24);
    if (fp2_is_equal(&e_P3Q3, &target_pairing)) {
      pk->EA = hd_isog.codomain.E2;
      use_E2 = 0;
    } else {
      // Finalize all ibz_t variables on failure
      ibz_finalize(&q);
      ibz_finalize(&alpha);
      ibz_finalize(&beta);
      ibz_finalize(&rhs);
      ibz_finalize(&deg);
      ibz_finalize(&A);
      ibz_finalize(&two_to_a);
      ibz_finalize(&tempx);
      ibz_finalize(&tempy);
      ibz_finalize(&three_m1_order);
      ibz_finalize(&remainder);
      ibz_finalize(&inverse);
      return 1;
    }
  }

  jac_point_t P, Q, R, S, T;
  ec_basis_t basis_even_copy = BASIS_EVEN;
  ec_basis_t basis_three_copy = BASIS_THREE;
  lift_basis(&P, &Q, &basis_even_copy, &curve);
  lift_basis(&R, &S, &basis_three_copy, &curve);

  jac_point_t P23x, Q23x, PmQ23x;
  ADD(&P23x, &P, &R, &curve);
  ADD(&Q23x, &Q, &S, &curve);
  jac_neg(&T, &Q23x);
  ADD(&PmQ23x, &P23x, &T, &curve);

  ec_basis_t eval_points;
  jac_to_xz(&eval_points.P, &P23x);
  jac_to_xz(&eval_points.Q, &Q23x);
  jac_to_xz(&eval_points.PmQ, &PmQ23x);

  theta_couple_point_t combined_out;
  ec_basis_t imPQ23x;
  combined_out.P1 = eval_points.P;
  ec_set_zero(&combined_out.P2);
  theta_chain_eval_special_case(&combined_out, &hd_isog, &combined_out, &E01);
  imPQ23x.P = use_E2 ? combined_out.P1 : combined_out.P2;
  combined_out.P1 = eval_points.Q;
  ec_set_zero(&combined_out.P2);
  theta_chain_eval_special_case(&combined_out, &hd_isog, &combined_out, &E01);
  imPQ23x.Q = use_E2 ? combined_out.P1 : combined_out.P2;
  combined_out.P1 = eval_points.PmQ;
  ec_set_zero(&combined_out.P2);
  theta_chain_eval_special_case(&combined_out, &hd_isog, &combined_out, &E01);
  imPQ23x.PmQ = use_E2 ? combined_out.P1 : combined_out.P2;

  ibz_t inv_3b, inv_2a;
  ibz_init(&inv_3b);
  ibz_init(&inv_2a);
  ibz_invmod(&inv_3b, &TORSION_PLUS_3POWER, &TORSION_PLUS_2POWER);
  ibz_invmod(&inv_2a, &TORSION_PLUS_2POWER, &TORSION_PLUS_3POWER);

  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_3POWER, &imPQ23x.P);
  ibz_mul(&rhs, &alpha, &inv_3b);
  ibz_mod(&rhs, &rhs, &A);
  ec_mul_ibz(&pk->PQA.P, &pk->EA, &rhs, &pointT);
  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_3POWER, &imPQ23x.Q);
  ec_mul_ibz(&pk->PQA.Q, &pk->EA, &rhs, &pointT);
  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_3POWER, &imPQ23x.PmQ);
  ec_mul_ibz(&pk->PQA.PmQ, &pk->EA, &rhs, &pointT);

  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_2POWER, &imPQ23x.P);
  ibz_mul(&rhs, &beta, &inv_2a);
  ibz_mod(&rhs, &rhs, &TORSION_PLUS_3POWER);
  ec_mul_ibz(&pk->RSA.P, &pk->EA, &rhs, &pointT);
  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_2POWER, &imPQ23x.Q);
  ec_mul_ibz(&pk->RSA.Q, &pk->EA, &rhs, &pointT);
  ec_mul_ibz(&pointT, &pk->EA, &TORSION_PLUS_2POWER, &imPQ23x.PmQ);
  ec_mul_ibz(&pk->RSA.PmQ, &pk->EA, &rhs, &pointT);

  ibz_finalize(&q);
  ibz_finalize(&alpha);
  ibz_finalize(&beta);
  ibz_finalize(&rhs);
  ibz_finalize(&deg);
  ibz_finalize(&A);
  ibz_finalize(&two_to_a);
  ibz_finalize(&tempx);
  ibz_finalize(&tempy);
  ibz_finalize(&three_m1_order);
  ibz_finalize(&remainder);
  ibz_finalize(&inverse);
  ibz_finalize(&inv_3b);
  ibz_finalize(&inv_2a);
  return 0;
}

int encrypt(pokemon_ct_t *ct, const pokemon_pk_t *pk, const unsigned char *m,
            const size_t m_len, const unsigned char *seed,
            const size_t seed_len) {
  ibz_mat_2x2_t mask_xy;
  ec_isog_even_t psi, psi_prime;
  ibz_t s, gamma, A;
  ec_curve_t EB, EAB;
  ec_basis_t eval_basis_B[2], eval_basis_AB[2];
  shake256ctx state;

  digit_t s_scalar[NWORDS_ORDER] = {0};
  digit_t gamma_scalar[NWORDS_ORDER] = {0};
  digit_t one_scalar[NWORDS_ORDER] = {1};

  ibz_init(&s);
  ibz_init(&gamma);
  ibz_init(&A);
  ibz_mat_2x2_init(&mask_xy);
  ibz_copy(&A, &TORSION_PLUS_2POWER);

  if (seed != NULL) {
    shake256_absorb(&state, seed, seed_len);
    ibz_rand_interval_with_state(&s, &ibz_const_zero, &A, &state);
    ibz_random_unit(&gamma, &A, &state);
    ibz_random_matrix(mask_xy, &TORSION_PLUS_3POWER, &state);
    shake256_ctx_release(&state);
  } else {
    ibz_rand_interval(&s, &ibz_const_zero, &A);
    ibz_random_unit(&gamma, &A, NULL);
    ibz_random_matrix(mask_xy, &TORSION_PLUS_3POWER, NULL);
  }

  ibz_to_digits(s_scalar, &s);
  ibz_to_digits(gamma_scalar, &gamma);

  psi.curve = CURVE_E0;
  psi.length = TORSION_PLUS_EVEN_POWER;
  ec_biscalar_mul_bounded(&psi.kernel, &psi.curve, one_scalar, s_scalar,
                          (ec_basis_t *)&BASIS_EVEN, TORSION_2POWER_BYTES * 8);

  eval_basis_B[0] = BASIS_EVEN;
  eval_basis_B[1] = BASIS_THREE;
  ec_eval_even(&EB, &psi, (ec_point_t *)eval_basis_B, 6);
  ct->EB = EB;

  psi_prime.curve = pk->EA;
  psi_prime.length = TORSION_PLUS_EVEN_POWER;
  ec_biscalar_mul_bounded(&psi_prime.kernel, &psi_prime.curve, one_scalar,
                          s_scalar, &pk->PQA, TORSION_2POWER_BYTES * 8);

  eval_basis_AB[0] = pk->PQA;
  eval_basis_AB[1] = pk->RSA;
  ec_eval_even(&EAB, &psi_prime, (ec_point_t *)eval_basis_AB, 6);
  ct->EAB = EAB;

  ec_mul_ibz(&ct->PB, &EB, &gamma, &eval_basis_B[0].P);
  ec_mul_ibz(&ct->PAB, &EAB, &gamma, &eval_basis_AB[0].P);

  digit_t d1[NWORDS_ORDER], d2[NWORDS_ORDER], d3[NWORDS_ORDER],
      d4[NWORDS_ORDER];
  ibz_to_digits(d1, &mask_xy[0][0]);
  ibz_to_digits(d2, &mask_xy[0][1]);
  ibz_to_digits(d3, &mask_xy[1][0]);
  ibz_to_digits(d4, &mask_xy[1][1]);

  ec_biscalar_mul_bounded(&ct->RSB.P, &EB, d1, d2,
                          (ec_basis_t *)&eval_basis_B[1],
                          TORSION_3POWER_BYTES * 8);
  ec_biscalar_mul_bounded(&ct->RSB.Q, &EB, d3, d4,
                          (ec_basis_t *)&eval_basis_B[1],
                          TORSION_3POWER_BYTES * 8);
  xADD(&ct->RSB.PmQ, &ct->RSB.P, &ct->RSB.Q, &ct->RSB.PmQ);

  ec_basis_t RS_AB;
  ec_biscalar_mul_bounded(&RS_AB.P, &EAB, d1, d2, &eval_basis_AB[1],
                          TORSION_3POWER_BYTES * 8);
  ec_biscalar_mul_bounded(&RS_AB.Q, &EAB, d3, d4, &eval_basis_AB[1],
                          TORSION_3POWER_BYTES * 8);

  unsigned char hash_input[4 * NWORDS_FIELD * RADIX / 8] = {0};
  unsigned char hash_output[32] = {0};
  ec_normalize_point(&RS_AB.P);
  ec_normalize_point(&RS_AB.Q);
  memcpy(hash_input, &RS_AB.P.x.re[0], NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + NWORDS_FIELD * RADIX / 8, &RS_AB.P.x.im[0],
         NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + 2 * NWORDS_FIELD * RADIX / 8, &RS_AB.Q.x.re[0],
         NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + 3 * NWORDS_FIELD * RADIX / 8, &RS_AB.Q.x.im[0],
         NWORDS_FIELD * RADIX / 8);

  SHAKE256(hash_output, sizeof(hash_output), hash_input, sizeof(hash_input));
  for (size_t i = 0; i < 32; i++) {
    ct->ct[i] = m[i] ^ hash_output[i];
  }

  ibz_finalize(&s);
  ibz_finalize(&gamma);
  ibz_finalize(&A);
  ibz_mat_2x2_finalize(&mask_xy);
  return 1;
}

int decrypt(unsigned char *m, size_t *m_len, const pokemon_ct_t *ct,
            const pokemon_sk_t *sk) {
  unsigned char hash_input[4 * NWORDS_FIELD * RADIX / 8] = {0};
  unsigned char hash_output[32] = {0};
  ec_basis_t RS_AB1;
  ibz_t alpha_inv, beta, q, A, tempx, tempy;

  ibz_init(&alpha_inv);
  ibz_init(&beta);
  ibz_init(&q);
  ibz_init(&A);
  ibz_init(&tempx);
  ibz_init(&tempy);

  ibz_copy_digits(&q, sk->deg, NWORDS_ORDER);
  ibz_copy_digits(&alpha_inv, sk->alpha, NWORDS_ORDER);
  ibz_copy_digits(&beta, sk->beta, NWORDS_ORDER);
  ibz_copy_digits(&tempx, sk->tempx, NWORDS_ORDER);
  ibz_copy_digits(&tempy, sk->tempy, NWORDS_ORDER);
  ibz_copy(&A, &TORSION_PLUS_2POWER);
  ibz_invmod(&alpha_inv, &alpha_inv, &A);

  ec_point_t P_AB_prime;
  ec_mul_ibz(&P_AB_prime, &ct->EAB, &alpha_inv, &ct->PAB);

  printf(
      "HINT: one_point (radical dim 4 isogeny) should be implemented here\n");
  ec_mul_ibz(&RS_AB1.P, &ct->EAB, &beta, &ct->RSB.P); // Placeholder
  ec_mul_ibz(&RS_AB1.Q, &ct->EAB, &beta, &ct->RSB.Q); // Placeholder

  ec_normalize_point(&RS_AB1.P);
  ec_normalize_point(&RS_AB1.Q);
  memcpy(hash_input, &RS_AB1.P.x.re[0], NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + NWORDS_FIELD * RADIX / 8, &RS_AB1.P.x.im[0],
         NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + 2 * NWORDS_FIELD * RADIX / 8, &RS_AB1.Q.x.re[0],
         NWORDS_FIELD * RADIX / 8);
  memcpy(hash_input + 3 * NWORDS_FIELD * RADIX / 8, &RS_AB1.Q.x.im[0],
         NWORDS_FIELD * RADIX / 8);

  SHAKE256(hash_output, sizeof(hash_output), hash_input, sizeof(hash_input));
  for (size_t i = 0; i < 32; i++) {
    m[i] = ct->ct[i] ^ hash_output[i];
  }
  *m_len = 32;

  ibz_finalize(&alpha_inv);
  ibz_finalize(&beta);
  ibz_finalize(&q);
  ibz_finalize(&A);
  ibz_finalize(&tempx);
  ibz_finalize(&tempy);
  return 1;
}

int check_ct(const pokemon_ct_t *ct, const pokemon_pk_t *pk,
             const unsigned char *seed, const size_t seed_len) {
  ec_isog_even_t isogB;
  ibz_t s, A;
  ec_curve_t EB;
  shake256ctx state;
  digit_t s_scalar[NWORDS_ORDER] = {0};
  digit_t one_scalar[NWORDS_ORDER] = {1};

  ibz_init(&s);
  ibz_init(&A);
  ibz_copy(&A, &TORSION_PLUS_2POWER);

  if (seed != NULL) {
    shake256_absorb(&state, seed, seed_len);
    ibz_rand_interval_with_state(&s, &ibz_const_zero, &A, &state);
    shake256_ctx_release(&state);
  } else {
    return 0;
  }
  ibz_to_digits(s_scalar, &s);

  isogB.curve = CURVE_E0;
  isogB.length = TORSION_PLUS_EVEN_POWER;
  ec_biscalar_mul_bounded(&isogB.kernel, &isogB.curve, one_scalar, s_scalar,
                          (ec_basis_t *)&BASIS_EVEN, TORSION_2POWER_BYTES * 8);

  ec_eval_even(&EB, &isogB, NULL, 0);

  fp2_t j1, j2;
  ec_j_inv(&j1, &EB);
  ec_j_inv(&j2, &ct->EB);

  ibz_finalize(&s);
  ibz_finalize(&A);
  return (fp2_is_equal(&j1, &j2) != 0);
}

const unsigned char G_hash_str[9] = "encrypt_";
const size_t G_hash_str_len = 8;

int ct_encode(unsigned char *encoded_ct, pokemon_ct_t *ct) {
  int offset = 0;
  fp2_encode(encoded_ct + offset, &ct->EB.A);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->EAB.A);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->RSB.P.x);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->RSB.Q.x);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->RSB.PmQ.x);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->PB.x);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_encode(encoded_ct + offset, &ct->PAB.x);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  memcpy(encoded_ct + offset, ct->ct, 32);
  return 1;
}

int ct_decode(pokemon_ct_t *ct, const unsigned char *encoded_ct) {
  int offset = 0;
  fp2_decode(&ct->EB.A, encoded_ct + offset);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->EAB.A, encoded_ct + offset);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->RSB.P.x, encoded_ct + offset);
  fp2_set_one(&ct->RSB.P.z);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->RSB.Q.x, encoded_ct + offset);
  fp2_set_one(&ct->RSB.Q.z);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->RSB.PmQ.x, encoded_ct + offset);
  fp2_set_one(&ct->RSB.PmQ.z);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->PB.x, encoded_ct + offset);
  fp2_set_one(&ct->PB.z);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  fp2_decode(&ct->PAB.x, encoded_ct + offset);
  fp2_set_one(&ct->PAB.z);
  offset += 2 * NWORDS_FIELD * RADIX / 8;
  memcpy(ct->ct, encoded_ct + offset, 32);
  return 1;
}

int encaps(unsigned char *key, pokemon_ct_t *ct, const pokemon_pk_t *pk) {
  unsigned char m[32];
  unsigned char tt[32 + G_hash_str_len];
  unsigned char gm[32];
  size_t encoded_ct_len = 32 + 7 * (2 * NWORDS_FIELD * RADIX / 8) + 32;
  unsigned char *encoded_ct = malloc(encoded_ct_len);

  randombytes(m, 32);
  memcpy(tt, G_hash_str, G_hash_str_len);
  memcpy(tt + G_hash_str_len, m, 32);
  SHAKE256(gm, 32, tt, 32 + G_hash_str_len);
  encrypt(ct, pk, m, 32, gm, 32);
  memcpy(encoded_ct, m, 32);
  ct_encode(encoded_ct + 32, ct);
  SHAKE256(key, 32, encoded_ct, encoded_ct_len);
  free(encoded_ct);
  return 1;
}

int decaps(unsigned char *key, pokemon_ct_t *ct, const pokemon_pk_t *pk,
           const pokemon_sk_t *sk, unsigned char *dummy_m) {
  unsigned char m[32];
  unsigned char tt[32 + G_hash_str_len];
  unsigned char gm[32];
  size_t encoded_ct_len = 32 + 7 * (2 * NWORDS_FIELD * RADIX / 8) + 32;
  unsigned char *ct_bytes = malloc(encoded_ct_len);
  size_t m_len;

  decrypt(m, &m_len, ct, sk);
  memcpy(tt, G_hash_str, G_hash_str_len);
  memcpy(tt + G_hash_str_len, m, 32);
  SHAKE256(gm, 32, tt, 32 + G_hash_str_len);
  if (check_ct(ct, pk, gm, 32) != 1) {
    memcpy(ct_bytes, dummy_m, 32);
  } else {
    memcpy(ct_bytes, m, 32);
  }
  ct_encode(ct_bytes + 32, ct);
  SHAKE256(key, 32, ct_bytes, encoded_ct_len);
  free(ct_bytes);
  return 1;
}
