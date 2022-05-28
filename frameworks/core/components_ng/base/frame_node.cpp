/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <atomic>
#include <memory>
#include <mutex>

#include "base/log/dump_log.h"
#include "base/memory/referenced.h"
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

FrameNode::FrameNode(const std::string& tag, const RefPtr<Pattern>& pattern, bool isRoot)
    : ElementNode(tag), pattern_(pattern)
{
    type_ = ElementType::RENDER_ELEMENT;
    renderContext_->InitContext(isRoot);
    renderProperty_ = pattern->CreateRenderProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
}

FrameNode::~FrameNode()
{
    pattern_->DetachFromFrameNode();
    Unmount();
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeAndMounToParent(
    const std::string& tag, const RefPtr<Pattern>& pattern, const RefPtr<ElementNode>& parent, int32_t slot)
{
    auto newChild = CreateFrameNode(tag, pattern);
    newChild->MountToParent(parent, slot);
    return newChild;
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(
    const std::string& tag, const RefPtr<Pattern>& pattern, const RefPtr<PipelineContext>& context)
{
    auto newChild = CreateFrameNode(tag, pattern, true);
    newChild->SetDepth(1);
    newChild->SetPipelineContext(context);
    newChild->SetFrameSlot(0);
    newChild->OnMounted();
    return newChild;
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(const std::string& tag, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, pattern, isRoot);
    frameNode->pattern_->AttachToFrameNode(frameNode);
    frameNode->renderContext_->SetRequestFrame([weak = WeakPtr<FrameNode>(frameNode)] {
        auto frameNode = weak.Upgrade();
        if (frameNode) {
            frameNode->RequestNextFrame();
        }
    });
    return frameNode;
}

void FrameNode::OnChildAdded(const RefPtr<ElementNode>& child)
{
    if (!child) {
        LOGE("ElementNode child is null");
        return;
    }

    if (child->GetType() == ElementType::RENDER_ELEMENT) {
        // Directly attach the FrameNode if child is FrameNode.
        auto frameNode = AceType::DynamicCast<FrameNode>(child);
        AddFrameChild(frameNode, frameNode->GetFrameSlot());
    }
}

void FrameNode::AddFrameChild(const RefPtr<FrameNode>& child, int32_t slot)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    auto it = std::find(frameChildren_.begin(), frameChildren_.end(), child);
    if (it != frameChildren_.end()) {
        LOGW("frame node exist AddChild failed");
        return;
    }

    auto pos = frameChildren_.begin();
    std::advance(pos, slot);
    auto iter = frameChildren_.insert(pos, child);
    auto distance = std::distance(frameChildren_.begin(), iter);
    child->SetFrameSlot(distance);
    child->SetFrameParent(WeakClaim(this));
    child->SetDepth(GetDepth() + 1);
    MarkDirtyLayoutBox(PROPERTY_UPDATE_NODE_TREE);
}

void FrameNode::RemoveFrameChild(const RefPtr<FrameNode>& child)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    // ClearChildren() before RemoveChild() also need to NotifyTransition().
    if (!frameChildren_.empty()) {
        auto it = std::find(frameChildren_.begin(), frameChildren_.end(), child);
        if (it == frameChildren_.end()) {
            LOGW("Child is not in  render node");
            return;
        }
        frameChildren_.erase(it);
        MarkDirtyLayoutBox(PROPERTY_UPDATE_NODE_TREE);
    }
    LOGD("FrameNode RemoveFrameChild %{public}zu", frameChildren_.size());
}

void FrameNode::MoveFramePosition(int32_t slot)
{
    auto parentNode = GetFrameParent().Upgrade();
    if (!parentNode) {
        LOGW("Invalid parent");
        return;
    }

    auto self = AceType::Claim(this);
    auto& children = parentNode->frameChildren_;
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
    parentNode->MarkDirtyLayoutBox(PROPERTY_UPDATE_NODE_TREE);
}

void FrameNode::ClearFrameChildren()
{
    frameChildren_.clear();
    MarkDirtyLayoutBox(PROPERTY_UPDATE_NODE_TREE);
}

void FrameNode::OnContextAttached()
{
    pattern_->OnContextAttached();
    auto context = context_.Upgrade();
    if (context && hasPendingRequest_) {
        context->RequestFrame();
        hasPendingRequest_ = false;
    }
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

void FrameNode::OnDepthUpdate() {}

void FrameNode::FlushModifyTask(StateModifyTask& stateModifyTask)
{
    if (!stateModifyTask.GetLayoutTask().empty()) {
        for (auto&& task : stateModifyTask.GetLayoutTask()) {
            task.FlushModify(RawPtr(layoutProperty_));
        }
    }
    MarkDirtyLayoutBox();
    if (!stateModifyTask.GetRenderTask().empty()) {
        for (auto&& task : stateModifyTask.GetRenderTask()) {
            task.FlushModify(RawPtr(renderProperty_));
        }
    }
    MarkDirtyRender();
    auto task = [contextTask = stateModifyTask.MoveRenderContext(),
                    renderContext = WeakPtr<RenderContext>(renderContext_)]() {
        auto context = renderContext.Upgrade();
        if (context) {
            for (auto&& task : contextTask) {
                task.FlushModify(RawPtr(context));
            }
        }
    };
    PostUiTask(std::move(task));
}

void FrameNode::SwapDirtyLayoutWrapperFromUiThread(const RefPtr<LayoutWrapper>& dirty)
{
    LOGD("SwapDirtyLayoutWrapperFromUiThread, %{public}s", GetTag().c_str());
    isLayouting_.store(false);
    if (!dirty) {
        LOGE("dirty node is nullptr");
        return;
    }
    if (isLayoutDirtyMarked_ || isLayouting_.load(std::memory_order_relaxed)) {
        LOGW("fail to swap due to current node is layouting");
        return;
    }
    pattern_->OnDirtyLayoutWrapperSwap(dirty);
    if (geometryNode_->CheckUnchanged(*(dirty->GetGeometryNode()))) {
        return;
    }
    SetGeometryNode(dirty->MoveGeometryNode());
    LOGD("%{public}s frameNode sync geometry, %{public}s", GetTag().c_str(),
        geometryNode_->GetFrame().ToString().c_str());
    renderContext_->SyncGeometryProperties(RawPtr(geometryNode_));
    UiTaskScheduler::GetInstance()->AddDirtyRenderNodeInUiThread(Claim(this));
}

std::shared_ptr<UiLayoutTask> FrameNode::CreateUiLayoutTask()
{
    UpdateLayoutPropertyFlag();
    auto layoutWrapper = CreateLayoutWrapper();
    auto task = [layoutWrapper, layoutConstraint = GetLayoutConstraint(), offset = GetParentGlobalOffset()]() {
        layoutWrapper->Measure(layoutConstraint);
        layoutWrapper->Layout(offset);
        layoutWrapper->MountToHostOnUiThread();
    };
    layoutProperty_->CleanDirty();
    isLayouting_.store(true);
    return std::make_shared<UiLayoutTask>(std::move(task));
}

std::shared_ptr<UiLayoutTask> FrameNode::CreateUiRenderTask()
{
    LOGD("create ui render task");
    auto wrapper = CreateRenderWrapper();
    auto task = [wrapper]() { wrapper->FlushRender(); };
    return std::make_shared<UiLayoutTask>(std::move(task));
}

std::optional<LayoutConstraintF> FrameNode::GetLayoutConstraint() const
{
    auto pipeline = GetContext().Upgrade();
    if (!pipeline) {
        LOGE("the pipeline is nullptr");
        return std::nullopt;
    }
    auto parent = frameParent_.Upgrade();
    if (!parent) {
        ScaleProperty scaleProperty = { pipeline->GetDipScale(), pipeline->GetFontScale(), pipeline->GetLogicScale() };
        LayoutConstraintF layoutConstraintF;
        layoutConstraintF.scaleProperty = scaleProperty;
        return layoutConstraintF;
    }
    return parent->layoutProperty_->GetContentLayoutConstraint();
}

std::optional<OffsetF> FrameNode::GetParentGlobalOffset() const
{
    auto parent = frameParent_.Upgrade();
    if (!parent) {
        return std::nullopt;
    }
    return parent->geometryNode_->GetParentGlobalOffset();
}

void FrameNode::UpdateLayoutPropertyFlag()
{
    // TODO: reduce the loop by PROPERTY_UPDATE_CHILD_REQUEST flag.
    auto flag = PROPERTY_UPDATE_NORMAL;
    for (const auto& child : frameChildren_) {
        child->UpdateLayoutPropertyFlag();
        flag = flag | child->layoutProperty_->GetPropertyChangeFlag();
    }
    if (((flag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) &&
        (layoutProperty_->GetMeasureType() == MeasureType::WRAP_CONTENT)) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    if ((flag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    }
    layoutProperty_->AjdustPropertyChangeFlagByChild(flag);
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    isLayoutDirtyMarked_ = false;
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_);
    auto flag = layoutProperty_->GetPropertyChangeFlag();
    if (CheckMeasureFlag(flag) || CheckTreeChangedFlag(flag) || forceMeasure) {
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
        UpdateChildrenLayoutWrapper(layoutWrapper);
    } else if (CheckLayoutFlag(flag) || forceLayout) {
        layoutWrapper->SetLayoutAlgorithm(
            MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm(), true, false));
        UpdateChildrenLayoutWrapper(layoutWrapper);
    } else {
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(nullptr, true, true));
    }
    if (CheckNodeTreeFlag(layoutProperty_->GetPropertyChangeFlag())) {
        PostUiTask([context = context_, node = WeakClaim(this)]() {
            auto sptr = context.Upgrade();
            if (sptr) {
                sptr->AddDirtyRenderTree(node.Upgrade());
            }
        });
    }
    return layoutWrapper;
}

void FrameNode::UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self)
{
    for (const auto& child : frameChildren_) {
        self->AddChild(child->CreateLayoutWrapper(!self->GetLayoutAlgorithm()->SkipMeasure()));
    }
}

RefPtr<RenderWrapper> FrameNode::CreateRenderWrapper()
{
    isRenderDirtyMarked_ = false;
    auto renderWrapper = MakeRefPtr<RenderWrapper>(renderContext_, geometryNode_, renderProperty_->Clone());
    renderWrapper->SetContentPaintImpl(pattern_->CreateContentPaintImpl());
    return renderWrapper;
}

void FrameNode::PostUiTask(std::function<void()>&& task)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to post ui task due to context is null");
        return;
    }
    context->PostAsyncEvent(std::move(task));
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
    layoutProperty_->UpdateCalcLayoutProperty(calcLayoutConstraint);
    MarkDirtyLayoutBox();
}

void FrameNode::RebuildRenderContextTree()
{
    LOGD("%{public}s rebuild render context tree", GetTag().c_str());
    renderContext_->RebuildFrame(this);
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

void FrameNode::MarkDirtyLayoutBox(PropertyChangeFlag propertyChangeFlag)
{
    MarkDirtyLayoutBox(IsMeasureBoundary(), propertyChangeFlag);
}

void FrameNode::MarkDirtyLayoutBox(bool selfOnly, PropertyChangeFlag propertyChangeFlag)
{
    layoutProperty_->UpdatePropertyChangeFlag(propertyChangeFlag);
    if (isLayoutDirtyMarked_) {
        LOGD("already mark dirty");
        return;
    }
    auto flag = layoutProperty_->GetPropertyChangeFlag();
    if ((selfOnly && !CheckNeedLayoutSelf(flag)) && (!selfOnly && !CheckNeedParentLayout(flag))) {
        LOGD("layoutProperty not changed");
        return;
    }
    isLayoutDirtyMarked_ = true;
    if (selfOnly) {
        UiTaskScheduler::GetInstance()->AddDirtyLayoutNode(Claim(this));
        return;
    }
    auto parent = frameParent_.Upgrade();
    if (parent) {
        parent->MarkDirtyLayoutBox(PROPERTY_UPDATE_CHILD_REQUEST);
    }
}

void FrameNode::MarkDirtyRender(bool forceParent)
{
    if (isRenderDirtyMarked_) {
        return;
    }
    // If has dirtyLayoutBox, need to mark dirty after layout done.
    if (isLayoutDirtyMarked_) {
        return;
    }
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("fail to post ui task due to context is null");
        return;
    }
    isRenderDirtyMarked_ = true;
    UiTaskScheduler::GetInstance()->AddDirtyRenderNode(Claim(this));
    if (forceParent) {
        auto parent = frameParent_.Upgrade();
        if (parent) {
            parent->MarkDirtyRender(false);
        }
    }
}

bool FrameNode::IsMeasureBoundary()
{
    return isMeasureBoundary_ || pattern_->IsMeasureBoundary();
}

const RefPtr<Pattern>& FrameNode::GetPattern() const
{
    return pattern_;
}

} // namespace OHOS::Ace::NG
