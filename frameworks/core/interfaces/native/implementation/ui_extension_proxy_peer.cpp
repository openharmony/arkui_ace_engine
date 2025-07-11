/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer.h"

#ifdef WINDOW_SCENE_SUPPORTED
#include "want.h"
#endif //WINDOW_SCENE_SUPPORTED

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef WINDOW_SCENE_SUPPORTED
void UIExtensionProxyPeerImpl::SendData(const AAFwk::WantParams& wantParams)
{
    if (proxy_ == nullptr) {
        return;
    }
    proxy_->SendData(wantParams);
}

int32_t UIExtensionProxyPeerImpl::SendDataSync(
    const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams)
{
    if (proxy_ == nullptr) {
        return 0;
    }
    return proxy_->SendDataSync(wantParams, reWantParams);
}
#endif //WINDOW_SCENE_SUPPORTED
} // namespace OHOS::Ace::NG::GeneratedModifier