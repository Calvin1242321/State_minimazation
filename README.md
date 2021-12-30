# State_minimazation
digital logic design-project4  

format of input
  
    .start_kiss  
    .i 1  
    .o 1  
    .p 14  
    .s 7  
    .r a  
    0 a a 0  
    1 a b 0  
    0 b c 0
    1 b d 0
    0 c a 0
    1 c d 0
    0 d e 0
    1 d f 1
    0 e a 0
    1 e f 1
    0 f g 0
    1 f f 1
    0 g a 0
    1 g f 1
    .end_kiss

format of output ( dot )  
  
    digraph STG{
        rankdir = LR;
        INIT[shape = point];
        a [label="a"];
        b [label="b"];
        c [label="c"];
        f [label="f"];
        g [label="g"];

        INIT -> a;
        a -> a [label="0/0"];
        a -> b [label="1/0"];
        b -> c [label="0/0"];
        b -> f [label="1/0"];
        c -> a [label="0/0"];
        c -> f [label="1/0"];
        f -> g [label="0/0"];
        f -> f [label="1/1"];
        g -> a [label="0/0"];
        g -> f [label="1/1"];
    }


