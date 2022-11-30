#include "aws.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

int droneDB(){
    char name[3][20] = {"drone", "drone_key", "5"};
    std::ofstream ofs;

    ofs.open("../output.txt", std::ios::trunc | std::ios::out | std::ios::in);
    Aws::SDKOptions options;

    Aws::InitAPI(options);
    {
        const Aws::String table =  name[0];
        const Aws::String key  = name[1];
        const Aws::String keyval = name[2];


        Aws::Client::ClientConfiguration clientConfig;
        Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
        Aws::DynamoDB::Model::GetItemRequest req;


        req.SetTableName(table);
        Aws::DynamoDB::Model::AttributeValue hashKey;
        hashKey.SetS(keyval);
        req.AddKey(key, hashKey);

        const Aws::DynamoDB::Model::GetItemOutcome& result = dynamoClient.GetItem(req);
        if (result.IsSuccess())
        {

            const Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>& item = result.GetResult().GetItem();
            if (item.size() > 0)
            {
                for (const auto& i : item){
                    if(i.first == "drone_key"){
                        ofs << i.second.GetS();
                        continue;
                    }
                    ofs  << i.second.GetN() << std::endl;

                     //   ofs << i.first << ": " << i.second.GetN() << std::endl;


                }

            }
            else
            {
                std::cout << "No item found with the key " << key << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get item: " << result.GetError().GetMessage();
        }

    }
    ofs.close();
    Aws::ShutdownAPI(options);
        return 0;
}

void ReceiveMessage(const Aws::String& queue_url)
{

    std::ofstream ofs;

    ofs.open("../from_message.txt",  std::ios::out | std::ios::in);

    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
    Aws::String queue_url = "https://sqs.ap-northeast-1.amazonaws.com/567042749692/message";

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
    std::cout << "  message Body: " << message.GetBody() << std::endl << std::endl;
    ofs<< message.GetBody() ;

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
    ofs.close();
    Aws::ShutdownAPI(options);
}

