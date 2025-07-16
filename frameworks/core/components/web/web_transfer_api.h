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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_TRANSFER_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_TRANSFER_API_H

#include "core/components/web/web_event.h"

#include <node_api.h>
#include <tuple>

namespace OHOS::Ace {

template <typename... Types>
class ACE_EXPORT WebTransferBase : public Referenced {
public:
    WebTransferBase() = default;
    ~WebTransferBase() = default;

    template <std::size_t I>
    auto get() {
        return std::get<I>(transferValues_);
    }
protected:
    std::tuple<Types...> transferValues_;
};

namespace Framework {
napi_value CreateJSScreenCaptureRequestObject(napi_env env, const RefPtr<WebScreenCaptureRequest>& value);
napi_value CreateJSWebDialogObject(napi_env env, const RefPtr<Result>& value);
napi_value CreateJSFileSelectorResultObject(napi_env env, const RefPtr<FileSelectorResult>& value);
napi_value CreateJSFileSelectorParamObject(napi_env env, const RefPtr<WebFileSelectorParam>& value);
napi_value CreateJSContextMenuResultObject(napi_env env, const RefPtr<ContextMenuResult>& value);
napi_value CreateJSContextMenuParamObject(napi_env env, const RefPtr<WebContextMenuParam>& value);
}
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_TRANSFER_API_H