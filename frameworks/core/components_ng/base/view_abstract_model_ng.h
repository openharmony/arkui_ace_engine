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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

#include <optional>
#include <utility>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/border_image.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewAbstractModelNG : public ViewAbstractModel {
public:
    ~ViewAbstractModelNG() override = default;

    void SetWidth(const Dimension& width) override
    {
        ViewAbstract::SetWidth(NG::CalcLength(width));
    }

    void SetHeight(const Dimension& height) override
    {
        ViewAbstract::SetHeight(NG::CalcLength(height));
    }

    void SetMinWidth(const Dimension& minWidth) override
    {
        ViewAbstract::SetMinWidth(NG::CalcLength(minWidth));
    }

    void SetMinHeight(const Dimension& minHeight) override
    {
        ViewAbstract::SetMinHeight(NG::CalcLength(minHeight));
    }

    void SetMaxWidth(const Dimension& maxWidth) override
    {
        ViewAbstract::SetMaxWidth(NG::CalcLength(maxWidth));
    }

    void SetMaxHeight(const Dimension& maxHeight) override
    {
        ViewAbstract::SetMaxHeight(NG::CalcLength(maxHeight));
    }

    void SetBackgroundColor(const Color& color) override
    {
        ViewAbstract::SetBackgroundColor(color);
    }

    void SetBackgroundImage(const std::string& src, RefPtr<ThemeConstants> themeConstant) override
    {
        ViewAbstract::SetBackgroundImage(src);
    }

    void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) override
    {
        ViewAbstract::SetBackgroundImageRepeat(imageRepeat);
    }

    void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) override
    {
        ViewAbstract::SetBackgroundImageSize(bgImgSize);
    }

    void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) override
    {
        ViewAbstract::SetBackgroundImagePosition(bgImgPosition);
    }

    void SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle) override
    {
        ViewAbstract::SetBackgroundBlurStyle(bgBlurStyle);
    }

    void SetPadding(const Dimension& value) override
    {
        ViewAbstract::SetPadding(NG::CalcLength(value));
    }

    void SetPaddings(const std::optional<Dimension>& top, const std::optional<Dimension>& bottom,
        const std::optional<Dimension>& left, const std::optional<Dimension>& right) override
    {
        NG::PaddingProperty paddings;
        if (top.has_value()) {
            paddings.top = NG::CalcLength(top.value());
        }
        if (bottom.has_value()) {
            paddings.bottom = NG::CalcLength(bottom.value());
        }
        if (left.has_value()) {
            paddings.left = NG::CalcLength(left.value());
        }
        if (right.has_value()) {
            paddings.right = NG::CalcLength(right.value());
        }
        ViewAbstract::SetPadding(paddings);
    }

    void SetMargin(const Dimension& value) override
    {
        ViewAbstract::SetMargin(NG::CalcLength(value));
    }

    void SetMargins(const std::optional<Dimension>& top, const std::optional<Dimension>& bottom,
        const std::optional<Dimension>& left, const std::optional<Dimension>& right) override
    {
        NG::MarginProperty margins;
        if (top.has_value()) {
            margins.top = NG::CalcLength(top.value());
        }
        if (bottom.has_value()) {
            margins.bottom = NG::CalcLength(bottom.value());
        }
        if (left.has_value()) {
            margins.left = NG::CalcLength(left.value());
        }
        if (right.has_value()) {
            margins.right = NG::CalcLength(right.value());
        }
        ViewAbstract::SetMargin(margins);
    }

    void SetBorderRadius(const Dimension& value) override
    {
        ViewAbstract::SetBorderRadius(value);
    }

    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override
    {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = radiusTopLeft;
        borderRadius.radiusTopRight = radiusTopRight;
        borderRadius.radiusBottomLeft = radiusBottomLeft;
        borderRadius.radiusBottomRight = radiusBottomRight;
        ViewAbstract::SetBorderRadius(borderRadius);
    }

    void SetBorderColor(const Color& value) override
    {
        ViewAbstract::SetBorderColor(value);
    }
    void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override
    {
        NG::BorderColorProperty borderColors;
        borderColors.leftColor = colorLeft;
        borderColors.rightColor = colorRight;
        borderColors.topColor = colorTop;
        borderColors.bottomColor = colorBottom;
        ViewAbstract::SetBorderColor(borderColors);
    }

    void SetBorderWidth(const Dimension& value) override
    {
        ViewAbstract::SetBorderWidth(value);
    }

    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty borderWidth;
        borderWidth.leftDimen = left;
        borderWidth.rightDimen = right;
        borderWidth.topDimen = top;
        borderWidth.bottomDimen = bottom;
        ViewAbstract::SetBorderWidth(borderWidth);
    }

    void SetBorderStyle(const BorderStyle& value) override
    {
        ViewAbstract::SetBorderStyle(value);
    }

    void SetBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override
    {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = styleLeft;
        borderStyles.styleRight = styleRight;
        borderStyles.styleTop = styleTop;
        borderStyles.styleBottom = styleBottom;
        ViewAbstract::SetBorderStyle(borderStyles);
    }

    void SetBorderImage(const RefPtr<BorderImage>& borderImage, uint8_t bitset) override
    {
        CHECK_NULL_VOID(borderImage);
        if (bitset | BorderImage::SOURCE_BIT) {
            ViewAbstract::SetBorderImageSource(borderImage->GetSrc());
        }
        if (bitset | BorderImage::OUTSET_BIT) {
            ViewAbstract::SetHasBorderImageOutset(true);
        }
        if (bitset | BorderImage::SLICE_BIT) {
            ViewAbstract::SetHasBorderImageSlice(true);
        }
        if (bitset | BorderImage::REPEAT_BIT) {
            ViewAbstract::SetHasBorderImageRepeat(true);
        }
        if (bitset | BorderImage::WIDTH_BIT) {
            ViewAbstract::SetHasBorderImageWidth(true);
        }
        ViewAbstract::SetBorderImage(borderImage);
    }

    void SetBorderImageGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetBorderImageGradient(gradient);
    }

    void SetLayoutPriority(int32_t priority) override {}

    void SetLayoutWeight(int32_t value) override
    {
        ViewAbstract::SetLayoutWeight(value);
    }

    void SetLayoutDirection(TextDirection value) override
    {
        ViewAbstract::SetLayoutDirection(value);
    }

    void SetAspectRatio(float ratio) override
    {
        if (LessOrEqual(ratio, 0.0)) {
            LOGW("the %{public}f value is illegal, use default", ratio);
            ratio = 1.0;
        }
        ViewAbstract::SetAspectRatio(ratio);
    }

    void SetAlign(const Alignment& alignment) override
    {
        ViewAbstract::SetAlign(alignment);
    }

    void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) override
    {
        ViewAbstract::SetAlignRules(alignRules);
    }

    void SetUseAlign(
        AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset) override
    {}

    void SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset, const RefPtr<GridContainerInfo>& info,
        GridSizeType type = GridSizeType::UNDEFINED) override
    {
        ViewAbstract::SetGrid(span, offset, type);
    }

    void SetZIndex(int32_t value) override
    {
        ViewAbstract::SetZIndex(value);
    }

    void SetPosition(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetPosition({ x, y });
    }

    void SetOffset(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetOffset({ x, y });
    }

    void MarkAnchor(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::MarkAnchor({ x, y });
    }

    void SetScale(float x, float y, float z) override
    {
        VectorF scale(x, y);
        ViewAbstract::SetScale(scale);
    }

    void SetPivot(const Dimension& x, const Dimension& y) override
    {
        DimensionOffset center(x, y);
        ViewAbstract::SetPivot(center);
    }

    void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) override
    {
        ViewAbstract::SetTranslate(NG::Vector3F(x.ConvertToPx(), y.ConvertToPx(), z.ConvertToPx()));
    }

    void SetRotate(float x, float y, float z, float angle) override
    {
        ViewAbstract::SetRotate(NG::Vector4F(x, y, z, angle));
    }

    void SetTransformMatrix(const std::vector<float>& matrix) override
    {
        NG::ViewAbstract::SetTransformMatrix(
            Matrix4(matrix[0], matrix[4], matrix[8], matrix[12], matrix[1], matrix[5], matrix[9], matrix[13], matrix[2],
                matrix[6], matrix[10], matrix[14], matrix[3], matrix[7], matrix[11], matrix[15]));
    }

    void SetOpacity(double opacity, bool passThrough = false) override
    {
        ViewAbstract::SetOpacity(opacity);
    }

    void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) override
    {
        ViewAbstract::SetTransition(transitionOptions);
    }

    void SetOverlay(const std::string& text, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY) override
    {
        NG::OverlayOptions overlay;
        overlay.content = text;
        overlay.align = align.value_or(Alignment::TOP_LEFT);
        if (offsetX.has_value()) {
            overlay.x = offsetX.value();
        }
        if (offsetY.has_value()) {
            overlay.y = offsetY.value();
        }
        ViewAbstract::SetOverlay(overlay);
    }

    void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) override
    {
        ViewAbstract::SetVisibility(visible);
    }

    void SetSharedTransition(const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option) override
    {
        ViewAbstract::SetSharedTransition(shareId, option);
    }

    void SetGeometryTransition(const std::string& id) override {}

    void SetMotionPath(const MotionPathOption& option) override
    {
        ViewAbstract::SetMotionPath(option);
    }

    void SetFlexBasis(const Dimension& value) override
    {
        ViewAbstract::SetFlexBasis(value);
    }

    void SetAlignSelf(FlexAlign value) override
    {
        ViewAbstract::SetAlignSelf(value);
    }

    void SetFlexShrink(float value) override
    {
        ViewAbstract::SetFlexShrink(value);
    }

    void SetFlexGrow(float value) override
    {
        ViewAbstract::SetFlexGrow(value);
    }

    void SetDisplayIndex(int32_t value) override
    {
        ViewAbstract::SetDisplayIndex(value);
    }

    void SetLinearGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetLinearGradient(gradient);
    }

    void SetSweepGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetSweepGradient(gradient);
    }

    void SetRadialGradient(const NG::Gradient& gradient) override
    {
        ViewAbstract::SetRadialGradient(gradient);
    }

    void SetClipShape(const RefPtr<BasicShape>& basicShape) override
    {
        ViewAbstract::SetClipShape(basicShape);
    }

    void SetClipEdge(bool isClip) override
    {
        ViewAbstract::SetClipEdge(isClip);
    }

    void SetMask(const RefPtr<BasicShape>& shape) override
    {
        ViewAbstract::SetMask(shape);
    }

    void SetBackdropBlur(const Dimension& radius) override
    {
        ViewAbstract::SetBackdropBlur(radius);
    }

    void SetFrontBlur(const Dimension& radius) override
    {
        ViewAbstract::SetFrontBlur(radius);
    }

    void SetBackShadow(const std::vector<Shadow>& shadows) override
    {
        if (!shadows.empty()) {
            ViewAbstract::SetBackShadow(shadows[0]);
        }
    }

    void SetColorBlend(const Color& value) override
    {
        ViewAbstract::SetColorBlend(value);
    }

    void SetWindowBlur(float progress, WindowBlurStyle blurStyle) override {}

    void SetBrightness(const Dimension& value) override
    {
        ViewAbstract::SetBrightness(value);
    }

    void SetGrayScale(const Dimension& value) override
    {
        ViewAbstract::SetGrayScale(value);
    }

    void SetContrast(const Dimension& value) override
    {
        ViewAbstract::SetContrast(value);
    }

    void SetSaturate(const Dimension& value) override
    {
        ViewAbstract::SetSaturate(value);
    }

    void SetSepia(const Dimension& value) override
    {
        ViewAbstract::SetSepia(value);
    }

    void SetInvert(const Dimension& value) override
    {
        ViewAbstract::SetInvert(value);
    }

    void SetHueRotate(float value) override
    {
        ViewAbstract::SetHueRotate(value);
    }

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override
    {
        ViewAbstract::SetOnClick(std::move(tapEventFunc));
    }

    void SetOnTouch(TouchEventFunc&& touchEventFunc) override
    {
        ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    }

    void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) override
    {
        ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    }

    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override
    {
        ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    }

    void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) override
    {
        ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    }

    void SetOnDelete(std::function<void()>&& onDeleteCallback) override {}

    void SetOnAppear(std::function<void()>&& onAppearCallback) override
    {
        ViewAbstract::SetOnAppear(std::move(onAppearCallback));
    }

    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override
    {
        ViewAbstract::SetOnDisappear(std::move(onDisAppearCallback));
    }

    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override {}

    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override {}

    void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) override {}

    void SetOnFocus(OnFocusFunc&& onFocusCallback) override
    {
        ViewAbstract::SetOnFocus(std::move(onFocusCallback));
    }

    void SetOnBlur(OnBlurFunc&& onBlurCallback) override
    {
        ViewAbstract::SetOnBlur(std::move(onBlurCallback));
    }

    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override
    {
        auto dragStart = [dragStartFunc = std::move(onDragStart)](const RefPtr<OHOS::Ace::DragEvent>& event,
                             const std::string& extraParams) -> DragDropInfo {
            auto dragInfo = dragStartFunc(event, extraParams);
            DragDropInfo info;
            info.extraInfo = dragInfo.extraInfo;
            info.pixelMap = dragInfo.pixelMap;
            info.customNode = AceType::DynamicCast<UINode>(dragInfo.node);
            return info;
        };
        ViewAbstract::SetOnDragStart(std::move(dragStart));
    }

    void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) override
    {
        ViewAbstract::SetOnDragEnter(std::move(onDragEnter));
    }

    void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) override
    {
        ViewAbstract::SetOnDragLeave(std::move(onDragLeave));
    }

    void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) override
    {
        ViewAbstract::SetOnDragMove(std::move(onDragMove));
    }

    void SetOnVisibleChange(
        std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratios) override
    {}

    void SetOnAreaChanged(
        std::function<void(const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)>&&
            onAreaChanged) override
    {
        auto areaChangeCallback = [areaChangeFunc = std::move(onAreaChanged)](const RectF& oldRect,
                                      const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
            areaChangeFunc(Rect(oldRect.GetX(), oldRect.GetY(), oldRect.Width(), oldRect.Height()),
                Offset(oldOrigin.GetX(), oldOrigin.GetY()), Rect(rect.GetX(), rect.GetY(), rect.Width(), rect.Height()),
                Offset(origin.GetX(), origin.GetY()));
        };
        ViewAbstract::SetOnAreaChanged(std::move(areaChangeCallback));
    }

    void SetOnDrop(NG::OnDragDropFunc&& onDrop) override
    {
        ViewAbstract::SetOnDrop(std::move(onDrop));
    }

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override
    {
        ViewAbstract::SetResponseRegion(responseRegion);
    }

    void SetEnabled(bool enabled) override
    {
        ViewAbstract::SetEnabled(enabled);
    }

    void SetTouchable(bool touchable) override
    {
        ViewAbstract::SetTouchable(touchable);
    }

    void SetFocusable(bool focusable) override
    {
        ViewAbstract::SetFocusable(focusable);
    }

    void SetFocusNode(bool focus) override {}

    void SetTabIndex(int32_t index) override
    {
        ViewAbstract::SetTabIndex(index);
    }

    void SetFocusOnTouch(bool isSet) override
    {
        ViewAbstract::SetFocusOnTouch(isSet);
    }

    void SetDefaultFocus(bool isSet) override
    {
        ViewAbstract::SetDefaultFocus(isSet);
    }

    void SetGroupDefaultFocus(bool isSet) override
    {
        ViewAbstract::SetGroupDefaultFocus(isSet);
    }

    void SetInspectorId(const std::string& inspectorId) override
    {
        ViewAbstract::SetInspectorId(inspectorId);
    }

    void SetRestoreId(int32_t restoreId) override {}

    void SetDebugLine(const std::string& line) override {}

    void SetHoverEffect(HoverEffectType hoverEffect) override
    {
        ViewAbstract::SetHoverEffect(hoverEffect);
    }

    void SetHitTestMode(NG::HitTestMode hitTestMode) override
    {
        ViewAbstract::SetHitTestMode(hitTestMode);
    }

    void BindPopup(const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode) override
    {
        auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ViewAbstract::BindPopup(param, targetNode, AceType::DynamicCast<UINode>(customNode));
    }

    void BindMenu(std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc) override
    {
        auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        GestureEventFunc event;
        if (!params.empty()) {
            event = [params, targetNode](GestureEvent& /*info*/) mutable {
                // menu already created
                if (params.empty()) {
                    NG::ViewAbstract::ShowMenu(targetNode->GetId());
                    return;
                }
                NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode);
            };
        } else if (buildFunc) {
            event = [builderFunc = std::move(buildFunc), targetNode](
                        const GestureEvent& /*info*/) mutable { CreateCustomMenu(builderFunc, targetNode); };
        } else {
            LOGE("empty param or null builder");
            return;
        }
        auto gestureHub = targetNode->GetOrCreateGestureEventHub();
        auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(event));
        gestureHub->AddClickEvent(onClick);

        // delete menu when target node is removed from render tree
        auto eventHub = targetNode->GetEventHub<NG::EventHub>();
        auto destructor = [id = targetNode->GetId()]() {
            auto pipeline = NG::PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto overlayManager = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->DeleteMenu(id);
        };
        eventHub->SetOnDisappear(destructor);
    }

    void BindContextMenu(ResponseType type, std::function<void()>&& buildFunc) override
    {
        auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(targetNode);
        auto hub = targetNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(hub);

        if (type == ResponseType::RIGHT_CLICK) {
            OnMouseEventFunc event = [builder = std::move(buildFunc), targetNode](MouseInfo& info) mutable {
                if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                    CreateCustomMenu(builder, targetNode);
                }
            };
            NG::ViewAbstract::SetOnMouse(std::move(event));
        } else if (type == ResponseType::LONGPRESS) {
            // create or show menu on long press
            auto event = [builder = std::move(buildFunc), targetNode](
                             const GestureEvent& /*info*/) mutable { CreateCustomMenu(builder, targetNode); };
            auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));

            hub->SetLongPressEvent(longPress);
        } else {
            LOGE("The arg responseType is invalid.");
            return;
        }
    }

    void SetAccessibilityGroup(bool accessible) override {}
    void SetAccessibilityText(const std::string& text) override {}
    void SetAccessibilityDescription(const std::string& description) override {}
    void SetAccessibilityImportance(const std::string& importance) override {}

private:
    static void CreateCustomMenu(std::function<void()>& buildFunc, const RefPtr<NG::FrameNode>& targetNode)
    {
        // builder already executed, just show menu
        if (!buildFunc) {
            NG::ViewAbstract::ShowMenu(targetNode->GetId());
            return;
        }
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        buildFunc();
        auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        NG::ViewAbstract::BindMenuWithCustomNode(customNode, targetNode);
        // nullify builder
        buildFunc = nullptr;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
