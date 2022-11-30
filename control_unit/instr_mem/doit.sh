#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f instr_mem.vcd

# run Verilator to translate Verilog into C++, including C++ testbench
verilator -Wall --cc --trace instr_mem.sv --exe instr_mem_tb.cpp

# build C++ project via make automatically generated by Verilator
make -j -C obj_dir/ -f Vinstr_mem.mk Vinstr_mem

# run executable simulation file
obj_dir/Vinstr_mem
