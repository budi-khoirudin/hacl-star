/* This file was auto-generated by KreMLin! */

#include "FStar.h"

static uint64_t FStar_UInt128_constant_time_carry(uint64_t a, uint64_t b)
{
  return (a ^ ((a ^ b) | ((a - b) ^ b))) >> (uint32_t)63U;
}

static uint64_t FStar_UInt128_carry(uint64_t a, uint64_t b)
{
  return FStar_UInt128_constant_time_carry(a, b);
}

FStar_UInt128_uint128 FStar_UInt128_add(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = a.low + b.low,
        .high = a.high + b.high + FStar_UInt128_carry(a.low + b.low, b.low)
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_add_mod(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = a.low + b.low,
        .high = a.high + b.high + FStar_UInt128_carry(a.low + b.low, b.low)
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_sub(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = a.low - b.low,
        .high = a.high - b.high - FStar_UInt128_carry(a.low, a.low - b.low)
      }
    );
}

static FStar_UInt128_uint128
FStar_UInt128_sub_mod_impl(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = a.low - b.low,
        .high = a.high - b.high - FStar_UInt128_carry(a.low, a.low - b.low)
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_sub_mod(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return FStar_UInt128_sub_mod_impl(a, b);
}

FStar_UInt128_uint128 FStar_UInt128_logand(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return ((FStar_UInt128_uint128){ .low = a.low & b.low, .high = a.high & b.high });
}

FStar_UInt128_uint128 FStar_UInt128_logxor(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return ((FStar_UInt128_uint128){ .low = a.low ^ b.low, .high = a.high ^ b.high });
}

FStar_UInt128_uint128 FStar_UInt128_logor(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return ((FStar_UInt128_uint128){ .low = a.low | b.low, .high = a.high | b.high });
}

FStar_UInt128_uint128 FStar_UInt128_lognot(FStar_UInt128_uint128 a)
{
  return ((FStar_UInt128_uint128){ .low = ~a.low, .high = ~a.high });
}

static uint32_t FStar_UInt128_u32_64 = (uint32_t)64U;

static uint64_t FStar_UInt128_add_u64_shift_left(uint64_t hi, uint64_t lo, uint32_t s)
{
  return (hi << s) + (lo >> (FStar_UInt128_u32_64 - s));
}

static uint64_t FStar_UInt128_add_u64_shift_left_respec(uint64_t hi, uint64_t lo, uint32_t s)
{
  return FStar_UInt128_add_u64_shift_left(hi, lo, s);
}

static FStar_UInt128_uint128
FStar_UInt128_shift_left_small(FStar_UInt128_uint128 a, uint32_t s)
{
  if (s == (uint32_t)0U)
    return a;
  else
    return
      (
        (FStar_UInt128_uint128){
          .low = a.low << s,
          .high = FStar_UInt128_add_u64_shift_left_respec(a.high, a.low, s)
        }
      );
}

static FStar_UInt128_uint128
FStar_UInt128_shift_left_large(FStar_UInt128_uint128 a, uint32_t s)
{
  return
    ((FStar_UInt128_uint128){ .low = (uint64_t)0U, .high = a.low << (s - FStar_UInt128_u32_64) });
}

FStar_UInt128_uint128 FStar_UInt128_shift_left(FStar_UInt128_uint128 a, uint32_t s)
{
  if (s < FStar_UInt128_u32_64)
    return FStar_UInt128_shift_left_small(a, s);
  else
    return FStar_UInt128_shift_left_large(a, s);
}

static uint64_t FStar_UInt128_add_u64_shift_right(uint64_t hi, uint64_t lo, uint32_t s)
{
  return (lo >> s) + (hi << (FStar_UInt128_u32_64 - s));
}

static uint64_t FStar_UInt128_add_u64_shift_right_respec(uint64_t hi, uint64_t lo, uint32_t s)
{
  return FStar_UInt128_add_u64_shift_right(hi, lo, s);
}

static FStar_UInt128_uint128
FStar_UInt128_shift_right_small(FStar_UInt128_uint128 a, uint32_t s)
{
  if (s == (uint32_t)0U)
    return a;
  else
    return
      (
        (FStar_UInt128_uint128){
          .low = FStar_UInt128_add_u64_shift_right_respec(a.high, a.low, s),
          .high = a.high >> s
        }
      );
}

static FStar_UInt128_uint128
FStar_UInt128_shift_right_large(FStar_UInt128_uint128 a, uint32_t s)
{
  return
    ((FStar_UInt128_uint128){ .low = a.high >> (s - FStar_UInt128_u32_64), .high = (uint64_t)0U });
}

FStar_UInt128_uint128 FStar_UInt128_shift_right(FStar_UInt128_uint128 a, uint32_t s)
{
  if (s < FStar_UInt128_u32_64)
    return FStar_UInt128_shift_right_small(a, s);
  else
    return FStar_UInt128_shift_right_large(a, s);
}

FStar_UInt128_uint128 FStar_UInt128_eq_mask(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = FStar_UInt64_eq_mask(a.low, b.low) & FStar_UInt64_eq_mask(a.high, b.high),
        .high = FStar_UInt64_eq_mask(a.low, b.low) & FStar_UInt64_eq_mask(a.high, b.high)
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_gte_mask(FStar_UInt128_uint128 a, FStar_UInt128_uint128 b)
{
  return
    (
      (FStar_UInt128_uint128){
        .low = (FStar_UInt64_gte_mask(a.high, b.high) & ~FStar_UInt64_eq_mask(a.high, b.high))
        | (FStar_UInt64_eq_mask(a.high, b.high) & FStar_UInt64_gte_mask(a.low, b.low)),
        .high = (FStar_UInt64_gte_mask(a.high, b.high) & ~FStar_UInt64_eq_mask(a.high, b.high))
        | (FStar_UInt64_eq_mask(a.high, b.high) & FStar_UInt64_gte_mask(a.low, b.low))
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_uint64_to_uint128(uint64_t a)
{
  return ((FStar_UInt128_uint128){ .low = a, .high = (uint64_t)0U });
}

uint64_t FStar_UInt128_uint128_to_uint64(FStar_UInt128_uint128 a)
{
  return a.low;
}

static uint64_t FStar_UInt128_u64_l32_mask = (uint64_t)0xffffffffU;

static uint64_t FStar_UInt128_u64_mod_32(uint64_t a)
{
  return a & FStar_UInt128_u64_l32_mask;
}

static uint32_t FStar_UInt128_u32_32 = (uint32_t)32U;

static K___uint64_t_uint64_t_uint64_t_uint64_t
FStar_UInt128_mul_wide_impl_t_(uint64_t x, uint64_t y)
{
  return
    (
      (K___uint64_t_uint64_t_uint64_t_uint64_t){
        .fst = FStar_UInt128_u64_mod_32(x),
        .snd = FStar_UInt128_u64_mod_32(FStar_UInt128_u64_mod_32(x) * FStar_UInt128_u64_mod_32(y)),
        .thd = x >> FStar_UInt128_u32_32,
        .f3 = (x >> FStar_UInt128_u32_32)
        * FStar_UInt128_u64_mod_32(y)
        + (FStar_UInt128_u64_mod_32(x) * FStar_UInt128_u64_mod_32(y) >> FStar_UInt128_u32_32)
      }
    );
}

static uint64_t FStar_UInt128_u32_combine_(uint64_t hi, uint64_t lo)
{
  return lo + (hi << FStar_UInt128_u32_32);
}

static FStar_UInt128_uint128 FStar_UInt128_mul_wide_impl(uint64_t x, uint64_t y)
{
  K___uint64_t_uint64_t_uint64_t_uint64_t scrut = FStar_UInt128_mul_wide_impl_t_(x, y);
  uint64_t u1 = scrut.fst;
  uint64_t w3 = scrut.snd;
  uint64_t x_ = scrut.thd;
  uint64_t t_ = scrut.f3;
  return
    (
      (FStar_UInt128_uint128){
        .low = FStar_UInt128_u32_combine_(u1
          * (y >> FStar_UInt128_u32_32)
          + FStar_UInt128_u64_mod_32(t_),
          w3),
        .high = x_
        * (y >> FStar_UInt128_u32_32)
        + (t_ >> FStar_UInt128_u32_32)
        +
          ((u1 * (y >> FStar_UInt128_u32_32) + FStar_UInt128_u64_mod_32(t_))
          >> FStar_UInt128_u32_32)
      }
    );
}

FStar_UInt128_uint128 FStar_UInt128_mul_wide(uint64_t x, uint64_t y)
{
  return FStar_UInt128_mul_wide_impl(x, y);
}

