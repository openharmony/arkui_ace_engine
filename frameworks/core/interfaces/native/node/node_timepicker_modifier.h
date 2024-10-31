/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TIME_PICKER_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TIME_PICKER_MODIFIER_H

#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUITimepickerModifier* GetTimepickerModifier();
const CJUITimepickerModifier* GetCJUITimepickerModifier();
void SetTimePickerOnChange(ArkUINodeHandle node, void* extraParam);
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TIME_PICKER_MODIFIER_H
