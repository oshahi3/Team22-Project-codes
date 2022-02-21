/******************************************************* 
* Jesus Ortiz
* Senior Design 2022 - Team 22: Galactic Space Flames
* Motor Control Signal Generator
* 
* Generates PWM and direction signals for the motor controller
* given a throttle value.
*
*******************************************************/*

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_signed.all;
use IEEE.std_logic_unsigned.all; 


--This is the PWM signal encoder for the motor control signal.
--The pulse frequencyc is 2KHz


entity MotorControllerPWM is

port (

--inputs

    sysCLK : in std_logic := '0';--system clock input
	 data_input : in unsigned(7 downto 0) := "00000000"; --data input for direction and throttle
--outputs
    
    dir_out : out std_logic := '0'; --direction out, 0 = forward
	 pwm_out : out std_logic := '0'  --output PWM signal
	 );
    
end MotorControllerPWM;


architecture arch_MotorControllerPWM of MotorControllerPWM is
	
begin
dir_out <= data_input(7);
 -- we're assuming a pwm frequency of 2KHz which is equivelent to 
 -- 12,500 sys_clock pulses per cycle.  The means that each 1% interval
 -- for duty cycle is a 125 sys_clock pulses difference for on time.


	 
PWM_encode : process(sysCLK, data_input)
	 variable clk_count : integer := 0;
	 variable on_percent,interval_count : natural range 0 to 127 := 0; 
    variable scratch01 : unsigned(15 downto 0); 
	 variable scratch02 : natural;
begin

on_percent := to_integer(data_input(6 downto 0)); --the throttle is bits 6 doownto 0 of the data input

if on_percent > 100 then --make sure throttle is never greater than 100%
	on_percent := 100;
end if;

--counting the 1% intervals
if falling_edge(sysCLK) then
	 if (clk_count >= (124)) then
  		if interval_count = 99 then
			interval_count := 0;
		else
			interval_count := interval_count + 1;
		end if;
		clk_count := 0;
    else
		clk_count := clk_count + 1;
	 end if;
end if;

if (interval_count <= on_percent) then
	pwm_out <= '1';
else
	pwm_out <= '0';
end if;


end process;     
	
end arch_MotorControllerPWM;
