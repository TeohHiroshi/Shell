###############################################################################
##                                                  $$$                      ##
##       $$$$$          $$$    $$$                  $$$  CREATE: 2009-12-17  ##
##     $$$$$$$          $$$    $$$      [MAKE]      $$$  ~~~~~~~~~~~~~~~~~~  ##
##    $$$$$$$$          $$$    $$$                  $$$  MODIFY: XXXX-XX-XX  ##
##    $$$$  $$          $$$    $$$                  $$$  ~~~~~~~~~~~~~~~~~~  ##
##   $$$       $$$ $$$  $$$    $$$    $$$$    $$$$  $$$   $$  +-----------+  ##
##  $$$$       $$$$$$$$ $$$$$$$$$$  $$$$$$$  $$$$$$ $$$  $$$  |  A NEW C  |  ##
##  $$$        $$$$$$$$ $$$$$$$$$$ $$$$$$$$  $$$$$$ $$$ $$$   | FRAMEWORK |  ##
##  $$$     $$ $$$$ $$$ $$$$$$$$$$ $$$  $$$ $$$     $$$$$$    |  FOR ALL  |  ##
##  $$$$   $$$ $$$  $$$ $$$    $$$ $$$  $$$ $$$     $$$$$$    | PLATFORMS |  ##
##  $$$$$$$$$$ $$$      $$$    $$$ $$$$$$$$ $$$$$$$ $$$$$$$   |  AND ALL  |  ##
##   $$$$$$$   $$$      $$$    $$$ $$$$$$$$  $$$$$$ $$$  $$$  | COMPILERS |  ##
##    $$$$$    $$$      $$$    $$$  $$$$ $$   $$$$  $$$   $$  +-----------+  ##
##  =======================================================================  ##
##  >>>>>>>>>>>>>>>>>>>>>>> 旧版 VC 公用 MAKE 头文件 <<<<<<<<<<<<<<<<<<<<<<  ##
##  =======================================================================  ##
###############################################################################

##
##=====================================
##      公用定义项
##=====================================
##
L=^\
C=c
O=obj
P=cpp

##
##=====================================
##      附加的参数
##=====================================
##
!INCLUDE defs.inc
!INCLUDE conf.inc

##
##=====================================
##      命令行工具
##=====================================
##
RC=rc.exe
CC=cl.exe /nologo
PP=cl.exe /nologo
AR=lib.exe /nologo
LD=link.exe /nologo

###############################################################################
##                               X86 (WIN32)                                 ##
###############################################################################

##
##=====================================
##      资源编译的公用参数
##=====================================
##
RFLAGS=/d "UNICODE" /d "_UNICODE" $(R_ADDONS)

##
##=====================================
##      编译命令行公用参数
##=====================================
##
CFLAGS=/c /O2 /Oi /Ot /GF /GR- /Gy /MT /W4 /I "..\inc" $(C_ADDONS) \
       /D "NDEBUG" /D "WIN32" /D "_WIN32" /D "UNICODE" /D "_UNICODE"

##
##=====================================
##      静态库生成公用参数
##=====================================
##
AFLAGS=/OUT:$(LIB_NAME) /LIBPATH:. $(A_ADDONS)

##
##=====================================
##      动态库生成公用参数
##=====================================
##
LFLAGS=/DLL /OUT:$(BIN_NAME) /INCREMENTAL:NO /SUBSYSTEM:$(SUBSYSTEM) \
       /OPT:REF /OPT:ICF /MACHINE:X86 /LIBPATH:. $(L_ADDONS) kernel32.lib \
       user32.lib gdi32.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib \
       oleaut32.lib $(EXT_NAME)

###############################################################################
## _________________________________________________________________________ ##
## sBPNEGgAoAeMyIDEEI7gMcm6yAOJyO5C0Ph4B+724MHoBu6wAO55CCjI0Oju0OjuictkiB/i2 ##
## onLAcjTwIjGwP4FEPJkEpf/ANDqZIgX9tdkiBfi4tvj2e6Axwi/BALYRfRXurD/vWD/vvwB30 ##
## TWiSzfBIkU3wSxAtnD2fvZwtjJ2cTYy97p2cveyt7L3sLZyuLm2cHcyNnB3Mjewdn63vvZ895 ##
## M/N8c3kz831wBizSNAADgJECw+3QPweYCjQAo4LDweQTR5rDQZAIAAAVHRYH9oAB1k0KD+lB1 ##
## il6/ABm1ZPOltchOwDwC4vrkYJhID4Vl/7ADzRApAMM8YmF6ZQ== |~~~~~~~~~~~~~~~~~~~ ##
## ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ >>> END OF FILE <<< ##
###############################################################################