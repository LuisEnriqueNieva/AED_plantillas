module cordic (
    input  wire clk,
    input  wire reset,
    input  wire start,
    input  wire [1:0] angle_in,
    output reg  [1:0] cos_out,
    output reg  [1:0] sin_out,
    output reg  done
);
    parameter N=16;  
    localparam IDLE=2'b00;
    localparam INIT=2'b01;
    localparam ITERATE=2'b10;
    localparam DONE=2'b11;

    reg [1:0] state, next_state;
    reg [4:0] i;  

    always @(posedge clk or posedge reset) begin
        if (reset)
            state <= IDLE;
        else
            state <= next_state;
    end

    always @(*) begin
        case (state)
            IDLE:    next_state = start ? INIT : IDLE;
            INIT:    next_state = ITERATE;
            ITERATE: next_state = (i == N-1) ? DONE : ITERATE;
            DONE:    next_state = start ? INIT : DONE;
            default: next_state = IDLE;
        endcase
    end

endmodule
