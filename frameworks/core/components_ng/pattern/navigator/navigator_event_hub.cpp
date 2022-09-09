/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "navigator_event_hub.h"

#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {

void NavigatorEventHub::NavigatePage()
{
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("get jsi delegate failed");
        return;
    }
    switch (type_) {
        case NavigatorType::PUSH:
            delegate->Push(url_, params_);
            break;
        case NavigatorType::REPLACE:
            delegate->Replace(url_, params_);
            break;
        case NavigatorType::BACK:
            delegate->Back(url_, params_);
            break;
        default:
            LOGE("Navigator type is invalid!");
    }
}

} // namespace OHOS::Ace::NG