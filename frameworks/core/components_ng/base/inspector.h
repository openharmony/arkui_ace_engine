/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H

#include <string>

#include "base/utils/macros.h"
#include "bridge/common/utils/componentInfo.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT Inspector {
public:
    static RefPtr<FrameNode> GetFrameNodeByKey(const std::string& key);
    static std::string GetInspectorNodeByKey(const std::string& key);
    static bool SendEventByKey(const std::string& key, int action, const std::string& params);
    static void GetRectangleById(const std::string& key, Rectangle& rectangle);
    static std::string GetInspector(bool isLayoutInspector = false);
    static void HideAllMenus();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_INSPECTOR_INSPECTOR_H
