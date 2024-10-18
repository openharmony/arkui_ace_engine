/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_TRANSPARENT_NODE_DETECTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_TRANSPARENT_NODE_DETECTOR_H

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class TransparentNodeDetector {
public:
    static constexpr uint8_t MAX_DETECT_COUNT = 2;

    static TransparentNodeDetector& GetInstance();
    void PostCheckNodeTransparentTask(const RefPtr<FrameNode>& node, const std::string& pageUrl,
        uint8_t detectCount = MAX_DETECT_COUNT);
private:
    TransparentNodeDetector() = default;
    ~TransparentNodeDetector() = default;
    TransparentNodeDetector(const TransparentNodeDetector& instance) = delete;
    const TransparentNodeDetector& operator = (const TransparentNodeDetector& instance) = delete;

    void DumpNodeInfo(const RefPtr<FrameNode>& node, Window* window);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_TRANSPARENT_NODE_DETECTOR_H

