This is the source code I use to play the video "bad apple" that has been downscaled to a resolution of 16x16 using ffmpeg, the video is then played on four MAX7219 8x8 matrix display configured in a 2x2 setting.
Any video can be played using this code as long as it fulfills these requirements:
  1. it's in a 16x16 resolution.
  2. the video only has two colors on it (black and white for example).

This code is then uploaded to a microcontroller, here I am using an ESP 32 due to it having a sufficient amount of memory to support both the video file and the code.
