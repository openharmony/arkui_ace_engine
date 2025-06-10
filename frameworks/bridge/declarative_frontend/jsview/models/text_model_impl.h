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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H

#include <functional>
#include <string>

#include "core/components/common/properties/text_style.h"
#include "core/components/text/text_component_v2.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT TextModelImpl : public TextModel {
public:
    void Create(const std::string& content) override;
    void Create(const std::u16string& content) override;
    void Create(const RefPtr<SpanStringBase>& spanString) override {}
    void SetFont(const Font& value) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void ResetTextColor() override {};
    void SetTextShadow(const std::vector<Shadow>& value) override;
    void SetTextSelection(int32_t startIndex, int32_t endIndex) override {};
    void SetTextSelectableMode(TextSelectableMode value) override {};
    void SetTextCaretColor(const Color& value) override;
    void SetSelectedBackgroundColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetVariableFontWeight(int32_t value) override {};
    void SetEnableVariableFontWeight(bool value) override {};
    void SetMinFontScale(const float value) override;
    void SetMaxFontScale(const float value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetTextAlign(TextAlign value) override;
    void SetTextOverflow(TextOverflow value) override;
    void SetMaxLines(uint32_t value) override;
    void SetTextIndent(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetLineSpacing(const Dimension& value) override;
    void SetOptimizeTrailingSpace(bool trim) override;
    void SetIsOnlyBetweenLines(bool isOnlyBetweenLines) override;
    void SetGradientShaderStyle(NG::Gradient& gradient) override;
    void SetTextDecoration(TextDecoration value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextDecorationStyle(TextDecorationStyle value) override;
    void SetBaselineOffset(const Dimension& value) override;
    void SetTextCase(TextCase value) override;
    void SetWordBreak(WordBreak value) override {};
    void SetLineBreakStrategy(LineBreakStrategy value) override {};
    void SetLetterSpacing(const Dimension& value) override;
    void SetAdaptMinFontSize(const Dimension& value) override;
    void SetAdaptMaxFontSize(const Dimension& value) override;
    void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) override;
    void SetTextDetectEnable(bool value) override;
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) override;
    void OnSetHeight() override;
    void OnSetWidth() override;
    void OnSetAlign() override;
    void SetOnClick(std::function<void(BaseEventInfo*)>&& click, double distanceThreshold) override;
    void ClearOnClick() override {};
    void SetRemoteMessage(std::function<void()>&& event) override;
    void SetCopyOption(CopyOptions copyOption) override;
    void SetOnCopy(std::function<void(const std::u16string&)>&& func) override {};
    void SetEllipsisMode(EllipsisMode modal) override {};
    void SetClipEdge(bool clip) override {};
    void SetFontFeature(const std::list<std::pair<std::string, int32_t>>& value) override {};
    void SetMarqueeOptions(const NG::TextMarqueeOptions& options) override {};
    void SetOnMarqueeStateChange(std::function<void(int32_t)>&& func) override {};
    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override;
    void SetHalfLeading(bool halfLeading) override;
    void SetEnableHapticFeedback(bool state) override {};
    void SetEnableAutoSpacing(bool enabled) override {};
    void SetLineThicknessScale(float value) override {};
    void SetTextVerticalAlign(TextVerticalAlign verticalAlign) override {};

private:
    static RefPtr<TextComponentV2> GetComponent();
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_TEXT_MODEL_IMPL_H
