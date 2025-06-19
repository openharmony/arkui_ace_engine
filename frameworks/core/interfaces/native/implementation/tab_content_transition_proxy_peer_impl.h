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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_CONTENT_TRANSITION_PROXY_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_CONTENT_TRANSITION_PROXY_PEER_H

#include <optional>
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class TabContentTransitionProxyPeerImpl {
public:
    TabContentTransitionProxyPeerImpl() = default;

    void AddTargetController(const WeakPtr<TabContentTransitionProxy> &handler)
    {
        handler_ = handler;
    }

    void FinishTransition()
    {
        if (auto proxy = handler_.Upgrade(); proxy) {
            proxy->FinishTransition();
        }
    }

    int32_t GetFrom()
    {
        if (auto proxy = handler_.Upgrade(); proxy) {
            return proxy->GetFromIndex();
        }
        return 0;
    }

    void SetFrom(int index)
    {
        if (auto proxy = handler_.Upgrade(); proxy) {
            proxy->SetFromIndex(index);
        }
    }

    int32_t GetTo()
    {
        if (auto proxy = handler_.Upgrade(); proxy) {
            return proxy->GetToIndex();
        }
        return 0;
    }

    void SetTo(int index)
    {
        if (auto proxy = handler_.Upgrade(); proxy) {
            proxy->SetToIndex(index);
        }
    }

private:
    Ace::WeakPtr<TabContentTransitionProxy> handler_;
};
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_TAB_CONTENT_TRANSITION_PROXY_PEER_H
