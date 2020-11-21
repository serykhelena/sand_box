global dat
delete(instrfind);
dat = serial('COM6', 'BaudRate', 115200);
dat.InputBufferSize = 4096;

fopen(dat);
set(dat, 'ByteOrder', 'littleEndian')

disp 'Ok!'

start = 'p';     % start 
fwrite(dat, start, 'uint8'); 
disp 'start!'
A = [];
B = [];

t1 = 8;

for i = 1:t1
   A=fread(dat, [100,1], 'float32');
   B = [B; A];
end
 


fclose(dat);
disp 'Finish!'

X = [];
Y = [];

for i = 1: 1: length(B)
    if mod(i, 2) == 0
        Y = [Y; B(i, 1)];
    else
        X = [X; B(i, 1)];
    end 
end 

plot(X, Y)

% 
% CNTRL = [];
% SPEED = []; 
% for i = 1: 1: length(B)
%     
%     CNTRL = [CNTRL; B(i, 1)];
% end
% % CNTRL = CNTRL./100;
% % for r = 2: 2:length(B)
% %    SPEED = [SPEED; B(r, 1)]; 
% % end
% % 
% % plot(CNTRL)
% % grid on 
% % hold on
% % plot(SPEED)
% 
% plot(B)
grid on

