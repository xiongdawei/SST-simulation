import sst
import sst.macro
from sst.macro import Interconnect

link_bw="12.5GB/s"
link_lat="100ns"
logpParams = {
  "bandwidth" : "12.5GB/s",
  "hop_latency" : "100ns",
  "out_in_latency" : "1.2us",
}

swParams = {
  "name" : "pisces",
  "mtu" : "4KB",
  "arbitrator" : "cut_through",
  "router" : {
    "name"     :     "torus_minimal",
  },
  "link" : {
    "bandwidth" : link_bw,
    "latency" : link_lat,
    "credits" : "128KB",
  },
  "xbar" : {
    "bandwidth" : "1000GB/s",
    "latency" : "10ns",
  },
  "logp" : logpParams,
}

mpiParams = {
 "max_vshort_msg_size" : 4096,
 "max_eager_msg_size" : 64000,
 "post_header_delay" : "0.35906660us",
 "post_rdma_delay" : "0.88178612us",
 "rdma_pin_latency" : "5.42639881us",
 "rdma_page_delay" : "50.50000000ns",
}

appParams = {
  "allocation" : "hostname",
  "indexing" : "hostname",
  "exe" : "halo3d-26",
  "argv" : "-pex 4 -pey 4 -pez 4 -nx 128 -ny 128 -nz 128 -sleep 0 -iterations 10",
  "launch_cmd" : "aprun -n 64 -N 1",
  "allocation" : "first_available",
  "indexing" : "block",
  "mpi" : mpiParams,
}

memParams = {
 "name" : "pisces",
 "latency" : "10ns",
 "total_bandwidth" : "100GB/s",
 "max_single_bandwidth" : "11.20GB/s",
}

nicParams = {
  "name" : "pisces",
  "injection" : {
    "mtu" : "4KB",
    "redundant" : 8,
    "bandwidth" : "13.04GB/s",
    "arbitrator" : "cut_through",
    "latency" : "0.6us",
    "credits" : "128KB",
  },
  "ejection" : {
    "latency" : link_lat,
  },  
}

nodeParams = {
  "memory" : memParams,
  "nic" : nicParams,
  "app1" : appParams,
  "name" : "simple",
  "proc" : {
    "frequency" : "2GHz",
    "ncores" : "4",
  }
}

topoParams = {
 "name" : "torus,
 "geometry" : "[4,4,4]",
}

params = {
  "node" : nodeParams,
  "switch" : swParams,
  "topology" : topoParams,
}

ic = Interconnect(params)
ic.build()