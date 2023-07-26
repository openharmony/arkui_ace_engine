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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ScrollBarOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(ScrollBarOverlayModifier, OverlayModifier)

public:
    ScrollBarOverlayModifier();

    ~ScrollBarOverlayModifier() override = default;

    void onDraw(DrawingContext& drawingContext) override;

    void SetOpacity(uint8_t opacity);

    void SetRect(const SizeF& fgSize, const SizeF& bgSize, const OffsetF& fgOffset, const OffsetF& bgOffset);

    void SetOffset(OffsetF fgOffset, OffsetF bgOffset);

    void SetFgColor(Color fgColor);

    void SetBgColor(Color bgColor);

    void StartBarEndAnimation();

    void StartBarAppearAnimation();

    void StopBarOpacityAnimation();

    void StopBarHoverAnimation();

    void SetNeedGrowAnimation(bool needGrowAnimation)
    {
        needGrowAnimation_ = needGrowAnimation;
    }

    bool GetNeedGrowAnimation() const
    {
        return needGrowAnimation_;
    }

    void SetNeedShrinkAnimation(bool needShrinkAnimation)
    {
        needShrinkAnimation_ = needShrinkAnimation;
    }

    bool GetNeedShrinkAnimation() const
    {
        return needShrinkAnimation_;
    }

    void SetNeedEndAnimation(bool needEndAnimation)
    {
        needEndAnimation_ = needEndAnimation;
    }

    bool GetNeedEndAnimation() const
    {
        return needEndAnimation_;
    }

    void SetNeedAppearAnimation(bool needAppearAnimation)
    {
        needAppearAnimation_ = needAppearAnimation;
    }

    bool GetNeedAppearAnimation() const
    {
        return needAppearAnimation_;
    }

    bool GetIsEnding() const
    {
        return isEnding_;
    }

    void SetIsEnding(bool isEnding)
    {
        isEnding_ = isEnding;
    }

    bool GetIsAppearing() const
    {
        return isAppearing_;
    }

    void SetIsAppearing(bool isAppearing)
    {
        isAppearing_ = isAppearing;
    }

    bool GetIsGrowing() const
    {
        return isGrowing_;
    }

    void SetIsGrowing(bool isGrowing)
    {
        isGrowing_ = isGrowing;
    }

    bool GetIsShrinking() const
    {
        return isShrinking_;
    }

    void SetIsShrinking(bool isShrinking)
    {
        isShrinking_ = isShrinking;
    }

private:
    // Animatable
    RefPtr<AnimatablePropertyUint8> opacity_;
    RefPtr<AnimatablePropertyOffsetF> fgOffset_;
    RefPtr<AnimatablePropertySizeF> fgSize_;
    RefPtr<AnimatablePropertyOffsetF> bgOffset_;
    RefPtr<AnimatablePropertySizeF> bgSize_;

    // no Animatable
    RefPtr<PropertyColor> fgColor_;
    RefPtr<PropertyColor> bgColor_;
    ACE_DISALLOW_COPY_AND_MOVE(ScrollBarOverlayModifier);

    std::shared_ptr<AnimationUtils::Animation> hoverAnimation_;
    std::shared_ptr<AnimationUtils::Animation> opacityAnimation_;
    bool isGrowing_ = false;
    bool isShrinking_ = false;
    bool needGrowAnimation_ = false;
    bool needShrinkAnimation_ = false;
    bool needEndAnimation_ = false;
    bool needAppearAnimation_ = false;
    bool isEnding_ = false;
    bool isAppearing_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_OVERLAY_MODIFIER_H