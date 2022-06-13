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
FrameNode::FrameNode(const std::string& tag, const std::string& id, const RefPtr<Pattern>& pattern, bool isRoot)
    : tag_(tag), id_(id), pattern_(pattern), isRoot_(isRoot)
{
    renderContext_->InitContext(isRoot_);
    renderProperty_ = pattern->CreateRenderProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
}

FrameNode::~FrameNode()
{
    pattern_->DetachFromFrameNode();
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeAndMounToParent(const std::string& tag, const std::string& id,
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
    newChild->AttachContextrecursively(context);
    newChild->SetSlot(0);
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
    child->SetSlot(std::distance(children_.begin(), result));
    needSyncRenderTree_ = true;
}

void FrameNode::RemoveChild(const RefPtr<FrameNode>& child)
{
    if (!child) {
        return;
    }
    children_.remove(child);
    needSyncRenderTree_ = true;
}

RefPtr<FrameNode> FrameNode::GetChildBySlot(int32_t slot)
{
    for (auto& iter : children_) {
        if (slot == iter->GetSlot()) {
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
    AttachContextrecursively(parent != nullptr ? parent->context_.Upgrade() : nullptr);
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

void FrameNode::AttachContextrecursively(const RefPtr<PipelineContext>& context)
{
    if (!context) {
        return;
    }
    SetPipelineContext(context);
    for (auto& child : children_) {
        child->AttachContextrecursively(context);
    }
}

void FrameNode::MovePosition(int32_t slot)
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
    if (needSyncRenderTree_) {
        RebuildRenderContextTree();
        needSyncRenderTree_ = false;
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

std::shared_ptr<LayoutTask> FrameNode::CreateLayoutTask(bool onCreate)
{
    RefPtr<LayoutWrapper> layoutWrapper;
    if (!onCreate) {
        UpdateLayoutPropertyFlag();
        layoutWrapper = CreateLayoutWrapper();
    } else {
        layoutWrapper = CreateLayoutWrapperOnCreate();
    }
    auto task = [layoutWrapper, layoutConstraint = GetLayoutConstraint(), offset = GetParentGlobalOffset(),
                    onCreate]() {
        layoutWrapper->Measure(layoutConstraint);
        layoutWrapper->Layout(offset);
        if (!onCreate) {
            layoutWrapper->MountToHostOnUiThread();
            return;
        }
        auto host = layoutWrapper->GetHostNode();
        if (!host) {
            LOGE("the host is nullptr");
            return;
        }
        host->PostUiTask([layoutWrapper]() { layoutWrapper->MountToHostOnUiThread(); });
    };
    isLayouting_.store(true);
    return std::make_shared<LayoutTask>(std::move(task));
}

std::shared_ptr<LayoutTask> FrameNode::CreateRenderTask()
{
    LOGD("create ui render task");
    auto wrapper = CreateRenderWrapper();
    auto task = [wrapper]() { wrapper->FlushRender(); };
    return std::make_shared<LayoutTask>(std::move(task));
}

std::optional<LayoutConstraintF> FrameNode::GetLayoutConstraint() const
{
    auto pipeline = GetContext();
    if (!pipeline) {
        LOGE("the pipeline is nullptr");
        return std::nullopt;
    }
    auto parent = parent_.Upgrade();
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
    auto parent = parent_.Upgrade();
    if (!parent) {
        return std::nullopt;
    }
    return parent->geometryNode_->GetParentGlobalOffset();
}

void FrameNode::UpdateLayoutPropertyFlag()
{
    // TODO: reduce the loop by PROPERTY_UPDATE_CHILD_REQUEST flag.
    auto flag = PROPERTY_UPDATE_NORMAL;
    for (const auto& child : children_) {
        child->UpdateLayoutPropertyFlag();
        flag = flag | child->layoutProperty_->GetPropertyChangeFlag();
    }
    if (((flag & PROPERTY_UPDATE_MEASURE) == PROPERTY_UPDATE_MEASURE) &&
        (layoutProperty_->GetMeasureType() == MeasureType::MATCH_CONTENT)) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    if ((flag & PROPERTY_UPDATE_POSITION) == PROPERTY_UPDATE_POSITION) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    }
    layoutProperty_->AjdustPropertyChangeFlagByChild(flag);
}

RefPtr<LayoutWrapper> FrameNode::CreateLayoutWrapperOnCreate()
{
    isLayoutDirtyMarked_ = false;
    auto layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_);
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
    RefPtr<LayoutWrapper> layoutWrapper;
    if (CheckMeasureFlag(flag) || CheckTreeChangedFlag(flag) || forceMeasure) {
        layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
        UpdateChildrenLayoutWrapper(layoutWrapper);
    } else if (CheckLayoutFlag(flag) || forceLayout) {
        layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
        layoutWrapper->SetLayoutAlgorithm(
            MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm(), true, false));
        UpdateChildrenLayoutWrapper(layoutWrapper);
    } else {
        layoutWrapper = MakeRefPtr<LayoutWrapper>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_);
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(nullptr, true, true));
    }
    layoutProperty_->CleanDirty();
    return layoutWrapper;
}

void FrameNode::UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapper>& self)
{
    for (const auto& child : children_) {
        self->AddChild(child->CreateLayoutWrapper(!self->GetLayoutAlgorithm()->SkipMeasure()));
    }
}

RefPtr<RenderWrapper> FrameNode::CreateRenderWrapper()
{
    isRenderDirtyMarked_ = false;
    auto renderWrapper = MakeRefPtr<RenderWrapper>(renderContext_, geometryNode_, renderProperty_->Clone());
    renderWrapper->SetContentPaintImpl(pattern_->CreateContentPaintImpl());
    renderProperty_->CleanDirty();
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
    if ((!isMeasureBoundary && CheckNeedParentLayout(flag)) || (isMeasureBoundary && CheckNeedLayoutSelf(flag))) {
        if (isLayoutDirtyMarked_) {
            LOGD("already mark dirty");
            return;
        }
        isLayoutDirtyMarked_ = true;
        if (isMeasureBoundary) {
            UiTaskScheduler::GetInstance()->AddDirtyLayoutNode(Claim(this));
            return;
        }
        auto parent = parent_.Upgrade();
        if (parent) {
            parent->MarkDirtyNode(PROPERTY_UPDATE_CHILD_REQUEST);
        }
        return;
    }
    // If has dirtyLayoutBox, need to mark dirty after layout done.
    if (isRenderDirtyMarked_ || isLayoutDirtyMarked_) {
        return;
    }
    isRenderDirtyMarked_ = true;
    if (isRenderBoundary) {
        UiTaskScheduler::GetInstance()->AddDirtyRenderNode(Claim(this));
        return;
    }
    auto parent = parent_.Upgrade();
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_CHILD_REQUEST);
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
} // namespace OHOS::Ace::NG
