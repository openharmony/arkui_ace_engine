/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LAYOUT_INSPECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LAYOUT_INSPECTOR_H

#include "core/common/container.h"
#include "core/components_ng/base/inspector.h"

namespace OHOS::Ace {
typedef struct {
    uint64_t rsNodeId = 0;
    int32_t frameNodeId = 0;
    std::string nodeType;
    std::string debugline;
    int32_t parentNodeId = -1;
} FrameNodeInfo;

typedef std::function<void(bool)> ProfilerStatusCallback;
typedef std::function<void(FrameNodeInfo)> RsProfilerNodeMountCallback;

class LayoutInspector {
public:
    static void SupportInspector();
    static void SetlayoutInspectorStatus(int32_t containerId);
    static void GetInspectorTreeJsonStr(std::string& treeJsonStr, int32_t containerId);
    static void CreateLayoutInfo(int32_t containerId);
    static void CreateContainerLayoutInfo(RefPtr<Container>& container);
    static void CreateLayoutInfoByWinId(uint32_t windId);
    static void SetCallback(int32_t instanceId);
    static void SetStatus(bool layoutInspectorStatus);
    static void GetSnapshotJson(int32_t containerId, std::unique_ptr<JsonValue>& message);
    static void RegisterConnectCallback();
    static void ProcessMessages(const std::string& message);

    // state profiler
    static bool GetStateProfilerStatus();
    static void SetStateProfilerStatus(bool status);
    static void TriggerJsStateProfilerStatusCallback(bool status);
    static void SendMessage(const std::string& message);
    static void SetJsStateProfilerStatusCallback(ProfilerStatusCallback&& callback);

    // rs profiler
    static RsProfilerNodeMountCallback GetRsProfilerNodeMountCallback();
    static void SetRsProfilerNodeMountCallback(RsProfilerNodeMountCallback&& callback);
    static void HandleStartRecord();
    static void HandleStopRecord();
    static void HandleInnerCallback(FrameNodeInfo node);
    static void ConnectServerCallback();
    using SetArkUICallback = void (*)(const std::function<void(const char*)>& arkuiCallback);

private:
    static bool stateProfilerStatus_;
    static bool layoutInspectorStatus_;
    static NG::InspectorTreeMap recNodeInfos_;
    static std::mutex recMutex_;
    static ProfilerStatusCallback jsStateProfilerStatusCallback_;
    static RsProfilerNodeMountCallback rsProfilerNodeMountCallback_;
    static bool isUseStageModel_;
    static std::once_flag loadFlag;
    static void* handlerConnectServerSo;
    static SetArkUICallback setArkUICallback;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LAYOUT_INSPECTOR_H