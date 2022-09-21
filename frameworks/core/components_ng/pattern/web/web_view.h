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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H

#include <functional>
#include <string>

#include "core/components/web/web_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WebView {
public:
    static void Create(const std::string& src, const RefPtr<WebController>& webController);
    static void SetOnPageStart(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onPageStart);
    static void SetOnPageFinish(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onPageEnd);
    static void SetOnHttpErrorReceive(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onHttpErrorReceive);
    static void SetOnErrorReceive(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onErrorReceive);
    static void SetOnConsole(std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>&& onConsole);
    static void SetJsEnabled(bool isJsEnabled);
    static void SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H
