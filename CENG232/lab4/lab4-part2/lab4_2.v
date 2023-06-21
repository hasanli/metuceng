`timescale 1ns / 1ps
module SelectionOfAvatar(
	input [1:0] mode,
	input [5:0] userID,
	input [1:0] candidate, // 00:Air 01:Fire, 10:Earth, 11: Water
	input CLK,
	output reg [1:0] ballotBoxId,
	output reg [5:0] numberOfRegisteredVoters,
	output reg [5:0] numberOfVotesWinner, // number of votes of winner
	output reg [1:0] WinnerId,
	output reg AlreadyRegistered,
	output reg AlreadyVoted,
	output reg NotRegistered,
	output reg VotingHasNotStarted,
	output reg RegistrationHasEnded
	);

	reg [7:0] counter;
	reg box [0:1][0:3][0:15];
	reg [5:0] winnerCount [0:3];
	
	initial begin
		counter = 0;
		AlreadyRegistered = 0;
		AlreadyVoted = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0;
		numberOfRegisteredVoters = 0;
		winnerCount[0] = 0;
		winnerCount[1] = 0;
		winnerCount[2] = 0;
		winnerCount[3] = 0;
		numberOfVotesWinner = 0; // number of votes of winner
		WinnerId = 0;
	end

	always @(posedge CLK)
	begin
	
		AlreadyRegistered = 0;
		AlreadyVoted = 0;
		NotRegistered = 0;
		VotingHasNotStarted = 0;
		RegistrationHasEnded = 0;
		
		ballotBoxId = userID[5:4];

		counter = counter + 1;

		if (counter < 101) begin //Reg process
			if (mode == 0) begin
				if (box[0][ballotBoxId][userID[3:0]] == 1) begin
					AlreadyRegistered = 1;
				end
				else begin
					box[0][ballotBoxId][userID[3:0]] = 1;
					numberOfRegisteredVoters = numberOfRegisteredVoters + 1;
				end
			end
			
			else begin
				VotingHasNotStarted = 1;
			end
		end
		
		else if (counter > 100 && counter < 201) begin //Vote process
			if (mode == 1) begin
				if (box[0][ballotBoxId][userID[3:0]] == 1) begin
					if (box[1][ballotBoxId][userID[3:0]] == 1) begin
						AlreadyVoted = 1;
					end
					else begin
						winnerCount[candidate] = winnerCount[candidate] + 1;
						box[1][ballotBoxId][userID[3:0]] = 1;
					end
				end
				else begin
					NotRegistered = 1;
				end
			end
			else begin
				RegistrationHasEnded = 1;
			end
		end
		
		else begin //Res process
			if(winnerCount[0] > winnerCount[1]
			&& winnerCount[0] > winnerCount[2]
			&& winnerCount[0] > winnerCount[3]) begin
				WinnerId <= 0;
				numberOfVotesWinner <= winnerCount[0];
			end
			else if(winnerCount[1] > winnerCount[0]
				  && winnerCount[1] > winnerCount[2]
				  && winnerCount[1] > winnerCount[3]) begin
				  WinnerId <= 1;
				  numberOfVotesWinner <= winnerCount[1];
			end
			else if(winnerCount[2] > winnerCount[0]
				  && winnerCount[2] > winnerCount[1]
			 	  && winnerCount[2] > winnerCount[3]) begin
				  WinnerId <= 2;
				  numberOfVotesWinner <= winnerCount[2];
			end
			else if(winnerCount[3] > winnerCount[0]
				  && winnerCount[3] > winnerCount[1]
				  && winnerCount[3] > winnerCount[2]) begin
				  WinnerId <= 3;
				  numberOfVotesWinner <= winnerCount[3];
			end
		end
		
	end

endmodule
