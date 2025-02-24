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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H

#include <optional>
#include <utility>

#include "base/geometry/ng/offset_t.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"

namespace OHOS::Ace::NG {

struct AvoidStrategyMember {
    float menuHeight = 0.f;
    double menuSpacingBetweenText = 0.0;
    double menuSpacingBetweenHandle = 0.0;
    double safeSpacing = 0.0;
    double bottomLimitOffsetY = 0.0;
    double menuSpacing = 0.0;
    double keyboardInsertStart = 0.0;
    bool hasKeyboard = false;
    bool downHandleIsReallyShow = true;
    double selectAreaTop = 0.0;
    double selectAndRootRectAreaTop = 0.0;
    double selectAndRootRectAreaBottom = 0.0;
};

class ACE_EXPORT SelectOverlayLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(SelectOverlayLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    explicit SelectOverlayLayoutAlgorithm(std::shared_ptr<SelectOverlayInfo> info, const OffsetF& defaultMenuEndOffset,
        const std::optional<float>& menuWidth, const std::optional<float>& menuHeight)
        : info_(std::move(info)), defaultMenuEndOffset_(defaultMenuEndOffset), menuWidth_(menuWidth),
          menuHeight_(menuHeight)
    {}
    ~SelectOverlayLayoutAlgorithm() override = default;

    void Layout(LayoutWrapper* layoutWrapper) override;
    void Measure(LayoutWrapper* layoutWrapper) override;

    static bool CheckInShowArea(const SelectOverlayInfo& info);

    const OffsetF& GetDefaultMenuStartOffset() const
    {
        return defaultMenuStartOffset_;
    }

    const OffsetF& GetDefaultMenuEndOffset() const
    {
        return defaultMenuEndOffset_;
    }

    const std::optional<float>& GetMenuWidth() const
    {
        return menuWidth_;
    }

    const std::optional<float>& GetMenuHeight() const
    {
        return menuHeight_;
    }

    bool GetHasExtensionMenu() const
    {
        return hasExtensionMenu_;
    }

    bool GetHideMoreOrBack() const
    {
        return hideMoreOrBack_;
    }

    void MeasureChild(LayoutWrapper* layoutWrapper);
    void LayoutChild(LayoutWrapper* layoutWrapper, SelectOverlayMode mode);
    void LayoutExtensionMenu(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& button);

private:
    OffsetF ComputeSelectMenuPosition(LayoutWrapper* layoutWrapper);
    OffsetF ComputeExtensionMenuPosition(LayoutWrapper* layoutWrapper, const OffsetF& offset);
    OffsetF AdjustSelectMenuOffset(
        LayoutWrapper* layoutWrapper, const RectF& menuRect, double spaceBetweenText, double spaceBetweenHandle);
    OffsetF AdjustSelectMenuOffsetWhenHandlesUnshown(const RectF& menuRect, double spaceBetweenText);
    void AdjustMenuOffsetAtSingleHandleBottom(const RectF handleRect, const RectF& menuRect, OffsetF& menuOffset,
        double spaceBetweenText);
    bool IsMenuAreaSmallerHandleArea(RectF handleRect, float menuHeight, float menuDistance);
    void AdjustMenuTooFarAway(LayoutWrapper* layoutWrapper, OffsetF& menuOffset, const RectF& menuRect);
    void AdjustMenuInRootRect(OffsetF& menuOffset, const SizeF& menuSize, const SizeF& rootSize);
    OffsetF CalculateCustomMenuByMouseOffset(LayoutWrapper* layoutWrapper);
    OffsetF NewMenuAvoidStrategy(LayoutWrapper* layoutWrapper, float menuWidth, float menuHeight);
    void CalculateCustomMenuLayoutConstraint(LayoutWrapper* layoutWrapper, LayoutConstraintF& layoutConstraint);
    void CheckHideBackOrMoreButton(const RefPtr<LayoutWrapper>& extensionMenu, const RefPtr<LayoutWrapper>& button);
    void NewMenuAvoidStrategyGetY(const AvoidStrategyMember& avoidStrategyMember, float& offsetY);
    bool IsTextAreaSelectAll();
    bool IsReverseLayout(LayoutWrapper* layoutWrapper) const;
    void CheckHandleIsInClipViewPort();
    float GetCustomMenuMaxHeight(float topSafeArea, float bottomSafeArea);
    void UpdateMainWindowOffset(LayoutWrapper* layoutWrapper);
    bool GetIsMenuShowInSubWindow(LayoutWrapper* layoutWrapper);

    std::shared_ptr<SelectOverlayInfo> info_;

    OffsetF defaultMenuStartOffset_;
    OffsetF defaultMenuEndOffset_;
    std::optional<float> menuWidth_;
    std::optional<float> menuHeight_;
    bool hasExtensionMenu_ = false;
    bool hideMoreOrBack_ = false;
    OffsetF mainWindowOffset_;
    OffsetF containerModalOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_OVERLAY_LAYOUT_ALGORITHM_H