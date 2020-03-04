/*!
@copyright
    Copyright (c) 2020, Kilian Kegel. All rights reserved.<BR>
    SPDX-License-Identifier: BSD-2-Clause-Patent

@file main.c

@brief 
    This module implements unit test for the <em>time.h / clock()</em> function
@todo

@mainpage
    clock() validation driver

@section intro_sec Introduction
    Validation of the <em>clock()</em>-function from the standard C library.<br><br>
    <a href="https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/clock?view=vs-2019">clock_t clock(void)</a>\n

@subsection Drv_sec Driver and Application matrix
    <table>
                <tr>
                    <Th></th>
                    <Th>PEI</th>
                    <Th>DXE</th>
                    <Th>Windows</th>
                 </tr>
                <tr><th>NAME</th>
                    <TD>clockPei.efi</td>
                    <TD>clockDxe.efi</td>
                    <TD>clock.exe</td>
                </tr>
                <tr><th>GUID</th>
                    <TD>CDE000FF-A2C0-4C76-82D5-F0206EA53289</td>
                    <TD>CDE000FF-FBBA-4AA6-B1C2-9701038905B2</td>
                    <TD>n/a</td></tr>
                <tr>
                    <th>parameter</th>
                    <td colspan="3">/frq <em>frequency</em> : print "." at <em>frequency</em>, NOTE: frequency <= CLOCKS_PER_SEC</td>
                </tr>
                <tr>
                    <th></th>
                    <td colspan="3">/count <em>count</em> : <em>count</em> of "."</td></tr>
                </tr>
    </table>

@subsection ref_sec References
    <a href="https://www.pdf-archive.com/2014/10/02/ansi-iso-9899-1990-1/ansi-iso-9899-1990-1.pdf">ANSI C Specification</a>\n


@subsection Parm_sec Command line parameters
*/
#pragma warning(disable:4005)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <CDE.h>

#include <Uefi.h>
#include <PiPei.h>
#define COUNT 20
#define FRQ   1

extern char _CdeGetCurrentPrivilegeLevel(void); // check emulation mode

extern char* strefierror(EFI_STATUS Status);

//#include <uefi.h>

static char* gszCdeDriverName;

int main(int argc, char** argv) {
    gszCdeDriverName = argv[0];
    clock_t clk;
    int i;
    long count = COUNT;
    long frq = FRQ;
    char buffer[256];

    CDEMOFINE((MFNINF(1) "##################################################################\n"));
    CDEMOFINE((MFNINF(1) "########################## Test clock() in %s %s\n", CDE_CONFIGURATION_STRING, CDE_PLATFORM_STRING));
    CDEMOFINE((MFNINF(1) "##################################################################\n"));
    //todo exit(0);
    if (1)
    {
        EFI_STATUS Status = 0LL;
        EFI_PEI_SERVICES** PeiServices = (void*)(argv[-1]);    //PeiServices is passed in argv[-1]
        //EFI_PEI_FILE_HANDLE FileHandle = (void*)(argv[-2]);    //FileHandle  is passed in argv[-2]

        static EFI_GUID gCdePeiTmpTest0Guid = CDE_PEI_TMPTEST0_GUID;
        static EFI_PEI_PPI_DESCRIPTOR CdeLoadOptionsPpiList = {/*Flags*/(EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),/**Guid*/&gCdePeiTmpTest0Guid, /*Ppi*/0 };
        
        if (0 == strcmp("EDK2 UEFI PRE(CdeLib)", CDE_CONFIGURATION_STRING)) {
            Status = (*PeiServices)->InstallPpi(PeiServices, &CdeLoadOptionsPpiList);
            Status &= 0xFFFFFFFFULL;
            CDEMOFINE((MFNBAR(1) "====================> %s %llX\n", strefierror(Status), Status));
        }
    }

    for (i = 0; i < argc; i++) {
        //
        // test strncmp() and strlen()
        //
        if (0 == strncmp("/frq", argv[i], strlen("frq"))) {
            frq = atol(argv[i + 1]);
        }

        if (0 == strncmp("/count", argv[i], strlen("/count"))) {
            count = atol(argv[i + 1]);
        }

    }

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "argc = %d, ", argc);
    for (i = 0; i < argc; i++) {
        sprintf(&buffer[strlen(buffer)], "argv[%d] = %s, ", i, argv[i]);
    }

    buffer[strlen(buffer) - 2] = '\0';          // kill last ', '


    CDEMOFINE((MFNINF(1) "%s\n", buffer));

    for (i = 0; i < count; i++) {

        clk = CLOCKS_PER_SEC / frq /*frequency*/ + clock();
        CDEMOFINE((MFNBAR(1) "."));
        while (clk > clock())
            ;

    }
    CDEMOFINE((MFNBAR(1) "\n"));

}