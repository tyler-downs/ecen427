-------------------------------------------------------------------------------
-- dma_controller_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library dma_controller_v1_00_a;
use dma_controller_v1_00_a.all;

entity dma_controller_0_wrapper is
  port (
    S_AXI_ACLK : in std_logic;
    S_AXI_ARESETN : in std_logic;
    S_AXI_AWADDR : in std_logic_vector(31 downto 0);
    S_AXI_AWVALID : in std_logic;
    S_AXI_WDATA : in std_logic_vector(31 downto 0);
    S_AXI_WSTRB : in std_logic_vector(3 downto 0);
    S_AXI_WVALID : in std_logic;
    S_AXI_BREADY : in std_logic;
    S_AXI_ARADDR : in std_logic_vector(31 downto 0);
    S_AXI_ARVALID : in std_logic;
    S_AXI_RREADY : in std_logic;
    S_AXI_ARREADY : out std_logic;
    S_AXI_RDATA : out std_logic_vector(31 downto 0);
    S_AXI_RRESP : out std_logic_vector(1 downto 0);
    S_AXI_RVALID : out std_logic;
    S_AXI_WREADY : out std_logic;
    S_AXI_BRESP : out std_logic_vector(1 downto 0);
    S_AXI_BVALID : out std_logic;
    S_AXI_AWREADY : out std_logic;
    m_axi_lite_aclk : in std_logic;
    m_axi_lite_aresetn : in std_logic;
    md_error : out std_logic;
    m_axi_lite_arready : in std_logic;
    m_axi_lite_arvalid : out std_logic;
    m_axi_lite_araddr : out std_logic_vector(31 downto 0);
    m_axi_lite_arprot : out std_logic_vector(2 downto 0);
    m_axi_lite_rready : out std_logic;
    m_axi_lite_rvalid : in std_logic;
    m_axi_lite_rdata : in std_logic_vector(31 downto 0);
    m_axi_lite_rresp : in std_logic_vector(1 downto 0);
    m_axi_lite_awready : in std_logic;
    m_axi_lite_awvalid : out std_logic;
    m_axi_lite_awaddr : out std_logic_vector(31 downto 0);
    m_axi_lite_awprot : out std_logic_vector(2 downto 0);
    m_axi_lite_wready : in std_logic;
    m_axi_lite_wvalid : out std_logic;
    m_axi_lite_wdata : out std_logic_vector(31 downto 0);
    m_axi_lite_wstrb : out std_logic_vector(3 downto 0);
    m_axi_lite_bready : out std_logic;
    m_axi_lite_bvalid : in std_logic;
    m_axi_lite_bresp : in std_logic_vector(1 downto 0)
  );
end dma_controller_0_wrapper;

architecture STRUCTURE of dma_controller_0_wrapper is

  component dma_controller is
    generic (
      C_S_AXI_DATA_WIDTH : INTEGER;
      C_S_AXI_ADDR_WIDTH : INTEGER;
      C_S_AXI_MIN_SIZE : std_logic_vector;
      C_USE_WSTRB : INTEGER;
      C_DPHASE_TIMEOUT : INTEGER;
      C_BASEADDR : std_logic_vector;
      C_HIGHADDR : std_logic_vector;
      C_FAMILY : STRING;
      C_NUM_REG : INTEGER;
      C_NUM_MEM : INTEGER;
      C_SLV_AWIDTH : INTEGER;
      C_SLV_DWIDTH : INTEGER;
      C_M_AXI_LITE_ADDR_WIDTH : INTEGER;
      C_M_AXI_LITE_DATA_WIDTH : INTEGER
    );
    port (
      S_AXI_ACLK : in std_logic;
      S_AXI_ARESETN : in std_logic;
      S_AXI_AWADDR : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      S_AXI_AWVALID : in std_logic;
      S_AXI_WDATA : in std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      S_AXI_WSTRB : in std_logic_vector(((C_S_AXI_DATA_WIDTH/8)-1) downto 0);
      S_AXI_WVALID : in std_logic;
      S_AXI_BREADY : in std_logic;
      S_AXI_ARADDR : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      S_AXI_ARVALID : in std_logic;
      S_AXI_RREADY : in std_logic;
      S_AXI_ARREADY : out std_logic;
      S_AXI_RDATA : out std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      S_AXI_RRESP : out std_logic_vector(1 downto 0);
      S_AXI_RVALID : out std_logic;
      S_AXI_WREADY : out std_logic;
      S_AXI_BRESP : out std_logic_vector(1 downto 0);
      S_AXI_BVALID : out std_logic;
      S_AXI_AWREADY : out std_logic;
      m_axi_lite_aclk : in std_logic;
      m_axi_lite_aresetn : in std_logic;
      md_error : out std_logic;
      m_axi_lite_arready : in std_logic;
      m_axi_lite_arvalid : out std_logic;
      m_axi_lite_araddr : out std_logic_vector((C_M_AXI_LITE_ADDR_WIDTH-1) downto 0);
      m_axi_lite_arprot : out std_logic_vector(2 downto 0);
      m_axi_lite_rready : out std_logic;
      m_axi_lite_rvalid : in std_logic;
      m_axi_lite_rdata : in std_logic_vector((C_M_AXI_LITE_DATA_WIDTH-1) downto 0);
      m_axi_lite_rresp : in std_logic_vector(1 downto 0);
      m_axi_lite_awready : in std_logic;
      m_axi_lite_awvalid : out std_logic;
      m_axi_lite_awaddr : out std_logic_vector((C_M_AXI_LITE_ADDR_WIDTH-1) downto 0);
      m_axi_lite_awprot : out std_logic_vector(2 downto 0);
      m_axi_lite_wready : in std_logic;
      m_axi_lite_wvalid : out std_logic;
      m_axi_lite_wdata : out std_logic_vector((C_M_AXI_LITE_DATA_WIDTH-1) downto 0);
      m_axi_lite_wstrb : out std_logic_vector(((C_M_AXI_LITE_DATA_WIDTH/8)-1) downto 0);
      m_axi_lite_bready : out std_logic;
      m_axi_lite_bvalid : in std_logic;
      m_axi_lite_bresp : in std_logic_vector(1 downto 0)
    );
  end component;

begin

  dma_controller_0 : dma_controller
    generic map (
      C_S_AXI_DATA_WIDTH => 32,
      C_S_AXI_ADDR_WIDTH => 32,
      C_S_AXI_MIN_SIZE => X"000001ff",
      C_USE_WSTRB => 0,
      C_DPHASE_TIMEOUT => 8,
      C_BASEADDR => X"77e00000",
      C_HIGHADDR => X"77e0ffff",
      C_FAMILY => "spartan6",
      C_NUM_REG => 7,
      C_NUM_MEM => 1,
      C_SLV_AWIDTH => 32,
      C_SLV_DWIDTH => 32,
      C_M_AXI_LITE_ADDR_WIDTH => 32,
      C_M_AXI_LITE_DATA_WIDTH => 32
    )
    port map (
      S_AXI_ACLK => S_AXI_ACLK,
      S_AXI_ARESETN => S_AXI_ARESETN,
      S_AXI_AWADDR => S_AXI_AWADDR,
      S_AXI_AWVALID => S_AXI_AWVALID,
      S_AXI_WDATA => S_AXI_WDATA,
      S_AXI_WSTRB => S_AXI_WSTRB,
      S_AXI_WVALID => S_AXI_WVALID,
      S_AXI_BREADY => S_AXI_BREADY,
      S_AXI_ARADDR => S_AXI_ARADDR,
      S_AXI_ARVALID => S_AXI_ARVALID,
      S_AXI_RREADY => S_AXI_RREADY,
      S_AXI_ARREADY => S_AXI_ARREADY,
      S_AXI_RDATA => S_AXI_RDATA,
      S_AXI_RRESP => S_AXI_RRESP,
      S_AXI_RVALID => S_AXI_RVALID,
      S_AXI_WREADY => S_AXI_WREADY,
      S_AXI_BRESP => S_AXI_BRESP,
      S_AXI_BVALID => S_AXI_BVALID,
      S_AXI_AWREADY => S_AXI_AWREADY,
      m_axi_lite_aclk => m_axi_lite_aclk,
      m_axi_lite_aresetn => m_axi_lite_aresetn,
      md_error => md_error,
      m_axi_lite_arready => m_axi_lite_arready,
      m_axi_lite_arvalid => m_axi_lite_arvalid,
      m_axi_lite_araddr => m_axi_lite_araddr,
      m_axi_lite_arprot => m_axi_lite_arprot,
      m_axi_lite_rready => m_axi_lite_rready,
      m_axi_lite_rvalid => m_axi_lite_rvalid,
      m_axi_lite_rdata => m_axi_lite_rdata,
      m_axi_lite_rresp => m_axi_lite_rresp,
      m_axi_lite_awready => m_axi_lite_awready,
      m_axi_lite_awvalid => m_axi_lite_awvalid,
      m_axi_lite_awaddr => m_axi_lite_awaddr,
      m_axi_lite_awprot => m_axi_lite_awprot,
      m_axi_lite_wready => m_axi_lite_wready,
      m_axi_lite_wvalid => m_axi_lite_wvalid,
      m_axi_lite_wdata => m_axi_lite_wdata,
      m_axi_lite_wstrb => m_axi_lite_wstrb,
      m_axi_lite_bready => m_axi_lite_bready,
      m_axi_lite_bvalid => m_axi_lite_bvalid,
      m_axi_lite_bresp => m_axi_lite_bresp
    );

end architecture STRUCTURE;

