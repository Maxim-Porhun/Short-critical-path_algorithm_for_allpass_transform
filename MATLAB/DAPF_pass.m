function [v1,v2] = DAPF_pass(x,alpha)
%APC_DIRECT_FORM

N = length(x);
v1 = zeros(1,N);
v2 = zeros(1,N);

w1 = 0;
w2 = 0;
for n=1:N
    [w2, w1, v2(n), v1(n)] = DAPF(w2, w1, x(n), alpha);
end

end

