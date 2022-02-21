/******************************************************* 
* Jesus Ortiz
* Senior Design 2022 - Team 22: Galactic Space Flames
* Wheel Rotary Encoder Receiver
* 
* For use with rotary Quadrature Encoders
* Assumes that Pulse order is A-B for forward
*
*******************************************************/*

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_signed.all;
use IEEE.std_logic_unsigned.all; 

entity EncoderReceiver is

generic (
    CLK_freq : natural := 25000000
    );

port (

--inputs
    sysclk : in std_logic;
	 A_pulse, B_pulse : in std_logic := '0'; --quadrature inputs
--outputs
    speed : out unsigned (7 downto 0); --rotational velocity per tenth of second
    latch : out std_logic; --signals to report updated data
	 dir : out std_logic --wheel turn direct 0 is forward 1 is backward
	 );
    
end EncoderReceiver;


architecture arch_EncoderReceiver of EncoderReceiver is
   
	signal wheel_dir : std_logic := '0';      
	type list is array (7 downto 0) of natural;
	signal speed_list : list; --array used for speed averaging

begin
	 
--   the following tracks the pulses and checks direction 
--   and averages wheel rotational speed 
count : process(A_pulse,B_pulse,sysclk)

    variable pulse_counter,clk_counter : natural;
	 variable old_wheel_dir : std_logic := '0';-- previous whhel direction
	 variable scratch01 : unsigned(15 downto 0);--scratch variable for conversion
	 variable scratch02 : natural;--scratch variable for conversion
begin


	if rising_edge(A_pulse) then
		pulse_counter := pulse_counter + 1;
		old_wheel_dir := wheel_dir;
		if B_pulse = '1' then --Check if Pulse B rose first first
			wheel_dir <= '1';
		else
			wheel_dir <= '0';
		end if;
		if clk_counter = 0 then
			pulse_counter := 0;
		end if;
	end if;


	if falling_edge(sysclk) then
		clk_counter := clk_counter + 1;
		
		if old_wheel_dir /= wheel_dir then --check for rotational direction change
			clk_counter := 0; --the wheel changed directions so reset the counter
		end if;
		
	
		case clk_counter is
			when 250000 =>
				latch <= '0';
			when 2500000 => --sample taken every 10th of seccond 
				speed_list(6 downto 0) <= speed_list(7 downto 1);
				speed_list(7) <= pulse_counter;
				scratch02 := (speed_list(7) + speed_list(6) + speed_list(5) + speed_list(4) + speed_list(3) + speed_list(2) + speed_list(1) + speed_list(0)) / 8;
				speed <= to_unsigned(scratch02,8);
				latch <= '1';
				clk_counter := 0;
			when others =>
		end case;
	end if;
	
end process;     

end arch_EncoderReceiver;
