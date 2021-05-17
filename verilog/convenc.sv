// a simple half rate convolutional encoder for the purpose of understanding the appendix D tables in the Galileo ICD.
module convenc #(
    parameter integer K = 7,                // constraint length
    parameter integer R = 2                 // rate change
) (
    input   logic[K-1:0]    G[R-1:0],  // the polynomials
    // 1st polynomial //G1 = 171 octal = 1111001 = 121 decimal
    // 2nd polynomial //G2 = 133 octal = 1011011 =  91 decimal
    input   logic           clk,
    input   logic           dv_in,
    input   logic           din,
    output  logic           dv_out,
    output  logic[1:0]      dout
);

    logic[K-1:0] shreg = 0;
    logic dv_in_reg = 0;
    always_ff @(posedge clk) begin
    
        if (dv_in) begin
            shreg <= {din, shreg[K-1:1]};  // shift in on msb
        end
        
        for (int i=0; i<R; i++) begin
            dout[i] <= ^(G[i]&shreg);
        end
        
        dv_in_reg <= dv_in;
        dv_out <= dv_in_reg;
    end

endmodule
