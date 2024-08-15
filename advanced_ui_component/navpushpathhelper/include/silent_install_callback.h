/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_SILENT_INSTALL_CALLBACK_H
#define ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_SILENT_INSTALL_CALLBACK_H

#include "atomic_service_status_callback.h"
#include "errors.h"
#include "iremote_broker.h"
#include "iremote_object.h"
#include "iremote_stub.h"
#include "base/log/log.h"
#include "want_params_wrapper.h"
#include "want.h"

namespace OHOS::NavPushPathHelper {
constexpr int32_t SILENT_INSTALL_SUCCESS = 0;
constexpr int32_t SILENT_INSTALL_FAIL_CODE = 300001;
constexpr char SILENT_INSTALL_FAIL_MESSAGE[] = "hsp silent install fail";

/**
 * @class IAtomicServiceStatusCallback
 * IAtomicServiceStatusCallback is used to notify caller ability that free install is complete.
 */
class IAtomicServiceStatusCallback : public OHOS::IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.IAtomicServiceStatusCallback");

    /**
     * @brief OnActionEvent.
     */
    virtual int32_t OnActionEvent() = 0;
    /**
     * @brief OnError.
     * @param code The code.
     * @param msg The msg.
     */
    virtual int32_t OnError(int32_t code, const std::string& msg) = 0;
};

/**
 * @class AtomicServiceStatusCallbackStub
 * AtomicServiceStatusCallbackStub.
 */
class AtomicServiceStatusCallbackStub : public OHOS::IRemoteStub<IAtomicServiceStatusCallback> {
public:
    AtomicServiceStatusCallbackStub()
    {
        handleOnActionEventFunc_ = &AtomicServiceStatusCallbackStub::HandleOnActionEvent;
        handleOnErrorFunc_ = &AtomicServiceStatusCallbackStub::HandleOnError;
    }
    ~AtomicServiceStatusCallbackStub() override
    {
        handleOnActionEventFunc_ = nullptr;
        handleOnErrorFunc_ = nullptr;
    }

    int32_t OnRemoteRequest(uint32_t code, OHOS::MessageParcel &data, OHOS::MessageParcel &reply,
        OHOS::MessageOption &option) override
    {
        TAG_LOGD(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN,
            "AtomicServiceStatusCallbackStub::OnReceived, code = %{public}u, flags= %{public}d.",
            code, option.GetFlags());
        std::u16string descriptor = AtomicServiceStatusCallbackStub::GetDescriptor();
        std::u16string remoteDescriptor = data.ReadInterfaceToken();
        if (descriptor != remoteDescriptor) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN,
                "%{public}s failed, local descriptor is not equal to remote", __func__);
            return OHOS::ERR_INVALID_VALUE;
        }

        auto resultCode = data.ReadInt32();
        if (resultCode == SILENT_INSTALL_SUCCESS) {
            if (handleOnActionEventFunc_ != nullptr) {
                return (this->*handleOnActionEventFunc_)();
            }
        }

        if (resultCode < SILENT_INSTALL_SUCCESS) {
            if (handleOnErrorFunc_ != nullptr) {
                return (this->*handleOnErrorFunc_)();
            }
        }
        return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }

private:
    int32_t HandleOnActionEvent()
    {
        return OnActionEvent();
    }
    int32_t HandleOnError()
    {
        return OnError(SILENT_INSTALL_FAIL_CODE, SILENT_INSTALL_FAIL_MESSAGE);
    }

    using HandleOnActionEventFunc = int32_t (AtomicServiceStatusCallbackStub::*)();
    HandleOnActionEventFunc handleOnActionEventFunc_;

    using HandleOnErrorFunc = int32_t (AtomicServiceStatusCallbackStub::*)();
    HandleOnErrorFunc handleOnErrorFunc_;

    DISALLOW_COPY_AND_MOVE(AtomicServiceStatusCallbackStub);
};

/**
 * @class AtomicServiceStatusCallback
 * AtomicServiceStatusCallback.
 */
class AtomicServiceStatusCallback : public AtomicServiceStatusCallbackStub {
public:
    AtomicServiceStatusCallback() = default;
    ~AtomicServiceStatusCallback() override = default;

    /**
     * @brief OnActionEvent.
     */
    int32_t OnActionEvent() override
    {
        if (!actionEventHandler_) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "actionEventHandler_ is null.");
            return OHOS::ERR_INVALID_VALUE;
        }
        actionEventHandler_();
        return OHOS::ERR_OK;
    }
    /**
     * @brief OnError.
     * @param code The code.
     * @param msg The msg.
     */
    int32_t OnError(int32_t code, const std::string& msg) override
    {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "OnError code: %{public}d, msg: %{public}s",
            code, msg.c_str());
        if (!errorEventHandler_) {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "errorEventHandler_ is null");
            return OHOS::ERR_INVALID_VALUE;
        }

        errorEventHandler_(code, msg);
        return OHOS::ERR_OK;
    }

    void SetActionEventHandler(const std::function<void()>& listener)
    {
        actionEventHandler_ = listener;
    }
    void SetErrorEventHandler(const std::function<void(int32_t, const std::string&)>& listener)
    {
        errorEventHandler_ = listener;
    }

private:
    std::function<void()> actionEventHandler_;
    std::function<void(int32_t, const std::string&)> errorEventHandler_;
};
}
#endif