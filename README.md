# CdePkgValidation
C Development Environment Validation Package for EDK2. This is a SubModule for the EDK2020-MinnowBoard project only. It demonstrates and validates the Standard C Library functions available for POST drivers. 
* [Introduction](README.md#introduction)
* [Intention](README.md#intention)
* [Implementation](README.md#implementation)
  * [Tracing](README.md#tracing)
* [Howto](README.md#howto)
* [Known Bugs](README.md#known-bugs)
* [Revision history](README.md#revision-history)

C Development Environment Validation Package for EDK2

## Introduction
**CdePkgValidation** is the environment for unit tests  of each single ANSI C library function
implemented and provided for other POST drivers in the [**CdePkg**](https://github.com/KilianKegel/CdePkg/blob/master/README.md#cdepkg)

The [list of completeness](https://github.com/KilianKegel/CdePkg/blob/master/implemented.md#validation-status) is updated
by the results of those unit tests.

Furthermore the concept of passing the `EFI_PEI_FILE_HANDLE*` and `EFI_PEI_SERVICES**` parameter to PEI
module's `main()` entry point and `EFI_HANDLE` and `EFI_SYSTEM_TABLE*` for DXE module's `main()` entry point respectively is
demonstrated.

## Intention
The strategy of validating **CdePkg** is to demonstrate, that each single C library function has identical runtime behaviour
when running in UEFI POST or UEFI Shell as if running on Windows NT linked against Microsoft LIBCMT.LIB.

**It is considered the only effective way to reach the ANSI C compatibility and strive for a *faultless implemenation*
within a reasonable amount of time, because by far most parts of each single function test can be run through, debugged and tested natively on the (Windows) development machine. Only final tests need to be run on the UEFI Shell target.**
This proceeding can be reached only by the [OSIF](https://github.com/KilianKegel/CdePkg/blob/master/README.md#interface-architecture) (Operating System Interface) architecture of the library.

NOTE: **Torito C Library** and CdePkg's **CdeLib** have the same sourcecode base. **Torito C Library**
provides CRT0 for Windows NT and CRT0 for UEFI Shell. In contrast **CdeLib**  provides CRT0 for DXE and PEI
drivers.

The tactical procedure for that intent is:
1.  create test programs that can be built for 
    * Windows NT (with Microsofts LIBCMT.LIB)
    * Windows NT (with Torito C Library)
    * UEFI SHELL (with Torito C Library)
    * UEFI DXE (with CdePkg CdeLib)
    * UEFI PEI (with CdePkg CdeLib)
    
    out of the same source code.
    
2.  issue test status messages utilizing a commonly used trace interface [`CDEMOFINE`](https://github.com/KilianKegel/CdePkg/blob/master/Include/CDE.h#L51) to 
    `stdout` (WinNT and UEFI SHELL) or to the StatusCode interface / COM1 at 115200,n,8,1 baud.
    
3.  
    1. Capture the trace messages for POST drivers (terminal program or log window of the emulator).
    2. Capture the trace messages from the same source module compiled as Windows NT executable (linked against libcmt.lib)
        by redirecting to `stdout` as reference traces.
    3. Compare both trace logs to verify equality of the **CdeLib** / **Torito C** functions and the original Microsoft implementation.

The tests are kept simple and quick. (A comprehensive validation can not be done in POST, since the
transmission rate of the trace messages is too slow.)<br>
NOTE: **Torito C Library** has its own, comprehensive validation that produces .log files in size > 50 MiB in UEFI SHELL

## Implementation
Each of the VS2019 projects / EDK2 components can be built in:

1. Visual Studio 2019
2. the EDK2 Emulation Build (EmulationPkg)
3. the EDK2 MinnowBoard Build (Vlv2TbltDevicePkg)

### Tracing
 [`CDEMOFINE`](https://github.com/KilianKegel/CdePkg/blob/master/Include/CDE.h#L51) (**MO**dule **FI**le Li**NE**)was created to provide
 detailed information about origin and location of an event in the trace message, without additional costs
 in maintaining the sourcecode. For that reason [`CDEMOFINE`](https://github.com/KilianKegel/CdePkg/blob/master/Include/CDE.h#L51) automatically emits drivername, filename, functionname, line of sourcecode and the message type 
 (warning, error, info  etc.) and includes a condition to enable or suppress the emission of the message.

## Howto
0. **CdePkgValidation** is a submodule of the [**EDK2020-MinnowBoard**](https://github.com/KilianKegel/EDK2020-MinnowBoard.git) project.<br> https://github.com/KilianKegel/EDK2020-MinnowBoard#howto-installbuildedit
1. Start the VS2019 solution **CdePkgValidation.sln**
2. Notice that each project can be built in 5 different target configurations 
3. Notice that some external EDK configuration files are pulled into the solution that needs to be adjusted
   to place driver binaries into the flash image and to start drivers during POST<br>
  ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled.png)
4. Export the **template** project<br>
   ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled2.png)
   ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled3.png)
   ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled4.png)
5. Create a new project based on that **template**
   ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled5.png)
   ![pci1](https://raw.githubusercontent.com/KilianKegel/pictures/master/Untitled6.png)
6. Get the new project buildable in all target configurations
7. Adjust the .DSC and .FDF files to involve the new driver into EDK2 build<br>
   [EmulatorPkg.dsc](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/EmulatorPkg/EmulatorPkg.dsc#L269)<br>
   [EmulatorPkg.dsc](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/EmulatorPkg/EmulatorPkg.dsc#L316)<br>
   [EmulatorPkg.fdf](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/EmulatorPkg/EmulatorPkg.fdf#L118)<br>
   [EmulatorPkg.fdf](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/EmulatorPkg/EmulatorPkg.fdf#L155)<br>

   [PlatformPkgX64.dsc](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/edk2-platforms/PlatformPkgX64.dsc#L745)<br>
   [PlatformPkgX64.dsc](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/edk2-platforms/PlatformPkgX64.dsc#L910)<br>
   [PlatformPkg.fdf](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/edk2-platforms/PlatformPkg.fdf#L337)<br>
   [PlatformPkg.fdf](https://github.com/KilianKegel/EDK2020-MinnowBoard/blob/master/overrides/edk2-platforms/PlatformPkg.fdf#L435)<br>
8. Add the FILE_GUID / commandline pair to [CdeLoadOptions.h](https://github.com/KilianKegel/CdePkg/blob/master/Include/CdeLoadOptions.h)
6. build the source tree:
    * For MINNOWBOARD BUILD type:<br>**`bldEMU.BAT`**
    * For  EMULATION  BUILD type:<br>**`bldMNW.BAT DEBUG/RELEASE`**
7. Emulation Build run/debug
    * debug: `dbgemu.bat`<br>
      NOTE: To use `__debugbreak()` the debug engine (VS2019) must be connected to the process *before*
            the breakpoint is reached.

  
## Known bugs
* Torito C Library based programs can not build in 32Bit mode because Torito C is for x86-64
  mode only

## Revision history
* update to **TORO C Library** *20230409*
### 20230212
* introduce `CDEABI`, an additional application binary interface ABI to ease coexistance of `CdePkg` based BIOS 
    drivers with incomplete [tianocore EDK2](https://github.com/tianocore/edk2) `C Library` 
    [fragments](https://github.com/tianocore/edk2/blob/master/CryptoPkg/Library/BaseCryptLib/SysCall/CrtWrapper.c#L603)

    NOTE: `CDEABI` uses the Microsoft DLL interface [`__declspec(dllimport)`](https://learn.microsoft.com/en-us/cpp/build/importing-into-an-application-using-declspec-dllimport?view=msvc-170) for EDK2-built drivers .
    Technically this uses *indirect function calls* on machine code level.
* promote `CDETRACE()`, remove former, alternate trace method (`CDEMOFINE()`) completely
### 20210821
* introduce new `IMAGE_ENTRY_POINT`:
  - `_cdeCRT0UefiPei` and respectively `_cdeCRT0UefiPeiEDK` for EDK build
  - `_cdeCRT0UefiDxe` and respectively `_cdeCRT0UefiDxeEDK` for EDK build
  - `_cdeCRT0UefiSmm` and respectively `_cdeCRT0UefiSmmEDK` for EDK build
  - `_cdeCRT0UefiShell` and respectively `_cdeCRT0UefiShellEDK` for EDK build
* but all parts exluded from current excluded from EDK2020-MinnowBoard
### 20210427
* source tree redesign
* torito C library redesign to coexist with / replace EDK2 driver functions
* configure CdePkg to support original tianocore DEBUG traces
* extend Microsft intrinsic __acrt_iob_func() to support variable length I/O buffer count
* improve EDK2 emulator support:
  1. check privileg level before _enable() and _disable()
  2. provide BREAKPOINT entries __cdeImageEntryPointPeiINT3(), __cdeImageEntryPointDxeINT3()
* remove dependancy from 'LoadOptions'
  CdePkg based drivers can start w/o LoadOptions and just get argv[0], argc == 1, if the LoadfOptions driver is not present in the system
* add missing UEFI SHELL Emulation support
* minor face lifts
  1. move forward to better module naming scheme with prefix '__cde'

### 20200315
* implement command line support based on NVRAM variables for the MinnowBoard
* adjust all validation drivers to skip test if no appropriate command line is available
* refer to **CdePkg** readme.md for more information

### 20200202
* move from [tianocore](https://github.com/tianocore/edk2-staging/tree/CdePkg) to my private account 

### 20191023
* Initial version


