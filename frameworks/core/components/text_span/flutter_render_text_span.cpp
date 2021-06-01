/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/text_span/flutter_render_text_span.h"

#include "base/utils/string_utils.h"
#include "core/components/calendar/flutter_render_calendar.h"
#include "core/components/font/constants_converter.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderTextSpan::Create()
{
    return AceType::MakeRefPtr<FlutterRenderTextSpan>();
}

void FlutterRenderTextSpan::UpdateTextContent(txt::ParagraphBuilder& builder)
{
    if (!isShow_) {
        LOGD("the span is not show");
        return;
    }
    if (hasNewStyle_) {
        LOGD("test span has new style");
        txt::TextStyle style;
        Constants::ConvertTxtStyle(spanStyle_, context_, style);
        builder.PushStyle(style);
    }
    builder.AddText(StringUtils::Str8ToStr16(spanData_));
    for (const auto& child : GetChildren()) {
        auto flutterRenderTextSpan = AceType::DynamicCast<FlutterRenderTextSpan>(child);
        if (flutterRenderTextSpan) {
            flutterRenderTextSpan->UpdateTextContent(builder);
        }
    }
    if (hasNewStyle_) {
        builder.Pop();
    }
}

} // namespace OHOS::Ace