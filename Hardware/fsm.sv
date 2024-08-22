module fsm (
  input         clk,
  input         resetn,
  input [3:1] r,
  output reg [3:1] g
);

  // Define states
  typedef enum logic [1:0] { A, B, C, D } my_state;
  my_state current_state, next_state;

  // State transition
  always_ff @(posedge clk, negedge resetn) begin
    if (!resetn)  current_state <= A;
    else          current_state <= next_state;
  end

  // Next state logic
  always_comb begin
    case (current_state)
      A:  if(r == 3'b000)                       next_state = A;
          else if(r[1] == 1'b1)                 next_state = B;
          else if(r[1] == 1'b0 && r[2] == 1'b1) next_state = C;
          else if(r == 3'b100)                  next_state = D;
          else                                  next_state = A;

      B:  if(r[1] == 1'b1)  next_state = B;
          else              next_state = A;

      C:  if(r[2] == 1'b1)  next_state = C;
          else              next_state = A;

      D:  if(r[3] == 1'b1)  next_state = D;
          else              next_state = A;

      default:              next_state = A;
    endcase
  end

  // Output logic
  always_comb begin
    case (current_state)
      A:        g = 3'b000;
      B:        g = 3'b001;
      C:        g = 3'b010;
      D:        g = 3'b100;
      default:  g = 3'b000;
    endcase
  end

endmodule