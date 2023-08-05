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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_NG_H

#include "core/components_ng/pattern/radio/radio_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RadioModelNG : public OHOS::Ace::RadioModel {
public:
    void Create(const std::optional<std::string>& value, const std::optional<std::string>& group) override;
    void SetChecked(bool isChecked) override;
    void SetOnChange(ChangeEvent&& onChange) override;
    void SetWidth(const Dimension& width) override;
    void SetHeight(const Dimension& height) override;
    void SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs) override;
    void SetCheckedBackgroundColor(const Color& color) override;
    void SetUncheckedBorderColor(const Color& color) override;
    void SetIndicatorColor(const Color& color) override;
    void SetOnChangeEvent(ChangeEvent&& onChangeEvent) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_MODEL_NG_H
