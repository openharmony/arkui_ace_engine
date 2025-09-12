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
        auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(primaryPattern);
        auto phPage = primaryPattern->GetOrCreatePlaceHolderPage();
        MountAndShowPlaceHolderPageIfNeeded(phPage, PageTransitionType::NONE);
        return;
    }

    // split -> stack
    TAG_LOGI(AceLogTag::ACE_ROUTER, "page mode change to stack");
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(lastPattern);
    if (lastPattern->GetPageType() != RouterPageType::PLACEHOLDER_PAGE) {
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

    if (lastPattern->GetPageType() != RouterPageType::PLACEHOLDER_PAGE &&
        lastPattern->GetPageType() != RouterPageType::SECONDARY_PAGE) {
        return;
    }

    auto primaryPage = lastPattern->GetPrimaryPage();
    if (show) {
        if (primaryPage) {
            auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
            CHECK_NULL_VOID(primaryPattern);
            primaryPattern->OnShow(true);
        }
        lastPattern->OnShow(true);
        return;
    }

    lastPattern->OnHide(true);
    if (primaryPage) {
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

void ParallelStageManager::FirePageHideOnPushPage(RouterPageType newPageType,
    const RefPtr<FrameNode>& lastPage, const RefPtr<FrameNode>& topPhPage, PageTransitionType hideTransitionType)
{
    if (newPageType == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  lastPage -> onPageHide
         */
        FireParallelPageHide(lastPage, hideTransitionType);
        return;
    }
    // node -> RouterPageType::PRIMARY_PAGE
    if (topPhPage) {
        /**
         * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | PlaceHolderB ]
         *  PlaceHolderA -> onPageHide
         *  PrimaryA -> onPageHide
         */
        FireParallelPageHide(topPhPage, hideTransitionType);
        auto topPhPattern = topPhPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_VOID(topPhPattern);
        auto primaryPage = topPhPattern->GetPrimaryPage();
        if (primaryPage) {
            FireParallelPageHide(primaryPage, hideTransitionType);
        } else {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "placeHolder must has PRIMARY_PAGE");
        }
        return;
    }
    /**
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ SecondaryA ] -> [ PrimaryB | PlaceHolderB ]
     *  SecondaryA -> onPageHide
     *  PrimaryA? -> onPageHide
     */
    FireParallelPageHide(lastPage, hideTransitionType);
    auto pattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    auto primaryPage = pattern->GetPrimaryPage();
    if (primaryPage) {
        FireParallelPageHide(primaryPage, hideTransitionType);
    }
}

void ParallelStageManager::FirePageShowOnPushPage(const RefPtr<FrameNode>& newTopPage,
    const RefPtr<ParallelPagePattern>& newTopPattern, PageTransitionType showTransitionType)
{
    if (newTopPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);
        return;
    }

    // newTopPage -> RouterPageType::PRIMARY_PAGE
    /**
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ SecondaryA ] -> [ PrimaryB | PlaceHolderB ]
     *  PrimaryB -> onPageShow
     *  PlaceHolderB -> aboutToAppear
     *  PlaceHolderB -> onPageShow
     */
    FireParallelPageShow(newTopPage, showTransitionType);

    if (isNewPageReplacing_) {
        /**
         * when replacing page in new life cycle.
         *  step1: PushPage
         *  step2: move page node position
         *  step3: PopPage
         *
         *  do not mount & show placeHolder in step1,
         *  mount & show placeHolder in step3
         */
        return;
    }

    auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
    MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
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
        auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }

    if (newTopPattern->GetPageType() != RouterPageType::PRIMARY_PAGE &&
        newTopPattern->GetPageType() != RouterPageType::SECONDARY_PAGE) {
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
    auto preTopPage = GetLastPage();
    RefPtr<FrameNode> lastPage = nullptr;
    if (!IsEmptyInSplitMode()) {
        lastPage = GetLastPage();
        CHECK_NULL_RETURN(lastPage, false);
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }

    RefPtr<FrameNode> topPhPage = nullptr;
    if (!RemovePlaceHolderPageIfExist(topPhPage, false)) {
        return false;
    }

    PageTransitionType hideTransitionType = PageTransitionType::NONE;
    RefPtr<FrameNode> hidePageNode;
    if (!IsEmptyInSplitMode() && needHideLast) {
        hidePageNode = lastPage;
        if (!isNewLifecycle) {
            FirePageHideOnPushPage(newTopPattern->GetPageType(), lastPage, topPhPage, hideTransitionType);
        }
    }

    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    newPageNode->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    newPageNode->MountToParent(stageNode_);
    // then build the total child. Build will trigger page create and onAboutToAppear
    newPageNode->Build(nullptr);
    // when create PrimaryPage, we need to create PlaceHolderPage at sametime.
    do {
        if (newTopPattern->GetPageType() != RouterPageType::PRIMARY_PAGE) {
            break;
        }
        auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
        if (!newPhPage) {
            break;
        }
        auto newPhPattern = newPhPage->GetPattern<ParallelPagePattern>();
        if (!newPhPattern) {
            break;
        }
        newPhPage->GetRenderContext()->SyncGeometryProperties(rect);
        // mount to parent and mark build render tree.
        newPhPage->MountToParent(stageNode_);
        if (!newPhPattern->IsPlaceHolderPageBuildCompleted()) {
            // then build the total child. Build will trigger page create and onAboutToAppear
            newPhPage->Build(nullptr);
            newPhPage->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            newPhPattern->SetIsPlaceHolderPageBuildCompleted(true);
        }
        stageNode_->RemoveChild(newPhPage);
    } while (false);
    // fire top SecondaryPage lifecycle if need to clear
    if (needClearSecondaryPage_ && !secondaryPageStack_.empty() && preTopPage) {
        FirePageHideOnPopPage(topPhPage, preTopPage, newPageNode, newTopPattern, hideTransitionType);
    }

    // fire new lifecycle
    if (hidePageNode && needHideLast && isNewLifecycle) {
        FirePageHideOnPushPage(newTopPattern->GetPageType(), lastPage, topPhPage, hideTransitionType);
    }
    stageNode_->RebuildRenderContextTree();

    FirePageShowOnPushPage(newPageNode, newTopPattern, PageTransitionType::NONE);

    auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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

bool ParallelStageManager::FirePageHideOnPopPage(const RefPtr<FrameNode>& topPhPage,
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
        auto prePrimaryPage = preTopPattern->GetPrePrimaryPage();
        preTopPattern->SetPrePrimaryPage(nullptr);
        if (isNewPageReplacing_ && prePrimaryPage &&
            newTopPattern->GetPageType() == RouterPageType::PRIMARY_PAGE && prePrimaryPage != newTopPage) {
            /**
             * replace(PrimaryA, single)
             * stack bottom  -> stack top
             * [ PrimaryA ] [ SecondaryA ] [ PrimaryB ] [ SecondaryB ] -> [ SecondaryA ] [ PrimaryB ] [ PrimaryA ]
             *  step1: MovePageToFront
             *  step2: move page node position
             *  step3: PopPage
             *    we need to hide SecondaryB's pre PrimaryPage(that is PrimaryB) in step3.
             */
            FireParallelPageHide(prePrimaryPage, hideTransitionType);
        }
        return true;
    }
    if (preType == RouterPageType::PRIMARY_PAGE) {
        /**
         * replace(SecondaryA, single)
         * stack bottom -> stack top
         * [ SecondaryA ] [ PrimaryB ] [ PrimaryA ] -> [ PrimaryB ] [ SecondaryA ]
         *  step1: MovePageToFront
         *  step2: move page position
         *  step3: PopPage
         *    we need to hide PrimaryA's placeHolder page in step3.
         */
        RefPtr<FrameNode> phPage = topPhPage;
        if (isNewPageReplacing_ && !phPage) {
            phPage = preTopPattern->GetOrCreatePlaceHolderPage();
        }

        /**
         * [ PrimaryA | PlaceHolderA ]  ->  [ xxx ]
         * [ PrimaryA | PlaceHolderA ]  ->  [ xxx | xxx ]
         * [ PrimaryA | noPlaceHolder ]  ->  xxx    (newPageReplacing)
         *  PrimaryA -> onPageHide
         *  PlaceHolderA? -> onPageHide
         */
        if (phPage) {
            FireParallelPageHide(phPage, hideTransitionType);
        }
        FireParallelPageHide(preTopPage, hideTransitionType);
        return true;
    }
    TAG_LOGW(AceLogTag::ACE_ROUTER, "unexpected pre top page type: %{public}d", static_cast<int32_t>(preType));
    return false;
}

bool ParallelStageManager::FirePageShowOnPopPage(const RefPtr<FrameNode>& topPhPage,
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
             * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | PlaceHolderA ]
             *  PlaceHolderA -> aboutToAppear
             *  PlaceHolderA -> onPageShow
             */
            auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
            MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
            return true;
        }
        TAG_LOGW(AceLogTag::ACE_ROUTER, "unexpected newTopPage type: %{public}d when preTopPage type is: %{public}d",
            static_cast<int32_t>(newType), static_cast<int32_t>(preType));
        return false;
    }
    if (preType == RouterPageType::PRIMARY_PAGE) {
        if (!topPhPage && !isNewPageReplacing_) {
            TAG_LOGW(AceLogTag::ACE_ROUTER, "PrimaryPage has no placeHolder Page in split mode");
        }
        if (newType == RouterPageType::SECONDARY_PAGE) {
            /**
             * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | SecondaryA ]
             * [ PrimaryA | PlaceHolderA ]  ->  [ SecondaryA ]
             *  SecondaryA -> onPageShow
             *  PrimaryB? -> onPageShow
             */
            auto newPrimaryPage = newTopPattern->GetPrimaryPage();
            if (newPrimaryPage) {
                FireParallelPageShow(newPrimaryPage, showTransitionType);
            }
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
            auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
            MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
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
        auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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
    int32_t pageNumberExcludePlaceHolder = 0;
    if (!GetPageNumberExcludePlaceHolderPage(pageNumberExcludePlaceHolder)) {
        return false;
    }
    needTransition &= (pageNumberExcludePlaceHolder >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    RefPtr<FrameNode> phPage = nullptr;
    if (!RemovePlaceHolderPageIfExist(phPage, !isNewPageReplacing_)) {
        return false;
    }

    auto preTopPage = GetLastPage();
    CHECK_NULL_RETURN(preTopPage, false);
    auto preTopPattern = preTopPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(preTopPattern, false);
    RefPtr<FrameNode> newTopPage = nullptr;
    RefPtr<ParallelPagePattern> newTopPattern = nullptr;
    if (pageNumberExcludePlaceHolder >= transitionPageSize) {
        newTopPage = AceType::DynamicCast<FrameNode>(*(++children.rbegin()));
        CHECK_NULL_RETURN(newTopPage, false);
        newTopPattern = newTopPage->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(newTopPattern, false);
    }

    if (!FirePageHideOnPopPage(phPage, preTopPage, newTopPage, newTopPattern, PageTransitionType::NONE)) {
        return false;
    }

    PageTransitionType showTransitionType = PageTransitionType::NONE;
    if (needShowNext && pageNumberExcludePlaceHolder >= transitionPageSize) {
        if (!FirePageShowOnPopPage(
            phPage, preTopPage, preTopPattern, newTopPage, newTopPattern, showTransitionType)) {
            return false;
        }
    }
    do {
        if (!isNewPageReplacing_) {
            break;
        }
        /**
         * replace(PrimaryC, standard)
         *  stack bottom -> stack top
         *  before: [ PrimaryA ] [ SecondaryA ] [PrimaryB ] [SecondaryB ]
         *  after: [ PrimaryA ] [ SecondaryA ] [PrimaryB ] [PrimaryC ]
         *  step1: LoadPage (pageC has not yet been recognized as the PrimaryPage before it was created)
         *  step2: OnPrimaryPageDetected (we won't create placeHolderPage at this step)
         *  step3: move page node position
         *  step4: PopPage (we will create placeHolderPage at this step)
         *   we need to create, mount, show PrimaryC's placeHolder
         */
        if (newTopPattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
            auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
            MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
            break;
        }
        RefreshAndGetLastPrimaryPage();
        auto primaryPage = newTopPattern->GetPrimaryPage();
        if (primaryPage) {
            FireParallelPageShow(primaryPage, showTransitionType);
        }
    } while (false);

    // close keyboard
    PageChangeCloseKeyboard();

    AddPageTransitionTrace(preTopPage, newTopPage);
    FireAutoSave(preTopPage, newTopPage);

    stageNode_->RemoveChild(preTopPage);

    auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
    stagePattern_->SetPrimaryPage(lastPrimaryPage);

    preTopPage->SetChildrenInDestroying();
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    return true;
}

bool ParallelStageManager::GetPageNumberExcludePlaceHolderPage(int32_t& pageNumber)
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
    if (lastPattern->GetPageType() == RouterPageType::PLACEHOLDER_PAGE) {
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
    bool& addNewPhPage, PageTransitionType showTransitionType)
{
    auto pattern = toPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto type = pattern->GetPageType();
    if (type == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ xxx ]/[ xxx | xxx ] -> [ SecondaryA ]
         * [ xxx ]/[ xxx | xxx ] -> [ PrimaryA | SecondaryA ]
         *  SecondaryA -> onPageShow
         *  PrimaryA? -> onPageShow
         */
        FireParallelPageShow(toPage, showTransitionType);
        auto newPrimaryPage = pattern->GetPrimaryPage();
        if (newPrimaryPage) {
            FireParallelPageShow(newPrimaryPage, showTransitionType);
        }
        return true;
    }
    if (type == RouterPageType::PRIMARY_PAGE) {
        /**
         * [ PrimaryA | PlaceHolderA ] -> [ PrimaryB | PlaceHolderB ]
         * [ PrimaryA | SecondaryA ] -> [ PrimaryB | PlaceHolderB ]
         *  PrimaryB -> onPageShow
         *  PlaceHolderB -> aboutToAppear
         *  PlaceHolderB -> onPageShow
         */
        FireParallelPageShow(toPage, showTransitionType);
        auto newPhPage = pattern->GetOrCreatePlaceHolderPage();
        MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
        addNewPhPage = true;
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
        auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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
    if (!GetPageNumberExcludePlaceHolderPage(pageNumber)) {
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

    RefPtr<FrameNode> phPage = nullptr;
    if (!RemovePlaceHolderPageIfExist(phPage)) {
        return false;
    }

    auto firstFromPage = GetLastPage();
    auto iter = children.rbegin();
    std::advance(iter, popSize);
    RefPtr<FrameNode> toPage = AceType::DynamicCast<FrameNode>(*iter);
    if (!FirePageHideOnPopPageToIndex(popSize)) {
        return false;
    }

    bool addNewPhPage = false;
    if (needShowNext) {
        if (!FirePageShowOnPopPageToIndex(
            stagePattern, toPage, addNewPhPage, PageTransitionType::NONE)) {
            return false;
        }
    }
    AddPageTransitionTrace(firstFromPage, toPage);

    FireAutoSave(firstFromPage, toPage);

    for (int32_t current = 0; current < popSize; ++current) {
        RefPtr<UINode> pageNode = nullptr;
        if (addNewPhPage) {
            pageNode = *(++children.rbegin());
        } else {
            pageNode = GetLastPage();
        }
        stageNode_->RemoveChild(pageNode);
    }

    auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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
        auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
        stagePattern->SetPrimaryPage(lastPrimaryPage);
        return result;
    }
    return CleanPageStackInSplitMode(stagePattern);
}

bool ParallelStageManager::CleanPageStackInSplitMode(const RefPtr<ParallelStagePattern>& stagePattern)
{
    auto pipeline = stageNode_->GetContext();
    CHECK_NULL_RETURN(pipeline, false);

    int32_t pageNumberExcludePlaceHolder = 0;
    if (!GetPageNumberExcludePlaceHolderPage(pageNumberExcludePlaceHolder)) {
        return false;
    }
    constexpr int32_t PAGE_NUMBER = 2;
    if (pageNumberExcludePlaceHolder < PAGE_NUMBER) {
        return false;
    }
    const auto& children = stageNode_->GetChildren();
    bool needHidePrimaryPage = true;
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(lastPattern, false);
    if (lastPattern->GetPageType() == RouterPageType::PLACEHOLDER_PAGE) {
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
    } else if (lastPattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
        return false;
    }

    bool hasDivider = stagePattern->HasDividerNode();
    auto popSize = pageNumberExcludePlaceHolder - 1;
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
            pagePattern->SetPrimaryPage(nullptr);
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
    auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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
        auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
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

RefPtr<FrameNode> ParallelStageManager::RefreshAndGetLastPrimaryPage()
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    RefPtr<FrameNode> curPrimaryPage = nullptr;
    for (auto it = children.begin(); it != children.end(); ++it) {
        auto page = AceType::DynamicCast<FrameNode>(*it);
        if (!page) {
            continue;
        }
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            continue;
        }
        auto type = pattern->GetPageType();
        if (type == RouterPageType::PRIMARY_PAGE) {
            curPrimaryPage = page;
        }
        pattern->SetPrimaryPage(curPrimaryPage);
    }

    return curPrimaryPage;
}

void ParallelStageManager::FirePageHideOnMovePageToFront(
    RouterPageType newTopPageType, const RefPtr<FrameNode>& preLastPage, PageTransitionType hideTransitionType)
{
    if (newTopPageType == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryA | SecondaryA ]
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  preLastPage -> onPageHide
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
     * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     *  preLastPage -> onPageHide
     *  prePrimaryPage? -> onPageHide
     */
    FireParallelPageHide(preLastPage, hideTransitionType);
    auto pattern = preLastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(pattern);
    auto prePrimaryPage = pattern->GetPrimaryPage();
    if (prePrimaryPage) {
        FireParallelPageHide(prePrimaryPage, hideTransitionType);
    }
}

RefPtr<FrameNode> ParallelStageManager::GetPrePrimaryPage(const RefPtr<FrameNode>& preTopPage)
{
    RefPtr<FrameNode> prePrimaryPage = nullptr;
    const auto& children = stageNode_->GetChildren();
    auto it = children.rbegin();
    for (;it != children.rend(); ++it) {
        if (*it == preTopPage) {
            return nullptr;
        }
    }
    if (*it != preTopPage) {
        return nullptr;
    }
    // skip preTopPage
    ++it;
    // find pre PrimaryPage
    for (;it != children.rend(); ++it) {
        auto page = AceType::DynamicCast<FrameNode>(*it);
        if (!page) {
            break;
        }
        auto pattern = page->GetPattern<ParallelPagePattern>();
        if (!pattern) {
            break;
        }
        if (pattern->GetPageType() == RouterPageType::PRIMARY_PAGE) {
            prePrimaryPage = page;
            break;
        }
    }
    return prePrimaryPage;
}

void ParallelStageManager::FirePageShowOnMovePageToFront(
    const RefPtr<FrameNode>& preTopPage, const RefPtr<ParallelPagePattern>& preTopPattern,
    const RefPtr<FrameNode>& newTopPage, const RefPtr<ParallelPagePattern>& newTopPattern,
    PageTransitionType showTransitionType)
{
    if (newTopPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
        /**
         * [ PrimaryA | SecondaryA ]  ->  [ PrimaryA | SecondaryB ]
         * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryA | SecondaryB ]
         * [ SecondaryA ]  ->  [ SecondaryB ]
         *  SecondaryB -> onPageShow
         */
        FireParallelPageShow(newTopPage, showTransitionType);

        if (preTopPattern->GetPageType() != RouterPageType::PRIMARY_PAGE || !isNewPageReplacing_) {
            return;
        }

        /**
         * replace(SecondaryA, single)
         * stack bottom -> stack top
         * [ PrimaryA ] [ SecondaryA ] [PrimaryB ] -> [ PrimaryA ] [ SecondaryA ]
         *  step1: MovePageToFront
         *  step2: move page node position
         *  step3: PopPage
         *   we need to show SecondaryA's PrimaryPage(that is PrimaryA) in step1.
         */
        RefPtr<FrameNode> prePrimaryPage = GetPrePrimaryPage(preTopPage);
        // show PrimaryA
        if (prePrimaryPage) {
            FireParallelPageShow(prePrimaryPage, showTransitionType);
        }
        return;
    }

    // RouterPageType::PRIMARY_PAGE
    /**
     * [ PrimaryA | PlaceHolderA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ PrimaryA | SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     * [ SecondaryA ]  ->  [ PrimaryB | PlaceHolderB ]
     *  PrimaryB -> onPageShow
     *  PlaceHolderB -> ?aboutToAppear
     *  PlaceHolderB -> onPageShow
     */
    FireParallelPageShow(newTopPage, showTransitionType);

    auto newPhPage = newTopPattern->GetOrCreatePlaceHolderPage();
    MountAndShowPlaceHolderPageIfNeeded(newPhPage, showTransitionType);
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
    RefPtr<FrameNode> prePrimaryPage = nullptr;
    auto lastPattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(lastPattern, false);
    if (lastPattern->GetPageType() == RouterPageType::PLACEHOLDER_PAGE) {
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
        prePrimaryPage = prePage;
        preTopPage = prePage;
        preTopPattern = prePattern;
        if (node == prePage) {
            return true;
        }
    } else {
        preTopPage = lastPage;
        preTopPattern = lastPattern;
        if (lastPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
            prePrimaryPage = lastPattern->GetPrimaryPage();
        }
    }

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }

    RefPtr<FrameNode> phPage = nullptr;
    if (!RemovePlaceHolderPageIfExist(phPage, !isNewPageReplacing_)) {
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

    auto lastPrimaryPage = RefreshAndGetLastPrimaryPage();
    stagePattern->SetPrimaryPage(lastPrimaryPage);

    if (isNewPageReplacing_ && lastPattern->GetPageType() == RouterPageType::SECONDARY_PAGE) {
        // save pre primary page for following PopPage when replace page in new life cycle.
        // @sa FirePageHideOnPopPage()
        lastPattern->SetPrePrimaryPage(prePrimaryPage);
    }

    RefPtr<FrameNode> outPageNode = nullptr;
    if (phPage) {
        outPageNode = prePrimaryPage;
    } else {
        outPageNode = lastPage;
    }
    AddPageTransitionTrace(outPageNode, node);
    FireAutoSave(outPageNode, node);

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    return true;
}

bool ParallelStageManager::RemovePlaceHolderPageIfExist(RefPtr<FrameNode>& phPage, bool needHidePlaceHolder)
{
    phPage = nullptr;
    if (IsEmptyInSplitMode()) {
        return true;
    }
    auto lastPage = GetLastPage();
    CHECK_NULL_RETURN(lastPage, false);
    auto pattern = lastPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(pattern, false);

    if (pattern->GetPageType() == RouterPageType::PLACEHOLDER_PAGE) {
        if (needHidePlaceHolder) {
            FireParallelPageHide(lastPage, PageTransitionType::NONE);
        }

        stageNode_->RemoveChild(lastPage);
        phPage = lastPage;
    }
    return true;
}

bool ParallelStageManager::OnPrimaryPageDetected(const RefPtr<FrameNode>& primaryPage,
    LoadPlaceHolderPageCallback&& callback, const std::list<WeakPtr<FrameNode>>& pageStack)
{
    StageOptScope scope(this);
    CHECK_NULL_RETURN(stageNode_, false);
    auto stagePattern = stageNode_->GetPattern<ParallelStagePattern>();
    CHECK_NULL_RETURN(stagePattern, false);

    auto preLastPrimaryPage = GetLastPrimaryPage();

    CHECK_NULL_RETURN(primaryPage, false);
    auto primaryPattern = primaryPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_RETURN(primaryPattern, false);
    primaryPattern->SetLoadPlaceHolderPageCallback(std::move(callback));
    primaryPattern->SetPageType(RouterPageType::PRIMARY_PAGE);

    auto curLastPrimaryPage = RefreshAndGetLastPrimaryPage();
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
     *  stack bottom -> stack top
     *  before: [ PrimaryA ] [ SecondaryA ] [PrimaryB ] [SecondaryB ]
     *  after: [ PrimaryA ] [ SecondaryA ] [PrimaryB ] [PrimaryC ]
     *  step1: LoadPage (pageC has not yet been recognized as the PrimaryPage before it was created)
     *  step2: OnPrimaryPageDetected (we won't create placeHolderPage at this step)
     *  step3: move page node position
     *  step4: PopPage (we will create placeHolderPage at this step)
     *   we need to create, mount, show PrimaryC's placeHolder
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

    auto phPage = primaryPattern->GetOrCreatePlaceHolderPage();
    MountAndShowPlaceHolderPageIfNeeded(phPage, PageTransitionType::NONE);
    return true;
}

void ParallelStageManager::MountAndShowPlaceHolderPageIfNeeded(
    const RefPtr<FrameNode>& phPage, PageTransitionType showTransitionType)
{
    CHECK_NULL_VOID(stageNode_);
    CHECK_NULL_VOID(phPage);
    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    auto phGeometryNode = phPage->GetGeometryNode();
    CHECK_NULL_VOID(phGeometryNode);
    phGeometryNode->SetFrameSize(rect.GetSize());
    phGeometryNode->SetMarginFrameOffset(rect.GetOffset());
    phPage->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    phPage->MountToParent(stageNode_);
    auto phPattern = phPage->GetPattern<ParallelPagePattern>();
    CHECK_NULL_VOID(phPattern);

    if (!phPattern->IsPlaceHolderPageBuildCompleted()) {
        // then build the total child. Build will trigger page create and onAboutToAppear
        phPage->Build(nullptr);
        phPage->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        phPattern->SetIsPlaceHolderPageBuildCompleted(true);
    }

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    FireParallelPageShow(phPage, showTransitionType, false);
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
        auto pattern = frameNode->GetPattern<ParallelPagePattern>();
        CHECK_NULL_RETURN(pattern, nullptr);
        auto primaryPage = pattern->GetPrimaryPage();
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
    auto needSyncPage = stagePattern->GetPrimaryPage().Upgrade();
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
        auto page = stagePattern->GetPrimaryPage().Upgrade();
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
}