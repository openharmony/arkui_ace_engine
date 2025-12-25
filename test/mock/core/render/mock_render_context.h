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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H

#include "gmock/gmock.h"
#include "ui/properties/ui_material.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class MockRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(MockRenderContext, RenderContext);
public:
    ~MockRenderContext() override = default;

    MOCK_METHOD1(GetPointWithTransform, void(PointF&));
    MOCK_METHOD1(AnimateHoverEffectScale, void(bool));
    MOCK_METHOD4(SetBounds, void(float, float, float, float));
    MOCK_METHOD1(DoTextureExport, bool(uint64_t));
    MOCK_METHOD0(StopTextureExport, bool());
    MOCK_METHOD1(GetPointTransform, void(PointF&));
    MOCK_METHOD1(GetPointWithRevert, void(PointF&));
    MOCK_METHOD1(SetSurfaceRotation, void(bool));
    MOCK_METHOD1(SetRenderFit, void(RenderFit));
    MOCK_METHOD1(SetSecurityLayer, void(bool));
    MOCK_METHOD1(SetHDRBrightness, void(float));
    MOCK_METHOD1(SetContentClip, void(const std::variant<RectF, RefPtr<ShapeRect>>&));
    MOCK_METHOD0(ResetContentClip, void());
    MOCK_METHOD1(SetTransparentLayer, void(bool));
    MOCK_METHOD1(SetClipToBounds, void(bool));
    MOCK_METHOD1(RemoveOverlayModifier, void(const RefPtr<OverlayModifier>&));
    MOCK_METHOD0(UpdateCustomBackground, void());
    MOCK_METHOD1(SetSurfaceBufferOpaque, void(bool));

    const RefPtr<NG::ChainedTransitionEffect> GetChainedTransitionEffect()
    {
        return chainedTransitionEffect_;
    }

    void SetVisible(bool visible) override
    {
        isVisible_ = visible;
    }

    void ResetBlendBgColor() override
    {
        blendColor_ = Color::TRANSPARENT;
    }

    void BlendBgColor(const Color& color) override
    {
        blendColor_ = color;
    }

    void UpdatePaintRect(const RectF& rect) override
    {
        paintRect_ = rect;
    }

    void SavePaintRect(bool isRound = true, uint16_t flag = 0) override
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto geometryNode = host->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        OnePixelRounding(flag);
        UpdatePaintRect(RectF(geometryNode->GetPixelGridRoundOffset(), geometryNode->GetPixelGridRoundSize()));
    }

    void OnePixelRounding(uint16_t flag)
    {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto geometryNode = frameNode->GetGeometryNode();
        float relativeLeft = geometryNode->GetFrameOffset().GetX();
        float relativeTop = geometryNode->GetFrameOffset().GetY();
        float nodeWidth = geometryNode->GetFrameSize().Width();
        float nodeHeight = geometryNode->GetFrameSize().Height();
        float roundToPixelErrorX = 0.0f;
        float roundToPixelErrorY = 0.0f;
        float absoluteRight = relativeLeft + nodeWidth;
        float absoluteBottom = relativeTop + nodeHeight;
        bool ceilLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
        bool floorLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START);
        bool noRoundLeft = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START);
        bool ceilTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
        bool floorTop = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
        bool noRoundTop = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP);
        bool ceilRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
        bool floorRight = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END);
        bool noRoundRight = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END);
        bool ceilBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
        bool floorBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);
        bool noRoundBottom = flag & static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);

        float nodeLeftI = OnePixelValueRounding(relativeLeft, !noRoundLeft, ceilLeft, floorLeft);
        float nodeTopI = OnePixelValueRounding(relativeTop, !noRoundTop, ceilTop, floorTop);
        roundToPixelErrorX += nodeLeftI - relativeLeft;
        roundToPixelErrorY += nodeTopI - relativeTop;
        geometryNode->SetPixelGridRoundOffset(OffsetF(nodeLeftI, nodeTopI));

        float nodeWidthI = OnePixelValueRounding(absoluteRight, !noRoundRight, ceilRight, floorRight) - nodeLeftI;
        float nodeWidthTemp = OnePixelValueRounding(nodeWidth, !noRoundRight, ceilRight, floorRight);
        roundToPixelErrorX += nodeWidthI - nodeWidth;
        if (roundToPixelErrorX > 0.5f) {
            nodeWidthI -= 1.0f;
            roundToPixelErrorX -= 1.0f;
        }
        bool enableForceFloorX =
            SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE && (floorLeft || floorRight);
        if (roundToPixelErrorX < -0.5f && !enableForceFloorX) {
            nodeWidthI += 1.0f;
            roundToPixelErrorX += 1.0f;
        }
        if (nodeWidthI < nodeWidthTemp) {
            roundToPixelErrorX += nodeWidthTemp - nodeWidthI;
            nodeWidthI = nodeWidthTemp;
        }

        float nodeHeightI = OnePixelValueRounding(absoluteBottom, !noRoundBottom, ceilBottom, floorBottom) - nodeTopI;
        float nodeHeightTemp = OnePixelValueRounding(nodeHeight, !noRoundBottom, ceilBottom, floorBottom);
        roundToPixelErrorY += nodeHeightI - nodeHeight;
        if (roundToPixelErrorY > 0.5f) {
            nodeHeightI -= 1.0f;
            roundToPixelErrorY -= 1.0f;
        }
        bool enableForceFloorY =
            SystemProperties::GetDeviceType() == DeviceType::TWO_IN_ONE && (floorTop || floorBottom);
        if (roundToPixelErrorY < -0.5f && !enableForceFloorY) {
            nodeHeightI += 1.0f;
            roundToPixelErrorY += 1.0f;
        }
        if (nodeHeightI < nodeHeightTemp) {
            roundToPixelErrorY += nodeHeightTemp - nodeHeightI;
            nodeHeightI = nodeHeightTemp;
        }
        geometryNode->SetPixelGridRoundSize(SizeF(nodeWidthI, nodeHeightI));
    }

    float OnePixelValueRounding(float value, bool isRound, bool forceCeil, bool forceFloor)
    {
        float fractials = fmod(value, 1.0f);
        if (NearEqual(fractials, 0.0f)) {
            return value;
        }
        if (LessNotEqual(fractials, 0.0f)) {
            ++fractials;
        }
        if (forceCeil) {
            return (value - fractials + 1.0f);
        } else if (forceFloor) {
            return (value - fractials);
        } else if (isRound) {
            if (NearEqual(fractials, 1.0f) || GreatOrEqual(fractials, 0.5f)) {
                return (value - fractials + 1.0f);
            } else {
                return (value - fractials);
            }
        }
        return value;
    }

    RectF GetPaintRectWithTransform() override
    {
        return rect_;
    }

    void SetPaintRectWithTransform(const RectF rect)
    {
        rect_ = rect;
    }

    RectF GetPaintRectWithoutTransform() override
    {
        return paintRect_;
    }

    void SetTransitionUserCallback(TransitionFinishCallback&& callback) override
    {
        transitionUserCallback_ = std::move(callback);
    }

#ifdef ENHANCED_ANIMATION
    void AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier) override;
    void DetachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyBase>& modifier) override {}

    void CancelTranslateXYAnimation() override;
    OffsetF GetTranslateXYProperty() override;
    void UpdateTranslateInXY(const OffsetF& offset) override;
#endif

    void UpdateBackBlurStyle(
        const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions = SysOptions())
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propBlurStyleOption = bgBlurStyle;
    }

    void UpdateBackgroundEffect(
        const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions = SysOptions())
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propEffectOption = effectOption;
    }

    void OnUseEffectUpdate(bool useEffect) override
    {
        propUseEffect_ = useEffect;
    }

    void OnUseEffectTypeUpdate(EffectType effectType) override
    {
        propUseEffectType_ = effectType;
    }
    void UpdateMotionBlur(const MotionBlurOption& motionBlurOption) override
    {
        const auto& groupProperty = GetOrCreateForeground();
        groupProperty->propMotionBlur = motionBlurOption;
    }

    int32_t CalcExpectedFrameRate(const std::string& scene, float speed)
    {
        return 0;
    }

    void SetOpacityMultiplier(float opacity)
    {
        opacityMultiplier_ = opacity;
    }

    bool HasDisappearTransition() const
    {
        return hasDisappearTransition_;
    }

    void SetTransitionOutCallback(std::function<void()>&& callback)
    {
        transitionOutCallback_ = std::move(callback);
    }

    void SetActualForegroundColor(const Color& value) override
    {
        actualForegroundColor_ = value;
    }

    size_t GetAnimationsCount() const override
    {
        return animationsCount_;
    }

    void SetAnimationsCount(size_t count)
    {
        animationsCount_ = count;
    }

    bool isVisible_ = true;
    bool hasDisappearTransition_ = false;
    RectF rect_;
    RectF paintRect_;
    Color blendColor_ = Color::TRANSPARENT;
    RefPtr<AnimatablePropertyOffsetF> translateXY_;
    float opacityMultiplier_ = 1.0f;
    std::function<void()> transitionOutCallback_;
    Color actualForegroundColor_;

    RefPtr<NG::ChainedTransitionEffect> chainedTransitionEffect_ = nullptr;
    TransitionFinishCallback transitionUserCallback_;
private:
    size_t animationsCount_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
