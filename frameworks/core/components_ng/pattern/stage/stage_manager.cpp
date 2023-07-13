/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stage/stage_manager.h"

#include <unordered_map>

#include "base/geometry/ng/size_t.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/memory/referenced.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/animation/page_transition_common.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/shared_overlay/shared_overlay_manager.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/stage/stage_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {
void FirePageTransition(const RefPtr<FrameNode>& page, PageTransitionType transitionType)
{
    CHECK_NULL_VOID(page);
    auto pagePattern = page->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    page->GetEventHub<EventHub>()->SetEnabled(false);
    pagePattern->SetPageInTransition(true);
    if (transitionType == PageTransitionType::EXIT_PUSH || transitionType == PageTransitionType::EXIT_POP) {
        pagePattern->TriggerPageTransition(
            transitionType, [weak = WeakPtr<FrameNode>(page), transitionType, instanceId = Container::CurrentId()]() {
                ContainerScope scope(instanceId);
                LOGI("pageTransition exit finish");
                auto page = weak.Upgrade();
                CHECK_NULL_VOID(page);
                auto context = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(context);
                auto pageFocusHub = page->GetFocusHub();
                CHECK_NULL_VOID(pageFocusHub);
                pageFocusHub->SetParentFocusable(false);
                pageFocusHub->LostFocus();
                if (transitionType == PageTransitionType::EXIT_POP && page->GetParent()) {
                    auto stageNode = page->GetParent();
                    stageNode->RemoveChild(page);
                    stageNode->RebuildRenderContextTree();
                    context->RequestFrame();
                    return;
                }
                page->GetEventHub<EventHub>()->SetEnabled(true);
                auto pattern = page->GetPattern<PagePattern>();
                CHECK_NULL_VOID(pattern);
                pattern->SetPageInTransition(false);
                pattern->ProcessHideState();
                context->MarkNeedFlushMouseEvent();
            });
        return;
    }
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "NA");
    pagePattern->TriggerPageTransition(
        transitionType, [weak = WeakPtr<FrameNode>(page), instanceId = Container::CurrentId()]() {
            ContainerScope scope(instanceId);
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::ABILITY_OR_PAGE_SWITCH, false);
            LOGI("pageTransition in finish");
            auto page = weak.Upgrade();
            CHECK_NULL_VOID(page);
            page->GetEventHub<EventHub>()->SetEnabled(true);
            auto pattern = page->GetPattern<PagePattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetPageInTransition(false);

            auto pageFocusHub = page->GetFocusHub();
            CHECK_NULL_VOID(pageFocusHub);
            pageFocusHub->SetParentFocusable(true);
            pageFocusHub->RequestFocus();
            auto context = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(context);
            context->MarkNeedFlushMouseEvent();
        });
}
} // namespace

void StageManager::StartTransition(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage, RouteType type)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sharedManager = pipeline->GetSharedOverlayManager();
    CHECK_NULL_VOID(sharedManager);
    sharedManager->StartSharedTransition(srcPage, destPage);
    srcPageNode_ = srcPage;
    destPageNode_ = destPage;
    if (type == RouteType::PUSH) {
        FirePageTransition(srcPage, PageTransitionType::EXIT_PUSH);
        FirePageTransition(destPage, PageTransitionType::ENTER_PUSH);
    } else if (type == RouteType::POP) {
        FirePageTransition(srcPage, PageTransitionType::EXIT_POP);
        FirePageTransition(destPage, PageTransitionType::ENTER_POP);
    }
}

StageManager::StageManager(const RefPtr<FrameNode>& stage) : stageNode_(stage)
{
    CHECK_NULL_VOID(stageNode_);
    stagePattern_ = DynamicCast<StagePattern>(stageNode_->GetPattern());
}

void StageManager::StopPageTransition()
{
    auto srcNode = srcPageNode_.Upgrade();
    if (srcNode) {
        auto pattern = srcNode->GetPattern<PagePattern>();
        pattern->StopPageTransition();
        srcPageNode_ = nullptr;
    }
    auto destNode = destPageNode_.Upgrade();
    if (destNode) {
        auto pattern = destNode->GetPattern<PagePattern>();
        pattern->StopPageTransition();
        destPageNode_ = nullptr;
    }
}

bool StageManager::PushPage(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    CHECK_NULL_RETURN(stageNode_, false);
    CHECK_NULL_RETURN(node, false);
    int64_t startTime = GetSysTimestamp();
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_RETURN(pipeline, false);
    StopPageTransition();

    const auto& children = stageNode_->GetChildren();
    RefPtr<FrameNode> outPageNode;
    needTransition &= !children.empty();
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    if (!children.empty() && needHideLast) {
        FirePageHide(children.back(), needTransition ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE);
        outPageNode = AceType::DynamicCast<FrameNode>(children.back());
    }
    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    node->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    node->MountToParent(stageNode_);
    // then build the total child.
    node->Build();
    stageNode_->RebuildRenderContextTree();
    FirePageShow(node, needTransition ? PageTransitionType::ENTER_PUSH : PageTransitionType::NONE);

    auto pagePattern = node->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    stagePattern_->currentPageIndex_ = pagePattern->GetPageInfo()->GetPageId();
    if (AceChecker::IsPerformanceCheckEnabled()) {
        // After completing layout tasks at all nodes on the page, perform performance testing and management
        pipeline->AddAfterLayoutTask([weakStage = WeakClaim(this), weakNode = WeakPtr<FrameNode>(node), startTime]() {
            auto stage = weakStage.Upgrade();
            CHECK_NULL_VOID(stage);
            auto pageNode = weakNode.Upgrade();
            int64_t endTime = GetSysTimestamp();
            stage->PerformanceCheck(pageNode, endTime - startTime);
        });
    }
    if (needTransition) {
        pipeline->AddAfterLayoutTask([weakStage = WeakClaim(this), weakIn = WeakPtr<FrameNode>(node),
                                         weakOut = WeakPtr<FrameNode>(outPageNode)]() {
            auto stage = weakStage.Upgrade();
            CHECK_NULL_VOID(stage);
            auto inPageNode = weakIn.Upgrade();
            auto outPageNode = weakOut.Upgrade();
            stage->StartTransition(outPageNode, inPageNode, RouteType::PUSH);
        });
    }

    // flush layout task.
    if (!stageNode_->GetGeometryNode()->GetMarginFrameSize().IsPositive()) {
        // in first load case, wait for window size.
        LOGI("waiting for window size");
        return true;
    }
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void StageManager::PerformanceCheck(const RefPtr<FrameNode>& pageNode, int64_t vsyncTimeout)
{
    CHECK_NULL_VOID_NOLOG(pageNode);
    PerformanceCheckNodeMap nodeMap;
    pageNode->GetPerformanceCheckData(nodeMap);
    AceScopedPerformanceCheck::RecordPerformanceCheckData(nodeMap, vsyncTimeout);
}

bool StageManager::PopPage(bool needShowNext, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition();
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to pop page due to children is null");
        return false;
    }
    auto pageNode = children.back();
    const size_t transitionPageSize = 2;
    needTransition &= (children.size() >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    FirePageHide(pageNode, needTransition ? PageTransitionType::EXIT_POP : PageTransitionType::NONE);

    RefPtr<FrameNode> inPageNode;
    if (needShowNext && children.size() >= transitionPageSize) {
        auto newPageNode = *(++children.rbegin());
        FirePageShow(newPageNode, needTransition ? PageTransitionType::ENTER_POP : PageTransitionType::NONE);
        inPageNode = AceType::DynamicCast<FrameNode>(newPageNode);
    }

    auto outPageNode = AceType::DynamicCast<FrameNode>(pageNode);
    if (needTransition) {
        StartTransition(outPageNode, inPageNode, RouteType::POP);
        inPageNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        return true;
    }
    stageNode_->RemoveChild(pageNode);
    pageNode->SetChildrenInDestroying();
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::PopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition();
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to pop page due to children is null");
        return false;
    }
    int32_t popSize = static_cast<int32_t>(children.size()) - index - 1;
    if (popSize < 0) {
        LOGE("fail to pop page due to index is out of range");
        return false;
    }
    if (popSize == 0) {
        LOGD("already here");
        return true;
    }

    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    bool firstPageTransition = true;
    auto outPageNode = AceType::DynamicCast<FrameNode>(children.back());
    auto iter = children.rbegin();
    for (int32_t current = 0; current < popSize; ++current) {
        auto pageNode = *iter;
        FirePageHide(
            pageNode, firstPageTransition && needTransition ? PageTransitionType::EXIT_POP : PageTransitionType::NONE);
        firstPageTransition = false;
        ++iter;
    }

    RefPtr<FrameNode> inPageNode;
    if (needShowNext) {
        const auto& newPageNode = *iter;
        FirePageShow(newPageNode, needTransition ? PageTransitionType::ENTER_POP : PageTransitionType::NONE);
        inPageNode = AceType::DynamicCast<FrameNode>(newPageNode);
    }

    if (needTransition) {
        // from the penultimate node, (popSize - 1) nodes are deleted.
        // the last node will be deleted after pageTransition
        LOGI("PopPageToIndex, before pageTransition, to index:%{public}d, children size:%{public}zu, "
             "stage children size:%{public}zu",
            index, children.size(), stageNode_->GetChildren().size());
        for (int32_t current = 1; current < popSize; ++current) {
            auto pageNode = *(++children.rbegin());
            stageNode_->RemoveChild(pageNode);
        }
        stageNode_->RebuildRenderContextTree();
        StartTransition(outPageNode, inPageNode, RouteType::POP);
        return true;
    }
    for (int32_t current = 0; current < popSize; ++current) {
        auto pageNode = children.back();
        stageNode_->RemoveChild(pageNode);
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::CleanPageStack()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    const auto& children = stageNode_->GetChildren();
    if (children.size() <= 1) {
        LOGE("fail to clean page stack due to children size is illegal");
        return false;
    }
    auto popSize = static_cast<int32_t>(children.size() - 1);
    for (int32_t count = 1; count <= popSize; ++count) {
        auto pageNode = children.front();
        stageNode_->RemoveChild(pageNode);
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition();
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("child is empty");
        return false;
    }
    const auto& lastPage = children.back();
    if (lastPage == node) {
        LOGD("page already on the top");
        return true;
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    if (needHideLast) {
        FirePageHide(lastPage, needTransition ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE);
    }
    node->MovePosition(static_cast<int32_t>(stageNode_->GetChildren().size() - 1));
    node->GetRenderContext()->ResetPageTransitionEffect();
    FirePageShow(node, needTransition ? PageTransitionType::ENTER_PUSH : PageTransitionType::NONE);

    stageNode_->RebuildRenderContextTree();
    if (needTransition) {
        auto outPageNode = AceType::DynamicCast<FrameNode>(lastPage);
        StartTransition(outPageNode, node, RouteType::PUSH);
    }
    pipeline->RequestFrame();
    return true;
}

void StageManager::FirePageHide(const RefPtr<UINode>& node, PageTransitionType transitionType)
{
    auto pageNode = DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnHide();
    if (transitionType == PageTransitionType::NONE) {
        // If there is a page transition, this function should execute after page transition,
        // otherwise the page will not be visible
        pagePattern->ProcessHideState();
    }

    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(false);
    pageFocusHub->LostFocus();

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(context);
    context->MarkNeedFlushMouseEvent();
}

void StageManager::FirePageShow(const RefPtr<UINode>& node, PageTransitionType transitionType)
{
    auto pageNode = DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(pageNode);
    auto layoutProperty = pageNode->GetLayoutProperty();
    auto pageFocusHub = pageNode->GetFocusHub();
    CHECK_NULL_VOID(pageFocusHub);
    pageFocusHub->SetParentFocusable(true);
    pageFocusHub->RequestFocus();

    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnShow();
    // With or without a page transition, we need to make the coming page visible first
    pagePattern->ProcessShowState();

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(context);
    context->MarkNeedFlushMouseEvent();
#ifdef UICAST_COMPONENT_SUPPORTED
    do {
        auto container = Container::Current();
        CHECK_NULL_BREAK(container);
        auto distributedUI = container->GetDistributedUI();
        CHECK_NULL_BREAK(distributedUI);
        distributedUI->OnPageChanged(node->GetPageId());
    } while (false);
#endif
}

RefPtr<FrameNode> StageManager::GetLastPage()
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        LOGE("fail to return page due to children is null");
        return nullptr;
    }
    return DynamicCast<FrameNode>(children.back());
}

RefPtr<FrameNode> StageManager::GetPageById(int32_t pageId)
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    for (const auto& child : children) {
        if (child->GetPageId() == pageId) {
            return DynamicCast<FrameNode>(child);
        }
    }
    LOGD("UITree page not found. %{public}d", pageId);
    return nullptr;
}

void StageManager::ReloadStage()
{
    CHECK_NULL_VOID(stageNode_);
    const auto& children = stageNode_->GetChildren();
    for (const auto& child : children) {
        auto frameNode = DynamicCast<FrameNode>(child);
        if (!frameNode) {
            continue;
        }
        auto pagePattern = frameNode->GetPattern<PagePattern>();
        if (!pagePattern) {
            continue;
        }
        pagePattern->ReloadPage();
    }
}

} // namespace OHOS::Ace::NG
