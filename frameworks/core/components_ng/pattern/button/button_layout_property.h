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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_MAXLINES = 1;
} // namespace

class ACE_EXPORT ButtonLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ButtonLayoutProperty, LayoutProperty);

public:
    ButtonLayoutProperty() = default;

    ~ButtonLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ButtonLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propType_ = CloneType();
        value->propFontSize_ = CloneFontSize();
        value->propFontWeight_ = CloneFontWeight();
        value->propFontColor_ = CloneFontColor();
        value->propFontFamily_ = CloneFontFamily();
        value->propFontStyle_ = CloneFontStyle();
        value->propLabel_ = CloneLabel();
        value->propBorderRadius_ = CloneBorderRadius();
        value->propTextOverflow_ = CloneTextOverflow();
        value->propMaxLines_ = CloneMaxLines();
        value->propMinFontSize_ = CloneMinFontSize();
        value->propMaxFontSize_ = CloneMaxFontSize();
        value->propHeightAdaptivePolicy_ = CloneHeightAdaptivePolicy();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetType();
        ResetFontSize();
        ResetFontWeight();
        ResetFontColor();
        ResetFontFamily();
        ResetFontStyle();
        ResetLabel();
        ResetBorderRadius();
        ResetTextOverflow();
        ResetMaxLines();
        ResetMinFontSize();
        ResetMaxFontSize();
        ResetHeightAdaptivePolicy();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Type, ButtonType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextOverflow, Ace::TextOverflow, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontSize, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontWeight, Ace::FontWeight, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontFamily, std::vector<std::string>, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FontStyle, Ace::FontStyle, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Label, std::string, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BorderRadius, NG::BorderRadiusProperty, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxLines, uint32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinFontSize, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxFontSize, Dimension, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HeightAdaptivePolicy, Ace::TextHeightAdaptivePolicy, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ButtonStyle, ButtonStyleMode, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ControlSize, ControlSize, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ButtonRole, ButtonRole, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CreateWithLabel, bool, PROPERTY_UPDATE_NORMAL);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ButtonLayoutProperty);
};

enum class ModuleDialogType {
    TIMEPICKER_DIALOG = 0,
    DATEPICKER_DIALOG,
};

class DialogTypeMargin {
public:
    static void BothSidesMargin(bool isRtl, MarginProperty& margin,
        const RefPtr<DialogTheme>& dialogTheme, bool lessTwelve)
    {
        if (lessTwelve) {
            if (isRtl) {
                margin.right = CalcLength(0.0_vp);
                margin.left = CalcLength(dialogTheme->GetDividerPadding().Left());
            } else {
                margin.right = CalcLength(dialogTheme->GetDividerPadding().Right());
                margin.left = CalcLength(0.0_vp);
            }
        } else {
            if (isRtl) {
                margin.right = CalcLength(0.0_vp);
                margin.left = CalcLength(dialogTheme->GetActionsPadding().Left());
            } else {
                margin.right = CalcLength(dialogTheme->GetActionsPadding().Right());
                margin.left = CalcLength(0.0_vp);
            }
        }
    }
    
    static void UpdateDialogMargin(bool isRtl, MarginProperty& margin,
        const RefPtr<DialogTheme>& dialogTheme, bool isLessThanTwelve, ModuleDialogType type)
    {
        DialogTypeMargin::BothSidesMargin(isRtl, margin, dialogTheme, isLessThanTwelve);
        switch (type) {
            case ModuleDialogType::TIMEPICKER_DIALOG:
                if (isLessThanTwelve) {
                    margin.top = CalcLength(dialogTheme->GetDividerHeight());
                    margin.bottom = CalcLength(dialogTheme->GetDividerPadding().Bottom());
                } else {
                    margin.top = CalcLength(dialogTheme->GetActionsPadding().Bottom());
                    margin.bottom = CalcLength(dialogTheme->GetActionsPadding().Bottom());
                }
                break;
            case ModuleDialogType::DATEPICKER_DIALOG:
                if (isLessThanTwelve) {
                    margin.top = CalcLength(dialogTheme->GetButtonBottomTopMargin());
                    margin.bottom = CalcLength(dialogTheme->GetButtonBottomTopMargin());
                } else {
                    margin.top = CalcLength(dialogTheme->GetTitlePaddingHorizontal());
                    margin.bottom = CalcLength(dialogTheme->GetTitlePaddingHorizontal());
                }
                break;
            default:
                break;
        }
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BUTTON_BUTTON_LAYOUT_PROPERTY_H
