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

#ifndef ARKUI_PERF_INTERFACES_H
#define ARKUI_PERF_INTERFACES_H

#include <cstdint>
#include <string>
#include "base/perfmonitor/perf_monitor.h"

namespace OHOS::Ace {

class PerfInterfaces {
public:
    static void SetScrollState(bool state);
    static void RecordInputEvent(PerfActionType type, PerfSourceType sourceType, int64_t time);
    static int64_t GetInputTime(const std::string& sceneId, PerfActionType type, const std::string& note);

    static void NotifyAppJankStatsBegin();
    static void NotifyAppJankStatsEnd();
    static void SetPageUrl(const std::string& pageUrl);
    static std::string GetPageUrl();
    static void SetPageName(const std::string& pageName);
    static std::string GetPageName();
    static void SetAppForeground(bool isShow);
    static void SetAppStartStatus();
    static bool IsScrollJank(const std::string& sceneId);

    static void Start(const std::string& sceneId, PerfActionType type, const std::string& note);
    static void End(const std::string& sceneId, bool isRsRender);
    static void StartCommercial(const std::string& sceneId, PerfActionType type, const std::string& note);
    static void EndCommercial(const std::string& sceneId, bool isRsRender);
    static void SetFrameTime(int64_t vsyncTime, int64_t duration, double jank, const std::string& windowName);

    static void ReportJankFrameApp(double jank, int32_t jankThreshold);
    static void ReportPageShowMsg(const std::string& pageUrl, const std::string& bundleName,
        const std::string& pageName);
};

} // namespace OHOS::Ace

#endif // ARKUI_PERF_INTERFACES_H
