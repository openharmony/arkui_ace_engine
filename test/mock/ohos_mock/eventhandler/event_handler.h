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

#ifndef FOUNDATION_ACE_MOCK_EVENTHANDLER_EVENT_HANDLER_H
#define FOUNDATION_ACE_MOCK_EVENTHANDLER_EVENT_HANDLER_H

#include <memory>

namespace OHOS {
namespace AppExecFwk {

class EventHandler {
public:
    EventHandler() = default;
    virtual ~EventHandler() = default;

    static std::shared_ptr<EventHandler> Current()
    {
        return nullptr;
    }
};

} // namespace AppExecFwk
} // namespace OHOS

#endif // FOUNDATION_ACE_MOCK_EVENTHANDLER_EVENT_HANDLER_H
