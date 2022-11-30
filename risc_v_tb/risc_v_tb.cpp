#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp" 
#include "Vrisc_v.h"
 
int main(int argc, char **argv, char **env) {
  int i; 
  int clk;   
  Verilated::commandArgs(argc, argv);
  
  Vrisc_v* top = new Vrisc_v;

  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  tfp->open ("risc_v.vcd");
 
  if (vbdOpen()!=1){
      return(-1);
  }

  vbdHeader("   R       a0 ");
  vbdSetMode(1); 
  
  top->clk = 1;
  top->rst = 0;

  for (int i=0; i<100; i++){                
    for (clk=0; clk<2; clk++){
        tfp->dump (2*i+clk);
        top->clk = !top->clk;
        top->eval ();
    }

    //reset feature using the toggle key on vbuddy
    if (vbdFlag()){  
      top->rst = 1;  
      vbdHex(4, top->rst & 0xF); //show rst value (on digit 4)
    }
    else{
      top->rst = 0;
      vbdHex(4, top->rst & 0xF); //show rst value (on digit 4)
    }

    vbdHex(1, top->a0 & 0xF); //showing output on TFT 7 segment display (on digit 1)
    vbdBar(top->a0 & 0xFF); //displaying 4-bit result on neopixel strip

    vbdCycle(i+1);
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q'))
    exit(0);
  }

  vbdClose();
  tfp->close();
  exit(0);
}
