/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

namespace OHOS::Ace {

class LayoutInspector {
public:
    static void SupportInspector();
    static void SetlayoutInspectorStatus(int32_t containerId);
    static void GetInspectorTreeJsonStr(std::string& treeJsonStr, int32_t containerId);
    static void CreateLayoutInfo(int32_t containerId);
    static void SetCallback(int32_t instanceId);
    static void SetStatus(bool layoutInspectorStatus);
    static void GetSnapshotJson(int32_t containerId, std::unique_ptr<JsonValue>& message);

private:
    static bool layoutInspectorStatus_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_LAYOUT_INSPECTOR_H