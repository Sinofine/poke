#include <ec.h>

/** @brief POKEmon secret key
 *
 * @typedef pokemon_sk_t
 *
 * @struct pokemon_sk_t
 *
 * An elliptic curve in projective Montgomery form
 */
typedef struct pokemon_sk_t {
  digit_t deg[NWORDS_ORDER];
  digit_t alpha[NWORDS_ORDER];
  digit_t beta[NWORDS_ORDER];
  digit_t tempx[NWORDS_ORDER];
  digit_t tempy[NWORDS_ORDER];
} pokemon_sk_t;

/** @brief POKEmon public key
 *
 * @typedef pokemon_pk_t
 *
 * @struct pokemon_pk_t
 *
 * An elliptic curve in projective Montgomery form
 */
typedef struct pokemon_pk_t {
  ec_curve_t EA;
  ec_basis_t PQA;
  ec_basis_t RSA;
} pokemon_pk_t;

/** @brief POKEmon ciphertext
 *
 * @typedef pokemon_ct_t
 *
 * @struct pokemon_ct_t
 *
 * An elliptic curve in projective Montgomery form
 */
typedef struct pokemon_ct_t {
  ec_curve_t EB;
  ec_curve_t EAB;
  ec_basis_t RSB;
  ec_point_t PB;
  ec_point_t PAB;
  uint8_t ct[32];
} pokemon_ct_t;

int decaps(unsigned char *key, pokemon_ct_t *ct, const pokemon_pk_t *pk,
           const pokemon_sk_t *sk, unsigned char *dummy_m);
int encaps(unsigned char *key, pokemon_ct_t *ct, const pokemon_pk_t *pk);
int ct_encode(unsigned char *encoded_ct, pokemon_ct_t *ct);
int ct_decode(pokemon_ct_t *ct, const unsigned char *encoded_ct);
int keygen(pokemon_sk_t *sk, pokemon_pk_t *pk);
int encrypt(pokemon_ct_t *ct, const pokemon_pk_t *pk, const unsigned char *m,
            const size_t m_len, const unsigned char *seed,
            const size_t seed_len);
int decrypt(unsigned char *m, size_t *m_len, const pokemon_ct_t *ct,
            const pokemon_sk_t *sk);