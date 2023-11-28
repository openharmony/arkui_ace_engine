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

#include "arkuiformrenderproxy_fuzzer.h"

#define private public
#define protected public
#include "interfaces/inner_api/form_render/include/form_renderer_delegate_proxy.h"
#include "interfaces/inner_api/form_render/include/form_renderer_dispatcher_proxy.h"
#include "test/mock/interfaces/mock_i_remote_object.h"
#undef private
#undef protected

namespace OHOS::Ace {
const uint32_t u16m = 65535;
bool DelegateProxyAPI(const std::string data, size_t size)
{
    sptr<IRemoteObject> impl = new MockIRemoteObject();
    FormRendererDelegateProxy delegateProxy(impl);
    std::shared_ptr<Rosen::RSSurfaceNode> surfaceNode;
    OHOS::AppExecFwk::FormJsInfo formJsInfo;
    AAFwk::Want want;
    delegateProxy.OnSurfaceCreate(surfaceNode, formJsInfo, want);
    delegateProxy.OnActionEvent(data);
    delegateProxy.OnError(data, data);
    return true;
}

bool DispatcherProxyAPI(const std::string data, size_t size)
{
    sptr<IRemoteObject> impl = new MockIRemoteObject();
    FormRendererDispatcherProxy dispatcherProxy(impl);
    std::shared_ptr<OHOS::MMI::PointerEvent> pointEvent;
    dispatcherProxy.DispatchPointerEvent(pointEvent);
    dispatcherProxy.SetAllowUpdate(true);
    return true;
}
}

using namespace OHOS;
using namespace OHOS::Ace;
/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    auto ri = size % u16m;
    std::string str(reinterpret_cast<const char*>(data), ri);
    /* Run your code on data */
    DelegateProxyAPI(str, size);
    DispatcherProxyAPI(str, size);
    return 0;
}
