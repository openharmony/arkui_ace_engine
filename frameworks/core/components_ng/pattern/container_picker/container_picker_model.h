/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_MODEL_H

#include <functional>
#include <memory>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_picker/container_picker_layout_property.h"

namespace OHOS::Ace::NG {

using ContainerPickerChangeEvent = std::function<void(const double&)>;

class ACE_EXPORT ContainerPickerModel {
public:
    static void Create();
    static void SetCanLoop(const bool isLoop);
    static void SetEnableHapticFeedback(const bool isEnableHapticFeedback);
    static void SetOnChange(ContainerPickerChangeEvent&& onChange);
    static void SetOnScrollStop(ContainerPickerChangeEvent&& onChange);
    static void SetIndicatorStyle(const PickerIndicatorStyle& style);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_PICKER_CONTAINER_PICKER_MODEL_H
