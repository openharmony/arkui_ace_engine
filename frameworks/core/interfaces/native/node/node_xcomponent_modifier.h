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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_XCOMPONENT_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_XCOMPONENT_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

#include <memory>

namespace OHOS::Ace {
class InnerXComponentController;
}

namespace OHOS::Ace::NG {
class FrameNode;
}

namespace OHOS::Ace::NG::NodeModifier {
    struct ArkUIXComponentCustomModifier {
        void* (*createFrameNode)(int32_t nodeId, const char* id, int32_t type,
            const char* libraryName, bool hasLibraryName);
        void* (*createTypeNode)(int32_t nodeId, void* params);
        const char* (*getLibraryName)(FrameNode* frameNode, bool* hasLibraryName);
        const char* (*getSoPath)(FrameNode* frameNode);
        int32_t (*getXComponentType)(FrameNode* frameNode);
        void* (*getNativeXComponent)(FrameNode* frameNode, const char* componentId);
        void (*initExternalEventCallbacks)(FrameNode* frameNode);
        void (*nativeXComponentInit)(FrameNode* frameNode);
        void (*setImageAIOptions)(FrameNode* frameNode, void* options);
        void (*getApsSdrRatio)(const char* packageName, int32_t indexForUsingClient, float apsSdrRatio);
        void (*setNodeRenderParams)(FrameNode* frameNode, int32_t renderType, const char* surfaceId);
        void (*initNode)(FrameNode* frameNode);
        bool (*changeRenderType)(FrameNode* frameNode, int32_t renderType);
        void (*createController)(std::shared_ptr<OHOS::Ace::InnerXComponentController>* controller);
        void (*legacyNativeXComponentInit)(void* taskPool, void* nativeXComponent, void* nativeXComponentImpl);
    };

    const ArkUIXComponentModifier* GetXComponentModifier();
    const CJUIXComponentModifier* GetCJUIXComponentModifier();
    const ArkUIXComponentCustomModifier* GetXComponentCustomModifier();
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_XCOMPONENT_MODIFIER_H
