--Asynchronus emory Read/Write 

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_signed.all;
use IEEE.std_logic_unsigned.all; 

entity RegisterBlock is

port (

--state inputs
	 data_latch : in std_logic := '0'; --data manager enables latch when operation is ready
	 
--input and output register info	 
	 address : in std_logic_vector(7 downto 0) := x"00";--address to read/write to
	 data : inout std_logic_vector(7 downto 0) := x"00";--data read or written to above address
	 
    op_type : in std_logic := '0';  -- operation ID from data manager: 0 is write operation, 1 is read operation
	 
--block status outputs
	 ready : buffer std_logic := '1';
);    
end RegisterBlock;


architecture arch_RegisterBlock of RegisterBlock is
   
	type mem is array (127 downto 0)of std_logic_vector(7 downto 0);
	signal mem_page1 : mem; --one page, 128 regs, 8 bits each      
	
begin



jetson_readwrite_process : process(data_latch)
begin

if rising_edge(data_latch) then
	ready <= '0';
	if op_type = '0' then
		mem_page1(to_integer(unsigned(address))) <= data;
	elsif op_type = '1' then
		data <= mem_page1(to_integer(unsigned(address)));
	end if;
	ready <= '1';
end if;

end process;     
	
end arch_RegisterBlock;
