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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_HICHECKER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_HICHECKER_H

#include <string>

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_EXPORT AceChecker final {
public:
    static bool IsPerformanceCheckEnabled();

    static void NotifyCaution(const std::string& tag);

    static void InitPerformanceParameters();

    static void SetPerformanceCheckStatus(bool status, const std::string& message);

    static bool IsWebSocketCheckEnabled()
    {
        return isWebSocketCheckEnabled_;
    }

    static std::string GetCheckMessge()
    {
        return checkMessage_;
    }

    static int32_t GetPageNodes()
    {
        return pageNodes_;
    }

    static int32_t GetPageDepth()
    {
        return pageDepth_;
    }

    static int32_t GetNodeChildren()
    {
        return nodeChildren_;
    }

    static int32_t GetFunctionTimeout()
    {
        return functionTimeout_;
    }

    static int32_t GetVsyncTimeout()
    {
        return vsyncTimeout_;
    }

    static int32_t GetNodeTimeout()
    {
        return nodeTimeout_;
    }

    static int32_t GetForeachItems()
    {
        return foreachItems_;
    }

    static int32_t GetFlexLayouts()
    {
        return flexLayouts_;
    }

private:
    static int32_t pageNodes_;
    static int32_t pageDepth_;
    static int32_t nodeChildren_;
    static int32_t functionTimeout_;
    static int32_t vsyncTimeout_;
    static int32_t nodeTimeout_;
    static int32_t foreachItems_;
    static int32_t flexLayouts_;
    static std::string checkMessage_;
    static bool isPerformanceCheckEnabled_;
    static bool isWebSocketCheckEnabled_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_HICHECKER_H
