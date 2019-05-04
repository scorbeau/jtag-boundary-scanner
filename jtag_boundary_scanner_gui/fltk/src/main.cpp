
#if 0
#include <stdio.h>

#include <controller/SystemController.h>
#include <jtag_core.h>
#endif
#include "controller/SystemController.h"

int main(int argc, char *argv[])
{
	SystemController controller;

	return controller.runApplication();
}

#if 0
#include <unistd.h>

int main(int argc, char *argv[])
{
	SystemController *controller = new SystemController();
	const SystemData *data = controller->getSystemData();
	size_t i;
	size_t j;
	int err;

	char cwd[255];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current working dir: %s\n", cwd);
	} else {
		perror("getcwd() error");
		return 1;
	}

	err = controller->initJtagCore();
	if(err) {
		printf("JTAG core init failed\n");
	} else {
		printf("JTAG core init done\n");
		err = controller->refreshProbeList();
	}

	if(!err) {
		printf("Nb probe detected :%ld\n", data->getNbProbe());
		for(i=0; i<data->getNbProbe(); i++) {
			const ProbeData *probe = data->getProbe(i);
			printf("Probe[%ld] : %s Probe id : %d\n",
				i,
				probe->getName().c_str(),
				probe->getIdentifier());
		}

		const ProbeData *probe = data->getProbe(0);
		err = controller->scanProcessor(probe->getIdentifier());
	} else {
		printf("Failed to get connected probes !\n");
	}

	if(!err) {
		for(i=0; i<data->getNbCpu(); i++) {
			const CpuData *cpu = data->getCpu(i);
			printf("CPU[%ld] :\n", i);
			printf("\t-Id : 0x%08lX\n", cpu->getCpuId());
			printf("\t-JTAG index : %d\n", cpu->getCpuJtagIndex());

			if(0 == cpu->getNbBsdlFiles()) {
				printf("\t-No BSDL file found\n");
			} else {
				printf("\t-BSDL file(s):\n");
			}
			
			for(j=0; j<cpu->getNbBsdlFiles(); j++) {
				printf("\t\t-%s\n",
				       cpu->getBsdlFile(j).c_str());
			}
		}
		if(data->getNbCpu() > 0) {
			printf("Add CPU[0] pins\n");
			err = controller->loadCpuBsdl(0, 0);
		}
	} else {
		printf("Failed to scan JTAG chain\n");
	}

	if(!err) {
		const CpuData *cpu = data->getCpu(0);
		printf("CPU[0] Nb usable gpios %ld :\n",
			cpu->getNbUsablePins());
		for(i=0; i<cpu->getNbUsablePins(); i++) {
			const PinData *pin = cpu->getUsablePin(i);
			printf("CPU[0]->usable_pin[%ld] = %s %s:%s:%s jtag"
			       "chain id=%ld\n",
			       i,
			       pin->getName().c_str(),
			       pin->isInput() ? "I" : "-",
			       pin->isOutput() ? "O" : "-",
			       pin->isTristate() ? "T" : "-",
			       pin->getJtagChainIndex());
		}
		printf("CPU[0] Nb unsable gpios %ld :\n",
			cpu->getNbUnusablePins());
		for(i=0; i<cpu->getNbUnusablePins(); i++) {
			const PinData *pin = cpu->getUnusablePin(i);
			printf("CPU[0]->unusable_pin[%ld] = %s\n",
			       i,
			       pin->getName().c_str());
		}
	}

	delete controller;

	return 0;
}
#endif

