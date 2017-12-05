wave add / -radix bin
isim force add Bus2IP_Clk 1 -value 0 -time 10 ns -repeat 20 ns

#reset
put Bus2IP_Resetn 0
put slv_reg0 00000000000000000000000000000F00
put slv_reg1 000000000000000000000000000F0000
put slv_reg2 00000000000000000000000000000005
put slv_reg3 00000000000000000000000000000000
run 200 ns

put Bus2IP_Resetn 1
