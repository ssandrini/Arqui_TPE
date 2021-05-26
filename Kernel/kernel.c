#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>

#include <keyboard.h>
#include <sysHandler.h>
extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	//char buffer[10];

	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	clearBSS(&bss, &endOfKernel - &bss);

	return getStackBase();
}

int main()
{	
	load_idt();
	ncClear();
	((EntryPoint)sampleCodeModuleAddress)();

	/*
	while (1)
	{
		if(getBufferSize() == 10) {
			ncPrint(getBuffer(),0);
			removeBuffer();
		}
	}
	*/

	// int fecha[3];
	// int hora[3];
	// sysHandler((uint64_t) 2, (uint64_t) fecha, (uint64_t) hora);
	// ncPrintDec(fecha[0]); //dia
	// ncPrint(" ",0);
	// ncPrintDec(fecha[1]); //mes
	// ncPrint(" ",0);
	// ncPrintDec(fecha[2]); //año
	// ncNewline();
	// ncPrintDec(hora[0]); //segundos
	// ncPrint(" ",0);
	// ncPrintDec(hora[1]); //minutos
	// ncPrint(" ",0);
	// ncPrintDec(hora[2]); //horas

	// uint64_t registros[15];
	// sysHandler((uint64_t) 3, (uint64_t) registros, (uint64_t)  73);
	// ncPrint("hola mundo", 0);
	// for(int i = 0 ; i < 15; i++){
	// 	ncPrint(registros[i], 0);
	// 	ncPrint(" ", 0);
	// }

	/*
	uint32_t * dir = 180000;
	uint32_t vec[8];
	
	sysHandler((uint64_t) 4, (uint64_t) dir,(uint64_t) vec);

	for(int i = 0; i<8;i++) {
		ncPrintHex((uint64_t) (*(dir+i*4)));
		ncPrint(" ", 0);
	}

	*/

	return 0;
}
