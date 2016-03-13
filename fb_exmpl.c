
#include "fb/fb.h"

// ----------------------------------------------------------
//                    FB example
// ----------------------------------------------------------
enum { 
	e_ex_in = 0, 
	e_ex_out = 1
}EFB_example;

typedef struct {
	RINTEGER  IntegerValue;   // Количество входов
	RFLOAT    FloatValue;   // Количество входов
} R_PACKED TCfgExample;               // Структура конфигурации ФБ

int FB_example( FB_MODE fbMode, FB_CB PTR fbCB)
{
	RES;

	if ( fbMode == fbmExecute )
	{
		TCfgExample PTR pCfg = (TCfgExample PTR)fbCB->pConfig;

		// call every cicle
		RFLOAT value;
		CHECK_RESULT(ReadFloat(fbCB, e_ex_in, &value));
		CHECK_RESULT(SetEventState(fbCB, 1, value > 10.0));
		CHECK_RESULT(SetEventState(fbCB, 43, value > 20.0));

		if (*((RINTEGER PTR)fbCB->pPersonalMem) != pCfg->IntegerValue)
		{
			CHECK_RESULT(FireSimpleEventForMultiple(fbCB, 2, pCfg->IntegerValue));
			*((RINTEGER PTR)fbCB->pPersonalMem) = pCfg->IntegerValue;
		}

		CHECK_RESULT(WriteInteger(fbCB, e_ex_out, pCfg->IntegerValue));

		return S_OK;
	}

	if( fbMode == fbmGetMem )
	{
		// call first time, on start
		fbCB->SizeShareMem    = 0;
		fbCB->SizePersonalMem = sizeof(RINTEGER);
		return S_OK;
	}

	if( fbMode == fbmInit )
	{
		// call on start, after fbmGetMem
		*((RINTEGER PTR)fbCB->pPersonalMem) = 0;
		return S_OK;
	}

	return E_FAIL;
}
