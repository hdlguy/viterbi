clear;

k = 7;   % constraint length
G1 = [ 1 1 1 1 0 0 1 ];  % octal 171  (data shifts in on left)
G2 = [ 1 0 1 1 0 1 1 ];  % octal 133

%s = zeros(N,1);
%s(1:10) = [0 0 1 0 0 0 1 0 0 0];

str1 = "111111111111000011001100101010100000000000001111001100110101010111100011111011001101111110001010000111000001001101000000";

s = char(num2cell(str1)); 
s = reshape(str2num(s),1,[]);
s = transpose(s);
N = length(s);

p =     zeros(N,2);
state = zeros(N,k);

for i=1:N-1
    p(i,1) = mod(sum(and(G1, state(i,:))),2);
    p(i,2) = mod(sum(and(G2, state(i,:))),2);
    state(i+1,:) = [s(i) state(i,1:(k-1))];
endfor

p2 = reshape(transpose(p), 2*N,1);  % multiplex the two convolver outputs.
p2(1:40)'
