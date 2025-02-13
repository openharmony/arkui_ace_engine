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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "base/log/ace_checker.h"
#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/common/ime/input_method_manager.h"

#if !defined(ACE_UNITTEST)
#include "core/components_ng/base/transparent_node_detector.h"
#endif

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
std::string KEY_PAGE_TRANSITION_PROPERTY = "pageTransitionProperty";
namespace {
constexpr char EMPTY_PAGE_INFO[] = "NA";

void FirePageTransition(const RefPtr<FrameNode>& page, PageTransitionType transitionType)
{
    CHECK_NULL_VOID(page);
    auto pagePattern = page->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    auto eventHub = page->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        if (transitionType == PageTransitionType::EXIT_POP) {
            eventHub->SetEnabled(false);
        }
    } else {
        eventHub->SetEnabled(false);
    }
    pagePattern->SetPageInTransition(true);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto stageManager = context->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    stageManager->SetStageInTrasition(true);
    pagePattern->SetAnimationId(stageManager->GetAnimationId());
    if (transitionType == PageTransitionType::EXIT_PUSH || transitionType == PageTransitionType::EXIT_POP) {
        pagePattern->TriggerPageTransition([weakPattern = WeakPtr<PagePattern>(pagePattern),
            animationId = stageManager->GetAnimationId(), transitionType]() {
                auto pagePattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pagePattern);
                pagePattern->FinishOutPage(animationId, transitionType);
            }, transitionType);
        pagePattern->RemoveJsChildImmediately(page, transitionType);
        return;
    }
    ACE_SCOPED_TRACE_COMMERCIAL("Router Page Transition Start");
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::ABILITY_OR_PAGE_SWITCH, PerfActionType::LAST_UP, "");
    pagePattern->TriggerPageTransition(
        [weak = WeakPtr<PagePattern>(pagePattern), animationId = stageManager->GetAnimationId(), transitionType]() {
            auto pagePattern = weak.Upgrade();
            CHECK_NULL_VOID(pagePattern);
            auto page = pagePattern->GetHost();
            CHECK_NULL_VOID(page);
            TAG_LOGI(AceLogTag::ACE_ANIMATION, "pageTransition in finish, nodeId:%{public}d", page->GetId());
            pagePattern->FinishInPage(animationId, transitionType);
        }, transitionType);
}
} // namespace

void StageManager::StartTransition(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage, RouteType type)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sharedManager = pipeline->GetSharedOverlayManager();
    CHECK_NULL_VOID(sharedManager);
    sharedManager->StartSharedTransition(srcPage, destPage);
    animationSrcPage_ = srcPage;
    destPageNode_ = destPage;
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "start pageTransition, from node %{public}d to %{public}d",
        srcPage ? srcPage->GetId() : -1, destPage ? destPage->GetId() : -1);
    // don't need to add animation id when routeType is none
    if (type == RouteType::NONE) {
        return;
    }
    animationId_++;
    if (type == RouteType::PUSH) {
        pushAnimations_.clear();
        FirePageTransition(srcPage, PageTransitionType::EXIT_PUSH);
        FirePageTransition(destPage, PageTransitionType::ENTER_PUSH);
    } else if (type == RouteType::POP) {
        popAnimations_.clear();
        FirePageTransition(srcPage, PageTransitionType::EXIT_POP);
        FirePageTransition(destPage, PageTransitionType::ENTER_POP);
    }
}

StageManager::StageManager(const RefPtr<FrameNode>& stage) : stageNode_(stage)
{
    CHECK_NULL_VOID(stageNode_);
    stagePattern_ = DynamicCast<StagePattern>(stageNode_->GetPattern());
}

void StageManager::PageChangeCloseKeyboard()
{
    // close keyboard
#if defined (ENABLE_STANDARD_INPUT)
    if (Container::CurrentId() == CONTAINER_ID_DIVIDE_SIZE) {
        TAG_LOGI(AceLogTag::ACE_KEYBOARD, "StageManager FrameNode notNeedSoftKeyboard.");
        auto container = Container::Current();
        if (!container) {
            return;
        }
        if (!container->IsScenceBoardWindow()) {
            TAG_LOGI(AceLogTag::ACE_KEYBOARD, "Container not ScenceBoardWindow.");
            InputMethodManager::GetInstance()->CloseKeyboard();
        }
    }
#endif
}

bool StageManager::PushPage(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    CHECK_NULL_RETURN(stageNode_, false);
    CHECK_NULL_RETURN(node, false);
    int64_t startTime = GetSysTimestamp();
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_RETURN(pipeline, false);
    StopPageTransition(needTransition);
    const auto& children = stageNode_->GetChildren();
    RefPtr<FrameNode> outPageNode;
    needTransition &= !children.empty();
    if (children.empty()) {
        auto pagePattern = node->GetPattern<NG::PagePattern>();
        CHECK_NULL_RETURN(pagePattern, false);
        auto pageInfo = pagePattern->GetPageInfo();
        CHECK_NULL_RETURN(pageInfo, false);
        auto pagePath = pageInfo->GetFullPath();
        ACE_SCOPED_TRACE_COMMERCIAL("Router Main Page: %s", pagePath.c_str());
        UiSessionManager::GetInstance()->OnRouterChange(pagePath, "routerPushPage");
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    RefPtr<UINode> hidePageNode;
    auto isNewLifecycle = AceApplicationInfo::GetInstance()
        .GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE);
    if (!children.empty() && needHideLast) {
        hidePageNode = srcPageNode_.Upgrade();
        outPageNode = AceType::DynamicCast<FrameNode>(hidePageNode);
        FireAutoSave(outPageNode, node);
        if (!isNewLifecycle) {
            FirePageHide(hidePageNode, needTransition ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE);
        }
        
    }
    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    node->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    node->MountToParent(stageNode_);
    // then build the total child. Build will trigger page create and onAboutToAppear
    node->Build(nullptr);
    // fire new lifecycle
    if (hidePageNode && needHideLast && isNewLifecycle) {
        FirePageHide(hidePageNode, needTransition ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE);
    }
    stageNode_->RebuildRenderContextTree();
    FirePageShow(node, needTransition ? PageTransitionType::ENTER_PUSH : PageTransitionType::NONE);

    auto pagePattern = node->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    stagePattern_->SetCurrentPageIndex(pagePattern->GetPageInfo()->GetPageId());
    if (AceChecker::IsPerformanceCheckEnabled()) {
        // After completing layout tasks at all nodes on the page, perform performance testing and management
        pipeline->AddAfterLayoutTask([weakStage = WeakClaim(this), weakNode = WeakPtr<FrameNode>(node), startTime]() {
            auto stage = weakStage.Upgrade();
            CHECK_NULL_VOID(stage);
            auto pageNode = weakNode.Upgrade();
            int64_t endTime = GetSysTimestamp();
            auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
            CHECK_NULL_VOID(pagePattern);
            auto pageInfo = pagePattern->GetPageInfo();
            CHECK_NULL_VOID(pageInfo);
            auto pagePath = pageInfo->GetFullPath();
            stage->PerformanceCheck(pageNode, endTime - startTime, pagePath);
        });
    }
#if !defined(ACE_UNITTEST)
    auto pageInfo = pagePattern->GetPageInfo();
    std::string pageUrl = "";
    if (pageInfo) {
        pageUrl = pageInfo->GetFullPath();
    }
    TransparentNodeDetector::GetInstance().PostCheckNodeTransparentTask(node, pageUrl);
#endif

    // close keyboard
    PageChangeCloseKeyboard();
    AddPageTransitionTrace(outPageNode, node);
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
        return true;
    }
    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

    return true;
}

bool StageManager::InsertPage(const RefPtr<FrameNode>& node, bool bellowTopOrBottom)
{
    CHECK_NULL_RETURN(stageNode_, false);
    CHECK_NULL_RETURN(node, false);

    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return false;
    }

    RefPtr<FrameNode> targetNode = nullptr;
    if (bellowTopOrBottom) {
        targetNode = AceType::DynamicCast<FrameNode>(children.back());
    } else {
        targetNode = AceType::DynamicCast<FrameNode>(children.front());
    }
    auto rect = stageNode_->GetGeometryNode()->GetFrameRect();
    rect.SetOffset({});
    node->GetRenderContext()->SyncGeometryProperties(rect);
    // mount to parent and mark build render tree.
    stageNode_->AddChildBefore(node, targetNode);
    // then build the total child. Build will trigger page create and onAboutToAppear
    node->Build(nullptr);

    stageNode_->RebuildRenderContextTree();

    stageNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    return true;
}

void StageManager::PerformanceCheck(const RefPtr<FrameNode>& pageNode, int64_t vsyncTimeout, std::string path)
{
    CHECK_NULL_VOID(pageNode);
    PerformanceCheckNodeMap nodeMap;
    pageNode->GetPerformanceCheckData(nodeMap);
    AceScopedPerformanceCheck::RecordPerformanceCheckData(nodeMap, vsyncTimeout, path);
}

bool StageManager::PopPage(const RefPtr<FrameNode>& inPage, bool needShowNext, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition(needTransition);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        TAG_LOGI(AceLogTag::ACE_ROUTER, "router pop page start, children is empty");
        return false;
    }
    auto pageNode = srcPageNode_.Upgrade();
    const size_t transitionPageSize = 2;
    needTransition &= (children.size() >= transitionPageSize);
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    auto outPageNode = AceType::DynamicCast<FrameNode>(pageNode);
    auto inPageNode = needShowNext ? inPage : nullptr;
    pipeline->GetMemoryManager()->RebuildImageByPage(inPageNode);
    FireAutoSave(outPageNode, inPageNode);
    FirePageHide(pageNode, needTransition ? PageTransitionType::EXIT_POP : PageTransitionType::NONE);
    FirePageShow(inPageNode, needTransition ? PageTransitionType::ENTER_POP : PageTransitionType::NONE);

    // close keyboard
    PageChangeCloseKeyboard();

    AddPageTransitionTrace(outPageNode, inPageNode);
    if (needTransition) {
        StartTransition(outPageNode, inPageNode, RouteType::POP);
        if (inPageNode) {
            inPageNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
        return true;
    }
    if (pageNode) {
        stageNode_->RemoveChild(pageNode);
        pageNode->SetChildrenInDestroying();
    }
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::PopPageToIndex(int32_t index, bool needShowNext, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition(needTransition);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return false;
    }
    int32_t popSize = static_cast<int32_t>(children.size()) - index - 1;
    if (popSize < 0) {
        return false;
    }
    if (popSize == 0) {
        return true;
    }
    auto outPageNode = AceType::DynamicCast<FrameNode>(srcPageNode_.Upgrade());
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    bool firstPageTransition = true;
    auto iter = children.rbegin();
    for (int32_t current = 0; current < popSize; ++current) {
        auto pageNode = *iter;
        if (!needTransition|| !CheckPageInTransition(pageNode)) {
            FirePageHide(
                pageNode,
                firstPageTransition && needTransition ?PageTransitionType::EXIT_POP : PageTransitionType::NONE);
            firstPageTransition = false;
        }
        ++iter;
    }

    RefPtr<FrameNode> inPageNode;
    if (needShowNext) {
        const auto& newPageNode = *iter;
        FirePageShow(newPageNode, needTransition ? PageTransitionType::ENTER_POP : PageTransitionType::NONE);
        inPageNode = AceType::DynamicCast<FrameNode>(newPageNode);
        pipeline->GetMemoryManager()->RebuildImageByPage(inPageNode);
    }
    PageChangeCloseKeyboard();
    AddPageTransitionTrace(outPageNode, inPageNode);

    FireAutoSave(outPageNode, inPageNode);
    if (needTransition) {
        // from the penultimate node, (popSize - 1) nodes are deleted.
        // the last node will be deleted after pageTransition
        for (int32_t current = 1; current < popSize; ++current) {
            auto pageNode = *(++children.rbegin());
            if (CheckPageInTransition(pageNode)) {
                UpdatePageNeedRemove(pageNode);
            } else {
                stageNode_->RemoveChild(pageNode);
            }
        }
        stageNode_->RebuildRenderContextTree();
        StartTransition(outPageNode, inPageNode, RouteType::POP);
        if (inPageNode) {
            inPageNode->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
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
        return false;
    }
    auto popSize = static_cast<int32_t>(children.size()) - 1;
    for (int32_t count = 1; count <= popSize; ++count) {
        auto pageNode = children.front();
        // mark pageNode child as destroying
        pageNode->SetChildrenInDestroying();
        stageNode_->RemoveChild(pageNode);
    }
    pipeline->GetMemoryManager()->RebuildImageByPage(AceType::DynamicCast<FrameNode>(children.back()));
    stageNode_->RebuildRenderContextTree();
    pipeline->RequestFrame();
    return true;
}

bool StageManager::MovePageToFront(const RefPtr<FrameNode>& node, bool needHideLast, bool needTransition)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    CHECK_NULL_RETURN(stageNode_, false);
    StopPageTransition(needTransition);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return false;
    }
    const auto& lastPage = children.back();
    if (lastPage == node) {
        return true;
    }
    if (needTransition) {
        pipeline->FlushPipelineImmediately();
    }
    if (needHideLast) {
        FirePageHide(lastPage, needTransition ? PageTransitionType::EXIT_PUSH : PageTransitionType::NONE);
    }
    node->MovePosition(static_cast<int32_t>(stageNode_->GetChildren().size()) - 1);
    auto pattern = node->GetPattern<PagePattern>();
    if  (pattern) {
        pattern->ResetPageTransitionEffect();
    }
    FirePageShow(node, needTransition ? PageTransitionType::ENTER_PUSH : PageTransitionType::NONE);

    stageNode_->RebuildRenderContextTree();
    auto outPageNode = AceType::DynamicCast<FrameNode>(lastPage);
    AddPageTransitionTrace(outPageNode, node);
    FireAutoSave(outPageNode, node);
    if (needTransition) {
        StartTransition(outPageNode, node, RouteType::PUSH);
        if (node) {
            node->OnAccessibilityEvent(AccessibilityEventType::CHANGE);
        }
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
    pagePattern->FocusViewHide();
    pagePattern->OnHide();
    if (transitionType == PageTransitionType::NONE) {
        // If there is a page transition, this function should execute after page transition,
        // otherwise the page will not be visible
        pagePattern->ProcessHideState();
    }

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->MarkNeedFlushMouseEvent();
}

void StageManager::FirePageShow(const RefPtr<UINode>& node, PageTransitionType transitionType, bool needFocus)
{
    auto pageNode = DynamicCast<FrameNode>(node);
    CHECK_NULL_VOID(pageNode);
    auto layoutProperty = pageNode->GetLayoutProperty();

    auto pagePattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    if (needFocus) {
        pagePattern->FocusViewShow();
    }
    pagePattern->OnShow();
    // With or without a page transition, we need to make the coming page visible first
    pagePattern->ProcessShowState();

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
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

void StageManager::FireAutoSave(const RefPtr<FrameNode>& outPageNode, const RefPtr<FrameNode>& inPageNode)
{
    CHECK_NULL_VOID(outPageNode);
    auto outPagePattern = outPageNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(outPagePattern);
    auto onUIExtNodeDestroy = [weak = WeakPtr<FrameNode>(inPageNode)]() {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIExtNodeDestroy called.");
        auto page = weak.Upgrade();
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsModalCovered(false);
    };
    auto onUIExtNodeBindingCompleted = [weak = WeakPtr<FrameNode>(inPageNode)]() {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UIExtNodeBindingCompleted called.");
        auto page = weak.Upgrade();
        CHECK_NULL_VOID(page);
        auto pattern = page->GetPattern<PagePattern>();
        CHECK_NULL_VOID(pattern);
        pattern->SetIsModalCovered(true);
    };
    outPagePattern->ProcessAutoSave(onUIExtNodeDestroy, onUIExtNodeBindingCompleted);
}

RefPtr<FrameNode> StageManager::GetLastPage() const
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
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

RefPtr<FrameNode> StageManager::GetLastPageWithTransition() const
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    auto lastChildFrame = DynamicCast<FrameNode>(children.back());
    auto pagePattern = lastChildFrame->GetPattern<PagePattern>();
    if (pagePattern && pagePattern->GetPageInTransition()) {
        return DynamicCast<FrameNode>(destPageNode_.Upgrade());
    }
    return lastChildFrame;
}

RefPtr<FrameNode> StageManager::GetPrevPageWithTransition() const
{
    CHECK_NULL_RETURN(stageNode_, nullptr);
    const auto& children = stageNode_->GetChildren();
    if (children.empty()) {
        return nullptr;
    }
    if (stageInTrasition_) {
        return DynamicCast<FrameNode>(animationSrcPage_.Upgrade());
    }
    return DynamicCast<FrameNode>(children.front());
}

void StageManager::AddPageTransitionTrace(const RefPtr<FrameNode>& srcPage, const RefPtr<FrameNode>& destPage)
{
    if (!destPage) {
        CHECK_NULL_VOID(srcPage);
        // when replace with pop first, destPage node info is empty, record srcPage info and use it when push happen.
        auto srcPattern = srcPage->GetPattern<NG::PagePattern>();
        CHECK_NULL_VOID(srcPattern);
        auto srcPageInfo = srcPattern->GetPageInfo();
        CHECK_NULL_VOID(srcPageInfo);
        replaceSrcPageInfo_ = srcPageInfo->GetFullPath();
        TAG_LOGD(AceLogTag::ACE_ROUTER, "replace router page with pop first, record srcPage info %{public}s",
            replaceSrcPageInfo_.c_str());
        return;
    }

    std::string srcFullPath = GetSrcPageInfo(srcPage);
    if (srcFullPath.empty()) {
        srcFullPath = replaceSrcPageInfo_.empty() ? EMPTY_PAGE_INFO : replaceSrcPageInfo_;
        replaceSrcPageInfo_.clear();
    }

    auto destPattern = destPage->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(destPattern);
    auto destPageInfo = destPattern->GetPageInfo();
    CHECK_NULL_VOID(destPageInfo);
    auto destFullPath = destPageInfo->GetFullPath();

    ACE_SCOPED_TRACE_COMMERCIAL("Router Page from %s to %s", srcFullPath.c_str(), destFullPath.c_str());
}

void StageManager::SyncPageSafeArea(bool keyboardSafeArea)
{
    auto changeType = keyboardSafeArea ? PROPERTY_UPDATE_LAYOUT : PROPERTY_UPDATE_MEASURE;
    auto lastPage = GetLastPageWithTransition();
    CHECK_NULL_VOID(lastPage);
    lastPage->MarkDirtyNode(changeType);
    auto lastPageOverlay = lastPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(lastPageOverlay);
    lastPageOverlay->MarkDirtyOverlay();

    auto prevPage = GetPrevPageWithTransition();
    CHECK_NULL_VOID(prevPage);
    auto prevPageOverlay = prevPage->GetPattern<PagePattern>();
    CHECK_NULL_VOID(prevPageOverlay);
    prevPageOverlay->MarkDirtyOverlay();
}

bool StageManager::CheckPageFocus()
{
    auto pageNode = GetLastPage();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN)) {
        pageNode = GetLastPageWithTransition();
    }
    CHECK_NULL_RETURN(pageNode, true);
    return pageNode->GetFocusHub() && pageNode->GetFocusHub()->IsCurrentFocus();
}

void StageManager::AbortAnimation()
{
    if (!pushAnimations_.empty()) {
        for (const auto& animation : pushAnimations_) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
        pushAnimations_.clear();
    }
    if (!popAnimations_.empty()) {
        for (const auto& animation : popAnimations_) {
            if (animation) {
                AnimationUtils::StopAnimation(animation);
            }
        }
        popAnimations_.clear();
    }
}

std::string StageManager::GetSrcPageInfo(const RefPtr<FrameNode>& srcPage)
{
    CHECK_NULL_RETURN(srcPage, "");
    auto srcPattern = srcPage->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(srcPattern, "");
    auto srcPageInfo = srcPattern->GetPageInfo();
    CHECK_NULL_RETURN(srcPageInfo, "");
    return srcPageInfo->GetFullPath();
}

bool StageManager::CheckPageInTransition(const RefPtr<UINode>& pageNode)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(pageNode);
    CHECK_NULL_RETURN(frameNode, false);
    auto pagePattern = frameNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    return pagePattern->GetPageInTransition();
}

void StageManager::UpdatePageNeedRemove(const RefPtr<UINode>& pageNode)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(pageNode);
    CHECK_NULL_VOID(frameNode);
    auto pagePattern = frameNode->GetPattern<PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetIsNeedRemove(true);
}

void StageManager::StopPageTransition(bool needTransition)
{
    if (needTransition) {
        return;
    }
    auto srcNode = animationSrcPage_.Upgrade();
    if (srcNode) {
        auto pattern = srcNode->GetPattern<PagePattern>();
        pattern->StopPageTransition();
        animationSrcPage_ = nullptr;
    }
    auto destNode = destPageNode_.Upgrade();
    if (destNode) {
        auto pattern = destNode->GetPattern<PagePattern>();
        pattern->StopPageTransition();
        destPageNode_ = nullptr;
    }
}

std::vector<RefPtr<FrameNode>> StageManager::GetTopPagesWithTransition() const
{
    std::vector<RefPtr<FrameNode>> pages;
    auto page = GetLastPageWithTransition();
    if (page) {
        pages.emplace_back(page);
    }
    return pages;
}

std::vector<std::string> StageManager::GetTopPagePaths() const
{
    std::vector<std::string> paths;
    auto pages = GetTopPagesWithTransition();
    for (auto& page : pages) {
        paths.emplace_back("");
        CHECK_NULL_CONTINUE(page);
        auto pattern = page->GetPattern<PagePattern>();
        CHECK_NULL_CONTINUE(pattern);
        auto info = pattern->GetPageInfo();
        CHECK_NULL_CONTINUE(info);
        CHECK_NULL_CONTINUE(getPagePathCallback_);
        paths.back() = getPagePathCallback_(info->GetPageUrl());
    }
    return paths;
}
} // namespace OHOS::Ace::NG
