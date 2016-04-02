%---------------------------------------------------
%   DPA Attack on TivaC Power Traces
%   Authors: Justin Cox & Tyler Travis
%   Date: 04/02/16
%---------------------------------------------------

%File Parsing
numTracesPreAv = 199990;
numTraces = 10000;

%Load in Power Traces
traces = zeros(numTracesPreAv,2500);

for i = 1:numTracesPreAv 
    f=['../recs/recs/' strrep(num2str(zeros(1,5-length(num2str(i)))), ' ', '') num2str(i) '.mat'];
	load(f);
    traces(i,:) = rec(1,:);
end

%Take Averages to make 10,000 traces

%Load input from files

%Perform DPA