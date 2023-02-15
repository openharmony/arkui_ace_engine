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

#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "core/common/thread_checker.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

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

    LOGE("can't find this page %{private}s path", uri.c_str());
    return "";
}

void FormFrontendDeclarative::RunPage(int32_t pageId, const std::string& url, const std::string& params)
{
    LOGI("FormFrontendDeclarative::RunPage url = %{public}s", url.c_str());
    std::string urlPath = GetFormSrcPath(url, FILE_TYPE_BIN);
    if (urlPath.empty()) {
        LOGE("fail to eTS Card run page due to path url is empty");
        EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
        return;
    }
    LOGI("FormFrontendDeclarative::RunPage urlPath = %{public}s", urlPath.c_str());
    if (delegate_) {
        auto container = Container::Current();
        if (!container) {
            LOGE("RunPage host container null");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }
        container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
        auto delegate = AceType::DynamicCast<Framework::FormFrontendDelegateDeclarative>(delegate_);
        if (delegate) {
            delegate->RunCard(urlPath, params, "", cardId_);
        } else {
            LOGE("FormFrontendDeclarative::RunPage delegate nullptr");
        }
    }
}

void FormFrontendDeclarative::UpdateData(const std::string& dataList)
{
    LOGI("FormFrontendDeclarative::UpdateData dataList = %{public}s", dataList.c_str());
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), dataList] {
            auto frontend = weak.Upgrade();
            if (frontend) {
                frontend->UpdatePageData(dataList);
            }
        },
        TaskExecutor::TaskType::UI); // eTSCard UI == Main JS/UI/PLATFORM
}

void FormFrontendDeclarative::UpdatePageData(const std::string& dataList)
{
    CHECK_RUN_ON(UI); // eTSCard UI == Main JS/UI/PLATFORM
    auto delegate = GetDelegate();
    if (!delegate) {
        LOGE("the delegate is null");
        EventReport::SendFormException(FormExcepType::UPDATE_PAGE_ERR);
        return;
    }
    delegate->UpdatePageData(dataList);
}

void FormFrontendDeclarative::SetColorMode(ColorMode colorMode) {}
void FormFrontendDeclarative::OnSurfaceChanged(int32_t width, int32_t height) {}

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
