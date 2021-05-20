// a simple half rate convolutional encoder for the purpose of understanding the appendix D tables in the Galileo ICD.
module convenc (
    input   logic           clk,
    input   logic           dv_in,
    input   logic           din,
    output  logic           dv_out,
    output  logic[1:0]      dout
);

    localparam integer K = 7;               // constraint length
    localparam integer R = 2;               // rate change
    localparam logic[6:0] G1 = 7'b1111001;  // 1st polynomial //G1 = 171 octal = 1111001 = 121 decimal
    localparam logic[6:0] G2 = 7'b1011011;  // 2nd polynomial //G2 = 133 octal = 1011011 =  91 decimal

    logic[K-1:0] shreg = 0;
    logic dv_in_reg = 0;
    always_ff @(posedge clk) begin
    
        if (dv_in) begin
            shreg <= {din, shreg[K-1:1]};  // shift in on msb
        end
        
        dout[0] <=  ^(G1&shreg);
        dout[1] <= ~^(G2&shreg); // note inversion
        
        dv_in_reg <= dv_in;
        dv_out <= dv_in_reg;
        
    end

endmodule
