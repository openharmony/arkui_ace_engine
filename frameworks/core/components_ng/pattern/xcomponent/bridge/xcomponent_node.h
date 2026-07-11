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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_XCOMPONENT_NODE_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_XCOMPONENT_NODE_H

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace::Framework {
struct XComponentParams {
    int32_t elmtId = -1;
    int32_t xcomponentType = 0;
    int32_t renderType = 0;
    int32_t width = 0;
    int32_t height = 0;
    std::string xcomponentId;
    std::string surfaceId;
    std::string libraryName;
    JSXComponentController* controller = nullptr;
};

class ACE_EXPORT XComponentNode {
public:
    // For xcomponent node
    static void* Create(const XComponentParams& params);

    void RegisterOnCreate(NG::ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& func);
    void RegisterOnDestroy(NG::ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& func);
    void SetFrameNode(RefPtr<AceType> frameNode)
    {
        frameNode_ = frameNode;
    }
    RefPtr<AceType> GetFrameNode() const
    {
        return frameNode_;
    }
    bool ChangeRenderType(int32_t renderType);

private:
    RefPtr<AceType> frameNode_;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_XCOMPONENT_BRIDGE_XCOMPONENT_NODE_H