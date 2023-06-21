`timescale 1ns / 1ps

module ROM (
input [2:0] addr,
output reg [7:0] dataOut);

always @(*) begin
	case (addr)
		3'b000: dataOut <= 0;
		3'b001: dataOut <= 85;
		3'b010: dataOut <= 170;
		3'b011: dataOut <= 51;
		3'b100: dataOut <= 204;
		3'b101: dataOut <= 15;
		3'b110: dataOut <= 240;
		3'b111: dataOut <= 255;
	endcase
end
	
endmodule

module Difference_RAM (
	input mode,
	input [2:0] addr,
	input [7:0] dataIn,
	input [7:0] mask,
	input CLK,
	output reg [7:0] dataOut);
	
	reg [7:0] mem [0:7];
	
	// write your XOR_RAM code here
	initial begin
		dataOut <= 0;
		mem[0] <= 0;
		mem[1] <= 0;
		mem[2] <= 0;
		mem[3] <= 0;
		mem[4] <= 0;
		mem[5] <= 0;
		mem[6] <= 0;
		mem[7] <= 0;
	end

	always @(posedge CLK) begin
		if (mode == 0) begin // write mode
			mem[addr] <= (dataIn > mask) ? (dataIn - mask) : (mask - dataIn);	
		end
	end
	
	always @(*) begin
		if (mode) begin
			dataOut <= mem[addr];
		end
	end

endmodule


module EncodedMemory (
input mode,
input [2:0] index,
input [7:0] number,
input CLK,
output [7:0] result);

	wire [7:0] mask;

	ROM R(index, mask);
	Difference_RAM DR(mode, index, number, mask, CLK, result);

endmodule



