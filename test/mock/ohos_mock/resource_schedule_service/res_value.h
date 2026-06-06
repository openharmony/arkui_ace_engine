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
#ifndef RES_TYPE_H
#define RES_TYPE_H

#include <cstdint>

namespace OHOS {
namespace ResourceSchedule {
namespace ResType {

enum EventType : uint32_t {
    EVENT_SYART = 0,
    EVENT_COMPONENT_PREMAKE = 21,
    EVENT_END,
};

enum EventListenerGroup : uint32_t {
    LISTENER_GROUP_BEGIN = 0,
    LISTENER_GROUP_COMMON = 1,
    LISTENER_GROUP_LLM = 2,
    LISTENER_GROUP_GAME = 3,
    LISTENER_GROUP_CHMERA = 4,
    LISTENER_GROUP_DH = 5,
    LISTENER_GROUP_KIDDO = 6,
    LISTENER_GROUP_END,
};
} // end ResType
} // end ResourceSchedule
} // OHOS
#endif
