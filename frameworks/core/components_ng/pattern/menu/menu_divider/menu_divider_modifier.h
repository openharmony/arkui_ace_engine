/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_DIVIDER_MENU_DIVIDER_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_DIVIDER_MENU_DIVIDER_MODIFIER_H

#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
class MenuDividerModifier : public ContentModifier {
    DECLARE_ACE_TYPE(MenuDividerModifier, ContentModifier);
public:
    MenuDividerModifier(float strokeWidth, const Color& dividerColor);
    ~MenuDividerModifier() override = default;
    void onDraw(DrawingContext& context) override;

    void SetLeftMargin(float leftMargin)
    {
        CHECK_NULL_VOID(leftMargin_);
        leftMargin_->Set(leftMargin);
    }

    void SetRightMargin(float rightMargin)
    {
        CHECK_NULL_VOID(rightMargin_);
        rightMargin_->Set(rightMargin);
    }

    void SetStrokeWidth(float strokeWidth)
    {
        CHECK_NULL_VOID(strokeWidth_);
        strokeWidth_->Set(strokeWidth);
    }

    void SetDividerColor(Color dividerColor)
    {
        CHECK_NULL_VOID(dividerColor_);
        dividerColor_->Set(dividerColor);
    }

    void SetNeedDivider(bool needDivider)
    {
        CHECK_NULL_VOID(needDivider_);
        needDivider_->Set(needDivider);
    }

    void SetPress(bool press)
    {
        CHECK_NULL_VOID(press_);
        press_->Set(press);
    }

    void SetHover(bool hover)
    {
        CHECK_NULL_VOID(hover_);
        hover_->Set(hover);
    }

    void SetSelected(bool selected)
    {
        CHECK_NULL_VOID(selected_);
        selected_->Set(selected);
    }

    void SetDefaultShow(bool defaultShow)
    {
        CHECK_NULL_VOID(defaultShow_);
        defaultShow_->Set(defaultShow);
    }

private:
    RefPtr<PropertyFloat> strokeWidth_;
    RefPtr<PropertyColor> dividerColor_;
    RefPtr<PropertyFloat> leftMargin_;
    RefPtr<PropertyFloat> rightMargin_;
    RefPtr<PropertyBool> needDivider_;
    RefPtr<PropertyBool> press_;
    RefPtr<PropertyBool> hover_;
    RefPtr<PropertyBool> selected_;
    RefPtr<PropertyBool> defaultShow_;
    ACE_DISALLOW_COPY_AND_MOVE(MenuDividerModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_DIVIDER_MENU_DIVIDER_MODIFIER_H
