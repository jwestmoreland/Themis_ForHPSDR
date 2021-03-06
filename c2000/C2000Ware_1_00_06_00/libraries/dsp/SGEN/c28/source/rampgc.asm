;=====================================================================
; File name     : RAMPGC.ASM                     
;                    
; Originator    : Advanced Embedded Control (AEC)
;                 Texas Instruments Inc.
;
; Description   : This file contains source for the RMPGEN_calc function.
;
; Routine Type  : "CcA Only"
;                               
; Date          : 28/12/2001 (DD/MM/YYYY)
;=====================================================================
; Routine Name: rmpgen_calc                             
;
; C prototype : int RMPGEN_calc(RMPGEN_handle);
;
; The struct is defined as follows:
; typedef struct  {   
;   int freq;      /* Frequency setting        Q15 Input     */ 
;   int freq_max;  /* Frequency setting        Q0  Input     */ 
;   int alpha;     /* Internal var - Phase angle history     */
;   int gain;      /* Waveform amplitude       Q15 Input     */
;   int offset;    /* Offset setting           Q15 Input     */ 
;   int out;       /* Ramp generator output    Q15 Output    */
;   int (*calc)(); /* Pointer to calculation function        */ 
;   } RMPGEN;
;
;=====================================================================
; ###########################################################################
; $TI Release: C28x SGEN Library v1.02.00.00 $
; $Release Date: Thu Oct 18 15:57:41 CDT 2018 $
; $Copyright: Copyright (C) 2011-2018 Texas Instruments Incorporated -
;             http://www.ti.com/ ALL RIGHTS RESERVED $
; ###########################################################################

                .def        _RMPGEN_calc

_RMPGEN_calc:
            SETC    SXM,OVM         ; XAR4->freq
                            
; Obtain the step value in pro-rata with the freq input         
            MOV     T,*XAR4++       ; XAR4->step_max, T=freq
            MPY     ACC,T,*XAR4++   ; XAR4->alpha, ACC=freq*step_max (Q15)
            MOVH    AL,ACC<<1           
            
; Increment the angle "alpha" by step value             
            ADD     AL,*XAR4        ; AL=(freq*step_max)+alpha  (Q0)
            MOV     *XAR4,AL        ; XAR4->alpha, alpha=alpha+step (Unsigned 8.8 format)   
            MOV     T,AL            

; Scale the SIN output with the gain and add offset           
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[3],AH    ; out=Y*gain+offset
        	CLRC 	OVM
        	LRETR
            


