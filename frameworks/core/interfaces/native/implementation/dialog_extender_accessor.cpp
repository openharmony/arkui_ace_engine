/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/interfaces/native/implementation/date_picker_dialog_extender.h"
#include "frameworks/core/interfaces/native/implementation/text_picker_dialog_extender.h"
#include "frameworks/core/interfaces/native/implementation/time_picker_dialog_extender.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DialogExtenderAccessor {
void ShowTimePickerDialogImpl(const Ark_TimePickerDialogOptions* options)
{
    TimePickerDialogExtender::Show(options);
}
void ShowTextPickerDialogImpl(const Ark_Union_TextPickerDialogOptions_TextPickerDialogOptionsExt* options)
{
    TextPickerDialogExtender::Show(options);
}
void ShowDatePickerDialogImpl(const Ark_DatePickerDialogOptions* options)
{
    DatePickerDialogExtender::Show(options);
}
} // namespace DialogExtenderAccessor
const GENERATED_ArkUIDialogExtenderAccessor* GetDialogExtenderAccessor()
{
    static const GENERATED_ArkUIDialogExtenderAccessor DialogExtenderAccessorImpl {
        DialogExtenderAccessor::ShowTimePickerDialogImpl,
        DialogExtenderAccessor::ShowTextPickerDialogImpl,
        DialogExtenderAccessor::ShowDatePickerDialogImpl,
    };
    return &DialogExtenderAccessorImpl;
}
} // namespace OHOS::Ace::NG::GeneratedModifier