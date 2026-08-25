/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_FOREGROUND_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_FOREGROUND_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class CounterForegroundModifier : public ForegroundModifier {
    DECLARE_ACE_TYPE(CounterForegroundModifier, ForegroundModifier);

public:
    explicit CounterForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~CounterForegroundModifier() override = default;

    void onDraw(DrawingContext& context) override = 0;

    void SetInnerBorderWidth(float value)
    {
        CHECK_NULL_VOID(innerBorderWidth_);
        innerBorderWidth_->Set(value);
    }

    void SetInnerBorderColor(Color value)
    {
        CHECK_NULL_VOID(innerBorderColor_);
        innerBorderColor_->Set(value);
    }

protected:
    float GetInnerBorderWidth() const
    {
        return innerBorderWidth_ ? innerBorderWidth_->Get() : 0.0f;
    }

    Color GetInnerBorderColor() const
    {
        return innerBorderColor_ ? innerBorderColor_->Get() : Color();
    }

    std::vector<RSPoint> MakeRRadius(const BorderRadiusProperty& border, float borderWidth) const;

    WeakPtr<Pattern> pattern_;
    RefPtr<PropertyColor> innerBorderColor_;
    RefPtr<PropertyFloat> innerBorderWidth_;

private:
    ACE_DISALLOW_COPY_AND_MOVE(CounterForegroundModifier);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_COMMON_TEXT_COUNTER_FOREGROUND_MODIFIER_H
