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

#include "frameworks/bridge/card_frontend/form_frontend_declarative.h"

namespace OHOS::Ace {
namespace {
const char FILE_TYPE_BIN[] = ".abc";
} // namespace

std::string FormFrontendDeclarative::GetFormSrcPath(const std::string& uri, const std::string& suffix) const
{
    // the case uri is starts with "/" and "/" is the mainPage
    if (uri.size() != 0) {
        auto result = uri;
        if (result.compare(result.size()-4, 4, ".ets") == 0) { // 4: length of '.ets'
            result = result.substr(0, result.size()-4); // 4: length of '.ets'
        }
        if (result.compare(0, 1, "/") == 0) { // 1: length of '/'
            return result.substr(1) + ".abc"; // 1: length of '/'
        }
        if (result.compare(0, 2, "./") == 0) { // 2: length of './'
            return result.substr(2) + ".abc"; // 2: length of './'
        }
    }

    return "";
}

UIContentErrorCode FormFrontendDeclarative::RunPage(const std::string& url, const std::string& params)
{
    return RunDynamicPage(url, params, "");
}

UIContentErrorCode FormFrontendDeclarative::RunDynamicPage(
    const std::string& url, const std::string& params, const std::string& entryPoint)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormFrontendDeclarative run page url = %{public}s, entryPoint = %{public}s",
        url.c_str(), entryPoint.c_str());
    auto container = Container::Current();
    if (!container) {
        return UIContentErrorCode::NULL_POINTER;
    }

    auto uiContentType = container->GetUIContentType();
    if (uiContentType == UIContentType::DYNAMIC_COMPONENT) {
        return InnerRunDynamicPage(url, params, entryPoint);
    }

    return InnerRunCardPage(url, params, entryPoint);
}

UIContentErrorCode FormFrontendDeclarative::InnerRunCardPage(
    const std::string& url, const std::string& params, const std::string& entryPoint)
{
    LOGI("InnerRunCardPage");
    std::string urlPath = GetFormSrcPath(url, FILE_TYPE_BIN);
    if (urlPath.empty()) {
        return UIContentErrorCode::NULL_URL;
    }
    if (delegate_) {
        auto container = Container::Current();
        if (!container) {
            return UIContentErrorCode::NULL_POINTER;
        }
        container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
        auto delegate = AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
        if (delegate) {
            return delegate->RunCard(urlPath, params, "", cardId_, entryPoint);
        }
    }

    return UIContentErrorCode::NULL_POINTER;
}

UIContentErrorCode FormFrontendDeclarative::InnerRunDynamicPage(
    const std::string& url, const std::string& params, const std::string& entryPoint)
{
    LOGI("InnerRunDynamicPage");
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
    CHECK_NULL_RETURN(delegate_, UIContentErrorCode::NULL_POINTER);
    auto delegate = AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
    CHECK_NULL_RETURN(delegate, UIContentErrorCode::NULL_POINTER);
    return delegate->RunCard(url, params, "", cardId_, entryPoint);
}

void FormFrontendDeclarative::UpdateData(const std::string& dataList)
{
    CHECK_NULL_VOID(taskExecutor_);
    // eTSCard UI == Main JS/UI/PLATFORM
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), dataList] {
            auto frontend = weak.Upgrade();
            if (frontend) {
                frontend->UpdatePageData(dataList);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIFormFrontendUpdatePageData", PriorityType::HIGH);
}

void FormFrontendDeclarative::UpdatePageData(const std::string& dataList)
{
    CHECK_RUN_ON(UI); // eTSCard UI == Main JS/UI/PLATFORM
    auto delegate = GetDelegate();
    if (!delegate) {
        return;
    }
    delegate->UpdatePageData(dataList);
}

void FormFrontendDeclarative::SetColorMode(ColorMode colorMode) {}

void FormFrontendDeclarative::OnSurfaceChanged(int32_t width, int32_t height)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "FormFrontendDeclarative OnSurfaceChanged entry");
    auto jsEngine = GetJsEngine();
    auto delegate = GetDelegate();
    if (!jsEngine || !delegate) {
        TAG_LOGE(AceLogTag::ACE_FORM, "FormFrontendDeclarative OnSurfaceChanged fail");
        return;
    }
    auto mediaQuery = delegate->GetMediaQueryInfoInstance();
    if (!mediaQuery) {
        TAG_LOGE(AceLogTag::ACE_FORM, "FormFrontendDeclarative OnSurfaceChanged, mediaQuery is null");
        return;
    }
    mediaQuery->EnsureListenerIdValid();
    const auto& listenerId = mediaQuery->GetListenerId();
    auto json = JsonUtil::Create(true);
    jsEngine->MediaQueryCallback(listenerId, json->ToString());
}

void FormFrontendDeclarative::HandleSurfaceChanged(int32_t width, int32_t height)
{
    CHECK_RUN_ON(JS);
    OnMediaFeatureUpdate();
}

void FormFrontendDeclarative::OnMediaFeatureUpdate()
{
    CHECK_RUN_ON(JS);
}

void FormFrontendDeclarative::SetErrorEventHandler(
    std::function<void(const std::string&, const std::string&)>&& errorCallback)
{
    auto jsEngine = GetJsEngine();
    if (!jsEngine) {
        return;
    }

    return jsEngine->SetErrorEventHandler(std::move(errorCallback));
}
} // namespace OHOS::Ace
