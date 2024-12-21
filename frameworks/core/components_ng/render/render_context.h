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

#include <cstdint>
#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/animation/page_transition_common.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/render_node/render_node_properties.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/attraction_effect.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/particle_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/particle_property_animation.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Rosen {
class DrawCmdList;
class VisualEffect;
class Filter;
enum class Gravity;
class BrightnessBlender;
}

namespace OHOS::Ace::NG {

typedef enum {
    OPINC_INVALID,
    OPINC_NODE,
    OPINC_SUGGESTED_OR_EXCLUDED,
    OPINC_PARENT_POSSIBLE,
    OPINC_NODE_POSSIBLE,
} OPINC_TYPE_E;

class GeometryNode;
class RenderPropertyNode;
class FrameNode;
class InspectorFilter;
class Modifier;

struct PaintFocusExtraInfo final {
    PaintFocusExtraInfo() = default;
    PaintFocusExtraInfo(bool isAccessibilityFocus, bool isFocusBoxGlow)
        : isAccessibilityFocus(isAccessibilityFocus), isFocusBoxGlow(isFocusBoxGlow)
    {}
    ~PaintFocusExtraInfo() = default;
    bool isAccessibilityFocus { false };
    bool isFocusBoxGlow { false };
};

using CanvasDrawFunction = std::function<void(RSCanvas& canvas)>;
using TransitionFinishCallback = std::function<void(bool)>;

inline constexpr int32_t ZINDEX_DEFAULT_VALUE = 0;

// RenderContext is used for render node to paint.
class ACE_FORCE_EXPORT RenderContext : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RenderContext, AceType)

public:
    ~RenderContext() override = default;

    static RefPtr<RenderContext> Create();

    void SetRequestFrame(const std::function<void()>& requestFrame);
    void RequestNextFrame() const;

    virtual void SetHostNode(const WeakPtr<FrameNode>& host);
    RefPtr<FrameNode> GetHost() const;
    FrameNode* GetUnsafeHost() const;

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

    virtual void SyncGeometryProperties(GeometryNode* geometryNode, bool isRound = true, uint8_t flag = 0) {}

    virtual void SyncGeometryProperties(const RectF& rectF) {}

    virtual void SetBorderRadius(const BorderRadiusProperty& value) {}

    virtual void SetBorderStyle(const BorderStyleProperty& value) {};

    virtual void SetBorderColor(const BorderColorProperty& value) {};

    virtual void SetBorderWidth(const BorderWidthProperty& value) {};

    virtual void SetDashGap(const BorderWidthProperty& value) {};

    virtual void SetDashWidth(const BorderWidthProperty& value) {};

    virtual void SetOuterBorderRadius(const BorderRadiusProperty& value) {};

    virtual void SetOuterBorderStyle(const BorderStyleProperty& value) {};

    virtual void SetOuterBorderColor(const BorderColorProperty& value) {};

    virtual void SetOuterBorderWidth(const BorderWidthProperty& value) {};

    // draw self and children in sandbox origin at parent's absolute position in root, drawing in sandbox
    // will be unaffected by parent's transition.
    virtual void SetSandBox(const std::optional<OffsetF>& parentPosition, bool force = false) {};

    virtual bool HasSandBox() const
    {
        return false;
    }

    virtual void SetFrameWithoutAnimation(const RectF& paintRect) {};

    virtual void RegisterSharedTransition(const RefPtr<RenderContext>& other) {}
    virtual void UnregisterSharedTransition(const RefPtr<RenderContext>& other) {}

    virtual void OnModifyDone() {}

    enum class ContextType : int8_t {
        CANVAS,
        ROOT,
        SURFACE,
        EFFECT,
        EXTERNAL,
        INCREMENTAL_CANVAS,
        HARDWARE_SURFACE,
#ifdef RENDER_EXTRACT_SUPPORTED
        HARDWARE_TEXTURE,
#endif
    };

    enum class PatternType : int8_t {
        DEFAULT,
        VIDEO,
        XCOM,
#ifdef PLATFORM_VIEW_SUPPORTED
        PLATFORM_VIEW,
#endif
    };
    struct ContextParam {
        ContextType type;
        std::optional<std::string> surfaceName;
        PatternType patternType = PatternType::DEFAULT;
    };

    virtual void InitContext(bool isRoot, const std::optional<ContextParam>& param) {}

    virtual void InitContext(bool isRoot, const std::optional<ContextParam>& param, bool isLayoutNode) {}

    virtual void SetSurfaceChangedCallBack(
        const std::function<void(float, float, float, float)>& callback) {}
    virtual void RemoveSurfaceChangedCallBack() {}

    virtual void MarkNewFrameAvailable(void* nativeWindow) {}
    virtual void AddAttachCallBack(const std::function<void(int64_t, bool)>& attachCallback) {}
    virtual void AddUpdateCallBack(const std::function<void(std::vector<float>&)>& updateCallback) {}
    virtual void AddInitTypeCallBack(const std::function<void(int32_t&)>& initTypeCallback) {}

    virtual void StartRecording() {}
    virtual void StopRecordingIfNeeded() {}

    virtual void SetDrawContentAtLast(bool useDrawContentLastOrder) {}

    virtual void ResetBlendBgColor() {}

    virtual void BlendBgColor(const Color& color) {}

    virtual void ResetBlendBorderColor() {}

    virtual void BlendBorderColor(const Color& color) {}

    // Paint focus state by component's setting. It will paint along the paintRect
    virtual void PaintFocusState(const RoundRect& paintRect, const Color& paintColor, const Dimension& paintWidth,
        bool isAccessibilityFocus = false, bool isFocusBoxGlow = false)
    {}
    // Paint focus state by component's setting. It will paint along the frameRect(padding: focusPaddingVp)
    virtual void PaintFocusState(const RoundRect& paintRect, const Dimension& focusPaddingVp, const Color& paintColor,
        const Dimension& paintWidth, const PaintFocusExtraInfo& paintFocusExtraInfo)
    {}
    // Paint focus state by default. It will paint along the component rect(padding: focusPaddingVp)
    virtual void PaintFocusState(const Dimension& focusPaddingVp, const Color& paintColor, const Dimension& paintWidth,
        bool isFocusBoxGlow = false)
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
    const RefPtr<OneCenterTransitionOptionType>& GetOneCenterTransitionOption()
    {
        return oneCenterTransition_;
    }
    void UpdateOneCenterTransitionOption(const RefPtr<OneCenterTransitionOptionType>& value)
    {
        oneCenterTransition_ = value;
    }
    virtual void OnNodeDisappear(bool recursive) {}
    virtual void OnNodeAppear(bool recursive) {}
    virtual bool HasTransitionOutAnimation() const
    {
        return false;
    }

    virtual bool HasDisappearTransition() const
    {
        return false;
    }

    virtual bool IsSynced() const
    {
        return isSynced_;
    }

    virtual void SetSharedTranslate(float xTranslate, float yTranslate) {}
    virtual void ResetSharedTranslate() {}

    virtual void AddChild(const RefPtr<RenderContext>& renderContext, int index) {}
    virtual void RemoveChild(const RefPtr<RenderContext>& renderContext) {}
    virtual void ClearChildren() {}
    virtual void SetBounds(float positionX, float positionY, float width, float height) {}
    virtual void SetContentRectToFrame(RectF rect) {}
    virtual void SetSecurityLayer(bool isSecure) {}
    virtual void SetHDRBrightness(float hdrBrightness) {}

    virtual void UpdateBackBlurRadius(const Dimension& radius) {}
    virtual void UpdateBackBlurStyle(const std::optional<BlurStyleOption>& bgBlurStyle) {}
    virtual void UpdateBackgroundEffect(const std::optional<EffectOption>& effectOption) {}
    virtual void UpdateBackBlur(const Dimension& radius, const BlurOption& blurOption) {}
    virtual void UpdateMotionBlur(const MotionBlurOption& motionBlurOption) {}
    virtual void UpdateFrontBlur(const Dimension& radius, const BlurOption& blurOption) {}
    virtual void UpdateFrontBlurStyle(const std::optional<BlurStyleOption>& fgBlurStyle) {}
    virtual void UpdateFrontBlurRadius(const Dimension& radius) {}
    virtual void ResetBackBlurStyle() {}
    virtual void ClipWithRect(const RectF& rectF) {}
    virtual void ClipWithRoundRect(const RoundRect& roundRect) {}
    virtual void ClipWithOval(const RectF& rectF) {}
    virtual void ClipWithCircle(const Circle& circle) {}
    virtual void ClipWithRRect(const RectF& rectF, const RadiusF& radiusF) {}
    virtual void RemoveClipWithRRect() {}
    virtual void UpdateWindowFocusState(bool isFocused) {}
    /**
     * @brief Only clip the content & foreground layer by @c rect.
     * @param rect - offset of @c rect is relative to FrameRect.
     */
    virtual void SetContentClip(const std::variant<RectF, RefPtr<ShapeRect>>& rect) {}

    // visual
    virtual void UpdateVisualEffect(const OHOS::Rosen::VisualEffect* visualEffect) {}
    virtual void UpdateBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter) {}
    virtual void UpdateForegroundFilter(const OHOS::Rosen::Filter* foregroundFilter) {}
    virtual void UpdateCompositingFilter(const OHOS::Rosen::Filter* compositingFilter) {}
    virtual void UpdateBrightnessBlender(const OHOS::Rosen::BrightnessBlender* brightnessBlender) {}

    virtual void OpacityAnimation(const AnimationOption& option, double begin, double end) {}
    virtual void ScaleAnimation(const AnimationOption& option, double begin, double end) {}

    virtual void OnTransformTranslateUpdate(const TranslateOptions& value) {}
    virtual void OnTransformScaleUpdate(const VectorF& value) {}
    virtual void OnTransformCenterUpdate(const DimensionOffset& value) {}
    virtual void OnOffsetUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnOffsetEdgesUpdate(const EdgesParam& value) {}

    // used in arkts_native_render_node_modifier set property directly to rsNode
    virtual void SetRotation(float rotationX, float rotationY, float rotationZ) {}
    virtual void SetShadowColor(uint32_t color) {}
    virtual void SetShadowOffset(float offsetX, float offsetY) {}
    virtual void SetShadowAlpha(float alpha) {}
    virtual void SetShadowElevation(float elevation) {}
    virtual void SetShadowRadius(float radius) {}
    virtual void SetScale(float scaleX, float scaleY) {}
    virtual void SetBackgroundColor(uint32_t colorValue) {}
    virtual void SetRenderPivot(float pivotX, float pivotY) {}
    virtual void SetFrame(float positionX, float positionY, float width, float height) {}
    virtual void SetOpacity(float opacity) {}
    virtual void SetTranslate(float translateX, float translateY, float translateZ) {}
    virtual void CleanTransition() {}
    virtual void SetRectMask(const RectF& rect, const ShapeMaskProperty& property) {}
    virtual void SetCircleMask(const Circle& circle, const ShapeMaskProperty& property) {}
    virtual void SetRoundRectMask(const RoundRect& roundRect, const ShapeMaskProperty& property) {}
    virtual void SetOvalMask(const RectF& rect, const ShapeMaskProperty& property) {}
    virtual void SetCommandPathMask(const std::string& commands, const ShapeMaskProperty& property) {}
    virtual void SetMarkNodeGroup(bool isNodeGroup) {}

    virtual RectF GetPaintRectWithTransform()
    {
        return {};
    }

    virtual void SavePaintRect(bool isRound = true, uint16_t flag = 0) {}
    virtual void SyncPartialRsProperties() {}
    virtual void UpdatePaintRect(const RectF& paintRect) {}

    virtual std::pair<RectF, bool> GetPaintRectWithTranslate()
    {
        return {};
    }

    virtual Matrix4 GetLocalTransformMatrix()
    {
        return Matrix4();
    }

    virtual void GetPointWithRevert(PointF& point) {}

    virtual void GetPointWithTransform(PointF& point) {}

    virtual void GetPointTransform(PointF& point) {}

    virtual void GetPointTransformRotate(PointF& point) {}

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

    virtual void CancelTranslateXYAnimation() {}

    virtual OffsetF GetTranslateXYProperty()
    {
        return OffsetF();
    }

    // update translateXY in backend.
    virtual void UpdateTranslateInXY(const OffsetF& offset) {}

    virtual void SetTransitionOutCallback(std::function<void()>&& callback) {}

    virtual void SetTransitionInCallback(std::function<void()>&& callback) {}

    virtual void SetTransitionUserCallback(TransitionFinishCallback&& callback) {}

    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    virtual void FromJson(const std::unique_ptr<JsonValue>& json);

    virtual void ClearDrawCommands() {}

    virtual void RemoveContentModifier(const RefPtr<ContentModifier>& ContentModifier) {}

    virtual void DumpInfo() {}
    virtual void DumpInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpSimplifyInfo(std::unique_ptr<JsonValue>& json) {}
    virtual void DumpAdvanceInfo() {}
    virtual void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) {}

    void ObscuredToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    void SetSharedTransitionOptions(const std::shared_ptr<SharedTransitionOption>& option);
    const std::shared_ptr<SharedTransitionOption>& GetSharedTransitionOption() const;
    void SetShareId(const ShareId& shareId);
    const ShareId& GetShareId() const;
    bool HasSharedTransition() const;
    bool HasSharedTransitionOption() const;

    void SetIsModalRootNode(bool isModalRootNode)
    {
        isModalRootNode_ = isModalRootNode;
    }

    void SetIsNeedRebuildRSTree(bool isNeedRebuildRSTree)
    {
        isNeedRebuildRSTree_ = isNeedRebuildRSTree;
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

    virtual void DetachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyBase>& modifier) {};

    virtual void PaintAccessibilityFocus() {};

    virtual void UpdateAccessibilityRoundRect() {};

    virtual void ClearAccessibilityFocus() {};

    virtual void OnAccessibilityFocusUpdate(
        bool isAccessibilityFocus, const int64_t accessibilityIdForVirtualNode = -2100000) {};
    virtual void OnAccessibilityFocusRectUpdate(RectT<int32_t> accessibilityFocusRect) {};

    virtual void OnMouseSelectUpdate(bool isSelected, const Color& fillColor, const Color& strokeColor) {}
    virtual void UpdateMouseSelectWithRect(const RectF& rect, const Color& fillColor, const Color& strokeColor) {}

    virtual void OnPositionUpdate(const OffsetT<Dimension>& value) {}
    virtual void OnPositionEdgesUpdate(const EdgesParam& value) {}
    virtual void RecalculatePosition() {}
    virtual void OnZIndexUpdate(int32_t value) {}

    virtual void OnBackgroundColorUpdate(const Color& value) {}
    virtual void OnOpacityUpdate(double opacity) {}
    virtual void OnDynamicRangeModeUpdate(DynamicRangeMode dynamicRangeMode) {}
    virtual void SetAlphaOffscreen(bool isOffScreen) {}
    virtual void OnSphericalEffectUpdate(double radio) {}
    virtual void OnPixelStretchEffectUpdate(const PixStretchEffectOption& option) {}
    virtual void OnLightUpEffectUpdate(double radio) {}
    virtual void OnClickEffectLevelUpdate(const ClickEffectInfo& info) {}
    virtual void OnRenderGroupUpdate(bool isRenderGroup) {}
    virtual void UpdateRenderGroup(bool isRenderGroup, bool isForced, bool includeProperty) {}
    virtual void OnSuggestedRenderGroupUpdate(bool isRenderGroup) {}
    virtual void OnDynamicDimDegreeUpdate(const float degree) {}
    virtual void OnRenderFitUpdate(RenderFit renderFit) {}
    virtual void OnNodeNameUpdate(const std::string& id) {}
    virtual void OnParticleOptionArrayUpdate(const std::list<ParticleOption>& optionArray) {}
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SphericalEffect, double);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(PixelStretchEffect, PixStretchEffectOption);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(LightUpEffect, double);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(DynamicDimDegree, float);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ParticleOptionArray, std::list<ParticleOption>);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ClickEffectLevel, ClickEffectInfo);
    virtual RefPtr<PixelMap> GetThumbnailPixelMap(bool needScale = false, bool isOffline = true)
    {
        return nullptr;
    }
    virtual void UpdateThumbnailPixelMapScale(float& scaleX, float& scaleY) {}

    virtual bool CreateThumbnailPixelMapAsyncTask(
        bool needScale, std::function<void(const RefPtr<PixelMap>)>&& callback)
    {
        return false;
    }

    virtual void SetActualForegroundColor(const Color& value) {}

    virtual void ResetSurface(int width, int height) {}
    virtual void PaintDebugBoundary(bool flag) {}
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
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Foreground, ForegroundEffect, float);

    // Background
    ACE_DEFINE_PROPERTY_GROUP(Background, BackgroundProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImage, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageRepeat, ImageRepeat);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageSize, BackgroundImageSize);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImagePosition, BackgroundImagePosition);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Background, BackgroundImageResizableSlice, ImageResizableSlice);

    // BorderImage
    ACE_DEFINE_PROPERTY_GROUP(BdImage, BorderImageProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImage, RefPtr<BorderImage>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImageSource, ImageSourceInfo);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageSlice, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageWidth, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageOutset, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, HasBorderImageRepeat, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderImageGradient, Gradient);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(BdImage, BorderSourceFromImage, bool);

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(BackgroundColor, Color);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Opacity, double);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RenderGroup, bool);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(NodeName, std::string);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(SuggestedRenderGroup, bool);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ForegroundColor, Color);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ForegroundColorStrategy, ForegroundColorStrategy);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(DynamicRangeMode, DynamicRangeMode);
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
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontInvert, InvertVariant);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, SystemBarEffect, bool);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontHueRotate, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FrontColorBlend, Color);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, LinearGradientBlur, NG::LinearGradientBlurPara);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, Magnifier, MagnifierParams);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, DynamicLightUpRate, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, DynamicLightUpDegree, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, BgDynamicBrightnessOption, BrightnessOption);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, FgDynamicBrightnessOption, BrightnessOption);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, BackShadow, Shadow);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, BackBlendMode, BlendMode);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Graphics, BackBlendApplyType, BlendApplyType);

    // BorderRadius.
    ACE_DEFINE_PROPERTY_GROUP(Border, BorderProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderWidth, BorderWidthProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderColor, BorderColorProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, BorderStyle, BorderStyleProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, DashGap, BorderWidthProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Border, DashWidth, BorderWidthProperty);

    // Outer Border
    ACE_DEFINE_PROPERTY_GROUP(OuterBorder, OuterBorderProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(OuterBorder, OuterBorderRadius, BorderRadiusProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(OuterBorder, OuterBorderWidth, BorderWidthProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(OuterBorder, OuterBorderColor, BorderColorProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(OuterBorder, OuterBorderStyle, BorderStyleProperty);

    // PointLight
    ACE_DEFINE_PROPERTY_GROUP(PointLight, PointLightProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, LightPosition, TranslateOptions);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, LightIntensity, float);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, LightColor, Color);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, LightIlluminated, uint32_t);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, IlluminatedBorderWidth, Dimension);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PointLight, Bloom, float);

    // Transition Options
    ACE_DEFINE_PROPERTY_GROUP(TransitionAppearing, TransitionOptions);
    ACE_DEFINE_PROPERTY_GROUP(TransitionDisappearing, TransitionOptions);

    // Position
    ACE_DEFINE_PROPERTY_GROUP(PositionProperty, RenderPositionProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, Position, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, Offset, OffsetT<Dimension>);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, PositionEdges, EdgesParam);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(PositionProperty, OffsetEdges, EdgesParam);
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
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Gradient, LastGradientType, NG::GradientType);

    // Overlay
    ACE_DEFINE_PROPERTY_GROUP(Overlay, OverlayProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Overlay, OverlayText, OverlayOptions)

    // MotionPath
    ACE_DEFINE_PROPERTY_GROUP(Motion, MotionPathProperty);
    ACE_DEFINE_PROPERTY_FUNC_WITH_GROUP(Motion, MotionPath, MotionPathOption)

    // accessibility
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP_FOR_VIRTUAL_NODE(AccessibilityFocus, bool);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(AccessibilityFocusRect, RectT<int32_t>);

    // useEffect
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(UseEffect, bool);
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(UseEffectType, EffectType);

    // useShadowBatching
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(UseShadowBatching, bool);

    // freeze
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Freeze, bool);

    // obscured
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(Obscured, std::vector<ObscuredReasons>);

    // renderFit
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RenderFit, RenderFit);

    // AttractionEffect
    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(AttractionEffect, AttractionEffect);

    virtual void SetUsingContentRectForRenderFrame(bool value, bool adjustRSFrameByContentRect = false) {}
    virtual void SetFrameGravity(OHOS::Rosen::Gravity gravity) {}

    virtual int32_t CalcExpectedFrameRate(const std::string& scene, float speed)
    {
        return 0;
    }

    virtual bool IsUniRenderEnabled()
    {
        return true;
    }
    virtual void SetRenderFrameOffset(const OffsetF& offset) {}

    virtual bool DoTextureExport(uint64_t /* surfaceId */)
    {
        return false;
    }

    virtual bool StopTextureExport()
    {
        return false;
    }

    virtual void SetSurfaceRotation(bool isLock) {}

    void SetHandleChildBounds(bool value) {
        handleChildBounds_ = value;
    }

    virtual Matrix4 GetRevertMatrix()
    {
        return Matrix4();
    }

    virtual void SuggestOpIncNode(bool isOpincNode, bool isNeedCalculate) {}

    // The additional opacity will be multiplied with the base opacity.
    virtual void SetOpacityMultiplier(float opacity) {}

    void SetNeedAnimateFlag(bool isNeedAnimate)
    {
        isNeedAnimate_ = isNeedAnimate;
    }

    virtual uint64_t GetNodeId() const
    {
        return 0;
    }

    virtual bool IsDisappearing() const
    {
        return false;
    }

    virtual void SetRenderFit(RenderFit renderFit) {}

    virtual void UpdateWindowBlur() {}
    virtual size_t GetAnimationsCount() const
    {
        return 0;
    }

protected:
    RenderContext() = default;
    std::shared_ptr<SharedTransitionOption> sharedTransitionOption_;
    ShareId shareId_;
    bool isModalRootNode_ = false;
    bool isSynced_ = false;
    bool isNeedRebuildRSTree_ = true;
    bool handleChildBounds_ = false;
    bool isNeedAnimate_ = true;

    virtual void OnBackgroundImageUpdate(const ImageSourceInfo& imageSourceInfo) {}
    virtual void OnBackgroundImageRepeatUpdate(const ImageRepeat& imageRepeat) {}
    virtual void OnBackgroundImageSizeUpdate(const BackgroundImageSize& bgImgSize) {}
    virtual void OnBackgroundImagePositionUpdate(const BackgroundImagePosition& bgImgPosition) {}
    virtual void OnBackgroundImageResizableSliceUpdate(const ImageResizableSlice& slice) {}

    virtual void OnForegroundColorUpdate(const Color& value) {}
    virtual void OnForegroundColorStrategyUpdate(const ForegroundColorStrategy& value) {}
    virtual void OnForegroundEffectUpdate(float radius) {};

    virtual void OnBackgroundPixelMapUpdate(const RefPtr<PixelMap>& value) {}
    virtual void OnBackgroundAlignUpdate(const Alignment& align) {}

    virtual void OnBorderImageUpdate(const RefPtr<BorderImage>& borderImage) {}
    virtual void OnBorderImageSourceUpdate(const ImageSourceInfo& borderImageSourceInfo) {}
    virtual void OnHasBorderImageSliceUpdate(bool tag) {}
    virtual void OnHasBorderImageWidthUpdate(bool tag) {}
    virtual void OnHasBorderImageOutsetUpdate(bool tag) {}
    virtual void OnHasBorderImageRepeatUpdate(bool tag) {}
    virtual void OnBorderImageGradientUpdate(const Gradient& gradient) {}
    virtual void OnBorderSourceFromImageUpdate(bool sourceFromImage) {}

    virtual void OnBorderWidthUpdate(const BorderWidthProperty& value) {}
    virtual void OnBorderRadiusUpdate(const BorderRadiusProperty& value) {}
    virtual void OnBorderColorUpdate(const BorderColorProperty& value) {}
    virtual void OnBorderStyleUpdate(const BorderStyleProperty& value) {}
    virtual void OnDashGapUpdate(const BorderWidthProperty& value) {}
    virtual void OnDashWidthUpdate(const BorderWidthProperty& value) {}

    virtual void OnOuterBorderWidthUpdate(const BorderWidthProperty& value) {}
    virtual void OnOuterBorderRadiusUpdate(const BorderRadiusProperty& value) {}
    virtual void OnOuterBorderColorUpdate(const BorderColorProperty& value) {}
    virtual void OnOuterBorderStyleUpdate(const BorderStyleProperty& value) {}

    virtual void OnLightPositionUpdate(const TranslateOptions& value) {}
    virtual void OnLightIntensityUpdate(const float value) {}
    virtual void OnLightColorUpdate(const Color& value) {}
    virtual void OnLightIlluminatedUpdate(const uint32_t value) {}
    virtual void OnIlluminatedBorderWidthUpdate(const Dimension& value) {}
    virtual void OnBloomUpdate(const float value) {}

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
    virtual void OnLastGradientTypeUpdate(const NG::GradientType& value) {}

    virtual void OnFrontBrightnessUpdate(const Dimension& value) {}
    virtual void OnFrontGrayScaleUpdate(const Dimension& value) {}
    virtual void OnFrontContrastUpdate(const Dimension& value) {}
    virtual void OnFrontSaturateUpdate(const Dimension& value) {}
    virtual void OnFrontSepiaUpdate(const Dimension& value) {}
    virtual void OnFrontInvertUpdate(const InvertVariant& value) {}
    virtual void OnSystemBarEffectUpdate(bool systemBarEffect) {}
    virtual void OnFrontHueRotateUpdate(float value) {}
    virtual void OnFrontColorBlendUpdate(const Color& value) {}
    virtual void OnLinearGradientBlurUpdate(const NG::LinearGradientBlurPara& blurPara) {}
    virtual void OnMagnifierUpdate(const MagnifierParams& magnifierParams) {}
    virtual void OnDynamicLightUpRateUpdate(const float rate) {}
    virtual void OnDynamicLightUpDegreeUpdate(const float degree) {}
    virtual void OnBgDynamicBrightnessOptionUpdate(const std::optional<BrightnessOption>& brightnessOption) {}
    virtual void OnFgDynamicBrightnessOptionUpdate(const std::optional<BrightnessOption>& brightnessOption) {}
    virtual void OnBackShadowUpdate(const Shadow& shadow) {}
    virtual void OnBackBlendModeUpdate(BlendMode blendMode) {}
    virtual void OnBackBlendApplyTypeUpdate(BlendApplyType blendApplyType) {}

    virtual void OnOverlayTextUpdate(const OverlayOptions& overlay) {}
    virtual void OnMotionPathUpdate(const MotionPathOption& motionPath) {}
    virtual void OnUseEffectUpdate(bool useEffect) {}
    virtual void OnUseEffectTypeUpdate(EffectType effectType) {}
    virtual bool GetStatusByEffectTypeAndWindow() { return false; }
    virtual void OnUseShadowBatchingUpdate(bool useShadowBatching) {}
    virtual void OnFreezeUpdate(bool isFreezed) {}
    virtual void OnObscuredUpdate(const std::vector<ObscuredReasons>& reasons) {}
    virtual void OnAttractionEffectUpdate(const AttractionEffect& effect) {}

private:
    friend class ViewAbstract;
    std::function<void()> requestFrame_;
    WeakPtr<FrameNode> host_;
    RefPtr<OneCenterTransitionOptionType> oneCenterTransition_;
    ACE_DISALLOW_COPY_AND_MOVE(RenderContext);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_CONTEXT_H
