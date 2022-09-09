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

#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/text/text_view.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::LEFT,
    TextAlign::RIGHT, TextAlign::JUSTIFY };

}; // namespace

void JSText::SetWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
}

void JSText::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
}

void JSText::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    NG::TextView::SetFontSize(fontSize);
}

void JSText::SetFontWeight(const std::string& value)
{
    NG::TextView::SetFontWeight(ConvertStrToFontWeight(value));
}

void JSText::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }

    NG::TextView::SetTextColor(textColor);
}

void JSText::SetTextOverflow(const JSCallbackInfo& info)
{
    info.SetReturnValue(info.This());
}

void JSText::SetMaxLines(int32_t value) {}

void JSText::SetFontStyle(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
        LOGE("Text fontStyle(%{public}d) illegal value", value);
        return;
    }

    NG::TextView::SetItalicFontStyle(FONT_STYLES[value]);
}

void JSText::SetTextAlign(int32_t value) {}

void JSText::SetAlign(int32_t value) {}

void JSText::SetLineHeight(const JSCallbackInfo& info) {}

void JSText::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }

    NG::TextView::SetFontFamily(fontFamilies);
}

void JSText::SetMinFontSize(const JSCallbackInfo& info) {}

void JSText::SetMaxFontSize(const JSCallbackInfo& info) {}

void JSText::SetLetterSpacing(const JSCallbackInfo& info) {}

void JSText::SetTextCase(int32_t value) {}

void JSText::SetBaselineOffset(const JSCallbackInfo& info) {}

void JSText::SetDecoration(const JSCallbackInfo& info) {}

void JSText::JsOnClick(const JSCallbackInfo& info) {}

void JSText::JsRemoteMessage(const JSCallbackInfo& info)
{
    EventMarker remoteMessageEventId;
    JSInteractableView::JsRemoteMessage(info, remoteMessageEventId);
}

void JSText::Create(const JSCallbackInfo& info)
{
    std::string data;
    if (info.Length() > 0) {
        ParseJsString(info[0], data);
    }

    NG::TextView::Create(data);
}

RefPtr<TextComponentV2> JSText::GetComponent()
{
    return nullptr;
}

void JSText::SetCopyOption(const JSCallbackInfo& info) {}

void JSText::JsOnDragStart(const JSCallbackInfo& info) {}

void JSText::JsOnDragEnter(const JSCallbackInfo& info) {}

void JSText::JsOnDragMove(const JSCallbackInfo& info) {}

void JSText::JsOnDragLeave(const JSCallbackInfo& info) {}

void JSText::JsOnDrop(const JSCallbackInfo& info) {}

void JSText::JsFocusable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGE("The info is wrong, it is supposed to be an boolean");
        return;
    }
    JSInteractableView::SetFocusable(info[0]->IsBoolean());
    JSInteractableView::SetFocusNode(false);
}

} // namespace OHOS::Ace::Framework
