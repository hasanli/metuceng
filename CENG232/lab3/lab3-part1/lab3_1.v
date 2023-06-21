`timescale 1ns / 1ps

module bh(input B, input H, input clk, output reg Q);

    initial begin
        Q = 1;
    end

	// You can implement your code here
    // ...
	 always@(posedge clk)
	 begin
		case({B, H})
			2'b00: Q <= ~Q;
			2'b01: Q <= 1;
			2'b10: Q <= 0;
			2'b11: Q <= Q;
			default: Q <= 1'bx;
		endcase
	 end

endmodule

module ic1337(// Inputs
              input A0,
              input A1,
              input A2,
              input clk,
              // Outputs
              output Q0,
              output Q1,
              output Z);

	// You can implement your code here
    // ...
		wire R1 = ((A0 ^ ~A1) | A2);
		wire R2 = (A0 & ~A2);
		wire R3 = (~(~A0 | A1) & A2);
		
		bh ff1(R1, R2, clk, Q0);
		bh ff2(R2, R3, clk, Q1);
		assign Z = ~(Q0 ^ Q1);
endmodule