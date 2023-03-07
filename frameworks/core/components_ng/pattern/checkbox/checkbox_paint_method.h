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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/checkbox/checkbox_modifier.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
namespace OHOS::Ace::NG {
class CheckBoxPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxPaintMethod, NodePaintMethod)

public:
    explicit CheckBoxPaintMethod(const RefPtr<CheckBoxModifier>& checkboxModifier) : checkboxModifier_(checkboxModifier)
    {}

    ~CheckBoxPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(checkboxModifier_, nullptr);
        return checkboxModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(checkboxModifier_);
        checkboxModifier_->InitializeParam();
        auto paintProperty = DynamicCast<CheckBoxPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty->GetCheckBoxSelect().has_value()) {
            checkboxModifier_->SetIsSelect(paintProperty->GetCheckBoxSelectValue());
        }
        if (paintProperty->HasCheckBoxSelectedColor()) {
            checkboxModifier_->SetUserActiveColor(paintProperty->GetCheckBoxSelectedColorValue());
        }
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        checkboxModifier_->SetSize(size);
        checkboxModifier_->SetOffset(offset);
        checkboxModifier_->SetEnabled(enabled_);
        checkboxModifier_->SetIsHover(isHover_);
        checkboxModifier_->UpdateAnimatableProperty();
    }

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

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    void SetTotalScale(float totalScale)
    {
        totalScale_ = totalScale;
    }

    void SetPointScale(float pointScale)
    {
        pointScale_ = pointScale;
    }

private:
    bool enabled_ = true;
    bool isHover_ = false;
    float totalScale_ = 1.0f;
    float pointScale_ = 0.5f;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;

    RefPtr<CheckBoxModifier> checkboxModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOX_CHECKBOX_PAINT_METHOD_H
