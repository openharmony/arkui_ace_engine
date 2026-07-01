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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_BUTTON_MODIFIER_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_BUTTON_MODIFIER_H

#include "base/utils/macros.h"
#include "core/components_ng/pattern/button/bridge/button_custom_modifier.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
ACE_FORCE_EXPORT const ArkUIButtonModifier* GetButtonModifier();
ACE_FORCE_EXPORT const CJUIButtonModifier* GetCJUIButtonModifier();
ACE_FORCE_EXPORT const ArkUIButtonCustomModifier* GetButtonCustomModifier();
}

#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_BUTTON_MODIFIER_H