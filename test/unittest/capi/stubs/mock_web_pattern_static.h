/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_WEB_PATTERN_STATIC_H
#define CAPI_STUBS_MOCK_WEB_PATTERN_STATIC_H

#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern_property.h"
#include "mock_web_pattern.h"

namespace OHOS::Ace::NG {
class WebPatternStatic : public WebPattern {
    DECLARE_ACE_TYPE(WebPatternStatic, WebPattern);
public:
    WebPatternStatic() = default;
    ~WebPatternStatic() = default;
    void SetWebSrcStatic(const std::string &webSrc);
    void SetPopup(bool popup);
    void SetParentNWebId(int32_t parentNWebId);
};
} // namespace OHOS::Ace::NG
#endif // CAPI_STUBS_MOCK_WEB_PATTERN_STATIC_H
