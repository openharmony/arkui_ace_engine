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

#include "core/components/text_span/rosen_render_text_span.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph_builder.h"
#include "txt/paragraph_txt.h"
#endif

#include "core/components/font/constants_converter.h"

namespace OHOS::Ace {

#ifndef USE_GRAPHIC_TEXT_GINE
void RosenRenderTextSpan::UpdateText(txt::ParagraphBuilder& builder,
    std::map<int32_t, std::map<GestureType, EventMarker>>& touchRegions, std::string& textValue)
#else
void RosenRenderTextSpan::UpdateText(Rosen::TypographyCreate& builder,
    std::map<int32_t, std::map<GestureType, EventMarker>>& touchRegions, std::string& textValue)
#endif
{
    if (!spanComponent_) {
        return;
    }

    if (!spanComponent_->IsShow()) {
        return;
    }
    if (spanComponent_->HasNewStyle()) {
#ifndef USE_GRAPHIC_TEXT_GINE
        txt::TextStyle style;
#else
        Rosen::TextStyle style;
#endif
        Constants::ConvertTxtStyle(spanStyle_, context_, style);
        builder.PushStyle(style);
    }
    UpdateTouchRegions(touchRegions);
    auto displayText = spanComponent_->GetSpanData();
    StringUtils::TransformStrCase(displayText, (int32_t)spanStyle_.GetTextCase());
#ifndef USE_GRAPHIC_TEXT_GINE
    builder.AddText(StringUtils::Str8ToStr16(displayText));
#else
    builder.AppendText(StringUtils::Str8ToStr16(displayText));
#endif
    textValue.append(displayText);
    for (const auto& child : GetChildren()) {
        auto rosenRenderTextSpan = AceType::DynamicCast<RosenRenderTextSpan>(child);
        if (rosenRenderTextSpan) {
            rosenRenderTextSpan->UpdateText(builder, touchRegions, textValue);
        }
    }
    if (spanComponent_->HasNewStyle()) {
#ifndef USE_GRAPHIC_TEXT_GINE
        builder.Pop();
#else
        builder.PopStyle();
#endif
    }
}

void RosenRenderTextSpan::UpdateTouchRegions(std::map<int32_t, std::map<GestureType, EventMarker>>& touchRegions)
{
    auto spanData = StringUtils::Str8ToStr16(spanComponent_->GetSpanData());
    if (spanData.empty()) {
        return;
    }

    std::map<GestureType, EventMarker> markersMap;
    auto declaration = spanComponent_->GetDeclaration();
    if (declaration) {
        auto& gestureEvent = static_cast<CommonGestureEvent&>(declaration->GetEvent(EventTag::COMMON_GESTURE_EVENT));
        if (gestureEvent.IsValid()) {
            if (!gestureEvent.click.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::CLICK, gestureEvent.click.eventMarker);
            }
            if (!gestureEvent.longPress.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::LONG_PRESS, gestureEvent.longPress.eventMarker);
            }
        }

        auto& rawEvent = static_cast<CommonRawEvent&>(declaration->GetEvent(EventTag::COMMON_RAW_EVENT));
        if (rawEvent.IsValid()) {
            if (!rawEvent.touchStart.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::TOUCH_START, rawEvent.touchStart.eventMarker);
            }
            if (!rawEvent.touchMove.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::TOUCH_MOVE, rawEvent.touchMove.eventMarker);
            }
            if (!rawEvent.touchCancel.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::TOUCH_CANCEL, rawEvent.touchCancel.eventMarker);
            }
            if (!rawEvent.touchEnd.eventMarker.IsEmpty()) {
                markersMap.try_emplace(GestureType::TOUCH_END, rawEvent.touchEnd.eventMarker);
            }
        }
    }

    if (touchRegions.empty()) {
        touchRegions.try_emplace(int32_t(spanData.length()), markersMap);
    } else {
        touchRegions.try_emplace(int32_t(touchRegions.rbegin()->first + spanData.length()), markersMap);
    }
}
} // namespace OHOS::Ace
