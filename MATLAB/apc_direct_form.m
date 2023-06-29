function [y] = apc_direct_form(x,alpha)
%APC_DIRECT_FORM

N = length(x);
y = zeros(1,N);
y_nm1 = 0;
x_nm1 = 0;

for n=1:N
    y(n) = x_nm1 + alpha*(x(n)-y_nm1);
    
    % update
    y_nm1 = y(n);
    x_nm1 = x(n);
end

end

