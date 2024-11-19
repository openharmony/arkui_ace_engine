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
    MOCK_METHOD1(SetContentClip, void(const std::variant<RectF, RefPtr<ShapeRect>>&));

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

#ifdef ENHANCED_ANIMATION
    void AttachNodeAnimatableProperty(RefPtr<NodeAnimatablePropertyBase> modifier) override;
    void DetachNodeAnimatableProperty(const RefPtr<NodeAnimatablePropertyBase>& modifier) override {}

    void CancelTranslateXYAnimation() override;
    OffsetF GetTranslateXYProperty() override;
    void UpdateTranslateInXY(const OffsetF& offset) override;
#endif


    void UpdateBackBlurStyle(const std::optional<BlurStyleOption>& bgBlurStyle)
    {
        const auto& groupProperty = GetOrCreateBackground();
        groupProperty->propBlurStyleOption = bgBlurStyle;
    }

    void UpdateMotionBlur(const MotionBlurOption& motionBlurOption)
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

    bool isVisible_ = true;
    bool hasDisappearTransition_ = false;
    RectF rect_;
    RectF paintRect_;
    Color blendColor_ = Color::TRANSPARENT;
    RefPtr<AnimatablePropertyOffsetF> translateXY_;
    float opacityMultiplier_ = 1.0f;
    std::function<void()> transitionOutCallback_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_RENDER_CONTEXT_H
