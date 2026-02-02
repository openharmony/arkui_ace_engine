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

#ifndef UI_SA_PROXY_H
#define UI_SA_PROXY_H

#include "iremote_proxy.h"
#include "ui_sa_interface.h"

namespace OHOS::Ace {

class UiSaProxy : public IRemoteProxy<UiSaInterface> {
public:
    explicit UiSaProxy(const sptr<IRemoteObject>& impl) : IRemoteProxy<UiSaInterface>(impl) {}
    ~UiSaProxy() = default;
};

} // namespace OHOS::Ace

#endif // UI_SA_PROXY_H