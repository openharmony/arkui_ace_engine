/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/card_frontend/card_frontend.h"

#include <memory>
#include <vector>

#include "base/log/event_report.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace {
namespace {

const char MANIFEST_JSON[] = "manifest.json";
const char FILE_TYPE_JSON[] = ".json";

} // namespace

CardFrontend::~CardFrontend() = default;

bool CardFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    type_ = type;
    taskExecutor_ = taskExecutor;
    delegate_ = AceType::MakeRefPtr<Framework::CardFrontendDelegate>();
    manifestParser_ = AceType::MakeRefPtr<Framework::ManifestParser>();
    return true;
}

void CardFrontend::AttachPipelineContext(const RefPtr<PipelineContext>& context)
{
    eventHandler_ = AceType::MakeRefPtr<CardEventHandler>(delegate_);
    context->RegisterEventHandler(eventHandler_);
    holder_.Attach(context);
    delegate_->GetJsAccessibilityManager()->SetPipelineContext(context);
    delegate_->GetJsAccessibilityManager()->InitializeCallback();
}

void CardFrontend::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    assetManager_ = assetManager;
}

void CardFrontend::ParseManifest() const
{
    std::call_once(onceFlag_, [this]() {
        std::string jsonContent;
        if (!Framework::GetAssetContentImpl(assetManager_, MANIFEST_JSON, jsonContent)) {
            LOGE("RunPage parse manifest.json failed");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }
        manifestParser_->Parse(jsonContent);
    });
}

void CardFrontend::RunPage(int32_t pageId, const std::string& url, const std::string& params)
{
    ParseManifest();
    std::string urlPath;
    if (!url.empty()) {
        urlPath = manifestParser_->GetRouter()->GetPagePath(url, FILE_TYPE_JSON);
    }
    if (urlPath.empty()) {
        urlPath = manifestParser_->GetRouter()->GetEntry(FILE_TYPE_JSON);
    }
    if (urlPath.empty()) {
        LOGE("fail to run page due to path url is empty");
        EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
        return;
    }
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), urlPath, params] {
            auto frontend = weak.Upgrade();
            if (frontend) {
                frontend->LoadPage(urlPath, params);
            }
        },
        TaskExecutor::TaskType::JS);
}

RefPtr<AcePage> CardFrontend::GetPage(int32_t pageId) const
{
    if (!delegate_) {
        return nullptr;
    }
    return delegate_->GetPage();
}

const WindowConfig& CardFrontend::GetWindowConfig() const
{
    ParseManifest();
    return manifestParser_->GetWindowConfig();
}

void CardFrontend::LoadPage(const std::string& urlPath, const std::string& params)
{
    auto page = delegate_->CreatePage(0, urlPath);
    page->SetPageParams(params);
    page->SetFlushCallback([weak = WeakClaim(this)](const RefPtr<Framework::JsAcePage>& page) {
        auto front = weak.Upgrade();
        if (front) {
            front->OnPageLoaded(page);
        }
    });

    std::string content;
    if (!Framework::GetAssetContentImpl(assetManager_, urlPath, content)) {
        LOGE("Failed to load page");
        EventReport::SendFormException(FormExcepType::LOAD_PAGE_ERR);
        return;
    }
    ParsePage(holder_.Get(), content, params, page);
}

void CardFrontend::ParsePage(const RefPtr<PipelineContext>& context, const std::string& pageContent,
    const std::string& params, const RefPtr<Framework::JsAcePage>& page)
{
    auto rootBody = Framework::ParseFileData(pageContent);
    if (!rootBody) {
        LOGE("parse index json error");
        return;
    }

    const auto& rootTemplate = rootBody->GetValue("template");
    parseJsCard_ = AceType::MakeRefPtr<Framework::JsCardParser>(context, assetManager_, std::move(rootBody));
    if (!parseJsCard_->Initialize()) {
        LOGE("js card parser initialize fail");
        return;
    }
    parseJsCard_->SetColorMode(colorMode_);
    parseJsCard_->SetDensity(density_);
    parseJsCard_->LoadImageInfo();
    parseJsCard_->CreateDomNode(page, rootTemplate, -1);
    parseJsCard_->ResetNodeId();
    page->FlushCommands();
    if (!params.empty()) {
        parseJsCard_->UpdatePageData(params, page);
    }
}

void CardFrontend::OnPageLoaded(const RefPtr<Framework::JsAcePage>& page)
{
    // Pop all JS command and execute them in UI thread.
    auto jsCommands = std::make_shared<std::vector<RefPtr<Framework::JsCommand>>>();
    page->PopAllCommands(*jsCommands);
    page->SetPipelineContext(holder_.Get());
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), page, jsCommands] {
            auto frontend = weak.Upgrade();
            if (!frontend) {
                return;
            }
            // Flush all JS commands.
            for (const auto& command : *jsCommands) {
                command->Execute(page);
            }

            auto pipelineContext = frontend->holder_.Get();

            auto document = page->GetDomDocument();
            if (frontend->pageLoaded_) {
                page->ClearShowCommand();
                std::vector<NodeId> dirtyNodes;
                page->PopAllDirtyNodes(dirtyNodes);
                if (dirtyNodes.empty()) {
                    return;
                }
                auto rootNodeId = dirtyNodes.front();
                if (rootNodeId == DOM_ROOT_NODE_ID_BASE) {
                    auto patchComponent = page->BuildPagePatch(rootNodeId);
                    if (patchComponent) {
                        pipelineContext->ScheduleUpdate(patchComponent);
                    }
                }
                if (document) {
                    // When a component is configured with "position: fixed", there is a proxy node in root tree
                    // instead of the real composed node. So here updates the real composed node.
                    for (int32_t nodeId : document->GetProxyRelatedNodes()) {
                        auto patchComponent = page->BuildPagePatch(nodeId);
                        if (patchComponent) {
                            pipelineContext->ScheduleUpdate(patchComponent);
                        }
                    }
                }
                return;
            }

            // Just clear all dirty nodes.
            page->ClearAllDirtyNodes();
            if (document) {
                document->HandleComponentPostBinding();
            }
            if (pipelineContext->GetAccessibilityManager()) {
                pipelineContext->GetAccessibilityManager()->HandleComponentPostBinding();
            }
            if (pipelineContext->CanPushPage()) {
                pipelineContext->PushPage(page->BuildPage(page->GetUrl()));
                frontend->pageLoaded_ = true;
                frontend->delegate_->GetJsAccessibilityManager()->SetRunningPage(page);
            }
        },
        TaskExecutor::TaskType::UI);
}

void CardFrontend::UpdateData(const std::string& dataList)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), dataList] {
            auto frontend = weak.Upgrade();
            if (frontend) {
                frontend->UpdatePageData(dataList);
            }
        },
        TaskExecutor::TaskType::JS);
}

void CardFrontend::UpdatePageData(const std::string& dataList)
{
    if (!delegate_ || !parseJsCard_) {
        LOGE("the delegate or parseJsCard is null");
        EventReport::SendFormException(FormExcepType::UPDATE_PAGE_ERR);
        return;
    }
    parseJsCard_->UpdatePageData(dataList, delegate_->GetPage());
}

void CardFrontend::SetColorMode(ColorMode colorMode)
{
    colorMode_ = colorMode;
    if (!delegate_ || !parseJsCard_) {
        LOGI("the delegate is null");
        return;
    }
    parseJsCard_->SetColorMode(colorMode);
    OnMediaFeatureUpdate();
}

void CardFrontend::RebuildAllPages()
{
    if (!delegate_) {
        LOGI("the delegate is null");
        return;
    }
    auto page = delegate_->GetPage();
    taskExecutor_->PostTask(
        [weakPage = WeakPtr<Framework::JsAcePage>(page)] {
            auto page = weakPage.Upgrade();
            if (!page) {
                return;
            }
            auto domDoc = page->GetDomDocument();
            if (!domDoc) {
                return;
            }
            auto rootNode = domDoc->GetDOMNodeById(domDoc->GetRootNodeId());
            if (!rootNode) {
                return;
            }
            rootNode->UpdateStyleWithChildren();
        },
        TaskExecutor::TaskType::UI);
}

void CardFrontend::OnSurfaceChanged(int32_t width, int32_t height)
{
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), width, height] {
            auto frontend = weak.Upgrade();
            if (frontend) {
                frontend->HandleSurfaceChanged(width, height);
            }
        },
        TaskExecutor::TaskType::JS);
}

void CardFrontend::HandleSurfaceChanged(int32_t width, int32_t height)
{
    if (!parseJsCard_) {
        LOGE("the parser is null");
        return;
    }
    parseJsCard_->OnSurfaceChanged(width, height);
    OnMediaFeatureUpdate();
}

void CardFrontend::OnMediaFeatureUpdate()
{
    if (!delegate_ || !parseJsCard_) {
        LOGE("the delegate or parser is null");
        return;
    }
    parseJsCard_->UpdateStyle(delegate_->GetPage());
}

} // namespace OHOS::Ace
