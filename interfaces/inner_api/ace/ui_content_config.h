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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_CONFIG_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_CONFIG_H

#include <string>
#include <vector>

namespace OHOS::Ace {
struct HostWindowInfo {
    int32_t hostInstanceId;
    uint32_t focusWindowId = 0;
    uint32_t realHostWindowId = 0;
};

struct DynamicInitialConfig {
    int32_t hostInstanceId;
    std::string hapPath;
    std::string abcPath;
    std::string entryPoint;
    std::vector<std::string> registerComponents;
    HostWindowInfo hostWindowInfo;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_CONFIG_H
