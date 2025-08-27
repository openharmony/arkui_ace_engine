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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H

#include <functional>
#include <string>

#include "interfaces/native/node/styled_string.h"

#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextModelNG : public TextModel {
public:
    void Create(const std::u16string& content) override;
    void Create(const std::string& content) override;
    void Create(const RefPtr<SpanStringBase>& spanString) override;
    void SetFont(const Font& value) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void ResetTextColor() override;
    void SetTextSelection(int32_t startIndex, int32_t endIndex) override;
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetTextCaretColor(const Color& value) override;
    void SetSelectedBackgroundColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetVariableFontWeight(int32_t value) override;
    void SetEnableVariableFontWeight(bool value) override;
    void SetMinFontScale(const float value) override;
    void SetMaxFontScale(const float value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextAlign(TextAlign value) override;
    void SetTextOverflow(TextOverflow value) override;
    void SetMaxLines(uint32_t value) override;
    void SetTextIndent(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetLineSpacing(const Dimension& value) override;
    void SetIsOnlyBetweenLines(bool isOnlyBetweenLines) override;
    void SetTextDecoration(TextDecoration value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextDecorationStyle(TextDecorationStyle value) override;
    void SetBaselineOffset(const Dimension& value) override;
    void SetWordBreak(WordBreak value) override;
    void SetLineBreakStrategy(LineBreakStrategy value) override;
    void SetTextSelectableMode(TextSelectableMode value) override;
    void SetEllipsisMode(EllipsisMode modal) override;
    void SetTextCase(TextCase value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetAdaptMinFontSize(const Dimension& value) override;
    void SetAdaptMaxFontSize(const Dimension& value) override;
    void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) override;
    void SetContentTransition(TextEffectStrategy value, TextFlipDirection direction, bool enableBlur) override;
    void ResetContentTransition() override;
    void SetTextDetectEnable(bool value) override;
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) override;
    void SetOnClick(std::function<void(BaseEventInfo* info)>&& click, double distanceThreshold) override;
    void ClearOnClick() override;
    void SetRemoteMessage(std::function<void()>&& event) override;
    void SetCopyOption(CopyOptions copyOption) override;
    void SetOnCopy(std::function<void(const std::u16string&)>&& func) override;
    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override;
    void BindSelectionMenu(TextSpanType& spanType, TextResponseType& responseType, std::function<void()>& buildFunc,
        SelectMenuParam& menuParam) override;
    void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) override;
    RefPtr<TextControllerBase> GetTextController() override;
    void SetClipEdge(bool clip) override;
    void SetFontFeature(const FONT_FEATURES_LIST& value) override;
    void SetMarqueeOptions(const TextMarqueeOptions& options) override;
    void SetOnMarqueeStateChange(std::function<void(int32_t)>&& func) override;
    void SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick,
        const NG::OnPrepareMenuCallback&& onPrepareMenuCallback) override;
    void SetResponseRegion(bool isUserSetResponseRegion) override;
    void SetHalfLeading(bool halfLeading) override;
    void SetEnableHapticFeedback(bool state) override;
    void SetEnableAutoSpacing(bool enabled) override;
    void SetLineThicknessScale(float value) override;
    void SetOptimizeTrailingSpace(bool trim) override;
    void SetGradientShaderStyle(NG::Gradient& gradient) override;
    void SetColorShaderStyle(const Color& value) override;
    void ResetGradientShaderStyle() override;
    void SetTextVerticalAlign(TextVerticalAlign verticalAlign) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, const std::u16string& content);
    static void InitText(FrameNode* frameNode, std::u16string& value);
    static void InitSpanStringController(FrameNode* frameNode, const RefPtr<SpanStringBase>& spanBase);
    static RefPtr<TextControllerBase> InitTextController(FrameNode* frameNode);
    static void SetFontWeight(FrameNode* frameNode, Ace::FontWeight value);
    static void SetVariableFontWeight(FrameNode* frameNode, int32_t value);
    static void SetEnableVariableFontWeight(FrameNode* frameNode, bool value);
    static void SetMinFontScale(FrameNode* frameNode, const float value);
    static void SetMaxFontScale(FrameNode* frameNode, const float value);
    static void SetItalicFontStyle(FrameNode* frameNode, Ace::FontStyle value);
    static void SetTextAlign(FrameNode* frameNode, Ace::TextAlign value);
    static void SetTextColor(FrameNode* frameNode, const Color& value);
    static void ResetTextColor(FrameNode* frameNode);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetLineHeight(FrameNode* frameNode, const Dimension& value);
    static void SetLineSpacing(FrameNode* frameNode, const Dimension& value, bool isOnlyBetweenLines);
    static void SetTextOverflow(FrameNode* frameNode, TextOverflow value);
    static void SetTextDecoration(FrameNode* frameNode, TextDecoration value);
    static void SetTextDecorationColor(FrameNode* frameNode, const Color& value);
    static void SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value);
    static void SetTextCase(FrameNode* frameNode, TextCase value);
    static void SetMaxLines(FrameNode* frameNode, uint32_t value);
    static void SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions copyOption);
    static void SetTextShadow(FrameNode* frameNode, const std::vector<Shadow>& value);
    static void SetHeightAdaptivePolicy(FrameNode* frameNode, TextHeightAdaptivePolicy value);
    static void SetTextIndent(FrameNode* frameNode, const Dimension& value);
    static void SetBaselineOffset(FrameNode* frameNode, const Dimension& value);
    static void SetLetterSpacing(FrameNode* frameNode, const Dimension& value);
    static void SetFont(FrameNode* frameNode, const Font& value);
    static void SetWordBreak(FrameNode* frameNode, WordBreak value);
    static void SetLineBreakStrategy(FrameNode* frameNode, LineBreakStrategy value);
    static void SetEllipsisMode(FrameNode* frameNode, EllipsisMode value);
    static void SetTextDetectEnable(FrameNode* frameNode, bool value);
    static void SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value);
    static void SetMarqueeOptions(FrameNode* frameNode, const TextMarqueeOptions& options);
    static void SetOnMarqueeStateChange(FrameNode* frameNode, std::function<void(int32_t)>&& func);
    static void SetTextDetectConfig(FrameNode* frameNode, const std::string& value);
    static void SetOnClick(FrameNode* frameNode, GestureEventFunc&& click);
    static void ClearOnClick(FrameNode* frameNode);
    static void SetResponseRegion(FrameNode* frameNode, std::vector<DimensionRect> regions);
    static void ClearResponseRegion(FrameNode* frameNode);
    static void SetOnDetectResultUpdate(FrameNode* frameNode, std::function<void(const std::string&)>&& onResult);
    static void SetCaretColor(FrameNode* frameNode, const Color& value);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value);
    static void SetTextContentWithStyledString(FrameNode* frameNode, ArkUI_StyledString* value);
    static std::vector<std::string> GetFontFamily(FrameNode* frameNode);
    static CopyOptions GetCopyOption(FrameNode* frameNode);
    static TextMarqueeOptions GetMarqueeOptions(FrameNode* frameNode);
    static TextHeightAdaptivePolicy GetHeightAdaptivePolicy(FrameNode* frameNode);
    static Dimension GetAdaptMinFontSize(FrameNode* frameNode);
    static Dimension GetAdaptMaxFontSize(FrameNode* frameNode);
    static Font GetFont(FrameNode* frameNode);
    static std::u16string GetContent(FrameNode* frameNode);
    static float GetLineHeight(FrameNode* frameNode);
    static float GetLineSpacing(FrameNode* frameNode);
    static TextDecoration GetDecoration(FrameNode* frameNode);
    static Color GetTextDecorationColor(FrameNode* frameNode);
    static TextDecorationStyle GetTextDecorationStyle(FrameNode* frameNode);
    static TextCase GetTextCase(FrameNode* frameNode);
    static Dimension GetLetterSpacing(FrameNode* frameNode);
    static uint32_t GetMaxLines(FrameNode* frameNode);
    static TextAlign GetTextAlign(FrameNode* frameNode);
    static TextOverflow GetTextOverflow(FrameNode* frameNode);
    static Dimension GetTextIndent(FrameNode* frameNode);

    static Dimension GetFontSize(FrameNode* frameNode);
    static Ace::FontWeight GetFontWeight(FrameNode* frameNode);
    static Ace::FontStyle GetItalicFontStyle(FrameNode* frameNode);
    static Color GetDefaultColor(int32_t themeScopeId);
    static Color GetFontColor(FrameNode* frameNode);
    static Dimension GetTextBaselineOffset(FrameNode* frameNode);
    static std::vector<Shadow> GetTextShadow(FrameNode* frameNode);
    static Ace::WordBreak GetWordBreak(FrameNode* frameNode);
    static EllipsisMode GetEllipsisMode(FrameNode* frameNode);
    static bool GetTextDetectEnable(FrameNode* frameNode);
    static std::string GetTextDetectConfig(FrameNode* frameNode);
    static FONT_FEATURES_LIST GetFontFeature(FrameNode* frameNode);
    static TextSelectableMode GetTextSelectableMode(FrameNode* frameNode);
    static Color GetCaretColor(FrameNode* frameNode);
    static void ResetCaretColor(FrameNode* frameNode);
    static Color GetSelectedBackgroundColor(FrameNode* frameNode);
    static void ResetSelectedBackgroundColor(FrameNode* frameNode);
    static LineBreakStrategy GetLineBreakStrategy(FrameNode* frameNode);
    static void SetTextSelection(FrameNode* frameNode, int32_t startIndex, int32_t endIndex);
    static void SetTextSelectableMode(FrameNode* frameNode, TextSelectableMode value);
    static void SetTextDetectConfig(FrameNode* frameNode, const TextDetectConfig& textDetectConfig);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetOnTextSelectionChange(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& func);
    static void OnCreateMenuCallbackUpdate(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback);
    static void OnMenuItemClickCallbackUpdate(
        FrameNode* frameNode, const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void OnPrepareMenuCallbackUpdate(
        FrameNode* frameNode, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback);
    static void SetHalfLeading(FrameNode* frameNode, bool halfLeading);
    static bool GetHalfLeading(FrameNode* frameNode);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool state);
    static size_t GetLineCount(FrameNode* frameNode);
    static void SetEnableAutoSpacing(FrameNode* frameNode, bool enabled);
    static bool GetEnableAutoSpacing(FrameNode* frameNode);
    static void SetLineThicknessScale(FrameNode* frameNode, float value);
    static void SetOptimizeTrailingSpace(FrameNode* frameNode, bool trim);
    static bool GetOptimizeTrailingSpace(FrameNode* frameNode);
    static void SetGradientStyle(FrameNode* frameNode, NG::Gradient& gradient);
    static void SetColorShaderStyle(FrameNode* frameNode, const Color& value);
    static NG::Gradient GetGradientStyle(FrameNode* frameNode);
    static void ResetTextGradient(FrameNode* frameNode);
    static void SetTextVerticalAlign(FrameNode* frameNode, TextVerticalAlign verticalAlign);
    static TextVerticalAlign GetTextVerticalAlign(FrameNode* frameNode);
    static void SetContentTransition(
        FrameNode* frameNode, TextEffectStrategy value, TextFlipDirection direction, bool enableBlur);
    static void ResetContentTransition(FrameNode* frameNode);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_VIEW_H
