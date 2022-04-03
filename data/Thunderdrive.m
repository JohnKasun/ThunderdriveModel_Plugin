drive1 = load("drive1.txt");
drive2 = load("drive2.txt");
drive3 = load("drive3.txt");
drive4 = load("drive4.txt");

subplot(2,2,1);
plot(drive1);
title("0");

subplot(2,2,2);
plot(drive2);
title("0.33");

subplot(2,2,3);
plot(drive3);
title("0.66");

subplot(2,2,4);
plot(drive4);
title("1");
