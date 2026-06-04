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
#include "core/accessibility/accessibility_manager.h"

#include <tuple>
#include <type_traits>
#include <utility>

namespace OHOS::Ace {
namespace {

const char MANIFEST_JSON[] = "manifest.json";
const char FILE_TYPE_JSON[] = ".json";

template<typename Owner, typename... Args>
struct WeakDispatchTask {
    using Dispatch = void (*)(Owner&, const Args& ...);

    WeakPtr<Owner> weak;
    Dispatch dispatch;
    std::tuple<Args...> args;

    void operator()() const
    {
        auto target = weak.Upgrade();
        if (!target) {
            return;
        }
        std::apply(
            [this, &target](const auto&... unpacked) {
                dispatch(*target, unpacked...);
            },
            args);
    }
};

template<typename Owner, typename... Args>
WeakDispatchTask<Owner, std::decay_t<Args>...> MakeWeakDispatchTask(
    const WeakPtr<Owner>& weak, typename WeakDispatchTask<Owner, std::decay_t<Args>...>::Dispatch dispatch,
    Args&&... args)
{
    return { weak, dispatch, std::tuple<std::decay_t<Args>...>{std::forward<Args>(args)...} };
}

} // namespace

CardFrontend::~CardFrontend()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "CardFrontend Destroyed");
}

bool CardFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    type_ = type;
    taskExecutor_ = taskExecutor;
    delegate_ = AceType::MakeRefPtr<Framework::CardFrontendDelegate>();
    manifestParser_ = AceType::MakeRefPtr<Framework::ManifestParser>();
    return true;
}

void CardFrontend::Destroy()
{
    CHECK_RUN_ON(JS);
    TAG_LOGI(AceLogTag::ACE_FORM, "CardFrontend Destroy begin.");
    parseJsCard_.Reset();
    delegate_.Reset();
    eventHandler_.Reset();
}

void CardFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    auto pipelineContext = DynamicCast<PipelineContext>(context);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(pipelineContext);
    eventHandler_ = AceType::MakeRefPtr<CardEventHandler>(delegate_);
    pipelineContext->RegisterEventHandler(eventHandler_);
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
            TAG_LOGW(AceLogTag::ACE_FORM, "RunPage parse manifest.json failed");
            return;
        }
        manifestParser_->Parse(jsonContent);
    });
}

UIContentErrorCode CardFrontend::RunPage(const std::string& url, const std::string& params)
{
    std::string urlPath;
    if (GetFormSrc().empty()) {
        ParseManifest();
        if (!url.empty()) {
            urlPath = manifestParser_->GetRouter()->GetPagePath(url, FILE_TYPE_JSON);
        }
        if (urlPath.empty()) {
            urlPath = manifestParser_->GetRouter()->GetEntry(FILE_TYPE_JSON);
        }
    } else {
        urlPath = GetFormSrcPath(GetFormSrc(), FILE_TYPE_JSON);
    }
    if (urlPath.empty()) {
        TAG_LOGW(AceLogTag::ACE_FORM, "fail to run page due to path url is empty");
        return UIContentErrorCode::NULL_URL;
    }
    using Dispatch = WeakDispatchTask<CardFrontend, std::string, std::string>::Dispatch;
    static constexpr Dispatch dispatch = [](CardFrontend& frontend, const std::string& loadUrlPath,
                                         const std::string& loadParams) {
        frontend.LoadPage(loadUrlPath, loadParams);
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), dispatch, urlPath, params), TaskExecutor::TaskType::JS,
        "ArkUICardFrontendRunPage");
    
    return UIContentErrorCode::NO_ERRORS;
}

std::string CardFrontend::GetFormSrcPath(const std::string& uri, const std::string& suffix) const
{
    if (uri.empty()) {
        return "";
    }
    // the case uri is starts with "/" and "/" is the mainPage
    if (uri.size() != 0) {
        return uri + suffix;
    }

    return "";
}

RefPtr<AcePage> CardFrontend::GetPage(int32_t pageId) const
{
    CHECK_NULL_RETURN(delegate_, nullptr);
    return delegate_->GetPage();
}

WindowConfig& CardFrontend::GetWindowConfig()
{
    ParseManifest();
    if (GetFormSrc().empty()) {
        if (!manifestParser_) {
            static WindowConfig windowConfig;
            TAG_LOGW(AceLogTag::ACE_FORM, "manifestParser is null, return default config");
            return windowConfig;
        }
        return manifestParser_->GetWindowConfig();
    } else {
        return GetCardWindowConfig();
    }
}

void CardFrontend::LoadPage(const std::string& urlPath, const std::string& params)
{
    CHECK_RUN_ON(JS);
    CHECK_NULL_VOID(delegate_);
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
        TAG_LOGW(AceLogTag::ACE_FORM, "Failed to load page");
        return;
    }
    ParsePage(holder_.Get(), content, params, page);
}

void CardFrontend::ParsePage(const RefPtr<PipelineBase>& context, const std::string& pageContent,
    const std::string& params, const RefPtr<Framework::JsAcePage>& page)
{
    CHECK_RUN_ON(JS);
    auto rootBody = Framework::ParseFileData(pageContent);
    CHECK_NULL_VOID(rootBody);

    const auto& rootTemplate = rootBody->GetValue("template");
    parseJsCard_ = AceType::MakeRefPtr<Framework::JsCardParser>(context, assetManager_, std::move(rootBody));
    if (!parseJsCard_->Initialize()) {
        TAG_LOGW(AceLogTag::ACE_FORM, "js card parser initialize fail");
        return;
    }
    parseJsCard_->SetColorMode(colorMode_);
    parseJsCard_->SetDensity(density_);
    parseJsCard_->LoadImageInfo();
    parseJsCard_->SetCardHapPath(cardHapPath_);
    parseJsCard_->CreateDomNode(page, rootTemplate, -1);
    parseJsCard_->ResetNodeId();
    page->FlushCommands();
    if (!params.empty()) {
        parseJsCard_->UpdatePageData(params, page);
    }
}

void CardFrontend::OnPageLoaded(const RefPtr<Framework::JsAcePage>& page)
{
    CHECK_RUN_ON(JS);
    // Pop all JS command and execute them in UI thread.
    auto jsCommands = std::make_shared<std::vector<RefPtr<Framework::JsCommand>>>();
    page->PopAllCommands(*jsCommands);
    page->SetPipelineContext(holder_.Get());
    using PageLoadedDispatch =
        WeakDispatchTask<CardFrontend, RefPtr<Framework::JsAcePage>,
            std::shared_ptr<std::vector<RefPtr<Framework::JsCommand>>>>::Dispatch;
    static constexpr PageLoadedDispatch pageLoadedDispatch =
        [](CardFrontend& frontend, const RefPtr<Framework::JsAcePage>& loadedPage,
            const std::shared_ptr<std::vector<RefPtr<Framework::JsCommand>>>& commands) {
            for (const auto& command : *commands) {
                command->Execute(loadedPage);
            }

            auto pipelineContext = AceType::DynamicCast<PipelineContext>(frontend.holder_.Get());
            CHECK_NULL_VOID(pipelineContext);
            auto minSdk = frontend.manifestParser_->GetMinPlatformVersion();
            pipelineContext->SetMinPlatformVersion(minSdk);

            auto document = loadedPage->GetDomDocument();
            if (frontend.pageLoaded_) {
                loadedPage->ClearShowCommand();
                std::vector<NodeId> dirtyNodes;
                loadedPage->PopAllDirtyNodes(dirtyNodes);
                if (dirtyNodes.empty()) {
                    return;
                }
                auto rootNodeId = dirtyNodes.front();
                if (rootNodeId == DOM_ROOT_NODE_ID_BASE) {
                    auto patchComponent = loadedPage->BuildPagePatch(rootNodeId);
                    if (patchComponent) {
                        pipelineContext->ScheduleUpdate(patchComponent);
                    }
                }
                if (document) {
                    // When a component is configured with "position: fixed", there is a proxy node in root tree
                    // instead of the real composed node. So here updates the real composed node.
                    for (int32_t nodeId : document->GetProxyRelatedNodes()) {
                        auto patchComponent = loadedPage->BuildPagePatch(nodeId);
                        if (patchComponent) {
                            pipelineContext->ScheduleUpdate(patchComponent);
                        }
                    }
                }
                return;
            }

            loadedPage->ClearAllDirtyNodes();
            if (document) {
                document->HandleComponentPostBinding();
            }
            if (pipelineContext->GetAccessibilityManager()) {
                pipelineContext->GetAccessibilityManager()->HandleComponentPostBinding();
            }
            if (pipelineContext->CanPushPage()) {
                pipelineContext->PushPage(loadedPage->BuildPage(loadedPage->GetUrl()));
                frontend.pageLoaded_ = true;
                if (frontend.delegate_) {
                    frontend.delegate_->GetJsAccessibilityManager()->SetRunningPage(loadedPage);
                }
            }
        };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), pageLoadedDispatch, page, jsCommands),
        TaskExecutor::TaskType::UI, "ArkUICardFrontendPageLoaded");
    using FireVisibleDispatch = WeakDispatchTask<CardFrontend>::Dispatch;
    static constexpr FireVisibleDispatch fireVisibleDispatch = [](CardFrontend& frontend) {
        frontend.FireFormVisiableCallback();
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), fireVisibleDispatch), TaskExecutor::TaskType::UI,
        "ArkUICardFrontendFireFormVisiable");
}

void CardFrontend::UpdateData(const std::string& dataList)
{
    using Dispatch = WeakDispatchTask<CardFrontend, std::string>::Dispatch;
    static constexpr Dispatch dispatch = [](CardFrontend& frontend, const std::string& updateDataList) {
        frontend.UpdatePageData(updateDataList);
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), dispatch, dataList), TaskExecutor::TaskType::JS,
        "ArkUICardFrontendUpdatePageData");
}

void CardFrontend::UpdatePageData(const std::string& dataList)
{
    CHECK_RUN_ON(JS);
    if (!delegate_ || !parseJsCard_) {
        TAG_LOGW(AceLogTag::ACE_FORM, "the delegate or parseJsCard is null");
        return;
    }
    parseJsCard_->UpdatePageData(dataList, delegate_->GetPage());
}

void CardFrontend::SetColorMode(ColorMode colorMode)
{
    using Dispatch = WeakDispatchTask<CardFrontend, ColorMode>::Dispatch;
    static constexpr Dispatch dispatch = [](CardFrontend& frontend, const ColorMode& newColorMode) {
        frontend.colorMode_ = newColorMode;
        if (!frontend.delegate_ || !frontend.parseJsCard_) {
            return;
        }
        frontend.parseJsCard_->SetColorMode(frontend.colorMode_);
        frontend.OnMediaFeatureUpdate();
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), dispatch, colorMode), TaskExecutor::TaskType::JS,
        "ArkUICardFrontendSetColorMode");
}

void CardFrontend::RebuildAllPages()
{
    CHECK_NULL_VOID(delegate_);
    auto page = delegate_->GetPage();
    using Dispatch = WeakDispatchTask<Framework::JsAcePage>::Dispatch;
    static constexpr Dispatch dispatch = [](Framework::JsAcePage& targetPage) {
        auto domDoc = targetPage.GetDomDocument();
        CHECK_NULL_VOID(domDoc);
        auto rootNode = domDoc->GetDOMNodeById(domDoc->GetRootNodeId());
        CHECK_NULL_VOID(rootNode);
        rootNode->UpdateStyleWithChildren();
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(WeakPtr<Framework::JsAcePage>(page), dispatch),
        TaskExecutor::TaskType::UI, "ArkUICardFrontendRebuildAllPages");
}

void CardFrontend::OnSurfaceChanged(int32_t width, int32_t height)
{
    using Dispatch = WeakDispatchTask<CardFrontend, int32_t, int32_t>::Dispatch;
    static constexpr Dispatch dispatch = [](CardFrontend& frontend, const int32_t& changedWidth,
                                         const int32_t& changedHeight) {
        frontend.HandleSurfaceChanged(changedWidth, changedHeight);
    };
    taskExecutor_->PostTask(
        MakeWeakDispatchTask(AceType::WeakClaim(this), dispatch, width, height),
        TaskExecutor::TaskType::JS, "ArkUICardFrontendSurfaceChanged");
}

void CardFrontend::HandleSurfaceChanged(int32_t width, int32_t height)
{
    CHECK_RUN_ON(JS);
    CHECK_NULL_VOID(parseJsCard_);
    parseJsCard_->OnSurfaceChanged(width, height);
    OnMediaFeatureUpdate();
}

void CardFrontend::OnMediaFeatureUpdate()
{
    CHECK_RUN_ON(JS);
    CHECK_NULL_VOID(delegate_);
    CHECK_NULL_VOID(parseJsCard_);
    parseJsCard_->UpdateStyle(delegate_->GetPage());
}
} // namespace OHOS::Ace
