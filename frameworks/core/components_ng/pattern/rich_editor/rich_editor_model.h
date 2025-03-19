/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H

#include <functional>
#include <mutex>
#include <optional>
#include <string>

#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/utils/device_config.h"
#include "core/common/ime/text_input_action.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/render/paragraph.h"
namespace OHOS::Ace {
struct SpanPositionInfo {
    SpanPositionInfo(int32_t index, int32_t start, int32_t end, int32_t offset)
        : spanIndex_(index), spanStart_(start), spanEnd_(end), spanOffset_(offset)
    {}

    SpanPositionInfo()
    {
        spanIndex_ = 0;
        spanStart_ = 0;
        spanEnd_ = 0;
        spanOffset_ = 0;
    }

    int32_t spanIndex_ = 0;
    int32_t spanStart_ = 0;
    int32_t spanEnd_ = 0;
    int32_t spanOffset_ = 0;

    std::string ToString() const
    {
        return "spanIndex: " + std::to_string(spanIndex_)
            + ", spanStart: " + std::to_string(spanStart_)
            + ", spanEnd" + std::to_string(spanEnd_)
            + ", spanOffset: " + std::to_string(spanOffset_);
    }
};

struct UpdateSpanStyle {
    void ResetStyle()
    {
        updateTextColor.reset();
        updateFontSize.reset();
        updateItalicFontStyle.reset();
        updateFontWeight.reset();
        updateFontFamily.reset();
        updateTextDecoration.reset();
        updateTextDecorationColor.reset();
        updateTextDecorationStyle.reset();
        updateTextShadows.reset();
        updateFontFeature.reset();
        updateTextBackgroundStyle.reset();
        updateUrlAddress.reset();

        updateLineHeight.reset();
        updateHalfLeading.reset();
        updateLetterSpacing.reset();

        updateImageWidth.reset();
        updateImageHeight.reset();
        updateImageVerticalAlign.reset();
        updateImageFit.reset();
        marginProp.reset();
        borderRadius.reset();
        isInitDecoration = false;

        updateSymbolColor.reset();
        updateSymbolFontSize.reset();
        updateSymbolFontWeight.reset();
        updateSymbolRenderingStrategy.reset();
        updateSymbolEffectStrategy.reset();
    }

    std::optional<Color> updateTextColor = std::nullopt;
    std::optional<CalcDimension> updateFontSize = std::nullopt;
    std::optional<FontStyle> updateItalicFontStyle = std::nullopt;
    std::optional<FontWeight> updateFontWeight = std::nullopt;
    std::optional<std::vector<std::string>> updateFontFamily = std::nullopt;
    std::optional<TextDecoration> updateTextDecoration = std::nullopt;
    std::optional<Color> updateTextDecorationColor = std::nullopt;
    std::optional<TextDecorationStyle> updateTextDecorationStyle = std::nullopt;
    std::optional<std::vector<Shadow>> updateTextShadows = std::nullopt;
    std::optional<NG::FONT_FEATURES_LIST> updateFontFeature = std::nullopt;
    std::optional<TextBackgroundStyle> updateTextBackgroundStyle = std::nullopt;
    std::optional<std::u16string> updateUrlAddress = std::nullopt;

    std::optional<CalcDimension> updateLineHeight = std::nullopt;
    std::optional<bool> updateHalfLeading = std::nullopt;
    std::optional<CalcDimension> updateLetterSpacing = std::nullopt;

    std::optional<CalcDimension> updateImageWidth = std::nullopt;
    std::optional<CalcDimension> updateImageHeight = std::nullopt;
    std::optional<VerticalAlign> updateImageVerticalAlign = std::nullopt;
    std::optional<ImageFit> updateImageFit = std::nullopt;
    std::optional<OHOS::Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<OHOS::Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    bool useThemeFontColor = true;
    bool useThemeDecorationColor = true;
    bool isInitDecoration = false;
    
    std::optional<std::vector<Color>> updateSymbolColor = std::nullopt;
    std::optional<CalcDimension> updateSymbolFontSize = std::nullopt;
    std::optional<FontWeight> updateSymbolFontWeight = std::nullopt;
    std::optional<uint32_t> updateSymbolRenderingStrategy = std::nullopt;
    std::optional<uint32_t> updateSymbolEffectStrategy = std::nullopt;

    void UpdateColorByResourceId()
    {
        if (updateTextColor) {
            updateTextColor->UpdateColorByResourceId();
        }
        if (updateTextDecorationColor) {
            updateTextDecorationColor->UpdateColorByResourceId();
        }
        if (updateTextShadows) {
            auto& shadows = updateTextShadows.value();
            std::for_each(shadows.begin(), shadows.end(), [](Shadow& sd) { sd.UpdateColorByResourceId(); });
        }
        if (updateSymbolColor) {
            auto& colors = updateSymbolColor.value();
            std::for_each(colors.begin(), colors.end(), [](Color& cl) { cl.UpdateColorByResourceId(); });
        }
        if (updateTextBackgroundStyle) {
            updateTextBackgroundStyle->UpdateColorByResourceId();
        }
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, updateTextColor);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, updateFontSize);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateItalicFontStyle);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateFontWeight);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateTextDecoration);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, updateTextDecorationColor);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateTextDecorationStyle);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateSymbolRenderingStrategy);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateSymbolEffectStrategy);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, updateImageWidth);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, updateImageHeight);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateImageVerticalAlign);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, updateImageFit);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, marginProp);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, borderRadius);
        JSON_STRING_PUT_BOOL(jsonValue, useThemeFontColor);
        JSON_STRING_PUT_BOOL(jsonValue, useThemeDecorationColor);
        return jsonValue->ToString();
    }
};

struct UpdateParagraphStyle {
    void Reset()
    {
        textAlign.reset();
        leadingMargin.reset();
        wordBreak.reset();
        lineBreakStrategy.reset();
        paragraphSpacing.reset();
    }
    std::optional<TextAlign> textAlign;
    std::optional<NG::LeadingMargin> leadingMargin;
    std::optional<WordBreak> wordBreak;
    std::optional<LineBreakStrategy> lineBreakStrategy;
    std::optional<Dimension> paragraphSpacing;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, textAlign);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, leadingMargin);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, wordBreak);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, lineBreakStrategy);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, paragraphSpacing);
        return jsonValue->ToString();
    }
};

struct RangeOptions {
    std::optional<int32_t> start;
    std::optional<int32_t> end;

    std::string ToString() const
    {
        return "["
            + (start ? std::to_string(*start) : "nullopt")
            + ","
            + (end ? std::to_string(*end) : "nullopt")
            + "]";
    }
};

struct TextSpanOptions : SpanOptionBase {
    std::optional<int32_t> offset;
    std::u16string value;
    std::optional<TextStyle> style;
    std::optional<UpdateParagraphStyle> paraStyle;
    std::optional<std::u16string> urlAddress;
    UserGestureOptions userGestureOption;
    bool useThemeFontColor = true;
    bool useThemeDecorationColor = true;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, offset);
        JSON_STRING_PUT_STRING(jsonValue, value);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, style);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, paraStyle);
        JSON_STRING_PUT_BOOL(jsonValue, useThemeFontColor);
        JSON_STRING_PUT_BOOL(jsonValue, useThemeDecorationColor);
        return jsonValue->ToString();
    }
};

struct SymbolSpanOptions : SpanOptionBase {
    std::optional<int32_t> offset;
    uint32_t symbolId;
    std::optional<TextStyle> style;
    RefPtr<ResourceObject> resourceObject;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, offset);
        JSON_STRING_PUT_INT(jsonValue, symbolId);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, style);
        return jsonValue->ToString();
    }
};

struct PlaceholderOptions {
    std::optional<std::u16string> value;
    std::optional<FontWeight> fontWeight;
    std::optional<Dimension> fontSize;
    std::optional<Color> fontColor;
    std::optional<FontStyle> fontStyle;
    std::vector<std::string> fontFamilies;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, value);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, fontWeight);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, fontSize);
        JSON_STRING_PUT_OPTIONAL_STRINGABLE(jsonValue, fontColor);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, fontStyle);
        return jsonValue->ToString();
    }
};

struct PreviewTextInfo {
    std::optional<std::u16string> value;
    std::optional<int32_t> offset;

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_OPTIONAL_STRING(jsonValue, value);
        JSON_STRING_PUT_OPTIONAL_INT(jsonValue, offset);
        return jsonValue->ToString();
    }
};

class ACE_EXPORT RichEditorBaseControllerBase : public AceType {
    DECLARE_ACE_TYPE(RichEditorBaseControllerBase, AceType);

public:
    virtual int32_t GetCaretOffset() = 0;
    virtual NG::RectF GetCaretRect() = 0;
    virtual bool SetCaretOffset(int32_t caretPosition) = 0;
    virtual void SetTypingStyle(std::optional<struct UpdateSpanStyle> typingStyle,
        std::optional<TextStyle> textStyle) = 0;
    virtual std::optional<struct UpdateSpanStyle> GetTypingStyle() = 0;
    virtual void CloseSelectionMenu() = 0;
    virtual bool IsEditing() = 0;
    virtual void StopEditing() = 0;
    virtual void SetSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options = std::nullopt, bool isForward = false) = 0;
    virtual WeakPtr<NG::LayoutInfoInterface> GetLayoutInfoInterface() = 0;
    virtual const PreviewTextInfo GetPreviewTextInfo() const = 0;
    virtual ColorMode GetColorMode() = 0;
    virtual RefPtr<NG::RichEditorTheme> GetTheme() = 0;
};

class ACE_EXPORT RichEditorControllerBase : virtual public RichEditorBaseControllerBase {
    DECLARE_ACE_TYPE(RichEditorControllerBase, RichEditorBaseControllerBase);

public:
    virtual int32_t AddImageSpan(const ImageSpanOptions& options) = 0;
    virtual int32_t AddTextSpan(const TextSpanOptions& options) = 0;
    virtual int32_t AddSymbolSpan(const SymbolSpanOptions& options) = 0;
    virtual int32_t AddPlaceholderSpan(const RefPtr<NG::UINode>& customNode, const SpanOptionBase& options) = 0;
    virtual void UpdateParagraphStyle(int32_t start, int32_t end, const UpdateParagraphStyle& style) = 0;
    virtual void UpdateSpanStyle(
        int32_t start, int32_t end, TextStyle textStyle, ImageSpanAttribute imageStyle) = 0;
    virtual void SetUpdateSpanStyle(struct UpdateSpanStyle updateSpanStyle) = 0;
    virtual SelectionInfo GetSpansInfo(int32_t start, int32_t end) = 0;
    virtual std::vector<ParagraphInfo> GetParagraphsInfo(int32_t start, int32_t end) = 0;
    virtual void DeleteSpans(const RangeOptions& options) = 0;
    virtual SelectionInfo GetSelectionSpansInfo() = 0;
    virtual RefPtr<SpanStringBase> ToStyledString(int32_t start, int32_t end) = 0;
    virtual SelectionInfo FromStyledString(RefPtr<SpanStringBase> value) = 0;
};

class ACE_EXPORT RichEditorStyledStringControllerBase : virtual public RichEditorBaseControllerBase {
    DECLARE_ACE_TYPE(RichEditorStyledStringControllerBase, RichEditorBaseControllerBase);

public:
    virtual void SetStyledString(const RefPtr<SpanStringBase>& value) = 0;
    virtual RefPtr<SpanStringBase> GetStyledString() = 0;
    virtual SelectionRangeInfo GetSelection() = 0;
    virtual void SetOnWillChange(std::function<bool(const NG::StyledStringChangeValue&)> && func) = 0;
    virtual void SetOnDidChange(std::function<void(const NG::StyledStringChangeValue&)> && func) = 0;
};

class ACE_FORCE_EXPORT RichEditorModel {
public:
    static RichEditorModel* GetInstance();
    virtual ~RichEditorModel() = default;
    virtual void Create(bool isStyledStringMode = false) = 0;
    virtual RefPtr<RichEditorBaseControllerBase> GetRichEditorController() = 0;
    virtual void SetOnReady(std::function<void()>&& func) = 0;
    virtual void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) = 0;
    virtual void SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func) = 0;
    virtual void SetAboutToIMEInput(std::function<bool(const NG::RichEditorInsertValue&)>&& func) = 0;
    virtual void SetOnIMEInputComplete(std::function<void(const NG::RichEditorAbstractSpanResult&)>&& func) = 0;
    virtual void SetOnDidIMEInput(std::function<void(const TextRange&)>&& func) = 0;
    virtual void SetAboutToDelete(std::function<bool(const NG::RichEditorDeleteValue&)>&& func) = 0;
    virtual void SetOnDeleteComplete(std::function<void()>&& func) = 0;
    virtual void SetCustomKeyboard(std::function<void()>&& func, bool supportAvoidance = false) = 0;
    virtual void SetCopyOption(CopyOptions& copyOptions) = 0;
    virtual void BindSelectionMenu(NG::TextSpanType& editorType, NG::TextResponseType& responseType,
        std::function<void()>& buildFunc, NG::SelectMenuParam& menuParam) = 0;
    virtual void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) = 0;
    virtual void SetPlaceholder(PlaceholderOptions& options) = 0;
    virtual void SetTextDetectEnable(bool value) = 0;
    virtual void SetSupportPreviewText(bool value) = 0;
    virtual void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) = 0;
    virtual void SetSelectedBackgroundColor(const Color& selectedColor) = 0;
    virtual void SetCaretColor(const Color& color) = 0;
    virtual void SetOnEditingChange(std::function<void(const bool&)>&& func) = 0;
    virtual void SetEnterKeyType(TextInputAction value) = 0;
    virtual void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) = 0;
    virtual void SetOnWillChange(std::function<bool(const NG::RichEditorChangeValue&)>&& func) = 0;
    virtual void SetOnDidChange(std::function<void(const NG::RichEditorChangeValue&)>&& func) = 0;
    virtual void SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func) = 0;
    virtual void SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func) = 0;
    virtual void SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func) = 0;
    virtual void SetSelectionMenuOptions(
        const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick) {}
    virtual void SetRequestKeyboardOnFocus(bool needToRequest) {}
    virtual void SetEnableHapticFeedback(bool isEnabled) {}
    virtual void SetBarState(DisplayMode mode) {}
    virtual void SetPreviewMenuParam(NG::TextSpanType spanType, std::function<void()>& buildFunc,
        const NG::SelectMenuParam& menuParam) {}
    virtual void SetMaxLength(std::optional<int32_t> value) {}
    virtual void ResetMaxLength() {}
    virtual void SetMaxLines(uint32_t value) {};
    virtual void SetStopBackPress(bool isStopBackPress) {};
    virtual void SetKeyboardAppearance(KeyboardAppearance value) {};

private:
    static std::unique_ptr<RichEditorModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H
