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
**    Define configurations for the Payload Simulator Library
**
**  Notes:
**    1. These macros can only be built with the application and can't
**       have a platform scope because the same file name is used for
**       all applications following the object-based application design.
**    2. This must be named lib_cfg.h and not app_cfg.h because apps
**       need to add the library soucre directory to their include
**       search path and they'd get a conflict with app_cfg.h.
**
**  References:
**    1. OpenSatKit Object-based Application Developer's Guide.
**    2. cFS Application Developer's Guide.
**
*/
#ifndef _lib_cfg_
#define _lib_cfg_

/*
** Includes
*/

#include "pl_sim_lib_eds_typedefs.h"
#include "app_c_fw.h"
#include "pl_sim_lib_platform_cfg.h"

/******************************************************************************
** PL_SIM Application Macros
*/

/*
** Versions:
**
** 1.0 - Initial release based on OpenSatKit Instrument Simulator(ISIM)
*/

#define  PL_SIM_LIB_MAJOR_VER   0
#define  PL_SIM_LIB_MINOR_VER   9


/******************************************************************************
** JSON init file definitions/declarations.
**    
*/

#define CFG_PWR_INIT_CYCLES    PWR_INIT_CYCLES
#define CFG_PWR_RESET_CYCLES   PWR_RESET_CYCLES

#define LIB_CONFIG(XX) \
   XX(PWR_INIT_CYCLES,uint32) \
   XX(PWR_RESET_CYCLES,uint32) \

DECLARE_ENUM(Config,LIB_CONFIG)


#endif /* _lib_cfg_ */
