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
enum class OpacityAnimationType {
    /*
     * do not run opacity animation.
     */
    NONE = 0,
    /*
     *  run disappear animation.
     */
    DISAPPEAR,
    /*
     * run appear animation.
     */
    APPEAR,
};

enum class HoverAnimationType {
    /*
     * do not run hover animation.
     */
    NONE = 0,
    /*
     *  run grow animation.
     */
    GROW,
    /*
     *  run shrink animation.
     */
    SHRINK,
};
class ScrollBarOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(ScrollBarOverlayModifier, OverlayModifier)

public:
    ScrollBarOverlayModifier();

    ~ScrollBarOverlayModifier() override = default;

    void onDraw(DrawingContext& drawingContext) override;

    void StartOpacityAnimation(OpacityAnimationType opacityAnimationType);

    void SetRect(const SizeF& fgSize, const SizeF& bgSize, const OffsetF& fgOffset, const OffsetF& bgOffset,
        HoverAnimationType hoverAnimationType);

    void SetOffset(OffsetF fgOffset, OffsetF bgOffset);

    void SetFgColor(Color fgColor);

    void SetBgColor(Color bgColor);

    void StopBarOpacityAnimation();

    void StopBarHoverAnimation();

    HoverAnimationType GetHoverAnimatingType() const
    {
        return hoverAnimatingType_;
    }

    void SetHoverAnimatingType(HoverAnimationType hoverAnimatingType)
    {
        hoverAnimatingType_ = hoverAnimatingType;
    }

    OpacityAnimationType GetOpacityAnimatingType() const
    {
        return opacityAnimatingType_;
    }

    void SetOpacityAnimatingType(OpacityAnimationType opacityAnimatingType)
    {
        opacityAnimatingType_ = opacityAnimatingType;
    }

    void SetOpacity(uint8_t opacity)
    {
        CHECK_NULL_VOID_NOLOG(opacity_);
        opacity_->Set(opacity);
    }

    uint8_t GetOpacity() const
    {
        CHECK_NULL_RETURN_NOLOG(opacity_, 0);
        return opacity_->Get();
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
    HoverAnimationType hoverAnimatingType_ = HoverAnimationType::NONE;
    OpacityAnimationType opacityAnimatingType_ = OpacityAnimationType::NONE;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SCROLL_BAR_OVERLAY_MODIFIER_H