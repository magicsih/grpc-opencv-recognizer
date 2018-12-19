FROM ubuntu
LABEL maintainer="Ilhwan Seo <sih@netmarble.com>"

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y autoconf automake libtool
RUN apt-get install -y pkg-config
RUN apt-get install -y libpng-dev
RUN apt-get install -y libjpeg8-dev
RUN apt-get install -y libtiff5-dev
RUN apt-get install -y zlib1g-dev
RUN apt-get install -y libleptonica-dev
RUN apt-get install -y git
RUN apt-get install -y wget
RUN apt-get install -y build-essential autoconf libtool pkg-config
RUN apt-get install -y libgflags-dev libgtest-dev
RUN apt-get install -y clang libc++-dev
RUN apt-get install -y curl unzip

RUN cd /usr/local/src && git clone --depth 1 --recursive https://github.com/grpc/grpc
RUN cd /usr/local/src/grpc && make && make DESTDIR=/usr/local install

RUN cd /usr/local/src && git clone --depth 1 --recursive https://github.com/protocolbuffers/protobuf.git
RUN cd /usr/local/src/protobuf && ./autogen.sh && ./configure --prefix=/usr/local && make && make install

RUN cd /usr/local/src && wget https://github.com/tesseract-ocr/tesseract/archive/4.0.0.zip && unzip 4.0.0.zip
RUN cd /usr/local/src/tesseract-4.0.0 && ./autogen.sh && ./configure --prefix=/usr/local && make && make install
RUN ldconfig

ADD . /grpc-opencv-recognizer
WORKDIR /grpc-opencv-recognizer

RUN make clean
RUN make recognizer_async_server
RUN ./recognizer_async_server
