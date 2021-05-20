`timescale 1ns/1ps

module convenc_tb ();

    localparam integer K = 7; // constraint length
    localparam integer R = 2; // rate change

    logic           dv_in;
    logic           din;
    logic           dv_out;
    logic[1:0]      dout;

    localparam clk_period = 10; logic clk = 0; initial forever #(clk_period/2) clk = ~clk;

    convenc uut (.*);

    localparam Ndata = 120;
    logic[0:Ndata-1] din_array = 120'b11111111_11110000_11001100_10101010_00000000_00001111_00110011_01010101_11100011_11101100_11011111_10001010_00011100_00010011_01000000;

    initial begin
        dv_in = 0;
        din = 0;
        #(clk_period*10);

//        dv_in = 1;
//        din = 0;
//        #(clk_period*10);

        for (int i=0; i<Ndata; i++) begin
            dv_in = 1;
            din = din_array[i];
            #(clk_period*1);
        end

        dv_in = 1;
        din = 0;
        #(clk_period*10);
        
        $stop;
        
    end
    
    always_ff @(posedge clk) begin
        if (dv_out) begin
            $display("%b", dout[0]);
            $display("%b", dout[1]);
        end
    end

endmodule
