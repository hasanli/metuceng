`timescale 1ns / 1ps

module lab3_2(
			input[5:0] money,
			input CLK,
			input vm, //0:VM0, 1:VM1
			input [2:0] productID, //000:sandwich, 001:chocolate, 11x: dont care
			input sugar, //0: No sugar, 1: With Sugar
			output reg [5:0] moneyLeft,
			output reg [4:0] itemLeft,
			output reg productUnavailable,//1:show warning, 0:do not show warning
			output reg insufficientFund , //1:full, 0:not full
			output reg notExactFund , //1:full, 0:not full
			output reg invalidProduct, //1: empty, 0:not empty
			output reg sugarUnsuitable, //1: empty, 0:not empty
			output reg productReady	//1:door is open, 0:closed
	);

	// Internal State of the Module
	// (you can change this but you probably need this)
	reg [4:0] numOfSandwiches = 10;
	reg [4:0] numOfChocolate = 10;
	reg [4:0] numOfWaterVM1 = 5;
	reg [4:0] numOfWaterVM2 = 10;
	reg [4:0] numOfCoffee = 10;
	reg [4:0] numOfTea = 10;

	initial
	begin
		productUnavailable = 0;
		insufficientFund = 0;
		notExactFund = 0;
		invalidProduct = 0;
		sugarUnsuitable = 0;
		productReady = 0;
	end

	//Modify the lines below to implement your design
	always @(posedge CLK)
	begin
		productUnavailable = 0;
		insufficientFund = 0;
		notExactFund = 0;
		invalidProduct = 0;
		sugarUnsuitable = 0;
		productReady = 0;
		moneyLeft = money;
		if(vm == 0) begin
			if(productID == 0 || productID == 1 || productID == 2) begin
				if(productID == 0) begin
					if(numOfSandwiches == 0) begin
						productUnavailable = 1;
					end
					else begin
						if(money == 20) begin
							productReady = 1;
							itemLeft = numOfSandwiches - 1;
							numOfSandwiches = numOfSandwiches - 1;
							moneyLeft = 0;
						end
						else begin
							notExactFund = 1;
						end
					end
				end
				else if(productID == 1) begin
					if(numOfChocolate == 0) begin
						productUnavailable = 1;
					end
					else begin
						if(money == 10) begin
							productReady = 1;
							itemLeft = numOfChocolate - 1;
							numOfChocolate = numOfChocolate - 1;
							moneyLeft = 0;
						end
						else begin
							notExactFund = 1;
						end
					end
				end
				else if(productID == 2) begin
					if(numOfWaterVM1 == 0) begin
						productUnavailable = 1;
					end
					else begin
						if(money == 5) begin
							productReady = 1;
							itemLeft = numOfWaterVM1 - 1;
							numOfWaterVM1 = numOfWaterVM1 - 1;
							moneyLeft = 0;
						end
						else begin
							notExactFund = 1;
						end
					end
				end
			end
			else begin
				invalidProduct = 1;
			end
		end
		else if(vm == 1) begin
			if(productID == 2 || productID == 3 || productID == 4) begin
				if(productID == 2) begin
					if(numOfWaterVM2 == 0) begin
						productUnavailable = 1;
					end
					else begin
							if(sugar == 1) 
								begin
								sugarUnsuitable = 1;
								end
							else 
								begin
								if(money < 5) begin
									insufficientFund = 1;
								end
								else begin
									productReady = 1;
									itemLeft = numOfWaterVM2 - 1;
									numOfWaterVM2 = numOfWaterVM2 - 1;
									moneyLeft = money - 5;
								end
							end
						end
					end
				if(productID == 3) begin
					if(numOfCoffee == 0) begin
						productUnavailable = 1;
					end
					else begin
						if(money < 12) begin
							insufficientFund = 1;
						end
						else begin
							productReady = 1;
							itemLeft = numOfCoffee - 1;
							numOfCoffee = numOfCoffee - 1;
							moneyLeft = money - 12;
						end
					end
				end
				if(productID == 4) begin
					if(numOfTea == 0) begin
						productUnavailable = 1;
					end
					else begin
						if(money < 8) begin
							insufficientFund = 1;
						end
						else begin
							productReady = 1;
							itemLeft = numOfTea - 1;
							numOfTea = numOfTea - 1;
							moneyLeft = money - 8;
						end
					end
				end
			end
			else begin
				invalidProduct = 1;
			end
		end
	end
endmodule