#pragma once

#include "taos_option.h"
#include "taos_result.h"
#include <string_view>

class TAOSClient
{
public:
    TAOSClient(const TAOSOption &option);
    ~TAOSClient();

    bool       Connect();
    bool       IsConnected() const;
    void       Close();
    TAOSResult Query(std::string_view sql);
    void       Execute(std::string_view sql);
    int        SelectDB(std::string_view db);
    TAOSResult Insert(std::string_view tb, std::string_view cols, std::string_view values);
    TAOSResult Update(std::string_view tb, std::string_view cols, std::string_view values);
    TAOSResult Delete(std::string_view tb, std::string_view cols, std::string_view values);
    TAOSResult Select(std::string_view tb, std::string_view cols, std::string_view values);

private:
    TAOSOption option_;
    TAOS      *taos_;
    bool       connected_{false};
};
