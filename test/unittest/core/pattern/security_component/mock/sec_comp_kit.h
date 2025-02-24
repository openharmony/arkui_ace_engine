/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef ACE_MOKC_INTERFACES_INNER_API_SECURITY_COMPONENT_KIT_H
#define ACE_MOKC_INTERFACES_INNER_API_SECURITY_COMPONENT_KIT_H

#include <string>
#include "iremote_object.h"
#include "i_sec_comp_probe.h"
#include "sec_comp_base_mock.h"

namespace OHOS {
namespace Security {
namespace SecurityComponent {
struct ExtraInfo {
    uint32_t dataSize;
    uint8_t* data;
};

enum class ClickEventType : int32_t {
    UNKNOWN_EVENT_TYPE,
    POINT_EVENT_TYPE,
    KEY_EVENT_TYPE
};

struct SecCompPointEvent {
    double touchX;
    double touchY;
    uint64_t timestamp;
};

struct SecCompKeyEvent {
    uint64_t timestamp;
    int32_t keyCode;
};

struct SecCompClickEvent {
    ClickEventType type;
    union {
        SecCompPointEvent point;
        SecCompKeyEvent key;
    };
    ExtraInfo extraInfo;
};

struct SecCompInfo {
    int32_t scId;
    std::string componentInfo;
    SecCompClickEvent clickInfo;
};

using OnFirstUseDialogCloseFunc = std::function<void(int32_t)>;

class SecCompUiRegister {
public:
    SecCompUiRegister(std::vector<uintptr_t>& callerList, ISecCompProbe* probe) {};
    virtual ~SecCompUiRegister() = default;
    static ISecCompProbe* callbackProbe;
};

class SecCompKit {
public:
    static int32_t RegisterSecurityComponent(SecCompType type, std::string& componentInfo, int32_t& scId)
    {
        scId = 1;
        return 0;
    };

    static int32_t UpdateSecurityComponent(int32_t scId, std::string& componentInfo)
    {
        return 0;
    };

    static int32_t UnregisterSecurityComponent(int32_t scId)
    {
        return 0;
    };

    static int32_t PreRegisterSecCompProcess()
    {
        return 0;
    };

    static int32_t ReportSecurityComponentClickEvent(SecCompInfo& secCompInfo,
        sptr<IRemoteObject> callerToken, OnFirstUseDialogCloseFunc&& func, std::string& message)
    {
        return 0;
    };

    static bool IsServiceExist()
    {
        return false;
    };

    static bool LoadService()
    {
        return true;
    };

    static bool IsSystemAppCalling()
    {
        return false;
    };
};
}  // namespace SecurityComponent
}  // namespace Security
}  // namespace OHOS
#endif  // ACE_MOKC_INTERFACES_INNER_API_SECURITY_COMPONENT_KIT_H
