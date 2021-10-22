FROM ubuntu
LABEL maintainer="Ilhwan Seo <wellknowngeek@gmail.com>"

RUN apt-get update
RUN apt-get install -y \
    g++ autoconf automake libtool build-essential pkg-config libc++-dev \
    libgflags-dev libgtest-dev \
    libpng-dev libjpeg8-dev libtiff5-dev \
    zlib1g-dev \
    libleptonica-dev \
    git wget curl unzip \
    libpthread-stubs0-dev

RUN cd /usr/local/src && git clone --depth 1 --recursive https://github.com/grpc/grpc
RUN cd /usr/local/src/grpc && make && make DESTDIR=/usr/local install && cd /usr/local/src/grpc/third_party/protobuf && make install

RUN cd /usr/local/src && wget https://github.com/tesseract-ocr/tesseract/archive/4.0.0.zip && unzip 4.0.0.zip
RUN cd /usr/local/src/tesseract-4.0.0 && ./autogen.sh && ./configure --prefix=/usr/local && make && make install
RUN ldconfig

ADD . /grpc-opencv-recognizer
WORKDIR /grpc-opencv-recognizer