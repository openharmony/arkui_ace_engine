/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MASK_PROGRESS_MOON_PROGRESS_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MASK_PROGRESS_MOON_PROGRESS_MODIFIER_H

#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::NG {
class MoonProgressModifier : public OverlayModifier {
public:
    MoonProgressModifier();
    ~MoonProgressModifier() override = default;
    
    void onDraw(DrawingContext& context) override;

    void SetMaskColor(LinearColor color);
    void SetValue(float value);
    void SetMaxValue(float value);
    float GetMaxValue();
    void InitRatio();
    void SetMoonAnimate(float value) const;
    void SetBigRadius(const SizeF& frameSize);

private:
    void PaintSquareMoon(RSCanvas& canvas, const SizeF& frameSize) const;

    // Animatable
    RefPtr<AnimatablePropertyColor> maskColor_;
    RefPtr<AnimatablePropertyFloat> ratio_;
    RefPtr<AnimatablePropertyFloat> value_;
    // No animatable
    RefPtr<PropertyFloat> maxValue_;
    // Others
    float bigRadius_ = .0f;
    float smallRadius_ = .0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MASK_PROGRESS_MOON_PROGRESS_MODIFIER_H
