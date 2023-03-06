/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H

#include <functional>
#include "base/geometry/dimension.h"
#include "core/components/picker/picker_theme.h"

namespace OHOS::Ace {
using TextChangeEvent = std::function<void(const std::string&, double)>;
class TextPickerModel {
public:
    static TextPickerModel* GetInstance();
    virtual ~TextPickerModel() = default;

    virtual void Create(RefPtr<PickerTheme> pickerTheme) =0;
    virtual void SetSelected(uint32_t value) = 0;
    virtual void SetRange(const std::vector<std::string>& value) = 0;
    virtual void SetValue(const std::string& value) = 0;
    virtual void SetOnChange(TextChangeEvent&& onChange) = 0;
    virtual void SetDefaultPickerItemHeight(const Dimension& value) = 0;
private:
    static std::unique_ptr<TextPickerModel> textPickerInstance_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_PICKER_TEXT_PICKER_MODEL_H
