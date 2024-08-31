/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "core/common/ai/ai_write_adapter.h"

#include "array_wrapper.h"
#include "bool_wrapper.h"
#include "int_wrapper.h"
#include "want.h"
#include "want_params.h"
#include "bundlemgr/bundle_mgr_interface.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"
#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace {
namespace {
#ifndef OS_ACCOUNT_EXISTS
constexpr int32_t DEFAULT_OS_ACCOUNT_ID = 0; // 0 is the default id when there is no os_account part
#endif                                       // OS_ACCOUNT_EXISTS

ErrCode GetActiveAccountIds(std::vector<int32_t>& userIds)
{
    userIds.clear();
#ifdef OS_ACCOUNT_EXISTS
    return AccountSA::OsAccountManager::QueryActiveOsAccountIds(userIds);
#else  // OS_ACCOUNT_EXISTS
    TAG_LOGW(AceLogTag::ACE_PLUGIN_COMPONENT, "os account part doesn't exist, use default id.");
    userIds.push_back(DEFAULT_OS_ACCOUNT_ID);
    return ERR_OK;
#endif // OS_ACCOUNT_EXISTS
}
const std::pair<std::string, std::string> UI_ENTENSION_TYPE = {"ability.want.params.uiExtensionType", "sys/commonUI"};
const std::wstring BOUNDARY_SYMBOLS = L",.?!，。？！";
const std::string SELECT_BUFFER = "selectBuffer";
const std::string SENTENCE_BUFFER = "sentenceBuffer";
const std::string API_VERSION = "apiVersion";
const std::string RESULT_BUFFER = "resultBuffer";
const std::string SHEET_DISMISS = "sheetDismiss";
const std::string PROCESS_ID = "processId";
const std::string MAX_CONTENT_LENGTH = "maxContentLength";
const std::string FIRST_HANDLE_RECT = "firstHandleRect";
const std::string SECOND_HANDLE_RECT = "secondHandleRect";
const std::string IS_AI_SUPPORT_METADATA = "isAiSupport";
} // namespace

bool AIWriteAdapter::GetAISupportFromMetadata(const std::string& bundleName, const std::string& abilityName)
{
    if (bundleName.empty() || abilityName.empty()) {
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "BundleName: %{public}s, abilityName: %{public}s", bundleName.c_str(), abilityName.c_str());

    std::vector<int32_t> userIds;
    ErrCode errCode = GetActiveAccountIds(userIds);
    if (errCode != ERR_OK) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Query Active OsAccountIds failed!");
        return false;
    }
    sptr<ISystemAbilityManager> systemAbilityManager =
        SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "GetBundleMgrProxy, systemAbilityManager is null");
        return false;
    }
    sptr<IRemoteObject> remoteObject = systemAbilityManager->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!remoteObject) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "GetBundleMgrProxy, remoteObject is null");
        return false;
    }
    sptr<AppExecFwk::IBundleMgr> bundleMgrProxy = iface_cast<AppExecFwk::IBundleMgr>(remoteObject);
    AppExecFwk::BundleInfo bundleInfo;
    int32_t bundleInfoFlag = static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_HAP_MODULE) |
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_APPLICATION) |
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_ABILITY) |
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_EXTENSION_ABILITY) |
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_METADATA);
    errCode = bundleMgrProxy->GetBundleInfoV9(bundleName, bundleInfoFlag, bundleInfo, userIds[0]);
    if (errCode != ERR_OK) {
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Get bundleName failed! errCode = %{public}d", errCode);
        return false;
    }
    return GetAISupportFromBundleInfo(bundleInfo, abilityName);
}

bool AIWriteAdapter::GetAISupportFromBundleInfo(
    const AppExecFwk::BundleInfo& bundleInfo, const std::string& abilityName)
{
    AppExecFwk::HapModuleInfo hapModuleInfo;
    for (const auto& item: bundleInfo.hapModuleInfos) {
        if (item.mainElementName == abilityName) {
            hapModuleInfo = item;
            break;
        }
    }
    std::vector<AppExecFwk::Metadata> metadataList;
    for (const auto& extensionInfo: hapModuleInfo.extensionInfos) {
        if (extensionInfo.name == abilityName) {
            metadataList = extensionInfo.metadata;
            break;
        }
    }
    bool isAISupport = false;
    for (const auto& metadata: metadataList) {
        if (metadata.name == IS_AI_SUPPORT_METADATA) {
            if (metadata.value == "true") {
                isAISupport = true;
            }
            break;
        }
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Read metadata from hap, isAISupport: %{public}d", isAISupport);
    return isAISupport;
}

bool AIWriteAdapter::IsSentenceBoundary(const wchar_t value)
{
    for (wchar_t item: BOUNDARY_SYMBOLS) {
        if (value == item) {
            return true;
        }
    }
    return false;
}

void AIWriteAdapter::CloseModalUIExtension()
{
    auto context = pipelineContext_.Upgrade();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseModalUIExtension(sessionId_);
    SetAIWrite(false);
}

void AIWriteAdapter::ShowModalUIExtension(const AIWriteInfo& info,
    std::function<void(std::vector<uint8_t>&)> resultCallback)
{
    AAFwk::Want want;
    SetWantParams(info, want);
    Ace::ModalUIExtensionCallbacks callbacks;
    callbacks.onResult = [](int32_t code, const AAFwk::Want& want) {
        TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension onResult, code: %{public}d", code);
    };
    callbacks.onDestroy = []() {
        TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension onDestroy.");
    };
    callbacks.onError = [](int32_t code, const std::string& name, const std::string& message) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExtension onError, code: %{public}d, name: %{public}s, message: %{public}s",
            code, name.c_str(), message.c_str());
    };
    callbacks.onRelease = [](int32_t code) {
        TAG_LOGD(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExtension onRelease, code: %{public}d", code);
    };
    callbacks.onReceive = [weak = WeakClaim(this), cb = std::move(resultCallback)]
        (const AAFwk::WantParams& wantParams) {
        auto aiWriteAdapter = weak.Upgrade();
        CHECK_NULL_VOID(aiWriteAdapter);
        auto result = aiWriteAdapter->GetBufferParam(RESULT_BUFFER, wantParams);
        auto isSheetClose = aiWriteAdapter->GetBoolParam(SHEET_DISMISS, wantParams);
        if (cb && !result.empty()) {
            cb(result);
        }
        if (isSheetClose) {
            aiWriteAdapter->CloseModalUIExtension();
        }
    };
    auto context = pipelineContext_.Upgrade();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    Ace::ModalUIExtensionConfig config;
    sessionId_ = overlayManager->CreateModalUIExtension(want, callbacks, config);
}

void AIWriteAdapter::SetWantParams(const AIWriteInfo& info, AAFwk::Want& want)
{
    std::vector<int> selectBufferVec(info.selectBuffer.size());
    std::transform(info.selectBuffer.begin(), info.selectBuffer.end(), selectBufferVec.begin(),
        [](uint8_t x) { return static_cast<int>(x); });
    std::vector<int> sentenceBufferVec(info.sentenceBuffer.size());
    std::transform(info.sentenceBuffer.begin(), info.sentenceBuffer.end(), sentenceBufferVec.begin(),
        [](uint8_t x) { return static_cast<int>(x); });
    auto apiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    want.SetElementName(bundleName_, abilityName_);
    want.SetParam(UI_ENTENSION_TYPE.first, UI_ENTENSION_TYPE.second);
    want.SetParam(SELECT_BUFFER, selectBufferVec);
    want.SetParam(SENTENCE_BUFFER, sentenceBufferVec);
    want.SetParam(API_VERSION, static_cast<int>(apiVersion));
    want.SetParam(PROCESS_ID, getpid());
    want.SetParam(MAX_CONTENT_LENGTH, info.maxLength);
    want.SetParam(FIRST_HANDLE_RECT, info.firstHandle);
    want.SetParam(SECOND_HANDLE_RECT, info.secondHandle);
}

std::vector<uint8_t> AIWriteAdapter::GetBufferParam(const std::string& key, const AAFwk::WantParams& wantParams)
{
    std::vector<uint8_t> array;
    auto value = wantParams.GetParam(key);
    AAFwk::IArray *ao = AAFwk::IArray::Query(value);
    if (ao != nullptr && AAFwk::Array::IsIntegerArray(ao)) {
        auto func = [&](AAFwk::IInterface *object) {
            CHECK_NULL_VOID(object);
            AAFwk::IInteger *value = AAFwk::IInteger::Query(object);
            CHECK_NULL_VOID(value);
            array.emplace_back(AAFwk::Integer::Unbox(value));
        };
        AAFwk::Array::ForEach(ao, func);
    }
    return array;
}

bool AIWriteAdapter::GetBoolParam(const std::string& key, const AAFwk::WantParams& wantParams)
{
    auto value = wantParams.GetParam(key);
    AAFwk::IBoolean *bo = AAFwk::IBoolean::Query(value);
    if (bo != nullptr) {
        return AAFwk::Boolean::Unbox(bo);
    }
    return false;
}
}