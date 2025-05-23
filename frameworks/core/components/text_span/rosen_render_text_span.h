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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SPAN_ROSEN_RENDER_TEXT_SPAN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SPAN_ROSEN_RENDER_TEXT_SPAN_H

#include "rosen_text/typography_create.h"

#include "core/components/text_span/render_text_span.h"
#include "core/gestures/gesture_type.h"

namespace OHOS::Ace {

class RosenRenderTextSpan final : public RenderTextSpan {
    DECLARE_ACE_TYPE(RosenRenderTextSpan, RenderTextSpan);

public:
    RosenRenderTextSpan() = default;
    ~RosenRenderTextSpan() override = default;

    // Called by parent to add text with style to builder.
    void UpdateText(Rosen::TypographyCreate& builder,
        std::map<int32_t, std::map<GestureType, EventMarker>>& touchRegions, std::string& textValue);

private:
    void UpdateTouchRegions(std::map<int32_t, std::map<GestureType, EventMarker>>& touchRegions);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SPAN_ROSEN_RENDER_TEXT_SPAN_H
