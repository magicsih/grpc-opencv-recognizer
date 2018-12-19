#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <streambuf>

#include <grpcpp/grpcpp.h>

#include "recognizer.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using recognizer::Matcher;
using recognizer::MatchTemplateRequest;
using recognizer::MatchTemplateReply;
using recognizer::FeatureShape;
using recognizer::OcrRequest;
using recognizer::OcrReply;

class MatcherClient {
    public:
        MatcherClient(std::shared_ptr<Channel> channel)
            : stub_(Matcher::NewStub(channel)) {}
    
    void MatchTemplate() {
        MatchTemplateRequest request;
        
        MatchTemplateReply reply;
        ClientContext context;
        stub_ ->MatchTemplate(&context, request, &reply);
    }

    //void RecognizeOpticalCharacters(::grpc::ClientContext* context, ::recognizer::OcrReply* response, ::grpc::experimental::ClientWriteReactor< ::recognizer::OcrRequest>* reactor) 
    std::string RecognizeOpticalCharacters(std::string filePath) {
        OcrRequest request;

        std::ifstream t(filePath);
        std::string str((std::istreambuf_iterator<char>(t)),
                 std::istreambuf_iterator<char>());
        t.close();

        request.set_image(str);

        OcrReply reply;
        ClientContext context;
        
        Status status = stub_->RecognizeOpticalCharacters(&context, request, &reply);
        
        if (status.ok()) {
            return reply.result();
        } else {
        std::cout << status.error_code() << ": " << status.error_message()
                    << std::endl;
        return "RPC failed";
        }
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

    private:
        std::unique_ptr<Matcher::Stub> stub_;
};

int main(int argc, char** argv) {
    MatcherClient matcher(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    std::cout << "Input file path:" << argv[1] << std::endl;
    std::string result = matcher.RecognizeOpticalCharacters(argv[1]);
    std::cout << "OCR RESULT:" << result << std::endl;
}