x = [1 zeros(1,50)];
n = 0:length(x)-1;

N = 16; % APC length
Ln = length(x);

alpha = 0.4;

[y] = apc_direct_form(x,alpha);

v = x;
for k = 1:N
    v = allpass_direct_form(v,alpha);    
end
v_N_APF = v;

v = x;
for k = 1:N/2
    [v1,v2] = DAPF_pass(v,alpha);
    v = v2;
end
v_N_DAPF = v;

figure;
subplot(311);
stem(n,v_N_APF,"filled",'LineWidth',1.5);
title('Output signal of APC based on direct form of allpass filter');
grid minor;
xlabel('$$n$$','interp','latex');
ylabel('$$v_{16}(n)$$','interp','latex');
set(gca, 'FontName', 'Times New Roman');
set(gca, 'FontSize', 14);

subplot(312);
stem(n,v_N_DAPF,"filled",'LineWidth',1.5);
title('Output signal of APC based on dual allpass filter');
grid minor;
xlabel('$$n$$','interp','latex');
ylabel('$$v_{16}(n)$$','interp','latex');
set(gca, 'FontName', 'Times New Roman');
set(gca, 'FontSize', 14);

subplot(313);
stem(n,v_N_APF-v_N_DAPF,"filled",'LineWidth',1.5);
title('Signals difference');
grid minor;
xlabel('$$n$$','interp','latex');
ylabel('$$v_{16}(n)$$','interp','latex');
set(gca, 'FontName', 'Times New Roman');
set(gca, 'FontSize', 14);