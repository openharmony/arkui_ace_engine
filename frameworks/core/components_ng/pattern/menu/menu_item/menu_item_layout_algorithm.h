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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_LAYOUT_ALGORITHM_H

#include "base/memory/referenced.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr static int32_t CLICKABLE_AREA_VIEW_INDEX = 2;
    constexpr static int32_t EXPANDABLE_AREA_VIEW_INDEX = 3;
}
class ACE_EXPORT MenuItemLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuItemLayoutAlgorithm, BoxLayoutAlgorithm);

public:
    MenuItemLayoutAlgorithm(bool isOption = false) : isOption_(isOption) {}
    ~MenuItemLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;
    void Layout(LayoutWrapper* layoutWrapper) override;

private:
    void CheckNeedMatchParent(LayoutWrapper* layoutWrapper,
        std::optional<LayoutConstraintF>& layoutConstraint);
    void CheckUserHeight(LayoutWrapper* layoutWrapper);
    void MeasureItemViews(LayoutConstraintF& childConstraint,
        std::optional<LayoutConstraintF>& layoutConstraint,
        PaddingPropertyF padding, LayoutWrapper* layoutWrapper);
    void MeasureRow(const RefPtr<LayoutWrapper>& row, const LayoutConstraintF& constraint);
    void CheckNeedExpandContent(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint);
    void UpdateSelfSize(LayoutWrapper* layoutWrapper, float width, float itemHeight, float expandableHeight);
    float GetDividerStroke(LayoutWrapper* layoutWrapper);
    float GetBordersHeight(LayoutWrapper* layoutWrapper);
    float GetMenuItemVerticalPadding();
    std::optional<float> GetIdealWidth(LayoutWrapper* layoutWrapper);
    void UpdateIconMargin(LayoutWrapper* layoutWrapper);
    void MeasureMenuItem(LayoutWrapper* layoutWrapper, const RefPtr<SelectTheme>& selectTheme,
        const RefPtr<LayoutProperty>& props, std::optional<LayoutConstraintF>& layoutConstraint);
    void MeasureOption(LayoutWrapper* layoutWrapper, const RefPtr<SelectTheme>& selectTheme,
        const RefPtr<LayoutProperty>& props, const std::optional<LayoutConstraintF>& layoutConstraint);
    void LayoutMenuItem(LayoutWrapper* layoutWrapper, const RefPtr<LayoutProperty>& props);
    void LayoutOption(LayoutWrapper* layoutWrapper, const RefPtr<LayoutProperty>& props);
    void ExtendTextAndRowNode(const RefPtr<LayoutWrapper>& row, const SizeF& optSize, float intervall);
    float MeasureExpandableHeight(LayoutConstraintF& childConstraint, LayoutWrapper* layoutWrapper);
    void InitPadding(const RefPtr<LayoutProperty>& props, std::optional<LayoutConstraintF>& layoutConstraint);
    float CalcItemHeight(float leftRowHeight, float rightRowHeight);

    float horInterval_ = 0.0f;
    float verInterval_ = 0.0f;
    float idealWidth_ = 0.0f;
    float userHeight_ = 0.0f;
    float emptyWidth_ = 0.0f;
    float maxRowWidth_ = 0.0f;
    float middleSpace_ = 0.0f;
    float minRowWidth_ = 0.0f;
    float minItemHeight_ = 0.0f;
    double iconSize_ = 0.0f;
    bool needExpandContent_ = false;
    bool isOption_ = false;
    PaddingPropertyF padding_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_ITEM_MENU_ITEM_LAYOUT_ALGORITHM_H
