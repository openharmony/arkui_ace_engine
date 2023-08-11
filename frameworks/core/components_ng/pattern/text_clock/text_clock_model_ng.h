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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_clock/text_clock_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextClockModelNG : public OHOS::Ace::TextClockModel {
public:
    RefPtr<TextClockController> Create() override;
    void SetFormat(const std::string& format) override;
    void SetHoursWest(const int32_t& hoursWest) override;
    void SetOnDateChange(std::function<void(const std::string)>&& onChange) override;
    void SetFontSize(const Dimension& value) override;
    void SetTextColor(const Color& value) override;
    void SetItalicFontStyle(Ace::FontStyle value) override;
    void SetFontWeight(FontWeight value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_NG_H
