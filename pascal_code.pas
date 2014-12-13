program all_sample;

var a,looper: integer;

procedure m0for;
    begin
        portc.0:=1;{first motor pin C1}
        delay_ms(1);   {1300 reverse  1500 stop 1700 forward}
        portc.0:=0;
        delay_ms(19); {rev<2000|for>3000}
    end;

procedure m0rev;
    begin
        portc.0:=1;{first motor pin C1}
        delay_ms(10);   {1300 reverse  1500 stop 1700 forward}
        portc.0:=0;
        delay_ms(10); {rev<2000|for>3000}
    end;
    
procedure m1for;
    begin
        portc.1:=1;{first motor pin C1}
        delay_ms(1);   {1300 reverse  1500 stop 1700 forward}
        portc.1:=0;
        delay_ms(19); {rev<2000|for>3000}
    end;
    
procedure m1rev;
    begin
        portc.1:=1;{first motor pin C1}
        delay_ms(10);   {1300 reverse  1500 stop 1700 forward}
        portc.1:=0;
        delay_ms(10); {rev<2000|for>3000}
    end;
//======================================================================
begin

TRISA:=255;
TRISB:=0;
TRISC:=0;
ANSEL:=0;
ANSELH:=0;
option_reg.7:=0;
portc:=0;
looper:=0;

repeat
   begin
        If (PortA.0=0) then
         begin
            m1for;
         end
        else
         begin
           m1rev;
         end;
        If (PortA.1=0) then
         begin
           m0rev;
         end
        else
         begin
           m0for;
        end;
    end;
 until looper=1;
end.