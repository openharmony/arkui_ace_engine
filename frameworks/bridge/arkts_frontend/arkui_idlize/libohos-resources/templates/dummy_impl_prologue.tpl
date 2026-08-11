/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define _HAS_STD_BYTE 0

#include <algorithm>
#include <array>
#include <chrono>
#include <future>
#include <thread>
#include <map>

#include "Serializers.h"
#include "interop-logging.h"
#include "arkoala-macros.h"
#include "tree.h"
#include "logging.h"
#include "dynamic-loader.h"
#include "interop-utils.h"
#include "%API_GENERATED%.h"

#undef max

// For logging we use operations exposed via interop, SetLoggerSymbol() is called
// when library is loaded.
const GroupLogger* loggerInstance = GetDefaultLogger();

const GroupLogger* GetDummyLogger() {
    return loggerInstance;
}

void SetDummyLogger(const GroupLogger* logger) {
    loggerInstance = logger;
}

void startGroupedLog(int kind) {
    GetDummyLogger()->startGroupedLog(kind);
}
void stopGroupedLog(int kind) {
    GetDummyLogger()->stopGroupedLog(kind);
}
const char* getGroupedLog(int kind) {
    return GetDummyLogger()->getGroupedLog(kind);
}
int needGroupedLog(int kind) {
    return GetDummyLogger()->needGroupedLog(kind);
}
void appendGroupedLog(int kind, const std::string& str) {
    GetDummyLogger()->appendGroupedLog(kind, str.c_str());
}

void dummyClassFinalizer(KNativePointer* ptr) {
    char hex[20];
    InteropPrintToBufferN(hex, sizeof(hex), "0x%llx", (long long)ptr);
    string out("dummyClassFinalizer(");
    out.append(hex);
    out.append(")");
    appendGroupedLog(1, out);
}

namespace TreeNodeDelays {

void busyWait(Ark_Int64 nsDelay) {
    if (nsDelay <= 0) {
        return;
    }
    using namespace std::chrono;
    auto start = steady_clock::now();
    auto now = start;
    auto deadline = now + nanoseconds(nsDelay);
    std::array<char, 8> buf;
    for (; now < deadline; now = steady_clock::now()) {
        auto nsNow = now.time_since_epoch().count();
        buf = { static_cast<char>(nsNow%100 + 20), 19, 18, 17, 16, 15, 14, static_cast<char>(nsNow%12) };
        for (int i = 0; i < 200; i++) {
            std::next_permutation(buf.begin(), buf.end());
        }
    }
    //ARKOALA_LOG("Requested wait %f ms, actual %f ms\n", nsDelay/1000000.0f, (now - start).count()/1000000.0f);
}

const int MAX_NODE_TYPE = 200;
std::array<Ark_Int64, MAX_NODE_TYPE> createNodeDelay = {};
std::array<Ark_Int64, MAX_NODE_TYPE> measureNodeDelay = {};
std::array<Ark_Int64, MAX_NODE_TYPE> layoutNodeDelay = {};
std::array<Ark_Int64, MAX_NODE_TYPE> drawNodeDelay = {};

void CheckType(GENERATED_Ark_NodeType type) {
    if (static_cast<int>(type) >= MAX_NODE_TYPE) {
        INTEROP_FATAL("Error: GENERATED_Ark_NodeType value is too big, change MAX_NODE_TYPE accordingly");
    }
}

void SetCreateNodeDelay(GENERATED_Ark_NodeType type, Ark_Int64 nanoseconds) {
    CheckType(type);
    createNodeDelay[type] = nanoseconds;
}

void SetMeasureNodeDelay(GENERATED_Ark_NodeType type, Ark_Int64 nanoseconds) {
    CheckType(type);
    measureNodeDelay[type] = nanoseconds;
}

void SetLayoutNodeDelay(GENERATED_Ark_NodeType type, Ark_Int64 nanoseconds) {
    CheckType(type);
    layoutNodeDelay[type] = nanoseconds;
}

void SetDrawNodeDelay(GENERATED_Ark_NodeType type, Ark_Int64 nanoseconds) {
    CheckType(type);
    drawNodeDelay[type] = nanoseconds;
}

}

inline Ark_NodeHandle AsNodeHandle(TreeNode* node) {
    return reinterpret_cast<Ark_NodeHandle>(node);
}

template<typename From>
constexpr TreeNode *AsNode(From ptr) {
    return reinterpret_cast<TreeNode *>(ptr);
}

void EmitOnClick(Ark_NativePointer node, Ark_ClickEvent event) {
    LOGE("EmitOnclick %p", node);
    auto frameNode = AsNode(node);
    frameNode->callClickEvent(event);
}
void RegisterOnClick(Ark_NativePointer node, const Callback_ClickEvent_Void* event) {
    auto frameNode = AsNode(node);
    auto callback = *event;
    callback.resource.hold(callback.resource.resourceId);
    auto onEvent = [callback](Ark_ClickEvent event) {
        if (callback.call) {
            callback.call(callback.resource.resourceId, event);
        }
    };
    frameNode->setClickEvent(std::move(onEvent));
}

void RegisterDrawModifierCallback(Ark_DrawModifier peer, const Callback_DrawContext_Void* event, int type) {
    std::shared_ptr<DrawModifierCaller> modifier = (DrawModifiersQueue.find(peer) != DrawModifiersQueue.end())
        ? DrawModifiersQueue[peer]
        : std::make_shared<DrawModifierCaller>();
    DrawModifiersQueue[peer] = modifier;
    auto callback = *event;
    callback.resource.hold(callback.resource.resourceId);
    auto onEvent = [callback](Ark_DrawContext event) {
        if (callback.call) {
            callback.call(callback.resource.resourceId, event);
        }
    };
    modifier->setDrawModifierCallback(std::move(onEvent), type);
}

void CallDrawModifierCallbacks(Ark_DrawModifier peer) {
    std::shared_ptr<DrawModifierCaller> modifier = DrawModifiersQueue[peer];
    uint64_t pointer = 42;
    auto context = reinterpret_cast<Ark_DrawContext*>(&pointer);
    modifier->callDrawModifierCallback(*context, DrawBehind);
    modifier->callDrawModifierCallback(*context, DrawContent);
    modifier->callDrawModifierCallback(*context, DrawFront);
}

void DumpTree(TreeNode *node, Ark_Int32 indent) {
    ARKOALA_LOG("%s[%s: %d]\n", string(indent * 2, ' ').c_str(), node->namePtr(), node->id());
    for (auto child: *node->children()) {
        if (child)
            DumpTree(child, indent + 1);
    }
}

// Improve: remove in favour of callbackCallerInstance!
GENERATED_Ark_APICallbackMethod *callbacks = nullptr;

int TreeNode::_globalId = 1;
string TreeNode::_noAttribute;

Ark_Float32 parseLength(Ark_Float32 parentValue, Ark_Float32 value, Ark_Int32 unit) {
    switch (unit) {
        //PX
        case 0: {
            const Ark_Float32 scale = 1; // Improve: need getting current device scale
            return value * scale;
        }
        //PERCENTAGE
        case 3: {
            return parentValue / 100 * value;
        }
        default:
            // VP, FP, LPX, UndefinedDimensionUnit: Improve: parse properly this units
            return value;
    }
}

void align(TreeNode *child, Ark_Float32 width, Ark_Float32 height, Ark_Float32* args) {
    switch (child->alignment) {
        case 0: { // Alignment.TopStart
            break;
        }
        case 3: { // Alignment.Start
            args[1] += (height - child->measureResult[1]) / 2;
            break;
        }
        case 6: { // Alignment.BottomStart
            args[1] += height - child->measureResult[1];
            break;
        }
        case 1: { // Alignment.Top
            args[0] += (width - child->measureResult[0]) / 2;
            break;
        }
        case 4: { // Alignment.Center
            args[0] += (width - child->measureResult[0]) / 2;
            args[1] += (height - child->measureResult[1]) / 2;
            break;
        }
        case 7: { // Alignment.Bottom
            args[0] += (width - child->measureResult[0]) / 2;
            args[1] += height - child->measureResult[1];
            break;
        }
        case 2: { // Alignment.TopEnd
            args[0] += width - child->measureResult[0];
            break;
        }
        case 5: { // Alignment.End
            args[0] += width - child->measureResult[0];
            args[1] += (height - child->measureResult[1]) / 2;
            break;
        }
        case 8: { // Alignment.BottomEnd
            args[0] += width - child->measureResult[0];
            args[1] += height - child->measureResult[1];
            break;
        }
    }
}

GENERATED_Ark_EventCallbackArg arg(Ark_Float32 f32) {
    GENERATED_Ark_EventCallbackArg result;
    result.f32 = f32;
    return result;
}

GENERATED_Ark_EventCallbackArg arg(Ark_Int32 i32) {
    GENERATED_Ark_EventCallbackArg result;
    result.i32 = i32;
    return result;
}

float TreeNode::measure(Ark_VMContext vmContext, float* data) {
    TreeNodeDelays::busyWait(TreeNodeDelays::measureNodeDelay[_customIntData]);

    Ark_Float32 minWidth = data[0];
    Ark_Float32 minHeight = data[1];
    Ark_Float32 maxWidth = data[2];
    Ark_Float32 maxHeight = data[3];
    if (_flags & Ark_APINodeFlags::GENERATED_CUSTOM_MEASURE) {
        GENERATED_Ark_EventCallbackArg args[] = {
            arg(Ark_APICustomOp::GENERATED_MEASURE),
            arg(minWidth),
            arg(minHeight),
            arg(maxWidth),
            arg(maxHeight)
    };
        callbacks->CallInt(vmContext, customId(), 5, &args[0]);
        _width = args[1].f32;
        _height = args[2].f32;
        return 0;
    }

    const Ark_Float32 constraintWidth = data[0];
    const Ark_Float32 constraintHeight = data[1];

    _width = parseLength(constraintWidth, dimensionWidth.value, dimensionWidth.unit);
    _height = parseLength(constraintHeight, dimensionHeight.value, dimensionHeight.unit);

    Ark_Float32 itData[] = { minWidth, minHeight, minHeight, maxHeight };
    if (dimensionWidth.unit != UndefinedDimensionUnit) {
        itData[0] = _width;
    }
    if (dimensionHeight.unit != UndefinedDimensionUnit) {
        itData[1] = _height;
    }

    const bool isWidthWrapped = dimensionWidth.unit == UndefinedDimensionUnit;
    const bool isHeightWrapped = dimensionHeight.unit == UndefinedDimensionUnit;

    for (auto* it: *children()) {
        it->measure(vmContext, &itData[0] );
        if (isWidthWrapped) {
            _width = std::max(_width, itData[0]);
        }
        if (isHeightWrapped) {
            _height = std::max(_height, itData[1]);
        }
    }

    data[0] = _width;
    data[1] = _height;

    measureResult = &data[0];

    // Improve: use return flag for dirty bits propagation.
    return 0;
}

Ark_CanvasHandle getCanvas(TreeNode* node) {
    // Improve: real canvas.
    return reinterpret_cast<Ark_CanvasHandle>(0x123456789aLL);
}

float TreeNode::layout(Ark_VMContext vmContext, float* data) {
    TreeNodeDelays::busyWait(TreeNodeDelays::layoutNodeDelay[_customIntData]);

    if (_flags & Ark_APINodeFlags::GENERATED_CUSTOM_LAYOUT) {
        GENERATED_Ark_EventCallbackArg args[] = {
            arg(Ark_APICustomOp::GENERATED_LAYOUT),
            arg(0.0f),
            arg(0.0f),
            arg(0.0f),
            arg(0.0f)
    };
        callbacks->CallInt(vmContext, customId(), 5, &args[0]);
        return 0;
    }

    _x = data[0];
    _y = data[1];

    for (auto* it: *children()) {
        Ark_Float32 itData[] = { data[0], data[1], data[2], data[3] };
        align(it, _width, _height, &itData[0]);
        it->layout(vmContext, &itData[0]);
    }

    layoutResult = &data[0];

    // Improve: use return flag for dirty bits propagation.
    return 0;
}

float TreeNode::draw(Ark_VMContext vmContext, float* data) {
    TreeNodeDelays::busyWait(TreeNodeDelays::drawNodeDelay[_customIntData]);
    if (_flags & Ark_APINodeFlags::GENERATED_CUSTOM_DRAW) {
        uintptr_t canvas = reinterpret_cast<uintptr_t>(getCanvas(this));
        GENERATED_Ark_EventCallbackArg args[] = {
            arg(Ark_APICustomOp::GENERATED_DRAW),
            arg((Ark_Int32)(canvas & 0xffffffff)),
            arg((Ark_Int32)((canvas >> 32) & 0xffffffff)),
            arg(data[0]), arg(data[1]), arg(data[2]), arg(data[3])
        };
        callbacks->CallInt(vmContext, customId(), 7, &args[0]);
        return 0;
    }
    for (auto* it: *children()) {
        Ark_Float32 itData[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        it->draw(vmContext, &itData[0]);
    }
    return 0;
}

void TreeNode::setMeasureWidthValue(float value) {
    if (measureResult != nullptr) measureResult[0] = value;
    _width = value;
}

float TreeNode::getMeasureWidthValue() {
    return (measureResult == nullptr) ? 0 : measureResult[0];
}

void TreeNode::setMeasureHeightValue(float value) {
    if (measureResult != nullptr) measureResult[1] = value;
    _height = value;
}

float TreeNode::getMeasureHeightValue() {
    return (measureResult == nullptr) ? 0 : measureResult[1];
}

void TreeNode::setXValue(float value) {
    if (layoutResult != nullptr) layoutResult[0] = value;
    _x = value;
}

float TreeNode::getXValue() {
    return (layoutResult == nullptr) ? 0 : layoutResult[0];
}

void TreeNode::setYValue(float value) {
    if (layoutResult != nullptr) layoutResult[1] = value;
    _y = value;
}

float TreeNode::getYValue() {
    return (layoutResult == nullptr) ? 0 : layoutResult[1];
}

namespace OHOS::Ace::NG {

namespace GeneratedBridge {

Ark_NodeHandle CreateNode(GENERATED_Ark_NodeType type, Ark_Int32 id, Ark_Int32 flags) {
    TreeNodeDelays::CheckType(type);
    TreeNodeDelays::busyWait(TreeNodeDelays::createNodeDelay[type]);
    TreeNode *node = new TreeNode("node", id, flags);
    node->setCustomIntData(type);
    Ark_NodeHandle result = AsNodeHandle(node);

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_NodeHandle peer" + std::to_string(reinterpret_cast<uintptr_t>(result))
            + " = GetBasicNodeApi()->createNode(GENERATED_Ark_NodeType("
            + std::to_string(type) + "), " + std::to_string(id) + ", " + std::to_string(flags) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }
    string out("createNode(");
    WriteToString(&out, (Ark_Int32)type);
    out.append(", ");
    WriteToString(&out, id);
    out.append(", ");
    WriteToString(&out, flags);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}
}

namespace GeneratedApiImpl {

static int res_num = 0;

void SetCallbackMethod(%CPP_PREFIX%Ark_APICallbackMethod* method) {
    callbacks = method;
}

Ark_Float32 GetDensity(Ark_Int32 deviceId) {
    Ark_Float32 result = 1.0f;

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("getDensity(");
    WriteToString(&out, deviceId);
    out.append(")");
    appendGroupedLog(1, out);

    return result;
}

Ark_Float32 GetFontScale(Ark_Int32 deviceId) {
    Ark_Float32 result = 1.0f;

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("getFontScale(");
    WriteToString(&out, deviceId);
    out.append(")");
    appendGroupedLog(1, out);

    return result;
}

Ark_Float32 GetDesignWidthScale(Ark_Int32 deviceId) {
    Ark_Float32 result = 1.0f;

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("getDesignWidthScale(");
    WriteToString(&out, deviceId);
    out.append(")");
    appendGroupedLog(1, out);

    return result;
}

Ark_NodeHandle GetNodeByViewStack() {
    Ark_NodeHandle result = reinterpret_cast<Ark_NodeHandle>(234);
    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_NodeHandle peer" + std::to_string(reinterpret_cast<uintptr_t>(result))
            + " = GetBasicNodeApi()->getNodeByViewStack();\n");
        appendGroupedLog(2, _logData);
    }
    if (!needGroupedLog(1)) {
        return result;
    }
    string out("getNodeByViewStack()");
    appendGroupedLog(1, out);
    return result;
}

void DisposeNode(Ark_NodeHandle node) {
    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  GetBasicNodeApi()->disposeNode(peer" + std::to_string(reinterpret_cast<uintptr_t>(node))
            + ");\n");
        appendGroupedLog(2, _logData);
    }
    if (needGroupedLog(1)) {
        string out("disposeNode(");
        WriteToString(&out, node);
        out.append(")");
        appendGroupedLog(1, out);
    }
    AsNode(node)->dispose();
}

void DumpTreeNode(Ark_NodeHandle node) {
    DumpTree(AsNode(node), 0);

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  GetBasicNodeApi()->dumpTreeNode(peer" + std::to_string(reinterpret_cast<uintptr_t>(node))
            + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return;
    }

    string out("dumpTreeNode(");
    WriteToString(&out, node);
    out.append(")");
    appendGroupedLog(1, out);
}

Ark_Int32 AddChild(Ark_NodeHandle parent, Ark_NodeHandle child) {
    int result = AsNode(parent)->addChild(AsNode(child));

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Int32 res" + std::to_string(res_num++) + " = GetBasicNodeApi()->addChild(peer"
            + std::to_string((uintptr_t)parent) + ", peer" + std::to_string((uintptr_t)child) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("addChild(");
    WriteToString(&out, parent);
    out.append(", ");
    WriteToString(&out, child);
    out.append(")");
    appendGroupedLog(1, out);

    // Improve: implement test
    return result;
}

void RemoveChild(Ark_NodeHandle parent, Ark_NodeHandle child) {
    TreeNode *parentPtr = reinterpret_cast<TreeNode *>(parent);
    TreeNode *childPtr = reinterpret_cast<TreeNode *>(child);
    parentPtr->removeChild(childPtr);

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  GetBasicNodeApi()->removeChild(peer"
            + std::to_string((uintptr_t)parent) + ", peer" + std::to_string((uintptr_t)child) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return;
    }

    string out("removeChild(");
    WriteToString(&out, parent);
    out.append(", ");
    WriteToString(&out, child);
    out.append(")");
    appendGroupedLog(1, out);
}

Ark_Int32 InsertChildAfter(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling) {
    int result = AsNode(parent)->insertChildAfter(AsNode(child), AsNode(sibling));

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Int32 res" + std::to_string(res_num++) + " = GetBasicNodeApi()->insertChildAfter(peer"
            + std::to_string((uintptr_t)parent) + ", peer" + std::to_string((uintptr_t)child)
            + ", peer" + std::to_string((uintptr_t)sibling) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("insertChildAfter(");
    WriteToString(&out, parent);
    out.append(", ");
    WriteToString(&out, child);
    out.append(", ");
    WriteToString(&out, sibling);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

Ark_Int32 InsertChildBefore(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_NodeHandle sibling) {
    int result = AsNode(parent)->insertChildBefore(AsNode(child), AsNode(sibling));

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Int32 res" + std::to_string(res_num++) + " = GetBasicNodeApi()->insertChildBefore(peer"
            + std::to_string((uintptr_t)parent) + ", peer" + std::to_string((uintptr_t)child)
            + ", peer" + std::to_string((uintptr_t)sibling) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("insertChildBefore(");
    WriteToString(&out, parent);
    out.append(", ");
    WriteToString(&out, child);
    out.append(", ");
    WriteToString(&out, sibling);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

Ark_Int32 InsertChildAt(Ark_NodeHandle parent, Ark_NodeHandle child, Ark_Int32 position) {
    int result = AsNode(parent)->insertChildAt(AsNode(child), position);

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Int32 res" + std::to_string(res_num++) + " = GetBasicNodeApi()->insertChildAt(peer"
            + std::to_string((uintptr_t)parent) + ", peer" + std::to_string((uintptr_t)child)
            + ", " + std::to_string(position) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("insertChildAt(");
    WriteToString(&out, parent);
    out.append(", ");
    WriteToString(&out, child);
    out.append(", ");
    WriteToString(&out, position);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

void ApplyModifierFinish(Ark_NodeHandle node) {
    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  GetBasicNodeApi()->applyModifierFinish(peer"
            + std::to_string(reinterpret_cast<uintptr_t>(node))
            + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return;
    }
    string out("applyModifierFinish(");
    WriteToString(&out, node);
    out.append(")");
    appendGroupedLog(1, out);
}

void MarkDirty(Ark_NodeHandle node, Ark_UInt32 flag) {
    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  GetBasicNodeApi()->markDirty(peer"+ std::to_string(reinterpret_cast<uintptr_t>(node))
            + ", "  + std::to_string(flag) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return;
    }
    string out("markDirty(");
    WriteToString(&out, node);
    out.append(", ");
    WriteToString(&out, flag);
    out.append(")");
    appendGroupedLog(1, out);
}

Ark_Boolean IsBuilderNode(Ark_NodeHandle node) {
    Ark_Boolean result = true;

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Boolean res" + std::to_string(res_num++) + " = GetBasicNodeApi()->isBuilderNode(peer"
            + std::to_string(reinterpret_cast<uintptr_t>(node)) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }
    string out("isBuilderNode(");
    WriteToString(&out, node);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

Ark_Float32 ConvertLengthMetricsUnit(Ark_Float32 value, Ark_Int32 originUnit, Ark_Int32 targetUnit) {
    Ark_Float32 result = value * originUnit;

    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_Float32 res"
            + std::to_string(res_num++) + " = GetBasicNodeApi()->convertLengthMetricsUnit("
            + std::to_string(value) + ", " + std::to_string(originUnit) + ", " + std::to_string(targetUnit) + ");\n");
        appendGroupedLog(2, _logData);
    }

    if (!needGroupedLog(1)) {
        return result;
    }

    string out("convertLengthMetricsUnit(");
    WriteToString(&out, value);
    out.append(", ");
    WriteToString(&out, originUnit);
    out.append(", ");
    WriteToString(&out, targetUnit);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

void SetCustomMethodFlag(Ark_NodeHandle node, Ark_Int32 flag) {}
Ark_Int32 GetCustomMethodFlag(Ark_NodeHandle node) {
    return 0;
}

void SetCustomCallback(Ark_VMContext context, Ark_NodeHandle node, Ark_Int32 callback) {}
void SetCustomNodeDestroyCallback(void (*destroy)(Ark_NodeHandle nodeId)) {}

Ark_Int32 MeasureNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32* data) {
    return AsNode(node)->measure(vmContext, data);
}

Ark_Int32 LayoutNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32 (*data)[2]) {
    return AsNode(node)->layout(vmContext, reinterpret_cast<Ark_Float32*>(data));
}

Ark_Int32 DrawNode(Ark_VMContext vmContext, Ark_NodeHandle node, Ark_Float32* data) {
    return AsNode(node)->draw(vmContext, data);
}

Ark_Int32 MeasureLayoutAndDraw(Ark_VMContext vmContext, Ark_NodeHandle root) {
    Ark_Float32 rootMeasures[] = {800, 600, 800, 600};
    MeasureNode(vmContext, root, &rootMeasures[0]);
    Ark_Float32 rootLayouts[] = {0, 0, 800, 600};
    LayoutNode(vmContext, root, reinterpret_cast<Ark_Float32(*)[2]>(&rootLayouts));
    Ark_Float32 rootDraw[] = {0, 0, 800, 600};
    DrawNode(vmContext, root, &rootDraw[0]);
    Ark_Int32 result = 0;
    if (!needGroupedLog(1)) {
        return result;
    }
    string out("measureLayoutAndDraw(");
    WriteToString(&out, root);
    out.append(")");
    appendGroupedLog(1, out);
    return result;
}

void SetAttachNodePtr(Ark_NodeHandle node, void* value) {}
void* GetAttachNodePtr(Ark_NodeHandle node) {
    return nullptr;
}
void SetMeasureWidth(Ark_NodeHandle node, Ark_Int32 value) {}

Ark_Int32 GetMeasureWidth(Ark_NodeHandle node) {
    return 0;
}

void SetMeasureHeight(Ark_NodeHandle node, Ark_Int32 value) {}
Ark_Int32 GetMeasureHeight(Ark_NodeHandle node) {
    return 0;
}
void SetX(Ark_NodeHandle node, Ark_Int32 value) {}
void SetY(Ark_NodeHandle node, Ark_Int32 value) {}
Ark_Int32 GetX(Ark_NodeHandle node) {
    return 0;
}
Ark_Int32 GetY(Ark_NodeHandle node) {
    return 0;
}
void SetAlignment(Ark_NodeHandle node, Ark_Int32 value) {}
Ark_Int32 GetAlignment(Ark_NodeHandle node) {
    return 0;
}
void GetLayoutConstraint(Ark_NodeHandle node, Ark_Int32* value) {}
Ark_Int32 IndexerChecker(Ark_VMContext vmContext, Ark_NodeHandle nodePtr) {
    return 0;
}
void SetRangeUpdater(Ark_NodeHandle nodePtr, Ark_Int32 updaterId) {}
void SetLazyItemIndexer(Ark_VMContext vmContext, Ark_NodeHandle nodePtr, Ark_Int32 indexerId) {}
Ark_PipelineContext GetPipelineContext(Ark_NodeHandle node) {
    return reinterpret_cast<Ark_PipelineContext>(42);
}
void SetVsyncCallback(Ark_PipelineContext pipelineContext, Ark_VsyncCallback callback) {
    using namespace std::chrono_literals;
    auto producer = std::thread([pipelineContext, callback] {
        while (true) {
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
            callback(pipelineContext);
        }
    });
    producer.detach();
}
void SetChildTotalCount(Ark_NodeHandle node, Ark_Int32 totalCount) {}
void ShowCrash(Ark_CharPtr message) {}
}
}

// handWritten implementations
namespace OHOS::Ace::NG::GeneratedModifier {
    namespace CommonMethodModifier {
        void SetOnClick0Impl(Ark_NativePointer node,
            const Opt_Callback_ClickEvent_Void* event)
        {
        RegisterOnClick(node, &event->value);
        if (!needGroupedLog(1)) {
            return;
        }
        string out("onClick(");
        WriteToString(&out, event);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void SetOnClick1Impl(Ark_NativePointer node,
        const Opt_Callback_ClickEvent_Void* event,
        const Opt_Float64* distanceThreshold)
    {
        RegisterOnClick(node, &event->value);
        if (!needGroupedLog(1)) {
            return;
        }
        string out("onClick(");
        WriteToString(&out, event);
        out.append(", ");
        WriteToString(&out, distanceThreshold);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void SetOnClickImpl(Ark_NativePointer node,
        const Callback_ClickEvent_Void* event,
        const Ark_Number* distanceThreshold)
    {
        RegisterOnClick(node, event);
        if (!needGroupedLog(1)) {
            return;
        }
        string out("onClick(");
        WriteToString(&out, event);
        out.append(", ");
        WriteToString(&out, distanceThreshold);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void SetDrawModifierImpl(Ark_NativePointer node,
        const Opt_DrawModifier* value)
    {
        if (value->value) {
            auto frameNode = AsNode(node);
            frameNode->setDrawModifier(value->value);
        }
        if (!needGroupedLog(1)) {
            return;
        }
        string out("drawModifier(");
        WriteToString(&out, value);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    } // CommonMethodModifier

    namespace EnvironmentBackendAccessor {
    Ark_Boolean IsAccessibilityEnabledImpl()
    {
        if (needGroupedLog(1)) {
            string out("isAccessibilityEnabled() \n");
            out.append("[return false] \n");
            appendGroupedLog(1, out);
        }
        return false;
    }
    Ark_ColorMode GetColorModeImpl()
    {
        if (needGroupedLog(1)) {
            string out("getColorMode() \n");
            out.append("[return Ark_ColorMode::ARK_COLOR_MODE_LIGHT] \n");
            appendGroupedLog(1, out);
        }
        return Ark_ColorMode::ARK_COLOR_MODE_LIGHT;
    }
    Ark_Float32 GetFontScaleImpl()
    {
        if (needGroupedLog(1)) {
            string out("getFontScale() \n");
            out.append("[return 1.0] \n");
            appendGroupedLog(1, out);
        }
        return 1.0;
    }
    Ark_Float32 GetFontWeightScaleImpl()
    {
        if (needGroupedLog(1)) {
            string out("getFontWeightScale() \n");
            out.append("[return 1.0] \n");
            appendGroupedLog(1, out);
        }
        return 1.0;
    }
    Ark_LayoutDirection GetLayoutDirectionImpl()
    {
        if (needGroupedLog(1)) {
            string out("getLayoutDirection() \n");
            out.append("[return Ark_LayoutDirection::ARK_LAYOUT_DIRECTION_LTR] \n");
            appendGroupedLog(1, out);
        }
        return Ark_LayoutDirection::ARK_LAYOUT_DIRECTION_LTR;
    }
    Ark_String GetLanguageCodeImpl()
    {
        if (needGroupedLog(1)) {
            string out("getLanguageCode() \n");
            out.append("[return \"en\"] \n");
            appendGroupedLog(1, out);
        }
        return { "en", 2 };
    }
    } // EnvironmentBackendAccessor

    namespace EventEmulatorAccessor {
    void EmitClickEventImpl(Ark_NativePointer node,
        Ark_ClickEvent event)
    {
        auto frameNode = AsNode(node);
        frameNode->callClickEvent(event);
    }
    } // EventEmulatorAccessor
    namespace ScreenshotServiceAccessor {
        Ark_Boolean RequestScreenshotImpl(const Ark_String* target, const Ark_String* name)
        {
            bool xxx = strcmp(name->chars, "XXX") == 0;
            bool yyy = strcmp(name->chars, "YYY") == 0;
            if (xxx || yyy) {
                if (!needGroupedLog(1)) {
                    return strcmp(name->chars, "XXX") == 0;
                }
                std::string out("requestScreenshot() \n");
                out.append("[return true] \n");
                appendGroupedLog(1, out);
                return strcmp(name->chars, "XXX") == 0;
            }
            // golden image comparison
            TGAInfo infoGolden;
            ReadImageTGA(baseGoldenPath + std::string("golden-base"), infoGolden);
            if (strcmp(name->chars, "golden-compare") == 0) {
                return CompareTwoTGA(std::string("golden-base"), infoGolden, infoGolden);
            }
            if (strcmp(name->chars, "golden-diff") == 0) {
                TGAInfo infoTarget;
                CopyTGAHeaders(infoGolden, infoTarget);
                StubTGA(baseBuildPath + std::string("golden-base-snapshot"), infoTarget);
                return CompareTwoTGA(std::string("golden-base"), infoGolden, infoTarget);
            }
            return false;
        }
    } // ScreenshotServiceAccessor
    namespace RenderServiceNodeAccessor {
        Ark_Int32 GetNodeIdImpl(const Ark_String* nodeId)
        {
            if (!needGroupedLog(1)) {
                return 42;
            }
            string out("getNodeId(");
            WriteToString(&out, nodeId);
            out.append(") \n");
            out.append("[return 42] \n");
            appendGroupedLog(1, out);
            return 42;
        }
    } // RenderServiceNodeAccessor
    namespace DrawModifierAccessor {
        void InvalidateImpl(Ark_DrawModifier peer)
        {
            CallDrawModifierCallbacks(peer);
            if (!needGroupedLog(1)) {
                return;
            }
            string out("invalidate(");
            out.append(") \n");
            appendGroupedLog(1, out);
        }
        void SetDrawBehind_callbackImpl(Ark_DrawModifier peer,
            const Callback_DrawContext_Void* drawBehind_callback)
        {
            RegisterDrawModifierCallback(peer, drawBehind_callback, DrawBehind);
            if (!needGroupedLog(1)) {
                return;
            }
            string out("setDrawBehind(");
            WriteToString(&out, drawBehind_callback);
            out.append(") \n");
            appendGroupedLog(1, out);
        }
        void SetDrawContent_callbackImpl(Ark_DrawModifier peer,
            const Callback_DrawContext_Void* drawContent_callback)
        {
            RegisterDrawModifierCallback(peer, drawContent_callback, DrawContent);
            if (!needGroupedLog(1)) {
                return;
            }
            string out("setDrawContent(");
            WriteToString(&out, drawContent_callback);
            out.append(") \n");
            appendGroupedLog(1, out);
        }
        void SetDrawFront_callbackImpl(Ark_DrawModifier peer,
            const Callback_DrawContext_Void* drawFront_callback)
        {
            RegisterDrawModifierCallback(peer, drawFront_callback, DrawFront);
            if (!needGroupedLog(1)) {
                return;
            }
            string out("setDrawFront(");
            WriteToString(&out, drawFront_callback);
            out.append(") \n");
            appendGroupedLog(1, out);
        }
    } // DrawModifierAccessor

    namespace StageExtenderAccessor {
        std::map<Ark_NativePointer, std::function<void()>> enterAnimations;
        std::map<Ark_NativePointer, std::function<void()>> exitAnimations;
        Ark_NativePointer srcNode = nullptr;

        void RunFor(std::function<void(double)> func,
                    unsigned int delay, unsigned int duration, unsigned int granularity)
        {
            std::thread([func, delay, duration, granularity]() {
                if (delay > 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                }

                auto step = std::chrono::milliseconds(duration / granularity);
                int counter = 0;
                double fractionalStep = 1.0 / granularity;
                double lastValue = 0.0;
                auto startTime = std::chrono::steady_clock::now();
                auto x = startTime;

                while (x - startTime < std::chrono::milliseconds(duration)) {
                    lastValue = (counter++) * fractionalStep;
                    func(lastValue);
                    std::this_thread::sleep_until(x);
                    x = std::chrono::steady_clock::now() + step;
                }

                std::this_thread::sleep_until(startTime + std::chrono::milliseconds(duration));

                if (lastValue < 1.0) {
                    func(1.0);
                }
            }).detach();
        }

        void SetSrcPageImpl(Ark_NativePointer node)
        {
            if (!needGroupedLog(1)) {
                return;
            }
            string out("SetSrcPage(");
            WriteToString(&out, node);
            out.append(") \n");
            appendGroupedLog(1, out);
            srcNode = node;
        }
        void PushPageImpl(Ark_NativePointer node)
        {
            if (!needGroupedLog(1)) {
                return;
            }
            string out("PushPage(");
            WriteToString(&out, node);
            out.append(") \n");
            appendGroupedLog(1, out);

            auto enterAnimation = enterAnimations.find(node);
            if (enterAnimation != enterAnimations.end()) {
                enterAnimation->second();
            }

            auto exitAnimation = exitAnimations.find(srcNode);
            if (exitAnimation != exitAnimations.end()) {
                exitAnimation->second();
            }
        }
        void PopPageAndSwitchToImpl(Ark_NativePointer node)
        {
            if (!needGroupedLog(1)) {
                return;
            }
            string out("PopPageAndSwitchTo(");
            WriteToString(&out, node);
            out.append(") \n");
            appendGroupedLog(1, out);

            auto enterAnimation = enterAnimations.find(node);
            if (enterAnimation != enterAnimations.end()) {
                enterAnimation->second();
            }
            auto exitAnimation = exitAnimations.find(srcNode);
            if (exitAnimation != exitAnimations.end()) {
                exitAnimation->second();
            }
        }
        void ResetTransitionsImpl(Ark_NativePointer node)
        {
            if (!needGroupedLog(1)) {
                return;
            }
            string out("ResetTransitions(");
            WriteToString(&out, node);
            out.append(") \n");
            appendGroupedLog(1, out);
            enterAnimations.erase(node);
            exitAnimations.erase(node);
        }
        void SetPageTransitionImpl(Ark_NativePointer node,
            const Ark_TransitionParam* param)
        {
            if (!needGroupedLog(1)) {
                return;
            }
            string out("SetPageTransition(");
            WriteToString(&out, node);
            out.append(", ");
            WriteToString(&out, param);
            out.append(") \n");
            appendGroupedLog(1, out);

            // Early exit if no progress callback
            if (param->onProgress.tag == INTEROP_TAG_UNDEFINED) {
                return;
            }

            auto delay = param->pageTransitionOptions.delay.tag != INTEROP_TAG_UNDEFINED
                ? param->pageTransitionOptions.delay.value.i32
                : 0;
            auto duration = param->pageTransitionOptions.duration.tag != INTEROP_TAG_UNDEFINED
                ? param->pageTransitionOptions.duration.value.i32
                : 0;

            if (duration <= 0) {
                return;
            }

            auto callback = param->onProgress.value;
            auto routeType = param->routeType.tag != INTEROP_TAG_UNDEFINED
                ? param->routeType.value
                : ARK_ROUTE_TYPE_NONE;
            callback.resource.hold(callback.resource.resourceId);

            auto onProgress = [callback, routeType](double progress) {
                if (!callback.call) {
                    return;
                }
                Ark_Number ark_progress = {
                    .tag = INTEROP_TAG_FLOAT32,
                    .f32 = static_cast<InteropFloat32>(progress)
                };
                callback.call(callback.resource.resourceId, routeType, ark_progress);
            };

            unsigned int granularity = 10;
            if (param->pageTransitionType == ARK_PAGE_TRANSITION_TYPE_ENTER) {
                enterAnimations[node] = std::bind(RunFor, onProgress, delay, duration, granularity);
            } else {
                exitAnimations[node] = std::bind(RunFor, onProgress, delay, duration, granularity);
            }
        }
    } // StageExtenderAccessor
}

// end of handWritten implementations
