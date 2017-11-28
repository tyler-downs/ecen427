wave add / -radix bin
isim force add Bus2IP_Clk 1 -value 0 -time 10 ns -repeat 20 ns

#reset
put Bus2IP_Resetn 0
put slv_reg0 00000000000000000000000000000000
put slv_reg1 00000000000000000000000000000000
run 200 ns

put Bus2IP_Resetn 1

#set duration, nothing should change except reg value
put slv_reg1 00000000000000000000000000000100
run 200 ns

#load register. Timer should load value but not count down
put slv_reg0 00000000000000000000000000000010
run 200 ns

#enable buzzer. Should vibrate but not count down
put slv_reg0 00000000000000000000000000000011
run 200 ns

#disable load. Should count down and buzz until it reaches 0.
put slv_reg0 00000000000000000000000000000001
run 200 ns

#reload timer
put slv_reg0 00000000000000000000000000000010
run 200 ns

#start counting down
put slv_reg0 00000000000000000000000000000001
run 40 ns

#stop in the middle. Output should turn off
put slv_reg0 00000000000000000000000000000000
run 200 ns

#let finish
put slv_reg0 00000000000000000000000000000001
run 200 ns