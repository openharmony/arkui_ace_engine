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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_ALGORITHM_H

#include <string>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

namespace OHOS::Ace::NG {
enum class TouchingBoundaryType {
    NotTouchBoundary = 0,
    TouchBottomBoundary,
    TouchRightBoundary,
};
// DialogLayoutAlgorithm uses for Dialog Node.
class ACE_EXPORT DialogLayoutAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(DialogLayoutAlgorithm, LayoutAlgorithm);

public:
    DialogLayoutAlgorithm() = default;
    DialogLayoutAlgorithm(WeakPtr<PipelineContext> context) : context_(context) {}
    ~DialogLayoutAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override;

    void Layout(LayoutWrapper* layoutWrapper) override;

    RectF GetTouchRegion() const
    {
        return touchRegion_;
    }

private:
    void ClipCustomMaskNode(const RefPtr<FrameNode>& dialog, const RectF& rect);
    void UpdateCustomMaskNodeLayout(const RefPtr<FrameNode>& dialog);
    LayoutConstraintF CreateDialogChildConstraint(LayoutWrapper* layoutWrapper, float height, float width);
    void Distribute(float& scrollHeight, float& listHeight, float restHeight);
    void AnalysisHeightOfChild(LayoutWrapper* layoutWrapper);
    void AnalysisLayoutOfContent(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& scroll);
    void AvoidScreen(OffsetF& topLeftPoint, const RefPtr<DialogLayoutProperty>& prop, SizeF childSize);

    bool ComputeInnerLayoutSizeParam(LayoutConstraintF& innerLayout, const RefPtr<DialogLayoutProperty>& dialogProp);
    bool IsGetExpandDisplayValidHeight(const RefPtr<DialogLayoutProperty>& dialogProp);
    RefPtr<PipelineContext> GetPipelineContext() const;
    void ComputeInnerLayoutParam(LayoutConstraintF& innerLayout, const RefPtr<DialogLayoutProperty>& dialogProp);
    double GetMaxWidthBasedOnGridType(const RefPtr<GridColumnInfo>& info, GridSizeType type, DeviceType deviceType);
    int32_t GetDeviceColumns(GridSizeType type, DeviceType deviceType);
    OffsetF ComputeChildPosition(
        const SizeF& childSize, const RefPtr<DialogLayoutProperty>& prop, const SizeF& slefSize);
    bool SetAlignmentSwitch(SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint);
    bool SetAlignmentSwitchLessThanAPITwelve(const SizeF& maxSize, const SizeF& childSize, OffsetF& topLeftPoint);
    bool IsAlignmentByWholeScreen();
    void CaculateMaxSize(SizeF& maxSize);
    bool IsDialogTouchingBoundary(OffsetF topLeftPoint, SizeF childSize, SizeF selfSize);
    void MultipleDialog(const RefPtr<DialogLayoutProperty>& dialogProp, const SizeF& childSize, const SizeF& selfSize,
        const RefPtr<OverlayManager> subOverlayManager);
    void ProcessMaskRect(std::optional<DimensionRect> maskRect, const RefPtr<FrameNode>& dialog, bool isMask = false);
    void SetSubWindowHotarea(
        const RefPtr<DialogLayoutProperty>& dialogProp, SizeF childSize, SizeF selfSize, int32_t frameNodeId);
    std::optional<DimensionRect> GetMaskRect(const RefPtr<FrameNode>& dialog);

    void UpdateTouchRegion();

    double GetPaddingBottom() const;
    double GetKeyboardAvoidDistance() const;

    OffsetF AdjustChildPosition(
        OffsetF& topLeftPoint, const OffsetF& dialogOffset, const SizeF& childSize, bool needAvoidKeyboard);

    SizeF UpdateHeightWithSafeArea(SizeF size);
    void UpdateSafeArea(const RefPtr<FrameNode>& frameNode);
    void UpdateChildLayoutConstraint(const RefPtr<DialogLayoutProperty>& dialogProp,
        LayoutConstraintF& childLayoutConstraint, RefPtr<LayoutWrapper>& childLayoutWrapper);
    void AdjustHeightForKeyboard(LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& child);
    void UpdateIsScrollHeightNegative(LayoutWrapper* layoutWrapper, float height);
    void UpdateChildMaxSizeHeight(SizeT<float>& maxSize);
    void ParseSubwindowId(const RefPtr<DialogLayoutProperty>& dialogProp);

    void ResizeDialogSubwindow(bool expandDisplay, bool isShowInSubWindow, bool isShowInFloatingWindow);

    bool IsEmbeddedDialog(const RefPtr<FrameNode>& frameNode);
    float GetEmbeddedDialogOffsetY(const RefPtr<FrameNode>& frameNode);
    float GetStackRootDialogOffsetY(const RefPtr<FrameNode>& frameNode);
    void AdjustHoverModeForWaterfall(const RefPtr<FrameNode>& frameNode);
    bool IsDefaultPosition(const RefPtr<DialogLayoutProperty>& dialogProp);

    RectF touchRegion_;
    OffsetF topLeftPoint_;
    bool customSize_ = false;
    SafeAreaInsets safeAreaInsets_;
    bool isModal_ = true;
    bool hasAddMaskNode_ = false;
    bool isShowInSubWindow_ = false;
    bool isSuitableForElderly_ = false;
    bool isSuitOldMeasure_ = false;
    float dialogMaxHeight_ = 0.0f;
    int32_t gridCount_ = -1;
    int32_t subWindowId_ = -1;
    DimensionOffset dialogOffset_;
    DialogAlignment alignment_ = DialogAlignment::DEFAULT;
    TouchingBoundaryType touchingBoundaryFlag_ = TouchingBoundaryType::NotTouchBoundary;

    bool expandDisplay_ = false;
    double expandDisplayValidHeight_ = 0.0;
    bool isUIExtensionSubWindow_ = false;
    RectF hostWindowRect_;

    SizeF dialogChildSize_;
    bool resizeFlag_ = false;
    bool isHoverMode_ = false;
    bool isKeyBoardShow_ = false;
    bool alignBottomScreen_ = false;
    Rect foldCreaseRect = Rect(0.0, 0.0, 0.0, 0.0);
    HoverModeAreaType hoverModeArea_ = HoverModeAreaType::BOTTOM_SCREEN;
    OffsetF wrapperOffset_ = OffsetF(0.0, 0.0);
    SizeF wrapperSize_ = SizeF(0.0, 0.0);

    KeyboardAvoidMode keyboardAvoidMode_ = KeyboardAvoidMode::DEFAULT;
    std::optional<Dimension> keyboardAvoidDistance_;

    bool isShowInFloatingWindow_ = false;

    float embeddedDialogOffsetY_ = 0.0f;
    float stackRootDialogOffsetY_ = 0.0f;
    float safeAreaBottomLength_ = 0.0f;

    WeakPtr<PipelineContext> context_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(DialogLayoutAlgorithm);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DIALOG_DIALOG_LAYOUT_ALGORITHM_H
