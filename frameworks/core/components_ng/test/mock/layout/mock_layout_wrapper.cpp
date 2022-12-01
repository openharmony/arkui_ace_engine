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

#define private public
#define protected public
#include <algorithm>

#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkPictureRecorder.h"

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/geometry/ng/offset_t.h"
#include "frameworks/base/geometry/ng/rect_t.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/core/components/common/properties/alignment.h"
#include "frameworks/core/components/common/properties/border_image_edge.h"
#include "frameworks/core/components/common/properties/decoration.h"
#include "frameworks/core/components_ng/base/geometry_node.h"
#include "frameworks/core/components_ng/base/modifier.h"
#include "frameworks/core/components_ng/layout/layout_wrapper.h"
#include "frameworks/core/components_ng/property/geometry_property.h"
#include "frameworks/core/components_ng/property/measure_property.h"
#include "frameworks/core/components_ng/render/adapter/rosen_render_context.h"
#include "frameworks/core/components_ng/render/adapter/skia_decoration_painter.h"
#include "frameworks/core/components_ng/render/adapter/svg_canvas_image.h"
#include "frameworks/core/components_ng/render/border_image_painter.h"
#include "frameworks/core/components_ng/render/canvas.h"
#include "frameworks/core/components_ng/render/render_context.h"
#include "frameworks/core/components_ng/test/mock/render/mock_render_context.h"
#undef private
#undef protected
namespace OHOS::Ace::NG {
namespace {
const double DOUBLE_NUMBER = 20.0;
}

RefPtr<LayoutWrapper> LayoutWrapper::GetOrCreateChildByIndex(int32_t index, bool addToRenderTree)
{
    OHOS::Ace::RefPtr<LayoutWrapper> rosenLayoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(nullptr, nullptr, nullptr);
    OHOS::Ace::RefPtr<GeometryNode> rosenGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    OHOS::Ace::NG::GeometryProperty rosenGeometryProperty;
    OHOS::Ace::NG::RectT rosenRectT(DOUBLE_NUMBER, DOUBLE_NUMBER, DOUBLE_NUMBER, DOUBLE_NUMBER);
    rosenGeometryNode->frame_ = rosenGeometryProperty;
    rosenGeometryNode->margin_ = nullptr;
    rosenLayoutWrapper->geometryNode_ = std::move(rosenGeometryNode);
    return rosenLayoutWrapper;
}

void LayoutWrapper::SetCacheCount(int32_t cacheCount)
{
    if (layoutWrapperBuilder_) {
        layoutWrapperBuilder_->SetCacheCount(cacheCount);
    }
}

const std::list<RefPtr<LayoutWrapper>>& LayoutWrapper::GetAllChildrenWithBuild(bool addToRenderTree)
{
    if (!cachedList_.empty()) {
        return cachedList_;
    }
    cachedList_ = children_;
    if (layoutWrapperBuilder_) {
        auto buildItems = layoutWrapperBuilder_->ExpandAllChildWrappers();
        auto index = layoutWrapperBuilder_->GetStartIndex();
        auto insertIter = cachedList_.begin();
        std::advance(insertIter, index);
        cachedList_.splice(insertIter, buildItems);
    }
    if (addToRenderTree) {
        for (const auto& child : cachedList_) {
            if (!child->isActive_) {
                child->isActive_ = true;
            }
        }
    }
    return cachedList_;
}

void LayoutWrapper::RemoveChildInRenderTree(const RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    wrapper->isActive_ = false;
}

void LayoutWrapper::RemoveChildInRenderTree(int32_t index)
{
    auto wrapper = GetOrCreateChildByIndex(index, false);
    CHECK_NULL_VOID(wrapper);
    wrapper->isActive_ = false;
}

void LayoutWrapper::RemoveAllChildInRenderTree()
{
    for (auto& child : childrenMap_) {
        child.second->isActive_ = false;
    }
    if (layoutWrapperBuilder_) {
        layoutWrapperBuilder_->RemoveAllChildInRenderTree();
    }
}

void LayoutWrapper::ResetHostNode()
{
    hostNode_.Reset();
}

RefPtr<FrameNode> LayoutWrapper::GetHostNode() const
{
    return hostNode_.Upgrade();
}

WeakPtr<FrameNode> LayoutWrapper::GetWeakHostNode() const
{
    return hostNode_;
}

std::string LayoutWrapper::GetHostTag() const
{
    auto host = GetHostNode();
    if (host) {
        return host->GetTag();
    }
    return "";
}

int32_t LayoutWrapper::GetHostDepth() const
{
    auto host = GetHostNode();
    if (host) {
        return host->GetDepth();
    }
    return -1;
}

// This will call child and self measure process.
void LayoutWrapper::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    auto host = GetHostNode();
    if (!layoutProperty_ || !geometryNode_ || !host) { return; }
    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipMeasure()) { return; }
    auto preConstraint = layoutProperty_->GetLayoutConstraint();
    auto contentConstraint = layoutProperty_->GetContentLayoutConstraint();
    layoutProperty_->BuildGridProperty(host);
    if (parentConstraint) {
        geometryNode_->SetParentLayoutConstraint(parentConstraint.value());
        layoutProperty_->UpdateLayoutConstraint(parentConstraint.value());
    } else {
        LayoutConstraintF layoutConstraint;
        layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
        layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
        layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    }
    layoutProperty_->UpdateContentConstraint();
    geometryNode_->UpdateMargin(layoutProperty_->CreateMargin());
    geometryNode_->UpdatePaddingWithBorder(layoutProperty_->CreatePaddingAndBorder());
    isConstraintNotChanged_ = preConstraint ? preConstraint == layoutProperty_->GetLayoutConstraint() : false;
    if (!isConstraintNotChanged_) {
        isConstraintNotChanged_ =
            contentConstraint ? contentConstraint == layoutProperty_->GetContentLayoutConstraint() : false;
    }
    if (isConstraintNotChanged_ && !skipMeasureContent_) {
        if (!CheckNeedForceMeasureAndLayout()) {
            skipMeasureContent_ = true;
        }
    }
    if (!skipMeasureContent_.value_or(false)) {
        skipMeasureContent_ = false;
        auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->CreateContentConstraint(), this);
        if (size.has_value()) {
            geometryNode_->SetContentSize(size.value());
        }
        layoutAlgorithm_->Measure(this);
        const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
        auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
        if (hasAspectRatio) {
            auto aspectRatio = magicItemProperty->GetAspectRatioValue();
            auto width = geometryNode_->GetFrameSize().Width();
            auto height = width / aspectRatio;
            geometryNode_->SetFrameSize( SizeF( { width, height } ));
        }
    }
}

// Called to perform layout children.
void LayoutWrapper::Layout()
{
    auto host = GetHostNode();
    if (!layoutProperty_ || !geometryNode_ || !host) {
        LOGE("Layout failed: the layoutProperty_ or geometryNode_ or host or frameNode is nullptr");
        return;
    }

    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipLayout()) {
        LOGD(
            "%{public}s, depth: %{public}d: the layoutAlgorithm skip layout", host->GetTag().c_str(), host->GetDepth());
        return;
    }

    LOGD("On Layout begin: type: %{public}s, depth: %{public}d", host->GetTag().c_str(), host->GetDepth());

    if ((skipMeasureContent_ == true)) {
        LOGD(
            "%{public}s (depth: %{public}d) skip measure content and layout", host->GetTag().c_str(), host->GetDepth());
        LOGD("On Layout Done: type: %{public}s, depth: %{public}d, Offset: %{public}s", host->GetTag().c_str(),
            host->GetDepth(), geometryNode_->GetFrameOffset().ToString().c_str());
        return;
    }

    if (!layoutProperty_->GetLayoutConstraint()) {
        const auto& parentLayoutConstraint = geometryNode_->GetParentLayoutConstraint();
        if (parentLayoutConstraint) {
            layoutProperty_->UpdateLayoutConstraint(parentLayoutConstraint.value());
        } else {
            LayoutConstraintF layoutConstraint;
            layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
            layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
            layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
        }
        layoutProperty_->UpdateContentConstraint();
    }
    layoutAlgorithm_->Layout(this);
    LOGD("On Layout Done: type: %{public}s, depth: %{public}d, Offset: %{public}s", host->GetTag().c_str(),
        host->GetDepth(), geometryNode_->GetFrameOffset().ToString().c_str());
}

bool LayoutWrapper::SkipMeasureContent() const
{
    return (skipMeasureContent_ == true) || layoutAlgorithm_->SkipMeasure();
}

bool LayoutWrapper::CheckNeedForceMeasureAndLayout()
{
    if (needForceMeasureAndLayout_) {
        return needForceMeasureAndLayout_.value();
    }
    PropertyChangeFlag flag = layoutProperty_->GetPropertyChangeFlag();
    // Need to remove layout flag when measure and layout make independent in each pattern layoutAlgorithm like
    // flex.
    bool needForceMeasureAndLayout = CheckNeedMeasure(flag) || CheckNeedLayout(flag);
    if (needForceMeasureAndLayout) {
        needForceMeasureAndLayout_ = true;
        return true;
    }
    // check child flag.
    needForceMeasureAndLayout_ = std::any_of(
        children_.begin(), children_.end(), [](const auto& item) { return item->CheckNeedForceMeasureAndLayout(); });
    return needForceMeasureAndLayout_.value();
}

bool LayoutWrapper::CheckChildNeedForceMeasureAndLayout()
{
    return std::any_of(
        children_.begin(), children_.end(), [](const auto& item) { return item->CheckNeedForceMeasureAndLayout(); });
}

void LayoutWrapper::MountToHostOnMainThread()
{
    SwapDirtyLayoutWrapperOnMainThread();
}

void LayoutWrapper::SwapDirtyLayoutWrapperOnMainThread()
{
    for (const auto& child : children_) {
        if (child) {
            child->SwapDirtyLayoutWrapperOnMainThread();
        }
    }

    if (layoutWrapperBuilder_) {
        layoutWrapperBuilder_->SwapDirtyAndUpdateBuildCache();
    }

    auto host = hostNode_.Upgrade();
    if (!host) {
        LOGE("the host is nullptr");
        return;
    }
    host->SwapDirtyLayoutWrapperOnMainThread(Claim(this));
}
} // namespace OHOS::Ace::NG
