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

#include "core/components_ng/layout/layout_wrapper.h"

#include <algorithm>

#include "base/geometry/dimension.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_trace.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool LayoutWrapper::SkipMeasureContent() const
{
    return skipMeasureContent_ == true;
}

void LayoutWrapper::ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint)
{
    SizeF safeSize { PipelineContext::GetCurrentRootWidth(), PipelineContext::GetCurrentRootHeight() };
    safeSize.MinusPadding(insets.left_.Length(), insets.right_.Length(), insets.top_.Length(), insets.bottom_.Length());
    if (safeSize.Width() < constraint.maxSize.Width() || safeSize.Height() < constraint.maxSize.Height()) {
        safeSize.SetWidth(std::min(safeSize.Width(), constraint.maxSize.Width()));
        safeSize.SetHeight(std::min(safeSize.Height(), constraint.maxSize.Height()));
        constraint.maxSize = safeSize;
        constraint.parentIdealSize = OptionalSizeF(safeSize);
        constraint.percentReference = safeSize;
    }
    if (safeSize < constraint.minSize) {
        constraint.minSize = safeSize;
    }
}

void LayoutWrapper::OffsetNodeToSafeArea()
{
    auto&& insets = GetLayoutProperty()->GetSafeAreaInsets();
    CHECK_NULL_VOID_NOLOG(insets);
    auto geometryNode = GetGeometryNode();
    auto offset = geometryNode->GetMarginFrameOffset();
    if (offset.GetX() < insets->left_.end) {
        offset.SetX(insets->left_.end);
    }
    if (offset.GetY() < insets->top_.end) {
        offset.SetY(insets->top_.end);
    }

    auto right = offset.GetX() + geometryNode->GetMarginFrameSize().Width();
    if (insets->right_.IsValid() && right > insets->right_.start) {
        offset.SetX(insets->right_.start - geometryNode->GetMarginFrameSize().Width());
    }
    auto bottom = offset.GetY() + geometryNode->GetMarginFrameSize().Height();
    if (insets->bottom_.IsValid() && bottom > insets->bottom_.start) {
        offset.SetY(insets->bottom_.start - geometryNode->GetMarginFrameSize().Height());
    }
    geometryNode->SetMarginFrameOffset(offset);
}

void LayoutWrapper::RestoreGeoState()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    auto&& restoreNodes = manager->GetGeoRestoreNodes();
    if (restoreNodes.find(hostNode_) != restoreNodes.end()) {
        GetGeometryNode()->Restore();
        manager->RemoveRestoreNode(hostNode_);
    }
}

void LayoutWrapper::AvoidKeyboard()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();

    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (!wrapper) {
            continue;
        }
        auto host = wrapper->GetHostNode();
        // apply keyboard avoidance on Page
        if (host && host->GetTag() == V2::PAGE_ETS_TAG) {
            wrapper->GetGeometryNode()->SetFrameOffset(
                wrapper->GetGeometryNode()->GetFrameOffset() + OffsetF(0, manager->GetKeyboardOffset()));
        }
    }
}

void LayoutWrapper::ExpandSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();

    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (wrapper && wrapper->GetLayoutProperty()->GetSafeAreaExpandOpts()) {
            wrapper->ExpandSafeAreaInner();
        }
    }

    manager->ResetWrappers();
}

void LayoutWrapper::SaveGeoState()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    // save geometry state before SafeArea expansion / keyboard avoidance.
    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (wrapper) {
            wrapper->GetGeometryNode()->Save();

            // record nodes whose geometry states need to be restored, to speed up RestoreGeoState
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            manager->AddGeoRestoreNode(wrapper->hostNode_);
        }
    }
}

void LayoutWrapper::ExpandSafeAreaInner()
{
    // children of Scrollable nodes don't support expandSafeArea
    auto host = GetHostNode();
    CHECK_NULL_VOID(host);
    auto parent = host->GetAncestorNodeOfFrame();
    if (parent && parent->GetPattern<ScrollablePattern>()) {
        return;
    }

    auto&& opts = GetLayoutProperty()->GetSafeAreaExpandOpts();
    CHECK_NULL_VOID_NOLOG(opts->Expansive());

    if ((opts->edges & SAFE_AREA_EDGE_BOTTOM) && (opts->type & SAFE_AREA_TYPE_KEYBOARD)) {
        ExpandIntoKeyboard();
    }

    if (!(opts->type & SAFE_AREA_TYPE_SYSTEM) && !(opts->type & SAFE_AREA_TYPE_CUTOUT)) {
        return;
    }
    // expand System and Cutout safeArea
    // get frame in global offset
    auto parentGlobalOffset = host->GetParentGlobalOffsetDuringLayout();
    auto geometryNode = GetGeometryNode();
    auto frame = geometryNode->GetFrameRect() + parentGlobalOffset;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto safeArea = pipeline->GetSafeAreaManager()->GetCombinedSafeArea(*opts);
    if ((opts->edges & SAFE_AREA_EDGE_START) && safeArea.left_.IsValid() && frame.Left() <= safeArea.left_.end) {
        frame.SetWidth(frame.Width() + frame.Left() - safeArea.left_.start);
        frame.SetLeft(safeArea.left_.start);
    }
    if ((opts->edges & SAFE_AREA_EDGE_TOP) && safeArea.top_.IsValid() && frame.Top() <= safeArea.top_.end) {
        frame.SetHeight(frame.Height() + frame.Top() - safeArea.top_.start);
        frame.SetTop(safeArea.top_.start);
    }

    if ((opts->edges & SAFE_AREA_EDGE_END) && safeArea.right_.IsValid() && frame.Right() >= safeArea.right_.start) {
        frame.SetWidth(frame.Width() + (safeArea.right_.end - frame.Right()));
    }
    if ((opts->edges & SAFE_AREA_EDGE_BOTTOM) && safeArea.bottom_.IsValid() &&
        frame.Bottom() >= safeArea.bottom_.start) {
        frame.SetHeight(frame.Height() + (safeArea.bottom_.end - frame.Bottom()));
    }

    // reset if User has fixed size
    auto layoutProperty = GetLayoutProperty();
    if (layoutProperty->HasFixedWidth()) {
        frame.SetWidth(geometryNode->GetFrameRect().Width());
    }
    if (layoutProperty->HasFixedHeight()) {
        frame.SetHeight(geometryNode->GetFrameRect().Height());
    }
    if (layoutProperty->HasAspectRatio()) {
        frame.SetHeight(frame.Width() / layoutProperty->GetAspectRatio());
    }

    // restore to local offset
    frame -= parentGlobalOffset;
    geometryNode->SetFrameOffset(frame.GetOffset());
    geometryNode->SetFrameSize(frame.GetSize());
}

void LayoutWrapper::ExpandIntoKeyboard()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto geometryNode = GetGeometryNode();
    geometryNode->SetFrameOffset(
        geometryNode->GetFrameOffset() - OffsetF(0, pipeline->GetSafeAreaManager()->GetKeyboardOffset()));
}

void LayoutWrapper::ApplyConstraint(LayoutConstraintF constraint)
{
    auto layoutProperty = GetLayoutProperty();
    const auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    if (magicItemProperty && magicItemProperty->HasAspectRatio()) {
        std::optional<CalcSize> idealSize = std::nullopt;
        if (layoutProperty->GetCalcLayoutConstraint()) {
            idealSize = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
        }
        constraint.ApplyAspectRatio(magicItemProperty->GetAspectRatioValue(), idealSize);
    }

    auto&& insets = layoutProperty->GetSafeAreaInsets();
    if (insets) {
        ApplySafeArea(*insets, constraint);
    }

    GetGeometryNode()->SetParentLayoutConstraint(constraint);
    layoutProperty->UpdateLayoutConstraint(constraint);
}

void LayoutWrapper::CreateRootConstraint()
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
    auto layoutProperty = GetLayoutProperty();
    const auto& magicItemProperty = layoutProperty->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty && magicItemProperty->HasAspectRatio();
    if (hasAspectRatio) {
        auto aspectRatio = magicItemProperty->GetAspectRatioValue();
        if (Positive(aspectRatio)) {
            auto height = PipelineContext::GetCurrentRootHeight() / aspectRatio;
            layoutConstraint.percentReference.SetHeight(height);
        }
    } else {
        layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
    }
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
}

RefPtr<FrameNode> LayoutWrapper::GetHostNode() const
{
    return hostNode_.Upgrade();
}

void LayoutWrapper::AddNodeFlexLayouts()
{
    if (!AceChecker::IsPerformanceCheckEnabled()) {
        return;
    }
    auto host = GetHostNode();
    CHECK_NULL_VOID(host);
    auto frameNodeParent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(frameNodeParent);
    if (frameNodeParent->GetTag() == V2::FLEX_ETS_TAG) {
        auto parent = host->GetParent();
        CHECK_NULL_VOID(parent);
        if (parent->GetTag() == V2::JS_VIEW_ETS_TAG) {
            parent->AddFlexLayouts();
        } else if (host->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            auto children = host->GetChildren();
            if (!children.empty()) {
                auto begin = children.begin();
                (*begin)->AddFlexLayouts();
            }
        } else {
            host->AddFlexLayouts();
        }
    }
}

void LayoutWrapper::AddNodeLayoutTime(int64_t time)
{
    if (!AceChecker::IsPerformanceCheckEnabled()) {
        return;
    }
    auto host = GetHostNode();
    CHECK_NULL_VOID(host);
    host->SetLayoutTime(time);
}

} // namespace OHOS::Ace::NG
