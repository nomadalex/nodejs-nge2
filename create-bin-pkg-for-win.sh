#! /bin/bash

hashcode="`git log --pretty=format:"%h" -1`"
dir="nodejs-nge2-$hashcode"

if [ -d $dir ]; then
	rm -rf $dir
fi

mkdir $dir
cp -r res $dir
cp Win32Depends/bin/*.dll $dir
cp *.js $dir

mkdir -p $dir/build/Release
cp build/Release/node_nge2.node $dir/build/Release
