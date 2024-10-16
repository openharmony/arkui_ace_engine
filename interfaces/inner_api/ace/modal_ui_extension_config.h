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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_MODAL_CONFIG_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_MODAL_CONFIG_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "modal_ui_extension_proxy.h"

namespace OHOS::AAFwk {
class Want;
class WantParams;
} // namespace OHOS::AAFwk

namespace OHOS::Ace {
struct ModalUIExtensionConfig {
    bool isProhibitBack = false;
    bool isAsyncModalBinding = false;
    bool isAllowedBeCovered = false;
    std::function<void()> doAfterAsyncModalBinding = nullptr;
    bool prohibitedRemoveByRouter = false;
};

struct ModalUIExtensionCallbacks {
    std::function<void(int32_t)> onRelease;
    std::function<void(int32_t, const AAFwk::Want&)> onResult;
    std::function<void(const AAFwk::WantParams&)> onReceive;
    std::function<void(int32_t, const std::string&, const std::string&)> onError;
    std::function<void(const std::shared_ptr<ModalUIExtensionProxy>&)> onRemoteReady;
    std::function<void()> onDestroy;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_MODAL_CONFIG_H
