#ifndef _INPUTKEY
#define _INPUTKEY

//-----------------------------------------------------------------------
//@author KatsuyaKikuchi
//@date 2016/02/11
//@brief Get input keyboard
//-----------------------------------------------------------------------

#include"Base.h"

namespace KeyBoard{
	extern int Key[256];
	int gpUpdateKey();
}

#endif