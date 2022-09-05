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
#include "base/log/log.h"
namespace OHOS::Ace {

HdcJdwpSimulator::HdcJdwpSimulator(const std::string pkgName)
{
    pkgName_ = pkgName;
    ctxPoint_ = (HCtxJdwpSimulator)MallocContext();
}

void HdcJdwpSimulator::FreeContext()
{
    if (ctxPoint_ != nullptr && ctxPoint_->cfd > -1) {
        close(ctxPoint_->cfd);
        ctxPoint_->cfd = -1;
    }
}

HdcJdwpSimulator::~HdcJdwpSimulator()
{
    if (ctxPoint_ != nullptr) {
        delete ctxPoint_;
        ctxPoint_ = nullptr;
    }
}

void HdcJdwpSimulator::SendToJpid(int fd, const uint8_t *buf, const int bufLen)
{
    LOGI("SendToJpid: %{public}s, %{public}d", buf, bufLen);
    ssize_t rc = write(fd, buf, bufLen);
    if (rc < 0) {
        LOGE("SendToJpid failed errno:%{public}d", errno);
    }
}

void HdcJdwpSimulator::ConnectJpid(void *param)
{
    uint32_t pid_curr = static_cast<uint32_t>(getpid());
    HdcJdwpSimulator *thisClass = static_cast<HdcJdwpSimulator *>(param);
#ifdef JS_JDWP_CONNECT
    string pkgName = thisClass->pkgName_;
    uint32_t pkgSize = pkgName.size() + sizeof(JsMsgHeader);
    uint8_t* info = new (std::nothrow) uint8_t[pkgSize]();
    if (!info) {
        LOGE("ConnectJpid new info fail.");
        return;
    }
    if (memset_s(info, pkgSize, 0, pkgSize) != EOK) {
        delete[] info;
        info = nullptr;
        return;
    }
    JsMsgHeader *jsMsg = reinterpret_cast<JsMsgHeader *>(info);
    jsMsg->pid = pid_curr;
    jsMsg->msgLen = pkgSize;
    LOGI("ConnectJpid send pid:%{public}d, pkgName:%{public}s, msglen:%{public}d",
        jsMsg->pid, pkgName.c_str(), jsMsg->msgLen);
    bool retFail = false;
    if (memcpy_s(info + sizeof(JsMsgHeader), pkgName.size(), &pkgName[0], pkgName.size()) != EOK) {
        LOGE("ConnectJpid memcpy_s fail :%{public}s.", pkgName.c_str());
        retFail = true;
    }
    if (!retFail) {
        LOGI("ConnectJpid send JS msg:%{public}s", info);
        SendToJpid(thisClass->ctxPoint_->cfd, (uint8_t*)info, pkgSize);
    }
    if (info) {
        delete[] info;
        info = nullptr;
    }
#endif
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
    if (!ctxPoint_) {
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
    int cfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (cfd < 0) {
        LOGE("socket failed errno:%{public}d", errno);
        return false;
    }

    int rc = connect(cfd, reinterpret_cast<struct sockaddr *>(&caddr), sizeof(caddr));
    if (rc != 0) {
        LOGE("connect failed errno:%{public}d", errno);
        close(cfd);
        return false;
    }
    ctxPoint_->cfd = cfd;
    ConnectJpid(this);
    return true;
}
} // namespace OHOS::Ace
