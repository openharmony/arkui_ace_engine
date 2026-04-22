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

#include "core/components_ng/pattern/stage/force_split/parallel_stage_manager.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"

#include <list>

#include "base/json/json_util.h"
#include "base/log/ace_checker.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"

namespace OHOS::Ace::NG {
namespace {
const RefPtr<InterpolatingSpring> ROUTER_SPLIT_POP_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f,
    342.0f, 37.0f);
const RefPtr<InterpolatingSpring> ROUTER_SPLIT_PUSH_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f,
    328.0f, 36.0f);

PageTransitionType GetRouterPushHideTransitionType(bool useRouterColumnAnimation)
{
    return useRouterColumnAnimation ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE;
}

PageTransitionType GetRouterPushShowTransitionType(bool useRouterColumnAnimation)
{
    return useRouterColumnAnimation ? PageTransitionType::ENTER_PUSH : PageTransitionType::NONE;
}

PageTransitionType GetRouterPopHideTransitionType(bool useRouterColumnAnimation)
{
    return useRouterColumnAnimation ? PageTransitionType::EXIT_POP : PageTransitionType::NONE;
}

PageTransitionType GetRouterPopShowTransitionType(bool useRouterColumnAnimation)
{
    return useRouterColumnAnimation ? PageTransitionType::ENTER_POP : PageTransitionType::NONE;
}

bool GetEffectiveRouterStagePage(
    const RefPtr<UINode>& child, RefPtr<FrameNode>& page, RouterPageType& pageType)
{
    page = AceType::DynamicCast<FrameNode>(child);
    if (!page || page->GetTag() != V2::PAGE_ETS_TAG) {
        return false;
    }
    auto pattern = page->GetPattern<ParallelPagePattern>();
    if (!pattern) {
        return false;
    }
    pageType = pattern->GetPageType();
    return pageType != RouterPageType::PLACEHOLDER_PAGE && pageType != RouterPageType::RELATED_PAGE;
}

}

ParallelStageManager::ParallelStageManager(const RefPtr<FrameNode>& stageNode) : StageManager(stageNode)
{
    CHECK_NULL_VOID(stageNode_);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    stagePattern->SetModeChangeCallback([weakMgr = WeakClaim(this)]() {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->OnModeChange();
    });
    stagePattern->SetWindowStateChangeCallback([weakMgr = WeakClaim(this)](bool show) {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->OnWindowStateChange(show);
    });
}

void ParallelStageManager::OnModeChange()
{
    StageOptScope scope(this);
    CHECK_NULL_VOID(stageNode_);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return;
    }
    auto lastPage = GetLastPage();
    CHECK_NULL_VOID(lastPage);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (IsVirtualStackBasedSplit()) {
        OnModeChangeInVirtualStackBasedSplit(lastPage);
        return;
    }
    if (stagePattern->GetIsSplit()) {  // stack -> split
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page mode change to split");
        AbortAnimation();
        auto homePage = GetHomePage();
        CHECK_NULL_VOID(homePage);
        if (homePage != lastPage) {
            FireParallelPageShow(homePage, PageTransitionType::NONE, false);
            return;
        }
        auto page = GetRelatedOrPlaceHolderPage();
        MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, PageTransitionType::NONE);
        return;
    }

    // split -> stack
    TAG_LOGI(AceLogTag::ACE_ROUTER, "page mode change to stack");
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(lastPattern);
    auto type = lastPattern->GetPageType();
    if (type != RouterPageType::PLACEHOLDER_PAGE && type != RouterPageType::RELATED_PAGE) {
        auto homePage = GetHomePage();
        if (homePage && lastPage != homePage) {
            FireParallelPageHide(homePage, PageTransitionType::NONE);
            UpdatePageFocus(lastPage);
        }
        return;
    }
    FireParallelPageHide(lastPage, PageTransitionType::NONE);
    stageNode_->RemoveChild(lastPage);
}

void ParallelStageManager::OnWindowStateChange(bool show)
{
    TAG_LOGI(AceLogTag::ACE_ROUTER, "window state change to %{public}s", show ? "show" : "hide");
    StageOptScope scope(this);
    CHECK_NULL_VOID(stageNode_);
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    auto lastPage = GetLastPage();
    CHECK_NULL_VOID(lastPage);
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(lastPattern);
    if (!stagePattern->GetIsSplit()) {
        if (show) {
            lastPattern->OnShow(true);
        } else {
            lastPattern->OnHide(true);
        }
        return;
    }

    if (IsVirtualStackBasedSplit()) {
        OnWindowStateChangeInVirtualStackBasedSplit(show);
        return;
    }

    auto homePage = GetHomePage();
    if (show) {
        if (homePage && homePage != lastPage) {
            auto homePattern = homePage->GetPattern<ParallelPagePattern>();
            CHECK_NULL_VOID(homePattern);
            homePattern->OnShow(true);
        }
        lastPattern->OnShow(true);
        return;
    }

    lastPattern->OnHide(true);
    if (homePage && homePage != lastPage) {
        auto homePattern = homePage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(homePattern);
        homePattern->OnHide(true);
    }
}

RefPtr<FrameNode> ParallelStageManager::GetHomePage() const
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    for (auto it = children.rbegin(); it != children.rend(); ++it) {
        auto node = AceType::DynamicCast<FrameNode>(*it);
        if (!node) {
            continue;
        }
        auto pattern = node->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        if (pattern->GetPageType() == RouterPageType::HOME_PAGE) {
            return node;
        }
    }
    return nullptr;
}

void ParallelStageManager::FirePageHideOnPushPage(
    RouterPageType newPageType, const RefPtr<FrameNode>& lastPage, const RefPtr<FrameNode>& topRelatedOrPhPage,
    const RefPtr<FrameNode>& preHomePage, PageTransitionType hideTransitionType, bool newPageIsFullScreenPage)
{
    auto lastPagePattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(lastPagePattern);
    auto lastPageType = lastPagePattern->GetPageType();
    if (newPageType == RouterPageType::DETAIL_PAGE) {
        /**
         * push/replace: [ PrimaryA | SecondaryA/PlaceHolder/RelatedPage ]  ->  [ PrimaryA | SecondaryB ]
         *  The last page needs to trigger the onPageHide lifecycle.
         *
         * push/replace: [ PrimaryA | empty ]  ->  [ PrimaryA | SecondaryB ]
         *  The last page(PrimaryA) does not need to trigger the onPageHide lifecycle.
         */
        if (lastPage != preHomePage || newPageIsFullScreenPage) {
            FireParallelPageHide(lastPage, hideTransitionType);
        }
        if (!isNewPageReplacing_) {
            return;
        }
        /**
         * when replacing page in new life cycle.
         *  step1: PushPage(current step)
         *  step2: move page node position
         *  step3: PopPage
         *
         *  replace: [ PrimaryA | RelatedPage/PlaceHolder ] -> [ SecondaryA ]
         *  replace: [ PrimaryA | empty ] -> [ SecondaryA ]
         *   need to notify PrimaryA's onPageHide
         */
        if (((lastPageType == RouterPageType::PLACEHOLDER_PAGE || lastPageType == RouterPageType::RELATED_PAGE) &&
            preHomePage) || (lastPage == preHomePage)) {
            FireParallelPageHide(preHomePage, hideTransitionType);
        }
        return;
    }
    // node -> RouterPageType::HOME_PAGE
    if (topRelatedOrPhPage) {
        /**
         * [ PrimaryA | PlaceHolder/Related ]  ->  [ PrimaryB | PlaceHolder/Related ]
         *  PrimaryA -> onPageHide
         */
        if (preHomePage) {
            FireParallelPageHide(preHomePage, hideTransitionType);
        }
        return;
    }
    /**
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolder/Related ]
     * [ SecondaryA ] -> [ PrimaryB | PlaceHolder/Related ]
     *  SecondaryA -> onPageHide
     *  PrimaryA? -> onPageHide
     */
    FireParallelPageHide(lastPage, hideTransitionType);
    if (preHomePage && preHomePage != lastPage) {
        FireParallelPageHide(preHomePage, hideTransitionType);
    }
}

void ParallelStageManager::FirePageShowOnPushPage(const RefPtr<FrameNode>& newTopPage,
    const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType showTransitionType)
{
    if (newTopPattern->GetPageType() == RouterPageType::DETAIL_PAGE) {
        /**
         * push: [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]  ->  [ PrimaryA | SecondaryB ]
         *  SecondaryB -> onPageShow
         * replace: [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ] -> [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);
        return;
    }

    // newTopPage -> RouterPageType::HOME_PAGE
    /**
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolder/RelatedPage ]
     * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ PrimaryB | PlaceHolder/RelatedPage ]
     * [ SecondaryA ] -> [ PrimaryB | PlaceHolder/RelatedPage ]
     *  PrimaryB -> onPageShow
     *  PlaceHolder/RelatedPage -> aboutToAppear?
     *  PlaceHolder/RelatedPage -> onPageShow
     */
    FireParallelPageShow(newTopPage, showTransitionType);

    if (isNewPageReplacing_) {
        /**
         * when replacing page in new life cycle.
         *  step1: PushPage(current step)
         *  step2: move page node position
         *  step3: PopPage
         *
         *  do not mount & show placeHolder in step1,
         *  mount & show placeHolder in step3
         */
        return;
    }

    auto page = GetRelatedOrPlaceHolderPage();
    MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
}

bool ParallelStageManager::PushPage(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition,
    const std::function<bool()>&& pushIntentPageCallback)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    CHECK_NULL_RETURN(node, false);
    auto newTopPattern = node->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(newTopPattern, false);
    newTopPattern->InitOnTouchEvent();
    if (!stagePattern->GetIsSplit() && !isTopFullScreenPageChanged_) {
        bool result = StageManager::PushPage(node, needHideLast, needTransition, std::move(pushIntentPageCallback));
        InvalidateRouterColumnNodes();
        auto homePage = GetHomePage();
        stagePattern->SetHomePage(homePage);
        return result;
    }

    if (newTopPattern->GetPageType() != RouterPageType::DETAIL_PAGE) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "New routerPage must be detail page in SplitMode");
        return false;
    }
    bool isEmpty = IsEmptyInSplitMode();
    needTransition &= !isEmpty;
    if (isEmpty) {
        auto pageInfo = newTopPattern->GetPageInfo();
        CHECK_NULL_RETURN(pageInfo, false);
        auto pagePath = pageInfo->GetFullPath();
        ACE_SCOPED_TRACE_COMMERCIAL("Router Main Page: %s", pagePath.c_str());
    }

    auto isNewLifecycle = AceApplicationInfo::GetInstance()
        .GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE);
    if (IsVirtualStackBasedSplit()) {
        return PushPageInVirtualStackBasedSplit(node, isNewLifecycle, needHideLast, needTransition);
    }
    return PushPageInSplitMode(node, isNewLifecycle, needHideLast, needTransition);
}

bool ParallelStageManager::PushPageInSplitMode(const RefPtr<FrameNode>& newPageNode,
    bool isNewLifecycle, bool needHideLast, bool needTransition)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto newTopPattern = newPageNode->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(newTopPattern, false);
    auto newPageInfo = newTopPattern->GetPageInfo();
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    bool newPageIsFullScreenPage = newPageInfo && forceSplitMgr ?
        forceSplitMgr->IsFullScreenPage(newPageInfo->GetPageUrl()) : false;
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto preHomePage = stagePattern->GetHomePage();
    auto preTopPage = GetLastPage();
    RefPtr<FrameNode> lastPage = nullptr;
    if (!IsEmptyInSplitMode()) {
        lastPage = GetLastPage();
        CHECK_NULL_RETURN(lastPage, false);
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }

    RefPtr<FrameNode> topRelatedOrPhPage = nullptr;
    if (!RemoveRelatedOrPlaceHolderPageIfExist(topRelatedOrPhPage, false)) {
        return false;
    }

    PageTransitionType hideTransitionType = PageTransitionType::NONE;
    RefPtr<FrameNode> hidePageNode;
    if (!IsEmptyInSplitMode() && needHideLast) {
        hidePageNode = lastPage;
        if (!isNewLifecycle) {
            FirePageHideOnPushPage(newTopPattern->GetPageType(), lastPage, topRelatedOrPhPage,
                preHomePage, hideTransitionType, newPageIsFullScreenPage);
        }
    }

    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    newPageNode->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    newPageNode->MountToParent(stageNode_);
    // then build the total child. Build will trigger page create and onAboutToAppear
    newPageNode->Build(nullptr);

    // fire top SecondaryPage lifecycle if need to clear
    if (needClearSecondaryPage_ && !secondaryPageStack_.empty() && preTopPage) {
        FirePageHideOnPopPage(topRelatedOrPhPage, preTopPage, newPageNode, newTopPattern, hideTransitionType);
    }

    // fire new lifecycle
    if (hidePageNode && needHideLast && isNewLifecycle) {
        FirePageHideOnPushPage(newTopPattern->GetPageType(), lastPage, topRelatedOrPhPage,
            preHomePage, hideTransitionType, newPageIsFullScreenPage);
    }
    stageNode_->RebuildRenderContextTree();

    FirePageShowOnPushPage(newPageNode, newTopPattern, PageTransitionType::NONE);

    auto homePage = GetHomePage();
    stagePattern->SetHomePage(homePage);

    stagePattern_->SetCurrentPageIndex(newTopPattern->GetPageInfo()->GetPageId());
    // close keyboard
    PageChangeCloseKeyboard();
    AddPageTransitionTrace(lastPage, newPageNode);
    FireAutoSave(lastPage, newPageNode);

    // flush layout task.
    if (!stageNode_->GetGeometryNode()->GetMarginFrameSize().IsPositive()) {
        // in first load case, wait for window size.
        TAG_LOGI(AceLogTag::ACE_ROUTER, "waiting for window size");
        return true;
    }
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    newPageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition) {
        ReportPageTransitionEnd(newPageNode);
    }
    return true;
}

bool ParallelStageManager::FirePageHideOnPopPage(const RefPtr<FrameNode>& relatedOrPhPage,
    const RefPtr<FrameNode>& preTopPage, const RefPtr<FrameNode>& newTopPage,
    const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType hideTransitionType)
{
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto preTopPattern = preTopPage->GetPattern<ParallelPagePattern>();
    auto preType = preTopPattern->GetPageType();
    if (preType == RouterPageType::DETAIL_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryA -> onPageHide
         */
        FireParallelPageHide(preTopPage, hideTransitionType);
        return true;
    }
    if (preType == RouterPageType::HOME_PAGE) {
        /**
         * replace(SecondaryA, single)
         * stack bottom -> stack top
         * [ SecondaryA ] [ PrimaryB ] -> [ SecondaryA ]
         *  step1: MovePageToFront
         *             Remove PrimaryB's RelatedPage/PlaceHolder, and then move SecondaryA to top
         *  step2: move page position
         *             Swap PrimaryB and SecondaryA
         *  step3: PopPage(current step)
         *             Remove PrimaryB
         *  we need to hide PrimaryB's RelatedPage/PlaceHolder in step3.
         */
        auto tempRelatedOrPhPage = relatedOrPhPage;
        if (isNewPageReplacing_ && !tempRelatedOrPhPage) {
            tempRelatedOrPhPage = GetRelatedOrPlaceHolderPage();
        }

        /**
         * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ xxx ]
         * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ xxx | xxx ]
         * [ PrimaryA | noPlaceHolder ]  ->  xxx    (newPageReplacing)
         *  PlaceHolder/RelatedPage? -> onPageHide
         *  PrimaryA -> onPageHide
         */
        if (tempRelatedOrPhPage) {
            FireParallelPageHide(tempRelatedOrPhPage, hideTransitionType);
        }
        FireParallelPageHide(preTopPage, hideTransitionType);
        return true;
    }
    TAG_LOGW(AceLogTag::ACE_ROUTER, "unexpected pre top page type: %{public}d", static_cast<int32_t>(preType));
    return false;
}

bool ParallelStageManager::FirePageShowOnPopPage(const RefPtr<FrameNode>& relatedOrPhPage,
    const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
    const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
    PageTransitionType showTransitionType)
{
    auto preType = preTopPattern->GetPageType();
    auto newType = newTopPattern->GetPageType();
    if (preType == RouterPageType::DETAIL_PAGE) {
        if (newType == RouterPageType::DETAIL_PAGE) {
            /**
             * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
             * [ SecondaryA ]  ->  [ SecondaryB ]
             *  SecondaryB -> onPageShow
             */
            FireParallelPageShow(newTopPage, showTransitionType);
            return true;
        }
        if (newType == RouterPageType::HOME_PAGE) {
            /**
             * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | PlaceHolder/RelatedPage ]
             *  PlaceHolder/RelatedPage -> aboutToAppear
             *  PlaceHolder/RelatedPage -> onPageShow
             */
            auto page = GetRelatedOrPlaceHolderPage();
            MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
            return true;
        }
        TAG_LOGW(AceLogTag::ACE_ROUTER, "unexpected newTopPage type: %{public}d when preTopPage type is: %{public}d",
            static_cast<int32_t>(newType), static_cast<int32_t>(preType));
        return false;
    }
    if (preType == RouterPageType::HOME_PAGE) {
        if (!relatedOrPhPage && !isNewPageReplacing_) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "HomePage has no placeHolder/related Page in split mode");
        }
        if (newType == RouterPageType::DETAIL_PAGE) {
            /**
             * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ PrimaryB | SecondaryA ]
             * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ SecondaryA ]
             *  SecondaryA -> onPageShow
             */
            FireParallelPageShow(newTopPage, showTransitionType);
            return true;
        }
        if (newType == RouterPageType::HOME_PAGE) {
            /**
             * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | PlaceHolderB ]
             *  PrimaryB -> onPageShow
             *  PlaceHolderB -> aboutToAppear
             *  PlaceHolderB -> onPageShow
             */
            FireParallelPageShow(newTopPage, showTransitionType);
            auto page = GetRelatedOrPlaceHolderPage();
            MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
            return true;
        }
        TAG_LOGI(AceLogTag::ACE_ROUTER, "unexpected new Top page type: %{public}d", static_cast<int32_t>(newType));
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "unexpected pre Top page type: %{public}d", static_cast<int32_t>(preType));
    return false;
}

bool ParallelStageManager::PopPage(const RefPtr<FrameNode>& pageNode, bool needShowNext, bool needTransition)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    if (!stagePattern->GetIsSplit() && !isTopFullScreenPageChanged_) {
        bool result = StageManager::PopPage(pageNode, needShowNext, needTransition);
        InvalidateRouterColumnNodes();
        auto homePage = GetHomePage();
        stagePattern->SetHomePage(homePage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
    }
    if (IsVirtualStackBasedSplit()) {
        return PopPageInVirtualStackBasedSplit(needShowNext, needTransition);
    }
    return PopPageInSplitMode(needShowNext, needTransition);
}

bool ParallelStageManager::PopPageInSplitMode(bool needShowNext, bool needTransition)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    const int32_t transitionPageSize = 2;
    const auto& children = stageNode_->GetChildren();
    int32_t pageNumber = 0;
    if (!GetPageNumberExcludeRelatedOrPlaceHolderPage(pageNumber)) {
        return false;
    }
    needTransition &= (pageNumber >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    RefPtr<FrameNode> relatedOrPhPage = nullptr;
    if (!RemoveRelatedOrPlaceHolderPageIfExist(relatedOrPhPage, !isNewPageReplacing_)) {
        return false;
    }

    auto preTopPage = GetLastPage();
    CHECK_NULL_RETURN(preTopPage, false);
    auto preTopPattern = preTopPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(preTopPattern, false);
    RefPtr<FrameNode> newTopPage = nullptr;
    RefPtr<ParallelPagePattern> newTopPattern = nullptr;
    if (pageNumber >= transitionPageSize) {
        newTopPage = AceType::DynamicCast<FrameNode>(*(++children.rbegin()));
        CHECK_NULL_RETURN(newTopPage, false);
        newTopPattern = newTopPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(newTopPattern, false);
    }

    if (!FirePageHideOnPopPage(relatedOrPhPage, preTopPage, newTopPage, newTopPattern, PageTransitionType::NONE)) {
        return false;
    }

    PageTransitionType showTransitionType = PageTransitionType::NONE;
    if (needShowNext && pageNumber >= transitionPageSize) {
        if (!FirePageShowOnPopPage(
            relatedOrPhPage, preTopPage, preTopPattern, newTopPage, newTopPattern, showTransitionType)) {
            return false;
        }
    }
    do {
        if (!isNewPageReplacing_) {
            break;
        }
        /**
         * replace(PrimaryC, standard)
         *  before: [ PrimaryA | RelatedPage/PlaceHolder ]
         *  after: [ PrimaryC | RelatedPage/PlaceHolder ]
         *  step1: LoadPage (pageC has not yet been recognized as the PrimaryPage before it was created)
         *             Remove RelatedPage/PlaceHolder, then add PageC
         *  step2: OnPrimaryPageDetected (we won't mount, show RelatedPage/PlaceHolder at this step)
         *             recognize PageC as PrimaryC
         *  step3: move page node position
         *             Swap PrimaryA and PrimaryC
         *  step4: PopPage (we will mount, show RelatedPage/PlaceHolder at this step)
         *             Add RelatedPage/PlaceHolder, and then remove PrimaryA
         */
        if (newTopPattern->GetPageType() == RouterPageType::HOME_PAGE) {
            auto page = GetRelatedOrPlaceHolderPage();
            MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
            break;
        }
    } while (false);

    // close keyboard
    PageChangeCloseKeyboard();

    AddPageTransitionTrace(preTopPage, newTopPage);
    FireAutoSave(preTopPage, newTopPage);

    stageNode_->RemoveChild(preTopPage);

    auto homePage = GetHomePage();
    stagePattern_->SetHomePage(homePage);

    preTopPage->SetChildrenInDestroying();
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition) {
        auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(stagePattern_);
        CHECK_NULL_RETURN(stagePattern, true);
        auto relatedPage = stagePattern->GetRelatedPage();
        if (newTopPage == homePage && relatedPage) {
            ReportPageTransitionEnd(relatedPage);
        } else {
            ReportPageTransitionEnd(newTopPage);
        }
    }
    return true;
}

bool ParallelStageManager::GetPageNumberExcludeRelatedOrPlaceHolderPage(int32_t& pageNumber)
{
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    const auto& children = stageNode_->GetChildren();
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(lastPattern, false);
    pageNumber = static_cast<int32_t>(children.size());
    if (stagePattern->HasDividerNode()) {
        pageNumber--;
    }
    auto type = lastPattern->GetPageType();
    if (type == RouterPageType::PLACEHOLDER_PAGE || type == RouterPageType::RELATED_PAGE) {
        pageNumber--;
    }
    return true;
}

bool ParallelStageManager::FirePageHideOnPopPageToIndex(int32_t popSize)
{
    const auto& children = stageNode_->GetChildren();
    auto iter = children.rbegin();
    for (int32_t current = 0; current < popSize; ++current, ++iter) {
        auto page = AceType::DynamicCast<FrameNode>(*iter);
        if (!page) {
            continue;
        }
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        auto type = pattern->GetPageType();
        if (type != RouterPageType::HOME_PAGE && type != RouterPageType::DETAIL_PAGE) {
            return false;
        }
        FireParallelPageHide(page, PageTransitionType::NONE);
    }
    return true;
}

bool ParallelStageManager::FirePageShowOnPopPageToIndex(
    const RefPtr<ParallelStagePattern>& stagePattern, const RefPtr<FrameNode>& toPage,
    bool& addRelatedOrPhPage, PageTransitionType showTransitionType)
{
    auto pattern = toPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto type = pattern->GetPageType();
    if (type == RouterPageType::DETAIL_PAGE) {
        /**
         * [ SecondaryB ]/[ PrimaryA | xxx ] -> [ SecondaryA ]
         * [ PrimaryA | SecondaryB ] -> [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]
         *  SecondaryA/RelatedPage/PlaceHolder -> onPageShow
         */
        FireParallelPageShow(toPage, showTransitionType);
        return true;
    }
    if (type == RouterPageType::HOME_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ] -> [ PrimaryA | PlaceHolder/RelatedPage ]
         *  PlaceHolder/RelatedPage -> aboutToAppear
         *  PlaceHolder/RelatedPage -> onPageShow
         */
        auto page = GetRelatedOrPlaceHolderPage();
        MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
        addRelatedOrPhPage = true;
        return true;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "invalid dest page type: %{public}d", static_cast<int32_t>(type));
    return false;
}

bool ParallelStageManager::PopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    if (!stagePattern->GetIsSplit() && !isTopFullScreenPageChanged_) {
        bool result = StageManager::PopPageToIndex(index, needShowNext, needTransition);
        InvalidateRouterColumnNodes();
        auto homePage = GetHomePage();
        stagePattern->SetHomePage(homePage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
    }
    if (IsVirtualStackBasedSplit()) {
        return PopPageToIndexInVirtualStackBasedSplit(index, needShowNext, needTransition);
    }
    return PopPageToIndexInSplitMode(index, needShowNext, needTransition);
}

bool ParallelStageManager::PopPageToIndexInSplitMode(int32_t index, bool needShowNext, bool needTransition)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    int32_t pageNumber = 0;
    if (!GetPageNumberExcludeRelatedOrPlaceHolderPage(pageNumber)) {
        return false;
    }
    const auto& children = stageNode_->GetChildren();
    int32_t popSize = pageNumber - index - 1;
    if (popSize < 0) {
        return false;
    }
    if (popSize == 0) {
        return true;
    }

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }

    RefPtr<FrameNode> relatedOrPhPage = nullptr;
    if (!RemoveRelatedOrPlaceHolderPageIfExist(relatedOrPhPage)) {
        return false;
    }

    auto firstFromPage = GetLastPage();
    auto iter = children.rbegin();
    std::advance(iter, popSize);
    RefPtr<FrameNode> toPage = AceType::DynamicCast<FrameNode>(*iter);
    if (!FirePageHideOnPopPageToIndex(popSize)) {
        return false;
    }

    bool addRelatedOrPhPage = false;
    if (needShowNext) {
        if (!FirePageShowOnPopPageToIndex(
            stagePattern, toPage, addRelatedOrPhPage, PageTransitionType::NONE)) {
            return false;
        }
    }
    AddPageTransitionTrace(firstFromPage, toPage);

    FireAutoSave(firstFromPage, toPage);

    for (int32_t current = 0; current < popSize; ++current) {
        RefPtr<UINode> pageNode = nullptr;
        if (addRelatedOrPhPage) {
            pageNode = *(++children.rbegin());
        } else {
            pageNode = GetLastPage();
        }
        stageNode_->RemoveChild(pageNode);
    }

    auto homePage = GetHomePage();
    stagePattern->SetHomePage(homePage);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition) {
        auto relatedPage = stagePattern->GetRelatedPage();
        if (toPage == homePage && relatedPage) {
            ReportPageTransitionEnd(relatedPage);
        } else {
            ReportPageTransitionEnd(toPage);
        }
    }
    return true;
}

bool ParallelStageManager::CleanPageStack()
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    if (!stagePattern->GetIsSplit() && !isTopFullScreenPageChanged_) {
        bool result = StageManager::CleanPageStack();
        InvalidateRouterColumnNodes();
        auto homePage = GetHomePage();
        stagePattern->SetHomePage(homePage);
        return result;
    }
    if (IsVirtualStackBasedSplit()) {
        return CleanPageStackInVirtualStackBasedSplit(stagePattern);
    }
    return CleanPageStackInSplitMode(stagePattern);
}

bool ParallelStageManager::CleanPageStackInSplitMode(const RefPtr<ParallelStagePattern>& stagePattern)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    int32_t pageNumber = 0;
    if (!GetPageNumberExcludeRelatedOrPlaceHolderPage(pageNumber)) {
        return false;
    }
    constexpr int32_t PAGE_NUMBER = 2;
    if (pageNumber < PAGE_NUMBER) {
        return false;
    }
    const auto& children = stageNode_->GetChildren();
    bool needHidePrimaryPage = true;
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(lastPattern, false);
    auto lastPageType = lastPattern->GetPageType();
    if (lastPageType == RouterPageType::PLACEHOLDER_PAGE || lastPageType == RouterPageType::RELATED_PAGE) {
        if (children.size() < PAGE_NUMBER) {
            return false;
        }
        auto prePage = AceType::DynamicCast<FrameNode>(*(++children.rbegin()));
        CHECK_NULL_RETURN(prePage, false);
        auto prePattern = prePage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(prePattern, false);
        if (prePattern->GetPageType() != RouterPageType::HOME_PAGE) {
            return false;
        }
        needHidePrimaryPage = false;
    } else if (lastPageType == RouterPageType::HOME_PAGE) {
        return false;
    }

    bool preHasHomePage = GetHomePage() != nullptr;
    bool hasDivider = stagePattern->HasDividerNode();
    auto popSize = pageNumber - 1;
    for (int32_t count = 0; count < popSize; ++count) {
        RefPtr<FrameNode> pageNode = nullptr;
        if (hasDivider) {
            // skip divider node
            pageNode = AceType::DynamicCast<FrameNode>(*(++children.begin()));
        } else {
            pageNode = AceType::DynamicCast<FrameNode>(children.front());
        }
        // mark pageNode child as destroying
        pageNode->SetChildrenInDestroying();
        do {
            auto pagePattern = pageNode->GetPattern<ParallelPagePattern>();
            if (!pagePattern) {
                break;
            }
            if (pagePattern->GetPageType() != RouterPageType::HOME_PAGE) {
                break;
            }
            if (!needHidePrimaryPage) {
                break;
            }
            FireParallelPageHide(pageNode, PageTransitionType::NONE);
            needHidePrimaryPage = false;
        } while (false);
        stageNode_->RemoveChild(pageNode);
    }
    auto homePage = GetHomePage();
    stagePattern->SetHomePage(homePage);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (preHasHomePage && !homePage) {
        ReportPageTransitionEnd(GetLastPage());
    }
    return true;
}

bool ParallelStageManager::MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    if (!stagePattern->GetIsSplit() && !isTopFullScreenPageChanged_) {
        bool result = StageManager::MovePageToFront(node, needHideLast, needTransition);
        InvalidateRouterColumnNodes();
        auto homePage = GetHomePage();
        stagePattern->SetHomePage(homePage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
    }

    auto newTopPattern = node->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(newTopPattern, false);
    if (newTopPattern->GetPageType() != RouterPageType::HOME_PAGE &&
        newTopPattern->GetPageType() != RouterPageType::DETAIL_PAGE) {
        return false;
    }

    const auto& lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    if (lastPage == node) {
        return true;
    }
    if (IsVirtualStackBasedSplit()) {
        return MovePageToFrontInVirtualStackBasedSplit(node, needHideLast, needTransition);
    }
    return MovePageToFrontInSplitMode(node, needHideLast, needTransition);
}

void ParallelStageManager::FirePageHideOnMovePageToFront(
    RouterPageType newTopPageType, const RefPtr<FrameNode>& preLastPage, PageTransitionType hideTransitionType)
{
    if (newTopPageType == RouterPageType::DETAIL_PAGE) {
        /**
         * [ PrimaryA | SecondaryA/PlaceHolder/RelatedPage ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  preLastPage(SecondaryA/PlaceHolder/RelatedPage) -> onPageHide
         */
        FireParallelPageHide(preLastPage, hideTransitionType);
        return;
    }

    if (newTopPageType != RouterPageType::HOME_PAGE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "new top should be HomePage or DetailPage");
        return;
    }

    // new top page is HomePage
    /**
     * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ PrimaryB | PlaceHolder/RelatedPage ]
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | PlaceHolder/RelatedPage ]
     * [ SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     *  preLastPage -> onPageHide
     */
    FireParallelPageHide(preLastPage, hideTransitionType);
}

void ParallelStageManager::FirePageShowOnMovePageToFront(
    const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
    const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
    PageTransitionType showTransitionType)
{
    if (newTopPattern->GetPageType() == RouterPageType::DETAIL_PAGE) {
        /**
         * [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);
        return;
    }

    // RouterPageType::HOME_PAGE
    /**
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | RelatedPage/PlaceHolder ]
     *  RelatedPage/PlaceHolder -> onPageShow
     */
    auto page = GetRelatedOrPlaceHolderPage();
    MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, showTransitionType);
}

bool ParallelStageManager::MovePageToFrontInSplitMode(
    const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto newTopPattern = node->GetPattern<ParallelPagePattern>();
    const auto& children = stageNode_->GetChildren();
    auto lastPage = GetLastPage();

    RefPtr<FrameNode> preTopPage = nullptr;
    RefPtr<ParallelPagePattern> preTopPattern = nullptr;
    RefPtr<FrameNode> preHomePage = GetHomePage();
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(lastPattern, false);
    auto lastPageType = lastPattern->GetPageType();
    if (lastPageType == RouterPageType::PLACEHOLDER_PAGE || lastPageType == RouterPageType::RELATED_PAGE) {
        constexpr size_t PAGE_NUM = 3;
        if (children.size() < PAGE_NUM) {
            return false;
        }
        auto prePage = AceType::DynamicCast<FrameNode>(*(++children.rbegin()));
        CHECK_NULL_RETURN(prePage, false);
        auto prePattern = prePage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(prePattern, false);
        if (prePattern->GetPageType() != RouterPageType::HOME_PAGE) {
            return false;
        }
        preTopPage = prePage;
        preTopPattern = prePattern;
        if (node == prePage) {
            return true;
        }
    } else {
        preTopPage = lastPage;
        preTopPattern = lastPattern;
    }

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }

    RefPtr<FrameNode> relatedOrPhPage = nullptr;
    if (!RemoveRelatedOrPlaceHolderPageIfExist(relatedOrPhPage, !isNewPageReplacing_)) {
        return false;
    }

    if (needHideLast) {
        FirePageHideOnMovePageToFront(newTopPattern->GetPageType(), lastPage, PageTransitionType::NONE);
    }
    node->MovePosition(static_cast<int32_t>(stageNode_->GetChildren().size()) - 1);
    auto pattern = node->GetPattern<PagePattern>();
    if (pattern) {
        pattern->ResetPageTransitionEffect();
    }
    FirePageShowOnMovePageToFront(
        preTopPage, preTopPattern, node, newTopPattern, PageTransitionType::NONE);

    auto homePage = GetHomePage();
    stagePattern->SetHomePage(homePage);

    RefPtr<FrameNode> outPageNode = nullptr;
    if (relatedOrPhPage) {
        outPageNode = preHomePage;
    } else {
        outPageNode = lastPage;
    }
    AddPageTransitionTrace(outPageNode, node);
    FireAutoSave(outPageNode, node);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition) {
        ReportPageTransitionEnd(node);
    }
    return true;
}

bool ParallelStageManager::RemoveRelatedOrPlaceHolderPageIfExist(RefPtr<FrameNode>& page, bool needHidePage)
{
    page = nullptr;
    if (IsEmptyInSplitMode()) {
        return true;
    }
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    auto pattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, false);

    auto type = pattern->GetPageType();
    if (type == RouterPageType::RELATED_PAGE || type == RouterPageType::PLACEHOLDER_PAGE) {
        if (needHidePage) {
            FireParallelPageHide(lastPage, PageTransitionType::NONE);
        }

        stageNode_->RemoveChild(lastPage);
        page = lastPage;
    }
    return true;
}

bool ParallelStageManager::OnHomePageDetected(
    const RefPtr<FrameNode>& homePage, const std::list<WeakPtr<FrameNode>>& pageStack)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);

    auto isVirtualStackBasedSplit = IsVirtualStackBasedSplit();
    auto preHomePage = GetHomePage();
    CHECK_NULL_RETURN(homePage, false);
    auto homePattern = homePage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(homePattern, false);
    homePattern->SetPageType(RouterPageType::HOME_PAGE);
    if (isVirtualStackBasedSplit) {
        auto preVisiblePages = GetRouterVisiblePages();
        homePattern->SetColumnType(ForceSplitPageColumnType::PRIMARY);
        UpdateRouterSplitPlaceholder();
        auto curHomePage = GetHomePage();
        stagePattern->SetHomePage(curHomePage);
        if (!stagePattern->GetIsSplit()) {
            return true;
        }
        auto newVisiblePages = GetRouterVisiblePages();
        FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages);
        FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages);
        return true;
    }

    auto curHomePage = GetHomePage();
    stagePattern->SetHomePage(curHomePage);
    if (!stagePattern->GetIsSplit()) {
        return true;
    }
    if (!preHomePage) {
        FireParallelPageShow(homePage, PageTransitionType::NONE);
    } else if (preHomePage != curHomePage) {
        FireParallelPageHide(preHomePage, PageTransitionType::NONE);
        FireParallelPageShow(homePage, PageTransitionType::NONE);
    }

    /**
     * example:
     * replace(PrimaryC, standard)
     *  before: [ PrimaryA | RelatedPage/PlaceHolder ]
     *  after: [ PrimaryC ] [ RelatedPage/PlaceHolder ]
     *  step1: LoadPage (pageC has not yet been recognized as the PrimaryPage before it was created)
     *             Remove RelatedPage/PlaceHolder, and then add PageC
     *  step2: OnHomePageDetected (we won't create placeHolderPage at this step)
     *             recognize PageC as PrimaryPage
     *  step3: move page node position
     *             Swap PrimaryA and PrimaryC
     *  step4: PopPage (we will mount, show RelatedPage/PlaceHolder at this step)
     *             Remove PrimaryA, and then mount&show RelatedPage/PlaceHolder
     */
    if (isNewPageReplacing_) {
        return true;
    }

    auto iter = std::find_if(pageStack.begin(), pageStack.end(),
        [homePage](const WeakPtr<FrameNode>& weakPage) {
            auto page = weakPage.Upgrade();
            if (!page) {
                return false;
            }
            return page == homePage;
        });
    if (iter == pageStack.end()) {
        return false;
    }
    if (*iter != *(pageStack.rbegin())) {
        return true;
    }

    auto page = GetRelatedOrPlaceHolderPage();
    MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, PageTransitionType::NONE);
    return true;
}

void ParallelStageManager::MountAndShowRelatedOrPlaceHolderPageIfNeeded(
    const RefPtr<FrameNode>& page, PageTransitionType showTransitionType)
{
    CHECK_NULL_VOID(stageNode_);
    CHECK_NULL_VOID(page);
    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    auto geometryNode = page->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(rect.GetSize());
    geometryNode->SetMarginFrameOffset(rect.GetOffset());
    page->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    page->MountToParent(stageNode_);
    InvalidateRouterColumnNodes();
    auto pattern = page->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsPageBuildCompleted()) {
        // then build the total child. Build will trigger page create and onAboutToAppear
        page->Build(nullptr);
        page->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        pattern->SetIsPageBuildCompleted(true);
    }

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FireParallelPageShow(page, showTransitionType, false);
}

RefPtr<FrameNode> ParallelStageManager::GetLastPage() const
{
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    for (auto child = children.rbegin(); child != children.rend(); child++) {
        auto frameNode = AceType::DynamicCast<FrameNode>(*child);
        if (!frameNode) {
            continue;
        }
        if (frameNode->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        return frameNode;
    }
    return nullptr;
}
 
RefPtr<FrameNode> ParallelStageManager::GetPrevPageWithTransition() const
{
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    if (stageInTrasition_) {
        return DynamicCast<FrameNode>(srcPageNode_.Upgrade());
    }
    for (const auto& child : children) {
        if (child->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        return AceType::DynamicCast<FrameNode>(child);
    }
    return nullptr;
}

RefPtr<FrameNode> ParallelStageManager::GetLastPageWithTransition() const
{
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode, nullptr);
    const auto& children = stageNode->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    if (stageInTrasition_) {
        return DynamicCast<FrameNode>(destPageNode_.Upgrade());
    } else {
        return GetLastPage();
    }
}

bool ParallelStageManager::ExchangePageFocus(bool &initFlag)
{
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);

    if (!stagePattern->GetIsSplit()) {
        return false;
    }

    // the focus move from one page to another.
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    RefPtr<FrameNode> primaryColumnPage = nullptr;
    if (IsVirtualStackBasedSplit()) {
        primaryColumnPage = GetTopPrimaryColumnPage();
    } else {
        primaryColumnPage = GetHomePage();
    }
    CHECK_NULL_RETURN(primaryColumnPage, false);

    auto focusHub = primaryColumnPage->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto pagePattern = primaryColumnPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (focusHub->IsCurrentFocus()) {
        // If the home page is focused, the focus should be exchanged to lastPage.
        focusHub = lastPage->GetFocusHub();
        CHECK_NULL_RETURN(focusHub, false);
        pagePattern = lastPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(pagePattern, false);
    }

    if (initFlag) {
        pagePattern->SetIsViewRootScopeFocused(false);
        initFlag = false;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Exchange focus to head child of new page.");
    focusHub->FocusToHeadOrTailChild(true);

    return true;
}

bool ParallelStageManager::UpdatePageFocus(RefPtr<FrameNode> &focusPage)
{
    auto focusHub = focusPage->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (focusHub->IsCurrentFocus()) {
        // If the focus is already at detail page, don't move the focus to head child.
        return true;
    }
    TAG_LOGI(AceLogTag::ACE_ROUTER, "Move focus to head child of detailPage from primaryPage");
    focusHub->FocusToHeadOrTailChild(true);
    return true;
}

RefPtr<FrameNode> ParallelStageManager::GetFocusPage() const
{
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode, nullptr);
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, nullptr);
    auto isVirtualStackBasedSplit = IsVirtualStackBasedSplit();
    const auto& children = stageNode->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    for (auto child = children.rbegin(); child != children.rend(); child++) {
        auto frameNode = AceType::DynamicCast<FrameNode>(*child);
        if (!frameNode) {
            continue;
        }
        if (frameNode->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        if (frameNode->GetFocusHub() && frameNode->GetFocusHub()->IsCurrentFocus()) {
            return frameNode;
        }
        if (isVirtualStackBasedSplit) {
            auto primaryColumnPage = GetTopPrimaryColumnPage();
            if (primaryColumnPage) {
                return primaryColumnPage;
            }
        } else {
            auto homePage = stagePattern->GetHomePage();
            if (homePage) {
                return homePage;
            }
        }
    }
    return nullptr;
}

bool ParallelStageManager::IsEmptyInSplitMode()
{
    CHECK_NULL_RETURN(stageNode_, true);
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(stageNode_->GetPattern());
    CHECK_NULL_RETURN(stageNode_, true);
    auto dividerNode = stagePattern->GetDividerNode();
    if (stageNode_->GetChildIndex(dividerNode) >= 0) {
        return stageNode_->GetChildren().size() <= 1;
    }
    return stageNode_->GetChildren().empty();
}

void ParallelStageManager::RemoveSecondaryPagesOfPrimaryPage()
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (secondaryPageStack_.empty()) {
        touchedPrimaryColumnPage_.Reset();
        return;
    }
    for (auto iter = secondaryPageStack_.begin(); iter != secondaryPageStack_.end(); iter++) {
        auto detailPage = (*iter).Upgrade();
        if (!detailPage) {
            continue;
        }
        detailPage->SetChildrenInDestroying();
        stageNode_->RemoveChild(detailPage);
        InvalidateRouterColumnNodes();
        ClearRouterPageState(detailPage);
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    secondaryPageStack_.clear();
    touchedPrimaryColumnPage_.Reset();
}

void ParallelStageManager::FireParallelPageShow(const RefPtr<UINode>& node, PageTransitionType transitionType,
    bool needFocus)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto pagePattern = AceType::DynamicCast<ParallelPagePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pagePattern);
    if (pagePattern->GetIsShow()) {
        return;
    }
    StageManager::FirePageShow(node, transitionType, needFocus);
}

void ParallelStageManager::MarkDirtyPageAndOverlay(const RefPtr<FrameNode>& needMarkDirtyPage,
    PropertyChangeFlag changeFlag)
{
    CHECK_NULL_VOID(needMarkDirtyPage);
    needMarkDirtyPage->MarkDirtyNode(changeFlag);
    auto needMarkDirtyPageOverlay = needMarkDirtyPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(needMarkDirtyPageOverlay);
    needMarkDirtyPageOverlay->MarkDirtyOverlay();
}

void ParallelStageManager::SyncPageSafeArea(bool KeyboardSafeArea)
{
    if (!IsSplitMode()) {
        return StageManager::SyncPageSafeArea(KeyboardSafeArea);
    }
    auto changeType = KeyboardSafeArea ? PROPERTY_UPDATE_LAYOUT : PROPERTY_UPDATE_MEASURE;
    auto lastPage = GetLastPageWithTransition();
    CHECK_NULL_VOID(lastPage);
    if (KeyboardSafeArea) {
        auto focusPage = GetFocusPage();
        CHECK_NULL_VOID(focusPage);
        MarkDirtyPageAndOverlay(focusPage, changeType);
    } else {
        MarkDirtyPageAndOverlay(lastPage, changeType);
    }

    auto prevPage = GetPrevPageWithTransition();
    CHECK_NULL_VOID(prevPage);
    auto prevPageOverlay = prevPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(prevPageOverlay);
    prevPageOverlay->MarkDirtyOverlay();

    CHECK_NULL_VOID(stageNode_);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit() || KeyboardSafeArea) {
        return;
    }
    stageNode_->MarkDirtyNode(changeType);
    RefPtr<FrameNode> needSyncPage = nullptr;
    auto isVirtualStackBasedSplit = IsVirtualStackBasedSplit();
    if (isVirtualStackBasedSplit) {
        needSyncPage = GetTopPrimaryColumnPage();
        CHECK_NULL_VOID(needSyncPage);
    } else {
        needSyncPage = stagePattern->GetHomePage();
        CHECK_NULL_VOID(needSyncPage);
        if (lastPage->GetPattern<ParallelPagePattern>()->GetPageType() == RouterPageType::HOME_PAGE) {
            needSyncPage = GetLastPage();
        }
    }
    if (isVirtualStackBasedSplit && needSyncPage == lastPage) {
        return;
    }
    MarkDirtyPageAndOverlay(needSyncPage, changeType);
}

bool ParallelStageManager::CheckPageFocus()
{
    if (!IsSplitMode()) {
        return StageManager::CheckPageFocus();
    }
    auto pageNode = GetFocusPage();
    CHECK_NULL_RETURN(pageNode, true);
    return pageNode->GetFocusHub() && pageNode->GetFocusHub()->IsCurrentFocus();
}

void ParallelStageManager::FireParallelPageHide(const RefPtr<UINode>& node, PageTransitionType transitionType)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto pagePattern = AceType::DynamicCast<ParallelPagePattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(pagePattern);
    if (!pagePattern->GetIsShow()) {
        if (transitionType != PageTransitionType::NONE) {
            return;
        }
        auto property = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(property);
        if (property->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
            return;
        }
        /**
         * When split-mode app switch to background, only the primaryPage's onPageHide lifecycle will be triggered,
         * the primaryPage's visibily propery still be Visible. At this time, if app switching to stack mode,
         * we need set it's visibility to Invisible.
         */
        pagePattern->ProcessHideState();
        return;
    }
    StageManager::FirePageHide(node, transitionType);
}

int32_t ParallelStageManager::UpdateSecondaryPageNeedRemoved(bool needClearSecondaryPage)
{
    secondaryPageStack_.clear();
    const auto& children = stageNode_->GetChildren();
    if (!needClearSecondaryPage || children.empty()) {
        touchedPrimaryColumnPage_.Reset();
        return 0;
    }
    RefPtr<FrameNode> stopPage = nullptr;
    if (IsVirtualStackBasedSplit()) {
        stopPage = GetTouchedPrimaryColumnPage();
    }
    bool stopPageFound = false;
    bool homePageFound = false;
    for (auto child = children.rbegin(); child != children.rend(); child++) {
        RefPtr<FrameNode> frameNode;
        RouterPageType type = RouterPageType::HOME_PAGE;
        if (!GetEffectiveRouterStagePage(*child, frameNode, type)) {
            continue;
        }
        if (stopPage) {
            if (frameNode == stopPage) {
                stopPageFound = true;
                break;
            }
            secondaryPageStack_.emplace_back(WeakPtr<FrameNode>(frameNode));
            continue;
        }
        if (type == RouterPageType::HOME_PAGE) {
            homePageFound = true;
            break;
        }
        if (type == RouterPageType::DETAIL_PAGE) {
            secondaryPageStack_.emplace_back(WeakPtr<FrameNode>(frameNode));
        }
    }
    touchedPrimaryColumnPage_.Reset();
    if (stopPage) {
        if (!stopPageFound) {
            secondaryPageStack_.clear();
            return 0;
        }
        return static_cast<int32_t>(secondaryPageStack_.size());
    }
    if (!homePageFound) {
        secondaryPageStack_.clear();
        return 0;
    }
    return static_cast<int32_t>(secondaryPageStack_.size());
}

std::vector<RefPtr<FrameNode>> ParallelStageManager::GetTopPagesWithTransition() const
{
    std::vector<RefPtr<FrameNode>> pages;
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode, pages);
    const auto& children = stageNode->GetChildren();
    if (children.empty()) {
        return pages;
    }
    auto stagePattern = stageNode->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, pages);
    if (stagePattern->GetIsSplit()) {
        RefPtr<FrameNode> page = nullptr;
        if (IsVirtualStackBasedSplit()) {
            page = GetTopPrimaryColumnPage();
        } else {
            page = stagePattern->GetHomePage();
        }
        if (page) {
            pages.push_back(page);
        }
    }
    RefPtr<FrameNode> lastPage = nullptr;
    if (stageInTrasition_) {
        lastPage = DynamicCast<FrameNode>(destPageNode_.Upgrade());
    } else {
        lastPage = GetLastPage();
    }
    if (lastPage) {
        pages.push_back(lastPage);
    }
    return pages;
}

bool ParallelStageManager::IsSplitMode() const
{
    auto stageNode = GetStageNode();
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    return stagePattern->GetIsSplit();
}

RefPtr<FrameNode> ParallelStageManager::GetRelatedOrPlaceHolderPage()
{
    auto stagePattern = AceType::DynamicCast<ParallelStagePattern>(stagePattern_);
    CHECK_NULL_RETURN(stagePattern, nullptr);
    return stagePattern->GetRelatedOrPlaceHolderPage();
}

void ParallelStageManager::ReportPageTransitionEnd(const RefPtr<FrameNode>& page)
{
    CHECK_NULL_VOID(page);
    auto context = page->GetContext();
    CHECK_NULL_VOID(context);
    auto mgr = context->GetContentChangeManager();
    CHECK_NULL_VOID(mgr);
    context->AddAfterLayoutTask([weakMgr = WeakPtr(mgr), weakNode = WeakPtr(page)]() {
        auto node = weakNode.Upgrade();
        CHECK_NULL_VOID(node);
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->OnPageTransitionEnd(node);
    });
}

bool ParallelStageManager::IsDisplaySplitMode() const
{
    if (IsVirtualStackBasedSplit() || GetHomePage() != nullptr) {
        return IsSplitMode();
    }
    return false;
}

bool ParallelStageManager::IsVirtualStackBasedSplit() const
{
    CHECK_NULL_RETURN(stageNode_, false);
    auto context = stageNode_->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto forceSplitMgr = context->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    return forceSplitMgr->CanPushPageToPrimary();
}

void ParallelStageManager::OnModeChangeInVirtualStackBasedSplit(const RefPtr<FrameNode>& lastPage)
{
    CHECK_NULL_VOID(lastPage);
    auto stagePattern = stageNode_ ? stageNode_->GetPattern<ParallelStagePattern>() : nullptr;
    CHECK_NULL_VOID(stagePattern);
    if (stagePattern->GetIsSplit()) {
        AbortAnimation();
        // New architecture handles stack/split switching exactly like an ordinary visible-result change:
        // compute pre visible pages/new visible pages, then only notify the delta.
        auto preVisiblePages = GetRouterVisiblePagesForCurrentStackTree();
        // While we stay in stack mode, stack operations may legitimately leave historical PRIMARY column ownership
        // on pages that are no longer supposed to stay on the primary side once split mode is restored.
        // Before calculating the split-mode visible result, normalize the current stack against the split rules first.
        NormalizeRouterColumnsAfterStackChange();
        UpdateRouterSplitPlaceholder();
        auto newVisiblePages = GetRouterVisiblePagesForCurrentSplitTree();
        FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages);
        FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages);
        return;
    }
    AbortAnimation();
    auto preVisiblePages = GetRouterVisiblePagesForCurrentSplitTree();
    UpdateRouterSplitPlaceholder();
    auto newVisiblePages = GetRouterVisiblePagesForCurrentStackTree();
    FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages);
    FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages);
    auto currentDetail = GetLastPageInStack();
    if (currentDetail && currentDetail != lastPage) {
        UpdatePageFocus(currentDetail);
    }
}

void ParallelStageManager::OnWindowStateChangeInVirtualStackBasedSplit(bool show)
{
    auto visiblePages = GetRouterVisiblePages();
    auto primaryPage = visiblePages.primary;
    auto detailPage = visiblePages.detail;
    auto fireShow = [](const RefPtr<FrameNode>& page) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnShow(true);
    };
    auto fireHide = [](const RefPtr<FrameNode>& page) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnHide(true);
    };
    // In split mode, window foreground/background callbacks must follow the actual visible result:
    // show: primary first, then secondary; hide: secondary first, then primary.
    if (show) {
        fireShow(primaryPage);
        if (detailPage != primaryPage) {
            fireShow(detailPage);
        }
        return;
    }
    if (detailPage && detailPage != primaryPage) {
        fireHide(detailPage);
    }
    fireHide(primaryPage);
}

bool ParallelStageManager::PushPageInVirtualStackBasedSplit(const RefPtr<FrameNode>& newPageNode,
    bool isNewLifecycle, bool needHideLast, bool needTransition)
{
    auto currentTopPage = GetLastPageInStack();
    auto touchedSecondaryPage = TakeTouchedSecondaryColumnPage();
    auto secondaryPageTriggered = touchedSecondaryPage && touchedSecondaryPage == currentTopPage;
    auto usePushToPrimaryFlow =
        !isNewPageReplacing_ && secondaryPageTriggered && ShouldCurrentPushPageToPrimary(newPageNode);
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto newTopPattern = newPageNode->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(newTopPattern, false);
    auto preVisiblePages = GetRouterVisiblePages();
    RefPtr<FrameNode> lastPage = nullptr;
    if (!IsEmptyInSplitMode()) {
        lastPage = GetLastPage();
        CHECK_NULL_RETURN(lastPage, false);
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    if (usePushToPrimaryFlow) {
        // Router page column must be written before we compute the final visible result,
        // but the actual column-node cache is rebuilt later after the new page is mounted.
        UpdateRouterColumnsOnPush(currentTopPage, newPageNode);
    }

    RefPtr<FrameNode> topRelatedOrPhPage = nullptr;
    auto fallbackPage = GetRelatedOrPlaceHolderPage();
    if (fallbackPage && stageNode_->GetChildIndex(fallbackPage) >= 0) {
        topRelatedOrPhPage = fallbackPage;
    }

    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    newPageNode->GetRenderContext()->SyncGeometryProperties(rect);
    // Keep placeholder/related as the last child when it is already mounted:
    // insert the new stack page before it instead of detaching and remounting the fallback page.
    if (topRelatedOrPhPage) {
        newPageNode->MountToParentBefore(stageNode_, topRelatedOrPhPage);
    } else {
        newPageNode->MountToParent(stageNode_);
    }
    // The new page is now in the real stage tree. Refresh router column caches before any lifecycle decision,
    // so newVisiblePages is derived from the actual node structure instead of a synthetic prediction.
    InvalidateRouterColumnNodes();
    auto homePage = GetHomePage();
    bool needMountPrimaryFallback = !usePushToPrimaryFlow && !homePage && fallbackPage &&
        stageNode_->GetChildIndex(fallbackPage) < 0;
    if (needMountPrimaryFallback) {
        fallbackPage->MountToParent(stageNode_);
        topRelatedOrPhPage = fallbackPage;
    }
    RebuildRouterColumnNodesIfNeeded();
    auto newVisiblePages = GetRouterVisiblePages();

    // then build the total child. Build will trigger page create and onAboutToAppear
    newPageNode->Build(nullptr);

    // Router split mode only keeps delayed hide semantics for the dedicated secondary-push-to-primary column animation.
    // Ordinary split push does not start the old page transition, so pages leaving the visible result must hide
    // immediately with transitionType=NONE.
    auto useRouterColumnAnimation =
        needTransition && usePushToPrimaryFlow && CheckIfMovePageToPrimaryIsAllowed(preVisiblePages, newVisiblePages);
    if (needHideLast && lastPage) {
        auto hideTransitionType = GetRouterPushHideTransitionType(useRouterColumnAnimation);
        FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages, hideTransitionType);
    }
    stageNode_->RebuildRenderContextTree();
    bool animated = false;
    auto showTransitionType = GetRouterPushShowTransitionType(useRouterColumnAnimation);
    FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages, showTransitionType);
    if (topRelatedOrPhPage && topRelatedOrPhPage != newVisiblePages.detail &&
        stageNode_->GetChildIndex(topRelatedOrPhPage) >= 0) {
        stageNode_->RemoveChild(topRelatedOrPhPage);
    }
    if (usePushToPrimaryFlow) {
        animated = useRouterColumnAnimation && StartRouterSplitAnimation(preVisiblePages, newVisiblePages);
    }

    stagePattern_->SetCurrentPageIndex(newTopPattern->GetPageInfo()->GetPageId());
    // close keyboard
    PageChangeCloseKeyboard();
    AddPageTransitionTrace(lastPage, newPageNode);
    FireAutoSave(lastPage, newPageNode);

    // flush layout task.
    if (!stageNode_->GetGeometryNode()->GetMarginFrameSize().IsPositive()) {
        // in first load case, wait for window size.
        return true;
    }
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    newPageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition && (!useRouterColumnAnimation || !animated)) {
        ReportPageTransitionEnd(newPageNode);
    }
    return true;
}

bool ParallelStageManager::PopPageInVirtualStackBasedSplit(bool needShowNext, bool needTransition)
{
    // Pop should only stay in push-to-primary flow when the current split relation already contains
    // a pushed-primary detail page. Unlike push, pop-to-secondary may be triggered by
    // edge-swipe/system back, so it must not depend on a secondary-column touch source.
    auto touchedSecondaryPage = TakeTouchedSecondaryColumnPage();
    auto needPushPageToPrimaryStateHandling = !isNewPageReplacing_ && HasRouterPushPageToPrimaryState();
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    const int32_t transitionPageSize = 2;
    int32_t pageNumber = 0;
    if (!GetPageNumberExcludeRelatedOrPlaceHolderPage(pageNumber)) {
        return false;
    }
    needTransition &= (pageNumber >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    auto preVisiblePages = GetRouterVisiblePages();

    auto relatedOrPhPage = GetRelatedOrPlaceHolderPage();
    auto stackPages = CollectRouterStackPages();
    auto preTopPage = !stackPages.empty() ? stackPages.back() : nullptr;
    RefPtr<FrameNode> newTopPage = nullptr;
    CHECK_NULL_RETURN(preTopPage, false);
    std::vector<RefPtr<FrameNode>> remainingStackPages;
    if (!stackPages.empty()) {
        remainingStackPages.assign(stackPages.begin(), stackPages.end() - 1);
    }
    if (!remainingStackPages.empty()) {
        newTopPage = remainingStackPages.back();
    }

    auto newVisiblePages = ResolveRouterVisiblePagesFromStackPages(remainingStackPages, relatedOrPhPage);
    auto movePageToSecondaryIsAllowed = CheckIfMovePageToSecondaryIsAllowed(preVisiblePages, newVisiblePages);
    auto useRouterColumnAnimation =
        needTransition && needPushPageToPrimaryStateHandling && movePageToSecondaryIsAllowed;
    auto hideTransitionType = GetRouterPopHideTransitionType(useRouterColumnAnimation);
    auto showTransitionType = GetRouterPopShowTransitionType(useRouterColumnAnimation);
    FireLifecycleOnPopByVisibleDiff(
        preVisiblePages, newVisiblePages, needShowNext, hideTransitionType, showTransitionType);

    // close keyboard
    PageChangeCloseKeyboard();

    AddPageTransitionTrace(preTopPage, newTopPage);
    FireAutoSave(preTopPage, newTopPage);

    bool animated = false;
    if (needPushPageToPrimaryStateHandling) {
        // Being in a push-primary stack only means we need push-primary-aware visible prediction and column cleanup.
        // Whether this pop really becomes pop-to-secondary is decided by the final visible diff.
        ClearRouterPageState(preTopPage);
        if (!useRouterColumnAnimation) {
            preTopPage->SetChildrenInDestroying();
            stageNode_->RemoveChild(preTopPage);
            InvalidateRouterColumnNodes();
        }
        animated = FinalizeRouterStackChange(preVisiblePages, newVisiblePages, needTransition);
        if (useRouterColumnAnimation && !animated) {
            preTopPage->SetChildrenInDestroying();
            stageNode_->RemoveChild(preTopPage);
            InvalidateRouterColumnNodes();
        }
    } else {
        preTopPage->SetChildrenInDestroying();
        stageNode_->RemoveChild(preTopPage);
        InvalidateRouterColumnNodes();
        EnsureSplitSecondaryPageIfNeeded();
    }

    auto lastHomePage = GetHomePage();
    stagePattern->SetHomePage(lastHomePage);
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition && (!useRouterColumnAnimation || !animated)) {
        ReportPageTransitionEnd(GetRouterTransitionEndPageForCurrentVisible());
    }
    return true;
}

bool ParallelStageManager::PopPageToIndexInVirtualStackBasedSplit(
    int32_t index, bool needShowNext, bool needTransition)
{
    // back(index/url) may remove multiple pages in one shot.
    // The new flow still follows the rule "visible diff decides show/hide, detach decides aboutToDisappear".
    // Like ordinary pop, pop-to-secondary back may come from system/gesture back instead of a page click.
    auto touchedSecondaryPage = TakeTouchedSecondaryColumnPage();
    auto needPushPageToPrimaryStateHandling = !isNewPageReplacing_ && HasRouterPushPageToPrimaryState();
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto stackPages = CollectRouterStackPages();
    int32_t pageNumber = static_cast<int32_t>(stackPages.size());
    if (pageNumber <= 0) {
        return false;
    }
    int32_t popSize = pageNumber - index - 1;
    if (popSize < 0) {
        return false;
    }
    if (popSize == 0) {
        return true;
    }

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    auto preVisiblePages = GetRouterVisiblePages();

    auto relatedOrPhPage = GetRelatedOrPlaceHolderPage();
    auto firstFromPage = stackPages.back();
    RefPtr<FrameNode> toPage = nullptr;
    if (index >= 0 && index < pageNumber) {
        toPage = stackPages[index];
    }
    std::vector<RefPtr<FrameNode>> pagesToRemove;
    pagesToRemove.reserve(popSize);
    std::vector<RefPtr<FrameNode>> remainingStackPages;
    remainingStackPages.reserve(index + 1);
    for (int32_t current = 0; current < pageNumber; ++current) {
        if (current <= index) {
            remainingStackPages.emplace_back(stackPages[current]);
            continue;
        }
        pagesToRemove.emplace_back(stackPages[current]);
    }
    auto newVisiblePages = ResolveRouterVisiblePagesFromStackPages(remainingStackPages, relatedOrPhPage);
    auto movePageToSecondaryIsAllowed = CheckIfMovePageToSecondaryIsAllowed(preVisiblePages, newVisiblePages);
    auto useRouterColumnAnimation =
        needTransition && needPushPageToPrimaryStateHandling && movePageToSecondaryIsAllowed;
    auto hideTransitionType = GetRouterPopHideTransitionType(useRouterColumnAnimation);
    auto showTransitionType = GetRouterPopShowTransitionType(useRouterColumnAnimation);
    FireLifecycleOnPopByVisibleDiff(
        preVisiblePages, newVisiblePages, needShowNext, hideTransitionType, showTransitionType);
    AddPageTransitionTrace(firstFromPage, toPage);

    FireAutoSave(firstFromPage, toPage);

    bool removedAnyPage = false;
    for (auto iter = pagesToRemove.rbegin(); iter != pagesToRemove.rend(); ++iter) {
        auto pageNode = *iter;
        CHECK_NULL_CONTINUE(pageNode);
        if (useRouterColumnAnimation && pageNode == preVisiblePages.detail) {
            ClearRouterPageState(pageNode);
            continue;
        }
        // Detached pages will later report aboutToDisappear through the normal PagePattern detach path.
        pageNode->SetChildrenInDestroying();
        stageNode_->RemoveChild(pageNode);
        if (needPushPageToPrimaryStateHandling) {
            ClearRouterPageState(pageNode);
        }
        removedAnyPage = true;
    }
    if (removedAnyPage) {
        InvalidateRouterColumnNodes();
    }
    bool animated = false;
    if (needPushPageToPrimaryStateHandling) {
        animated = FinalizeRouterStackChange(preVisiblePages, newVisiblePages, needTransition);
        if (useRouterColumnAnimation && !animated && preVisiblePages.detail) {
            preVisiblePages.detail->SetChildrenInDestroying();
            stageNode_->RemoveChild(preVisiblePages.detail);
            InvalidateRouterColumnNodes();
        }
    } else {
        EnsureSplitSecondaryPageIfNeeded();
    }

    auto lastHomePage = GetHomePage();
    stagePattern->SetHomePage(lastHomePage);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition && (!useRouterColumnAnimation || !animated)) {
        ReportPageTransitionEnd(GetRouterTransitionEndPageForCurrentVisible());
    }
    return true;
}

bool ParallelStageManager::CleanPageStackInVirtualStackBasedSplit(const RefPtr<ParallelStagePattern>& stagePattern)
{
    CHECK_NULL_RETURN(stagePattern, false);
    auto stackPages = CollectRouterStackPages();
    constexpr int32_t MIN_STACK_PAGE_COUNT = 2;
    if (static_cast<int32_t>(stackPages.size()) < MIN_STACK_PAGE_COUNT) {
        return false;
    }

    auto preVisiblePages = GetRouterVisiblePages();
    auto remainingTopPage = stackPages.back();
    CHECK_NULL_RETURN(remainingTopPage, false);
    auto relatedOrPhPage = GetRelatedOrPlaceHolderPage();

    RouterVisiblePages newVisiblePages;
    // clean() keeps only the current stack top. In split mode that leaves a single stack page on
    // the primary side, with placeholder/related as the secondary-side fallback when available.
    newVisiblePages.primary = remainingTopPage;
    newVisiblePages.detail = relatedOrPhPage;
    FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages);
    FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages);

    std::vector<RefPtr<FrameNode>> pagesToRemove(stackPages.begin(), stackPages.end() - 1);

    for (const auto& pageNode : pagesToRemove) {
        pageNode->SetChildrenInDestroying();
        stageNode_->RemoveChild(pageNode);
        ClearRouterPageState(pageNode);
    }

    InvalidateRouterColumnNodes();
    RebuildRouterColumnNodesIfNeeded();
    stagePattern->SetHomePage(GetHomePage());
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

bool ParallelStageManager::MovePageToFrontInVirtualStackBasedSplit(
    const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    // Move-to-front serves RouterMode::Single and replace combinations.
    // Unlike pop/back, MovePosition itself does not trigger detach-side lifecycle.
    // We can therefore reorder first, refresh the real column caches, and then fire hide/show
    // from the actual visible result.
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto stackPages = CollectRouterStackPages();
    auto currentTopPage = !stackPages.empty() ? stackPages.back() : nullptr;
    CHECK_NULL_RETURN(currentTopPage, false);
    auto touchedSecondaryPage = TakeTouchedSecondaryColumnPage();
    auto secondaryPageTriggered = touchedSecondaryPage && touchedSecondaryPage == currentTopPage;
    if (currentTopPage == node) {
        return true;
    }
    auto needPushPageToPrimaryStateHandling = secondaryPageTriggered && (HasRouterPushPageToPrimaryState() ||
        ShouldMovePageToPrimaryForTransition(currentTopPage, node, false));
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    auto preVisiblePages = GetRouterVisiblePages();
    auto relatedOrPhPage = GetRelatedOrPlaceHolderPage();
    if (needPushPageToPrimaryStateHandling) {
        if (ShouldMovePageToPrimaryForTransition(currentTopPage, node)) {
            SetPageColumnType(currentTopPage, ForceSplitPageColumnType::PRIMARY);
        }
        SetPageColumnType(node, ForceSplitPageColumnType::SECONDARY);
    }

    // MovePosition itself does not trigger page lifecycle. We reorder first, then rebuild column caches,
    // and only after that decide hide/show from the actual resulting visible pages.
    node->MovePosition(static_cast<int32_t>(stageNode_->GetChildren().size()) - 1);
    InvalidateRouterColumnNodes();
    if (needPushPageToPrimaryStateHandling) {
        NormalizeRouterColumnsAfterStackChange();
    } else {
        RebuildRouterColumnNodesIfNeeded();
    }
    auto pattern = node->GetPattern<PagePattern>();
    if (pattern) {
        pattern->ResetPageTransitionEffect();
    }
    auto newVisiblePages = GetRouterVisiblePages();
    if (stagePattern->GetIsSplit() && !newVisiblePages.detail && relatedOrPhPage) {
        newVisiblePages.detail = relatedOrPhPage;
    }

    auto isPushToPrimary = needPushPageToPrimaryStateHandling &&
        CheckIfMovePageToPrimaryIsAllowed(preVisiblePages, newVisiblePages);
    auto isPopToSecondary =
        needPushPageToPrimaryStateHandling && CheckIfMovePageToSecondaryIsAllowed(preVisiblePages, newVisiblePages);
    auto hideTransitionType = PageTransitionType::NONE;
    auto showTransitionType = PageTransitionType::NONE;
    if (needTransition) {
        if (isPushToPrimary) {
            hideTransitionType = GetRouterPushHideTransitionType(true);
            showTransitionType = GetRouterPushShowTransitionType(true);
        } else if (isPopToSecondary) {
            hideTransitionType = GetRouterPopHideTransitionType(true);
            showTransitionType = GetRouterPopShowTransitionType(true);
        }
    }
    if (needHideLast) {
        FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages, hideTransitionType);
    }
    FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages, showTransitionType);
    bool animated = false;
    if (!needPushPageToPrimaryStateHandling) {
        EnsureSplitSecondaryPageIfNeeded();
    } else if (needTransition && (isPushToPrimary || isPopToSecondary)) {
        animated = StartRouterSplitAnimation(preVisiblePages, newVisiblePages);
    }

    auto lastHomePage = GetHomePage();
    stagePattern->SetHomePage(lastHomePage);

    RefPtr<FrameNode> outPageNode = preVisiblePages.detail;
    if (outPageNode) {
        auto outPattern = outPageNode->GetPattern<ParallelPagePattern>();
        if (outPattern && outPattern->GetPageType() == RouterPageType::PLACEHOLDER_PAGE) {
            outPageNode.Reset();
        }
    }
    if (!outPageNode) {
        outPageNode = preVisiblePages.primary ? preVisiblePages.primary : lastPage;
    }
    AddPageTransitionTrace(outPageNode, node);
    FireAutoSave(outPageNode, node);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (needTransition && !animated) {
        ReportPageTransitionEnd(node);
    }
    return true;
}

void ParallelStageManager::InvalidateRouterColumnNodes() const
{
    routerColumnNodesDirty_ = true;
}

void ParallelStageManager::RebuildRouterColumnNodesIfNeeded() const
{
    if (!routerColumnNodesDirty_) {
        return;
    }
    primaryNodes_.clear();
    secondaryNodes_.clear();
    CHECK_NULL_VOID(stageNode_);
    std::vector<RefPtr<FrameNode>> stackPages;
    RefPtr<FrameNode> homePage;
    const auto& children = stageNode_->GetChildren();
    for (const auto& child : children) {
        auto page = AceType::DynamicCast<FrameNode>(child);
        if (!page || page->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        auto type = pattern->GetPageType();
        if (type == RouterPageType::PLACEHOLDER_PAGE || type == RouterPageType::RELATED_PAGE) {
            continue;
        }
        stackPages.emplace_back(page);
        if (type == RouterPageType::HOME_PAGE) {
            homePage = page;
        }
    }

    if (!homePage) {
        // Before home page detection, all stack pages are temporarily displayed on the primary side,
        // so primaryNodes_ records the current primary-column distribution.
        // ColumnType is still not treated as valid primary/secondary ownership at this stage.
        for (const auto& page : stackPages) {
            primaryNodes_.emplace_back(page);
        }
        routerColumnNodesDirty_ = false;
        return;
    }

    bool passedHomePage = false;
    for (const auto& page : stackPages) {
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_CONTINUE(pattern);
        if (!passedHomePage) {
            primaryNodes_.emplace_back(page);
            if (page == homePage) {
                passedHomePage = true;
            }
            continue;
        }
        auto columnType = pattern->GetColumnType();
        if (columnType == ForceSplitPageColumnType::PRIMARY) {
            primaryNodes_.emplace_back(page);
        } else {
            secondaryNodes_.emplace_back(page);
        }
    }
    routerColumnNodesDirty_ = false;
}

RefPtr<FrameNode> ParallelStageManager::GetTopPrimaryColumnPage() const
{
    RebuildRouterColumnNodesIfNeeded();
    while (!primaryNodes_.empty()) {
        auto node = primaryNodes_.back().Upgrade();
        if (node && stageNode_ && stageNode_->GetChildIndex(node) >= 0) {
            return node;
        }
        primaryNodes_.pop_back();
    }
    return nullptr;
}

RefPtr<FrameNode> ParallelStageManager::GetTopSecondaryColumnPage() const
{
    if (!GetHomePage()) {
        return nullptr;
    }
    RebuildRouterColumnNodesIfNeeded();
    while (!secondaryNodes_.empty()) {
        auto node = secondaryNodes_.back().Upgrade();
        if (node && stageNode_ && stageNode_->GetChildIndex(node) >= 0) {
            return node;
        }
        secondaryNodes_.pop_back();
    }
    return nullptr;
}

void ParallelStageManager::FireRouterHideByVisibleDiff(const RouterVisiblePages& preVisiblePages,
    const RouterVisiblePages& newVisiblePages, PageTransitionType transitionType)
{
    auto existInNewVisiblePages = [&newVisiblePages](const RefPtr<FrameNode>& page) {
        return page && (page == newVisiblePages.primary || page == newVisiblePages.detail);
    };
    if (preVisiblePages.primary && !existInNewVisiblePages(preVisiblePages.primary)) {
        FireParallelPageHide(preVisiblePages.primary, transitionType);
    }
    if (preVisiblePages.detail && preVisiblePages.detail != preVisiblePages.primary &&
        !existInNewVisiblePages(preVisiblePages.detail)) {
        FireParallelPageHide(preVisiblePages.detail, transitionType);
    }
}

void ParallelStageManager::FireRouterShowByVisibleDiff(const RouterVisiblePages& preVisiblePages,
    const RouterVisiblePages& newVisiblePages, PageTransitionType transitionType)
{
    auto existInPreVisiblePages = [&preVisiblePages](const RefPtr<FrameNode>& page) {
        return page && (page == preVisiblePages.primary || page == preVisiblePages.detail);
    };
    auto fireShow = [this, transitionType](const RefPtr<FrameNode>& page) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        auto pageType = pattern->GetPageType();
        if (pageType == RouterPageType::PLACEHOLDER_PAGE || pageType == RouterPageType::RELATED_PAGE) {
            MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, transitionType);
            return;
        }
        FireParallelPageShow(page, transitionType);
    };
    if (newVisiblePages.primary && !existInPreVisiblePages(newVisiblePages.primary)) {
        fireShow(newVisiblePages.primary);
    }
    if (newVisiblePages.detail && newVisiblePages.detail != newVisiblePages.primary &&
        !existInPreVisiblePages(newVisiblePages.detail)) {
        fireShow(newVisiblePages.detail);
    }
}

void ParallelStageManager::FireLifecycleOnPopByVisibleDiff(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages,
    bool needShowNext, PageTransitionType hideTransitionType, PageTransitionType showTransitionType)
{
    FireRouterHideByVisibleDiff(preVisiblePages, newVisiblePages, hideTransitionType);
    if (!needShowNext) {
        return;
    }
    FireRouterShowByVisibleDiff(preVisiblePages, newVisiblePages, showTransitionType);
}

void ParallelStageManager::EnsureSplitSecondaryPageIfNeeded()
{
    CHECK_NULL_VOID(stageNode_);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit()) {
        return;
    }
    auto page = GetRelatedOrPlaceHolderPage();
    CHECK_NULL_VOID(page);
    if (!GetHomePage()) {
        if (stageNode_->GetChildIndex(page) < 0) {
            MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, PageTransitionType::NONE);
        }
        return;
    }
    if (GetTopSecondaryColumnPage()) {
        return;
    }
    if (stageNode_->GetChildIndex(page) < 0) {
        MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, PageTransitionType::NONE);
    }
}

bool ParallelStageManager::HasRouterPushPageToPrimaryState() const
{
    auto manager = const_cast<ParallelStageManager*>(this);
    manager->RebuildRouterColumnNodesIfNeeded();
    if (manager->primaryNodes_.empty() || manager->secondaryNodes_.empty()) {
        return false;
    }
    // Only treat it as push-page-to-primary state when a non-home page has really been moved into the primary column.
    for (const auto& weakNode : manager->primaryNodes_) {
        auto node = weakNode.Upgrade();
        if (!node || !stageNode_ || stageNode_->GetChildIndex(node) < 0) {
            continue;
        }
        auto pattern = node->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        if (pattern->GetPageType() == RouterPageType::DETAIL_PAGE) {
            return true;
        }
    }
    return false;
}

bool ParallelStageManager::ShouldCurrentPushPageToPrimary(const RefPtr<FrameNode>& newPageNode) const
{
    if (!IsVirtualStackBasedSplit()) {
        return false;
    }
    if (isNewPageReplacing_) {
        return false;
    }
    auto currentTopPage = GetLastPageInStack();
    CHECK_NULL_RETURN(currentTopPage, false);
    return ShouldMovePageToPrimaryForTransition(currentTopPage, newPageNode, false) ||
        HasRouterPushPageToPrimaryState();
}

RefPtr<FrameNode> ParallelStageManager::GetLastPageInStack() const
{
    auto stackPages = CollectRouterStackPages();
    return stackPages.empty() ? nullptr : stackPages.back();
}

std::vector<RefPtr<FrameNode>> ParallelStageManager::CollectRouterStackPages() const
{
    std::vector<RefPtr<FrameNode>> emptyExcludedPages;
    return CollectRouterStackPages(emptyExcludedPages);
}

std::vector<RefPtr<FrameNode>> ParallelStageManager::CollectRouterStackPages(
    const std::vector<RefPtr<FrameNode>>& excludedPages) const
{
    std::vector<RefPtr<FrameNode>> stackPages;
    CHECK_NULL_RETURN(stageNode_, stackPages);
    auto isExcluded = [&excludedPages](const RefPtr<FrameNode>& page) {
        return std::find(excludedPages.begin(), excludedPages.end(), page) != excludedPages.end();
    };
    const auto& children = stageNode_->GetChildren();
    for (const auto& child : children) {
        auto page = AceType::DynamicCast<FrameNode>(child);
        if (!page || page->GetTag() != V2::PAGE_ETS_TAG || isExcluded(page)) {
            continue;
        }
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        // EXIT_POP pages may stay mounted until their own finish callback removes them,
        // but logically they have already been popped and must not participate in stack calculation.
        if (pattern->GetPageInTransition() && pattern->GetSplitTransitionType() == PageTransitionType::EXIT_POP) {
            continue;
        }
        auto type = pattern->GetPageType();
        if (type == RouterPageType::PLACEHOLDER_PAGE || type == RouterPageType::RELATED_PAGE) {
            continue;
        }
        stackPages.emplace_back(page);
    }
    return stackPages;
}

ForceSplitPageColumnType ParallelStageManager::GetPageColumnType(const RefPtr<FrameNode>& page) const
{
    CHECK_NULL_RETURN(page, ForceSplitPageColumnType::NONE);
    auto pattern = page->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, ForceSplitPageColumnType::NONE);
    auto columnType = pattern->GetColumnType();
    if (columnType != ForceSplitPageColumnType::NONE) {
        return columnType;
    }
    auto type = pattern->GetPageType();
    if (type == RouterPageType::HOME_PAGE) {
        return ForceSplitPageColumnType::PRIMARY;
    }
    if (type == RouterPageType::DETAIL_PAGE) {
        return ForceSplitPageColumnType::SECONDARY;
    }
    return ForceSplitPageColumnType::NONE;
}

void ParallelStageManager::SetPageColumnType(const RefPtr<FrameNode>& page, ForceSplitPageColumnType columnType)
{
    CHECK_NULL_VOID(page);
    auto pattern = page->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetColumnType() == columnType) {
        return;
    }
    pattern->SetColumnType(columnType);
    InvalidateRouterColumnNodes();
}

void ParallelStageManager::ClearRouterPageState(const RefPtr<FrameNode>& page)
{
    CHECK_NULL_VOID(page);
    auto pattern = page->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetColumnType() == ForceSplitPageColumnType::NONE) {
        return;
    }
    pattern->SetColumnType(ForceSplitPageColumnType::NONE);
    InvalidateRouterColumnNodes();
}


void ParallelStageManager::OnStageNodeStructureChanged()
{
    InvalidateRouterColumnNodes();
}

int32_t ParallelStageManager::GetPrimaryNodeCount() const
{
    auto self = const_cast<ParallelStageManager*>(this);
    self->RebuildRouterColumnNodesIfNeeded();
    int32_t count = 0;
    for (const auto& weakNode : self->primaryNodes_) {
        auto node = weakNode.Upgrade();
        if (node && stageNode_ && stageNode_->GetChildIndex(node) >= 0) {
            ++count;
        }
    }
    return count;
}

bool ParallelStageManager::ShouldMovePageToPrimaryForTransition(
    const RefPtr<FrameNode>& fromPage, const RefPtr<FrameNode>& toPage, bool onlyWhenSplit) const
{
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    if (onlyWhenSplit && (!stagePattern->GetIsSplit() || needClearSecondaryPage_)) {
        return false;
    }
    CHECK_NULL_RETURN(fromPage, false);
    CHECK_NULL_RETURN(toPage, false);
    if (fromPage == toPage) {
        return false;
    }
    auto homePage = GetHomePage();
    if (!homePage) {
        return false;
    }
    if (fromPage == homePage || toPage == homePage) {
        return false;
    }
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto forceSplitMgr = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(forceSplitMgr, false);
    auto fromPattern = fromPage->GetPattern<ParallelPagePattern>();
    auto toPattern = toPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(fromPattern, false);
    CHECK_NULL_RETURN(toPattern, false);
    auto fromInfo = fromPattern->GetPageInfo();
    auto toInfo = toPattern->GetPageInfo();
    CHECK_NULL_RETURN(fromInfo, false);
    CHECK_NULL_RETURN(toInfo, false);
    return forceSplitMgr->IsTransitionShouldMovePageToPrimary(fromInfo->GetPageUrl(), toInfo->GetPageUrl());
}

bool ParallelStageManager::FinalizeRouterStackChange(
    const RouterVisiblePages& beforeVisible, const RouterVisiblePages& afterVisible, bool needTransition)
{
    NormalizeRouterColumnsAfterStackChange(afterVisible);
    auto animated = needTransition && StartRouterSplitAnimation(beforeVisible, afterVisible);
    return animated;
}

void ParallelStageManager::NormalizeRouterColumnsAfterStackChange()
{
    RebuildRouterColumnNodesIfNeeded();
    if (!GetHomePage()) {
        return;
    }
    auto topPage = GetLastPageInStack();
    CHECK_NULL_VOID(topPage);
    auto topPattern = topPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(topPattern);
    bool needDemoteTopPage = false;
    auto rawColumnType = topPattern->GetColumnType();
    if (rawColumnType == ForceSplitPageColumnType::PRIMARY) {
        // After the stack top changes, a detail page cannot continue occupying the primary side
        // when another page is already the primary owner.
        needDemoteTopPage = primaryNodes_.size() > 1;
    } else if (rawColumnType == ForceSplitPageColumnType::NONE &&
        topPattern->GetPageType() != RouterPageType::HOME_PAGE) {
        needDemoteTopPage = true;
    }
    if (!needDemoteTopPage) {
        return;
    }
    SetPageColumnType(topPage, ForceSplitPageColumnType::SECONDARY);
    RebuildRouterColumnNodesIfNeeded();
}

void ParallelStageManager::NormalizeRouterColumnsAfterStackChange(const RouterVisiblePages& afterVisible)
{
    NormalizeRouterColumnsAfterStackChange();
    if (!GetHomePage()) {
        return;
    }
    if (afterVisible.primary && afterVisible.primary != afterVisible.detail) {
        auto primaryPattern = afterVisible.primary->GetPattern<ParallelPagePattern>();
        if (primaryPattern && primaryPattern->GetPageType() != RouterPageType::HOME_PAGE) {
            SetPageColumnType(afterVisible.primary, ForceSplitPageColumnType::PRIMARY);
        }
    }
    if (afterVisible.detail && afterVisible.detail != afterVisible.primary) {
        auto detailPattern = afterVisible.detail->GetPattern<ParallelPagePattern>();
        if (detailPattern && detailPattern->GetPageType() == RouterPageType::DETAIL_PAGE) {
            SetPageColumnType(afterVisible.detail, ForceSplitPageColumnType::SECONDARY);
        }
    }
    RebuildRouterColumnNodesIfNeeded();
}

void ParallelStageManager::UpdateRouterColumnsOnPush(
    const RefPtr<FrameNode>& currentTopPage, const RefPtr<FrameNode>& newPageNode)
{
    CHECK_NULL_VOID(newPageNode);
    if (ShouldMovePageToPrimaryForTransition(currentTopPage, newPageNode)) {
        SetPageColumnType(currentTopPage, ForceSplitPageColumnType::PRIMARY);
    }
    SetPageColumnType(newPageNode, ForceSplitPageColumnType::SECONDARY);
}

ParallelStageManager::RouterVisiblePages ParallelStageManager::GetRouterVisiblePagesForCurrentStackTree() const
{
    RouterVisiblePages visiblePages;
    visiblePages.detail = GetLastPageInStack();
    return visiblePages;
}

ParallelStageManager::RouterVisiblePages ParallelStageManager::GetRouterVisiblePagesForCurrentSplitTree() const
{
    RouterVisiblePages visiblePages;
    CHECK_NULL_RETURN(stageNode_, visiblePages);
    RefPtr<FrameNode> secondaryFallbackPage = nullptr;
    auto relatedOrPlaceholderPage = const_cast<ParallelStageManager*>(this)->GetRelatedOrPlaceHolderPage();
    if (relatedOrPlaceholderPage && stageNode_->GetChildIndex(relatedOrPlaceholderPage) >= 0) {
        secondaryFallbackPage = relatedOrPlaceholderPage;
    }
    visiblePages.primary = GetTopPrimaryColumnPage();
    visiblePages.detail = GetTopSecondaryColumnPage();
    if (!visiblePages.detail) {
        visiblePages.detail = secondaryFallbackPage;
    }
    if (!visiblePages.primary) {
        visiblePages.primary = GetLastPageInStack();
    }
    if (visiblePages.primary == visiblePages.detail) {
        visiblePages.primary.Reset();
    }
    return visiblePages;
}

ParallelStageManager::RouterVisiblePages ParallelStageManager::GetRouterVisiblePages()
{
    RouterVisiblePages visiblePages;
    CHECK_NULL_RETURN(stageNode_, visiblePages);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, visiblePages);
    if (!stagePattern->GetIsSplit()) {
        return GetRouterVisiblePagesForCurrentStackTree();
    }
    return GetRouterVisiblePagesForCurrentSplitTree();
}

ParallelStageManager::RouterVisiblePages ParallelStageManager::ResolveRouterVisiblePagesFromStackPages(
    const std::vector<RefPtr<FrameNode>>& stackPages, const RefPtr<FrameNode>& secondaryFallbackPage) const
{
    RouterVisiblePages visiblePages;
    CHECK_NULL_RETURN(stageNode_, visiblePages);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, visiblePages);
    if (!stagePattern->GetIsSplit()) {
        if (!stackPages.empty()) {
            visiblePages.detail = stackPages.back();
        }
        return visiblePages;
    }
    RefPtr<FrameNode> homePage = nullptr;
    for (const auto& page : stackPages) {
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (pattern && pattern->GetPageType() == RouterPageType::HOME_PAGE) {
            homePage = page;
            break;
        }
    }
    if (!homePage) {
        if (!stackPages.empty()) {
            visiblePages.primary = stackPages.back();
        }
        visiblePages.detail = secondaryFallbackPage;
        return visiblePages;
    }

    std::vector<RefPtr<FrameNode>> primaryPages;
    std::vector<RefPtr<FrameNode>> secondaryPages;
    bool passedHomePage = false;
    for (const auto& page : stackPages) {
        if (!passedHomePage) {
            primaryPages.emplace_back(page);
            if (page == homePage) {
                passedHomePage = true;
            }
            continue;
        }
        if (GetPageColumnType(page) == ForceSplitPageColumnType::PRIMARY) {
            primaryPages.emplace_back(page);
        } else {
            secondaryPages.emplace_back(page);
        }
    }
    if (!stackPages.empty()) {
        auto topPage = stackPages.back();
        if (topPage != homePage && !primaryPages.empty() && primaryPages.back() == topPage && primaryPages.size() > 1) {
            // Mirror NormalizeRouterColumnsAfterStackChange() for predicted stack results:
            // once the real top page changes, it should fall back to the secondary side
            // while another page still owns the primary side.
            primaryPages.pop_back();
            secondaryPages.emplace_back(topPage);
        }
    }
    if (!primaryPages.empty()) {
        visiblePages.primary = primaryPages.back();
    }
    if (!secondaryPages.empty()) {
        visiblePages.detail = secondaryPages.back();
    } else {
        visiblePages.detail = secondaryFallbackPage;
    }
    if (visiblePages.primary == visiblePages.detail) {
        visiblePages.primary.Reset();
    }
    return visiblePages;
}

ParallelStageManager::RouterVisiblePages ParallelStageManager::GetRouterVisiblePagesExcluding(
    const std::vector<RefPtr<FrameNode>>& excludedPages)
{
    RouterVisiblePages visiblePages;
    CHECK_NULL_RETURN(stageNode_, visiblePages);
    auto isExcluded = [&excludedPages](const RefPtr<FrameNode>& page) {
        return std::find(excludedPages.begin(), excludedPages.end(), page) != excludedPages.end();
    };
    auto stackPages = CollectRouterStackPages(excludedPages);
    RefPtr<FrameNode> secondaryFallbackPage = nullptr;
    auto relatedOrPlaceholderPage = GetRelatedOrPlaceHolderPage();
    if (relatedOrPlaceholderPage && !isExcluded(relatedOrPlaceholderPage) &&
        stageNode_->GetChildIndex(relatedOrPlaceholderPage) >= 0) {
        secondaryFallbackPage = relatedOrPlaceholderPage;
    }
    return ResolveRouterVisiblePagesFromStackPages(stackPages, secondaryFallbackPage);
}

bool ParallelStageManager::CheckIfMovePageToPrimaryIsAllowed(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages) const
{
    if (!preVisiblePages.primary || !preVisiblePages.detail || !newVisiblePages.primary || !newVisiblePages.detail) {
        return false;
    }
    if (preVisiblePages.primary == preVisiblePages.detail || newVisiblePages.primary == newVisiblePages.detail) {
        return false;
    }
    return preVisiblePages.detail == newVisiblePages.primary && preVisiblePages.primary != newVisiblePages.detail;
}

bool ParallelStageManager::CheckIfMovePageToSecondaryIsAllowed(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages) const
{
    if (!preVisiblePages.primary || !preVisiblePages.detail || !newVisiblePages.primary || !newVisiblePages.detail) {
        return false;
    }
    if (preVisiblePages.primary == preVisiblePages.detail || newVisiblePages.primary == newVisiblePages.detail) {
        return false;
    }
    return newVisiblePages.detail == preVisiblePages.primary && newVisiblePages.primary != preVisiblePages.detail;
}

RefPtr<FrameNode> ParallelStageManager::GetRouterTransitionEndPageForCurrentVisible()
{
    auto visiblePages = GetRouterVisiblePages();
    if (visiblePages.detail) {
        return visiblePages.detail;
    }
    if (visiblePages.primary) {
        return visiblePages.primary;
    }
    return GetLastPageInStack();
}

void ParallelStageManager::UpdateRouterSplitPlaceholder()
{
    CHECK_NULL_VOID(stageNode_);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    if (!stagePattern->GetIsSplit()) {
        RefPtr<FrameNode> removedPage;
        RemoveRelatedOrPlaceHolderPageIfExist(removedPage, true);
        return;
    }
    RefPtr<FrameNode> removedPage;
    RemoveRelatedOrPlaceHolderPageIfExist(removedPage, false);
    RebuildRouterColumnNodesIfNeeded();
    auto primaryPage = GetTopPrimaryColumnPage();
    if (primaryPage && !GetTopSecondaryColumnPage()) {
        auto page = GetRelatedOrPlaceHolderPage();
        MountAndShowRelatedOrPlaceHolderPageIfNeeded(page, PageTransitionType::NONE);
    }
}

void ParallelStageManager::ResetRouterAnimatedPages()
{
    bool removedAnyPage = false;
    for (const auto& animatedPage : routerAnimatedPages_) {
        auto page = animatedPage.page.Upgrade();
        auto pattern = page ? page->GetPattern<ParallelPagePattern>() : nullptr;
        if (!pattern) {
            continue;
        }
        pattern->AbortSplitTransition();
        // Abort should still settle the stack to the post-operation result:
        // EXIT_POP detaches immediately, other EXIT_* pages hide immediately.
        if (animatedPage.transitionType == PageTransitionType::EXIT_POP) {
            page->SetChildrenInDestroying();
            CHECK_NULL_CONTINUE(stageNode_);
            if (stageNode_->GetChildIndex(page) >= 0) {
                stageNode_->RemoveChild(page);
                removedAnyPage = true;
            }
            continue;
        }
        if (animatedPage.transitionType == PageTransitionType::EXIT_PUSH) {
            pattern->ProcessHideState();
        }
    }
    if (removedAnyPage && stageNode_) {
        stageNode_->RebuildRenderContextTree();
        OnStageNodeStructureChanged();
        auto context = stageNode_->GetContext();
        if (context) {
            context->RequestFrame();
        }
    }
    ClearCurrentRouterAnimationState();
}

void ParallelStageManager::OnRouterPagesSplitPushStart(
    const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage, const RefPtr<FrameNode>& enterPage)
{
    auto applyStart = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnSplitTransitionStart(type);
    };
    // Split manager only dispatches the push-start phase and role to each page.
    applyStart(exitPage, PageTransitionType::EXIT_PUSH);
    applyStart(movePage, PageTransitionType::MOVE_PUSH);
    applyStart(enterPage, PageTransitionType::ENTER_PUSH);
}

void ParallelStageManager::OnRouterPagesSplitPushEnd(
    const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage, const RefPtr<FrameNode>& enterPage)
{
    auto updateEndState = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSplitTransitionState(type, SplitTransitionPhase::END);
    };
    auto applyEnd = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnSplitTransitionEnd(type);
    };
    updateEndState(exitPage, PageTransitionType::EXIT_PUSH);
    updateEndState(movePage, PageTransitionType::MOVE_PUSH);
    updateEndState(enterPage, PageTransitionType::ENTER_PUSH);
    CHECK_NULL_VOID(stageNode_);
    auto context = stageNode_->GetContext();
    CHECK_NULL_VOID(context);
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    applyEnd(exitPage, PageTransitionType::EXIT_PUSH);
    applyEnd(movePage, PageTransitionType::MOVE_PUSH);
    applyEnd(enterPage, PageTransitionType::ENTER_PUSH);
}

void ParallelStageManager::OnRouterPagesSplitPopStart(
    const RefPtr<FrameNode>& enterPage, const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage)
{
    auto applyStart = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnSplitTransitionStart(type);
    };
    // Split manager only dispatches the pop-start phase and role to each page.
    applyStart(enterPage, PageTransitionType::ENTER_POP);
    applyStart(movePage, PageTransitionType::MOVE_POP);
    applyStart(exitPage, PageTransitionType::EXIT_POP);
}

void ParallelStageManager::OnRouterPagesSplitPopEnd(
    const RefPtr<FrameNode>& enterPage, const RefPtr<FrameNode>& exitPage, const RefPtr<FrameNode>& movePage)
{
    auto updateEndState = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->UpdateSplitTransitionState(type, SplitTransitionPhase::END);
    };
    auto applyEnd = [](const RefPtr<FrameNode>& page, PageTransitionType type) {
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnSplitTransitionEnd(type);
    };
    updateEndState(enterPage, PageTransitionType::ENTER_POP);
    updateEndState(movePage, PageTransitionType::MOVE_POP);
    updateEndState(exitPage, PageTransitionType::EXIT_POP);
    CHECK_NULL_VOID(stageNode_);
    auto context = stageNode_->GetContext();
    CHECK_NULL_VOID(context);
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    context->FlushUITasks();
    applyEnd(enterPage, PageTransitionType::ENTER_POP);
    applyEnd(movePage, PageTransitionType::MOVE_POP);
    applyEnd(exitPage, PageTransitionType::EXIT_POP);
}

void ParallelStageManager::SetRouterDividerVisible(bool visible)
{
    CHECK_NULL_VOID(stageNode_);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_VOID(stagePattern);
    auto dividerNode = stagePattern->GetDividerNode();
    CHECK_NULL_VOID(dividerNode);
    auto layoutProperty = dividerNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto targetVisible = visible ? VisibleType::VISIBLE : VisibleType::INVISIBLE;
    if (layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) == targetVisible) {
        return;
    }
    // Divider stays mounted and still occupies layout space during animation; only visibility changes.
    layoutProperty->UpdateVisibility(targetVisible, false, false);
    dividerNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void ParallelStageManager::OnRouterPagesSplitFinish(
    const std::vector<RouterAnimatedPageInfo>& animatedPages, int32_t animationId)
{
    for (const auto& animatedPage : animatedPages) {
        auto page = animatedPage.page.Upgrade();
        CHECK_NULL_CONTINUE(page);
        auto pattern = page->GetPattern<ParallelPagePattern>();
        CHECK_NULL_CONTINUE(pattern);
        // Each page decides whether this callback still belongs to its latest split animation.
        pattern->OnSplitTransitionFinish(animationId, animatedPage.transitionType);
    }
}

void ParallelStageManager::ClearCurrentRouterAnimationState()
{
    SetRouterDividerVisible(true);
    routerAnimatedPages_.clear();
    routerFocusOnFinishPage_.Reset();
    routerTransitionEndPage_.Reset();
}

void ParallelStageManager::AddRouterAnimatedPage(
    const RefPtr<FrameNode>& page, PageTransitionType transitionType, int32_t animationId)
{
    CHECK_NULL_VOID(page);
    auto pattern = page->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    // Split manager assigns the role, while each page owns its local animation-id state.
    pattern->PrepareSplitTransition(animationId, transitionType);
    RouterAnimatedPageInfo pageInfo;
    pageInfo.page = page;
    pageInfo.transitionType = transitionType;
    routerAnimatedPages_.emplace_back(std::move(pageInfo));
}

void ParallelStageManager::OnAbortAnimation()
{
    ResetRouterAnimatedPages();
}

bool ParallelStageManager::StartSplitPushAnimation(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages)
{
    if (!CheckIfMovePageToPrimaryIsAllowed(preVisiblePages, newVisiblePages)) {
        return false;
    }

    auto pushExitPage = preVisiblePages.primary;
    auto movingPage = preVisiblePages.detail;
    auto enteringPage = newVisiblePages.detail;
    auto animationId = ++animationId_;
    AddRouterAnimatedPage(pushExitPage, PageTransitionType::EXIT_PUSH, animationId);
    AddRouterAnimatedPage(movingPage, PageTransitionType::MOVE_PUSH, animationId);
    AddRouterAnimatedPage(enteringPage, PageTransitionType::ENTER_PUSH, animationId);
    routerFocusOnFinishPage_ = enteringPage;
    routerTransitionEndPage_ = enteringPage;

    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    // Flush once before the spring starts so START-state widths/slots are materialized,
    // then use render translate to place pages at their visual start positions.
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    pipeline->FlushUITasks();
    OnRouterPagesSplitPushStart(pushExitPage, movingPage, enteringPage);
    SetRouterDividerVisible(false);
    auto animatedPages = routerAnimatedPages_;
    AnimationOption option;
    option.SetCurve(ROUTER_SPLIT_PUSH_CURVE);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(0);
    option.SetOnFinishEvent([weak = WeakClaim(this), animationId, animatedPages]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->OnRouterPagesSplitFinish(animatedPages, animationId);
        if (manager->GetAnimationId() != animationId) {
            return;
        }
        auto focusPage = manager->routerFocusOnFinishPage_.Upgrade();
        auto endPage = manager->routerTransitionEndPage_.Upgrade();
        manager->ClearCurrentRouterAnimationState();
        if (focusPage) {
            manager->UpdatePageFocus(focusPage);
        }
        if (endPage) {
            manager->ReportPageTransitionEnd(endPage);
        }
    });
    auto animation = AnimationUtils::StartAnimation(option, [
        weak = WeakClaim(this), weakPushExit = WeakPtr(pushExitPage),
        weakMoving = WeakPtr(movingPage), weakEntering = WeakPtr(enteringPage)]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->OnRouterPagesSplitPushEnd(
            weakPushExit.Upgrade(), weakMoving.Upgrade(), weakEntering.Upgrade());
    }, option.GetOnFinishEvent(), nullptr, stageNode_->GetContextRefPtr());
    AddAnimation(animation, true);
    return true;
}

bool ParallelStageManager::StartSplitPopAnimation(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages)
{
    if (!CheckIfMovePageToSecondaryIsAllowed(preVisiblePages, newVisiblePages)) {
        return false;
    }
    auto popEnterPage = newVisiblePages.primary;
    auto exitingPage = preVisiblePages.detail;
    auto movingPage = preVisiblePages.primary;
    auto animationId = ++animationId_;
    AddRouterAnimatedPage(popEnterPage, PageTransitionType::ENTER_POP, animationId);
    AddRouterAnimatedPage(exitingPage, PageTransitionType::EXIT_POP, animationId);
    AddRouterAnimatedPage(movingPage, PageTransitionType::MOVE_POP, animationId);
    routerFocusOnFinishPage_ = newVisiblePages.detail;
    routerTransitionEndPage_ = newVisiblePages.detail;

    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    // Materialize START-state widths/slots first, then use render translate to restore the
    // current visual relation before driving to the restored split relation.
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    pipeline->FlushUITasks();
    OnRouterPagesSplitPopStart(popEnterPage, exitingPage, movingPage);
    SetRouterDividerVisible(false);
    auto animatedPages = routerAnimatedPages_;
    AnimationOption option;
    option.SetCurve(ROUTER_SPLIT_POP_CURVE);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(0);
    option.SetOnFinishEvent([weak = WeakClaim(this), animationId, animatedPages]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->OnRouterPagesSplitFinish(animatedPages, animationId);
        if (manager->GetAnimationId() != animationId) {
            return;
        }
        auto focusPage = manager->routerFocusOnFinishPage_.Upgrade();
        auto endPage = manager->routerTransitionEndPage_.Upgrade();
        manager->ClearCurrentRouterAnimationState();
        if (focusPage) {
            manager->UpdatePageFocus(focusPage);
        }
        if (endPage) {
            manager->ReportPageTransitionEnd(endPage);
        }
    });
    auto animation = AnimationUtils::StartAnimation(option, [weak = WeakClaim(this),
        weakPopEnter = WeakPtr(popEnterPage), weakExiting = WeakPtr(exitingPage), weakMoving = WeakPtr(movingPage)]() {
        auto manager = weak.Upgrade();
        CHECK_NULL_VOID(manager);
        manager->OnRouterPagesSplitPopEnd(
            weakPopEnter.Upgrade(), weakExiting.Upgrade(), weakMoving.Upgrade());
    }, option.GetOnFinishEvent(), nullptr, stageNode_->GetContextRefPtr());
    AddAnimation(animation, false);
    return true;
}

bool ParallelStageManager::StartRouterSplitAnimation(
    const RouterVisiblePages& preVisiblePages, const RouterVisiblePages& newVisiblePages)
{
    // do not actively finish pages from the previous session here.
    // Each page owns its own finish timing and only settles in its own animation finish callback.
    ClearCurrentRouterAnimationState();
    // Router split animation currently only covers secondary-push-to-primary and primary-pop-to-secondary.
    return StartSplitPushAnimation(preVisiblePages, newVisiblePages) ||
        StartSplitPopAnimation(preVisiblePages, newVisiblePages);
}
}