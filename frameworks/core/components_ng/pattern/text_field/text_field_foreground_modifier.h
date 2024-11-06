/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_FOREGROUND_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_FOREGROUND_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class TextFieldForegroundModifier : public ForegroundModifier {
    DECLARE_ACE_TYPE(TextFieldForegroundModifier, ForegroundModifier);

public:
    explicit TextFieldForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern);
    ~TextFieldForegroundModifier() override = default;

    void onDraw(DrawingContext& context) override;

    void SetInnerBorderWidth(float value)
    {
        CHECK_NULL_VOID(innerBorderWidth_);
        innerBorderWidth_->Set(value);
    }

private:
    std::vector<RSPoint> MakeRRadius(const BorderRadiusProperty& border, float borderWidth) const;
    WeakPtr<Pattern> pattern_;

    RefPtr<PropertyFloat> innerBorderWidth_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldForegroundModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_FOREGROUND_MODIFIER_H
