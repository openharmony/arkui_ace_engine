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

#include "base/memory/referenced.h"
#include "core/common/ime/ime_extra_config.h"

struct InputMethodExtraConfigPeer final {
    OHOS::Ace::RefPtr<OHOS::Ace::IMEExtraConfig> aceExtraConfig_ = nullptr;

    static InputMethodExtraConfigPeer* Create(void* data)
    {
        auto config = OHOS::Ace::IMEExtraConfig::CreateFromNative(data);
        return new InputMethodExtraConfigPeer(config);
    }

    static void Destroy(InputMethodExtraConfigPeer* peer)
    {
        CHECK_NULL_VOID(peer);
        delete peer;
    }

protected:
    explicit InputMethodExtraConfigPeer(OHOS::Ace::RefPtr<OHOS::Ace::IMEExtraConfig> aceExtraConfig)
        : aceExtraConfig_(aceExtraConfig) {};
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_IME_EXTRA_CONFIG_PEER_H