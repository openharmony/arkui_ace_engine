/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "page_url_checker_ohos.h"

#include <string>

#include "ability_runtime/context/context.h"
#include "app_mgr_client.h"
#include "atomic_service_status_callback.h"
#include "errors.h"
#include "iremote_broker.h"
#include "iremote_object.h"
#include "iremote_stub.h"
#include "iservice_registry.h"
#include "nocopyable.h"
#include "singleton.h"
#include "system_ability_definition.h"
#include "want.h"

namespace OHOS::Ace {
const char BUNDLE_TAG[] = "@bundle:";
constexpr size_t BUNDLE_START_POS = 8;
constexpr int32_t SILENT_INSTALL_SUCCESS = 0;

/**
 * @class IAtomicServiceStatusCallback
 * IAtomicServiceStatusCallback is used to notify caller ability that free install is complete.
 */
class IAtomicServiceStatusCallback : public IRemoteBroker {
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
class AtomicServiceStatusCallbackStub : public IRemoteStub<IAtomicServiceStatusCallback> {
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

    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override
    {
        LOGI("AtomicServiceStatusCallbackStub::OnReceived, code = %{public}u, flags= %{public}d.",
            code, option.GetFlags());
        std::u16string descriptor = AtomicServiceStatusCallbackStub::GetDescriptor();
        std::u16string remoteDescriptor = data.ReadInterfaceToken();
        if (descriptor != remoteDescriptor) {
            LOGE("%{public}s failed, local descriptor is not equal to remote", __func__);
            return ERR_INVALID_VALUE;
        }

        auto resultCode = data.ReadInt32();
        if (resultCode == SILENT_INSTALL_SUCCESS) {
            if (handleOnActionEventFunc_ != nullptr) {
                return (this->*handleOnActionEventFunc_)();
            }
        }

        if (resultCode < SILENT_INSTALL_SUCCESS) {
            if (handleOnErrorFunc_ != nullptr) {
                return (this->*handleOnErrorFunc_)(data);
            }
        }

        return IPCObjectStub::OnRemoteRequest(code, data, reply, option);
    }

private:
    int32_t HandleOnActionEvent()
    {
        return OnActionEvent();
    }
    int32_t HandleOnError(MessageParcel &data)
    {
        int32_t code = data.ReadInt32();
        std::string msg = data.ReadString();
        return OnError(code, msg);
    }

    using HandleOnActionEventFunc = int32_t (AtomicServiceStatusCallbackStub::*)();
    HandleOnActionEventFunc handleOnActionEventFunc_;

    using HandleOnErrorFunc = int32_t (AtomicServiceStatusCallbackStub::*)(MessageParcel &data);
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
            LOGE("actionEventHandler_ is null.");
            return ERR_INVALID_VALUE;
        }
        actionEventHandler_();
        return ERR_OK;
    }
    /**
     * @brief OnError.
     * @param code The code.
     * @param msg The msg.
     */
    int32_t OnError(int32_t code, const std::string& msg) override
    {
        LOGE("OnError code: %{public}d, msg: %{public}s", code, msg.c_str());
        if (!errorEventHandler_) {
            LOGE("errorEventHandler_ is null");
            return ERR_INVALID_VALUE;
        }

        errorEventHandler_(code, msg);
        return ERR_OK;
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

sptr<AppExecFwk::IBundleMgr> PageUrlCheckerOhos::GetBundleManager()
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        LOGE("Failed to get SystemAbilityManager.");
        return nullptr;
    }

    auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (bundleObj == nullptr) {
        LOGE("Failed to get bundle manager service");
        return nullptr;
    }

    return iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
}

void PageUrlCheckerOhos::LoadPageUrl(const std::string& url, const std::function<void()>& callback,
    const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack)
{
    if (url.substr(0, strlen(BUNDLE_TAG)) != BUNDLE_TAG) {
        return;
    }

    size_t bundleEndPos = url.find('/');
    std::string bundleName = url.substr(BUNDLE_START_POS, bundleEndPos - BUNDLE_START_POS);
    size_t moduleStartPos = bundleEndPos + 1;
    size_t moduleEndPos = url.find('/', moduleStartPos);
    std::string moduleName = url.substr(moduleStartPos, moduleEndPos - moduleStartPos);

    auto appInfo = context_->GetApplicationInfo();
    if (appInfo) {
        std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
        bool isInstalled = false;
        auto res = std::any_of(moduleList.begin(), moduleList.end(), [moduleName](const auto &module) {
            return module.moduleName == moduleName;
        });
        if (res) {
            isInstalled = true;
        }

        if (!isInstalled) {
            auto bms = GetBundleManager();
            CHECK_NULL_VOID(bms);
            AAFwk::Want want;
            want.SetBundle(bundleName);
            want.SetModuleName(moduleName);
            sptr<AtomicServiceStatusCallback> routerCallback = new AtomicServiceStatusCallback();
            routerCallback->SetActionEventHandler(callback);
            routerCallback->SetErrorEventHandler(silentInstallErrorCallBack);
            if (bms->SilentInstall(want, appInfo->uid / AppExecFwk::Constants::BASE_USER_RANGE, routerCallback)) {
                LOGI("Begin to silent install");
            }
        } else {
            callback();
        }
    }
}

void PageUrlCheckerOhos::CheckPreload(const std::string& url)
{
    if (url.substr(0, strlen(BUNDLE_TAG)) != BUNDLE_TAG) {
        return;
    }

    size_t bundleEndPos = url.find('/');
    std::string bundleName = url.substr(BUNDLE_START_POS, bundleEndPos - BUNDLE_START_POS);
    size_t moduleStartPos = bundleEndPos + 1;
    size_t moduleEndPos = url.find('/', moduleStartPos);
    std::string moduleName = url.substr(moduleStartPos, moduleEndPos - moduleStartPos);

    auto appInfo = context_->GetApplicationInfo();
    CHECK_NULL_VOID(appInfo);
    if (appInfo->CheckNeedPreload(moduleName)) {
        auto bms = GetBundleManager();
        CHECK_NULL_VOID(bms);
        AAFwk::Want want;
        // only need to Transfer bundleName and moduleName
        want.SetElementName("", bundleName, "", moduleName);
        want.SetParam("uid", appInfo->uid);
        bms->ProcessPreload(want);
    }
}

void PageUrlCheckerOhos::NotifyPageShow(const std::string& pageName)
{
    LOGD("NotifyPageShow start pageName %{public}s", pageName.c_str());
    std::string moduleName = moduleNameCallback_(pageName);
    if (moduleName == "") {
        LOGD("moduleName moduleNameCallback_ is null");
        moduleName = abilityInfo_->moduleName;
    }
    AppExecFwk::PageStateData pageStateData;
    pageStateData.bundleName = abilityInfo_->bundleName;
    pageStateData.moduleName = moduleName;
    pageStateData.abilityName = abilityInfo_->name;
    pageStateData.pageName = pageName;
    DelayedSingleton<AppExecFwk::AppMgrClient>::GetInstance()->
        NotifyPageShow(context_->GetToken(), pageStateData);
    LOGD("NotifyPageShow end,bundleName: %{public}s moduleName: %{public}s abilityName: %{public}s "
        "pageName: %{public}s", abilityInfo_->bundleName.c_str(), moduleName.c_str(),
        abilityInfo_->name.c_str(), pageName.c_str());
}

void PageUrlCheckerOhos::NotifyPageHide(const std::string& pageName)
{
    LOGD("NotifyPageHide start pageName %{public}s", pageName.c_str());
    std::string moduleName = moduleNameCallback_(pageName);
    if (moduleName == "") {
        LOGD("moduleName moduleNameCallback_ is null");
        moduleName = abilityInfo_->moduleName;
    }
    AppExecFwk::PageStateData pageStateData;
    pageStateData.bundleName = abilityInfo_->bundleName;
    pageStateData.moduleName = moduleName;
    pageStateData.abilityName = abilityInfo_->name;
    pageStateData.pageName = pageName;
    DelayedSingleton<AppExecFwk::AppMgrClient>::GetInstance()->
        NotifyPageHide(context_->GetToken(), pageStateData);
    LOGD("NotifyPageHide end,bundleName: %{public}s moduleName: %{public}s abilityName: %{public}s "
        "pageName: %{public}s", abilityInfo_->bundleName.c_str(), moduleName.c_str(),
        abilityInfo_->name.c_str(), pageName.c_str());
}

void PageUrlCheckerOhos::SetModuleNameCallback(std::function<std::string(const std::string&)>&& callback)
{
    moduleNameCallback_ = std::move(callback);
}
} // namespace OHOS::Ace