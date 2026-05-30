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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_TYPES_H

#include <functional>
#include <vector>

#include "core/components_ng/pattern/picker_utils/dialog_event_types.h"

namespace OHOS::Ace::NG {

using TextChangeEvent = std::function<void(const std::vector<std::string>&, const std::vector<double>&)>;
using TextValueChangeEvent = std::function<void(const std::vector<std::string>&)>;
using TextSelectedChangeEvent = std::function<void(const std::vector<double>&)>;
using DialogTextEvent = DialogEvent;

struct TextPickerInteractiveEvent {
    DialogCancelEvent cancelEvent;
    DialogTextEvent acceptEvent;
    DialogTextEvent changeEvent;
    DialogTextEvent scrollStopEvent;
    DialogTextEvent enterSelectedAreaEvent;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_PICKER_TEXT_PICKER_EVENT_TYPES_H
