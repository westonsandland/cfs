#include "sys.h"
#include "stdint.h"
#include "idt.h"
#include "debug.h"
#include "machine.h"
#include "u8250.h"

extern "C" int sysHandler(uint32_t eax, uint32_t *frame) {
	U8250 out;
	uint32_t* usp = (uint32_t*)(*(frame + 3));
	
	if(eax) {
		uint32_t* buffer = (uint32_t*)(*(usp + 2));
		uint32_t len = (uint32_t)(*(usp + 3));
		char* wordList = (char*)buffer;
		for(uint32_t x = 0; x < len; x++) {
			out.put((char)(*(wordList + x)));
		}
		return (int)len;
	}
	else {
		Debug::shutdown();
		return eax;
	}
}

void SYS::init(void) {
    IDT::trap(48,(uint32_t)sysHandler_,3);
}
