begin=$1
end=$2
dirbegin=$(((begin/100)*100))
dirend=$((dirbegin+99))
dirname=`pwd`/../yukicoder/${dirbegin}-${dirend}
mkdir -p $dirname
cd $dirname
for i in `seq ${begin} ${end}`
do
filename=${i}.cpp
if [ ! -e filename ]; then
    cat ../../solver/F.cpp > $filename
fi
done
