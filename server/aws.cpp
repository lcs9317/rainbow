#include "aws.h"


int droneDB(){
    char name[3][20] = {"coordinate", "drone_key", "1"};
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
                    if(i.first == "drone_key")
                        continue;

                    std::cout <<  i.first << ": " << i.second.GetN() << std::endl;

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
    Aws::ShutdownAPI(options);
        return 0;
}