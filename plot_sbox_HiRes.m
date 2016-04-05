load('sbox_HiRes_4bit.mat');

subplot(421); plot(1:1250, sbox1_Res(:,:)); hold on; plot(1:1250, sbox1_Res(correctKey(1),:),'k-','LineWidth',3); title('Sbox1'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(422); plot(1:1250, sbox2_Res(:,:)); hold on; plot(1:1250, sbox2_Res(correctKey(2),:),'k-','LineWidth',3); title('Sbox2'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(423); plot(1:1250, sbox3_Res(:,:)); hold on; plot(1:1250, sbox3_Res(correctKey(3),:),'k-','LineWidth',3); title('Sbox3'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(424); plot(1:1250, sbox4_Res(:,:)); hold on; plot(1:1250, sbox4_Res(correctKey(4),:),'k-','LineWidth',3); title('Sbox4'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(425); plot(1:1250, sbox5_Res(:,:)); hold on; plot(1:1250, sbox5_Res(correctKey(5),:),'k-','LineWidth',3); title('Sbox5'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(426); plot(1:1250, sbox6_Res(:,:)); hold on; plot(1:1250, sbox6_Res(correctKey(6),:),'k-','LineWidth',3); title('Sbox6'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(427); plot(1:1250, sbox7_Res(:,:)); hold on; plot(1:1250, sbox7_Res(correctKey(7),:),'k-','LineWidth',3); title('Sbox7'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);
subplot(428); plot(1:1250, sbox8_Res(:,:)); hold on; plot(1:1250, sbox8_Res(correctKey(8),:),'k-','LineWidth',3); title('Sbox8'); xlabel('Sample Point'); ylabel('Volts(mV)'); xlim([100 1110]);

