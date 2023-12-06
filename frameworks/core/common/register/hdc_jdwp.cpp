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

HdcJdwpSimulator::HdcJdwpSimulator(const std::string processName, const std::string pkgName, bool isDebug, Callback cb)
{
    processName_ = processName;
    pkgName_ = pkgName;
    isDebug_ = isDebug;
    cb_ = cb;
    cfd_ = -1;
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
        if (readThread_.joinable()) {
            readThread_.join();
        }
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
    string processName = thisClass->processName_;
    string pkgName = thisClass->pkgName_;
    bool isDebug = thisClass->isDebug_;
    string pp = pkgName;
    if (!processName.empty()) {
        pp += "/" + processName;
    }
    uint32_t ppSize = pp.size() + sizeof(JsMsgHeader);
    uint8_t* info = new (std::nothrow) uint8_t[ppSize]();
    if (info == nullptr) {
        LOGE("ConnectJpid new info fail.");
        return false;
    }
    if (memset_s(info, ppSize, 0, ppSize) != EOK) {
        delete[] info;
        info = nullptr;
        return false;
    }
    JsMsgHeader *jsMsg = reinterpret_cast<JsMsgHeader *>(info);
    jsMsg->msgLen = ppSize;
    jsMsg->pid = pid_curr;
    jsMsg->isDebug = isDebug;
    LOGI("ConnectJpid send pid:%{public}d, pp:%{public}s, isDebug:%{public}d, msglen:%{public}d",
        jsMsg->pid, pp.c_str(), isDebug, jsMsg->msgLen);
    bool ret = true;
    if (memcpy_s(info + sizeof(JsMsgHeader), pp.size(), &pp[0], pp.size()) != EOK) {
        LOGE("ConnectJpid memcpy_s fail :%{public}s.", pp.c_str());
        ret = false;
    } else {
        LOGI("ConnectJpid send JS msg:%{public}s", info);
        ret = SendToJpid(thisClass->ctxPoint_->cfd, (uint8_t*)info, ppSize);
    }
    delete[] info;
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
    cfd_ = socket(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0);
    if (cfd_ < 0) {
        LOGE("socket failed errno:%{public}d", errno);
        return false;
    }
    ctxPoint_->cfd = cfd_;

    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(cfd_, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    size_t caddrLen = sizeof(caddr.sun_family) + sizeof(jdwp) - 1;
    int rc = connect(cfd_, reinterpret_cast<struct sockaddr *>(&caddr), caddrLen);
    if (rc != 0) {
        LOGE("connect failed errno:%{public}d", errno);
        close(cfd_);
        return false;
    }
    if (ConnectJpid(this)) {
        ReadStart();
    }
    return true;
}

int32_t HdcJdwpSimulator::Bytes2Int(uint8_t b[])
{
    int32_t value = 0;
    value = (b[0] & 0xFF);
    value |= ((b[1] << 8) & 0xFF00);
    value |= ((b[2] << 16) & 0xFF0000);
    value |= ((b[3] << 24) & 0xFF000000);
    return value;
}

void HdcJdwpSimulator::ReadStart()
{
    readThread_ = std::thread(ReadWork, this);
}

void HdcJdwpSimulator::ReadWork(void *param)
{
    HdcJdwpSimulator *jdwp = (HdcJdwpSimulator *)param;
    jdwp->Read();
}

void HdcJdwpSimulator::Read()
{
    constexpr size_t size = 256;
    constexpr long sec = 5;
    uint8_t buf[size] = { 0 };
    while(!disconnectFlag_) {
        ssize_t cnt = 0;
        fd_set rset;
        struct timeval timeout;
        timeout.tv_sec = sec;
        timeout.tv_usec = 0;
        FD_ZERO(&rset);
        FD_SET(cfd_, &rset);
        int rc = select(cfd_ + 1, &rset, nullptr, nullptr, &timeout);
        if (rc < 0) {
            LOGE("Read select fd:%{public}d error:%{public}d", cfd_, errno);
            break;
        } else if (rc == 0) {
            continue;
        }
        if (memset_s(buf, size, 0, size) != EOK) {
            continue;
        }
        struct iovec iov;
        iov.iov_base = buf;
        iov.iov_len = size - 1;
        struct msghdr msg;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        int len = CMSG_SPACE(static_cast<unsigned int>(sizeof(int)));
        char ctlBuf[len];
        msg.msg_controllen = sizeof(ctlBuf);
        msg.msg_control = ctlBuf;
        cnt = recvmsg(cfd_, &msg, 0);
        if (cnt <= 0) {
            break;
        } else if (0 < cnt && cnt < 5) {
            continue;
        }
        int32_t fd = Bytes2Int(buf);
        // bool flag = buf[4];
        std::string str = (char *)(buf + 4);
        LOGI("Read fd:%{public}d str:%{public}s", fd, str.c_str());
        struct cmsghdr *cmsg;
        for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != nullptr; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
            if (cmsg->cmsg_type != SCM_RIGHTS) {
                continue;
            }
            int *newfd = (int *) CMSG_DATA(cmsg);
            LOGI("Read fd:%{public}d newfd:%{public}d str:%{public}s", fd, *newfd, str.c_str());
            if (cb_) {
                cb_(*newfd, str);
            }
            break;
        }
    }
}
} // namespace OHOS::Ace
