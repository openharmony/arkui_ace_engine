/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H

#include <list>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"

namespace OHOS::Ace::NG {
class MenuLayoutProperty;
class MenuPattern;
class MenuLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuLayoutAlgorithm, BoxLayoutAlgorithm)
public:
    MenuLayoutAlgorithm(int32_t id, const std::string& tag);
    MenuLayoutAlgorithm() = default;
    ~MenuLayoutAlgorithm() override;

    // override measureSelf and measureChildren.
    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

protected:
    float VerticalLayout(const SizeF& size, float clickPosition);
    float HorizontalLayout(const SizeF& size, float clickPosition, bool IsSelectMenu = false);

    RefPtr<MenuPaintProperty> GetPaintProperty(const LayoutWrapper* layoutWrapper);

    OffsetF position_;
    OffsetF positionOffset_;
    SizeF wrapperSize_;
    OffsetF pageOffset_;

private:
    enum class ErrorPositionType {
        NORMAL = 0,
        TOP_LEFT_ERROR,
        BOTTOM_RIGHT_ERROR,
    };
    void Initialize(LayoutWrapper* layoutWrapper);
    LayoutConstraintF CreateChildConstraint(LayoutWrapper* layoutWrapper);
    void UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintBaseOnOptions(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateOptionConstraint(std::list<RefPtr<LayoutWrapper>>& options, float width);

    void ComputeMenuPositionByAlignType(const RefPtr<MenuLayoutProperty>& menuProp, const SizeF& menuSize);
    OffsetF ComputeMenuPositionByOffset(
        const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<GeometryNode>& geometryNode);
    OffsetF MenuLayoutAvoidAlgorithm(
        const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<MenuPattern>& menuPattern, const SizeF& size);

    void LayoutArrow(const LayoutWrapper* layoutWrapper);
    OffsetF GetArrowPositionWithPlacement(const SizeF& menuSize);
    bool GetIfNeedArrow(const LayoutWrapper* layoutWrapper, const SizeF& menuSize);
    void UpdateArrowOffsetWithMenuLimit(const SizeF& menuSize);
    void UpdatePropArrowOffset();

    // get option LayoutWrapper for measure get max width
    std::list<RefPtr<LayoutWrapper>> GetOptionsLayoutWrappper(LayoutWrapper* layoutWrapper);

    OffsetF GetPositionWithPlacement(const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition);
    void InitTargetSizeAndPosition(const RefPtr<MenuLayoutProperty>& layoutProp);
    OffsetF GetChildPosition(const SizeF& childSize, const RefPtr<MenuLayoutProperty>& layoutProp, bool isContextMenu);
    ErrorPositionType GetErrorPositionType(const OffsetF& childOffset, const SizeF& childSize);
    OffsetF FitToScreen(const OffsetF& fitPosition, const SizeF& childSize, bool isContextMenu);

    OffsetF GetPositionWithPlacementTop(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementTopLeft(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementTopRight(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementBottom(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementBottomLeft(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementBottomRight(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementLeft(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementLeftTop(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementLeftBottom(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementRight(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementRightTop(const SizeF&, const OffsetF&, const OffsetF&);
    OffsetF GetPositionWithPlacementRightBottom(const SizeF&, const OffsetF&, const OffsetF&);

    RefPtr<PipelineContext> GetCurrentPipelineContext();

    OffsetF targetOffset_;
    SizeF targetSize_;
    Placement placement_ = Placement::BOTTOM;
    int32_t targetNodeId_ = -1;
    std::string targetTag_;

    // current page offset relative to window.
    float topSpace_ = 0.0f;
    float bottomSpace_ = 0.0f;
    float leftSpace_ = 0.0f;
    float rightSpace_ = 0.0f;

    // arrow
    float menuRadius_ = 0.0f;
    float targetSpace_ = 0.0f;
    float arrowMinLimit_ = 0.0f;
    float arrowOffset_ = 0.0f;
    float arrowWidth_ = 0.0f;
    bool arrowInMenu_ = false;
    bool propNeedArrow_ = false;
    OffsetF arrowPosition_;
    Dimension propArrowOffset_;
    std::unordered_set<Placement> setHorizontal_;
    std::unordered_set<Placement> setVertical_;
    Placement arrowPlacement_ = Placement::NONE;

    float margin_ = 0.0f;
    float optionPadding_ = 0.0f;

    using PlacementFunc = OffsetF (MenuLayoutAlgorithm::*)(const SizeF&, const OffsetF&, const OffsetF&);
    std::map<Placement, PlacementFunc> placementFuncMap_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H
