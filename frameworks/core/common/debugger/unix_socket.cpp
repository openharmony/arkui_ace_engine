/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "frameworks/core/common/debugger/unix_socket.h"

#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

#include "base/log/log.h"
#include "securec.h"

namespace OHOS::Ace {
static constexpr uint32_t SLEEP_TIME_MS = 500U;
static constexpr int CONTROL_SOCK_SEND_TIMEOUT = 10U;

int32_t UnixSocketClient::UnixSocketConn()
{
    uint32_t sleep_ms = SLEEP_TIME_MS;
    char destBuff[BUFF_SIZE];
    const uint32_t SLEEP_MAX_MS = 4 * SLEEP_TIME_MS;
    control_sock = socket(AF_UNIX, SOCK_STREAM, 0);
    if (control_sock < 0) {
        LOGE("Could not create control socket");
        return -1;
    }
    memset_s(&controlAddrUn, sizeof(destBuff), 0, sizeof(controlAddrUn));
    controlAddrUn.sun_family = AF_UNIX;
    memcpy_s(controlAddrUn.sun_path, sizeof(destBuff), JDWP_CONTROL_NAME, JDWP_CONTROL_NAME_LEN);
    control_addr_len = sizeof(controlAddrUn.sun_family) + JDWP_CONTROL_NAME_LEN;
    while (true) {
        int ret = connect(control_sock, (struct sockaddr *)&controlAddrUn, control_addr_len);
        if (ret >= 0) {
            LOGI("Connect Successful");
            return 0;
        }
        const int sleep_times = 2;
        usleep(sleep_ms * SLEEP_TIME_MS * sleep_times);
        sleep_ms += (sleep_ms >> 1);
        if (sleep_ms > SLEEP_MAX_MS) {
            sleep_ms = SLEEP_MAX_MS;
        }
    }
    return -1;
}

int32_t UnixSocketClient::SendMessage(int32_t pid)
{
    std::string pidStr = std::to_string(pid);
    int size_ = pidStr.size();
    char buff[size_];
    buff[size_] = 0;
    if (control_sock < 0) {
        LOGE("Error Occur!");
        return -1;
    }
    memcpy_s(buff, sizeof(buff), pidStr.c_str(), size_);
    struct timeval timeout {
    };
    timeout.tv_sec = CONTROL_SOCK_SEND_TIMEOUT;
    timeout.tv_usec = 0;
    setsockopt(control_sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    while (true) {
        int ret = send(control_sock, buff, size_, 0);
        if (ret >= 0) {
            LOGI("PID sent as '%s' to HDC", buff);
            return 0;
        }
        LOGE("Weird, can't send JDWP process pid to HDC");
        return -1;
    }
}

void UnixSocketClient::UnixSocketClose()
{
    close(control_sock);
}

} // namespace OHOS::Ace

