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

#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_base.h"

#include "core/components_ng/manager/drag_drop/drag_drop_behavior_reporter/drag_drop_behavior_reporter.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/manager/drag_drop/drag_drop_initiating/drag_drop_initiating_state_machine.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/gestures/drag_event.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PIXELMAP_ANIMATION_DURATION = 300;
constexpr float PIXELMAP_DRAG_SCALE_MULTIPLE = 1.05f;
} // namespace

void DragDropInitiatingStateBase::DoPixelMapScaleForDragThroughTouch(
    DragDropInitiatingParams& params, const RefPtr<PixelMap>& pixelMap, float targetScale)
{
#if defined(PIXEL_MAP_SUPPORTED)
    params.preScaledPixelMap = PixelMap::CopyPixelMap(pixelMap);
    if (!params.preScaledPixelMap) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Copy preScaledPixelMap is failure!");
        return;
    }
    params.preScaledPixelMap->Scale(targetScale, targetScale, AceAntiAliasingOption::HIGH);
    params.preScaleValue = targetScale;
#endif
}

void DragDropInitiatingStateBase::PrepareFinalPixelMapForDragThroughTouch(
    const RefPtr<PixelMap>& pixelMap, bool immediately)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto windowScale = dragDropManager->GetWindowScale();
    float scale = windowScale * PIXELMAP_DRAG_SCALE_MULTIPLE;

    auto task = [weak = WeakClaim(this), pixelMap, scale]() {
        auto stateBase = weak.Upgrade();
        CHECK_NULL_VOID(stateBase);
        auto machine = stateBase->GetStateMachine();
        CHECK_NULL_VOID(machine);
        auto& params = machine->GetDragDropInitiatingParams();
        stateBase->DoPixelMapScaleForDragThroughTouch(params, pixelMap, scale);
        params.isThumbnailCallbackTriggered = true;
    };

    if (immediately) {
        task();
        return;
    }

    auto taskScheduler = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskScheduler);
    taskScheduler->PostTask(task, TaskExecutor::TaskType::UI, "ArkUIPrepareScaledPixel", PriorityType::VIP);
}

void DragDropInitiatingStateBase::FireCustomerOnDragEnd()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto eventHub = frameNode ->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->FireCustomerOnDragEnd(pipelineContext, eventHub);
}

void DragDropInitiatingStateBase::HidePixelMap(bool startDrag, double x, double y, bool showAnimation)
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    if (params.hasGatherNode) {
        if (!startDrag) {
            manager->RemovePreviewBadgeNode();
            manager->RemoveGatherNodeWithAnimation();
        }
        DragAnimationHelper::HideDragNodeCopyWithAnimation(manager, frameNode);
    }

    if (showAnimation) {
        manager->RemovePixelMapAnimation(startDrag, x, y);
    } else {
        manager->RemovePixelMap();
    }
}

void DragDropInitiatingStateBase::HideEventColumn()
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->RemoveEventColumn();
}

bool DragDropInitiatingStateBase::IsAllowedDrag()
{
    auto machine = GetStateMachine();
    CHECK_NULL_RETURN(machine, false);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    return isAllowedDrag;
}

void DragDropInitiatingStateBase::UpdateDragPreviewOptionFromModifier()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto& params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto dragPreviewOption = frameNode->GetDragPreviewOption();
    DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(dragPreviewOption, dragPreviewOption.isMultiSelectionEnabled);
    frameNode->SetDragPreviewOptions(dragPreviewOption);
    auto modifierOnApply = dragPreviewOption.onApply;
    if (modifierOnApply) {
        DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(modifierOnApply, dragPreviewOption);
        frameNode->SetDragPreviewOptions(dragPreviewOption);
    }
    params.optionsAfterApplied = dragPreviewOption.options;
}

void DragDropInitiatingStateBase::ResetBorderRadiusAnimation()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    BorderRadiusProperty borderRadius;
    if (renderContext->GetBorderRadius().has_value()) {
        borderRadius.UpdateWithCheck(renderContext->GetBorderRadius().value());
    }
    borderRadius.multiValued = false;
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option,
        [renderContext = renderContext, borderRadius = borderRadius]() {
            renderContext->UpdateBorderRadius(borderRadius);
        },
        option.GetOnFinishEvent());
}

bool DragDropInitiatingStateBase::CheckStatusForPanActionBegin(
    const RefPtr<FrameNode>& frameNode, const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_RETURN(dragDropManager, false);
    if (dragDropManager->IsDragging() || dragDropManager->IsMSDPDragging()) {
        DragDropBehaviorReporterTrigger trigger(DragReporterPharse::DRAG_START, Container::CurrentId());
        DragDropBehaviorReporter::GetInstance().UpdateDragStartResult(DragStartResult::REPEAT_DRAG_FAIL);
        TAG_LOGI(AceLogTag::ACE_DRAG, "It's already dragging now, dragging is %{public}d, MSDP dragging is %{public}d",
            dragDropManager->IsDragging(), dragDropManager->IsMSDPDragging());
        return false;
    }
    if (dragDropManager->IsDragNodeNeedClean()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Drag node have been cleaned by backpress or click event, stop dragging.");
        return false;
    }
    CHECK_NULL_RETURN(frameNode, false);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    if (gestureHub->GetTextDraggable() && !gestureHub->GetIsTextDraggable()) {
        TAG_LOGI(AceLogTag::ACE_DRAG, "Text category component does not meet the drag condition, forbidden drag.");
        dragDropManager->ResetDragging();
        return false;
    }
    return true;
}

int32_t DragDropInitiatingStateBase::GetCurDuration(const TouchEvent& touchEvent, int32_t curDuration)
{
    int64_t currentTimeStamp = GetSysTimestamp();
    auto machine = GetStateMachine();
    CHECK_NULL_RETURN(machine, 0);
    int64_t eventTimeStamp = static_cast<int64_t>(touchEvent.time.time_since_epoch().count());
    if (currentTimeStamp > eventTimeStamp) {
        curDuration = curDuration - static_cast<int32_t>((currentTimeStamp- eventTimeStamp) / TIME_BASE);
        curDuration = curDuration < 0 ? 0: curDuration;
    }
    return curDuration;
}

void DragDropInitiatingStateBase::SetTextPixelMap()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    CHECK_NULL_VOID(pattern);
    auto dragNode = pattern->MoveDragNode();
    pattern->CloseSelectOverlay();
    CHECK_NULL_VOID(dragNode);
    if (params.preScaledPixelMap) {
        gestureHub->SetPixelMap(params.preScaledPixelMap);
        params.preScaledPixelMap = nullptr;
        return;
    }
    auto renderContext = dragNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pixelMap = renderContext->GetThumbnailPixelMap();
    if (pixelMap) {
        gestureHub->SetPixelMap(pixelMap);
    } else {
        gestureHub->SetPixelMap(nullptr);
    }
}

std::function<void()> GetTextAnimationFinishCallback(
    bool startDrag, const RefPtr<FrameNode>& frameNode, const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextDragBase>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto node = pattern->MoveDragNode();
    CHECK_NULL_RETURN(node, nullptr);
    auto textDragPattern = node->GetPattern<TextDragPattern>();
    CHECK_NULL_RETURN(textDragPattern, nullptr);
    auto modifier = textDragPattern->GetOverlayModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    return [id = Container::CurrentId(), startDrag, weakPattern = WeakPtr<TextDragBase>(pattern),
               weakEvent = AceType::WeakClaim(AceType::RawPtr(gestureHub)),
               weakModifier = WeakPtr<TextDragOverlayModifier>(modifier)] {
        ContainerScope scope(id);
        if (!startDrag) {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto modifier = weakModifier.Upgrade();
            CHECK_NULL_VOID(modifier);
            pattern->ShowHandles(modifier->IsHandlesShow());
        }
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto manager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(manager);
        manager->RemovePixelMap();
        TAG_LOGD(AceLogTag::ACE_DRAG, "In removeColumnNode callback, set DragWindowVisible true.");
        auto gestureHub = weakEvent.Upgrade();
        CHECK_NULL_VOID(gestureHub);
        auto dragDropManager = pipeline->GetDragDropManager();
        if (!gestureHub->IsPixelMapNeedScale() && dragDropManager && dragDropManager->IsDragging()) {
            InteractionInterface::GetInstance()->SetDragWindowVisible(true);
        }
        gestureHub->SetPixelMap(nullptr);
    };
}

void DragDropInitiatingStateBase::HideTextAnimation(bool startDrag, double globalX, double globalY)
{
    TAG_LOGD(AceLogTag::ACE_DRAG, "DragEvent start hide text animation.");
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    bool isAllowedDrag = gestureHub->IsAllowedDrag(eventHub);
    if (!gestureHub->GetTextDraggable() || !isAllowedDrag) {
        TAG_LOGD(AceLogTag::ACE_DRAG, "Text is not draggable, stop set hide text animation.");
        return;
    }
    auto removeColumnNode = GetTextAnimationFinishCallback(startDrag, frameNode, gestureHub);
    AnimationOption option;
    option.SetDuration(PIXELMAP_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetOnFinishEvent(removeColumnNode);

    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    auto dragNode = manager->GetPixelMapNode();
    CHECK_NULL_VOID(dragNode);
    auto dragFrame = dragNode->GetGeometryNode()->GetFrameRect();
    auto frameWidth = dragFrame.Width();
    auto frameHeight = dragFrame.Height();
    auto pixelMap = gestureHub->GetPixelMap();
    float scale = 1.0f;
    if (pixelMap) {
        scale = gestureHub->GetPixelMapScale(pixelMap->GetHeight(), pixelMap->GetWidth());
    }
    auto context = dragNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformScale(VectorF(1.0f, 1.0f));
    AnimationUtils::Animate(
        option,
        [context, startDrag, globalX, globalY, frameWidth, frameHeight, scale]() {
            if (startDrag) {
                context->UpdatePosition(OffsetT<Dimension>(Dimension(globalX + frameWidth * PIXELMAP_WIDTH_RATE),
                    Dimension(globalY + frameHeight * PIXELMAP_HEIGHT_RATE)));
                context->UpdateTransformScale(VectorF(scale, scale));
                context->OnModifyDone();
            }
        },
        option.GetOnFinishEvent());
}

void DragDropInitiatingStateBase::HandleTextDragCallback()
{
    auto machine = GetStateMachine();
    CHECK_NULL_VOID(machine);
    auto params = machine->GetDragDropInitiatingParams();
    auto frameNode = params.frameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto pattern = frameNode->GetPattern<TextBase>();
    if (pattern->BetweenSelectedPosition(params.touchOffset)) {
        if (params.getTextThumbnailPixelMapCallback) {
            params.getTextThumbnailPixelMapCallback(params.touchOffset);
        }
    } else if (!gestureHub->GetIsTextDraggable()) {
        gestureHub->SetPixelMap(nullptr);
    }
}
} // namespace OHOS::Ace::NG
