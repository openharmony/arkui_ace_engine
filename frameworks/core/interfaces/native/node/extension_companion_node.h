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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/base/frame_node.h"

using std::string;

class ExtensionCompanionNode {
private:
    ArkUI_Int32 peerId_;
    ArkUI_Int32 customCallbackId_;
    ArkUI_Int32 flags_;
    std::vector<ExtensionCompanionNode*> children_;
    ExtensionCompanionNode* parent_;
    ArkUI_Float32 width_;
    ArkUI_Float32 height_;
    ArkUI_Float32 x_;
    ArkUI_Float32 y_;

    ArkUICanvasHandle getCanvas();
    ArkUIEventCallbackArg arg(ArkUI_Float32 f32);
    ArkUIEventCallbackArg arg(ArkUI_Int32 i32);

public:
    ExtensionCompanionNode(int peerId, int flags) : peerId_(peerId), flags_(flags), parent_(nullptr) {}

    ~ExtensionCompanionNode() = default;

    void* peer = nullptr;
    ArkUI_Int32 alignment = 0;
    ArkUI_Float32 measureResult[4] = { 0, 0, 0, 0 };
    ArkUI_Float32 layoutResult[4] = { 0, 0, 0, 0 };

    ArkUI_Int32 getPeerId() const;
    ArkUI_Int32 getCallbackId() const;
    void setCallbackId(int id);

    void setParent(ExtensionCompanionNode* parent);
    ExtensionCompanionNode* getParent() const;
    const std::vector<ExtensionCompanionNode*>* getChildren();

    void addChild(ExtensionCompanionNode* node);
    void removeChild(ExtensionCompanionNode* node);
    void insertChildAfter(ExtensionCompanionNode* node, ExtensionCompanionNode* sibling);

    void setMeasureWidthValue(ArkUI_Float32 value);
    ArkUI_Float32 getMeasureWidthValue();
    void setMeasureHeightValue(ArkUI_Float32 value);
    ArkUI_Float32 getMeasureHeightValue();
    void setXValue(ArkUI_Float32 value);
    void setYValue(ArkUI_Float32 value);

    ArkUI_Int32 measure(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks);
    ArkUI_Int32 layout(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks);
    ArkUI_Int32 draw(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks);
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H