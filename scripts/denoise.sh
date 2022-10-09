#!/bin/bash
dir=$(dirname $1)
name=$(basename $dir .png)
convert -endian lsb $1 "${dir}/temp.pfm"
oidnDenoise -hdr "${dir}/temp.pfm" -o "${dir}/temp2.pfm"
convert "${dir}/temp2.pfm" "${dir}/${name}-f.png"
rm "${dir}/temp.pfm"
rm "${dir}/temp2.pfm"
