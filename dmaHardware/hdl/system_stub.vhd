-------------------------------------------------------------------------------
-- system_stub.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

entity system_stub is
  port (
    zio : inout std_logic;
    rzq : inout std_logic;
    mcbx_dram_we_n : out std_logic;
    mcbx_dram_udqs_n : inout std_logic;
    mcbx_dram_udqs : inout std_logic;
    mcbx_dram_udm : out std_logic;
    mcbx_dram_ras_n : out std_logic;
    mcbx_dram_odt : out std_logic;
    mcbx_dram_ldm : out std_logic;
    mcbx_dram_dqs_n : inout std_logic;
    mcbx_dram_dqs : inout std_logic;
    mcbx_dram_dq : inout std_logic_vector(15 downto 0);
    mcbx_dram_clk_n : out std_logic;
    mcbx_dram_clk : out std_logic;
    mcbx_dram_cke : out std_logic;
    mcbx_dram_cas_n : out std_logic;
    mcbx_dram_ba : out std_logic_vector(2 downto 0);
    mcbx_dram_addr : out std_logic_vector(12 downto 0);
    RS232_Uart_1_sout : out std_logic;
    RS232_Uart_1_sin : in std_logic;
    RESET : in std_logic;
    Push_Buttons_5Bits_TRI_I : in std_logic_vector(0 to 4);
    LEDs_8Bits_TRI_O : out std_logic_vector(7 downto 0);
    GCLK : in std_logic;
    DIP_Switches_8Bits_TRI_I : in std_logic_vector(7 downto 0)
  );
end system_stub;

architecture STRUCTURE of system_stub is

  component system is
    port (
      zio : inout std_logic;
      rzq : inout std_logic;
      mcbx_dram_we_n : out std_logic;
      mcbx_dram_udqs_n : inout std_logic;
      mcbx_dram_udqs : inout std_logic;
      mcbx_dram_udm : out std_logic;
      mcbx_dram_ras_n : out std_logic;
      mcbx_dram_odt : out std_logic;
      mcbx_dram_ldm : out std_logic;
      mcbx_dram_dqs_n : inout std_logic;
      mcbx_dram_dqs : inout std_logic;
      mcbx_dram_dq : inout std_logic_vector(15 downto 0);
      mcbx_dram_clk_n : out std_logic;
      mcbx_dram_clk : out std_logic;
      mcbx_dram_cke : out std_logic;
      mcbx_dram_cas_n : out std_logic;
      mcbx_dram_ba : out std_logic_vector(2 downto 0);
      mcbx_dram_addr : out std_logic_vector(12 downto 0);
      RS232_Uart_1_sout : out std_logic;
      RS232_Uart_1_sin : in std_logic;
      RESET : in std_logic;
      Push_Buttons_5Bits_TRI_I : in std_logic_vector(0 to 4);
      LEDs_8Bits_TRI_O : out std_logic_vector(7 downto 0);
      GCLK : in std_logic;
      DIP_Switches_8Bits_TRI_I : in std_logic_vector(7 downto 0)
    );
  end component;

  attribute BOX_TYPE : STRING;
  attribute BOX_TYPE of system : component is "user_black_box";

begin

  system_i : system
    port map (
      zio => zio,
      rzq => rzq,
      mcbx_dram_we_n => mcbx_dram_we_n,
      mcbx_dram_udqs_n => mcbx_dram_udqs_n,
      mcbx_dram_udqs => mcbx_dram_udqs,
      mcbx_dram_udm => mcbx_dram_udm,
      mcbx_dram_ras_n => mcbx_dram_ras_n,
      mcbx_dram_odt => mcbx_dram_odt,
      mcbx_dram_ldm => mcbx_dram_ldm,
      mcbx_dram_dqs_n => mcbx_dram_dqs_n,
      mcbx_dram_dqs => mcbx_dram_dqs,
      mcbx_dram_dq => mcbx_dram_dq,
      mcbx_dram_clk_n => mcbx_dram_clk_n,
      mcbx_dram_clk => mcbx_dram_clk,
      mcbx_dram_cke => mcbx_dram_cke,
      mcbx_dram_cas_n => mcbx_dram_cas_n,
      mcbx_dram_ba => mcbx_dram_ba,
      mcbx_dram_addr => mcbx_dram_addr,
      RS232_Uart_1_sout => RS232_Uart_1_sout,
      RS232_Uart_1_sin => RS232_Uart_1_sin,
      RESET => RESET,
      Push_Buttons_5Bits_TRI_I => Push_Buttons_5Bits_TRI_I,
      LEDs_8Bits_TRI_O => LEDs_8Bits_TRI_O,
      GCLK => GCLK,
      DIP_Switches_8Bits_TRI_I => DIP_Switches_8Bits_TRI_I
    );

end architecture STRUCTURE;

