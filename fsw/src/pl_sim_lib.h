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
**    Define the Payload Simulator Object
**
**  Notes:
**    1. PL_SIM serves as an example of how a library interface
**       to a hardware device can be replaced with simulated
**       behavior. The functions perform the following roles:
**       A. Model instrinsic payload behavior
**          - PL_SIM_LIB_Constructor()
**          - PL_SIM_LIB_ExecuteStep()
**          - PL_SIM_LIB_SetFault()
**          - PL_SIM_LIB_ClearFault()
**       B. Model payload Electrical Interface
**          - PL_SIM_LIB_PowerOn()
**          - PL_SIM_LIB_PowerOff()
**          - PL_SIM_LIB_PowerReset()
**       C. Model payload data interface
**          - PL_SIM_LIB_DetectorOn()
**          - PL_SIM_LIB_DetectorOff()
**          - PL_SIM_LIB_ReadState()
**    2. This header can't include lib_cfg.h because it would
**       cause an initbl CFG definition conflict with apps that
**       include this header. The initbl design assumes the
**       the CFG_ definitions are unique to an app or a lib.
**
*/
#ifndef _pl_sim_lib_
#define _pl_sim_lib_

/*
** Includes
*/
#include "pl_sim_lib_eds_typedefs.h"

/***********************/
/** Macro Definitions **/
/***********************/


#define PL_SIM_LIB_DETECTOR_ROW_LEN        32
#define PL_SIM_LIB_DETECTOR_ROWS_PER_IMAGE 10

/*
** Event Message IDs
*/

#define PL_SIM_LIB_POWER_INIT_COMPLETE_EID  (APP_C_FW_LIB_BASE_EID + 0)
#define PL_SIM_LIB_POWER_INVALID_STATE_EID  (APP_C_FW_LIB_BASE_EID + 1)
#define PL_SIM_LIB_POWER_TRANSITION_EID     (APP_C_FW_LIB_BASE_EID + 2)
#define PL_SIM_LIB_DETECTOR_RESET_CMD_EID   (APP_C_FW_LIB_BASE_EID + 3)
#define PL_SIM_LIB_DETECTOR_RESET_EID       (APP_C_FW_LIB_BASE_EID + 4)
#define PL_SIM_LIB_DETECTOR_SIM_ERR_EID     (APP_C_FW_LIB_BASE_EID + 5)

/**********************/
/** Type Definitions **/
/**********************/


typedef struct
{
   
   char Data[PL_SIM_LIB_DETECTOR_ROW_LEN];
   
} PL_SIM_LIB_DetectorRow_t;

typedef struct
{
   
   uint16  ReadoutRow;   
   uint16  ImageCnt;
   PL_SIM_LIB_DetectorRow_t Row;

} PL_SIM_LIB_Detector_t;


typedef struct
{

   uint16   PowerInitCycleLim;
   uint16   DetectorResetCycleLim;

} PL_SIM_LIB_Config_t;

typedef struct
{

   PL_SIM_LIB_Power_Enum_t Power;
   uint16  PowerInitCycleCnt;
   uint16  DetectorResetCycleCnt;
   
   PL_SIM_LIB_Detector_Enum_t Detector;
   uint16  DetectorReadoutRow; 
   bool    DetectorFaultPresent;

} PL_SIM_LIB_State_t;

typedef struct
{

   /* 
   ** App Framework
   */ 
   
   INITBL_Class_t  IniTbl;
   
   /* 
   ** PL_SIM State
   */ 

   PL_SIM_LIB_Detector_t Detector;  
   PL_SIM_LIB_State_t    State;
   PL_SIM_LIB_Config_t   Config;
   
} PL_SIM_LIB_Class_t;


/************************/
/** Exported Functions **/
/************************/

/******************************************************************************
** Function: PL_SIM_LIB_Constructor
**
** Initialize the payload simulator to a known state
**
** Notes:
**   1. This must be called prior to any other function.
**
*/
bool PL_SIM_LIB_Constructor(PL_SIM_LIB_Class_t *PlSimPtr);


/******************************************************************************
** Functions: PL_SIM_LIB_ClearFault
**
** Clear fault state.
**
** Notes:
**   1. No return status required, the simulated fault is always cleared.
**
*/
void PL_SIM_LIB_ClearFault(void);


/******************************************************************************
** Functions: PL_SIM_LIB_DetectorOff
**
** Turn off the detector
**
** Notes:
**   1. This does not affect the power state.
**
*/
void PL_SIM_LIB_DetectorOff(void);


/******************************************************************************
** Functions: PL_SIM_LIB_DetectorOn
**
** Turn on the detector
**
** Notes:
**   1. This does not affect the power state.
**
*/
void PL_SIM_LIB_DetectorOn(void);


/******************************************************************************
** Functions: PL_SIM_LIB_DetectorReset
**
** Reset detector electronics
**
** Notes:
**   1. Reset clears simulated faults and allows some system state to persist
**      across the reset. 
**   2. No return status required, power is always set to true.
**
*/
void PL_SIM_LIB_DetectorReset(void);


/******************************************************************************
** Function: PL_SIM_LIB_ExecuteStep
**
** Execute a single simulation step.
**
** Notes:
**   None
*/
void PL_SIM_LIB_ExecuteStep(void);


/******************************************************************************
** Functions: PL_SIM_LIB_GetPowerStateStr
**
** Read the state of the library simulation
**
** Notes:
**  1. In a non-simulated environment this would not exist.
**
*/
const char* PL_SIM_LIB_GetPowerStateStr(PL_SIM_LIB_Power_Enum_t Power);


/******************************************************************************
** Functions: PL_SIM_LIB_PowerOff
**
** Power off the simulated payload
**
** Notes:
**   1. No return status required, power is always set to false.
**
*/
void PL_SIM_LIB_PowerOff(void);


/******************************************************************************
** Functions: PL_SIM_LIB_PowerOn
**
** Power on the simulated payload to a known default state
**
** Notes:
**   1. The JSON init file defines configurable default state parameters
**   2. No return status required, power is always set to true.
**
*/
void PL_SIM_LIB_PowerOn(void);


/******************************************************************************
** Functions: PL_SIM_LIB_ReadDetector
**
** Read the detector data and state information
**
** Notes:
**  1. In a non-simulated environment this would be read across a hardware
**     interface.
**
*/
bool PL_SIM_LIB_ReadDetector(PL_SIM_LIB_Detector_t *Detector);


/******************************************************************************
** Functions: PL_SIM_LIB_ReadPowerState
**
** Read the current power state of the payload
**
** Notes:
**  1. In a non-simulated environment this would be read across a hardware
**     interface.
**
*/
PL_SIM_LIB_Power_Enum_t PL_SIM_LIB_ReadPowerState(void);


/******************************************************************************
** Functions: PL_SIM_LIB_ReadLibraryState
**
** Read the state of the library simulation
**
** Notes:
**  1. In a non-simulated environment this would not exist.
**
*/
void PL_SIM_LIB_ReadState(PL_SIM_LIB_Class_t *PlSimObj);


/******************************************************************************
** Functions: PL_SIM_LIB_SetFault
**
** Set/clear fault state.
**
** Notes:
**   1. No return status required, the simulated fault is always set.
**
*/
void PL_SIM_LIB_SetFault(void);


#endif /* _pl_sim_lib_ */
