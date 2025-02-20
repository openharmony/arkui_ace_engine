/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SYMBOL_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SYMBOL_CONSTANTS_H

#include <cstdint>

namespace OHOS::Ace {

enum class SymbolEffectType {
    NONE = 0,
    SCALE,
    HIERARCHICAL,
    APPEAR,
    DISAPPEAR,
    BOUNCE,
    PULSE,
    REPLACE,
};

enum class CommonSubType {
    DOWN = 0,
    UP,
};

enum class ScopeType {
    LAYER = 0,
    WHOLE,
};

enum class FillStyle {
    CUMULATIVE = 0,
    ITERATIVE,
};

enum class SymbolType {
    SYSTEM = 0,
    CUSTOM,
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H
