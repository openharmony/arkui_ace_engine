/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"

#include <list>

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/pipeline/base/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
FrameNode::FrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
    : UINode(tag, nodeId, isRoot), pattern_(pattern)
{
    renderContext_->InitContext(IsRootNode(), pattern_->SurfaceNodeName());
    paintProperty_ = pattern->CreatePaintProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
    eventHub_ = pattern->CreateEventHub();
}

FrameNode::~FrameNode()
{
    pattern_->DetachFromFrameNode();
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    auto newChild = CreateFrameNode(tag, nodeId, pattern, true);
    newChild->SetDepth(1);
    return newChild;
}

RefPtr<FrameNode> FrameNode::GetOrCreateFrameNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return frameNode;
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    return CreateFrameNode(tag, nodeId, pattern);
}

RefPtr<FrameNode> FrameNode::GetFrameNode(const std::string& tag, int32_t nodeId)
{
    auto frameNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
    if (!frameNode) {
        return nullptr;
    }
    if (frameNode->tag_ != tag) {
        LOGE("the tag is changed");
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = frameNode->GetParent();
        if (parent) {
            parent->RemoveChild(frameNode);
        }
        return nullptr;
    }
    return frameNode;
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);
    return frameNode;
}

void FrameNode::InitializePatternAndContext()
{
    eventHub_->AttachHost(WeakClaim(this));
    pattern_->AttachToFrameNode(WeakClaim(this));
    renderContext_->SetRequestFrame([weak = WeakClaim(this)] {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (frameNode->onMainTree_) {
            auto context = frameNode->GetContext();
            CHECK_NULL_VOID(context);
            context->RequestFrame();
            return;
        }
        frameNode->hasPendingRequest_ = true;
    });
}

void FrameNode::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
    DumpLog::GetInstance().AddDesc(std::string("FrameRect: ").append(geometryNode_->GetFrame().ToString()));
    DumpLog::GetInstance().AddDesc(std::string("LayoutConstraint: ")
                                       .append(layoutProperty_->GetLayoutConstraint().has_value()
                                                   ? layoutProperty_->GetLayoutConstraint().value().ToString()
                                                   : "NA"));
}

void FrameNode::OnAttachToMainTree()
{
    UINode::OnAttachToMainTree();
    if (!hasPendingRequest_) {
        return;
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    hasPendingRequest_ = false;
}

void FrameNode::SwapDirtyLayoutWrapperOnMainThread(const RefPtr<LayoutWrapper>& dirty)
{
    ACE_FUNCTION_TRACE();
    LOGD("SwapDirtyLayoutWrapperOnMainThread, %{public}s", GetTag().c_str());
    CHECK_NULL_VOID(dirty);

    // active change flag judge.
    bool activeChanged = false;
    if (dirty->IsActive() && !isActive_) {
        pattern_->OnActive();
        isActive_ = true;
        activeChanged = true;
    }
    if (!dirty->IsActive() && isActive_) {
        pattern_->OnInActive();
        isActive_ = false;
        activeChanged = true;
    }
    if (activeChanged && !dirty->IsRootMeasureNode()) {
        auto parent = GetAncestorNodeOfFrame();
        if (parent) {
            parent->MarkNeedSyncRenderTree();
        }
    }
    if (!isActive_) {
        LOGD("current node is inactive, don't need to render");
        return;
    }

    // check if need to paint content.
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(
        dirty, layoutAlgorithmWrapper->SkipMeasure(), layoutAlgorithmWrapper->SkipLayout());
    if (needRerender || CheckNeedRender(paintProperty_->GetPropertyChangeFlag())) {
        MarkDirtyNode(true, true, PROPERTY_UPDATE_RENDER);
    }

    // rebuild child render node.
    RebuildRenderContextTree();

    // update layout size.
    bool frameSizeChange = geometryNode_->GetFrameSize() != dirty->GetGeometryNode()->GetFrameSize();
    bool frameOffsetChange = geometryNode_->GetFrameOffset() != dirty->GetGeometryNode()->GetFrameOffset();
    bool contentSizeChange = geometryNode_->GetContentSize() != dirty->GetGeometryNode()->GetContentSize();
    bool contentOffsetChange = geometryNode_->GetContentOffset() != dirty->GetGeometryNode()->GetContentOffset();
    if (frameSizeChange || frameOffsetChange) {
        renderContext_->SyncGeometryProperties(RawPtr(dirty->GetGeometryNode()));
    }
    if (layoutProperty_->GetBorderWidthProperty()) {
        if (layoutProperty_->GetLayoutConstraint().has_value()) {
            renderContext_->UpdateBorderWidth(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(),
                layoutProperty_->GetLayoutConstraint()->percentReference.Width()));
        } else {
            renderContext_->UpdateBorderWidth(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth()));
        }
    }
    SetGeometryNode(dirty->MoveGeometryNode());
    pattern_->OnLayoutChange(frameSizeChange, frameOffsetChange, contentSizeChange, contentOffsetChange);

    // clean layout flag.
    layoutProperty_->CleanDirty();
}

void FrameNode::SetGeometryNode(RefPtr<GeometryNode>&& node)
{
    geometryNode_.Swap(std::move(node));
}

std::optional<UITask> FrameNode::CreateLayoutTask(bool onCreate, bool forceUseMainThread)
{
    if (!isLayoutDirtyMarked_) {
        return std::nullopt;
    }
    ACE_SCOPED_TRACE("CreateLayoutTask:PrepareTask");
    RefPtr<LayoutWrapper> layoutWrapper;
    if (!onCreate) {
        UpdateLayoutPropertyFlag();
        layoutWrapper = CreateLayoutWrapper();
    } else {
        layoutWrapper = CreateLayoutWrapperOnCreate();
    }
    auto task = [layoutWrapper, layoutConstraint = GetLayoutConstraint(), offset = GetParentGlobalOffset(),
                    forceUseMainThread]() {
        layoutWrapper->SetActive();
        layoutWrapper->SetRootMeasureNode();
        {
            ACE_SCOPED_TRACE("LayoutWrapper::Measure");
            layoutWrapper->Measure(layoutConstraint);
        }
        {
            ACE_SCOPED_TRACE("LayoutWrapper::Layout");
            layoutWrapper->Layout(offset);
        }
        {
            ACE_SCOPED_TRACE("LayoutWrapper::MountToHostOnMainThread");
            if (forceUseMainThread || layoutWrapper->CheckShouldRunOnMain()) {
                layoutWrapper->MountToHostOnMainThread();
                return;
            }
            auto host = layoutWrapper->GetHostNode();
            CHECK_NULL_VOID(host);
            host->PostTask([layoutWrapper]() { layoutWrapper->MountToHostOnMainThread(); });
        }
    };
    if (forceUseMainThread || layoutWrapper->CheckShouldRunOnMain()) {
        return UITask(std::move(task), MAIN_TASK);
    }
    return UITask(std::move(task), layoutWrapper->CanRunOnWhichThread());
}

std::optional<UITask> FrameNode::CreateRenderTask(bool forceUseMainThread)
{
    if (!isRenderDirtyMarked_) {
        return std::nullopt;
    }
    ACE_SCOPED_TRACE("CreateRenderTask:PrepareTask");
    auto wrapper = CreatePaintWrapper();
    auto task = [wrapper, paintProperty = paintProperty_]() {
        ACE_SCOPED_TRACE("FrameNode::RenderTask");
        wrapper->FlushRender();
        paintProperty->CleanDirty();
    };
    if (forceUseMainThread || wrapper->CheckShouldRunOnMain()) {
        return UITask(std::move(task), MAIN_TASK);
    }
    return UITask(std::move(task), wrapper->CanRunOnWhichThread());
}

LayoutConstraintF FrameNode::GetLayoutConstraint() const
{
    if (geometryNode_->GetParentLayoutConstraint().has_value()) {
        return geometryNode_->GetParentLayoutConstraint().value();
    }
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.scaleProperty = ScaleProperty::CreateScaleProperty();
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    LayoutConstraint.percentReference.SetWidth(rootWidth);
    LayoutConstraint.percentReference.SetHeight(rootHeight);
    LayoutConstraint.maxSize.SetHeight(rootWidth);
    LayoutConstraint.maxSize.SetHeight(rootHeight);
    return LayoutConstraint;
}

OffsetF FrameNode::GetParentGlobalOffset() const
{
    auto parent = GetAncestorNodeOfFrame();
    if (!parent) {
        return { 0.0f, 0.0f };
    }
    return parent->geometryNode_->GetParentGlobalOffset();
}

void FrameNode::UpdateLayoutPropertyFlag()
{
    if (!CheckUpdateByChildRequest(layoutProperty_->GetPropertyChangeFlag())) {
        return;
    }
    auto flag = PROPERTY_UPDATE_NORMAL;
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->UpdateLayoutPropertyFlag();
        child->AdjustParentLayoutFlag(flag);
    }
    if ((flag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    if ((flag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    }
}

void FrameNode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
    flag = flag | layoutProperty_->GetPropertyChangeFlag();
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapperOnCreate()
{
    pattern_->BeforeCreateLayoutWrapper();
    isLayoutDirtyMarked_ = false;
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->AdjustLayoutWrapperTree(layoutWrapper, true, true);
    }
    return layoutWrapper;
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    pattern_->BeforeCreateLayoutWrapper();
    isLayoutDirtyMarked_ = false;
    auto flag = layoutProperty_->GetPropertyChangeFlag();
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    do {
        // when inactive node need to reactive in render tree, need to measure again.
        if (CheckMeasureFlag(flag) || CheckMeasureSelfFlag(flag) || forceMeasure) {
            layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
            bool forceChildMeasure = CheckMeasureFlag(flag) || forceMeasure;
            UpdateChildrenLayoutWrapper(layoutWrapper, forceChildMeasure, false);
            break;
        }
        if (CheckLayoutFlag(flag) || forceLayout) {
            layoutWrapper->SetLayoutAlgorithm(
                MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm(), true, false));
            UpdateChildrenLayoutWrapper(layoutWrapper, false, false);
            break;
        }
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(nullptr, true, true));
    } while (false);
    return layoutWrapper;
}

void FrameNode::UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self, bool forceMeasure, bool forceLayout)
{
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->AdjustLayoutWrapperTree(self, forceMeasure, forceLayout);
    }
}

void FrameNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapper>& parent, bool forceMeasure, bool forceLayout)
{
    ACE_DCHECK(parent);
    auto layoutWrapper = CreateLayoutWrapper(forceMeasure, forceLayout);
    parent->AppendChild(layoutWrapper);
}

RefPtr<PaintWrapper> FrameNode::CreatePaintWrapper()
{
    pattern_->BeforeCreatePaintWrapper();
    isRenderDirtyMarked_ = false;
    auto paintWrapper = MakeRefPtr<PaintWrapper>(renderContext_, geometryNode_->Clone(), paintProperty_->Clone());
    paintWrapper->SetNodePaintMethod(pattern_->CreateNodePaintMethod());
    return paintWrapper;
}

void FrameNode::PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->PostAsyncEvent(std::move(task), taskType);
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
    layoutProperty_->UpdateCalcLayoutProperty(calcLayoutConstraint);
}

void FrameNode::RebuildRenderContextTree()
{
    if (!needSyncRenderTree_) {
        return;
    }
    std::list<RefPtr<FrameNode>> children;
    GenerateOneDepthVisibleFrame(children);
    LOGD("%{public}s rebuild render context tree, child: %{public}d", GetTag().c_str(),
        static_cast<int32_t>(children.size()));
    renderContext_->RebuildFrame(this, children);
    needSyncRenderTree_ = false;
}

void FrameNode::MarkModifyDone()
{
    pattern_->OnModifyDone();
}

void FrameNode::FlushUpdateAndMarkDirty()
{
    MarkDirtyNode();
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    MarkDirtyNode(IsMeasureBoundary(), IsRenderBoundary(), extraFlag);
}

RefPtr<FrameNode> FrameNode::GetAncestorNodeOfFrame() const
{
    auto parent = GetParent();
    while (parent) {
        if (InstanceOf<FrameNode>(parent)) {
            return DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void FrameNode::MarkDirtyNode(bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag)
{
    layoutProperty_->UpdatePropertyChangeFlag(extraFlag);
    paintProperty_->UpdatePropertyChangeFlag(extraFlag);
    auto layoutFlag = layoutProperty_->GetPropertyChangeFlag();
    auto paintFlag = paintProperty_->GetPropertyChangeFlag();
    if (CheckNoChanged(layoutFlag | paintFlag)) {
        return;
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);

    if (CheckNeedRequestMeasureAndLayout(layoutFlag)) {
        if (isLayoutDirtyMarked_) {
            return;
        }
        isLayoutDirtyMarked_ = true;
        if (!isMeasureBoundary && CheckNeedRequestParentMeasure(layoutFlag)) {
            auto parent = GetAncestorNodeOfFrame();
            if (parent) {
                parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            }
            return;
        }
        context->AddDirtyLayoutNode(Claim(this));
        return;
    }
    layoutProperty_->CleanDirty();

    // If has dirtyLayoutBox, need to mark dirty after layout done.
    if (isRenderDirtyMarked_ || isLayoutDirtyMarked_) {
        return;
    }
    isRenderDirtyMarked_ = true;
    if (isRenderBoundary) {
        context->AddDirtyRenderNode(Claim(this));
        return;
    }
    auto parent = GetAncestorNodeOfFrame();
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    }
}

void FrameNode::OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    if (isActive_) {
        visibleList.emplace_back(Claim(this));
    }
}

bool FrameNode::IsMeasureBoundary()
{
    return isMeasureBoundary_ || pattern_->IsMeasureBoundary();
}

bool FrameNode::IsRenderBoundary()
{
    return pattern_->IsRenderBoundary();
}

const RefPtr<Pattern>& FrameNode::GetPattern() const
{
    return pattern_;
}

bool FrameNode::IsAtomicNode() const
{
    return pattern_->IsAtomicNode();
}

HitTestMode FrameNode::GetHitTestMode() const
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetHitTestMode() : HitTestMode::DEFAULT;
}

HitTestResult FrameNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    const auto& rect = geometryNode_->GetFrame().GetRect();
    LOGD("TouchTest: type is %{public}s, the region is %{public}s", GetTag().c_str(), rect.ToString().c_str());

    if (!rect.IsInRegion(parentLocalPoint)) {
        return HitTestResult::OUT_OF_REGION;
    }

    bool preventBubbling = false;
    // Child nodes are repackaged into gesture groups (parallel gesture groups, exclusive gesture groups, etc.) based on
    // the gesture attributes set by the current parent node (high and low priority, parallel gestures, etc.), the
    // newComingTargets is the template object to collect child nodes gesture and used by gestureHub to pack gesture
    // group.
    TouchTestResult newComingTargets;
    const auto localPoint = parentLocalPoint - geometryNode_->GetFrameOffset();
    // TODO: add hit test mode.
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        const auto& child = *iter;
        auto childHitResult = child->TouchTest(globalPoint, localPoint, touchRestrict, newComingTargets);
        if (childHitResult == HitTestResult::STOP_BUBBLING) {
            preventBubbling = true;
            break;
        }
        // In normal process, the node block the brother node.
        if (childHitResult == HitTestResult::BUBBLING) {
            // TODO: add hit test mode judge.
            break;
        }
    }
    if (!preventBubbling) {
        auto gestureHub = eventHub_->GetGestureEventHub();
        if (gestureHub) {
            TouchTestResult finalResult;
            const auto coordinateOffset = globalPoint - localPoint;
            preventBubbling =
                gestureHub->ProcessTouchTestHit(coordinateOffset, touchRestrict, newComingTargets, finalResult);
            newComingTargets.swap(finalResult);
        }
    }
    result.splice(result.end(), std::move(newComingTargets));
    if (preventBubbling) {
        return HitTestResult::STOP_BUBBLING;
    }
    return HitTestResult::BUBBLING;
}
} // namespace OHOS::Ace::NG
