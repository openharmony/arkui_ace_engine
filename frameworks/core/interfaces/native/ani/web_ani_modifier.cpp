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

#include "web_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/ani/web_model_static.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#endif

namespace OHOS::Ace::NG {

void SetWebOptions(ArkUINodeHandle node, const WebviewControllerInfo& controllerInfo)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    if (!frameNode) {
        if (controllerInfo.releaseRefFunc) {
            controllerInfo.releaseRefFunc();
        }
        return;
    }
    if (controllerInfo.getNativePtrFunc) {
        int32_t parentNWebId = -1;
        bool isPopup = ControllerHandlerPeer::ExistController(controllerInfo.getNativePtrFunc(), parentNWebId);
        WebModelStatic::SetPopup(frameNode, isPopup, parentNWebId);
    }
    auto setWebIdFunc = std::move(controllerInfo.setWebIdFunc);
    auto setHapPathFunc = std::move(controllerInfo.setHapPathFunc);
    WebModelStatic::SetWebIdCallback(frameNode, std::move(setWebIdFunc));
    WebModelStatic::SetHapPathCallback(frameNode, std::move(setHapPathFunc));
#endif // WEB_SUPPORTED
}

void SetWebControllerControllerHandler(void* controllerHandler, const WebviewControllerInfo& controllerInfo)
{
#ifdef WEB_SUPPORTED
    ControllerHandlerPeer* peer = reinterpret_cast<ControllerHandlerPeer *>(controllerHandler);
    if (!peer) {
        if (controllerInfo.releaseRefFunc) {
            controllerInfo.releaseRefFunc();
        }
        return;
    }
    peer->SetWebController(controllerInfo);
#endif // WEB_SUPPORTED
}

const ArkUIAniWebModifier* GetWebAniModifier()
{
    static const ArkUIAniWebModifier impl = {
        .setWebOptions = OHOS::Ace::NG::SetWebOptions,
        .setWebControllerControllerHandler = OHOS::Ace::NG::SetWebControllerControllerHandler,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
