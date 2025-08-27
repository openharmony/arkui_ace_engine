/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_PROPERTY_H

#include "base/utils/utf_helper.h"
#include "core/common/ime/text_input_type.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextFieldLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(TextFieldLayoutProperty, LayoutProperty);

public:
    TextFieldLayoutProperty() = default;

    ~TextFieldLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<TextFieldLayoutProperty>();
        Clone(value);
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetFontStyle();
        ResetTextLineStyle();
        ResetValue();
        ResetPlaceholderFontStyle();
        ResetPlaceholderTextLineStyle();
        ResetShowPasswordText();
        ResetPlaceholder();
        ResetTextInputType();
        ResetInputFilter();
        ResetShowPasswordIcon();
        ResetCopyOptions();
        ResetLastValue();
        ResetNeedFireOnChange();
        ResetWidthAuto();
        ResetErrorText();
        ResetShowErrorText();
        ResetShowCounter();
        ResetShowUnderline();
        ResetShowPasswordSourceInfo();
        ResetHidePasswordSourceInfo();
        ResetTextAlignChanged();
        ResetDisplayMode();
        ResetMaxViewLines();
        ResetNormalMaxViewLines();
        ResetMinLines();
        ResetSelectionMenuHidden();
        ResetPasswordRules();
        ResetEnableAutoFill();
        ResetEnableAutoFillAnimation();
        ResetCleanNodeStyle();
        ResetIconSize();
        ResetIconSrc();
        ResetBundleName();
        ResetModuleName();
        ResetIconColor();
        ResetIsShowSymbol();
        ResetSelectAllValue();
        ResetShowHighlightBorder();
        ResetSetCounter();
        ResetNumberOfLines();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("showPasswordIcon", propShowPasswordIcon_.value_or(true), filter);
        json->PutExtAttr("showPassword", propShowPasswordText_.value_or(false), filter);
        json->PutExtAttr("errorText", UtfUtils::Str16DebugToStr8(propErrorText_.value_or(u"")).c_str(), filter);
        json->PutExtAttr("showErrorText", propShowErrorText_.value_or(false), filter);
        json->PutExtAttr("highlightBorder", propShowHighlightBorder_.value_or(true), filter);
        json->PutExtAttr("showUnderline", propShowUnderline_.value_or(false), filter);
        json->PutExtAttr("passwordRules", propPasswordRules_.value_or("").c_str(), filter);
        json->PutExtAttr("enableAutoFill", propEnableAutoFill_.value_or(true), filter);
        json->PutExtAttr("enableAutoFillAnimation", propEnableAutoFillAnimation_.value_or(true), filter);
        auto jsonCancelButton = JsonUtil::Create(true);
        jsonCancelButton->Put("style", static_cast<int32_t>(propCleanNodeStyle_.value_or(CleanNodeStyle::INPUT)));
        auto jsonIconOptions = JsonUtil::Create(true);
        jsonIconOptions->Put("size", propIconSize_.value_or(Dimension()).ToString().c_str());
        jsonIconOptions->Put("src", propIconSrc_.value_or("").c_str());
        jsonIconOptions->Put("color", propIconColor_.value_or(Color()).ColorToString().c_str());
        jsonCancelButton->Put("icon", jsonIconOptions->ToString().c_str());
        json->PutExtAttr("cancelButton", jsonCancelButton->ToString().c_str(), filter);
        json->PutExtAttr("selectAll", propSelectAllValue_.value_or(false), filter);
        json->PutExtAttr("letterSpacing", GetLetterSpacing().value_or(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("lineHeight", GetLineHeight().value_or(0.0_vp).ToString().c_str(), filter);
        json->PutExtAttr("halfLeading", GetHalfLeading().value_or(false), filter);
        json->PutExtAttr("lineSpacing", GetLineSpacing().value_or(0.0_vp).ToString().c_str(), filter);
        auto jsonDecoration = JsonUtil::Create(true);
        std::string type = V2::ConvertWrapTextDecorationToStirng(
            GetTextDecoration().value_or(std::vector<TextDecoration>({TextDecoration::NONE})));
        jsonDecoration->Put("type", type.c_str());
        jsonDecoration->Put("color", GetTextDecorationColor().value_or(Color::BLACK).ColorToString().c_str());
        std::string style = V2::ConvertWrapTextDecorationStyleToString(
            GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID));
        jsonDecoration->Put("style", style.c_str());
        json->PutExtAttr("decoration", jsonDecoration->ToString().c_str(), filter);
        json->PutExtAttr("minFontSize", GetAdaptMinFontSize().value_or(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("maxFontSize", GetAdaptMaxFontSize().value_or(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("heightAdaptivePolicy", V2::ConvertWrapTextHeightAdaptivePolicyToString(
            GetHeightAdaptivePolicy().value_or(TextHeightAdaptivePolicy::MAX_LINES_FIRST)).c_str(), filter);
        json->Put("wordBreak",
            V2::ConvertWrapWordBreakToString(GetWordBreak().value_or(WordBreak::BREAK_WORD)).c_str());
        json->Put("textOverflow",
            V2::ConvertWrapTextOverflowToString(GetTextOverflow().value_or(TextOverflow::CLIP)).c_str());
        json->PutExtAttr("textIndent", GetTextIndent().value_or(0.0_vp).ToString().c_str(), filter);
        json->PutExtAttr("stopBackPress", GetStopBackPress().value_or(true), filter);
        json->PutExtAttr("onlyBetweenLines", GetIsOnlyBetweenLines().value_or(false) ? "true" : "false", filter);
        json->PutExtAttr("enableAutoSpacing", std::to_string(GetEnableAutoSpacing().value_or(false)).c_str(), filter);
    }

    const std::function<void(WeakPtr<NG::FrameNode>)>& GetCancelIconSymbol() const
    {
        return cancelIconSymbol_;
    }

    void SetCancelIconSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& cancelIconSymbol)
    {
        cancelIconSymbol_ = cancelIconSymbol;
    }

    TextDecoration GetTextDecorationFirst() const
    {
        auto decorations = GetTextDecoration();
        if (!decorations.has_value()) {
            return TextDecoration::NONE;
        }
        return decorations.value().size() > 0 ?
            decorations.value()[0] : TextDecoration::NONE;
    }

    ACE_DEFINE_PROPERTY_GROUP(FontStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, MinFontScale, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, MaxFontScale, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, ItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, FontFeature, FONT_FEATURES_LIST, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, LetterSpacing, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, AdaptMinFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, AdaptMaxFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        FontStyle, TextDecoration, std::vector<TextDecoration>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextDecorationColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, TextDecorationStyle, TextDecorationStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FontStyle, StrokeColor, Color, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(TextLineStyle, TextLineStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextAlign, TextAlign, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, LineBreakStrategy, LineBreakStrategy, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, MaxLength, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, MaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, OverflowMode, OverflowMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        TextLineStyle, HeightAdaptivePolicy, TextHeightAdaptivePolicy, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, LineHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, HalfLeading, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, LineSpacing, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, IsOnlyBetweenLines, bool, PROPERTY_UPDATE_MEASURE)
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, WordBreak, WordBreak, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextOverflow, TextOverflow, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, TextIndent, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, NumberOfLines, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(TextLineStyle, EllipsisMode, EllipsisMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Value, std::u16string, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreviewText, PreviewText, PROPERTY_UPDATE_NORMAL);

    ACE_DEFINE_PROPERTY_GROUP(PlaceholderFontStyle, FontStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontSize, PlaceholderFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, TextColor, PlaceholderTextColor, Color, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, ItalicFontStyle, PlaceholderItalicFontStyle, Ace::FontStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontWeight, PlaceholderFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderFontStyle, FontFamily, PlaceholderFontFamily, std::vector<std::string>, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(PlaceholderTextLineStyle, TextLineStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderTextLineStyle, LineHeight, PlaceholderLineHeight, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderTextLineStyle, TextAlign, PlaceholderTextAlign, TextAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderTextLineStyle, MaxLength, PlaceholderMaxLength, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP_ITEM(
        PlaceholderTextLineStyle, MaxLines, PlaceholderMaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Placeholder, std::u16string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ErrorText, std::u16string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowErrorText, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextContentType, TextContentType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextInputType, TextInputType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InputFilter, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowPasswordText, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowPasswordIcon, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCounter, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowUnderline, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, DisplayMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MaxViewLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NormalMaxViewLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MinLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsDisabled, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextOverflowMaxLines, uint32_t, PROPERTY_UPDATE_MEASURE);
    
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextContentTypeChanged, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(WidthAuto, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TypeChanged, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TextAlignChanged, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CopyOptions, CopyOptions, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreferredNewLineHeightNeedToUpdate, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreferredTextLineHeightNeedToUpdate, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PreferredPlaceholderLineHeightNeedToUpdate, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LastValue, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(NeedFireOnChange, bool, PROPERTY_UPDATE_NORMAL);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowPasswordSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HidePasswordSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectionMenuHidden, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PasswordRules, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableAutoFill, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableAutoFillAnimation, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SelectAllValue, bool, PROPERTY_UPDATE_NORMAL);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CleanNodeStyle, CleanNodeStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconSize, CalcDimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconSrc, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BundleName, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ModuleName, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IconColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowSymbol, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowCancelButton, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SetCounter, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowHighlightBorder, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StopBackPress, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EnableAutoSpacing, bool, PROPERTY_UPDATE_MEASURE);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<TextFieldLayoutProperty>(property);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propFontStyle_ = CloneFontStyle();
        value->propTextLineStyle_ = CloneTextLineStyle();
        value->propValue_ = CloneValue();
        value->propPlaceholderFontStyle_ = ClonePlaceholderFontStyle();
        value->propPlaceholderTextLineStyle_ = ClonePlaceholderTextLineStyle();
        value->propPlaceholder_ = ClonePlaceholder();
        value->propTextInputType_ = CloneTextInputType();
        value->propInputFilter_ = CloneInputFilter();
        value->propShowPasswordIcon_ = CloneShowPasswordIcon();
        value->propCopyOptions_ = CloneCopyOptions();
        value->propLastValue_ = CloneLastValue();
        value->propNeedFireOnChange_ = CloneNeedFireOnChange();
        value->propWidthAuto_ = CloneWidthAuto();
        value->propErrorText_ = CloneErrorText();
        value->propShowErrorText_ = CloneShowErrorText();
        value->propShowCounter_ = CloneShowCounter();
        value->propShowUnderline_ = CloneShowUnderline();
        value->propShowPasswordSourceInfo_ = CloneShowPasswordSourceInfo();
        value->propHidePasswordSourceInfo_ = CloneHidePasswordSourceInfo();
        value->propTextAlignChanged_ = CloneTextAlignChanged();
        value->propDisplayMode_ = CloneDisplayMode();
        value->propMaxViewLines_ = CloneMaxViewLines();
        value->propIsDisabled_ = CloneIsDisabled();
        value->propSelectionMenuHidden_ = CloneSelectionMenuHidden();
        value->propPasswordRules_ = ClonePasswordRules();
        value->propEnableAutoFill_ = CloneEnableAutoFill();
        value->propEnableAutoFillAnimation_ = CloneEnableAutoFillAnimation();
        value->propShowPasswordText_ = CloneShowPasswordText();
        value->propCleanNodeStyle_ = CloneCleanNodeStyle();
        value->propIconSize_ = CloneIconSize();
        value->propIconSrc_ =  CloneIconSrc();
        value->propIconColor_ = CloneIconColor();
        value->propIsShowSymbol_ = CloneIsShowSymbol();
        value->propSelectAllValue_ = CloneSelectAllValue();
        value->propSetCounter_ = CloneSetCounter();
        value->propShowHighlightBorder_ = CloneShowHighlightBorder();
        value->propBundleName_ = CloneBundleName();
        value->propModuleName_ = CloneModuleName();
        value->propStopBackPress_ = CloneStopBackPress();
        value->propEnableAutoSpacing_ = CloneEnableAutoSpacing();
    }

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldLayoutProperty);

private:
    std::function<void(WeakPtr<NG::FrameNode>)> cancelIconSymbol_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_LAYOUT_PROPERTY_H