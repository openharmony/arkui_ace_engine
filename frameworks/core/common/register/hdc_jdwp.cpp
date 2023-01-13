/*
 * Copyright (C) 2021-2022 Huawei Device Co., Ltd.
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
 *
 */
#include "frameworks/core/common/register/hdc_jdwp.h"

#include <unistd.h>

#include "base/log/log.h"
namespace OHOS::Ace {

HdcJdwpSimulator::HdcJdwpSimulator(const std::string pkgName)
{
    pkgName_ = pkgName;
    ctxPoint_ = (HCtxJdwpSimulator)MallocContext();
    disconnectFlag_ = false;
}

void HdcJdwpSimulator::Disconnect()
{
    if (ctxPoint_ != nullptr && ctxPoint_->cfd > -1) {
        disconnectFlag_ = true;
        shutdown(ctxPoint_->cfd, SHUT_RDWR);
        close(ctxPoint_->cfd);
        ctxPoint_->cfd = -1;
        unsigned int threadDelay = 500000;
        usleep(threadDelay);
    }
}

HdcJdwpSimulator::~HdcJdwpSimulator()
{
    if (ctxPoint_ != nullptr) {
        if (ctxPoint_->cfd > -1) {
            disconnectFlag_ = true;
            shutdown(ctxPoint_->cfd, SHUT_RDWR);
            close(ctxPoint_->cfd);
            ctxPoint_->cfd = -1;
        }
        delete ctxPoint_;
        ctxPoint_ = nullptr;
    }
}

bool HdcJdwpSimulator::SendToJpid(int fd, const uint8_t *buf, const int bufLen)
{
    LOGI("SendToJpid: %{public}s, %{public}d", buf, bufLen);
    ssize_t rc = write(fd, buf, bufLen);
    if (rc < 0) {
        LOGE("SendToJpid failed errno:%{public}d", errno);
        return false;
    }
    return true;
}

bool HdcJdwpSimulator::ConnectJpid(void *param)
{
    uint32_t pid_curr = static_cast<uint32_t>(getpid());
    HdcJdwpSimulator *thisClass = static_cast<HdcJdwpSimulator *>(param);
#ifdef JS_JDWP_CONNECT
    string pkgName = thisClass->pkgName_;
    uint32_t pkgSize = pkgName.size() + sizeof(JsMsgHeader);
    uint8_t* info = new (std::nothrow) uint8_t[pkgSize]();
    if (info == nullptr) {
        LOGE("ConnectJpid new info fail.");
        return false;
    }
    if (memset_s(info, pkgSize, 0, pkgSize) != EOK) {
        delete[] info;
        info = nullptr;
        return false;
    }
    JsMsgHeader *jsMsg = reinterpret_cast<JsMsgHeader *>(info);
    jsMsg->pid = pid_curr;
    jsMsg->msgLen = pkgSize;
    LOGI("ConnectJpid send pid:%{public}d, pkgName:%{public}s, msglen:%{public}d",
        jsMsg->pid, pkgName.c_str(), jsMsg->msgLen);
    bool ret = true;
    if (memcpy_s(info + sizeof(JsMsgHeader), pkgName.size(), &pkgName[0], pkgName.size()) != EOK) {
        LOGE("ConnectJpid memcpy_s fail :%{public}s.", pkgName.c_str());
        ret = false;
    } else {
        LOGI("ConnectJpid send JS msg:%{public}s", info);
        ret = SendToJpid(thisClass->ctxPoint_->cfd, (uint8_t*)info, pkgSize);
    }
    if (info != nullptr) {
        delete[] info;
        info = nullptr;
    }
    return ret;
#endif
    return false;
}

void *HdcJdwpSimulator::MallocContext()
{
    HCtxJdwpSimulator ctx = nullptr;
    if ((ctx = new (std::nothrow) ContextJdwpSimulator()) == nullptr) {
        return nullptr;
    }
    ctx->thisClass = this;
    ctx->cfd = -1;
    return ctx;
}

bool HdcJdwpSimulator::Connect()
{
    const char jdwp[] = { '\0', 'o', 'h', 'j', 'p', 'i', 'd', '-', 'c', 'o', 'n', 't', 'r', 'o', 'l', 0 };
    if (ctxPoint_ == nullptr) {
        LOGE("MallocContext failed");
        return false;
    }
    struct sockaddr_un caddr;
    if (memset_s(&caddr, sizeof(caddr), 0, sizeof(caddr)) != EOK) {
        LOGE("memset_s failed");
        return false;
    }
    caddr.sun_family = AF_UNIX;
    for (size_t i = 0; i < sizeof(jdwp); i++) {
        caddr.sun_path[i] = jdwp[i];
    }

    while (!disconnectFlag_) {
        int cfd = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
        if (cfd < 0) {
            LOGE("socket failed errno:%{public}d", errno);
            return false;
        }
        ctxPoint_->cfd = cfd;

        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        setsockopt(cfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
        size_t caddrLen = sizeof(caddr.sun_family) + sizeof(jdwp) - 1;
        int rc = connect(cfd, reinterpret_cast<struct sockaddr *>(&caddr), caddrLen);
        if (rc != 0) {
            LOGE("connect failed errno:%{public}d", errno);
        } else if (ConnectJpid(this)) {
            char recvBuf[100] = { 0 }; // 100 buf size
            int ret = recv(cfd, recvBuf, sizeof(recvBuf), 0); // stop when server connect, or retry
            LOGE("jdwp retry connect server errno:%{public}d, ret:%{public}d", errno, ret);
        }
        if (ctxPoint_->cfd > -1) {
            close(ctxPoint_->cfd);
            ctxPoint_->cfd = -1;
        }
        if (!disconnectFlag_) {
            sleep(3); // connect per 3 second
        }
    }
    return true;
}
} // namespace OHOS::Ace
