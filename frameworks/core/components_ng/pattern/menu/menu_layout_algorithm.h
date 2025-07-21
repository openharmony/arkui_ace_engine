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
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/menu_property.h"

namespace OHOS::Ace::NG {
struct PreviewMenuParam {
    SizeF windowGlobalSizeF;
    Rect menuWindowRect;
    Rect wrapperRect;
    float windowsOffsetX = 0.0f;
    float windowsOffsetY = 0.0f;
    float top = 0.0f;
    float bottom = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
    float topSecurity = 0.0f;
    float bottomSecurity = 0.0f;
    float leftSecurity = 0.0f;
    float rightSecurity = 0.0f;
    float previewMenuGap = 0.0f;
    float menuItemTotalHeight = 0.0f;
};

struct MenuDumpInfo {
    uint32_t menuPreviewMode = 0;
    uint32_t menuType = 0;
    bool enableArrow = false;
    OffsetF offset;
    std::string targetNode;
    OffsetF targetOffset;
    SizeF targetSize;
    Rect menuWindowRect;
    Rect wrapperRect;
    float previewBeginScale = 0.0f;
    float previewEndScale = 0.0f;
    float top = 0.0f;
    float bottom = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
    OffsetF globalLocation;
    std::string originPlacement;
    std::string defaultPlacement;
    OffsetF finalPosition;
    std::string finalPlacement = "NONE";
    OffsetF anchorPosition;
};
class MenuLayoutProperty;
class MenuPattern;
class MenuLayoutAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(MenuLayoutAlgorithm, BoxLayoutAlgorithm)
public:
    MenuLayoutAlgorithm(int32_t id, const std::string& tag,
        const std::optional<OffsetF>& lastPosition = std::nullopt);
    MenuLayoutAlgorithm() = default;
    ~MenuLayoutAlgorithm() override;

    // override measureSelf and measureChildren.
    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    Placement GetPlacement() const
    {
        return placement_;
    }

    std::string& GetClipPath()
    {
        return clipPath_;
    }

    bool canExpandCurrentWindow_ = false;
    void InitCanExpandCurrentWindow(bool isShowInSubWindow, LayoutWrapper* layoutWrapper);
    bool HoldEmbeddedMenuPosition(LayoutWrapper* layoutWrapper);
    Rect GetMenuWindowRectInfo(const RefPtr<MenuPattern>& menuPattern);

protected:
    float VerticalLayout(const SizeF& size, float clickPosition, bool IsContextMenu = false);
    float HorizontalLayout(const SizeF& size, float clickPosition, bool IsSelectMenu = false);

    RefPtr<MenuPaintProperty> GetPaintProperty(const LayoutWrapper* layoutWrapper);
    OffsetF GetMenuWrapperOffset(const LayoutWrapper* layoutWrapper);
    void ClipMenuPath(LayoutWrapper* layoutWrapper);
    float GetFirstItemBottomPositionY(const RefPtr<FrameNode>& menu);
    float GetLastItemTopPositionY(const RefPtr<FrameNode>& menu);
    float GetMenuBottomPositionY(const RefPtr<FrameNode>& menu);
    bool isContainerModal(const RefPtr<FrameNode>& node);
    float GetContainerModalOffsetY(const RefPtr<FrameNode>& node);
    float CalcVerticalPosition(const SizeF& size);

    // position input is relative to main window left top point,
    // menu show position is relative to menuWrapper.
    OffsetF position_;
    OffsetF positionOffset_;
    SizeF wrapperSize_;
    // rect is relative to menuWrapper
    Rect wrapperRect_;
    PreviewMenuParam param_;

private:
    enum class ErrorPositionType {
        NORMAL = 0,
        TOP_LEFT_ERROR,
        BOTTOM_RIGHT_ERROR,
    };
    enum class DirectionState {
        Bottom_Direction = 1,
        Top_Direction,
        Right_Direction,
        Left_Direction,
        None_Direction,
    };

    void Initialize(LayoutWrapper* layoutWrapper);
    void InitializePadding(LayoutWrapper* layoutWrapper);
    void InitializePaddingAPI12(LayoutWrapper* layoutWrapper);
    void InitializeSecurityPadding();
    void InitializeParam(LayoutWrapper* layoutWrapper, const RefPtr<MenuPattern>& menuPattern);
    void InitializeLayoutRegionMargin(const RefPtr<MenuPattern>& menuPattern);
    void InitWrapperRect(const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern);
    void CalcWrapperRectForHoverMode(const RefPtr<MenuPattern>& menuPattern);
    void UpdateWrapperRectForHoverMode(
        const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern, double creaseHeightOffset);
    uint32_t GetBottomBySafeAreaManager(const RefPtr<SafeAreaManager>& safeAreaManager,
        const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern);
    void InitSpace(const RefPtr<MenuLayoutProperty>& props, const RefPtr<MenuPattern>& menuPattern);
    void ModifyPositionToWrapper(LayoutWrapper* layoutWrapper, OffsetF& position);
    LayoutConstraintF CreateChildConstraint(LayoutWrapper* layoutWrapper);
    void UpdateConstraintWidth(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateConstraintSelectHeight(LayoutWrapper* layoutWrapper, LayoutConstraintF& LayoutConstraintF);
    void UpdateConstraintBaseOnOptions(LayoutWrapper* layoutWrapper, LayoutConstraintF& constraint);
    void UpdateOptionConstraint(std::list<RefPtr<LayoutWrapper>>& options, float width);
    float GetMenuMaxBottom(const RefPtr<MenuPattern>& menuPattern);

    void ComputeMenuPositionByAlignType(const RefPtr<MenuLayoutProperty>& menuProp, const SizeF& menuSize);
    OffsetF ComputeMenuPositionByOffset(
        const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<GeometryNode>& geometryNode);
    void ComputePlacementByAlignType(const RefPtr<MenuLayoutProperty>& menuProp);
    OffsetF MenuLayoutAvoidAlgorithm(const RefPtr<MenuLayoutProperty>& menuProp, const RefPtr<MenuPattern>& menuPattern,
        const SizeF& size, bool didNeedArrow = false, LayoutWrapper* layoutWrapper = nullptr);
    OffsetF SelectLayoutAvoidAlgorithm(const RefPtr<MenuLayoutProperty>& menuProp,
        const RefPtr<MenuPattern>& menuPattern, const SizeF& size, bool didNeedArrow = false,
        LayoutWrapper* layoutWrapper = nullptr);
    void PlacementRTL(LayoutWrapper* layoutWrapper, Placement& placement_);
    void SetMenuPlacementForAnimation(LayoutWrapper* layoutWrapper);

    void LayoutArrow(const LayoutWrapper* layoutWrapper);
    OffsetF GetArrowPositionWithPlacement(const SizeF& menuSize, const LayoutWrapper* layoutWrapper);
    bool GetIfNeedArrow(const LayoutWrapper* layoutWrapper, const SizeF& menuSize);
    void UpdateArrowOffsetWithMenuLimit(const SizeF& menuSize, const LayoutWrapper* layoutWrapper);
    void UpdatePropArrowOffset();
    void LimitContainerModalMenuRect(double& rectWidth, double& rectHeight, const RefPtr<MenuPattern>& menuPattern);

    // get option LayoutWrapper for measure get max width
    std::list<RefPtr<LayoutWrapper>> GetOptionsLayoutWrappper(LayoutWrapper* layoutWrapper);

    OffsetF GetPositionWithPlacement(const SizeF& childSize, const OffsetF& topPosition, const OffsetF& bottomPosition);
    void InitTargetSizeAndPosition(const LayoutWrapper* layoutWrapper, bool isContextMenu,
        const RefPtr<MenuPattern>& menuPattern);
    bool SkipUpdateTargetNodeSize(const RefPtr<FrameNode>& targetNode, const RefPtr<MenuPattern>& menuPattern);
    OffsetF GetChildPosition(const SizeF& childSize, bool didNeedArrow = false);
    OffsetF GetSelectChildPosition(const SizeF& childSize, bool didNeedArrow = false,
        LayoutWrapper* layoutWrapper = nullptr);
    OffsetF FitToScreen(const OffsetF& position, const SizeF& childSize, bool didNeedArrow = false);
    bool CheckPosition(const OffsetF& position, const SizeF& childSize);

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
    OffsetF AddTargetSpace(const OffsetF& position);
    OffsetF AddOffset(const OffsetF& position);
    bool CheckPositionInPlacementRect(const Rect& rect, const OffsetF& position, const SizeF& childSize);
    OffsetF AdjustPosition(const OffsetF& position, float width, float height, float space);
    OffsetF GetAdjustPosition(std::vector<Placement>& currentPlacementStates, size_t step, const SizeF& childSize,
        const OffsetF& topPosition, const OffsetF& bottomPosition);
    OffsetF GetSelectAdjustPosition(std::vector<Placement>& currentPlacementStates, const SizeF& childSize,
        const OffsetF& topPosition, const OffsetF& bottomPosition);
    void CalculateChildOffset(bool didNeedArrow);
    OffsetF CalculateMenuPositionWithArrow(const OffsetF& menuPosition, bool didNeedArrow);
    void UpdateMenuFrameSizeWithArrow(const RefPtr<GeometryNode>& geometryNode, bool didNeedArrow);

    void LayoutPreviewMenu(LayoutWrapper* layoutWrapper);
    void LayoutPreviewMenuGreateThanForConstant(
        const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode);
    void UpdatePreviewPositionAndOffset(
        RefPtr<LayoutWrapper>& previewLayoutWrapper, RefPtr<LayoutWrapper>& menuLayoutWrapper);
    void ModifyPreviewMenuPlacement(LayoutWrapper* layoutWrapper);
    void GetPreviewNodeTotalSize(const RefPtr<LayoutWrapper>& child, const Rect& menuWindowRect,
        RefPtr<LayoutWrapper>& previewLayoutWrapper, SizeF& size, const RefPtr<LayoutWrapper>& menuLayoutWrapper);
    SizeF GetPreviewNodeAndMenuNodeTotalSize(const RefPtr<FrameNode>& frameNode,
        RefPtr<LayoutWrapper>& previewLayoutWrapper, RefPtr<LayoutWrapper>& menuLayoutWrapper);

    void LayoutNormalTopPreviewBottomMenu(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight,
        LayoutWrapper* layoutWrapper);
    void LayoutNormalTopPreviewBottomMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);
    void LayoutNormalTopPreviewBottomMenuGreateThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);
    void LayoutNormalBottomPreviewTopMenu(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight,
        LayoutWrapper* layoutWrapper);
    void LayoutNormalBottomPreviewTopMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);
    void LayoutNormalBottomPreviewTopMenuGreateThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);

    float CheckHorizontalLayoutPreviewOffsetX(
        const RefPtr<GeometryNode>& previewGeometryNode, const RefPtr<GeometryNode>& menuGeometryNode, float offsetX);
    void LayoutOtherDeviceLeftPreviewRightMenu(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize, float menuItemTotalHeight);
    void LayoutOtherDeviceLeftPreviewRightMenuLessThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);
    void LayoutOtherDeviceLeftPreviewRightMenuGreateThan(const RefPtr<GeometryNode>& previewGeometryNode,
        const RefPtr<GeometryNode>& menuGeometryNode, SizeF& totalSize);
    void UpdateScrollAndColumnLayoutConstraint(
        const RefPtr<LayoutWrapper>& previewLayoutWrapper, const RefPtr<LayoutWrapper>& menuLayoutWrapper);
    float GetMenuItemTotalHeight(const RefPtr<LayoutWrapper>& menuLayoutWrapper);
    OffsetF FixMenuOriginOffset(float beforeAnimationScale, float afterAnimationScale);
    bool CheckPlacement(const SizeF& childSize);

    void ProcessArrowParams(const LayoutWrapper* layoutWrapper, const SizeF& menuSize);
    BorderRadiusProperty GetMenuRadius(const LayoutWrapper* layoutWrapper, const SizeF& menuSize);

    void UpdateSelectFocus(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint);
    void CalculateIdealSize(LayoutWrapper* layoutWrapper, LayoutConstraintF& childConstraint,
        PaddingPropertyF padding, SizeF& idealSize, RefPtr<FrameNode> parentItem);
    void TranslateOptions(LayoutWrapper* layoutWrapper);
    bool CheckChildConstraintCondition(const RefPtr<MenuPattern>& menuPattern);
    void UpdateChildConstraintByDevice(const RefPtr<MenuPattern>& menuPattern,
        LayoutConstraintF& childConstraint, const LayoutConstraintF& layoutConstraint);
    void CheckPreviewConstraint(const RefPtr<FrameNode>& frameNode, const Rect& menuWindowRect);
    void CheckPreviewConstraintForConstant(const RefPtr<GeometryNode>& previewGeometryNode);
    void CheckPreviewSize(const RefPtr<LayoutWrapper>& previewLayoutWrapper, const RefPtr<MenuPattern>& menuPattern);
    void ModifyTargetOffset();
    OffsetF UpdateMenuPosition(LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& menuNode,
        RefPtr<MenuPattern> menuPattern, const RefPtr<MenuLayoutProperty>& menuProp);
    bool IsSelectMenuShowInSubWindow(LayoutWrapper* layoutWrapper, const RefPtr<FrameNode>& menuNode);

    std::string MoveTo(double x, double y);
    std::string LineTo(double x, double y);
    std::string ArcTo(double rx, double ry, double rotation, int32_t arc_flag, double x, double y);
    void BuildBottomArrowPath(float arrowX, float arrowY, std::string& path);
    void BuildTopArrowPath(float arrowX, float arrowY, std::string& path);
    void BuildRightArrowPath(float arrowX, float arrowY, std::string& path);
    void BuildLeftArrowPath(float arrowX, float arrowY, std::string& path);
    std::string BuildTopLinePath(const OffsetF& arrowPosition, float radiusPx,
        Placement arrowBuildPlacement, bool didNeedArrow);
    std::string BuildRightLinePath(const OffsetF& arrowPosition, float radiusPx,
        Placement arrowBuildPlacement, bool didNeedArrow);
    std::string BuildBottomLinePath(const OffsetF& arrowPosition, float radiusPx,
        Placement arrowBuildPlacement, bool didNeedArrow);
    std::string BuildLeftLinePath(const OffsetF& arrowPosition, float radiusPx,
        Placement arrowBuildPlacement, bool didNeedArrow);
    void NormalizeBorderRadius(float& radiusTopLeftPx, float& radiusTopRightPx,
        float& radiusBottomLeftPx, float& radiusBottomRightPx);
    std::string CalculateMenuPath(LayoutWrapper* layoutWrapper, bool didNeedArrow);
    bool UpdateSelectOverlayMenuColumnInfo(
        const RefPtr<MenuPattern>& menuPattern, const RefPtr<GridColumnInfo>& columnInfo);
    float CalcSubMenuMaxHeightConstraint(LayoutConstraintF& childConstraint, RefPtr<FrameNode> parentItem);
    float CalcSubMenuMaxHeightWithPreview(RefPtr<FrameNode> parentMenu, LayoutConstraintF& childConstraint,
        float lastItemTopPositionY, float firstItemBottomPositionY, float parentMenuPositionY);
    float CalcSubMenuMaxHeightNoPreview(RefPtr<FrameNode> parentItem, LayoutConstraintF& childConstraint,
        float lastItemTopPositionY, float firstItemBottomPositionY, float parentMenuPositionY);
    RefPtr<SelectTheme> GetCurrentSelectTheme(const RefPtr<FrameNode>& frameNode);

    std::optional<OffsetF> lastPosition_;
    OffsetF targetOffset_;
    SizeF targetSize_;
    Placement placement_ = Placement::BOTTOM_LEFT;
    int32_t targetNodeId_ = -1;
    std::string targetTag_;
    float targetSecurity_ = TARGET_SECURITY.ConvertToPx();

    // current page offset relative to window.
    float topSpace_ = 0.0f;
    float bottomSpace_ = 0.0f;
    float leftSpace_ = 0.0f;
    float rightSpace_ = 0.0f;

    // arrow
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
    float paddingStart_ = 0.0f;
    float paddingEnd_ = 0.0f;
    float paddingTop_ = 0.0f;
    float paddingBottom_ = 0.0f;
    float optionPadding_ = 0.0f;

    float top_ = 0.0;
    float bottom_ = 0.0;
    float left_ = 0.0;
    float right_ = 0.0;
    double width_ = 0.0;
    double height_ = 0.0;

    OffsetF targetCenterOffset_;
    OffsetF previewOriginOffset_;
    OffsetF previewOffset_;
    SizeF previewSize_;
    int32_t state_ = 0;
    int32_t prevState_ = -1;
    OffsetF preOffset_;
    Rect preRect_;
    bool flag_ = false;
    // previewScale_ must be greater than 0
    float previewScale_ = 1.0f;
    MenuDumpInfo dumpInfo_;
    MarginPropertyF layoutRegionMargin_;
    bool isTargetNodeInSubwindow_ = false;
    bool isExpandDisplay_ = false;
    bool isFreeMultiWindow_ = false;
    bool isUIExtensionSubWindow_ = false;
    RectF displayWindowRect_;
    RectF UIExtensionHostWindowRect_;

    OffsetF childOffset_;
    SizeF childMarginFrameSize_;
    std::string clipPath_;
    bool isPreviewContainScale_ = false;
    bool holdEmbeddedMenuPosition_ = false;
    bool didNeedArrow_ = false;
    std::optional<PreviewScaleMode> previewScaleMode_ = std::nullopt;
    std::optional<AvailableLayoutAreaMode> availableLayoutAreaMode_ = std::nullopt;

    using PlacementFunc = OffsetF (MenuLayoutAlgorithm::*)(const SizeF&, const OffsetF&, const OffsetF&);
    std::map<Placement, PlacementFunc> placementFuncMap_;

    std::optional<OffsetF> anchorPosition_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MENU_MENU_LAYOUT_ALGORITHM_H
