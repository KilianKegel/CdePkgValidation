/*!
@copyright
    Copyright (c) 2020, Kilian Kegel. All rights reserved.<BR>
    SPDX-License-Identifier: BSD-2-Clause-Patent

@file EfiCallerBaseName.c

@brief C Development Environment (CDE) driver name\n
    
    Supply of the drivers / executables name, for the CDEMOFINE trace infrastructure.
    
    In the EDK build process this file must not be used, since
    'gEfiCallerBaseName' is automatically generated by the build process.


*/
char* gEfiCallerBaseName = CDE_DRIVER_NAME;