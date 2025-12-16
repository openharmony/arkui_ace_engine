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

#include "callback_helper.h"

namespace OHOS::Ace::NG {

#if !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)
RefPtr<OHOS::Ace::NG::DetachedFreeRootProxyNode> CreateProxyNode(const RefPtr<UINode>& uiNode)
{
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto instanceId = container->GetInstanceId();
    auto proxyNode = AceType::MakeRefPtr<DetachedFreeRootProxyNode>(instanceId);
    CHECK_NULL_RETURN(proxyNode, nullptr);
    proxyNode->AddChild(uiNode);
    return proxyNode;
}
#endif // !defined(PREVIEW) && !defined(ARKUI_CAPI_UNITTEST)

}