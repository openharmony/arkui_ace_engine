/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H

#include "core/components/common/layout/constants.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextPickerModelNG : public TextPickerModel {
public:
    void Create(RefPtr<PickerTheme> pickerTheme, uint32_t columnKind) override;
    void SetSelected(uint32_t value) override;
    void SetRange(const std::vector<NG::RangeContent>& value) override;
    void SetValue(const std::string& value) override;
    void SetOnChange(TextChangeEvent&& onChange) override;
    void SetDefaultPickerItemHeight(const Dimension& value) override;
    void SetDefaultAttributes(const RefPtr<PickerTheme>& pickerTheme) override;
    void SetDisappearTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
    void SetNormalTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
    void SetSelectedTextStyle(const RefPtr<PickerTheme>& pickerTheme, const NG::PickerTextStyle& value) override;
private:
    static RefPtr<FrameNode> CreateStackNode();
    static RefPtr<FrameNode> CreateButtonNode();
    RefPtr<FrameNode> CreateColumnNode(uint32_t columnKind, uint32_t showCount);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_MODEL_NG_H