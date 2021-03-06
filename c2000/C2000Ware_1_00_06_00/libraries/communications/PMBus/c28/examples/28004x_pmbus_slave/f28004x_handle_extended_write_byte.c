//#############################################################################
//
//! \file   f28004x_handle_extended_write_byte.c
//!
//! \brief  Write Byte
//! \author Vishal Coelho
//! \date   Jul 7, 2015
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
// PMBus_Stack_extWriteByteHandler()
//=============================================================================
void PMBus_Stack_extWriteByteHandler(PMBus_Stack_Handle hnd)
{
    // Locals
    uint16_t nBytes  = PMBus_Stack_Obj_getNBytes(hnd);
    uint32_t base    = PMBus_Stack_Obj_getModuleBase(hnd);
    uint16_t *buffer = PMBus_Stack_Obj_getPtrBuffer(hnd);
    PMBus_Transaction trn = PMBus_Stack_Obj_getTransaction(hnd);
    uint32_t status  = PMBus_Stack_Obj_getModuleStatus(hnd);

    (nBytes == 4U)? pass++ : fail++;
    (hnd->ptrBuffer[0U] ==  PMBUS_CMD_MFR_SPECIFIC_COMMAND)? pass++ : fail++;
    (hnd->ptrBuffer[1U] ==  PMBUS_CMD_STORE_DEFAULT_CODE)? pass++ : fail++;
    (hnd->ptrBuffer[2U] ==  PMBUS_CMD_STORE_DEFAULT_CODE ^ 0xFFU)? pass++ :
                                                                   fail++;
    (trn == PMBUS_TRANSACTION_WRITEBYTE)? pass++: fail++;

    // For extended read/writes have to run CRC on
    // Addr+W, Extension, Command, Addr+R/W, Byte(s)
    // Cant run PMBus_verifyPEC, just check the PEC_VALID bit
    if((status & PMBUS_PMBSTS_PEC_VALID) != 0U)
    {
        pass++;
    }
    else
    {
        fail++;
    }
    // Update number of completed tests
    testsCompleted++;
}


// End of File
