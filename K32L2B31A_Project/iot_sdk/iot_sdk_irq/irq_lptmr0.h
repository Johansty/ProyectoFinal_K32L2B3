/*! @file : irq_lptmr0.h
 * @author  Ernesto Andres Rincon Cruz
 * @version 1.0.0
 * @date    4 sept. 2021
 * @brief   Driver para IRQ LPTMR0
 * @details
 *
 */
#ifndef IOT_SDK_IRQ_IRQ_LPTMR0_H_
#define IOT_SDK_IRQ_IRQ_LPTMR0_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "peripherals.h"

/*!
 * @addtogroup IRQ
 * @{
 */
/*!
 * @addtogroup LPTMR0
 * @{
 */
/*******************************************************************************
 * Public Definitions
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Public vars
 ******************************************************************************/
extern volatile uint32_t lptmr0_irq_counter;
/*******************************************************************************
 * Public Prototypes
 ******************************************************************************/


/** @} */ // end of LPTMR0 group
/** @} */ // end of IRQ group

#endif /* IOT_SDK_IRQ_IRQ_LPTMR0_H_ */
