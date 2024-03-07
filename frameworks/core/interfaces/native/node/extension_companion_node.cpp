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

#include "core/interfaces/native/node/extension_companion_node.h"

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_5 = 5;
constexpr int NUM_7 = 7;
constexpr int NUM_32 = 32;
constexpr float DEFAULT_FVALUE = 0.0f;

ArkUICanvasHandle ExtensionCompanionNode::getCanvas()
{
    return reinterpret_cast<ArkUICanvasHandle>(0x123456789aLL);
}

ArkUIEventCallbackArg ExtensionCompanionNode::arg(ArkUI_Float32 f32)
{
    ArkUIEventCallbackArg result;
    result.f32 = f32;
    return result;
}

ArkUIEventCallbackArg ExtensionCompanionNode::arg(ArkUI_Int32 i32)
{
    ArkUIEventCallbackArg result;
    result.i32 = i32;
    return result;
}

ArkUI_Int32 ExtensionCompanionNode::getPeerId() const
{
    return peerId_;
}

ArkUI_Int32 ExtensionCompanionNode::getCallbackId() const
{
    return customCallbackId_;
}

void ExtensionCompanionNode::setCallbackId(int id)
{
    customCallbackId_ = id;
}

const std::vector<ExtensionCompanionNode*>* ExtensionCompanionNode::getChildren()
{
    return &children_;
}

void ExtensionCompanionNode::setParent(ExtensionCompanionNode* parent)
{
    this->parent_ = parent;
}

ExtensionCompanionNode* ExtensionCompanionNode::getParent() const
{
    return this->parent_;
}

void ExtensionCompanionNode::addChild(ExtensionCompanionNode* node)
{
    children_.push_back(node);
    node->setParent(this);
}

void ExtensionCompanionNode::removeChild(ExtensionCompanionNode* node)
{
    auto it = std::find(children_.begin(), children_.end(), node);
    if (it != children_.end()) {
        children_.erase(it);
        node->setParent(nullptr);
    }
}

void ExtensionCompanionNode::insertChildAfter(ExtensionCompanionNode* node, ExtensionCompanionNode* sibling)
{
    auto it = std::find(children_.begin(), children_.end(), sibling);
    children_.insert(it, node);
    node->setParent(this);
}

void ExtensionCompanionNode::setMeasureWidthValue(ArkUI_Float32 value)
{
    measureResult[NUM_0] = value;
    width_ = value;
}

ArkUI_Float32 ExtensionCompanionNode::getMeasureWidthValue()
{
    return measureResult[NUM_0];
}

void ExtensionCompanionNode::setMeasureHeightValue(ArkUI_Float32 value)
{
    measureResult[NUM_1] = value;
    height_ = value;
}

ArkUI_Float32 ExtensionCompanionNode::getMeasureHeightValue()
{
    return measureResult[NUM_1];
}

void ExtensionCompanionNode::setXValue(ArkUI_Float32 value)
{
    layoutResult[NUM_0] = value;
    x_ = value;
}

void ExtensionCompanionNode::setYValue(ArkUI_Float32 value)
{
    layoutResult[NUM_1] = value;
    y_ = value;
}

ArkUI_Int32 ExtensionCompanionNode::measure(
    ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
{
    ArkUI_Float32 minW = data[NUM_0];
    ArkUI_Float32 minH = data[NUM_1];
    ArkUI_Float32 maxW = data[NUM_2];
    ArkUI_Float32 maxH = data[NUM_3];

    if (flags_ & ArkUIAPINodeFlags::CUSTOM_MEASURE) {
        ArkUIEventCallbackArg args[] = { arg(ArkUIAPICustomOp::MEASURE),
            arg(minW), arg(minH), arg(maxW), arg(maxH) };
        callbacks->CallInt(context,  getCallbackId(), NUM_5, &args[NUM_0]);
        width_ = args[NUM_1].f32;
        height_ = args[NUM_2].f32;
        return NUM_0;
    }

    auto* frameNode = reinterpret_cast<OHOS::Ace::NG::FrameNode*>(peer);
    if (frameNode->GetTag() != OHOS::Ace::V2::STACK_ETS_TAG) {
        frameNode->Measure(OHOS::Ace::NG::LayoutConstraintF());
        float scale = static_cast<float>(OHOS::Ace::SystemProperties::GetResolution());
        width_ = frameNode->GetGeometryNode()->GetFrameSize().Width() / scale;
        height_ = frameNode->GetGeometryNode()->GetFrameSize().Height() / scale;
    }

    ArkUI_Float32 itData[] = { minW, minH, maxW, maxH };

    for (auto& it: children_) {
        it->measure(context, &itData[NUM_0], callbacks);
    }

    itData[NUM_0] = width_;
    itData[NUM_1] = height_;

    measureResult[NUM_0] = itData[NUM_0];
    measureResult[NUM_1] = itData[NUM_1];
    measureResult[NUM_2] = itData[NUM_2];
    measureResult[NUM_3] = itData[NUM_3];

    return NUM_0;
}

ArkUI_Int32 ExtensionCompanionNode::layout(
    ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_LAYOUT) {
        ArkUIEventCallbackArg args[] = { arg(ArkUIAPICustomOp::LAYOUT), arg(DEFAULT_FVALUE),
            arg(DEFAULT_FVALUE), arg(DEFAULT_FVALUE), arg(DEFAULT_FVALUE) };
        callbacks->CallInt(context,  getCallbackId(), NUM_5, &args[NUM_0]);
        return NUM_0;
    }

    x_ = data[NUM_0];
    y_ = data[NUM_1];

    for (auto& it: children_) {
        ArkUI_Float32 itData[] = { data[NUM_0],  data[NUM_1], data[NUM_2], data[NUM_3] };
        it->layout(context, &itData[NUM_0], callbacks);
    }

    layoutResult[NUM_0] = data[NUM_0];
    layoutResult[NUM_1] = data[NUM_1];
    layoutResult[NUM_2] = data[NUM_2];
    layoutResult[NUM_3] = data[NUM_3];

    return NUM_0;
}

ArkUI_Int32 ExtensionCompanionNode::draw(
    ArkUIVMContext context, ArkUI_Float32* data, ArkUIAPICallbackMethod* callbacks)
{
    if (flags_ & ArkUIAPINodeFlags::CUSTOM_DRAW) {
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
        callbacks->CallInt(context,  getCallbackId(), NUM_7, &args[NUM_0]);
        return NUM_0;
    }

    for (auto& it: children_) {
        ArkUI_Float32 itData[] = { DEFAULT_FVALUE, DEFAULT_FVALUE, DEFAULT_FVALUE, DEFAULT_FVALUE };
        it->draw(context, &itData[NUM_0], callbacks);
    }

    return NUM_0;
}