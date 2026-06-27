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

#ifndef ARC_SCROLL_BAR_CUSTOM_MODIFIER_H
#define ARC_SCROLL_BAR_CUSTOM_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class Pattern;
class FrameNode;

class ScrollBarOverlayModifier;
class ScrollBar;

struct ArkUIArcScrollBarCustomModifier {
    // Factory: create ArcScrollBarPattern instance
    RefPtr<Pattern> (*createArcScrollBarPattern)() = nullptr;
    // Proxy: create ArcScrollBar instance
    RefPtr<ScrollBar> (*createArcScrollBar)() = nullptr;
    // Proxy: create ArcScrollBarOverlayModifier, initialized from existing scrollBar
    RefPtr<ScrollBarOverlayModifier> (*createArcScrollBarOverlayModifier)(ScrollBar* existingBar) = nullptr;
    // Proxy: update arc-specific scroll bar overlay properties
    void (*updateArcScrollBarOverlay)(ScrollBarOverlayModifier* overlay, ScrollBar* bar, bool& result) = nullptr;
};
} // namespace OHOS::Ace::NG
#endif
