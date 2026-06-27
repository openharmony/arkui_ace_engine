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

#ifndef ARC_SCROLL_BAR_DYNAMIC_MODIFIER_H
#define ARC_SCROLL_BAR_DYNAMIC_MODIFIER_H

#include "core/components_ng/pattern/arc_scroll_bar/bridge/arc_scroll_bar_custom_modifier.h"

namespace OHOS::Ace::NG::NodeModifier {
// Table builder, defined in arc_scroll_bar_dynamic_modifier.cpp.
// Cross builds fetch it via dlopen; non-cross builds call it directly.
const ArkUIArcScrollBarCustomModifier* GetArcScrollBarCustomModifier();
} // namespace OHOS::Ace::NG::NodeModifier

#endif // ARC_SCROLL_BAR_DYNAMIC_MODIFIER_H
