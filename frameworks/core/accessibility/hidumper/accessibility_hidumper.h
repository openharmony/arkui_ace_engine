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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_HIDUMPER_ACCESSIBILITY_HIDUMPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_HIDUMPER_ACCESSIBILITY_HIDUMPER_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Accessibility {
}

namespace OHOS::Ace {
class FrameNode;

enum class InjectActionType : uint32_t {
    UNDEFINED_ACTION = 0,
    NOTIFY_CHILD_ACTION = 1,
    SECURITY_CLICK_ACTION = 2,
};

enum class DumpMode {
    TREE,
    NODE,
    HANDLE_EVENT,
    HOVER_TEST,
    EVENT_TEST,
    INJECT_ACTION_TEST,
    EMBED_SEARCH_TEST,
    EMBED_HOVER_TEST,
    SET_CHECKLIST_TEST,
    GET_CHECKLIST_TEST,
    SPECIFIC_SEARCH_TEST,
};

struct DumpInfoArgument {
    bool useWindowId = false;
    DumpMode mode = DumpMode::TREE;
    bool isDumpSimplify = false;
    bool verbose = false;
    int64_t rootId = -1;
    int32_t pointX = 0;
    int32_t pointY = 0;
    int64_t nodeId = -1;
    int32_t action = 0;
    int32_t eventId = -1;
};

class AccessibilityHidumper {
public:
    static bool DumpProcessInjectActionParameters(
        const std::vector<std::string>& params,
        int64_t& nodeId,
        int32_t& result,
        InjectActionType& actionType);
};
} // OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_HIDUMPER_ACCESSIBILITY_HIDUMPER_H
