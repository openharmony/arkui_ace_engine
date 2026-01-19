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

#ifndef FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_H
#define FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_H

#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"

namespace OHOS::Ace::TabModifier {

const ArkUIInnerTabsModifier* GetTabsInnerModifier();
const ArkUIInnerTabBarModifier* GetTabBarInnerModifier();
const ArkUITabContentModifier* GetTabContentInnerModifier();
} // namespace OHOS::Ace::TabModifier

#endif // FRAMEWORKS_COMPATIBLE_COMPONENTS_TAB_BAR_MODIFIER_TAB_MODIFIER_H
