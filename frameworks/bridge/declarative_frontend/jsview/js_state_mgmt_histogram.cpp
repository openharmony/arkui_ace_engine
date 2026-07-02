/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_state_mgmt_histogram.h"

#include "base/hiviewdfx/histogram_wrapper.h"
#include "base/log/log_wrapper.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings.h"

namespace OHOS::Ace::Framework {
void JSStateMgmtHistogram::JSBind(BindingTarget globalObj)
{
    JSClass<JSStateMgmtHistogram>::Declare("StateMgmtHistogram");
    JSClass<JSStateMgmtHistogram>::StaticMethod("recordBoolean", &JSStateMgmtHistogram::RecordBoolean);
    JSClass<JSStateMgmtHistogram>::Bind(globalObj);
}

void JSStateMgmtHistogram::RecordBoolean(const JSCallbackInfo& info)
{
    // The metric name is supplied by the frontend caller.
#ifdef ACE_ENGINE_API_METRICS_EXT_ENABLE
    if (!info[0]->IsString() || !info[1]->IsNumber()) {
        TAG_LOGE(AceLogTag::ACE_STATE_MGMT,
            "JSStateMgmtHistogram::RecordBoolean invalid arguments, expected (string, number)");
        return;
    }
    std::string fullName = "ArkUI." + info[0]->ToString();
    int32_t sample = info[1]->ToNumber<int32_t>();
    HISTOGRAM_BOOLEAN(fullName.c_str(), sample ? 1 : 0);
#endif
}
} // namespace OHOS::Ace::Framework
