//
// Created by huxy on 07/03/19.
//
#include <cstring>
#include <ChatMsg.h>

ChatMsg::ChatMsg(std::string user,
                 std::string msg, std::time_t stamp)
        : username(user), msg_text(msg), timestamp(stamp)
{

}

ChatMsg::ChatMsg(const char* data) {
    username = (reinterpret_cast<const char *>(data));
    msg_text = (reinterpret_cast<const char *>(data +
                                               username.length() + 1));
    auto stamp_loc = data
                     + (username.length() + 1)
                     + (msg_text.length() + 1);
    memcpy(&timestamp, stamp_loc, sizeof(std::time_t));
}

const std::string &ChatMsg::getMsg() const {
    return msg_text;
}


const std::time_t &ChatMsg::getStamp() const {
    return timestamp;
}

const std::string &ChatMsg::getUsername() const
{
    return username;
}

char* ChatMsg::data(unsigned int& size) const {
    const int username_length = username.length() + 1;
    const int txt_length = msg_text.length() + 1;
    const int timestamp_size = sizeof(std::time_t);
    size = username_length + txt_length + timestamp_size;
    char *data = new char[size];
    memcpy((void *) &data[0],
           username.data(), username_length);
    memcpy((void *) &data[username_length],
           msg_text.data(), txt_length);
    memcpy((void *) &data[username_length + txt_length],
           (void *) &timestamp, timestamp_size);
    return data;
}
