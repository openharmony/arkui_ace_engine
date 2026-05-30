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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_UTILS_DIALOG_EVENT_TYPES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_UTILS_DIALOG_EVENT_TYPES_H

#include <functional>
#include <string>

namespace OHOS::Ace {
class GestureEvent;
}

namespace OHOS::Ace::NG {

using DialogEvent = std::function<void(const std::string&)>;
using SelectedChangeEvent = DialogEvent;
using DialogCancelEvent = std::function<void()>;
using DialogGestureEvent = std::function<void(const GestureEvent& info)>;

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_UTILS_DIALOG_EVENT_TYPES_H
