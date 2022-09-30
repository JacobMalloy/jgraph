#!/usr/bin/env bash
set -e
make spiro
rm -rf tmp_video
mkdir tmp_video
for j in 1 2 3 4 5;do
    i="0"
    while [ $i -le 10000 ] ; do
        cat input${j}.txt | sed "s/10000 10000/10000 $i/" |  ./spiro  | jgraph | convert -density 600 - tmp_video/$(printf "%02d%05d" $j $i).jpg &
        i=$(($i + 16))
    done;
done;

wait

ffmpeg -framerate 30 -pattern_type glob -i "tmp_video/*.jpg" -c:v libx264 -pix_fmt yuv420p -vf "pad=ceil(iw/2)*2:ceil(ih/2)*2" output.mp4
