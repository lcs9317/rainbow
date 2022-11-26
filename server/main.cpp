#include <QtGlobal>
#if QT_VERSION >= 0x050000
#include <QApplication>
#else
#include <QGuiApplication>
#endif
#include "mainwindow.h"
#include <aws/core/Aws.h>
#include <aws/sqs/SQSClient.h>
#include <aws/sqs/model/ReceiveMessageRequest.h>
#include <aws/sqs/model/ReceiveMessageResult.h>
#include <aws/sqs/model/DeleteMessageRequest.h>
#include <iostream>


void ReceiveMessage(const Aws::String& queue_url)
{

    Aws::Client::ClientConfiguration client_cfg;
    client_cfg.requestTimeoutMs = 30000;


    Aws::SQS::SQSClient sqs(client_cfg);

    Aws::SQS::Model::ReceiveMessageRequest rm_req;
    rm_req.SetQueueUrl(queue_url);
    rm_req.SetMaxNumberOfMessages(1);
     for(int i = 0; i < 3000; i++){
    auto rm_out = sqs.ReceiveMessage(rm_req);
    if (!rm_out.IsSuccess())
    {
        std::cout << "Error receiving message from queue " << queue_url << ": "
            << rm_out.GetError().GetMessage() << std::endl;
        return;
    }

    const auto& messages = rm_out.GetResult().GetMessages();
    if (messages.size() == 0)
    {
        std::cout << "No messages received from queue " << queue_url <<
            std::endl;
        return;
    }

    const auto& message = messages[0];
   // std::cout << "Received message:" << std::endl;
   // std::cout << "  MessageId: " << message.GetMessageId() << std::endl;
   // std::cout << "  ReceiptHandle: " << message.GetReceiptHandle() << std::endl;
    std::cout << "  message Body: " << message.GetBody() << std::endl << std::endl;

    Aws::SQS::Model::DeleteMessageRequest dm_req;
    dm_req.SetQueueUrl(queue_url);
    dm_req.SetReceiptHandle(message.GetReceiptHandle());

    auto dm_out = sqs.DeleteMessage(dm_req);
    if (dm_out.IsSuccess())
    {
        std::cout << "Successfully deleted message " << message.GetMessageId()
            << " from queue " << queue_url << std::endl;
    }
    else
    {
        std::cout << "Error deleting message " << message.GetMessageId() <<
            " from queue " << queue_url << ": " <<
            dm_out.GetError().GetMessage() << std::endl;
    }
    }

}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    argc = 2;
    argv[1] = "https://sqs.ap-northeast-1.amazonaws.com/567042749692/message";
    if (argc != 2)
    {
        std::cout << "Usage: receive_message <queue_url>" << std::endl;
        return 1;
    }

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        Aws::String queue_url = argv[1];

        ReceiveMessage(queue_url);
    }
    Aws::ShutdownAPI(options);


    return a.exec();
}
