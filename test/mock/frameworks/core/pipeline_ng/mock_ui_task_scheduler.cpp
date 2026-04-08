/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/pipeline_ng/ui_task_scheduler.h"
#include "core/components_ng/base/frame_node.h"
#define private public
#include "core/pipeline_ng/pipeline_context.h"
#undef private

namespace OHOS::Ace::NG {
uint64_t UITaskScheduler::frameId_ = 0;

UITaskScheduler::UITaskScheduler() = default;
UITaskScheduler::~UITaskScheduler() = default;

void UITaskScheduler::AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty)
{
    if (!dirty) {
        return;
    }
    dirtyLayoutNodes_.emplace_back(dirty);
    auto context = PipelineContext::GetCurrentContextSafelyWithCheck();
    if (context && context->taskScheduler_ && context->taskScheduler_.get() != this) {
        context->taskScheduler_->dirtyLayoutNodes_.emplace_back(dirty);
    }
}
void UITaskScheduler::AddIgnoreLayoutSafeAreaBundle(IgnoreLayoutSafeAreaBundle&& bundle, bool postByTraverse)
{
    (void)bundle;
    (void)postByTraverse;
}
void UITaskScheduler::AddLayoutNode(const RefPtr<FrameNode>& layoutNode)
{
    if (layoutNode) {
        layoutNodes_.emplace_back(layoutNode);
    }
}
void UITaskScheduler::AddDirtyRenderNode(const RefPtr<FrameNode>& dirty)
{
    if (!dirty) {
        return;
    }
    dirtyRenderNodes_[dirty->GetPageId()].emplace(dirty);
}
void UITaskScheduler::AddPredictTask(PredictTask&& task)
{
    if (task) {
        predictTask_.emplace_back(std::move(task));
    }
}
void UITaskScheduler::AddAfterLayoutTask(std::function<void()>&& task, bool isFlushInImplicitAnimationTask)
{
    if (!task) {
        return;
    }
    if (isFlushInImplicitAnimationTask) {
        afterLayoutCallbacksInImplicitAnimationTask_.emplace_back(std::move(task));
        return;
    }
    afterLayoutTasks_.emplace_back(std::move(task));
}
void UITaskScheduler::AddAfterRenderTask(std::function<void()>&& task)
{
    if (task) {
        afterRenderTasks_.emplace_back(std::move(task));
    }
}
void UITaskScheduler::AddPersistAfterLayoutTask(std::function<void()>&& task)
{
    if (task) {
        persistAfterLayoutTasks_.emplace_back(std::move(task));
    }
}
void UITaskScheduler::AddAfterModifierTask(std::function<void()>&& task)
{
    if (task) {
        afterModifierTasks_.emplace_back(std::move(task));
    }
}
void UITaskScheduler::FlushLayoutTask(bool forceUseMainThread)
{
    (void)forceUseMainThread;
    dirtyLayoutNodes_.clear();
    layoutNodes_.clear();
    ignoreLayoutSafeAreaBundles_.clear();
    traverseSafeAreaBundles_.clear();
    singleDirtyNodesToFlush_.clear();
}

void UITaskScheduler::FlushRenderTask(bool forceUseMainThread)
{
    (void)forceUseMainThread;
    dirtyRenderNodes_.clear();
}
void UITaskScheduler::FlushTask()
{
    FlushLayoutTask();
    FlushRenderTask();
    FlushAfterLayoutTask();
    FlushAfterRenderTask();
    FlushPersistAfterLayoutTask();
    FlushAfterModifierTask();
}
void UITaskScheduler::FlushTaskWithCheck(bool triggeredByImplicitAnimation)
{
    (void)triggeredByImplicitAnimation;
    FlushTask();
}
void UITaskScheduler::FlushPredictTask(int64_t deadline, bool canUseLongPredictTask)
{
    auto tasks = std::move(predictTask_);
    predictTask_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task(deadline, canUseLongPredictTask);
        }
    }
}
void UITaskScheduler::FlushAfterLayoutTask()
{
    auto tasks = std::move(afterLayoutTasks_);
    afterLayoutTasks_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}
void UITaskScheduler::FlushAfterLayoutCallbackInImplicitAnimationTask()
{
    auto tasks = std::move(afterLayoutCallbacksInImplicitAnimationTask_);
    afterLayoutCallbacksInImplicitAnimationTask_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}
void UITaskScheduler::FlushAfterRenderTask()
{
    auto tasks = std::move(afterRenderTasks_);
    afterRenderTasks_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}
void UITaskScheduler::FlushPersistAfterLayoutTask()
{
    auto tasks = std::move(persistAfterLayoutTasks_);
    persistAfterLayoutTasks_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}
void UITaskScheduler::FlushAfterModifierTask()
{
    auto tasks = std::move(afterModifierTasks_);
    afterModifierTasks_.clear();
    for (const auto& task : tasks) {
        if (task) {
            task();
        }
    }
}
void UITaskScheduler::ExpandSafeArea() {}
void UITaskScheduler::FlushDelayJsActive() {}
void UITaskScheduler::CleanUp() {}
bool UITaskScheduler::isEmpty()
{
    return dirtyLayoutNodes_.empty() && layoutNodes_.empty() && dirtyRenderNodes_.empty() && predictTask_.empty() &&
           afterLayoutTasks_.empty() && afterLayoutCallbacksInImplicitAnimationTask_.empty() &&
           afterRenderTasks_.empty() && persistAfterLayoutTasks_.empty() && afterModifierTasks_.empty();
}
bool UITaskScheduler::IsPredictTaskEmpty()
{
    return predictTask_.empty();
}
void UITaskScheduler::AddSingleNodeToFlush(const RefPtr<FrameNode>& dirtyNode)
{
    if (!dirtyNode) {
        return;
    }
    singleDirtyNodesToFlush_.insert(dirtyNode);
}
bool UITaskScheduler::RequestFrameOnLayoutCountExceeds() { return false; }
void UITaskScheduler::SetJSViewActive(bool active, WeakPtr<CustomNode> custom)
{
    (void)active;
    (void)custom;
}
void UITaskScheduler::AddSafeAreaPaddingProcessTask(FrameNode* node) { (void)node; }
void UITaskScheduler::RemoveSafeAreaPaddingProcessTask(FrameNode* node) { (void)node; }
void UITaskScheduler::FlushSafeAreaPaddingProcess() {}
void UITaskScheduler::FlushSyncGeometryNodeTasks() {}
void UITaskScheduler::FlushPostponedLayoutTask(bool forceUseMainThread) { (void)forceUseMainThread; }

bool UITaskScheduler::NeedAdditionalLayout() { return false; }
void UITaskScheduler::FlushAllSingleNodeTasks() {}
void UITaskScheduler::SetLayoutNodeRect() {}
} // namespace OHOS::Ace::NG
