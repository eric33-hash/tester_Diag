function make_archive() {

tar -zxvf libpcap-1.10.4.tar.gz
cd libpcap-1.10.4

OUTPUT=$(pwd)/install
if [ -d $OUTPUT ]; then
    rm -r $OUTPUT
fi
mkdir $OUTPUT

echo $OUTPUT

export PATH=$PATH:/usr/bin

./configure --prefix=$OUTPUT    \
    --disable-static 

make && make install

cp -r ./install ../

}

make_archive



