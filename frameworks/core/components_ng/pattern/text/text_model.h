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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components/box/drag_drop_event.h"
#include "core/components/common/properties/color.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_menu_extension.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"
#include "core/components_ng/pattern/text_field/text_selector.h"

namespace OHOS::Ace {
struct TextDetectConfig {
    std::string types;
    std::function<void(const std::string&)> onResult;
    Color entityColor;
    TextDecoration entityDecorationType = TextDecoration::UNDERLINE;
    Color entityDecorationColor;
    TextDecorationStyle entityDecorationStyle = TextDecorationStyle::SOLID;

    TextDetectConfig()
    {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto hyperlinkTheme = pipeline->GetTheme<HyperlinkTheme>();
        CHECK_NULL_VOID(hyperlinkTheme);
        entityColor = hyperlinkTheme->GetTextColor();
        entityDecorationType = TextDecoration::UNDERLINE;
        entityDecorationColor = entityColor;
        entityDecorationStyle = TextDecorationStyle::SOLID;
    }
    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        jsonValue->Put("types", types.c_str());
        jsonValue->Put("color", entityColor.ToString().c_str());
        auto decorationJson = JsonUtil::Create(true);
        decorationJson->Put("type", static_cast<int64_t>(entityDecorationType));
        decorationJson->Put("color", entityDecorationColor.ToString().c_str());
        decorationJson->Put("style", static_cast<int64_t>(entityDecorationStyle));
        jsonValue->Put("decoration", decorationJson);
        return jsonValue->ToString();
    }
};

class ACE_EXPORT SpanStringBase : public AceType {
    DECLARE_ACE_TYPE(SpanStringBase, AceType);
};
class ACE_EXPORT TextControllerBase : public AceType {
    DECLARE_ACE_TYPE(TextControllerBase, AceType);

public:
    virtual void CloseSelectionMenu() = 0;
    virtual void SetStyledString(const RefPtr<SpanStringBase>& value, bool closeSelectOverlay) = 0;
    virtual WeakPtr<NG::LayoutInfoInterface> GetLayoutInfoInterface() = 0;
};

class ACE_FORCE_EXPORT TextModel {
public:
    static TextModel* GetInstance();
    virtual ~TextModel() = default;

    virtual void Create(const std::u16string& content) {};
    virtual void Create(const std::string& content) {};
    virtual void Create(const RefPtr<SpanStringBase>& spanString) = 0;
    virtual void SetFont(const Font& value) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void ResetTextColor() = 0;
    virtual void SetTextShadow(const std::vector<Shadow>& value) = 0;
    virtual void SetItalicFontStyle(Ace::FontStyle value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetVariableFontWeight(int32_t value) = 0;
    virtual void SetEnableVariableFontWeight(bool value) = 0;
    virtual void SetMinFontScale(const float value) = 0;
    virtual void SetMaxFontScale(const float value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetWordBreak(WordBreak wordBreak) = 0;
    virtual void SetLineBreakStrategy(LineBreakStrategy lineBreakStrategy) = 0;
    virtual void SetTextAlign(TextAlign value) = 0;
    virtual void SetTextOverflow(TextOverflow value) = 0;
    virtual void SetMaxLines(uint32_t value) = 0;
    virtual void SetTextIndent(const Dimension& value) = 0;
    virtual void SetLineHeight(const Dimension& value) = 0;
    virtual void SetLineSpacing(const Dimension& value) = 0;
    virtual void SetIsOnlyBetweenLines(bool isOnlyBetweenLines) = 0;
    virtual void SetTextDecoration(TextDecoration value) = 0;
    virtual void SetTextDecorationColor(const Color& value) = 0;
    virtual void SetTextDecorationStyle(TextDecorationStyle value) = 0;
    virtual void SetBaselineOffset(const Dimension& value) = 0;
    virtual void SetTextCase(TextCase value) = 0;
    virtual void SetLetterSpacing(const Dimension& value) = 0;
    virtual void SetAdaptMinFontSize(const Dimension& value) = 0;
    virtual void SetAdaptMaxFontSize(const Dimension& value) = 0;
    virtual void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) = 0;
    virtual void SetTextDetectEnable(bool value) = 0;
    virtual void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) = 0;
    virtual void OnSetWidth() {};
    virtual void OnSetHeight() {};
    virtual void OnSetAlign() {};
    virtual void SetOnClick(std::function<void(BaseEventInfo* info)>&& click, double distanceThreshold) = 0;
    virtual void ClearOnClick() = 0;
    virtual void SetRemoteMessage(std::function<void()>&& click) = 0;
    virtual void SetCopyOption(CopyOptions copyOption) = 0;
    virtual void SetOnCopy(std::function<void(const std::u16string&)>&& func) = 0;
    virtual void SetEllipsisMode(EllipsisMode modal) = 0;

    virtual void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) = 0;
    virtual void SetTextSelection(int32_t startIndex, int32_t endIndex) = 0;
    virtual void SetTextSelectableMode(TextSelectableMode textSelectable) = 0;
    virtual void SetTextCaretColor(const Color& value) = 0;
    virtual void SetSelectedBackgroundColor(const Color& value) = 0;
    virtual void BindSelectionMenu(NG::TextSpanType& spanType, NG::TextResponseType& responseType,
        std::function<void()>& buildFunc, NG::SelectMenuParam& menuParam) {};
    virtual void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) {};
    virtual RefPtr<TextControllerBase> GetTextController()
    {
        return nullptr;
    };
    virtual void SetClipEdge(bool clip) = 0;
    virtual void SetFontFeature(const std::list<std::pair<std::string, int32_t>>& value) = 0;
    virtual void SetMarqueeOptions(const NG::TextMarqueeOptions& options) = 0;
    virtual void SetOnMarqueeStateChange(std::function<void(int32_t)>&& func) = 0;
    virtual void SetSelectionMenuOptions(
        const NG::OnCreateMenuCallback&& onCreateMenuCallback, const NG::OnMenuItemClickCallback&& onMenuItemClick) {};
    virtual void SetResponseRegion(bool isUserSetResponseRegion) {};
    virtual void SetHalfLeading(bool halfLeading) = 0;
    virtual void SetEnableHapticFeedback(bool state) = 0;

private:
    static std::unique_ptr<TextModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_TEXT_MODEL_H
