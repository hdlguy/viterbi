`timescale 1ns/1ps

module convenc_tb ();

    localparam integer K = 7; // constraint length
    localparam integer R = 2; // rate change

    logic[K-1:0]    G[R-1:0]; // the polynomials
    logic           dv_in;
    logic           din;
    logic           dv_out;
    logic[1:0]      dout;

    localparam clk_period = 10; logic clk = 0; initial forever #(clk_period/2) clk = ~clk;

    convenc #(.K(K), .R(R)) uut (.*);

    assign G[0] = 7'b111_1001; // 1st polynomial //G1 = 171 octal = 1111001 = 121 decimal
    assign G[1] = 7'b101_1011; // 2nd polynomial //G2 = 133 octal = 1011011 =  91 decimal

    localparam Ndata = 120;
    logic[0:Ndata-1] din_array = 120'b11111111_11110000_11001100_10101010_00000000_00001111_00110011_01010101_11100011_11101100_11011111_10001010_00011100_00010011_01000000;

    initial begin
        dv_in = 0;
        din = 0;
        #(clk_period*10);

        forever begin
            dv_in = 1;
            din = 0;
            #(clk_period*10);

            for (int i=0; i<Ndata; i++) begin
                dv_in = 1;
                din = din_array[i];
                #(clk_period*1);
            end

            dv_in = 1;
            din = 0;
            #(clk_period*10);
        end
    end
    
    always_ff @(posedge clk) begin
        if (dv_out) begin
            $display("%b", dout[0]);
            $display("%b", dout[1]);
        end
    end

endmodule
