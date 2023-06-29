function [w2_n, w1_n, v2_n, v1_n] = DAPF(w2_nM1, w1_nM1, v0_n, alpha)
    
    % Precomputations
    A = alpha*alpha;
    B = 1 - alpha*alpha;
    C = -alpha*(1 - alpha*alpha);

    % 1st level
	r1 = v0_n * A;
	r2 = v0_n * alpha;
	r3 = w1_nM1 * B;
	r4 = w1_nM1 * alpha;
	r5 = w1_nM1 * C;
	r6 = w2_nM1 * alpha;				
	r7 = w2_nM1 * B;						

	% 2nd level
	r3   = r3 - r2;
	r1   = r1 + r5;		
	w1_n = r4 + v0_n;

	% 3rd level		
	r1   = r1 + r7;			
	w2_n = r3 + r6;

	% Store
	v1_n = r3;
	v2_n = r1;
end