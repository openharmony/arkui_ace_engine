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

#ifndef ARKUI_PERF_MONITOR_H
#define ARKUI_PERF_MONITOR_H

#include <mutex>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <memory>

#include "base/utils/macros.h"
#include "base/utils/aps_monitor.h"
#include "core/common/window_animation_config.h"

namespace OHOS::Ace {
constexpr int32_t US_TO_MS = 1000;
constexpr int32_t NS_TO_MS = 1000000;
constexpr int32_t NS_TO_S = 1000000000;

enum PerfActionType {
    UNKNOWN_ACTION = -1,
    LAST_DOWN = 0,
    LAST_UP = 1,
    FIRST_MOVE = 2
};

enum PerfSourceType {
    UNKNOWN_SOURCE = -1,
    PERF_TOUCH_EVENT = 0,
    PERF_MOUSE_EVENT = 1,
    PERF_TOUCH_PAD = 2,
    PERF_JOY_STICK = 3,
    PERF_KEY_EVENT = 4
};

std::string ParsePageUrl(const std::string& pagePath);

class ACE_FORCE_EXPORT PerfMonitor {
public:
    void Start(const std::string& sceneId, PerfActionType type, const std::string& note);
    void End(const std::string& sceneId, bool isRsRender);
    void StartCommercial(const std::string& sceneId, PerfActionType type, const std::string& note);
    void EndCommercial(const std::string& sceneId, bool isRsRender);
    void RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time);
    int64_t GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note);
    void SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName);
    void SetSubHealthInfo(const std::string& info, const std::string& reason, const int32_t duration);
    void ReportJankFrameApp(double jank);
    void SetPageUrl(const std::string& pageUrl);
    std::string GetPageUrl();
    void SetPageName(const std::string& pageName);
    std::string GetPageName();
    void SetAppForeground(bool isShow);
    void SetAppStartStatus();
    static PerfMonitor* GetPerfMonitor();
    static PerfMonitor* pMonitor;
    static std::once_flag initFlag;
    static void InitInstance();
    void SetApsMonitor(const std::shared_ptr<ApsMonitor>& apsMonitor);
    void ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
                           const std::string& pageName);
    void RecordWindowRectResize(OHOS::Ace::WindowSizeChangeReason reason,
                           const std::string& bundleName);
    void NotifyAppJankStatsBegin();
    void NotifyAppJankStatsEnd();
    void SetApplicationInfo();
    void ReportSurface(const uint64_t& uniqueId, const std::string& surfaceName, const std::string& componentName,
        const std::string& bundleName, const int32_t pid);
private:
    std::shared_ptr<ApsMonitor> apsMonitor_ = nullptr;
};
} // namespace OHOS::Ace
#endif // ARKUI_PERF_MONITOR_H
