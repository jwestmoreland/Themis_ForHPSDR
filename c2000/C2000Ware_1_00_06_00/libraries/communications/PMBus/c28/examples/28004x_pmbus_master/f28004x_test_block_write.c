//#############################################################################
//
//! \file   f28004x_test_block_write.c
//!
//! \brief  Block Write (255 bytes)
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
#include "f28004x_pmbus_master_test.h"

//*****************************************************************************
// the function definitions
//*****************************************************************************

//=============================================================================
// PMBUS_TEST_initBlockWrite()
//=============================================================================
void PMBUS_TEST_initBlockWrite(PMBUS_TEST_Handle hnd)
{
    // Reset flags
    RESET_FLAGS
    // Reset test object
    RESET_TEST_OBJECT
    // Set the block length to 255
    hnd->count = 255U;

    // Enable the test
#if ENABLE_TEST_4 == 1
    hnd->enabled = true;
#else
    hnd->enabled = false;
#endif //ENABLE_TEST_4 == 1
}

//=============================================================================
// PMBUS_TEST_runBlockWrite()
//=============================================================================
void PMBUS_TEST_runBlockWrite(PMBUS_TEST_Handle hnd)
{
    // Locals
    uint16_t i = 0U;

    pmbusMasterBuffer[0] = 0x55U;       // Command
    for(i = 1U; i <= hnd->count; i++)
    {
        pmbusMasterBuffer[i] = i - 1; // Bytes #0 to #N-1 (254)
    }

    // Block writes must be done in chunks of 4 bytes starting with the
    // command byte

    // Config the master to enable PEC, enable Write (by omitting the read
    // option from the configWord, you enable write), enable command,
    // >=3 bytes to transfer
    PMBus_configMaster(PMBUSA_BASE, SLAVE_ADDRESS, hnd->count,
            (PMBUS_MASTER_ENABLE_PEC | PMBUS_MASTER_ENABLE_CMD));
    // Transfer the first 4 bytes, i.e., command, byte #0, #1, #2
    // NOTE: Byte count is automatically inserted after command
    PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[0], 4U);
    // Write the remaining bytes in chunks of 4, last transaction is N+2 % 4
    for(i = 4U; i <= hnd->count; ){
        // Wait for DATA_REQUEST to assert
        while(masterDataRequested == false){}
        masterDataRequested = false;
        if((hnd->count - i - 1U) >= 4U)
        {    // Transfer 4 bytes at a time
            PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[i], 4U);
            i = i + 4U;
        }
        else // remaining bytes < 4U
        {
            PMBus_putMasterData(PMBUSA_BASE, &pmbusMasterBuffer[i],
                    (hnd->count + 1U - i));
            i += (hnd->count + 1U - i);
        }
        // NOTE: PEC is automatically inserted at the end of block write
        // transmission
    }

    // Wait for the EOM, and slave to ack the address before
    // reading data -- done in the ISR
    while(endOfMessage == false){}

    // Once the bus is free, if the slave NACK'd its a failure
    (slaveAckReceived == true) ? hnd->pass++ : hnd->fail++;

    return;
}

// End of File
