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

#include <list>

#include "base/json/json_util.h"
#include "base/log/ace_checker.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/stage/force_split/parallel_stage_pattern.h"

namespace OHOS::Ace::NG {
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

    if (stagePattern->GetIsSplit()) {  // stack -> split
        TAG_LOGI(AceLogTag::ACE_ROUTER, "page mode change to split");
        AbortAnimation();
        auto primaryPage = GetLastPrimaryPage();
        CHECK_NULL_VOID(primaryPage);
        if (primaryPage != lastPage) {
            FireParallelPageShow(primaryPage, PageTransitionType::NONE, false);
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        if (lastPrimaryPage && lastPage != lastPrimaryPage) {
            FireParallelPageHide(lastPrimaryPage, PageTransitionType::NONE);
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

    auto primaryPage = GetLastPrimaryPage();
    if (show) {
        if (primaryPage && primaryPage != lastPage) {
            auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
            CHECK_NULL_VOID(primaryPattern);
            primaryPattern->OnShow(true);
        }
        lastPattern->OnShow(true);
        return;
    }

    lastPattern->OnHide(true);
    if (primaryPage && primaryPage != lastPage) {
        auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(primaryPattern);
        primaryPattern->OnHide(true);
    }
}

RefPtr<FrameNode> ParallelStageManager::GetLastPrimaryPage()
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
        if (pattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
            return node;
        }
    }
    return nullptr;
}

void ParallelStageManager::FirePageHideOnPushPage(
    RouterPageType newPageType, const RefPtr<FrameNode>& lastPage, const RefPtr<FrameNode>& topRelatedOrPhPage,
    const RefPtr<FrameNode>& prePrimaryPage, PageTransitionType hideTransitionType)
{
    auto lastPagePattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(lastPagePattern);
    auto lastPageType = lastPagePattern->GetPageType();
    if (newPageType == RouterPageType::SECONDARY_PAGE) {
        /**
         * push/replace: [ PrimaryA | SecondaryA/PlaceHolder/RelatedPage ]  ->  [ PrimaryA | SecondaryB ]
         *  The last page needs to trigger the onPageHide lifecycle.
         *
         * push/replace: [ PrimaryA | empty ]  ->  [ PrimaryA | SecondaryB ]
         *  The last page(PrimaryA) does not need to trigger the onPageHide lifecycle.
         */
        if (lastPage != prePrimaryPage) {
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
            prePrimaryPage) || (lastPage == prePrimaryPage)) {
            FireParallelPageHide(prePrimaryPage, hideTransitionType);
        }
        return;
    }
    // node -> RouterPageType::PRIMARY_PAGE
    if (topRelatedOrPhPage) {
        /**
         * [ PrimaryA | PlaceHolder/Related ]  ->  [ PrimaryB | PlaceHolder/Related ]
         *  PrimaryA -> onPageHide
         */
        if (prePrimaryPage) {
            FireParallelPageHide(prePrimaryPage, hideTransitionType);
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
    if (prePrimaryPage && prePrimaryPage != lastPage) {
        FireParallelPageHide(prePrimaryPage, hideTransitionType);
    }
}

void ParallelStageManager::FirePageShowOnPushPage(const RefPtr<FrameNode>& newTopPage,
    const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType showTransitionType)
{
    if (newTopPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
        /**
         * push: [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]  ->  [ PrimaryA | SecondaryB ]
         *  SecondaryB -> onPageShow
         * replace: [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ] -> [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);
        return;
    }

    // newTopPage -> RouterPageType::PRIMARY_PAGE
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }

    if (newTopPattern->GetPageType() != RouterPageType::SECONDARY_PAGE) {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "New routerPage must be Secondary page in SplitMode");
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
    return PushPageInSplitMode(node, isNewLifecycle, needHideLast, needTransition);
}

bool ParallelStageManager::PushPageInSplitMode(const RefPtr<FrameNode>& newPageNode,
    bool isNewLifecycle, bool needHideLast, bool needTransition)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto newTopPattern = newPageNode->GetPattern<ParallelPagePattern>();
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);
    auto prePrimaryPage = stagePattern->GetPrimaryPage();
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
            FirePageHideOnPushPage(
                newTopPattern->GetPageType(), lastPage, topRelatedOrPhPage, prePrimaryPage, hideTransitionType);
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
        FirePageHideOnPushPage(
            newTopPattern->GetPageType(), lastPage, topRelatedOrPhPage, prePrimaryPage, hideTransitionType);
    }
    stageNode_->RebuildRenderContextTree();

    FirePageShowOnPushPage(newPageNode, newTopPattern, PageTransitionType::NONE);

    auto lastPrimaryPage = GetLastPrimaryPage();
    stagePattern->SetPrimaryPage(lastPrimaryPage);

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
    if (preType == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryA -> onPageHide
         */
        FireParallelPageHide(preTopPage, hideTransitionType);
        return true;
    }
    if (preType == RouterPageType::PRIMARY_PAGE) {
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
    if (preType == RouterPageType::SECONDARY_PAGE) {
        if (newType == RouterPageType::SECONDARY_PAGE) {
            /**
             * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
             * [ SecondaryA ]  ->  [ SecondaryB ]
             *  SecondaryB -> onPageShow
             */
            FireParallelPageShow(newTopPage, showTransitionType);
            return true;
        }
        if (newType == RouterPageType::PRIMARY_PAGE) {
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
    if (preType == RouterPageType::PRIMARY_PAGE) {
        if (!relatedOrPhPage && !isNewPageReplacing_) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "PrimaryPage has no placeHolder/related Page in split mode");
        }
        if (newType == RouterPageType::SECONDARY_PAGE) {
            /**
             * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ PrimaryB | SecondaryA ]
             * [ PrimaryA | PlaceHolder/RelatedPage ]  ->  [ SecondaryA ]
             *  SecondaryA -> onPageShow
             */
            FireParallelPageShow(newTopPage, showTransitionType);
            return true;
        }
        if (newType == RouterPageType::PRIMARY_PAGE) {
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
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
        if (newTopPattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
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

    auto lastPrimaryPage = GetLastPrimaryPage();
    stagePattern_->SetPrimaryPage(lastPrimaryPage);

    preTopPage->SetChildrenInDestroying();
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        if (type != RouterPageType::PRIMARY_PAGE && type != RouterPageType::SECONDARY_PAGE) {
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
    if (type == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ SecondaryB ]/[ PrimaryA | xxx ] -> [ SecondaryA ]
         * [ PrimaryA | SecondaryB ] -> [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]
         *  SecondaryA/RelatedPage/PlaceHolder -> onPageShow
         */
        FireParallelPageShow(toPage, showTransitionType);
        return true;
    }
    if (type == RouterPageType::PRIMARY_PAGE) {
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
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

    auto lastPrimaryPage = GetLastPrimaryPage();
    stagePattern->SetPrimaryPage(lastPrimaryPage);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
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
        if (prePattern->GetPageType() != RouterPageType::PRIMARY_PAGE) {
            return false;
        }
        needHidePrimaryPage = false;
    } else if (lastPageType == RouterPageType::PRIMARY_PAGE) {
        return false;
    }

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
            if (pagePattern->GetPageType() != RouterPageType::PRIMARY_PAGE) {
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
    auto lastPrimaryPage = GetLastPrimaryPage();
    stagePattern->SetPrimaryPage(lastPrimaryPage);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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
        auto lastPrimaryPage = GetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }

    if (IsEmptyInSplitMode()) {
        return false;
    }

    auto newTopPattern = node->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(newTopPattern, false);
    if (newTopPattern->GetPageType() != RouterPageType::PRIMARY_PAGE &&
        newTopPattern->GetPageType() != RouterPageType::SECONDARY_PAGE) {
        return false;
    }

    const auto& lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    if (lastPage == node) {
        return true;
    }
    return MovePageToFrontInSplitMode(node, needHideLast, needTransition);
}

void ParallelStageManager::FirePageHideOnMovePageToFront(
    RouterPageType newTopPageType, const RefPtr<FrameNode>& preLastPage, PageTransitionType hideTransitionType)
{
    if (newTopPageType == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA/PlaceHolder/RelatedPage ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  preLastPage(SecondaryA/PlaceHolder/RelatedPage) -> onPageHide
         */
        FireParallelPageHide(preLastPage, hideTransitionType);
        return;
    }

    if (newTopPageType != RouterPageType::PRIMARY_PAGE) {
        TAG_LOGW(AceLogTag::ACE_ROUTER, "new top should be PrimaryPage or SecondaryPage");
        return;
    }

    // new top page is PrimaryPage
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
    if (newTopPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA/RelatedPage/PlaceHolder ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);
        return;
    }

    // RouterPageType::PRIMARY_PAGE
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
    RefPtr<FrameNode> prePrimaryPage = GetLastPrimaryPage();
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
        if (prePattern->GetPageType() != RouterPageType::PRIMARY_PAGE) {
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

    auto lastPrimaryPage = GetLastPrimaryPage();
    stagePattern->SetPrimaryPage(lastPrimaryPage);

    RefPtr<FrameNode> outPageNode = nullptr;
    if (relatedOrPhPage) {
        outPageNode = prePrimaryPage;
    } else {
        outPageNode = lastPage;
    }
    AddPageTransitionTrace(outPageNode, node);
    FireAutoSave(outPageNode, node);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
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

bool ParallelStageManager::OnPrimaryPageDetected(
    const RefPtr<FrameNode>& primaryPage, const std::list<WeakPtr<FrameNode>>& pageStack)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);

    auto preLastPrimaryPage = GetLastPrimaryPage();
    CHECK_NULL_RETURN(primaryPage, false);
    auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(primaryPattern, false);
    primaryPattern->SetPageType(RouterPageType::PRIMARY_PAGE);

    auto curLastPrimaryPage = GetLastPrimaryPage();
    stagePattern->SetPrimaryPage(curLastPrimaryPage);
    if (!stagePattern->GetIsSplit()) {
        return true;
    }
    if (!preLastPrimaryPage) {
        FireParallelPageShow(primaryPage, PageTransitionType::NONE);
    } else if (preLastPrimaryPage != curLastPrimaryPage) {
        FireParallelPageHide(preLastPrimaryPage, PageTransitionType::NONE);
        FireParallelPageShow(primaryPage, PageTransitionType::NONE);
    }

    /**
     * example:
     * replace(PrimaryC, standard)
     *  before: [ PrimaryA | RelatedPage/PlaceHolder ]
     *  after: [ PrimaryC ] [ RelatedPage/PlaceHolder ]
     *  step1: LoadPage (pageC has not yet been recognized as the PrimaryPage before it was created)
     *             Remove RelatedPage/PlaceHolder, and then add PageC
     *  step2: OnPrimaryPageDetected (we won't create placeHolderPage at this step)
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
        [primaryPage](const WeakPtr<FrameNode>& weakPage) {
            auto page = weakPage.Upgrade();
            if (!page) {
                return false;
            }
            return page == primaryPage;
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
    auto lastPrimaryPage = GetLastPrimaryPage();
    CHECK_NULL_RETURN(lastPrimaryPage, false);

    auto focusHub = lastPrimaryPage->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    auto pagePattern = lastPrimaryPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (focusHub->IsCurrentFocus()) {
        // If the primary page is focused, the focus should be exchanged to lastPage.
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
        auto primaryPage = stagePattern->GetPrimaryPage();
        if (primaryPage) {
            return primaryPage;
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

void ParallelStageManager::RemoveSecondaryPagesOfPrimaryHomePage()
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (secondaryPageStack_.empty()) {
        return;
    }
    for (auto iter = secondaryPageStack_.begin(); iter != secondaryPageStack_.end(); iter++) {
        auto detailPage = (*iter).Upgrade();
        if (!detailPage) {
            continue;
        }
        stageNode_->RemoveChild(detailPage);
        detailPage->SetChildrenInDestroying();
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    secondaryPageStack_.clear();
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
    auto needSyncPage = stagePattern->GetPrimaryPage();
    CHECK_NULL_VOID(needSyncPage);
    if (lastPage->GetPattern<ParallelPagePattern>()->GetPageType() == RouterPageType::PRIMARY_PAGE) {
        needSyncPage = GetLastPage();
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
        return;
    }
    StageManager::FirePageHide(node, transitionType);
}

int32_t ParallelStageManager::UpdateSecondaryPageNeedRemoved(bool needClearSecondaryPage)
{
    secondaryPageStack_.clear();
    const auto& children = stageNode_->GetChildren();
    if (!needClearSecondaryPage || children.empty()) {
        return 0;
    }
    bool findPrimaryPage = false;
    for (auto child = children.rbegin(); child != children.rend(); child++) {
        auto frameNode = AceType::DynamicCast<FrameNode>(*child);
        if (!frameNode) {
            continue;
        }
        if (frameNode->GetTag() != V2::PAGE_ETS_TAG) {
            continue;
        }
        auto pattern = frameNode->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        if (RouterPageType::SECONDARY_PAGE == pattern->GetPageType()) {
            secondaryPageStack_.emplace_back(WeakPtr<FrameNode>(frameNode));
        }
        if (RouterPageType::PRIMARY_PAGE == pattern->GetPageType()) {
            findPrimaryPage = true;
            break;
        }
    }
    if (!findPrimaryPage) {
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
        auto page = stagePattern->GetPrimaryPage();
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
}