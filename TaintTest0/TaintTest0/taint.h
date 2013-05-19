#pragma once
 
#ifndef __ARIETIS_TAINT_DIRECTIVE_H__
#define __ARIETIS_TAINT_DIRECTIVE_H__
 
#define TAINT_CODE_BEGIN()  __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0x65 __asm __emit 0x92 __asm __emit 0x15 __asm __emit 0x14
#define TAINT_CODE_END()    __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0x14 __asm __emit 0x15 __asm __emit 0x92 __asm __emit 0x65

#define DO_TAINT()    __asm __emit 0xeb __asm __emit 0x04 __asm __emit 0xcf __asm __emit 0xca __asm __emit 0xed __asm __emit 0xf1

#endif // __ARIETIS_TAINT_DIRECTIVE_H__