/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/card_frontend/card_frontend_declarative.h"

#include <memory>
#include <vector>

#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "core/common/thread_checker.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {

const char MANIFEST_JSON[] = "manifest.json";
const char FILE_TYPE_BIN[] = ".abc";

} // namespace

// CardFrontendDeclarative::~CardFrontendDeclarative()
// {
//     LOG_DESTROY();
// }

// bool CardFrontendDeclarative::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
// {
//     type_ = type;
//     taskExecutor_ = taskExecutor;
//     // InitializeDelegate(taskExecutor);
//     manifestParser_ = AceType::MakeRefPtr<Framework::ManifestParser>();
//     return true;
// }

void CardFrontendDeclarative::InitializeDelegate(const RefPtr<TaskExecutor>& taskExecutor)
{
    // auto pageRouterManager = AceType::MakeRefPtr<NG::PageRouterManager>();
    // delegate_ = AceType::MakeRefPtr<Framework::CardFrontendDelegateDeclarative>(taskExecutor);
    // delegate_->SetPageRouterManager(pageRouterManager);
}

// RefPtr<NG::PageRouterManager> CardFrontendDeclarative::GetPageRouterManager() const
// {
//     CHECK_NULL_RETURN(delegate_, nullptr);
//     return delegate_->GetPageRouterManager();
// }

// void CardFrontendDeclarative::Destroy()
// {
//     CHECK_RUN_ON(JS);
//     delegate_.Reset();
//     eventHandler_.Reset();
// }

// void CardFrontendDeclarative::AttachPipelineContext(const RefPtr<PipelineBase>& context)
// {
//     auto pipelineContext = DynamicCast<NG::PipelineContext>(context);
//     CHECK_NULL_VOID_NOLOG(delegate_);
//     CHECK_NULL_VOID_NOLOG(pipelineContext);
//     eventHandler_ = AceType::MakeRefPtr<CardEventHandlerDeclarative>(delegate_);

//     holder_.Attach(context);
//     delegate_->AttachPipelineContext(context);
// }

// void CardFrontendDeclarative::SetAssetManager(const RefPtr<AssetManager>& assetManager)
// {
//     LOGE("Kee CardFrontendDeclarative::SetAssetManager");
//     assetManager_ = assetManager;
//     if (delegate_) {
//         delegate_->SetAssetManager(assetManager);
//     }
// }

std::string CardFrontendDeclarative::GetFormSrcPath(const std::string& uri, const std::string& suffix) const
{
    if (uri.empty()) {
        LOGW("page uri is empty");
        return "";
    }
    // the case uri is starts with "/" and "/" is the mainPage
    if (uri.size() != 0) {
        return uri + suffix;
    }

    LOGE("can't find this page %{private}s path", uri.c_str());
    return "";
}

void CardFrontendDeclarative::ParseManifest() const
{
    std::call_once(onceFlag_, [this]() {
        std::string jsonContent;
        if (!Framework::GetAssetContentImpl(assetManager_, MANIFEST_JSON, jsonContent)) {
            LOGE("Kee CardFrontendDeclarative::ParseManifest RunPage parse manifest.json failed");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }
        manifestParser_->Parse(jsonContent);
    });
}

void CardFrontendDeclarative::RunPage(int32_t pageId, const std::string& url, const std::string& params)
{
    LOGE("Kee CardFrontendDeclarative::RunPage url = %{public}s", url.c_str());
    std::string urlPath;
    if (GetFormSrc().empty()) {
        ParseManifest();
        if (!url.empty()) {
            urlPath = manifestParser_->GetRouter()->GetPagePath(url, FILE_TYPE_BIN);
        }
        if (urlPath.empty()) {
            urlPath = manifestParser_->GetRouter()->GetEntry(FILE_TYPE_BIN);
        }
    } else {
        urlPath = GetFormSrcPath(GetFormSrc(), FILE_TYPE_BIN);
    }
    if (urlPath.empty()) {
        LOGE("fail to eTS Card run page due to path url is empty");
        // EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
        // return;
        urlPath = url;
    }
    LOGE("Kee CardFrontendDeclarative::RunPage urlPath = %{public}s", urlPath.c_str());
    if (delegate_) {
        LOGE("Kee CardFrontendDeclarative::RunPage 1");
        auto container = Container::Current();
        if (!container) {
            LOGE("RunPage host container null");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }
        LOGE("Kee CardFrontendDeclarative::RunPage 2");
        container->SetCardFrontend(AceType::WeakClaim(this), cardId_);
        auto delegate = AceType::DynamicCast<Framework::CardFrontendDelegateDeclarative>(delegate_);
        if (delegate) {
            LOGE("Kee CardFrontendDeclarative::RunPage delegate->RunCard");
            delegate->RunCard(urlPath, params, "", cardId_);
        } else {
            LOGE("Kee CardFrontendDeclarative::RunPage delegate nullptr");
        }
        // LOGE("Kee CardFrontendDeclarative::RunPage delegate->RunCard");
        // delegate_->RunCard(urlPath, params, "", cardId_);
    }
}

void CardFrontendDeclarative::UpdateData(const std::string& dataList)
{
    LOGE("Kee CardFrontendDeclarative::UpdateData dataList = %{public}s", dataList.c_str());
    // taskExecutor_->PostTask(
    //     [weak = AceType::WeakClaim(this), dataList] {
    //         auto frontend = weak.Upgrade();
    //         if (frontend) {
    //             frontend->UpdatePageData(dataList);
    //         }
    //     },
    //     TaskExecutor::TaskType::UI); // eTSCard UI == Main JS/UI/PLATFORM
}

void CardFrontendDeclarative::UpdatePageData(const std::string& dataList)
{
    CHECK_RUN_ON(UI); // eTSCard UI == Main JS/UI/PLATFORM
    if (!delegate_) {
        LOGE("the delegate is null");
        EventReport::SendFormException(FormExcepType::UPDATE_PAGE_ERR);
        return;
    }
    // delegate_->UpdatePageData(dataList);
}

void CardFrontendDeclarative::SetColorMode(ColorMode colorMode)
{
    LOGE("Kee CardFrontendDeclarative::SetColorMode");
    // taskExecutor_->PostTask(
    //     [weak = AceType::WeakClaim(this), colorMode]() {
    //         auto frontend = weak.Upgrade();
    //         if (frontend) {
    //             frontend->colorMode_ = colorMode;
    //             if (!frontend->delegate_) {
    //                 LOGE("the delegate is null");
    //                 return;
    //             }
    //             frontend->OnMediaFeatureUpdate();
    //         } else {
    //             LOGE("eTS Card frontend is nullptr");
    //         }
    //     },
    //     TaskExecutor::TaskType::JS);
}

// void CardFrontendDeclarative::RebuildAllPages()
// {
// }

void CardFrontendDeclarative::OnSurfaceChanged(int32_t width, int32_t height)
{
    LOGE("Kee CardFrontendDeclarative::OnSurfaceChanged width = %{public}d height = %{public}d", width, height);
    // taskExecutor_->PostTask(
    //     [weak = AceType::WeakClaim(this), width, height] {
    //         auto frontend = weak.Upgrade();
    //         if (frontend) {
    //             frontend->HandleSurfaceChanged(width, height);
    //         }
    //     },
    //     TaskExecutor::TaskType::JS);
}

void CardFrontendDeclarative::HandleSurfaceChanged(int32_t width, int32_t height)
{
    CHECK_RUN_ON(JS);
    OnMediaFeatureUpdate();
}

void CardFrontendDeclarative::OnMediaFeatureUpdate()
{
    CHECK_RUN_ON(JS);
}

} // namespace OHOS::Ace
