//#############################################################################
//! \file  2837x_Round/C-model/Round.c
//!
//! \brief  Unbiased rounding of a floating point real number
//! \author David M. Alter
//! \date   06/27/11
//
//  Group:             C2000
//  Target Family:     F2837x
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.50.00.00 $
// $Release Date: Oct 18, 2018 $
// $Copyright: Copyright (C) 2018 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//#############################################################################

#include "Round.h"                // Main include file
#include <math.h>

/**********************************************************************
* Function: round()
*
* Description: Unbiased rounding of a floating point real number.
* 
* Benchmark: 78 cycles using C28x compiler v6.0.1
**********************************************************************/
float round(float x)
{

    return( floor(x+0.5) ); 

} // end round()

// End of file
