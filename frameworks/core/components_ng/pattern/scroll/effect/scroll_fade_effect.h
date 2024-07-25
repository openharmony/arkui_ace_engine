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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_EFFECT_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_controller.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_painter.h"

namespace OHOS::Ace::NG {
constexpr float SCALE_THRESHOLD = 0.3f;
constexpr float OVER_SCROLL_THRESHOLD = 2.0f;

class ACE_EXPORT ScrollFadeEffect final : public ScrollEdgeEffect {
    DECLARE_ACE_TYPE(ScrollFadeEffect, ScrollEdgeEffect);

public:
    explicit ScrollFadeEffect(const Color& color = Color::GRAY)
        : ScrollEdgeEffect(EdgeEffect::FADE), fadeColor_(color) {}
    ~ScrollFadeEffect() override = default;

    const Color& GetFadeColor() const
    {
        return fadeColor_;
    }

    void InitialEdgeEffect() override;
    double CalculateOverScroll(double oldPosition, bool isReachMax) override;
    void Paint(RSCanvas& canvas, const SizeF& viewPort, const OffsetF& offset) override;
    void HandleOverScroll(Axis axis, float overScroll, const SizeF& viewPort,
        bool isScrollFromUpdate = false, bool isNotPositiveScrollableDistance = false) override;
    void SetHandleOverScrollCallback(const HandleOverScrollCallback& callback) override;

private:
    void ResetFadeEffect(const Color& color);
    void SetOpacityAndScale(float opacity, float scale);
    void SetPaintDirection(Axis axis, float overScroll, bool isNotPositiveScrollableDistance);

    Color fadeColor_ = Color::GRAY;
    RefPtr<ScrollFadePainter> fadePainter_;
    RefPtr<ScrollFadeController> fadeController_;
    HandleOverScrollCallback handleOverScrollCallback_ = nullptr;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_EFFECT_SCROLL_FADE_EFFECT_H
