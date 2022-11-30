module risc_v (
    input logic clk,
    input logic rst,
    output logic [3:0] a0
);

logic [3:0] sreg;

always_ff @ (posedge clk, posedge rst)
    if(rst)
        sreg <= 4'b1;
    else 
        sreg <= {sreg[2:0], sreg[3] ^ sreg[2]};
assign a0 = sreg;

endmodule
