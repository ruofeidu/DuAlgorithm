# !/bin/sh
# sh gifit.sh FILENAME
# Reference: http://blog.pkh.me/p/21-high-quality-gif-with-ffmpeg.html
start_time=0:0
duration=17
palette="/tmp/palette.png"
filters="fps=15,scale=320:-1:flags=lanczos"
ffmpeg -v warning --s $start_time -t $duration -i $1.mp4 -vf "$filters,palettegen" -y $palette
ffmpeg -v warning --s $start_time -t $duration -i $1.mp4 -i $palette -lavfi "$filters [x]; [x][1:v] paletteuse" -y $1.gif

