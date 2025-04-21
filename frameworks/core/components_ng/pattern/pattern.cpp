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

#include "core/components_ng/pattern/pattern.h"

#include "core/components_ng/pattern/corner_mark/corner_mark.h"

namespace OHOS::Ace::NG {
int32_t Pattern::OnRecvCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return RET_FAILED;
    }
    auto event = json->GetString("cmd");
    if (event.compare("click") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, RET_FAILED);
        auto clickEventFunc = gestureHub->GetClickEvent();
        CHECK_NULL_RETURN(clickEventFunc, RET_FAILED);
        GestureEvent info;
        clickEventFunc(info);
        return RET_SUCCESS;
    } else if (event.compare("ShowCornerMark") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto cornerMark = AceType::MakeRefPtr<CornerMark>();
        CHECK_NULL_RETURN(cornerMark, RET_FAILED);
        return cornerMark->ResponseShowCornerMarkEvent(host, command);
    } else {
        return OnInjectionEvent(command);
    }
    return RET_FAILED;
}
} // namespace OHOS::Ace::NG