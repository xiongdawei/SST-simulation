import sst
cpu1 = sst.Component("cpu1", "cpuSimulation.cpu")
cpu2 = sst.Component("cpu2", "cpuSimulation.cpu")
cpu3 = sst.Component("cpu3", "cpuSimulation.cpu")
cpu4 = sst.Component("cpu4", "cpuSimulation.cpu")

params = {
        "eventsToSend" : 1,    # Required parameter, error if not provided
        "eventSize" : 10,
        "ShowRes" : 1 
              # Optional parameter, defaults to 16 if not provided
}
cpu1.addParams(params)
cpu2.addParams(params)
cpu3.addParams(params)
params_showData = {
        "eventsToSend" : 2,    # Required parameter, error if not provided
        "eventSize" : 10,
        "ShowRes" : 1
}
cpu4.addParams(params_showData)

link1 = sst.Link("cpu1_to_cpu2")
link2 = sst.Link("cpu2_to_cpu3")
link3 = sst.Link("cpu3_to_cpu4")
link4 = sst.Link("cpu4_to_cpu1")

link1.connect((cpu1, "right_port", "1ns"), (cpu2, "left_port", "1ns"))
link2.connect((cpu2, "bottom_port", "1ns"), (cpu4, "top_port", "1ns"))
link3.connect((cpu4, "left_port", "1ns"), (cpu3, "right_port", "1ns"))
link4.connect((cpu3, "top_port", "1ns"), (cpu1, "bottom_port", "1ns"))

# cpu0 - cpu1
#   |     |
# cpu2 - cpu3
#



