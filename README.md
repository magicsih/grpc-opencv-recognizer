# gRPC-based Template Matching and OCR Server with OpenCV

This repository contains a gRPC-based server and client for template matching and Optical Character Recognition (OCR) using OpenCV and Tesseract OCR.

## Features

- gRPC server and client for efficient and scalable communication.
- Template matching functionality using OpenCV.
- OCR functionality using Tesseract OCR.
- Cross-platform compatibility.

## Dependencies

- gRPC (https://grpc.io/)
- OpenCV (https://opencv.org/)
- Tesseract OCR (https://tesseract-ocr.github.io/)
- Leptonica (http://leptonica.org/)

## Demo
![grpcserver](https://user-images.githubusercontent.com/2772002/138396107-3a1141dd-74d8-47b8-bd0d-c40e7686a447.gif)

## Run the server:
```bash
./recognizer_async_server
Tesseract Base API Load Successfully
Server listening on 0.0.0.0:50051
```
## Run the client with an image file as an argument:
```bash
./recognizer_client img/hey1219.png
OCR RESULT:HEY
1219
```

## Target Image
![target](https://github.com/magicsih/grpc-opencv-recognizer/blob/master/img/hey1219.png)

## Server Implementation (recognizer_async_server.cc)
The server is implemented in C++ and exposes two gRPC services: MatchTemplate for template matching and RecognizeOpticalCharacters for OCR. The server initializes Tesseract OCR with the given language data and processes incoming requests.

## Client Implementation (recognizer_client.cc)
The client is also implemented in C++ and communicates with the server using gRPC. The client reads the image file, sends it to the server, and receives the OCR result.

## Build
### 1. Install gRPC
### 2. Install Tesseract
#### 2-1. Tesseract needs below
- Leptonica
- libjpeg
- libtiff
- libpng
- libssl-dev

### 3. Protoc : generate source files
```bash
protoc --proto_path=./protos recognizer.proto --cpp_out=./ --grpc_out=./ --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin
```

### 4. Download Tesseract TrainedData
```bash
wget https://github.com/tesseract-ocr/tessdata/blob/main/eng.traineddata?raw=true
```
Put the file tessdata/ or set TESSDATA_PREFIX environment variable.

# License
This project is licensed under the terms of the MIT license.
