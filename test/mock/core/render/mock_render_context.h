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

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/rect_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
class MockRenderContext : public RenderContext {
    DECLARE_ACE_TYPE(MockRenderContext, RenderContext)
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

    void UpdateChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect) override
    {
        chainedTransitionEffect_ = effect;
    }

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
        paintRect_ = geometryNode->GetFrameRect();
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
        const std::optional<BlurStyleOption>& bgBlurStyle, const SysOptions& sysOptions = SysOptions()) override
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propBlurStyleOption = bgBlurStyle;
    }

    void UpdateBackBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propBlurRadius = radius;
        // see ./components_ng/render/adapter/rosen_render_context.cpp
        // RosenRenderContext::UpdateBackBlur
        backdropBlurOption = blurOption;
        sysOptions_ = sysOptions;
    }

    void UpdateBackgroundEffect(
        const std::optional<EffectOption>& effectOption, const SysOptions& sysOptions = SysOptions()) override
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propEffectOption = effectOption;
    }

    void SetOuterBorderWidth(const BorderWidthProperty& value) override
    {
        GetOrCreateOuterBorder()->propOuterBorderWidth = value;
    };

    void SetOuterBorderColor(const BorderColorProperty& value) override
    {
        GetOrCreateOuterBorder()->propOuterBorderColor = value;
    }

    void UpdateMotionBlur(const MotionBlurOption& motionBlurOption) override
    {
        const auto& groupProperty = GetOrCreateForeground();
        groupProperty->propMotionBlur = motionBlurOption;
    }

    void UpdateFrontBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override
    {
        const auto& groupProperty = GetOrCreateForeground();
        groupProperty->propBlurRadius = radius;
        foregroundBlurOption = blurOption;
    }

    void UpdateTransition(const TransitionOptions& options) override
    {
        const auto& groupPropertyA = GetOrCreateTransitionAppearing();
        if (options.Type == TransitionType::APPEARING || options.Type == TransitionType::ALL) {
            groupPropertyA->Type = options.Type;
            if (options.HasOpacity()) {
                groupPropertyA->UpdateOpacity(options.GetOpacityValue());
            }
            if (options.HasTranslate()) {
                groupPropertyA->UpdateTranslate(options.GetTranslateValue());
            }
            if (options.HasScale()) {
                groupPropertyA->UpdateScale(options.GetScaleValue());
            }
            if (options.HasRotate()) {
                groupPropertyA->UpdateRotate(options.GetRotateValue());
            }
        }
        const auto& groupPropertyD = GetOrCreateTransitionDisappearing();
        if (options.Type == TransitionType::DISAPPEARING || options.Type == TransitionType::ALL) {
            groupPropertyD->Type = options.Type;
            if (options.HasOpacity()) {
                groupPropertyD->UpdateOpacity(options.GetOpacityValue());
            }
            if (options.HasTranslate()) {
                groupPropertyD->UpdateTranslate(options.GetTranslateValue());
            }
            if (options.HasScale()) {
                groupPropertyD->UpdateScale(options.GetScaleValue());
            }
            if (options.HasRotate()) {
                groupPropertyD->UpdateRotate(options.GetRotateValue());
            }
        }
    }

    int32_t CalcExpectedFrameRate(const std::string& scene, float speed) override
    {
        return 0;
    }

    void SetOpacityMultiplier(float opacity) override
    {
        opacityMultiplier_ = opacity;
    }

    bool HasDisappearTransition() const override
    {
        return hasDisappearTransition_;
    }

    void SetTransitionOutCallback(std::function<void()>&& callback) override
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

    const std::optional<SysOptions>& GetSysOptions() const
    {
        return sysOptions_;
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

    size_t animationsCount_ = 0;
    BlurOption backdropBlurOption;
    BlurOption foregroundBlurOption;
    RefPtr<NG::ChainedTransitionEffect> chainedTransitionEffect_ = nullptr;
    TransitionFinishCallback transitionUserCallback_;
    std::optional<SysOptions> sysOptions_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
