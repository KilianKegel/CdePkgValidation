/*!
@copyright
    Copyright (c) 2020-2024, Kilian Kegel. All rights reserved.<BR>
    SPDX-License-Identifier: BSD-2-Clause-Patent

@file main.c

@brief 
    This is the CdePkgValidation asserthfunctions driver
@todo

@mainpage
    This is the CdePkgValidation asserthfunctions driver

@section intro_sec Introduction
    This is the CdePkgValidation asserthfunctions driver

@subsection Drv_sec Driver and Application matrix
    <table>
                <tr>
                    <Th></th>
                    <Th>PEI</th>
                    <Th>DXE</th>
                    <Th>Windows</th>
                 </tr>
                <tr><th>NAME</th>
                    <TD>asserthfunctionsPei.efi</td>
                    <TD>asserthfunctionsDxe.efi</td>
                    <TD>asserthfunctions.exe</td>
                </tr>
                <tr><th>GUID</th>
                    <TD>CDE000FF-C6F5-49CC-BFD3-F44A5912649A</td>
                    <TD>CDE000FF-D381-49C3-8D4A-44C94843F83C</td>
                    <TD>n/a</td></tr>
                <tr>
                    <th>parameter</th>
                    <td colspan="3"></td>
                </tr>
                <tr>
                    <th></th>
                    <td colspan="3"></td></tr>
                </tr>
    </table>

@subsection ref_sec References
    <a href="https://www.pdf-archive.com/2014/10/02/ansi-iso-9899-1990-1/ansi-iso-9899-1990-1.pdf">ANSI C Specification</a>\n
	<a href="https://docs.microsoft.com/en-us/cpp/c-language/c-language-reference?view=vs-2019">Microsoft Language Refernce</a>\n


@subsection Parm_sec Command line parameters
*/
#include <CDE.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char** argv) {

    //__debugbreak(); NOTE: to use breakpoints run DBGEMU.BAT

	CDETRACE((TRCINF(1) "##################################################################\n"));
    CDETRACE((TRCINF(1) "########################## CdePkg driver asserthfunctions %s %s\n", CDE_CONFIGURATION_STRING, CDE_PLATFORM_STRING));
    CDETRACE((TRCINF(1) "##################################################################\n"));

    CDETRACE((TRCFAT/*M-odule F-ile li-N-e FATAL (including termination)*/(0 == strncmp(argv[0], "unknownCdeDriver", strlen("unknownCdeDriver"))) "\nA command line is not injected into NVRAM (\"LoadOption.efi\") - driver terminated\n\n"));

    assert(argc == 3);
    
    CDETRACE((TRCINF(1) "##################################################################\n"));
    
    return 0;
}