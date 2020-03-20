@echo off
@echo NOTE: POST traces include timestamp, Windows traces does
@echo simulating PEI Phase
argcv               abc "d e f g" \"1 23
rem systeminterfacePEI
timehfunctions
stringhfunctions
wcharhfunctions
stdiohfunctions
stdlibhfunctions
ctypehfunctions     /count 256
wctypehfunctions    /count 512 please_test_up_to_65537_instead_of_512
asserthfunctions
localehfunctions
clock               /frq 1 /count 21

@echo simulating DXE Phase
argcv               abc "d e f g" \"1 23
rem systeminterfacePEI
timehfunctions
stringhfunctions
wcharhfunctions
stdiohfunctions
stdlibhfunctions
ctypehfunctions     /count 256
wctypehfunctions    /count 512 please_test_up_to_65537_instead_of_512
asserthfunctions
localehfunctions
clock               /frq 3 /count 63
