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

#include "render_service_client/core/ui/rs_node.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkPictureRecorder.h"
#include "third_party/skia/include/core/SkRefCnt.h"

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/adapter/graphics_modifier.h"
#include "core/components_ng/render/adapter/rosen_modifier_property.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class BorderImageModifier;
class DebugBoundaryModifier;
class MouseSelectModifier;
class FocusStateModifier;
class PageTransitionEffect;
class OverlayTextModifier;
class RosenRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(RosenRenderContext, NG::RenderContext)
public:
    RosenRenderContext() = default;
    ~RosenRenderContext() override;

    void InitContext(bool isRoot, const std::optional<std::string>& surfaceName, bool useExternalNode) override;

    void SyncGeometryProperties(GeometryNode* geometryNode) override;

    void SyncGeometryProperties(const RectF& paintRect) override;

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

    RefPtr<Canvas> GetCanvas() override;
    void Restore() override;

    const std::shared_ptr<Rosen::RSNode>& GetRSNode();

    void SetRSNode(const std::shared_ptr<Rosen::RSNode>& rsNode);

    void StartRecording() override;

    void StopRecordingIfNeeded() override;

    bool IsRecording()
    {
        return !!recordingCanvas_;
    }

    void StartPictureRecording(float x, float y, float width, float height);
    sk_sp<SkPicture> FinishRecordingAsPicture();

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
    void UpdateBackBlurStyle(const BlurStyleOption& bgBlurStyle) override;
    void OnBackShadowUpdate(const Shadow& shadow) override;
    void UpdateBorderWidthF(const BorderWidthPropertyF& value) override;

    void OnTransformMatrixUpdate(const Matrix4& matrix) override;

    void UpdateTransition(const TransitionOptions& options) override;
    bool HasAppearingTransition() const
    {
        return propTransitionAppearing_ != nullptr;
    }
    bool HasDisappearingTransition() const
    {
        return propTransitionDisappearing_ != nullptr;
    }
    void OnNodeAppear() override;
    void OnNodeDisappear() override;
    void ClipWithRect(const RectF& rectF) override;
    void SetClipBoundsWithCommands(const std::string& commands) override;
    bool TriggerPageTransition(PageTransitionType type, const std::function<void()>& onFinish) override;

    void SetSharedTranslate(float xTranslate, float yTranslate) override;
    void ResetSharedTranslate() override;
    void ResetPageTransitionEffect() override;

    static std::list<std::shared_ptr<Rosen::RSNode>> GetChildrenRSNodes(
        const std::list<RefPtr<FrameNode>>& frameChildren);

    // if translate params use percent dimension, frameSize should be given correctly
    static std::shared_ptr<Rosen::RSTransitionEffect> GetRSTransitionWithoutType(
        const TransitionOptions& options, const SizeF& frameSize = SizeF());

    void FlushContentModifier(const RefPtr<Modifier>& modifier) override;
    void FlushOverlayModifier(const RefPtr<Modifier>& modifier) override;

    void AddChild(const RefPtr<RenderContext>& renderContext, int index) override;
    void SetBounds(float positionX, float positionY, float width, float height) override;
    void OnTransformTranslateUpdate(const TranslateOptions& value) override;

    RectF GetPaintRectWithTransform() override;

    RectF GetPaintRectWithoutTransform() override;

    virtual void GetPointWithTransform(PointF& point) override;

    void ClearDrawCommands() override;

    void NotifyTransition(
        const AnimationOption& option, const TransitionOptions& transOptions, bool isTransitionIn) override;

    void OpacityAnimation(const AnimationOption& option, double begin, double end) override;
    void ScaleAnimation(const AnimationOption& option, double begin, double end) override;

    void PaintAccessibilityFocus() override;

    virtual void ClearAccessibilityFocus() override;

    void OnAccessibilityFocusUpdate(bool isAccessibilityFocus) override;

    void OnMouseSelectUpdate(bool isSelected, const Color& fillColor, const Color& strokeColor) override;
    void UpdateMouseSelectWithRect(const RectF& rect, const Color& fillColor, const Color& strokeColor) override;

    void OnPositionUpdate(const OffsetT<Dimension>& value) override;
    void OnZIndexUpdate(int32_t value) override;
    void DumpInfo() const override;

    void SetNeedDebugBoundary(bool flag) override
    {
        needDebugBoundary_ = flag;
    }

    bool NeedDebugBoundary() const override
    {
        return needDebugBoundary_;
    }

    void OnBackgroundColorUpdate(const Color& value) override;

private:
    void OnBackgroundImageUpdate(const ImageSourceInfo& imageSourceInfo) override;
    void OnBackgroundImageRepeatUpdate(const ImageRepeat& imageRepeat) override;
    void OnBackgroundImageSizeUpdate(const BackgroundImageSize& bgImgSize) override;
    void OnBackgroundImagePositionUpdate(const BackgroundImagePosition& bgImgPosition) override;

    void OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) override;
    void OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo) override;
    void OnHasBorderImageSliceUpdate(bool tag) override;
    void OnHasBorderImageWidthUpdate(bool tag) override;
    void OnHasBorderImageOutsetUpdate(bool tag) override;
    void OnHasBorderImageRepeatUpdate(bool tag) override;
    void OnBorderImageGradientUpdate(const Gradient& gradient) override;

    void OnBorderRadiusUpdate(const BorderRadiusProperty& value) override;
    void OnBorderColorUpdate(const BorderColorProperty& value) override;
    void OnBorderStyleUpdate(const BorderStyleProperty& value) override;
    void OnOpacityUpdate(double opacity) override;

    void OnTransformScaleUpdate(const VectorF& value) override;
    void OnTransformCenterUpdate(const DimensionOffset& value) override;
    void OnTransformRotateUpdate(const Vector4F& value) override;

    void OnOffsetUpdate(const OffsetT<Dimension>& value) override;
    void OnAnchorUpdate(const OffsetT<Dimension>& value) override;

    void OnClipShapeUpdate(const RefPtr<BasicShape>& basicShape) override;
    void OnClipEdgeUpdate(bool isClip) override;
    void OnClipMaskUpdate(const RefPtr<BasicShape>& basicShape) override;

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
    void OnFrontBlurRadiusUpdate(const Dimension& radius) override;

    void OnOverlayTextUpdate(const OverlayOptions& overlay) override;
    void OnMotionPathUpdate(const MotionPathOption& motionPath) override;

    void ReCreateRsNodeTree(const std::list<RefPtr<FrameNode>>& children);

    void NotifyTransitionInner(const SizeF& frameSize, bool isTransitionIn);
    void SetTransitionPivot(const SizeF& frameSize, bool transitionIn);
    void SetPivot(float xPivot, float yPivot);

    RefPtr<PageTransitionEffect> GetDefaultPageTransition(PageTransitionType type);
    RefPtr<PageTransitionEffect> GetPageTransitionEffect(const RefPtr<PageTransitionEffect>& transition);

    void PaintBackground();
    void PaintClip(const SizeF& frameSize);
    void PaintGradient(const SizeF& frameSize);
    void PaintGraphics();
    void PaintOverlayText();
    void PaintBorderImage();
    void PaintBorderImageGradient();
    void PaintMouseSelectRect(const RectF& rect, const Color& fillColor, const Color& strokeColor);
    void SetBackBlurFilter();
    void GetPaddingOfFirstFrameNodeParent(Dimension& parentPaddingLeft, Dimension& parentPaddingTop);

    // helper function to check if paint rect is valid
    bool RectIsNull();

    /** Set data to the modifier and bind it to rsNode_
     *   If [modifier] not initialized, initialize it and add it to rsNode
     *
     *   @param modifier     shared_ptr to a member modifier
     *   @param data         passed to SetCustomData, set to the modifier
     */
    template<typename T, typename D>
    void SetModifier(std::shared_ptr<T>& modifier, D data);

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

    RefPtr<ImageLoadingContext> bgLoadingCtx_;
    RefPtr<CanvasImage> bgImage_;

    RefPtr<ImageLoadingContext> bdImageLoadingCtx_;
    RefPtr<CanvasImage> bdImage_;

    std::shared_ptr<Rosen::RSNode> rsNode_;
    SkPictureRecorder* recorder_ = nullptr;
    RefPtr<Canvas> recordingCanvas_;
    RefPtr<Canvas> rosenCanvas_;

    bool isHoveredScale_ = false;
    bool isHoveredBoard_ = false;
    bool isPositionChanged_ = false;
    bool firstTransitionIn_ = false;
    bool isBackBlurChanged_ = false;
    bool needDebugBoundary_ = false;
    Color blendColor_ = Color::TRANSPARENT;
    Color hoveredColor_ = Color::TRANSPARENT;

    std::shared_ptr<DebugBoundaryModifier> debugBoundaryModifier_;
    std::shared_ptr<BorderImageModifier> borderImageModifier_ = nullptr;
    std::shared_ptr<MouseSelectModifier> mouseSelectModifier_ = nullptr;
    std::shared_ptr<FocusStateModifier> focusStateModifier_;
    std::shared_ptr<FocusStateModifier> accessibilityFocusStateModifier_;
    std::optional<TransformMatrixModifier> transformMatrixModifier_;
    std::shared_ptr<Rosen::RSProperty<Rosen::Vector2f>> pivotProperty_;
    std::unique_ptr<SharedTransitionModifier> sharedTransitionModifier_;
    std::shared_ptr<OverlayTextModifier> modifier_ = nullptr;

    // graphics modifiers
    std::shared_ptr<GrayScaleModifier> grayScaleModifier_;
    std::shared_ptr<BrightnessModifier> brightnessModifier_;
    std::shared_ptr<ContrastModifier> contrastModifier_;
    std::shared_ptr<SaturateModifier> saturateModifier_;
    std::shared_ptr<SepiaModifier> sepiaModifier_;
    std::shared_ptr<InvertModifier> invertModifier_;
    std::shared_ptr<HueRotateModifier> hueRotateModifier_;
    std::shared_ptr<ColorBlendModifier> colorBlendModifier_;

    ACE_DISALLOW_COPY_AND_MOVE(RosenRenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_CONTEXT_H
