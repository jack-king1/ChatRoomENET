//
// Created by huxy on 07/03/19.
//

#ifndef PROJECT_CHATMSG_H
#define PROJECT_CHATMSG_H

#include <chrono>
#include <iostream>


class ChatMsg
{
public:
    ChatMsg(std::string user,
            std::string msg,
            time_t time = std::time(nullptr));

    ChatMsg(const char* data);

    ~ChatMsg() = default;
    char* data(unsigned int& size) const;
    const std::string& getMsg() const;
    const std::string& getUsername() const;
    const std::time_t& getStamp() const;

private:
    std::string msg_text;
    std::string username;
    std::time_t timestamp;
};

#endif //PROJECT_CHATMSG_H
