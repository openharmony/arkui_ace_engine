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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H

#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/animation/page_transition_common.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/particle_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/particle_property_animation.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/render_property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Rosen {
class DrawCmdList;
enum class Gravity;
}

namespace OHOS::Ace::NG {
class GeometryNode;
class RenderPropertyNode;
class FrameNode;
class Modifier;

using CanvasDrawFunction = std::function<void(RSCanvas& canvas)>;

inline constexpr int32_t ZINDEX_DEFAULT_VALUE = 0;

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

    virtual void SetNeedDebugBoundary(bool flag) {}
    virtual bool NeedDebugBoundary() const
    {
        return false;
    }

    virtual void FlushContentDrawFunction(CanvasDrawFunction&& contentDraw) {}

    virtual void FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw) {}

    virtual void FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) {}

    virtual void FlushContentModifier(const RefPtr<Modifier>& modifier) {}
    virtual void FlushForegroundModifier(const RefPtr<Modifier>& modifier) {}
    virtual void FlushOverlayModifier(const RefPtr<Modifier>& modifier) {}

    virtual void RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void AddFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void RemoveFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) {};

    virtual void MoveFrame(FrameNode* self, const RefPtr<FrameNode>& child, int32_t index) {}

    virtual void SyncGeometryProperties(GeometryNode* geometryNode) {}

    virtual void SyncGeometryProperties(const RectF& rectF) {}

    virtual void SetBorderRadius(const BorderRadiusProperty& value) {}

    // draw self and children in sandbox origin at parent's absolute position in root, drawing in sandbox
    // will be unaffected by parent's transition.
    virtual void SetSandBox(const std::optional<OffsetF>& parentPosition, bool force = false) {};

    virtual void RegisterSharedTransition(const RefPtr<RenderContext>& other) {}
    virtual void UnregisterSharedTransition(const RefPtr<RenderContext>& other) {}

    virtual void OnModifyDone() {}

    enum class ContextType : int8_t { CANVAS, ROOT, SURFACE, EFFECT, EXTERNAL, INCREMENTAL_CANVAS, HARDWARE_SURFACE };
    struct ContextParam {
        ContextType type;
        std::optional<std::string> surfaceName;
    };
    virtual void InitContext(bool isRoot, const std::optional<ContextParam>& param)
    {}

    virtual void SetSurfaceChangedCallBack(
        const std::function<void(float, float, float, float)>& callback) {}
    virtual void RemoveSurfaceChangedCallBack() {}

    virtual void StartRecording() {}
    virtual void StopRecordingIfNeeded() {}

    virtual void SetDrawContentAtLast(bool useDrawContentLastOrder) {}

    virtual void ResetBlendBgColor() {}

    virtual void BlendBgColor(const Color& color) {}

    virtual void ResetBlendBorderColor() {}

    virtual void BlendBorderColor(const Color& color) {}

    // Paint focus state by component's setting. It will paint along the paintRect
    virtual void PaintFocusState(const RoundRect& paintRect, const Color& paintColor, const Dimension& paintWidth,
        bool isAccessibilityFocus = false)
    {}
    // Paint focus state by component's setting. It will paint along the frameRect(padding: focusPaddingVp)
    virtual void PaintFocusState(const RoundRect& paintRect, const Dimension& focusPaddingVp, const Color& paintColor,
        const Dimension& paintWidth, bool isAccessibilityFocus = false)
    {}
    // Paint focus state by default. It will paint along the component rect(padding: focusPaddingVp)
    virtual void PaintFocusState(const Dimension& focusPaddingVp, const Color& paintColor, const Dimension& paintWidth)
    {}

    virtual void ClearFocusState() {}

    virtual void CreateBackgroundPixelMap(const RefPtr<FrameNode>& value) {}

    virtual void UpdateBorderWidthF(const BorderWidthPropertyF& value) {}

    // clip node without padding
    virtual void SetClipToFrame(bool useClip) {}

    // clip node with padding
    virtual void SetClipToBounds(bool useClip) {}
    virtual void SetClipBoundsWithCommands(const std::string& commands) {};
    virtual void SetVisible(bool visible) {}

    virtual void MarkContentChanged(bool isChanged) {}
    virtual void MarkDrivenRender(bool flag) {}
    virtual void MarkDrivenRenderItemIndex(int32_t index) {}
    virtual void MarkDrivenRenderFramePaintState(bool flag) {}

    virtual void AnimateHoverEffectScale(bool isHovered) {}
    virtual void AnimateHoverEffectBoard(bool isHovered) {}

    virtual void UpdateTransition(const TransitionOptions& options) {}
    virtual void UpdateChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect) {}
    virtual void OnNodeDisappear(bool recursive) {}
    virtual void OnNodeAppear(bool recursive) {}
    virtual bool HasTransitionOutAnimation() const
    {
        return false;
    }

    virtual bool HasTransition() const
    {
        return false;
    }

    virtual bool IsSynced() const
    {
        return isSynced_;
    }

    virtual bool TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish)
    {
        return false;
    }

    virtual void SetSharedTranslate(float xTranslate, float yTranslate) {}
    virtual void ResetSharedTranslate() {}
    virtual void ResetPageTransitionEffect() {}

    virtual void AddChild(const RefPtr<RenderContext>& renderContext, int index) {}
    virtual void RemoveChild(const RefPtr<RenderContext>& renderContext) {}
    virtual void SetBounds(float positionX, float positionY, float width, float height) {}
    virtual void SetContentRectToFrame(RectF rect) {}

    virtual void UpdateBackBlurRadius(const Dimension& radius) {}
    virtual void UpdateBackBlurStyle(const std::optional<BlurStyleOption>& bgBlurStyle) {}
    virtual void UpdateBackgroundEffect(const std::optional<EffectOption>& effectOption) {}
    virtual void UpdateFrontBlurStyle(const std::optional<BlurStyleOption>& fgBlurStyle) {}
    virtual void UpdateFrontBlurRadius(const Dimension& radius) {}
    virtual void ResetBackBlurStyle() {}
    virtual void ClipWithRect(const RectF& rectF) {}
    virtual void ClipWithRRect(const RectF& rectF, const RadiusF& radiusF) {}

    virtual void OpacityAnimation(const AnimationOption& option, double begin, double end) {}
    virtual void ScaleAnimation(const AnimationOption& option, double begin, double end) {}

    virtual void OnTransformTranslateUpdate(const TranslateOptions& value) {}
    virtual void OnTransformScaleUpdate(const VectorF& value) {}
    virtual void OnTransformCenterUpdate(const DimensionOffset& value) {}
    virtual void OnOffsetUpdate(const OffsetT<Dimension>& value) {}

    virtual RectF GetPaintRectWithTransform()
    {
        return {};
    }

    virtual RectF GetPaintRectWithTranslate()
    {
        return {};
    }

    virtual void GetPointWithTransform(PointF& point) {}

    virtual RectF GetPaintRectWithoutTransform()
    {
        return {};
    }

    // get position property
    virtual RectF GetPropertyOfPosition()
    {
        return {};
    }

    // stop the property animation and get the current paint rect.
    virtual OffsetF GetShowingTranslateProperty()
    {
        return OffsetF();
    }
    // update translateXY in backend.
    virtual void UpdateTranslateInXY(const OffsetF& offset) {}

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const;

    virtual void FromJson(const std::unique_ptr<JsonValue>& json);

    virtual void ClearDrawCommands() {}

    virtual void DumpInfo() const {}

    void ObscuredToJsonValue(std::unique_ptr<JsonValue>& json) const;

    void SetSharedTransitionOptions(const std::shared_ptr<SharedTransitionOption>& option)
    {
        sharedTransitionOption_ = option;
    }
    const std::shared_ptr<SharedTransitionOption>& GetSharedTransitionOption() const
    {
        return sharedTransitionOption_;
    }
    void SetShareId(const ShareId& shareId)
    {
        shareId_ = shareId;
    }
    const ShareId& GetShareId() const
    {
        return shareId_;
    }
    bool HasSharedTransition() const
    {
        return !shareId_.empty();
    }
    bool HasSharedTransitionOption() const
    {
        return sharedTransitionOption_ != nullptr;
    }

    void SetIsModalRootNode(bool isModalRootNode)
    {
        isModalRootNode_ = isModalRootNode;
    }

    std::optional<BlurStyleOption> GetBackBlurStyle() const
    {
        return GetBackground() ? GetBackground()->propBlurStyleOption : std::nullopt;
    }
    std::optional<Dimension> GetBackBlurRadius() const
    {
        return GetBackground() ? GetBackground()->propBlurRadius : std::nullopt;
    }
    std::optional<EffectOption> GetBackgroundEffect() const
    {
        return GetBackground() ? GetBackground()->propEffectOption : std::nullopt;
    }
    std::optional<BlurStyleOption> GetFrontBlurStyle() const
    {
        return GetForeground() ? GetForeground()->propBlurStyleOption : std::nullopt;
    }
    std::optional<Dimension> GetFrontBlurRadius() const
    {
        return GetForeground() ? GetForeground()->propBlurRadius : std::nullopt;
    }

    virtual void AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier) {};

    virtual void PaintAccessibilityFocus() {};

    virtual void ClearAccessibilityFocus() {};

    virtual void OnAccessibilityFocusUpdate(bool isAccessibilityFocus) {};

    virtual void OnMouseSelectUpdate(bool isSelected, const Color& fillColor, const Color& strokeColor) {}
    virtual void UpdateMouseSelectWithRect(const RectF& rect, const Color& fillColor, const Color& strokeColor) {}

    virtual void OnPositionUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnZIndexUpdate(int32_t value) {}

    virtual void OnBackgroundColorUpdate(const Color& value) {}
    virtual void OnSphericalEffectUpdate(double radio) {}
    virtual void OnPixelStretchEffectUpdate(const PixStretchEffectOption& option) {}
    virtual void OnLightUpEffectUpdate(double radio) {}
    virtual void OnClickEffectLevelUpdate(const ClickEffectInfo& info) {}
    virtual void OnRenderGroupUpdate(bool isRenderGroup) {}
    virtual void OnRenderFitUpdate(RenderFit renderFit) {}
    virtual void OnParticleOptionArrayUpdate(const std::list<ParticleOption>& optionArray) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SphericalEffect, double);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PixelStretchEffect, PixStretchEffectOption);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(LightUpEffect, double);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ParticleOptionArray, std::list<ParticleOption>);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ClickEffectLevel, ClickEffectInfo);
    virtual RefPtr<PixelMap> GetThumbnailPixelMap()
    {
        return nullptr;
    }

    virtual void SetActualForegroundColor(const Color& value) {}
    // transform matrix
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TransformMatrix, Matrix4);

    // Transform
    ACE_DEFINE_PROPERTY_GROUP(Transform, TransformProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformScale, VectorF);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformCenter, DimensionOffset);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformTranslate, TranslateOptions);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Transform, TransformRotate, Vector5F);

    // Foreground
    ACE_DEFINE_PROPERTY_GROUP(Foreground, ForegroundProperty);

    // Background
    ACE_DEFINE_PROPERTY_GROUP(Background, BackgroundProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImage, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageSize, BackgroundImageSize);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImagePosition, BackgroundImagePosition);

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
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RenderGroup, bool);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ForegroundColor, Color);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ForegroundColorStrategy, ForegroundColorStrategy);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ForegroundColorFlag, bool);

    // CustomBackground
    ACE_DEFINE_PROPERTY_GROUP(CustomBackground, CustomBackgroundProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(CustomBackground, BackgroundPixelMap, RefPtr<PixelMap>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(CustomBackground, BackgroundAlign, Alignment);

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
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, LinearGradientBlur, NG::LinearGradientBlurPara);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, DynamicLightUpRate, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, DynamicLightUpDegree, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, BackShadow, Shadow);

    // BorderRadius.
    ACE_DEFINE_PROPERTY_GROUP(Border, BorderProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderWidth, BorderWidthProperty);
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
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Clip, ClipShape, RefPtr<BasicShape>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Clip, ClipEdge, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Clip, ClipMask, RefPtr<BasicShape>);

    // ProgressMask
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ProgressMask, RefPtr<ProgressMaskProperty>);

    // Gradient
    ACE_DEFINE_PROPERTY_GROUP(Gradient, GradientProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, LinearGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, SweepGradient, NG::Gradient);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, RadialGradient, NG::Gradient);

    // Overlay
    ACE_DEFINE_PROPERTY_GROUP(Overlay, OverlayProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Overlay, OverlayText, OverlayOptions)

    // MotionPath
    ACE_DEFINE_PROPERTY_GROUP(Motion, MotionPathProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Motion, MotionPath, MotionPathOption)

    // accessibility
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(AccessibilityFocus, bool);

    // useEffect
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(UseEffect, bool);

    // freeze
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Freeze, bool);

    // obscured
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Obscured, std::vector<ObscuredReasons>);

    // renderFit
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RenderFit, RenderFit);

    virtual void SetUsingContentRectForRenderFrame(bool value) {}
    virtual std::vector<double> GetTrans()
    {
        return std::vector<double>();
    }
    virtual void SetFrameGravity(OHOS::Rosen::Gravity gravity) {}

    virtual void AddFRCSceneInfo(const std::string& scene, float speed) {}

protected:
    RenderContext() = default;
    std::shared_ptr<SharedTransitionOption> sharedTransitionOption_;
    ShareId shareId_;
    bool isModalRootNode_ = false;
    bool isSynced_ = false;

    virtual void OnBackgroundImageUpdate(const ImageSourceInfo& imageSourceInfo) {}
    virtual void OnBackgroundImageRepeatUpdate(const ImageRepeat& imageRepeat) {}
    virtual void OnBackgroundImageSizeUpdate(const BackgroundImageSize& bgImgSize) {}
    virtual void OnBackgroundImagePositionUpdate(const BackgroundImagePosition& bgImgPosition) {}

    virtual void OnForegroundColorUpdate(const Color& value) {}
    virtual void OnForegroundColorStrategyUpdate(const ForegroundColorStrategy& value) {}

    virtual void OnBackgroundPixelMapUpdate(const RefPtr<PixelMap>& value) {}
    virtual void OnBackgroundAlignUpdate(const Alignment& align) {}

    virtual void OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) {}
    virtual void OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo) {}
    virtual void OnHasBorderImageSliceUpdate(bool tag) {}
    virtual void OnHasBorderImageWidthUpdate(bool tag) {}
    virtual void OnHasBorderImageOutsetUpdate(bool tag) {}
    virtual void OnHasBorderImageRepeatUpdate(bool tag) {}
    virtual void OnBorderImageGradientUpdate(const Gradient& gradient) {}

    virtual void OnBorderWidthUpdate(const BorderWidthProperty& value) {}
    virtual void OnBorderRadiusUpdate(const BorderRadiusProperty& value) {}
    virtual void OnBorderColorUpdate(const BorderColorProperty& value) {}
    virtual void OnBorderStyleUpdate(const BorderStyleProperty& value) {}
    virtual void OnOpacityUpdate(double opacity) {}

    virtual void OnTransformRotateUpdate(const Vector5F& value) {}
    virtual void OnTransformMatrixUpdate(const Matrix4& matrix) {}

    virtual void OnAnchorUpdate(const OffsetT<Dimension>& value) {}

    virtual void OnClipShapeUpdate(const RefPtr<BasicShape>& basicShape) {}
    virtual void OnClipEdgeUpdate(bool isClip) {}
    virtual void OnClipMaskUpdate(const RefPtr<BasicShape>& basicShape) {}

    virtual void OnProgressMaskUpdate(const RefPtr<ProgressMaskProperty>& progress) {}

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
    virtual void OnLinearGradientBlurUpdate(const NG::LinearGradientBlurPara& blurPara) {}
    virtual void OnDynamicLightUpRateUpdate(const float rate) {}
    virtual void OnDynamicLightUpDegreeUpdate(const float degree) {}
    virtual void OnBackShadowUpdate(const Shadow& shadow) {}

    virtual void OnOverlayTextUpdate(const OverlayOptions& overlay) {}
    virtual void OnMotionPathUpdate(const MotionPathOption& motionPath) {}
    virtual void OnUseEffectUpdate(bool useEffect) {}
    virtual void OnFreezeUpdate(bool isFreezed) {}
    virtual void OnObscuredUpdate(const std::vector<ObscuredReasons>& reasons) {}

private:
    std::function<void()> requestFrame_;
    WeakPtr<FrameNode> host_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
