clear;
[y, fs] = audioread( 'gliss.m4a' );
y = y(:,1); % just one channelG
writematrix(y,'gliss.txt')
N = length( y );
nFFT = 1024; % This can be changed for better/worse resolution
hop = floor( nFFT / 4 );
nFrames = floor( N / hop ) - 1; % approximately
%printf("%d frames.\n", nFrames);
F = zeros( nFFT, nFrames );
w = hanning( nFFT ); % Window choice, again, this can be changed
for n = 1:nFrames
iStart = (n-1) * hop;
if iStart+nFFT > N, break; end
F(:, n) = fft( w .* y(iStart+1 : iStart+nFFT) );
G(:, n) = 20*log10(abs(F(1:nFFT/2, n)));
end