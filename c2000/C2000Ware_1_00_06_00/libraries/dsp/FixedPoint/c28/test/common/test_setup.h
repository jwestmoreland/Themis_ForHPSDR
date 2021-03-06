#ifndef _TEST_SETUP_H_
#define _TEST_SETUP_H_
//#############################################################################
//! \file /$FOLDER_TEST$/common/examples_setup.h
//!
//! \brief  Test framework for the Fixed Point library examples
//! \date   Sep 22, 2014
//
//  Group:          C2000
//  Target Family:  C28x
//
//#############################################################################
//$TI Release: C28x Fixed Point DSP Library v1.20.00.00 $
//$Release Date: Thu Oct 18 15:57:22 CDT 2018 $
//$Copyright: Copyright (C) 2014-2018 Texas Instruments Incorporated -
//            http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "DSP28x_Project.h"
#include <stdint.h>
#include <float.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_150MHZ	1

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void FIXPT_DSP_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void FIXPT_DSP_initEpie(void);

// \brief Initialize Flash
//
void FIXPT_DSP_initFlash(void);

// \brief End of test
//
void FIXPT_DSP_testEnd(void);

// \brief Test error handler
//
void FIXPT_DSP_testError(void);

//! \brief autobot done()
//!
void done(void);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _TEST_SETUP_H_ definition
