# Overview
This code shows how to call opencv and tesseract remotely by using gRPC. 

# Libraries
- gRPC
- Tesseract

# Build
## 1. Install gRPC
## 2. Install Tesseract
### 2-1. Tesseract needs below
- Leptonica
- libjpeg
- libtiff
- libpng
- libssl-dev

## 3. Protoc : generate source files
```protoc --proto_path=./protos recognizer.proto --cpp_out=./ --grpc_out=./ --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin```

## 4. Download Tesseract TrainedData
```wget https://github.com/tesseract-ocr/tessdata/blob/main/eng.traineddata?raw=true```
Put the file tessdata/ or set TESSDATA_PREFIX environment variable.

# Run
```./recognizer_async_server```

```Tesseract Base API Load Successfully
Server listening on 0.0.0.0:50051```

```./recognizer_client img/hey1219.png```

```OCR RESULT:HEY
1219```