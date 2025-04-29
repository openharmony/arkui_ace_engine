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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t TEXT_ANIMATION_DURATION = 300;
constexpr Dimension TEXT_DRAG_DEFAULT_OFFSET = 8.0_vp;
constexpr int32_t TEXT_FLOATING_ANIMATE_HANDLE_OPACITY_DURATION = 150;

class TextDragPattern;
enum class DragAnimType { FLOATING, FLOATING_CANCEL, DEFAULT };

class TextDragOverlayModifier : public OverlayModifier {
    DECLARE_ACE_TYPE(TextDragOverlayModifier, OverlayModifier);

public:
    explicit TextDragOverlayModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextDragOverlayModifier() override = default;

    virtual void StartFloatingAnimate();
    void StartFloatingSelBackgroundAnimate();

    bool IsHandlesShow()
    {
        return isHandlesShow_;
    }

    void UpdateHandlesShowFlag(bool isHandlesShow)
    {
        isHandlesShow_ = isHandlesShow;
    }

    void SetAnimateFlag(bool isAnimate)
    {
        isAnimating_ = isAnimate;
    }

    void SetShadowOpacity(float opacity)
    {
        CHECK_NULL_VOID(shadowOpacity_);
        shadowOpacity_->Set(opacity);
    }

    void SetHandleOpacity(float opacity)
    {
        CHECK_NULL_VOID(handleOpacity_);
        handleOpacity_->Set(opacity);
    }

    void SetFirstHandle(const RectF& handle)
    {
        CHECK_NULL_VOID(firstHandle_);
        firstHandle_->Set(handle);
    }

    void SetSecondHandle(const RectF& handle)
    {
        CHECK_NULL_VOID(secondHandle_);
        secondHandle_->Set(handle);
    }

    void SetHandleRadius(float radius)
    {
        CHECK_NULL_VOID(handleRadius_);
        handleRadius_->Set(radius);
    }

    void SetInnerHandleRadius(float radius)
    {
        CHECK_NULL_VOID(innerHandleRadius_);
        innerHandleRadius_->Set(radius);
    }

    void SetInnerHandleColor(const Color& color)
    {
        CHECK_NULL_VOID(innerHandleColor_);
        innerHandleColor_->Set(color);
    }

    void SetHandleColor(const Color& color)
    {
        CHECK_NULL_VOID(handleColor_);
        handleColor_->Set(color);
    }

    void SetSelectedColor(uint32_t selectedColor)
    {
        CHECK_NULL_VOID(selectedColor_);
        selectedColor_->Set(static_cast<int32_t>(selectedColor));
    }

    void SetIsFirstHandleAnimated(bool isFirstHandleAnimated)
    {
        isFirstHandleAnimated_ = isFirstHandleAnimated;
    }

    void SetIsSecondHandleAnimated(bool isSecondHandleAnimated)
    {
        isSecondHandleAnimated_ = isSecondHandleAnimated;
    }

    void PaintBackground(const RSPath& path, RSCanvas& canvas, RefPtr<TextDragPattern> textDragPattern);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);
    void onDraw(DrawingContext& context) override;
    void SetBackgroundOffset(float offset);
    void SetSelectedBackgroundOpacity(float opacity);
    void PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool isFirstHandle, float startX, float startY);
    void PaintHandleRing(RSCanvas& canvas);
    void PaintHandleHold(RSCanvas& canvas, const RectF& handleRect, const OffsetF& startPoint,
        const OffsetF& endPoint);
    void PaintSelBackground(RSCanvas& canvas, const RefPtr<TextDragPattern>& textDragPattern);
    void PaintImage(RSCanvas& canvas);

protected:
    WeakPtr<Pattern> pattern_;
    bool isAnimating_ = false;
    bool isHandlesShow_ = false;
    bool isFirstHandleAnimated_ = true;
    bool isSecondHandleAnimated_ = true;
    RefPtr<AnimatablePropertyFloat> backgroundOffset_;
    RefPtr<AnimatablePropertyFloat> selectedBackgroundOpacity_;
    RefPtr<AnimatablePropertyFloat> handleOpacity_;
    RefPtr<PropertyRectF> firstHandle_;
    RefPtr<PropertyRectF> secondHandle_;
    RefPtr<PropertyFloat> handleRadius_;
    RefPtr<PropertyColor> innerHandleColor_;
    RefPtr<PropertyColor> handleColor_;
    RefPtr<PropertyFloat> innerHandleRadius_;
    RefPtr<PropertyInt> selectedColor_;
private:
    DragAnimType type_ = DragAnimType::DEFAULT;
    RefPtr<AnimatablePropertyFloat> shadowOpacity_;

    ACE_DISALLOW_COPY_AND_MOVE(TextDragOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_DRAG_TEXT_DRAG_OVERLAY_MODIFIER_H
