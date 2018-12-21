#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include "recognizer.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using recognizer::Matcher;
using recognizer::MatchTemplateRequest;
using recognizer::MatchTemplateReply;
using recognizer::FeatureShape;
using recognizer::OcrRequest;
using recognizer::OcrReply;

// Logic and data behind the server's behavior.
class MatcherServiceImpl final : public Matcher::Service {

  public:
    void LoadTesseract(void);
  private:
    tesseract::TessBaseAPI *tesseractApi;

  Status RecognizeOpticalCharacters(ServerContext* context, const OcrRequest* request, OcrReply* reply) override {
    std::cout << "RecognizeOpticalCharacters..." << std::endl;

    const l_uint8 * data = reinterpret_cast<const l_uint8 *>(request->image().c_str());
    Pix *image = pixReadMem(data, request->image().size());
    if(!image) {
      return Status::CANCELLED;
    }

    tesseractApi->SetImage(image);

    char *outText = tesseractApi->GetUTF8Text();

    std::cout << "OCR Output:" << outText << std::endl;
    reply->set_result(outText);
    
    delete [] outText;
    pixDestroy(&image);

    return Status::OK;
  }

  Status MatchTemplate(ServerContext* context, const MatchTemplateRequest* request, MatchTemplateReply* reply) override {
    return Status::OK;
  }
};

void MatcherServiceImpl::LoadTesseract(void) {
    tesseractApi = new tesseract::TessBaseAPI();
    if(tesseractApi->Init("tessdata/", "eng")) {
      std::cerr << "Couldn't initialize tesseract." << std::endl;
      exit(1);
    }
    tesseractApi->SetVariable("enable_new_segsearch","0"); //Enable new segmentation search path. It could solve the problem of dividing one character to two characters
    std::cout << "Tesseract Base API Load Successfully" << std::endl;
  }

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MatcherServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  service.LoadTesseract();
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}