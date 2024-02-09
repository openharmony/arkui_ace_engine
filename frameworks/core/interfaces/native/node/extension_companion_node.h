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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/components_ng/base/frame_node.h"

using std::string;

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_32 = 32;
constexpr int UNDEFINED_DIMENSION_UNIT = -1;
constexpr float DEFAULT_FVALUE = 0.0f;

struct Dimension {
    ArkUI_Float32 value = NUM_0;
    ArkUI_Int32 unit = UNDEFINED_DIMENSION_UNIT;
};

struct ExtensionCompanionNode {
    private:

    ArkUI_Int32 peerId;
    ArkUI_Int32 customCallbackId;
    ArkUI_Int32 flags;
    std::vector<ExtensionCompanionNode*> children;
    ExtensionCompanionNode* parent;
    ArkUI_Float32 width;
    ArkUI_Float32 height;
    ArkUI_Float32 x;
    ArkUI_Float32 y;

    ArkUICanvasHandle getCanvas()
    {
        return reinterpret_cast<ArkUICanvasHandle>(0x123456789aLL);
    }

    ArkUIEventCallbackArg arg(ArkUI_Float32 f32)
    {
        ArkUIEventCallbackArg result;
        result.f32 = f32;
        return result;
    }

    ArkUIEventCallbackArg arg(ArkUI_Int32 i32)
    {
        ArkUIEventCallbackArg result;
        result.i32 = i32;
        return result;
    }

    public:
    ExtensionCompanionNode(int peerId, int flags) : peerId(peerId), flags(flags), parent(nullptr) {}

    ~ExtensionCompanionNode() {}

    void* peer = nullptr;
    Dimension dimensionWidth;
    Dimension dimensionHeight;
    ArkUI_Int32 alignment = NUM_0;
    ArkUI_Float32* measureResult = new ArkUI_Float32[4];
    ArkUI_Float32* layoutResult = new ArkUI_Float32[4];

    ArkUI_Int32 getPeerId() const { return peerId; }

    ArkUI_Int32 callbackId() const { return customCallbackId; }

    void setCallbackId(int id) { customCallbackId = id; }

    const std::vector<ExtensionCompanionNode*>* getChildren() { return &children; }

    void dispose() { delete this; }

    void setParent(ExtensionCompanionNode* parent) { this->parent = parent; }

    ExtensionCompanionNode* getParent() const { return this->parent; }

    void addChild(ExtensionCompanionNode* node)
    {
        children.push_back(node);
        node->setParent(this);
    }

    void removeChild(ExtensionCompanionNode* node)
    {
        auto it = std::find(children.begin(), children.end(), node);
        if (it != children.end()) {
            children.erase(it);
            node->setParent(nullptr);
        }
    }

    void insertChildAfter(ExtensionCompanionNode* node, ExtensionCompanionNode* sibling)
    {
        auto it = std::find(children.begin(), children.end(), sibling);
        children.insert(it, node);
        node->setParent(this);
    }

    void setMeasureWidthValue(ArkUI_Float32 value)
    {
        if (measureResult != nullptr) measureResult[NUM_0] = value;
        width = value;
    }

    ArkUI_Float32 getMeasureWidthValue()
    {
        return (measureResult == nullptr) ? NUM_0 : measureResult[NUM_0];
    }

    void setMeasureHeightValue(ArkUI_Float32 value)
    {
        if (measureResult != nullptr) measureResult[NUM_1] = value;
        height = value;
    }

    ArkUI_Float32 getMeasureHeightValue()
    {
        return (measureResult == nullptr) ? NUM_0 : measureResult[NUM_1];
    }

    void setXValue(ArkUI_Float32 value)
    {
        if (layoutResult != nullptr) layoutResult[NUM_0] = value;
        x = value;
    }

    void setYValue(ArkUI_Float32 value)
    {
        if (layoutResult != nullptr) layoutResult[NUM_1] = value;
        y = value;
    }

    ArkUI_Int32 measure(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
    {
        ArkUI_Float32 minW = data[NUM_0];
        ArkUI_Float32 minH = data[NUM_1];
        ArkUI_Float32 maxW = data[NUM_2];
        ArkUI_Float32 maxH = data[NUM_3];

        if (flags & ArkUIAPINodeFlags::CUSTOM_MEASURE) {
            ArkUIEventCallbackArg args[] = { arg(ArkUIAPICustomOp::MEASURE),
                arg(minW), arg(minH), arg(maxW), arg(maxH) };
            callbacks->CallInt(context,  callbackId(), NUM_5, &args[NUM_0]);
            width = args[NUM_1].f32;
            height = args[NUM_2].f32;
            return NUM_0;
        }

        auto* frameNode = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(peer);
        if (frameNode->GetTag() != OHOS::Ace::V2::STACK_ETS_TAG) {
            frameNode->Measure(OHOS::Ace::NG::LayoutConstraintF());
            float scale = (float) OHOS::Ace::SystemProperties::GetResolution();
            width = frameNode->GetGeometryNode()->GetFrameSize().Width() / scale;
            height = frameNode->GetGeometryNode()->GetFrameSize().Height() / scale;
        }

        ArkUI_Float32 itData[] = { minW, minH, maxW, maxH };

        for (auto& it: children) {
            it->measure(context, &itData[NUM_0], callbacks);
        }

        itData[NUM_0] = width;
        itData[NUM_1] = height;

        measureResult[NUM_0] = itData[NUM_0];
        measureResult[NUM_1] = itData[NUM_1];

        return NUM_0;
    }

    ArkUI_Int32 layout(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
    {
        if (flags & ArkUIAPINodeFlags::CUSTOM_LAYOUT) {
            ArkUIEventCallbackArg args[] = { arg(ArkUIAPICustomOp::LAYOUT), arg(DEFAULT_FVALUE),
                arg(DEFAULT_FVALUE), arg(DEFAULT_FVALUE), arg(DEFAULT_FVALUE) };
            callbacks->CallInt(context,  callbackId(), NUM_5, &args[NUM_0]);
            return NUM_0;
        }

        x = data[NUM_0];
        y = data[NUM_1];

        for (auto& it: children) {
            ArkUI_Float32 itData[] = { data[NUM_0],  data[NUM_1], data[NUM_2], data[NUM_3] };
            it->layout(context, &itData[NUM_0], callbacks);
        }

        layoutResult = &data[NUM_0];

        return NUM_0;
    }

    ArkUI_Int32 draw(ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
    {
        if (flags & ArkUIAPINodeFlags::CUSTOM_DRAW) {
            uintptr_t canvas = reinterpret_cast<uintptr_t>(getCanvas());
            ArkUIEventCallbackArg args[] = {
                arg(ArkUIAPICustomOp::DRAW),
                arg((ArkUI_Int32)(canvas & 0xffffffff)),
                arg((ArkUI_Int32)((static_cast<uint64_t>(canvas) >> NUM_32) & 0xffffffff)),
                arg(data[NUM_0]),
                arg(data[NUM_1]),
                arg(data[NUM_2]),
                arg(data[NUM_3])
            };
            callbacks->CallInt(context,  callbackId(), NUM_7, &args[NUM_0]);
            return NUM_0;
        }

        for (auto& it: children) {
            ArkUI_Float32 itData[] = { DEFAULT_FVALUE, DEFAULT_FVALUE, DEFAULT_FVALUE, DEFAULT_FVALUE };
            it->draw(context, &itData[NUM_0], callbacks);
        }

        return NUM_0;
    }
};

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_EXTENSION_COMPANION_NODE_H