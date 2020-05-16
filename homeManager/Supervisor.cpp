#include "Supervisor.h"

Supervisor::Supervisor() {
	homeManager.registerSupervisor(this);
}