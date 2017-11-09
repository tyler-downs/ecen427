wave add / -radix bin
isim force add Bus2IP_Clk 1 -value 0 -time 10 ns -repeat 20 ns

#reset
put Bus2IP_Resetn 0
put slv_reg0 00000000000000000000000000000111
put slv_reg1 00000000000000000000000000001010
run 200 ns

#normal operation
put Bus2IP_Resetn 1
run 500 ns

#decrement disabled
put slv_reg0 00000000000000000000000000000110
run 100 ns

#interrupt disabled
put slv_reg0 00000000000000000000000000000101
run 500 ns

#reload disabled
put slv_reg0 00000000000000000000000000000011
run 500 ns

#reload and interrupt disabled
put slv_reg0 00000000000000000000000000000001
run 100 ns