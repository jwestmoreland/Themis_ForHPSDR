//#############################################################################
//
//! \file   f28004x_handle_extended_read_word.c
//!
//! \brief  Read Word (Extended)
//! \author Vishal Coelho
//! \date   Jul 8, 2015
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
// PMBus_Stack_extReadWordHandler()
//=============================================================================
void PMBus_Stack_extReadWordHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    uint16_t command = buffer[1];
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);

    // Set the number of bytes to send
    PMBus_Stack_Obj_setNBytes(hnd, 2U);

    buffer[0] = command ^ 0xFF; // Send this message to the master
    buffer[1] = command ^ 0x55; // Send this message to the master

    (trn == PMBUS_TRANSACTION_READWORD)? pass++: fail++;
    
    // Update number of completed tests
    testsCompleted++;
}


// End of File
