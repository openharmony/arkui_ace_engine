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
    MockRenderContext() = default;
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

    float OnePixelValueRounding(float value, bool isRound, bool forceCeil, bool forceFloor)
    {
        return 0.0f;
    }

    RectF GetPaintRectWithTransform() override
    {
        return rect_;
    }

    void SetPaintRectWithTransform(const RectF rect)
    {
        rect_ = rect;
        paintRect_ = rect;
    }

    RectF GetPaintRectWithoutTransform() override
    {
        return paintRect_;
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
        (void)bgBlurStyle;
        sysOptions_ = sysOptions;
    }

    void UpdateBackBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        (void)radius;
        backdropBlurOption = blurOption;
        sysOptions_ = sysOptions;
    }

    void UpdateBackgroundEffect(
        const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions = SysOptions())
    {
        (void)effectOption;
        sysOptions_ = sysOptions;
    }

    void OnUseEffectTypeUpdate(EffectType effectType) override
    {
    }
    void UpdateMotionBlur(const MotionBlurOption& motionBlurOption) override
    {
    }

    void UpdateFrontBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        (void)radius;
        foregroundBlurOption = blurOption;
        sysOptions_ = sysOptions;
    }

    void UpdateChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect) override
    {
        chainedTransitionEffect_ = effect;
    }

    void SetTransitionUserCallback(TransitionFinishCallback&& callback) override
    {
        transitionUserCallback_ = std::move(callback);
    }

    int32_t CalcExpectedFrameRate(const std::string& scene, float speed)
    {
        return 0;
    }

    bool HasDisappearTransition() const
    {
        return hasDisappearTransition_;
    }

    size_t GetAnimationsCount() const override
    {
        return animationsCount_;
    }

    void SetAnimationsCount(size_t count)
    {
        animationsCount_ = count;
    }

    const std::optional<SysOptions>& GetSysOptions() const
    {
        return sysOptions_;
    }

    bool hasDisappearTransition_ = false;
    RectF rect_;
    RectF paintRect_;
    BlurOption foregroundBlurOption;
    BlurOption backdropBlurOption;
    RefPtr<NG::ChainedTransitionEffect> chainedTransitionEffect_ = nullptr;
    TransitionFinishCallback transitionUserCallback_ = nullptr;
    std::optional<SysOptions> sysOptions_;
    size_t animationsCount_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
