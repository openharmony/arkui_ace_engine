/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_IME_EXTRA_CONFIG_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_IME_EXTRA_CONFIG_PEER_H

#include <cstdint>

#include "extra_config.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct InputMethodExtraConfigPeer final {
    using ExtraConfig = OHOS::MiscServices::ExtraConfig;
    std::shared_ptr<ExtraConfig> extraInfo = nullptr;

protected:
    explicit InputMethodExtraConfigPeer(std::shared_ptr<ExtraConfig> extraInfo) : extraInfo(extraInfo) {};
    virtual ~InputMethodExtraConfigPeer() = default;
    friend OHOS::Ace::NG::PeerUtils;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_IME_EXTRA_CONFIG_PEER_H