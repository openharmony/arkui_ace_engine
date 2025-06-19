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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/checkbox/checkbox_modifier.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components/checkable/checkable_theme.h"
namespace OHOS::Ace::NG {
class CheckBoxPaintProperty;
constexpr float CHECKBOX_MARK_STROKEWIDTH_LIMIT_RATIO = 0.25f;
class CheckBoxPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxPaintMethod, NodePaintMethod)

public:
    CheckBoxPaintMethod() = default;

    ~CheckBoxPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override;

    void UpdateCheckboxColors(const RefPtr<CheckBoxPaintProperty>& paintProperty);

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;

    void SetModifierBoundsRect(
        const RefPtr<CheckboxTheme>& theme, const SizeF& size, const OffsetF& offset, PaintWrapper* paintWrapper);

    void SetHoverEffectType(const RefPtr<CheckBoxPaintProperty>& checkBoxPaintProperty);

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
    }

    void SetTotalScale(float totalScale)
    {
        totalScale_ = totalScale;
    }

    void SetPointScale(float pointScale)
    {
        pointScale_ = pointScale;
    }

    void SetTouchHoverAnimationType(const TouchHoverAnimationType touchHoverType)
    {
        touchHoverType_ = touchHoverType;
    }

    void SetCheckboxStyle(CheckBoxStyle checkBoxStyle)
    {
        checkBoxStyle_ = checkBoxStyle;
    }

    void SetUseContentModifier(bool useContentModifier)
    {
        useContentModifier_ = useContentModifier;
    }

    void SetHasBuilder(bool hasBuilder)
    {
        hasBuilder_ = hasBuilder;
    }

    RefPtr<CheckBoxModifier> GetCheckBoxModifier()
    {
        return checkboxModifier_;
    }

    void SetNeedAnimation(bool needAnimation)
    {
        needAnimation_ = needAnimation;
    }

private:
    bool enabled_ = true;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    bool hasBuilder_ = false;
    bool useContentModifier_ = false;
    bool needAnimation_ = true;
    CheckBoxStyle checkBoxStyle_ = CheckBoxStyle::CIRCULAR_STYLE;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    TouchHoverAnimationType touchHoverType_ = TouchHoverAnimationType::NONE;

    RefPtr<CheckBoxModifier> checkboxModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
