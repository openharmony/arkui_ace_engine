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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text_drag/text_drag_overlay_modifier.h"

namespace OHOS::Ace::NG {
class TextDragPattern;

class RichEditorDragOverlayModifier : public TextDragOverlayModifier {
    DECLARE_ACE_TYPE(RichEditorDragOverlayModifier, TextDragOverlayModifier);

public:
    RichEditorDragOverlayModifier(
        const WeakPtr<OHOS::Ace::NG::Pattern>& pattern, const WeakPtr<TextPattern>& hostPattern)
        : TextDragOverlayModifier(pattern), hostPattern_(hostPattern)
    {
        firstHandle_ = AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0));
        secondHandle_ = AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0));
        handleRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
        handleColor_ = AceType::MakeRefPtr<PropertyColor>(Color::BLACK);
        innerHandleRadius_ = AceType::MakeRefPtr<PropertyFloat>(0.0);
        innerHandleColor_ = AceType::MakeRefPtr<PropertyColor>(Color::BLACK);
        handleOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
        selectedColor_ = AceType::MakeRefPtr<PropertyInt>(0);
        shadowOpacity_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0);
        AttachProperty(firstHandle_);
        AttachProperty(secondHandle_);
        AttachProperty(handleRadius_);
        AttachProperty(handleColor_);
        AttachProperty(innerHandleRadius_);
        AttachProperty(innerHandleColor_);
        AttachProperty(handleOpacity_);
        AttachProperty(selectedColor_);
        AttachProperty(shadowOpacity_);
    }

    ~RichEditorDragOverlayModifier() override = default;

    void onDraw(DrawingContext& context) override;
    void StartFloatingAnimate() override;
    void StartFloatingSelBackgroundAnimate();

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

    void SetHandleColor(const Color& color)
    {
        CHECK_NULL_VOID(handleColor_);
        handleColor_->Set(color);
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

    void SetHandleOpacity(float opacity)
    {
        CHECK_NULL_VOID(handleOpacity_);
        handleOpacity_->Set(opacity);
    }

    void SetSelectedColor(uint32_t selectedColor)
    {
        CHECK_NULL_VOID(selectedColor_);
        selectedColor_->Set(static_cast<int32_t>(selectedColor));
    }

    void SetShadowOpacity(float opacity)
    {
        CHECK_NULL_VOID(shadowOpacity_);
        shadowOpacity_->Set(opacity);
    }

    void SetDragBackgroundColor(const std::optional<Color>& color)
    {
        dragBackgroundColor_ = color;
    }

    void SetIsDragShadowNeeded(bool isDragShadowNeeded)
    {
        isDragShadowNeeded_ = isDragShadowNeeded;
    }

private:
    void PaintImage(DrawingContext& context);
    void PaintImageNode(DrawingContext& context, const RefPtr<FrameNode>& imageNode,
        const RefPtr<ImagePattern>& pattern, const OffsetF& offset);
    void PaintFrameNode(DrawingContext& context, const RefPtr<FrameNode>& frameNode,
        const RefPtr<Pattern>& pattern, const OffsetF& offset);
    void PaintBackground(const RSPath& path, RSCanvas& canvas, RefPtr<TextDragPattern> textDragPattern,
        RefPtr<RichEditorPattern> richEditorPattern);
    void PaintSelBackground(RSCanvas& canvas, RefPtr<TextDragPattern> textDragPattern,
        RefPtr<RichEditorPattern> richEditorPattern);
    void PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool isFirstHandle, float startX, float startY);
    void PaintHandleRing(RSCanvas& canvas);
    void PaintHandleHold(RSCanvas& canvas, const RectF& handleRect, const OffsetF& startPoint,
        const OffsetF& endPoint);
    void PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas& canvas);
    Color GetDragBackgroundColor(const Color& defaultColor);

    DragAnimType type_ = DragAnimType::DEFAULT;
    const WeakPtr<TextPattern> hostPattern_;
    RefPtr<PropertyRectF> firstHandle_;
    RefPtr<PropertyRectF> secondHandle_;
    RefPtr<PropertyFloat> handleRadius_;
    RefPtr<PropertyColor> handleColor_;
    RefPtr<PropertyFloat> innerHandleRadius_;
    RefPtr<PropertyColor> innerHandleColor_;
    RefPtr<AnimatablePropertyFloat> handleOpacity_;
    RefPtr<AnimatablePropertyFloat> shadowOpacity_;
    RefPtr<PropertyInt> selectedColor_;
    std::optional<Color> dragBackgroundColor_;
    bool isDragShadowNeeded_ = true;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorDragOverlayModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_DRAG_RICH_EDITOR_DRAG_OVERLAY_MODIFIER_H
