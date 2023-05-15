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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_DISTRIBUTE_UI_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_DISTRIBUTE_UI_H

#include <cstdint>
#include <functional>
#include <set>

#include "interfaces/inner_api/ace/serializeable_object.h"

#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {
class DistributeUI {
public:
    enum UpdateType : uint8_t {
        PAGE_UPDATE = 0,
        PAGE_CHANGE = 1,
    };

    enum StateMachine : uint8_t {
        INIT = 0,
        SOURCE_START = 1,
        SINK_START = 2,
        STOP = 3,
    };

    // for distribute UI source
    static SerializeableObjectArray DumpUITree();
    static void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate);
    static void UnSubscribeUpdate();
    static void ProcessSerializeableInputEvent(const SerializeableObjectArray& array);

    // for distribute UI sink
    static void RestoreUITree(const SerializeableObjectArray& array);
    static void UpdateUITree(const SerializeableObjectArray& array);
    static void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent);
    static void UnSubscribeInputEventProcess();

    // internal APIs for distribute UI source
    static void AddDeletedNode(int32_t nodeId);
    static void AddNewNode(int32_t nodeId);
    static void AddDirtyCustomNode(int32_t nodeId);
    static void AddDirtyRenderNode(int32_t nodeId);
    static void AddDirtyLayoutNode(int32_t nodeId);
    static void OnTreeUpdate();
    static void OnPageChanged(int32_t pageId);
    static int32_t GetCurrentPageId();

    // internal APIs for distribute UI sink
    static void BypassEvent(const TouchEvent& point, bool isSubPipe);
    static bool IsSinkMode();
    static void ApplyOneUpdate();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_INSPECTOR_DISTRIBUTE_UI_H
