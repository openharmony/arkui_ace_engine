/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/modal_ui_extension_proxy_impl.h"

namespace OHOS::Ace::NG {
ModalUIExtensionProxyImpl::ModalUIExtensionProxyImpl(const RefPtr<SessionWrapper>& sessionWrapper)
    : sessionWrapper_(sessionWrapper)
{}

void ModalUIExtensionProxyImpl::SendData(const AAFwk::WantParams& params)
{
    CHECK_NULL_VOID(sessionWrapper_);
    sessionWrapper_->SendDataAsync(params);
}
} // namespace OHOS::Ace::NG
