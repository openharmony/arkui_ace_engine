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

#include "ability_runtime/context/context.h"
#include "app_mgr_client.h"
#include "iremote_stub.h"
#include "iservice_registry.h"
#include "singleton.h"
#include "system_ability_definition.h"

#include "base/utils/utils.h"

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
        TAG_LOGI(AceLogTag::ACE_ROUTER,
            "AtomicServiceStatusCallbackStub::OnReceived,code = %{public}u, flags= %{public}d.", code,
            option.GetFlags());
        std::u16string descriptor = AtomicServiceStatusCallbackStub::GetDescriptor();
        std::u16string remoteDescriptor = data.ReadInterfaceToken();
        if (descriptor != remoteDescriptor) {
            TAG_LOGE(AceLogTag::ACE_ROUTER, "%{public}s failed, local descriptor is not equal to remote", __func__);
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
            TAG_LOGE(AceLogTag::ACE_ROUTER, "actionEventHandler_ is null.");
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
        TAG_LOGW(AceLogTag::ACE_ROUTER, "silent install Error, code: %{public}d, msg: %{public}s", code, msg.c_str());
        if (!errorEventHandler_) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "errorEventHandler_ is null");
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
        TAG_LOGE(AceLogTag::ACE_ROUTER, "Failed to get SystemAbilityManager.");
        return nullptr;
    }

    auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (bundleObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "Failed to get bundle manager service");
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
    size_t harStartPos = moduleName.find('@');
    if (harStartPos != std::string::npos) {
        moduleName = moduleName.substr(0, harStartPos);
    }

    auto appInfo = context_->GetApplicationInfo();
    if (appInfo) {
        std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
        auto res = std::any_of(moduleList.begin(), moduleList.end(), [moduleName](const auto &module) {
            return module.moduleName == moduleName;
        });
        if (res) {
            callback();
            return;
        }

        auto bms = GetBundleManager();
        CHECK_NULL_VOID(bms);
        std::vector<AppExecFwk::BaseSharedBundleInfo> baseSharedBundleInfo;
        if (bms->GetBaseSharedBundleInfos(bundleName, baseSharedBundleInfo) != 0 &&
            baseSharedBundleInfo.size() != 0) {
            callback();
            return;
        }

        AppExecFwk::BundleInfo bundleInfo;
        int32_t ret = bms->GetDependentBundleInfo(bundleName, bundleInfo,
            AppExecFwk::GetDependentBundleInfoFlag::GET_APP_SERVICE_HSP_BUNDLE_INFO);
        if (ret == ERR_OK && bundleInfo.hapModuleInfos.size() != 0) {
            callback();
            return;
        }

        AAFwk::Want want;
        want.SetBundle(bundleName);
        want.SetModuleName(moduleName);
        sptr<AtomicServiceStatusCallback> routerCallback = new AtomicServiceStatusCallback();
        routerCallback->SetActionEventHandler(callback);
        routerCallback->SetErrorEventHandler(silentInstallErrorCallBack);
        if (bms->SilentInstall(want, appInfo->uid / AppExecFwk::Constants::BASE_USER_RANGE, routerCallback)) {
            TAG_LOGI(AceLogTag::ACE_ROUTER, "Begin to silent install");
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
    std::string targetBundleName;
    std::string targetModuleName;
    GetTargetPageInfo(pageName, targetBundleName, targetModuleName);
    AppExecFwk::PageStateData pageStateData;
    pageStateData.bundleName = abilityInfo_->bundleName;
    pageStateData.moduleName = abilityInfo_->moduleName;
    pageStateData.abilityName = abilityInfo_->name;
    pageStateData.pageName = pageName;
    pageStateData.targetBundleName = targetBundleName;
    pageStateData.targetModuleName = targetModuleName;
    DelayedSingleton<AppExecFwk::AppMgrClient>::GetInstance()->
        NotifyPageShow(context_->GetToken(), pageStateData);
}

void PageUrlCheckerOhos::NotifyPageHide(const std::string& pageName)
{
    std::string targetBundleName;
    std::string targetModuleName;
    GetTargetPageInfo(pageName, targetBundleName, targetModuleName);
    AppExecFwk::PageStateData pageStateData;
    pageStateData.bundleName = abilityInfo_->bundleName;
    pageStateData.moduleName = abilityInfo_->moduleName;
    pageStateData.abilityName = abilityInfo_->name;
    pageStateData.pageName = pageName;
    pageStateData.targetBundleName = targetBundleName;
    pageStateData.targetModuleName = targetModuleName;
    DelayedSingleton<AppExecFwk::AppMgrClient>::GetInstance()->
        NotifyPageHide(context_->GetToken(), pageStateData);
}

void PageUrlCheckerOhos::GetTargetPageInfo(const std::string& pageName, std::string& targetBundleName,
    std::string& targetModuleName) const
{
    if (pageName.substr(0, strlen(BUNDLE_TAG)) == BUNDLE_TAG) {
        size_t bundleEndPos = pageName.find('/');
        targetBundleName = pageName.substr(BUNDLE_START_POS, bundleEndPos - BUNDLE_START_POS);
        size_t moduleStartPos = bundleEndPos + 1;
        size_t moduleEndPos = pageName.find('/', moduleStartPos);
        targetModuleName = pageName.substr(moduleStartPos, moduleEndPos - moduleStartPos);
    } else {
        targetBundleName = abilityInfo_->bundleName;
        std::string moduleName = moduleNameCallback_(pageName);
        if (moduleName == "") {
            moduleName = abilityInfo_->moduleName;
        }
        targetModuleName = moduleName;
    }
}

void PageUrlCheckerOhos::SetModuleNameCallback(std::function<std::string(const std::string&)>&& callback)
{
    moduleNameCallback_ = std::move(callback);
}
} // namespace OHOS::Ace