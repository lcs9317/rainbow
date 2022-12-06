#include "aws.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

int droneDB(){
    char name[3][20] = {"drones", "drone_key", "5"};
    std::ofstream ofs;
    int i = 0;
    ofs.open("../output.txt", std::ios::trunc | std::ios::out | std::ios::in);
    Aws::SDKOptions options;
    for(i = 1; i <= 100; i ++){
    Aws::InitAPI(options);
    {

        sprintf(name[2],"%d",i);
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

                    ofs  << i.second.GetS() << std::endl;

                     //   ofs << i.first << ": " << i.second.GetN() << std::endl;


                }

            }
            else
            {
                continue;
                std::cout << "No item found with the key " << key << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to get item: " << result.GetError().GetMessage();
        }

    }


    Aws::ShutdownAPI(options);
    }
    ofs.close();
        return 0;
}
