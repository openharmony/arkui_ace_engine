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

#include "reporter_impl.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/manager/event/json_child_report.h"
#include "frameworks/core/components_ng/manager/event/json_report.h"
namespace OHOS::Ace::NG {
Reporter& Reporter::GetInstance()
{
    static ReporterImpl singleInstance;
    return singleInstance;
}

void ReporterImpl::HandleUISessionReporting(const JsonReport& report) const
{
    auto value = report.GetJsonData();
    if (value->IsNull()) {
        return;
    }
    LOGD("UISession JsonString %{public}s", value->ToString().c_str());
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(report.GetId(), "event", value);
}
} // namespace OHOS::Ace::NG