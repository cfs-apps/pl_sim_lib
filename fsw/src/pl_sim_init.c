/*
**  Copyright 2022 bitValence, Inc.
**  All Rights Reserved.
**
**  This program is free software; you can modify and/or redistribute it
**  under the terms of the GNU Affero General Public License
**  as published by the Free Software Foundation; version 3 with
**  attribution addendums as found in the LICENSE.txt
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Affero General Public License for more details.
**
**  Purpose:
**    Entry point function for OSK app framework library
**
**  Notes:
**    None
**
**  References:
**    1. OpenSatKit Object-based Application Developer's Guide.
**    2. cFS Application Developer's Guide.
**
*/

/*
** Includes
*/

#include "lib_cfg.h"
#include "pl_sim_lib.h"

/*****************/
/** Global Data **/
/*****************/

PL_SIM_LIB_Class_t  PlSimLib;


/************************/
/** Exported Functions **/
/************************/

/******************************************************************************
** Entry function
**
*/
uint32 PL_SIM_LibInit(void)
{

   uint32 RetStatus = OS_ERROR;
   
   /*
   ** Initialize objects 
   */

   if (PL_SIM_LIB_Constructor(&PlSimLib))
   {

      RetStatus = OS_SUCCESS;
      OS_printf("Payload Simulator Library Initialized. Version %d.%d.%d\n",
                PL_SIM_LIB_MAJOR_VER, PL_SIM_LIB_MINOR_VER, PL_SIM_LIB_PLATFORM_REV);
   }
   else
   {
      OS_printf("Error initializing Payload Simulator Library. Version %d.%d.%d\n",
                PL_SIM_LIB_MAJOR_VER, PL_SIM_LIB_MINOR_VER, PL_SIM_LIB_PLATFORM_REV);      
   }
   
   return RetStatus;

} /* End PL_SIM_LibInit() */

