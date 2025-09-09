/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "parallel_page_router_manager.h"
#include "bridge/declarative_frontend/ng/force_split/parallel_page_router_manager.h"

#include <vector>
#include <sstream>

#include "bridge/common/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/base/view_advanced_register.h"
#include "core/components_ng/pattern/stage/force_split/parallel_page_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/image/image_layout_property.h"

namespace OHOS::Ace::NG {

namespace {
constexpr char PLACEHOLDER_PAGE_URL[] = "placeholder";
constexpr char PLACEHOLDER_PAGE_PATH[] = "placeholder.js";
const std::string BG_COLOR_SYS_RES_NAME = "sys.color.ohos_id_color_sub_background";
constexpr int32_t PRIMARY_PAGE_NODE_THRESHOLD = 100;
constexpr int32_t MAX_ROUTER_STACK_SIZE = 32;
constexpr Dimension APP_ICON_SIZE = 64.0_vp;
const std::vector<std::string> PRIMARY_PAGE_PREFIX = {"main", "home", "index", "root"};
}

void ParallelPageRouterManager::LoadPage(
    int32_t pageId, const RouterPageInfo& target, bool needHideLast, bool needTransition, bool isPush)
{
    ACE_SCOPED_TRACE_COMMERCIAL("load page: %s(id:%d)", target.url.c_str(), pageId);
    CHECK_RUN_ON(JS);
    bool needClearSecondaryPage = CheckSecondaryPageNeedClear(isPush);
    if (!CheckStackSize(target, needClearSecondaryPage)) {
        return;
    }
    auto pageNode = CreatePage(pageId, target);
    if (!pageNode) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "failed to create page: %{public}s", target.url.c_str());
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipelineContext->GetStageManager());
    CHECK_NULL_VOID(stageManager);

    RefPtr<FrameNode> preLastPage = nullptr;
    if (!pageRouterStack_.empty()) {
        preLastPage = pageRouterStack_.rbegin()->Upgrade();
    }
    std::list<WeakPtr<FrameNode>> prevPageRouterStack;
    std::copy(pageRouterStack_.begin(), pageRouterStack_.end(), std::back_inserter(prevPageRouterStack));
    auto removePageSize = stageManager->UpdateSecondaryPageNeedRemoved(needClearSecondaryPage);
    while (removePageSize > 0) {
        pageRouterStack_.pop_back();
        removePageSize--;
    };
    pageRouterStack_.emplace_back(pageNode);
    if (intentInfo_.has_value()) {
        if (!OnPageReadyAndHandleIntent(pageNode, needHideLast)) {
            intentInfo_.reset();
            std::swap(prevPageRouterStack, pageRouterStack_);
            TAG_LOGW(AceLogTag::ACE_ROUTER, "OnPageReadyAndHandleIntent Failed");
            return;
        }
    } else if (!OnPageReady(pageNode, needHideLast, needTransition)) {
        std::swap(prevPageRouterStack, pageRouterStack_);
        return;
    }
    stageManager->RemoveSecondaryPagesOfPrimaryHomePage();

    if (DetectPrimaryPage(target, preLastPage)) {
        auto loadPlaceHolderPageCallback = [weakMgr = WeakClaim(this)]() -> RefPtr<FrameNode> {
            auto mgr = weakMgr.Upgrade();
            CHECK_NULL_RETURN(mgr, nullptr);
            return mgr->LoadPlaceHolderPage();
        };
        TAG_LOGI(AceLogTag::ACE_ROUTER, "url: %{public}s was recognised as primary page", target.url.c_str());
        stageManager->OnPrimaryPageDetected(pageNode, std::move(loadPlaceHolderPageCallback), pageRouterStack_);
    }

    pageNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);

    if (!SetOnKeyEvent(pageNode)) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "Fail to init the keyEvent of page");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "LoadPage Success");
}

int32_t ParallelPageRouterManager::GetLastPageIndex()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, -1);
    auto stageManager = pipelineContext->GetStageManager();
    CHECK_NULL_RETURN(stageManager, -1);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_RETURN(stageNode, -1);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, -1);
    auto dividerNode = stagePattern->GetDividerNode();
    if (stagePattern->GetIsSplit() && stageNode->GetChildIndex(dividerNode) >= 0) {
        return pageRouterStack_.size();
    }
    return pageRouterStack_.size() - 1;
}

bool ParallelPageRouterManager::DetectPrimaryPage(const RouterPageInfo& target, const RefPtr<FrameNode>& preLastPage)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, false);

    if (!stageManager->GetDetectPrimaryPageEnable()) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "No need for home page recognition");
        return false;
    }

    if (!ShouldDetectPrimaryPage(context, preLastPage)) {
        return false;
    }

    return JudgePrimaryPage(target);
}
 
bool ParallelPageRouterManager::JudgePrimaryPage(const RouterPageInfo& target)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, false);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, false);

    std::string homePageConfig = stageManager->GetHomePageConfig();
    std::string pageInfo = target.url;
    if (strcmp(homePageConfig.c_str(), pageInfo.c_str()) == 0) {
        TAG_LOGD(AceLogTag::ACE_ROUTER,
            "current page: %{public}s is consistent with home page config", pageInfo.c_str());
        return true;
    }

    int32_t elementNum = ElementRegister::GetInstance()->GetLastestElementId();
    TAG_LOGI(AceLogTag::ACE_ROUTER,
        "Judge primary page, url: %{public}s, lastest elementId: %{public}d", target.url.c_str(), elementNum);
    if (elementNum >= PRIMARY_PAGE_NODE_THRESHOLD) {
        return true;
    }

    std::transform(pageInfo.begin(), pageInfo.end(), pageInfo.begin(), ::tolower);
    std::istringstream stream(pageInfo);
    std::string temp;
    std::string realPage;
    while (getline(stream, temp, '/')) {
        realPage = temp;
    }
    for (auto it = PRIMARY_PAGE_PREFIX.begin(); it != PRIMARY_PAGE_PREFIX.end(); it++) {
        std::string prefix = *it;
        if (realPage.find(prefix) != std::string::npos) {
            return true;
        }
    }
    return false;
}

RefPtr<FrameNode> ParallelPageRouterManager::LoadPlaceHolderPage()
{
    auto pageId = GenerateNextPageId();
    // create pageNode
    ACE_SCOPED_TRACE_COMMERCIAL("load placeholder(id:%d)", pageId);
    CHECK_RUN_ON(JS);
    auto entryPageInfo = AceType::MakeRefPtr<EntryPageInfo>(pageId, PLACEHOLDER_PAGE_URL, PLACEHOLDER_PAGE_PATH, "");
    auto pagePattern = ViewAdvancedRegister::GetInstance()->CreatePagePattern(entryPageInfo);
    auto placeHolderPageNode =
        FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), pagePattern);
    CHECK_NULL_RETURN(placeHolderPageNode, nullptr);

    int32_t stackId = ElementRegister::GetInstance()->MakeUniqueId();
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
    CHECK_NULL_RETURN(stackNode, nullptr);
    stackNode->MountToParent(placeHolderPageNode);
    auto stackContext = stackNode->GetRenderContext();
    CHECK_NULL_RETURN(stackContext, nullptr);
    auto resourceWrapper = CreateResourceWrapper();
    CHECK_NULL_RETURN(resourceWrapper, nullptr);
    Color bgColor = resourceWrapper->GetColorByName(BG_COLOR_SYS_RES_NAME);
    stackContext->UpdateBackgroundColor(bgColor);
    auto stackLayoutProperty = stackNode->GetLayoutProperty();
    CHECK_NULL_RETURN(stackLayoutProperty, nullptr);
    stackLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);

    int32_t imageId = ElementRegister::GetInstance()->MakeUniqueId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, imageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_RETURN(imageNode, nullptr);
    auto pipeline = imageNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto themeConstants = themeManager->GetThemeConstants();
    CHECK_NULL_RETURN(themeConstants, nullptr);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_RETURN(windowManager, nullptr);
    auto id = windowManager->GetAppIconId();
    auto pixelMap = themeConstants->GetPixelMap(id);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(imageLayoutProperty, nullptr);
    CalcSize imageCalcSize((CalcLength(APP_ICON_SIZE)), CalcLength(APP_ICON_SIZE));
    imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
    imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(PixelMap::CreatePixelMap(&pixelMap)));
    imageNode->MountToParent(stackNode);
    imageNode->MarkModifyDone();

    if (!SetOnKeyEvent(placeHolderPageNode)) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "fail to init key event handler of SystemPlaceHolder");
        return nullptr;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "success to load SystemPlaceHolder");
    return placeHolderPageNode;
}

RefPtr<ResourceWrapper> ParallelPageRouterManager::CreateResourceWrapper()
{
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    RefPtr<ThemeConstants> themeConstants = nullptr;
    if (SystemProperties::GetResourceDecoupling()) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(Container::CurrentIdSafely());
        if (!resourceAdapter) {
            return nullptr;
        }
    } else {
        themeConstants = Framework::JSViewAbstract::GetThemeConstants();
        if (!themeConstants) {
            return nullptr;
        }
    }
    auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
    return resourceWrapper;
}

bool ParallelPageRouterManager::ShouldDetectPrimaryPage(
    const RefPtr<PipelineContext>& context, const RefPtr<FrameNode>& preLastPage)
{
    CHECK_NULL_RETURN(context, false);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_RETURN(stageManager, false);
    auto stageNode = stageManager->GetStageNode();
    CHECK_NULL_RETURN(stageNode, false);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto primaryNode = stagePattern->GetPrimaryPage().Upgrade();
    if (!primaryNode) {
        return true;
    }

    if (!isNewPageReplacing_) {
        return false;
    }

    CHECK_NULL_RETURN(preLastPage, false);
    auto preLastPattern = preLastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(preLastPattern, false);
    if (preLastPattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
        // we need to detect new primary page when replace top primarypage.
        return true;
    }

    return false;
}

void ParallelPageRouterManager::RefreshAllPageIndex()
{
    int32_t startIndex = 1;
    for (auto it = pageRouterStack_.begin(); it != pageRouterStack_.end(); ++it, ++startIndex) {
        auto pageNode = it->Upgrade();
        if (!pageNode) {
            continue;
        }
        auto pagePattern = pageNode->GetPattern<PagePattern>();
        if (pagePattern) {
            pagePattern->GetPageInfo()->SetPageIndex(startIndex);
        }
    }
}

bool ParallelPageRouterManager::SetOnKeyEvent(const RefPtr<FrameNode> &pageNode)
{
    auto focusHub = pageNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipelineContext->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    WeakPtr<ParallelStageManager> weakManager = stageManager;

    bool initFlag = true;
    auto onKeyEventCallback = [weakManager, initFlag](const KeyEvent& event) mutable -> bool {
        if (event.code != KeyCode::KEY_TAB || event.action != KeyAction::DOWN) {
            return false;
        }
        auto stageManager = weakManager.Upgrade();
        CHECK_NULL_RETURN(stageManager, false);
        return stageManager->ExchangePageFocus(initFlag);
    };

    focusHub->SetOnKeyEventInternal(std::move(onKeyEventCallback));
    return true;
}

bool ParallelPageRouterManager::CheckSecondaryPageNeedClear(bool isPush)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto stageManager = AceType::DynamicCast<ParallelStageManager>(pipelineContext->GetStageManager());
    CHECK_NULL_RETURN(stageManager, false);
    if (pageRouterStack_.empty()) {
        stageManager->SetNeedClearSecondaryPage(false);
        return false;
    }
    auto preTopPage = pageRouterStack_.back().Upgrade();
    if (preTopPage) {
        auto preTopPagePattern = preTopPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(preTopPagePattern, false);
        auto needClearSecondaryPage = isPush && RouterPageType::SECONDARY_PAGE == preTopPagePattern->GetPageType()
            && stageManager->GetPrimaryPageTouched();
        stageManager->SetNeedClearSecondaryPage(needClearSecondaryPage);
        return needClearSecondaryPage;
    }
    stageManager->SetNeedClearSecondaryPage(false);
    return false;
}

bool ParallelPageRouterManager::CheckStackSize(const RouterPageInfo& target, bool needClearSecondaryPage)
{
    // Dont't block push operation when trigger secondaryPage clear
    if (needClearSecondaryPage) {
        return true;
    }
    if (GetStackSize() >= MAX_ROUTER_STACK_SIZE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "Router stack size is larger than max size 32.");
        if (target.errorCallback != nullptr) {
            target.errorCallback("The pages are pushed too much.", ERROR_CODE_PAGE_STACK_FULL);
        }
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG
