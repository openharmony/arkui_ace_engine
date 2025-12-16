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

namespace OHOS {
namespace AAFwk {
    class Want;
}; // namespace AAFwk

namespace Ace {
struct HostWindowInfo {
    int32_t hostInstanceId;
    uint32_t focusWindowId = 0;
    uint32_t realHostWindowId = 0;
    std::shared_ptr<OHOS::AAFwk::Want> hostWantParams;
};

struct DynamicInitialConfig {
    int32_t hostInstanceId;
    int32_t workerId = -1;
    std::string hapPath;
    std::string abcPath;
    std::string entryPoint;
    std::vector<std::string> registerComponents;
    HostWindowInfo hostWindowInfo;
};

struct SystemForceSplitConfig {
    bool isRouter;
    std::string homePage;
    std::string configJsonStr;
};

struct AppForceSplitConfig {
    bool isRouter;
    std::string configJsonStr;
};

struct FrameMetrics {
    bool firstDrawFrame = false; // Indicates whether the first frame of the window.
    uint64_t vsyncTimestamp = 0; // Indicates the timestamp of the actual vaync for this frame. The value is expressed
                                 // in nanoseconds.
    uint64_t inputHandlingDuration =
        0; // Indicates the number of nanoseconds elapsed in the input handling stage of a frame.
    uint64_t layoutMeasureDuration =
        0; // Indicates the number of nanoseconds elapsed in the layout measure stage of a frame.
};

struct NavigateChangeInfo {
    std::string name; // the navigate page name
    bool isSplit; // Indicates page is split or not
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_CONFIG_H
