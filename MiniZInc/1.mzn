int: nc = 10000;
int: uno = 1;

var 1..nc: A;   var 1..nc: B;  var 1..nc: C;   var 1..nc: D;
var 1..nc: E;  var 1..nc: F;   var 1..nc: G;   var 1..nc: H;
var 1..nc: I;

constraint (A/(B*C))+(D/(E*F))+(G/(H*I)) == uno;
constraint A != B;
constraint A != C;
constraint A != D;
constraint A != E;
constraint A != F;
constraint A != G;
constraint A != H;
constraint A != I;
constraint B != C; 
constraint B != D;
constraint B != E;
constraint B != F;
constraint B != G;
constraint B != H;
constraint B != I;
constraint C != D;
constraint C != E;
constraint C != F;
constraint C != G;
constraint C != H;
constraint C != I;
constraint D != E;
constraint D != F;
constraint D != G;
constraint D != H;
constraint D != I;
constraint E != F;
constraint E != G;
constraint E != H;
constraint E != I;
constraint F != G;
constraint F != H;
constraint F != I;
constraint G != H;
constraint G != I;
constraint H != I;
solve satisfy;

output ["A=", show(A), "\t B=", show(B), 
        "\t C=", show(C), "\n", "D=", show(D),  
        "\t E=", show(E), "\t F=", show(F), "\n",
         "G=", show(G),"\t H=", show(H), "\t I=", show(I), "\n",];
