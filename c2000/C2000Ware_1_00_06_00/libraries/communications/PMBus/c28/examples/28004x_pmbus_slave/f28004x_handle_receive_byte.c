//#############################################################################
//
//! \file   f28004x_handle_receive_byte.c
//!
//! \brief  Receive Byte
//! \author Vishal Coelho
//! \date   Apr 6, 2015
//
//  Group:          C2000
//  Target Device:  TMS320F28xxxx
//
// Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
// $TI Release: C28x PMBus Communications Stack Library v1.00.00.00 $
// $Release Date: Oct 18, 2018 $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************
#include "f28004x_pmbus_slave_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBus_Stack_receiveByteHandler()
//=============================================================================
void PMBus_Stack_receiveByteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    // Set the number of bytes to send
    PMBus_Stack_Obj_setNBytes(hnd, 1U);

    buffer[0] = 0x55U; // Send this message to the master

    (trn == PMBUS_TRANSACTION_RECEIVEBYTE)? pass++: fail++;

    // Update number of completed tests
    testsCompleted++;
}

// End of File
