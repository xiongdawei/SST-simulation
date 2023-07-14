import sst
cpu1 = sst.Component("cpu1", "cpuSimulation.cpu")
cpu2 = sst.Component("cpu2", "cpuSimulation.cpu")
# cpu3 = sst.Component("cpu3", "cpuSimulation.cpu")
# cpu4 = sst.Component("cpu4", "cpuSimulation.cpu")

params = {
        "eventsToSend" : 2,    # Required parameter, error if not provided
        "eventSize" : 2        # Optional parameter, defaults to 16 if not provided
}
cpu1.addParams(params)
cpu2.addParams(params)
# cpu3.addParams(params)
# cpu4.addParams(params)

link1 = sst.Link("cpu1_to_cpu2")
link2 = sst.Link("cpu2_to_cpu1")

# cpu1.addLink(link1, "right_port", "1ns")
# cpu2.addLink(link1, "left_port", "1ns")
# cpu2.addLink(link2, "right_port", "1ns")
# cpu3.addLink(link2, "left_port", "1ns")
# cpu2.addLink(link2, "right_port", "1ns")

link1.connect((cpu1, "right_port", "1ns"), (cpu2, "left_port", "1ns"))
link2.connect((cpu2, "right_port", "1ns"), (cpu1, "left_port", "1ns"))

