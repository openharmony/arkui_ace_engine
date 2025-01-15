/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_PRESENTATION_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_PRESENTATION_LAYOUT_ALGORITHM_H

#include <cstdint>
#include <functional>
#include <optional>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SheetPresentationLayoutAlgorithm : public LinearLayoutAlgorithm {
    DECLARE_ACE_TYPE(SheetPresentationLayoutAlgorithm, LayoutAlgorithm);

public:
    SheetPresentationLayoutAlgorithm() = default;
    SheetPresentationLayoutAlgorithm(SheetType sheetType, SheetPopupInfo popupInfo)
        : sheetType_(sheetType), sheetPopupInfo_(popupInfo) {}
    ~SheetPresentationLayoutAlgorithm() override = default;

    void InitParameter();
    void OnReset() override {}
    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;
    float GetSheetMaxHeight()
    {
        return sheetMaxHeight_;
    }

    float GetSheetMaxWidth()
    {
        return sheetMaxWidth_;
    }

    float GetCenterHeight()
    {
        return sheetHeight_;
    }

    float GetSheetOffsetX()
    {
        return sheetOffsetX_;
    }

    float GetSheetOffsetY()
    {
        return sheetOffsetY_;
    }

    void UpdatePopupInfoAndRemeasure(LayoutWrapper* layoutWrapper, const SheetPopupInfo& sheetPopupInfo,
        const float& sheetWidth, const float& sheetHeight);

    void CalculateSheetHeightInOtherScenes(LayoutWrapper* layoutWrapper);
    void CalculateSheetOffsetInOtherScenes(LayoutWrapper* layoutWrapper);
private:
    float GetWidthByScreenSizeType(const SizeF& maxSize, LayoutWrapper* layoutWrapper) const;
    float GetHeightByScreenSizeType(const SizeF& maxSize, LayoutWrapper* layoutWrapper) const;
    float GetHeightBySheetStyle(LayoutWrapper* layoutWrapper) const;
    bool SheetInSplitWindow() const;
    LayoutConstraintF CreateSheetChildConstraint(
        RefPtr<SheetPresentationProperty> layoutprop, LayoutWrapper* layoutWrapper);
    void UpdateMaxSizeWithPlacement(float& maxWidth, float& maxHeight);
    void UpdateTranslateOffsetWithPlacement(OffsetF& translate);
    void AddArrowHeightToSheetSize();
    void RemeasureForPopup(const RefPtr<LayoutWrapper>& layoutWrapper);

    float sheetHeight_ = 0.0f;
    float sheetWidth_ = 0.0f;
    float sheetMaxHeight_ = 0.0f;
    float sheetMaxWidth_ = 0.0f;
    float sheetOffsetX_ = 0.0f;
    float sheetOffsetY_ = 0.0f;
    SheetType sheetType_ = SheetType::SHEET_BOTTOM;
    SheetStyle sheetStyle_;
    bool isKeyBoardShow_ = false;
    bool isHoverMode_ = false;
    HoverModeAreaType hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    using DirectionCheckFunc = bool (SheetPresentationLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, DirectionCheckFunc> directionCheckFunc_;
    using PlacementCheckFunc = bool (SheetPresentationLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, PlacementCheckFunc> placementCheckFunc_;
    using OffsetGetFunc = OffsetF (SheetPresentationLayoutAlgorithm::*)(const SizeF&, const OffsetF&);
    std::unordered_map<Placement, OffsetGetFunc> getOffsetFunc_;
    ACE_DISALLOW_COPY_AND_MOVE(SheetPresentationLayoutAlgorithm);
    SheetPopupInfo sheetPopupInfo_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_OVERLAY_SHEET_PRESENTATION_LAYOUT_ALGORITHM_H