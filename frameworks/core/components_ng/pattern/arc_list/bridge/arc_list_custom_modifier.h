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

#ifndef ARC_LIST_CUSTOM_MODIFIER_H
#define ARC_LIST_CUSTOM_MODIFIER_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/event/crown_event.h"

namespace OHOS::Ace::NG {
class Pattern;
class FrameNode;

struct ArkUIArcListCustomModifier {
    RefPtr<Pattern> (*createArcListPattern)() = nullptr;
    void (*addHeader)(FrameNode* frameNode, FrameNode* header) = nullptr;
    RefPtr<FrameNode> (*getHeader)(FrameNode* frameNode) = nullptr;
    void (*resetHeader)(FrameNode* frameNode) = nullptr;
    void (*setDigitalCrownSensitivity)(FrameNode* frameNode, CrownSensitivity sensitivity) = nullptr;
    CrownSensitivity (*getDigitalCrownSensitivity)(FrameNode* frameNode) = nullptr;
};

struct ArkUIArcListItemCustomModifier {
    RefPtr<Pattern> (*createArcListItemPattern)(void* builder, int32_t style) = nullptr;
    void (*setAutoScale)(FrameNode* frameNode, bool autoScale) = nullptr;
    void (*resetAutoScale)(FrameNode* frameNode) = nullptr;
};
} // namespace OHOS::Ace::NG
#endif
