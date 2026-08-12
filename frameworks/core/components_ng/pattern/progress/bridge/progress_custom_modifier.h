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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_BRIDGE_PROGRESS_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_BRIDGE_PROGRESS_CUSTOM_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace {
class Color;
class Dimension;
namespace NG {
class FrameNode;
class ProgressConfiguration;
using ProgressMakeCallback = std::function<RefPtr<FrameNode>(const ProgressConfiguration&)>;

struct LinearIndicatorProgressConfig {
    Color color;
    Color backgroundColor;
    Dimension strokeWidth;
    Dimension strokeRadius;
    int32_t direction;
    bool isInitialCreate;
};
struct ArkUIProgressCustomModifier {
    RefPtr<FrameNode> (*createProgressNode)(int32_t nodeId);
    void (*updateProgressProperties)(const RefPtr<FrameNode>& targetNode,
        const LinearIndicatorProgressConfig& config);
    void (*setBackgroundColorToModelStatic)(FrameNode* frameNode, const std::optional<Color>& value);
    void (*setBuilderFuncToModelNG)(FrameNode* frameNode, ProgressMakeCallback&& makeFunc);
};
} // namespace NG
} // namespace OHOS::Ace;


#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PROGRESS_BRIDGE_PROGRESS_CUSTOM_MODIFIER_H
