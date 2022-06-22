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

#include "base/geometry/ng/point_t.h"
#include "base/log/ace_trace.h"
#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/modifier/modify_task.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/render_wrapper.h"
#include "core/pipeline/base/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
FrameNode::FrameNode(const std::string& tag, const std::string& id, const RefPtr<Pattern>& pattern, bool isRoot)
    : tag_(tag), id_(id), pattern_(pattern), isRoot_(isRoot)
{
    renderContext_->InitContext(isRoot_);
    renderProperty_ = pattern->CreateRenderProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
    eventHub_ = pattern->CreateEventHub();
}

FrameNode::~FrameNode()
{
    pattern_->DetachFromFrameNode();
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeAndMountToParent(const std::string& tag, const std::string& id,
    const RefPtr<Pattern>& pattern, const RefPtr<FrameNode>& parent, int32_t slot)
{
    auto newChild = CreateFrameNode(tag, id, pattern);
    newChild->MountToParent(parent, slot);
    return newChild;
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(const std::string& tag, const std::string& id,
    const RefPtr<Pattern>& pattern, const RefPtr<PipelineContext>& context)
{
    auto newChild = CreateFrameNode(tag, id, pattern, true);
    newChild->SetDepth(1);
    newChild->AttachContextRecursively(context);
    newChild->SetSlotId(0);
    return newChild;
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(
    const std::string& tag, const std::string& id, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, id, pattern, isRoot);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

void FrameNode::InitializePatternAndContext()
{
    eventHub_->AttachHost(WeakClaim(this));
    pattern_->AttachToFrameNode(WeakClaim(this));
    renderContext_->SetRequestFrame([weak = WeakClaim(this)] {
        auto frameNode = weak.Upgrade();
        if (frameNode) {
            frameNode->RequestNextFrame();
        }
    });
}

void FrameNode::AddChild(const RefPtr<FrameNode>& child, int32_t slot)
{
    if (!child) {
        return;
    }

    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("Child element is already existed");
        return;
    }

    it = children_.begin();
    std::advance(it, slot);
    auto result = children_.insert(it, child);
    child->SetSlotId(std::distance(children_.begin(), result));
    child->OnActive();
    needSyncRenderTree_ = true;
}

void FrameNode::RemoveChild(const RefPtr<FrameNode>& child)
{
    if (!child) {
        return;
    }
    children_.remove(child);
    child->OnInActive();
    needSyncRenderTree_ = true;
}

void FrameNode::OnInActive()
{
    pattern_->OnActive();
    for (const auto& child : children_) {
        child->OnInActive();
    }
}

void FrameNode::OnActive()
{
    pattern_->OnActive();
    for (const auto& child : children_) {
        child->OnActive();
    }
}

RefPtr<FrameNode> FrameNode::GetChildBySlot(uint32_t slot)
{
    for (auto& iter : children_) {
        if (slot == iter->GetSlotId()) {
            return iter;
        }
    }
    return nullptr;
}

void FrameNode::DumpTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpInfo();
        DumpLog::GetInstance().AddDesc("tag: " + tag_);
        DumpLog::GetInstance().AddDesc("id: " + id_);
        DumpLog::GetInstance().AddDesc(std::string("Depth: ").append(std::to_string(GetDepth())));
        DumpLog::GetInstance().AddDesc(std::string("FrameRect: ").append(geometryNode_->GetFrame().ToString()));
        DumpLog::GetInstance().AddDesc(std::string("LayoutConstraint: ")
                                           .append(layoutProperty_->GetLayoutConstraint().has_value()
                                                       ? layoutProperty_->GetLayoutConstraint().value().ToString()
                                                       : "NA"));
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), static_cast<int32_t>(children_.size()));
    }

    for (const auto& item : children_) {
        item->DumpTree(depth + 1);
    }
}

void FrameNode::MountToParent(const RefPtr<FrameNode>& parent, int32_t slot)
{
    SetParent(parent);
    SetDepth(parent != nullptr ? parent->GetDepth() + 1 : 1);
    if (parent) {
        parent->AddChild(AceType::Claim(this), slot);
    }
    AttachContextRecursively(parent != nullptr ? parent->context_.Upgrade() : nullptr);
}

void FrameNode::SetPipelineContext(const RefPtr<PipelineContext>& context)
{
    context_ = context;
    pattern_->OnContextAttached();
    if (hasPendingRequest_) {
        context->RequestFrame();
        hasPendingRequest_ = false;
    }
    OnContextAttached();
}

void FrameNode::AttachContextRecursively(const RefPtr<PipelineContext>& context)
{
    if (!context) {
        return;
    }
    SetPipelineContext(context);
    for (auto& child : children_) {
        child->AttachContextRecursively(context);
    }
}

void FrameNode::MovePosition(uint32_t slot)
{
    auto parentNode = parent_.Upgrade();
    if (!parentNode) {
        LOGW("Invalid parent");
        return;
    }

    auto self = AceType::Claim(this);
    auto& children = parentNode->children_;
    auto it = children.end();
    if (slot >= 0 && static_cast<size_t>(slot) < children.size()) {
        it = children.begin();
        std::advance(it, slot);
        if (*it == this) {
            // Already at the right place
            return;
        }

        auto itSelf = std::find(it, children.end(), self);
        if (itSelf != children.end()) {
            children.erase(itSelf);
        } else {
            LOGW("Should NOT be here");
            children.remove(self);
            ++it;
        }
    } else {
        children.remove(self);
    }
    needSyncRenderTree_ = true;
}

void FrameNode::ClearChildren()
{
    children_.clear();
    needSyncRenderTree_ = true;
}

void FrameNode::RequestNextFrame()
{
    auto context = context_.Upgrade();
    if (context) {
        context->RequestFrame();
    } else {
        hasPendingRequest_ = true;
    }
}

RefPtr<PipelineContext> FrameNode::GetContext() const
{
    return context_.Upgrade();
}

void FrameNode::FlushModifyTaskOnCreate(StateModifyTask& stateModifyTask)
{
    if (!stateModifyTask.GetLayoutTask().empty()) {
        for (auto&& task : stateModifyTask.GetLayoutTask()) {
            task.FlushModify(RawPtr(layoutProperty_));
        }
    }
    if (!stateModifyTask.GetRenderTask().empty()) {
        for (auto&& task : stateModifyTask.GetRenderTask()) {
            task.FlushModify(RawPtr(renderProperty_));
        }
    }
    if (!stateModifyTask.GetRenderContextTask().empty()) {
        for (auto&& task : stateModifyTask.GetRenderContextTask()) {
            task.FlushModify(RawPtr(renderContext_));
        }
    }
    pattern_->OnModifyDone();
}

void FrameNode::FlushModifyTaskOnRerender(StateModifyTask& stateModifyTask)
{
    if (!stateModifyTask.GetLayoutTask().empty()) {
        for (auto&& task : stateModifyTask.GetLayoutTask()) {
            task.FlushModify(RawPtr(layoutProperty_));
        }
    }
    if (!stateModifyTask.GetRenderTask().empty()) {
        for (auto&& task : stateModifyTask.GetRenderTask()) {
            task.FlushModify(RawPtr(renderProperty_));
        }
    }
    MarkDirtyNode();
    auto task = [contextTask = stateModifyTask.MoveRenderContextTask(),
                    renderContext = WeakPtr<RenderContext>(renderContext_)]() {
        auto context = renderContext.Upgrade();
        if (context) {
            for (auto&& task : contextTask) {
                task.FlushModify(RawPtr(context));
            }
        }
    };
    PostTask(std::move(task));
    pattern_->OnModifyDone();
}

void FrameNode::SwapDirtyLayoutWrapperOnMainThread(const RefPtr<LayoutWrapper>& dirty)
{
    LOGD("SwapDirtyLayoutWrapperOnMainThread, %{public}s", GetTag().c_str());
    CHECK_NULL_VOID(dirty);
    if (needSyncRenderTree_) {
        RebuildRenderContextTree();
        needSyncRenderTree_ = false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(
        dirty, layoutAlgorithmWrapper->SkipMeasure(), layoutAlgorithmWrapper->SkipLayout());
    if (needRerender || CheckNeedRender(renderProperty_->GetPropertyChangeFlag())) {
        MarkDirtyNode(true, true, PROPERTY_UPDATE_RENDER);
    }
    if (geometryNode_->GetFrame().GetRect() != dirty->GetGeometryNode()->GetFrame().GetRect()) {
        renderContext_->SyncGeometryProperties(RawPtr(dirty->GetGeometryNode()));
    }
    SetGeometryNode(dirty->MoveGeometryNode());
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
    ACE_SCOPED_TRACE("prepare layout task");
    RefPtr<LayoutWrapper> layoutWrapper;
    if (!onCreate) {
        UpdateLayoutPropertyFlag();
        layoutWrapper = CreateLayoutWrapper();
    } else {
        layoutWrapper = CreateLayoutWrapperOnCreate();
    }
    auto task = [layoutWrapper, layoutConstraint = GetLayoutConstraint(), offset = GetParentGlobalOffset(),
                    forceUseMainThread]() {
        ACE_SCOPED_TRACE("FrameNode::LayoutTask");
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
    ACE_SCOPED_TRACE("prepare render task");
    LOGD("create ui render task");
    auto wrapper = CreateRenderWrapper();
    auto task = [wrapper]() {
        ACE_SCOPED_TRACE("FrameNode::RenderTask");
        wrapper->FlushRender();
    };
    if (forceUseMainThread || wrapper->CheckShouldRunOnMain()) {
        return UITask(std::move(task), MAIN_TASK);
    }
    return UITask(std::move(task), wrapper->CanRunOnWhichThread());
}

std::optional<LayoutConstraintF> FrameNode::GetLayoutConstraint() const
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, std::nullopt);
    ScaleProperty scaleProperty = { pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale() };
    if (geometryNode_->GetParentLayoutConstraint().has_value()) {
        LayoutConstraintF LayoutConstraint = geometryNode_->GetParentLayoutConstraint().value();
        LayoutConstraint.scaleProperty = scaleProperty;
        return LayoutConstraint;
    }
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.scaleProperty = scaleProperty;
    return LayoutConstraint;
}

std::optional<OffsetF> FrameNode::GetParentGlobalOffset() const
{
    auto parent = parent_.Upgrade();
    CHECK_NULL_RETURN(parent, std::nullopt);
    return parent->geometryNode_->GetParentGlobalOffset();
}

void FrameNode::UpdateLayoutPropertyFlag()
{
    // TODO: reduce the loop by PROPERTY_UPDATE_BY_CHILD_REQUEST flag.
    auto flag = PROPERTY_UPDATE_NORMAL;
    for (const auto& child : children_) {
        child->UpdateLayoutPropertyFlag();
        flag = flag | child->layoutProperty_->GetPropertyChangeFlag();
    }
    if ((flag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    if ((flag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    }
    layoutProperty_->AdjustPropertyChangeFlagByChild(flag);
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapperOnCreate()
{
    isLayoutDirtyMarked_ = false;
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
    for (const auto& child : children_) {
        layoutWrapper->AddChild(child->CreateLayoutWrapperOnCreate());
    }
    layoutProperty_->CleanDirty();
    return layoutWrapper;
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    isLayoutDirtyMarked_ = false;
    auto flag = layoutProperty_->GetPropertyChangeFlag();
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    do {
        if (CheckMeasureFlag(flag) || CheckRequestNewChildNodeFlag(flag) || forceMeasure) {
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
    layoutProperty_->CleanDirty();
    return layoutWrapper;
}

void FrameNode::UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self, bool forceMeasure, bool forceLayout)
{
    for (const auto& child : children_) {
        self->AddChild(child->CreateLayoutWrapper(forceMeasure, forceLayout));
    }
}

RefPtr<RenderWrapper> FrameNode::CreateRenderWrapper()
{
    isRenderDirtyMarked_ = false;
    auto renderWrapper = MakeRefPtr<RenderWrapper>(renderContext_, geometryNode_->Clone(), renderProperty_->Clone());
    renderWrapper->SetContentPaintImpl(pattern_->CreateContentPaintImpl());
    renderProperty_->CleanDirty();
    return renderWrapper;
}

void FrameNode::PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->PostAsyncEvent(std::move(task), taskType);
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
    layoutProperty_->UpdateCalcLayoutProperty(calcLayoutConstraint);
}

void FrameNode::RebuildRenderContextTree()
{
    LOGD("%{public}s rebuild render context tree", GetTag().c_str());
    renderContext_->RebuildFrame(this);
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    MarkDirtyNode(IsMeasureBoundary(), IsRenderBoundary(), extraFlag);
}

void FrameNode::MarkDirtyNode(bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag)
{
    layoutProperty_->UpdatePropertyChangeFlag(extraFlag);
    renderProperty_->UpdatePropertyChangeFlag(extraFlag);
    auto flag = layoutProperty_->GetPropertyChangeFlag() | renderProperty_->GetPropertyChangeFlag();
    if (CheckNoChanged(flag)) {
        return;
    }
    if (CheckNeedRequestMeasureAndLayout(flag)) {
        if (isLayoutDirtyMarked_) {
            return;
        }
        isLayoutDirtyMarked_ = true;
        if (!isMeasureBoundary && CheckNeedRequestParent(flag)) {
            auto parent = parent_.Upgrade();
            if (parent) {
                parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
            }
            return;
        }
        UITaskScheduler::GetInstance()->AddDirtyLayoutNode(Claim(this));
        return;
    }
    layoutProperty_->CleanDirty();
    // If has dirtyLayoutBox, need to mark dirty after layout done.
    if (isRenderDirtyMarked_ || isLayoutDirtyMarked_) {
        return;
    }
    isRenderDirtyMarked_ = true;
    if (isRenderBoundary) {
        UITaskScheduler::GetInstance()->AddDirtyRenderNode(Claim(this));
        return;
    }
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
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

bool FrameNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    const auto& rect = geometryNode_->GetFrame().GetRect();
    LOGD("TouchTest: type is %{public}s, the region is %{public}s", GetTag().c_str(), rect.ToString().c_str());

    if (!rect.IsInRegion(parentLocalPoint)) {
        return false;
    }
    bool preventBubbling = false;
    const auto localPoint = parentLocalPoint - geometryNode_->GetFrameOffset();
    for (auto iter = children_.rbegin(); iter != children_.rend(); ++iter) {
        auto& child = *iter;
        if (child->TouchTest(globalPoint, localPoint, touchRestrict, result)) {
            preventBubbling = true;
            break;
        }
    }
    if (preventBubbling) {
        return true;
    }
    auto gestureHub = eventHub_->GetGestureEventHub();
    if (gestureHub) {
        const auto coordinateOffset = globalPoint - localPoint;
        return gestureHub->OnTouchTestHit(coordinateOffset, touchRestrict, result);
    }
    return false;
}
} // namespace OHOS::Ace::NG
