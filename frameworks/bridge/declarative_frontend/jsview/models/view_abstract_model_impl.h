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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H

#include "base/utils/macros.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

class ViewAbstractModelImpl : public ViewAbstractModel {
public:
    ~ViewAbstractModelImpl() override = default;

    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetMinWidth(const Dimension& minWidth) override;
    void SetMinHeight(const Dimension& minHeight) override;
    void SetMaxWidth(const Dimension& maxWidth) override;
    void SetMaxHeight(const Dimension& maxHeight) override;

    void SetBackgroundColor(const Color& color) override;
    void SetBackgroundImage(const std::string& src, RefPtr<ThemeConstants> themeConstant) override;
    void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) override;
    void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) override;
    void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) override;
    void SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle) override;
    void SetPadding(const Dimension& value) override;
    void SetPaddings(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right) override;
    void SetMargin(const Dimension& value) override;
    void SetMargins(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right) override;
    void SetBorderRadius(const Dimension& value) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override;
    void SetBorderColor(const Color& value) override;
    void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override;
    void SetBorderWidth(const Dimension& value) override;
    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override;
    void SetBorderStyle(const BorderStyle& value) override;
    void SetBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override;

    void SetLayoutPriority(int32_t priority) override;
    void SetLayoutWeight(int32_t value) override;
    void SetAspectRatio(float ratio) override;
    void SetAlign(const Alignment& alignment) override;

    void SetPosition(const Dimension& x, const Dimension& y) override;
    void SetOffset(const Dimension& x, const Dimension& y) override;
    void MarkAnchor(const Dimension& x, const Dimension& y) override;

    void SetScale(float x, float y, float z) override;
    void SetPivot(const Dimension& x, const Dimension& y) override;
    void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) override;
    void SetRotate(float x, float y, float z, float angle) override;
    void SetTransformMatrix(const std::vector<float>& matrix) override;

    void SetOpacity(double opacity) override;
    void SetTransition(const NG::TransitionOptions& transitionOptions) override;
    void SetOverlay(const std::string& text, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY) override;
    void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) override;
    void SetSharedTransition(const SharedTransitionOption& option) override;
    void SetGeometryTransition(const std::string& id) override;

    void SetFlexBasis(const Dimension& value) override;
    void SetAlignSelf(FlexAlign value) override;
    void SetFlexShrink(float value) override;
    void SetFlexGrow(float value) override;
    void SetDisplayIndex(int32_t value) override;

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override;
    void SetOnTouch(TouchEventFunc&& touchEventFunc) override;
    void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) override;
    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override;
    void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) override;
    void SetOnDelete(std::function<void()>&& onDeleteCallback) override;
    void SetOnAppear(std::function<void()>&& onAppearCallback) override;
    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override;
    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override;
    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override;

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void SetEnabled(bool enabled) override;
    void SetTouchable(bool touchable) override;
    void SetFocusable(bool focusable) override;
    void SetFocusNode(bool focus) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H
