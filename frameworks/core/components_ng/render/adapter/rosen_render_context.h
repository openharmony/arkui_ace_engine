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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_CONTEXT_H

#include <cstdint>
#include <memory>
#include <optional>

#include "include/core/SkCanvas.h"
#include "include/core/SkPictureRecorder.h"
#include "include/core/SkRefCnt.h"
#include "render_service_client/core/ui/rs_node.h"

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/render/adapter/graphic_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_property.h"
#include "core/components_ng/render/adapter/rosen_transition_effect.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class BackgroundModifier;
class BorderImageModifier;
class DebugBoundaryModifier;
class MouseSelectModifier;
class MoonProgressModifier;
class FocusStateModifier;
class PageTransitionEffect;
class OverlayTextModifier;
class GradientStyleModifier;
class RosenRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(RosenRenderContext, NG::RenderContext)
public:
    RosenRenderContext() = default;
    ~RosenRenderContext() override;

    void InitContext(bool isRoot, const std::optional<ContextParam>& param) override;

    void SyncGeometryProperties(GeometryNode* geometryNode) override;

    void SyncGeometryProperties(const RectF& paintRect) override;

    void SetSandBox(const std::optional<OffsetF>& parentPosition) override;

    void RebuildFrame(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) override;

    void AddFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) override;

    void RemoveFrameChildren(FrameNode* self, const std::list<RefPtr<FrameNode>>& children) override;

    void MoveFrame(FrameNode* self, const RefPtr<FrameNode>& child, int32_t index) override;

    void OnModifyDone() override;

    void ResetBlendBgColor() override;

    void BlendBgColor(const Color& color) override;

    void ResetBlendBorderColor() override;

    void BlendBorderColor(const Color& color) override;

    // Paint focus state by component's setting. It will paint along the paintRect
    void PaintFocusState(const RoundRect& paintRect, const Color& paintColor, const Dimension& paintWidth,
        bool isAccessibilityFocus = false) override;
    // Paint focus state by component's setting. It will paint along the frameRect(padding: focusPaddingVp)
    void PaintFocusState(const RoundRect& paintRect, const Dimension& focusPaddingVp, const Color& paintColor,
        const Dimension& paintWidth, bool isAccessibilityFocus = false) override;
    // Paint focus state by default. It will paint along the component rect(padding: focusPaddingVp)
    void PaintFocusState(
        const Dimension& focusPaddingVp, const Color& paintColor, const Dimension& paintWidth) override;

    void ClearFocusState() override;

    const std::shared_ptr<Rosen::RSNode>& GetRSNode();

    void SetRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode);

    void StartRecording() override;

    void StopRecordingIfNeeded() override;

    void SetDrawContentAtLast(bool useDrawContentLastOrder) override
    {
        CHECK_NULL_VOID(rsNode_);
        rsNode_->SetPaintOrder(useDrawContentLastOrder);
    }

    void SetClipToFrame(bool useClip) override
    {
        CHECK_NULL_VOID(rsNode_);
        rsNode_->SetClipToFrame(useClip);
    }

    void SetClipToBounds(bool useClip) override
    {
        CHECK_NULL_VOID(rsNode_);
        rsNode_->SetClipToBounds(useClip);
    }

    void SetVisible(bool visible) override
    {
        CHECK_NULL_VOID(rsNode_);
        rsNode_->SetVisible(visible);
    }

    void FlushContentDrawFunction(CanvasDrawFunction&& contentDraw) override;

    void FlushForegroundDrawFunction(CanvasDrawFunction&& foregroundDraw) override;

    void FlushOverlayDrawFunction(CanvasDrawFunction&& overlayDraw) override;

    void AnimateHoverEffectScale(bool isHovered) override;
    void AnimateHoverEffectBoard(bool isHovered) override;
    void UpdateBackBlurRadius(const Dimension& radius) override;
    void UpdateBackBlurStyle(const std::optional<BlurStyleOption>& bgBlurStyle) override;
    void UpdateBackgroundEffect(const std::optional<EffectOption>& effectOption) override;
    void UpdateFrontBlurRadius(const Dimension& radius) override;
    void UpdateFrontBlurStyle(const std::optional<BlurStyleOption>& fgBlurStyle) override;
    void ResetBackBlurStyle() override;
    void OnSphericalEffectUpdate(double radio) override;
    void OnPixelStretchEffectUpdate(const PixStretchEffectOption& option) override;
    void OnLightUpEffectUpdate(double radio) override;
    void OnBackShadowUpdate(const Shadow& shadow) override;
    void UpdateBorderWidthF(const BorderWidthPropertyF& value) override;

    void OnTransformMatrixUpdate(const Matrix4& matrix) override;

    void UpdateTransition(const TransitionOptions& options) override;
    void UpdateChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect) override;
    bool HasAppearingTransition() const
    {
        return propTransitionAppearing_ != nullptr;
    }
    bool HasDisappearingTransition() const
    {
        return propTransitionDisappearing_ != nullptr;
    }
    void OnNodeAppear(bool recursive) override;
    void OnNodeDisappear(bool recursive) override;
    void ClipWithRect(const RectF& rectF) override;
    void ClipWithRRect(const RectF& rectF, const RadiusF& radiusF) override;

    bool TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish) override;

    void SetSharedTranslate(float xTranslate, float yTranslate) override;
    void ResetSharedTranslate() override;
    void ResetPageTransitionEffect() override;

    static std::list<std::shared_ptr<Rosen::RSNode>> GetChildrenRSNodes(
        const std::list<RefPtr<FrameNode>>& frameChildren);

    // if translate params use percent dimension, frameSize should be given correctly
    static std::shared_ptr<Rosen::RSTransitionEffect> GetRSTransitionWithoutType(
        const std::unique_ptr<TransitionOptions>& options, const SizeF& frameSize = SizeF());

    static float ConvertDimensionToScaleBySize(const Dimension& dimension, float size);

    void FlushContentModifier(const RefPtr<Modifier>& modifier) override;
    void FlushOverlayModifier(const RefPtr<Modifier>& modifier) override;

    void AddChild(const RefPtr<RenderContext>& renderContext, int index) override;
    void RemoveChild(const RefPtr<RenderContext>& renderContext) override;
    void SetBounds(float positionX, float positionY, float width, float height) override;
    void OnTransformTranslateUpdate(const TranslateOptions& value) override;

    RectF GetPaintRectWithTransform() override;

    RectF GetPaintRectWithTranslate() override;

    RectF GetPaintRectWithoutTransform() override;

    // get position property
    RectF GetPropertyOfPosition() override;

    // append translate value and return origin value.
    void UpdateTranslateInXY(const OffsetF& offset) override;
    OffsetF GetShowingTranslateProperty() override;

    void GetPointWithTransform(PointF& point) override;

    void ClearDrawCommands() override;

    void OpacityAnimation(const AnimationOption& option, double begin, double end) override;
    void ScaleAnimation(const AnimationOption& option, double begin, double end) override;

    void PaintAccessibilityFocus() override;

    void ClearAccessibilityFocus() override;

    void OnAccessibilityFocusUpdate(bool isAccessibilityFocus) override;

    void OnMouseSelectUpdate(bool isSelected, const Color& fillColor, const Color& strokeColor) override;
    void UpdateMouseSelectWithRect(const RectF& rect, const Color& fillColor, const Color& strokeColor) override;

    void OnPositionUpdate(const OffsetT<Dimension>& value) override;
    void OnZIndexUpdate(int32_t value) override;
    void DumpInfo() const override;
    void SetClipBoundsWithCommands(const std::string& commands) override;
    void SetNeedDebugBoundary(bool flag) override
    {
        needDebugBoundary_ = flag;
    }

    bool NeedDebugBoundary() const override
    {
        return needDebugBoundary_;
    }

    void OnBackgroundAlignUpdate(const Alignment& align) override;
    void OnBackgroundPixelMapUpdate(const RefPtr<PixelMap>& value) override;
    void CreateBackgroundPixelMap(const RefPtr<FrameNode>& customNode) override;

    void OnBackgroundColorUpdate(const Color& value) override;

    void MarkContentChanged(bool isChanged) override;
    void MarkDrivenRender(bool flag) override;
    void MarkDrivenRenderItemIndex(int32_t index) override;
    void MarkDrivenRenderFramePaintState(bool flag) override;
    RefPtr<PixelMap> GetThumbnailPixelMap() override;
#ifndef USE_ROSEN_DRAWING
    bool GetBitmap(SkBitmap& bitmap, std::shared_ptr<OHOS::Rosen::DrawCmdList> drawCmdList = nullptr);
#else
    bool GetBitmap(RSBitmap& bitmap, std::shared_ptr<RSDrawCmdList> drawCmdList = nullptr);
#endif
    void SetActualForegroundColor(const Color& value) override;
    void AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> property) override;

    void RegisterSharedTransition(const RefPtr<RenderContext>& other) override;
    void UnregisterSharedTransition(const RefPtr<RenderContext>& other) override;

    void SetUsingContentRectForRenderFrame(bool value) override;

private:
    void OnBackgroundImageUpdate(const ImageSourceInfo& src) override;
    void OnBackgroundImageRepeatUpdate(const ImageRepeat& imageRepeat) override;
    void OnBackgroundImageSizeUpdate(const BackgroundImageSize& bgImgSize) override;
    void OnBackgroundImagePositionUpdate(const BackgroundImagePosition& bgImgPosition) override;

    void OnForegroundColorUpdate(const Color& value) override;
    void OnForegroundColorStrategyUpdate(const ForegroundColorStrategy& value) override;

    void OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) override;
    void OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo) override;
    void OnHasBorderImageSliceUpdate(bool tag) override {}
    void OnHasBorderImageWidthUpdate(bool tag) override {}
    void OnHasBorderImageOutsetUpdate(bool tag) override {}
    void OnHasBorderImageRepeatUpdate(bool tag) override {}
    void OnBorderImageGradientUpdate(const Gradient& gradient) override;

    void OnBorderRadiusUpdate(const BorderRadiusProperty& value) override;
    void OnBorderColorUpdate(const BorderColorProperty& value) override;
    void OnBorderStyleUpdate(const BorderStyleProperty& value) override;
    void OnOpacityUpdate(double opacity) override;

    void OnTransformScaleUpdate(const VectorF& value) override;
    void OnTransformCenterUpdate(const DimensionOffset& value) override;
    void OnTransformRotateUpdate(const Vector5F& value) override;

    void OnOffsetUpdate(const OffsetT<Dimension>& value) override;
    void OnAnchorUpdate(const OffsetT<Dimension>& value) override;

    void OnClipShapeUpdate(const RefPtr<BasicShape>& basicShape) override;
    void OnClipEdgeUpdate(bool isClip) override;
    void OnClipMaskUpdate(const RefPtr<BasicShape>& basicShape) override;

    void OnProgressMaskUpdate(const RefPtr<ProgressMaskProperty>& progress) override;

    void OnLinearGradientUpdate(const NG::Gradient& value) override;
    void OnSweepGradientUpdate(const NG::Gradient& value) override;
    void OnRadialGradientUpdate(const NG::Gradient& value) override;

    void OnFrontBrightnessUpdate(const Dimension& brightness) override;
    void OnFrontGrayScaleUpdate(const Dimension& grayScale) override;
    void OnFrontContrastUpdate(const Dimension& contrast) override;
    void OnFrontSaturateUpdate(const Dimension& saturate) override;
    void OnFrontSepiaUpdate(const Dimension& sepia) override;
    void OnFrontInvertUpdate(const Dimension& invert) override;
    void OnFrontHueRotateUpdate(float hueRotate) override;
    void OnFrontColorBlendUpdate(const Color& colorBlend) override;
    void OnLinearGradientBlurUpdate(const NG::LinearGradientBlurPara& blurPara) override;

    void OnOverlayTextUpdate(const OverlayOptions& overlay) override;
    void OnMotionPathUpdate(const MotionPathOption& motionPath) override;

    void OnUseEffectUpdate(bool useEffect) override;
    void OnFreezeUpdate(bool isFreezed) override;
    void OnRenderGroupUpdate(bool isRenderGroup) override;
    void OnRenderFitUpdate(RenderFit renderFit) override;
    void ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children);

    void NotifyTransitionInner(const SizeF& frameSize, bool isTransitionIn);
    void NotifyTransition(bool isTransitionIn);
    bool HasTransitionOutAnimation() const override
    {
        return disappearingTransitionCount_ > 0;
    }
    bool HasTransition() const override
    {
        return transitionEffect_ != nullptr;
    }
    void OnTransitionInFinish();
    void OnTransitionOutFinish();
    void RemoveDefaultTransition();
    void SetTransitionPivot(const SizeF& frameSize, bool transitionIn);
    void SetPivot(float xPivot, float yPivot, float zPivot = 0.0f);
    void SetPositionToRSNode();

    RefPtr<PageTransitionEffect> GetDefaultPageTransition(PageTransitionType type);
    RefPtr<PageTransitionEffect> GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition);

    // Convert BorderRadiusProperty to Rosen::Vector4f
    static inline void ConvertRadius(const BorderRadiusProperty& value, Rosen::Vector4f& cornerRadius);

    void PaintBackground();
    void PaintClip(const SizeF& frameSize);
    void PaintProgressMask();
    void PaintGradient(const SizeF& frameSize);
    void PaintGraphics();
    void PaintOverlayText();
    void PaintBorderImage();
#ifndef USE_ROSEN_DRAWING
    void PaintSkBgImage();
#else
    void PaintRSBgImage();
#endif
    void PaintPixmapBgImage();
    void PaintBorderImageGradient();
    void PaintMouseSelectRect(const RectF& rect, const Color& fillColor, const Color& strokeColor);
    void SetBackBlurFilter();
    void SetFrontBlurFilter();
    void GetPaddingOfFirstFrameNodeParent(Dimension& parentPaddingLeft, Dimension& parentPaddingTop);
    void CombineMarginAndPosition(Dimension& resultX, Dimension& resultY, const Dimension& parentPaddingLeft,
        const Dimension& parentPaddingTop, float widthPercentReference, float heightPercentReference);

    void InitEventClickEffect();
    RefPtr<Curve> UpdatePlayAnimationValue(const ClickEffectLevel& level, float& scaleValue);
    void ClickEffectPlayAnimation(const TouchType& touchType);

    // helper function to check if paint rect is valid
    bool RectIsNull();

    /** Set data to the modifier and bind it to rsNode_
     *   If [modifier] not initialized, initialize it and add it to rsNode
     *
     *   @param modifier     shared_ptr to a member modifier
     *   @param data         passed to SetCustomData, set to the modifier
     */
    template<typename T, typename D>
    void SetGraphicModifier(std::shared_ptr<T>& modifier, D data);

    void AddModifier(const std::shared_ptr<Rosen::RSModifier>& modifier);
    void RemoveModifier(const std::shared_ptr<Rosen::RSModifier>& modifier);

    // helper function to update one of the graphic effects
    template<typename T, typename D>
    void UpdateGraphic(std::shared_ptr<T>& modifier, D data);

    RectF AdjustPaintRect();

    DataReadyNotifyTask CreateBgImageDataReadyCallback();
    LoadSuccessNotifyTask CreateBgImageLoadSuccessCallback();
    DataReadyNotifyTask CreateBorderImageDataReadyCallback();
    LoadSuccessNotifyTask CreateBorderImageLoadSuccessCallback();
    void BdImagePaintTask(RSCanvas& canvas);

    void PaintDebugBoundary();
    bool IsUsingPosition(const RefPtr<FrameNode>& frameNode);

    void SetContentRectToFrame(RectF rect);

    RefPtr<ImageLoadingContext> bgLoadingCtx_;
    RefPtr<CanvasImage> bgImage_;
    RefPtr<ImageLoadingContext> bdImageLoadingCtx_;
    RefPtr<CanvasImage> bdImage_;

    std::shared_ptr<Rosen::RSNode> rsNode_;
    bool isHoveredScale_ = false;
    bool isHoveredBoard_ = false;
    bool firstTransitionIn_ = false;
    bool isBreakingPoint_ = false;
    bool isBackBlurChanged_ = false;
    bool needDebugBoundary_ = false;
    bool isDisappearing_ = false;
    bool hasDefaultTransition_ = false;
    int appearingTransitionCount_ = 0;
    int disappearingTransitionCount_ = 0;
    int sandBoxCount_ = 0;
    Color blendColor_ = Color::TRANSPARENT;
    Color hoveredColor_ = Color::TRANSPARENT;

    RefPtr<RosenTransitionEffect> transitionEffect_;
    std::shared_ptr<DebugBoundaryModifier> debugBoundaryModifier_;
    std::shared_ptr<BackgroundModifier> backgroundModifier_;
    std::shared_ptr<BorderImageModifier> borderImageModifier_;
    std::shared_ptr<MouseSelectModifier> mouseSelectModifier_;
    std::shared_ptr<MoonProgressModifier> moonProgressModifier_;
    std::shared_ptr<FocusStateModifier> focusStateModifier_;
    std::shared_ptr<FocusStateModifier> accessibilityFocusStateModifier_;
    std::optional<TransformMatrixModifier> transformMatrixModifier_;
    std::shared_ptr<Rosen::RSProperty<Rosen::Vector2f>> pivotProperty_;
    std::unique_ptr<SharedTransitionModifier> sharedTransitionModifier_;
    std::shared_ptr<OverlayTextModifier> modifier_ = nullptr;
    std::shared_ptr<GradientStyleModifier> gradientStyleModifier_;

    // translate modifiers for developer
    std::shared_ptr<Rosen::RSTranslateModifier> translateXY_;

    // graphics modifiers
    struct GraphicModifiers {
        std::shared_ptr<GrayScaleModifier> grayScale;
        std::shared_ptr<BrightnessModifier> brightness;
        std::shared_ptr<ContrastModifier> contrast;
        std::shared_ptr<SaturateModifier> saturate;
        std::shared_ptr<SepiaModifier> sepia;
        std::shared_ptr<InvertModifier> invert;
        std::shared_ptr<HueRotateModifier> hueRotate;
        std::shared_ptr<ColorBlendModifier> colorBlend;
    };
    std::unique_ptr<GraphicModifiers> graphics_;

    RefPtr<TouchEventImpl> touchListener_;
    VectorF currentScale_ = VectorF(1.0f, 1.0f);
    bool isTouchUpFinished_ = true;

    bool useContentRectForRSFrame_;

    template<typename Modifier, typename PropertyType>
    friend class PropertyTransitionEffectTemplate;
    friend class RosenPivotTransitionEffect;

    ACE_DISALLOW_COPY_AND_MOVE(RosenRenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_CONTEXT_H
