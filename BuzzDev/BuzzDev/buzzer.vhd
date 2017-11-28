----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:22:57 11/27/2017 
-- Design Name: 
-- Module Name:    buzzer - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity buzzer is
  generic
  (
    C_NUM_REG                      : integer              := 2;
    C_SLV_DWIDTH                   : integer              := 32

  );
    Port ( vibrate : out  STD_LOGIC);
end buzzer;

architecture Behavioral of buzzer is
	signal Bus2IP_Clk : std_logic;
	signal Bus2IP_Resetn : std_logic;

  signal slv_reg0                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0); --control bits (bit 0 is buzz enable, bit 1 is reload)
  signal slv_reg1                       : std_logic_vector(C_SLV_DWIDTH-1 downto 0); --duration (how long to vibrate)
	signal timer : unsigned(31 downto 0) := (others => '0');
	signal buzzEnable : std_logic;
	signal reload : std_logic; --reset the timer to the value in reg1

begin

--	IP2Bus_Data <= slv_ip2bus_data when slv_read_ack = '1' else 
--									(others => '0');
--									
--	IP2Bus_WrAck <= slv_write_ack;
--	IP2Bus_RdAck <= slv_read_ack;
--	IP2Bus_Error <= '0';
	
	
	buzzEnable <= slv_reg0(0);
	reload <= slv_reg0(1);
	
	process (Bus2IP_Clk)
	begin
		if (Bus2IP_Resetn = '0') then --on reset (low asserted)
			timer <= (others => '0'); --set the timer to 0
		elsif Bus2IP_Clk 'event and Bus2IP_Clk = '1' then
			if (reload = '1') then
				timer <= unsigned(slv_reg1);
			elsif (buzzEnable = '1' and timer > 0) then
				timer <= timer - 1;
			else
				timer <= timer;
			end if;
		end if;
	end process;
	
	vibrate <= '1' when timer > 0 and buzzEnable = '1' else
						 '0';
		
	
	

end Behavioral;

