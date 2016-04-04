%---------------------------------------------------
%   DPA Attack on TivaC Power Traces
%   Authors: Justin Cox & Tyler Travis
%   Date: 04/02/16
%---------------------------------------------------

%File Parsing
numTracesPreAv = 199990;
numTraces = 10000;

%Load in Power Traces
traces = zeros(numTracesPreAv,2501);

for i = 1:numTracesPreAv 
    f=['../recs/sample' strrep(num2str(zeros(1,5-length(num2str(i)))), ' ', '') num2str(i) '.mat'];
	load(f);
    traces(i,:) = rec(1,:);
    disp(i);
end


%Take Averages to make 10,000 traces

traceAv = zeros(numTraces,2501);

for i = 1:20:numTracesPreAv
    if i == 199981
        traceAv(floor(i/20)+1,:) = mean(traces(i:i+9,:));
    else
        traceAv(floor(i/20)+1,:) = mean(traces(i:i+19,:));
    end
    disp(i);
    disp(floor(i/20));
end

clearvars('traces');
%Load input from files
file_xor_out = 'DES_c/pre-fp_text';
fileID = fopen(file_xor_out,'r');
dataArray = textscan(fileID, '%s%s','ReturnOnError', false);
left = uint32(hex2dec(dataArray{1,1}(:)));
right = uint32(hex2dec(dataArray{1,2}(:)));

fclose(fileID);

file_fFunction_out = 'DES_c/fFunction_output_text';
fileID = fopen(file_fFunction_out, 'r');
dataArray = textscan(fileID, '%s', 'Delimiter', ',', 'ReturnOnError', false);

fFunction_output = uint32(zeros(10000,64));

for i = 1:10000
    for j = 1:64
        fFunction_output(i,j) = uint32(hex2dec(dataArray{1,1}((i-1)*64+j)));
        fFunction_outputHEX(i,j) = dataArray{1,1}((i-1)*64+j);
    end
end

clearvars('dataArray');

fclose(fileID);

%Perform DPA
%   0xf0be2e5b242c
%   111100  001011  111000  101110  010110  110010  010000  101100
correctKey = [61 12 57 47 23 51 17 45];

for i = 1:10000
   traceAv(i,:) = traceAv(i,:) - mean(traceAv(i,:)); 
end

ave1 = zeros(64, 2501);
ave0 = zeros(64, 2501);

%sboxMask = uint32(hex2dec(['00808202' '40084010' '04010104' '80401040' '21040080' '10202008' '02100401' '08020820']));
%sboxBits = [9 13 24 26 8 4 32 5];

sboxBitsArray = [9 17 23 31; ...
                13 28 2 18; ...
                24 16 30 6; ...
                26 20 10 1; ...
                8 14 25 3; ...
                4 29 11 19; ...
                32 12 22 7; ...
                5 27 15 21];

dbit = uint32(zeros(10000, 64));
%sets = uint32(zeros(10000, 64));
setB1 = uint32(zeros(10000, 64));
setB2 = uint32(zeros(10000, 64));
setB3 = uint32(zeros(10000, 64));
setB4 = uint32(zeros(10000, 64));
for sbox = 1:8
    for key = 1:64
        disp(['Key: ' num2str(key)]);
        dbit(:,key) = bitxor(left(:), fFunction_output(:,key));
        setB1(:,key) = bitget(dbit(:,key), sboxBitsArray(sbox,1));
        setB2(:,key) = bitget(dbit(:,key), sboxBitsArray(sbox,2));
        setB3(:,key) = bitget(dbit(:,key), sboxBitsArray(sbox,3));
        setB4(:,key) = bitget(dbit(:,key), sboxBitsArray(sbox,4));
%        sets(:,key) = bitget(dbit(:,key), sboxBits(sbox));
%        size1 = sum(sets(:,key));
%        size0 = 10000 - size1;
%        S0 = zeros(size0,2501);
%        S1 = zeros(size1,2501);
        counter0 = 1;
        counter1 = 1;
        for i = 1:10000
            if (setB1(i,key) == 1 && setB2(i,key) == 1 && setB3(i,key) == 1 && setB4(i,key) == 1)
                S1(counter1,:) = traceAv(i,:);
                counter1 = counter1 + 1;
            elseif (setB1(i,key) == 0 && setB2(i,key) == 0 && setB3(i,key) == 0 && setB4(i,key) == 0)
                S0(counter0,:) = traceAv(i,:);
                counter0 = counter0 + 1;
            end
        end
        ave1(key,:) = mean(S1);
        ave0(key,:) = mean(S0);
    end
    
    switch sbox
        case 1
            sbox1_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox1 Done---');
        case 2
            sbox2_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox2 Done---');
        case 3
            sbox3_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox3 Done---');
        case 4
            sbox4_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox4 Done---');
        case 5
            sbox5_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox5 Done---');
        case 6
            sbox6_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox6 Done---');
        case 7
            sbox7_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox7 Done---');
        case 8
            sbox8_Res = ave1(:,:) - ave0(:,:);
            display('---Sbox8 Done---');
        otherwise
            display('Sbox error');
    end
end

clear S0 S1 ave0 ave1 counter0 counter1 dbit i key sets size0 size1 sbox;

%figure(1); plot(1:2501, sbox1_Res(:,:)); hold on; plot(1:2501, sbox1_Res(correctKey(1),:),'k-','LineWidth',3); hold off;

