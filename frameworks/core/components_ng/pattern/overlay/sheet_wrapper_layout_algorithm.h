/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_LAYOUT_ALGORITHM_H

#include "core/common/container.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SheetWrapperLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SheetWrapperLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    SheetWrapperLayoutAlgorithm()
    {
        placementCheckFunc_[Placement::BOTTOM] = &SheetWrapperLayoutAlgorithm::CheckPlacementBottom;
        placementCheckFunc_[Placement::BOTTOM_LEFT] = &SheetWrapperLayoutAlgorithm::CheckPlacementBottomLeft;
        placementCheckFunc_[Placement::BOTTOM_RIGHT] = &SheetWrapperLayoutAlgorithm::CheckPlacementBottomRight;

        directionCheckFunc_[Placement::BOTTOM] = &SheetWrapperLayoutAlgorithm::CheckDirectionBottom;
        directionCheckFunc_[Placement::BOTTOM_LEFT] = &SheetWrapperLayoutAlgorithm::CheckDirectionBottom;
        directionCheckFunc_[Placement::BOTTOM_RIGHT] = &SheetWrapperLayoutAlgorithm::CheckDirectionBottom;
        directionCheckFunc_[Placement::TOP] = &SheetWrapperLayoutAlgorithm::CheckDirectionTop;
        directionCheckFunc_[Placement::TOP_LEFT] = &SheetWrapperLayoutAlgorithm::CheckDirectionTop;
        directionCheckFunc_[Placement::TOP_RIGHT] = &SheetWrapperLayoutAlgorithm::CheckDirectionTop;
        directionCheckFunc_[Placement::LEFT] = &SheetWrapperLayoutAlgorithm::CheckDirectionLeft;
        directionCheckFunc_[Placement::LEFT_TOP] = &SheetWrapperLayoutAlgorithm::CheckDirectionLeft;
        directionCheckFunc_[Placement::LEFT_BOTTOM] = &SheetWrapperLayoutAlgorithm::CheckDirectionLeft;
        directionCheckFunc_[Placement::RIGHT] = &SheetWrapperLayoutAlgorithm::CheckDirectionRight;
        directionCheckFunc_[Placement::RIGHT_TOP] = &SheetWrapperLayoutAlgorithm::CheckDirectionRight;
        directionCheckFunc_[Placement::RIGHT_BOTTOM] = &SheetWrapperLayoutAlgorithm::CheckDirectionRight;

        getOffsetFunc_[Placement::BOTTOM] = &SheetWrapperLayoutAlgorithm::GetOffsetWithBottom;
        getOffsetFunc_[Placement::BOTTOM_LEFT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithBottomLeft;
        getOffsetFunc_[Placement::BOTTOM_RIGHT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithBottomRight;
        getOffsetFunc_[Placement::TOP] = &SheetWrapperLayoutAlgorithm::GetOffsetWithTop;
        getOffsetFunc_[Placement::TOP_LEFT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithTopLeft;
        getOffsetFunc_[Placement::TOP_RIGHT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithTopRight;
        getOffsetFunc_[Placement::LEFT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithLeft;
        getOffsetFunc_[Placement::LEFT_TOP] = &SheetWrapperLayoutAlgorithm::GetOffsetWithLeftTop;
        getOffsetFunc_[Placement::LEFT_BOTTOM] = &SheetWrapperLayoutAlgorithm::GetOffsetWithLeftBottom;
        getOffsetFunc_[Placement::RIGHT] = &SheetWrapperLayoutAlgorithm::GetOffsetWithRight;
        getOffsetFunc_[Placement::RIGHT_TOP] = &SheetWrapperLayoutAlgorithm::GetOffsetWithRightTop;
        getOffsetFunc_[Placement::RIGHT_BOTTOM] = &SheetWrapperLayoutAlgorithm::GetOffsetWithRightBottom;
    }
    ~SheetWrapperLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

    void MeasureSheetMask(LayoutWrapper* layoutWrapper);
    void LayoutMaskNode(LayoutWrapper* layoutWrapper);

private:
    void InitParameter(LayoutWrapper* layoutWrapper);
    void GetSheetPageSize(LayoutWrapper* layoutWrapper);
    void DecreaseArrowHeightWhenArrowIsShown(const RefPtr<FrameNode>& sheetNode);
    OffsetF GetPopupStyleSheetOffset(LayoutWrapper* layoutWrapper);
    OffsetF GetOffsetInAvoidanceRule(
        LayoutWrapper* layoutWrapper, const SizeF& targetSize, const OffsetF& targetOffset);
    Placement AvoidanceRuleBottom(
        const Placement& currentPlacement, const SizeF& targetSize, const OffsetF& targetOffset);
    Placement AvoidanceRuleOfPlacement(
        LayoutWrapper* layoutWrapper, const SizeF& targetSize, const OffsetF& targetOffset);
    Placement RecheckBestPlacementWithInsufficientSpace(const SizeF&, const OffsetF&, SizeF&);
    SizeF GetLeftSpaceWithPlacement(const Placement& placement, const SizeF& targetSize, const OffsetF& targetOffset);
    bool CheckDirectionBottom(const SizeF&, const OffsetF&);
    bool CheckDirectionTop(const SizeF&, const OffsetF&);
    bool CheckDirectionRight(const SizeF&, const OffsetF&);
    bool CheckDirectionLeft(const SizeF&, const OffsetF&);

    bool CheckPlacementBottom(const SizeF&, const OffsetF&);
    bool CheckPlacementBottomLeft(const SizeF&, const OffsetF&);
    bool CheckPlacementBottomRight(const SizeF&, const OffsetF&);

    OffsetF GetOffsetWithBottom(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithBottomLeft(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithBottomRight(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithTop(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithTopLeft(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithTopRight(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithLeft(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithLeftTop(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithLeftBottom(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithRight(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithRightTop(const SizeF&, const OffsetF&);
    OffsetF GetOffsetWithRightBottom(const SizeF&, const OffsetF&);

    void SetArrowOffsetInBottomOrTop(const SizeF&, const OffsetF&, float);
    void SetArrowOffsetInRightOrLeft(const SizeF&, const OffsetF&, float);

    void RestrictOffsetInSpaceBottom(float&, float&);
    void RestrictOffsetInSpaceTop(float&, float&);
    void RestrictOffsetInSpaceLeft(float&, float&);
    void RestrictOffsetInSpaceRight(float&, float&);
    void CheckIsArrowOverlapSheetRadius();

    void RemeasureForPopup(LayoutWrapper* layoutWrapper);
    void UpdateSheetNodePopupInfo(LayoutWrapper* layoutWrapper);

    bool IsTargetNodeHideByKeyboard(const SafeAreaInsets::Inset& keyboardInset, const RefPtr<FrameNode>& targetNode);

    using DirectionCheckFunc = bool (SheetWrapperLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, DirectionCheckFunc> directionCheckFunc_;
    using OffsetGetFunc = OffsetF (SheetWrapperLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, OffsetGetFunc> getOffsetFunc_;
    using PlacementCheckFunc = bool (SheetWrapperLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, PlacementCheckFunc> placementCheckFunc_;

    SheetPopupInfo sheetPopupInfo_;
    Placement placement_ = Placement::BOTTOM;
    Rect windowGlobalRect_;
    float sheetWidth_ = 0.f;
    float sheetHeight_ = 0.f;
    BorderRadiusProperty sheetRadius_;
    float windowEdgeWidth_ = 0.f;
    ACE_DISALLOW_COPY_AND_MOVE(SheetWrapperLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_WRAPPER_LAYOUT_ALGORITHM_H
