/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file    GCC/ARMCMx/STM32F1xx/vectors.c
 * @brief   Interrupt vectors for the STM32F1xx family.
 *
 * @defgroup ARMCMx_STM32F1xx_VECTORS STM32F1xx Interrupt Vectors
 * @ingroup ARMCMx_SPECIFIC
 * @details Interrupt vectors for the STM32F1xx family.
 *          One of the following macros must be defined on the
 *          compiler command line or in a file named <tt>board.h</tt>:
 *          - @p STM32F10X_LD
 *          - @p STM32F10X_LD_VL
 *          - @p STM32F10X_MD
 *          - @p STM32F10X_MD_VL
 *          - @p STM32F10X_HD
 *          - @p STM32F10X_XL
 *          - @p STM32F10X_CL
 *          .
 *          This is required in order to include a vectors table with
 *          the correct length for the specified STM32 model.
 * @{
 */

#include "ch.h"
#include "chconf.h" // @KL

#if defined(STM32F10X_MD_VL) ||  defined(__DOXYGEN__)
#define NUM_VECTORS     46
#elif defined(STM32F10X_HD)  || defined(STM32F10X_XL)
#define NUM_VECTORS     60
#elif defined(STM32F10X_CL)
#define NUM_VECTORS     68
#else
#define NUM_VECTORS     43
#endif

/**
 * @brief   Type of an IRQ vector.
 */
typedef void  (*irq_vector_t)(void);

/**
 * @brief   Type of a structure representing the whole vectors table.
 */
typedef struct {
  uint32_t      *init_stack;
  irq_vector_t  reset_vector;
  irq_vector_t  nmi_vector;
  irq_vector_t  hardfault_vector;
  irq_vector_t  memmanage_vector;
  irq_vector_t  busfault_vector;
  irq_vector_t  usagefault_vector;
  irq_vector_t  vector1c;
  irq_vector_t  vector20;
  irq_vector_t  vector24;
  irq_vector_t  vector28;
  irq_vector_t  svcall_vector;
  irq_vector_t  debugmonitor_vector;
  irq_vector_t  vector34;
  irq_vector_t  pendsv_vector;
  irq_vector_t  systick_vector;
  irq_vector_t  vectors[NUM_VECTORS];
} vectors_t;

#if !defined(__DOXYGEN__)
extern uint32_t __main_stack_end__;
extern void ResetHandler(void);
extern void NMIVector(void);
extern void HardFaultVector(void);
extern void MemManageVector(void);
extern void BusFaultVector(void);
extern void UsageFaultVector(void);
extern void Vector1C(void);
extern void Vector20(void);
extern void Vector24(void);
extern void Vector28(void);
extern void SVCallVector(void);
extern void DebugMonitorVector(void);
extern void Vector34(void);
extern void PendSVVector(void);
extern void SysTickVector(void);
extern void Vector40(void);
extern void Vector44(void);
extern void Vector48(void);
extern void Vector4C(void);
extern void Vector50(void);
extern void Vector54(void);
extern void Vector58(void);
extern void Vector5C(void);
extern void Vector60(void);
extern void Vector64(void);
extern void Vector68(void);
extern void Vector6C(void);
extern void Vector70(void);
extern void Vector74(void);
extern void Vector78(void);
extern void Vector7C(void);
extern void Vector80(void);
extern void Vector84(void);
extern void Vector88(void);
extern void Vector8C(void);
extern void Vector90(void);
extern void Vector94(void);
extern void Vector98(void);
extern void Vector9C(void);
extern void VectorA0(void);
extern void VectorA4(void);
extern void VectorA8(void);
extern void VectorAC(void);
extern void VectorB0(void);
extern void VectorB4(void);
extern void VectorB8(void);
extern void VectorBC(void);
extern void VectorC0(void);
extern void VectorC4(void);
extern void VectorC8(void);
extern void VectorCC(void);
extern void VectorD0(void);
extern void VectorD4(void);
extern void VectorD8(void);
extern void VectorDC(void);
extern void VectorE0(void);
extern void VectorE4(void);
extern void VectorE8(void);
#if defined(STM32F10X_MD_VL) || defined(STM32F10X_HD) ||                    \
    defined(STM32F10X_XL)    || defined(STM32F10X_CL)
extern void VectorEC(void);
extern void VectorF0(void);
extern void VectorF4(void);
#endif
#if defined(STM32F10X_HD)    || defined(STM32F10X_XL) || defined(STM32F10X_CL)
extern void VectorF8(void);
extern void VectorFC(void);
extern void Vector100(void);
extern void Vector104(void);
extern void Vector108(void);
extern void Vector10C(void);
extern void Vector110(void);
extern void Vector114(void);
extern void Vector118(void);
extern void Vector11C(void);
extern void Vector120(void);
extern void Vector124(void);
extern void Vector128(void);
extern void Vector12C(void);
#endif
#if defined(STM32F10X_CL)
extern void Vector130(void);
extern void Vector134(void);
extern void Vector138(void);
extern void Vector13C(void);
extern void Vector140(void);
extern void Vector144(void);
extern void Vector148(void);
extern void Vector14C(void);
#endif
#endif

/**
 * @brief   STM32 vectors table.
 */
#if !defined(__DOXYGEN__)
__attribute__ ((section("vectors")))
#endif
vectors_t _vectors = {
  &__main_stack_end__,ResetHandler,       NMIVector,          HardFaultVector,
  MemManageVector,    BusFaultVector,     UsageFaultVector,   Vector1C,
  Vector20,           Vector24,           Vector28,           SVCallVector,
  DebugMonitorVector, Vector34,           PendSVVector,       SysTickVector,
  {
    Vector40,           Vector44,           Vector48,           Vector4C,
    Vector50,           Vector54,           Vector58,           Vector5C,
    Vector60,           Vector64,           Vector68,           Vector6C,
    Vector70,           Vector74,           Vector78,           Vector7C,
    Vector80,           Vector84,           Vector88,           Vector8C,
    Vector90,           Vector94,           Vector98,           Vector9C,
    VectorA0,           VectorA4,           VectorA8,           VectorAC,
    VectorB0,           VectorB4,           VectorB8,           VectorBC,
    VectorC0,           VectorC4,           VectorC8,           VectorCC,
    VectorD0,           VectorD4,           VectorD8,           VectorDC,
    VectorE0,           VectorE4,           VectorE8,
#if defined(STM32F10X_MD_VL) || defined(STM32F10X_HD) ||                    \
    defined(STM32F10X_XL)    || defined(STM32F10X_CL)
    VectorEC,           VectorF0,           VectorF4,
#endif
#if defined(STM32F10X_HD)    || defined(STM32F10X_XL) || defined(STM32F10X_CL)
    VectorF8,           VectorFC,           Vector100,          Vector104,
    Vector108,          Vector10C,          Vector110,          Vector114,
    Vector118,          Vector11C,          Vector120,          Vector124,
    Vector128,          Vector12C,
#endif
#if defined(STM32F10X_CL)
    Vector130,          Vector134,          Vector138,          Vector13C,
    Vector140,          Vector144,          Vector148,          Vector14C
#endif
  }
};

/**
 * @brief   Unhandled exceptions handler.
 * @details Any undefined exception vector points to this function by default.
 *          This function simply stops the system into an infinite loop.
 *
 * @notapi
 */
#if !defined(__DOXYGEN__)
__attribute__ ((naked))
#endif
void _unhandled_exception(void) {

  while (TRUE)
    ;
}

void NMIVector(void) __attribute__((weak, alias("_unhandled_exception")));
void HardFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void MemManageVector(void) __attribute__((weak, alias("_unhandled_exception")));
void BusFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void UsageFaultVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector1C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector20(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector24(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector28(void) __attribute__((weak, alias("_unhandled_exception")));
void SVCallVector(void) __attribute__((weak, alias("_unhandled_exception")));
void DebugMonitorVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector34(void) __attribute__((weak, alias("_unhandled_exception")));
void PendSVVector(void) __attribute__((weak, alias("_unhandled_exception")));
void SysTickVector(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector40(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector44(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector48(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector4C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector50(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector54(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector58(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector5C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector60(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector64(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector68(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector6C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector70(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector74(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector78(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector7C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector80(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector84(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector88(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector8C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector90(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector94(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector98(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector9C(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorA8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorAC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorB8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorBC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorC0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorC4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorC8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorCC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorD0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorD4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorD8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorDC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorE0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorE4(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorE8(void) __attribute__((weak, alias("_unhandled_exception")));
#if defined(STM32F10X_MD_VL) || defined(STM32F10X_HD) ||                    \
    defined(STM32F10X_XL)    || defined(STM32F10X_CL)
void VectorEC(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorF0(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorF4(void) __attribute__((weak, alias("_unhandled_exception")));
#endif
#if defined(STM32F10X_HD)    || defined(STM32F10X_XL) || defined(STM32F10X_CL)
void VectorF8(void) __attribute__((weak, alias("_unhandled_exception")));
void VectorFC(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector100(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector104(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector108(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector10C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector110(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector114(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector118(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector11C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector120(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector124(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector128(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector12C(void) __attribute__((weak, alias("_unhandled_exception")));
#endif
#if defined(STM32F10X_CL)
void Vector130(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector134(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector138(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector13C(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector140(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector144(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector148(void) __attribute__((weak, alias("_unhandled_exception")));
void Vector14C(void) __attribute__((weak, alias("_unhandled_exception")));
#endif

/** @} */
