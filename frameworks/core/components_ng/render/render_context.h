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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H

#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/animation/page_transition_common.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/render_property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Rosen {
class RSNode;
namespace Drawing {
class Canvas;
}
}
namespace OHOS::Ace::NG {
class GeometryNode;
class RenderPropertyNode;
class FrameNode;
class Modifier;

using RSNode = Rosen::RSNode;
using RSCanvas = Rosen::Drawing::Canvas;
using CanvasDrawFunction = std::function<void(RSCanvas& canvas)>;

// RenderContext is used for render node to paint.
class RenderContext : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RenderContext, AceType)

public:
    ~RenderContext() override = default;

    static RefPtr<RenderContext> Create();

    void SetRequestFrame(const std::function<void()>& requestFrame);
    void RequestNextFrame() const;

    void SetHostNode(const WeakPtr<FrameNode>& host);
    RefPtr<FrameNode> GetHost() const;

    virtual void FlushContentDrawFunction(CanvasDrawFunction&& contentDraw) {}

    virtual void FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw) {}

    virtual void FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) {}

    virtual void FlushModifier(const RefPtr<Modifier>& modifier) {}

    virtual void RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void AddFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void RemoveFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void MoveFrame(FrameNode* self, const RefPtr<FrameNode>& child, int32_t index) {}

    virtual void SyncGeometryProperties(GeometryNode* geometryNode) {}

    virtual void SyncGeometryProperties(const RectF& rectF) {}

    virtual void OnModifyDone() {}

    virtual void InitContext(bool isRoot, const std::optional<std::string>& surfaceName, bool useExternalNode = false)
    {}

    virtual void StartRecording() {}
    virtual void StopRecordingIfNeeded() {}

    virtual void SetDrawContentAtLast(bool useDrawContentLastOrder) {}

    virtual void ResetBlendBgColor() {}

    virtual void BlendBgColor(const Color& color) {}

    virtual void ResetBlendBorderColor() {}

    virtual void BlendBorderColor(const Color& color) {}

    virtual void UpdateBorderWidthF(const BorderWidthPropertyF& value) {}

    // clip node without padding
    virtual void SetClipToFrame(bool useClip) {}

    // clip node with padding
    virtual void SetClipToBounds(bool useClip) {}

    virtual RefPtr<Canvas> GetCanvas() = 0;

    virtual void Restore() = 0;

    virtual void AnimateHoverEffectScale(bool isHovered) {}
    virtual void AnimateHoverEffectBoard(bool isHovered) {}
    virtual void UpdateTransition(const TransitionOptions& options) {}
    virtual bool TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish) const
    {
        return false;
    }

    virtual void AddChild(const RefPtr<RenderContext>& renderContext, int index) {}
    virtual void SetBounds(float positionX, float positionY, float width, float height) {}

    virtual void UpdateBackBlurRadius(const Dimension& radius) {}
    virtual void UpdateFrontBlurRadius(const Dimension& radius) {}
    virtual void UpdateBackShadow(const Shadow& shadow) {}

    virtual void ClipWithRect(const RectF& rectF) {}

    virtual void OnTransformTranslateUpdate(const Vector3F& value) {}

    virtual RectF GetPaintRectWithTransform()
    {
        return {};
    }

    virtual RectF GetPaintRectWithoutTransform()
    {
        return {};
    }

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const;

    virtual void ClearDrawCommands() {}

    virtual void NotifyTransition(
        const AnimationOption& option, const TransitionOptions& transOptions, bool isTransitionIn)
    {}

    // transform matrix
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TransformMatrix, Matrix4);

    // Transform
    ACE_DEFINE_PROPERTY_GROUP(Transform, TransformProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformScale, VectorF);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformCenter, DimensionOffset);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformTranslate, Vector3F);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformRotate, Vector4F);

    // Background
    ACE_DEFINE_PROPERTY_GROUP(Background, BackgroundProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImage, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageSize, BackgroundImageSize);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImagePosition, BackgroundImagePosition);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundBlurStyle, BlurStyle);

    // BorderImage
    ACE_DEFINE_PROPERTY_GROUP(BdImage, BorderImageProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImage, RefPtr<BorderImage>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImageSource, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageSlice, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageWidth, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageOutset, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageRepeat, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImageGradient, Gradient);

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BackgroundColor, Color);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Opacity, double);

    // Decoration
    ACE_DEFINE_PROPERTY_GROUP(BackDecoration, DecorationProperty);
    ACE_DEFINE_PROPERTY_GROUP(FrontDecoration, DecorationProperty);

    // Border
    // Graphics
    ACE_DEFINE_PROPERTY_GROUP(Graphics, GraphicsProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontBrightness, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontGrayScale, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontContrast, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontSaturate, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontSepia, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontInvert, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontHueRotate, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontColorBlend, Color);

    // BorderRadius.
    ACE_DEFINE_PROPERTY_GROUP(Border, BorderProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderColor, BorderColorProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderStyle, BorderStyleProperty);

    // Transition Options
    ACE_DEFINE_PROPERTY_GROUP(TransitionAppearing, TransitionOptions);
    ACE_DEFINE_PROPERTY_GROUP(TransitionDisappearing, TransitionOptions);

    // Position
    ACE_DEFINE_PROPERTY_GROUP(PositionProperty, RenderPositionProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, Position, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, Offset, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, Anchor, OffsetT<Dimension>);

    // zIndex
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ZIndex, int32_t);

    // Clip
    ACE_DEFINE_PROPERTY_GROUP(Clip, ClipProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Clip, ClipShape, ClipPathNG);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Clip, ClipEdge, bool);

    // Gradient
    ACE_DEFINE_PROPERTY_GROUP(Gradient, GradientProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, LinearGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, SweepGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, RadialGradient, NG::Gradient);

protected:
    RenderContext() = default;

    virtual void OnBackgroundColorUpdate(const Color& value) {}
    virtual void OnBackgroundImageUpdate(const ImageSourceInfo& imageSourceInfo) {}
    virtual void OnBackgroundImageRepeatUpdate(const ImageRepeat& imageRepeat) {}
    virtual void OnBackgroundImageSizeUpdate(const BackgroundImageSize& bgImgSize) {}
    virtual void OnBackgroundImagePositionUpdate(const BackgroundImagePosition& bgImgPosition) {}
    virtual void OnBackgroundBlurStyleUpdate(const BlurStyle& bgBlurStyle) {}

    virtual void OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) {}
    virtual void OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo) {}
    virtual void OnHasBorderImageSliceUpdate(bool tag) {}
    virtual void OnHasBorderImageWidthUpdate(bool tag) {}
    virtual void OnHasBorderImageOutsetUpdate(bool tag) {}
    virtual void OnHasBorderImageRepeatUpdate(bool tag) {}
    virtual void OnBorderImageGradientUpdate(const Gradient& gradient) {}

    virtual void OnBorderRadiusUpdate(const BorderRadiusProperty& value) {}
    virtual void OnBorderColorUpdate(const BorderColorProperty& value) {}
    virtual void OnBorderStyleUpdate(const BorderStyleProperty& value) {}
    virtual void OnOpacityUpdate(double opacity) {}

    virtual void OnTransformScaleUpdate(const VectorF& value) {}
    virtual void OnTransformCenterUpdate(const DimensionOffset& value) {}
    virtual void OnTransformRotateUpdate(const Vector4F& value) {}
    virtual void OnTransformMatrixUpdate(const Matrix4& matrix) {}

    virtual void OnPositionUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnOffsetUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnAnchorUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnZIndexUpdate(int32_t value) {}

    virtual void OnClipShapeUpdate(const ClipPathNG& clipPath) {}
    virtual void OnClipEdgeUpdate(bool isClip) {}

    virtual void OnLinearGradientUpdate(const NG::Gradient& value) {}
    virtual void OnSweepGradientUpdate(const NG::Gradient& value) {}
    virtual void OnRadialGradientUpdate(const NG::Gradient& value) {}

    virtual void OnFrontBrightnessUpdate(const Dimension& value) {}
    virtual void OnFrontGrayScaleUpdate(const Dimension& value) {}
    virtual void OnFrontContrastUpdate(const Dimension& value) {}
    virtual void OnFrontSaturateUpdate(const Dimension& value) {}
    virtual void OnFrontSepiaUpdate(const Dimension& value) {}
    virtual void OnFrontInvertUpdate(const Dimension& value) {}
    virtual void OnFrontHueRotateUpdate(float value) {}
    virtual void OnFrontColorBlendUpdate(const Color& value) {}

private:
    std::function<void()> requestFrame_;
    WeakPtr<FrameNode> host_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
