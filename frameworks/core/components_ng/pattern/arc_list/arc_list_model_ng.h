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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_MODEL_NG_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/event/crown_event.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT ArcListModelNG {
public:
    static void SetHeader(FrameNode* frameNode, FrameNode* headerNode);
    static RefPtr<FrameNode> GetHeader(FrameNode* frameNode);
    static void ResetHeader(FrameNode* frameNode);
#ifdef SUPPORT_DIGITAL_CROWN
    static void SetDigitalCrownSensitivity(FrameNode* frameNode, CrownSensitivity sensitivity);
    static CrownSensitivity GetDigitalCrownSensitivity(FrameNode* frameNode);
    static void ResetDigitalCrownSensitivity(FrameNode* frameNode);
#endif
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_MODEL_NG_H
