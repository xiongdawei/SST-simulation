import sst

obj = sst.Component("cpuSimulation", "cpuSimulation.cpuSimulation")
obj.addParams({
    "printFrequency" : "5",
    "repeats" : "25"
    })

cpu_to_memory = sst.Link("cpu_to_memory")


