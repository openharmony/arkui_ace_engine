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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H

#include <mutex>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_clock/text_clock_controller.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT TextClockModel {
public:
    static TextClockModel* GetInstance();
    virtual ~TextClockModel() = default;

    virtual RefPtr<TextClockController> Create() = 0;
    virtual void SetFormat(const std::string& format) = 0;
    virtual void SetHoursWest(float hoursWest) = 0;
    virtual void SetOnDateChange(std::function<void(const std::string)>&& onChange) = 0;
    virtual void SetFontSize(const Dimension& value) = 0;
    virtual void SetTextColor(const Color& value) = 0;
    virtual void SetItalicFontStyle(Ace::FontStyle value) = 0;
    virtual void SetFontWeight(FontWeight value) = 0;
    virtual void SetFontFamily(const std::vector<std::string>& value) = 0;
    virtual void SetTextShadow(const std::vector<Shadow>& value) = 0;
    virtual void SetFontFeature(const std::list<std::pair<std::string, int32_t>>& value) = 0;
    virtual void InitFontDefault(const TextStyle& textStyle) = 0;
    virtual void SetDateTimeOptions(const ZeroPrefixType& hourType) {};
    
private:
    static std::unique_ptr<TextClockModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_CLOCK_MODEL_H
