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

#ifndef FRAMEWORKS_COMPATIBLE_COMPONENTS_STEPPER_STEPPER_MODIFIER_API_H
#define FRAMEWORKS_COMPATIBLE_COMPONENTS_STEPPER_STEPPER_MODIFIER_API_H

#include <cstdint>

#include "ui/base/ace_type.h"

#ifdef __cplusplus
extern "C" {
#endif

namespace OHOS::Ace {
class Element;
class Component;

namespace Framework {
class DOMNode;
class JSLazyForEachComponent;
} // namespace Framework

namespace V2 {
class ElementProxyHost;
class ElementProxy;
} // namespace V2

struct ArkUIStepperItemComponentModifier {
    RefPtr<Component> (*createStepperItem)();
    RefPtr<Component> (*updateStepperItem)(const RefPtr<Component>& component);
};
} // namespace OHOS::Ace

#ifdef __cplusplus
};
#endif

#endif // FRAMEWORKS_COMPATIBLE_COMPONENTS_STEPPER_STEPPER_MODIFIER_API_H