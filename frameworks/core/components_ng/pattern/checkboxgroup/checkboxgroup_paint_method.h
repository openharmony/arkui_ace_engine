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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_modifier.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/radio/radio_paint_method.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {

class CheckBoxGroupPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(CheckBoxGroupPaintMethod, NodePaintMethod)

public:
    CheckBoxGroupPaintMethod(bool enabled, bool isTouch, bool isHover, float shapeScale, UIStatus uiStatus,
        const RefPtr<CheckBoxGroupModifier>& checkboxGroupModifier)
        : enabled_(enabled), isTouch_(isTouch), isHover_(isHover),
        shapeScale_(shapeScale), uiStatus_(uiStatus), checkboxGroupModifier_(checkboxGroupModifier)
    {};

    ~CheckBoxGroupPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(checkboxGroupModifier_, nullptr);
        return checkboxGroupModifier_;
    }
    
    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(checkboxGroupModifier_);
        CHECK_NULL_VOID(paintWrapper);
        auto paintProperty = DynamicCast<CheckBoxGroupPaintProperty>(paintWrapper->GetPaintProperty());
        auto size = paintWrapper->GetContentSize();
        auto offset = paintWrapper->GetContentOffset();
        float strokePaintSize = size.Width();
        if (paintProperty->GetCheckBoxGroupSelectedColor().has_value()) {
            checkboxGroupModifier_->SetActiveColor(paintProperty->GetCheckBoxGroupSelectedColor().value());
        }
        if (paintProperty->GetCheckBoxGroupUnSelectedColor().has_value()) {
            checkboxGroupModifier_->SetInactiveColor(paintProperty->GetCheckBoxGroupUnSelectedColor().value());
        }
        if (paintProperty->GetCheckBoxGroupCheckMarkColor().has_value()) {
            checkboxGroupModifier_->SetPointColor(paintProperty->GetCheckBoxGroupCheckMarkColor().value());
        }
        if (paintProperty->GetCheckBoxGroupCheckMarkSize().has_value()) {
            if (paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx() >= 0) {
                strokePaintSize = paintProperty->GetCheckBoxGroupCheckMarkSizeValue().ConvertToPx();
            } else {
                paintProperty->UpdateCheckBoxGroupCheckMarkSize(Dimension(strokePaintSize));
            }
        }
        checkboxGroupModifier_->SetCheckMarkPaintSize(strokePaintSize);
        if (paintProperty->GetCheckBoxGroupCheckMarkWidth().has_value()) {
            checkboxGroupModifier_->SetCheckStroke(paintProperty->GetCheckBoxGroupCheckMarkWidthValue().ConvertToPx());
        }
        auto selectStatus = paintProperty->GetSelectStatus();

        checkboxGroupModifier_->SetEnabled(enabled_);
        checkboxGroupModifier_->SetIsTouch(isTouch_);
        checkboxGroupModifier_->SetIsHover(isHover_);
        checkboxGroupModifier_->SetShapeScale(shapeScale_);
        checkboxGroupModifier_->SetUiStatus(uiStatus_);
        checkboxGroupModifier_->SetSelectStatus(selectStatus);
        checkboxGroupModifier_->SetOffset(offset);
        checkboxGroupModifier_->SetSize(size);
    }

    void SetHotZoneOffset(OffsetF& hotZoneOffset)
    {
        hotZoneOffset_ = hotZoneOffset;
    }

    void SetHotZoneSize(SizeF& hotZoneSize)
    {
        hotZoneSize_ = hotZoneSize;
    }

private:
    bool enabled_ = true;
    bool isTouch_ = false;
    bool isHover_ = false;
    float shapeScale_ = 1.0f;
    UIStatus uiStatus_ = UIStatus::UNSELECTED;
    OffsetF hotZoneOffset_;
    SizeF hotZoneSize_;
    RefPtr<CheckBoxGroupModifier> checkboxGroupModifier_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_CHECKBOXGROUP_CHECKBOXGROUP_PAINT_METHOD_H
