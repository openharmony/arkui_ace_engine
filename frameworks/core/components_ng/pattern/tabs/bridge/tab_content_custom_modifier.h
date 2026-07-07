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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TAB_CONTENT_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TAB_CONTENT_CUSTOM_MODIFIER_H

#include "core/interfaces/arkoala/arkoala_api.h"

struct ArkUITabContentCustomModifier {
    ArkUINodeHandle (*createFrameNode)(ArkUI_Int32 nodeId);
    void (*setShallowBuilder)(ArkUINodeHandle node, void* shallowBuilder);
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_BRIDGE_TAB_CONTENT_CUSTOM_MODIFIER_H
