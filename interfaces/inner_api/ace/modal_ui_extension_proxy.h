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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_UI_EXTENSION_PROXY_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_UI_EXTENSION_PROXY_H

#include <cstdint>
#include "macros.h"

namespace OHOS::AAFwk {
class WantParams;
}; // namespace OHOS::AAFwk

namespace OHOS::Ace {
class ACE_FORCE_EXPORT ModalUIExtensionProxy {
public:
    ModalUIExtensionProxy() = default;
    virtual ~ModalUIExtensionProxy() = default;

    /**
     * @description: Send real-time data to the UIExtensionAbility through this Proxy object.
     * @param params Indicates the data to be sent in key-value (K-V) format.
     * If creation is not successful, it returns 0 by default.
     */
    virtual void SendData(const AAFwk::WantParams& params) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_UI_EXTENSION_PROXY_H
