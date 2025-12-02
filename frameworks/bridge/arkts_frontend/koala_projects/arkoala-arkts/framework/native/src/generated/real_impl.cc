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

#include "Serializers.h"
#include "interop-logging.h"
#include "arkoala-macros.h"
#include "tree.h"
#include "logging.h"
#include "dynamic-loader.h"
#include "interop-utils.h"
#include "arkoala_api_generated.h"

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
    interop_snprintf(hex, sizeof(hex), "0x%llx", (long long)ptr);
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
        GENERATED_Ark_EventCallbackArg args[] = { arg(Ark_APICustomOp::GENERATED_MEASURE), arg(minWidth), arg(minHeight), arg(maxWidth), arg(maxHeight) };
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
        GENERATED_Ark_EventCallbackArg args[] = { arg(Ark_APICustomOp::GENERATED_LAYOUT), arg(0.0f), arg(0.0f), arg(0.0f), arg(0.0f) };
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
        _logData.append("  Ark_NodeHandle peer" + std::to_string(reinterpret_cast<uintptr_t>(result)) + " = GetBasicNodeApi()->createNode(GENERATED_Ark_NodeType("
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

void SetCallbackMethod(GENERATED_Ark_APICallbackMethod* method) {
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
        _logData.append("  Ark_NodeHandle peer" + std::to_string(reinterpret_cast<uintptr_t>(result)) + " = GetBasicNodeApi()->getNodeByViewStack();\n");
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
        _logData.append("  GetBasicNodeApi()->disposeNode(peer" + std::to_string(reinterpret_cast<uintptr_t>(node)) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->dumpTreeNode(peer" + std::to_string(reinterpret_cast<uintptr_t>(node)) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->applyModifierFinish(peer" + std::to_string(reinterpret_cast<uintptr_t>(node)) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->markDirty(peer" + std::to_string(reinterpret_cast<uintptr_t>(node)) + ", " + std::to_string(flag) + ");\n");
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
        _logData.append("  Ark_Float32 res" + std::to_string(res_num++) + " = GetBasicNodeApi()->convertLengthMetricsUnit("
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
        void OnClick0Impl(Ark_NativePointer node,
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
    void OnClick1Impl(Ark_NativePointer node,
                      const Opt_Callback_ClickEvent_Void* event,
                      const Opt_Number* distanceThreshold)
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
    void OnClickImpl(Ark_NativePointer node,
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
    void DrawModifierImpl(Ark_NativePointer node,
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
        if (needGroupedLog(1))
        {
            string out("isAccessibilityEnabled() \n");
            out.append("[return false] \n");
            appendGroupedLog(1, out);
        }
        return false;
    }
    Ark_Int32 GetColorModeImpl()
    {
        if (needGroupedLog(1))
        {
            string out("getColorMode() \n");
            out.append("[return 1] \n");
            appendGroupedLog(1, out);
        }
        return 1;
    }
    Ark_Float32 GetFontScaleImpl()
    {
        if (needGroupedLog(1))
        {
            string out("getFontScale() \n");
            out.append("[return 1.0] \n");
            appendGroupedLog(1, out);
        }
        return 1.0;
    }
    Ark_Float32 GetFontWeightScaleImpl()
    {
        if (needGroupedLog(1))
        {
            string out("getFontWeightScale() \n");
            out.append("[return 1.0] \n");
            appendGroupedLog(1, out);
        }
        return 1.0;
    }
    Ark_String GetLayoutDirectionImpl()
    {
        if (needGroupedLog(1))
        {
            string out("getLayoutDirection() \n");
            out.append("[return \"LTR\"] \n");
            appendGroupedLog(1, out);
        }
        return { "LTR", 3 };
    }
    Ark_String GetLanguageCodeImpl()
    {
        if (needGroupedLog(1))
        {
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
}

// end of handWritten implementations
namespace OHOS::Ace::NG::GeneratedModifier {
    namespace AlphabetIndexerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // AlphabetIndexerModifier
    namespace AlphabetIndexerInterfaceModifier {
    void SetAlphabetIndexerOptionsImpl(Ark_NativePointer node,
                                       const Ark_AlphabetIndexerOptions* options)
    {
    }
    } // AlphabetIndexerInterfaceModifier
    namespace AlphabetIndexerAttributeModifier {
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetPopupColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetPopupBackgroundImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetPopupSelectedColorImpl(Ark_NativePointer node,
                                   const Opt_ResourceColor* value)
    {
    }
    void SetPopupUnselectedColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void SetPopupItemBackgroundColorImpl(Ark_NativePointer node,
                                         const Opt_ResourceColor* value)
    {
    }
    void SetUsingPopupImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetSelectedFontImpl(Ark_NativePointer node,
                             const Opt_Font* value)
    {
    }
    void SetPopupFontImpl(Ark_NativePointer node,
                          const Opt_Font* value)
    {
    }
    void SetPopupItemFontImpl(Ark_NativePointer node,
                              const Opt_Font* value)
    {
    }
    void SetItemSizeImpl(Ark_NativePointer node,
                         const Opt_Union_String_Number* value)
    {
    }
    void SetFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
    {
    }
    void SetOnSelectImpl(Ark_NativePointer node,
                         const Opt_OnAlphabetIndexerSelectCallback* value)
    {
    }
    void SetOnRequestPopupDataImpl(Ark_NativePointer node,
                                   const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
    {
    }
    void SetOnPopupSelectImpl(Ark_NativePointer node,
                              const Opt_OnAlphabetIndexerPopupSelectCallback* value)
    {
    }
    void SetSelectedImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Bindable* value)
    {
    }
    void SetPopupPositionImpl(Ark_NativePointer node,
                              const Opt_Position* value)
    {
    }
    void SetAutoCollapseImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetPopupItemBorderRadiusImpl(Ark_NativePointer node,
                                      const Opt_Number* value)
    {
    }
    void SetItemBorderRadiusImpl(Ark_NativePointer node,
                                 const Opt_Float64* value)
    {
    }
    void SetPopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                         const Opt_BlurStyle* value)
    {
    }
    void SetPopupTitleBackgroundImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetAlignStyleImpl(Ark_NativePointer node,
                           const Opt_IndexerAlign* value,
                           const Opt_Length* offset)
    {
    }
    } // AlphabetIndexerAttributeModifier
    namespace AnimatorModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // AnimatorModifier
    namespace AnimatorInterfaceModifier {
    void SetAnimatorOptionsImpl(Ark_NativePointer node,
                                const Ark_String* value)
    {
    }
    } // AnimatorInterfaceModifier
    namespace AnimatorAttributeModifier {
    void SetStateImpl(Ark_NativePointer node,
                      const Opt_AnimationStatus* value)
    {
    }
    void SetDurationImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void SetCurveImpl(Ark_NativePointer node,
                      const Opt_curves_Curve* value)
    {
    }
    void SetDelayImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void SetFillModeImpl(Ark_NativePointer node,
                         const Opt_FillMode* value)
    {
    }
    void SetIterationsImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void SetPlayModeImpl(Ark_NativePointer node,
                         const Opt_PlayMode* value)
    {
    }
    void SetMotionImpl(Ark_NativePointer node,
                       const Opt_Union_SpringMotion_FrictionMotion_ScrollMotion* value)
    {
    }
    void SetOnStartImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnPauseImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnRepeatImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnCancelImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnFrameImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Void* value)
    {
    }
    } // AnimatorAttributeModifier
    namespace BadgeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // BadgeModifier
    namespace BadgeInterfaceModifier {
    void SetBadgeOptionsImpl(Ark_NativePointer node,
                             const Ark_Union_BadgeParamWithNumber_BadgeParamWithString* value)
    {
    }
    } // BadgeInterfaceModifier
    namespace BaseSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetTextBackgroundStyleImpl(Ark_NativePointer node,
                                    const Opt_TextBackgroundStyle* value)
    {
    }
    void SetBaselineOffsetImpl(Ark_NativePointer node,
                               const Opt_LengthMetrics* value)
    {
    }
    } // BaseSpanModifier
    namespace BlankModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // BlankModifier
    namespace BlankInterfaceModifier {
    void SetBlankOptionsImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* min)
    {
    }
    } // BlankInterfaceModifier
    namespace BlankAttributeModifier {
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
    {
    }
    } // BlankAttributeModifier
    namespace ButtonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ButtonModifier
    namespace ButtonInterfaceModifier {
    void SetButtonOptions0Impl(Ark_NativePointer node,
                               const Ark_ResourceStr* label,
                               const Opt_ButtonOptions* options)
    {
    }
    void SetButtonOptions1Impl(Ark_NativePointer node,
                               const Opt_ButtonOptions* options)
    {
    }
    } // ButtonInterfaceModifier
    namespace ButtonAttributeModifier {
    void SetTypeImpl(Ark_NativePointer node,
                     const Opt_ButtonType* value)
    {
    }
    void SetStateEffectImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetButtonStyleImpl(Ark_NativePointer node,
                            const Opt_ButtonStyleMode* value)
    {
    }
    void SetControlSizeImpl(Ark_NativePointer node,
                            const Opt_ControlSize* value)
    {
    }
    void SetRoleImpl(Ark_NativePointer node,
                     const Opt_ButtonRole* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_Union_String_Resource* value)
    {
    }
    void SetLabelStyleImpl(Ark_NativePointer node,
                           const Opt_ButtonLabelStyle* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    } // ButtonAttributeModifier
    namespace CalendarPickerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CalendarPickerModifier
    namespace CalendarPickerInterfaceModifier {
    void SetCalendarPickerOptionsImpl(Ark_NativePointer node,
                                      const Opt_CalendarOptions* options)
    {
    }
    } // CalendarPickerInterfaceModifier
    namespace CalendarPickerAttributeModifier {
    void SetTextStyleImpl(Ark_NativePointer node,
                          const Opt_PickerTextStyle* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Date_Void* value)
    {
    }
    void SetMarkTodayImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetEdgeAlignImpl(Ark_NativePointer node,
                          const Opt_CalendarAlign* alignType,
                          const Opt_Offset* offset)
    {
    }
    } // CalendarPickerAttributeModifier
    namespace CanvasModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CanvasModifier
    namespace CanvasInterfaceModifier {
    void SetCanvasOptionsImpl(Ark_NativePointer node,
                              const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context,
                              const Opt_ImageAIOptions* imageAIOptions)
    {
    }
    } // CanvasInterfaceModifier
    namespace CanvasAttributeModifier {
    void SetOnReadyImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void SetEnableAnalyzerImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    } // CanvasAttributeModifier
    namespace CheckboxModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CheckboxModifier
    namespace CheckboxInterfaceModifier {
    void SetCheckboxOptionsImpl(Ark_NativePointer node,
                                const Opt_CheckboxOptions* options)
    {
    }
    } // CheckboxInterfaceModifier
    namespace CheckboxAttributeModifier {
    void SetSelectImpl(Ark_NativePointer node,
                       const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetShapeImpl(Ark_NativePointer node,
                      const Opt_CheckBoxShape* value)
    {
    }
    void SetUnselectedColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetMarkImpl(Ark_NativePointer node,
                     const Opt_MarkStyle* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnCheckboxChangeCallback* value)
    {
    }
    } // CheckboxAttributeModifier
    namespace CheckboxGroupModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CheckboxGroupModifier
    namespace CheckboxGroupInterfaceModifier {
    void SetCheckboxGroupOptionsImpl(Ark_NativePointer node,
                                     const Opt_CheckboxGroupOptions* options)
    {
    }
    } // CheckboxGroupInterfaceModifier
    namespace CheckboxGroupAttributeModifier {
    void SetSelectAllImpl(Ark_NativePointer node,
                          const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetUnselectedColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetMarkImpl(Ark_NativePointer node,
                     const Opt_MarkStyle* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnCheckboxGroupChangeCallback* value)
    {
    }
    void SetCheckboxShapeImpl(Ark_NativePointer node,
                              const Opt_CheckBoxShape* value)
    {
    }
    } // CheckboxGroupAttributeModifier
    namespace CircleModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CircleModifier
    namespace CircleInterfaceModifier {
    void SetCircleOptionsImpl(Ark_NativePointer node,
                              const Opt_CircleOptions* options)
    {
    }
    } // CircleInterfaceModifier
    namespace ColumnModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ColumnModifier
    namespace ColumnInterfaceModifier {
    void SetColumnOptionsImpl(Ark_NativePointer node,
                              const Opt_Union_ColumnOptions_ColumnOptionsV2* options)
    {
    }
    } // ColumnInterfaceModifier
    namespace ColumnAttributeModifier {
    void SetAlignItemsImpl(Ark_NativePointer node,
                           const Opt_HorizontalAlign* value)
    {
    }
    void SetJustifyContentImpl(Ark_NativePointer node,
                               const Opt_FlexAlign* value)
    {
    }
    void SetReverseImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    } // ColumnAttributeModifier
    namespace ColumnSplitModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ColumnSplitModifier
    namespace ColumnSplitInterfaceModifier {
    void SetColumnSplitOptionsImpl(Ark_NativePointer node)
    {
    }
    } // ColumnSplitInterfaceModifier
    namespace ColumnSplitAttributeModifier {
    void SetResizeableImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_ColumnSplitDividerStyle* value)
    {
    }
    } // ColumnSplitAttributeModifier
    namespace CommonMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetWidthImpl(Ark_NativePointer node,
                      const Opt_Union_Length_LayoutPolicy* value)
    {
    }
    void SetHeightImpl(Ark_NativePointer node,
                       const Opt_Union_Length_LayoutPolicy* value)
    {
    }
    void SetResponseRegionImpl(Ark_NativePointer node,
                               const Opt_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void SetMouseResponseRegionImpl(Ark_NativePointer node,
                                    const Opt_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void SetResponseRegionListImpl(Ark_NativePointer node,
                                   const Opt_Array_ResponseRegion* value)
    {
    }
    void SetSizeImpl(Ark_NativePointer node,
                     const Opt_SizeOptions* value)
    {
    }
    void SetConstraintSizeImpl(Ark_NativePointer node,
                               const Opt_ConstraintSizeOptions* value)
    {
    }
    void SetHitTestBehaviorImpl(Ark_NativePointer node,
                                const Opt_HitTestMode* value)
    {
    }
    void SetOnChildTouchTestImpl(Ark_NativePointer node,
                                 const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
    {
    }
    void SetLayoutWeightImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
    {
    }
    void SetChainWeightImpl(Ark_NativePointer node,
                            const Opt_ChainWeightOptions* value)
    {
    }
    void SetPaddingImpl(Ark_NativePointer node,
                        const Opt_Union_Padding_Length_LocalizedPadding* value)
    {
    }
    void SetSafeAreaPaddingImpl(Ark_NativePointer node,
                                const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
    {
    }
    void SetMarginImpl(Ark_NativePointer node,
                       const Opt_Union_Margin_Length_LocalizedMargin* value)
    {
    }
    void SetBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_Union_ResourceColor_ColorMetrics* value)
    {
    }
    void SetPixelRoundImpl(Ark_NativePointer node,
                           const Opt_PixelRoundPolicy* value)
    {
    }
    void SetBackgroundImageSizeImpl(Ark_NativePointer node,
                                    const Opt_Union_SizeOptions_ImageSize* value)
    {
    }
    void SetBackgroundImagePositionImpl(Ark_NativePointer node,
                                        const Opt_Union_Position_Alignment* value)
    {
    }
    void SetBackgroundEffect0Impl(Ark_NativePointer node,
                                  const Opt_BackgroundEffectOptions* value)
    {
    }
    void SetBackgroundImageResizableImpl(Ark_NativePointer node,
                                         const Opt_ResizableOptions* value)
    {
    }
    void SetForegroundEffectImpl(Ark_NativePointer node,
                                 const Opt_ForegroundEffectOptions* value)
    {
    }
    void SetVisualEffectImpl(Ark_NativePointer node,
                             const Opt_uiEffect_VisualEffect* value)
    {
    }
    void SetBackgroundFilterImpl(Ark_NativePointer node,
                                 const Opt_uiEffect_Filter* value)
    {
    }
    void SetForegroundFilterImpl(Ark_NativePointer node,
                                 const Opt_uiEffect_Filter* value)
    {
    }
    void SetCompositingFilterImpl(Ark_NativePointer node,
                                  const Opt_uiEffect_Filter* value)
    {
    }
    void SetOpacityImpl(Ark_NativePointer node,
                        const Opt_Union_F64_Resource* value)
    {
    }
    void SetBorderImpl(Ark_NativePointer node,
                       const Opt_BorderOptions* value)
    {
    }
    void SetBorderStyleImpl(Ark_NativePointer node,
                            const Opt_Union_BorderStyle_EdgeStyles* value)
    {
    }
    void SetBorderWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
    {
    }
    void SetBorderColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void SetBorderRadius0Impl(Ark_NativePointer node,
                             const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
    {
    }
    void SetBorderImageImpl(Ark_NativePointer node,
                            const Opt_BorderImageOption* value)
    {
    }
    void SetOutlineImpl(Ark_NativePointer node,
                        const Opt_OutlineOptions* value)
    {
    }
    void SetOutlineStyleImpl(Ark_NativePointer node,
                             const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
    {
    }
    void SetOutlineWidthImpl(Ark_NativePointer node,
                             const Opt_Union_Dimension_EdgeOutlineWidths* value)
    {
    }
    void SetOutlineColorImpl(Ark_NativePointer node,
                             const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void SetOutlineRadiusImpl(Ark_NativePointer node,
                              const Opt_Union_Dimension_OutlineRadiuses* value)
    {
    }
    void SetForegroundColorImpl(Ark_NativePointer node,
                                const Opt_Union_ResourceColor_ColoringStrategy* value)
    {
    }
    void SetOnClick0Impl(Ark_NativePointer node,
                         const Opt_Callback_ClickEvent_Void* value)
    {
    }
    void SetOnHoverImpl(Ark_NativePointer node,
                        const Opt_Callback_Boolean_HoverEvent_Void* value)
    {
    }
    void SetOnHoverMoveImpl(Ark_NativePointer node,
                            const Opt_Callback_HoverEvent_Void* value)
    {
    }
    void SetOnAccessibilityHoverImpl(Ark_NativePointer node,
                                     const Opt_AccessibilityCallback* value)
    {
    }
    void SetOnAccessibilityHoverTransparentImpl(Ark_NativePointer node,
                                                const Opt_AccessibilityTransparentCallback* value)
    {
    }
    void SetHoverEffectImpl(Ark_NativePointer node,
                            const Opt_HoverEffect* value)
    {
    }
    void SetOnMouseImpl(Ark_NativePointer node,
                        const Opt_Callback_MouseEvent_Void* value)
    {
    }
    void SetOnTouchImpl(Ark_NativePointer node,
                        const Opt_Callback_TouchEvent_Void* value)
    {
    }
    void SetOnKeyEventImpl(Ark_NativePointer node,
                           const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void SetOnDigitalCrownImpl(Ark_NativePointer node,
                               const Opt_Callback_CrownEvent_Void* value)
    {
    }
    void SetOnKeyPreImeImpl(Ark_NativePointer node,
                            const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void SetOnKeyEventDispatchImpl(Ark_NativePointer node,
                                   const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void SetOnFocusAxisEventImpl(Ark_NativePointer node,
                                 const Opt_Callback_FocusAxisEvent_Void* value)
    {
    }
    void SetOnAxisEventImpl(Ark_NativePointer node,
                            const Opt_Callback_AxisEvent_Void* value)
    {
    }
    void SetFocusableImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetNextFocusImpl(Ark_NativePointer node,
                          const Opt_FocusMovement* value)
    {
    }
    void SetTabStopImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SetOnFocusImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnBlurImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
    {
    }
    void SetTabIndexImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetDefaultFocusImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetGroupDefaultFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetFocusOnTouchImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetFocusBoxImpl(Ark_NativePointer node,
                         const Opt_FocusBoxStyle* value)
    {
    }
    void SetAnimationImpl(Ark_NativePointer node,
                          const Opt_AnimateParam* value)
    {
    }
    void SetTransition0Impl(Ark_NativePointer node,
                            const Opt_TransitionEffect* value)
    {
    }
    void SetMotionBlurImpl(Ark_NativePointer node,
                           const Opt_MotionBlurOptions* value)
    {
    }
    void SetBrightnessImpl(Ark_NativePointer node,
                           const Opt_Float64* value)
    {
    }
    void SetContrastImpl(Ark_NativePointer node,
                         const Opt_Float64* value)
    {
    }
    void SetGrayscaleImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
    {
    }
    void SetColorBlendImpl(Ark_NativePointer node,
                           const Opt_Union_Color_String_Resource* value)
    {
    }
    void SetSaturateImpl(Ark_NativePointer node,
                         const Opt_Float64* value)
    {
    }
    void SetSepiaImpl(Ark_NativePointer node,
                      const Opt_Float64* value)
    {
    }
    void SetInvertImpl(Ark_NativePointer node,
                       const Opt_Union_F64_InvertOptions* value)
    {
    }
    void SetHueRotateImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String* value)
    {
    }
    void SetUseShadowBatchingImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetUseEffect0Impl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetRenderGroupImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetFreezeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void SetTranslateImpl(Ark_NativePointer node,
                          const Opt_TranslateOptions* value)
    {
    }
    void SetScaleImpl(Ark_NativePointer node,
                      const Opt_ScaleOptions* value)
    {
    }
    void SetRotateImpl(Ark_NativePointer node,
                       const Opt_Union_RotateOptions_RotateAngleOptions* value)
    {
    }
    void SetTransformImpl(Ark_NativePointer node,
                          const Opt_matrix4_Matrix4Transit* value)
    {
    }
    void SetTransform3DImpl(Ark_NativePointer node,
                            const Opt_matrix4_Matrix4Transit* value)
    {
    }
    void SetOnAppearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnDisAppearImpl(Ark_NativePointer node,
                            const Opt_Callback_Void* value)
    {
    }
    void SetOnAttachImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* value)
    {
    }
    void SetOnDetachImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* value)
    {
    }
    void SetOnAreaChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Area_Area_Void* value)
    {
    }
    void SetVisibilityImpl(Ark_NativePointer node,
                           const Opt_Visibility* value)
    {
    }
    void SetFlexGrowImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void SetFlexShrinkImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void SetFlexBasisImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
    {
    }
    void SetAlignSelfImpl(Ark_NativePointer node,
                          const Opt_ItemAlign* value)
    {
    }
    void SetLayoutGravityImpl(Ark_NativePointer node,
                              const Opt_LocalizedAlignment* value)
    {
    }
    void SetDisplayPriorityImpl(Ark_NativePointer node,
                                const Opt_Number* value)
    {
    }
    void SetZIndexImpl(Ark_NativePointer node,
                       const Opt_Int32* value)
    {
    }
    void SetDirectionImpl(Ark_NativePointer node,
                          const Opt_Direction* value)
    {
    }
    void SetAlignImpl(Ark_NativePointer node,
                      const Opt_Union_Alignment_LocalizedAlignment* value)
    {
    }
    void SetPositionImpl(Ark_NativePointer node,
                         const Opt_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void SetMarkAnchorImpl(Ark_NativePointer node,
                           const Opt_Union_Position_LocalizedPosition* value)
    {
    }
    void SetOffsetImpl(Ark_NativePointer node,
                       const Opt_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void SetEnabledImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SetAlignRulesImpl(Ark_NativePointer node,
                           const Opt_Union_AlignRuleOption_LocalizedAlignRuleOptions* value)
    {
    }
    void SetAspectRatioImpl(Ark_NativePointer node,
                            const Opt_Number* value)
    {
    }
    void SetClickEffectImpl(Ark_NativePointer node,
                            const Opt_ClickEffect* value)
    {
    }
    void SetOnDragStartImpl(Ark_NativePointer node,
                            const Opt_Type_CommonMethod_onDragStart* value)
    {
    }
    void SetOnDragEnterImpl(Ark_NativePointer node,
                            const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void SetOnDragMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void SetOnDragLeaveImpl(Ark_NativePointer node,
                            const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void SetOnDrop0Impl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void SetOnDragEndImpl(Ark_NativePointer node,
                          const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void SetDraggableImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetDragPreview0Impl(Ark_NativePointer node,
                             const Opt_Union_CustomBuilder_DragItemInfo_String* value)
    {
    }
    void SetOnPreDragImpl(Ark_NativePointer node,
                          const Opt_Callback_PreDragStatus_Void* value)
    {
    }
    void SetLinearGradientImpl(Ark_NativePointer node,
                               const Opt_LinearGradientOptions* value)
    {
    }
    void SetSweepGradientImpl(Ark_NativePointer node,
                              const Opt_SweepGradientOptions* value)
    {
    }
    void SetRadialGradientImpl(Ark_NativePointer node,
                               const Opt_RadialGradientOptions* value)
    {
    }
    void SetMotionPathImpl(Ark_NativePointer node,
                           const Opt_MotionPathOptions* value)
    {
    }
    void SetShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_ShadowStyle* value)
    {
    }
    void SetClipImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void SetClipShapeImpl(Ark_NativePointer node,
                          const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void SetMaskImpl(Ark_NativePointer node,
                     const Opt_ProgressMask* value)
    {
    }
    void SetMaskShapeImpl(Ark_NativePointer node,
                          const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void SetKeyImpl(Ark_NativePointer node,
                    const Opt_String* value)
    {
    }
    void SetIdImpl(Ark_NativePointer node,
                   const Opt_String* value)
    {
    }
    void SetGeometryTransition0Impl(Ark_NativePointer node,
                                    const Opt_String* value)
    {
    }
    void SetRestoreIdImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
    {
    }
    void SetSphericalEffectImpl(Ark_NativePointer node,
                                const Opt_Float64* value)
    {
    }
    void SetLightUpEffectImpl(Ark_NativePointer node,
                              const Opt_Float64* value)
    {
    }
    void SetPixelStretchEffectImpl(Ark_NativePointer node,
                                   const Opt_PixelStretchEffectOptions* value)
    {
    }
    void SetAccessibilityGroupWithValueImpl(Ark_NativePointer node,
                                            const Opt_Boolean* value)
    {
    }
    void SetAccessibilityTextOfStringTypeImpl(Ark_NativePointer node,
                                              const Opt_String* value)
    {
    }
    void SetAccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                         const Opt_String* value)
    {
    }
    void SetAccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void SetAccessibilityUseSamePageImpl(Ark_NativePointer node,
                                         const Opt_AccessibilitySamePageMode* value)
    {
    }
    void SetAccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                               const Opt_Boolean* value)
    {
    }
    void SetAccessibilityTextOfResourceTypeImpl(Ark_NativePointer node,
                                                const Opt_Resource* value)
    {
    }
    void SetAccessibilityRoleImpl(Ark_NativePointer node,
                                  const Opt_AccessibilityRoleType* value)
    {
    }
    void SetOnAccessibilityFocusImpl(Ark_NativePointer node,
                                     const Opt_AccessibilityFocusCallback* value)
    {
    }
    void SetOnAccessibilityActionInterceptImpl(Ark_NativePointer node,
                                               const Opt_AccessibilityActionInterceptCallback* value)
    {
    }
    void SetAccessibilityTextHintImpl(Ark_NativePointer node,
                                      const Opt_String* value)
    {
    }
    void SetAccessibilityDescriptionOfStringTypeImpl(Ark_NativePointer node,
                                                     const Opt_String* value)
    {
    }
    void SetAccessibilityDescriptionOfResourceTypeImpl(Ark_NativePointer node,
                                                       const Opt_Resource* value)
    {
    }
    void SetAccessibilityLevelImpl(Ark_NativePointer node,
                                   const Opt_String* value)
    {
    }
    void SetAccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                         const Opt_CustomNodeBuilder* value)
    {
    }
    void SetAccessibilityCheckedImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetAccessibilitySelectedImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetObscuredImpl(Ark_NativePointer node,
                         const Opt_Array_ObscuredReasons* value)
    {
    }
    void SetReuseIdImpl(Ark_NativePointer node,
                        const Opt_String* value)
    {
    }
    void SetReuseImpl(Ark_NativePointer node,
                      const Opt_ReuseOptions* value)
    {
    }
    void SetRenderFitImpl(Ark_NativePointer node,
                          const Opt_RenderFit* value)
    {
    }
    void SetBackgroundBrightnessImpl(Ark_NativePointer node,
                                     const Opt_BackgroundBrightnessOptions* value)
    {
    }
    void SetOnGestureJudgeBeginImpl(Ark_NativePointer node,
                                    const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
    {
    }
    void SetOnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                               const Opt_GestureRecognizerJudgeBeginCallback* value)
    {
    }
    void SetShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                                    const Opt_ShouldBuiltInRecognizerParallelWithCallback* value)
    {
    }
    void SetMonopolizeEventsImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetOnTouchInterceptImpl(Ark_NativePointer node,
                                 const Opt_Callback_TouchEvent_HitTestMode* value)
    {
    }
    void SetOnSizeChangeImpl(Ark_NativePointer node,
                             const Opt_SizeChangeCallback* value)
    {
    }
    void SetAccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                            const Opt_FocusDrawLevel* value)
    {
    }
    void SetExpandSafeAreaImpl(Ark_NativePointer node,
                               const Opt_Array_SafeAreaType* types,
                               const Opt_Array_SafeAreaEdge* edges)
    {
    }
    void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                     const Opt_Array_LayoutSafeAreaType* types,
                                     const Opt_Array_LayoutSafeAreaEdge* edges)
    {
    }
    void SetBackgroundImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* builder,
                           const Opt_BackgroundOptions* options)
    {
    }
    void SetBackgroundImage0Impl(Ark_NativePointer node,
                                 const Opt_Union_ResourceStr_PixelMap* value)
    {
    }
    void SetBackgroundImage1Impl(Ark_NativePointer node,
                                 const Opt_Union_ResourceStr_PixelMap* src,
                                 const Opt_BackgroundImageOptions* options)
    {
    }
    void SetBackgroundImage2Impl(Ark_NativePointer node,
                                 const Opt_Union_ResourceStr_PixelMap* src,
                                 const Opt_ImageRepeat* repeat)
    {
    }
    void SetBackgroundBlurStyleImpl(Ark_NativePointer node,
                                    const Opt_BlurStyle* style,
                                    const Opt_BackgroundBlurStyleOptions* options,
                                    const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SetBackgroundEffect1Impl(Ark_NativePointer node,
                                  const Opt_BackgroundEffectOptions* options,
                                  const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SetForegroundBlurStyleImpl(Ark_NativePointer node,
                                    const Opt_BlurStyle* style,
                                    const Opt_ForegroundBlurStyleOptions* options,
                                    const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SetBorderRadius1Impl(Ark_NativePointer node,
                              const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value,
                              const Opt_RenderStrategy* type)
    {
    }
    void SetOnClick1Impl(Ark_NativePointer node,
                         const Opt_Callback_ClickEvent_Void* event,
                         const Opt_Float64* distanceThreshold)
    {
    }
    void SetFocusScopeIdImpl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_Boolean* isGroup,
                             const Opt_Boolean* arrowStepOut)
    {
    }
    void SetFocusScopePriorityImpl(Ark_NativePointer node,
                                   const Opt_String* scopeId,
                                   const Opt_FocusPriority* priority)
    {
    }
    void SetTransition1Impl(Ark_NativePointer node,
                            const Opt_TransitionEffect* effect,
                            const Opt_TransitionFinishCallback* onFinish)
    {
    }
    void SetGestureImpl(Ark_NativePointer node,
                        const Opt_GestureType* gesture,
                        const Opt_GestureMask* mask)
    {
    }
    void SetPriorityGestureImpl(Ark_NativePointer node,
                                const Opt_GestureType* gesture,
                                const Opt_GestureMask* mask)
    {
    }
    void SetParallelGestureImpl(Ark_NativePointer node,
                                const Opt_GestureType* gesture,
                                const Opt_GestureMask* mask)
    {
    }
    void SetBlurImpl(Ark_NativePointer node,
                     const Opt_Float64* blurRadius,
                     const Opt_BlurOptions* options,
                     const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SetLinearGradientBlurImpl(Ark_NativePointer node,
                                   const Opt_Float64* value,
                                   const Opt_LinearGradientBlurOptions* options)
    {
    }
    void SetSystemBarEffectImpl(Ark_NativePointer node)
    {
    }
    void SetUseEffect1Impl(Ark_NativePointer node,
                           const Opt_Boolean* useEffect,
                           const Opt_EffectType* effectType)
    {
    }
    void SetBackdropBlurImpl(Ark_NativePointer node,
                             const Opt_Float64* radius,
                             const Opt_BlurOptions* options,
                             const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SetSharedTransitionImpl(Ark_NativePointer node,
                                 const Opt_String* id,
                                 const Opt_sharedTransitionOptions* options)
    {
    }
    void SetChainModeImpl(Ark_NativePointer node,
                          const Opt_Axis* direction,
                          const Opt_ChainStyle* style)
    {
    }
    void SetOnDrop1Impl(Ark_NativePointer node,
                        const Opt_OnDragEventCallback* eventCallback,
                        const Opt_DropOptions* dropOptions)
    {
    }
    void SetDragPreview1Impl(Ark_NativePointer node,
                             const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                             const Opt_PreviewConfiguration* config)
    {
    }
    void SetOverlayImpl(Ark_NativePointer node,
                        const Opt_Union_String_CustomBuilder_ComponentContent* value,
                        const Opt_OverlayOptions* options)
    {
    }
    void SetBlendModeImpl(Ark_NativePointer node,
                          const Opt_BlendMode* value,
                          const Opt_BlendApplyType* type)
    {
    }
    void SetAdvancedBlendModeImpl(Ark_NativePointer node,
                                  const Ark_Union_BlendMode_Blender* effect,
                                  const Opt_BlendApplyType* type)
    {
    }
    void SetGeometryTransition1Impl(Ark_NativePointer node,
                                    const Opt_String* id,
                                    const Opt_GeometryTransitionOptions* options)
    {
    }
    void SetBindTipsImpl(Ark_NativePointer node,
                         const Opt_TipsMessageType* message,
                         const Opt_TipsOptions* options)
    {
    }
    void SetBindPopupImpl(Ark_NativePointer node,
                          const Opt_Boolean* show,
                          const Opt_Union_PopupOptions_CustomPopupOptions* popup)
    {
    }
    void SetBindMenu0Impl(Ark_NativePointer node,
                          const Opt_Union_Array_MenuElement_CustomBuilder* content,
                          const Opt_MenuOptions* options)
    {
    }
    void SetBindMenu1Impl(Ark_NativePointer node,
                          const Opt_Boolean* isShow,
                          const Opt_Union_Array_MenuElement_CustomBuilder* content,
                          const Opt_MenuOptions* options)
    {
    }
    void SetBindContextMenu0Impl(Ark_NativePointer node,
                                 const Opt_CustomNodeBuilder* content,
                                 const Opt_ResponseType* responseType,
                                 const Opt_ContextMenuOptions* options)
    {
    }
    void SetBindContextMenu1Impl(Ark_NativePointer node,
                                 const Opt_Boolean* isShown,
                                 const Opt_CustomNodeBuilder* content,
                                 const Opt_ContextMenuOptions* options)
    {
    }
    void SetBindContentCover0Impl(Ark_NativePointer node,
                                  const Opt_Union_Boolean_Bindable* isShow,
                                  const Opt_CustomNodeBuilder* builder,
                                  const Opt_ModalTransition* type)
    {
    }
    void SetBindContentCover1Impl(Ark_NativePointer node,
                                  const Opt_Union_Boolean_Bindable* isShow,
                                  const Opt_CustomNodeBuilder* builder,
                                  const Opt_ContentCoverOptions* options)
    {
    }
    void SetBindSheetImpl(Ark_NativePointer node,
                          const Opt_Union_Boolean_Bindable* isShow,
                          const Opt_CustomNodeBuilder* builder,
                          const Opt_SheetOptions* options)
    {
    }
    void SetOnVisibleAreaChangeImpl(Ark_NativePointer node,
                                    const Opt_Array_Float64* ratios,
                                    const Opt_VisibleAreaChangeCallback* event)
    {
    }
    void SetOnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                               const Opt_VisibleAreaEventOptions* options,
                                               const Opt_VisibleAreaChangeCallback* event)
    {
    }
    void SetKeyboardShortcutImpl(Ark_NativePointer node,
                                 const Opt_Union_String_FunctionKey* value,
                                 const Opt_Array_ModifierKey* keys,
                                 const Opt_Callback_Void* action)
    {
    }
    void SetAccessibilityGroupWithConfigImpl(Ark_NativePointer node,
                                             const Opt_Boolean* isGroup,
                                             const Opt_AccessibilityOptions* config)
    {
    }
    void SetOnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                               const Opt_GestureRecognizerJudgeBeginCallback* callback_,
                                               const Opt_Boolean* exposeInnerGesture)
    {
    }
    } // CommonMethodModifier
    namespace CommonShapeMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetStrokeImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void SetFillImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
    {
    }
    void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                                 const Opt_Union_Number_String* value)
    {
    }
    void SetStrokeLineCapImpl(Ark_NativePointer node,
                              const Opt_LineCapStyle* value)
    {
    }
    void SetStrokeLineJoinImpl(Ark_NativePointer node,
                               const Opt_LineJoinStyle* value)
    {
    }
    void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                                 const Opt_Union_Number_String* value)
    {
    }
    void SetStrokeOpacityImpl(Ark_NativePointer node,
                              const Opt_Union_Number_String_Resource* value)
    {
    }
    void SetFillOpacityImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String_Resource* value)
    {
    }
    void SetStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Length* value)
    {
    }
    void SetAntiAliasImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetStrokeDashArrayImpl(Ark_NativePointer node,
                                const Opt_Array_Length* value)
    {
    }
    } // CommonShapeMethodModifier
    namespace Component3DModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // Component3DModifier
    namespace Component3DInterfaceModifier {
    void SetComponent3DOptionsImpl(Ark_NativePointer node,
                                   const Opt_SceneOptions* sceneOptions)
    {
    }
    } // Component3DInterfaceModifier
    namespace Component3DAttributeModifier {
    void SetEnvironmentImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value)
    {
    }
    void SetShaderImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
    {
    }
    void SetShaderImageTextureImpl(Ark_NativePointer node,
                                   const Opt_ResourceStr* value)
    {
    }
    void SetShaderInputBufferImpl(Ark_NativePointer node,
                                  const Opt_Array_Number* value)
    {
    }
    void SetRenderWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
    {
    }
    void SetRenderHeightImpl(Ark_NativePointer node,
                             const Opt_Dimension* value)
    {
    }
    void SetCustomRenderImpl(Ark_NativePointer node,
                             const Opt_ResourceStr* uri,
                             const Opt_Boolean* selfRenderUpdate)
    {
    }
    } // Component3DAttributeModifier
    namespace ComponentRootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ComponentRootModifier
    namespace ContainerSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ContainerSpanModifier
    namespace ContainerSpanInterfaceModifier {
    void SetContainerSpanOptionsImpl(Ark_NativePointer node)
    {
    }
    } // ContainerSpanInterfaceModifier
    namespace ContainerSpanAttributeModifier {
    void SetTextBackgroundStyleImpl(Ark_NativePointer node,
                                    const Opt_TextBackgroundStyle* value)
    {
    }
    } // ContainerSpanAttributeModifier
    namespace CounterModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CounterModifier
    namespace CounterInterfaceModifier {
    void SetCounterOptionsImpl(Ark_NativePointer node)
    {
    }
    } // CounterInterfaceModifier
    namespace CounterAttributeModifier {
    void SetOnIncImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
    {
    }
    void SetOnDecImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
    {
    }
    void SetEnableDecImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetEnableIncImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    } // CounterAttributeModifier
    namespace CustomBuilderRootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CustomBuilderRootModifier
    namespace CustomLayoutRootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetSubscribeOnMeasureSizeImpl(Ark_NativePointer node,
                                       const Callback_onMeasureSize_SizeResult* value)
    {
    }
    void SetSubscribeOnPlaceChildrenImpl(Ark_NativePointer node,
                                         const Callback_onPlaceChildren_Void* value)
    {
    }
    } // CustomLayoutRootModifier
    namespace DataPanelModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // DataPanelModifier
    namespace DataPanelInterfaceModifier {
    void SetDataPanelOptionsImpl(Ark_NativePointer node,
                                 const Ark_DataPanelOptions* options)
    {
    }
    } // DataPanelInterfaceModifier
    namespace DataPanelAttributeModifier {
    void SetCloseEffectImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetValueColorsImpl(Ark_NativePointer node,
                            const Opt_Array_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SetTrackBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void SetStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Length* value)
    {
    }
    void SetTrackShadowImpl(Ark_NativePointer node,
                            const Opt_DataPanelShadowOptions* value)
    {
    }
    } // DataPanelAttributeModifier
    namespace DatePickerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // DatePickerModifier
    namespace DatePickerInterfaceModifier {
    void SetDatePickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_DatePickerOptions* options)
    {
    }
    } // DatePickerInterfaceModifier
    namespace DatePickerAttributeModifier {
    void SetLunarImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void SetDisappearTextStyleImpl(Ark_NativePointer node,
                                   const Opt_PickerTextStyle* value)
    {
    }
    void SetTextStyleImpl(Ark_NativePointer node,
                          const Opt_PickerTextStyle* value)
    {
    }
    void SetSelectedTextStyleImpl(Ark_NativePointer node,
                                  const Opt_PickerTextStyle* value)
    {
    }
    void SetOnDateChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Date_Void* value)
    {
    }
    void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                        const Opt_CrownSensitivity* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    } // DatePickerAttributeModifier
    namespace DividerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // DividerModifier
    namespace DividerInterfaceModifier {
    void SetDividerOptionsImpl(Ark_NativePointer node)
    {
    }
    } // DividerInterfaceModifier
    namespace DividerAttributeModifier {
    void SetVerticalImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
    {
    }
    void SetStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String* value)
    {
    }
    void SetLineCapImpl(Ark_NativePointer node,
                        const Opt_LineCapStyle* value)
    {
    }
    } // DividerAttributeModifier
    namespace EffectComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // EffectComponentModifier
    namespace EffectComponentInterfaceModifier {
    void SetEffectComponentOptionsImpl(Ark_NativePointer node)
    {
    }
    } // EffectComponentInterfaceModifier
    namespace EllipseModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // EllipseModifier
    namespace EllipseInterfaceModifier {
    void SetEllipseOptionsImpl(Ark_NativePointer node,
                               const Opt_EllipseOptions* options)
    {
    }
    } // EllipseInterfaceModifier
    namespace EmbeddedComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // EmbeddedComponentModifier
    namespace EmbeddedComponentInterfaceModifier {
    void SetEmbeddedComponentOptionsImpl(Ark_NativePointer node,
                                         Ark_Want loader,
                                         const Opt_EmbeddedType* type)
    {
    }
    } // EmbeddedComponentInterfaceModifier
    namespace EmbeddedComponentAttributeModifier {
    void SetOnTerminatedImpl(Ark_NativePointer node,
                             const Opt_Callback_TerminationInfo_Void* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_ErrorCallback_Ohos_Base_BusinessError* value)
    {
    }
    } // EmbeddedComponentAttributeModifier
    namespace FlexModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // FlexModifier
    namespace FlexInterfaceModifier {
    void SetFlexOptionsImpl(Ark_NativePointer node,
                            const Opt_FlexOptions* value)
    {
    }
    } // FlexInterfaceModifier
    namespace FlowItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // FlowItemModifier
    namespace FlowItemInterfaceModifier {
    void SetFlowItemOptionsImpl(Ark_NativePointer node)
    {
    }
    } // FlowItemInterfaceModifier
    namespace FolderStackModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // FolderStackModifier
    namespace FolderStackInterfaceModifier {
    void SetFolderStackOptionsImpl(Ark_NativePointer node,
                                   const Opt_FolderStackOptions* options)
    {
    }
    } // FolderStackInterfaceModifier
    namespace FolderStackAttributeModifier {
    void SetAlignContentImpl(Ark_NativePointer node,
                             const Opt_Alignment* value)
    {
    }
    void SetOnFolderStateChangeImpl(Ark_NativePointer node,
                                    const Opt_OnFoldStatusChangeCallback* value)
    {
    }
    void SetOnHoverStatusChangeImpl(Ark_NativePointer node,
                                    const Opt_OnHoverStatusChangeCallback* value)
    {
    }
    void SetEnableAnimationImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetAutoHalfFoldImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    } // FolderStackAttributeModifier
    namespace FormComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // FormComponentModifier
    namespace FormComponentInterfaceModifier {
    void SetFormComponentOptionsImpl(Ark_NativePointer node,
                                     const Ark_FormInfo* value)
    {
    }
    } // FormComponentInterfaceModifier
    namespace FormComponentAttributeModifier {
    void SetSizeImpl(Ark_NativePointer node,
                     const Opt_FormSize* value)
    {
    }
    void SetModuleNameImpl(Ark_NativePointer node,
                           const Opt_String* value)
    {
    }
    void SetDimensionImpl(Ark_NativePointer node,
                          const Opt_FormDimension* value)
    {
    }
    void SetAllowUpdateImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetVisibilityImpl(Ark_NativePointer node,
                           const Opt_Visibility* value)
    {
    }
    void SetOnAcquiredImpl(Ark_NativePointer node,
                           const Opt_Callback_FormCallbackInfo_Void* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_Callback_ErrorInformation_Void* value)
    {
    }
    void SetOnRouterImpl(Ark_NativePointer node,
                         const Opt_Callback_RouterCallbackInfo_Void* value)
    {
    }
    void SetOnUninstallImpl(Ark_NativePointer node,
                            const Opt_Callback_FormCallbackInfo_Void* value)
    {
    }
    void SetOnLoadImpl(Ark_NativePointer node,
                       const Opt_VoidCallback* value)
    {
    }
    void SetOnUpdateImpl(Ark_NativePointer node,
                         const Opt_Callback_FormCallbackInfo_Void* value)
    {
    }
    } // FormComponentAttributeModifier
    namespace FormLinkModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // FormLinkModifier
    namespace FormLinkInterfaceModifier {
    void SetFormLinkOptionsImpl(Ark_NativePointer node,
                                const Ark_FormLinkOptions* options)
    {
    }
    } // FormLinkInterfaceModifier
    namespace GaugeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GaugeModifier
    namespace GaugeInterfaceModifier {
    void SetGaugeOptionsImpl(Ark_NativePointer node,
                             const Ark_GaugeOptions* options)
    {
    }
    } // GaugeInterfaceModifier
    namespace GaugeAttributeModifier {
    void SetValueImpl(Ark_NativePointer node,
                      const Opt_Float64* value)
    {
    }
    void SetStartAngleImpl(Ark_NativePointer node,
                           const Opt_Float64* value)
    {
    }
    void SetEndAngleImpl(Ark_NativePointer node,
                         const Opt_Float64* value)
    {
    }
    void SetColorsImpl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_ResourceColor_LinearGradient_F64* value)
    {
    }
    void SetStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Length* value)
    {
    }
    void SetDescriptionImpl(Ark_NativePointer node,
                            const Opt_CustomNodeBuilder* value)
    {
    }
    void SetTrackShadowImpl(Ark_NativePointer node,
                            const Opt_GaugeShadowOptions* value)
    {
    }
    void SetIndicatorImpl(Ark_NativePointer node,
                          const Opt_GaugeIndicatorOptions* value)
    {
    }
    void SetPrivacySensitiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    } // GaugeAttributeModifier
    namespace GridModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GridModifier
    namespace GridInterfaceModifier {
    void SetGridOptionsImpl(Ark_NativePointer node,
                            const Opt_Scroller* scroller,
                            const Opt_GridLayoutOptions* layoutOptions)
    {
    }
    } // GridInterfaceModifier
    namespace GridAttributeModifier {
    void SetColumnsTemplateImpl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    void SetRowsTemplateImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void SetColumnsGapImpl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void SetRowsGapImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void SetScrollBarWidthImpl(Ark_NativePointer node,
                               const Opt_Union_F64_String* value)
    {
    }
    void SetScrollBarColorImpl(Ark_NativePointer node,
                               const Opt_Union_Color_I32_String* value)
    {
    }
    void SetScrollBarImpl(Ark_NativePointer node,
                          const Opt_BarState* value)
    {
    }
    void SetOnScrollBarUpdateImpl(Ark_NativePointer node,
                                  const Opt_Callback_I32_F64_ComputedBarAttribute* value)
    {
    }
    void SetOnScrollIndexImpl(Ark_NativePointer node,
                              const Opt_Callback_I32_I32_Void* value)
    {
    }
    void SetCachedCount0Impl(Ark_NativePointer node,
                             const Opt_Int32* value)
    {
    }
    void SetEditModeImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetMultiSelectableImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetMaxCountImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetMinCountImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetCellLengthImpl(Ark_NativePointer node,
                           const Opt_Float64* value)
    {
    }
    void SetLayoutDirectionImpl(Ark_NativePointer node,
                                const Opt_GridDirection* value)
    {
    }
    void SetSupportAnimationImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetOnItemDragStartImpl(Ark_NativePointer node,
                                const Opt_OnItemDragStartCallback* value)
    {
    }
    void SetOnItemDragEnterImpl(Ark_NativePointer node,
                                const Opt_Callback_ItemDragInfo_Void* value)
    {
    }
    void SetOnItemDragMoveImpl(Ark_NativePointer node,
                               const Opt_Callback_ItemDragInfo_I32_I32_Void* value)
    {
    }
    void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                                const Opt_Callback_ItemDragInfo_I32_Void* value)
    {
    }
    void SetOnItemDropImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void* value)
    {
    }
    void SetNestedScrollImpl(Ark_NativePointer node,
                             const Opt_NestedScrollOptions* value)
    {
    }
    void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetFrictionImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
    {
    }
    void SetAlignItemsImpl(Ark_NativePointer node,
                           const Opt_GridItemAlignment* value)
    {
    }
    void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                                   const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void SetOnWillScrollImpl(Ark_NativePointer node,
                             const Opt_OnWillScrollCallback* value)
    {
    }
    void SetOnDidScrollImpl(Ark_NativePointer node,
                            const Opt_OnScrollCallback* value)
    {
    }
    void SetCachedCount1Impl(Ark_NativePointer node,
                             const Opt_Int32* count,
                             const Opt_Boolean* show)
    {
    }
    void SetEdgeEffectImpl(Ark_NativePointer node,
                           const Opt_EdgeEffect* value,
                           const Opt_EdgeEffectOptions* options)
    {
    }
    } // GridAttributeModifier
    namespace GridColModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GridColModifier
    namespace GridColInterfaceModifier {
    void SetGridColOptionsImpl(Ark_NativePointer node,
                               const Opt_GridColOptions* option)
    {
    }
    } // GridColInterfaceModifier
    namespace GridColAttributeModifier {
    void SetSpanImpl(Ark_NativePointer node,
                     const Opt_Union_Number_GridColColumnOption* value)
    {
    }
    void SetGridColOffsetImpl(Ark_NativePointer node,
                              const Opt_Union_Number_GridColColumnOption* value)
    {
    }
    void SetOrderImpl(Ark_NativePointer node,
                      const Opt_Union_Number_GridColColumnOption* value)
    {
    }
    } // GridColAttributeModifier
    namespace GridItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GridItemModifier
    namespace GridItemInterfaceModifier {
    void SetGridItemOptionsImpl(Ark_NativePointer node,
                                const Opt_GridItemOptions* value)
    {
    }
    } // GridItemInterfaceModifier
    namespace GridItemAttributeModifier {
    void SetRowStartImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetRowEndImpl(Ark_NativePointer node,
                       const Opt_Int32* value)
    {
    }
    void SetColumnStartImpl(Ark_NativePointer node,
                            const Opt_Int32* value)
    {
    }
    void SetColumnEndImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
    {
    }
    void SetSelectableImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetSelectedImpl(Ark_NativePointer node,
                         const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetOnSelectImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
    {
    }
    } // GridItemAttributeModifier
    namespace GridRowModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GridRowModifier
    namespace GridRowInterfaceModifier {
    void SetGridRowOptionsImpl(Ark_NativePointer node,
                               const Opt_GridRowOptions* option)
    {
    }
    } // GridRowInterfaceModifier
    namespace GridRowAttributeModifier {
    void SetOnBreakpointChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_String_Void* value)
    {
    }
    void SetAlignItemsImpl(Ark_NativePointer node,
                           const Opt_ItemAlign* value)
    {
    }
    } // GridRowAttributeModifier
    namespace HyperlinkModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // HyperlinkModifier
    namespace HyperlinkInterfaceModifier {
    void SetHyperlinkOptionsImpl(Ark_NativePointer node,
                                 const Opt_Union_String_Resource* address,
                                 const Opt_Union_String_Resource* content)
    {
    }
    } // HyperlinkInterfaceModifier
    namespace HyperlinkAttributeModifier {
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_Union_Color_I32_String_Resource* value)
    {
    }
    } // HyperlinkAttributeModifier
    namespace ImageModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ImageModifier
    namespace ImageInterfaceModifier {
    void SetImageOptionsImpl(Ark_NativePointer node,
                             const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src,
                             const Opt_ImageAIOptions* imageAIOptions)
    {
    }
    } // ImageInterfaceModifier
    namespace ImageAttributeModifier {
    void SetAltImpl(Ark_NativePointer node,
                    const Opt_Union_String_Resource_PixelMap* value)
    {
    }
    void SetMatchTextDirectionImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetFitOriginalSizeImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetFillColorImpl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_ColorContent_ColorMetrics* value)
    {
    }
    void SetObjectFitImpl(Ark_NativePointer node,
                          const Opt_ImageFit* value)
    {
    }
    void SetImageMatrixImpl(Ark_NativePointer node,
                            const Opt_matrix4_Matrix4Transit* value)
    {
    }
    void SetObjectRepeatImpl(Ark_NativePointer node,
                             const Opt_ImageRepeat* value)
    {
    }
    void SetAutoResizeImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetRenderModeImpl(Ark_NativePointer node,
                           const Opt_ImageRenderMode* value)
    {
    }
    void SetDynamicRangeModeImpl(Ark_NativePointer node,
                                 const Opt_DynamicRangeMode* value)
    {
    }
    void SetInterpolationImpl(Ark_NativePointer node,
                              const Opt_ImageInterpolation* value)
    {
    }
    void SetSourceSizeImpl(Ark_NativePointer node,
                           const Opt_ImageSourceSize* value)
    {
    }
    void SetSyncLoadImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetColorFilterImpl(Ark_NativePointer node,
                            const Opt_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void SetCopyOptionImpl(Ark_NativePointer node,
                           const Opt_CopyOptions* value)
    {
    }
    void SetDraggableImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetPointLightImpl(Ark_NativePointer node,
                           const Opt_PointLightStyle* value)
    {
    }
    void SetEdgeAntialiasingImpl(Ark_NativePointer node,
                                 const Opt_Float64* value)
    {
    }
    void SetOnCompleteImpl(Ark_NativePointer node,
                           const Opt_ImageOnCompleteCallback* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_ImageErrorCallback* value)
    {
    }
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetEnableAnalyzerImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetAnalyzerConfigImpl(Ark_NativePointer node,
                               const Opt_ImageAnalyzerConfig* value)
    {
    }
    void SetResizableImpl(Ark_NativePointer node,
                          const Opt_ResizableOptions* value)
    {
    }
    void SetPrivacySensitiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetEnhancedImageQualityImpl(Ark_NativePointer node,
                                     const Opt_image_ResolutionQuality* value)
    {
    }
    void SetOrientationImpl(Ark_NativePointer node,
                            const Opt_ImageRotateOrientation* value)
    {
    }
    } // ImageAttributeModifier
    namespace ImageAnimatorModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ImageAnimatorModifier
    namespace ImageAnimatorInterfaceModifier {
    void SetImageAnimatorOptionsImpl(Ark_NativePointer node)
    {
    }
    } // ImageAnimatorInterfaceModifier
    namespace ImageAnimatorAttributeModifier {
    void SetImagesImpl(Ark_NativePointer node,
                       const Opt_Array_ImageFrameInfo* value)
    {
    }
    void SetStateImpl(Ark_NativePointer node,
                      const Opt_AnimationStatus* value)
    {
    }
    void SetDurationImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetReverseImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SetFixedSizeImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetFillModeImpl(Ark_NativePointer node,
                         const Opt_FillMode* value)
    {
    }
    void SetIterationsImpl(Ark_NativePointer node,
                           const Opt_Int32* value)
    {
    }
    void SetMonitorInvisibleAreaImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetOnStartImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnPauseImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnRepeatImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnCancelImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    } // ImageAnimatorAttributeModifier
    namespace ImageSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ImageSpanModifier
    namespace ImageSpanInterfaceModifier {
    void SetImageSpanOptionsImpl(Ark_NativePointer node,
                                 const Ark_Union_ResourceStr_PixelMap* value)
    {
    }
    } // ImageSpanInterfaceModifier
    namespace ImageSpanAttributeModifier {
    void SetVerticalAlignImpl(Ark_NativePointer node,
                              const Opt_ImageSpanAlignment* value)
    {
    }
    void SetColorFilterImpl(Ark_NativePointer node,
                            const Opt_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void SetObjectFitImpl(Ark_NativePointer node,
                          const Opt_ImageFit* value)
    {
    }
    void SetOnCompleteImpl(Ark_NativePointer node,
                           const Opt_ImageCompleteCallback* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_ImageErrorCallback* value)
    {
    }
    void SetAltImpl(Ark_NativePointer node,
                    const Opt_image_PixelMap* value)
    {
    }
    } // ImageSpanAttributeModifier
    namespace IndicatorComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // IndicatorComponentModifier
    namespace IndicatorComponentInterfaceModifier {
    void SetIndicatorComponentOptionsImpl(Ark_NativePointer node,
                                          const Opt_IndicatorComponentController* controller)
    {
    }
    } // IndicatorComponentInterfaceModifier
    namespace IndicatorComponentAttributeModifier {
    void SetInitialIndexImpl(Ark_NativePointer node,
                             const Opt_Number* value)
    {
    }
    void SetCountImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void SetStyleImpl(Ark_NativePointer node,
                      const Opt_Union_DotIndicator_DigitIndicator* value)
    {
    }
    void SetLoopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void SetVerticalImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
    {
    }
    } // IndicatorComponentAttributeModifier
    namespace LazyGridLayoutAttributeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetRowsGapImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
    {
    }
    void SetColumnsGapImpl(Ark_NativePointer node,
                           const Opt_LengthMetrics* value)
    {
    }
    } // LazyGridLayoutAttributeModifier
    namespace LazyVGridLayoutModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // LazyVGridLayoutModifier
    namespace LazyVGridLayoutInterfaceModifier {
    void SetLazyVGridLayoutOptionsImpl(Ark_NativePointer node)
    {
    }
    } // LazyVGridLayoutInterfaceModifier
    namespace LazyVGridLayoutAttributeModifier {
    void SetColumnsTemplateImpl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    } // LazyVGridLayoutAttributeModifier
    namespace LineModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // LineModifier
    namespace LineInterfaceModifier {
    void SetLineOptionsImpl(Ark_NativePointer node,
                            const Opt_LineOptions* options)
    {
    }
    } // LineInterfaceModifier
    namespace LineAttributeModifier {
    void SetStartPointImpl(Ark_NativePointer node,
                           const Opt_ShapePoint* value)
    {
    }
    void SetEndPointImpl(Ark_NativePointer node,
                         const Opt_ShapePoint* value)
    {
    }
    } // LineAttributeModifier
    namespace LinearIndicatorModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // LinearIndicatorModifier
    namespace LinearIndicatorInterfaceModifier {
    void SetLinearIndicatorOptionsImpl(Ark_NativePointer node,
                                       const Opt_Number* count,
                                       const Opt_LinearIndicatorController* controller)
    {
    }
    } // LinearIndicatorInterfaceModifier
    namespace LinearIndicatorAttributeModifier {
    void SetIndicatorStyleImpl(Ark_NativePointer node,
                               const Opt_LinearIndicatorStyle* value)
    {
    }
    void SetIndicatorLoopImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnLinearIndicatorChangeCallback* value)
    {
    }
    } // LinearIndicatorAttributeModifier
    namespace ListModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ListModifier
    namespace ListInterfaceModifier {
    void SetListOptionsImpl(Ark_NativePointer node,
                            const Opt_ListOptions* options)
    {
    }
    } // ListInterfaceModifier
    namespace ListAttributeModifier {
    void SetAlignListItemImpl(Ark_NativePointer node,
                              const Opt_ListItemAlign* value)
    {
    }
    void SetListDirectionImpl(Ark_NativePointer node,
                              const Opt_Axis* value)
    {
    }
    void SetContentStartOffsetImpl(Ark_NativePointer node,
                                   const Opt_Float64* value)
    {
    }
    void SetContentEndOffsetImpl(Ark_NativePointer node,
                                 const Opt_Float64* value)
    {
    }
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_ListDividerOptions* value)
    {
    }
    void SetMultiSelectableImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetCachedCount0Impl(Ark_NativePointer node,
                             const Opt_Int32* value)
    {
    }
    void SetChainAnimationImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetChainAnimationOptionsImpl(Ark_NativePointer node,
                                      const Opt_ChainAnimationOptions* value)
    {
    }
    void SetStickyImpl(Ark_NativePointer node,
                       const Opt_StickyStyle* value)
    {
    }
    void SetScrollSnapAlignImpl(Ark_NativePointer node,
                                const Opt_ScrollSnapAlign* value)
    {
    }
    void SetChildrenMainSizeImpl(Ark_NativePointer node,
                                 const Opt_ChildrenMainSize* value)
    {
    }
    void SetMaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                               const Opt_Boolean* value)
    {
    }
    void SetStackFromEndImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetOnScrollIndexImpl(Ark_NativePointer node,
                              const Opt_Callback_I32_I32_I32_Void* value)
    {
    }
    void SetOnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                             const Opt_OnScrollVisibleContentChangeCallback* value)
    {
    }
    void SetOnItemMoveImpl(Ark_NativePointer node,
                           const Opt_Callback_I32_I32_Boolean* value)
    {
    }
    void SetOnItemDragStartImpl(Ark_NativePointer node,
                                const Opt_OnItemDragStartCallback* value)
    {
    }
    void SetOnItemDragEnterImpl(Ark_NativePointer node,
                                const Opt_Callback_ItemDragInfo_Void* value)
    {
    }
    void SetOnItemDragMoveImpl(Ark_NativePointer node,
                               const Opt_Callback_ItemDragInfo_I32_I32_Void* value)
    {
    }
    void SetOnItemDragLeaveImpl(Ark_NativePointer node,
                                const Opt_Callback_ItemDragInfo_I32_Void* value)
    {
    }
    void SetOnItemDropImpl(Ark_NativePointer node,
                           const Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void* value)
    {
    }
    void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                                   const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void SetOnWillScrollImpl(Ark_NativePointer node,
                             const Opt_OnWillScrollCallback* value)
    {
    }
    void SetOnDidScrollImpl(Ark_NativePointer node,
                            const Opt_OnScrollCallback* value)
    {
    }
    void SetLanesImpl(Ark_NativePointer node,
                      const Opt_Union_I32_LengthConstrain* value,
                      const Opt_Dimension* gutter)
    {
    }
    void SetCachedCount1Impl(Ark_NativePointer node,
                             const Opt_Int32* count,
                             const Opt_Boolean* show)
    {
    }
    } // ListAttributeModifier
    namespace ListItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ListItemModifier
    namespace ListItemInterfaceModifier {
    void SetListItemOptionsImpl(Ark_NativePointer node,
                                const Opt_ListItemOptions* value)
    {
    }
    } // ListItemInterfaceModifier
    namespace ListItemAttributeModifier {
    void SetSelectableImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetSelectedImpl(Ark_NativePointer node,
                         const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetSwipeActionImpl(Ark_NativePointer node,
                            const Opt_SwipeActionOptions* value)
    {
    }
    void SetOnSelectImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
    {
    }
    } // ListItemAttributeModifier
    namespace ListItemGroupModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ListItemGroupModifier
    namespace ListItemGroupInterfaceModifier {
    void SetListItemGroupOptionsImpl(Ark_NativePointer node,
                                     const Opt_ListItemGroupOptions* options)
    {
    }
    } // ListItemGroupInterfaceModifier
    namespace ListItemGroupAttributeModifier {
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_ListDividerOptions* value)
    {
    }
    void SetChildrenMainSizeImpl(Ark_NativePointer node,
                                 const Opt_ChildrenMainSize* value)
    {
    }
    } // ListItemGroupAttributeModifier
    namespace LoadingProgressModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // LoadingProgressModifier
    namespace LoadingProgressInterfaceModifier {
    void SetLoadingProgressOptionsImpl(Ark_NativePointer node)
    {
    }
    } // LoadingProgressInterfaceModifier
    namespace LoadingProgressAttributeModifier {
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
    {
    }
    void SetEnableLoadingImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    } // LoadingProgressAttributeModifier
    namespace MarqueeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // MarqueeModifier
    namespace MarqueeInterfaceModifier {
    void SetMarqueeOptionsImpl(Ark_NativePointer node,
                               const Ark_MarqueeOptions* options)
    {
    }
    } // MarqueeInterfaceModifier
    namespace MarqueeAttributeModifier {
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetAllowScaleImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_Union_String_Resource* value)
    {
    }
    void SetMarqueeUpdateStrategyImpl(Ark_NativePointer node,
                                      const Opt_MarqueeUpdateStrategy* value)
    {
    }
    void SetOnStartImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnBounceImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    } // MarqueeAttributeModifier
    namespace MediaCachedImageModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // MediaCachedImageModifier
    namespace MediaCachedImageInterfaceModifier {
    void SetMediaCachedImageOptionsImpl(Ark_NativePointer node,
                                        const Ark_Union_Image_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource* src)
    {
    }
    } // MediaCachedImageInterfaceModifier
    namespace MenuModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // MenuModifier
    namespace MenuInterfaceModifier {
    void SetMenuOptionsImpl(Ark_NativePointer node)
    {
    }
    } // MenuInterfaceModifier
    namespace MenuAttributeModifier {
    void SetFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetRadiusImpl(Ark_NativePointer node,
                       const Opt_Union_Dimension_BorderRadiuses* value)
    {
    }
    void SetMenuItemDividerImpl(Ark_NativePointer node,
                                const Opt_DividerStyleOptions* value)
    {
    }
    void SetMenuItemGroupDividerImpl(Ark_NativePointer node,
                                     const Opt_DividerStyleOptions* value)
    {
    }
    void SetSubMenuExpandingModeImpl(Ark_NativePointer node,
                                     const Opt_SubMenuExpandingMode* value)
    {
    }
    void SetSubMenuExpandSymbolImpl(Ark_NativePointer node,
                                    const Opt_SymbolGlyphModifier* value)
    {
    }
    } // MenuAttributeModifier
    namespace MenuItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // MenuItemModifier
    namespace MenuItemInterfaceModifier {
    void SetMenuItemOptionsImpl(Ark_NativePointer node,
                                const Opt_Union_MenuItemOptions_CustomBuilder* value)
    {
    }
    } // MenuItemInterfaceModifier
    namespace MenuItemAttributeModifier {
    void SetSelectedImpl(Ark_NativePointer node,
                         const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetSelectIconImpl(Ark_NativePointer node,
                           const Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetContentFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
    {
    }
    void SetContentFontColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetLabelFontImpl(Ark_NativePointer node,
                          const Opt_Font* value)
    {
    }
    void SetLabelFontColorImpl(Ark_NativePointer node,
                               const Opt_ResourceColor* value)
    {
    }
    } // MenuItemAttributeModifier
    namespace MenuItemGroupModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // MenuItemGroupModifier
    namespace MenuItemGroupInterfaceModifier {
    void SetMenuItemGroupOptionsImpl(Ark_NativePointer node,
                                     const Opt_MenuItemGroupOptions* value)
    {
    }
    } // MenuItemGroupInterfaceModifier
    namespace NavDestinationModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // NavDestinationModifier
    namespace NavDestinationInterfaceModifier {
    void SetNavDestinationOptionsImpl(Ark_NativePointer node,
                                      const Opt_NavDestinationModuleInfo* moduleInfo)
    {
    }
    } // NavDestinationInterfaceModifier
    namespace NavDestinationAttributeModifier {
    void SetHideTitleBar0Impl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetHideBackButtonImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetOnShownImpl(Ark_NativePointer node,
                        const const Opt_Callback_VisibilityChangeReason_Void* value)
    {
    }
    void SetOnHiddenImpl(Ark_NativePointer node,
                         const const Opt_Callback_VisibilityChangeReason_Void* value)
    {
    }
    void SetOnBackPressedImpl(Ark_NativePointer node,
                              const Opt_Callback_Boolean* value)
    {
    }
    void SetOnResultImpl(Ark_NativePointer node,
                         const Opt_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void* value)
    {
    }
    void SetModeImpl(Ark_NativePointer node,
                     const Opt_NavDestinationMode* value)
    {
    }
    void SetBackButtonIcon0Impl(Ark_NativePointer node,
                                const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
    {
    }
    void SetMenus0Impl(Ark_NativePointer node,
                       const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
    {
    }
    void SetOnReadyImpl(Ark_NativePointer node,
                        const Opt_Callback_NavDestinationContext_Void* value)
    {
    }
    void SetOnWillAppearImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void SetOnWillDisappearImpl(Ark_NativePointer node,
                                const Opt_Callback_Void* value)
    {
    }
    void SetOnWillShowImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
    {
    }
    void SetOnWillHideImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
    {
    }
    void SetSystemBarStyleImpl(Ark_NativePointer node,
                               const Opt_window_SystemBarStyle* value)
    {
    }
    void SetRecoverableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetSystemTransitionImpl(Ark_NativePointer node,
                                 const Opt_NavigationSystemTransitionType* value)
    {
    }
    void SetBindToScrollableImpl(Ark_NativePointer node,
                                 const Opt_Array_Scroller* value)
    {
    }
    void SetBindToNestedScrollableImpl(Ark_NativePointer node,
                                       const Opt_Array_NestedScrollInfo* value)
    {
    }
    void SetOnActiveImpl(Ark_NativePointer node,
                         const Opt_Callback_NavDestinationActiveReason_Void* value)
    {
    }
    void SetOnInactiveImpl(Ark_NativePointer node,
                           const Opt_Callback_NavDestinationActiveReason_Void* value)
    {
    }
    void SetCustomTransitionImpl(Ark_NativePointer node,
                                 const Opt_NavDestinationTransitionDelegate* value)
    {
    }
    void SetOnNewParamImpl(Ark_NativePointer node,
                           const Opt_Callback_Union_Object_Idlize_Stdlib_Null_Undefined_Void* value)
    {
    }
    void SetPreferredOrientationImpl(Ark_NativePointer node,
                                     const Opt_window_Orientation* value)
    {
    }
    void SetEnableNavigationIndicatorImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void SetTitleImpl(Ark_NativePointer node,
                      const Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource* value,
                      const Opt_NavigationTitleOptions* options)
    {
    }
    void SetHideTitleBar1Impl(Ark_NativePointer node,
                              const Opt_Boolean* hide,
                              const Opt_Boolean* animated)
    {
    }
    void SetBackButtonIcon1Impl(Ark_NativePointer node,
                                const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
                                const Opt_ResourceStr* accessibilityText)
    {
    }
    void SetMenus1Impl(Ark_NativePointer node,
                       const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                       const Opt_NavigationMenuOptions* options)
    {
    }
    void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                     const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                                     const Opt_NavigationToolbarOptions* options)
    {
    }
    void SetHideToolBarImpl(Ark_NativePointer node,
                            const Opt_Boolean* hide,
                            const Opt_Boolean* animated)
    {
    }
    void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                     const Opt_Array_LayoutSafeAreaType* types,
                                     const Opt_Array_LayoutSafeAreaEdge* edges)
    {
    }
    void SetEnableStatusBarImpl(Ark_NativePointer node,
                                const Opt_Boolean* enabled,
                                const Opt_Boolean* animated)
    {
    }
    } // NavDestinationAttributeModifier
    namespace NavigationModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // NavigationModifier
    namespace NavigationInterfaceModifier {
    void SetNavigationOptionsImpl(Ark_NativePointer node,
                                  const Opt_NavPathStack* pathInfos,
                                  const Opt_NavigationModuleInfo* moduleInfo)
    {
    }
    } // NavigationInterfaceModifier
    namespace NavigationAttributeModifier {
    void SetNavBarWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Length_Bindable* value)
    {
    }
    void SetNavBarPositionImpl(Ark_NativePointer node,
                               const Opt_NavBarPosition* value)
    {
    }
    void SetNavBarWidthRangeImpl(Ark_NativePointer node,
                                 const Opt_Tuple_Dimension_Dimension* value)
    {
    }
    void SetMinContentWidthImpl(Ark_NativePointer node,
                                const Opt_Dimension* value)
    {
    }
    void SetModeImpl(Ark_NativePointer node,
                     const Opt_NavigationMode* value)
    {
    }
    void SetBackButtonIcon0Impl(Ark_NativePointer node,
                                const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
    {
    }
    void SetHideNavBarImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetHideTitleBar0Impl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetHideBackButtonImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetTitleModeImpl(Ark_NativePointer node,
                          const Opt_NavigationTitleMode* value)
    {
    }
    void SetMenus0Impl(Ark_NativePointer node,
                       const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
    {
    }
    void SetHideToolBar0Impl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetEnableToolBarAdaptationImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetOnTitleModeChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_NavigationTitleMode_Void* value)
    {
    }
    void SetOnNavBarStateChangeImpl(Ark_NativePointer node,
                                    const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetOnNavigationModeChangeImpl(Ark_NativePointer node,
                                       const Opt_Callback_NavigationMode_Void* value)
    {
    }
    void SetCustomNavContentTransitionImpl(Ark_NativePointer node,
                                           const Opt_Type_NavigationAttribute_customNavContentTransition* value)
    {
    }
    void SetSystemBarStyleImpl(Ark_NativePointer node,
                               const Opt_window_SystemBarStyle* value)
    {
    }
    void SetRecoverableImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetEnableDragBarImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetEnableModeChangeAnimationImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void SetBackButtonIcon1Impl(Ark_NativePointer node,
                                const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                                const Opt_ResourceStr* accessibilityText)
    {
    }
    void SetTitleImpl(Ark_NativePointer node,
                      const Opt_Union_ResourceStr_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle* value,
                      const Opt_NavigationTitleOptions* options)
    {
    }
    void SetHideTitleBar1Impl(Ark_NativePointer node,
                              const Opt_Boolean* hide,
                              const Opt_Boolean* animated)
    {
    }
    void SetMenus1Impl(Ark_NativePointer node,
                       const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                       const Opt_NavigationMenuOptions* options)
    {
    }
    void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                     const Opt_Union_Array_ToolbarItem_CustomBuilder* value,
                                     const Opt_NavigationToolbarOptions* options)
    {
    }
    void SetHideToolBar1Impl(Ark_NativePointer node,
                             const Opt_Boolean* hide,
                             const Opt_Boolean* animated)
    {
    }
    void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                     const Opt_Array_LayoutSafeAreaType* types,
                                     const Opt_Array_LayoutSafeAreaEdge* edges)
    {
    }
    } // NavigationAttributeModifier
    namespace NodeContainerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // NodeContainerModifier
    namespace NodeContainerInterfaceModifier {
    void SetNodeContainerOptionsImpl(Ark_NativePointer node,
                                     Ark_NodeController controller)
    {
    }
    } // NodeContainerInterfaceModifier
    namespace PasteButtonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PasteButtonModifier
    namespace PasteButtonInterfaceModifier {
    void SetPasteButtonOptionsImpl(Ark_NativePointer node,
                                   const Opt_PasteButtonOptions* options)
    {
    }
    } // PasteButtonInterfaceModifier
    namespace PasteButtonAttributeModifier {
    void SetOnClickImpl(Ark_NativePointer node,
                        const Opt_PasteButtonCallback* value)
    {
    }
    } // PasteButtonAttributeModifier
    namespace PathModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PathModifier
    namespace PathInterfaceModifier {
    void SetPathOptionsImpl(Ark_NativePointer node,
                            const Opt_PathOptions* options)
    {
    }
    } // PathInterfaceModifier
    namespace PathAttributeModifier {
    void SetCommandsImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    } // PathAttributeModifier
    namespace PatternLockModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PatternLockModifier
    namespace PatternLockInterfaceModifier {
    void SetPatternLockOptionsImpl(Ark_NativePointer node,
                                   const Opt_PatternLockController* controller)
    {
    }
    } // PatternLockInterfaceModifier
    namespace PatternLockAttributeModifier {
    void SetSideLengthImpl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void SetCircleRadiusImpl(Ark_NativePointer node,
                             const Opt_Length* value)
    {
    }
    void SetBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetRegularColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetActiveColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
    {
    }
    void SetPathColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetPathStrokeWidthImpl(Ark_NativePointer node,
                                const Opt_Union_F64_String* value)
    {
    }
    void SetOnPatternCompleteImpl(Ark_NativePointer node,
                                  const Opt_Callback_Array_I32_Void* value)
    {
    }
    void SetAutoResetImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetOnDotConnectImpl(Ark_NativePointer node,
                             const Opt_Callback_I32_Void* value)
    {
    }
    void SetActivateCircleStyleImpl(Ark_NativePointer node,
                                    const Opt_CircleStyleOptions* value)
    {
    }
    void SetSkipUnselectedPointImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    } // PatternLockAttributeModifier
    namespace PluginComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PluginComponentModifier
    namespace PluginComponentInterfaceModifier {
    void SetPluginComponentOptionsImpl(Ark_NativePointer node,
                                       const Ark_PluginComponentOptions* options)
    {
    }
    } // PluginComponentInterfaceModifier
    namespace PluginComponentAttributeModifier {
    void SetOnCompleteImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_PluginErrorCallback* value)
    {
    }
    } // PluginComponentAttributeModifier
    namespace PolygonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PolygonModifier
    namespace PolygonInterfaceModifier {
    void SetPolygonOptionsImpl(Ark_NativePointer node,
                               const Opt_PolygonOptions* options)
    {
    }
    } // PolygonInterfaceModifier
    namespace PolygonAttributeModifier {
    void SetPointsImpl(Ark_NativePointer node,
                       const Opt_Array_ShapePoint* value)
    {
    }
    } // PolygonAttributeModifier
    namespace PolylineModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PolylineModifier
    namespace PolylineInterfaceModifier {
    void SetPolylineOptionsImpl(Ark_NativePointer node,
                                const Opt_PolylineOptions* options)
    {
    }
    } // PolylineInterfaceModifier
    namespace PolylineAttributeModifier {
    void SetPointsImpl(Ark_NativePointer node,
                       const Opt_Array_ShapePoint* value)
    {
    }
    } // PolylineAttributeModifier
    namespace ProgressModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ProgressModifier
    namespace ProgressInterfaceModifier {
    void SetProgressOptionsImpl(Ark_NativePointer node,
                                const Ark_ProgressOptions* options)
    {
    }
    } // ProgressInterfaceModifier
    namespace ProgressAttributeModifier {
    void SetValueImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SetStyleImpl(Ark_NativePointer node,
                      const Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions* value)
    {
    }
    void SetPrivacySensitiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    } // ProgressAttributeModifier
    namespace QRCodeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // QRCodeModifier
    namespace QRCodeInterfaceModifier {
    void SetQRCodeOptionsImpl(Ark_NativePointer node,
                              const Ark_ResourceStr* value)
    {
    }
    } // QRCodeInterfaceModifier
    namespace QRCodeAttributeModifier {
    void SetColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
    {
    }
    void SetBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetContentOpacityImpl(Ark_NativePointer node,
                               const Opt_Union_F64_Resource* value)
    {
    }
    } // QRCodeAttributeModifier
    namespace RadioModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RadioModifier
    namespace RadioInterfaceModifier {
    void SetRadioOptionsImpl(Ark_NativePointer node,
                             const Ark_RadioOptions* options)
    {
    }
    } // RadioInterfaceModifier
    namespace RadioAttributeModifier {
    void SetCheckedImpl(Ark_NativePointer node,
                        const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnRadioChangeCallback* value)
    {
    }
    void SetRadioStyleImpl(Ark_NativePointer node,
                           const Opt_RadioStyle* value)
    {
    }
    } // RadioAttributeModifier
    namespace RatingModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RatingModifier
    namespace RatingInterfaceModifier {
    void SetRatingOptionsImpl(Ark_NativePointer node,
                              const Opt_RatingOptions* options)
    {
    }
    } // RatingInterfaceModifier
    namespace RatingAttributeModifier {
    void SetStarsImpl(Ark_NativePointer node,
                      const Opt_Int32* value)
    {
    }
    void SetStepSizeImpl(Ark_NativePointer node,
                         const Opt_Float64* value)
    {
    }
    void SetStarStyleImpl(Ark_NativePointer node,
                          const Opt_StarStyleOptions* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnRatingChangeCallback* value)
    {
    }
    } // RatingAttributeModifier
    namespace RectModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RectModifier
    namespace RectInterfaceModifier {
    void SetRectOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_RectOptions_RoundedRectOptions* options)
    {
    }
    } // RectInterfaceModifier
    namespace RectAttributeModifier {
    void SetRadiusWidthImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String* value)
    {
    }
    void SetRadiusHeightImpl(Ark_NativePointer node,
                             const Opt_Union_F64_String* value)
    {
    }
    void SetRadiusImpl(Ark_NativePointer node,
                       const Opt_Union_Length_Array_RadiusItem* value)
    {
    }
    } // RectAttributeModifier
    namespace RefreshModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RefreshModifier
    namespace RefreshInterfaceModifier {
    void SetRefreshOptionsImpl(Ark_NativePointer node,
                               const Ark_RefreshOptions* value)
    {
    }
    } // RefreshInterfaceModifier
    namespace RefreshAttributeModifier {
    void SetOnStateChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_RefreshStatus_Void* value)
    {
    }
    void SetOnRefreshingImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void SetRefreshOffsetImpl(Ark_NativePointer node,
                              const Opt_Float64* value)
    {
    }
    void SetPullToRefreshImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetOnOffsetChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_F64_Void* value)
    {
    }
    void SetPullDownRatioImpl(Ark_NativePointer node,
                              const Opt_Float64* value)
    {
    }
    } // RefreshAttributeModifier
    namespace RelativeContainerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RelativeContainerModifier
    namespace RelativeContainerInterfaceModifier {
    void SetRelativeContainerOptionsImpl(Ark_NativePointer node)
    {
    }
    } // RelativeContainerInterfaceModifier
    namespace RelativeContainerAttributeModifier {
    void SetGuideLineImpl(Ark_NativePointer node,
                          const Opt_Array_GuideLineStyle* value)
    {
    }
    void SetBarrierImpl(Ark_NativePointer node,
                        const Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle* value)
    {
    }
    } // RelativeContainerAttributeModifier
    namespace RemoteWindowModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RemoteWindowModifier
    namespace RemoteWindowInterfaceModifier {
    void SetRemoteWindowOptionsImpl(Ark_NativePointer node,
                                    const Ark_WindowAnimationTarget* target)
    {
    }
    } // RemoteWindowInterfaceModifier
    namespace RichEditorModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RichEditorModifier
    namespace RichEditorInterfaceModifier {
    void SetRichEditorOptionsImpl(Ark_NativePointer node,
                                  const Ark_Union_RichEditorOptions_RichEditorStyledStringOptions* options)
    {
    }
    } // RichEditorInterfaceModifier
    namespace RichEditorAttributeModifier {
    void SetOnReadyImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void SetOnSelectImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorSelection_Void* value)
    {
    }
    void SetOnSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_RichEditorRange_Void* value)
    {
    }
    void SetAboutToIMEInputImpl(Ark_NativePointer node,
                                const Opt_Callback_RichEditorInsertValue_Boolean* value)
    {
    }
    void SetOnIMEInputCompleteImpl(Ark_NativePointer node,
                                   const Opt_Callback_RichEditorTextSpanResult_Void* value)
    {
    }
    void SetOnDidIMEInputImpl(Ark_NativePointer node,
                              const Opt_Callback_TextRange_Void* value)
    {
    }
    void SetAboutToDeleteImpl(Ark_NativePointer node,
                              const Opt_Callback_RichEditorDeleteValue_Boolean* value)
    {
    }
    void SetOnDeleteCompleteImpl(Ark_NativePointer node,
                                 const Opt_VoidCallback* value)
    {
    }
    void SetCopyOptionsImpl(Ark_NativePointer node,
                            const Opt_CopyOptions* value)
    {
    }
    void SetOnPasteImpl(Ark_NativePointer node,
                        const Opt_PasteEventCallback* value)
    {
    }
    void SetEnableDataDetectorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetEnablePreviewTextImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetDataDetectorConfigImpl(Ark_NativePointer node,
                                   const Opt_TextDataDetectorConfig* value)
    {
    }
    void SetCaretColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetOnEditingChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetEnterKeyTypeImpl(Ark_NativePointer node,
                             const Opt_EnterKeyType* value)
    {
    }
    void SetOnSubmitImpl(Ark_NativePointer node,
                         const Opt_SubmitCallback* value)
    {
    }
    void SetOnWillChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_RichEditorChangeValue_Boolean* value)
    {
    }
    void SetOnDidChangeImpl(Ark_NativePointer node,
                            const Opt_OnDidChangeCallback* value)
    {
    }
    void SetOnCutImpl(Ark_NativePointer node,
                      const Opt_Callback_CutEvent_Void* value)
    {
    }
    void SetOnCopyImpl(Ark_NativePointer node,
                       const Opt_Callback_CopyEvent_Void* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetBarStateImpl(Ark_NativePointer node,
                         const Opt_BarState* value)
    {
    }
    void SetMaxLengthImpl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void SetMaxLinesImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                                   const Opt_KeyboardAppearance* value)
    {
    }
    void SetStopBackPressImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetBindSelectionMenuImpl(Ark_NativePointer node,
                                  const Opt_RichEditorSpanType* spanType,
                                  const Opt_CustomNodeBuilder* content,
                                  const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                                  const Opt_SelectionMenuOptions* options)
    {
    }
    void SetCustomKeyboardImpl(Ark_NativePointer node,
                               const Opt_Union_CustomBuilder_ComponentContent* value,
                               const Opt_KeyboardOptions* options)
    {
    }
    void SetPlaceholderImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value,
                            const Opt_PlaceholderStyle* style)
    {
    }
    } // RichEditorAttributeModifier
    namespace RichTextModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RichTextModifier
    namespace RichTextInterfaceModifier {
    void SetRichTextOptionsImpl(Ark_NativePointer node,
                                const Ark_Union_String_Resource* content)
    {
    }
    } // RichTextInterfaceModifier
    namespace RichTextAttributeModifier {
    void SetOnStartImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnCompleteImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
    {
    }
    } // RichTextAttributeModifier
    namespace RootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RootModifier
    namespace RootSceneModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RootSceneModifier
    namespace RootSceneInterfaceModifier {
    void SetRootSceneOptionsImpl(Ark_NativePointer node,
                                 const Ark_RootSceneSession* session)
    {
    }
    } // RootSceneInterfaceModifier
    namespace RowModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RowModifier
    namespace RowInterfaceModifier {
    void SetRowOptionsImpl(Ark_NativePointer node,
                           const Opt_Union_RowOptions_RowOptionsV2* options)
    {
    }
    } // RowInterfaceModifier
    namespace RowAttributeModifier {
    void SetAlignItemsImpl(Ark_NativePointer node,
                           const Opt_VerticalAlign* value)
    {
    }
    void SetJustifyContentImpl(Ark_NativePointer node,
                               const Opt_FlexAlign* value)
    {
    }
    void SetReverseImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    } // RowAttributeModifier
    namespace RowSplitModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RowSplitModifier
    namespace RowSplitInterfaceModifier {
    void SetRowSplitOptionsImpl(Ark_NativePointer node)
    {
    }
    } // RowSplitInterfaceModifier
    namespace RowSplitAttributeModifier {
    void SetResizeableImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    } // RowSplitAttributeModifier
    namespace SaveButtonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SaveButtonModifier
    namespace SaveButtonInterfaceModifier {
    void SetSaveButtonOptionsImpl(Ark_NativePointer node,
                                  const Opt_SaveButtonOptions* options)
    {
    }
    } // SaveButtonInterfaceModifier
    namespace SaveButtonAttributeModifier {
    void SetOnClickImpl(Ark_NativePointer node,
                        const Opt_SaveButtonCallback* value)
    {
    }
    void SetSetIconImpl(Ark_NativePointer node,
                        const Opt_Resource* value)
    {
    }
    void SetSetTextImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* value)
    {
    }
    void SetIconSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Dimension_SizeOptions* value)
    {
    }
    void SetIconBorderRadiusImpl(Ark_NativePointer node,
                                 const Opt_Union_Dimension_BorderRadiuses* value)
    {
    }
    void SetStateEffectImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetUserCancelEventImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    } // SaveButtonAttributeModifier
    namespace ScreenModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ScreenModifier
    namespace ScreenInterfaceModifier {
    void SetScreenOptionsImpl(Ark_NativePointer node,
                              const Ark_Number* screenId)
    {
    }
    } // ScreenInterfaceModifier
    namespace ScrollModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ScrollModifier
    namespace ScrollInterfaceModifier {
    void SetScrollOptionsImpl(Ark_NativePointer node,
                              const Opt_Scroller* scroller)
    {
    }
    } // ScrollInterfaceModifier
    namespace ScrollAttributeModifier {
    void SetScrollableImpl(Ark_NativePointer node,
                           const Opt_ScrollDirection* value)
    {
    }
    void SetOnWillScrollImpl(Ark_NativePointer node,
                             const Opt_ScrollOnWillScrollCallback* value)
    {
    }
    void SetOnDidScrollImpl(Ark_NativePointer node,
                            const Opt_ScrollOnScrollCallback* value)
    {
    }
    void SetOnScrollEdgeImpl(Ark_NativePointer node,
                             const Opt_OnScrollEdgeCallback* value)
    {
    }
    void SetOnScrollStartImpl(Ark_NativePointer node,
                              const Opt_VoidCallback* value)
    {
    }
    void SetOnScrollStopImpl(Ark_NativePointer node,
                             const Opt_VoidCallback* value)
    {
    }
    void SetScrollBarImpl(Ark_NativePointer node,
                          const Opt_BarState* value)
    {
    }
    void SetScrollBarColorImpl(Ark_NativePointer node,
                               const Opt_Union_Color_I32_String* value)
    {
    }
    void SetScrollBarWidthImpl(Ark_NativePointer node,
                               const Opt_Union_F64_String* value)
    {
    }
    void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                                   const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void SetNestedScrollImpl(Ark_NativePointer node,
                             const Opt_NestedScrollOptions* value)
    {
    }
    void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetFrictionImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
    {
    }
    void SetScrollSnapImpl(Ark_NativePointer node,
                           const Opt_ScrollSnapOptions* value)
    {
    }
    void SetEnablePagingImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetInitialOffsetImpl(Ark_NativePointer node,
                              const Opt_OffsetOptions* value)
    {
    }
    void SetEdgeEffectImpl(Ark_NativePointer node,
                           const Opt_EdgeEffect* edgeEffect,
                           const Opt_EdgeEffectOptions* options)
    {
    }
    } // ScrollAttributeModifier
    namespace ScrollableCommonMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetScrollBarImpl(Ark_NativePointer node,
                          const Opt_BarState* value)
    {
    }
    void SetScrollBarColorImpl(Ark_NativePointer node,
                               const Opt_Union_Color_Number_String* value)
    {
    }
    void SetScrollBarWidthImpl(Ark_NativePointer node,
                               const Opt_Union_Number_String* value)
    {
    }
    void SetNestedScrollImpl(Ark_NativePointer node,
                             const Opt_NestedScrollOptions* value)
    {
    }
    void SetEnableScrollInteractionImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetFrictionImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
    {
    }
    void SetOnReachStartImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void SetOnReachEndImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
    {
    }
    void SetOnScrollStartImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
    {
    }
    void SetOnScrollStopImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void SetFlingSpeedLimitImpl(Ark_NativePointer node,
                                const Opt_Number* value)
    {
    }
    void SetClipContentImpl(Ark_NativePointer node,
                            const Opt_Union_ContentClipMode_RectShape* value)
    {
    }
    void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                        const Opt_CrownSensitivity* value)
    {
    }
    void SetBackToTopImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetEdgeEffectImpl(Ark_NativePointer node,
                           const Opt_EdgeEffect* edgeEffect,
                           const Opt_EdgeEffectOptions* options)
    {
    }
    void SetFadingEdgeImpl(Ark_NativePointer node,
                           const Opt_Boolean* enabled,
                           const Opt_FadingEdgeOptions* options)
    {
    }
    } // ScrollableCommonMethodModifier
    namespace ScrollBarModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ScrollBarModifier
    namespace ScrollBarInterfaceModifier {
    void SetScrollBarOptionsImpl(Ark_NativePointer node,
                                 const Ark_ScrollBarOptions* value)
    {
    }
    } // ScrollBarInterfaceModifier
    namespace ScrollBarAttributeModifier {
    void SetEnableNestedScrollImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    } // ScrollBarAttributeModifier
    namespace SearchModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SearchModifier
    namespace SearchInterfaceModifier {
    void SetSearchOptionsImpl(Ark_NativePointer node,
                              const Opt_SearchOptions* options)
    {
    }
    } // SearchInterfaceModifier
    namespace SearchAttributeModifier {
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetSearchIconImpl(Ark_NativePointer node,
                           const Opt_Union_IconOptions_SymbolGlyphModifier* value)
    {
    }
    void SetCancelButtonImpl(Ark_NativePointer node,
                             const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
    {
    }
    void SetTextIndentImpl(Ark_NativePointer node,
                           const Opt_Dimension* value)
    {
    }
    void SetOnEditChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetCaretStyleImpl(Ark_NativePointer node,
                           const Opt_CaretStyle* value)
    {
    }
    void SetPlaceholderColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetPlaceholderFontImpl(Ark_NativePointer node,
                                const Opt_Font* value)
    {
    }
    void SetTextFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
    {
    }
    void SetEnterKeyTypeImpl(Ark_NativePointer node,
                             const Opt_EnterKeyType* value)
    {
    }
    void SetOnSubmitImpl(Ark_NativePointer node,
                         const Opt_SearchSubmitCallback* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                      const Opt_OnTextSelectionChangeCallback* value)
    {
    }
    void SetOnContentScrollImpl(Ark_NativePointer node,
                                const Opt_OnContentScrollCallback* value)
    {
    }
    void SetOnCopyImpl(Ark_NativePointer node,
                       const Opt_Callback_String_Void* value)
    {
    }
    void SetOnCutImpl(Ark_NativePointer node,
                      const Opt_Callback_String_Void* value)
    {
    }
    void SetOnPasteImpl(Ark_NativePointer node,
                        const Opt_OnPasteCallback* value)
    {
    }
    void SetCopyOptionImpl(Ark_NativePointer node,
                           const Opt_CopyOptions* value)
    {
    }
    void SetMaxLengthImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
    {
    }
    void SetTextAlignImpl(Ark_NativePointer node,
                          const Opt_TextAlign* value)
    {
    }
    void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMaxFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetDecorationImpl(Ark_NativePointer node,
                           const Opt_TextDecorationOptions* value)
    {
    }
    void SetLetterSpacingImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetLineHeightImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetTypeImpl(Ark_NativePointer node,
                     const Opt_SearchType* value)
    {
    }
    void SetFontFeatureImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void SetOnWillInsertImpl(Ark_NativePointer node,
                             const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void SetOnDidInsertImpl(Ark_NativePointer node,
                            const Opt_Callback_InsertValue_Void* value)
    {
    }
    void SetOnWillDeleteImpl(Ark_NativePointer node,
                             const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void SetOnDidDeleteImpl(Ark_NativePointer node,
                            const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetEnablePreviewTextImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                       const Opt_AutoCapitalizationMode* value)
    {
    }
    void SetHalfLeadingImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetStopBackPressImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetOnWillChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                                   const Opt_KeyboardAppearance* value)
    {
    }
    void SetDividerColorImpl(Ark_NativePointer node,
                         const Opt_ColorMetrics* value)
    {
    }
    void SetSearchButtonImpl(Ark_NativePointer node,
                             const Opt_String* value,
                             const Opt_SearchButtonOptions* option)
    {
    }
    void SetInputFilterImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value,
                            const Opt_Callback_String_Void* error)
    {
    }
    void SetCustomKeyboardImpl(Ark_NativePointer node,
                               const Opt_CustomNodeBuilder* value,
                               const Opt_KeyboardOptions* options)
    {
    }
    } // SearchAttributeModifier
    namespace SecurityComponentMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SetIconSizeImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
    {
    }
    void SetLayoutDirectionImpl(Ark_NativePointer node,
                                const Opt_SecurityComponentLayoutDirection* value)
    {
    }
    void SetPositionImpl(Ark_NativePointer node,
                         const Opt_Position* value)
    {
    }
    void SetMarkAnchorImpl(Ark_NativePointer node,
                           const Opt_Position* value)
    {
    }
    void SetOffsetImpl(Ark_NativePointer node,
                       const Opt_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String_Resource* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_Union_String_Resource* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetIconColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetBorderStyleImpl(Ark_NativePointer node,
                            const Opt_BorderStyle* value)
    {
    }
    void SetBorderWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
    {
    }
    void SetBorderColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
    {
    }
    void SetBorderRadiusImpl(Ark_NativePointer node,
                             const Opt_Union_Dimension_BorderRadiuses* radius)
    {
    }
    void SetPaddingImpl(Ark_NativePointer node,
                        const Opt_Union_Padding_Dimension* value)
    {
    }
    void SetTextIconSpaceImpl(Ark_NativePointer node,
                              const Opt_Dimension* value)
    {
    }
    void SetKeyImpl(Ark_NativePointer node,
                    const Opt_String* value)
    {
    }
    void SetWidthImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void SetHeightImpl(Ark_NativePointer node,
                       const Opt_Length* value)
    {
    }
    void SetSizeImpl(Ark_NativePointer node,
                     const Opt_SizeOptions* value)
    {
    }
    void SetConstraintSizeImpl(Ark_NativePointer node,
                               const Opt_ConstraintSizeOptions* value)
    {
    }
    void SetAlignImpl(Ark_NativePointer node,
                      const Opt_Alignment* alignType)
    {
    }
    void SetAlignRulesImpl(Ark_NativePointer node,
                           const Opt_Union_AlignRuleOption_LocalizedAlignRuleOptions* alignRule)
    {
    }
    void SetIdImpl(Ark_NativePointer node,
                   const Opt_String* description)
    {
    }
    void SetChainModeImpl(Ark_NativePointer node,
                          const Opt_Axis* direction,
                          const Opt_ChainStyle* style)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* scale)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* scale)
    {
    }
    void SetMaxLinesImpl(Ark_NativePointer node,
                         const Opt_Union_I32_Resource* line)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* minSize)
    {
    }
    void SetMaxFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* maxSize)
    {
    }
    void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                     const Opt_TextHeightAdaptivePolicy* policy)
    {
    }
    void SetEnabledImpl(Ark_NativePointer node,
                        const Opt_Boolean* respond)
    {
    }
    void SetFocusBoxImpl(Ark_NativePointer node,
                         const Opt_FocusBoxStyle* style)
    {
    }
    } // SecurityComponentMethodModifier
    namespace SelectModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SelectModifier
    namespace SelectInterfaceModifier {
    void SetSelectOptionsImpl(Ark_NativePointer node,
                              const Array_SelectOption* options)
    {
    }
    } // SelectInterfaceModifier
    namespace SelectAttributeModifier {
    void SetSelectedImpl(Ark_NativePointer node,
                         const Opt_Union_I32_Resource_Bindable_Bindable* value)
    {
    }
    void SetValueImpl(Ark_NativePointer node,
                      const Opt_Union_ResourceStr_Bindable_Bindable* value)
    {
    }
    void SetFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetSelectedOptionBgColorImpl(Ark_NativePointer node,
                                      const Opt_ResourceColor* value)
    {
    }
    void SetSelectedOptionFontImpl(Ark_NativePointer node,
                                   const Opt_Font* value)
    {
    }
    void SetSelectedOptionFontColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetOptionBgColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetOptionFontImpl(Ark_NativePointer node,
                           const Opt_Font* value)
    {
    }
    void SetOptionFontColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetOnSelectImpl(Ark_NativePointer node,
                         const Opt_OnSelectCallback* value)
    {
    }
    void SetSpaceImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void SetArrowPositionImpl(Ark_NativePointer node,
                              const Opt_ArrowPosition* value)
    {
    }
    void SetOptionWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Dimension_OptionWidthMode* value)
    {
    }
    void SetOptionHeightImpl(Ark_NativePointer node,
                             const Opt_Dimension* value)
    {
    }
    void SetMenuBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
    {
    }
    void SetMenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                        const Opt_BlurStyle* value)
    {
    }
    void SetControlSizeImpl(Ark_NativePointer node,
                            const Opt_ControlSize* value)
    {
    }
    void SetTextModifierImpl(Ark_NativePointer node,
                             const Opt_TextModifier* value)
    {
    }
    void SetArrowModifierImpl(Ark_NativePointer node,
                              const Opt_SymbolGlyphModifier* value)
    {
    }
    void SetOptionTextModifierImpl(Ark_NativePointer node,
                                   const Opt_TextModifier* value)
    {
    }
    void SetSelectedOptionTextModifierImpl(Ark_NativePointer node,
                                           const Opt_TextModifier* value)
    {
    }
    void SetDividerStyleImpl(Ark_NativePointer node,
                             const Opt_DividerStyleOptions* value)
    {
    }
    void SetAvoidanceImpl(Ark_NativePointer node,
                          const Opt_AvoidanceMode* value)
    {
    }
    void SetMenuOutlineImpl(Ark_NativePointer node,
                            const Opt_MenuOutlineOptions* value)
    {
    }
    void SetShowInSubWindowImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetShowDefaultSelectedIconImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void SetMenuAlignImpl(Ark_NativePointer node,
                          const Opt_MenuAlignType* alignType,
                          const Opt_Offset* offset)
    {
    }
    } // SelectAttributeModifier
    namespace ShapeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ShapeModifier
    namespace ShapeInterfaceModifier {
    void SetShapeOptionsImpl(Ark_NativePointer node,
                             const Opt_image_PixelMap* value)
    {
    }
    } // ShapeInterfaceModifier
    namespace ShapeAttributeModifier {
    void SetViewPortImpl(Ark_NativePointer node,
                         const Opt_ViewportRect* value)
    {
    }
    void SetStrokeImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void SetFillImpl(Ark_NativePointer node,
                     const Opt_ResourceColor* value)
    {
    }
    void SetStrokeDashOffsetImpl(Ark_NativePointer node,
                                 const Opt_Union_F64_String* value)
    {
    }
    void SetStrokeDashArrayImpl(Ark_NativePointer node,
                                const Opt_Array_Length* value)
    {
    }
    void SetStrokeLineCapImpl(Ark_NativePointer node,
                              const Opt_LineCapStyle* value)
    {
    }
    void SetStrokeLineJoinImpl(Ark_NativePointer node,
                               const Opt_LineJoinStyle* value)
    {
    }
    void SetStrokeMiterLimitImpl(Ark_NativePointer node,
                                 const Opt_Union_F64_String* value)
    {
    }
    void SetStrokeOpacityImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetFillOpacityImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetStrokeWidthImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String* value)
    {
    }
    void SetAntiAliasImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetMeshImpl(Ark_NativePointer node,
                     const Opt_Array_Float64* value,
                     const Opt_Int32* column,
                     const Opt_Int32* row)
    {
    }
    } // ShapeAttributeModifier
    namespace SideBarContainerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SideBarContainerModifier
    namespace SideBarContainerInterfaceModifier {
    void SetSideBarContainerOptionsImpl(Ark_NativePointer node,
                                        const Opt_SideBarContainerType* type)
    {
    }
    } // SideBarContainerInterfaceModifier
    namespace SideBarContainerAttributeModifier {
    void SetShowSideBarImpl(Ark_NativePointer node,
                            const Opt_Union_Boolean_Bindable* value)
    {
    }
    void SetControlButtonImpl(Ark_NativePointer node,
                              const Opt_ButtonStyle* value)
    {
    }
    void SetShowControlButtonImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetSideBarWidthImpl(Ark_NativePointer node,
                             const Opt_Union_Length_Bindable* value)
    {
    }
    void SetMinSideBarWidth0Impl(Ark_NativePointer node,
                                 const Opt_Number* value)
    {
    }
    void SetMaxSideBarWidth0Impl(Ark_NativePointer node,
                                 const Opt_Number* value)
    {
    }
    void SetMinSideBarWidth1Impl(Ark_NativePointer node,
                                 const Opt_Length* value)
    {
    }
    void SetMaxSideBarWidth1Impl(Ark_NativePointer node,
                                 const Opt_Length* value)
    {
    }
    void SetAutoHideImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetSideBarPositionImpl(Ark_NativePointer node,
                                const Opt_SideBarPosition* value)
    {
    }
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_DividerStyle* value)
    {
    }
    void SetMinContentWidthImpl(Ark_NativePointer node,
                                const Opt_Dimension* value)
    {
    }
    } // SideBarContainerAttributeModifier
    namespace SliderModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SliderModifier
    namespace SliderInterfaceModifier {
    void SetSliderOptionsImpl(Ark_NativePointer node,
                              const Opt_SliderOptions* options)
    {
    }
    } // SliderInterfaceModifier
    namespace SliderAttributeModifier {
    void SetBlockColorImpl(Ark_NativePointer node,
                           const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SetTrackColorImpl(Ark_NativePointer node,
                           const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SetShowSteps0Impl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetTrackThicknessImpl(Ark_NativePointer node,
                               const Opt_Length* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_F64_SliderChangeMode_Void* value)
    {
    }
    void SetBlockBorderColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetBlockBorderWidthImpl(Ark_NativePointer node,
                                 const Opt_Length* value)
    {
    }
    void SetStepColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetTrackBorderRadiusImpl(Ark_NativePointer node,
                                  const Opt_Length* value)
    {
    }
    void SetSelectedBorderRadiusImpl(Ark_NativePointer node,
                                     const Opt_Dimension* value)
    {
    }
    void SetBlockSizeImpl(Ark_NativePointer node,
                          const Opt_SizeOptions* value)
    {
    }
    void SetBlockStyleImpl(Ark_NativePointer node,
                           const Opt_SliderBlockStyle* value)
    {
    }
    void SetStepSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetSliderInteractionModeImpl(Ark_NativePointer node,
                                      const Opt_SliderInteraction* value)
    {
    }
    void SetMinResponsiveDistanceImpl(Ark_NativePointer node,
                                      const Opt_Float64* value)
    {
    }
    void SetSlideRangeImpl(Ark_NativePointer node,
                           const Opt_SlideRange* value)
    {
    }
    void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                        const Opt_CrownSensitivity* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetShowSteps1Impl(Ark_NativePointer node,
                           const Opt_Boolean* value,
                           const Opt_SliderShowStepOptions* options)
    {
    }
    void SetShowTipsImpl(Ark_NativePointer node,
                         const Opt_Boolean* value,
                         const Opt_ResourceStr* content)
    {
    }
    } // SliderAttributeModifier
    namespace SpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SpanModifier
    namespace SpanInterfaceModifier {
    void SetSpanOptionsImpl(Ark_NativePointer node,
                            const Ark_Union_String_Resource* value)
    {
    }
    } // SpanInterfaceModifier
    namespace SpanAttributeModifier {
    void SetFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_Union_String_Resource* value)
    {
    }
    void SetDecorationImpl(Ark_NativePointer node,
                           const Opt_DecorationStyleInterface* value)
    {
    }
    void SetLetterSpacingImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String* value)
    {
    }
    void SetTextCaseImpl(Ark_NativePointer node,
                         const Opt_TextCase* value)
    {
    }
    void SetLineHeightImpl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void SetTextShadowImpl(Ark_NativePointer node,
                           const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void SetTextBackgroundStyleImpl(Ark_NativePointer node,
                                    const Opt_TextBackgroundStyle* value)
    {
    }
    void SetBaselineOffsetImpl(Ark_NativePointer node,
                               const Opt_LengthMetrics* value)
    {
    }
    void SetKeyImpl(Ark_NativePointer node,
                    const Opt_String* value)
    {
    }
    void SetIdImpl(Ark_NativePointer node,
                   const Opt_String* value)
    {
    }
    void SetOnClick0Impl(Ark_NativePointer node,
                         const Opt_Callback_ClickEvent_Void* value)
    {
    }
    void SetOnHoverImpl(Ark_NativePointer node,
                        const Opt_HoverCallback* value)
    {
    }
    void SetOnClick1Impl(Ark_NativePointer node,
                         const Opt_Callback_ClickEvent_Void* event,
                         const Opt_Float64* distanceThreshold)
    {
    }
    } // SpanAttributeModifier
    namespace StackModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // StackModifier
    namespace StackInterfaceModifier {
    void SetStackOptionsImpl(Ark_NativePointer node,
                             const Opt_StackOptions* options)
    {
    }
    } // StackInterfaceModifier
    namespace StackAttributeModifier {
    void SetAlignContentImpl(Ark_NativePointer node,
                             const Opt_Alignment* value)
    {
    }
    } // StackAttributeModifier
    namespace StepperModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // StepperModifier
    namespace StepperInterfaceModifier {
    void SetStepperOptionsImpl(Ark_NativePointer node,
                               const Opt_StepperOptions* value)
    {
    }
    } // StepperInterfaceModifier
    namespace StepperAttributeModifier {
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void SetOnSkipImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Number_Void* value)
    {
    }
    void SetOnNextImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Number_Void* value)
    {
    }
    void SetOnPreviousImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_Void* value)
    {
    }
    } // StepperAttributeModifier
    namespace StepperItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // StepperItemModifier
    namespace StepperItemInterfaceModifier {
    void SetStepperItemOptionsImpl(Ark_NativePointer node)
    {
    }
    } // StepperItemInterfaceModifier
    namespace StepperItemAttributeModifier {
    void SetPrevLabelImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void SetNextLabelImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void SetStatusImpl(Ark_NativePointer node,
                       const Opt_ItemState* value)
    {
    }
    } // StepperItemAttributeModifier
    namespace SwiperModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SwiperModifier
    namespace SwiperInterfaceModifier {
    void SetSwiperOptionsImpl(Ark_NativePointer node,
                              const Opt_SwiperController* controller)
    {
    }
    } // SwiperInterfaceModifier
    namespace SwiperAttributeModifier {
    void SetIndexImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Bindable* value)
    {
    }
    void SetAutoPlay0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetIntervalImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void SetIndicatorImpl(Ark_NativePointer node,
                          const Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean* value)
    {
    }
    void SetLoopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void SetDurationImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void SetVerticalImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetItemSpaceImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
    {
    }
    void SetDisplayModeImpl(Ark_NativePointer node,
                            const Opt_SwiperDisplayMode* value)
    {
    }
    void SetCachedCount0Impl(Ark_NativePointer node,
                             const Opt_Number* value)
    {
    }
    void SetEffectModeImpl(Ark_NativePointer node,
                           const Opt_EdgeEffect* value)
    {
    }
    void SetDisableSwipeImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetCurveImpl(Ark_NativePointer node,
                      const Opt_Union_Curve_String_ICurve* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
    {
    }
    void SetOnSelectedImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Void* value)
    {
    }
    void SetOnUnselectedImpl(Ark_NativePointer node,
                             const Opt_Callback_Number_Void* value)
    {
    }
    void SetOnAnimationStartImpl(Ark_NativePointer node,
                                 const Opt_OnSwiperAnimationStartCallback* value)
    {
    }
    void SetOnAnimationEndImpl(Ark_NativePointer node,
                               const Opt_OnSwiperAnimationEndCallback* value)
    {
    }
    void SetOnGestureSwipeImpl(Ark_NativePointer node,
                               const Opt_OnSwiperGestureSwipeCallback* value)
    {
    }
    void SetNestedScrollImpl(Ark_NativePointer node,
                             const Opt_SwiperNestedScrollMode* value)
    {
    }
    void SetCustomContentTransitionImpl(Ark_NativePointer node,
                                        const Opt_SwiperContentAnimatedTransition* value)
    {
    }
    void SetOnContentDidScrollImpl(Ark_NativePointer node,
                                   const Opt_ContentDidScrollCallback* value)
    {
    }
    void SetIndicatorInteractiveImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetPageFlipModeImpl(Ark_NativePointer node,
                             const Opt_PageFlipMode* value)
    {
    }
    void SetOnContentWillScrollImpl(Ark_NativePointer node,
                                    const Opt_ContentWillScrollCallback* value)
    {
    }
    void SetAutoPlay1Impl(Ark_NativePointer node,
                          const Opt_Boolean* autoPlay,
                          const Opt_AutoPlayOptions* options)
    {
    }
    void SetDisplayArrowImpl(Ark_NativePointer node,
                             const Opt_Union_ArrowStyle_Boolean* value,
                             const Opt_Boolean* isHoverShow)
    {
    }
    void SetCachedCount1Impl(Ark_NativePointer node,
                             const Opt_Number* count,
                             const Opt_Boolean* isShown)
    {
    }
    void SetDisplayCountImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String_SwiperAutoFill* value,
                             const Opt_Boolean* swipeByGroup)
    {
    }
    void SetPrevMarginImpl(Ark_NativePointer node,
                           const Opt_Length* value,
                           const Opt_Boolean* ignoreBlank)
    {
    }
    void SetNextMarginImpl(Ark_NativePointer node,
                           const Opt_Length* value,
                           const Opt_Boolean* ignoreBlank)
    {
    }
    } // SwiperAttributeModifier
    namespace SymbolGlyphModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SymbolGlyphModifier
    namespace SymbolGlyphInterfaceModifier {
    void SetSymbolGlyphOptionsImpl(Ark_NativePointer node,
                                   const Opt_Resource* value)
    {
    }
    } // SymbolGlyphInterfaceModifier
    namespace SymbolGlyphAttributeModifier {
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_Array_ResourceColor* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetEffectStrategyImpl(Ark_NativePointer node,
                               const Opt_SymbolEffectStrategy* value)
    {
    }
    void SetRenderingStrategyImpl(Ark_NativePointer node,
                                  const Opt_SymbolRenderingStrategy* value)
    {
    }
    void SetSymbolEffect0Impl(Ark_NativePointer node,
                              const Opt_SymbolEffect* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetSymbolEffect1Impl(Ark_NativePointer node,
                              const Opt_SymbolEffect* symbolEffect,
                              const Opt_Boolean* isActive)
    {
    }
    void SetSymbolEffect2Impl(Ark_NativePointer node,
                              const Opt_SymbolEffect* symbolEffect,
                              const Opt_Int32* triggerValue)
    {
    }
    } // SymbolGlyphAttributeModifier
    namespace SymbolSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // SymbolSpanModifier
    namespace SymbolSpanInterfaceModifier {
    void SetSymbolSpanOptionsImpl(Ark_NativePointer node,
                                  const Ark_Resource* value)
    {
    }
    } // SymbolSpanInterfaceModifier
    namespace SymbolSpanAttributeModifier {
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_Array_ResourceColor* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetEffectStrategyImpl(Ark_NativePointer node,
                               const Opt_SymbolEffectStrategy* value)
    {
    }
    void SetRenderingStrategyImpl(Ark_NativePointer node,
                                  const Opt_SymbolRenderingStrategy* value)
    {
    }
    void SetKeyImpl(Ark_NativePointer node,
                    const Opt_String* value)
    {
    }
    void SetIdImpl(Ark_NativePointer node,
                   const Opt_String* value)
    {
    }
    } // SymbolSpanAttributeModifier
    namespace TabContentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TabContentModifier
    namespace TabContentInterfaceModifier {
    void SetTabContentOptionsImpl(Ark_NativePointer node)
    {
    }
    } // TabContentInterfaceModifier
    namespace TabContentAttributeModifier {
    void SetTabBarImpl(Ark_NativePointer node,
                       const Opt_Union_ComponentContent_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomBuilder_TabBarOptions* value)
    {
    }
    void SetOnWillShowImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* value)
    {
    }
    void SetOnWillHideImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* value)
    {
    }
    } // TabContentAttributeModifier
    namespace TabsModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TabsModifier
    namespace TabsInterfaceModifier {
    void SetTabsOptionsImpl(Ark_NativePointer node,
                            const Opt_TabsOptions* options)
    {
    }
    } // TabsInterfaceModifier
    namespace TabsAttributeModifier {
    void SetVerticalImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetBarPositionImpl(Ark_NativePointer node,
                            const Opt_BarPosition* value)
    {
    }
    void SetScrollableImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetBarWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetAnimationCurveImpl(Ark_NativePointer node,
                               const Opt_Union_Curve_ICurve* value)
    {
    }
    void SetAnimationDurationImpl(Ark_NativePointer node,
                                  const Opt_Int32* value)
    {
    }
    void SetAnimationModeImpl(Ark_NativePointer node,
                              const Opt_AnimationMode* value)
    {
    }
    void SetEdgeEffectImpl(Ark_NativePointer node,
                           const Opt_EdgeEffect* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_I32_Void* value)
    {
    }
    void SetOnSelectedImpl(Ark_NativePointer node,
                           const Opt_Callback_I32_Void* value)
    {
    }
    void SetOnTabBarClickImpl(Ark_NativePointer node,
                              const Opt_Callback_I32_Void* value)
    {
    }
    void SetOnUnselectedImpl(Ark_NativePointer node,
                             const Opt_Callback_I32_Void* value)
    {
    }
    void SetOnAnimationStartImpl(Ark_NativePointer node,
                                 const Opt_OnTabsAnimationStartCallback* value)
    {
    }
    void SetOnAnimationEndImpl(Ark_NativePointer node,
                               const Opt_OnTabsAnimationEndCallback* value)
    {
    }
    void SetOnGestureSwipeImpl(Ark_NativePointer node,
                               const Opt_OnTabsGestureSwipeCallback* value)
    {
    }
    void SetFadingEdgeImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_DividerStyle* value)
    {
    }
    void SetBarOverlapImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetBarBackgroundColorImpl(Ark_NativePointer node,
                                   const Opt_ResourceColor* value)
    {
    }
    void SetBarGridAlignImpl(Ark_NativePointer node,
                             const Opt_BarGridColumnOptions* value)
    {
    }
    void SetCustomContentTransitionImpl(Ark_NativePointer node,
                                        const Opt_TabsCustomContentTransitionCallback* value)
    {
    }
    void SetBarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                        const Opt_BlurStyle* value)
    {
    }
    void SetPageFlipModeImpl(Ark_NativePointer node,
                             const Opt_PageFlipMode* value)
    {
    }
    void SetBarBackgroundEffectImpl(Ark_NativePointer node,
                                    const Opt_BackgroundEffectOptions* value)
    {
    }
    void SetOnContentWillChangeImpl(Ark_NativePointer node,
                                    const Opt_OnTabsContentWillChangeCallback* value)
    {
    }
    void SetOnContentDidScrollImpl(Ark_NativePointer node,
                                   const Opt_OnTabsContentDidScrollCallback* value)
    {
    }
    void SetBarModeImpl(Ark_NativePointer node,
                        const Opt_BarMode* value,
                        const Opt_ScrollableBarModeOptions* options)
    {
    }
    void SetBarHeightImpl(Ark_NativePointer node,
                          const Opt_Length* height,
                          const Opt_Boolean* noMinHeightLimit)
    {
    }
    void SetBarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                        const Opt_BlurStyle* style,
                                        const Opt_BackgroundBlurStyleOptions* options)
    {
    }
    void SetCachedMaxCountImpl(Ark_NativePointer node,
                               const Opt_Int32* count,
                               const Opt_TabsCacheMode* mode)
    {
    }
    } // TabsAttributeModifier
    namespace TextModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextModifier
    namespace TextInterfaceModifier {
    void SetTextOptionsImpl(Ark_NativePointer node,
                            const Opt_Union_String_Resource* content,
                            const Opt_TextOptions* value)
    {
    }
    } // TextInterfaceModifier
    namespace TextAttributeModifier {
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMaxFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetLineSpacingImpl(Ark_NativePointer node,
                            const Opt_LengthMetrics* value)
    {
    }
    void SetTextAlignImpl(Ark_NativePointer node,
                          const Opt_TextAlign* value)
    {
    }
    void SetLineHeightImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetTextOverflowImpl(Ark_NativePointer node,
                             const Opt_TextOverflowOptions* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_Union_String_Resource* value)
    {
    }
    void SetMaxLinesImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetDecorationImpl(Ark_NativePointer node,
                           const Opt_DecorationStyleInterface* value)
    {
    }
    void SetLetterSpacingImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String* value)
    {
    }
    void SetTextCaseImpl(Ark_NativePointer node,
                         const Opt_TextCase* value)
    {
    }
    void SetBaselineOffsetImpl(Ark_NativePointer node,
                               const Opt_Union_F64_String* value)
    {
    }
    void SetCopyOptionImpl(Ark_NativePointer node,
                           const Opt_CopyOptions* value)
    {
    }
    void SetDraggableImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetTextShadowImpl(Ark_NativePointer node,
                           const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                     const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void SetTextIndentImpl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void SetWordBreakImpl(Ark_NativePointer node,
                          const Opt_WordBreak* value)
    {
    }
    void SetLineBreakStrategyImpl(Ark_NativePointer node,
                                  const Opt_LineBreakStrategy* value)
    {
    }
    void SetOnCopyImpl(Ark_NativePointer node,
                       const Opt_Callback_String_Void* value)
    {
    }
    void SetCaretColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetEllipsisModeImpl(Ark_NativePointer node,
                             const Opt_EllipsisMode* value)
    {
    }
    void SetEnableDataDetectorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetDataDetectorConfigImpl(Ark_NativePointer node,
                                   const Opt_TextDataDetectorConfig* value)
    {
    }
    void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                      const Opt_Callback_I32_I32_Void* value)
    {
    }
    void SetFontFeatureImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void SetMarqueeOptionsImpl(Ark_NativePointer node,
                               const Opt_TextMarqueeOptions* value)
    {
    }
    void SetOnMarqueeStateChangeImpl(Ark_NativePointer node,
                                     const Opt_Callback_MarqueeState_Void* value)
    {
    }
    void SetPrivacySensitiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetTextSelectableImpl(Ark_NativePointer node,
                               const Opt_TextSelectableMode* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetHalfLeadingImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetFontImpl(Ark_NativePointer node,
                     const Opt_Font* fontValue,
                     const Opt_FontSettingOptions* options)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* weight,
                           const Opt_FontSettingOptions* options)
    {
    }
    void SetSelectionImpl(Ark_NativePointer node,
                          const Opt_Int32* selectionStart,
                          const Opt_Int32* selectionEnd)
    {
    }
    void SetBindSelectionMenuImpl(Ark_NativePointer node,
                                  const Opt_TextSpanType* spanType,
                                  const Opt_CustomNodeBuilder* content,
                                  const Opt_TextResponseType* responseType,
                                  const Opt_SelectionMenuOptions* options)
    {
    }
    } // TextAttributeModifier
    namespace TextAreaModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextAreaModifier
    namespace TextAreaInterfaceModifier {
    void SetTextAreaOptionsImpl(Ark_NativePointer node,
                                const Opt_TextAreaOptions* value)
    {
    }
    } // TextAreaInterfaceModifier
    namespace TextAreaAttributeModifier {
    void SetPlaceholderColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetPlaceholderFontImpl(Ark_NativePointer node,
                                const Opt_Font* value)
    {
    }
    void SetEnterKeyTypeImpl(Ark_NativePointer node,
                             const Opt_EnterKeyType* value)
    {
    }
    void SetTextAlignImpl(Ark_NativePointer node,
                          const Opt_TextAlign* value)
    {
    }
    void SetCaretColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_ResourceStr* value)
    {
    }
    void SetTextOverflowImpl(Ark_NativePointer node,
                             const Opt_TextOverflow* value)
    {
    }
    void SetTextIndentImpl(Ark_NativePointer node,
                           const Opt_Dimension* value)
    {
    }
    void SetCaretStyleImpl(Ark_NativePointer node,
                           const Opt_CaretStyle* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetOnSubmitImpl(Ark_NativePointer node,
                         const Opt_TextAreaSubmitCallback* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                      const Opt_Callback_I32_I32_Void* value)
    {
    }
    void SetOnContentScrollImpl(Ark_NativePointer node,
                                const Opt_Callback_F64_F64_Void* value)
    {
    }
    void SetOnEditChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetOnCopyImpl(Ark_NativePointer node,
                       const Opt_Callback_String_Void* value)
    {
    }
    void SetOnCutImpl(Ark_NativePointer node,
                      const Opt_Callback_String_Void* value)
    {
    }
    void SetOnPasteImpl(Ark_NativePointer node,
                        const Opt_Callback_String_PasteEvent_Void* value)
    {
    }
    void SetCopyOptionImpl(Ark_NativePointer node,
                           const Opt_CopyOptions* value)
    {
    }
    void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetMaxLengthImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
    {
    }
    void SetStyleImpl(Ark_NativePointer node,
                      const Opt_TextContentStyle* value)
    {
    }
    void SetBarStateImpl(Ark_NativePointer node,
                         const Opt_BarState* value)
    {
    }
    void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMaxFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                     const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void SetMaxLinesImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetWordBreakImpl(Ark_NativePointer node,
                          const Opt_WordBreak* value)
    {
    }
    void SetLineBreakStrategyImpl(Ark_NativePointer node,
                                  const Opt_LineBreakStrategy* value)
    {
    }
    void SetDecorationImpl(Ark_NativePointer node,
                           const Opt_TextDecorationOptions* value)
    {
    }
    void SetLetterSpacingImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetLineSpacingImpl(Ark_NativePointer node,
                            const Opt_LengthMetrics* value)
    {
    }
    void SetLineHeightImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetTypeImpl(Ark_NativePointer node,
                     const Opt_TextAreaType* value)
    {
    }
    void SetEnableAutoFillImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetContentTypeImpl(Ark_NativePointer node,
                            const Opt_ContentType* value)
    {
    }
    void SetFontFeatureImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void SetOnWillInsertImpl(Ark_NativePointer node,
                             const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void SetOnDidInsertImpl(Ark_NativePointer node,
                            const Opt_Callback_InsertValue_Void* value)
    {
    }
    void SetOnWillDeleteImpl(Ark_NativePointer node,
                             const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void SetOnDidDeleteImpl(Ark_NativePointer node,
                            const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetEnablePreviewTextImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                       const Opt_AutoCapitalizationMode* value)
    {
    }
    void SetHalfLeadingImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetEllipsisModeImpl(Ark_NativePointer node,
                             const Opt_EllipsisMode* value)
    {
    }
    void SetStopBackPressImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetOnWillChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                                   const Opt_KeyboardAppearance* value)
    {
    }
    void SetInputFilterImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value,
                            const Opt_Callback_String_Void* error)
    {
    }
    void SetShowCounterImpl(Ark_NativePointer node,
                            const Opt_Boolean* value,
                            const Opt_InputCounterOptions* options)
    {
    }
    void SetCustomKeyboardImpl(Ark_NativePointer node,
                               const Opt_CustomNodeBuilder* value,
                               const Opt_KeyboardOptions* options)
    {
    }
    } // TextAreaAttributeModifier
    namespace TextClockModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextClockModifier
    namespace TextClockInterfaceModifier {
    void SetTextClockOptionsImpl(Ark_NativePointer node,
                                 const Opt_TextClockOptions* options)
    {
    }
    } // TextClockInterfaceModifier
    namespace TextClockAttributeModifier {
    void SetFormatImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
    {
    }
    void SetOnDateChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_I64_Void* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_ResourceStr* value)
    {
    }
    void SetTextShadowImpl(Ark_NativePointer node,
                           const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void SetFontFeatureImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void SetDateTimeOptionsImpl(Ark_NativePointer node,
                                const Opt_intl_DateTimeOptions* value)
    {
    }
    } // TextClockAttributeModifier
    namespace TextInputModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextInputModifier
    namespace TextInputInterfaceModifier {
    void SetTextInputOptionsImpl(Ark_NativePointer node,
                                 const Opt_TextInputOptions* value)
    {
    }
    } // TextInputInterfaceModifier
    namespace TextInputAttributeModifier {
    void SetTypeImpl(Ark_NativePointer node,
                     const Opt_InputType* value)
    {
    }
    void SetContentTypeImpl(Ark_NativePointer node,
                            const Opt_ContentType* value)
    {
    }
    void SetPlaceholderColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetTextOverflowImpl(Ark_NativePointer node,
                             const Opt_TextOverflow* value)
    {
    }
    void SetTextIndentImpl(Ark_NativePointer node,
                           const Opt_Dimension* value)
    {
    }
    void SetPlaceholderFontImpl(Ark_NativePointer node,
                                const Opt_Font* value)
    {
    }
    void SetEnterKeyTypeImpl(Ark_NativePointer node,
                             const Opt_EnterKeyType* value)
    {
    }
    void SetCaretColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SetOnEditChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetOnSubmitImpl(Ark_NativePointer node,
                         const Opt_OnSubmitCallback* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                      const Opt_OnTextSelectionChangeCallback* value)
    {
    }
    void SetOnContentScrollImpl(Ark_NativePointer node,
                                const Opt_OnContentScrollCallback* value)
    {
    }
    void SetMaxLengthImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_String* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_ResourceStr* value)
    {
    }
    void SetOnCopyImpl(Ark_NativePointer node,
                       const Opt_Callback_String_Void* value)
    {
    }
    void SetOnCutImpl(Ark_NativePointer node,
                      const Opt_Callback_String_Void* value)
    {
    }
    void SetOnPasteImpl(Ark_NativePointer node,
                        const Opt_OnPasteCallback* value)
    {
    }
    void SetCopyOptionImpl(Ark_NativePointer node,
                           const Opt_CopyOptions* value)
    {
    }
    void SetShowPasswordIconImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetTextAlignImpl(Ark_NativePointer node,
                          const Opt_TextAlign* value)
    {
    }
    void SetStyleImpl(Ark_NativePointer node,
                      const Opt_Union_TextInputStyle_TextContentStyle* value)
    {
    }
    void SetCaretStyleImpl(Ark_NativePointer node,
                           const Opt_CaretStyle* value)
    {
    }
    void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                        const Opt_ResourceColor* value)
    {
    }
    void SetCaretPositionImpl(Ark_NativePointer node,
                              const Opt_Int32* value)
    {
    }
    void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetPasswordIconImpl(Ark_NativePointer node,
                             const Opt_PasswordIcon* value)
    {
    }
    void SetShowErrorImpl(Ark_NativePointer node,
                          const Opt_ResourceStr* value)
    {
    }
    void SetShowUnitImpl(Ark_NativePointer node,
                         const Opt_CustomNodeBuilder* value)
    {
    }
    void SetShowUnderlineImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetUnderlineColorImpl(Ark_NativePointer node,
                               const Opt_Union_ResourceColor_UnderlineColor* value)
    {
    }
    void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    void SetBarStateImpl(Ark_NativePointer node,
                         const Opt_BarState* value)
    {
    }
    void SetMaxLinesImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void SetWordBreakImpl(Ark_NativePointer node,
                          const Opt_WordBreak* value)
    {
    }
    void SetLineBreakStrategyImpl(Ark_NativePointer node,
                                  const Opt_LineBreakStrategy* value)
    {
    }
    void SetCancelButton0Impl(Ark_NativePointer node,
                              const Opt_CancelButtonOptions* value)
    {
    }
    void SetCancelButton1Impl(Ark_NativePointer node,
                              const Opt_CancelButtonSymbolOptions* value)
    {
    }
    void SetSelectAllImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMaxFontSizeImpl(Ark_NativePointer node,
                            const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetMinFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetMaxFontScaleImpl(Ark_NativePointer node,
                             const Opt_Union_F64_Resource* value)
    {
    }
    void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                     const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void SetEnableAutoFillImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetDecorationImpl(Ark_NativePointer node,
                           const Opt_TextDecorationOptions* value)
    {
    }
    void SetLetterSpacingImpl(Ark_NativePointer node,
                              const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetLineHeightImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String_Resource* value)
    {
    }
    void SetPasswordRulesImpl(Ark_NativePointer node,
                              const Opt_String* value)
    {
    }
    void SetFontFeatureImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void SetShowPasswordImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetOnSecurityStateChangeImpl(Ark_NativePointer node,
                                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetOnWillInsertImpl(Ark_NativePointer node,
                             const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void SetOnDidInsertImpl(Ark_NativePointer node,
                            const Opt_Callback_InsertValue_Void* value)
    {
    }
    void SetOnWillDeleteImpl(Ark_NativePointer node,
                             const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void SetOnDidDeleteImpl(Ark_NativePointer node,
                            const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetEnablePreviewTextImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                       const Opt_AutoCapitalizationMode* value)
    {
    }
    void SetHalfLeadingImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetEllipsisModeImpl(Ark_NativePointer node,
                             const Opt_EllipsisMode* value)
    {
    }
    void SetStopBackPressImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void SetOnWillChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                                   const Opt_KeyboardAppearance* value)
    {
    }
    void SetInputFilterImpl(Ark_NativePointer node,
                            const Opt_ResourceStr* value,
                            const Opt_Callback_String_Void* error)
    {
    }
    void SetCustomKeyboardImpl(Ark_NativePointer node,
                               const Opt_CustomNodeBuilder* value,
                               const Opt_KeyboardOptions* options)
    {
    }
    void SetShowCounterImpl(Ark_NativePointer node,
                            const Opt_Boolean* value,
                            const Opt_InputCounterOptions* options)
    {
    }
    } // TextInputAttributeModifier
    namespace TextPickerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextPickerModifier
    namespace TextPickerInterfaceModifier {
    void SetTextPickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_TextPickerOptions* options)
    {
    }
    } // TextPickerInterfaceModifier
    namespace TextPickerAttributeModifier {
    void SetDefaultPickerItemHeightImpl(Ark_NativePointer node,
                                        const Opt_Union_F64_String* value)
    {
    }
    void SetCanLoopImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SetDisappearTextStyleImpl(Ark_NativePointer node,
                                   const Opt_PickerTextStyle* value)
    {
    }
    void SetTextStyleImpl(Ark_NativePointer node,
                          const Opt_PickerTextStyle* value)
    {
    }
    void SetSelectedTextStyleImpl(Ark_NativePointer node,
                                  const Opt_PickerTextStyle* value)
    {
    }
    void SetDisableTextStyleAnimationImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void SetDefaultTextStyleImpl(Ark_NativePointer node,
                                 const Opt_TextPickerTextStyle* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnTextPickerChangeCallback* value)
    {
    }
    void SetOnScrollStopImpl(Ark_NativePointer node,
                             const Opt_TextPickerScrollStopCallback* value)
    {
    }
    void SetOnEnterSelectedAreaImpl(Ark_NativePointer node,
                                    const Opt_TextPickerEnterSelectedAreaCallback* value)
    {
    }
    void SetSelectedIndexImpl(Ark_NativePointer node,
                              const Opt_Union_I32_Array_I32* value)
    {
    }
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_DividerOptions* value)
    {
    }
    void SetGradientHeightImpl(Ark_NativePointer node,
                               const Opt_Dimension* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                        const Opt_CrownSensitivity* value)
    {
    }
    } // TextPickerAttributeModifier
    namespace TextTimerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TextTimerModifier
    namespace TextTimerInterfaceModifier {
    void SetTextTimerOptionsImpl(Ark_NativePointer node,
                                 const Opt_TextTimerOptions* options)
    {
    }
    } // TextTimerInterfaceModifier
    namespace TextTimerAttributeModifier {
    void SetFormatImpl(Ark_NativePointer node,
                       const Opt_String* value)
    {
    }
    void SetFontColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SetFontSizeImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void SetFontStyleImpl(Ark_NativePointer node,
                          const Opt_FontStyle* value)
    {
    }
    void SetFontWeightImpl(Ark_NativePointer node,
                           const Opt_Union_I32_FontWeight_ResourceStr* value)
    {
    }
    void SetFontFamilyImpl(Ark_NativePointer node,
                           const Opt_ResourceStr* value)
    {
    }
    void SetOnTimerImpl(Ark_NativePointer node,
                        const Opt_TimerCallback* value)
    {
    }
    void SetTextShadowImpl(Ark_NativePointer node,
                           const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    } // TextTimerAttributeModifier
    namespace TimePickerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // TimePickerModifier
    namespace TimePickerInterfaceModifier {
    void SetTimePickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_TimePickerOptions* options)
    {
    }
    } // TimePickerInterfaceModifier
    namespace TimePickerAttributeModifier {
    void SetUseMilitaryTimeImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetLoopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void SetDisappearTextStyleImpl(Ark_NativePointer node,
                                   const Opt_PickerTextStyle* value)
    {
    }
    void SetTextStyleImpl(Ark_NativePointer node,
                          const Opt_PickerTextStyle* value)
    {
    }
    void SetSelectedTextStyleImpl(Ark_NativePointer node,
                                  const Opt_PickerTextStyle* value)
    {
    }
    void SetDateTimeOptionsImpl(Ark_NativePointer node,
                                const Opt_intl_DateTimeOptions* value)
    {
    }
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_OnTimePickerChangeCallback* value)
    {
    }
    void SetOnEnterSelectedAreaImpl(Ark_NativePointer node,
                                    const Opt_Callback_TimePickerResult_Void* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                        const Opt_CrownSensitivity* value)
    {
    }
    void SetEnableCascadeImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    } // TimePickerAttributeModifier
    namespace ToggleModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ToggleModifier
    namespace ToggleInterfaceModifier {
    void SetToggleOptionsImpl(Ark_NativePointer node,
                              const Ark_ToggleOptions* options)
    {
    }
    } // ToggleInterfaceModifier
    namespace ToggleAttributeModifier {
    void SetOnChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
    {
    }
    void SetSelectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SetSwitchPointColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void SetSwitchStyleImpl(Ark_NativePointer node,
                            const Opt_SwitchStyle* value)
    {
    }
    } // ToggleAttributeModifier
    namespace ToolBarItemModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ToolBarItemModifier
    namespace ToolBarItemInterfaceModifier {
    void SetToolBarItemOptionsImpl(Ark_NativePointer node,
                                   const Opt_ToolBarItemOptions* options)
    {
    }
    } // ToolBarItemInterfaceModifier
    namespace UIExtensionComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // UIExtensionComponentModifier
    namespace UIExtensionComponentInterfaceModifier {
    void SetUIExtensionComponentOptionsImpl(Ark_NativePointer node,
                                            Ark_Want want,
                                            const Opt_UIExtensionOptions* options)
    {
    }
    } // UIExtensionComponentInterfaceModifier
    namespace UIExtensionComponentAttributeModifier {
    void SetOnRemoteReadyImpl(Ark_NativePointer node,
                              const Opt_Callback_UIExtensionProxy_Void* value)
    {
    }
    void SetOnReceiveImpl(Ark_NativePointer node,
                          const Opt_Callback_Map_String_RecordData_Void* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_ErrorCallback_Ohos_Base_BusinessError* value)
    {
    }
    void SetOnTerminatedImpl(Ark_NativePointer node,
                             const Opt_Callback_TerminationInfo_Void* value)
    {
    }
    void SetOnDrawReadyImpl(Ark_NativePointer node,
                            const Opt_Callback_Void* value)
    {
    }
    } // UIExtensionComponentAttributeModifier
    namespace VideoModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // VideoModifier
    namespace VideoInterfaceModifier {
    void SetVideoOptionsImpl(Ark_NativePointer node,
                             const Ark_VideoOptions* value)
    {
    }
    } // VideoInterfaceModifier
    namespace VideoAttributeModifier {
    void SetMutedImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void SetAutoPlayImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetControlsImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SetLoopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void SetObjectFitImpl(Ark_NativePointer node,
                          const Opt_ImageFit* value)
    {
    }
    void SetOnStartImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void SetOnPauseImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void SetOnFinishImpl(Ark_NativePointer node,
                         const Opt_VoidCallback* value)
    {
    }
    void SetOnFullscreenChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_FullscreenInfo_Void* value)
    {
    }
    void SetOnPreparedImpl(Ark_NativePointer node,
                           const Opt_Callback_PreparedInfo_Void* value)
    {
    }
    void SetOnSeekingImpl(Ark_NativePointer node,
                          const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void SetOnSeekedImpl(Ark_NativePointer node,
                         const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void SetOnUpdateImpl(Ark_NativePointer node,
                         const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void SetOnErrorImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SetOnStopImpl(Ark_NativePointer node,
                       const Opt_VoidCallback* value)
    {
    }
    void SetEnableAnalyzerImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetAnalyzerConfigImpl(Ark_NativePointer node,
                               const Opt_ImageAnalyzerConfig* value)
    {
    }
    void SetEnableShortcutKeyImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    } // VideoAttributeModifier
    namespace WaterFlowModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // WaterFlowModifier
    namespace WaterFlowInterfaceModifier {
    void SetWaterFlowOptionsImpl(Ark_NativePointer node,
                                 const Opt_WaterFlowOptions* options)
    {
    }
    } // WaterFlowInterfaceModifier
    namespace WaterFlowAttributeModifier {
    void SetColumnsTemplateImpl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    void SetItemConstraintSizeImpl(Ark_NativePointer node,
                                   const Opt_ConstraintSizeOptions* value)
    {
    }
    void SetRowsTemplateImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void SetColumnsGapImpl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void SetRowsGapImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void SetLayoutDirectionImpl(Ark_NativePointer node,
                                const Opt_FlexDirection* value)
    {
    }
    void SetCachedCount0Impl(Ark_NativePointer node,
                             const Opt_Int32* value)
    {
    }
    void SetOnScrollFrameBeginImpl(Ark_NativePointer node,
                                   const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void SetOnScrollIndexImpl(Ark_NativePointer node,
                              const Opt_Callback_I32_I32_Void* value)
    {
    }
    void SetOnWillScrollImpl(Ark_NativePointer node,
                             const Opt_OnWillScrollCallback* value)
    {
    }
    void SetOnDidScrollImpl(Ark_NativePointer node,
                            const Opt_OnScrollCallback* value)
    {
    }
    void SetCachedCount1Impl(Ark_NativePointer node,
                             const Opt_Int32* count,
                             const Opt_Boolean* show)
    {
    }
    } // WaterFlowAttributeModifier
    namespace WebModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // WebModifier
    namespace WebInterfaceModifier {
    void SetWebOptionsImpl(Ark_NativePointer node,
                           const Ark_WebOptions* value)
    {
    }
    } // WebInterfaceModifier
    namespace WebAttributeModifier {
    void SetJavaScriptAccessImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetFileAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetOnlineImageAccessImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetDomStorageAccessImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void SetImageAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetMixedModeImpl(Ark_NativePointer node,
                          const Opt_MixedMode* value)
    {
    }
    void SetZoomAccessImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void SetRotateRenderEffectImpl(Ark_NativePointer node,
                                   const Opt_WebRotateEffect* value)
    {
    }
    void SetGeolocationAccessImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetJavaScriptProxyImpl(Ark_NativePointer node,
                                const Opt_JavaScriptProxy* value)
    {
    }
    void SetCacheModeImpl(Ark_NativePointer node,
                          const Opt_CacheMode* value)
    {
    }
    void SetDarkModeImpl(Ark_NativePointer node,
                         const Opt_WebDarkMode* value)
    {
    }
    void SetForceDarkAccessImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetMediaOptionsImpl(Ark_NativePointer node,
                             const Opt_WebMediaOptions* value)
    {
    }
    void SetOverviewModeAccessImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetOverScrollModeImpl(Ark_NativePointer node,
                               const Opt_OverScrollMode* value)
    {
    }
    void SetBlurOnKeyboardHideModeImpl(Ark_NativePointer node,
                                       const Opt_BlurOnKeyboardHideMode* value)
    {
    }
    void SetTextZoomRatioImpl(Ark_NativePointer node,
                              const Opt_Int32* value)
    {
    }
    void SetDatabaseAccessImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetInitialScaleImpl(Ark_NativePointer node,
                             const Opt_Float64* value)
    {
    }
    void SetMetaViewportImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetOnPageEndImpl(Ark_NativePointer node,
                          const Opt_Callback_OnPageEndEvent_Void* value)
    {
    }
    void SetOnPageBeginImpl(Ark_NativePointer node,
                            const Opt_Callback_OnPageBeginEvent_Void* value)
    {
    }
    void SetOnLoadStartedImpl(Ark_NativePointer node,
                              const Opt_Callback_OnLoadStartedEvent_Void* value)
    {
    }
    void SetOnLoadFinishedImpl(Ark_NativePointer node,
                               const Opt_Callback_OnLoadFinishedEvent_Void* value)
    {
    }
    void SetOnProgressChangeImpl(Ark_NativePointer node,
                                 const Opt_Callback_OnProgressChangeEvent_Void* value)
    {
    }
    void SetOnTitleReceiveImpl(Ark_NativePointer node,
                               const Opt_Callback_OnTitleReceiveEvent_Void* value)
    {
    }
    void SetOnGeolocationHideImpl(Ark_NativePointer node,
                                  const Opt_Callback_Void* value)
    {
    }
    void SetOnGeolocationShowImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnGeolocationShowEvent_Void* value)
    {
    }
    void SetOnRequestSelectedImpl(Ark_NativePointer node,
                                  const Opt_Callback_Void* value)
    {
    }
    void SetOnAlertImpl(Ark_NativePointer node,
                        const Opt_Callback_OnAlertEvent_Boolean* value)
    {
    }
    void SetOnBeforeUnloadImpl(Ark_NativePointer node,
                               const Opt_Callback_OnBeforeUnloadEvent_Boolean* value)
    {
    }
    void SetOnConfirmImpl(Ark_NativePointer node,
                          const Opt_Callback_OnConfirmEvent_Boolean* value)
    {
    }
    void SetOnPromptImpl(Ark_NativePointer node,
                         const Opt_Callback_OnPromptEvent_Boolean* value)
    {
    }
    void SetOnConsoleImpl(Ark_NativePointer node,
                          const Opt_Callback_OnConsoleEvent_Boolean* value)
    {
    }
    void SetOnErrorReceiveImpl(Ark_NativePointer node,
                               const Opt_Callback_OnErrorReceiveEvent_Void* value)
    {
    }
    void SetOnHttpErrorReceiveImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnHttpErrorReceiveEvent_Void* value)
    {
    }
    void SetOnOverrideErrorPageImpl(Ark_NativePointer node,
                                    const Opt_OnOverrideErrorPageCallback* value)
    {
    }
    void SetOnDownloadStartImpl(Ark_NativePointer node,
                                const Opt_Callback_OnDownloadStartEvent_Void* value)
    {
    }
    void SetOnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                         const Opt_Callback_OnRefreshAccessedHistoryEvent_Void* value)
    {
    }
    void SetOnRenderExitedImpl(Ark_NativePointer node,
                               const Opt_Callback_OnRenderExitedEvent_Void* value)
    {
    }
    void SetOnShowFileSelectorImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnShowFileSelectorEvent_Boolean* value)
    {
    }
    void SetOnResourceLoadImpl(Ark_NativePointer node,
                               const Opt_Callback_OnResourceLoadEvent_Void* value)
    {
    }
    void SetOnFullScreenExitImpl(Ark_NativePointer node,
                                 const Opt_Callback_Void* value)
    {
    }
    void SetOnFullScreenEnterImpl(Ark_NativePointer node,
                                  const Opt_OnFullScreenEnterCallback* value)
    {
    }
    void SetOnScaleChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_OnScaleChangeEvent_Void* value)
    {
    }
    void SetOnHttpAuthRequestImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnHttpAuthRequestEvent_Boolean* value)
    {
    }
    void SetOnInterceptRequestImpl(Ark_NativePointer node,
                                   const Opt_Type_WebAttribute_onInterceptRequest* value)
    {
    }
    void SetOnPermissionRequestImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnPermissionRequestEvent_Void* value)
    {
    }
    void SetOnScreenCaptureRequestImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnScreenCaptureRequestEvent_Void* value)
    {
    }
    void SetOnContextMenuShowImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnContextMenuShowEvent_Boolean* value)
    {
    }
    void SetOnContextMenuHideImpl(Ark_NativePointer node,
                                  const Opt_OnContextMenuHideCallback* value)
    {
    }
    void SetMediaPlayGestureAccessImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void SetOnSearchResultReceiveImpl(Ark_NativePointer node,
                                      const Opt_Callback_OnSearchResultReceiveEvent_Void* value)
    {
    }
    void SetOnScrollImpl(Ark_NativePointer node,
                         const Opt_Callback_OnScrollEvent_Void* value)
    {
    }
    void SetOnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnSslErrorEventReceiveEvent_Void* value)
    {
    }
    void SetOnSslErrorEventImpl(Ark_NativePointer node,
                                const Opt_OnSslErrorEventCallback* value)
    {
    }
    void SetOnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                              const Opt_Callback_OnClientAuthenticationEvent_Void* value)
    {
    }
    void SetOnWindowNewImpl(Ark_NativePointer node,
                            const Opt_Callback_OnWindowNewEvent_Void* value)
    {
    }
    void SetOnWindowExitImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void SetMultiWindowAccessImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetOnInterceptKeyEventImpl(Ark_NativePointer node,
                                    const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void SetWebStandardFontImpl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    void SetWebSerifFontImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void SetWebSansSerifFontImpl(Ark_NativePointer node,
                                 const Opt_String* value)
    {
    }
    void SetWebFixedFontImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void SetWebFantasyFontImpl(Ark_NativePointer node,
                               const Opt_String* value)
    {
    }
    void SetWebCursiveFontImpl(Ark_NativePointer node,
                               const Opt_String* value)
    {
    }
    void SetDefaultFixedFontSizeImpl(Ark_NativePointer node,
                                     const Opt_Int32* value)
    {
    }
    void SetDefaultFontSizeImpl(Ark_NativePointer node,
                                const Opt_Int32* value)
    {
    }
    void SetMinFontSizeImpl(Ark_NativePointer node,
                            const Opt_Int32* value)
    {
    }
    void SetMinLogicalFontSizeImpl(Ark_NativePointer node,
                                   const Opt_Int32* value)
    {
    }
    void SetDefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                          const Opt_String* value)
    {
    }
    void SetForceDisplayScrollBarImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetBlockNetworkImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetHorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void SetVerticalScrollBarAccessImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
    {
    }
    void SetOnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnTouchIconUrlReceivedEvent_Void* value)
    {
    }
    void SetOnFaviconReceivedImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnFaviconReceivedEvent_Void* value)
    {
    }
    void SetOnPageVisibleImpl(Ark_NativePointer node,
                              const Opt_Callback_OnPageVisibleEvent_Void* value)
    {
    }
    void SetOnDataResubmittedImpl(Ark_NativePointer node,
                                  const Opt_Callback_OnDataResubmittedEvent_Void* value)
    {
    }
    void SetPinchSmoothImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void SetAllowWindowOpenMethodImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetOnAudioStateChangedImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnAudioStateChangedEvent_Void* value)
    {
    }
    void SetOnFirstContentfulPaintImpl(Ark_NativePointer node,
                                       const Opt_Callback_OnFirstContentfulPaintEvent_Void* value)
    {
    }
    void SetOnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                       const Opt_OnFirstMeaningfulPaintCallback* value)
    {
    }
    void SetOnLargestContentfulPaintImpl(Ark_NativePointer node,
                                         const Opt_OnLargestContentfulPaintCallback* value)
    {
    }
    void SetOnLoadInterceptImpl(Ark_NativePointer node,
                                const Opt_Callback_OnLoadInterceptEvent_Boolean* value)
    {
    }
    void SetOnControllerAttachedImpl(Ark_NativePointer node,
                                     const Opt_Callback_Void* value)
    {
    }
    void SetOnOverScrollImpl(Ark_NativePointer node,
                             const Opt_Callback_OnOverScrollEvent_Void* value)
    {
    }
    void SetOnPdfScrollAtBottomImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnPdfScrollEvent_Void* value)
    {
    }
    void SetOnPdfLoadEventImpl(Ark_NativePointer node,
                               const Opt_Callback_OnPdfLoadEvent_Void* value)
    {
    }
    void SetOnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                          const Opt_OnSafeBrowsingCheckResultCallback* value)
    {
    }
    void SetOnSafeBrowsingCheckFinishImpl(Ark_NativePointer node,
                                          const Opt_OnSafeBrowsingCheckResultCallback* value)
    {
    }
    void SetOnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                           const Opt_OnNavigationEntryCommittedCallback* value)
    {
    }
    void SetOnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                                      const Opt_OnIntelligentTrackingPreventionCallback* value)
    {
    }
    void SetJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                          const Opt_Array_ScriptItem* value)
    {
    }
    void SetJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                        const Opt_Array_ScriptItem* value)
    {
    }
    void SetLayoutModeImpl(Ark_NativePointer node,
                           const Opt_WebLayoutMode* value)
    {
    }
    void SetNestedScrollImpl(Ark_NativePointer node,
                             const Opt_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
    {
    }
    void SetEnableNativeEmbedModeImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
    {
    }
    void SetOnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                             const Opt_Callback_NativeEmbedDataInfo_Void* value)
    {
    }
    void SetOnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                              const Opt_OnNativeEmbedVisibilityChangeCallback* value)
    {
    }
    void SetOnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                          const Opt_Callback_NativeEmbedTouchInfo_Void* value)
    {
    }
    void SetOnNativeEmbedMouseEventImpl(Ark_NativePointer node,
                                        const Opt_MouseInfoCallback* value)
    {
    }
    void SetOnNativeEmbedObjectParamChangeImpl(Ark_NativePointer node,
                                               const Opt_OnNativeEmbedObjectParamChangeCallback* value)
    {
    }
    void SetCopyOptionsImpl(Ark_NativePointer node,
                            const Opt_CopyOptions* value)
    {
    }
    void SetOnOverrideUrlLoadingImpl(Ark_NativePointer node,
                                     const Opt_OnOverrideUrlLoadingCallback* value)
    {
    }
    void SetTextAutosizingImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetEnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                        const Opt_NativeMediaPlayerConfig* value)
    {
    }
    void SetOnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                             const Opt_OnRenderProcessNotRespondingCallback* value)
    {
    }
    void SetOnRenderProcessRespondingImpl(Ark_NativePointer node,
                                          const Opt_OnRenderProcessRespondingCallback* value)
    {
    }
    void SetOnViewportFitChangedImpl(Ark_NativePointer node,
                                     const Opt_OnViewportFitChangedCallback* value)
    {
    }
    void SetOnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                          const Opt_WebKeyboardCallback* value)
    {
    }
    void SetOnAdsBlockedImpl(Ark_NativePointer node,
                             const Opt_OnAdsBlockedCallback* value)
    {
    }
    void SetKeyboardAvoidModeImpl(Ark_NativePointer node,
                                  const Opt_WebKeyboardAvoidMode* value)
    {
    }
    void SetEditMenuOptionsImpl(Ark_NativePointer node,
                                const Opt_EditMenuOptions* value)
    {
    }
    void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetOptimizeParserBudgetImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void SetEnableFollowSystemFontWeightImpl(Ark_NativePointer node,
                                             const Opt_Boolean* value)
    {
    }
    void SetEnableWebAVSessionImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetRunJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                             const Opt_Array_ScriptItem* value)
    {
    }
    void SetRunJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                           const Opt_Array_ScriptItem* value)
    {
    }
    void SetRunJavaScriptOnHeadEndImpl(Ark_NativePointer node,
                                       const Opt_Array_ScriptItem* value)
    {
    }
    void SetNativeEmbedOptionsImpl(Ark_NativePointer node,
                                   const Opt_EmbedOptions* value)
    {
    }
    void SetEnableDataDetectorImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SetDataDetectorConfigImpl(Ark_NativePointer node,
                                   const Opt_TextDataDetectorConfig* value)
    {
    }
    void SetOnActivateContentImpl(Ark_NativePointer node,
                                  const Opt_VoidCallback* value)
    {
    }
    void SetBypassVsyncConditionImpl(Ark_NativePointer node,
                                     const Opt_WebBypassVsyncCondition* value)
    {
    }
    void SetGestureFocusModeImpl(Ark_NativePointer node,
                                 const Opt_GestureFocusMode* value)
    {
    }
    void SetForceEnableZoomImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void SetBackToTopImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void SetOnDetectedBlankScreenImpl(Ark_NativePointer node,
                                      const Opt_OnDetectBlankScreenCallback* value)
    {
    }
    void SetBlankScreenDetectionConfigImpl(Ark_NativePointer node,
                                           const Opt_BlankScreenDetectionConfig* value)
    {
    }
    void SetZoomControlAccessImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void SetEnableSelectedDataDetectorImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
    {
    }
    void SetEnableImageAnalyzerImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    void SetRegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                        const Opt_String* tag,
                                        const Opt_String* type)
    {
    }
    void SetBindSelectionMenuImpl(Ark_NativePointer node,
                                  const Opt_WebElementType* elementType,
                                  const Opt_CustomNodeBuilder* content,
                                  const Opt_WebResponseType* responseType,
                                  const Opt_SelectionMenuOptionsExt* options)
    {
    }
    } // WebAttributeModifier
    namespace WindowSceneModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // WindowSceneModifier
    namespace WindowSceneInterfaceModifier {
    void SetWindowSceneOptionsImpl(Ark_NativePointer node,
                                   const Ark_Number* persistentId)
    {
    }
    } // WindowSceneInterfaceModifier
    namespace WindowSceneAttributeModifier {
    void SetAttractionEffectImpl(Ark_NativePointer node,
                                 const Opt_Position* destination,
                                 const Opt_Number* fraction)
    {
    }
    } // WindowSceneAttributeModifier
    namespace WithThemeModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // WithThemeModifier
    namespace WithThemeInterfaceModifier {
    void SetWithThemeOptionsImpl(Ark_NativePointer node,
                                 const Ark_WithThemeOptions* options)
    {
    }
    } // WithThemeInterfaceModifier
    namespace XComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // XComponentModifier
    namespace XComponentInterfaceModifier {
    void SetXComponentOptionsImpl(Ark_NativePointer node,
                                  const Ark_Union_XComponentParameters_XComponentOptions_NativeXComponentParameters* params)
    {
    }
    } // XComponentInterfaceModifier
    namespace XComponentAttributeModifier {
    void SetOnLoadImpl(Ark_NativePointer node,
                       const Opt_VoidCallback* value)
    {
    }
    void SetOnDestroyImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* value)
    {
    }
    void SetEnableAnalyzerImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void SetEnableSecureImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void SetHdrBrightnessImpl(Ark_NativePointer node,
                              const Opt_Float64* value)
    {
    }
    } // XComponentAttributeModifier
    const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
    {
        static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
            AlphabetIndexerModifier::ConstructImpl,
            AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
            AlphabetIndexerAttributeModifier::SetColorImpl,
            AlphabetIndexerAttributeModifier::SetSelectedColorImpl,
            AlphabetIndexerAttributeModifier::SetPopupColorImpl,
            AlphabetIndexerAttributeModifier::SetSelectedBackgroundColorImpl,
            AlphabetIndexerAttributeModifier::SetPopupBackgroundImpl,
            AlphabetIndexerAttributeModifier::SetPopupSelectedColorImpl,
            AlphabetIndexerAttributeModifier::SetPopupUnselectedColorImpl,
            AlphabetIndexerAttributeModifier::SetPopupItemBackgroundColorImpl,
            AlphabetIndexerAttributeModifier::SetUsingPopupImpl,
            AlphabetIndexerAttributeModifier::SetSelectedFontImpl,
            AlphabetIndexerAttributeModifier::SetPopupFontImpl,
            AlphabetIndexerAttributeModifier::SetPopupItemFontImpl,
            AlphabetIndexerAttributeModifier::SetItemSizeImpl,
            AlphabetIndexerAttributeModifier::SetFontImpl,
            AlphabetIndexerAttributeModifier::SetOnSelectImpl,
            AlphabetIndexerAttributeModifier::SetOnRequestPopupDataImpl,
            AlphabetIndexerAttributeModifier::SetOnPopupSelectImpl,
            AlphabetIndexerAttributeModifier::SetSelectedImpl,
            AlphabetIndexerAttributeModifier::SetPopupPositionImpl,
            AlphabetIndexerAttributeModifier::SetAutoCollapseImpl,
            AlphabetIndexerAttributeModifier::SetPopupItemBorderRadiusImpl,
            AlphabetIndexerAttributeModifier::SetItemBorderRadiusImpl,
            AlphabetIndexerAttributeModifier::SetPopupBackgroundBlurStyleImpl,
            AlphabetIndexerAttributeModifier::SetPopupTitleBackgroundImpl,
            AlphabetIndexerAttributeModifier::SetEnableHapticFeedbackImpl,
            AlphabetIndexerAttributeModifier::SetAlignStyleImpl,
        };
        return &ArkUIAlphabetIndexerModifierImpl;
    }

    const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier()
    {
        static const GENERATED_ArkUIAnimatorModifier ArkUIAnimatorModifierImpl {
            AnimatorModifier::ConstructImpl,
            AnimatorInterfaceModifier::SetAnimatorOptionsImpl,
            AnimatorAttributeModifier::SetStateImpl,
            AnimatorAttributeModifier::SetDurationImpl,
            AnimatorAttributeModifier::SetCurveImpl,
            AnimatorAttributeModifier::SetDelayImpl,
            AnimatorAttributeModifier::SetFillModeImpl,
            AnimatorAttributeModifier::SetIterationsImpl,
            AnimatorAttributeModifier::SetPlayModeImpl,
            AnimatorAttributeModifier::SetMotionImpl,
            AnimatorAttributeModifier::SetOnStartImpl,
            AnimatorAttributeModifier::SetOnPauseImpl,
            AnimatorAttributeModifier::SetOnRepeatImpl,
            AnimatorAttributeModifier::SetOnCancelImpl,
            AnimatorAttributeModifier::SetOnFinishImpl,
            AnimatorAttributeModifier::SetOnFrameImpl,
        };
        return &ArkUIAnimatorModifierImpl;
    }

    const GENERATED_ArkUIBadgeModifier* GetBadgeModifier()
    {
        static const GENERATED_ArkUIBadgeModifier ArkUIBadgeModifierImpl {
            BadgeModifier::ConstructImpl,
            BadgeInterfaceModifier::SetBadgeOptionsImpl,
        };
        return &ArkUIBadgeModifierImpl;
    }

    const GENERATED_ArkUIBaseSpanModifier* GetBaseSpanModifier()
    {
        static const GENERATED_ArkUIBaseSpanModifier ArkUIBaseSpanModifierImpl {
            BaseSpanModifier::ConstructImpl,
            BaseSpanModifier::SetTextBackgroundStyleImpl,
            BaseSpanModifier::SetBaselineOffsetImpl,
        };
        return &ArkUIBaseSpanModifierImpl;
    }

    const GENERATED_ArkUIBlankModifier* GetBlankModifier()
    {
        static const GENERATED_ArkUIBlankModifier ArkUIBlankModifierImpl {
            BlankModifier::ConstructImpl,
            BlankInterfaceModifier::SetBlankOptionsImpl,
            BlankAttributeModifier::SetColorImpl,
        };
        return &ArkUIBlankModifierImpl;
    }

    const GENERATED_ArkUIButtonModifier* GetButtonModifier()
    {
        static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
            ButtonModifier::ConstructImpl,
            ButtonInterfaceModifier::SetButtonOptions0Impl,
            ButtonInterfaceModifier::SetButtonOptions1Impl,
            ButtonAttributeModifier::SetTypeImpl,
            ButtonAttributeModifier::SetStateEffectImpl,
            ButtonAttributeModifier::SetButtonStyleImpl,
            ButtonAttributeModifier::SetControlSizeImpl,
            ButtonAttributeModifier::SetRoleImpl,
            ButtonAttributeModifier::SetFontColorImpl,
            ButtonAttributeModifier::SetFontSizeImpl,
            ButtonAttributeModifier::SetFontWeightImpl,
            ButtonAttributeModifier::SetFontStyleImpl,
            ButtonAttributeModifier::SetFontFamilyImpl,
            ButtonAttributeModifier::SetLabelStyleImpl,
            ButtonAttributeModifier::SetMinFontScaleImpl,
            ButtonAttributeModifier::SetMaxFontScaleImpl,
        };
        return &ArkUIButtonModifierImpl;
    }

    const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier()
    {
        static const GENERATED_ArkUICalendarPickerModifier ArkUICalendarPickerModifierImpl {
            CalendarPickerModifier::ConstructImpl,
            CalendarPickerInterfaceModifier::SetCalendarPickerOptionsImpl,
            CalendarPickerAttributeModifier::SetTextStyleImpl,
            CalendarPickerAttributeModifier::SetOnChangeImpl,
            CalendarPickerAttributeModifier::SetMarkTodayImpl,
            CalendarPickerAttributeModifier::SetEdgeAlignImpl,
        };
        return &ArkUICalendarPickerModifierImpl;
    }

    const GENERATED_ArkUICanvasModifier* GetCanvasModifier()
    {
        static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
            CanvasModifier::ConstructImpl,
            CanvasInterfaceModifier::SetCanvasOptionsImpl,
            CanvasAttributeModifier::SetOnReadyImpl,
            CanvasAttributeModifier::SetEnableAnalyzerImpl,
        };
        return &ArkUICanvasModifierImpl;
    }

    const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
    {
        static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
            CheckboxModifier::ConstructImpl,
            CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
            CheckboxAttributeModifier::SetSelectImpl,
            CheckboxAttributeModifier::SetSelectedColorImpl,
            CheckboxAttributeModifier::SetShapeImpl,
            CheckboxAttributeModifier::SetUnselectedColorImpl,
            CheckboxAttributeModifier::SetMarkImpl,
            CheckboxAttributeModifier::SetOnChangeImpl,
        };
        return &ArkUICheckboxModifierImpl;
    }

    const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
    {
        static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
            CheckboxGroupModifier::ConstructImpl,
            CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
            CheckboxGroupAttributeModifier::SetSelectAllImpl,
            CheckboxGroupAttributeModifier::SetSelectedColorImpl,
            CheckboxGroupAttributeModifier::SetUnselectedColorImpl,
            CheckboxGroupAttributeModifier::SetMarkImpl,
            CheckboxGroupAttributeModifier::SetOnChangeImpl,
            CheckboxGroupAttributeModifier::SetCheckboxShapeImpl,
        };
        return &ArkUICheckboxGroupModifierImpl;
    }

    const GENERATED_ArkUICircleModifier* GetCircleModifier()
    {
        static const GENERATED_ArkUICircleModifier ArkUICircleModifierImpl {
            CircleModifier::ConstructImpl,
            CircleInterfaceModifier::SetCircleOptionsImpl,
        };
        return &ArkUICircleModifierImpl;
    }

    const GENERATED_ArkUIColumnModifier* GetColumnModifier()
    {
        static const GENERATED_ArkUIColumnModifier ArkUIColumnModifierImpl {
            ColumnModifier::ConstructImpl,
            ColumnInterfaceModifier::SetColumnOptionsImpl,
            ColumnAttributeModifier::SetAlignItemsImpl,
            ColumnAttributeModifier::SetJustifyContentImpl,
            ColumnAttributeModifier::SetReverseImpl,
        };
        return &ArkUIColumnModifierImpl;
    }

    const GENERATED_ArkUIColumnSplitModifier* GetColumnSplitModifier()
    {
        static const GENERATED_ArkUIColumnSplitModifier ArkUIColumnSplitModifierImpl {
            ColumnSplitModifier::ConstructImpl,
            ColumnSplitInterfaceModifier::SetColumnSplitOptionsImpl,
            ColumnSplitAttributeModifier::SetResizeableImpl,
            ColumnSplitAttributeModifier::SetDividerImpl,
        };
        return &ArkUIColumnSplitModifierImpl;
    }

    const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
    {
        static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
            CommonMethodModifier::ConstructImpl,
            CommonMethodModifier::SetWidthImpl,
            CommonMethodModifier::SetHeightImpl,
            CommonMethodModifier::SetResponseRegionImpl,
            CommonMethodModifier::SetMouseResponseRegionImpl,
            CommonMethodModifier::SetResponseRegionListImpl,
            CommonMethodModifier::SetSizeImpl,
            CommonMethodModifier::SetConstraintSizeImpl,
            CommonMethodModifier::SetHitTestBehaviorImpl,
            CommonMethodModifier::SetOnChildTouchTestImpl,
            CommonMethodModifier::SetLayoutWeightImpl,
            CommonMethodModifier::SetChainWeightImpl,
            CommonMethodModifier::SetPaddingImpl,
            CommonMethodModifier::SetSafeAreaPaddingImpl,
            CommonMethodModifier::SetMarginImpl,
            CommonMethodModifier::SetBackgroundColorImpl,
            CommonMethodModifier::SetPixelRoundImpl,
            CommonMethodModifier::SetBackgroundImageSizeImpl,
            CommonMethodModifier::SetBackgroundImagePositionImpl,
            CommonMethodModifier::SetBackgroundEffect0Impl,
            CommonMethodModifier::SetBackgroundImageResizableImpl,
            CommonMethodModifier::SetForegroundEffectImpl,
            CommonMethodModifier::SetVisualEffectImpl,
            CommonMethodModifier::SetBackgroundFilterImpl,
            CommonMethodModifier::SetForegroundFilterImpl,
            CommonMethodModifier::SetCompositingFilterImpl,
            CommonMethodModifier::SetOpacityImpl,
            CommonMethodModifier::SetBorderImpl,
            CommonMethodModifier::SetBorderStyleImpl,
            CommonMethodModifier::SetBorderWidthImpl,
            CommonMethodModifier::SetBorderColorImpl,
            CommonMethodModifier::SetBorderRadius0Impl,
            CommonMethodModifier::SetBorderImageImpl,
            CommonMethodModifier::SetOutlineImpl,
            CommonMethodModifier::SetOutlineStyleImpl,
            CommonMethodModifier::SetOutlineWidthImpl,
            CommonMethodModifier::SetOutlineColorImpl,
            CommonMethodModifier::SetOutlineRadiusImpl,
            CommonMethodModifier::SetForegroundColorImpl,
            CommonMethodModifier::SetOnClick0Impl,
            CommonMethodModifier::SetOnHoverImpl,
            CommonMethodModifier::SetOnHoverMoveImpl,
            CommonMethodModifier::SetOnAccessibilityHoverImpl,
            CommonMethodModifier::SetOnAccessibilityHoverTransparentImpl,
            CommonMethodModifier::SetHoverEffectImpl,
            CommonMethodModifier::SetOnMouseImpl,
            CommonMethodModifier::SetOnTouchImpl,
            CommonMethodModifier::SetOnKeyEventImpl,
            CommonMethodModifier::SetOnDigitalCrownImpl,
            CommonMethodModifier::SetOnKeyPreImeImpl,
            CommonMethodModifier::SetOnKeyEventDispatchImpl,
            CommonMethodModifier::SetOnFocusAxisEventImpl,
            CommonMethodModifier::SetOnAxisEventImpl,
            CommonMethodModifier::SetFocusableImpl,
            CommonMethodModifier::SetNextFocusImpl,
            CommonMethodModifier::SetTabStopImpl,
            CommonMethodModifier::SetOnFocusImpl,
            CommonMethodModifier::SetOnBlurImpl,
            CommonMethodModifier::SetTabIndexImpl,
            CommonMethodModifier::SetDefaultFocusImpl,
            CommonMethodModifier::SetGroupDefaultFocusImpl,
            CommonMethodModifier::SetFocusOnTouchImpl,
            CommonMethodModifier::SetFocusBoxImpl,
            CommonMethodModifier::SetAnimationImpl,
            CommonMethodModifier::SetTransition0Impl,
            CommonMethodModifier::SetMotionBlurImpl,
            CommonMethodModifier::SetBrightnessImpl,
            CommonMethodModifier::SetContrastImpl,
            CommonMethodModifier::SetGrayscaleImpl,
            CommonMethodModifier::SetColorBlendImpl,
            CommonMethodModifier::SetSaturateImpl,
            CommonMethodModifier::SetSepiaImpl,
            CommonMethodModifier::SetInvertImpl,
            CommonMethodModifier::SetHueRotateImpl,
            CommonMethodModifier::SetUseShadowBatchingImpl,
            CommonMethodModifier::SetUseEffect0Impl,
            CommonMethodModifier::SetRenderGroupImpl,
            CommonMethodModifier::SetFreezeImpl,
            CommonMethodModifier::SetTranslateImpl,
            CommonMethodModifier::SetScaleImpl,
            CommonMethodModifier::SetRotateImpl,
            CommonMethodModifier::SetTransformImpl,
            CommonMethodModifier::SetTransform3DImpl,
            CommonMethodModifier::SetOnAppearImpl,
            CommonMethodModifier::SetOnDisAppearImpl,
            CommonMethodModifier::SetOnAttachImpl,
            CommonMethodModifier::SetOnDetachImpl,
            CommonMethodModifier::SetOnAreaChangeImpl,
            CommonMethodModifier::SetVisibilityImpl,
            CommonMethodModifier::SetFlexGrowImpl,
            CommonMethodModifier::SetFlexShrinkImpl,
            CommonMethodModifier::SetFlexBasisImpl,
            CommonMethodModifier::SetAlignSelfImpl,
            CommonMethodModifier::SetLayoutGravityImpl,
            CommonMethodModifier::SetDisplayPriorityImpl,
            CommonMethodModifier::SetZIndexImpl,
            CommonMethodModifier::SetDirectionImpl,
            CommonMethodModifier::SetAlignImpl,
            CommonMethodModifier::SetPositionImpl,
            CommonMethodModifier::SetMarkAnchorImpl,
            CommonMethodModifier::SetOffsetImpl,
            CommonMethodModifier::SetEnabledImpl,
            CommonMethodModifier::SetAlignRulesImpl,
            CommonMethodModifier::SetAspectRatioImpl,
            CommonMethodModifier::SetClickEffectImpl,
            CommonMethodModifier::SetOnDragStartImpl,
            CommonMethodModifier::SetOnDragEnterImpl,
            CommonMethodModifier::SetOnDragMoveImpl,
            CommonMethodModifier::SetOnDragLeaveImpl,
            CommonMethodModifier::SetOnDrop0Impl,
            CommonMethodModifier::SetOnDragEndImpl,
            CommonMethodModifier::SetDraggableImpl,
            CommonMethodModifier::SetDragPreview0Impl,
            CommonMethodModifier::SetOnPreDragImpl,
            CommonMethodModifier::SetLinearGradientImpl,
            CommonMethodModifier::SetSweepGradientImpl,
            CommonMethodModifier::SetRadialGradientImpl,
            CommonMethodModifier::SetMotionPathImpl,
            CommonMethodModifier::SetShadowImpl,
            CommonMethodModifier::SetClipImpl,
            CommonMethodModifier::SetClipShapeImpl,
            CommonMethodModifier::SetMaskImpl,
            CommonMethodModifier::SetMaskShapeImpl,
            CommonMethodModifier::SetKeyImpl,
            CommonMethodModifier::SetIdImpl,
            CommonMethodModifier::SetGeometryTransition0Impl,
            CommonMethodModifier::SetRestoreIdImpl,
            CommonMethodModifier::SetSphericalEffectImpl,
            CommonMethodModifier::SetLightUpEffectImpl,
            CommonMethodModifier::SetPixelStretchEffectImpl,
            CommonMethodModifier::SetAccessibilityGroupWithValueImpl,
            CommonMethodModifier::SetAccessibilityTextOfStringTypeImpl,
            CommonMethodModifier::SetAccessibilityNextFocusIdImpl,
            CommonMethodModifier::SetAccessibilityDefaultFocusImpl,
            CommonMethodModifier::SetAccessibilityUseSamePageImpl,
            CommonMethodModifier::SetAccessibilityScrollTriggerableImpl,
            CommonMethodModifier::SetAccessibilityTextOfResourceTypeImpl,
            CommonMethodModifier::SetAccessibilityRoleImpl,
            CommonMethodModifier::SetOnAccessibilityFocusImpl,
            CommonMethodModifier::SetOnAccessibilityActionInterceptImpl,
            CommonMethodModifier::SetAccessibilityTextHintImpl,
            CommonMethodModifier::SetAccessibilityDescriptionOfStringTypeImpl,
            CommonMethodModifier::SetAccessibilityDescriptionOfResourceTypeImpl,
            CommonMethodModifier::SetAccessibilityLevelImpl,
            CommonMethodModifier::SetAccessibilityVirtualNodeImpl,
            CommonMethodModifier::SetAccessibilityCheckedImpl,
            CommonMethodModifier::SetAccessibilitySelectedImpl,
            CommonMethodModifier::SetObscuredImpl,
            CommonMethodModifier::SetReuseIdImpl,
            CommonMethodModifier::SetReuseImpl,
            CommonMethodModifier::SetRenderFitImpl,
            CommonMethodModifier::SetBackgroundBrightnessImpl,
            CommonMethodModifier::SetOnGestureJudgeBeginImpl,
            CommonMethodModifier::SetOnGestureRecognizerJudgeBegin0Impl,
            CommonMethodModifier::SetShouldBuiltInRecognizerParallelWithImpl,
            CommonMethodModifier::SetMonopolizeEventsImpl,
            CommonMethodModifier::SetOnTouchInterceptImpl,
            CommonMethodModifier::SetOnSizeChangeImpl,
            CommonMethodModifier::SetAccessibilityFocusDrawLevelImpl,
            CommonMethodModifier::SetExpandSafeAreaImpl,
            CommonMethodModifier::SetIgnoreLayoutSafeAreaImpl,
            CommonMethodModifier::SetBackgroundImpl,
            CommonMethodModifier::SetBackgroundImage0Impl,
            CommonMethodModifier::SetBackgroundImage1Impl,
            CommonMethodModifier::SetBackgroundImage2Impl,
            CommonMethodModifier::SetBackgroundBlurStyleImpl,
            CommonMethodModifier::SetBackgroundEffect1Impl,
            CommonMethodModifier::SetForegroundBlurStyleImpl,
            CommonMethodModifier::SetBorderRadius1Impl,
            CommonMethodModifier::SetOnClick1Impl,
            CommonMethodModifier::SetFocusScopeIdImpl,
            CommonMethodModifier::SetFocusScopePriorityImpl,
            CommonMethodModifier::SetTransition1Impl,
            CommonMethodModifier::SetGestureImpl,
            CommonMethodModifier::SetPriorityGestureImpl,
            CommonMethodModifier::SetParallelGestureImpl,
            CommonMethodModifier::SetBlurImpl,
            CommonMethodModifier::SetLinearGradientBlurImpl,
            CommonMethodModifier::SetSystemBarEffectImpl,
            CommonMethodModifier::SetUseEffect1Impl,
            CommonMethodModifier::SetBackdropBlurImpl,
            CommonMethodModifier::SetSharedTransitionImpl,
            CommonMethodModifier::SetChainModeImpl,
            CommonMethodModifier::SetOnDrop1Impl,
            CommonMethodModifier::SetDragPreview1Impl,
            CommonMethodModifier::SetOverlayImpl,
            CommonMethodModifier::SetBlendModeImpl,
            CommonMethodModifier::SetAdvancedBlendModeImpl,
            CommonMethodModifier::SetGeometryTransition1Impl,
            CommonMethodModifier::SetBindTipsImpl,
            CommonMethodModifier::SetBindPopupImpl,
            CommonMethodModifier::SetBindMenu0Impl,
            CommonMethodModifier::SetBindMenu1Impl,
            CommonMethodModifier::SetBindContextMenu0Impl,
            CommonMethodModifier::SetBindContextMenu1Impl,
            CommonMethodModifier::SetBindContentCover0Impl,
            CommonMethodModifier::SetBindContentCover1Impl,
            CommonMethodModifier::SetBindSheetImpl,
            CommonMethodModifier::SetOnVisibleAreaChangeImpl,
            CommonMethodModifier::SetOnVisibleAreaApproximateChangeImpl,
            CommonMethodModifier::SetKeyboardShortcutImpl,
            CommonMethodModifier::SetAccessibilityGroupWithConfigImpl,
            CommonMethodModifier::SetOnGestureRecognizerJudgeBegin1Impl,
        };
        return &ArkUICommonMethodModifierImpl;
    }

    const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier()
    {
        static const GENERATED_ArkUICommonShapeMethodModifier ArkUICommonShapeMethodModifierImpl {
            CommonShapeMethodModifier::ConstructImpl,
            CommonShapeMethodModifier::SetStrokeImpl,
            CommonShapeMethodModifier::SetFillImpl,
            CommonShapeMethodModifier::SetStrokeDashOffsetImpl,
            CommonShapeMethodModifier::SetStrokeLineCapImpl,
            CommonShapeMethodModifier::SetStrokeLineJoinImpl,
            CommonShapeMethodModifier::SetStrokeMiterLimitImpl,
            CommonShapeMethodModifier::SetStrokeOpacityImpl,
            CommonShapeMethodModifier::SetFillOpacityImpl,
            CommonShapeMethodModifier::SetStrokeWidthImpl,
            CommonShapeMethodModifier::SetAntiAliasImpl,
            CommonShapeMethodModifier::SetStrokeDashArrayImpl,
        };
        return &ArkUICommonShapeMethodModifierImpl;
    }

    const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
    {
        static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
            Component3DModifier::ConstructImpl,
            Component3DInterfaceModifier::SetComponent3DOptionsImpl,
            Component3DAttributeModifier::SetEnvironmentImpl,
            Component3DAttributeModifier::SetShaderImpl,
            Component3DAttributeModifier::SetShaderImageTextureImpl,
            Component3DAttributeModifier::SetShaderInputBufferImpl,
            Component3DAttributeModifier::SetRenderWidthImpl,
            Component3DAttributeModifier::SetRenderHeightImpl,
            Component3DAttributeModifier::SetCustomRenderImpl,
        };
        return &ArkUIComponent3DModifierImpl;
    }

    const GENERATED_ArkUIComponentRootModifier* GetComponentRootModifier()
    {
        static const GENERATED_ArkUIComponentRootModifier ArkUIComponentRootModifierImpl {
            ComponentRootModifier::ConstructImpl,
        };
        return &ArkUIComponentRootModifierImpl;
    }

    const GENERATED_ArkUIContainerSpanModifier* GetContainerSpanModifier()
    {
        static const GENERATED_ArkUIContainerSpanModifier ArkUIContainerSpanModifierImpl {
            ContainerSpanModifier::ConstructImpl,
            ContainerSpanInterfaceModifier::SetContainerSpanOptionsImpl,
            ContainerSpanAttributeModifier::SetTextBackgroundStyleImpl,
        };
        return &ArkUIContainerSpanModifierImpl;
    }

    const GENERATED_ArkUICounterModifier* GetCounterModifier()
    {
        static const GENERATED_ArkUICounterModifier ArkUICounterModifierImpl {
            CounterModifier::ConstructImpl,
            CounterInterfaceModifier::SetCounterOptionsImpl,
            CounterAttributeModifier::SetOnIncImpl,
            CounterAttributeModifier::SetOnDecImpl,
            CounterAttributeModifier::SetEnableDecImpl,
            CounterAttributeModifier::SetEnableIncImpl,
        };
        return &ArkUICounterModifierImpl;
    }

    const GENERATED_ArkUICustomBuilderRootModifier* GetCustomBuilderRootModifier()
    {
        static const GENERATED_ArkUICustomBuilderRootModifier ArkUICustomBuilderRootModifierImpl {
            CustomBuilderRootModifier::ConstructImpl,
        };
        return &ArkUICustomBuilderRootModifierImpl;
    }

    const GENERATED_ArkUICustomLayoutRootModifier* GetCustomLayoutRootModifier()
    {
        static const GENERATED_ArkUICustomLayoutRootModifier ArkUICustomLayoutRootModifierImpl {
            CustomLayoutRootModifier::ConstructImpl,
            CustomLayoutRootModifier::SetSubscribeOnMeasureSizeImpl,
            CustomLayoutRootModifier::SetSubscribeOnPlaceChildrenImpl,
        };
        return &ArkUICustomLayoutRootModifierImpl;
    }

    const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
    {
        static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
            DataPanelModifier::ConstructImpl,
            DataPanelInterfaceModifier::SetDataPanelOptionsImpl,
            DataPanelAttributeModifier::SetCloseEffectImpl,
            DataPanelAttributeModifier::SetValueColorsImpl,
            DataPanelAttributeModifier::SetTrackBackgroundColorImpl,
            DataPanelAttributeModifier::SetStrokeWidthImpl,
            DataPanelAttributeModifier::SetTrackShadowImpl,
        };
        return &ArkUIDataPanelModifierImpl;
    }

    const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
    {
        static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
            DatePickerModifier::ConstructImpl,
            DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
            DatePickerAttributeModifier::SetLunarImpl,
            DatePickerAttributeModifier::SetDisappearTextStyleImpl,
            DatePickerAttributeModifier::SetTextStyleImpl,
            DatePickerAttributeModifier::SetSelectedTextStyleImpl,
            DatePickerAttributeModifier::SetOnDateChangeImpl,
            DatePickerAttributeModifier::SetDigitalCrownSensitivityImpl,
            DatePickerAttributeModifier::SetEnableHapticFeedbackImpl,
        };
        return &ArkUIDatePickerModifierImpl;
    }

    const GENERATED_ArkUIDividerModifier* GetDividerModifier()
    {
        static const GENERATED_ArkUIDividerModifier ArkUIDividerModifierImpl {
            DividerModifier::ConstructImpl,
            DividerInterfaceModifier::SetDividerOptionsImpl,
            DividerAttributeModifier::SetVerticalImpl,
            DividerAttributeModifier::SetColorImpl,
            DividerAttributeModifier::SetStrokeWidthImpl,
            DividerAttributeModifier::SetLineCapImpl,
        };
        return &ArkUIDividerModifierImpl;
    }

    const GENERATED_ArkUIEffectComponentModifier* GetEffectComponentModifier()
    {
        static const GENERATED_ArkUIEffectComponentModifier ArkUIEffectComponentModifierImpl {
            EffectComponentModifier::ConstructImpl,
            EffectComponentInterfaceModifier::SetEffectComponentOptionsImpl,
        };
        return &ArkUIEffectComponentModifierImpl;
    }

    const GENERATED_ArkUIEllipseModifier* GetEllipseModifier()
    {
        static const GENERATED_ArkUIEllipseModifier ArkUIEllipseModifierImpl {
            EllipseModifier::ConstructImpl,
            EllipseInterfaceModifier::SetEllipseOptionsImpl,
        };
        return &ArkUIEllipseModifierImpl;
    }

    const GENERATED_ArkUIEmbeddedComponentModifier* GetEmbeddedComponentModifier()
    {
        static const GENERATED_ArkUIEmbeddedComponentModifier ArkUIEmbeddedComponentModifierImpl {
            EmbeddedComponentModifier::ConstructImpl,
            EmbeddedComponentInterfaceModifier::SetEmbeddedComponentOptionsImpl,
            EmbeddedComponentAttributeModifier::SetOnTerminatedImpl,
            EmbeddedComponentAttributeModifier::SetOnErrorImpl,
        };
        return &ArkUIEmbeddedComponentModifierImpl;
    }

    const GENERATED_ArkUIFlexModifier* GetFlexModifier()
    {
        static const GENERATED_ArkUIFlexModifier ArkUIFlexModifierImpl {
            FlexModifier::ConstructImpl,
            FlexInterfaceModifier::SetFlexOptionsImpl,
        };
        return &ArkUIFlexModifierImpl;
    }

    const GENERATED_ArkUIFlowItemModifier* GetFlowItemModifier()
    {
        static const GENERATED_ArkUIFlowItemModifier ArkUIFlowItemModifierImpl {
            FlowItemModifier::ConstructImpl,
            FlowItemInterfaceModifier::SetFlowItemOptionsImpl,
        };
        return &ArkUIFlowItemModifierImpl;
    }

    const GENERATED_ArkUIFolderStackModifier* GetFolderStackModifier()
    {
        static const GENERATED_ArkUIFolderStackModifier ArkUIFolderStackModifierImpl {
            FolderStackModifier::ConstructImpl,
            FolderStackInterfaceModifier::SetFolderStackOptionsImpl,
            FolderStackAttributeModifier::SetAlignContentImpl,
            FolderStackAttributeModifier::SetOnFolderStateChangeImpl,
            FolderStackAttributeModifier::SetOnHoverStatusChangeImpl,
            FolderStackAttributeModifier::SetEnableAnimationImpl,
            FolderStackAttributeModifier::SetAutoHalfFoldImpl,
        };
        return &ArkUIFolderStackModifierImpl;
    }

    const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
    {
        static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
            FormComponentModifier::ConstructImpl,
            FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
            FormComponentAttributeModifier::SetSizeImpl,
            FormComponentAttributeModifier::SetModuleNameImpl,
            FormComponentAttributeModifier::SetDimensionImpl,
            FormComponentAttributeModifier::SetAllowUpdateImpl,
            FormComponentAttributeModifier::SetVisibilityImpl,
            FormComponentAttributeModifier::SetOnAcquiredImpl,
            FormComponentAttributeModifier::SetOnErrorImpl,
            FormComponentAttributeModifier::SetOnRouterImpl,
            FormComponentAttributeModifier::SetOnUninstallImpl,
            FormComponentAttributeModifier::SetOnLoadImpl,
            FormComponentAttributeModifier::SetOnUpdateImpl,
        };
        return &ArkUIFormComponentModifierImpl;
    }

    const GENERATED_ArkUIFormLinkModifier* GetFormLinkModifier()
    {
        static const GENERATED_ArkUIFormLinkModifier ArkUIFormLinkModifierImpl {
            FormLinkModifier::ConstructImpl,
            FormLinkInterfaceModifier::SetFormLinkOptionsImpl,
        };
        return &ArkUIFormLinkModifierImpl;
    }

    const GENERATED_ArkUIGaugeModifier* GetGaugeModifier()
    {
        static const GENERATED_ArkUIGaugeModifier ArkUIGaugeModifierImpl {
            GaugeModifier::ConstructImpl,
            GaugeInterfaceModifier::SetGaugeOptionsImpl,
            GaugeAttributeModifier::SetValueImpl,
            GaugeAttributeModifier::SetStartAngleImpl,
            GaugeAttributeModifier::SetEndAngleImpl,
            GaugeAttributeModifier::SetColorsImpl,
            GaugeAttributeModifier::SetStrokeWidthImpl,
            GaugeAttributeModifier::SetDescriptionImpl,
            GaugeAttributeModifier::SetTrackShadowImpl,
            GaugeAttributeModifier::SetIndicatorImpl,
            GaugeAttributeModifier::SetPrivacySensitiveImpl,
        };
        return &ArkUIGaugeModifierImpl;
    }

    const GENERATED_ArkUIGridModifier* GetGridModifier()
    {
        static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
            GridModifier::ConstructImpl,
            GridInterfaceModifier::SetGridOptionsImpl,
            GridAttributeModifier::SetColumnsTemplateImpl,
            GridAttributeModifier::SetRowsTemplateImpl,
            GridAttributeModifier::SetColumnsGapImpl,
            GridAttributeModifier::SetRowsGapImpl,
            GridAttributeModifier::SetScrollBarWidthImpl,
            GridAttributeModifier::SetScrollBarColorImpl,
            GridAttributeModifier::SetScrollBarImpl,
            GridAttributeModifier::SetOnScrollBarUpdateImpl,
            GridAttributeModifier::SetOnScrollIndexImpl,
            GridAttributeModifier::SetCachedCount0Impl,
            GridAttributeModifier::SetEditModeImpl,
            GridAttributeModifier::SetMultiSelectableImpl,
            GridAttributeModifier::SetMaxCountImpl,
            GridAttributeModifier::SetMinCountImpl,
            GridAttributeModifier::SetCellLengthImpl,
            GridAttributeModifier::SetLayoutDirectionImpl,
            GridAttributeModifier::SetSupportAnimationImpl,
            GridAttributeModifier::SetOnItemDragStartImpl,
            GridAttributeModifier::SetOnItemDragEnterImpl,
            GridAttributeModifier::SetOnItemDragMoveImpl,
            GridAttributeModifier::SetOnItemDragLeaveImpl,
            GridAttributeModifier::SetOnItemDropImpl,
            GridAttributeModifier::SetNestedScrollImpl,
            GridAttributeModifier::SetEnableScrollInteractionImpl,
            GridAttributeModifier::SetFrictionImpl,
            GridAttributeModifier::SetAlignItemsImpl,
            GridAttributeModifier::SetOnScrollFrameBeginImpl,
            GridAttributeModifier::SetOnWillScrollImpl,
            GridAttributeModifier::SetOnDidScrollImpl,
            GridAttributeModifier::SetCachedCount1Impl,
            GridAttributeModifier::SetEdgeEffectImpl,
        };
        return &ArkUIGridModifierImpl;
    }

    const GENERATED_ArkUIGridColModifier* GetGridColModifier()
    {
        static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
            GridColModifier::ConstructImpl,
            GridColInterfaceModifier::SetGridColOptionsImpl,
            GridColAttributeModifier::SetSpanImpl,
            GridColAttributeModifier::SetGridColOffsetImpl,
            GridColAttributeModifier::SetOrderImpl,
        };
        return &ArkUIGridColModifierImpl;
    }

    const GENERATED_ArkUIGridItemModifier* GetGridItemModifier()
    {
        static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
            GridItemModifier::ConstructImpl,
            GridItemInterfaceModifier::SetGridItemOptionsImpl,
            GridItemAttributeModifier::SetRowStartImpl,
            GridItemAttributeModifier::SetRowEndImpl,
            GridItemAttributeModifier::SetColumnStartImpl,
            GridItemAttributeModifier::SetColumnEndImpl,
            GridItemAttributeModifier::SetSelectableImpl,
            GridItemAttributeModifier::SetSelectedImpl,
            GridItemAttributeModifier::SetOnSelectImpl,
        };
        return &ArkUIGridItemModifierImpl;
    }

    const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
    {
        static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
            GridRowModifier::ConstructImpl,
            GridRowInterfaceModifier::SetGridRowOptionsImpl,
            GridRowAttributeModifier::SetOnBreakpointChangeImpl,
            GridRowAttributeModifier::SetAlignItemsImpl,
        };
        return &ArkUIGridRowModifierImpl;
    }

    const GENERATED_ArkUIHyperlinkModifier* GetHyperlinkModifier()
    {
        static const GENERATED_ArkUIHyperlinkModifier ArkUIHyperlinkModifierImpl {
            HyperlinkModifier::ConstructImpl,
            HyperlinkInterfaceModifier::SetHyperlinkOptionsImpl,
            HyperlinkAttributeModifier::SetColorImpl,
        };
        return &ArkUIHyperlinkModifierImpl;
    }

    const GENERATED_ArkUIImageModifier* GetImageModifier()
    {
        static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
            ImageModifier::ConstructImpl,
            ImageInterfaceModifier::SetImageOptionsImpl,
            ImageAttributeModifier::SetAltImpl,
            ImageAttributeModifier::SetMatchTextDirectionImpl,
            ImageAttributeModifier::SetFitOriginalSizeImpl,
            ImageAttributeModifier::SetFillColorImpl,
            ImageAttributeModifier::SetObjectFitImpl,
            ImageAttributeModifier::SetImageMatrixImpl,
            ImageAttributeModifier::SetObjectRepeatImpl,
            ImageAttributeModifier::SetAutoResizeImpl,
            ImageAttributeModifier::SetRenderModeImpl,
            ImageAttributeModifier::SetDynamicRangeModeImpl,
            ImageAttributeModifier::SetInterpolationImpl,
            ImageAttributeModifier::SetSourceSizeImpl,
            ImageAttributeModifier::SetSyncLoadImpl,
            ImageAttributeModifier::SetColorFilterImpl,
            ImageAttributeModifier::SetCopyOptionImpl,
            ImageAttributeModifier::SetDraggableImpl,
            ImageAttributeModifier::SetPointLightImpl,
            ImageAttributeModifier::SetEdgeAntialiasingImpl,
            ImageAttributeModifier::SetOnCompleteImpl,
            ImageAttributeModifier::SetOnErrorImpl,
            ImageAttributeModifier::SetOnFinishImpl,
            ImageAttributeModifier::SetEnableAnalyzerImpl,
            ImageAttributeModifier::SetAnalyzerConfigImpl,
            ImageAttributeModifier::SetResizableImpl,
            ImageAttributeModifier::SetPrivacySensitiveImpl,
            ImageAttributeModifier::SetEnhancedImageQualityImpl,
            ImageAttributeModifier::SetOrientationImpl,
        };
        return &ArkUIImageModifierImpl;
    }

    const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
    {
        static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
            ImageAnimatorModifier::ConstructImpl,
            ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
            ImageAnimatorAttributeModifier::SetImagesImpl,
            ImageAnimatorAttributeModifier::SetStateImpl,
            ImageAnimatorAttributeModifier::SetDurationImpl,
            ImageAnimatorAttributeModifier::SetReverseImpl,
            ImageAnimatorAttributeModifier::SetFixedSizeImpl,
            ImageAnimatorAttributeModifier::SetFillModeImpl,
            ImageAnimatorAttributeModifier::SetIterationsImpl,
            ImageAnimatorAttributeModifier::SetMonitorInvisibleAreaImpl,
            ImageAnimatorAttributeModifier::SetOnStartImpl,
            ImageAnimatorAttributeModifier::SetOnPauseImpl,
            ImageAnimatorAttributeModifier::SetOnRepeatImpl,
            ImageAnimatorAttributeModifier::SetOnCancelImpl,
            ImageAnimatorAttributeModifier::SetOnFinishImpl,
        };
        return &ArkUIImageAnimatorModifierImpl;
    }

    const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
    {
        static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
            ImageSpanModifier::ConstructImpl,
            ImageSpanInterfaceModifier::SetImageSpanOptionsImpl,
            ImageSpanAttributeModifier::SetVerticalAlignImpl,
            ImageSpanAttributeModifier::SetColorFilterImpl,
            ImageSpanAttributeModifier::SetObjectFitImpl,
            ImageSpanAttributeModifier::SetOnCompleteImpl,
            ImageSpanAttributeModifier::SetOnErrorImpl,
            ImageSpanAttributeModifier::SetAltImpl,
        };
        return &ArkUIImageSpanModifierImpl;
    }

    const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
    {
        static const GENERATED_ArkUIIndicatorComponentModifier ArkUIIndicatorComponentModifierImpl {
            IndicatorComponentModifier::ConstructImpl,
            IndicatorComponentInterfaceModifier::SetIndicatorComponentOptionsImpl,
            IndicatorComponentAttributeModifier::SetInitialIndexImpl,
            IndicatorComponentAttributeModifier::SetCountImpl,
            IndicatorComponentAttributeModifier::SetStyleImpl,
            IndicatorComponentAttributeModifier::SetLoopImpl,
            IndicatorComponentAttributeModifier::SetVerticalImpl,
            IndicatorComponentAttributeModifier::SetOnChangeImpl,
        };
        return &ArkUIIndicatorComponentModifierImpl;
    }

    const GENERATED_ArkUILazyGridLayoutAttributeModifier* GetLazyGridLayoutAttributeModifier()
    {
        static const GENERATED_ArkUILazyGridLayoutAttributeModifier ArkUILazyGridLayoutAttributeModifierImpl {
            LazyGridLayoutAttributeModifier::ConstructImpl,
            LazyGridLayoutAttributeModifier::SetRowsGapImpl,
            LazyGridLayoutAttributeModifier::SetColumnsGapImpl,
        };
        return &ArkUILazyGridLayoutAttributeModifierImpl;
    }

    const GENERATED_ArkUILazyVGridLayoutModifier* GetLazyVGridLayoutModifier()
    {
        static const GENERATED_ArkUILazyVGridLayoutModifier ArkUILazyVGridLayoutModifierImpl {
            LazyVGridLayoutModifier::ConstructImpl,
            LazyVGridLayoutInterfaceModifier::SetLazyVGridLayoutOptionsImpl,
            LazyVGridLayoutAttributeModifier::SetColumnsTemplateImpl,
        };
        return &ArkUILazyVGridLayoutModifierImpl;
    }

    const GENERATED_ArkUILineModifier* GetLineModifier()
    {
        static const GENERATED_ArkUILineModifier ArkUILineModifierImpl {
            LineModifier::ConstructImpl,
            LineInterfaceModifier::SetLineOptionsImpl,
            LineAttributeModifier::SetStartPointImpl,
            LineAttributeModifier::SetEndPointImpl,
        };
        return &ArkUILineModifierImpl;
    }

    const GENERATED_ArkUILinearIndicatorModifier* GetLinearIndicatorModifier()
    {
        static const GENERATED_ArkUILinearIndicatorModifier ArkUILinearIndicatorModifierImpl {
            LinearIndicatorModifier::ConstructImpl,
            LinearIndicatorInterfaceModifier::SetLinearIndicatorOptionsImpl,
            LinearIndicatorAttributeModifier::SetIndicatorStyleImpl,
            LinearIndicatorAttributeModifier::SetIndicatorLoopImpl,
            LinearIndicatorAttributeModifier::SetOnChangeImpl,
        };
        return &ArkUILinearIndicatorModifierImpl;
    }

    const GENERATED_ArkUIListModifier* GetListModifier()
    {
        static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
            ListModifier::ConstructImpl,
            ListInterfaceModifier::SetListOptionsImpl,
            ListAttributeModifier::SetAlignListItemImpl,
            ListAttributeModifier::SetListDirectionImpl,
            ListAttributeModifier::SetContentStartOffsetImpl,
            ListAttributeModifier::SetContentEndOffsetImpl,
            ListAttributeModifier::SetDividerImpl,
            ListAttributeModifier::SetMultiSelectableImpl,
            ListAttributeModifier::SetCachedCount0Impl,
            ListAttributeModifier::SetChainAnimationImpl,
            ListAttributeModifier::SetChainAnimationOptionsImpl,
            ListAttributeModifier::SetStickyImpl,
            ListAttributeModifier::SetScrollSnapAlignImpl,
            ListAttributeModifier::SetChildrenMainSizeImpl,
            ListAttributeModifier::SetMaintainVisibleContentPositionImpl,
            ListAttributeModifier::SetStackFromEndImpl,
            ListAttributeModifier::SetOnScrollIndexImpl,
            ListAttributeModifier::SetOnScrollVisibleContentChangeImpl,
            ListAttributeModifier::SetOnItemMoveImpl,
            ListAttributeModifier::SetOnItemDragStartImpl,
            ListAttributeModifier::SetOnItemDragEnterImpl,
            ListAttributeModifier::SetOnItemDragMoveImpl,
            ListAttributeModifier::SetOnItemDragLeaveImpl,
            ListAttributeModifier::SetOnItemDropImpl,
            ListAttributeModifier::SetOnScrollFrameBeginImpl,
            ListAttributeModifier::SetOnWillScrollImpl,
            ListAttributeModifier::SetOnDidScrollImpl,
            ListAttributeModifier::SetLanesImpl,
            ListAttributeModifier::SetCachedCount1Impl,
        };
        return &ArkUIListModifierImpl;
    }

    const GENERATED_ArkUIListItemModifier* GetListItemModifier()
    {
        static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
            ListItemModifier::ConstructImpl,
            ListItemInterfaceModifier::SetListItemOptionsImpl,
            ListItemAttributeModifier::SetSelectableImpl,
            ListItemAttributeModifier::SetSelectedImpl,
            ListItemAttributeModifier::SetSwipeActionImpl,
            ListItemAttributeModifier::SetOnSelectImpl,
        };
        return &ArkUIListItemModifierImpl;
    }

    const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier()
    {
        static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
            ListItemGroupModifier::ConstructImpl,
            ListItemGroupInterfaceModifier::SetListItemGroupOptionsImpl,
            ListItemGroupAttributeModifier::SetDividerImpl,
            ListItemGroupAttributeModifier::SetChildrenMainSizeImpl,
        };
        return &ArkUIListItemGroupModifierImpl;
    }

    const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressModifier()
    {
        static const GENERATED_ArkUILoadingProgressModifier ArkUILoadingProgressModifierImpl {
            LoadingProgressModifier::ConstructImpl,
            LoadingProgressInterfaceModifier::SetLoadingProgressOptionsImpl,
            LoadingProgressAttributeModifier::SetColorImpl,
            LoadingProgressAttributeModifier::SetEnableLoadingImpl,
        };
        return &ArkUILoadingProgressModifierImpl;
    }

    const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
    {
        static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
            MarqueeModifier::ConstructImpl,
            MarqueeInterfaceModifier::SetMarqueeOptionsImpl,
            MarqueeAttributeModifier::SetFontColorImpl,
            MarqueeAttributeModifier::SetFontSizeImpl,
            MarqueeAttributeModifier::SetAllowScaleImpl,
            MarqueeAttributeModifier::SetFontWeightImpl,
            MarqueeAttributeModifier::SetFontFamilyImpl,
            MarqueeAttributeModifier::SetMarqueeUpdateStrategyImpl,
            MarqueeAttributeModifier::SetOnStartImpl,
            MarqueeAttributeModifier::SetOnBounceImpl,
            MarqueeAttributeModifier::SetOnFinishImpl,
        };
        return &ArkUIMarqueeModifierImpl;
    }

    const GENERATED_ArkUIMediaCachedImageModifier* GetMediaCachedImageModifier()
    {
        static const GENERATED_ArkUIMediaCachedImageModifier ArkUIMediaCachedImageModifierImpl {
            MediaCachedImageModifier::ConstructImpl,
            MediaCachedImageInterfaceModifier::SetMediaCachedImageOptionsImpl,
        };
        return &ArkUIMediaCachedImageModifierImpl;
    }

    const GENERATED_ArkUIMenuModifier* GetMenuModifier()
    {
        static const GENERATED_ArkUIMenuModifier ArkUIMenuModifierImpl {
            MenuModifier::ConstructImpl,
            MenuInterfaceModifier::SetMenuOptionsImpl,
            MenuAttributeModifier::SetFontImpl,
            MenuAttributeModifier::SetFontColorImpl,
            MenuAttributeModifier::SetRadiusImpl,
            MenuAttributeModifier::SetMenuItemDividerImpl,
            MenuAttributeModifier::SetMenuItemGroupDividerImpl,
            MenuAttributeModifier::SetSubMenuExpandingModeImpl,
            MenuAttributeModifier::SetSubMenuExpandSymbolImpl,
        };
        return &ArkUIMenuModifierImpl;
    }

    const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier()
    {
        static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
            MenuItemModifier::ConstructImpl,
            MenuItemInterfaceModifier::SetMenuItemOptionsImpl,
            MenuItemAttributeModifier::SetSelectedImpl,
            MenuItemAttributeModifier::SetSelectIconImpl,
            MenuItemAttributeModifier::SetOnChangeImpl,
            MenuItemAttributeModifier::SetContentFontImpl,
            MenuItemAttributeModifier::SetContentFontColorImpl,
            MenuItemAttributeModifier::SetLabelFontImpl,
            MenuItemAttributeModifier::SetLabelFontColorImpl,
        };
        return &ArkUIMenuItemModifierImpl;
    }

    const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupModifier()
    {
        static const GENERATED_ArkUIMenuItemGroupModifier ArkUIMenuItemGroupModifierImpl {
            MenuItemGroupModifier::ConstructImpl,
            MenuItemGroupInterfaceModifier::SetMenuItemGroupOptionsImpl,
        };
        return &ArkUIMenuItemGroupModifierImpl;
    }

    const GENERATED_ArkUINavDestinationModifier* GetNavDestinationModifier()
    {
        static const GENERATED_ArkUINavDestinationModifier ArkUINavDestinationModifierImpl {
            NavDestinationModifier::ConstructImpl,
            NavDestinationInterfaceModifier::SetNavDestinationOptionsImpl,
            NavDestinationAttributeModifier::SetHideTitleBar0Impl,
            NavDestinationAttributeModifier::SetHideBackButtonImpl,
            NavDestinationAttributeModifier::SetOnShownImpl,
            NavDestinationAttributeModifier::SetOnHiddenImpl,
            NavDestinationAttributeModifier::SetOnBackPressedImpl,
            NavDestinationAttributeModifier::SetOnResultImpl,
            NavDestinationAttributeModifier::SetModeImpl,
            NavDestinationAttributeModifier::SetBackButtonIcon0Impl,
            NavDestinationAttributeModifier::SetMenus0Impl,
            NavDestinationAttributeModifier::SetOnReadyImpl,
            NavDestinationAttributeModifier::SetOnWillAppearImpl,
            NavDestinationAttributeModifier::SetOnWillDisappearImpl,
            NavDestinationAttributeModifier::SetOnWillShowImpl,
            NavDestinationAttributeModifier::SetOnWillHideImpl,
            NavDestinationAttributeModifier::SetSystemBarStyleImpl,
            NavDestinationAttributeModifier::SetRecoverableImpl,
            NavDestinationAttributeModifier::SetSystemTransitionImpl,
            NavDestinationAttributeModifier::SetBindToScrollableImpl,
            NavDestinationAttributeModifier::SetBindToNestedScrollableImpl,
            NavDestinationAttributeModifier::SetOnActiveImpl,
            NavDestinationAttributeModifier::SetOnInactiveImpl,
            NavDestinationAttributeModifier::SetCustomTransitionImpl,
            NavDestinationAttributeModifier::SetOnNewParamImpl,
            NavDestinationAttributeModifier::SetPreferredOrientationImpl,
            NavDestinationAttributeModifier::SetEnableNavigationIndicatorImpl,
            NavDestinationAttributeModifier::SetTitleImpl,
            NavDestinationAttributeModifier::SetHideTitleBar1Impl,
            NavDestinationAttributeModifier::SetBackButtonIcon1Impl,
            NavDestinationAttributeModifier::SetMenus1Impl,
            NavDestinationAttributeModifier::SetToolbarConfigurationImpl,
            NavDestinationAttributeModifier::SetHideToolBarImpl,
            NavDestinationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
            NavDestinationAttributeModifier::SetEnableStatusBarImpl,
        };
        return &ArkUINavDestinationModifierImpl;
    }

    const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
    {
        static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
            NavigationModifier::ConstructImpl,
            NavigationInterfaceModifier::SetNavigationOptionsImpl,
            NavigationAttributeModifier::SetNavBarWidthImpl,
            NavigationAttributeModifier::SetNavBarPositionImpl,
            NavigationAttributeModifier::SetNavBarWidthRangeImpl,
            NavigationAttributeModifier::SetMinContentWidthImpl,
            NavigationAttributeModifier::SetModeImpl,
            NavigationAttributeModifier::SetBackButtonIcon0Impl,
            NavigationAttributeModifier::SetHideNavBarImpl,
            NavigationAttributeModifier::SetHideTitleBar0Impl,
            NavigationAttributeModifier::SetHideBackButtonImpl,
            NavigationAttributeModifier::SetTitleModeImpl,
            NavigationAttributeModifier::SetMenus0Impl,
            NavigationAttributeModifier::SetHideToolBar0Impl,
            NavigationAttributeModifier::SetEnableToolBarAdaptationImpl,
            NavigationAttributeModifier::SetOnTitleModeChangeImpl,
            NavigationAttributeModifier::SetOnNavBarStateChangeImpl,
            NavigationAttributeModifier::SetOnNavigationModeChangeImpl,
            NavigationAttributeModifier::SetCustomNavContentTransitionImpl,
            NavigationAttributeModifier::SetSystemBarStyleImpl,
            NavigationAttributeModifier::SetRecoverableImpl,
            NavigationAttributeModifier::SetEnableDragBarImpl,
            NavigationAttributeModifier::SetEnableModeChangeAnimationImpl,
            NavigationAttributeModifier::SetBackButtonIcon1Impl,
            NavigationAttributeModifier::SetTitleImpl,
            NavigationAttributeModifier::SetHideTitleBar1Impl,
            NavigationAttributeModifier::SetMenus1Impl,
            NavigationAttributeModifier::SetToolbarConfigurationImpl,
            NavigationAttributeModifier::SetHideToolBar1Impl,
            NavigationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
        };
        return &ArkUINavigationModifierImpl;
    }

    const GENERATED_ArkUINodeContainerModifier* GetNodeContainerModifier()
    {
        static const GENERATED_ArkUINodeContainerModifier ArkUINodeContainerModifierImpl {
            NodeContainerModifier::ConstructImpl,
            NodeContainerInterfaceModifier::SetNodeContainerOptionsImpl,
        };
        return &ArkUINodeContainerModifierImpl;
    }

    const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier()
    {
        static const GENERATED_ArkUIPasteButtonModifier ArkUIPasteButtonModifierImpl {
            PasteButtonModifier::ConstructImpl,
            PasteButtonInterfaceModifier::SetPasteButtonOptionsImpl,
            PasteButtonAttributeModifier::SetOnClickImpl,
        };
        return &ArkUIPasteButtonModifierImpl;
    }

    const GENERATED_ArkUIPathModifier* GetPathModifier()
    {
        static const GENERATED_ArkUIPathModifier ArkUIPathModifierImpl {
            PathModifier::ConstructImpl,
            PathInterfaceModifier::SetPathOptionsImpl,
            PathAttributeModifier::SetCommandsImpl,
        };
        return &ArkUIPathModifierImpl;
    }

    const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
    {
        static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
            PatternLockModifier::ConstructImpl,
            PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
            PatternLockAttributeModifier::SetSideLengthImpl,
            PatternLockAttributeModifier::SetCircleRadiusImpl,
            PatternLockAttributeModifier::SetBackgroundColorImpl,
            PatternLockAttributeModifier::SetRegularColorImpl,
            PatternLockAttributeModifier::SetSelectedColorImpl,
            PatternLockAttributeModifier::SetActiveColorImpl,
            PatternLockAttributeModifier::SetPathColorImpl,
            PatternLockAttributeModifier::SetPathStrokeWidthImpl,
            PatternLockAttributeModifier::SetOnPatternCompleteImpl,
            PatternLockAttributeModifier::SetAutoResetImpl,
            PatternLockAttributeModifier::SetOnDotConnectImpl,
            PatternLockAttributeModifier::SetActivateCircleStyleImpl,
            PatternLockAttributeModifier::SetSkipUnselectedPointImpl,
        };
        return &ArkUIPatternLockModifierImpl;
    }

    const GENERATED_ArkUIPluginComponentModifier* GetPluginComponentModifier()
    {
        static const GENERATED_ArkUIPluginComponentModifier ArkUIPluginComponentModifierImpl {
            PluginComponentModifier::ConstructImpl,
            PluginComponentInterfaceModifier::SetPluginComponentOptionsImpl,
            PluginComponentAttributeModifier::SetOnCompleteImpl,
            PluginComponentAttributeModifier::SetOnErrorImpl,
        };
        return &ArkUIPluginComponentModifierImpl;
    }

    const GENERATED_ArkUIPolygonModifier* GetPolygonModifier()
    {
        static const GENERATED_ArkUIPolygonModifier ArkUIPolygonModifierImpl {
            PolygonModifier::ConstructImpl,
            PolygonInterfaceModifier::SetPolygonOptionsImpl,
            PolygonAttributeModifier::SetPointsImpl,
        };
        return &ArkUIPolygonModifierImpl;
    }

    const GENERATED_ArkUIPolylineModifier* GetPolylineModifier()
    {
        static const GENERATED_ArkUIPolylineModifier ArkUIPolylineModifierImpl {
            PolylineModifier::ConstructImpl,
            PolylineInterfaceModifier::SetPolylineOptionsImpl,
            PolylineAttributeModifier::SetPointsImpl,
        };
        return &ArkUIPolylineModifierImpl;
    }

    const GENERATED_ArkUIProgressModifier* GetProgressModifier()
    {
        static const GENERATED_ArkUIProgressModifier ArkUIProgressModifierImpl {
            ProgressModifier::ConstructImpl,
            ProgressInterfaceModifier::SetProgressOptionsImpl,
            ProgressAttributeModifier::SetValueImpl,
            ProgressAttributeModifier::SetColorImpl,
            ProgressAttributeModifier::SetStyleImpl,
            ProgressAttributeModifier::SetPrivacySensitiveImpl,
        };
        return &ArkUIProgressModifierImpl;
    }

    const GENERATED_ArkUIQRCodeModifier* GetQRCodeModifier()
    {
        static const GENERATED_ArkUIQRCodeModifier ArkUIQRCodeModifierImpl {
            QRCodeModifier::ConstructImpl,
            QRCodeInterfaceModifier::SetQRCodeOptionsImpl,
            QRCodeAttributeModifier::SetColorImpl,
            QRCodeAttributeModifier::SetBackgroundColorImpl,
            QRCodeAttributeModifier::SetContentOpacityImpl,
        };
        return &ArkUIQRCodeModifierImpl;
    }

    const GENERATED_ArkUIRadioModifier* GetRadioModifier()
    {
        static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
            RadioModifier::ConstructImpl,
            RadioInterfaceModifier::SetRadioOptionsImpl,
            RadioAttributeModifier::SetCheckedImpl,
            RadioAttributeModifier::SetOnChangeImpl,
            RadioAttributeModifier::SetRadioStyleImpl,
        };
        return &ArkUIRadioModifierImpl;
    }

    const GENERATED_ArkUIRatingModifier* GetRatingModifier()
    {
        static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
            RatingModifier::ConstructImpl,
            RatingInterfaceModifier::SetRatingOptionsImpl,
            RatingAttributeModifier::SetStarsImpl,
            RatingAttributeModifier::SetStepSizeImpl,
            RatingAttributeModifier::SetStarStyleImpl,
            RatingAttributeModifier::SetOnChangeImpl,
        };
        return &ArkUIRatingModifierImpl;
    }

    const GENERATED_ArkUIRectModifier* GetRectModifier()
    {
        static const GENERATED_ArkUIRectModifier ArkUIRectModifierImpl {
            RectModifier::ConstructImpl,
            RectInterfaceModifier::SetRectOptionsImpl,
            RectAttributeModifier::SetRadiusWidthImpl,
            RectAttributeModifier::SetRadiusHeightImpl,
            RectAttributeModifier::SetRadiusImpl,
        };
        return &ArkUIRectModifierImpl;
    }

    const GENERATED_ArkUIRefreshModifier* GetRefreshModifier()
    {
        static const GENERATED_ArkUIRefreshModifier ArkUIRefreshModifierImpl {
            RefreshModifier::ConstructImpl,
            RefreshInterfaceModifier::SetRefreshOptionsImpl,
            RefreshAttributeModifier::SetOnStateChangeImpl,
            RefreshAttributeModifier::SetOnRefreshingImpl,
            RefreshAttributeModifier::SetRefreshOffsetImpl,
            RefreshAttributeModifier::SetPullToRefreshImpl,
            RefreshAttributeModifier::SetOnOffsetChangeImpl,
            RefreshAttributeModifier::SetPullDownRatioImpl,
        };
        return &ArkUIRefreshModifierImpl;
    }

    const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier()
    {
        static const GENERATED_ArkUIRelativeContainerModifier ArkUIRelativeContainerModifierImpl {
            RelativeContainerModifier::ConstructImpl,
            RelativeContainerInterfaceModifier::SetRelativeContainerOptionsImpl,
            RelativeContainerAttributeModifier::SetGuideLineImpl,
            RelativeContainerAttributeModifier::SetBarrierImpl,
        };
        return &ArkUIRelativeContainerModifierImpl;
    }

    const GENERATED_ArkUIRemoteWindowModifier* GetRemoteWindowModifier()
    {
        static const GENERATED_ArkUIRemoteWindowModifier ArkUIRemoteWindowModifierImpl {
            RemoteWindowModifier::ConstructImpl,
            RemoteWindowInterfaceModifier::SetRemoteWindowOptionsImpl,
        };
        return &ArkUIRemoteWindowModifierImpl;
    }

    const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
    {
        static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
            RichEditorModifier::ConstructImpl,
            RichEditorInterfaceModifier::SetRichEditorOptionsImpl,
            RichEditorAttributeModifier::SetOnReadyImpl,
            RichEditorAttributeModifier::SetOnSelectImpl,
            RichEditorAttributeModifier::SetOnSelectionChangeImpl,
            RichEditorAttributeModifier::SetAboutToIMEInputImpl,
            RichEditorAttributeModifier::SetOnIMEInputCompleteImpl,
            RichEditorAttributeModifier::SetOnDidIMEInputImpl,
            RichEditorAttributeModifier::SetAboutToDeleteImpl,
            RichEditorAttributeModifier::SetOnDeleteCompleteImpl,
            RichEditorAttributeModifier::SetCopyOptionsImpl,
            RichEditorAttributeModifier::SetOnPasteImpl,
            RichEditorAttributeModifier::SetEnableDataDetectorImpl,
            RichEditorAttributeModifier::SetEnablePreviewTextImpl,
            RichEditorAttributeModifier::SetDataDetectorConfigImpl,
            RichEditorAttributeModifier::SetCaretColorImpl,
            RichEditorAttributeModifier::SetSelectedBackgroundColorImpl,
            RichEditorAttributeModifier::SetOnEditingChangeImpl,
            RichEditorAttributeModifier::SetEnterKeyTypeImpl,
            RichEditorAttributeModifier::SetOnSubmitImpl,
            RichEditorAttributeModifier::SetOnWillChangeImpl,
            RichEditorAttributeModifier::SetOnDidChangeImpl,
            RichEditorAttributeModifier::SetOnCutImpl,
            RichEditorAttributeModifier::SetOnCopyImpl,
            RichEditorAttributeModifier::SetEditMenuOptionsImpl,
            RichEditorAttributeModifier::SetEnableKeyboardOnFocusImpl,
            RichEditorAttributeModifier::SetEnableHapticFeedbackImpl,
            RichEditorAttributeModifier::SetBarStateImpl,
            RichEditorAttributeModifier::SetMaxLengthImpl,
            RichEditorAttributeModifier::SetMaxLinesImpl,
            RichEditorAttributeModifier::SetKeyboardAppearanceImpl,
            RichEditorAttributeModifier::SetStopBackPressImpl,
            RichEditorAttributeModifier::SetBindSelectionMenuImpl,
            RichEditorAttributeModifier::SetCustomKeyboardImpl,
            RichEditorAttributeModifier::SetPlaceholderImpl,
        };
        return &ArkUIRichEditorModifierImpl;
    }

    const GENERATED_ArkUIRichTextModifier* GetRichTextModifier()
    {
        static const GENERATED_ArkUIRichTextModifier ArkUIRichTextModifierImpl {
            RichTextModifier::ConstructImpl,
            RichTextInterfaceModifier::SetRichTextOptionsImpl,
            RichTextAttributeModifier::SetOnStartImpl,
            RichTextAttributeModifier::SetOnCompleteImpl,
        };
        return &ArkUIRichTextModifierImpl;
    }

    const GENERATED_ArkUIRootModifier* GetRootModifier()
    {
        static const GENERATED_ArkUIRootModifier ArkUIRootModifierImpl {
            RootModifier::ConstructImpl,
        };
        return &ArkUIRootModifierImpl;
    }

    const GENERATED_ArkUIRootSceneModifier* GetRootSceneModifier()
    {
        static const GENERATED_ArkUIRootSceneModifier ArkUIRootSceneModifierImpl {
            RootSceneModifier::ConstructImpl,
            RootSceneInterfaceModifier::SetRootSceneOptionsImpl,
        };
        return &ArkUIRootSceneModifierImpl;
    }

    const GENERATED_ArkUIRowModifier* GetRowModifier()
    {
        static const GENERATED_ArkUIRowModifier ArkUIRowModifierImpl {
            RowModifier::ConstructImpl,
            RowInterfaceModifier::SetRowOptionsImpl,
            RowAttributeModifier::SetAlignItemsImpl,
            RowAttributeModifier::SetJustifyContentImpl,
            RowAttributeModifier::SetReverseImpl,
        };
        return &ArkUIRowModifierImpl;
    }

    const GENERATED_ArkUIRowSplitModifier* GetRowSplitModifier()
    {
        static const GENERATED_ArkUIRowSplitModifier ArkUIRowSplitModifierImpl {
            RowSplitModifier::ConstructImpl,
            RowSplitInterfaceModifier::SetRowSplitOptionsImpl,
            RowSplitAttributeModifier::SetResizeableImpl,
        };
        return &ArkUIRowSplitModifierImpl;
    }

    const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier()
    {
        static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
            SaveButtonModifier::ConstructImpl,
            SaveButtonInterfaceModifier::SetSaveButtonOptionsImpl,
            SaveButtonAttributeModifier::SetOnClickImpl,
            SaveButtonAttributeModifier::SetSetIconImpl,
            SaveButtonAttributeModifier::SetSetTextImpl,
            SaveButtonAttributeModifier::SetIconSizeImpl,
            SaveButtonAttributeModifier::SetIconBorderRadiusImpl,
            SaveButtonAttributeModifier::SetStateEffectImpl,
            SaveButtonAttributeModifier::SetUserCancelEventImpl,
        };
        return &ArkUISaveButtonModifierImpl;
    }

    const GENERATED_ArkUIScreenModifier* GetScreenModifier()
    {
        static const GENERATED_ArkUIScreenModifier ArkUIScreenModifierImpl {
            ScreenModifier::ConstructImpl,
            ScreenInterfaceModifier::SetScreenOptionsImpl,
        };
        return &ArkUIScreenModifierImpl;
    }

    const GENERATED_ArkUIScrollModifier* GetScrollModifier()
    {
        static const GENERATED_ArkUIScrollModifier ArkUIScrollModifierImpl {
            ScrollModifier::ConstructImpl,
            ScrollInterfaceModifier::SetScrollOptionsImpl,
            ScrollAttributeModifier::SetScrollableImpl,
            ScrollAttributeModifier::SetOnWillScrollImpl,
            ScrollAttributeModifier::SetOnDidScrollImpl,
            ScrollAttributeModifier::SetOnScrollEdgeImpl,
            ScrollAttributeModifier::SetOnScrollStartImpl,
            ScrollAttributeModifier::SetOnScrollStopImpl,
            ScrollAttributeModifier::SetScrollBarImpl,
            ScrollAttributeModifier::SetScrollBarColorImpl,
            ScrollAttributeModifier::SetScrollBarWidthImpl,
            ScrollAttributeModifier::SetOnScrollFrameBeginImpl,
            ScrollAttributeModifier::SetNestedScrollImpl,
            ScrollAttributeModifier::SetEnableScrollInteractionImpl,
            ScrollAttributeModifier::SetFrictionImpl,
            ScrollAttributeModifier::SetScrollSnapImpl,
            ScrollAttributeModifier::SetEnablePagingImpl,
            ScrollAttributeModifier::SetInitialOffsetImpl,
            ScrollAttributeModifier::SetEdgeEffectImpl,
        };
        return &ArkUIScrollModifierImpl;
    }

    const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
    {
        static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
            ScrollableCommonMethodModifier::ConstructImpl,
            ScrollableCommonMethodModifier::SetScrollBarImpl,
            ScrollableCommonMethodModifier::SetScrollBarColorImpl,
            ScrollableCommonMethodModifier::SetScrollBarWidthImpl,
            ScrollableCommonMethodModifier::SetNestedScrollImpl,
            ScrollableCommonMethodModifier::SetEnableScrollInteractionImpl,
            ScrollableCommonMethodModifier::SetFrictionImpl,
            ScrollableCommonMethodModifier::SetOnReachStartImpl,
            ScrollableCommonMethodModifier::SetOnReachEndImpl,
            ScrollableCommonMethodModifier::SetOnScrollStartImpl,
            ScrollableCommonMethodModifier::SetOnScrollStopImpl,
            ScrollableCommonMethodModifier::SetFlingSpeedLimitImpl,
            ScrollableCommonMethodModifier::SetClipContentImpl,
            ScrollableCommonMethodModifier::SetDigitalCrownSensitivityImpl,
            ScrollableCommonMethodModifier::SetBackToTopImpl,
            ScrollableCommonMethodModifier::SetEdgeEffectImpl,
            ScrollableCommonMethodModifier::SetFadingEdgeImpl,
        };
        return &ArkUIScrollableCommonMethodModifierImpl;
    }

    const GENERATED_ArkUIScrollBarModifier* GetScrollBarModifier()
    {
        static const GENERATED_ArkUIScrollBarModifier ArkUIScrollBarModifierImpl {
            ScrollBarModifier::ConstructImpl,
            ScrollBarInterfaceModifier::SetScrollBarOptionsImpl,
            ScrollBarAttributeModifier::SetEnableNestedScrollImpl,
        };
        return &ArkUIScrollBarModifierImpl;
    }

    const GENERATED_ArkUISearchModifier* GetSearchModifier()
    {
        static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
            SearchModifier::ConstructImpl,
            SearchInterfaceModifier::SetSearchOptionsImpl,
            SearchAttributeModifier::SetFontColorImpl,
            SearchAttributeModifier::SetSearchIconImpl,
            SearchAttributeModifier::SetCancelButtonImpl,
            SearchAttributeModifier::SetTextIndentImpl,
            SearchAttributeModifier::SetOnEditChangeImpl,
            SearchAttributeModifier::SetSelectedBackgroundColorImpl,
            SearchAttributeModifier::SetCaretStyleImpl,
            SearchAttributeModifier::SetPlaceholderColorImpl,
            SearchAttributeModifier::SetPlaceholderFontImpl,
            SearchAttributeModifier::SetTextFontImpl,
            SearchAttributeModifier::SetEnterKeyTypeImpl,
            SearchAttributeModifier::SetOnSubmitImpl,
            SearchAttributeModifier::SetOnChangeImpl,
            SearchAttributeModifier::SetOnTextSelectionChangeImpl,
            SearchAttributeModifier::SetOnContentScrollImpl,
            SearchAttributeModifier::SetOnCopyImpl,
            SearchAttributeModifier::SetOnCutImpl,
            SearchAttributeModifier::SetOnPasteImpl,
            SearchAttributeModifier::SetCopyOptionImpl,
            SearchAttributeModifier::SetMaxLengthImpl,
            SearchAttributeModifier::SetTextAlignImpl,
            SearchAttributeModifier::SetEnableKeyboardOnFocusImpl,
            SearchAttributeModifier::SetSelectionMenuHiddenImpl,
            SearchAttributeModifier::SetMinFontSizeImpl,
            SearchAttributeModifier::SetMaxFontSizeImpl,
            SearchAttributeModifier::SetMinFontScaleImpl,
            SearchAttributeModifier::SetMaxFontScaleImpl,
            SearchAttributeModifier::SetDecorationImpl,
            SearchAttributeModifier::SetLetterSpacingImpl,
            SearchAttributeModifier::SetLineHeightImpl,
            SearchAttributeModifier::SetTypeImpl,
            SearchAttributeModifier::SetFontFeatureImpl,
            SearchAttributeModifier::SetOnWillInsertImpl,
            SearchAttributeModifier::SetOnDidInsertImpl,
            SearchAttributeModifier::SetOnWillDeleteImpl,
            SearchAttributeModifier::SetOnDidDeleteImpl,
            SearchAttributeModifier::SetEditMenuOptionsImpl,
            SearchAttributeModifier::SetEnablePreviewTextImpl,
            SearchAttributeModifier::SetEnableHapticFeedbackImpl,
            SearchAttributeModifier::SetAutoCapitalizationModeImpl,
            SearchAttributeModifier::SetHalfLeadingImpl,
            SearchAttributeModifier::SetStopBackPressImpl,
            SearchAttributeModifier::SetOnWillChangeImpl,
            SearchAttributeModifier::SetKeyboardAppearanceImpl,
            SearchAttributeModifier::SetDividerColorImpl,
            SearchAttributeModifier::SetSearchButtonImpl,
            SearchAttributeModifier::SetInputFilterImpl,
            SearchAttributeModifier::SetCustomKeyboardImpl,
        };
        return &ArkUISearchModifierImpl;
    }

    const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
    {
        static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
            SecurityComponentMethodModifier::ConstructImpl,
            SecurityComponentMethodModifier::SetIconSizeImpl,
            SecurityComponentMethodModifier::SetLayoutDirectionImpl,
            SecurityComponentMethodModifier::SetPositionImpl,
            SecurityComponentMethodModifier::SetMarkAnchorImpl,
            SecurityComponentMethodModifier::SetOffsetImpl,
            SecurityComponentMethodModifier::SetFontSizeImpl,
            SecurityComponentMethodModifier::SetFontStyleImpl,
            SecurityComponentMethodModifier::SetFontWeightImpl,
            SecurityComponentMethodModifier::SetFontFamilyImpl,
            SecurityComponentMethodModifier::SetFontColorImpl,
            SecurityComponentMethodModifier::SetIconColorImpl,
            SecurityComponentMethodModifier::SetBackgroundColorImpl,
            SecurityComponentMethodModifier::SetBorderStyleImpl,
            SecurityComponentMethodModifier::SetBorderWidthImpl,
            SecurityComponentMethodModifier::SetBorderColorImpl,
            SecurityComponentMethodModifier::SetBorderRadiusImpl,
            SecurityComponentMethodModifier::SetPaddingImpl,
            SecurityComponentMethodModifier::SetTextIconSpaceImpl,
            SecurityComponentMethodModifier::SetKeyImpl,
            SecurityComponentMethodModifier::SetWidthImpl,
            SecurityComponentMethodModifier::SetHeightImpl,
            SecurityComponentMethodModifier::SetSizeImpl,
            SecurityComponentMethodModifier::SetConstraintSizeImpl,
            SecurityComponentMethodModifier::SetAlignImpl,
            SecurityComponentMethodModifier::SetAlignRulesImpl,
            SecurityComponentMethodModifier::SetIdImpl,
            SecurityComponentMethodModifier::SetChainModeImpl,
            SecurityComponentMethodModifier::SetMinFontScaleImpl,
            SecurityComponentMethodModifier::SetMaxFontScaleImpl,
            SecurityComponentMethodModifier::SetMaxLinesImpl,
            SecurityComponentMethodModifier::SetMinFontSizeImpl,
            SecurityComponentMethodModifier::SetMaxFontSizeImpl,
            SecurityComponentMethodModifier::SetHeightAdaptivePolicyImpl,
            SecurityComponentMethodModifier::SetEnabledImpl,
            SecurityComponentMethodModifier::SetFocusBoxImpl,
        };
        return &ArkUISecurityComponentMethodModifierImpl;
    }

    const GENERATED_ArkUISelectModifier* GetSelectModifier()
    {
        static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
            SelectModifier::ConstructImpl,
            SelectInterfaceModifier::SetSelectOptionsImpl,
            SelectAttributeModifier::SetSelectedImpl,
            SelectAttributeModifier::SetValueImpl,
            SelectAttributeModifier::SetFontImpl,
            SelectAttributeModifier::SetFontColorImpl,
            SelectAttributeModifier::SetSelectedOptionBgColorImpl,
            SelectAttributeModifier::SetSelectedOptionFontImpl,
            SelectAttributeModifier::SetSelectedOptionFontColorImpl,
            SelectAttributeModifier::SetOptionBgColorImpl,
            SelectAttributeModifier::SetOptionFontImpl,
            SelectAttributeModifier::SetOptionFontColorImpl,
            SelectAttributeModifier::SetOnSelectImpl,
            SelectAttributeModifier::SetSpaceImpl,
            SelectAttributeModifier::SetArrowPositionImpl,
            SelectAttributeModifier::SetOptionWidthImpl,
            SelectAttributeModifier::SetOptionHeightImpl,
            SelectAttributeModifier::SetMenuBackgroundColorImpl,
            SelectAttributeModifier::SetMenuBackgroundBlurStyleImpl,
            SelectAttributeModifier::SetControlSizeImpl,
            SelectAttributeModifier::SetTextModifierImpl,
            SelectAttributeModifier::SetArrowModifierImpl,
            SelectAttributeModifier::SetOptionTextModifierImpl,
            SelectAttributeModifier::SetSelectedOptionTextModifierImpl,
            SelectAttributeModifier::SetDividerStyleImpl,
            SelectAttributeModifier::SetAvoidanceImpl,
            SelectAttributeModifier::SetMenuOutlineImpl,
            SelectAttributeModifier::SetShowInSubWindowImpl,
            SelectAttributeModifier::SetShowDefaultSelectedIconImpl,
            SelectAttributeModifier::SetBackgroundColorImpl,
            SelectAttributeModifier::SetMenuAlignImpl,
        };
        return &ArkUISelectModifierImpl;
    }

    const GENERATED_ArkUIShapeModifier* GetShapeModifier()
    {
        static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
            ShapeModifier::ConstructImpl,
            ShapeInterfaceModifier::SetShapeOptionsImpl,
            ShapeAttributeModifier::SetViewPortImpl,
            ShapeAttributeModifier::SetStrokeImpl,
            ShapeAttributeModifier::SetFillImpl,
            ShapeAttributeModifier::SetStrokeDashOffsetImpl,
            ShapeAttributeModifier::SetStrokeDashArrayImpl,
            ShapeAttributeModifier::SetStrokeLineCapImpl,
            ShapeAttributeModifier::SetStrokeLineJoinImpl,
            ShapeAttributeModifier::SetStrokeMiterLimitImpl,
            ShapeAttributeModifier::SetStrokeOpacityImpl,
            ShapeAttributeModifier::SetFillOpacityImpl,
            ShapeAttributeModifier::SetStrokeWidthImpl,
            ShapeAttributeModifier::SetAntiAliasImpl,
            ShapeAttributeModifier::SetMeshImpl,
        };
        return &ArkUIShapeModifierImpl;
    }

    const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier()
    {
        static const GENERATED_ArkUISideBarContainerModifier ArkUISideBarContainerModifierImpl {
            SideBarContainerModifier::ConstructImpl,
            SideBarContainerInterfaceModifier::SetSideBarContainerOptionsImpl,
            SideBarContainerAttributeModifier::SetShowSideBarImpl,
            SideBarContainerAttributeModifier::SetControlButtonImpl,
            SideBarContainerAttributeModifier::SetShowControlButtonImpl,
            SideBarContainerAttributeModifier::SetOnChangeImpl,
            SideBarContainerAttributeModifier::SetSideBarWidthImpl,
            SideBarContainerAttributeModifier::SetMinSideBarWidth0Impl,
            SideBarContainerAttributeModifier::SetMaxSideBarWidth0Impl,
            SideBarContainerAttributeModifier::SetMinSideBarWidth1Impl,
            SideBarContainerAttributeModifier::SetMaxSideBarWidth1Impl,
            SideBarContainerAttributeModifier::SetAutoHideImpl,
            SideBarContainerAttributeModifier::SetSideBarPositionImpl,
            SideBarContainerAttributeModifier::SetDividerImpl,
            SideBarContainerAttributeModifier::SetMinContentWidthImpl,
        };
        return &ArkUISideBarContainerModifierImpl;
    }

    const GENERATED_ArkUISliderModifier* GetSliderModifier()
    {
        static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
            SliderModifier::ConstructImpl,
            SliderInterfaceModifier::SetSliderOptionsImpl,
            SliderAttributeModifier::SetBlockColorImpl,
            SliderAttributeModifier::SetTrackColorImpl,
            SliderAttributeModifier::SetSelectedColorImpl,
            SliderAttributeModifier::SetShowSteps0Impl,
            SliderAttributeModifier::SetTrackThicknessImpl,
            SliderAttributeModifier::SetOnChangeImpl,
            SliderAttributeModifier::SetBlockBorderColorImpl,
            SliderAttributeModifier::SetBlockBorderWidthImpl,
            SliderAttributeModifier::SetStepColorImpl,
            SliderAttributeModifier::SetTrackBorderRadiusImpl,
            SliderAttributeModifier::SetSelectedBorderRadiusImpl,
            SliderAttributeModifier::SetBlockSizeImpl,
            SliderAttributeModifier::SetBlockStyleImpl,
            SliderAttributeModifier::SetStepSizeImpl,
            SliderAttributeModifier::SetSliderInteractionModeImpl,
            SliderAttributeModifier::SetMinResponsiveDistanceImpl,
            SliderAttributeModifier::SetSlideRangeImpl,
            SliderAttributeModifier::SetDigitalCrownSensitivityImpl,
            SliderAttributeModifier::SetEnableHapticFeedbackImpl,
            SliderAttributeModifier::SetShowSteps1Impl,
            SliderAttributeModifier::SetShowTipsImpl,
        };
        return &ArkUISliderModifierImpl;
    }

    const GENERATED_ArkUISpanModifier* GetSpanModifier()
    {
        static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
            SpanModifier::ConstructImpl,
            SpanInterfaceModifier::SetSpanOptionsImpl,
            SpanAttributeModifier::SetFontImpl,
            SpanAttributeModifier::SetFontColorImpl,
            SpanAttributeModifier::SetFontSizeImpl,
            SpanAttributeModifier::SetFontStyleImpl,
            SpanAttributeModifier::SetFontWeightImpl,
            SpanAttributeModifier::SetFontFamilyImpl,
            SpanAttributeModifier::SetDecorationImpl,
            SpanAttributeModifier::SetLetterSpacingImpl,
            SpanAttributeModifier::SetTextCaseImpl,
            SpanAttributeModifier::SetLineHeightImpl,
            SpanAttributeModifier::SetTextShadowImpl,
            SpanAttributeModifier::SetTextBackgroundStyleImpl,
            SpanAttributeModifier::SetBaselineOffsetImpl,
            SpanAttributeModifier::SetKeyImpl,
            SpanAttributeModifier::SetIdImpl,
            SpanAttributeModifier::SetOnClick0Impl,
            SpanAttributeModifier::SetOnHoverImpl,
            SpanAttributeModifier::SetOnClick1Impl,
        };
        return &ArkUISpanModifierImpl;
    }

    const GENERATED_ArkUIStackModifier* GetStackModifier()
    {
        static const GENERATED_ArkUIStackModifier ArkUIStackModifierImpl {
            StackModifier::ConstructImpl,
            StackInterfaceModifier::SetStackOptionsImpl,
            StackAttributeModifier::SetAlignContentImpl,
        };
        return &ArkUIStackModifierImpl;
    }

    const GENERATED_ArkUIStepperModifier* GetStepperModifier()
    {
        static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
            StepperModifier::ConstructImpl,
            StepperInterfaceModifier::SetStepperOptionsImpl,
            StepperAttributeModifier::SetOnFinishImpl,
            StepperAttributeModifier::SetOnSkipImpl,
            StepperAttributeModifier::SetOnChangeImpl,
            StepperAttributeModifier::SetOnNextImpl,
            StepperAttributeModifier::SetOnPreviousImpl,
        };
        return &ArkUIStepperModifierImpl;
    }

    const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier()
    {
        static const GENERATED_ArkUIStepperItemModifier ArkUIStepperItemModifierImpl {
            StepperItemModifier::ConstructImpl,
            StepperItemInterfaceModifier::SetStepperItemOptionsImpl,
            StepperItemAttributeModifier::SetPrevLabelImpl,
            StepperItemAttributeModifier::SetNextLabelImpl,
            StepperItemAttributeModifier::SetStatusImpl,
        };
        return &ArkUIStepperItemModifierImpl;
    }

    const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
    {
        static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
            SwiperModifier::ConstructImpl,
            SwiperInterfaceModifier::SetSwiperOptionsImpl,
            SwiperAttributeModifier::SetIndexImpl,
            SwiperAttributeModifier::SetAutoPlay0Impl,
            SwiperAttributeModifier::SetIntervalImpl,
            SwiperAttributeModifier::SetIndicatorImpl,
            SwiperAttributeModifier::SetLoopImpl,
            SwiperAttributeModifier::SetDurationImpl,
            SwiperAttributeModifier::SetVerticalImpl,
            SwiperAttributeModifier::SetItemSpaceImpl,
            SwiperAttributeModifier::SetDisplayModeImpl,
            SwiperAttributeModifier::SetCachedCount0Impl,
            SwiperAttributeModifier::SetEffectModeImpl,
            SwiperAttributeModifier::SetDisableSwipeImpl,
            SwiperAttributeModifier::SetCurveImpl,
            SwiperAttributeModifier::SetOnChangeImpl,
            SwiperAttributeModifier::SetOnSelectedImpl,
            SwiperAttributeModifier::SetOnUnselectedImpl,
            SwiperAttributeModifier::SetOnAnimationStartImpl,
            SwiperAttributeModifier::SetOnAnimationEndImpl,
            SwiperAttributeModifier::SetOnGestureSwipeImpl,
            SwiperAttributeModifier::SetNestedScrollImpl,
            SwiperAttributeModifier::SetCustomContentTransitionImpl,
            SwiperAttributeModifier::SetOnContentDidScrollImpl,
            SwiperAttributeModifier::SetIndicatorInteractiveImpl,
            SwiperAttributeModifier::SetPageFlipModeImpl,
            SwiperAttributeModifier::SetOnContentWillScrollImpl,
            SwiperAttributeModifier::SetAutoPlay1Impl,
            SwiperAttributeModifier::SetDisplayArrowImpl,
            SwiperAttributeModifier::SetCachedCount1Impl,
            SwiperAttributeModifier::SetDisplayCountImpl,
            SwiperAttributeModifier::SetPrevMarginImpl,
            SwiperAttributeModifier::SetNextMarginImpl,
        };
        return &ArkUISwiperModifierImpl;
    }

    const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
    {
        static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
            SymbolGlyphModifier::ConstructImpl,
            SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
            SymbolGlyphAttributeModifier::SetFontSizeImpl,
            SymbolGlyphAttributeModifier::SetFontColorImpl,
            SymbolGlyphAttributeModifier::SetFontWeightImpl,
            SymbolGlyphAttributeModifier::SetEffectStrategyImpl,
            SymbolGlyphAttributeModifier::SetRenderingStrategyImpl,
            SymbolGlyphAttributeModifier::SetSymbolEffect0Impl,
            SymbolGlyphAttributeModifier::SetMinFontScaleImpl,
            SymbolGlyphAttributeModifier::SetMaxFontScaleImpl,
            SymbolGlyphAttributeModifier::SetSymbolEffect1Impl,
            SymbolGlyphAttributeModifier::SetSymbolEffect2Impl,
        };
        return &ArkUISymbolGlyphModifierImpl;
    }

    const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanModifier()
    {
        static const GENERATED_ArkUISymbolSpanModifier ArkUISymbolSpanModifierImpl {
            SymbolSpanModifier::ConstructImpl,
            SymbolSpanInterfaceModifier::SetSymbolSpanOptionsImpl,
            SymbolSpanAttributeModifier::SetFontSizeImpl,
            SymbolSpanAttributeModifier::SetFontColorImpl,
            SymbolSpanAttributeModifier::SetFontWeightImpl,
            SymbolSpanAttributeModifier::SetEffectStrategyImpl,
            SymbolSpanAttributeModifier::SetRenderingStrategyImpl,
            SymbolSpanAttributeModifier::SetKeyImpl,
            SymbolSpanAttributeModifier::SetIdImpl,
        };
        return &ArkUISymbolSpanModifierImpl;
    }

    const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
    {
        static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
            TabContentModifier::ConstructImpl,
            TabContentInterfaceModifier::SetTabContentOptionsImpl,
            TabContentAttributeModifier::SetTabBarImpl,
            TabContentAttributeModifier::SetOnWillShowImpl,
            TabContentAttributeModifier::SetOnWillHideImpl,
        };
        return &ArkUITabContentModifierImpl;
    }

    const GENERATED_ArkUITabsModifier* GetTabsModifier()
    {
        static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
            TabsModifier::ConstructImpl,
            TabsInterfaceModifier::SetTabsOptionsImpl,
            TabsAttributeModifier::SetVerticalImpl,
            TabsAttributeModifier::SetBarPositionImpl,
            TabsAttributeModifier::SetScrollableImpl,
            TabsAttributeModifier::SetBarWidthImpl,
            TabsAttributeModifier::SetAnimationCurveImpl,
            TabsAttributeModifier::SetAnimationDurationImpl,
            TabsAttributeModifier::SetAnimationModeImpl,
            TabsAttributeModifier::SetEdgeEffectImpl,
            TabsAttributeModifier::SetOnChangeImpl,
            TabsAttributeModifier::SetOnSelectedImpl,
            TabsAttributeModifier::SetOnTabBarClickImpl,
            TabsAttributeModifier::SetOnUnselectedImpl,
            TabsAttributeModifier::SetOnAnimationStartImpl,
            TabsAttributeModifier::SetOnAnimationEndImpl,
            TabsAttributeModifier::SetOnGestureSwipeImpl,
            TabsAttributeModifier::SetFadingEdgeImpl,
            TabsAttributeModifier::SetDividerImpl,
            TabsAttributeModifier::SetBarOverlapImpl,
            TabsAttributeModifier::SetBarBackgroundColorImpl,
            TabsAttributeModifier::SetBarGridAlignImpl,
            TabsAttributeModifier::SetCustomContentTransitionImpl,
            TabsAttributeModifier::SetBarBackgroundBlurStyle0Impl,
            TabsAttributeModifier::SetPageFlipModeImpl,
            TabsAttributeModifier::SetBarBackgroundEffectImpl,
            TabsAttributeModifier::SetOnContentWillChangeImpl,
            TabsAttributeModifier::SetOnContentDidScrollImpl,
            TabsAttributeModifier::SetBarModeImpl,
            TabsAttributeModifier::SetBarHeightImpl,
            TabsAttributeModifier::SetBarBackgroundBlurStyle1Impl,
            TabsAttributeModifier::SetCachedMaxCountImpl,
        };
        return &ArkUITabsModifierImpl;
    }

    const GENERATED_ArkUITextModifier* GetTextModifier()
    {
        static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
            TextModifier::ConstructImpl,
            TextInterfaceModifier::SetTextOptionsImpl,
            TextAttributeModifier::SetFontColorImpl,
            TextAttributeModifier::SetFontSizeImpl,
            TextAttributeModifier::SetMinFontSizeImpl,
            TextAttributeModifier::SetMaxFontSizeImpl,
            TextAttributeModifier::SetMinFontScaleImpl,
            TextAttributeModifier::SetMaxFontScaleImpl,
            TextAttributeModifier::SetFontStyleImpl,
            TextAttributeModifier::SetLineSpacingImpl,
            TextAttributeModifier::SetTextAlignImpl,
            TextAttributeModifier::SetLineHeightImpl,
            TextAttributeModifier::SetTextOverflowImpl,
            TextAttributeModifier::SetFontFamilyImpl,
            TextAttributeModifier::SetMaxLinesImpl,
            TextAttributeModifier::SetDecorationImpl,
            TextAttributeModifier::SetLetterSpacingImpl,
            TextAttributeModifier::SetTextCaseImpl,
            TextAttributeModifier::SetBaselineOffsetImpl,
            TextAttributeModifier::SetCopyOptionImpl,
            TextAttributeModifier::SetDraggableImpl,
            TextAttributeModifier::SetTextShadowImpl,
            TextAttributeModifier::SetHeightAdaptivePolicyImpl,
            TextAttributeModifier::SetTextIndentImpl,
            TextAttributeModifier::SetWordBreakImpl,
            TextAttributeModifier::SetLineBreakStrategyImpl,
            TextAttributeModifier::SetOnCopyImpl,
            TextAttributeModifier::SetCaretColorImpl,
            TextAttributeModifier::SetSelectedBackgroundColorImpl,
            TextAttributeModifier::SetEllipsisModeImpl,
            TextAttributeModifier::SetEnableDataDetectorImpl,
            TextAttributeModifier::SetDataDetectorConfigImpl,
            TextAttributeModifier::SetOnTextSelectionChangeImpl,
            TextAttributeModifier::SetFontFeatureImpl,
            TextAttributeModifier::SetMarqueeOptionsImpl,
            TextAttributeModifier::SetOnMarqueeStateChangeImpl,
            TextAttributeModifier::SetPrivacySensitiveImpl,
            TextAttributeModifier::SetTextSelectableImpl,
            TextAttributeModifier::SetEditMenuOptionsImpl,
            TextAttributeModifier::SetHalfLeadingImpl,
            TextAttributeModifier::SetEnableHapticFeedbackImpl,
            TextAttributeModifier::SetFontImpl,
            TextAttributeModifier::SetFontWeightImpl,
            TextAttributeModifier::SetSelectionImpl,
            TextAttributeModifier::SetBindSelectionMenuImpl,
        };
        return &ArkUITextModifierImpl;
    }

    const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
    {
        static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
            TextAreaModifier::ConstructImpl,
            TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
            TextAreaAttributeModifier::SetPlaceholderColorImpl,
            TextAreaAttributeModifier::SetPlaceholderFontImpl,
            TextAreaAttributeModifier::SetEnterKeyTypeImpl,
            TextAreaAttributeModifier::SetTextAlignImpl,
            TextAreaAttributeModifier::SetCaretColorImpl,
            TextAreaAttributeModifier::SetFontColorImpl,
            TextAreaAttributeModifier::SetFontSizeImpl,
            TextAreaAttributeModifier::SetFontStyleImpl,
            TextAreaAttributeModifier::SetFontWeightImpl,
            TextAreaAttributeModifier::SetFontFamilyImpl,
            TextAreaAttributeModifier::SetTextOverflowImpl,
            TextAreaAttributeModifier::SetTextIndentImpl,
            TextAreaAttributeModifier::SetCaretStyleImpl,
            TextAreaAttributeModifier::SetSelectedBackgroundColorImpl,
            TextAreaAttributeModifier::SetOnSubmitImpl,
            TextAreaAttributeModifier::SetOnChangeImpl,
            TextAreaAttributeModifier::SetOnTextSelectionChangeImpl,
            TextAreaAttributeModifier::SetOnContentScrollImpl,
            TextAreaAttributeModifier::SetOnEditChangeImpl,
            TextAreaAttributeModifier::SetOnCopyImpl,
            TextAreaAttributeModifier::SetOnCutImpl,
            TextAreaAttributeModifier::SetOnPasteImpl,
            TextAreaAttributeModifier::SetCopyOptionImpl,
            TextAreaAttributeModifier::SetEnableKeyboardOnFocusImpl,
            TextAreaAttributeModifier::SetMaxLengthImpl,
            TextAreaAttributeModifier::SetStyleImpl,
            TextAreaAttributeModifier::SetBarStateImpl,
            TextAreaAttributeModifier::SetSelectionMenuHiddenImpl,
            TextAreaAttributeModifier::SetMinFontSizeImpl,
            TextAreaAttributeModifier::SetMaxFontSizeImpl,
            TextAreaAttributeModifier::SetMinFontScaleImpl,
            TextAreaAttributeModifier::SetMaxFontScaleImpl,
            TextAreaAttributeModifier::SetHeightAdaptivePolicyImpl,
            TextAreaAttributeModifier::SetMaxLinesImpl,
            TextAreaAttributeModifier::SetWordBreakImpl,
            TextAreaAttributeModifier::SetLineBreakStrategyImpl,
            TextAreaAttributeModifier::SetDecorationImpl,
            TextAreaAttributeModifier::SetLetterSpacingImpl,
            TextAreaAttributeModifier::SetLineSpacingImpl,
            TextAreaAttributeModifier::SetLineHeightImpl,
            TextAreaAttributeModifier::SetTypeImpl,
            TextAreaAttributeModifier::SetEnableAutoFillImpl,
            TextAreaAttributeModifier::SetContentTypeImpl,
            TextAreaAttributeModifier::SetFontFeatureImpl,
            TextAreaAttributeModifier::SetOnWillInsertImpl,
            TextAreaAttributeModifier::SetOnDidInsertImpl,
            TextAreaAttributeModifier::SetOnWillDeleteImpl,
            TextAreaAttributeModifier::SetOnDidDeleteImpl,
            TextAreaAttributeModifier::SetEditMenuOptionsImpl,
            TextAreaAttributeModifier::SetEnablePreviewTextImpl,
            TextAreaAttributeModifier::SetEnableHapticFeedbackImpl,
            TextAreaAttributeModifier::SetAutoCapitalizationModeImpl,
            TextAreaAttributeModifier::SetHalfLeadingImpl,
            TextAreaAttributeModifier::SetEllipsisModeImpl,
            TextAreaAttributeModifier::SetStopBackPressImpl,
            TextAreaAttributeModifier::SetOnWillChangeImpl,
            TextAreaAttributeModifier::SetKeyboardAppearanceImpl,
            TextAreaAttributeModifier::SetInputFilterImpl,
            TextAreaAttributeModifier::SetShowCounterImpl,
            TextAreaAttributeModifier::SetCustomKeyboardImpl,
        };
        return &ArkUITextAreaModifierImpl;
    }

    const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
    {
        static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
            TextClockModifier::ConstructImpl,
            TextClockInterfaceModifier::SetTextClockOptionsImpl,
            TextClockAttributeModifier::SetFormatImpl,
            TextClockAttributeModifier::SetOnDateChangeImpl,
            TextClockAttributeModifier::SetFontColorImpl,
            TextClockAttributeModifier::SetFontSizeImpl,
            TextClockAttributeModifier::SetFontStyleImpl,
            TextClockAttributeModifier::SetFontWeightImpl,
            TextClockAttributeModifier::SetFontFamilyImpl,
            TextClockAttributeModifier::SetTextShadowImpl,
            TextClockAttributeModifier::SetFontFeatureImpl,
            TextClockAttributeModifier::SetDateTimeOptionsImpl,
        };
        return &ArkUITextClockModifierImpl;
    }

    const GENERATED_ArkUITextInputModifier* GetTextInputModifier()
    {
        static const GENERATED_ArkUITextInputModifier ArkUITextInputModifierImpl {
            TextInputModifier::ConstructImpl,
            TextInputInterfaceModifier::SetTextInputOptionsImpl,
            TextInputAttributeModifier::SetTypeImpl,
            TextInputAttributeModifier::SetContentTypeImpl,
            TextInputAttributeModifier::SetPlaceholderColorImpl,
            TextInputAttributeModifier::SetTextOverflowImpl,
            TextInputAttributeModifier::SetTextIndentImpl,
            TextInputAttributeModifier::SetPlaceholderFontImpl,
            TextInputAttributeModifier::SetEnterKeyTypeImpl,
            TextInputAttributeModifier::SetCaretColorImpl,
            TextInputAttributeModifier::SetOnEditChangeImpl,
            TextInputAttributeModifier::SetOnSubmitImpl,
            TextInputAttributeModifier::SetOnChangeImpl,
            TextInputAttributeModifier::SetOnTextSelectionChangeImpl,
            TextInputAttributeModifier::SetOnContentScrollImpl,
            TextInputAttributeModifier::SetMaxLengthImpl,
            TextInputAttributeModifier::SetFontColorImpl,
            TextInputAttributeModifier::SetFontSizeImpl,
            TextInputAttributeModifier::SetFontStyleImpl,
            TextInputAttributeModifier::SetFontWeightImpl,
            TextInputAttributeModifier::SetFontFamilyImpl,
            TextInputAttributeModifier::SetOnCopyImpl,
            TextInputAttributeModifier::SetOnCutImpl,
            TextInputAttributeModifier::SetOnPasteImpl,
            TextInputAttributeModifier::SetCopyOptionImpl,
            TextInputAttributeModifier::SetShowPasswordIconImpl,
            TextInputAttributeModifier::SetTextAlignImpl,
            TextInputAttributeModifier::SetStyleImpl,
            TextInputAttributeModifier::SetCaretStyleImpl,
            TextInputAttributeModifier::SetSelectedBackgroundColorImpl,
            TextInputAttributeModifier::SetCaretPositionImpl,
            TextInputAttributeModifier::SetEnableKeyboardOnFocusImpl,
            TextInputAttributeModifier::SetPasswordIconImpl,
            TextInputAttributeModifier::SetShowErrorImpl,
            TextInputAttributeModifier::SetShowUnitImpl,
            TextInputAttributeModifier::SetShowUnderlineImpl,
            TextInputAttributeModifier::SetUnderlineColorImpl,
            TextInputAttributeModifier::SetSelectionMenuHiddenImpl,
            TextInputAttributeModifier::SetBarStateImpl,
            TextInputAttributeModifier::SetMaxLinesImpl,
            TextInputAttributeModifier::SetWordBreakImpl,
            TextInputAttributeModifier::SetLineBreakStrategyImpl,
            TextInputAttributeModifier::SetCancelButton0Impl,
            TextInputAttributeModifier::SetCancelButton1Impl,
            TextInputAttributeModifier::SetSelectAllImpl,
            TextInputAttributeModifier::SetMinFontSizeImpl,
            TextInputAttributeModifier::SetMaxFontSizeImpl,
            TextInputAttributeModifier::SetMinFontScaleImpl,
            TextInputAttributeModifier::SetMaxFontScaleImpl,
            TextInputAttributeModifier::SetHeightAdaptivePolicyImpl,
            TextInputAttributeModifier::SetEnableAutoFillImpl,
            TextInputAttributeModifier::SetDecorationImpl,
            TextInputAttributeModifier::SetLetterSpacingImpl,
            TextInputAttributeModifier::SetLineHeightImpl,
            TextInputAttributeModifier::SetPasswordRulesImpl,
            TextInputAttributeModifier::SetFontFeatureImpl,
            TextInputAttributeModifier::SetShowPasswordImpl,
            TextInputAttributeModifier::SetOnSecurityStateChangeImpl,
            TextInputAttributeModifier::SetOnWillInsertImpl,
            TextInputAttributeModifier::SetOnDidInsertImpl,
            TextInputAttributeModifier::SetOnWillDeleteImpl,
            TextInputAttributeModifier::SetOnDidDeleteImpl,
            TextInputAttributeModifier::SetEditMenuOptionsImpl,
            TextInputAttributeModifier::SetEnablePreviewTextImpl,
            TextInputAttributeModifier::SetEnableHapticFeedbackImpl,
            TextInputAttributeModifier::SetAutoCapitalizationModeImpl,
            TextInputAttributeModifier::SetHalfLeadingImpl,
            TextInputAttributeModifier::SetEllipsisModeImpl,
            TextInputAttributeModifier::SetStopBackPressImpl,
            TextInputAttributeModifier::SetOnWillChangeImpl,
            TextInputAttributeModifier::SetKeyboardAppearanceImpl,
            TextInputAttributeModifier::SetInputFilterImpl,
            TextInputAttributeModifier::SetCustomKeyboardImpl,
            TextInputAttributeModifier::SetShowCounterImpl,
        };
        return &ArkUITextInputModifierImpl;
    }

    const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
    {
        static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
            TextPickerModifier::ConstructImpl,
            TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
            TextPickerAttributeModifier::SetDefaultPickerItemHeightImpl,
            TextPickerAttributeModifier::SetCanLoopImpl,
            TextPickerAttributeModifier::SetDisappearTextStyleImpl,
            TextPickerAttributeModifier::SetTextStyleImpl,
            TextPickerAttributeModifier::SetSelectedTextStyleImpl,
            TextPickerAttributeModifier::SetDisableTextStyleAnimationImpl,
            TextPickerAttributeModifier::SetDefaultTextStyleImpl,
            TextPickerAttributeModifier::SetOnChangeImpl,
            TextPickerAttributeModifier::SetOnScrollStopImpl,
            TextPickerAttributeModifier::SetOnEnterSelectedAreaImpl,
            TextPickerAttributeModifier::SetSelectedIndexImpl,
            TextPickerAttributeModifier::SetDividerImpl,
            TextPickerAttributeModifier::SetGradientHeightImpl,
            TextPickerAttributeModifier::SetEnableHapticFeedbackImpl,
            TextPickerAttributeModifier::SetDigitalCrownSensitivityImpl,
        };
        return &ArkUITextPickerModifierImpl;
    }

    const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier()
    {
        static const GENERATED_ArkUITextTimerModifier ArkUITextTimerModifierImpl {
            TextTimerModifier::ConstructImpl,
            TextTimerInterfaceModifier::SetTextTimerOptionsImpl,
            TextTimerAttributeModifier::SetFormatImpl,
            TextTimerAttributeModifier::SetFontColorImpl,
            TextTimerAttributeModifier::SetFontSizeImpl,
            TextTimerAttributeModifier::SetFontStyleImpl,
            TextTimerAttributeModifier::SetFontWeightImpl,
            TextTimerAttributeModifier::SetFontFamilyImpl,
            TextTimerAttributeModifier::SetOnTimerImpl,
            TextTimerAttributeModifier::SetTextShadowImpl,
        };
        return &ArkUITextTimerModifierImpl;
    }

    const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
    {
        static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
            TimePickerModifier::ConstructImpl,
            TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
            TimePickerAttributeModifier::SetUseMilitaryTimeImpl,
            TimePickerAttributeModifier::SetLoopImpl,
            TimePickerAttributeModifier::SetDisappearTextStyleImpl,
            TimePickerAttributeModifier::SetTextStyleImpl,
            TimePickerAttributeModifier::SetSelectedTextStyleImpl,
            TimePickerAttributeModifier::SetDateTimeOptionsImpl,
            TimePickerAttributeModifier::SetOnChangeImpl,
            TimePickerAttributeModifier::SetOnEnterSelectedAreaImpl,
            TimePickerAttributeModifier::SetEnableHapticFeedbackImpl,
            TimePickerAttributeModifier::SetDigitalCrownSensitivityImpl,
            TimePickerAttributeModifier::SetEnableCascadeImpl,
        };
        return &ArkUITimePickerModifierImpl;
    }

    const GENERATED_ArkUIToggleModifier* GetToggleModifier()
    {
        static const GENERATED_ArkUIToggleModifier ArkUIToggleModifierImpl {
            ToggleModifier::ConstructImpl,
            ToggleInterfaceModifier::SetToggleOptionsImpl,
            ToggleAttributeModifier::SetOnChangeImpl,
            ToggleAttributeModifier::SetSelectedColorImpl,
            ToggleAttributeModifier::SetSwitchPointColorImpl,
            ToggleAttributeModifier::SetSwitchStyleImpl,
        };
        return &ArkUIToggleModifierImpl;
    }

    const GENERATED_ArkUIToolBarItemModifier* GetToolBarItemModifier()
    {
        static const GENERATED_ArkUIToolBarItemModifier ArkUIToolBarItemModifierImpl {
            ToolBarItemModifier::ConstructImpl,
            ToolBarItemInterfaceModifier::SetToolBarItemOptionsImpl,
        };
        return &ArkUIToolBarItemModifierImpl;
    }

    const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
    {
        static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
            UIExtensionComponentModifier::ConstructImpl,
            UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
            UIExtensionComponentAttributeModifier::SetOnRemoteReadyImpl,
            UIExtensionComponentAttributeModifier::SetOnReceiveImpl,
            UIExtensionComponentAttributeModifier::SetOnErrorImpl,
            UIExtensionComponentAttributeModifier::SetOnTerminatedImpl,
            UIExtensionComponentAttributeModifier::SetOnDrawReadyImpl,
        };
        return &ArkUIUIExtensionComponentModifierImpl;
    }

    const GENERATED_ArkUIVideoModifier* GetVideoModifier()
    {
        static const GENERATED_ArkUIVideoModifier ArkUIVideoModifierImpl {
            VideoModifier::ConstructImpl,
            VideoInterfaceModifier::SetVideoOptionsImpl,
            VideoAttributeModifier::SetMutedImpl,
            VideoAttributeModifier::SetAutoPlayImpl,
            VideoAttributeModifier::SetControlsImpl,
            VideoAttributeModifier::SetLoopImpl,
            VideoAttributeModifier::SetObjectFitImpl,
            VideoAttributeModifier::SetOnStartImpl,
            VideoAttributeModifier::SetOnPauseImpl,
            VideoAttributeModifier::SetOnFinishImpl,
            VideoAttributeModifier::SetOnFullscreenChangeImpl,
            VideoAttributeModifier::SetOnPreparedImpl,
            VideoAttributeModifier::SetOnSeekingImpl,
            VideoAttributeModifier::SetOnSeekedImpl,
            VideoAttributeModifier::SetOnUpdateImpl,
            VideoAttributeModifier::SetOnErrorImpl,
            VideoAttributeModifier::SetOnStopImpl,
            VideoAttributeModifier::SetEnableAnalyzerImpl,
            VideoAttributeModifier::SetAnalyzerConfigImpl,
            VideoAttributeModifier::SetEnableShortcutKeyImpl,
        };
        return &ArkUIVideoModifierImpl;
    }

    const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
    {
        static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
            WaterFlowModifier::ConstructImpl,
            WaterFlowInterfaceModifier::SetWaterFlowOptionsImpl,
            WaterFlowAttributeModifier::SetColumnsTemplateImpl,
            WaterFlowAttributeModifier::SetItemConstraintSizeImpl,
            WaterFlowAttributeModifier::SetRowsTemplateImpl,
            WaterFlowAttributeModifier::SetColumnsGapImpl,
            WaterFlowAttributeModifier::SetRowsGapImpl,
            WaterFlowAttributeModifier::SetLayoutDirectionImpl,
            WaterFlowAttributeModifier::SetCachedCount0Impl,
            WaterFlowAttributeModifier::SetOnScrollFrameBeginImpl,
            WaterFlowAttributeModifier::SetOnScrollIndexImpl,
            WaterFlowAttributeModifier::SetOnWillScrollImpl,
            WaterFlowAttributeModifier::SetOnDidScrollImpl,
            WaterFlowAttributeModifier::SetCachedCount1Impl,
        };
        return &ArkUIWaterFlowModifierImpl;
    }

    const GENERATED_ArkUIWebModifier* GetWebModifier()
    {
        static const GENERATED_ArkUIWebModifier ArkUIWebModifierImpl {
            WebModifier::ConstructImpl,
            WebInterfaceModifier::SetWebOptionsImpl,
            WebAttributeModifier::SetJavaScriptAccessImpl,
            WebAttributeModifier::SetFileAccessImpl,
            WebAttributeModifier::SetOnlineImageAccessImpl,
            WebAttributeModifier::SetDomStorageAccessImpl,
            WebAttributeModifier::SetImageAccessImpl,
            WebAttributeModifier::SetMixedModeImpl,
            WebAttributeModifier::SetZoomAccessImpl,
            WebAttributeModifier::SetRotateRenderEffectImpl,
            WebAttributeModifier::SetGeolocationAccessImpl,
            WebAttributeModifier::SetJavaScriptProxyImpl,
            WebAttributeModifier::SetCacheModeImpl,
            WebAttributeModifier::SetDarkModeImpl,
            WebAttributeModifier::SetForceDarkAccessImpl,
            WebAttributeModifier::SetMediaOptionsImpl,
            WebAttributeModifier::SetOverviewModeAccessImpl,
            WebAttributeModifier::SetOverScrollModeImpl,
            WebAttributeModifier::SetBlurOnKeyboardHideModeImpl,
            WebAttributeModifier::SetTextZoomRatioImpl,
            WebAttributeModifier::SetDatabaseAccessImpl,
            WebAttributeModifier::SetInitialScaleImpl,
            WebAttributeModifier::SetMetaViewportImpl,
            WebAttributeModifier::SetOnPageEndImpl,
            WebAttributeModifier::SetOnPageBeginImpl,
            WebAttributeModifier::SetOnLoadStartedImpl,
            WebAttributeModifier::SetOnLoadFinishedImpl,
            WebAttributeModifier::SetOnProgressChangeImpl,
            WebAttributeModifier::SetOnTitleReceiveImpl,
            WebAttributeModifier::SetOnGeolocationHideImpl,
            WebAttributeModifier::SetOnGeolocationShowImpl,
            WebAttributeModifier::SetOnRequestSelectedImpl,
            WebAttributeModifier::SetOnAlertImpl,
            WebAttributeModifier::SetOnBeforeUnloadImpl,
            WebAttributeModifier::SetOnConfirmImpl,
            WebAttributeModifier::SetOnPromptImpl,
            WebAttributeModifier::SetOnConsoleImpl,
            WebAttributeModifier::SetOnErrorReceiveImpl,
            WebAttributeModifier::SetOnHttpErrorReceiveImpl,
            WebAttributeModifier::SetOnOverrideErrorPageImpl,
            WebAttributeModifier::SetOnDownloadStartImpl,
            WebAttributeModifier::SetOnRefreshAccessedHistoryImpl,
            WebAttributeModifier::SetOnRenderExitedImpl,
            WebAttributeModifier::SetOnShowFileSelectorImpl,
            WebAttributeModifier::SetOnResourceLoadImpl,
            WebAttributeModifier::SetOnFullScreenExitImpl,
            WebAttributeModifier::SetOnFullScreenEnterImpl,
            WebAttributeModifier::SetOnScaleChangeImpl,
            WebAttributeModifier::SetOnHttpAuthRequestImpl,
            WebAttributeModifier::SetOnInterceptRequestImpl,
            WebAttributeModifier::SetOnPermissionRequestImpl,
            WebAttributeModifier::SetOnScreenCaptureRequestImpl,
            WebAttributeModifier::SetOnContextMenuShowImpl,
            WebAttributeModifier::SetOnContextMenuHideImpl,
            WebAttributeModifier::SetMediaPlayGestureAccessImpl,
            WebAttributeModifier::SetOnSearchResultReceiveImpl,
            WebAttributeModifier::SetOnScrollImpl,
            WebAttributeModifier::SetOnSslErrorEventReceiveImpl,
            WebAttributeModifier::SetOnSslErrorEventImpl,
            WebAttributeModifier::SetOnClientAuthenticationRequestImpl,
            WebAttributeModifier::SetOnWindowNewImpl,
            WebAttributeModifier::SetOnWindowExitImpl,
            WebAttributeModifier::SetMultiWindowAccessImpl,
            WebAttributeModifier::SetOnInterceptKeyEventImpl,
            WebAttributeModifier::SetWebStandardFontImpl,
            WebAttributeModifier::SetWebSerifFontImpl,
            WebAttributeModifier::SetWebSansSerifFontImpl,
            WebAttributeModifier::SetWebFixedFontImpl,
            WebAttributeModifier::SetWebFantasyFontImpl,
            WebAttributeModifier::SetWebCursiveFontImpl,
            WebAttributeModifier::SetDefaultFixedFontSizeImpl,
            WebAttributeModifier::SetDefaultFontSizeImpl,
            WebAttributeModifier::SetMinFontSizeImpl,
            WebAttributeModifier::SetMinLogicalFontSizeImpl,
            WebAttributeModifier::SetDefaultTextEncodingFormatImpl,
            WebAttributeModifier::SetForceDisplayScrollBarImpl,
            WebAttributeModifier::SetBlockNetworkImpl,
            WebAttributeModifier::SetHorizontalScrollBarAccessImpl,
            WebAttributeModifier::SetVerticalScrollBarAccessImpl,
            WebAttributeModifier::SetOnTouchIconUrlReceivedImpl,
            WebAttributeModifier::SetOnFaviconReceivedImpl,
            WebAttributeModifier::SetOnPageVisibleImpl,
            WebAttributeModifier::SetOnDataResubmittedImpl,
            WebAttributeModifier::SetPinchSmoothImpl,
            WebAttributeModifier::SetAllowWindowOpenMethodImpl,
            WebAttributeModifier::SetOnAudioStateChangedImpl,
            WebAttributeModifier::SetOnFirstContentfulPaintImpl,
            WebAttributeModifier::SetOnFirstMeaningfulPaintImpl,
            WebAttributeModifier::SetOnLargestContentfulPaintImpl,
            WebAttributeModifier::SetOnLoadInterceptImpl,
            WebAttributeModifier::SetOnControllerAttachedImpl,
            WebAttributeModifier::SetOnOverScrollImpl,
            WebAttributeModifier::SetOnPdfScrollAtBottomImpl,
            WebAttributeModifier::SetOnPdfLoadEventImpl,
            WebAttributeModifier::SetOnSafeBrowsingCheckResultImpl,
            WebAttributeModifier::SetOnSafeBrowsingCheckFinishImpl,
            WebAttributeModifier::SetOnNavigationEntryCommittedImpl,
            WebAttributeModifier::SetOnIntelligentTrackingPreventionResultImpl,
            WebAttributeModifier::SetJavaScriptOnDocumentStartImpl,
            WebAttributeModifier::SetJavaScriptOnDocumentEndImpl,
            WebAttributeModifier::SetLayoutModeImpl,
            WebAttributeModifier::SetNestedScrollImpl,
            WebAttributeModifier::SetEnableNativeEmbedModeImpl,
            WebAttributeModifier::SetOnNativeEmbedLifecycleChangeImpl,
            WebAttributeModifier::SetOnNativeEmbedVisibilityChangeImpl,
            WebAttributeModifier::SetOnNativeEmbedGestureEventImpl,
            WebAttributeModifier::SetOnNativeEmbedMouseEventImpl,
            WebAttributeModifier::SetOnNativeEmbedObjectParamChangeImpl,
            WebAttributeModifier::SetCopyOptionsImpl,
            WebAttributeModifier::SetOnOverrideUrlLoadingImpl,
            WebAttributeModifier::SetTextAutosizingImpl,
            WebAttributeModifier::SetEnableNativeMediaPlayerImpl,
            WebAttributeModifier::SetOnRenderProcessNotRespondingImpl,
            WebAttributeModifier::SetOnRenderProcessRespondingImpl,
            WebAttributeModifier::SetOnViewportFitChangedImpl,
            WebAttributeModifier::SetOnInterceptKeyboardAttachImpl,
            WebAttributeModifier::SetOnAdsBlockedImpl,
            WebAttributeModifier::SetKeyboardAvoidModeImpl,
            WebAttributeModifier::SetEditMenuOptionsImpl,
            WebAttributeModifier::SetEnableHapticFeedbackImpl,
            WebAttributeModifier::SetOptimizeParserBudgetImpl,
            WebAttributeModifier::SetEnableFollowSystemFontWeightImpl,
            WebAttributeModifier::SetEnableWebAVSessionImpl,
            WebAttributeModifier::SetRunJavaScriptOnDocumentStartImpl,
            WebAttributeModifier::SetRunJavaScriptOnDocumentEndImpl,
            WebAttributeModifier::SetRunJavaScriptOnHeadEndImpl,
            WebAttributeModifier::SetNativeEmbedOptionsImpl,
            WebAttributeModifier::SetEnableDataDetectorImpl,
            WebAttributeModifier::SetDataDetectorConfigImpl,
            WebAttributeModifier::SetOnActivateContentImpl,
            WebAttributeModifier::SetBypassVsyncConditionImpl,
            WebAttributeModifier::SetGestureFocusModeImpl,
            WebAttributeModifier::SetForceEnableZoomImpl,
            WebAttributeModifier::SetBackToTopImpl,
            WebAttributeModifier::SetOnDetectedBlankScreenImpl,
            WebAttributeModifier::SetBlankScreenDetectionConfigImpl,
            WebAttributeModifier::SetZoomControlAccessImpl,
            WebAttributeModifier::SetEnableSelectedDataDetectorImpl,
            WebAttributeModifier::SetEnableImageAnalyzerImpl,
            WebAttributeModifier::SetRegisterNativeEmbedRuleImpl,
            WebAttributeModifier::SetBindSelectionMenuImpl,
        };
        return &ArkUIWebModifierImpl;
    }

    const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier()
    {
        static const GENERATED_ArkUIWindowSceneModifier ArkUIWindowSceneModifierImpl {
            WindowSceneModifier::ConstructImpl,
            WindowSceneInterfaceModifier::SetWindowSceneOptionsImpl,
            WindowSceneAttributeModifier::SetAttractionEffectImpl,
        };
        return &ArkUIWindowSceneModifierImpl;
    }

    const GENERATED_ArkUIWithThemeModifier* GetWithThemeModifier()
    {
        static const GENERATED_ArkUIWithThemeModifier ArkUIWithThemeModifierImpl {
            WithThemeModifier::ConstructImpl,
            WithThemeInterfaceModifier::SetWithThemeOptionsImpl,
        };
        return &ArkUIWithThemeModifierImpl;
    }

    const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
    {
        static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
            XComponentModifier::ConstructImpl,
            XComponentInterfaceModifier::SetXComponentOptionsImpl,
            XComponentAttributeModifier::SetOnLoadImpl,
            XComponentAttributeModifier::SetOnDestroyImpl,
            XComponentAttributeModifier::SetEnableAnalyzerImpl,
            XComponentAttributeModifier::SetEnableSecureImpl,
            XComponentAttributeModifier::SetHdrBrightnessImpl,
        };
        return &ArkUIXComponentModifierImpl;
    }

    const GENERATED_ArkUINodeModifiers* GENERATED_GetArkUINodeModifiers()
    {
        static const GENERATED_ArkUINodeModifiers modifiersImpl = {
            GetAlphabetIndexerModifier,
            GetAnimatorModifier,
            GetBadgeModifier,
            GetBaseSpanModifier,
            GetBlankModifier,
            GetButtonModifier,
            GetCalendarPickerModifier,
            GetCanvasModifier,
            GetCheckboxModifier,
            GetCheckboxGroupModifier,
            GetCircleModifier,
            GetColumnModifier,
            GetColumnSplitModifier,
            GetCommonMethodModifier,
            GetCommonShapeMethodModifier,
            GetComponent3DModifier,
            GetComponentRootModifier,
            GetContainerSpanModifier,
            GetCounterModifier,
            GetCustomBuilderRootModifier,
            GetCustomLayoutRootModifier,
            GetDataPanelModifier,
            GetDatePickerModifier,
            GetDividerModifier,
            GetEffectComponentModifier,
            GetEllipseModifier,
            GetEmbeddedComponentModifier,
            GetFlexModifier,
            GetFlowItemModifier,
            GetFolderStackModifier,
            GetFormComponentModifier,
            GetFormLinkModifier,
            GetGaugeModifier,
            GetGridModifier,
            GetGridColModifier,
            GetGridItemModifier,
            GetGridRowModifier,
            GetHyperlinkModifier,
            GetImageModifier,
            GetImageAnimatorModifier,
            GetImageSpanModifier,
            GetIndicatorComponentModifier,
            GetLazyGridLayoutAttributeModifier,
            GetLazyVGridLayoutModifier,
            GetLineModifier,
            GetLinearIndicatorModifier,
            GetListModifier,
            GetListItemModifier,
            GetListItemGroupModifier,
            GetLoadingProgressModifier,
            GetMarqueeModifier,
            GetMediaCachedImageModifier,
            GetMenuModifier,
            GetMenuItemModifier,
            GetMenuItemGroupModifier,
            GetNavDestinationModifier,
            GetNavigationModifier,
            GetNodeContainerModifier,
            GetPasteButtonModifier,
            GetPathModifier,
            GetPatternLockModifier,
            GetPluginComponentModifier,
            GetPolygonModifier,
            GetPolylineModifier,
            GetProgressModifier,
            GetQRCodeModifier,
            GetRadioModifier,
            GetRatingModifier,
            GetRectModifier,
            GetRefreshModifier,
            GetRelativeContainerModifier,
            GetRemoteWindowModifier,
            GetRichEditorModifier,
            GetRichTextModifier,
            GetRootModifier,
            GetRootSceneModifier,
            GetRowModifier,
            GetRowSplitModifier,
            GetSaveButtonModifier,
            GetScreenModifier,
            GetScrollModifier,
            GetScrollableCommonMethodModifier,
            GetScrollBarModifier,
            GetSearchModifier,
            GetSecurityComponentMethodModifier,
            GetSelectModifier,
            GetShapeModifier,
            GetSideBarContainerModifier,
            GetSliderModifier,
            GetSpanModifier,
            GetStackModifier,
            GetStepperModifier,
            GetStepperItemModifier,
            GetSwiperModifier,
            GetSymbolGlyphModifier,
            GetSymbolSpanModifier,
            GetTabContentModifier,
            GetTabsModifier,
            GetTextModifier,
            GetTextAreaModifier,
            GetTextClockModifier,
            GetTextInputModifier,
            GetTextPickerModifier,
            GetTextTimerModifier,
            GetTimePickerModifier,
            GetToggleModifier,
            GetToolBarItemModifier,
            GetUIExtensionComponentModifier,
            GetVideoModifier,
            GetWaterFlowModifier,
            GetWebModifier,
            GetWindowSceneModifier,
            GetWithThemeModifier,
            GetXComponentModifier,
        };
        return &modifiersImpl;
    }
    namespace AccessibilityHoverEventAccessor {
    void DestroyPeerImpl(Ark_AccessibilityHoverEvent peer)
    {
        auto peerImpl = reinterpret_cast<AccessibilityHoverEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AccessibilityHoverEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_AccessibilityHoverType GetTypeImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetTypeImpl(Ark_AccessibilityHoverEvent peer,
                     Ark_AccessibilityHoverType type)
    {
    }
    Ark_Float64 GetXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_AccessibilityHoverEvent peer,
                  Ark_Float64 x)
    {
    }
    Ark_Float64 GetYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_AccessibilityHoverEvent peer,
                  Ark_Float64 y)
    {
    }
    Ark_Float64 GetDisplayXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_AccessibilityHoverEvent peer,
                         Ark_Float64 displayX)
    {
    }
    Ark_Float64 GetDisplayYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_AccessibilityHoverEvent peer,
                         Ark_Float64 displayY)
    {
    }
    Ark_Float64 GetWindowXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_AccessibilityHoverEvent peer,
                        Ark_Float64 windowX)
    {
    }
    Ark_Float64 GetWindowYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_AccessibilityHoverEvent peer,
                        Ark_Float64 windowY)
    {
    }
    } // AccessibilityHoverEventAccessor
    namespace ActionSheetAccessor {
    void ShowImpl(const Ark_ActionSheetOptions* options)
    {
    }
    } // ActionSheetAccessor
    namespace AlertDialogAccessor {
    void ShowImpl(const Ark_Union_AlertDialogParamWithConfirm_AlertDialogParamWithButtons_AlertDialogParamWithOptions* options)
    {
    }
    } // AlertDialogAccessor
    namespace AnimationExtenderAccessor {
    void SetClipRectImpl(Ark_NativePointer node,
                         Ark_Float32 x,
                         Ark_Float32 y,
                         Ark_Float32 width,
                         Ark_Float32 height)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OpenImplicitAnimationImpl(const Ark_AnimateParam* param)
    {
    }
    void CloseImplicitAnimationImpl()
    {
    }
    void StartDoubleAnimationImpl(Ark_NativePointer node,
                                  const Ark_DoubleAnimationParam* param)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void AnimationTranslateImpl(Ark_NativePointer node,
                                const Ark_TranslateOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void AnimateToImmediatelyImplImpl(const Ark_AnimateParam* param,
                                      const Callback_Void* event,
                                      Ark_Boolean immediately)
    {
    }
    void KeyframeAnimationImplImpl(const Ark_KeyframeAnimateParam* param,
                                   const Array_KeyframeState* keyfames)
    {
    }
    } // AnimationExtenderAccessor
    namespace AppearSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_AppearSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<AppearSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AppearSymbolEffect ConstructImpl(const Opt_EffectScope* scope)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectScope GetScopeImpl(Ark_AppearSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_AppearSymbolEffect peer,
                      const Opt_EffectScope* scope)
    {
    }
    } // AppearSymbolEffectAccessor
    namespace ArcListExtenderAccessor {
    Ark_NativePointer ConstructorImpl()
    {
        return {};
    }
    void SetArkListOptionsImpl(Ark_NativePointer node,
                               const Opt_ArkListOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* sensitivity)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SpaceImpl(Ark_NativePointer node,
                   const Opt_LengthMetrics* space)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       const Opt_BarState* status)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Opt_ColorMetrics* color)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Opt_LengthMetrics* width)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void CachedCountImpl(Ark_NativePointer node,
                         const Opt_Int32* count)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ChainAnimationImpl(Ark_NativePointer node,
                            const Opt_Boolean* enable)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ChildrenMainSizeImpl(Ark_NativePointer node,
                              const Opt_ChildrenMainSize* size)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     const Opt_Boolean* enable)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void FadingEdgeImpl(Ark_NativePointer node,
                        const Opt_Boolean* enable)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Opt_Float64* friction)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void FlingSpeedLimitImpl(Ark_NativePointer node,
                             const Opt_Float64* speed)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Opt_ArcScrollIndexHandler* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnReachStartImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_OnWillScrollCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const Opt_OnScrollCallback* handler)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // ArcListExtenderAccessor
    namespace ArcListItemExtenderAccessor {
    Ark_NativePointer ConstructorImpl()
    {
        return {};
    }
    void AutoScaleImpl(Ark_NativePointer node,
                       const Opt_Boolean* enable)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SwipeActionImpl(Ark_NativePointer node,
                         const Opt_SwipeActionOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // ArcListItemExtenderAccessor
    namespace ArcScrollBarExtenderAccessor {
    Ark_NativePointer ConstructorImpl()
    {
        return {};
    }
    void SetArcScrollBarOptionsImpl(Ark_NativePointer node,
                                    const Ark_ArcScrollBarOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // ArcScrollBarExtenderAccessor
    namespace AxisEventAccessor {
    void DestroyPeerImpl(Ark_AxisEvent peer)
    {
        auto peerImpl = reinterpret_cast<AxisEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AxisEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetHorizontalAxisValueImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    Ark_Float64 GetVerticalAxisValueImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    Ark_Boolean HasAxisImpl(Ark_AxisEvent peer,
                            Ark_AxisType axisType)
    {
        return {};
    }
    Ark_AxisAction GetActionImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetActionImpl(Ark_AxisEvent peer,
                       Ark_AxisAction action)
    {
    }
    Ark_Float64 GetDisplayXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_AxisEvent peer,
                         Ark_Float64 displayX)
    {
    }
    Ark_Float64 GetDisplayYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_AxisEvent peer,
                         Ark_Float64 displayY)
    {
    }
    Ark_Float64 GetWindowXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_AxisEvent peer,
                        Ark_Float64 windowX)
    {
    }
    Ark_Float64 GetWindowYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_AxisEvent peer,
                        Ark_Float64 windowY)
    {
    }
    Ark_Float64 GetXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_AxisEvent peer,
                  Ark_Float64 x)
    {
    }
    Ark_Float64 GetYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_AxisEvent peer,
                  Ark_Float64 y)
    {
    }
    Opt_Int32 GetScrollStepImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetScrollStepImpl(Ark_AxisEvent peer,
                           const Opt_Int32* scrollStep)
    {
    }
    void PropagationImpl(Ark_AxisEvent peer)
    {
    }
    } // AxisEventAccessor
    namespace BackgroundColorStyleAccessor {
    void DestroyPeerImpl(Ark_BackgroundColorStyle peer)
    {
        auto peerImpl = reinterpret_cast<BackgroundColorStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BackgroundColorStyle ConstructImpl(const Ark_TextBackgroundStyle* textBackgroundStyle)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TextBackgroundStyle GetTextBackgroundStyleImpl(Ark_BackgroundColorStyle peer)
    {
        return {};
    }
    } // BackgroundColorStyleAccessor
    namespace BaseEventAccessor {
    void DestroyPeerImpl(Ark_BaseEvent peer)
    {
        auto peerImpl = reinterpret_cast<BaseEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EventTarget GetTargetImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTargetImpl(Ark_BaseEvent peer,
                       const Ark_EventTarget* target)
    {
    }
    Ark_Int64 GetTimestampImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTimestampImpl(Ark_BaseEvent peer,
                          Ark_Int64 timestamp)
    {
    }
    Ark_SourceType GetSourceImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetSourceImpl(Ark_BaseEvent peer,
                       Ark_SourceType source)
    {
    }
    Opt_Float64 GetAxisHorizontalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                               const Opt_Float64* axisHorizontal)
    {
    }
    Opt_Float64 GetAxisVerticalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisVerticalImpl(Ark_BaseEvent peer,
                             const Opt_Float64* axisVertical)
    {
    }
    Ark_Float64 GetPressureImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetPressureImpl(Ark_BaseEvent peer,
                         Ark_Float64 pressure)
    {
    }
    Ark_Float64 GetTiltXImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTiltXImpl(Ark_BaseEvent peer,
                      Ark_Float64 tiltX)
    {
    }
    Ark_Float64 GetTiltYImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTiltYImpl(Ark_BaseEvent peer,
                      Ark_Float64 tiltY)
    {
    }
    Opt_Float64 GetRollAngleImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetRollAngleImpl(Ark_BaseEvent peer,
                          const Opt_Float64* rollAngle)
    {
    }
    Ark_SourceTool GetSourceToolImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetSourceToolImpl(Ark_BaseEvent peer,
                           Ark_SourceTool sourceTool)
    {
    }
    Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetGetModifierKeyStateImpl(Ark_BaseEvent peer,
                                    const Opt_ModifierKeyStateGetter* getModifierKeyState)
    {
    }
    Opt_Int32 GetDeviceIdImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetDeviceIdImpl(Ark_BaseEvent peer,
                         const Opt_Int32* deviceId)
    {
    }
    Opt_Int32 GetTargetDisplayIdImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTargetDisplayIdImpl(Ark_BaseEvent peer,
                                const Opt_Int32* targetDisplayId)
    {
    }
    } // BaseEventAccessor
    namespace BaseGestureEventAccessor {
    void DestroyPeerImpl(Ark_BaseGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<BaseGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Array_FingerInfo GetFingerListImpl(Ark_BaseGestureEvent peer)
    {
        return {};
    }
    void SetFingerListImpl(Ark_BaseGestureEvent peer,
                           const Array_FingerInfo* fingerList)
    {
    }
    Array_FingerInfo GetFingerInfosImpl(Ark_BaseGestureEvent peer)
    {
        return {};
    }
    } // BaseGestureEventAccessor
    namespace BaselineOffsetStyleAccessor {
    void DestroyPeerImpl(Ark_BaselineOffsetStyle peer)
    {
        auto peerImpl = reinterpret_cast<BaselineOffsetStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaselineOffsetStyle ConstructImpl(const Ark_LengthMetrics* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetBaselineOffsetImpl(Ark_BaselineOffsetStyle peer)
    {
        return {};
    }
    } // BaselineOffsetStyleAccessor
    namespace BaseShapeAccessor {
    void DestroyPeerImpl(Ark_BaseShape peer)
    {
        auto peerImpl = reinterpret_cast<BaseShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseShape ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_BaseShape WidthImpl(Ark_BaseShape peer,
                            const Ark_Length* width)
    {
        return {};
    }
    Ark_BaseShape HeightImpl(Ark_BaseShape peer,
                             const Ark_Length* height)
    {
        return {};
    }
    Ark_BaseShape SizeImpl(Ark_BaseShape peer,
                           const Ark_SizeOptions* size)
    {
        return {};
    }
    } // BaseShapeAccessor
    namespace BounceSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_BounceSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<BounceSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BounceSymbolEffect ConstructImpl(const Opt_EffectScope* scope,
                                         const Opt_EffectDirection* direction)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectScope GetScopeImpl(Ark_BounceSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_BounceSymbolEffect peer,
                      const Opt_EffectScope* scope)
    {
    }
    Opt_EffectDirection GetDirectionImpl(Ark_BounceSymbolEffect peer)
    {
        return {};
    }
    void SetDirectionImpl(Ark_BounceSymbolEffect peer,
                          const Opt_EffectDirection* direction)
    {
    }
    } // BounceSymbolEffectAccessor
    namespace BuilderNodeOpsAccessor {
    void DestroyPeerImpl(Ark_BuilderNodeOps peer)
    {
        auto peerImpl = reinterpret_cast<BuilderNodeOpsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BuilderNodeOps ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CreateImpl(Ark_BuilderNodeOps peer,
                    const Callback_Void* buildFunc)
    {
    }
    void DisposeNodeImpl(Ark_BuilderNodeOps peer)
    {
    }
    void SetUpdateConfigurationCallbackImpl(Ark_BuilderNodeOps peer,
                                            const Callback_Void* configurationUpdateFunc)
    {
    }
    void SetOptionsImpl(Ark_BuilderNodeOps peer,
                        const Ark_BuilderNodeOptions* options)
    {
    }
    Ark_Boolean PostTouchEventImpl(Ark_BuilderNodeOps peer,
                                   Ark_TouchEvent event)
    {
        return {};
    }
    Ark_NativePointer SetRootFrameNodeInBuilderNodeImpl(Ark_BuilderNodeOps peer,
                                                        Ark_NativePointer node)
    {
        return {};
    }
    } // BuilderNodeOpsAccessor
    namespace CalendarPickerDialogAccessor {
    void DestroyPeerImpl(Ark_CalendarPickerDialog peer)
    {
        auto peerImpl = reinterpret_cast<CalendarPickerDialogPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CalendarPickerDialog ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ShowImpl(const Opt_CalendarDialogOptions* options)
    {
    }
    } // CalendarPickerDialogAccessor
    namespace CanvasGradientAccessor {
    void DestroyPeerImpl(Ark_CanvasGradient peer)
    {
        auto peerImpl = reinterpret_cast<CanvasGradientPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasGradient ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void AddColorStopImpl(Ark_CanvasGradient peer,
                          Ark_Float64 offset,
                          const Ark_Union_String_ColorMetrics* color)
    {
    }
    } // CanvasGradientAccessor
    namespace CanvasPathAccessor {
    void DestroyPeerImpl(Ark_CanvasPath peer)
    {
        auto peerImpl = reinterpret_cast<CanvasPathPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasPath ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ArcImpl(Ark_CanvasPath peer,
                 const Ark_Number* x,
                 const Ark_Number* y,
                 const Ark_Number* radius,
                 const Ark_Number* startAngle,
                 const Ark_Number* endAngle,
                 const Opt_Boolean* counterclockwise)
    {
    }
    void ArcToImpl(Ark_CanvasPath peer,
                   const Ark_Number* x1,
                   const Ark_Number* y1,
                   const Ark_Number* x2,
                   const Ark_Number* y2,
                   const Ark_Number* radius)
    {
    }
    void BezierCurveToImpl(Ark_CanvasPath peer,
                           const Ark_Number* cp1x,
                           const Ark_Number* cp1y,
                           const Ark_Number* cp2x,
                           const Ark_Number* cp2y,
                           const Ark_Number* x,
                           const Ark_Number* y)
    {
    }
    void ClosePathImpl(Ark_CanvasPath peer)
    {
    }
    void EllipseImpl(Ark_CanvasPath peer,
                     const Ark_Number* x,
                     const Ark_Number* y,
                     const Ark_Number* radiusX,
                     const Ark_Number* radiusY,
                     const Ark_Number* rotation,
                     const Ark_Number* startAngle,
                     const Ark_Number* endAngle,
                     const Opt_Boolean* counterclockwise)
    {
    }
    void LineToImpl(Ark_CanvasPath peer,
                    const Ark_Number* x,
                    const Ark_Number* y)
    {
    }
    void MoveToImpl(Ark_CanvasPath peer,
                    const Ark_Number* x,
                    const Ark_Number* y)
    {
    }
    void QuadraticCurveToImpl(Ark_CanvasPath peer,
                              const Ark_Number* cpx,
                              const Ark_Number* cpy,
                              const Ark_Number* x,
                              const Ark_Number* y)
    {
    }
    void RectImpl(Ark_CanvasPath peer,
                  const Ark_Number* x,
                  const Ark_Number* y,
                  const Ark_Number* w,
                  const Ark_Number* h)
    {
    }
    } // CanvasPathAccessor
    namespace CanvasPatternAccessor {
    void DestroyPeerImpl(Ark_CanvasPattern peer)
    {
        auto peerImpl = reinterpret_cast<CanvasPatternPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasPattern ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetTransformImpl(Ark_CanvasPattern peer,
                          const Opt_Matrix2D* transform)
    {
    }
    } // CanvasPatternAccessor
    namespace CanvasRendererAccessor {
    void DestroyPeerImpl(Ark_CanvasRenderer peer)
    {
        auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasRenderer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DrawImage0Impl(Ark_CanvasRenderer peer,
                        const Ark_Union_ImageBitmap_PixelMap* image,
                        const Ark_Number* dx,
                        const Ark_Number* dy)
    {
    }
    void DrawImage1Impl(Ark_CanvasRenderer peer,
                        const Ark_Union_ImageBitmap_PixelMap* image,
                        const Ark_Number* dx,
                        const Ark_Number* dy,
                        const Ark_Number* dw,
                        const Ark_Number* dh)
    {
    }
    void DrawImage2Impl(Ark_CanvasRenderer peer,
                        const Ark_Union_ImageBitmap_PixelMap* image,
                        const Ark_Number* sx,
                        const Ark_Number* sy,
                        const Ark_Number* sw,
                        const Ark_Number* sh,
                        const Ark_Number* dx,
                        const Ark_Number* dy,
                        const Ark_Number* dw,
                        const Ark_Number* dh)
    {
    }
    void BeginPathImpl(Ark_CanvasRenderer peer)
    {
    }
    void Clip0Impl(Ark_CanvasRenderer peer,
                   const Opt_String* fillRule)
    {
    }
    void Clip1Impl(Ark_CanvasRenderer peer,
                   Ark_Path2D path,
                   const Opt_String* fillRule)
    {
    }
    void Fill0Impl(Ark_CanvasRenderer peer,
                   const Opt_String* fillRule)
    {
    }
    void Fill1Impl(Ark_CanvasRenderer peer,
                   Ark_Path2D path,
                   const Opt_String* fillRule)
    {
    }
    void StrokeImpl(Ark_CanvasRenderer peer,
                    const Opt_Path2D* path)
    {
    }
    Ark_CanvasGradient CreateLinearGradientImpl(Ark_CanvasRenderer peer,
                                                const Ark_Number* x0,
                                                const Ark_Number* y0,
                                                const Ark_Number* x1,
                                                const Ark_Number* y1)
    {
        return {};
    }
    Opt_CanvasPattern CreatePatternImpl(Ark_CanvasRenderer peer,
                                        Ark_ImageBitmap image,
                                        const Opt_String* repetition)
    {
        return {};
    }
    Ark_CanvasGradient CreateRadialGradientImpl(Ark_CanvasRenderer peer,
                                                const Ark_Number* x0,
                                                const Ark_Number* y0,
                                                const Ark_Number* r0,
                                                const Ark_Number* x1,
                                                const Ark_Number* y1,
                                                const Ark_Number* r1)
    {
        return {};
    }
    Ark_CanvasGradient CreateConicGradientImpl(Ark_CanvasRenderer peer,
                                               const Ark_Number* startAngle,
                                               const Ark_Number* x,
                                               const Ark_Number* y)
    {
        return {};
    }
    Ark_ImageData CreateImageData0Impl(Ark_CanvasRenderer peer,
                                       const Ark_Number* sw,
                                       const Ark_Number* sh)
    {
        return {};
    }
    Ark_ImageData CreateImageData1Impl(Ark_CanvasRenderer peer,
                                       Ark_ImageData imagedata)
    {
        return {};
    }
    Ark_ImageData GetImageDataImpl(Ark_CanvasRenderer peer,
                                   const Ark_Number* sx,
                                   const Ark_Number* sy,
                                   const Ark_Number* sw,
                                   const Ark_Number* sh)
    {
        return {};
    }
    Ark_image_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
                                       const Ark_Number* sx,
                                       const Ark_Number* sy,
                                       const Ark_Number* sw,
                                       const Ark_Number* sh)
    {
        return {};
    }
    void PutImageData0Impl(Ark_CanvasRenderer peer,
                           Ark_ImageData imagedata,
                           const Ark_Union_Number_String* dx,
                           const Ark_Union_Number_String* dy)
    {
    }
    void PutImageData1Impl(Ark_CanvasRenderer peer,
                           Ark_ImageData imagedata,
                           const Ark_Union_Number_String* dx,
                           const Ark_Union_Number_String* dy,
                           const Ark_Union_Number_String* dirtyX,
                           const Ark_Union_Number_String* dirtyY,
                           const Ark_Union_Number_String* dirtyWidth,
                           const Ark_Union_Number_String* dirtyHeight)
    {
    }
    Array_Number GetLineDashImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLineDashImpl(Ark_CanvasRenderer peer,
                         const Array_Number* segments)
    {
    }
    void ClearRectImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* x,
                       const Ark_Number* y,
                       const Ark_Number* w,
                       const Ark_Number* h)
    {
    }
    void FillRectImpl(Ark_CanvasRenderer peer,
                      const Ark_Number* x,
                      const Ark_Number* y,
                      const Ark_Number* w,
                      const Ark_Number* h)
    {
    }
    void StrokeRectImpl(Ark_CanvasRenderer peer,
                        const Ark_Number* x,
                        const Ark_Number* y,
                        const Ark_Number* w,
                        const Ark_Number* h)
    {
    }
    void RestoreImpl(Ark_CanvasRenderer peer)
    {
    }
    void SaveImpl(Ark_CanvasRenderer peer)
    {
    }
    void FillTextImpl(Ark_CanvasRenderer peer,
                      const Ark_String* text,
                      const Ark_Number* x,
                      const Ark_Number* y,
                      const Opt_Number* maxWidth)
    {
    }
    Ark_TextMetrics MeasureTextImpl(Ark_CanvasRenderer peer,
                                    const Ark_String* text)
    {
        return {};
    }
    void StrokeTextImpl(Ark_CanvasRenderer peer,
                        const Ark_String* text,
                        const Ark_Number* x,
                        const Ark_Number* y,
                        const Opt_Number* maxWidth)
    {
    }
    Ark_Matrix2D GetTransformImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void ResetTransformImpl(Ark_CanvasRenderer peer)
    {
    }
    void RotateImpl(Ark_CanvasRenderer peer,
                    const Ark_Number* angle)
    {
    }
    void ScaleImpl(Ark_CanvasRenderer peer,
                   const Ark_Number* x,
                   const Ark_Number* y)
    {
    }
    void SetTransform0Impl(Ark_CanvasRenderer peer,
                           const Ark_Number* a,
                           const Ark_Number* b,
                           const Ark_Number* c,
                           const Ark_Number* d,
                           const Ark_Number* e,
                           const Ark_Number* f)
    {
    }
    void SetTransform1Impl(Ark_CanvasRenderer peer,
                           const Opt_Matrix2D* transform)
    {
    }
    void TransformImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* a,
                       const Ark_Number* b,
                       const Ark_Number* c,
                       const Ark_Number* d,
                       const Ark_Number* e,
                       const Ark_Number* f)
    {
    }
    void TranslateImpl(Ark_CanvasRenderer peer,
                       const Ark_Number* x,
                       const Ark_Number* y)
    {
    }
    void SetPixelMapImpl(Ark_CanvasRenderer peer,
                         const Opt_image_PixelMap* value)
    {
    }
    void TransferFromImageBitmapImpl(Ark_CanvasRenderer peer,
                                     Ark_ImageBitmap bitmap)
    {
    }
    void SaveLayerImpl(Ark_CanvasRenderer peer)
    {
    }
    void RestoreLayerImpl(Ark_CanvasRenderer peer)
    {
    }
    void ResetImpl(Ark_CanvasRenderer peer)
    {
    }
    Ark_Union_LengthMetrics_String GetLetterSpacingImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLetterSpacingImpl(Ark_CanvasRenderer peer,
                              const Ark_Union_LengthMetrics_String* letterSpacing)
    {
    }
    Ark_Number GetGlobalAlphaImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetGlobalAlphaImpl(Ark_CanvasRenderer peer,
                            const Ark_Number* globalAlpha)
    {
    }
    Ark_String GetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetGlobalCompositeOperationImpl(Ark_CanvasRenderer peer,
                                         const Ark_String* globalCompositeOperation)
    {
    }
    Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern GetFillStyleImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetFillStyleImpl(Ark_CanvasRenderer peer,
                          const Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern* fillStyle)
    {
    }
    Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern GetStrokeStyleImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                            const Ark_Union_String_Color_I32_CanvasGradient_CanvasPattern* strokeStyle)
    {
    }
    Ark_String GetFilterImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetFilterImpl(Ark_CanvasRenderer peer,
                       const Ark_String* filter)
    {
    }
    Ark_Boolean GetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetImageSmoothingEnabledImpl(Ark_CanvasRenderer peer,
                                      Ark_Boolean imageSmoothingEnabled)
    {
    }
    Ark_String GetImageSmoothingQualityImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetImageSmoothingQualityImpl(Ark_CanvasRenderer peer,
                                      const Ark_String* imageSmoothingQuality)
    {
    }
    Ark_String GetLineCapImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLineCapImpl(Ark_CanvasRenderer peer,
                        const Ark_String* lineCap)
    {
    }
    Ark_Number GetLineDashOffsetImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLineDashOffsetImpl(Ark_CanvasRenderer peer,
                               const Ark_Number* lineDashOffset)
    {
    }
    Ark_String GetLineJoinImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLineJoinImpl(Ark_CanvasRenderer peer,
                         const Ark_String* lineJoin)
    {
    }
    Ark_Number GetLineWidthImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetLineWidthImpl(Ark_CanvasRenderer peer,
                          const Ark_Number* lineWidth)
    {
    }
    Ark_Number GetMiterLimitImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetMiterLimitImpl(Ark_CanvasRenderer peer,
                           const Ark_Number* miterLimit)
    {
    }
    Ark_Number GetShadowBlurImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetShadowBlurImpl(Ark_CanvasRenderer peer,
                           const Ark_Number* shadowBlur)
    {
    }
    Ark_String GetShadowColorImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetShadowColorImpl(Ark_CanvasRenderer peer,
                            const Ark_String* shadowColor)
    {
    }
    Ark_Number GetShadowOffsetXImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetShadowOffsetXImpl(Ark_CanvasRenderer peer,
                              const Ark_Number* shadowOffsetX)
    {
    }
    Ark_Number GetShadowOffsetYImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetShadowOffsetYImpl(Ark_CanvasRenderer peer,
                              const Ark_Number* shadowOffsetY)
    {
    }
    Ark_String GetDirectionImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetDirectionImpl(Ark_CanvasRenderer peer,
                          const Ark_String* direction)
    {
    }
    Ark_String GetFontImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetFontImpl(Ark_CanvasRenderer peer,
                     const Ark_String* font)
    {
    }
    Ark_String GetTextAlignImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetTextAlignImpl(Ark_CanvasRenderer peer,
                          const Ark_String* textAlign)
    {
    }
    Ark_String GetTextBaselineImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetTextBaselineImpl(Ark_CanvasRenderer peer,
                             const Ark_String* textBaseline)
    {
    }
    } // CanvasRendererAccessor
    namespace CanvasRenderingContext2DAccessor {
    void DestroyPeerImpl(Ark_CanvasRenderingContext2D peer)
    {
        auto peerImpl = reinterpret_cast<CanvasRenderingContext2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasRenderingContext2D ConstructImpl(const Opt_RenderingContextSettings* settings,
                                               const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String ToDataURLImpl(Ark_CanvasRenderingContext2D peer,
                             const Opt_String* type,
                             const Opt_Number* quality)
    {
        return {};
    }
    void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_CanvasRenderingContext2D peer,
                                const Ark_ImageAnalyzerConfig* config,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void StopImageAnalyzerImpl(Ark_CanvasRenderingContext2D peer)
    {
    }
    void OnOnAttachImpl(Ark_VMContext vmContext,
                        Ark_CanvasRenderingContext2D peer,
                        const Callback_Void* callback_)
    {
    }
    void OffOnAttachImpl(Ark_VMContext vmContext,
                         Ark_CanvasRenderingContext2D peer,
                         const Opt_Callback_Void* callback_)
    {
    }
    void OnOnDetachImpl(Ark_CanvasRenderingContext2D peer,
                        const Callback_Void* callback_)
    {
    }
    void OffOnDetachImpl(Ark_CanvasRenderingContext2D peer,
                         const Opt_Callback_Void* callback_)
    {
    }
    Ark_Number GetHeightImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    void SetHeightImpl(Ark_CanvasRenderingContext2D peer,
                       const Ark_Number* height)
    {
    }
    Ark_Number GetWidthImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    void SetWidthImpl(Ark_CanvasRenderingContext2D peer,
                      const Ark_Number* width)
    {
    }
    Ark_FrameNode GetCanvasImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    void SetCanvasImpl(Ark_CanvasRenderingContext2D peer,
                       Ark_FrameNode canvas)
    {
    }
    } // CanvasRenderingContext2DAccessor
    namespace ChildrenMainSizeAccessor {
    void DestroyPeerImpl(Ark_ChildrenMainSize peer)
    {
        auto peerImpl = reinterpret_cast<ChildrenMainSizePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ChildrenMainSize ConstructImpl(Ark_Float64 childDefaultSize)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SpliceImpl(Ark_ChildrenMainSize peer,
                    Ark_Int32 start,
                    const Opt_Int32* deleteCount,
                    const Opt_Array_Float64* childrenSize)
    {
    }
    void UpdateImpl(Ark_ChildrenMainSize peer,
                    Ark_Int32 index,
                    Ark_Float64 childSize)
    {
    }
    Ark_Float64 GetChildDefaultSizeImpl(Ark_ChildrenMainSize peer)
    {
        return {};
    }
    void SetChildDefaultSizeImpl(Ark_ChildrenMainSize peer,
                                 Ark_Float64 childDefaultSize)
    {
    }
    } // ChildrenMainSizeAccessor
    namespace ClickEventAccessor {
    void DestroyPeerImpl(Ark_ClickEvent peer)
    {
        auto peerImpl = reinterpret_cast<ClickEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ClickEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetDisplayXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_ClickEvent peer,
                         Ark_Float64 displayX)
    {
    }
    Ark_Float64 GetDisplayYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_ClickEvent peer,
                         Ark_Float64 displayY)
    {
    }
    Ark_Float64 GetWindowXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_ClickEvent peer,
                        Ark_Float64 windowX)
    {
    }
    Ark_Float64 GetWindowYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_ClickEvent peer,
                        Ark_Float64 windowY)
    {
    }
    Ark_Float64 GetXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_ClickEvent peer,
                  Ark_Float64 x)
    {
    }
    Ark_Float64 GetYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_ClickEvent peer,
                  Ark_Float64 y)
    {
    }
    Opt_InteractionHand GetHandImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetHandImpl(Ark_ClickEvent peer,
                     const Opt_InteractionHand* hand)
    {
    }
    void PreventDefaultImpl(Ark_ClickEvent peer)
    {
    }
    } // ClickEventAccessor
    namespace ClientAuthenticationHandlerAccessor {
    void DestroyPeerImpl(Ark_ClientAuthenticationHandler peer)
    {
        auto peerImpl = reinterpret_cast<ClientAuthenticationHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ClientAuthenticationHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void Confirm0Impl(Ark_ClientAuthenticationHandler peer,
                      const Ark_String* priKeyFile,
                      const Ark_String* certChainFile)
    {
    }
    void Confirm1Impl(Ark_ClientAuthenticationHandler peer,
                      const Ark_String* authUri)
    {
    }
    void CancelImpl(Ark_ClientAuthenticationHandler peer)
    {
    }
    void IgnoreImpl(Ark_ClientAuthenticationHandler peer)
    {
    }
    } // ClientAuthenticationHandlerAccessor
    namespace ColorContentAccessor {
    void DestroyPeerImpl(Ark_ColorContent peer)
    {
        auto peerImpl = reinterpret_cast<ColorContentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ColorContent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_ColorContent GetORIGINImpl()
    {
        return {};
    }
    } // ColorContentAccessor
    namespace ColorFilterAccessor {
    void DestroyPeerImpl(Ark_ColorFilter peer)
    {
        auto peerImpl = reinterpret_cast<ColorFilterPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ColorFilter ConstructImpl(const Array_Number* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // ColorFilterAccessor
    namespace CommonShapeAccessor {
    void DestroyPeerImpl(Ark_CommonShape peer)
    {
        auto peerImpl = reinterpret_cast<CommonShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CommonShape ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CommonShape OffsetImpl(Ark_CommonShape peer,
                               const Ark_Position* offset)
    {
        return {};
    }
    Ark_CommonShape FillImpl(Ark_CommonShape peer,
                             const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_CommonShape PositionImpl(Ark_CommonShape peer,
                                 const Ark_Position* position)
    {
        return {};
    }
    } // CommonShapeAccessor
    namespace ConsoleMessageAccessor {
    void DestroyPeerImpl(Ark_ConsoleMessage peer)
    {
        auto peerImpl = reinterpret_cast<ConsoleMessagePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ConsoleMessage ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetMessageImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    Ark_String GetSourceIdImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    Ark_Int32 GetLineNumberImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    Ark_MessageLevel GetMessageLevelImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    Ark_ConsoleMessageSource GetSourceImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    } // ConsoleMessageAccessor
    namespace ContentModifierHelperAccessor {
    void ContentModifierButtonImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const ButtonModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierButtonImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierCheckBoxImpl(Ark_NativePointer node,
                                     const Ark_Object* contentModifier,
                                     const CheckBoxModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierCheckBoxImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierDataPanelImpl(Ark_NativePointer node,
                                      const Ark_Object* contentModifier,
                                      const DataPanelModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierDataPanelImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierGaugeImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const GaugeModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierGaugeImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierLoadingProgressImpl(Ark_NativePointer node,
                                            const Ark_Object* contentModifier,
                                            const LoadingProgressModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierLoadingProgressImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierProgressImpl(Ark_NativePointer node,
                                     const Ark_Object* contentModifier,
                                     const ProgressModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierProgressImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierRadioImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const RadioModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierRadioImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierRatingImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const RatingModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierRatingImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierMenuItemImpl(Ark_NativePointer node,
                                     const Ark_Object* contentModifier,
                                     const MenuItemModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierMenuItemImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierSliderImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const SliderModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierSliderImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierTextClockImpl(Ark_NativePointer node,
                                      const Ark_Object* contentModifier,
                                      const TextClockModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierTextClockImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierTextTimerImpl(Ark_NativePointer node,
                                      const Ark_Object* contentModifier,
                                      const TextTimerModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierTextTimerImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ContentModifierToggleImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const ToggleModifierBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ResetContentModifierToggleImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // ContentModifierHelperAccessor
    namespace ControllerHandlerAccessor {
    void DestroyPeerImpl(Ark_ControllerHandler peer)
    {
        auto peerImpl = reinterpret_cast<ControllerHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ControllerHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetWebControllerImpl(Ark_ControllerHandler peer,
                              Ark_webview_WebviewController controller)
    {
    }
    } // ControllerHandlerAccessor
    namespace CopyEventAccessor {
    void DestroyPeerImpl(Ark_CopyEvent peer)
    {
        auto peerImpl = reinterpret_cast<CopyEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CopyEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void PreventDefaultImpl(Ark_CopyEvent peer)
    {
    }
    } // CopyEventAccessor
    namespace CustomDialogControllerAccessor {
    void DestroyPeerImpl(Ark_CustomDialogController peer)
    {
        auto peerImpl = reinterpret_cast<CustomDialogControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CustomDialogController ConstructImpl(const Ark_CustomDialogControllerOptions* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OpenImpl(Ark_CustomDialogController peer)
    {
    }
    void CloseImpl(Ark_CustomDialogController peer)
    {
    }
    Ark_CustomDialogControllerExternalOptions GetExternalOptionsImpl(Ark_CustomDialogController peer)
    {
        return {};
    }
    Ark_promptAction_CommonState GetStateImpl(Ark_CustomDialogController peer)
    {
        return {};
    }
    } // CustomDialogControllerAccessor
    namespace CustomDialogControllerExtenderAccessor {
    void DestroyPeerImpl(Ark_CustomDialogControllerExtender peer)
    {
        auto peerImpl = reinterpret_cast<CustomDialogControllerExtenderPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CustomDialogControllerExtender ConstructImpl(const Ark_CustomDialogControllerOptionsExtender* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OpenImpl(Ark_CustomDialogControllerExtender peer)
    {
    }
    void CloseImpl(Ark_CustomDialogControllerExtender peer)
    {
    }
    void SetOwnerViewImpl(Ark_CustomDialogControllerExtender peer,
                          Ark_NativePointer content)
    {
    }
    Ark_CustomDialogControllerExternalOptionsExtender GetExternalOptionsImpl(Ark_CustomDialogControllerExtender peer)
    {
        return {};
    }
    Ark_promptAction_CommonState GetStateImpl(Ark_CustomDialogControllerExtender peer)
    {
        return {};
    }
    } // CustomDialogControllerExtenderAccessor
    namespace CustomSpanAccessor {
    void DestroyPeerImpl(Ark_CustomSpan peer)
    {
        auto peerImpl = reinterpret_cast<CustomSpanPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CustomSpan ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InvalidateImpl(Ark_CustomSpan peer)
    {
    }
    Callback_CustomSpanMeasureInfo_CustomSpanMetrics GetOnMeasure_callbackImpl(Ark_CustomSpan peer)
    {
        return {};
    }
    void SetOnMeasure_callbackImpl(Ark_CustomSpan peer,
                                   const Callback_CustomSpanMeasureInfo_CustomSpanMetrics* onMeasure_callback)
    {
    }
    Callback_DrawContext_CustomSpanDrawInfo_Void GetOnDraw_callbackImpl(Ark_CustomSpan peer)
    {
        return {};
    }
    void SetOnDraw_callbackImpl(Ark_CustomSpan peer,
                                const Callback_DrawContext_CustomSpanDrawInfo_Void* onDraw_callback)
    {
    }
    } // CustomSpanAccessor
    namespace CutEventAccessor {
    void DestroyPeerImpl(Ark_CutEvent peer)
    {
        auto peerImpl = reinterpret_cast<CutEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CutEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void PreventDefaultImpl(Ark_CutEvent peer)
    {
    }
    } // CutEventAccessor
    namespace DataResubmissionHandlerAccessor {
    void DestroyPeerImpl(Ark_DataResubmissionHandler peer)
    {
        auto peerImpl = reinterpret_cast<DataResubmissionHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DataResubmissionHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ResendImpl(Ark_DataResubmissionHandler peer)
    {
    }
    void CancelImpl(Ark_DataResubmissionHandler peer)
    {
    }
    } // DataResubmissionHandlerAccessor
    namespace DatePickerDialogAccessor {
    void DestroyPeerImpl(Ark_DatePickerDialog peer)
    {
        auto peerImpl = reinterpret_cast<DatePickerDialogPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DatePickerDialog ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // DatePickerDialogAccessor
    namespace DecorationStyleAccessor {
    void DestroyPeerImpl(Ark_DecorationStyle peer)
    {
        auto peerImpl = reinterpret_cast<DecorationStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DecorationStyle ConstructImpl(const Ark_DecorationStyleInterface* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TextDecorationType GetTypeImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    Opt_ResourceColor GetColorImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    Opt_TextDecorationStyle GetStyleImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    } // DecorationStyleAccessor
    namespace DialogExtenderAccessor {
    void ShowTimePickerDialogImpl(const Ark_TimePickerDialogOptions* options)
    {
    }
    void ShowTextPickerDialogImpl(const Ark_TextPickerDialogOptions* options)
    {
    }
    void ShowDatePickerDialogImpl(const Ark_DatePickerDialogOptions* options)
    {
    }
    } // DialogExtenderAccessor
    namespace DisappearSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_DisappearSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<DisappearSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DisappearSymbolEffect ConstructImpl(const Opt_EffectScope* scope)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectScope GetScopeImpl(Ark_DisappearSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_DisappearSymbolEffect peer,
                      const Opt_EffectScope* scope)
    {
    }
    } // DisappearSymbolEffectAccessor
    namespace DismissDialogActionAccessor {
    void DestroyPeerImpl(Ark_DismissDialogAction peer)
    {
        auto peerImpl = reinterpret_cast<DismissDialogActionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DismissDialogAction ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DismissImpl(Ark_DismissDialogAction peer)
    {
    }
    Ark_DismissReason GetReasonImpl(Ark_DismissDialogAction peer)
    {
        return {};
    }
    void SetReasonImpl(Ark_DismissDialogAction peer,
                       Ark_DismissReason reason)
    {
    }
    } // DismissDialogActionAccessor
    namespace DismissPopupActionAccessor {
    void DestroyPeerImpl(Ark_DismissPopupAction peer)
    {
        auto peerImpl = reinterpret_cast<DismissPopupActionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DismissPopupAction ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DismissImpl(Ark_DismissPopupAction peer)
    {
    }
    Ark_DismissReason GetReasonImpl(Ark_DismissPopupAction peer)
    {
        return {};
    }
    void SetReasonImpl(Ark_DismissPopupAction peer,
                       Ark_DismissReason reason)
    {
    }
    } // DismissPopupActionAccessor
    namespace DragEventAccessor {
    void DestroyPeerImpl(Ark_DragEvent peer)
    {
        auto peerImpl = reinterpret_cast<DragEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DragEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetDisplayXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetDisplayYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetWindowXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetWindowYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetDataImpl(Ark_DragEvent peer,
                     Ark_unifiedDataChannel_UnifiedData unifiedData)
    {
    }
    Opt_unifiedDataChannel_UnifiedData GetDataImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Opt_unifiedDataChannel_Summary GetSummaryImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetResultImpl(Ark_DragEvent peer,
                       Ark_DragResult dragResult)
    {
    }
    Ark_DragResult GetResultImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Rectangle GetPreviewRectImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetVelocityXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetVelocityYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Float64 GetVelocityImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void ExecuteDropAnimationImpl(Ark_DragEvent peer,
                                  const Callback_Void* customDropAnimation)
    {
    }
    void EnableInternalDropAnimationImpl(Ark_DragEvent peer,
                                         const Ark_String* configuration)
    {
    }
    Ark_DragBehavior GetDragBehaviorImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetDragBehaviorImpl(Ark_DragEvent peer,
                             Ark_DragBehavior dragBehavior)
    {
    }
    Ark_Boolean GetUseCustomDropAnimationImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetUseCustomDropAnimationImpl(Ark_DragEvent peer,
                                       Ark_Boolean useCustomDropAnimation)
    {
    }
    Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetGetModifierKeyStateImpl(Ark_DragEvent peer,
                                    const Opt_ModifierKeyStateGetter* getModifierKeyState)
    {
    }
    } // DragEventAccessor
    namespace DrawingRenderingContextAccessor {
    void DestroyPeerImpl(Ark_DrawingRenderingContext peer)
    {
        auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawingRenderingContext ConstructImpl(const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InvalidateImpl(Ark_DrawingRenderingContext peer)
    {
    }
    Ark_Size GetSizeImpl(Ark_DrawingRenderingContext peer)
    {
        return {};
    }
    void SetSizeImpl(Ark_DrawingRenderingContext peer,
                     const Ark_Size* size)
    {
    }
    } // DrawingRenderingContextAccessor
    namespace EnvironmentBackendAccessor {
    Ark_Boolean IsAccessibilityEnabledImpl()
    {
        return {};
    }
    Ark_Int32 GetColorModeImpl()
    {
        return {};
    }
    Ark_Float32 GetFontScaleImpl()
    {
        return {};
    }
    Ark_Float32 GetFontWeightScaleImpl()
    {
        return {};
    }
    Ark_String GetLayoutDirectionImpl()
    {
        return {};
    }
    Ark_String GetLanguageCodeImpl()
    {
        return {};
    }
    } // EnvironmentBackendAccessor
    namespace EventEmulatorAccessor {
    void EmitClickEventImpl(Ark_NativePointer node,
                            Ark_ClickEvent event)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void EmitTextInputEventImpl(Ark_NativePointer node,
                                const Ark_String* text)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // EventEmulatorAccessor
    namespace EventResultAccessor {
    void DestroyPeerImpl(Ark_EventResult peer)
    {
        auto peerImpl = reinterpret_cast<EventResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EventResult ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetGestureEventResult0Impl(Ark_EventResult peer,
                                    Ark_Boolean result)
    {
    }
    void SetGestureEventResult1Impl(Ark_EventResult peer,
                                    Ark_Boolean result,
                                    Ark_Boolean stopPropagation)
    {
    }
    void SetMouseEventResultImpl(Ark_EventResult peer,
                                 Ark_Boolean result,
                                 const Opt_Boolean* stopPropagation)
    {
    }
    } // EventResultAccessor
    namespace EventTargetInfoAccessor {
    void DestroyPeerImpl(Ark_EventTargetInfo peer)
    {
        auto peerImpl = reinterpret_cast<EventTargetInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EventTargetInfo ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetIdImpl(Ark_EventTargetInfo peer)
    {
        return {};
    }
    } // EventTargetInfoAccessor
    namespace ExtendableComponentAccessor {
    void DestroyPeerImpl(Ark_ExtendableComponent peer)
    {
        auto peerImpl = reinterpret_cast<ExtendableComponentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ExtendableComponent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_UIContext GetUIContextImpl(Ark_ExtendableComponent peer)
    {
        return {};
    }
    Ark_Int32 GetUniqueIdImpl(Ark_ExtendableComponent peer)
    {
        return {};
    }
    Opt_uiObserver_NavDestinationInfo QueryNavDestinationInfo0Impl(Ark_ExtendableComponent peer)
    {
        return {};
    }
    Opt_uiObserver_NavDestinationInfo QueryNavDestinationInfo1Impl(Ark_ExtendableComponent peer,
                                                                   const Opt_Boolean* isInner)
    {
        return {};
    }
    Opt_uiObserver_NavigationInfo QueryNavigationInfoImpl(Ark_ExtendableComponent peer)
    {
        return {};
    }
    Opt_uiObserver_RouterPageInfo QueryRouterPageInfoImpl(Ark_ExtendableComponent peer)
    {
        return {};
    }
    } // ExtendableComponentAccessor
    namespace FileSelectorParamAccessor {
    void DestroyPeerImpl(Ark_FileSelectorParam peer)
    {
        auto peerImpl = reinterpret_cast<FileSelectorParamPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FileSelectorParam ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetTitleImpl(Ark_FileSelectorParam peer)
    {
        return {};
    }
    Ark_FileSelectorMode GetModeImpl(Ark_FileSelectorParam peer)
    {
        return {};
    }
    Array_String GetAcceptTypeImpl(Ark_FileSelectorParam peer)
    {
        return {};
    }
    Ark_Boolean IsCaptureImpl(Ark_FileSelectorParam peer)
    {
        return {};
    }
    Array_String GetMimeTypesImpl(Ark_FileSelectorParam peer)
    {
        return {};
    }
    } // FileSelectorParamAccessor
    namespace FileSelectorResultAccessor {
    void DestroyPeerImpl(Ark_FileSelectorResult peer)
    {
        auto peerImpl = reinterpret_cast<FileSelectorResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FileSelectorResult ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void HandleFileListImpl(Ark_FileSelectorResult peer,
                            const Array_String* fileList)
    {
    }
    } // FileSelectorResultAccessor
    namespace FocusAxisEventAccessor {
    void DestroyPeerImpl(Ark_FocusAxisEvent peer)
    {
        auto peerImpl = reinterpret_cast<FocusAxisEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FocusAxisEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Map_AxisModel_Float64 GetAxisMapImpl(Ark_FocusAxisEvent peer)
    {
        return {};
    }
    void SetAxisMapImpl(Ark_FocusAxisEvent peer,
                        const Map_AxisModel_Float64* axisMap)
    {
    }
    void StopPropagationImpl(Ark_FocusAxisEvent peer)
    {
    }
    } // FocusAxisEventAccessor
    namespace FocusControllerAccessor {
    void RequestFocusImpl(const Ark_String* key)
    {
    }
    } // FocusControllerAccessor
    namespace ForEachOpsAccessor {
    void SyncOnMoveOpsImpl(Ark_NativePointer node,
                           const Array_NativePointer* additionalChild,
                           const Opt_OnMoveHandler* onMoveOps,
                           const Opt_ItemDragEventHandler* onMoveDragEventOps)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // ForEachOpsAccessor
    namespace FrameNodeExtenderAccessor {
    Ark_NativePointer ConstructorFrameNodeImpl()
    {
        return {};
    }
    Ark_NativePointer GetDestroyImpl()
    {
        return {};
    }
    void DestroyPeerImpl(Ark_FrameNode peer)
    {
        auto peerImpl = reinterpret_cast<FrameNodeExtenderPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Boolean IsModifiableImpl(Ark_NativePointer peer)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_Int32 AppendChildImpl(Ark_FrameNode peer,
                              Ark_FrameNode child)
    {
        return {};
    }
    Ark_Int32 InsertChildAfterImpl(Ark_NativePointer peer,
                                   Ark_NativePointer child,
                                   Ark_NativePointer sibling)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    void RemoveChildImpl(Ark_FrameNode peer,
                         Ark_FrameNode child)
    {
    }
    void ClearChildrenImpl(Ark_FrameNode peer)
    {
    }
    Ark_NativePointer GetChildImpl(Ark_FrameNode peer,
                                   const Ark_Number* index,
                                   const Ark_Number* expandMode)
    {
        return {};
    }
    Ark_NativePointer GetFirstChildImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NativePointer GetNextSiblingImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NativePointer GetPreviousSiblingImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NativePointer GetParentImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Int32 GetChildrenCountImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void DisposeImpl(Ark_FrameNode peer)
    {
    }
    Ark_Vector2 GetPositionToWindowImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Vector2 GetPositionToParentImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Size GetMeasuredSizeImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Vector2 GetLayoutPositionImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_String GetIdImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Number GetUniqueIdImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_String GetNodeTypeImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Number GetOpacityImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Boolean IsVisibleImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Boolean IsClipToFrameImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Boolean IsAttachedImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_String GetInspectorInfoImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void InvalidateImpl(Ark_FrameNode peer)
    {
    }
    void DisposeTreeImpl(Ark_FrameNode peer)
    {
    }
    Ark_Boolean SetCrossLanguageOptionsImpl(Ark_FrameNode peer,
                                            Ark_Boolean options)
    {
        return {};
    }
    Ark_Boolean GetCrossLanguageOptionsImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void SetMeasuredSizeImpl(Ark_FrameNode peer,
                             const Ark_Size* size)
    {
    }
    void SetLayoutPositionImpl(Ark_FrameNode peer,
                               const Ark_Vector2* position)
    {
    }
    void MeasureImpl(Ark_FrameNode peer,
                     const Ark_LayoutConstraint* constraint)
    {
    }
    void LayoutImpl(Ark_FrameNode peer,
                    const Ark_Vector2* position)
    {
    }
    void SetNeedsLayoutImpl(Ark_FrameNode peer)
    {
    }
    Ark_Vector2 GetPositionToScreenImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Vector2 GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Vector2 GetPositionToParentWithTransformImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Vector2 GetPositionToScreenWithTransformImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NodeEdgesLengthMetrics GetUserConfigBorderWidthImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NodeEdgesLengthMetrics GetUserConfigPaddingImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NodeEdgesLengthMetrics GetUserConfigMarginImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_SizeTLengthMetrics GetUserConfigSizeImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NativePointer GetFrameNodeByKeyImpl(const Ark_String* name)
    {
        return {};
    }
    Ark_Number GetIdByFrameNodeImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_Int32 MoveToImpl(Ark_FrameNode peer,
                         Ark_FrameNode targetParent,
                         const Ark_Number* index)
    {
        return {};
    }
    Ark_Number GetFirstChildIndexWithoutExpandImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Number GetLastChildIndexWithoutExpandImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_NativePointer GetAttachedFrameNodeByIdImpl(const Ark_String* id)
    {
        return {};
    }
    Ark_NativePointer GetFrameNodeByIdImpl(const Ark_Number* id)
    {
        return {};
    }
    Ark_NativePointer GetFrameNodeByUniqueIdImpl(const Ark_Number* id)
    {
        return {};
    }
    void ReuseImpl(Ark_FrameNode peer)
    {
    }
    void RecycleImpl(Ark_FrameNode peer)
    {
    }
    Ark_Boolean CreateAnimationImpl(Ark_FrameNode peer,
                                    Ark_AnimationPropertyType property,
                                    const Opt_Array_Float64* startValue,
                                    const Array_Float64* endValue,
                                    const Ark_AnimateParam* param)
    {
        return {};
    }
    Ark_Boolean CancelAnimationsImpl(Ark_FrameNode peer,
                                     const Array_AnimationPropertyType* properties)
    {
        return {};
    }
    Array_Float64 GetNodePropertyValueImpl(Ark_FrameNode peer,
                                           Ark_AnimationPropertyType property)
    {
        return {};
    }
    Ark_NativePointer GetFrameNodePtrImpl(Ark_FrameNode node)
    {
        return {};
    }
    Ark_NativePointer CreateTypedFrameNodeImpl(const Ark_String* type)
    {
        return {};
    }
    Ark_NativePointer CreateByRawPtrImpl(Ark_NativePointer ptr)
    {
        return {};
    }
    Ark_NativePointer UnWrapRawPtrImpl(Ark_NativePointer ptr)
    {
        return {};
    }
    Ark_UICommonEvent GetCommonEventImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Int32 AdoptChildImpl(Ark_FrameNode peer,
                             Ark_FrameNode child)
    {
        return {};
    }
    Ark_Int32 RemoveAdoptedChildImpl(Ark_FrameNode peer,
                                     Ark_FrameNode child)
    {
        return {};
    }
    Ark_Boolean IsOnRenderTreeImpl(Ark_FrameNode peer)
    {
       return {};
    }
    } // FrameNodeExtenderAccessor
    namespace FrictionMotionAccessor {
    void DestroyPeerImpl(Ark_FrictionMotion peer)
    {
        auto peerImpl = reinterpret_cast<FrictionMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FrictionMotion ConstructImpl(const Ark_Number* friction,
                                     const Ark_Number* position,
                                     const Ark_Number* velocity)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // FrictionMotionAccessor
    namespace FullScreenExitHandlerAccessor {
    void DestroyPeerImpl(Ark_FullScreenExitHandler peer)
    {
        auto peerImpl = reinterpret_cast<FullScreenExitHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FullScreenExitHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ExitFullScreenImpl(Ark_FullScreenExitHandler peer)
    {
    }
    } // FullScreenExitHandlerAccessor
    namespace GestureAccessor {
    void DestroyPeerImpl(Ark_Gesture peer)
    {
        auto peerImpl = reinterpret_cast<GesturePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Gesture ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void TagImpl(Ark_Gesture peer,
                 const Ark_String* tag)
    {
    }
    void AllowedTypesImpl(Ark_Gesture peer,
                          const Array_SourceTool* types)
    {
    }
    } // GestureAccessor
    namespace GestureEventAccessor {
    void DestroyPeerImpl(Ark_GestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<GestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean GetRepeatImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetRepeatImpl(Ark_GestureEvent peer,
                       Ark_Boolean repeat)
    {
    }
    Array_FingerInfo GetFingerListImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetFingerListImpl(Ark_GestureEvent peer,
                           const Array_FingerInfo* fingerList)
    {
    }
    Array_FingerInfo GetFingerInfosImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    Ark_Float64 GetOffsetXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetOffsetXImpl(Ark_GestureEvent peer,
                        Ark_Float64 offsetX)
    {
    }
    Ark_Float64 GetOffsetYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetOffsetYImpl(Ark_GestureEvent peer,
                        Ark_Float64 offsetY)
    {
    }
    Ark_Float64 GetAngleImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_GestureEvent peer,
                      Ark_Float64 angle)
    {
    }
    Ark_Float64 GetSpeedImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetSpeedImpl(Ark_GestureEvent peer,
                      Ark_Float64 speed)
    {
    }
    Ark_Float64 GetScaleImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetScaleImpl(Ark_GestureEvent peer,
                      Ark_Float64 scale)
    {
    }
    Ark_Float64 GetPinchCenterXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterXImpl(Ark_GestureEvent peer,
                             Ark_Float64 pinchCenterX)
    {
    }
    Ark_Float64 GetPinchCenterYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterYImpl(Ark_GestureEvent peer,
                             Ark_Float64 pinchCenterY)
    {
    }
    Ark_Float64 GetVelocityXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityXImpl(Ark_GestureEvent peer,
                          Ark_Float64 velocityX)
    {
    }
    Ark_Float64 GetVelocityYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityYImpl(Ark_GestureEvent peer,
                          Ark_Float64 velocityY)
    {
    }
    Ark_Float64 GetVelocityImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityImpl(Ark_GestureEvent peer,
                         Ark_Float64 velocity)
    {
    }
    Opt_EventLocationInfo GetTapLocationImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    } // GestureEventAccessor
    namespace GestureGroupAccessor {
    void DestroyPeerImpl(Ark_GestureGroup peer)
    {
        auto peerImpl = reinterpret_cast<GestureGroupPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureGroup ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_GestureGroup $_instantiateImpl(const Callback_GestureGroup* factory,
                                       Ark_GestureMode mode,
                                       const Array_GestureType* gesture)
    {
        return {};
    }
    Ark_GestureGroup OnCancelImpl(Ark_GestureGroup peer,
                                  const Callback_Void* event)
    {
        return {};
    }
    } // GestureGroupAccessor
    namespace GestureRecognizerAccessor {
    void DestroyPeerImpl(Ark_GestureRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<GestureRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetTagImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_GestureControl_GestureType GetTypeImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_Boolean IsBuiltInImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    void SetEnabledImpl(Ark_GestureRecognizer peer,
                        Ark_Boolean isEnabled)
    {
    }
    Ark_Boolean IsEnabledImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_GestureRecognizerState GetStateImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_Boolean IsValidImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_Int32 GetFingerCountImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    Ark_Boolean IsFingerCountLimitImpl(Ark_GestureRecognizer peer)
    {
        return {};
    }
    } // GestureRecognizerAccessor
    namespace GestureStyleAccessor {
    void DestroyPeerImpl(Ark_GestureStyle peer)
    {
        auto peerImpl = reinterpret_cast<GestureStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureStyle ConstructImpl(const Opt_GestureStyleInterface* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // GestureStyleAccessor
    namespace GlobalScope_ohos_arkui_componentSnapshotAccessor {
    void GetImpl(const Ark_String* id,
                 const AsyncCallback_image_PixelMap_Void* callback,
                 const Opt_SnapshotOptions* options)
    {
    }
    } // GlobalScope_ohos_arkui_componentSnapshotAccessor
    namespace GlobalScope_ohos_arkui_performanceMonitorAccessor {
    void BeginImpl(const Ark_String* scene,
                   Ark_PerfMonitorActionType startInputType,
                   const Opt_String* note)
    {
    }
    void EndImpl(const Ark_String* scene)
    {
    }
    void RecordInputEventTimeImpl(Ark_PerfMonitorActionType actionType,
                                  Ark_PerfMonitorSourceType sourceType,
                                  Ark_Int64 time)
    {
    }
    } // GlobalScope_ohos_arkui_performanceMonitorAccessor
    namespace GlobalScope_ohos_fontAccessor {
    void RegisterFontImpl(const Ark_CustomObject* options)
    {
    }
    Array_String GetSystemFontListImpl()
    {
        return {};
    }
    Ark_CustomObject GetFontByNameImpl(const Ark_String* fontName)
    {
        return {};
    }
    } // GlobalScope_ohos_fontAccessor
    namespace GlobalScope_ohos_measure_utilsAccessor {
    Ark_Float64 MeasureTextImpl(const Ark_MeasureOptions* options)
    {
        return {};
    }
    Ark_SizeOptions MeasureTextSizeImpl(const Ark_MeasureOptions* options)
    {
        return {};
    }
    } // GlobalScope_ohos_measure_utilsAccessor
    namespace HierarchicalSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_HierarchicalSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<HierarchicalSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HierarchicalSymbolEffect ConstructImpl(const Opt_EffectFillStyle* fillStyle)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectFillStyle GetFillStyleImpl(Ark_HierarchicalSymbolEffect peer)
    {
        return {};
    }
    void SetFillStyleImpl(Ark_HierarchicalSymbolEffect peer,
                          const Opt_EffectFillStyle* fillStyle)
    {
    }
    } // HierarchicalSymbolEffectAccessor
    namespace HoverEventAccessor {
    void DestroyPeerImpl(Ark_HoverEvent peer)
    {
        auto peerImpl = reinterpret_cast<HoverEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HoverEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Float64 GetXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_HoverEvent peer,
                  const Opt_Float64* x)
    {
    }
    Opt_Float64 GetYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_HoverEvent peer,
                  const Opt_Float64* y)
    {
    }
    Opt_Float64 GetWindowXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_HoverEvent peer,
                        const Opt_Float64* windowX)
    {
    }
    Opt_Float64 GetWindowYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_HoverEvent peer,
                        const Opt_Float64* windowY)
    {
    }
    Opt_Float64 GetDisplayXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_HoverEvent peer,
                         const Opt_Float64* displayX)
    {
    }
    Opt_Float64 GetDisplayYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_HoverEvent peer,
                         const Opt_Float64* displayY)
    {
    }
    void StopPropagationImpl(Ark_HoverEvent peer)
    {
    }
    } // HoverEventAccessor
    namespace HttpAuthHandlerAccessor {
    void DestroyPeerImpl(Ark_HttpAuthHandler peer)
    {
        auto peerImpl = reinterpret_cast<HttpAuthHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HttpAuthHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean ConfirmImpl(Ark_HttpAuthHandler peer,
                            const Ark_String* userName,
                            const Ark_String* password)
    {
        return {};
    }
    void CancelImpl(Ark_HttpAuthHandler peer)
    {
    }
    Ark_Boolean IsHttpAuthInfoSavedImpl(Ark_HttpAuthHandler peer)
    {
        return {};
    }
    } // HttpAuthHandlerAccessor
    namespace ImageAnalyzerControllerAccessor {
    void DestroyPeerImpl(Ark_ImageAnalyzerController peer)
    {
        auto peerImpl = reinterpret_cast<ImageAnalyzerControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageAnalyzerController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Array_ImageAnalyzerType GetImageAnalyzerSupportTypesImpl(Ark_ImageAnalyzerController peer)
    {
        return {};
    }
    } // ImageAnalyzerControllerAccessor
    namespace ImageAttachmentAccessor {
    void DestroyPeerImpl(Ark_ImageAttachment peer)
    {
        auto peerImpl = reinterpret_cast<ImageAttachmentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageAttachment ConstructImpl(const Opt_AttachmentType* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_image_PixelMap GetValueImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Opt_SizeOptions GetSizeImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Opt_ImageSpanAlignment GetVerticalAlignImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Opt_ImageFit GetObjectFitImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Opt_ImageAttachmentLayoutStyle GetLayoutStyleImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Opt_ColorFilterType GetColorFilterImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    } // ImageAttachmentAccessor
    namespace ImageBitmapAccessor {
    void DestroyPeerImpl(Ark_ImageBitmap peer)
    {
        auto peerImpl = reinterpret_cast<ImageBitmapPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageBitmap ConstructImpl(const Ark_Union_PixelMap_String* src,
                                  const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CloseImpl(Ark_ImageBitmap peer)
    {
    }
    Ark_Number GetHeightImpl(Ark_ImageBitmap peer)
    {
        return {};
    }
    void SetHeightImpl(Ark_ImageBitmap peer,
                       const Ark_Number* height)
    {
    }
    Ark_Number GetWidthImpl(Ark_ImageBitmap peer)
    {
        return {};
    }
    void SetWidthImpl(Ark_ImageBitmap peer,
                      const Ark_Number* width)
    {
    }
    } // ImageBitmapAccessor
    namespace ImageDataAccessor {
    void DestroyPeerImpl(Ark_ImageData peer)
    {
        auto peerImpl = reinterpret_cast<ImageDataPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageData ConstructImpl(const Ark_Number* width,
                                const Ark_Number* height,
                                const Opt_Buffer* data,
                                const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Buffer GetDataImpl(Ark_ImageData peer)
    {
        return {};
    }
    void SetDataImpl(Ark_ImageData peer,
                     const Ark_Buffer* data)
    {
    }
    Ark_Int32 GetHeightImpl(Ark_ImageData peer)
    {
        return {};
    }
    void SetHeightImpl(Ark_ImageData peer,
                       Ark_Int32 height)
    {
    }
    Ark_Int32 GetWidthImpl(Ark_ImageData peer)
    {
        return {};
    }
    void SetWidthImpl(Ark_ImageData peer,
                      Ark_Int32 width)
    {
    }
    } // ImageDataAccessor
    namespace IndicatorComponentControllerAccessor {
    void DestroyPeerImpl(Ark_IndicatorComponentController peer)
    {
        auto peerImpl = reinterpret_cast<IndicatorComponentControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_IndicatorComponentController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ShowNextImpl(Ark_IndicatorComponentController peer)
    {
    }
    void ShowPreviousImpl(Ark_IndicatorComponentController peer)
    {
    }
    void ChangeIndexImpl(Ark_IndicatorComponentController peer,
                         const Ark_Number* index,
                         const Opt_Boolean* useAnimation)
    {
    }
    } // IndicatorComponentControllerAccessor
    namespace IUIContextAccessor {
    void FreezeUINode0Impl(const Ark_String* id,
                           Ark_Boolean isFrozen)
    {
    }
    void FreezeUINode1Impl(const Ark_Number* id,
                           Ark_Boolean isFrozen)
    {
    }
    Ark_Boolean DispatchKeyEventImpl(const Ark_Union_Number_String* node,
                                     Ark_KeyEvent event)
    {
        return {};
    }
    void OpenBindSheetImpl(Ark_VMContext vmContext,
                           Ark_AsyncWorkerPtr asyncWorker,
                           Ark_NativePointer bindSheetContent,
                           const Opt_SheetOptions* sheetOptions,
                           const Opt_Int32* targetId,
                           const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpdateBindSheetImpl(Ark_VMContext vmContext,
                             Ark_AsyncWorkerPtr asyncWorker,
                             Ark_NativePointer bindSheetContent,
                             const Ark_SheetOptions* sheetOptions,
                             const Opt_Boolean* partialUpdate,
                             const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void CloseBindSheetImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_NativePointer bindSheetContent,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    } // IUIContextAccessor
    namespace JsGeolocationAccessor {
    void DestroyPeerImpl(Ark_JsGeolocation peer)
    {
        auto peerImpl = reinterpret_cast<JsGeolocationPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_JsGeolocation ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InvokeImpl(Ark_JsGeolocation peer,
                    const Ark_String* origin,
                    Ark_Boolean allow,
                    Ark_Boolean retain)
    {
    }
    } // JsGeolocationAccessor
    namespace JsResultAccessor {
    void DestroyPeerImpl(Ark_JsResult peer)
    {
        auto peerImpl = reinterpret_cast<JsResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_JsResult ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void HandleCancelImpl(Ark_JsResult peer)
    {
    }
    void HandleConfirmImpl(Ark_JsResult peer)
    {
    }
    void HandlePromptConfirmImpl(Ark_JsResult peer,
                                 const Ark_String* result)
    {
    }
    } // JsResultAccessor
    namespace KeyEventAccessor {
    void DestroyPeerImpl(Ark_KeyEvent peer)
    {
        auto peerImpl = reinterpret_cast<KeyEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_KeyEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_KeyType GetTypeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetTypeImpl(Ark_KeyEvent peer,
                     Ark_KeyType type)
    {
    }
    Ark_Int32 GetKeyCodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetKeyCodeImpl(Ark_KeyEvent peer,
                        const Ark_Int32* keyCode)
    {
    }
    Ark_String GetKeyTextImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetKeyTextImpl(Ark_KeyEvent peer,
                        const Ark_String* keyText)
    {
    }
    Ark_KeySource GetKeySourceImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetKeySourceImpl(Ark_KeyEvent peer,
                          Ark_KeySource keySource)
    {
    }
    Ark_Int32 GetDeviceIdImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetDeviceIdImpl(Ark_KeyEvent peer,
                         Ark_Int32 deviceId)
    {
    }
    Ark_Int32 GetMetaKeyImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetMetaKeyImpl(Ark_KeyEvent peer,
                        Ark_Int32 metaKey)
    {
    }
    Ark_Int64 GetTimestampImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetTimestampImpl(Ark_KeyEvent peer,
                          Ark_Int64 timestamp)
    {
    }
    Callback_Void GetStopPropagationImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetStopPropagationImpl(Ark_KeyEvent peer,
                                const Callback_Void* stopPropagation)
    {
    }
    Ark_IntentionCode GetIntentionCodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetIntentionCodeImpl(Ark_KeyEvent peer,
                              Ark_IntentionCode intentionCode)
    {
    }
    Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetGetModifierKeyStateImpl(Ark_KeyEvent peer,
                                    const Opt_ModifierKeyStateGetter* getModifierKeyState)
    {
    }
    Opt_Int64 GetUnicodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetUnicodeImpl(Ark_KeyEvent peer,
                        const Opt_Int64* unicode)
    {
    }
    } // KeyEventAccessor
    namespace LayoutableAccessor {
    void DestroyPeerImpl(Ark_Layoutable peer)
    {
        auto peerImpl = reinterpret_cast<LayoutablePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Layoutable ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void LayoutImpl(Ark_Layoutable peer,
                    const Ark_Position* position)
    {
    }
    Opt_DirectionalEdgesT GetMarginImpl(Ark_Layoutable peer)
    {
        return {};
    }
    Opt_DirectionalEdgesT GetPaddingImpl(Ark_Layoutable peer)
    {
        return {};
    }
    Opt_DirectionalEdgesT GetBorderWidthImpl(Ark_Layoutable peer)
    {
        return {};
    }
    Ark_MeasureResult GetMeasureResultImpl(Ark_Layoutable peer)
    {
        return {};
    }
    void SetMeasureResultImpl(Ark_Layoutable peer,
                              const Ark_MeasureResult* measureResult)
    {
    }
    Opt_Number GetUniqueIdImpl(Ark_Layoutable peer)
    {
        return {};
    }
    void SetUniqueIdImpl(Ark_Layoutable peer,
                         const Opt_Number* uniqueId)
    {
    }
    } // LayoutableAccessor
    namespace LayoutManagerAccessor {
    void DestroyPeerImpl(Ark_LayoutManager peer)
    {
        auto peerImpl = reinterpret_cast<LayoutManagerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayoutManager ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Int32 GetLineCountImpl(Ark_LayoutManager peer)
    {
        return {};
    }
    Ark_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_LayoutManager peer,
                                                              Ark_Float64 x,
                                                              Ark_Float64 y)
    {
        return {};
    }
    Ark_text_LineMetrics GetLineMetricsImpl(Ark_LayoutManager peer,
                                            Ark_Int32 lineNumber)
    {
        return {};
    }
    Array_text_TextBox GetRectsForRangeImpl(Ark_LayoutManager peer,
                                            const Ark_TextRange* range,
                                            Ark_text_RectWidthStyle widthStyle,
                                            Ark_text_RectHeightStyle heightStyle)
    {
        return {};
    }
    } // LayoutManagerAccessor
    namespace LayoutPolicyAccessor {
    void DestroyPeerImpl(Ark_LayoutPolicy peer)
    {
        auto peerImpl = reinterpret_cast<LayoutPolicyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayoutPolicy ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_LayoutPolicy GetMatchParentImpl()
    {
        return {};
    }
    Ark_LayoutPolicy GetWrapContentImpl()
    {
        return {};
    }
    Ark_LayoutPolicy GetFixAtIdealSizeImpl()
    {
        return {};
    }
    } // LayoutPolicyAccessor
    namespace LazyBuildAccessor {
    void ApplyLazyBuilderImpl()
    {
    }
    void SetListItemLazyBuilderImpl(Ark_NativePointer node,
                                    const CustomNodeBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetTabContentLazyBuilderImpl(Ark_NativePointer node,
                                      const CustomNodeBuilder* builder)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // LazyBuildAccessor
    namespace LazyForEachOpsAccessor {
    void NotifyChangeImpl(Ark_NativePointer node,
                          Ark_Int32 startIndex,
                          Ark_Int32 endIndex,
                          Ark_Int32 count)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SyncImpl(Ark_NativePointer node,
                  Ark_Int32 totalCount,
                  const Callback_CreateItem* creator,
                  const Callback_RangeUpdate* updater)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SyncOnMoveOpsImpl(Ark_NativePointer node,
                           const Callback_OnMoveFromTo* onMoveFromToOps,
                           const Opt_OnMoveHandler* onMoveOps,
                           const Opt_ItemDragEventHandler* onMoveDragEventOps)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // LazyForEachOpsAccessor
    namespace LetterSpacingStyleAccessor {
    void DestroyPeerImpl(Ark_LetterSpacingStyle peer)
    {
        auto peerImpl = reinterpret_cast<LetterSpacingStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LetterSpacingStyle ConstructImpl(const Ark_LengthMetrics* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetLetterSpacingImpl(Ark_LetterSpacingStyle peer)
    {
        return {};
    }
    } // LetterSpacingStyleAccessor
    namespace LevelOrderExtenderAccessor {
    void DestroyPeerImpl(Ark_LevelOrderExtender peer)
    {
        auto peerImpl = reinterpret_cast<LevelOrderExtenderPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LevelOrderExtender ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_LevelOrderExtender ClampImpl(const Ark_Number* order)
    {
        return {};
    }
    Ark_Number GetOrderImpl(Ark_LevelOrderExtender peer)
    {
        return {};
    }
    } // LevelOrderExtenderAccessor
    namespace LifeCycleAccessor {
    void DestroyPeerImpl(Ark_LifeCycle peer)
    {
        auto peerImpl = reinterpret_cast<LifeCyclePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LifeCycle ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void AboutToAppearImpl(Ark_LifeCycle peer)
    {
    }
    void AboutToDisappearImpl(Ark_LifeCycle peer)
    {
    }
    void OnDidBuildImpl(Ark_LifeCycle peer)
    {
    }
    void BuildImpl(Ark_LifeCycle peer)
    {
    }
    } // LifeCycleAccessor
    namespace LinearGradientAccessor {
    void DestroyPeerImpl(Ark_LinearGradient peer)
    {
        auto peerImpl = reinterpret_cast<LinearGradientPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LinearGradient ConstructImpl(const Array_ColorStop* colorStops)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // LinearGradientAccessor
    namespace LinearIndicatorControllerAccessor {
    void DestroyPeerImpl(Ark_LinearIndicatorController peer)
    {
        auto peerImpl = reinterpret_cast<LinearIndicatorControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LinearIndicatorController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetProgressImpl(Ark_LinearIndicatorController peer,
                         const Ark_Number* index,
                         const Ark_Number* progress)
    {
    }
    void StartImpl(Ark_LinearIndicatorController peer,
                   const Opt_LinearIndicatorStartOptions* options)
    {
    }
    void PauseImpl(Ark_LinearIndicatorController peer)
    {
    }
    void StopImpl(Ark_LinearIndicatorController peer)
    {
    }
    } // LinearIndicatorControllerAccessor
    namespace LineHeightStyleAccessor {
    void DestroyPeerImpl(Ark_LineHeightStyle peer)
    {
        auto peerImpl = reinterpret_cast<LineHeightStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LineHeightStyle ConstructImpl(const Ark_LengthMetrics* lineHeight)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetLineHeightImpl(Ark_LineHeightStyle peer)
    {
        return {};
    }
    } // LineHeightStyleAccessor
    namespace ListScrollerAccessor {
    void DestroyPeerImpl(Ark_ListScroller peer)
    {
        auto peerImpl = reinterpret_cast<ListScrollerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ListScroller ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_RectResult GetItemRectInGroupImpl(Ark_VMContext vmContext,
                                          Ark_ListScroller peer,
                                          Ark_Int32 index,
                                          Ark_Int32 indexInGroup)
    {
        return {};
    }
    void ScrollToItemInGroupImpl(Ark_VMContext vmContext,
                                 Ark_ListScroller peer,
                                 Ark_Int32 index,
                                 Ark_Int32 indexInGroup,
                                 const Opt_Boolean* smooth,
                                 const Opt_ScrollAlign* align)
    {
    }
    void CloseAllSwipeActionsImpl(Ark_VMContext vmContext,
                                  Ark_ListScroller peer,
                                  const Opt_CloseSwipeActionOptions* options)
    {
    }
    Ark_VisibleListContentInfo GetVisibleListContentInfoImpl(Ark_VMContext vmContext,
                                                             Ark_ListScroller peer,
                                                             Ark_Float64 x,
                                                             Ark_Float64 y)
    {
        return {};
    }
    } // ListScrollerAccessor
    namespace LongPressGestureEventAccessor {
    void DestroyPeerImpl(Ark_LongPressGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<LongPressGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LongPressGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean GetRepeatImpl(Ark_LongPressGestureEvent peer)
    {
        return {};
    }
    void SetRepeatImpl(Ark_LongPressGestureEvent peer,
                       Ark_Boolean repeat)
    {
    }
    } // LongPressGestureEventAccessor
    namespace LongPressRecognizerAccessor {
    void DestroyPeerImpl(Ark_LongPressRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<LongPressRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LongPressRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean IsRepeatImpl(Ark_LongPressRecognizer peer)
    {
        return {};
    }
    Ark_Int32 GetDurationImpl(Ark_LongPressRecognizer peer)
    {
        return {};
    }
    } // LongPressRecognizerAccessor
    namespace Matrix2DAccessor {
    void DestroyPeerImpl(Ark_Matrix2D peer)
    {
        auto peerImpl = reinterpret_cast<Matrix2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Matrix2D Construct0Impl()
    {
        return {};
    }
    Ark_Matrix2D Construct1Impl(Ark_LengthMetricsUnit unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Matrix2D IdentityImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    Ark_Matrix2D InvertImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    Ark_Matrix2D RotateImpl(Ark_Matrix2D peer,
                            const Ark_Number* degree,
                            const Opt_Number* rx,
                            const Opt_Number* ry)
    {
        return {};
    }
    Ark_Matrix2D TranslateImpl(Ark_Matrix2D peer,
                               const Opt_Number* tx,
                               const Opt_Number* ty)
    {
        return {};
    }
    Ark_Matrix2D ScaleImpl(Ark_Matrix2D peer,
                           const Opt_Number* sx,
                           const Opt_Number* sy)
    {
        return {};
    }
    Opt_Number GetScaleXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetScaleXImpl(Ark_Matrix2D peer,
                       const Opt_Number* scaleX)
    {
    }
    Opt_Number GetScaleYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetScaleYImpl(Ark_Matrix2D peer,
                       const Opt_Number* scaleY)
    {
    }
    Opt_Number GetRotateXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetRotateXImpl(Ark_Matrix2D peer,
                        const Opt_Number* rotateX)
    {
    }
    Opt_Number GetRotateYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetRotateYImpl(Ark_Matrix2D peer,
                        const Opt_Number* rotateY)
    {
    }
    Opt_Number GetTranslateXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetTranslateXImpl(Ark_Matrix2D peer,
                           const Opt_Number* translateX)
    {
    }
    Opt_Number GetTranslateYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetTranslateYImpl(Ark_Matrix2D peer,
                           const Opt_Number* translateY)
    {
    }
    } // Matrix2DAccessor
    namespace MeasurableAccessor {
    void DestroyPeerImpl(Ark_Measurable peer)
    {
        auto peerImpl = reinterpret_cast<MeasurablePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Measurable ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_MeasureResult MeasureImpl(Ark_Measurable peer,
                                  const Ark_ConstraintSizeOptions* constraint)
    {
        return {};
    }
    Opt_DirectionalEdgesT GetMarginImpl(Ark_Measurable peer)
    {
        return {};
    }
    Opt_DirectionalEdgesT GetPaddingImpl(Ark_Measurable peer)
    {
        return {};
    }
    Opt_DirectionalEdgesT GetBorderWidthImpl(Ark_Measurable peer)
    {
        return {};
    }
    Opt_Number GetUniqueIdImpl(Ark_Measurable peer)
    {
        return {};
    }
    void SetUniqueIdImpl(Ark_Measurable peer,
                         const Opt_Number* uniqueId)
    {
    }
    } // MeasurableAccessor
    namespace MenuItemConfigurationAccessor {
    void DestroyPeerImpl(Ark_MenuItemConfiguration peer)
    {
        auto peerImpl = reinterpret_cast<MenuItemConfigurationPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_MenuItemConfiguration ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void TriggerSelectImpl(Ark_MenuItemConfiguration peer,
                           Ark_Int32 index,
                           const Ark_String* value)
    {
    }
    Ark_Boolean GetEnabledImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetEnabledImpl(Ark_MenuItemConfiguration peer,
                        Ark_Boolean enabled)
    {
    }
    Ark_ContentModifier GetContentModifierImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetContentModifierImpl(Ark_MenuItemConfiguration peer,
                                const Ark_Object* contentModifier)
    {
    }
    Ark_ResourceStr GetValueImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetValueImpl(Ark_MenuItemConfiguration peer,
                      const Ark_ResourceStr* value)
    {
    }
    Opt_ResourceStr GetIconImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetIconImpl(Ark_MenuItemConfiguration peer,
                     const Opt_ResourceStr* icon)
    {
    }
    Opt_SymbolGlyphModifier GetSymbolIconImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetSymbolIconImpl(Ark_MenuItemConfiguration peer,
                           const Opt_SymbolGlyphModifier* symbolIcon)
    {
    }
    Ark_Boolean GetSelectedImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetSelectedImpl(Ark_MenuItemConfiguration peer,
                         Ark_Boolean selected)
    {
    }
    Ark_Int32 GetIndexImpl(Ark_MenuItemConfiguration peer)
    {
        return {};
    }
    void SetIndexImpl(Ark_MenuItemConfiguration peer,
                      Ark_Int32 index)
    {
    }
    } // MenuItemConfigurationAccessor
    namespace MouseEventAccessor {
    void DestroyPeerImpl(Ark_MouseEvent peer)
    {
        auto peerImpl = reinterpret_cast<MouseEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_MouseEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_MouseButton GetButtonImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetButtonImpl(Ark_MouseEvent peer,
                       Ark_MouseButton button)
    {
    }
    Ark_MouseAction GetActionImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetActionImpl(Ark_MouseEvent peer,
                       Ark_MouseAction action)
    {
    }
    Ark_Float64 GetDisplayXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_MouseEvent peer,
                         Ark_Float64 displayX)
    {
    }
    Ark_Float64 GetDisplayYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_MouseEvent peer,
                         Ark_Float64 displayY)
    {
    }
    Ark_Float64 GetWindowXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_MouseEvent peer,
                        Ark_Float64 windowX)
    {
    }
    Ark_Float64 GetWindowYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_MouseEvent peer,
                        Ark_Float64 windowY)
    {
    }
    Ark_Float64 GetXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_MouseEvent peer,
                  Ark_Float64 x)
    {
    }
    Ark_Float64 GetYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_MouseEvent peer,
                  Ark_Float64 y)
    {
    }
    Callback_Void GetStopPropagationImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetStopPropagationImpl(Ark_MouseEvent peer,
                                const Callback_Void* stopPropagation)
    {
    }
    Opt_Float64 GetRawDeltaXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetRawDeltaXImpl(Ark_MouseEvent peer,
                          const Opt_Float64* rawDeltaX)
    {
    }
    Opt_Float64 GetRawDeltaYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetRawDeltaYImpl(Ark_MouseEvent peer,
                          const Opt_Float64* rawDeltaY)
    {
    }
    Opt_Array_MouseButton GetPressedButtonsImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetPressedButtonsImpl(Ark_MouseEvent peer,
                               const Opt_Array_MouseButton* pressedButtons)
    {
    }
    } // MouseEventAccessor
    namespace MutableStyledStringAccessor {
    void DestroyPeerImpl(Ark_MutableStyledString peer)
    {
        auto peerImpl = reinterpret_cast<MutableStyledStringPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_MutableStyledString ConstructImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                                          const Opt_Array_StyleOptions* styles)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReplaceStringImpl(Ark_MutableStyledString peer,
                           Ark_Int32 start,
                           Ark_Int32 length,
                           const Ark_String* other)
    {
    }
    void InsertStringImpl(Ark_MutableStyledString peer,
                          Ark_Int32 start,
                          const Ark_String* other)
    {
    }
    void RemoveStringImpl(Ark_MutableStyledString peer,
                          Ark_Int32 start,
                          Ark_Int32 length)
    {
    }
    void ReplaceStyleImpl(Ark_MutableStyledString peer,
                          const Ark_SpanStyle* spanStyle)
    {
    }
    void SetStyleImpl(Ark_MutableStyledString peer,
                      const Ark_SpanStyle* spanStyle)
    {
    }
    void RemoveStyleImpl(Ark_MutableStyledString peer,
                         Ark_Int32 start,
                         Ark_Int32 length,
                         Ark_StyledStringKey styledKey)
    {
    }
    void RemoveStylesImpl(Ark_MutableStyledString peer,
                          Ark_Int32 start,
                          Ark_Int32 length)
    {
    }
    void ClearStylesImpl(Ark_MutableStyledString peer)
    {
    }
    void ReplaceStyledStringImpl(Ark_MutableStyledString peer,
                                 Ark_Int32 start,
                                 Ark_Int32 length,
                                 Ark_StyledString other)
    {
    }
    void InsertStyledStringImpl(Ark_MutableStyledString peer,
                                Ark_Int32 start,
                                Ark_StyledString other)
    {
    }
    void AppendStyledStringImpl(Ark_MutableStyledString peer,
                                Ark_StyledString other)
    {
    }
    } // MutableStyledStringAccessor
    namespace NavDestinationContextAccessor {
    void DestroyPeerImpl(Ark_NavDestinationContext peer)
    {
        auto peerImpl = reinterpret_cast<NavDestinationContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavDestinationContext ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_RouteMapConfig GetConfigInRouteMapImpl(Ark_NavDestinationContext peer)
    {
        return {};
    }
    Ark_NavPathInfo GetPathInfoImpl(Ark_NavDestinationContext peer)
    {
        return {};
    }
    void SetPathInfoImpl(Ark_NavDestinationContext peer,
                         Ark_NavPathInfo pathInfo)
    {
    }
    Ark_NavPathStack GetPathStackImpl(Ark_NavDestinationContext peer)
    {
        return {};
    }
    void SetPathStackImpl(Ark_NavDestinationContext peer,
                          Ark_NavPathStack pathStack)
    {
    }
    Opt_String GetNavDestinationIdImpl(Ark_NavDestinationContext peer)
    {
        return {};
    }
    void SetNavDestinationIdImpl(Ark_NavDestinationContext peer,
                                 const Opt_String* navDestinationId)
    {
    }
    } // NavDestinationContextAccessor
    namespace NavExtenderAccessor {
    void SetNavigationOptionsImpl(Ark_NativePointer ptr,
                                  Ark_NavPathStack pathStack)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetUpdateStackCallbackImpl(Ark_NavPathStack peer,
                                    const NavExtender_OnUpdateStack* callback)
    {
    }
    void SyncStackImpl(Ark_NavPathStack peer)
    {
    }
    Ark_Boolean CheckNeedCreateImpl(Ark_NativePointer navigation,
                                    Ark_Int32 index)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                                   Ark_Int32 index,
                                   Ark_NativePointer node)
    {
    }
    void PushPathImpl(Ark_NavPathStack pathStack,
                      Ark_NavPathInfo info,
                      const Ark_NavigationOptions* options)
    {
    }
    void ReplacePathImpl(Ark_NavPathStack pathStack,
                         Ark_NavPathInfo info,
                         const Ark_NavigationOptions* options)
    {
    }
    Ark_String PopImpl(Ark_NavPathStack pathStack,
                       Ark_Boolean animated)
    {
        return {};
    }
    void SetOnPopCallbackImpl(Ark_NavPathStack pathStack,
                              const Callback_String_Void* popCallback)
    {
    }
    Ark_String GetIdByIndexImpl(Ark_NavPathStack pathStack,
                                Ark_Int32 index)
    {
        return {};
    }
    Array_String GetIdByNameImpl(Ark_NavPathStack pathStack,
                                 const Ark_String* name)
    {
        return {};
    }
    void PopToIndexImpl(Ark_NavPathStack pathStack,
                        Ark_Int32 index,
                        Ark_Boolean animated)
    {
    }
    Ark_Number PopToNameImpl(Ark_NavPathStack pathStack,
                             const Ark_String* name,
                             Ark_Boolean animated)
    {
        return {};
    }
    void SetCreateNavDestinationCallbackImpl(Ark_NavPathStack peer,
                                             const NavExtender_CreateNavDestination* callback)
    {
    }
    Array_String GetRouteMapInConfigImpl(Ark_NativePointer context)
    {
        return {};
    }
    } // NavExtenderAccessor
    namespace NavigationTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_NavigationTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<NavigationTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavigationTransitionProxy ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void FinishTransitionImpl(Ark_NavigationTransitionProxy peer)
    {
    }
    Ark_NavContentInfo GetFromImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetFromImpl(Ark_NavigationTransitionProxy peer,
                     const Ark_NavContentInfo* from)
    {
    }
    Ark_NavContentInfo GetToImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetToImpl(Ark_NavigationTransitionProxy peer,
                   const Ark_NavContentInfo* to)
    {
    }
    Opt_Boolean GetIsInteractiveImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetIsInteractiveImpl(Ark_NavigationTransitionProxy peer,
                              const Opt_Boolean* isInteractive)
    {
    }
    Opt_VoidCallback GetCancelTransitionImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetCancelTransitionImpl(Ark_NavigationTransitionProxy peer,
                                 const Opt_VoidCallback* cancelTransition)
    {
    }
    Opt_UpdateTransitionCallback GetUpdateTransitionImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetUpdateTransitionImpl(Ark_NavigationTransitionProxy peer,
                                 const Opt_UpdateTransitionCallback* updateTransition)
    {
    }
    } // NavigationTransitionProxyAccessor
    namespace NavPathInfoAccessor {
    void DestroyPeerImpl(Ark_NavPathInfo peer)
    {
        auto peerImpl = reinterpret_cast<NavPathInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavPathInfo ConstructImpl(const Ark_String* name,
                                  const Opt_Object* param,
                                  const Opt_Callback_PopInfo_Void* onPop,
                                  const Opt_Boolean* isEntry)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetNameImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetNameImpl(Ark_NavPathInfo peer,
                     const Ark_String* name)
    {
    }
    Opt_Object GetParamImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetParamImpl(Ark_NavPathInfo peer,
                      const Opt_Object* param)
    {
    }
    Opt_Callback_PopInfo_Void GetOnPopImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetOnPopImpl(Ark_NavPathInfo peer,
                      const Opt_Callback_PopInfo_Void* onPop)
    {
    }
    Opt_Boolean GetIsEntryImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetIsEntryImpl(Ark_NavPathInfo peer,
                        const Opt_Boolean* isEntry)
    {
    }
    Opt_String GetNavDestinationIdImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetNavDestinationIdImpl(Ark_NavPathInfo peer,
                                 const Opt_String* navDestinationId)
    {
    }
    } // NavPathInfoAccessor
    namespace NavPathStackAccessor {
    void DestroyPeerImpl(Ark_NavPathStack peer)
    {
        auto peerImpl = reinterpret_cast<NavPathStackPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavPathStack ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void PushPath0Impl(Ark_NavPathStack peer,
                       Ark_NavPathInfo info,
                       const Opt_Boolean* animated)
    {
    }
    void PushPath1Impl(Ark_NavPathStack peer,
                       Ark_NavPathInfo info,
                       const Opt_NavigationOptions* options)
    {
    }
    void PushDestination0Impl(Ark_VMContext vmContext,
                              Ark_AsyncWorkerPtr asyncWorker,
                              Ark_NavPathStack peer,
                              Ark_NavPathInfo info,
                              const Opt_Boolean* animated,
                              const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PushDestination1Impl(Ark_VMContext vmContext,
                              Ark_AsyncWorkerPtr asyncWorker,
                              Ark_NavPathStack peer,
                              Ark_NavPathInfo info,
                              const Opt_NavigationOptions* options,
                              const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PushPathByName0Impl(Ark_NavPathStack peer,
                             const Ark_String* name,
                             const Opt_Object* param,
                             const Opt_Boolean* animated)
    {
    }
    void PushPathByName1Impl(Ark_NavPathStack peer,
                             const Ark_String* name,
                             const Ark_Object* param,
                             const Callback_PopInfo_Void* onPop,
                             const Opt_Boolean* animated)
    {
    }
    void PushDestinationByName0Impl(Ark_VMContext vmContext,
                                    Ark_AsyncWorkerPtr asyncWorker,
                                    Ark_NavPathStack peer,
                                    const Ark_String* name,
                                    const Ark_Object* param,
                                    const Opt_Boolean* animated,
                                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PushDestinationByName1Impl(Ark_VMContext vmContext,
                                    Ark_AsyncWorkerPtr asyncWorker,
                                    Ark_NavPathStack peer,
                                    const Ark_String* name,
                                    const Ark_Object* param,
                                    const Callback_PopInfo_Void* onPop,
                                    const Opt_Boolean* animated,
                                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ReplacePath0Impl(Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_Boolean* animated)
    {
    }
    void ReplacePath1Impl(Ark_NavPathStack peer,
                          Ark_NavPathInfo info,
                          const Opt_NavigationOptions* options)
    {
    }
    void ReplaceDestinationImpl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_NavPathStack peer,
                                Ark_NavPathInfo info,
                                const Opt_NavigationOptions* options,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ReplacePathByNameImpl(Ark_NavPathStack peer,
                               const Ark_String* name,
                               const Ark_Object* param,
                               const Opt_Boolean* animated)
    {
    }
    Ark_Number RemoveByIndexesImpl(Ark_NavPathStack peer,
                                   const Array_Number* indexes)
    {
        return {};
    }
    Ark_Number RemoveByNameImpl(Ark_NavPathStack peer,
                                const Ark_String* name)
    {
        return {};
    }
    Ark_Boolean RemoveByNavDestinationIdImpl(Ark_NavPathStack peer,
                                             const Ark_String* navDestinationId)
    {
        return {};
    }
    Opt_NavPathInfo Pop0Impl(Ark_NavPathStack peer,
                             const Opt_Boolean* animated)
    {
        return {};
    }
    Opt_NavPathInfo Pop1Impl(Ark_NavPathStack peer,
                             const Ark_Object* result,
                             const Opt_Boolean* animated)
    {
        return {};
    }
    Ark_Number PopToName0Impl(Ark_NavPathStack peer,
                              const Ark_String* name,
                              const Opt_Boolean* animated)
    {
        return {};
    }
    Ark_Number PopToName1Impl(Ark_NavPathStack peer,
                              const Ark_String* name,
                              const Ark_Object* result,
                              const Opt_Boolean* animated)
    {
        return {};
    }
    void PopToIndex0Impl(Ark_NavPathStack peer,
                         const Ark_Number* index,
                         const Opt_Boolean* animated)
    {
    }
    void PopToIndex1Impl(Ark_NavPathStack peer,
                         const Ark_Number* index,
                         const Ark_Object* result,
                         const Opt_Boolean* animated)
    {
    }
    Ark_Number MoveToTopImpl(Ark_NavPathStack peer,
                             const Ark_String* name,
                             const Opt_Boolean* animated)
    {
        return {};
    }
    void MoveIndexToTopImpl(Ark_NavPathStack peer,
                            const Ark_Number* index,
                            const Opt_Boolean* animated)
    {
    }
    void ClearImpl(Ark_NavPathStack peer,
                   const Opt_Boolean* animated)
    {
    }
    Array_String GetAllPathNameImpl(Ark_NavPathStack peer)
    {
        return {};
    }
    Opt_Object GetParamByIndexImpl(Ark_NavPathStack peer,
                                   const Ark_Number* index)
    {
        return {};
    }
    Array_Opt_Object GetParamByNameImpl(Ark_NavPathStack peer,
                                        const Ark_String* name)
    {
        return {};
    }
    Array_Number GetIndexByNameImpl(Ark_NavPathStack peer,
                                    const Ark_String* name)
    {
        return {};
    }
    Opt_NavPathStack GetParentImpl(Ark_NavPathStack peer)
    {
        return {};
    }
    Ark_Number SizeImpl(Ark_NavPathStack peer)
    {
        return {};
    }
    void DisableAnimationImpl(Ark_NavPathStack peer,
                              Ark_Boolean value)
    {
    }
    void SetInterceptionImpl(Ark_NavPathStack peer,
                             const Ark_NavigationInterception* interception)
    {
    }
    Array_NavPathInfo GetPathStackImpl(Ark_NavPathStack peer)
    {
        return {};
    }
    void SetPathStackImpl(Ark_NavPathStack peer,
                          const Array_NavPathInfo* pathStack,
                          const Opt_Boolean* animated)
    {
    }
    } // NavPathStackAccessor
    namespace NodeContainerOpsAccessor {
    Ark_NativePointer NodeContainerOpsConstructImpl(Ark_Int32 id,
                                                    Ark_Int32 flags)
    {
        return {};
    }
    void NodeContainerSetNodeContainerOptionsImpl(Ark_NativePointer ptr,
                                                  Ark_NativePointer controller)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void AddNodeContainerRootNodeImpl(Ark_NativePointer self,
                                      Ark_NativePointer child)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetAboutToAppearImpl(Ark_NativePointer self,
                              const Callback_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetAboutToDisappearImpl(Ark_NativePointer self,
                                 const Callback_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetAboutToResizeImpl(Ark_NativePointer self,
                              const Callback_Size_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetOnAttachImpl(Ark_NativePointer self,
                         const Callback_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetOnDetachImpl(Ark_NativePointer self,
                         const Callback_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetOnTouchEventImpl(Ark_NativePointer self,
                             const Opt_Callback_TouchEvent_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetOnDestoryEventImpl(Ark_NativePointer self,
                               const Callback_OnDestory_Void* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // NodeContainerOpsAccessor
    namespace NodeContentExtenderAccessor {
    Ark_NativePointer ConstructorNodeContentImpl()
    {
        return {};
    }
    Ark_NativePointer GetDestroyImpl()
    {
        return {};
    }
    Ark_Int32 AddFrameNodeImpl(Ark_NativePointer content,
                               Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_Boolean RemoveFrameNodeImpl(Ark_NativePointer content,
                                    Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    } // NodeContentExtenderAccessor
    namespace OffscreenCanvasAccessor {
    void DestroyPeerImpl(Ark_OffscreenCanvas peer)
    {
        auto peerImpl = reinterpret_cast<OffscreenCanvasPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_OffscreenCanvas ConstructImpl(const Ark_Number* width,
                                      const Ark_Number* height,
                                      const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvas peer)
    {
        return {};
    }
    Ark_OffscreenCanvasRenderingContext2D GetContext2dImpl(Ark_OffscreenCanvas peer,
                                                           const Opt_RenderingContextSettings* options)
    {
        return {};
    }
    Ark_Number GetHeightImpl(Ark_OffscreenCanvas peer)
    {
        return {};
    }
    void SetHeightImpl(Ark_OffscreenCanvas peer,
                       const Ark_Number* height)
    {
    }
    Ark_Number GetWidthImpl(Ark_OffscreenCanvas peer)
    {
        return {};
    }
    void SetWidthImpl(Ark_OffscreenCanvas peer,
                      const Ark_Number* width)
    {
    }
    } // OffscreenCanvasAccessor
    namespace OffscreenCanvasRenderingContext2DAccessor {
    void DestroyPeerImpl(Ark_OffscreenCanvasRenderingContext2D peer)
    {
        auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_OffscreenCanvasRenderingContext2D ConstructImpl(const Ark_Number* width,
                                                        const Ark_Number* height,
                                                        const Opt_RenderingContextSettings* settings,
                                                        const Opt_LengthMetricsUnit* unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String ToDataURLImpl(Ark_OffscreenCanvasRenderingContext2D peer,
                             const Opt_String* type,
                             const Opt_Number* quality)
    {
        return {};
    }
    Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvasRenderingContext2D peer)
    {
        return {};
    }
    } // OffscreenCanvasRenderingContext2DAccessor
    namespace PanGestureEventAccessor {
    void DestroyPeerImpl(Ark_PanGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetOffsetXImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetOffsetXImpl(Ark_PanGestureEvent peer,
                        Ark_Float64 offsetX)
    {
    }
    Ark_Float64 GetOffsetYImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetOffsetYImpl(Ark_PanGestureEvent peer,
                        Ark_Float64 offsetY)
    {
    }
    Ark_Float64 GetVelocityXImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityXImpl(Ark_PanGestureEvent peer,
                          Ark_Float64 velocityX)
    {
    }
    Ark_Float64 GetVelocityYImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityYImpl(Ark_PanGestureEvent peer,
                          Ark_Float64 velocityY)
    {
    }
    Ark_Float64 GetVelocityImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityImpl(Ark_PanGestureEvent peer,
                         Ark_Float64 velocity)
    {
    }
    } // PanGestureEventAccessor
    namespace PanGestureOptionsAccessor {
    void DestroyPeerImpl(Ark_PanGestureOptions peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureOptionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureOptions ConstructImpl(const Opt_PanGestureHandlerOptions* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetDirectionImpl(Ark_PanGestureOptions peer,
                          Ark_PanDirection value)
    {
    }
    void SetDistanceImpl(Ark_PanGestureOptions peer,
                         Ark_Float64 value)
    {
    }
    void SetFingersImpl(Ark_PanGestureOptions peer,
                        Ark_Int32 value)
    {
    }
    Ark_PanDirection GetDirectionImpl(Ark_PanGestureOptions peer)
    {
        return {};
    }
    Ark_Float64 GetDistanceImpl(Ark_PanGestureOptions peer)
    {
        return {};
    }
    } // PanGestureOptionsAccessor
    namespace PanRecognizerAccessor {
    void DestroyPeerImpl(Ark_PanRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<PanRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PanGestureOptions GetPanGestureOptionsImpl(Ark_PanRecognizer peer)
    {
        return {};
    }
    } // PanRecognizerAccessor
    namespace ParagraphStyleAccessor {
    void DestroyPeerImpl(Ark_ParagraphStyle peer)
    {
        auto peerImpl = reinterpret_cast<ParagraphStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ParagraphStyle ConstructImpl(const Opt_ParagraphStyleInterface* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Float64 GetTextIndentImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Int32 GetMaxLinesImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Union_F64_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Float64 GetParagraphSpacingImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    } // ParagraphStyleAccessor
    namespace Path2DAccessor {
    void DestroyPeerImpl(Ark_Path2D peer)
    {
        auto peerImpl = reinterpret_cast<Path2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Path2D Construct0Impl()
    {
        return {};
    }
    Ark_Path2D Construct1Impl(Ark_LengthMetricsUnit unit)
    {
        return {};
    }
    Ark_Path2D Construct2Impl(Ark_Path2D path)
    {
        return {};
    }
    Ark_Path2D Construct3Impl(Ark_Path2D path,
                              Ark_LengthMetricsUnit unit)
    {
        return {};
    }
    Ark_Path2D Construct4Impl(const Ark_String* d)
    {
        return {};
    }
    Ark_Path2D Construct5Impl(const Ark_String* description,
                              Ark_LengthMetricsUnit unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void AddPathImpl(Ark_Path2D peer,
                     Ark_Path2D path,
                     const Opt_Matrix2D* transform)
    {
    }
    } // Path2DAccessor
    namespace PatternLockControllerAccessor {
    void DestroyPeerImpl(Ark_PatternLockController peer)
    {
        auto peerImpl = reinterpret_cast<PatternLockControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PatternLockController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ResetImpl(Ark_PatternLockController peer)
    {
    }
    void SetChallengeResultImpl(Ark_PatternLockController peer,
                                Ark_PatternLockChallengeResult result)
    {
    }
    } // PatternLockControllerAccessor
    namespace PermissionRequestAccessor {
    void DestroyPeerImpl(Ark_PermissionRequest peer)
    {
        auto peerImpl = reinterpret_cast<PermissionRequestPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PermissionRequest ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DenyImpl(Ark_PermissionRequest peer)
    {
    }
    Ark_String GetOriginImpl(Ark_PermissionRequest peer)
    {
        return {};
    }
    Array_String GetAccessibleResourceImpl(Ark_PermissionRequest peer)
    {
        return {};
    }
    void GrantImpl(Ark_PermissionRequest peer,
                   const Array_String* resources)
    {
    }
    } // PermissionRequestAccessor
    namespace PersistentStorageBackendAccessor {
    Opt_String GetImpl(const Ark_String* key)
    {
        return {};
    }
    Ark_Boolean HasImpl(const Ark_String* key)
    {
        return {};
    }
    void RemoveImpl(const Ark_String* key)
    {
    }
    void SetImpl(const Ark_String* key,
                 const Ark_String* value)
    {
    }
    void ClearImpl()
    {
    }
    } // PersistentStorageBackendAccessor
    namespace PinchGestureEventAccessor {
    void DestroyPeerImpl(Ark_PinchGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<PinchGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PinchGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetScaleImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetScaleImpl(Ark_PinchGestureEvent peer,
                      Ark_Float64 scale)
    {
    }
    Ark_Float64 GetPinchCenterXImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterXImpl(Ark_PinchGestureEvent peer,
                             Ark_Float64 pinchCenterX)
    {
    }
    Ark_Float64 GetPinchCenterYImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterYImpl(Ark_PinchGestureEvent peer,
                             Ark_Float64 pinchCenterY)
    {
    }
    } // PinchGestureEventAccessor
    namespace PinchRecognizerAccessor {
    void DestroyPeerImpl(Ark_PinchRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<PinchRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PinchRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetDistanceImpl(Ark_PinchRecognizer peer)
    {
        return {};
    }
    } // PinchRecognizerAccessor
    namespace PixelMapMockAccessor {
    void DestroyPeerImpl(Ark_PixelMapMock peer)
    {
        auto peerImpl = reinterpret_cast<PixelMapMockPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PixelMapMock ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReleaseImpl(Ark_PixelMapMock peer)
    {
    }
    } // PixelMapMockAccessor
    namespace ProgressMaskAccessor {
    void DestroyPeerImpl(Ark_ProgressMask peer)
    {
        auto peerImpl = reinterpret_cast<ProgressMaskPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ProgressMask ConstructImpl(Ark_Float64 value,
                                   Ark_Float64 total,
                                   const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void UpdateProgressImpl(Ark_ProgressMask peer,
                            Ark_Float64 value)
    {
    }
    void UpdateColorImpl(Ark_ProgressMask peer,
                         const Ark_ResourceColor* value)
    {
    }
    void EnableBreathingAnimationImpl(Ark_ProgressMask peer,
                                      Ark_Boolean value)
    {
    }
    } // ProgressMaskAccessor
    namespace PromptActionExtenderAccessor {
    void OpenPopupImpl(Ark_VMContext vmContext,
                       Ark_AsyncWorkerPtr asyncWorker,
                       Ark_NativePointer content,
                       const Ark_TargetInfo* target,
                       const Opt_PopupCommonOptions* options,
                       const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpdatePopupImpl(Ark_VMContext vmContext,
                         Ark_AsyncWorkerPtr asyncWorker,
                         Ark_NativePointer content,
                         const Ark_PopupCommonOptions* options,
                         const Opt_Boolean* partialUpdate,
                         const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ClosePopupImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_NativePointer content,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void OpenMenuImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_NativePointer content,
                      const Ark_TargetInfo* target,
                      const Opt_MenuOptions* options,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpdateMenuImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_NativePointer content,
                        const Ark_MenuOptions* options,
                        const Opt_Boolean* partialUpdate,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void CloseMenuImpl(Ark_VMContext vmContext,
                       Ark_AsyncWorkerPtr asyncWorker,
                       Ark_NativePointer content,
                       const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    } // PromptActionExtenderAccessor
    namespace PulseSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_PulseSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<PulseSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PulseSymbolEffect ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // PulseSymbolEffectAccessor
    namespace RenderingContextSettingsAccessor {
    void DestroyPeerImpl(Ark_RenderingContextSettings peer)
    {
        auto peerImpl = reinterpret_cast<RenderingContextSettingsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RenderingContextSettings ConstructImpl(const Opt_Boolean* antialias)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Boolean GetAntialiasImpl(Ark_RenderingContextSettings peer)
    {
        return {};
    }
    void SetAntialiasImpl(Ark_RenderingContextSettings peer,
                          const Opt_Boolean* antialias)
    {
    }
    } // RenderingContextSettingsAccessor
    namespace RenderServiceNodeAccessor {
    Ark_Int32 GetNodeIdImpl(const Ark_String* nodeId)
    {
        return {};
    }
    } // RenderServiceNodeAccessor
    namespace ReplaceSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_ReplaceSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<ReplaceSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ReplaceSymbolEffect ConstructImpl(const Opt_EffectScope* scope)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectScope GetScopeImpl(Ark_ReplaceSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_ReplaceSymbolEffect peer,
                      const Opt_EffectScope* scope)
    {
    }
    } // ReplaceSymbolEffectAccessor
    namespace RestrictedWorkerAccessor {
    void DestroyPeerImpl(Ark_RestrictedWorker peer)
    {
        auto peerImpl = reinterpret_cast<RestrictedWorkerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RestrictedWorker ConstructImpl(const Ark_String* scriptURL,
                                       const Opt_WorkerOptions* options)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void PostMessage0Impl(Ark_VMContext vmContext,
                          Ark_RestrictedWorker peer,
                          const Ark_Object* message,
                          const Array_Buffer* transfer)
    {
    }
    void PostMessage1Impl(Ark_VMContext vmContext,
                          Ark_RestrictedWorker peer,
                          const Ark_Object* message,
                          const Opt_PostMessageOptions* options)
    {
    }
    void PostMessageWithSharedSendableImpl(Ark_VMContext vmContext,
                                           Ark_RestrictedWorker peer,
                                           const Ark_Object* message,
                                           const Opt_Array_Buffer* transfer)
    {
    }
    void OnImpl(Ark_VMContext vmContext,
                Ark_RestrictedWorker peer,
                const Ark_String* Type,
                const WorkerEventListener* listener)
    {
    }
    void OnceImpl(Ark_VMContext vmContext,
                  Ark_RestrictedWorker peer,
                  const Ark_String* Type,
                  const WorkerEventListener* listener)
    {
    }
    void OffImpl(Ark_VMContext vmContext,
                 Ark_RestrictedWorker peer,
                 const Ark_String* Type,
                 const Opt_WorkerEventListener* listener)
    {
    }
    void TerminateImpl(Ark_VMContext vmContext,
                       Ark_RestrictedWorker peer)
    {
    }
    void AddEventListenerImpl(Ark_VMContext vmContext,
                              Ark_RestrictedWorker peer,
                              const Ark_String* Type,
                              const WorkerEventListener* listener)
    {
    }
    Ark_Boolean DispatchEventImpl(Ark_VMContext vmContext,
                                  Ark_RestrictedWorker peer,
                                  const Ark_Event* event)
    {
        return {};
    }
    void RemoveEventListenerImpl(Ark_VMContext vmContext,
                                 Ark_RestrictedWorker peer,
                                 const Ark_String* Type,
                                 const Opt_WorkerEventListener* callback_)
    {
    }
    void RemoveAllListenerImpl(Ark_VMContext vmContext,
                               Ark_RestrictedWorker peer)
    {
    }
    void RegisterGlobalCallObjectImpl(Ark_VMContext vmContext,
                                      Ark_RestrictedWorker peer,
                                      const Ark_String* instanceName,
                                      const Ark_Object* globalCallObject)
    {
    }
    void UnregisterGlobalCallObjectImpl(Ark_VMContext vmContext,
                                        Ark_RestrictedWorker peer,
                                        const Opt_String* instanceName)
    {
    }
    Opt_RestrictedWorker_onexit_Callback GetOnexitImpl(Ark_RestrictedWorker peer)
    {
        return {};
    }
    void SetOnexitImpl(Ark_RestrictedWorker peer,
                       const Opt_RestrictedWorker_onexit_Callback* onexit)
    {
    }
    Opt_RestrictedWorker_onerror_Callback GetOnerrorImpl(Ark_RestrictedWorker peer)
    {
        return {};
    }
    void SetOnerrorImpl(Ark_RestrictedWorker peer,
                        const Opt_RestrictedWorker_onerror_Callback* onerror)
    {
    }
    Opt_RestrictedWorker_onmessage_Callback GetOnmessageImpl(Ark_RestrictedWorker peer)
    {
        return {};
    }
    void SetOnmessageImpl(Ark_RestrictedWorker peer,
                          const Opt_RestrictedWorker_onmessage_Callback* onmessage)
    {
    }
    Opt_RestrictedWorker_onmessage_Callback GetOnmessageerrorImpl(Ark_RestrictedWorker peer)
    {
        return {};
    }
    void SetOnmessageerrorImpl(Ark_RestrictedWorker peer,
                               const Opt_RestrictedWorker_onmessage_Callback* onmessageerror)
    {
    }
    } // RestrictedWorkerAccessor
    namespace RichEditorBaseControllerAccessor {
    void DestroyPeerImpl(Ark_RichEditorBaseController peer)
    {
        auto peerImpl = reinterpret_cast<RichEditorBaseControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RichEditorBaseController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Int32 GetCaretOffsetImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Opt_Boolean SetCaretOffsetImpl(Ark_RichEditorBaseController peer,
                                   Ark_Int32 offset)
    {
        return {};
    }
    void CloseSelectionMenuImpl(Ark_RichEditorBaseController peer)
    {
    }
    Opt_RichEditorTextStyle GetTypingStyleImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    void SetTypingStyleImpl(Ark_RichEditorBaseController peer,
                            const Ark_RichEditorTextStyle* value)
    {
    }
    void SetSelectionImpl(Ark_RichEditorBaseController peer,
                          const Ark_Number* selectionStart,
                          const Ark_Number* selectionEnd,
                          const Opt_SelectionOptions* options)
    {
    }
    Opt_Boolean IsEditingImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    void StopEditingImpl(Ark_RichEditorBaseController peer)
    {
    }
    Opt_LayoutManager GetLayoutManagerImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Opt_PreviewText GetPreviewTextImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Opt_RectResult GetCaretRectImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    void DeleteBackwardImpl(Ark_RichEditorBaseController peer)
    {
    }
    } // RichEditorBaseControllerAccessor
    namespace RichEditorControllerAccessor {
    void DestroyPeerImpl(Ark_RichEditorController peer)
    {
        auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RichEditorController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Int32 AddTextSpanImpl(Ark_RichEditorController peer,
                              const Ark_ResourceStr* content,
                              const Opt_RichEditorTextSpanOptions* options)
    {
        return {};
    }
    Opt_Int32 AddImageSpanImpl(Ark_RichEditorController peer,
                               const Ark_Union_PixelMap_ResourceStr* value,
                               const Opt_RichEditorImageSpanOptions* options)
    {
        return {};
    }
    Opt_Int32 AddBuilderSpanImpl(Ark_RichEditorController peer,
                                 const CustomNodeBuilder* value,
                                 const Opt_RichEditorBuilderSpanOptions* options)
    {
        return {};
    }
    Opt_Int32 AddSymbolSpanImpl(Ark_RichEditorController peer,
                                const Ark_Resource* value,
                                const Opt_RichEditorSymbolSpanOptions* options)
    {
        return {};
    }
    void UpdateSpanStyleImpl(Ark_RichEditorController peer,
                             const Ark_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions* value)
    {
    }
    void UpdateParagraphStyleImpl(Ark_RichEditorController peer,
                                  const Ark_RichEditorParagraphStyleOptions* value)
    {
    }
    void DeleteSpansImpl(Ark_RichEditorController peer,
                         const Opt_RichEditorRange* value)
    {
    }
    Opt_Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult GetSpansImpl(Ark_RichEditorController peer,
                                                                                    const Opt_RichEditorRange* value)
    {
        return {};
    }
    Opt_Array_RichEditorParagraphResult GetParagraphsImpl(Ark_RichEditorController peer,
                                                          const Opt_RichEditorRange* value)
    {
        return {};
    }
    Opt_RichEditorSelection GetSelectionImpl(Ark_RichEditorController peer)
    {
        return {};
    }
    Opt_Array_RichEditorSpan FromStyledStringImpl(Ark_RichEditorController peer,
                                                  Ark_StyledString value)
    {
        return {};
    }
    Opt_StyledString ToStyledStringImpl(Ark_RichEditorController peer,
                                        const Ark_RichEditorRange* value)
    {
        return {};
    }
    } // RichEditorControllerAccessor
    namespace RichEditorStyledStringControllerAccessor {
    void DestroyPeerImpl(Ark_RichEditorStyledStringController peer)
    {
        auto peerImpl = reinterpret_cast<RichEditorStyledStringControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RichEditorStyledStringController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetStyledStringImpl(Ark_RichEditorStyledStringController peer,
                             Ark_StyledString styledString)
    {
    }
    Opt_MutableStyledString GetStyledStringImpl(Ark_RichEditorStyledStringController peer)
    {
        return {};
    }
    Opt_RichEditorRange GetSelectionImpl(Ark_RichEditorStyledStringController peer)
    {
        return {};
    }
    void OnContentChangedImpl(Ark_RichEditorStyledStringController peer,
                              const Ark_StyledStringChangedListener* listener)
    {
    }
    } // RichEditorStyledStringControllerAccessor
    namespace RotationGestureAccessor {
    void DestroyPeerImpl(Ark_RotationGesture peer)
    {
        auto peerImpl = reinterpret_cast<RotationGesturePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RotationGesture ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_RotationGesture $_instantiateImpl(const Callback_RotationGesture* factory,
                                          const Opt_RotationGestureHandlerOptions* value)
    {
        return {};
    }
    void OnActionStartImpl(Ark_RotationGesture peer,
                           const Callback_GestureEvent_Void* event)
    {
    }
    void OnActionUpdateImpl(Ark_RotationGesture peer,
                            const Callback_GestureEvent_Void* event)
    {
    }
    void OnActionEndImpl(Ark_RotationGesture peer,
                         const Callback_GestureEvent_Void* event)
    {
    }
    void OnActionCancelImpl(Ark_RotationGesture peer,
                            const Callback_GestureEvent_Void* event)
    {
    }
    } // RotationGestureAccessor
    namespace RotationGestureEventAccessor {
    void DestroyPeerImpl(Ark_RotationGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<RotationGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RotationGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetAngleImpl(Ark_RotationGestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_RotationGestureEvent peer,
                      Ark_Float64 angle)
    {
    }
    } // RotationGestureEventAccessor
    namespace RotationRecognizerAccessor {
    void DestroyPeerImpl(Ark_RotationRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<RotationRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RotationRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetAngleImpl(Ark_RotationRecognizer peer)
    {
        return {};
    }
    } // RotationRecognizerAccessor
    namespace RouterExtenderAccessor {
    Ark_NativePointer PushImpl(Ark_NativePointer jsView,
                               const Ark_String* url,
                               const Opt_Boolean* recover,
                               const Opt_RouterFinishCallback* finishCallback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer ReplaceImpl(Ark_NativePointer jsView,
                                  const Ark_String* url,
                                  const Opt_Boolean* recover,
                                  const Opt_RouterFinishCallback* enterFinishCallback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    void MoveCommonUnderPageNodeImpl(Ark_NativePointer commonNode,
                                     Ark_NativePointer pageNode)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void BackImpl()
    {
    }
    void BackWithOptionsImpl(const Ark_String* url,
                             const Opt_Object* params)
    {
    }
    Ark_NativePointer RunPageImpl(Ark_NativePointer jsView,
                                  const Ark_String* url,
                                  const Opt_Boolean* recover,
                                  const Opt_RouterFinishCallback* finishCallback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    void ClearImpl()
    {
    }
    void ShowAlertBeforeBackPageImpl(const Ark_String* message)
    {
    }
    void HideAlertBeforeBackPageImpl()
    {
    }
    void PushNamedRoute0Impl(Ark_VMContext vmContext,
                             Ark_AsyncWorkerPtr asyncWorker,
                             Ark_NativePointer jsView,
                             const Ark_PageRouterOptions* options,
                             const Opt_RouterFinishCallback* finishCallback,
                             const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PushNamedRoute1Impl(Ark_NativePointer jsView,
                             const Ark_PageRouterOptions* options,
                             const Opt_RouterFinishCallback* finishCallback,
                             const Opt_AsyncCallback_Void* callback_)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void ReplaceNamedRoute0Impl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_NativePointer jsView,
                                const Ark_PageRouterOptions* options,
                                const Opt_RouterFinishCallback* finishCallback,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ReplaceNamedRoute1Impl(Ark_NativePointer jsView,
                                const Ark_PageRouterOptions* options,
                                const Opt_RouterFinishCallback* finishCallback,
                                const Opt_AsyncCallback_Void* callback_)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    Ark_NativePointer CreateDynamicImpl(const Ark_String* url,
                                        const Opt_Boolean* recover)
    {
        return {};
    }
    Ark_NativePointer PushDynamicImpl(Ark_NativePointer pageNode,
                                      const Ark_String* url,
                                      const Opt_Boolean* recover,
                                      const Opt_RouterFinishCallback* finishCallback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer ReplaceDynamicImpl(Ark_NativePointer pageNode,
                                         const Ark_String* url,
                                         const Opt_Boolean* recover,
                                         const Opt_RouterFinishCallback* finishCallback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    } // RouterExtenderAccessor
    namespace ScaleSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_ScaleSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<ScaleSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScaleSymbolEffect ConstructImpl(const Opt_EffectScope* scope,
                                        const Opt_EffectDirection* direction)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EffectScope GetScopeImpl(Ark_ScaleSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_ScaleSymbolEffect peer,
                      const Opt_EffectScope* scope)
    {
    }
    Opt_EffectDirection GetDirectionImpl(Ark_ScaleSymbolEffect peer)
    {
        return {};
    }
    void SetDirectionImpl(Ark_ScaleSymbolEffect peer,
                          const Opt_EffectDirection* direction)
    {
    }
    } // ScaleSymbolEffectAccessor
    namespace ScreenCaptureHandlerAccessor {
    void DestroyPeerImpl(Ark_ScreenCaptureHandler peer)
    {
        auto peerImpl = reinterpret_cast<ScreenCaptureHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScreenCaptureHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetOriginImpl(Ark_ScreenCaptureHandler peer)
    {
        return {};
    }
    void GrantImpl(Ark_ScreenCaptureHandler peer,
                   const Ark_ScreenCaptureConfig* config)
    {
    }
    void DenyImpl(Ark_ScreenCaptureHandler peer)
    {
    }
    } // ScreenCaptureHandlerAccessor
    namespace ScreenshotServiceAccessor {
    Ark_Boolean RequestScreenshotImpl(const Ark_String* target,
                                      const Ark_String* name)
    {
        return {};
    }
    } // ScreenshotServiceAccessor
    namespace ScrollableTargetInfoAccessor {
    void DestroyPeerImpl(Ark_ScrollableTargetInfo peer)
    {
        auto peerImpl = reinterpret_cast<ScrollableTargetInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScrollableTargetInfo ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean IsBeginImpl(Ark_ScrollableTargetInfo peer)
    {
        return {};
    }
    Ark_Boolean IsEndImpl(Ark_ScrollableTargetInfo peer)
    {
        return {};
    }
    } // ScrollableTargetInfoAccessor
    namespace ScrollerAccessor {
    void DestroyPeerImpl(Ark_Scroller peer)
    {
        auto peerImpl = reinterpret_cast<ScrollerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Scroller ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ScrollToImpl(Ark_VMContext vmContext,
                      Ark_Scroller peer,
                      const Ark_ScrollOptions* options)
    {
    }
    void ScrollEdgeImpl(Ark_VMContext vmContext,
                        Ark_Scroller peer,
                        Ark_Edge value,
                        const Opt_ScrollEdgeOptions* options)
    {
    }
    void FlingImpl(Ark_VMContext vmContext,
                   Ark_Scroller peer,
                   Ark_Float64 velocity)
    {
    }
    void ScrollPageImpl(Ark_VMContext vmContext,
                        Ark_Scroller peer,
                        const Ark_ScrollPageOptions* value)
    {
    }
    Opt_OffsetResult CurrentOffsetImpl(Ark_VMContext vmContext,
                                       Ark_Scroller peer)
    {
        return {};
    }
    void ScrollToIndexImpl(Ark_VMContext vmContext,
                           Ark_Scroller peer,
                           Ark_Int32 value,
                           const Opt_Boolean* smooth,
                           const Opt_ScrollAlign* align,
                           const Opt_ScrollToIndexOptions* options)
    {
    }
    void ScrollByImpl(Ark_VMContext vmContext,
                      Ark_Scroller peer,
                      const Ark_Length* dx,
                      const Ark_Length* dy)
    {
    }
    Ark_Boolean IsAtEndImpl(Ark_VMContext vmContext,
                            Ark_Scroller peer)
    {
        return {};
    }
    Ark_RectResult GetItemRectImpl(Ark_VMContext vmContext,
                                   Ark_Scroller peer,
                                   Ark_Int32 index)
    {
        return {};
    }
    Ark_Int32 GetItemIndexImpl(Ark_VMContext vmContext,
                               Ark_Scroller peer,
                               Ark_Float64 x,
                               Ark_Float64 y)
    {
        return {};
    }
    } // ScrollerAccessor
    namespace ScrollMotionAccessor {
    void DestroyPeerImpl(Ark_ScrollMotion peer)
    {
        auto peerImpl = reinterpret_cast<ScrollMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScrollMotion ConstructImpl(const Ark_Number* position,
                                   const Ark_Number* velocity,
                                   const Ark_Number* min,
                                   const Ark_Number* max,
                                   Ark_SpringProp prop)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // ScrollMotionAccessor
    namespace ScrollResultAccessor {
    void DestroyPeerImpl(Ark_ScrollResult peer)
    {
        auto peerImpl = reinterpret_cast<ScrollResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScrollResult ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetOffsetRemainImpl(Ark_ScrollResult peer)
    {
        return {};
    }
    void SetOffsetRemainImpl(Ark_ScrollResult peer,
                             Ark_Float64 offsetRemain)
    {
    }
    } // ScrollResultAccessor
    namespace SearchControllerAccessor {
    void DestroyPeerImpl(Ark_SearchController peer)
    {
        auto peerImpl = reinterpret_cast<SearchControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SearchController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CaretPositionImpl(Ark_SearchController peer,
                           Ark_Int32 value)
    {
    }
    void StopEditingImpl(Ark_SearchController peer)
    {
    }
    void SetTextSelectionImpl(Ark_SearchController peer,
                              Ark_Int32 selectionStart,
                              Ark_Int32 selectionEnd,
                              const Opt_SelectionOptions* options)
    {
    }
    } // SearchControllerAccessor
    namespace SearchOpsAccessor {
    Ark_NativePointer RegisterSearchValueCallbackImpl(Ark_NativePointer node,
                                                      const Ark_String* value,
                                                      const SearchValueCallback* callback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    } // SearchOpsAccessor
    namespace SelectExtenderAccessor {
    void SetDividerImpl(Ark_NativePointer node,
                        const Opt_DividerOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // SelectExtenderAccessor
    namespace SliderExtenderAccessor {
    void SetPrefixImpl(Ark_NativePointer node,
                       Ark_NativePointer prefixNode,
                       const Opt_SliderPrefixOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetSuffixImpl(Ark_NativePointer node,
                       Ark_NativePointer suffixNode,
                       const Opt_SliderSuffixOptions* options)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // SliderExtenderAccessor
    namespace SpringMotionAccessor {
    void DestroyPeerImpl(Ark_SpringMotion peer)
    {
        auto peerImpl = reinterpret_cast<SpringMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SpringMotion ConstructImpl(const Ark_Number* start,
                                   const Ark_Number* end,
                                   const Ark_Number* velocity,
                                   Ark_SpringProp prop)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // SpringMotionAccessor
    namespace SpringPropAccessor {
    void DestroyPeerImpl(Ark_SpringProp peer)
    {
        auto peerImpl = reinterpret_cast<SpringPropPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SpringProp ConstructImpl(const Ark_Number* mass,
                                 const Ark_Number* stiffness,
                                 const Ark_Number* damping)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // SpringPropAccessor
    namespace SslErrorHandlerAccessor {
    void DestroyPeerImpl(Ark_SslErrorHandler peer)
    {
        auto peerImpl = reinterpret_cast<SslErrorHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SslErrorHandler ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void HandleConfirmImpl(Ark_SslErrorHandler peer)
    {
    }
    void HandleCancel0Impl(Ark_SslErrorHandler peer)
    {
    }
    void HandleCancel1Impl(Ark_SslErrorHandler peer,
                           Ark_Boolean abortLoading)
    {
    }
    } // SslErrorHandlerAccessor
    namespace StateStylesOpsAccessor {
    void OnStateStyleChangeImpl(Ark_NativePointer node,
                                const Callback_StateStylesChange* stateStyleChange,
                                Ark_Int32 allState)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // StateStylesOpsAccessor
    namespace StyledStringAccessor {
    void DestroyPeerImpl(Ark_StyledString peer)
    {
        auto peerImpl = reinterpret_cast<StyledStringPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_StyledString ConstructImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                                   const Opt_Array_StyleOptions* styles)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetStringImpl(Ark_StyledString peer)
    {
        return {};
    }
    Array_SpanStyle GetStylesImpl(Ark_StyledString peer,
                                  Ark_Int32 start,
                                  Ark_Int32 length,
                                  const Opt_StyledStringKey* styledKey)
    {
        return {};
    }
    Ark_Boolean EqualsImpl(Ark_StyledString peer,
                           Ark_StyledString other)
    {
        return {};
    }
    Ark_StyledString SubStyledStringImpl(Ark_StyledString peer,
                                         Ark_Int32 start,
                                         const Opt_Int32* length)
    {
        return {};
    }
    void FromHtmlImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      const Ark_String* html,
                      const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    Ark_String ToHtmlImpl(Ark_StyledString styledString)
    {
        return {};
    }
    Ark_Buffer Marshalling0Impl(Ark_StyledString styledString,
                                const StyledStringMarshallCallback* callback_)
    {
        return {};
    }
    void Unmarshalling0Impl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            const Ark_Buffer* buffer,
                            const StyledStringUnmarshallCallback* callback_,
                            const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    Ark_Buffer Marshalling1Impl(Ark_StyledString styledString)
    {
        return {};
    }
    void Unmarshalling1Impl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            const Ark_Buffer* buffer,
                            const Callback_Opt_StyledString_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    Ark_Int32 GetLengthImpl(Ark_StyledString peer)
    {
        return {};
    }
    void SetLengthImpl(Ark_StyledString peer,
                       Ark_Int32 length)
    {
    }
    } // StyledStringAccessor
    namespace StyledStringControllerAccessor {
    void DestroyPeerImpl(Ark_StyledStringController peer)
    {
        auto peerImpl = reinterpret_cast<StyledStringControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_StyledStringController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetStyledStringImpl(Ark_StyledStringController peer,
                             Ark_StyledString styledString)
    {
    }
    Opt_MutableStyledString GetStyledStringImpl(Ark_StyledStringController peer)
    {
        return {};
    }
    } // StyledStringControllerAccessor
    namespace SubmitEventAccessor {
    void DestroyPeerImpl(Ark_SubmitEvent peer)
    {
        auto peerImpl = reinterpret_cast<SubmitEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SubmitEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void KeepEditableStateImpl(Ark_SubmitEvent peer)
    {
    }
    Ark_String GetTextImpl(Ark_SubmitEvent peer)
    {
        return {};
    }
    void SetTextImpl(Ark_SubmitEvent peer,
                     const Ark_String* text)
    {
    }
    } // SubmitEventAccessor
    namespace SwipeGestureAccessor {
    void DestroyPeerImpl(Ark_SwipeGesture peer)
    {
        auto peerImpl = reinterpret_cast<SwipeGesturePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwipeGesture ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_SwipeGesture $_instantiateImpl(const Callback_SwipeGesture* factory,
                                       const Opt_SwipeGestureHandlerOptions* value)
    {
        return {};
    }
    void OnActionImpl(Ark_SwipeGesture peer,
                      const Callback_GestureEvent_Void* event)
    {
    }
    } // SwipeGestureAccessor
    namespace SwipeGestureEventAccessor {
    void DestroyPeerImpl(Ark_SwipeGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<SwipeGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwipeGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetAngleImpl(Ark_SwipeGestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_SwipeGestureEvent peer,
                      Ark_Float64 angle)
    {
    }
    Ark_Float64 GetSpeedImpl(Ark_SwipeGestureEvent peer)
    {
        return {};
    }
    void SetSpeedImpl(Ark_SwipeGestureEvent peer,
                      Ark_Float64 speed)
    {
    }
    } // SwipeGestureEventAccessor
    namespace SwiperContentTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_SwiperContentTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwiperContentTransitionProxy ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void FinishTransitionImpl(Ark_SwiperContentTransitionProxy peer)
    {
    }
    Ark_Int32 GetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer,
                              Ark_Int32 selectedIndex)
    {
    }
    Ark_Int32 GetIndexImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetIndexImpl(Ark_SwiperContentTransitionProxy peer,
                      Ark_Int32 index)
    {
    }
    Ark_Float64 GetPositionImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetPositionImpl(Ark_SwiperContentTransitionProxy peer,
                         Ark_Float64 position)
    {
    }
    Ark_Float64 GetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer,
                               Ark_Float64 mainAxisLength)
    {
    }
    } // SwiperContentTransitionProxyAccessor
    namespace SwiperControllerAccessor {
    void DestroyPeerImpl(Ark_SwiperController peer)
    {
        auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwiperController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ShowNextImpl(Ark_SwiperController peer)
    {
    }
    void ShowPreviousImpl(Ark_SwiperController peer)
    {
    }
    void ChangeIndexImpl(Ark_SwiperController peer,
                         const Opt_Number* index,
                         const Opt_Union_SwiperAnimationMode_Boolean* animationMode)
    {
    }
    void FinishAnimationImpl(Ark_SwiperController peer,
                             const Opt_VoidCallback* callback_)
    {
    }
    void PreloadItemsImpl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_SwiperController peer,
                          const Opt_Array_Number* indices,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    } // SwiperControllerAccessor
    namespace SwipeRecognizerAccessor {
    void DestroyPeerImpl(Ark_SwipeRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<SwipeRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwipeRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Float64 GetVelocityThresholdImpl(Ark_SwipeRecognizer peer)
    {
        return {};
    }
    Ark_SwipeDirection GetDirectionImpl(Ark_SwipeRecognizer peer)
    {
        return {};
    }
    } // SwipeRecognizerAccessor
    namespace SymbolEffectAccessor {
    void DestroyPeerImpl(Ark_SymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<SymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SymbolEffect ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // SymbolEffectAccessor
    namespace SystemOpsAccessor {
    Ark_NativePointer StartFrameImpl()
    {
        return {};
    }
    void EndFrameImpl(Ark_NativePointer root)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SyncInstanceIdImpl(Ark_Int32 instanceId)
    {
    }
    void RestoreInstanceIdImpl()
    {
    }
    Ark_Int32 GetResourceIdImpl(const Ark_String* bundleName,
                                const Ark_String* moduleName,
                                const Array_String* params)
    {
        return {};
    }
    void ResourceManagerResetImpl()
    {
    }
    void SetFrameCallbackImpl(const Callback_Number_Void* onFrameCallback,
                              const Callback_Number_Void* onIdleCallback,
                              const Ark_Number* delayTime)
    {
    }
    Array_Number ColorMetricsResourceColorImpl(const Ark_Resource* color)
    {
        return {};
    }
    Ark_LengthMetricsCustom ResoureToLengthMetricsImpl(const Ark_Resource* res)
    {
        return {};
    }
    } // SystemOpsAccessor
    namespace TabBarSymbolAccessor {
    void DestroyPeerImpl(Ark_TabBarSymbol peer)
    {
        auto peerImpl = reinterpret_cast<TabBarSymbolPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TabBarSymbol ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_SymbolGlyphModifier GetNormalImpl(Ark_TabBarSymbol peer)
    {
        return {};
    }
    void SetNormalImpl(Ark_TabBarSymbol peer,
                       Ark_SymbolGlyphModifier normal)
    {
    }
    Opt_SymbolGlyphModifier GetSelectedImpl(Ark_TabBarSymbol peer)
    {
        return {};
    }
    void SetSelectedImpl(Ark_TabBarSymbol peer,
                         const Opt_SymbolGlyphModifier* selected)
    {
    }
    } // TabBarSymbolAccessor
    namespace TabContentTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_TabContentTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<TabContentTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TabContentTransitionProxy ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void FinishTransitionImpl(Ark_TabContentTransitionProxy peer)
    {
    }
    Ark_Int32 GetFromImpl(Ark_TabContentTransitionProxy peer)
    {
        return {};
    }
    void SetFromImpl(Ark_TabContentTransitionProxy peer,
                     const Ark_Int32 from)
    {
    }
    Ark_Int32 GetToImpl(Ark_TabContentTransitionProxy peer)
    {
        return {};
    }
    void SetToImpl(Ark_TabContentTransitionProxy peer,
                   const Ark_Int32 to)
    {
    }
    } // TabContentTransitionProxyAccessor
    namespace TabsControllerAccessor {
    void DestroyPeerImpl(Ark_TabsController peer)
    {
        auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TabsController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ChangeIndexImpl(Ark_TabsController peer,
                         const Ark_Int32 value)
    {
    }
    void PreloadItemsImpl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_TabsController peer,
                          const Opt_Array_Int32* indices,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void SetTabBarTranslateImpl(Ark_TabsController peer,
                                const Ark_TranslateOptions* translate)
    {
    }
    void SetTabBarOpacityImpl(Ark_TabsController peer,
                              const Ark_Float64 opacity)
    {
    }
    } // TabsControllerAccessor
    namespace TabsExtenderAccessor {
    void ApplyAttributesFinishImpl(Ark_NativePointer node)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // TabsExtenderAccessor
    namespace TapGestureEventAccessor {
    void DestroyPeerImpl(Ark_TapGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<TapGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TapGestureEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_EventLocationInfo GetTapLocationImpl(Ark_TapGestureEvent peer)
    {
        return {};
    }
    } // TapGestureEventAccessor
    namespace TapRecognizerAccessor {
    void DestroyPeerImpl(Ark_TapRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<TapRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TapRecognizer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Int32 GetTapCountImpl(Ark_TapRecognizer peer)
    {
        return {};
    }
    } // TapRecognizerAccessor
    namespace TextAreaControllerAccessor {
    void DestroyPeerImpl(Ark_TextAreaController peer)
    {
        auto peerImpl = reinterpret_cast<TextAreaControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextAreaController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CaretPositionImpl(Ark_TextAreaController peer,
                           Ark_Int32 value)
    {
    }
    void SetTextSelectionImpl(Ark_TextAreaController peer,
                              Ark_Int32 selectionStart,
                              Ark_Int32 selectionEnd,
                              const Opt_SelectionOptions* options)
    {
    }
    void StopEditingImpl(Ark_TextAreaController peer)
    {
    }
    } // TextAreaControllerAccessor
    namespace TextBaseControllerAccessor {
    void DestroyPeerImpl(Ark_TextBaseController peer)
    {
        auto peerImpl = reinterpret_cast<TextBaseControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextBaseController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetSelectionImpl(Ark_TextBaseController peer,
                          const Ark_Number* selectionStart,
                          const Ark_Number* selectionEnd,
                          const Opt_SelectionOptions* options)
    {
    }
    void CloseSelectionMenuImpl(Ark_TextBaseController peer)
    {
    }
    Opt_LayoutManager GetLayoutManagerImpl(Ark_TextBaseController peer)
    {
        return {};
    }
    } // TextBaseControllerAccessor
    namespace TextClockControllerAccessor {
    void DestroyPeerImpl(Ark_TextClockController peer)
    {
        auto peerImpl = reinterpret_cast<TextClockControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextClockController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void StartImpl(Ark_TextClockController peer)
    {
    }
    void StopImpl(Ark_TextClockController peer)
    {
    }
    } // TextClockControllerAccessor
    namespace TextContentControllerBaseAccessor {
    void DestroyPeerImpl(Ark_TextContentControllerBase peer)
    {
        auto peerImpl = reinterpret_cast<TextContentControllerBasePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextContentControllerBase ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CaretOffset GetCaretOffsetImpl(Ark_TextContentControllerBase peer)
    {
        return {};
    }
    Ark_RectResult GetTextContentRectImpl(Ark_TextContentControllerBase peer)
    {
        return {};
    }
    Ark_Int32 GetTextContentLineCountImpl(Ark_TextContentControllerBase peer)
    {
        return {};
    }
    Ark_Int32 AddTextImpl(Ark_TextContentControllerBase peer,
                          const Ark_String* text,
                          const Opt_TextContentControllerOptions* textOperationOptions)
    {
        return {};
    }
    void DeleteTextImpl(Ark_TextContentControllerBase peer,
                        const Opt_TextRange* range)
    {
    }
    Ark_TextRange GetSelectionImpl(Ark_TextContentControllerBase peer)
    {
        return {};
    }
    void ClearPreviewTextImpl(Ark_TextContentControllerBase peer)
    {
    }
    Ark_String GetTextImpl(Ark_TextContentControllerBase peer,
                           const Opt_TextRange* range)
    {
        return {};
    }
    void DeleteBackwardImpl(Ark_TextContentControllerBase peer)
    {
    }
    } // TextContentControllerBaseAccessor
    namespace TextControllerAccessor {
    void DestroyPeerImpl(Ark_TextController peer)
    {
        auto peerImpl = reinterpret_cast<TextControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CloseSelectionMenuImpl(Ark_TextController peer)
    {
    }
    void SetStyledStringImpl(Ark_TextController peer,
                             Ark_StyledString value)
    {
    }
    Ark_LayoutManager GetLayoutManagerImpl(Ark_TextController peer)
    {
        return {};
    }
    void SetTextSelectionImpl(Ark_TextController peer,
                              const Opt_Int32* selectionStart,
                              const Opt_Int32* selectionEnd,
                              const Opt_SelectionOptions* options)
    {
    }
    } // TextControllerAccessor
    namespace TextEditControllerExAccessor {
    void DestroyPeerImpl(Ark_TextEditControllerEx peer)
    {
        auto peerImpl = reinterpret_cast<TextEditControllerExPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextEditControllerEx ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Boolean IsEditingImpl(Ark_TextEditControllerEx peer)
    {
        return {};
    }
    void StopEditingImpl(Ark_TextEditControllerEx peer)
    {
    }
    Opt_Boolean SetCaretOffsetImpl(Ark_TextEditControllerEx peer,
                                   const Ark_Number* offset)
    {
        return {};
    }
    Opt_Number GetCaretOffsetImpl(Ark_TextEditControllerEx peer)
    {
        return {};
    }
    Opt_PreviewText GetPreviewTextImpl(Ark_TextEditControllerEx peer)
    {
        return {};
    }
    } // TextEditControllerExAccessor
    namespace TextFieldOpsAccessor {
    Ark_NativePointer RegisterTextFieldValueCallbackImpl(Ark_NativePointer node,
                                                         const Ark_ResourceStr* value,
                                                         const TextFieldValueCallback* callback)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetWidthImpl(Ark_NativePointer node,
                                               const Opt_Union_Length_LayoutPolicy* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetHeightImpl(Ark_NativePointer node,
                                                const Opt_Union_Length_LayoutPolicy* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetPaddingImpl(Ark_NativePointer node,
                                                 const Opt_Union_Padding_Length_LocalizedPadding* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetMarginImpl(Ark_NativePointer node,
                                                const Opt_Union_Padding_Length_LocalizedPadding* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBorderImpl(Ark_NativePointer node,
                                                const Opt_BorderOptions* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBorderWidthImpl(Ark_NativePointer node,
                                                     const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBorderColorImpl(Ark_NativePointer node,
                                                     const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBorderStyleImpl(Ark_NativePointer node,
                                                     const Opt_Union_BorderStyle_EdgeStyles* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBorderRadiusImpl(Ark_NativePointer node,
                                                      const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    Ark_NativePointer TextFieldOpsSetBackgroundColorImpl(Ark_NativePointer node,
                                                         const Opt_ResourceColor* value)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
        return {};
    }
    } // TextFieldOpsAccessor
    namespace TextInputControllerAccessor {
    void DestroyPeerImpl(Ark_TextInputController peer)
    {
        auto peerImpl = reinterpret_cast<TextInputControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextInputController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CaretPositionImpl(Ark_TextInputController peer,
                           Ark_Int32 value)
    {
    }
    void SetTextSelectionImpl(Ark_TextInputController peer,
                              Ark_Int32 selectionStart,
                              Ark_Int32 selectionEnd,
                              const Opt_SelectionOptions* options)
    {
    }
    void StopEditingImpl(Ark_TextInputController peer)
    {
    }
    } // TextInputControllerAccessor
    namespace TextMenuItemIdAccessor {
    void DestroyPeerImpl(Ark_TextMenuItemId peer)
    {
        auto peerImpl = reinterpret_cast<TextMenuItemIdPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextMenuItemId ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TextMenuItemId OfImpl(const Ark_ResourceStr* id)
    {
        return {};
    }
    Ark_Boolean EqualsImpl(Ark_TextMenuItemId peer,
                           Ark_TextMenuItemId id)
    {
        return {};
    }
    Ark_TextMenuItemId GetCUTImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetCOPYImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetPASTEImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetSELECT_ALLImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetCOLLABORATION_SERVICEImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetCAMERA_INPUTImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetAI_WRITERImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetTRANSLATEImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetSEARCHImpl()
    {
        return {};
    }
    Ark_TextMenuItemId GetSHAREImpl()
    {
        return {};
    }
    } // TextMenuItemIdAccessor
    namespace TextPickerDialogAccessor {
    void DestroyPeerImpl(Ark_TextPickerDialog peer)
    {
        auto peerImpl = reinterpret_cast<TextPickerDialogPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextPickerDialog ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // TextPickerDialogAccessor
    namespace TextShadowStyleAccessor {
    void DestroyPeerImpl(Ark_TextShadowStyle peer)
    {
        auto peerImpl = reinterpret_cast<TextShadowStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextShadowStyle ConstructImpl(const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Array_ShadowOptions GetTextShadowImpl(Ark_TextShadowStyle peer)
    {
        return {};
    }
    } // TextShadowStyleAccessor
    namespace TextStyleAccessor {
    void DestroyPeerImpl(Ark_TextStyle peer)
    {
        auto peerImpl = reinterpret_cast<TextStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextStyle ConstructImpl(const Opt_TextStyleInterface* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_ResourceColor GetFontColorImpl(Ark_TextStyle peer)
    {
        return {};
    }
    Opt_String GetFontFamilyImpl(Ark_TextStyle peer)
    {
        return {};
    }
    Opt_Float64 GetFontSizeImpl(Ark_TextStyle peer)
    {
        return {};
    }
    Opt_Int32 GetFontWeightImpl(Ark_TextStyle peer)
    {
        return {};
    }
    Opt_FontStyle GetFontStyleImpl(Ark_TextStyle peer)
    {
        return {};
    }
    } // TextStyleAccessor
    namespace TextTimerControllerAccessor {
    void DestroyPeerImpl(Ark_TextTimerController peer)
    {
        auto peerImpl = reinterpret_cast<TextTimerControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextTimerController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void StartImpl(Ark_TextTimerController peer)
    {
    }
    void PauseImpl(Ark_TextTimerController peer)
    {
    }
    void ResetImpl(Ark_TextTimerController peer)
    {
    }
    } // TextTimerControllerAccessor
    namespace ThemeOpsAccessor {
    void SendThemeToNativeImpl(const Array_ResourceColor* colorArray,
                               Ark_Int32 elmtId)
    {
    }
    void SetDefaultThemeImpl(const Array_ResourceColor* colorArray,
                             Ark_Boolean isDark)
    {
    }
    } // ThemeOpsAccessor
    namespace TimePickerDialogAccessor {
    void DestroyPeerImpl(Ark_TimePickerDialog peer)
    {
        auto peerImpl = reinterpret_cast<TimePickerDialogPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TimePickerDialog ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // TimePickerDialogAccessor
    namespace TouchEventAccessor {
    void DestroyPeerImpl(Ark_TouchEvent peer)
    {
        auto peerImpl = reinterpret_cast<TouchEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TouchEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Opt_Array_HistoricalPoint GetHistoricalPointsImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    Ark_TouchType GetTypeImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    void SetTypeImpl(Ark_TouchEvent peer,
                     Ark_TouchType type)
    {
    }
    Array_TouchObject GetTouchesImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    void SetTouchesImpl(Ark_TouchEvent peer,
                        const Array_TouchObject* touches)
    {
    }
    Array_TouchObject GetChangedTouchesImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    void SetChangedTouchesImpl(Ark_TouchEvent peer,
                               const Array_TouchObject* changedTouches)
    {
    }
    void StopPropagationImpl(Ark_TouchEvent peer)
    {
    }
    void PreventDefaultImpl(Ark_TouchEvent peer)
    {
    }
    } // TouchEventAccessor
    namespace TransitionEffectAccessor {
    void DestroyPeerImpl(Ark_TransitionEffect peer)
    {
        auto peerImpl = reinterpret_cast<TransitionEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TransitionEffect Construct0Impl(const Ark_String* type)
    {
        return {};
    }
    Ark_TransitionEffect Construct1Impl(Ark_Float64 effect)
    {
        return {};
    }
    Ark_TransitionEffect Construct2Impl(Ark_TransitionEdge effect)
    {
        return {};
    }
    Ark_TransitionEffect Construct3Impl(const Ark_TranslateOptions* effect)
    {
        return {};
    }
    Ark_TransitionEffect Construct4Impl(const Ark_RotateOptions* effect)
    {
        return {};
    }
    Ark_TransitionEffect Construct5Impl(const Ark_ScaleOptions* effect)
    {
        return {};
    }
    Ark_TransitionEffect Construct6Impl(const Ark_AsymmetricTransitionOption* effect)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TransitionEffect TranslateImpl(const Ark_TranslateOptions* options)
    {
        return {};
    }
    Ark_TransitionEffect RotateImpl(const Ark_RotateOptions* options)
    {
        return {};
    }
    Ark_TransitionEffect ScaleImpl(const Ark_ScaleOptions* options)
    {
        return {};
    }
    Ark_TransitionEffect OpacityImpl(Ark_Float64 alpha)
    {
        return {};
    }
    Ark_TransitionEffect MoveImpl(Ark_TransitionEdge edge)
    {
        return {};
    }
    Ark_TransitionEffect AsymmetricImpl(Ark_TransitionEffect appear,
                                        Ark_TransitionEffect disappear)
    {
        return {};
    }
    Ark_TransitionEffect AnimationImpl(Ark_TransitionEffect peer,
                                       const Ark_AnimateParam* value)
    {
        return {};
    }
    Ark_TransitionEffect CombineImpl(Ark_TransitionEffect peer,
                                     Ark_TransitionEffect transitionEffect)
    {
        return {};
    }
    Ark_TransitionEffect GetIDENTITYImpl()
    {
        return {};
    }
    void SetIDENTITYImpl(Ark_TransitionEffect IDENTITY)
    {
    }
    Ark_TransitionEffect GetOPACITYImpl()
    {
        return {};
    }
    void SetOPACITYImpl(Ark_TransitionEffect OPACITY)
    {
    }
    Ark_TransitionEffect GetSLIDEImpl()
    {
        return {};
    }
    void SetSLIDEImpl(Ark_TransitionEffect SLIDE)
    {
    }
    Ark_TransitionEffect GetSLIDE_SWITCHImpl()
    {
        return {};
    }
    void SetSLIDE_SWITCHImpl(Ark_TransitionEffect SLIDE_SWITCH)
    {
    }
    } // TransitionEffectAccessor
    namespace UICommonEventAccessor {
    void DestroyPeerImpl(Ark_UICommonEvent peer)
    {
        auto peerImpl = reinterpret_cast<UICommonEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UICommonEvent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetOnClickImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_ClickEvent_Void* callback_)
    {
    }
    void SetOnTouchImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_TouchEvent_Void* callback_)
    {
    }
    void SetOnAppearImpl(Ark_UICommonEvent peer,
                         const Opt_Callback_Void* callback_)
    {
    }
    void SetOnDisappearImpl(Ark_UICommonEvent peer,
                            const Opt_Callback_Void* callback_)
    {
    }
    void SetOnKeyEventImpl(Ark_UICommonEvent peer,
                           const Opt_Callback_KeyEvent_Void* callback_)
    {
    }
    void SetOnFocusImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_Void* callback_)
    {
    }
    void SetOnBlurImpl(Ark_UICommonEvent peer,
                       const Opt_Callback_Void* callback_)
    {
    }
    void SetOnHoverImpl(Ark_UICommonEvent peer,
                        const Opt_HoverCallback* callback_)
    {
    }
    void SetOnMouseImpl(Ark_UICommonEvent peer,
                        const Opt_Callback_MouseEvent_Void* callback_)
    {
    }
    void SetOnSizeChangeImpl(Ark_UICommonEvent peer,
                             const Opt_SizeChangeCallback* callback_)
    {
    }
    void SetOnVisibleAreaApproximateChangeImpl(Ark_UICommonEvent peer,
                                               const Ark_VisibleAreaEventOptions* options,
                                               const Opt_VisibleAreaChangeCallback* event)
    {
    }
    } // UICommonEventAccessor
    namespace UIContextAtomicServiceBarAccessor {
    Ark_Frame GetBarRectImpl()
    {
        return {};
    }
    } // UIContextAtomicServiceBarAccessor
    namespace UIExtensionProxyAccessor {
    void DestroyPeerImpl(Ark_UIExtensionProxy peer)
    {
        auto peerImpl = reinterpret_cast<UIExtensionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UIExtensionProxy ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SendImpl(Ark_UIExtensionProxy peer,
                  const Map_String_Opt_Object* data)
    {
    }
    Map_String_Opt_Object SendSyncImpl(Ark_UIExtensionProxy peer,
                                       const Map_String_Opt_Object* data)
    {
        return {};
    }
    void OnAsyncReceiverRegisterAsyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                                          const Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OnSyncReceiverRegisterSyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                                        const Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OffAsyncReceiverRegisterAsyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                                           const Opt_Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OffSyncReceiverRegisterSyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                                         const Opt_Callback_UIExtensionProxy_Void* callback_)
    {
    }
    } // UIExtensionProxyAccessor
    namespace UrlStyleAccessor {
    void DestroyPeerImpl(Ark_UrlStyle peer)
    {
        auto peerImpl = reinterpret_cast<UrlStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UrlStyle ConstructImpl(const Ark_String* url)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetUrlImpl(Ark_UrlStyle peer)
    {
        return {};
    }
    } // UrlStyleAccessor
    namespace VideoControllerAccessor {
    void DestroyPeerImpl(Ark_VideoController peer)
    {
        auto peerImpl = reinterpret_cast<VideoControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_VideoController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void StartImpl(Ark_VideoController peer)
    {
    }
    void PauseImpl(Ark_VideoController peer)
    {
    }
    void StopImpl(Ark_VideoController peer)
    {
    }
    void RequestFullscreenImpl(Ark_VideoController peer,
                               Ark_Boolean value)
    {
    }
    void ExitFullscreenImpl(Ark_VideoController peer)
    {
    }
    void SetCurrentTimeDefaultImpl(Ark_VideoController peer,
                                   Ark_Float64 value)
    {
    }
    void SetCurrentTimeWithModeImpl(Ark_VideoController peer,
                                    Ark_Float64 value,
                                    Ark_SeekMode seekMode)
    {
    }
    void ResetImpl(Ark_VideoController peer)
    {
    }
    } // VideoControllerAccessor
    namespace WaterFlowSectionsAccessor {
    void DestroyPeerImpl(Ark_WaterFlowSections peer)
    {
        auto peerImpl = reinterpret_cast<WaterFlowSectionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WaterFlowSections ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean SpliceImpl(Ark_WaterFlowSections peer,
                           Ark_Int32 start,
                           const Opt_Int32* deleteCount,
                           const Opt_Array_SectionOptions* sections)
    {
        return {};
    }
    Ark_Boolean PushImpl(Ark_WaterFlowSections peer,
                         const Ark_SectionOptions* section)
    {
        return {};
    }
    Ark_Boolean UpdateImpl(Ark_WaterFlowSections peer,
                           Ark_Int32 sectionIndex,
                           const Ark_SectionOptions* section)
    {
        return {};
    }
    Array_SectionOptions ValuesImpl(Ark_WaterFlowSections peer)
    {
        return {};
    }
    Ark_Int32 LengthImpl(Ark_WaterFlowSections peer)
    {
        return {};
    }
    } // WaterFlowSectionsAccessor
    namespace WebContextMenuParamAccessor {
    void DestroyPeerImpl(Ark_WebContextMenuParam peer)
    {
        auto peerImpl = reinterpret_cast<WebContextMenuParamPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebContextMenuParam ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Int32 XImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Int32 YImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_String GetLinkUrlImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_String GetUnfilteredLinkUrlImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_String GetSourceUrlImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Boolean ExistsImageContentsImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_ContextMenuMediaType GetMediaTypeImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_String GetSelectionTextImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_ContextMenuSourceType GetSourceTypeImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_ContextMenuInputFieldType GetInputFieldTypeImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Boolean IsEditableImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Int32 GetEditStateFlagsImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Int32 GetPreviewWidthImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Int32 GetPreviewHeightImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_ContextMenuDataMediaType GetContextMenuMediaTypeImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    } // WebContextMenuParamAccessor
    namespace WebContextMenuResultAccessor {
    void DestroyPeerImpl(Ark_WebContextMenuResult peer)
    {
        auto peerImpl = reinterpret_cast<WebContextMenuResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebContextMenuResult ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void CloseContextMenuImpl(Ark_WebContextMenuResult peer)
    {
    }
    void CopyImageImpl(Ark_WebContextMenuResult peer)
    {
    }
    void CopyImpl(Ark_WebContextMenuResult peer)
    {
    }
    void PasteImpl(Ark_WebContextMenuResult peer)
    {
    }
    void CutImpl(Ark_WebContextMenuResult peer)
    {
    }
    void SelectAllImpl(Ark_WebContextMenuResult peer)
    {
    }
    void RedoImpl(Ark_WebContextMenuResult peer)
    {
    }
    void UndoImpl(Ark_WebContextMenuResult peer)
    {
    }
    void PasteAndMatchStyleImpl(Ark_WebContextMenuResult peer)
    {
    }
    } // WebContextMenuResultAccessor
    namespace WebKeyboardControllerAccessor {
    void DestroyPeerImpl(Ark_WebKeyboardController peer)
    {
        auto peerImpl = reinterpret_cast<WebKeyboardControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebKeyboardController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InsertTextImpl(Ark_WebKeyboardController peer,
                        const Ark_String* text)
    {
    }
    void DeleteForwardImpl(Ark_WebKeyboardController peer,
                           Ark_Int32 length)
    {
    }
    void DeleteBackwardImpl(Ark_WebKeyboardController peer,
                            Ark_Int32 length)
    {
    }
    void SendFunctionKeyImpl(Ark_WebKeyboardController peer,
                             Ark_Int32 key)
    {
    }
    void CloseImpl(Ark_WebKeyboardController peer)
    {
    }
    } // WebKeyboardControllerAccessor
    namespace WebResourceErrorAccessor {
    void DestroyPeerImpl(Ark_WebResourceError peer)
    {
        auto peerImpl = reinterpret_cast<WebResourceErrorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebResourceError ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetErrorInfoImpl(Ark_WebResourceError peer)
    {
        return {};
    }
    Ark_Int32 GetErrorCodeImpl(Ark_WebResourceError peer)
    {
        return {};
    }
    } // WebResourceErrorAccessor
    namespace WebResourceRequestAccessor {
    void DestroyPeerImpl(Ark_WebResourceRequest peer)
    {
        auto peerImpl = reinterpret_cast<WebResourceRequestPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebResourceRequest ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Array_Header GetRequestHeaderImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    Ark_String GetRequestUrlImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    Ark_Boolean IsRequestGestureImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    Ark_Boolean IsMainFrameImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    Ark_Boolean IsRedirectImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    Ark_String GetRequestMethodImpl(Ark_WebResourceRequest peer)
    {
        return {};
    }
    } // WebResourceRequestAccessor
    namespace WebResourceResponseAccessor {
    void DestroyPeerImpl(Ark_WebResourceResponse peer)
    {
        auto peerImpl = reinterpret_cast<WebResourceResponsePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebResourceResponse ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetResponseDataImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Opt_Union_String_I32_Buffer_Resource GetResponseDataExImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Ark_String GetResponseEncodingImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Ark_String GetResponseMimeTypeImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Ark_String GetReasonMessageImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Array_Header GetResponseHeaderImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    Ark_Int32 GetResponseCodeImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    void SetResponseDataImpl(Ark_WebResourceResponse peer,
                             const Ark_Union_String_I32_Resource_Buffer* data)
    {
    }
    void SetResponseEncodingImpl(Ark_WebResourceResponse peer,
                                 const Ark_String* encoding)
    {
    }
    void SetResponseMimeTypeImpl(Ark_WebResourceResponse peer,
                                 const Ark_String* mimeType)
    {
    }
    void SetReasonMessageImpl(Ark_WebResourceResponse peer,
                              const Ark_String* reason)
    {
    }
    void SetResponseHeaderImpl(Ark_WebResourceResponse peer,
                               const Array_Header* header)
    {
    }
    void SetResponseCodeImpl(Ark_WebResourceResponse peer,
                             Ark_Int32 code)
    {
    }
    void SetResponseIsReadyImpl(Ark_WebResourceResponse peer,
                                Ark_Boolean IsReady)
    {
    }
    Ark_Boolean GetResponseIsReadyImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    } // WebResourceResponseAccessor
    namespace XComponentControllerAccessor {
    void DestroyPeerImpl(Ark_XComponentController peer)
    {
        auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_XComponentController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetXComponentSurfaceRectImpl(Ark_XComponentController peer,
                                      const Ark_SurfaceRect* rect)
    {
    }
    Ark_SurfaceRect GetXComponentSurfaceRectImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetXComponentSurfaceRotationImpl(Ark_XComponentController peer,
                                          const Ark_SurfaceRotationOptions* rotationOptions)
    {
    }
    Ark_SurfaceRotationOptions GetXComponentSurfaceRotationImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void StartImageAnalyzerImpl(Ark_VMContext vmContext,
                                Ark_AsyncWorkerPtr asyncWorker,
                                Ark_XComponentController peer,
                                const Ark_ImageAnalyzerConfig* config,
                                const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void StopImageAnalyzerImpl(Ark_XComponentController peer)
    {
    }
    Callback_String_Void GetOnSurfaceCreatedImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetOnSurfaceCreatedImpl(Ark_XComponentController peer,
                                 const Callback_String_Void* onSurfaceCreated)
    {
    }
    Callback_String_SurfaceRect_Void GetOnSurfaceChangedImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetOnSurfaceChangedImpl(Ark_XComponentController peer,
                                 const Callback_String_SurfaceRect_Void* onSurfaceChanged)
    {
    }
    Callback_String_Void GetOnSurfaceDestroyedImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetOnSurfaceDestroyedImpl(Ark_XComponentController peer,
                                   const Callback_String_Void* onSurfaceDestroyed)
    {
    }
    } // XComponentControllerAccessor
    namespace GlobalScopeAccessor {
    Ark_Resource $rImpl(const Ark_String* value,
                        const Array_Opt_Object* params)
    {
        return {};
    }
    Ark_Resource $rawfileImpl(const Ark_String* value)
    {
        return {};
    }
    void AnimateToImpl(const Ark_AnimateParam* value,
                       const Callback_Void* event)
    {
    }
    void AnimateToImmediatelyImpl(const Ark_AnimateParam* value,
                                  const Callback_Void* event)
    {
    }
    void CursorControl_restoreDefaultImpl()
    {
    }
    void CursorControl_setCursorImpl(Ark_pointer_PointerStyle value)
    {
    }
    Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
    {
        return {};
    }
    Ark_ComponentInfo GetRectangleByIdImpl(const Ark_String* id)
    {
        return {};
    }
    void PostCardActionImpl(const Ark_Object* component,
                            const Ark_Object* action)
    {
    }
    void Profiler_registerVsyncCallbackImpl(const Profiler_Callback_String_Void* callback_)
    {
    }
    void Profiler_unregisterVsyncCallbackImpl()
    {
    }
    Ark_Number Px2vpImpl(const Ark_Number* value)
    {
        return {};
    }
    void SetAppBgColorImpl(const Ark_String* value)
    {
    }
    Ark_Number Vp2pxImpl(const Ark_Number* value)
    {
        return {};
    }
    } // GlobalScopeAccessor
    const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor()
    {
        static const GENERATED_ArkUIAccessibilityHoverEventAccessor AccessibilityHoverEventAccessorImpl {
            AccessibilityHoverEventAccessor::DestroyPeerImpl,
            AccessibilityHoverEventAccessor::ConstructImpl,
            AccessibilityHoverEventAccessor::GetFinalizerImpl,
            AccessibilityHoverEventAccessor::GetTypeImpl,
            AccessibilityHoverEventAccessor::SetTypeImpl,
            AccessibilityHoverEventAccessor::GetXImpl,
            AccessibilityHoverEventAccessor::SetXImpl,
            AccessibilityHoverEventAccessor::GetYImpl,
            AccessibilityHoverEventAccessor::SetYImpl,
            AccessibilityHoverEventAccessor::GetDisplayXImpl,
            AccessibilityHoverEventAccessor::SetDisplayXImpl,
            AccessibilityHoverEventAccessor::GetDisplayYImpl,
            AccessibilityHoverEventAccessor::SetDisplayYImpl,
            AccessibilityHoverEventAccessor::GetWindowXImpl,
            AccessibilityHoverEventAccessor::SetWindowXImpl,
            AccessibilityHoverEventAccessor::GetWindowYImpl,
            AccessibilityHoverEventAccessor::SetWindowYImpl,
        };
        return &AccessibilityHoverEventAccessorImpl;
    }

    struct AccessibilityHoverEventPeer {
        virtual ~AccessibilityHoverEventPeer() = default;
    };
    const GENERATED_ArkUIActionSheetAccessor* GetActionSheetAccessor()
    {
        static const GENERATED_ArkUIActionSheetAccessor ActionSheetAccessorImpl {
            ActionSheetAccessor::ShowImpl,
        };
        return &ActionSheetAccessorImpl;
    }

    const GENERATED_ArkUIAlertDialogAccessor* GetAlertDialogAccessor()
    {
        static const GENERATED_ArkUIAlertDialogAccessor AlertDialogAccessorImpl {
            AlertDialogAccessor::ShowImpl,
        };
        return &AlertDialogAccessorImpl;
    }

    const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
    {
        static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
            AnimationExtenderAccessor::SetClipRectImpl,
            AnimationExtenderAccessor::OpenImplicitAnimationImpl,
            AnimationExtenderAccessor::CloseImplicitAnimationImpl,
            AnimationExtenderAccessor::StartDoubleAnimationImpl,
            AnimationExtenderAccessor::AnimationTranslateImpl,
            AnimationExtenderAccessor::AnimateToImmediatelyImplImpl,
            AnimationExtenderAccessor::KeyframeAnimationImplImpl,
        };
        return &AnimationExtenderAccessorImpl;
    }

    const GENERATED_ArkUIAppearSymbolEffectAccessor* GetAppearSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIAppearSymbolEffectAccessor AppearSymbolEffectAccessorImpl {
            AppearSymbolEffectAccessor::DestroyPeerImpl,
            AppearSymbolEffectAccessor::ConstructImpl,
            AppearSymbolEffectAccessor::GetFinalizerImpl,
            AppearSymbolEffectAccessor::GetScopeImpl,
            AppearSymbolEffectAccessor::SetScopeImpl,
        };
        return &AppearSymbolEffectAccessorImpl;
    }

    struct AppearSymbolEffectPeer {
        virtual ~AppearSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIArcListExtenderAccessor* GetArcListExtenderAccessor()
    {
        static const GENERATED_ArkUIArcListExtenderAccessor ArcListExtenderAccessorImpl {
            ArcListExtenderAccessor::ConstructorImpl,
            ArcListExtenderAccessor::SetArkListOptionsImpl,
            ArcListExtenderAccessor::DigitalCrownSensitivityImpl,
            ArcListExtenderAccessor::SpaceImpl,
            ArcListExtenderAccessor::ScrollBarImpl,
            ArcListExtenderAccessor::ScrollBarColorImpl,
            ArcListExtenderAccessor::ScrollBarWidthImpl,
            ArcListExtenderAccessor::CachedCountImpl,
            ArcListExtenderAccessor::ChainAnimationImpl,
            ArcListExtenderAccessor::ChildrenMainSizeImpl,
            ArcListExtenderAccessor::EnableScrollInteractionImpl,
            ArcListExtenderAccessor::FadingEdgeImpl,
            ArcListExtenderAccessor::FrictionImpl,
            ArcListExtenderAccessor::FlingSpeedLimitImpl,
            ArcListExtenderAccessor::OnScrollIndexImpl,
            ArcListExtenderAccessor::OnReachStartImpl,
            ArcListExtenderAccessor::OnReachEndImpl,
            ArcListExtenderAccessor::OnScrollStartImpl,
            ArcListExtenderAccessor::OnScrollStopImpl,
            ArcListExtenderAccessor::OnWillScrollImpl,
            ArcListExtenderAccessor::OnDidScrollImpl,
        };
        return &ArcListExtenderAccessorImpl;
    }

    const GENERATED_ArkUIArcListItemExtenderAccessor* GetArcListItemExtenderAccessor()
    {
        static const GENERATED_ArkUIArcListItemExtenderAccessor ArcListItemExtenderAccessorImpl {
            ArcListItemExtenderAccessor::ConstructorImpl,
            ArcListItemExtenderAccessor::AutoScaleImpl,
            ArcListItemExtenderAccessor::SwipeActionImpl,
        };
        return &ArcListItemExtenderAccessorImpl;
    }

    const GENERATED_ArkUIArcScrollBarExtenderAccessor* GetArcScrollBarExtenderAccessor()
    {
        static const GENERATED_ArkUIArcScrollBarExtenderAccessor ArcScrollBarExtenderAccessorImpl {
            ArcScrollBarExtenderAccessor::ConstructorImpl,
            ArcScrollBarExtenderAccessor::SetArcScrollBarOptionsImpl,
        };
        return &ArcScrollBarExtenderAccessorImpl;
    }

    const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor()
    {
        static const GENERATED_ArkUIAxisEventAccessor AxisEventAccessorImpl {
            AxisEventAccessor::DestroyPeerImpl,
            AxisEventAccessor::ConstructImpl,
            AxisEventAccessor::GetFinalizerImpl,
            AxisEventAccessor::GetHorizontalAxisValueImpl,
            AxisEventAccessor::GetVerticalAxisValueImpl,
            AxisEventAccessor::HasAxisImpl,
            AxisEventAccessor::GetActionImpl,
            AxisEventAccessor::SetActionImpl,
            AxisEventAccessor::GetDisplayXImpl,
            AxisEventAccessor::SetDisplayXImpl,
            AxisEventAccessor::GetDisplayYImpl,
            AxisEventAccessor::SetDisplayYImpl,
            AxisEventAccessor::GetWindowXImpl,
            AxisEventAccessor::SetWindowXImpl,
            AxisEventAccessor::GetWindowYImpl,
            AxisEventAccessor::SetWindowYImpl,
            AxisEventAccessor::GetXImpl,
            AxisEventAccessor::SetXImpl,
            AxisEventAccessor::GetYImpl,
            AxisEventAccessor::SetYImpl,
            AxisEventAccessor::GetScrollStepImpl,
            AxisEventAccessor::SetScrollStepImpl,
            AxisEventAccessor::PropagationImpl,
        };
        return &AxisEventAccessorImpl;
    }

    struct AxisEventPeer {
        virtual ~AxisEventPeer() = default;
    };
    const GENERATED_ArkUIBackgroundColorStyleAccessor* GetBackgroundColorStyleAccessor()
    {
        static const GENERATED_ArkUIBackgroundColorStyleAccessor BackgroundColorStyleAccessorImpl {
            BackgroundColorStyleAccessor::DestroyPeerImpl,
            BackgroundColorStyleAccessor::ConstructImpl,
            BackgroundColorStyleAccessor::GetFinalizerImpl,
            BackgroundColorStyleAccessor::GetTextBackgroundStyleImpl,
        };
        return &BackgroundColorStyleAccessorImpl;
    }

    struct BackgroundColorStylePeer {
        virtual ~BackgroundColorStylePeer() = default;
    };
    const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
    {
        static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
            BaseEventAccessor::DestroyPeerImpl,
            BaseEventAccessor::ConstructImpl,
            BaseEventAccessor::GetFinalizerImpl,
            BaseEventAccessor::GetTargetImpl,
            BaseEventAccessor::SetTargetImpl,
            BaseEventAccessor::GetTimestampImpl,
            BaseEventAccessor::SetTimestampImpl,
            BaseEventAccessor::GetSourceImpl,
            BaseEventAccessor::SetSourceImpl,
            BaseEventAccessor::GetAxisHorizontalImpl,
            BaseEventAccessor::SetAxisHorizontalImpl,
            BaseEventAccessor::GetAxisVerticalImpl,
            BaseEventAccessor::SetAxisVerticalImpl,
            BaseEventAccessor::GetPressureImpl,
            BaseEventAccessor::SetPressureImpl,
            BaseEventAccessor::GetTiltXImpl,
            BaseEventAccessor::SetTiltXImpl,
            BaseEventAccessor::GetTiltYImpl,
            BaseEventAccessor::SetTiltYImpl,
            BaseEventAccessor::GetRollAngleImpl,
            BaseEventAccessor::SetRollAngleImpl,
            BaseEventAccessor::GetSourceToolImpl,
            BaseEventAccessor::SetSourceToolImpl,
            BaseEventAccessor::GetGetModifierKeyStateImpl,
            BaseEventAccessor::SetGetModifierKeyStateImpl,
            BaseEventAccessor::GetDeviceIdImpl,
            BaseEventAccessor::SetDeviceIdImpl,
            BaseEventAccessor::GetTargetDisplayIdImpl,
            BaseEventAccessor::SetTargetDisplayIdImpl,
        };
        return &BaseEventAccessorImpl;
    }

    struct BaseEventPeer {
        virtual ~BaseEventPeer() = default;
    };
    const GENERATED_ArkUIBaseGestureEventAccessor* GetBaseGestureEventAccessor()
    {
        static const GENERATED_ArkUIBaseGestureEventAccessor BaseGestureEventAccessorImpl {
            BaseGestureEventAccessor::DestroyPeerImpl,
            BaseGestureEventAccessor::ConstructImpl,
            BaseGestureEventAccessor::GetFinalizerImpl,
            BaseGestureEventAccessor::GetFingerListImpl,
            BaseGestureEventAccessor::SetFingerListImpl,
            BaseGestureEventAccessor::GetFingerInfosImpl,
        };
        return &BaseGestureEventAccessorImpl;
    }

    struct BaseGestureEventPeer {
        virtual ~BaseGestureEventPeer() = default;
    };
    const GENERATED_ArkUIBaselineOffsetStyleAccessor* GetBaselineOffsetStyleAccessor()
    {
        static const GENERATED_ArkUIBaselineOffsetStyleAccessor BaselineOffsetStyleAccessorImpl {
            BaselineOffsetStyleAccessor::DestroyPeerImpl,
            BaselineOffsetStyleAccessor::ConstructImpl,
            BaselineOffsetStyleAccessor::GetFinalizerImpl,
            BaselineOffsetStyleAccessor::GetBaselineOffsetImpl,
        };
        return &BaselineOffsetStyleAccessorImpl;
    }

    struct BaselineOffsetStylePeer {
        virtual ~BaselineOffsetStylePeer() = default;
    };
    const GENERATED_ArkUIBaseShapeAccessor* GetBaseShapeAccessor()
    {
        static const GENERATED_ArkUIBaseShapeAccessor BaseShapeAccessorImpl {
            BaseShapeAccessor::DestroyPeerImpl,
            BaseShapeAccessor::ConstructImpl,
            BaseShapeAccessor::GetFinalizerImpl,
            BaseShapeAccessor::WidthImpl,
            BaseShapeAccessor::HeightImpl,
            BaseShapeAccessor::SizeImpl,
        };
        return &BaseShapeAccessorImpl;
    }

    struct BaseShapePeer {
        virtual ~BaseShapePeer() = default;
    };
    const GENERATED_ArkUIBounceSymbolEffectAccessor* GetBounceSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIBounceSymbolEffectAccessor BounceSymbolEffectAccessorImpl {
            BounceSymbolEffectAccessor::DestroyPeerImpl,
            BounceSymbolEffectAccessor::ConstructImpl,
            BounceSymbolEffectAccessor::GetFinalizerImpl,
            BounceSymbolEffectAccessor::GetScopeImpl,
            BounceSymbolEffectAccessor::SetScopeImpl,
            BounceSymbolEffectAccessor::GetDirectionImpl,
            BounceSymbolEffectAccessor::SetDirectionImpl,
        };
        return &BounceSymbolEffectAccessorImpl;
    }

    struct BounceSymbolEffectPeer {
        virtual ~BounceSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIBuilderNodeOpsAccessor* GetBuilderNodeOpsAccessor()
    {
        static const GENERATED_ArkUIBuilderNodeOpsAccessor BuilderNodeOpsAccessorImpl {
            BuilderNodeOpsAccessor::DestroyPeerImpl,
            BuilderNodeOpsAccessor::ConstructImpl,
            BuilderNodeOpsAccessor::GetFinalizerImpl,
            BuilderNodeOpsAccessor::CreateImpl,
            BuilderNodeOpsAccessor::DisposeNodeImpl,
            BuilderNodeOpsAccessor::SetUpdateConfigurationCallbackImpl,
            BuilderNodeOpsAccessor::SetOptionsImpl,
            BuilderNodeOpsAccessor::PostTouchEventImpl,
            BuilderNodeOpsAccessor::SetRootFrameNodeInBuilderNodeImpl,
        };
        return &BuilderNodeOpsAccessorImpl;
    }

    struct BuilderNodeOpsPeer {
        virtual ~BuilderNodeOpsPeer() = default;
    };
    const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor()
    {
        static const GENERATED_ArkUICalendarPickerDialogAccessor CalendarPickerDialogAccessorImpl {
            CalendarPickerDialogAccessor::DestroyPeerImpl,
            CalendarPickerDialogAccessor::ConstructImpl,
            CalendarPickerDialogAccessor::GetFinalizerImpl,
            CalendarPickerDialogAccessor::ShowImpl,
        };
        return &CalendarPickerDialogAccessorImpl;
    }

    struct CalendarPickerDialogPeer {
        virtual ~CalendarPickerDialogPeer() = default;
    };
    const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor()
    {
        static const GENERATED_ArkUICanvasGradientAccessor CanvasGradientAccessorImpl {
            CanvasGradientAccessor::DestroyPeerImpl,
            CanvasGradientAccessor::ConstructImpl,
            CanvasGradientAccessor::GetFinalizerImpl,
            CanvasGradientAccessor::AddColorStopImpl,
        };
        return &CanvasGradientAccessorImpl;
    }

    struct CanvasGradientPeer {
        virtual ~CanvasGradientPeer() = default;
    };
    const GENERATED_ArkUICanvasPathAccessor* GetCanvasPathAccessor()
    {
        static const GENERATED_ArkUICanvasPathAccessor CanvasPathAccessorImpl {
            CanvasPathAccessor::DestroyPeerImpl,
            CanvasPathAccessor::ConstructImpl,
            CanvasPathAccessor::GetFinalizerImpl,
            CanvasPathAccessor::ArcImpl,
            CanvasPathAccessor::ArcToImpl,
            CanvasPathAccessor::BezierCurveToImpl,
            CanvasPathAccessor::ClosePathImpl,
            CanvasPathAccessor::EllipseImpl,
            CanvasPathAccessor::LineToImpl,
            CanvasPathAccessor::MoveToImpl,
            CanvasPathAccessor::QuadraticCurveToImpl,
            CanvasPathAccessor::RectImpl,
        };
        return &CanvasPathAccessorImpl;
    }

    struct CanvasPathPeer {
        virtual ~CanvasPathPeer() = default;
    };
    const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor()
    {
        static const GENERATED_ArkUICanvasPatternAccessor CanvasPatternAccessorImpl {
            CanvasPatternAccessor::DestroyPeerImpl,
            CanvasPatternAccessor::ConstructImpl,
            CanvasPatternAccessor::GetFinalizerImpl,
            CanvasPatternAccessor::SetTransformImpl,
        };
        return &CanvasPatternAccessorImpl;
    }

    struct CanvasPatternPeer {
        virtual ~CanvasPatternPeer() = default;
    };
    const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor()
    {
        static const GENERATED_ArkUICanvasRendererAccessor CanvasRendererAccessorImpl {
            CanvasRendererAccessor::DestroyPeerImpl,
            CanvasRendererAccessor::ConstructImpl,
            CanvasRendererAccessor::GetFinalizerImpl,
            CanvasRendererAccessor::DrawImage0Impl,
            CanvasRendererAccessor::DrawImage1Impl,
            CanvasRendererAccessor::DrawImage2Impl,
            CanvasRendererAccessor::BeginPathImpl,
            CanvasRendererAccessor::Clip0Impl,
            CanvasRendererAccessor::Clip1Impl,
            CanvasRendererAccessor::Fill0Impl,
            CanvasRendererAccessor::Fill1Impl,
            CanvasRendererAccessor::StrokeImpl,
            CanvasRendererAccessor::CreateLinearGradientImpl,
            CanvasRendererAccessor::CreatePatternImpl,
            CanvasRendererAccessor::CreateRadialGradientImpl,
            CanvasRendererAccessor::CreateConicGradientImpl,
            CanvasRendererAccessor::CreateImageData0Impl,
            CanvasRendererAccessor::CreateImageData1Impl,
            CanvasRendererAccessor::GetImageDataImpl,
            CanvasRendererAccessor::GetPixelMapImpl,
            CanvasRendererAccessor::PutImageData0Impl,
            CanvasRendererAccessor::PutImageData1Impl,
            CanvasRendererAccessor::GetLineDashImpl,
            CanvasRendererAccessor::SetLineDashImpl,
            CanvasRendererAccessor::ClearRectImpl,
            CanvasRendererAccessor::FillRectImpl,
            CanvasRendererAccessor::StrokeRectImpl,
            CanvasRendererAccessor::RestoreImpl,
            CanvasRendererAccessor::SaveImpl,
            CanvasRendererAccessor::FillTextImpl,
            CanvasRendererAccessor::MeasureTextImpl,
            CanvasRendererAccessor::StrokeTextImpl,
            CanvasRendererAccessor::GetTransformImpl,
            CanvasRendererAccessor::ResetTransformImpl,
            CanvasRendererAccessor::RotateImpl,
            CanvasRendererAccessor::ScaleImpl,
            CanvasRendererAccessor::SetTransform0Impl,
            CanvasRendererAccessor::SetTransform1Impl,
            CanvasRendererAccessor::TransformImpl,
            CanvasRendererAccessor::TranslateImpl,
            CanvasRendererAccessor::SetPixelMapImpl,
            CanvasRendererAccessor::TransferFromImageBitmapImpl,
            CanvasRendererAccessor::SaveLayerImpl,
            CanvasRendererAccessor::RestoreLayerImpl,
            CanvasRendererAccessor::ResetImpl,
            CanvasRendererAccessor::GetLetterSpacingImpl,
            CanvasRendererAccessor::SetLetterSpacingImpl,
            CanvasRendererAccessor::GetGlobalAlphaImpl,
            CanvasRendererAccessor::SetGlobalAlphaImpl,
            CanvasRendererAccessor::GetGlobalCompositeOperationImpl,
            CanvasRendererAccessor::SetGlobalCompositeOperationImpl,
            CanvasRendererAccessor::GetFillStyleImpl,
            CanvasRendererAccessor::SetFillStyleImpl,
            CanvasRendererAccessor::GetStrokeStyleImpl,
            CanvasRendererAccessor::SetStrokeStyleImpl,
            CanvasRendererAccessor::GetFilterImpl,
            CanvasRendererAccessor::SetFilterImpl,
            CanvasRendererAccessor::GetImageSmoothingEnabledImpl,
            CanvasRendererAccessor::SetImageSmoothingEnabledImpl,
            CanvasRendererAccessor::GetImageSmoothingQualityImpl,
            CanvasRendererAccessor::SetImageSmoothingQualityImpl,
            CanvasRendererAccessor::GetLineCapImpl,
            CanvasRendererAccessor::SetLineCapImpl,
            CanvasRendererAccessor::GetLineDashOffsetImpl,
            CanvasRendererAccessor::SetLineDashOffsetImpl,
            CanvasRendererAccessor::GetLineJoinImpl,
            CanvasRendererAccessor::SetLineJoinImpl,
            CanvasRendererAccessor::GetLineWidthImpl,
            CanvasRendererAccessor::SetLineWidthImpl,
            CanvasRendererAccessor::GetMiterLimitImpl,
            CanvasRendererAccessor::SetMiterLimitImpl,
            CanvasRendererAccessor::GetShadowBlurImpl,
            CanvasRendererAccessor::SetShadowBlurImpl,
            CanvasRendererAccessor::GetShadowColorImpl,
            CanvasRendererAccessor::SetShadowColorImpl,
            CanvasRendererAccessor::GetShadowOffsetXImpl,
            CanvasRendererAccessor::SetShadowOffsetXImpl,
            CanvasRendererAccessor::GetShadowOffsetYImpl,
            CanvasRendererAccessor::SetShadowOffsetYImpl,
            CanvasRendererAccessor::GetDirectionImpl,
            CanvasRendererAccessor::SetDirectionImpl,
            CanvasRendererAccessor::GetFontImpl,
            CanvasRendererAccessor::SetFontImpl,
            CanvasRendererAccessor::GetTextAlignImpl,
            CanvasRendererAccessor::SetTextAlignImpl,
            CanvasRendererAccessor::GetTextBaselineImpl,
            CanvasRendererAccessor::SetTextBaselineImpl,
        };
        return &CanvasRendererAccessorImpl;
    }

    struct CanvasRendererPeer {
        virtual ~CanvasRendererPeer() = default;
    };
    const GENERATED_ArkUICanvasRenderingContext2DAccessor* GetCanvasRenderingContext2DAccessor()
    {
        static const GENERATED_ArkUICanvasRenderingContext2DAccessor CanvasRenderingContext2DAccessorImpl {
            CanvasRenderingContext2DAccessor::DestroyPeerImpl,
            CanvasRenderingContext2DAccessor::ConstructImpl,
            CanvasRenderingContext2DAccessor::GetFinalizerImpl,
            CanvasRenderingContext2DAccessor::ToDataURLImpl,
            CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
            CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
            CanvasRenderingContext2DAccessor::OnOnAttachImpl,
            CanvasRenderingContext2DAccessor::OffOnAttachImpl,
            CanvasRenderingContext2DAccessor::OnOnDetachImpl,
            CanvasRenderingContext2DAccessor::OffOnDetachImpl,
            CanvasRenderingContext2DAccessor::GetHeightImpl,
            CanvasRenderingContext2DAccessor::SetHeightImpl,
            CanvasRenderingContext2DAccessor::GetWidthImpl,
            CanvasRenderingContext2DAccessor::SetWidthImpl,
            CanvasRenderingContext2DAccessor::GetCanvasImpl,
            CanvasRenderingContext2DAccessor::SetCanvasImpl,
        };
        return &CanvasRenderingContext2DAccessorImpl;
    }

    struct CanvasRenderingContext2DPeer {
        virtual ~CanvasRenderingContext2DPeer() = default;
    };
    const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor()
    {
        static const GENERATED_ArkUIChildrenMainSizeAccessor ChildrenMainSizeAccessorImpl {
            ChildrenMainSizeAccessor::DestroyPeerImpl,
            ChildrenMainSizeAccessor::ConstructImpl,
            ChildrenMainSizeAccessor::GetFinalizerImpl,
            ChildrenMainSizeAccessor::SpliceImpl,
            ChildrenMainSizeAccessor::UpdateImpl,
            ChildrenMainSizeAccessor::GetChildDefaultSizeImpl,
            ChildrenMainSizeAccessor::SetChildDefaultSizeImpl,
        };
        return &ChildrenMainSizeAccessorImpl;
    }

    struct ChildrenMainSizePeer {
        virtual ~ChildrenMainSizePeer() = default;
    };
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
    {
        static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
            ClickEventAccessor::DestroyPeerImpl,
            ClickEventAccessor::ConstructImpl,
            ClickEventAccessor::GetFinalizerImpl,
            ClickEventAccessor::GetDisplayXImpl,
            ClickEventAccessor::SetDisplayXImpl,
            ClickEventAccessor::GetDisplayYImpl,
            ClickEventAccessor::SetDisplayYImpl,
            ClickEventAccessor::GetWindowXImpl,
            ClickEventAccessor::SetWindowXImpl,
            ClickEventAccessor::GetWindowYImpl,
            ClickEventAccessor::SetWindowYImpl,
            ClickEventAccessor::GetXImpl,
            ClickEventAccessor::SetXImpl,
            ClickEventAccessor::GetYImpl,
            ClickEventAccessor::SetYImpl,
            ClickEventAccessor::GetHandImpl,
            ClickEventAccessor::SetHandImpl,
            ClickEventAccessor::PreventDefaultImpl,
        };
        return &ClickEventAccessorImpl;
    }

    struct ClickEventPeer {
        virtual ~ClickEventPeer() = default;
    };
    const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor()
    {
        static const GENERATED_ArkUIClientAuthenticationHandlerAccessor ClientAuthenticationHandlerAccessorImpl {
            ClientAuthenticationHandlerAccessor::DestroyPeerImpl,
            ClientAuthenticationHandlerAccessor::ConstructImpl,
            ClientAuthenticationHandlerAccessor::GetFinalizerImpl,
            ClientAuthenticationHandlerAccessor::Confirm0Impl,
            ClientAuthenticationHandlerAccessor::Confirm1Impl,
            ClientAuthenticationHandlerAccessor::CancelImpl,
            ClientAuthenticationHandlerAccessor::IgnoreImpl,
        };
        return &ClientAuthenticationHandlerAccessorImpl;
    }

    struct ClientAuthenticationHandlerPeer {
        virtual ~ClientAuthenticationHandlerPeer() = default;
    };
    const GENERATED_ArkUIColorContentAccessor* GetColorContentAccessor()
    {
        static const GENERATED_ArkUIColorContentAccessor ColorContentAccessorImpl {
            ColorContentAccessor::DestroyPeerImpl,
            ColorContentAccessor::ConstructImpl,
            ColorContentAccessor::GetFinalizerImpl,
            ColorContentAccessor::GetORIGINImpl,
        };
        return &ColorContentAccessorImpl;
    }

    struct ColorContentPeer {
        virtual ~ColorContentPeer() = default;
    };
    const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor()
    {
        static const GENERATED_ArkUIColorFilterAccessor ColorFilterAccessorImpl {
            ColorFilterAccessor::DestroyPeerImpl,
            ColorFilterAccessor::ConstructImpl,
            ColorFilterAccessor::GetFinalizerImpl,
        };
        return &ColorFilterAccessorImpl;
    }

    struct ColorFilterPeer {
        virtual ~ColorFilterPeer() = default;
    };
    const GENERATED_ArkUICommonShapeAccessor* GetCommonShapeAccessor()
    {
        static const GENERATED_ArkUICommonShapeAccessor CommonShapeAccessorImpl {
            CommonShapeAccessor::DestroyPeerImpl,
            CommonShapeAccessor::ConstructImpl,
            CommonShapeAccessor::GetFinalizerImpl,
            CommonShapeAccessor::OffsetImpl,
            CommonShapeAccessor::FillImpl,
            CommonShapeAccessor::PositionImpl,
        };
        return &CommonShapeAccessorImpl;
    }

    struct CommonShapePeer {
        virtual ~CommonShapePeer() = default;
    };
    const GENERATED_ArkUIConsoleMessageAccessor* GetConsoleMessageAccessor()
    {
        static const GENERATED_ArkUIConsoleMessageAccessor ConsoleMessageAccessorImpl {
            ConsoleMessageAccessor::DestroyPeerImpl,
            ConsoleMessageAccessor::ConstructImpl,
            ConsoleMessageAccessor::GetFinalizerImpl,
            ConsoleMessageAccessor::GetMessageImpl,
            ConsoleMessageAccessor::GetSourceIdImpl,
            ConsoleMessageAccessor::GetLineNumberImpl,
            ConsoleMessageAccessor::GetMessageLevelImpl,
        };
        return &ConsoleMessageAccessorImpl;
    }

    struct ConsoleMessagePeer {
        virtual ~ConsoleMessagePeer() = default;
    };
    const GENERATED_ArkUIContentModifierHelperAccessor* GetContentModifierHelperAccessor()
    {
        static const GENERATED_ArkUIContentModifierHelperAccessor ContentModifierHelperAccessorImpl {
            ContentModifierHelperAccessor::ContentModifierButtonImpl,
            ContentModifierHelperAccessor::ResetContentModifierButtonImpl,
            ContentModifierHelperAccessor::ContentModifierCheckBoxImpl,
            ContentModifierHelperAccessor::ResetContentModifierCheckBoxImpl,
            ContentModifierHelperAccessor::ContentModifierDataPanelImpl,
            ContentModifierHelperAccessor::ResetContentModifierDataPanelImpl,
            ContentModifierHelperAccessor::ContentModifierGaugeImpl,
            ContentModifierHelperAccessor::ResetContentModifierGaugeImpl,
            ContentModifierHelperAccessor::ContentModifierLoadingProgressImpl,
            ContentModifierHelperAccessor::ResetContentModifierLoadingProgressImpl,
            ContentModifierHelperAccessor::ContentModifierProgressImpl,
            ContentModifierHelperAccessor::ResetContentModifierProgressImpl,
            ContentModifierHelperAccessor::ContentModifierRadioImpl,
            ContentModifierHelperAccessor::ResetContentModifierRadioImpl,
            ContentModifierHelperAccessor::ContentModifierRatingImpl,
            ContentModifierHelperAccessor::ResetContentModifierRatingImpl,
            ContentModifierHelperAccessor::ContentModifierMenuItemImpl,
            ContentModifierHelperAccessor::ResetContentModifierMenuItemImpl,
            ContentModifierHelperAccessor::ContentModifierSliderImpl,
            ContentModifierHelperAccessor::ResetContentModifierSliderImpl,
            ContentModifierHelperAccessor::ContentModifierTextClockImpl,
            ContentModifierHelperAccessor::ResetContentModifierTextClockImpl,
            ContentModifierHelperAccessor::ContentModifierTextTimerImpl,
            ContentModifierHelperAccessor::ResetContentModifierTextTimerImpl,
            ContentModifierHelperAccessor::ContentModifierToggleImpl,
            ContentModifierHelperAccessor::ResetContentModifierToggleImpl,
        };
        return &ContentModifierHelperAccessorImpl;
    }

    const GENERATED_ArkUIControllerHandlerAccessor* GetControllerHandlerAccessor()
    {
        static const GENERATED_ArkUIControllerHandlerAccessor ControllerHandlerAccessorImpl {
            ControllerHandlerAccessor::DestroyPeerImpl,
            ControllerHandlerAccessor::ConstructImpl,
            ControllerHandlerAccessor::GetFinalizerImpl,
            ControllerHandlerAccessor::SetWebControllerImpl,
        };
        return &ControllerHandlerAccessorImpl;
    }

    struct ControllerHandlerPeer {
        virtual ~ControllerHandlerPeer() = default;
    };
    const GENERATED_ArkUICopyEventAccessor* GetCopyEventAccessor()
    {
        static const GENERATED_ArkUICopyEventAccessor CopyEventAccessorImpl {
            CopyEventAccessor::DestroyPeerImpl,
            CopyEventAccessor::ConstructImpl,
            CopyEventAccessor::GetFinalizerImpl,
            CopyEventAccessor::PreventDefaultImpl,
        };
        return &CopyEventAccessorImpl;
    }

    struct CopyEventPeer {
        virtual ~CopyEventPeer() = default;
    };
    const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
    {
        static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
            CustomDialogControllerAccessor::DestroyPeerImpl,
            CustomDialogControllerAccessor::ConstructImpl,
            CustomDialogControllerAccessor::GetFinalizerImpl,
            CustomDialogControllerAccessor::OpenImpl,
            CustomDialogControllerAccessor::CloseImpl,
            CustomDialogControllerAccessor::GetExternalOptionsImpl,
            CustomDialogControllerAccessor::GetStateImpl,
        };
        return &CustomDialogControllerAccessorImpl;
    }

    struct CustomDialogControllerPeer {
        virtual ~CustomDialogControllerPeer() = default;
    };
    const GENERATED_ArkUICustomDialogControllerExtenderAccessor* GetCustomDialogControllerExtenderAccessor()
    {
        static const GENERATED_ArkUICustomDialogControllerExtenderAccessor CustomDialogControllerExtenderAccessorImpl {
            CustomDialogControllerExtenderAccessor::DestroyPeerImpl,
            CustomDialogControllerExtenderAccessor::ConstructImpl,
            CustomDialogControllerExtenderAccessor::GetFinalizerImpl,
            CustomDialogControllerExtenderAccessor::OpenImpl,
            CustomDialogControllerExtenderAccessor::CloseImpl,
            CustomDialogControllerExtenderAccessor::SetOwnerViewImpl,
            CustomDialogControllerExtenderAccessor::GetExternalOptionsImpl,
            CustomDialogControllerExtenderAccessor::GetStateImpl,
        };
        return &CustomDialogControllerExtenderAccessorImpl;
    }

    struct CustomDialogControllerExtenderPeer {
        virtual ~CustomDialogControllerExtenderPeer() = default;
    };
    const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
    {
        static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
            CustomSpanAccessor::DestroyPeerImpl,
            CustomSpanAccessor::ConstructImpl,
            CustomSpanAccessor::GetFinalizerImpl,
            CustomSpanAccessor::InvalidateImpl,
            CustomSpanAccessor::GetOnMeasure_callbackImpl,
            CustomSpanAccessor::SetOnMeasure_callbackImpl,
            CustomSpanAccessor::GetOnDraw_callbackImpl,
            CustomSpanAccessor::SetOnDraw_callbackImpl,
        };
        return &CustomSpanAccessorImpl;
    }

    struct CustomSpanPeer {
        virtual ~CustomSpanPeer() = default;
    };
    const GENERATED_ArkUICutEventAccessor* GetCutEventAccessor()
    {
        static const GENERATED_ArkUICutEventAccessor CutEventAccessorImpl {
            CutEventAccessor::DestroyPeerImpl,
            CutEventAccessor::ConstructImpl,
            CutEventAccessor::GetFinalizerImpl,
            CutEventAccessor::PreventDefaultImpl,
        };
        return &CutEventAccessorImpl;
    }

    struct CutEventPeer {
        virtual ~CutEventPeer() = default;
    };
    const GENERATED_ArkUIDataResubmissionHandlerAccessor* GetDataResubmissionHandlerAccessor()
    {
        static const GENERATED_ArkUIDataResubmissionHandlerAccessor DataResubmissionHandlerAccessorImpl {
            DataResubmissionHandlerAccessor::DestroyPeerImpl,
            DataResubmissionHandlerAccessor::ConstructImpl,
            DataResubmissionHandlerAccessor::GetFinalizerImpl,
            DataResubmissionHandlerAccessor::ResendImpl,
            DataResubmissionHandlerAccessor::CancelImpl,
        };
        return &DataResubmissionHandlerAccessorImpl;
    }

    struct DataResubmissionHandlerPeer {
        virtual ~DataResubmissionHandlerPeer() = default;
    };
    const GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogAccessor()
    {
        static const GENERATED_ArkUIDatePickerDialogAccessor DatePickerDialogAccessorImpl {
            DatePickerDialogAccessor::DestroyPeerImpl,
            DatePickerDialogAccessor::ConstructImpl,
            DatePickerDialogAccessor::GetFinalizerImpl,
        };
        return &DatePickerDialogAccessorImpl;
    }

    struct DatePickerDialogPeer {
        virtual ~DatePickerDialogPeer() = default;
    };
    const GENERATED_ArkUIDecorationStyleAccessor* GetDecorationStyleAccessor()
    {
        static const GENERATED_ArkUIDecorationStyleAccessor DecorationStyleAccessorImpl {
            DecorationStyleAccessor::DestroyPeerImpl,
            DecorationStyleAccessor::ConstructImpl,
            DecorationStyleAccessor::GetFinalizerImpl,
            DecorationStyleAccessor::GetTypeImpl,
            DecorationStyleAccessor::GetColorImpl,
            DecorationStyleAccessor::GetStyleImpl,
        };
        return &DecorationStyleAccessorImpl;
    }

    struct DecorationStylePeer {
        virtual ~DecorationStylePeer() = default;
    };
    const GENERATED_ArkUIDialogExtenderAccessor* GetDialogExtenderAccessor()
    {
        static const GENERATED_ArkUIDialogExtenderAccessor DialogExtenderAccessorImpl {
            DialogExtenderAccessor::ShowTimePickerDialogImpl,
            DialogExtenderAccessor::ShowTextPickerDialogImpl,
            DialogExtenderAccessor::ShowDatePickerDialogImpl,
        };
        return &DialogExtenderAccessorImpl;
    }

    const GENERATED_ArkUIDisappearSymbolEffectAccessor* GetDisappearSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIDisappearSymbolEffectAccessor DisappearSymbolEffectAccessorImpl {
            DisappearSymbolEffectAccessor::DestroyPeerImpl,
            DisappearSymbolEffectAccessor::ConstructImpl,
            DisappearSymbolEffectAccessor::GetFinalizerImpl,
            DisappearSymbolEffectAccessor::GetScopeImpl,
            DisappearSymbolEffectAccessor::SetScopeImpl,
        };
        return &DisappearSymbolEffectAccessorImpl;
    }

    struct DisappearSymbolEffectPeer {
        virtual ~DisappearSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIDismissDialogActionAccessor* GetDismissDialogActionAccessor()
    {
        static const GENERATED_ArkUIDismissDialogActionAccessor DismissDialogActionAccessorImpl {
            DismissDialogActionAccessor::DestroyPeerImpl,
            DismissDialogActionAccessor::ConstructImpl,
            DismissDialogActionAccessor::GetFinalizerImpl,
            DismissDialogActionAccessor::DismissImpl,
            DismissDialogActionAccessor::GetReasonImpl,
            DismissDialogActionAccessor::SetReasonImpl,
        };
        return &DismissDialogActionAccessorImpl;
    }

    struct DismissDialogActionPeer {
        virtual ~DismissDialogActionPeer() = default;
    };
    const GENERATED_ArkUIDismissPopupActionAccessor* GetDismissPopupActionAccessor()
    {
        static const GENERATED_ArkUIDismissPopupActionAccessor DismissPopupActionAccessorImpl {
            DismissPopupActionAccessor::DestroyPeerImpl,
            DismissPopupActionAccessor::ConstructImpl,
            DismissPopupActionAccessor::GetFinalizerImpl,
            DismissPopupActionAccessor::DismissImpl,
            DismissPopupActionAccessor::GetReasonImpl,
            DismissPopupActionAccessor::SetReasonImpl,
        };
        return &DismissPopupActionAccessorImpl;
    }

    struct DismissPopupActionPeer {
        virtual ~DismissPopupActionPeer() = default;
    };
    const GENERATED_ArkUIDragEventAccessor* GetDragEventAccessor()
    {
        static const GENERATED_ArkUIDragEventAccessor DragEventAccessorImpl {
            DragEventAccessor::DestroyPeerImpl,
            DragEventAccessor::ConstructImpl,
            DragEventAccessor::GetFinalizerImpl,
            DragEventAccessor::GetDisplayXImpl,
            DragEventAccessor::GetDisplayYImpl,
            DragEventAccessor::GetWindowXImpl,
            DragEventAccessor::GetWindowYImpl,
            DragEventAccessor::SetDataImpl,
            DragEventAccessor::GetDataImpl,
            DragEventAccessor::GetSummaryImpl,
            DragEventAccessor::SetResultImpl,
            DragEventAccessor::GetResultImpl,
            DragEventAccessor::GetPreviewRectImpl,
            DragEventAccessor::GetVelocityXImpl,
            DragEventAccessor::GetVelocityYImpl,
            DragEventAccessor::GetVelocityImpl,
            DragEventAccessor::ExecuteDropAnimationImpl,
            DragEventAccessor::EnableInternalDropAnimationImpl,
            DragEventAccessor::GetDragBehaviorImpl,
            DragEventAccessor::SetDragBehaviorImpl,
            DragEventAccessor::GetUseCustomDropAnimationImpl,
            DragEventAccessor::SetUseCustomDropAnimationImpl,
            DragEventAccessor::GetGetModifierKeyStateImpl,
            DragEventAccessor::SetGetModifierKeyStateImpl,
        };
        return &DragEventAccessorImpl;
    }

    struct DragEventPeer {
        virtual ~DragEventPeer() = default;
    };
    const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor()
    {
        static const GENERATED_ArkUIDrawingRenderingContextAccessor DrawingRenderingContextAccessorImpl {
            DrawingRenderingContextAccessor::DestroyPeerImpl,
            DrawingRenderingContextAccessor::ConstructImpl,
            DrawingRenderingContextAccessor::GetFinalizerImpl,
            DrawingRenderingContextAccessor::InvalidateImpl,
            DrawingRenderingContextAccessor::GetSizeImpl,
            DrawingRenderingContextAccessor::SetSizeImpl,
            DrawingRenderingContextAccessor::GetCanvasImpl,
            DrawingRenderingContextAccessor::SetCanvasImpl,
        };
        return &DrawingRenderingContextAccessorImpl;
    }

    struct DrawingRenderingContextPeer {
        virtual ~DrawingRenderingContextPeer() = default;
    };
    const GENERATED_ArkUIEnvironmentBackendAccessor* GetEnvironmentBackendAccessor()
    {
        static const GENERATED_ArkUIEnvironmentBackendAccessor EnvironmentBackendAccessorImpl {
            EnvironmentBackendAccessor::IsAccessibilityEnabledImpl,
            EnvironmentBackendAccessor::GetColorModeImpl,
            EnvironmentBackendAccessor::GetFontScaleImpl,
            EnvironmentBackendAccessor::GetFontWeightScaleImpl,
            EnvironmentBackendAccessor::GetLayoutDirectionImpl,
            EnvironmentBackendAccessor::GetLanguageCodeImpl,
        };
        return &EnvironmentBackendAccessorImpl;
    }

    const GENERATED_ArkUIEventEmulatorAccessor* GetEventEmulatorAccessor()
    {
        static const GENERATED_ArkUIEventEmulatorAccessor EventEmulatorAccessorImpl {
            EventEmulatorAccessor::EmitClickEventImpl,
            EventEmulatorAccessor::EmitTextInputEventImpl,
        };
        return &EventEmulatorAccessorImpl;
    }

    const GENERATED_ArkUIEventResultAccessor* GetEventResultAccessor()
    {
        static const GENERATED_ArkUIEventResultAccessor EventResultAccessorImpl {
            EventResultAccessor::DestroyPeerImpl,
            EventResultAccessor::ConstructImpl,
            EventResultAccessor::GetFinalizerImpl,
            EventResultAccessor::SetGestureEventResult0Impl,
            EventResultAccessor::SetGestureEventResult1Impl,
            EventResultAccessor::SetMouseEventResultImpl,
        };
        return &EventResultAccessorImpl;
    }

    struct EventResultPeer {
        virtual ~EventResultPeer() = default;
    };
    const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor()
    {
        static const GENERATED_ArkUIEventTargetInfoAccessor EventTargetInfoAccessorImpl {
            EventTargetInfoAccessor::DestroyPeerImpl,
            EventTargetInfoAccessor::ConstructImpl,
            EventTargetInfoAccessor::GetFinalizerImpl,
            EventTargetInfoAccessor::GetIdImpl,
        };
        return &EventTargetInfoAccessorImpl;
    }

    struct EventTargetInfoPeer {
        virtual ~EventTargetInfoPeer() = default;
    };
    const GENERATED_ArkUIExtendableComponentAccessor* GetExtendableComponentAccessor()
    {
        static const GENERATED_ArkUIExtendableComponentAccessor ExtendableComponentAccessorImpl {
            ExtendableComponentAccessor::DestroyPeerImpl,
            ExtendableComponentAccessor::ConstructImpl,
            ExtendableComponentAccessor::GetFinalizerImpl,
            ExtendableComponentAccessor::GetUIContextImpl,
            ExtendableComponentAccessor::GetUniqueIdImpl,
            ExtendableComponentAccessor::QueryNavDestinationInfo0Impl,
            ExtendableComponentAccessor::QueryNavDestinationInfo1Impl,
            ExtendableComponentAccessor::QueryNavigationInfoImpl,
            ExtendableComponentAccessor::QueryRouterPageInfoImpl,
        };
        return &ExtendableComponentAccessorImpl;
    }

    struct ExtendableComponentPeer {
        virtual ~ExtendableComponentPeer() = default;
    };
    const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor()
    {
        static const GENERATED_ArkUIFileSelectorParamAccessor FileSelectorParamAccessorImpl {
            FileSelectorParamAccessor::DestroyPeerImpl,
            FileSelectorParamAccessor::ConstructImpl,
            FileSelectorParamAccessor::GetFinalizerImpl,
            FileSelectorParamAccessor::GetTitleImpl,
            FileSelectorParamAccessor::GetModeImpl,
            FileSelectorParamAccessor::GetAcceptTypeImpl,
            FileSelectorParamAccessor::IsCaptureImpl,
            FileSelectorParamAccessor::GetMimeTypesImpl,
        };
        return &FileSelectorParamAccessorImpl;
    }

    struct FileSelectorParamPeer {
        virtual ~FileSelectorParamPeer() = default;
    };
    const GENERATED_ArkUIFileSelectorResultAccessor* GetFileSelectorResultAccessor()
    {
        static const GENERATED_ArkUIFileSelectorResultAccessor FileSelectorResultAccessorImpl {
            FileSelectorResultAccessor::DestroyPeerImpl,
            FileSelectorResultAccessor::ConstructImpl,
            FileSelectorResultAccessor::GetFinalizerImpl,
            FileSelectorResultAccessor::HandleFileListImpl,
        };
        return &FileSelectorResultAccessorImpl;
    }

    struct FileSelectorResultPeer {
        virtual ~FileSelectorResultPeer() = default;
    };
    const GENERATED_ArkUIFocusAxisEventAccessor* GetFocusAxisEventAccessor()
    {
        static const GENERATED_ArkUIFocusAxisEventAccessor FocusAxisEventAccessorImpl {
            FocusAxisEventAccessor::DestroyPeerImpl,
            FocusAxisEventAccessor::ConstructImpl,
            FocusAxisEventAccessor::GetFinalizerImpl,
            FocusAxisEventAccessor::GetAxisMapImpl,
            FocusAxisEventAccessor::SetAxisMapImpl,
            FocusAxisEventAccessor::StopPropagationImpl,
        };
        return &FocusAxisEventAccessorImpl;
    }

    struct FocusAxisEventPeer {
        virtual ~FocusAxisEventPeer() = default;
    };
    const GENERATED_ArkUIFocusControllerAccessor* GetFocusControllerAccessor()
    {
        static const GENERATED_ArkUIFocusControllerAccessor FocusControllerAccessorImpl {
            FocusControllerAccessor::RequestFocusImpl,
        };
        return &FocusControllerAccessorImpl;
    }

    const GENERATED_ArkUIForEachOpsAccessor* GetForEachOpsAccessor()
    {
        static const GENERATED_ArkUIForEachOpsAccessor ForEachOpsAccessorImpl {
            ForEachOpsAccessor::SyncOnMoveOpsImpl,
        };
        return &ForEachOpsAccessorImpl;
    }

    const GENERATED_ArkUIFrameNodeExtenderAccessor* GetFrameNodeExtenderAccessor()
    {
        static const GENERATED_ArkUIFrameNodeExtenderAccessor FrameNodeExtenderAccessorImpl {
            FrameNodeExtenderAccessor::ConstructorFrameNodeImpl,
            FrameNodeExtenderAccessor::GetDestroyImpl,
            FrameNodeExtenderAccessor::DestroyPeerImpl,
            FrameNodeExtenderAccessor::IsModifiableImpl,
            FrameNodeExtenderAccessor::AppendChildImpl,
            FrameNodeExtenderAccessor::InsertChildAfterImpl,
            FrameNodeExtenderAccessor::RemoveChildImpl,
            FrameNodeExtenderAccessor::ClearChildrenImpl,
            FrameNodeExtenderAccessor::GetChildImpl,
            FrameNodeExtenderAccessor::GetFirstChildImpl,
            FrameNodeExtenderAccessor::GetNextSiblingImpl,
            FrameNodeExtenderAccessor::GetPreviousSiblingImpl,
            FrameNodeExtenderAccessor::GetParentImpl,
            FrameNodeExtenderAccessor::GetChildrenCountImpl,
            FrameNodeExtenderAccessor::DisposeImpl,
            FrameNodeExtenderAccessor::GetPositionToWindowImpl,
            FrameNodeExtenderAccessor::GetPositionToParentImpl,
            FrameNodeExtenderAccessor::GetMeasuredSizeImpl,
            FrameNodeExtenderAccessor::GetLayoutPositionImpl,
            FrameNodeExtenderAccessor::GetIdImpl,
            FrameNodeExtenderAccessor::GetUniqueIdImpl,
            FrameNodeExtenderAccessor::GetNodeTypeImpl,
            FrameNodeExtenderAccessor::GetOpacityImpl,
            FrameNodeExtenderAccessor::IsVisibleImpl,
            FrameNodeExtenderAccessor::IsClipToFrameImpl,
            FrameNodeExtenderAccessor::IsAttachedImpl,
            FrameNodeExtenderAccessor::GetInspectorInfoImpl,
            FrameNodeExtenderAccessor::InvalidateImpl,
            FrameNodeExtenderAccessor::DisposeTreeImpl,
            FrameNodeExtenderAccessor::SetCrossLanguageOptionsImpl,
            FrameNodeExtenderAccessor::GetCrossLanguageOptionsImpl,
            FrameNodeExtenderAccessor::SetMeasuredSizeImpl,
            FrameNodeExtenderAccessor::SetLayoutPositionImpl,
            FrameNodeExtenderAccessor::MeasureImpl,
            FrameNodeExtenderAccessor::LayoutImpl,
            FrameNodeExtenderAccessor::SetNeedsLayoutImpl,
            FrameNodeExtenderAccessor::GetPositionToScreenImpl,
            FrameNodeExtenderAccessor::GetPositionToWindowWithTransformImpl,
            FrameNodeExtenderAccessor::GetPositionToParentWithTransformImpl,
            FrameNodeExtenderAccessor::GetPositionToScreenWithTransformImpl,
            FrameNodeExtenderAccessor::GetUserConfigBorderWidthImpl,
            FrameNodeExtenderAccessor::GetUserConfigPaddingImpl,
            FrameNodeExtenderAccessor::GetUserConfigMarginImpl,
            FrameNodeExtenderAccessor::GetUserConfigSizeImpl,
            FrameNodeExtenderAccessor::GetFrameNodeByKeyImpl,
            FrameNodeExtenderAccessor::GetIdByFrameNodeImpl,
            FrameNodeExtenderAccessor::MoveToImpl,
            FrameNodeExtenderAccessor::GetFirstChildIndexWithoutExpandImpl,
            FrameNodeExtenderAccessor::GetLastChildIndexWithoutExpandImpl,
            FrameNodeExtenderAccessor::GetAttachedFrameNodeByIdImpl,
            FrameNodeExtenderAccessor::GetFrameNodeByIdImpl,
            FrameNodeExtenderAccessor::GetFrameNodeByUniqueIdImpl,
            FrameNodeExtenderAccessor::ReuseImpl,
            FrameNodeExtenderAccessor::RecycleImpl,
            FrameNodeExtenderAccessor::CreateAnimationImpl,
            FrameNodeExtenderAccessor::CancelAnimationsImpl,
            FrameNodeExtenderAccessor::GetNodePropertyValueImpl,
            FrameNodeExtenderAccessor::GetFrameNodePtrImpl,
            FrameNodeExtenderAccessor::CreateTypedFrameNodeImpl,
            FrameNodeExtenderAccessor::CreateByRawPtrImpl,
            FrameNodeExtenderAccessor::UnWrapRawPtrImpl,
            FrameNodeExtenderAccessor::GetCommonEventImpl,
            FrameNodeExtenderAccessor::IsOnRenderTreeImpl,
        };
        return &FrameNodeExtenderAccessorImpl;
    }

    const GENERATED_ArkUIFrictionMotionAccessor* GetFrictionMotionAccessor()
    {
        static const GENERATED_ArkUIFrictionMotionAccessor FrictionMotionAccessorImpl {
            FrictionMotionAccessor::DestroyPeerImpl,
            FrictionMotionAccessor::ConstructImpl,
            FrictionMotionAccessor::GetFinalizerImpl,
        };
        return &FrictionMotionAccessorImpl;
    }

    struct FrictionMotionPeer {
        virtual ~FrictionMotionPeer() = default;
    };
    const GENERATED_ArkUIFullScreenExitHandlerAccessor* GetFullScreenExitHandlerAccessor()
    {
        static const GENERATED_ArkUIFullScreenExitHandlerAccessor FullScreenExitHandlerAccessorImpl {
            FullScreenExitHandlerAccessor::DestroyPeerImpl,
            FullScreenExitHandlerAccessor::ConstructImpl,
            FullScreenExitHandlerAccessor::GetFinalizerImpl,
            FullScreenExitHandlerAccessor::ExitFullScreenImpl,
        };
        return &FullScreenExitHandlerAccessorImpl;
    }

    struct FullScreenExitHandlerPeer {
        virtual ~FullScreenExitHandlerPeer() = default;
    };
    const GENERATED_ArkUIGestureAccessor* GetGestureAccessor()
    {
        static const GENERATED_ArkUIGestureAccessor GestureAccessorImpl {
            GestureAccessor::DestroyPeerImpl,
            GestureAccessor::ConstructImpl,
            GestureAccessor::GetFinalizerImpl,
            GestureAccessor::TagImpl,
            GestureAccessor::AllowedTypesImpl,
        };
        return &GestureAccessorImpl;
    }

    struct GesturePeer {
        virtual ~GesturePeer() = default;
    };
    const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor()
    {
        static const GENERATED_ArkUIGestureEventAccessor GestureEventAccessorImpl {
            GestureEventAccessor::DestroyPeerImpl,
            GestureEventAccessor::ConstructImpl,
            GestureEventAccessor::GetFinalizerImpl,
            GestureEventAccessor::GetRepeatImpl,
            GestureEventAccessor::SetRepeatImpl,
            GestureEventAccessor::GetFingerListImpl,
            GestureEventAccessor::SetFingerListImpl,
            GestureEventAccessor::GetFingerInfosImpl,
            GestureEventAccessor::GetOffsetXImpl,
            GestureEventAccessor::SetOffsetXImpl,
            GestureEventAccessor::GetOffsetYImpl,
            GestureEventAccessor::SetOffsetYImpl,
            GestureEventAccessor::GetAngleImpl,
            GestureEventAccessor::SetAngleImpl,
            GestureEventAccessor::GetSpeedImpl,
            GestureEventAccessor::SetSpeedImpl,
            GestureEventAccessor::GetScaleImpl,
            GestureEventAccessor::SetScaleImpl,
            GestureEventAccessor::GetPinchCenterXImpl,
            GestureEventAccessor::SetPinchCenterXImpl,
            GestureEventAccessor::GetPinchCenterYImpl,
            GestureEventAccessor::SetPinchCenterYImpl,
            GestureEventAccessor::GetVelocityXImpl,
            GestureEventAccessor::SetVelocityXImpl,
            GestureEventAccessor::GetVelocityYImpl,
            GestureEventAccessor::SetVelocityYImpl,
            GestureEventAccessor::GetVelocityImpl,
            GestureEventAccessor::SetVelocityImpl,
            GestureEventAccessor::GetTapLocationImpl,
        };
        return &GestureEventAccessorImpl;
    }

    struct GestureEventPeer {
        virtual ~GestureEventPeer() = default;
    };
    const GENERATED_ArkUIGestureGroupAccessor* GetGestureGroupAccessor()
    {
        static const GENERATED_ArkUIGestureGroupAccessor GestureGroupAccessorImpl {
            GestureGroupAccessor::DestroyPeerImpl,
            GestureGroupAccessor::ConstructImpl,
            GestureGroupAccessor::GetFinalizerImpl,
            GestureGroupAccessor::$_instantiateImpl,
            GestureGroupAccessor::OnCancelImpl,
        };
        return &GestureGroupAccessorImpl;
    }

    struct GestureGroupPeer {
        virtual ~GestureGroupPeer() = default;
    };
    const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor()
    {
        static const GENERATED_ArkUIGestureRecognizerAccessor GestureRecognizerAccessorImpl {
            GestureRecognizerAccessor::DestroyPeerImpl,
            GestureRecognizerAccessor::ConstructImpl,
            GestureRecognizerAccessor::GetFinalizerImpl,
            GestureRecognizerAccessor::GetTagImpl,
            GestureRecognizerAccessor::GetTypeImpl,
            GestureRecognizerAccessor::IsBuiltInImpl,
            GestureRecognizerAccessor::SetEnabledImpl,
            GestureRecognizerAccessor::IsEnabledImpl,
            GestureRecognizerAccessor::GetStateImpl,
            GestureRecognizerAccessor::GetEventTargetInfoImpl,
            GestureRecognizerAccessor::IsValidImpl,
            GestureRecognizerAccessor::GetFingerCountImpl,
            GestureRecognizerAccessor::IsFingerCountLimitImpl,
        };
        return &GestureRecognizerAccessorImpl;
    }

    struct GestureRecognizerPeer {
        virtual ~GestureRecognizerPeer() = default;
    };
    const GENERATED_ArkUIGestureStyleAccessor* GetGestureStyleAccessor()
    {
        static const GENERATED_ArkUIGestureStyleAccessor GestureStyleAccessorImpl {
            GestureStyleAccessor::DestroyPeerImpl,
            GestureStyleAccessor::ConstructImpl,
            GestureStyleAccessor::GetFinalizerImpl,
        };
        return &GestureStyleAccessorImpl;
    }

    struct GestureStylePeer {
        virtual ~GestureStylePeer() = default;
    };
    const GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor* GetGlobalScope_ohos_arkui_componentSnapshotAccessor()
    {
        static const GENERATED_ArkUIGlobalScope_ohos_arkui_componentSnapshotAccessor GlobalScope_ohos_arkui_componentSnapshotAccessorImpl {
            GlobalScope_ohos_arkui_componentSnapshotAccessor::GetImpl,
        };
        return &GlobalScope_ohos_arkui_componentSnapshotAccessorImpl;
    }

    const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor* GetGlobalScope_ohos_arkui_performanceMonitorAccessor()
    {
        static const GENERATED_ArkUIGlobalScope_ohos_arkui_performanceMonitorAccessor GlobalScope_ohos_arkui_performanceMonitorAccessorImpl {
            GlobalScope_ohos_arkui_performanceMonitorAccessor::BeginImpl,
            GlobalScope_ohos_arkui_performanceMonitorAccessor::EndImpl,
            GlobalScope_ohos_arkui_performanceMonitorAccessor::RecordInputEventTimeImpl,
        };
        return &GlobalScope_ohos_arkui_performanceMonitorAccessorImpl;
    }

    const GENERATED_ArkUIGlobalScope_ohos_fontAccessor* GetGlobalScope_ohos_fontAccessor()
    {
        static const GENERATED_ArkUIGlobalScope_ohos_fontAccessor GlobalScope_ohos_fontAccessorImpl {
            GlobalScope_ohos_fontAccessor::RegisterFontImpl,
            GlobalScope_ohos_fontAccessor::GetSystemFontListImpl,
            GlobalScope_ohos_fontAccessor::GetFontByNameImpl,
        };
        return &GlobalScope_ohos_fontAccessorImpl;
    }

    const GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor* GetGlobalScope_ohos_measure_utilsAccessor()
    {
        static const GENERATED_ArkUIGlobalScope_ohos_measure_utilsAccessor GlobalScope_ohos_measure_utilsAccessorImpl {
            GlobalScope_ohos_measure_utilsAccessor::MeasureTextImpl,
            GlobalScope_ohos_measure_utilsAccessor::MeasureTextSizeImpl,
        };
        return &GlobalScope_ohos_measure_utilsAccessorImpl;
    }

    const GENERATED_ArkUIHierarchicalSymbolEffectAccessor* GetHierarchicalSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIHierarchicalSymbolEffectAccessor HierarchicalSymbolEffectAccessorImpl {
            HierarchicalSymbolEffectAccessor::DestroyPeerImpl,
            HierarchicalSymbolEffectAccessor::ConstructImpl,
            HierarchicalSymbolEffectAccessor::GetFinalizerImpl,
            HierarchicalSymbolEffectAccessor::GetFillStyleImpl,
            HierarchicalSymbolEffectAccessor::SetFillStyleImpl,
        };
        return &HierarchicalSymbolEffectAccessorImpl;
    }

    struct HierarchicalSymbolEffectPeer {
        virtual ~HierarchicalSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor()
    {
        static const GENERATED_ArkUIHoverEventAccessor HoverEventAccessorImpl {
            HoverEventAccessor::DestroyPeerImpl,
            HoverEventAccessor::ConstructImpl,
            HoverEventAccessor::GetFinalizerImpl,
            HoverEventAccessor::GetXImpl,
            HoverEventAccessor::SetXImpl,
            HoverEventAccessor::GetYImpl,
            HoverEventAccessor::SetYImpl,
            HoverEventAccessor::GetWindowXImpl,
            HoverEventAccessor::SetWindowXImpl,
            HoverEventAccessor::GetWindowYImpl,
            HoverEventAccessor::SetWindowYImpl,
            HoverEventAccessor::GetDisplayXImpl,
            HoverEventAccessor::SetDisplayXImpl,
            HoverEventAccessor::GetDisplayYImpl,
            HoverEventAccessor::SetDisplayYImpl,
            HoverEventAccessor::StopPropagationImpl,
        };
        return &HoverEventAccessorImpl;
    }

    struct HoverEventPeer {
        virtual ~HoverEventPeer() = default;
    };
    const GENERATED_ArkUIHttpAuthHandlerAccessor* GetHttpAuthHandlerAccessor()
    {
        static const GENERATED_ArkUIHttpAuthHandlerAccessor HttpAuthHandlerAccessorImpl {
            HttpAuthHandlerAccessor::DestroyPeerImpl,
            HttpAuthHandlerAccessor::ConstructImpl,
            HttpAuthHandlerAccessor::GetFinalizerImpl,
            HttpAuthHandlerAccessor::ConfirmImpl,
            HttpAuthHandlerAccessor::CancelImpl,
            HttpAuthHandlerAccessor::IsHttpAuthInfoSavedImpl,
        };
        return &HttpAuthHandlerAccessorImpl;
    }

    struct HttpAuthHandlerPeer {
        virtual ~HttpAuthHandlerPeer() = default;
    };
    const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor()
    {
        static const GENERATED_ArkUIImageAnalyzerControllerAccessor ImageAnalyzerControllerAccessorImpl {
            ImageAnalyzerControllerAccessor::DestroyPeerImpl,
            ImageAnalyzerControllerAccessor::ConstructImpl,
            ImageAnalyzerControllerAccessor::GetFinalizerImpl,
            ImageAnalyzerControllerAccessor::GetImageAnalyzerSupportTypesImpl,
        };
        return &ImageAnalyzerControllerAccessorImpl;
    }

    struct ImageAnalyzerControllerPeer {
        virtual ~ImageAnalyzerControllerPeer() = default;
    };
    const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor()
    {
        static const GENERATED_ArkUIImageAttachmentAccessor ImageAttachmentAccessorImpl {
            ImageAttachmentAccessor::DestroyPeerImpl,
            ImageAttachmentAccessor::ConstructImpl,
            ImageAttachmentAccessor::GetFinalizerImpl,
            ImageAttachmentAccessor::GetValueImpl,
            ImageAttachmentAccessor::GetSizeImpl,
            ImageAttachmentAccessor::GetVerticalAlignImpl,
            ImageAttachmentAccessor::GetObjectFitImpl,
            ImageAttachmentAccessor::GetLayoutStyleImpl,
            ImageAttachmentAccessor::GetColorFilterImpl,
        };
        return &ImageAttachmentAccessorImpl;
    }

    struct ImageAttachmentPeer {
        virtual ~ImageAttachmentPeer() = default;
    };
    const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
    {
        static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
            ImageBitmapAccessor::DestroyPeerImpl,
            ImageBitmapAccessor::ConstructImpl,
            ImageBitmapAccessor::GetFinalizerImpl,
            ImageBitmapAccessor::CloseImpl,
            ImageBitmapAccessor::GetHeightImpl,
            ImageBitmapAccessor::SetHeightImpl,
            ImageBitmapAccessor::GetWidthImpl,
            ImageBitmapAccessor::SetWidthImpl,
        };
        return &ImageBitmapAccessorImpl;
    }

    struct ImageBitmapPeer {
        virtual ~ImageBitmapPeer() = default;
    };
    const GENERATED_ArkUIImageDataAccessor* GetImageDataAccessor()
    {
        static const GENERATED_ArkUIImageDataAccessor ImageDataAccessorImpl {
            ImageDataAccessor::DestroyPeerImpl,
            ImageDataAccessor::ConstructImpl,
            ImageDataAccessor::GetFinalizerImpl,
            ImageDataAccessor::GetDataImpl,
            ImageDataAccessor::SetDataImpl,
            ImageDataAccessor::GetHeightImpl,
            ImageDataAccessor::SetHeightImpl,
            ImageDataAccessor::GetWidthImpl,
            ImageDataAccessor::SetWidthImpl,
        };
        return &ImageDataAccessorImpl;
    }

    struct ImageDataPeer {
        virtual ~ImageDataPeer() = default;
    };
    const GENERATED_ArkUIIndicatorComponentControllerAccessor* GetIndicatorComponentControllerAccessor()
    {
        static const GENERATED_ArkUIIndicatorComponentControllerAccessor IndicatorComponentControllerAccessorImpl {
            IndicatorComponentControllerAccessor::DestroyPeerImpl,
            IndicatorComponentControllerAccessor::ConstructImpl,
            IndicatorComponentControllerAccessor::GetFinalizerImpl,
            IndicatorComponentControllerAccessor::ShowNextImpl,
            IndicatorComponentControllerAccessor::ShowPreviousImpl,
            IndicatorComponentControllerAccessor::ChangeIndexImpl,
        };
        return &IndicatorComponentControllerAccessorImpl;
    }

    struct IndicatorComponentControllerPeer {
        virtual ~IndicatorComponentControllerPeer() = default;
    };
    const GENERATED_ArkUIIUIContextAccessor* GetIUIContextAccessor()
    {
        static const GENERATED_ArkUIIUIContextAccessor IUIContextAccessorImpl {
            IUIContextAccessor::FreezeUINode0Impl,
            IUIContextAccessor::FreezeUINode1Impl,
            IUIContextAccessor::OpenBindSheetImpl,
            IUIContextAccessor::UpdateBindSheetImpl,
            IUIContextAccessor::CloseBindSheetImpl,
        };
        return &IUIContextAccessorImpl;
    }

    const GENERATED_ArkUIJsGeolocationAccessor* GetJsGeolocationAccessor()
    {
        static const GENERATED_ArkUIJsGeolocationAccessor JsGeolocationAccessorImpl {
            JsGeolocationAccessor::DestroyPeerImpl,
            JsGeolocationAccessor::ConstructImpl,
            JsGeolocationAccessor::GetFinalizerImpl,
            JsGeolocationAccessor::InvokeImpl,
        };
        return &JsGeolocationAccessorImpl;
    }

    struct JsGeolocationPeer {
        virtual ~JsGeolocationPeer() = default;
    };
    const GENERATED_ArkUIJsResultAccessor* GetJsResultAccessor()
    {
        static const GENERATED_ArkUIJsResultAccessor JsResultAccessorImpl {
            JsResultAccessor::DestroyPeerImpl,
            JsResultAccessor::ConstructImpl,
            JsResultAccessor::GetFinalizerImpl,
            JsResultAccessor::HandleCancelImpl,
            JsResultAccessor::HandleConfirmImpl,
            JsResultAccessor::HandlePromptConfirmImpl,
        };
        return &JsResultAccessorImpl;
    }

    struct JsResultPeer {
        virtual ~JsResultPeer() = default;
    };
    const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor()
    {
        static const GENERATED_ArkUIKeyEventAccessor KeyEventAccessorImpl {
            KeyEventAccessor::DestroyPeerImpl,
            KeyEventAccessor::ConstructImpl,
            KeyEventAccessor::GetFinalizerImpl,
            KeyEventAccessor::GetTypeImpl,
            KeyEventAccessor::SetTypeImpl,
            KeyEventAccessor::GetKeyCodeImpl,
            KeyEventAccessor::SetKeyCodeImpl,
            KeyEventAccessor::GetKeyTextImpl,
            KeyEventAccessor::SetKeyTextImpl,
            KeyEventAccessor::GetKeySourceImpl,
            KeyEventAccessor::SetKeySourceImpl,
            KeyEventAccessor::GetDeviceIdImpl,
            KeyEventAccessor::SetDeviceIdImpl,
            KeyEventAccessor::GetMetaKeyImpl,
            KeyEventAccessor::SetMetaKeyImpl,
            KeyEventAccessor::GetTimestampImpl,
            KeyEventAccessor::SetTimestampImpl,
            KeyEventAccessor::GetStopPropagationImpl,
            KeyEventAccessor::SetStopPropagationImpl,
            KeyEventAccessor::GetIntentionCodeImpl,
            KeyEventAccessor::SetIntentionCodeImpl,
            KeyEventAccessor::GetGetModifierKeyStateImpl,
            KeyEventAccessor::SetGetModifierKeyStateImpl,
            KeyEventAccessor::GetUnicodeImpl,
            KeyEventAccessor::SetUnicodeImpl,
        };
        return &KeyEventAccessorImpl;
    }

    struct KeyEventPeer {
        virtual ~KeyEventPeer() = default;
    };
    const GENERATED_ArkUILayoutableAccessor* GetLayoutableAccessor()
    {
        static const GENERATED_ArkUILayoutableAccessor LayoutableAccessorImpl {
            LayoutableAccessor::DestroyPeerImpl,
            LayoutableAccessor::ConstructImpl,
            LayoutableAccessor::GetFinalizerImpl,
            LayoutableAccessor::LayoutImpl,
            LayoutableAccessor::GetMarginImpl,
            LayoutableAccessor::GetPaddingImpl,
            LayoutableAccessor::GetBorderWidthImpl,
            LayoutableAccessor::GetMeasureResultImpl,
            LayoutableAccessor::SetMeasureResultImpl,
            LayoutableAccessor::GetUniqueIdImpl,
            LayoutableAccessor::SetUniqueIdImpl,
        };
        return &LayoutableAccessorImpl;
    }

    struct LayoutablePeer {
        virtual ~LayoutablePeer() = default;
    };
    const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
    {
        static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
            LayoutManagerAccessor::DestroyPeerImpl,
            LayoutManagerAccessor::ConstructImpl,
            LayoutManagerAccessor::GetFinalizerImpl,
            LayoutManagerAccessor::GetLineCountImpl,
            LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
            LayoutManagerAccessor::GetLineMetricsImpl,
            LayoutManagerAccessor::GetRectsForRangeImpl,
        };
        return &LayoutManagerAccessorImpl;
    }

    struct LayoutManagerPeer {
        virtual ~LayoutManagerPeer() = default;
    };
    const GENERATED_ArkUILayoutPolicyAccessor* GetLayoutPolicyAccessor()
    {
        static const GENERATED_ArkUILayoutPolicyAccessor LayoutPolicyAccessorImpl {
            LayoutPolicyAccessor::DestroyPeerImpl,
            LayoutPolicyAccessor::ConstructImpl,
            LayoutPolicyAccessor::GetFinalizerImpl,
            LayoutPolicyAccessor::GetMatchParentImpl,
            LayoutPolicyAccessor::GetWrapContentImpl,
            LayoutPolicyAccessor::GetFixAtIdealSizeImpl,
        };
        return &LayoutPolicyAccessorImpl;
    }

    struct LayoutPolicyPeer {
        virtual ~LayoutPolicyPeer() = default;
    };
    const GENERATED_ArkUILazyBuildAccessor* GetLazyBuildAccessor()
    {
        static const GENERATED_ArkUILazyBuildAccessor LazyBuildAccessorImpl {
            LazyBuildAccessor::ApplyLazyBuilderImpl,
            LazyBuildAccessor::SetListItemLazyBuilderImpl,
            LazyBuildAccessor::SetTabContentLazyBuilderImpl,
        };
        return &LazyBuildAccessorImpl;
    }

    const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
    {
        static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
            LazyForEachOpsAccessor::NotifyChangeImpl,
            LazyForEachOpsAccessor::SyncImpl,
            LazyForEachOpsAccessor::SyncOnMoveOpsImpl,
        };
        return &LazyForEachOpsAccessorImpl;
    }

    const GENERATED_ArkUILetterSpacingStyleAccessor* GetLetterSpacingStyleAccessor()
    {
        static const GENERATED_ArkUILetterSpacingStyleAccessor LetterSpacingStyleAccessorImpl {
            LetterSpacingStyleAccessor::DestroyPeerImpl,
            LetterSpacingStyleAccessor::ConstructImpl,
            LetterSpacingStyleAccessor::GetFinalizerImpl,
            LetterSpacingStyleAccessor::GetLetterSpacingImpl,
        };
        return &LetterSpacingStyleAccessorImpl;
    }

    struct LetterSpacingStylePeer {
        virtual ~LetterSpacingStylePeer() = default;
    };

    const GENERATED_ArkUILevelOrderExtenderAccessor* GetLevelOrderExtenderAccessor()
    {
        static const GENERATED_ArkUILevelOrderExtenderAccessor LevelOrderExtenderAccessorImpl {
            LevelOrderExtenderAccessor::DestroyPeerImpl,
            LevelOrderExtenderAccessor::ConstructImpl,
            LevelOrderExtenderAccessor::GetFinalizerImpl,
            LevelOrderExtenderAccessor::ClampImpl,
            LevelOrderExtenderAccessor::GetOrderImpl,
        };
        return &LevelOrderExtenderAccessorImpl;
    }

    struct LevelOrderExtenderPeer {
        virtual ~LevelOrderExtenderPeer() = default;
    };
    const GENERATED_ArkUILifeCycleAccessor* GetLifeCycleAccessor()
    {
        static const GENERATED_ArkUILifeCycleAccessor LifeCycleAccessorImpl {
            LifeCycleAccessor::DestroyPeerImpl,
            LifeCycleAccessor::ConstructImpl,
            LifeCycleAccessor::GetFinalizerImpl,
            LifeCycleAccessor::AboutToAppearImpl,
            LifeCycleAccessor::AboutToDisappearImpl,
            LifeCycleAccessor::OnDidBuildImpl,
            LifeCycleAccessor::BuildImpl,
        };
        return &LifeCycleAccessorImpl;
    }

    struct LifeCyclePeer {
        virtual ~LifeCyclePeer() = default;
    };
    const GENERATED_ArkUILinearGradientAccessor* GetLinearGradientAccessor()
    {
        static const GENERATED_ArkUILinearGradientAccessor LinearGradientAccessorImpl {
            LinearGradientAccessor::DestroyPeerImpl,
            LinearGradientAccessor::ConstructImpl,
            LinearGradientAccessor::GetFinalizerImpl,
        };
        return &LinearGradientAccessorImpl;
    }

    struct LinearGradientPeer {
        virtual ~LinearGradientPeer() = default;
    };
    const GENERATED_ArkUILinearIndicatorControllerAccessor* GetLinearIndicatorControllerAccessor()
    {
        static const GENERATED_ArkUILinearIndicatorControllerAccessor LinearIndicatorControllerAccessorImpl {
            LinearIndicatorControllerAccessor::DestroyPeerImpl,
            LinearIndicatorControllerAccessor::ConstructImpl,
            LinearIndicatorControllerAccessor::GetFinalizerImpl,
            LinearIndicatorControllerAccessor::SetProgressImpl,
            LinearIndicatorControllerAccessor::StartImpl,
            LinearIndicatorControllerAccessor::PauseImpl,
            LinearIndicatorControllerAccessor::StopImpl,
        };
        return &LinearIndicatorControllerAccessorImpl;
    }

    struct LinearIndicatorControllerPeer {
        virtual ~LinearIndicatorControllerPeer() = default;
    };
    const GENERATED_ArkUILineHeightStyleAccessor* GetLineHeightStyleAccessor()
    {
        static const GENERATED_ArkUILineHeightStyleAccessor LineHeightStyleAccessorImpl {
            LineHeightStyleAccessor::DestroyPeerImpl,
            LineHeightStyleAccessor::ConstructImpl,
            LineHeightStyleAccessor::GetFinalizerImpl,
            LineHeightStyleAccessor::GetLineHeightImpl,
        };
        return &LineHeightStyleAccessorImpl;
    }

    struct LineHeightStylePeer {
        virtual ~LineHeightStylePeer() = default;
    };
    const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor()
    {
        static const GENERATED_ArkUIListScrollerAccessor ListScrollerAccessorImpl {
            ListScrollerAccessor::DestroyPeerImpl,
            ListScrollerAccessor::ConstructImpl,
            ListScrollerAccessor::GetFinalizerImpl,
            ListScrollerAccessor::GetItemRectInGroupImpl,
            ListScrollerAccessor::ScrollToItemInGroupImpl,
            ListScrollerAccessor::CloseAllSwipeActionsImpl,
            ListScrollerAccessor::GetVisibleListContentInfoImpl,
        };
        return &ListScrollerAccessorImpl;
    }

    struct ListScrollerPeer {
        virtual ~ListScrollerPeer() = default;
    };
    const GENERATED_ArkUILongPressGestureEventAccessor* GetLongPressGestureEventAccessor()
    {
        static const GENERATED_ArkUILongPressGestureEventAccessor LongPressGestureEventAccessorImpl {
            LongPressGestureEventAccessor::DestroyPeerImpl,
            LongPressGestureEventAccessor::ConstructImpl,
            LongPressGestureEventAccessor::GetFinalizerImpl,
            LongPressGestureEventAccessor::GetRepeatImpl,
            LongPressGestureEventAccessor::SetRepeatImpl,
        };
        return &LongPressGestureEventAccessorImpl;
    }

    struct LongPressGestureEventPeer {
        virtual ~LongPressGestureEventPeer() = default;
    };
    const GENERATED_ArkUILongPressRecognizerAccessor* GetLongPressRecognizerAccessor()
    {
        static const GENERATED_ArkUILongPressRecognizerAccessor LongPressRecognizerAccessorImpl {
            LongPressRecognizerAccessor::DestroyPeerImpl,
            LongPressRecognizerAccessor::ConstructImpl,
            LongPressRecognizerAccessor::GetFinalizerImpl,
            LongPressRecognizerAccessor::IsRepeatImpl,
            LongPressRecognizerAccessor::GetDurationImpl,
        };
        return &LongPressRecognizerAccessorImpl;
    }

    struct LongPressRecognizerPeer {
        virtual ~LongPressRecognizerPeer() = default;
    };
    const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor()
    {
        static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
            Matrix2DAccessor::DestroyPeerImpl,
            Matrix2DAccessor::Construct0Impl,
            Matrix2DAccessor::Construct1Impl,
            Matrix2DAccessor::GetFinalizerImpl,
            Matrix2DAccessor::IdentityImpl,
            Matrix2DAccessor::InvertImpl,
            Matrix2DAccessor::RotateImpl,
            Matrix2DAccessor::TranslateImpl,
            Matrix2DAccessor::ScaleImpl,
            Matrix2DAccessor::GetScaleXImpl,
            Matrix2DAccessor::SetScaleXImpl,
            Matrix2DAccessor::GetScaleYImpl,
            Matrix2DAccessor::SetScaleYImpl,
            Matrix2DAccessor::GetRotateXImpl,
            Matrix2DAccessor::SetRotateXImpl,
            Matrix2DAccessor::GetRotateYImpl,
            Matrix2DAccessor::SetRotateYImpl,
            Matrix2DAccessor::GetTranslateXImpl,
            Matrix2DAccessor::SetTranslateXImpl,
            Matrix2DAccessor::GetTranslateYImpl,
            Matrix2DAccessor::SetTranslateYImpl,
        };
        return &Matrix2DAccessorImpl;
    }

    struct Matrix2DPeer {
        virtual ~Matrix2DPeer() = default;
    };
    const GENERATED_ArkUIMeasurableAccessor* GetMeasurableAccessor()
    {
        static const GENERATED_ArkUIMeasurableAccessor MeasurableAccessorImpl {
            MeasurableAccessor::DestroyPeerImpl,
            MeasurableAccessor::ConstructImpl,
            MeasurableAccessor::GetFinalizerImpl,
            MeasurableAccessor::MeasureImpl,
            MeasurableAccessor::GetMarginImpl,
            MeasurableAccessor::GetPaddingImpl,
            MeasurableAccessor::GetBorderWidthImpl,
            MeasurableAccessor::GetUniqueIdImpl,
            MeasurableAccessor::SetUniqueIdImpl,
        };
        return &MeasurableAccessorImpl;
    }

    struct MeasurablePeer {
        virtual ~MeasurablePeer() = default;
    };
    const GENERATED_ArkUIMenuItemConfigurationAccessor* GetMenuItemConfigurationAccessor()
    {
        static const GENERATED_ArkUIMenuItemConfigurationAccessor MenuItemConfigurationAccessorImpl {
            MenuItemConfigurationAccessor::DestroyPeerImpl,
            MenuItemConfigurationAccessor::ConstructImpl,
            MenuItemConfigurationAccessor::GetFinalizerImpl,
            MenuItemConfigurationAccessor::TriggerSelectImpl,
            MenuItemConfigurationAccessor::GetEnabledImpl,
            MenuItemConfigurationAccessor::SetEnabledImpl,
            MenuItemConfigurationAccessor::GetContentModifierImpl,
            MenuItemConfigurationAccessor::SetContentModifierImpl,
            MenuItemConfigurationAccessor::GetValueImpl,
            MenuItemConfigurationAccessor::SetValueImpl,
            MenuItemConfigurationAccessor::GetIconImpl,
            MenuItemConfigurationAccessor::SetIconImpl,
            MenuItemConfigurationAccessor::GetSymbolIconImpl,
            MenuItemConfigurationAccessor::SetSymbolIconImpl,
            MenuItemConfigurationAccessor::GetSelectedImpl,
            MenuItemConfigurationAccessor::SetSelectedImpl,
            MenuItemConfigurationAccessor::GetIndexImpl,
            MenuItemConfigurationAccessor::SetIndexImpl,
        };
        return &MenuItemConfigurationAccessorImpl;
    }

    struct MenuItemConfigurationPeer {
        virtual ~MenuItemConfigurationPeer() = default;
    };
    const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor()
    {
        static const GENERATED_ArkUIMouseEventAccessor MouseEventAccessorImpl {
            MouseEventAccessor::DestroyPeerImpl,
            MouseEventAccessor::ConstructImpl,
            MouseEventAccessor::GetFinalizerImpl,
            MouseEventAccessor::GetButtonImpl,
            MouseEventAccessor::SetButtonImpl,
            MouseEventAccessor::GetActionImpl,
            MouseEventAccessor::SetActionImpl,
            MouseEventAccessor::GetDisplayXImpl,
            MouseEventAccessor::SetDisplayXImpl,
            MouseEventAccessor::GetDisplayYImpl,
            MouseEventAccessor::SetDisplayYImpl,
            MouseEventAccessor::GetWindowXImpl,
            MouseEventAccessor::SetWindowXImpl,
            MouseEventAccessor::GetWindowYImpl,
            MouseEventAccessor::SetWindowYImpl,
            MouseEventAccessor::GetXImpl,
            MouseEventAccessor::SetXImpl,
            MouseEventAccessor::GetYImpl,
            MouseEventAccessor::SetYImpl,
            MouseEventAccessor::GetStopPropagationImpl,
            MouseEventAccessor::SetStopPropagationImpl,
            MouseEventAccessor::GetRawDeltaXImpl,
            MouseEventAccessor::SetRawDeltaXImpl,
            MouseEventAccessor::GetRawDeltaYImpl,
            MouseEventAccessor::SetRawDeltaYImpl,
            MouseEventAccessor::GetPressedButtonsImpl,
            MouseEventAccessor::SetPressedButtonsImpl,
        };
        return &MouseEventAccessorImpl;
    }

    struct MouseEventPeer {
        virtual ~MouseEventPeer() = default;
    };
    const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
    {
        static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
            MutableStyledStringAccessor::DestroyPeerImpl,
            MutableStyledStringAccessor::ConstructImpl,
            MutableStyledStringAccessor::GetFinalizerImpl,
            MutableStyledStringAccessor::ReplaceStringImpl,
            MutableStyledStringAccessor::InsertStringImpl,
            MutableStyledStringAccessor::RemoveStringImpl,
            MutableStyledStringAccessor::ReplaceStyleImpl,
            MutableStyledStringAccessor::SetStyleImpl,
            MutableStyledStringAccessor::RemoveStyleImpl,
            MutableStyledStringAccessor::RemoveStylesImpl,
            MutableStyledStringAccessor::ClearStylesImpl,
            MutableStyledStringAccessor::ReplaceStyledStringImpl,
            MutableStyledStringAccessor::InsertStyledStringImpl,
            MutableStyledStringAccessor::AppendStyledStringImpl,
        };
        return &MutableStyledStringAccessorImpl;
    }

    struct MutableStyledStringPeer {
        virtual ~MutableStyledStringPeer() = default;
    };
    const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor()
    {
        static const GENERATED_ArkUINavDestinationContextAccessor NavDestinationContextAccessorImpl {
            NavDestinationContextAccessor::DestroyPeerImpl,
            NavDestinationContextAccessor::ConstructImpl,
            NavDestinationContextAccessor::GetFinalizerImpl,
            NavDestinationContextAccessor::GetConfigInRouteMapImpl,
            NavDestinationContextAccessor::GetPathInfoImpl,
            NavDestinationContextAccessor::SetPathInfoImpl,
            NavDestinationContextAccessor::GetPathStackImpl,
            NavDestinationContextAccessor::SetPathStackImpl,
            NavDestinationContextAccessor::GetNavDestinationIdImpl,
            NavDestinationContextAccessor::SetNavDestinationIdImpl,
        };
        return &NavDestinationContextAccessorImpl;
    }

    struct NavDestinationContextPeer {
        virtual ~NavDestinationContextPeer() = default;
    };
    const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
    {
        static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
            NavExtenderAccessor::SetNavigationOptionsImpl,
            NavExtenderAccessor::SetUpdateStackCallbackImpl,
            NavExtenderAccessor::SyncStackImpl,
            NavExtenderAccessor::CheckNeedCreateImpl,
            NavExtenderAccessor::SetNavDestinationNodeImpl,
            NavExtenderAccessor::PushPathImpl,
            NavExtenderAccessor::ReplacePathImpl,
            NavExtenderAccessor::PopImpl,
            NavExtenderAccessor::SetOnPopCallbackImpl,
            NavExtenderAccessor::GetIdByIndexImpl,
            NavExtenderAccessor::GetIdByNameImpl,
            NavExtenderAccessor::PopToIndexImpl,
            NavExtenderAccessor::PopToNameImpl,
            NavExtenderAccessor::SetCreateNavDestinationCallbackImpl,
            NavExtenderAccessor::GetRouteMapInConfigImpl,
        };
        return &NavExtenderAccessorImpl;
    }

    const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor()
    {
        static const GENERATED_ArkUINavigationTransitionProxyAccessor NavigationTransitionProxyAccessorImpl {
            NavigationTransitionProxyAccessor::DestroyPeerImpl,
            NavigationTransitionProxyAccessor::ConstructImpl,
            NavigationTransitionProxyAccessor::GetFinalizerImpl,
            NavigationTransitionProxyAccessor::FinishTransitionImpl,
            NavigationTransitionProxyAccessor::GetFromImpl,
            NavigationTransitionProxyAccessor::SetFromImpl,
            NavigationTransitionProxyAccessor::GetToImpl,
            NavigationTransitionProxyAccessor::SetToImpl,
            NavigationTransitionProxyAccessor::GetIsInteractiveImpl,
            NavigationTransitionProxyAccessor::SetIsInteractiveImpl,
            NavigationTransitionProxyAccessor::GetCancelTransitionImpl,
            NavigationTransitionProxyAccessor::SetCancelTransitionImpl,
            NavigationTransitionProxyAccessor::GetUpdateTransitionImpl,
            NavigationTransitionProxyAccessor::SetUpdateTransitionImpl,
        };
        return &NavigationTransitionProxyAccessorImpl;
    }

    struct NavigationTransitionProxyPeer {
        virtual ~NavigationTransitionProxyPeer() = default;
    };
    const GENERATED_ArkUINavPathInfoAccessor* GetNavPathInfoAccessor()
    {
        static const GENERATED_ArkUINavPathInfoAccessor NavPathInfoAccessorImpl {
            NavPathInfoAccessor::DestroyPeerImpl,
            NavPathInfoAccessor::ConstructImpl,
            NavPathInfoAccessor::GetFinalizerImpl,
            NavPathInfoAccessor::GetNameImpl,
            NavPathInfoAccessor::SetNameImpl,
            NavPathInfoAccessor::GetParamImpl,
            NavPathInfoAccessor::SetParamImpl,
            NavPathInfoAccessor::GetOnPopImpl,
            NavPathInfoAccessor::SetOnPopImpl,
            NavPathInfoAccessor::GetIsEntryImpl,
            NavPathInfoAccessor::SetIsEntryImpl,
            NavPathInfoAccessor::GetNavDestinationIdImpl,
            NavPathInfoAccessor::SetNavDestinationIdImpl,
        };
        return &NavPathInfoAccessorImpl;
    }

    struct NavPathInfoPeer {
        virtual ~NavPathInfoPeer() = default;
    };
    const GENERATED_ArkUINavPathStackAccessor* GetNavPathStackAccessor()
    {
        static const GENERATED_ArkUINavPathStackAccessor NavPathStackAccessorImpl {
            NavPathStackAccessor::DestroyPeerImpl,
            NavPathStackAccessor::ConstructImpl,
            NavPathStackAccessor::GetFinalizerImpl,
            NavPathStackAccessor::PushPath0Impl,
            NavPathStackAccessor::PushPath1Impl,
            NavPathStackAccessor::PushDestination0Impl,
            NavPathStackAccessor::PushDestination1Impl,
            NavPathStackAccessor::PushPathByName0Impl,
            NavPathStackAccessor::PushPathByName1Impl,
            NavPathStackAccessor::PushDestinationByName0Impl,
            NavPathStackAccessor::PushDestinationByName1Impl,
            NavPathStackAccessor::ReplacePath0Impl,
            NavPathStackAccessor::ReplacePath1Impl,
            NavPathStackAccessor::ReplaceDestinationImpl,
            NavPathStackAccessor::ReplacePathByNameImpl,
            NavPathStackAccessor::RemoveByIndexesImpl,
            NavPathStackAccessor::RemoveByNameImpl,
            NavPathStackAccessor::RemoveByNavDestinationIdImpl,
            NavPathStackAccessor::Pop0Impl,
            NavPathStackAccessor::Pop1Impl,
            NavPathStackAccessor::PopToName0Impl,
            NavPathStackAccessor::PopToName1Impl,
            NavPathStackAccessor::PopToIndex0Impl,
            NavPathStackAccessor::PopToIndex1Impl,
            NavPathStackAccessor::MoveToTopImpl,
            NavPathStackAccessor::MoveIndexToTopImpl,
            NavPathStackAccessor::ClearImpl,
            NavPathStackAccessor::GetAllPathNameImpl,
            NavPathStackAccessor::GetParamByIndexImpl,
            NavPathStackAccessor::GetParamByNameImpl,
            NavPathStackAccessor::GetIndexByNameImpl,
            NavPathStackAccessor::GetParentImpl,
            NavPathStackAccessor::SizeImpl,
            NavPathStackAccessor::DisableAnimationImpl,
            NavPathStackAccessor::SetInterceptionImpl,
            NavPathStackAccessor::GetPathStackImpl,
            NavPathStackAccessor::SetPathStackImpl,
        };
        return &NavPathStackAccessorImpl;
    }

    struct NavPathStackPeer {
        virtual ~NavPathStackPeer() = default;
    };
    const GENERATED_ArkUINodeContainerOpsAccessor* GetNodeContainerOpsAccessor()
    {
        static const GENERATED_ArkUINodeContainerOpsAccessor NodeContainerOpsAccessorImpl {
            NodeContainerOpsAccessor::NodeContainerOpsConstructImpl,
            NodeContainerOpsAccessor::NodeContainerSetNodeContainerOptionsImpl,
            NodeContainerOpsAccessor::AddNodeContainerRootNodeImpl,
            NodeContainerOpsAccessor::SetAboutToAppearImpl,
            NodeContainerOpsAccessor::SetAboutToDisappearImpl,
            NodeContainerOpsAccessor::SetAboutToResizeImpl,
            NodeContainerOpsAccessor::SetOnAttachImpl,
            NodeContainerOpsAccessor::SetOnDetachImpl,
            NodeContainerOpsAccessor::SetOnTouchEventImpl,
            NodeContainerOpsAccessor::SetOnDestoryEventImpl,
        };
        return &NodeContainerOpsAccessorImpl;
    }

    const GENERATED_ArkUINodeContentExtenderAccessor* GetNodeContentExtenderAccessor()
    {
        static const GENERATED_ArkUINodeContentExtenderAccessor NodeContentExtenderAccessorImpl {
            NodeContentExtenderAccessor::ConstructorNodeContentImpl,
            NodeContentExtenderAccessor::GetDestroyImpl,
            NodeContentExtenderAccessor::AddFrameNodeImpl,
            NodeContentExtenderAccessor::RemoveFrameNodeImpl,
        };
        return &NodeContentExtenderAccessorImpl;
    }

    const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor()
    {
        static const GENERATED_ArkUIOffscreenCanvasAccessor OffscreenCanvasAccessorImpl {
            OffscreenCanvasAccessor::DestroyPeerImpl,
            OffscreenCanvasAccessor::ConstructImpl,
            OffscreenCanvasAccessor::GetFinalizerImpl,
            OffscreenCanvasAccessor::TransferToImageBitmapImpl,
            OffscreenCanvasAccessor::GetContext2dImpl,
            OffscreenCanvasAccessor::GetHeightImpl,
            OffscreenCanvasAccessor::SetHeightImpl,
            OffscreenCanvasAccessor::GetWidthImpl,
            OffscreenCanvasAccessor::SetWidthImpl,
        };
        return &OffscreenCanvasAccessorImpl;
    }

    struct OffscreenCanvasPeer {
        virtual ~OffscreenCanvasPeer() = default;
    };
    const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor()
    {
        static const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor OffscreenCanvasRenderingContext2DAccessorImpl {
            OffscreenCanvasRenderingContext2DAccessor::DestroyPeerImpl,
            OffscreenCanvasRenderingContext2DAccessor::ConstructImpl,
            OffscreenCanvasRenderingContext2DAccessor::GetFinalizerImpl,
            OffscreenCanvasRenderingContext2DAccessor::ToDataURLImpl,
            OffscreenCanvasRenderingContext2DAccessor::TransferToImageBitmapImpl,
        };
        return &OffscreenCanvasRenderingContext2DAccessorImpl;
    }

    struct OffscreenCanvasRenderingContext2DPeer {
        virtual ~OffscreenCanvasRenderingContext2DPeer() = default;
    };
    const GENERATED_ArkUIPanGestureEventAccessor* GetPanGestureEventAccessor()
    {
        static const GENERATED_ArkUIPanGestureEventAccessor PanGestureEventAccessorImpl {
            PanGestureEventAccessor::DestroyPeerImpl,
            PanGestureEventAccessor::ConstructImpl,
            PanGestureEventAccessor::GetFinalizerImpl,
            PanGestureEventAccessor::GetOffsetXImpl,
            PanGestureEventAccessor::SetOffsetXImpl,
            PanGestureEventAccessor::GetOffsetYImpl,
            PanGestureEventAccessor::SetOffsetYImpl,
            PanGestureEventAccessor::GetVelocityXImpl,
            PanGestureEventAccessor::SetVelocityXImpl,
            PanGestureEventAccessor::GetVelocityYImpl,
            PanGestureEventAccessor::SetVelocityYImpl,
            PanGestureEventAccessor::GetVelocityImpl,
            PanGestureEventAccessor::SetVelocityImpl,
        };
        return &PanGestureEventAccessorImpl;
    }

    struct PanGestureEventPeer {
        virtual ~PanGestureEventPeer() = default;
    };
    const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor()
    {
        static const GENERATED_ArkUIPanGestureOptionsAccessor PanGestureOptionsAccessorImpl {
            PanGestureOptionsAccessor::DestroyPeerImpl,
            PanGestureOptionsAccessor::ConstructImpl,
            PanGestureOptionsAccessor::GetFinalizerImpl,
            PanGestureOptionsAccessor::SetDirectionImpl,
            PanGestureOptionsAccessor::SetDistanceImpl,
            PanGestureOptionsAccessor::SetFingersImpl,
            PanGestureOptionsAccessor::GetDirectionImpl,
            PanGestureOptionsAccessor::GetDistanceImpl,
        };
        return &PanGestureOptionsAccessorImpl;
    }

    struct PanGestureOptionsPeer {
        virtual ~PanGestureOptionsPeer() = default;
    };
    const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor()
    {
        static const GENERATED_ArkUIPanRecognizerAccessor PanRecognizerAccessorImpl {
            PanRecognizerAccessor::DestroyPeerImpl,
            PanRecognizerAccessor::ConstructImpl,
            PanRecognizerAccessor::GetFinalizerImpl,
            PanRecognizerAccessor::GetPanGestureOptionsImpl,
        };
        return &PanRecognizerAccessorImpl;
    }

    struct PanRecognizerPeer {
        virtual ~PanRecognizerPeer() = default;
    };
    const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor()
    {
        static const GENERATED_ArkUIParagraphStyleAccessor ParagraphStyleAccessorImpl {
            ParagraphStyleAccessor::DestroyPeerImpl,
            ParagraphStyleAccessor::ConstructImpl,
            ParagraphStyleAccessor::GetFinalizerImpl,
            ParagraphStyleAccessor::GetTextAlignImpl,
            ParagraphStyleAccessor::GetTextIndentImpl,
            ParagraphStyleAccessor::GetMaxLinesImpl,
            ParagraphStyleAccessor::GetOverflowImpl,
            ParagraphStyleAccessor::GetWordBreakImpl,
            ParagraphStyleAccessor::GetLeadingMarginImpl,
            ParagraphStyleAccessor::GetParagraphSpacingImpl,
        };
        return &ParagraphStyleAccessorImpl;
    }

    struct ParagraphStylePeer {
        virtual ~ParagraphStylePeer() = default;
    };
    const GENERATED_ArkUIPasteEventAccessor* GetPasteEventAccessor()
    {
        static const GENERATED_ArkUIPasteEventAccessor PasteEventAccessorImpl {
            PasteEventAccessor::DestroyPeerImpl,
            PasteEventAccessor::ConstructImpl,
            PasteEventAccessor::GetFinalizerImpl,
            PasteEventAccessor::PreventDefaultImpl,
        };
        return &PasteEventAccessorImpl;
    }

    struct PasteEventPeer {
        virtual ~PasteEventPeer() = default;
    };
    const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor()
    {
        static const GENERATED_ArkUIPath2DAccessor Path2DAccessorImpl {
            Path2DAccessor::DestroyPeerImpl,
            Path2DAccessor::Construct0Impl,
            Path2DAccessor::Construct1Impl,
            Path2DAccessor::Construct2Impl,
            Path2DAccessor::Construct3Impl,
            Path2DAccessor::Construct4Impl,
            Path2DAccessor::Construct5Impl,
            Path2DAccessor::GetFinalizerImpl,
            Path2DAccessor::AddPathImpl,
        };
        return &Path2DAccessorImpl;
    }

    struct Path2DPeer {
        virtual ~Path2DPeer() = default;
    };
    const GENERATED_ArkUIPatternLockControllerAccessor* GetPatternLockControllerAccessor()
    {
        static const GENERATED_ArkUIPatternLockControllerAccessor PatternLockControllerAccessorImpl {
            PatternLockControllerAccessor::DestroyPeerImpl,
            PatternLockControllerAccessor::ConstructImpl,
            PatternLockControllerAccessor::GetFinalizerImpl,
            PatternLockControllerAccessor::ResetImpl,
            PatternLockControllerAccessor::SetChallengeResultImpl,
        };
        return &PatternLockControllerAccessorImpl;
    }

    struct PatternLockControllerPeer {
        virtual ~PatternLockControllerPeer() = default;
    };
    const GENERATED_ArkUIPermissionRequestAccessor* GetPermissionRequestAccessor()
    {
        static const GENERATED_ArkUIPermissionRequestAccessor PermissionRequestAccessorImpl {
            PermissionRequestAccessor::DestroyPeerImpl,
            PermissionRequestAccessor::ConstructImpl,
            PermissionRequestAccessor::GetFinalizerImpl,
            PermissionRequestAccessor::DenyImpl,
            PermissionRequestAccessor::GetOriginImpl,
            PermissionRequestAccessor::GetAccessibleResourceImpl,
            PermissionRequestAccessor::GrantImpl,
        };
        return &PermissionRequestAccessorImpl;
    }

    struct PermissionRequestPeer {
        virtual ~PermissionRequestPeer() = default;
    };
    const GENERATED_ArkUIPersistentStorageBackendAccessor* GetPersistentStorageBackendAccessor()
    {
        static const GENERATED_ArkUIPersistentStorageBackendAccessor PersistentStorageBackendAccessorImpl {
            PersistentStorageBackendAccessor::GetImpl,
            PersistentStorageBackendAccessor::HasImpl,
            PersistentStorageBackendAccessor::RemoveImpl,
            PersistentStorageBackendAccessor::SetImpl,
            PersistentStorageBackendAccessor::ClearImpl,
        };
        return &PersistentStorageBackendAccessorImpl;
    }

    const GENERATED_ArkUIPinchGestureEventAccessor* GetPinchGestureEventAccessor()
    {
        static const GENERATED_ArkUIPinchGestureEventAccessor PinchGestureEventAccessorImpl {
            PinchGestureEventAccessor::DestroyPeerImpl,
            PinchGestureEventAccessor::ConstructImpl,
            PinchGestureEventAccessor::GetFinalizerImpl,
            PinchGestureEventAccessor::GetScaleImpl,
            PinchGestureEventAccessor::SetScaleImpl,
            PinchGestureEventAccessor::GetPinchCenterXImpl,
            PinchGestureEventAccessor::SetPinchCenterXImpl,
            PinchGestureEventAccessor::GetPinchCenterYImpl,
            PinchGestureEventAccessor::SetPinchCenterYImpl,
        };
        return &PinchGestureEventAccessorImpl;
    }

    struct PinchGestureEventPeer {
        virtual ~PinchGestureEventPeer() = default;
    };
    const GENERATED_ArkUIPinchRecognizerAccessor* GetPinchRecognizerAccessor()
    {
        static const GENERATED_ArkUIPinchRecognizerAccessor PinchRecognizerAccessorImpl {
            PinchRecognizerAccessor::DestroyPeerImpl,
            PinchRecognizerAccessor::ConstructImpl,
            PinchRecognizerAccessor::GetFinalizerImpl,
            PinchRecognizerAccessor::GetDistanceImpl,
        };
        return &PinchRecognizerAccessorImpl;
    }

    struct PinchRecognizerPeer {
        virtual ~PinchRecognizerPeer() = default;
    };
    const GENERATED_ArkUIPixelMapMockAccessor* GetPixelMapMockAccessor()
    {
        static const GENERATED_ArkUIPixelMapMockAccessor PixelMapMockAccessorImpl {
            PixelMapMockAccessor::DestroyPeerImpl,
            PixelMapMockAccessor::ConstructImpl,
            PixelMapMockAccessor::GetFinalizerImpl,
            PixelMapMockAccessor::ReleaseImpl,
        };
        return &PixelMapMockAccessorImpl;
    }

    struct PixelMapMockPeer {
        virtual ~PixelMapMockPeer() = default;
    };
    const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor()
    {
        static const GENERATED_ArkUIProgressMaskAccessor ProgressMaskAccessorImpl {
            ProgressMaskAccessor::DestroyPeerImpl,
            ProgressMaskAccessor::ConstructImpl,
            ProgressMaskAccessor::GetFinalizerImpl,
            ProgressMaskAccessor::UpdateProgressImpl,
            ProgressMaskAccessor::UpdateColorImpl,
            ProgressMaskAccessor::EnableBreathingAnimationImpl,
        };
        return &ProgressMaskAccessorImpl;
    }

    struct ProgressMaskPeer {
        virtual ~ProgressMaskPeer() = default;
    };
    const GENERATED_ArkUIPromptActionExtenderAccessor* GetPromptActionExtenderAccessor()
    {
        static const GENERATED_ArkUIPromptActionExtenderAccessor PromptActionExtenderAccessorImpl {
            PromptActionExtenderAccessor::OpenPopupImpl,
            PromptActionExtenderAccessor::UpdatePopupImpl,
            PromptActionExtenderAccessor::ClosePopupImpl,
            PromptActionExtenderAccessor::OpenMenuImpl,
            PromptActionExtenderAccessor::UpdateMenuImpl,
            PromptActionExtenderAccessor::CloseMenuImpl,
        };
        return &PromptActionExtenderAccessorImpl;
    }

    const GENERATED_ArkUIPulseSymbolEffectAccessor* GetPulseSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIPulseSymbolEffectAccessor PulseSymbolEffectAccessorImpl {
            PulseSymbolEffectAccessor::DestroyPeerImpl,
            PulseSymbolEffectAccessor::ConstructImpl,
            PulseSymbolEffectAccessor::GetFinalizerImpl,
        };
        return &PulseSymbolEffectAccessorImpl;
    }

    struct PulseSymbolEffectPeer {
        virtual ~PulseSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIRenderingContextSettingsAccessor* GetRenderingContextSettingsAccessor()
    {
        static const GENERATED_ArkUIRenderingContextSettingsAccessor RenderingContextSettingsAccessorImpl {
            RenderingContextSettingsAccessor::DestroyPeerImpl,
            RenderingContextSettingsAccessor::ConstructImpl,
            RenderingContextSettingsAccessor::GetFinalizerImpl,
            RenderingContextSettingsAccessor::GetAntialiasImpl,
            RenderingContextSettingsAccessor::SetAntialiasImpl,
        };
        return &RenderingContextSettingsAccessorImpl;
    }

    struct RenderingContextSettingsPeer {
        virtual ~RenderingContextSettingsPeer() = default;
    };
    const GENERATED_ArkUIRenderServiceNodeAccessor* GetRenderServiceNodeAccessor()
    {
        static const GENERATED_ArkUIRenderServiceNodeAccessor RenderServiceNodeAccessorImpl {
            RenderServiceNodeAccessor::GetNodeIdImpl,
        };
        return &RenderServiceNodeAccessorImpl;
    }

    const GENERATED_ArkUIReplaceSymbolEffectAccessor* GetReplaceSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIReplaceSymbolEffectAccessor ReplaceSymbolEffectAccessorImpl {
            ReplaceSymbolEffectAccessor::DestroyPeerImpl,
            ReplaceSymbolEffectAccessor::ConstructImpl,
            ReplaceSymbolEffectAccessor::GetFinalizerImpl,
            ReplaceSymbolEffectAccessor::GetScopeImpl,
            ReplaceSymbolEffectAccessor::SetScopeImpl,
        };
        return &ReplaceSymbolEffectAccessorImpl;
    }

    struct ReplaceSymbolEffectPeer {
        virtual ~ReplaceSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIRestrictedWorkerAccessor* GetRestrictedWorkerAccessor()
    {
        static const GENERATED_ArkUIRestrictedWorkerAccessor RestrictedWorkerAccessorImpl {
            RestrictedWorkerAccessor::DestroyPeerImpl,
            RestrictedWorkerAccessor::ConstructImpl,
            RestrictedWorkerAccessor::GetFinalizerImpl,
            RestrictedWorkerAccessor::PostMessage0Impl,
            RestrictedWorkerAccessor::PostMessage1Impl,
            RestrictedWorkerAccessor::PostMessageWithSharedSendableImpl,
            RestrictedWorkerAccessor::OnImpl,
            RestrictedWorkerAccessor::OnceImpl,
            RestrictedWorkerAccessor::OffImpl,
            RestrictedWorkerAccessor::TerminateImpl,
            RestrictedWorkerAccessor::AddEventListenerImpl,
            RestrictedWorkerAccessor::DispatchEventImpl,
            RestrictedWorkerAccessor::RemoveEventListenerImpl,
            RestrictedWorkerAccessor::RemoveAllListenerImpl,
            RestrictedWorkerAccessor::RegisterGlobalCallObjectImpl,
            RestrictedWorkerAccessor::UnregisterGlobalCallObjectImpl,
            RestrictedWorkerAccessor::GetOnexitImpl,
            RestrictedWorkerAccessor::SetOnexitImpl,
            RestrictedWorkerAccessor::GetOnerrorImpl,
            RestrictedWorkerAccessor::SetOnerrorImpl,
            RestrictedWorkerAccessor::GetOnmessageImpl,
            RestrictedWorkerAccessor::SetOnmessageImpl,
            RestrictedWorkerAccessor::GetOnmessageerrorImpl,
            RestrictedWorkerAccessor::SetOnmessageerrorImpl,
        };
        return &RestrictedWorkerAccessorImpl;
    }

    struct RestrictedWorkerPeer {
        virtual ~RestrictedWorkerPeer() = default;
    };
    const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
    {
        static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
            RichEditorBaseControllerAccessor::DestroyPeerImpl,
            RichEditorBaseControllerAccessor::ConstructImpl,
            RichEditorBaseControllerAccessor::GetFinalizerImpl,
            RichEditorBaseControllerAccessor::GetCaretOffsetImpl,
            RichEditorBaseControllerAccessor::SetCaretOffsetImpl,
            RichEditorBaseControllerAccessor::CloseSelectionMenuImpl,
            RichEditorBaseControllerAccessor::GetTypingStyleImpl,
            RichEditorBaseControllerAccessor::SetTypingStyleImpl,
            RichEditorBaseControllerAccessor::SetSelectionImpl,
            RichEditorBaseControllerAccessor::IsEditingImpl,
            RichEditorBaseControllerAccessor::StopEditingImpl,
            RichEditorBaseControllerAccessor::GetLayoutManagerImpl,
            RichEditorBaseControllerAccessor::GetPreviewTextImpl,
            RichEditorBaseControllerAccessor::GetCaretRectImpl,
        };
        return &RichEditorBaseControllerAccessorImpl;
    }

    struct RichEditorBaseControllerPeer {
        virtual ~RichEditorBaseControllerPeer() = default;
    };
    const GENERATED_ArkUIRichEditorControllerAccessor* GetRichEditorControllerAccessor()
    {
        static const GENERATED_ArkUIRichEditorControllerAccessor RichEditorControllerAccessorImpl {
            RichEditorControllerAccessor::DestroyPeerImpl,
            RichEditorControllerAccessor::ConstructImpl,
            RichEditorControllerAccessor::GetFinalizerImpl,
            RichEditorControllerAccessor::AddTextSpanImpl,
            RichEditorControllerAccessor::AddImageSpanImpl,
            RichEditorControllerAccessor::AddBuilderSpanImpl,
            RichEditorControllerAccessor::AddSymbolSpanImpl,
            RichEditorControllerAccessor::UpdateSpanStyleImpl,
            RichEditorControllerAccessor::UpdateParagraphStyleImpl,
            RichEditorControllerAccessor::DeleteSpansImpl,
            RichEditorControllerAccessor::GetSpansImpl,
            RichEditorControllerAccessor::GetParagraphsImpl,
            RichEditorControllerAccessor::GetSelectionImpl,
            RichEditorControllerAccessor::FromStyledStringImpl,
            RichEditorControllerAccessor::ToStyledStringImpl,
        };
        return &RichEditorControllerAccessorImpl;
    }

    struct RichEditorControllerPeer {
        virtual ~RichEditorControllerPeer() = default;
    };
    const GENERATED_ArkUIRichEditorStyledStringControllerAccessor* GetRichEditorStyledStringControllerAccessor()
    {
        static const GENERATED_ArkUIRichEditorStyledStringControllerAccessor RichEditorStyledStringControllerAccessorImpl {
            RichEditorStyledStringControllerAccessor::DestroyPeerImpl,
            RichEditorStyledStringControllerAccessor::ConstructImpl,
            RichEditorStyledStringControllerAccessor::GetFinalizerImpl,
            RichEditorStyledStringControllerAccessor::SetStyledStringImpl,
            RichEditorStyledStringControllerAccessor::GetStyledStringImpl,
            RichEditorStyledStringControllerAccessor::GetSelectionImpl,
            RichEditorStyledStringControllerAccessor::OnContentChangedImpl,
        };
        return &RichEditorStyledStringControllerAccessorImpl;
    }

    struct RichEditorStyledStringControllerPeer {
        virtual ~RichEditorStyledStringControllerPeer() = default;
    };
    const GENERATED_ArkUIRotationGestureAccessor* GetRotationGestureAccessor()
    {
        static const GENERATED_ArkUIRotationGestureAccessor RotationGestureAccessorImpl {
            RotationGestureAccessor::DestroyPeerImpl,
            RotationGestureAccessor::ConstructImpl,
            RotationGestureAccessor::GetFinalizerImpl,
            RotationGestureAccessor::$_instantiateImpl,
            RotationGestureAccessor::OnActionStartImpl,
            RotationGestureAccessor::OnActionUpdateImpl,
            RotationGestureAccessor::OnActionEndImpl,
            RotationGestureAccessor::OnActionCancelImpl,
        };
        return &RotationGestureAccessorImpl;
    }

    struct RotationGesturePeer {
        virtual ~RotationGesturePeer() = default;
    };
    const GENERATED_ArkUIRotationGestureEventAccessor* GetRotationGestureEventAccessor()
    {
        static const GENERATED_ArkUIRotationGestureEventAccessor RotationGestureEventAccessorImpl {
            RotationGestureEventAccessor::DestroyPeerImpl,
            RotationGestureEventAccessor::ConstructImpl,
            RotationGestureEventAccessor::GetFinalizerImpl,
            RotationGestureEventAccessor::GetAngleImpl,
            RotationGestureEventAccessor::SetAngleImpl,
        };
        return &RotationGestureEventAccessorImpl;
    }

    struct RotationGestureEventPeer {
        virtual ~RotationGestureEventPeer() = default;
    };
    const GENERATED_ArkUIRotationRecognizerAccessor* GetRotationRecognizerAccessor()
    {
        static const GENERATED_ArkUIRotationRecognizerAccessor RotationRecognizerAccessorImpl {
            RotationRecognizerAccessor::DestroyPeerImpl,
            RotationRecognizerAccessor::ConstructImpl,
            RotationRecognizerAccessor::GetFinalizerImpl,
            RotationRecognizerAccessor::GetAngleImpl,
        };
        return &RotationRecognizerAccessorImpl;
    }

    struct RotationRecognizerPeer {
        virtual ~RotationRecognizerPeer() = default;
    };
    const GENERATED_ArkUIRouterExtenderAccessor* GetRouterExtenderAccessor()
    {
        static const GENERATED_ArkUIRouterExtenderAccessor RouterExtenderAccessorImpl {
            RouterExtenderAccessor::PushImpl,
            RouterExtenderAccessor::ReplaceImpl,
            RouterExtenderAccessor::MoveCommonUnderPageNodeImpl,
            RouterExtenderAccessor::BackImpl,
            RouterExtenderAccessor::BackWithOptionsImpl,
            RouterExtenderAccessor::RunPageImpl,
            RouterExtenderAccessor::ClearImpl,
            RouterExtenderAccessor::ShowAlertBeforeBackPageImpl,
            RouterExtenderAccessor::HideAlertBeforeBackPageImpl,
            RouterExtenderAccessor::PushNamedRoute0Impl,
            RouterExtenderAccessor::PushNamedRoute1Impl,
            RouterExtenderAccessor::ReplaceNamedRoute0Impl,
            RouterExtenderAccessor::ReplaceNamedRoute1Impl,
            RouterExtenderAccessor::CreateDynamicImpl,
            RouterExtenderAccessor::PushDynamicImpl,
            RouterExtenderAccessor::ReplaceDynamicImpl,
        };
        return &RouterExtenderAccessorImpl;
    }

    const GENERATED_ArkUIScaleSymbolEffectAccessor* GetScaleSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIScaleSymbolEffectAccessor ScaleSymbolEffectAccessorImpl {
            ScaleSymbolEffectAccessor::DestroyPeerImpl,
            ScaleSymbolEffectAccessor::ConstructImpl,
            ScaleSymbolEffectAccessor::GetFinalizerImpl,
            ScaleSymbolEffectAccessor::GetScopeImpl,
            ScaleSymbolEffectAccessor::SetScopeImpl,
            ScaleSymbolEffectAccessor::GetDirectionImpl,
            ScaleSymbolEffectAccessor::SetDirectionImpl,
        };
        return &ScaleSymbolEffectAccessorImpl;
    }

    struct ScaleSymbolEffectPeer {
        virtual ~ScaleSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIScreenCaptureHandlerAccessor* GetScreenCaptureHandlerAccessor()
    {
        static const GENERATED_ArkUIScreenCaptureHandlerAccessor ScreenCaptureHandlerAccessorImpl {
            ScreenCaptureHandlerAccessor::DestroyPeerImpl,
            ScreenCaptureHandlerAccessor::ConstructImpl,
            ScreenCaptureHandlerAccessor::GetFinalizerImpl,
            ScreenCaptureHandlerAccessor::GetOriginImpl,
            ScreenCaptureHandlerAccessor::GrantImpl,
            ScreenCaptureHandlerAccessor::DenyImpl,
        };
        return &ScreenCaptureHandlerAccessorImpl;
    }

    struct ScreenCaptureHandlerPeer {
        virtual ~ScreenCaptureHandlerPeer() = default;
    };
    const GENERATED_ArkUIScreenshotServiceAccessor* GetScreenshotServiceAccessor()
    {
        static const GENERATED_ArkUIScreenshotServiceAccessor ScreenshotServiceAccessorImpl {
            ScreenshotServiceAccessor::RequestScreenshotImpl,
        };
        return &ScreenshotServiceAccessorImpl;
    }

    const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor()
    {
        static const GENERATED_ArkUIScrollableTargetInfoAccessor ScrollableTargetInfoAccessorImpl {
            ScrollableTargetInfoAccessor::DestroyPeerImpl,
            ScrollableTargetInfoAccessor::ConstructImpl,
            ScrollableTargetInfoAccessor::GetFinalizerImpl,
            ScrollableTargetInfoAccessor::IsBeginImpl,
            ScrollableTargetInfoAccessor::IsEndImpl,
        };
        return &ScrollableTargetInfoAccessorImpl;
    }

    struct ScrollableTargetInfoPeer {
        virtual ~ScrollableTargetInfoPeer() = default;
    };
    const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
    {
        static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
            ScrollerAccessor::DestroyPeerImpl,
            ScrollerAccessor::ConstructImpl,
            ScrollerAccessor::GetFinalizerImpl,
            ScrollerAccessor::ScrollToImpl,
            ScrollerAccessor::ScrollEdgeImpl,
            ScrollerAccessor::FlingImpl,
            ScrollerAccessor::ScrollPageImpl,
            ScrollerAccessor::CurrentOffsetImpl,
            ScrollerAccessor::ScrollToIndexImpl,
            ScrollerAccessor::ScrollByImpl,
            ScrollerAccessor::IsAtEndImpl,
            ScrollerAccessor::GetItemRectImpl,
            ScrollerAccessor::GetItemIndexImpl,
        };
        return &ScrollerAccessorImpl;
    }

    struct ScrollerPeer {
        virtual ~ScrollerPeer() = default;
    };
    const GENERATED_ArkUIScrollMotionAccessor* GetScrollMotionAccessor()
    {
        static const GENERATED_ArkUIScrollMotionAccessor ScrollMotionAccessorImpl {
            ScrollMotionAccessor::DestroyPeerImpl,
            ScrollMotionAccessor::ConstructImpl,
            ScrollMotionAccessor::GetFinalizerImpl,
        };
        return &ScrollMotionAccessorImpl;
    }

    struct ScrollMotionPeer {
        virtual ~ScrollMotionPeer() = default;
    };
    const GENERATED_ArkUIScrollResultAccessor* GetScrollResultAccessor()
    {
        static const GENERATED_ArkUIScrollResultAccessor ScrollResultAccessorImpl {
            ScrollResultAccessor::DestroyPeerImpl,
            ScrollResultAccessor::ConstructImpl,
            ScrollResultAccessor::GetFinalizerImpl,
            ScrollResultAccessor::GetOffsetRemainImpl,
            ScrollResultAccessor::SetOffsetRemainImpl,
        };
        return &ScrollResultAccessorImpl;
    }

    struct ScrollResultPeer {
        virtual ~ScrollResultPeer() = default;
    };
    const GENERATED_ArkUISearchControllerAccessor* GetSearchControllerAccessor()
    {
        static const GENERATED_ArkUISearchControllerAccessor SearchControllerAccessorImpl {
            SearchControllerAccessor::DestroyPeerImpl,
            SearchControllerAccessor::ConstructImpl,
            SearchControllerAccessor::GetFinalizerImpl,
            SearchControllerAccessor::CaretPositionImpl,
            SearchControllerAccessor::StopEditingImpl,
            SearchControllerAccessor::SetTextSelectionImpl,
        };
        return &SearchControllerAccessorImpl;
    }

    struct SearchControllerPeer {
        virtual ~SearchControllerPeer() = default;
    };
    const GENERATED_ArkUISearchOpsAccessor* GetSearchOpsAccessor()
    {
        static const GENERATED_ArkUISearchOpsAccessor SearchOpsAccessorImpl {
            SearchOpsAccessor::RegisterSearchValueCallbackImpl,
        };
        return &SearchOpsAccessorImpl;
    }

    const GENERATED_ArkUISelectExtenderAccessor* GetSelectExtenderAccessor()
    {
        static const GENERATED_ArkUISelectExtenderAccessor SelectExtenderAccessorImpl {
            SelectExtenderAccessor::SetDividerImpl,
        };
        return &SelectExtenderAccessorImpl;
    }

    const GENERATED_ArkUISliderExtenderAccessor* GetSliderExtenderAccessor()
    {
        static const GENERATED_ArkUISliderExtenderAccessor SliderExtenderAccessorImpl {
            SliderExtenderAccessor::SetPrefixImpl,
            SliderExtenderAccessor::SetSuffixImpl,
        };
        return &SliderExtenderAccessorImpl;
    }

    const GENERATED_ArkUISpringMotionAccessor* GetSpringMotionAccessor()
    {
        static const GENERATED_ArkUISpringMotionAccessor SpringMotionAccessorImpl {
            SpringMotionAccessor::DestroyPeerImpl,
            SpringMotionAccessor::ConstructImpl,
            SpringMotionAccessor::GetFinalizerImpl,
        };
        return &SpringMotionAccessorImpl;
    }

    struct SpringMotionPeer {
        virtual ~SpringMotionPeer() = default;
    };
    const GENERATED_ArkUISpringPropAccessor* GetSpringPropAccessor()
    {
        static const GENERATED_ArkUISpringPropAccessor SpringPropAccessorImpl {
            SpringPropAccessor::DestroyPeerImpl,
            SpringPropAccessor::ConstructImpl,
            SpringPropAccessor::GetFinalizerImpl,
        };
        return &SpringPropAccessorImpl;
    }

    struct SpringPropPeer {
        virtual ~SpringPropPeer() = default;
    };
    const GENERATED_ArkUISslErrorHandlerAccessor* GetSslErrorHandlerAccessor()
    {
        static const GENERATED_ArkUISslErrorHandlerAccessor SslErrorHandlerAccessorImpl {
            SslErrorHandlerAccessor::DestroyPeerImpl,
            SslErrorHandlerAccessor::ConstructImpl,
            SslErrorHandlerAccessor::GetFinalizerImpl,
            SslErrorHandlerAccessor::HandleConfirmImpl,
            SslErrorHandlerAccessor::HandleCancel0Impl,
            SslErrorHandlerAccessor::HandleCancel1Impl,
        };
        return &SslErrorHandlerAccessorImpl;
    }

    struct SslErrorHandlerPeer {
        virtual ~SslErrorHandlerPeer() = default;
    };
    const GENERATED_ArkUIStateStylesOpsAccessor* GetStateStylesOpsAccessor()
    {
        static const GENERATED_ArkUIStateStylesOpsAccessor StateStylesOpsAccessorImpl {
            StateStylesOpsAccessor::OnStateStyleChangeImpl,
        };
        return &StateStylesOpsAccessorImpl;
    }

    const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
    {
        static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
            StyledStringAccessor::DestroyPeerImpl,
            StyledStringAccessor::ConstructImpl,
            StyledStringAccessor::GetFinalizerImpl,
            StyledStringAccessor::GetStringImpl,
            StyledStringAccessor::GetStylesImpl,
            StyledStringAccessor::EqualsImpl,
            StyledStringAccessor::SubStyledStringImpl,
            StyledStringAccessor::FromHtmlImpl,
            StyledStringAccessor::ToHtmlImpl,
            StyledStringAccessor::Marshalling0Impl,
            StyledStringAccessor::Unmarshalling0Impl,
            StyledStringAccessor::Marshalling1Impl,
            StyledStringAccessor::Unmarshalling1Impl,
            StyledStringAccessor::GetLengthImpl,
            StyledStringAccessor::SetLengthImpl,
        };
        return &StyledStringAccessorImpl;
    }

    struct StyledStringPeer {
        virtual ~StyledStringPeer() = default;
    };
    const GENERATED_ArkUIStyledStringControllerAccessor* GetStyledStringControllerAccessor()
    {
        static const GENERATED_ArkUIStyledStringControllerAccessor StyledStringControllerAccessorImpl {
            StyledStringControllerAccessor::DestroyPeerImpl,
            StyledStringControllerAccessor::ConstructImpl,
            StyledStringControllerAccessor::GetFinalizerImpl,
            StyledStringControllerAccessor::SetStyledStringImpl,
            StyledStringControllerAccessor::GetStyledStringImpl,
        };
        return &StyledStringControllerAccessorImpl;
    }

    struct StyledStringControllerPeer {
        virtual ~StyledStringControllerPeer() = default;
    };
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor()
    {
        static const GENERATED_ArkUISubmitEventAccessor SubmitEventAccessorImpl {
            SubmitEventAccessor::DestroyPeerImpl,
            SubmitEventAccessor::ConstructImpl,
            SubmitEventAccessor::GetFinalizerImpl,
            SubmitEventAccessor::KeepEditableStateImpl,
            SubmitEventAccessor::GetTextImpl,
            SubmitEventAccessor::SetTextImpl,
        };
        return &SubmitEventAccessorImpl;
    }

    struct SubmitEventPeer {
        virtual ~SubmitEventPeer() = default;
    };
    const GENERATED_ArkUISwipeGestureAccessor* GetSwipeGestureAccessor()
    {
        static const GENERATED_ArkUISwipeGestureAccessor SwipeGestureAccessorImpl {
            SwipeGestureAccessor::DestroyPeerImpl,
            SwipeGestureAccessor::ConstructImpl,
            SwipeGestureAccessor::GetFinalizerImpl,
            SwipeGestureAccessor::$_instantiateImpl,
            SwipeGestureAccessor::OnActionImpl,
        };
        return &SwipeGestureAccessorImpl;
    }

    struct SwipeGesturePeer {
        virtual ~SwipeGesturePeer() = default;
    };
    const GENERATED_ArkUISwipeGestureEventAccessor* GetSwipeGestureEventAccessor()
    {
        static const GENERATED_ArkUISwipeGestureEventAccessor SwipeGestureEventAccessorImpl {
            SwipeGestureEventAccessor::DestroyPeerImpl,
            SwipeGestureEventAccessor::ConstructImpl,
            SwipeGestureEventAccessor::GetFinalizerImpl,
            SwipeGestureEventAccessor::GetAngleImpl,
            SwipeGestureEventAccessor::SetAngleImpl,
            SwipeGestureEventAccessor::GetSpeedImpl,
            SwipeGestureEventAccessor::SetSpeedImpl,
        };
        return &SwipeGestureEventAccessorImpl;
    }

    struct SwipeGestureEventPeer {
        virtual ~SwipeGestureEventPeer() = default;
    };
    const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
    {
        static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
            SwiperContentTransitionProxyAccessor::DestroyPeerImpl,
            SwiperContentTransitionProxyAccessor::ConstructImpl,
            SwiperContentTransitionProxyAccessor::GetFinalizerImpl,
            SwiperContentTransitionProxyAccessor::FinishTransitionImpl,
            SwiperContentTransitionProxyAccessor::GetSelectedIndexImpl,
            SwiperContentTransitionProxyAccessor::SetSelectedIndexImpl,
            SwiperContentTransitionProxyAccessor::GetIndexImpl,
            SwiperContentTransitionProxyAccessor::SetIndexImpl,
            SwiperContentTransitionProxyAccessor::GetPositionImpl,
            SwiperContentTransitionProxyAccessor::SetPositionImpl,
            SwiperContentTransitionProxyAccessor::GetMainAxisLengthImpl,
            SwiperContentTransitionProxyAccessor::SetMainAxisLengthImpl,
        };
        return &SwiperContentTransitionProxyAccessorImpl;
    }

    struct SwiperContentTransitionProxyPeer {
        virtual ~SwiperContentTransitionProxyPeer() = default;
    };
    const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor()
    {
        static const GENERATED_ArkUISwiperControllerAccessor SwiperControllerAccessorImpl {
            SwiperControllerAccessor::DestroyPeerImpl,
            SwiperControllerAccessor::ConstructImpl,
            SwiperControllerAccessor::GetFinalizerImpl,
            SwiperControllerAccessor::ShowNextImpl,
            SwiperControllerAccessor::ShowPreviousImpl,
            SwiperControllerAccessor::ChangeIndexImpl,
            SwiperControllerAccessor::FinishAnimationImpl,
            SwiperControllerAccessor::PreloadItemsImpl,
        };
        return &SwiperControllerAccessorImpl;
    }

    struct SwiperControllerPeer {
        virtual ~SwiperControllerPeer() = default;
    };
    const GENERATED_ArkUISwipeRecognizerAccessor* GetSwipeRecognizerAccessor()
    {
        static const GENERATED_ArkUISwipeRecognizerAccessor SwipeRecognizerAccessorImpl {
            SwipeRecognizerAccessor::DestroyPeerImpl,
            SwipeRecognizerAccessor::ConstructImpl,
            SwipeRecognizerAccessor::GetFinalizerImpl,
            SwipeRecognizerAccessor::GetVelocityThresholdImpl,
            SwipeRecognizerAccessor::GetDirectionImpl,
        };
        return &SwipeRecognizerAccessorImpl;
    }

    struct SwipeRecognizerPeer {
        virtual ~SwipeRecognizerPeer() = default;
    };
    const GENERATED_ArkUISymbolEffectAccessor* GetSymbolEffectAccessor()
    {
        static const GENERATED_ArkUISymbolEffectAccessor SymbolEffectAccessorImpl {
            SymbolEffectAccessor::DestroyPeerImpl,
            SymbolEffectAccessor::ConstructImpl,
            SymbolEffectAccessor::GetFinalizerImpl,
        };
        return &SymbolEffectAccessorImpl;
    }

    struct SymbolEffectPeer {
        virtual ~SymbolEffectPeer() = default;
    };
    const GENERATED_ArkUISystemOpsAccessor* GetSystemOpsAccessor()
    {
        static const GENERATED_ArkUISystemOpsAccessor SystemOpsAccessorImpl {
            SystemOpsAccessor::StartFrameImpl,
            SystemOpsAccessor::EndFrameImpl,
            SystemOpsAccessor::SyncInstanceIdImpl,
            SystemOpsAccessor::RestoreInstanceIdImpl,
            SystemOpsAccessor::GetResourceIdImpl,
            SystemOpsAccessor::ResourceManagerResetImpl,
            SystemOpsAccessor::SetFrameCallbackImpl,
            SystemOpsAccessor::ColorMetricsResourceColorImpl,
            SystemOpsAccessor::ResoureToLengthMetricsImpl,
        };
        return &SystemOpsAccessorImpl;
    }

    const GENERATED_ArkUITabBarSymbolAccessor* GetTabBarSymbolAccessor()
    {
        static const GENERATED_ArkUITabBarSymbolAccessor TabBarSymbolAccessorImpl {
            TabBarSymbolAccessor::DestroyPeerImpl,
            TabBarSymbolAccessor::ConstructImpl,
            TabBarSymbolAccessor::GetFinalizerImpl,
            TabBarSymbolAccessor::GetNormalImpl,
            TabBarSymbolAccessor::SetNormalImpl,
            TabBarSymbolAccessor::GetSelectedImpl,
            TabBarSymbolAccessor::SetSelectedImpl,
        };
        return &TabBarSymbolAccessorImpl;
    }

    struct TabBarSymbolPeer {
        virtual ~TabBarSymbolPeer() = default;
    };
    const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor()
    {
        static const GENERATED_ArkUITabContentTransitionProxyAccessor TabContentTransitionProxyAccessorImpl {
            TabContentTransitionProxyAccessor::DestroyPeerImpl,
            TabContentTransitionProxyAccessor::ConstructImpl,
            TabContentTransitionProxyAccessor::GetFinalizerImpl,
            TabContentTransitionProxyAccessor::FinishTransitionImpl,
            TabContentTransitionProxyAccessor::GetFromImpl,
            TabContentTransitionProxyAccessor::SetFromImpl,
            TabContentTransitionProxyAccessor::GetToImpl,
            TabContentTransitionProxyAccessor::SetToImpl,
        };
        return &TabContentTransitionProxyAccessorImpl;
    }

    struct TabContentTransitionProxyPeer {
        virtual ~TabContentTransitionProxyPeer() = default;
    };
    const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor()
    {
        static const GENERATED_ArkUITabsControllerAccessor TabsControllerAccessorImpl {
            TabsControllerAccessor::DestroyPeerImpl,
            TabsControllerAccessor::ConstructImpl,
            TabsControllerAccessor::GetFinalizerImpl,
            TabsControllerAccessor::ChangeIndexImpl,
            TabsControllerAccessor::PreloadItemsImpl,
            TabsControllerAccessor::SetTabBarTranslateImpl,
            TabsControllerAccessor::SetTabBarOpacityImpl,
        };
        return &TabsControllerAccessorImpl;
    }

    struct TabsControllerPeer {
        virtual ~TabsControllerPeer() = default;
    };
    const GENERATED_ArkUITabsExtenderAccessor* GetTabsExtenderAccessor()
    {
        static const GENERATED_ArkUITabsExtenderAccessor TabsExtenderAccessorImpl {
            TabsExtenderAccessor::ApplyAttributesFinishImpl,
        };
        return &TabsExtenderAccessorImpl;
    }

    const GENERATED_ArkUITapGestureEventAccessor* GetTapGestureEventAccessor()
    {
        static const GENERATED_ArkUITapGestureEventAccessor TapGestureEventAccessorImpl {
            TapGestureEventAccessor::DestroyPeerImpl,
            TapGestureEventAccessor::ConstructImpl,
            TapGestureEventAccessor::GetFinalizerImpl,
            TapGestureEventAccessor::GetTapLocationImpl,
        };
        return &TapGestureEventAccessorImpl;
    }

    struct TapGestureEventPeer {
        virtual ~TapGestureEventPeer() = default;
    };
    const GENERATED_ArkUITapRecognizerAccessor* GetTapRecognizerAccessor()
    {
        static const GENERATED_ArkUITapRecognizerAccessor TapRecognizerAccessorImpl {
            TapRecognizerAccessor::DestroyPeerImpl,
            TapRecognizerAccessor::ConstructImpl,
            TapRecognizerAccessor::GetFinalizerImpl,
            TapRecognizerAccessor::GetTapCountImpl,
        };
        return &TapRecognizerAccessorImpl;
    }

    struct TapRecognizerPeer {
        virtual ~TapRecognizerPeer() = default;
    };
    const GENERATED_ArkUITextAreaControllerAccessor* GetTextAreaControllerAccessor()
    {
        static const GENERATED_ArkUITextAreaControllerAccessor TextAreaControllerAccessorImpl {
            TextAreaControllerAccessor::DestroyPeerImpl,
            TextAreaControllerAccessor::ConstructImpl,
            TextAreaControllerAccessor::GetFinalizerImpl,
            TextAreaControllerAccessor::CaretPositionImpl,
            TextAreaControllerAccessor::SetTextSelectionImpl,
            TextAreaControllerAccessor::StopEditingImpl,
        };
        return &TextAreaControllerAccessorImpl;
    }

    struct TextAreaControllerPeer {
        virtual ~TextAreaControllerPeer() = default;
    };
    const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor()
    {
        static const GENERATED_ArkUITextBaseControllerAccessor TextBaseControllerAccessorImpl {
            TextBaseControllerAccessor::DestroyPeerImpl,
            TextBaseControllerAccessor::ConstructImpl,
            TextBaseControllerAccessor::GetFinalizerImpl,
            TextBaseControllerAccessor::SetSelectionImpl,
            TextBaseControllerAccessor::CloseSelectionMenuImpl,
            TextBaseControllerAccessor::GetLayoutManagerImpl,
        };
        return &TextBaseControllerAccessorImpl;
    }

    struct TextBaseControllerPeer {
        virtual ~TextBaseControllerPeer() = default;
    };
    const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor()
    {
        static const GENERATED_ArkUITextClockControllerAccessor TextClockControllerAccessorImpl {
            TextClockControllerAccessor::DestroyPeerImpl,
            TextClockControllerAccessor::ConstructImpl,
            TextClockControllerAccessor::GetFinalizerImpl,
            TextClockControllerAccessor::StartImpl,
            TextClockControllerAccessor::StopImpl,
        };
        return &TextClockControllerAccessorImpl;
    }

    struct TextClockControllerPeer {
        virtual ~TextClockControllerPeer() = default;
    };
    const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor()
    {
        static const GENERATED_ArkUITextContentControllerBaseAccessor TextContentControllerBaseAccessorImpl {
            TextContentControllerBaseAccessor::DestroyPeerImpl,
            TextContentControllerBaseAccessor::ConstructImpl,
            TextContentControllerBaseAccessor::GetFinalizerImpl,
            TextContentControllerBaseAccessor::GetCaretOffsetImpl,
            TextContentControllerBaseAccessor::GetTextContentRectImpl,
            TextContentControllerBaseAccessor::GetTextContentLineCountImpl,
            TextContentControllerBaseAccessor::AddTextImpl,
            TextContentControllerBaseAccessor::DeleteTextImpl,
            TextContentControllerBaseAccessor::GetSelectionImpl,
            TextContentControllerBaseAccessor::ClearPreviewTextImpl,
            TextContentControllerBaseAccessor::GetTextImpl,
            TextContentControllerBaseAccessor::DeleteBackwardImpl,
        };
        return &TextContentControllerBaseAccessorImpl;
    }

    struct TextContentControllerBasePeer {
        virtual ~TextContentControllerBasePeer() = default;
    };
    const GENERATED_ArkUITextControllerAccessor* GetTextControllerAccessor()
    {
        static const GENERATED_ArkUITextControllerAccessor TextControllerAccessorImpl {
            TextControllerAccessor::DestroyPeerImpl,
            TextControllerAccessor::ConstructImpl,
            TextControllerAccessor::GetFinalizerImpl,
            TextControllerAccessor::CloseSelectionMenuImpl,
            TextControllerAccessor::SetStyledStringImpl,
            TextControllerAccessor::GetLayoutManagerImpl,
            TextControllerAccessor::SetTextSelectionImpl,
        };
        return &TextControllerAccessorImpl;
    }

    struct TextControllerPeer {
        virtual ~TextControllerPeer() = default;
    };
    const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor()
    {
        static const GENERATED_ArkUITextEditControllerExAccessor TextEditControllerExAccessorImpl {
            TextEditControllerExAccessor::DestroyPeerImpl,
            TextEditControllerExAccessor::ConstructImpl,
            TextEditControllerExAccessor::GetFinalizerImpl,
            TextEditControllerExAccessor::IsEditingImpl,
            TextEditControllerExAccessor::StopEditingImpl,
            TextEditControllerExAccessor::SetCaretOffsetImpl,
            TextEditControllerExAccessor::GetCaretOffsetImpl,
            TextEditControllerExAccessor::GetPreviewTextImpl,
        };
        return &TextEditControllerExAccessorImpl;
    }

    struct TextEditControllerExPeer {
        virtual ~TextEditControllerExPeer() = default;
    };
    const GENERATED_ArkUITextFieldOpsAccessor* GetTextFieldOpsAccessor()
    {
        static const GENERATED_ArkUITextFieldOpsAccessor TextFieldOpsAccessorImpl {
            TextFieldOpsAccessor::RegisterTextFieldValueCallbackImpl,
            TextFieldOpsAccessor::TextFieldOpsSetWidthImpl,
            TextFieldOpsAccessor::TextFieldOpsSetHeightImpl,
            TextFieldOpsAccessor::TextFieldOpsSetPaddingImpl,
            TextFieldOpsAccessor::TextFieldOpsSetMarginImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBorderImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBorderWidthImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBorderColorImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBorderStyleImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBorderRadiusImpl,
            TextFieldOpsAccessor::TextFieldOpsSetBackgroundColorImpl,
        };
        return &TextFieldOpsAccessorImpl;
    }

    const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor()
    {
        static const GENERATED_ArkUITextInputControllerAccessor TextInputControllerAccessorImpl {
            TextInputControllerAccessor::DestroyPeerImpl,
            TextInputControllerAccessor::ConstructImpl,
            TextInputControllerAccessor::GetFinalizerImpl,
            TextInputControllerAccessor::CaretPositionImpl,
            TextInputControllerAccessor::SetTextSelectionImpl,
            TextInputControllerAccessor::StopEditingImpl,
        };
        return &TextInputControllerAccessorImpl;
    }

    struct TextInputControllerPeer {
        virtual ~TextInputControllerPeer() = default;
    };
    const GENERATED_ArkUITextMenuItemIdAccessor* GetTextMenuItemIdAccessor()
    {
        static const GENERATED_ArkUITextMenuItemIdAccessor TextMenuItemIdAccessorImpl {
            TextMenuItemIdAccessor::DestroyPeerImpl,
            TextMenuItemIdAccessor::ConstructImpl,
            TextMenuItemIdAccessor::GetFinalizerImpl,
            TextMenuItemIdAccessor::OfImpl,
            TextMenuItemIdAccessor::EqualsImpl,
            TextMenuItemIdAccessor::GetCUTImpl,
            TextMenuItemIdAccessor::GetCOPYImpl,
            TextMenuItemIdAccessor::GetPASTEImpl,
            TextMenuItemIdAccessor::GetSELECT_ALLImpl,
            TextMenuItemIdAccessor::GetCOLLABORATION_SERVICEImpl,
            TextMenuItemIdAccessor::GetCAMERA_INPUTImpl,
            TextMenuItemIdAccessor::GetAI_WRITERImpl,
            TextMenuItemIdAccessor::GetTRANSLATEImpl,
            TextMenuItemIdAccessor::GetSEARCHImpl,
            TextMenuItemIdAccessor::GetSHAREImpl,
        };
        return &TextMenuItemIdAccessorImpl;
    }

    struct TextMenuItemIdPeer {
        virtual ~TextMenuItemIdPeer() = default;
    };
    const GENERATED_ArkUITextPickerDialogAccessor* GetTextPickerDialogAccessor()
    {
        static const GENERATED_ArkUITextPickerDialogAccessor TextPickerDialogAccessorImpl {
            TextPickerDialogAccessor::DestroyPeerImpl,
            TextPickerDialogAccessor::ConstructImpl,
            TextPickerDialogAccessor::GetFinalizerImpl,
        };
        return &TextPickerDialogAccessorImpl;
    }

    struct TextPickerDialogPeer {
        virtual ~TextPickerDialogPeer() = default;
    };
    const GENERATED_ArkUITextShadowStyleAccessor* GetTextShadowStyleAccessor()
    {
        static const GENERATED_ArkUITextShadowStyleAccessor TextShadowStyleAccessorImpl {
            TextShadowStyleAccessor::DestroyPeerImpl,
            TextShadowStyleAccessor::ConstructImpl,
            TextShadowStyleAccessor::GetFinalizerImpl,
            TextShadowStyleAccessor::GetTextShadowImpl,
        };
        return &TextShadowStyleAccessorImpl;
    }

    struct TextShadowStylePeer {
        virtual ~TextShadowStylePeer() = default;
    };
    const GENERATED_ArkUITextStyleAccessor* GetTextStyleAccessor()
    {
        static const GENERATED_ArkUITextStyleAccessor TextStyleAccessorImpl {
            TextStyleAccessor::DestroyPeerImpl,
            TextStyleAccessor::ConstructImpl,
            TextStyleAccessor::GetFinalizerImpl,
            TextStyleAccessor::GetFontColorImpl,
            TextStyleAccessor::GetFontFamilyImpl,
            TextStyleAccessor::GetFontSizeImpl,
            TextStyleAccessor::GetFontWeightImpl,
            TextStyleAccessor::GetFontStyleImpl,
        };
        return &TextStyleAccessorImpl;
    }

    struct TextStylePeer {
        virtual ~TextStylePeer() = default;
    };
    const GENERATED_ArkUITextTimerControllerAccessor* GetTextTimerControllerAccessor()
    {
        static const GENERATED_ArkUITextTimerControllerAccessor TextTimerControllerAccessorImpl {
            TextTimerControllerAccessor::DestroyPeerImpl,
            TextTimerControllerAccessor::ConstructImpl,
            TextTimerControllerAccessor::GetFinalizerImpl,
            TextTimerControllerAccessor::StartImpl,
            TextTimerControllerAccessor::PauseImpl,
            TextTimerControllerAccessor::ResetImpl,
        };
        return &TextTimerControllerAccessorImpl;
    }

    struct TextTimerControllerPeer {
        virtual ~TextTimerControllerPeer() = default;
    };
    const GENERATED_ArkUIThemeOpsAccessor* GetThemeOpsAccessor()
    {
        static const GENERATED_ArkUIThemeOpsAccessor ThemeOpsAccessorImpl {
            ThemeOpsAccessor::SendThemeToNativeImpl,
            ThemeOpsAccessor::SetDefaultThemeImpl,
        };
        return &ThemeOpsAccessorImpl;
    }

    const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor()
    {
        static const GENERATED_ArkUITimePickerDialogAccessor TimePickerDialogAccessorImpl {
            TimePickerDialogAccessor::DestroyPeerImpl,
            TimePickerDialogAccessor::ConstructImpl,
            TimePickerDialogAccessor::GetFinalizerImpl,
        };
        return &TimePickerDialogAccessorImpl;
    }

    struct TimePickerDialogPeer {
        virtual ~TimePickerDialogPeer() = default;
    };
    const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
    {
        static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
            TouchEventAccessor::DestroyPeerImpl,
            TouchEventAccessor::ConstructImpl,
            TouchEventAccessor::GetFinalizerImpl,
            TouchEventAccessor::GetHistoricalPointsImpl,
            TouchEventAccessor::GetTypeImpl,
            TouchEventAccessor::SetTypeImpl,
            TouchEventAccessor::GetTouchesImpl,
            TouchEventAccessor::SetTouchesImpl,
            TouchEventAccessor::GetChangedTouchesImpl,
            TouchEventAccessor::SetChangedTouchesImpl,
            TouchEventAccessor::StopPropagationImpl,
            TouchEventAccessor::PreventDefaultImpl,
        };
        return &TouchEventAccessorImpl;
    }

    struct TouchEventPeer {
        virtual ~TouchEventPeer() = default;
    };
    const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor()
    {
        static const GENERATED_ArkUITransitionEffectAccessor TransitionEffectAccessorImpl {
            TransitionEffectAccessor::DestroyPeerImpl,
            TransitionEffectAccessor::Construct0Impl,
            TransitionEffectAccessor::Construct1Impl,
            TransitionEffectAccessor::Construct2Impl,
            TransitionEffectAccessor::Construct3Impl,
            TransitionEffectAccessor::Construct4Impl,
            TransitionEffectAccessor::Construct5Impl,
            TransitionEffectAccessor::Construct6Impl,
            TransitionEffectAccessor::GetFinalizerImpl,
            TransitionEffectAccessor::TranslateImpl,
            TransitionEffectAccessor::RotateImpl,
            TransitionEffectAccessor::ScaleImpl,
            TransitionEffectAccessor::OpacityImpl,
            TransitionEffectAccessor::MoveImpl,
            TransitionEffectAccessor::AsymmetricImpl,
            TransitionEffectAccessor::AnimationImpl,
            TransitionEffectAccessor::CombineImpl,
            TransitionEffectAccessor::GetIDENTITYImpl,
            TransitionEffectAccessor::SetIDENTITYImpl,
            TransitionEffectAccessor::GetOPACITYImpl,
            TransitionEffectAccessor::SetOPACITYImpl,
            TransitionEffectAccessor::GetSLIDEImpl,
            TransitionEffectAccessor::SetSLIDEImpl,
            TransitionEffectAccessor::GetSLIDE_SWITCHImpl,
            TransitionEffectAccessor::SetSLIDE_SWITCHImpl,
        };
        return &TransitionEffectAccessorImpl;
    }

    struct TransitionEffectPeer {
        virtual ~TransitionEffectPeer() = default;
    };
    const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor()
    {
        static const GENERATED_ArkUIUICommonEventAccessor UICommonEventAccessorImpl {
            UICommonEventAccessor::DestroyPeerImpl,
            UICommonEventAccessor::ConstructImpl,
            UICommonEventAccessor::GetFinalizerImpl,
            UICommonEventAccessor::SetOnClickImpl,
            UICommonEventAccessor::SetOnTouchImpl,
            UICommonEventAccessor::SetOnAppearImpl,
            UICommonEventAccessor::SetOnDisappearImpl,
            UICommonEventAccessor::SetOnKeyEventImpl,
            UICommonEventAccessor::SetOnFocusImpl,
            UICommonEventAccessor::SetOnBlurImpl,
            UICommonEventAccessor::SetOnHoverImpl,
            UICommonEventAccessor::SetOnMouseImpl,
            UICommonEventAccessor::SetOnSizeChangeImpl,
            UICommonEventAccessor::SetOnVisibleAreaApproximateChangeImpl,
        };
        return &UICommonEventAccessorImpl;
    }

    struct UICommonEventPeer {
        virtual ~UICommonEventPeer() = default;
    };
    const GENERATED_ArkUIUIContextAtomicServiceBarAccessor* GetUIContextAtomicServiceBarAccessor()
    {
        static const GENERATED_ArkUIUIContextAtomicServiceBarAccessor UIContextAtomicServiceBarAccessorImpl {
            UIContextAtomicServiceBarAccessor::GetBarRectImpl,
        };
        return &UIContextAtomicServiceBarAccessorImpl;
    }

    const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor()
    {
        static const GENERATED_ArkUIUIExtensionProxyAccessor UIExtensionProxyAccessorImpl {
            UIExtensionProxyAccessor::DestroyPeerImpl,
            UIExtensionProxyAccessor::ConstructImpl,
            UIExtensionProxyAccessor::GetFinalizerImpl,
            UIExtensionProxyAccessor::SendImpl,
            UIExtensionProxyAccessor::SendSyncImpl,
            UIExtensionProxyAccessor::OnAsyncReceiverRegisterAsyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OnSyncReceiverRegisterSyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OffAsyncReceiverRegisterAsyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OffSyncReceiverRegisterSyncReceiverRegisterImpl,
        };
        return &UIExtensionProxyAccessorImpl;
    }

    struct UIExtensionProxyPeer {
        virtual ~UIExtensionProxyPeer() = default;
    };
    const GENERATED_ArkUIUrlStyleAccessor* GetUrlStyleAccessor()
    {
        static const GENERATED_ArkUIUrlStyleAccessor UrlStyleAccessorImpl {
            UrlStyleAccessor::DestroyPeerImpl,
            UrlStyleAccessor::ConstructImpl,
            UrlStyleAccessor::GetFinalizerImpl,
            UrlStyleAccessor::GetUrlImpl,
        };
        return &UrlStyleAccessorImpl;
    }

    struct UrlStylePeer {
        virtual ~UrlStylePeer() = default;
    };
    const GENERATED_ArkUIVideoControllerAccessor* GetVideoControllerAccessor()
    {
        static const GENERATED_ArkUIVideoControllerAccessor VideoControllerAccessorImpl {
            VideoControllerAccessor::DestroyPeerImpl,
            VideoControllerAccessor::ConstructImpl,
            VideoControllerAccessor::GetFinalizerImpl,
            VideoControllerAccessor::StartImpl,
            VideoControllerAccessor::PauseImpl,
            VideoControllerAccessor::StopImpl,
            VideoControllerAccessor::RequestFullscreenImpl,
            VideoControllerAccessor::ExitFullscreenImpl,
            VideoControllerAccessor::SetCurrentTimeDefaultImpl,
            VideoControllerAccessor::SetCurrentTimeWithModeImpl,
            VideoControllerAccessor::ResetImpl,
        };
        return &VideoControllerAccessorImpl;
    }

    struct VideoControllerPeer {
        virtual ~VideoControllerPeer() = default;
    };
    const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsAccessor()
    {
        static const GENERATED_ArkUIWaterFlowSectionsAccessor WaterFlowSectionsAccessorImpl {
            WaterFlowSectionsAccessor::DestroyPeerImpl,
            WaterFlowSectionsAccessor::ConstructImpl,
            WaterFlowSectionsAccessor::GetFinalizerImpl,
            WaterFlowSectionsAccessor::SpliceImpl,
            WaterFlowSectionsAccessor::PushImpl,
            WaterFlowSectionsAccessor::UpdateImpl,
            WaterFlowSectionsAccessor::ValuesImpl,
            WaterFlowSectionsAccessor::LengthImpl,
        };
        return &WaterFlowSectionsAccessorImpl;
    }

    struct WaterFlowSectionsPeer {
        virtual ~WaterFlowSectionsPeer() = default;
    };
    const GENERATED_ArkUIWebContextMenuParamAccessor* GetWebContextMenuParamAccessor()
    {
        static const GENERATED_ArkUIWebContextMenuParamAccessor WebContextMenuParamAccessorImpl {
            WebContextMenuParamAccessor::DestroyPeerImpl,
            WebContextMenuParamAccessor::ConstructImpl,
            WebContextMenuParamAccessor::GetFinalizerImpl,
            WebContextMenuParamAccessor::XImpl,
            WebContextMenuParamAccessor::YImpl,
            WebContextMenuParamAccessor::GetLinkUrlImpl,
            WebContextMenuParamAccessor::GetUnfilteredLinkUrlImpl,
            WebContextMenuParamAccessor::GetSourceUrlImpl,
            WebContextMenuParamAccessor::ExistsImageContentsImpl,
            WebContextMenuParamAccessor::GetMediaTypeImpl,
            WebContextMenuParamAccessor::GetSelectionTextImpl,
            WebContextMenuParamAccessor::GetSourceTypeImpl,
            WebContextMenuParamAccessor::GetInputFieldTypeImpl,
            WebContextMenuParamAccessor::IsEditableImpl,
            WebContextMenuParamAccessor::GetEditStateFlagsImpl,
            WebContextMenuParamAccessor::GetPreviewWidthImpl,
            WebContextMenuParamAccessor::GetPreviewHeightImpl,
            WebContextMenuParamAccessor::GetContextMenuMediaTypeImpl,
        };
        return &WebContextMenuParamAccessorImpl;
    }

    struct WebContextMenuParamPeer {
        virtual ~WebContextMenuParamPeer() = default;
    };
    const GENERATED_ArkUIWebContextMenuResultAccessor* GetWebContextMenuResultAccessor()
    {
        static const GENERATED_ArkUIWebContextMenuResultAccessor WebContextMenuResultAccessorImpl {
            WebContextMenuResultAccessor::DestroyPeerImpl,
            WebContextMenuResultAccessor::ConstructImpl,
            WebContextMenuResultAccessor::GetFinalizerImpl,
            WebContextMenuResultAccessor::CloseContextMenuImpl,
            WebContextMenuResultAccessor::CopyImageImpl,
            WebContextMenuResultAccessor::CopyImpl,
            WebContextMenuResultAccessor::PasteImpl,
            WebContextMenuResultAccessor::CutImpl,
            WebContextMenuResultAccessor::SelectAllImpl,
            WebContextMenuResultAccessor::RedoImpl,
            WebContextMenuResultAccessor::UndoImpl,
            WebContextMenuResultAccessor::PasteAndMatchStyleImpl,
        };
        return &WebContextMenuResultAccessorImpl;
    }

    struct WebContextMenuResultPeer {
        virtual ~WebContextMenuResultPeer() = default;
    };
    const GENERATED_ArkUIWebKeyboardControllerAccessor* GetWebKeyboardControllerAccessor()
    {
        static const GENERATED_ArkUIWebKeyboardControllerAccessor WebKeyboardControllerAccessorImpl {
            WebKeyboardControllerAccessor::DestroyPeerImpl,
            WebKeyboardControllerAccessor::ConstructImpl,
            WebKeyboardControllerAccessor::GetFinalizerImpl,
            WebKeyboardControllerAccessor::InsertTextImpl,
            WebKeyboardControllerAccessor::DeleteForwardImpl,
            WebKeyboardControllerAccessor::DeleteBackwardImpl,
            WebKeyboardControllerAccessor::SendFunctionKeyImpl,
            WebKeyboardControllerAccessor::CloseImpl,
        };
        return &WebKeyboardControllerAccessorImpl;
    }

    struct WebKeyboardControllerPeer {
        virtual ~WebKeyboardControllerPeer() = default;
    };
    const GENERATED_ArkUIWebResourceErrorAccessor* GetWebResourceErrorAccessor()
    {
        static const GENERATED_ArkUIWebResourceErrorAccessor WebResourceErrorAccessorImpl {
            WebResourceErrorAccessor::DestroyPeerImpl,
            WebResourceErrorAccessor::ConstructImpl,
            WebResourceErrorAccessor::GetFinalizerImpl,
            WebResourceErrorAccessor::GetErrorInfoImpl,
            WebResourceErrorAccessor::GetErrorCodeImpl,
        };
        return &WebResourceErrorAccessorImpl;
    }

    struct WebResourceErrorPeer {
        virtual ~WebResourceErrorPeer() = default;
    };
    const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor()
    {
        static const GENERATED_ArkUIWebResourceRequestAccessor WebResourceRequestAccessorImpl {
            WebResourceRequestAccessor::DestroyPeerImpl,
            WebResourceRequestAccessor::ConstructImpl,
            WebResourceRequestAccessor::GetFinalizerImpl,
            WebResourceRequestAccessor::GetRequestHeaderImpl,
            WebResourceRequestAccessor::GetRequestUrlImpl,
            WebResourceRequestAccessor::IsRequestGestureImpl,
            WebResourceRequestAccessor::IsMainFrameImpl,
            WebResourceRequestAccessor::IsRedirectImpl,
            WebResourceRequestAccessor::GetRequestMethodImpl,
        };
        return &WebResourceRequestAccessorImpl;
    }

    struct WebResourceRequestPeer {
        virtual ~WebResourceRequestPeer() = default;
    };
    const GENERATED_ArkUIWebResourceResponseAccessor* GetWebResourceResponseAccessor()
    {
        static const GENERATED_ArkUIWebResourceResponseAccessor WebResourceResponseAccessorImpl {
            WebResourceResponseAccessor::DestroyPeerImpl,
            WebResourceResponseAccessor::ConstructImpl,
            WebResourceResponseAccessor::GetFinalizerImpl,
            WebResourceResponseAccessor::GetResponseDataImpl,
            WebResourceResponseAccessor::GetResponseDataExImpl,
            WebResourceResponseAccessor::GetResponseEncodingImpl,
            WebResourceResponseAccessor::GetResponseMimeTypeImpl,
            WebResourceResponseAccessor::GetReasonMessageImpl,
            WebResourceResponseAccessor::GetResponseHeaderImpl,
            WebResourceResponseAccessor::GetResponseCodeImpl,
            WebResourceResponseAccessor::SetResponseDataImpl,
            WebResourceResponseAccessor::SetResponseEncodingImpl,
            WebResourceResponseAccessor::SetResponseMimeTypeImpl,
            WebResourceResponseAccessor::SetReasonMessageImpl,
            WebResourceResponseAccessor::SetResponseHeaderImpl,
            WebResourceResponseAccessor::SetResponseCodeImpl,
            WebResourceResponseAccessor::SetResponseIsReadyImpl,
            WebResourceResponseAccessor::GetResponseIsReadyImpl,
        };
        return &WebResourceResponseAccessorImpl;
    }

    struct WebResourceResponsePeer {
        virtual ~WebResourceResponsePeer() = default;
    };
    const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
    {
        static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
            XComponentControllerAccessor::DestroyPeerImpl,
            XComponentControllerAccessor::ConstructImpl,
            XComponentControllerAccessor::GetFinalizerImpl,
            XComponentControllerAccessor::GetXComponentSurfaceIdImpl,
            XComponentControllerAccessor::SetXComponentSurfaceRectImpl,
            XComponentControllerAccessor::GetXComponentSurfaceRectImpl,
            XComponentControllerAccessor::SetXComponentSurfaceRotationImpl,
            XComponentControllerAccessor::GetXComponentSurfaceRotationImpl,
            XComponentControllerAccessor::StartImageAnalyzerImpl,
            XComponentControllerAccessor::StopImageAnalyzerImpl,
            XComponentControllerAccessor::GetOnSurfaceCreatedImpl,
            XComponentControllerAccessor::SetOnSurfaceCreatedImpl,
            XComponentControllerAccessor::GetOnSurfaceChangedImpl,
            XComponentControllerAccessor::SetOnSurfaceChangedImpl,
            XComponentControllerAccessor::GetOnSurfaceDestroyedImpl,
            XComponentControllerAccessor::SetOnSurfaceDestroyedImpl,
        };
        return &XComponentControllerAccessorImpl;
    }

    struct XComponentControllerPeer {
        virtual ~XComponentControllerPeer() = default;
    };
    const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
    {
        static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
            GlobalScopeAccessor::$rImpl,
            GlobalScopeAccessor::$rawfileImpl,
            GlobalScopeAccessor::AnimateToImpl,
            GlobalScopeAccessor::AnimateToImmediatelyImpl,
            GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
            GlobalScopeAccessor::CursorControl_setCursorImpl,
            GlobalScopeAccessor::FocusControl_requestFocusImpl,
            GlobalScopeAccessor::GetRectangleByIdImpl,
            GlobalScopeAccessor::PostCardActionImpl,
            GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
            GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
            GlobalScopeAccessor::Px2vpImpl,
            GlobalScopeAccessor::SetAppBgColorImpl,
            GlobalScopeAccessor::Vp2pxImpl,
        };
        return &GlobalScopeAccessorImpl;
    }

    struct GlobalScopePeer {
        virtual ~GlobalScopePeer() = default;
    };
    const GENERATED_ArkUIAccessors* GENERATED_GetArkUIAccessors()
    {
        static const GENERATED_ArkUIAccessors accessorsImpl = {
            GetAccessibilityHoverEventAccessor,
            GetActionSheetAccessor,
            GetAlertDialogAccessor,
            GetAnimationExtenderAccessor,
            GetAppearSymbolEffectAccessor,
            GetArcListExtenderAccessor,
            GetArcListItemExtenderAccessor,
            GetArcScrollBarExtenderAccessor,
            GetAxisEventAccessor,
            GetBackgroundColorStyleAccessor,
            GetBaseEventAccessor,
            GetBaseGestureEventAccessor,
            GetBaselineOffsetStyleAccessor,
            GetBaseShapeAccessor,
            GetBounceSymbolEffectAccessor,
            GetBuilderNodeOpsAccessor,
            GetCalendarPickerDialogAccessor,
            GetCanvasGradientAccessor,
            GetCanvasPathAccessor,
            GetCanvasPatternAccessor,
            GetCanvasRendererAccessor,
            GetCanvasRenderingContext2DAccessor,
            GetChildrenMainSizeAccessor,
            GetClickEventAccessor,
            GetClientAuthenticationHandlerAccessor,
            GetColorContentAccessor,
            GetColorFilterAccessor,
            GetCommonShapeAccessor,
            GetConsoleMessageAccessor,
            GetContentModifierHelperAccessor,
            GetControllerHandlerAccessor,
            GetCopyEventAccessor,
            GetCustomDialogControllerAccessor,
            GetCustomDialogControllerExtenderAccessor,
            GetCustomSpanAccessor,
            GetCutEventAccessor,
            GetDataResubmissionHandlerAccessor,
            GetDatePickerDialogAccessor,
            GetDecorationStyleAccessor,
            GetDialogExtenderAccessor,
            GetDisappearSymbolEffectAccessor,
            GetDismissDialogActionAccessor,
            GetDismissPopupActionAccessor,
            GetDragEventAccessor,
            GetDrawingRenderingContextAccessor,
            GetEnvironmentBackendAccessor,
            GetEventEmulatorAccessor,
            GetEventResultAccessor,
            GetEventTargetInfoAccessor,
            GetExtendableComponentAccessor,
            GetFileSelectorParamAccessor,
            GetFileSelectorResultAccessor,
            GetFocusAxisEventAccessor,
            GetFocusControllerAccessor,
            GetForEachOpsAccessor,
            GetFrameNodeExtenderAccessor,
            GetFrictionMotionAccessor,
            GetFullScreenExitHandlerAccessor,
            GetGestureAccessor,
            GetGestureEventAccessor,
            GetGestureGroupAccessor,
            GetGestureRecognizerAccessor,
            GetGestureStyleAccessor,
            GetGlobalScope_ohos_arkui_componentSnapshotAccessor,
            GetGlobalScope_ohos_arkui_performanceMonitorAccessor,
            GetGlobalScope_ohos_fontAccessor,
            GetGlobalScope_ohos_measure_utilsAccessor,
            GetHierarchicalSymbolEffectAccessor,
            GetHoverEventAccessor,
            GetHttpAuthHandlerAccessor,
            GetImageAnalyzerControllerAccessor,
            GetImageAttachmentAccessor,
            GetImageBitmapAccessor,
            GetImageDataAccessor,
            GetIndicatorComponentControllerAccessor,
            GetIUIContextAccessor,
            GetJsGeolocationAccessor,
            GetJsResultAccessor,
            GetKeyEventAccessor,
            GetLayoutableAccessor,
            GetLayoutManagerAccessor,
            GetLayoutPolicyAccessor,
            GetLazyBuildAccessor,
            GetLazyForEachOpsAccessor,
            GetLetterSpacingStyleAccessor,
            GetLevelOrderExtenderAccessor,
            GetLifeCycleAccessor,
            GetLinearGradientAccessor,
            GetLinearIndicatorControllerAccessor,
            GetLineHeightStyleAccessor,
            GetListScrollerAccessor,
            GetLongPressGestureEventAccessor,
            GetLongPressRecognizerAccessor,
            GetMatrix2DAccessor,
            GetMeasurableAccessor,
            GetMenuItemConfigurationAccessor,
            GetMouseEventAccessor,
            GetMutableStyledStringAccessor,
            GetNavDestinationContextAccessor,
            GetNavExtenderAccessor,
            GetNavigationTransitionProxyAccessor,
            GetNavPathInfoAccessor,
            GetNavPathStackAccessor,
            GetNodeContainerOpsAccessor,
            GetNodeContentExtenderAccessor,
            GetOffscreenCanvasAccessor,
            GetOffscreenCanvasRenderingContext2DAccessor,
            GetPanGestureEventAccessor,
            GetPanGestureOptionsAccessor,
            GetPanRecognizerAccessor,
            GetParagraphStyleAccessor,
            GetPasteEventAccessor,
            GetPath2DAccessor,
            GetPatternLockControllerAccessor,
            GetPermissionRequestAccessor,
            GetPersistentStorageBackendAccessor,
            GetPinchGestureEventAccessor,
            GetPinchRecognizerAccessor,
            GetPixelMapMockAccessor,
            GetProgressMaskAccessor,
            GetPromptActionExtenderAccessor,
            GetPulseSymbolEffectAccessor,
            GetRenderingContextSettingsAccessor,
            GetRenderServiceNodeAccessor,
            GetReplaceSymbolEffectAccessor,
            GetRestrictedWorkerAccessor,
            GetRichEditorBaseControllerAccessor,
            GetRichEditorControllerAccessor,
            GetRichEditorStyledStringControllerAccessor,
            GetRotationGestureAccessor,
            GetRotationGestureEventAccessor,
            GetRotationRecognizerAccessor,
            GetRouterExtenderAccessor,
            GetScaleSymbolEffectAccessor,
            GetScreenCaptureHandlerAccessor,
            GetScreenshotServiceAccessor,
            GetScrollableTargetInfoAccessor,
            GetScrollerAccessor,
            GetScrollMotionAccessor,
            GetScrollResultAccessor,
            GetSearchControllerAccessor,
            GetSearchOpsAccessor,
            GetSelectExtenderAccessor,
            GetSliderExtenderAccessor,
            GetSpringMotionAccessor,
            GetSpringPropAccessor,
            GetSslErrorHandlerAccessor,
            GetStateStylesOpsAccessor,
            GetStyledStringAccessor,
            GetStyledStringControllerAccessor,
            GetSubmitEventAccessor,
            GetSwipeGestureAccessor,
            GetSwipeGestureEventAccessor,
            GetSwiperContentTransitionProxyAccessor,
            GetSwiperControllerAccessor,
            GetSwipeRecognizerAccessor,
            GetSymbolEffectAccessor,
            GetSystemOpsAccessor,
            GetTabBarSymbolAccessor,
            GetTabContentTransitionProxyAccessor,
            GetTabsControllerAccessor,
            GetTabsExtenderAccessor,
            GetTapGestureEventAccessor,
            GetTapRecognizerAccessor,
            GetTextAreaControllerAccessor,
            GetTextBaseControllerAccessor,
            GetTextClockControllerAccessor,
            GetTextContentControllerBaseAccessor,
            GetTextControllerAccessor,
            GetTextEditControllerExAccessor,
            GetTextFieldOpsAccessor,
            GetTextInputControllerAccessor,
            GetTextMenuItemIdAccessor,
            GetTextPickerDialogAccessor,
            GetTextShadowStyleAccessor,
            GetTextStyleAccessor,
            GetTextTimerControllerAccessor,
            GetThemeOpsAccessor,
            GetTimePickerDialogAccessor,
            GetTouchEventAccessor,
            GetTransitionEffectAccessor,
            GetUICommonEventAccessor,
            GetUIContextAtomicServiceBarAccessor,
            GetUIExtensionProxyAccessor,
            GetUrlStyleAccessor,
            GetVideoControllerAccessor,
            GetWaterFlowSectionsAccessor,
            GetWebContextMenuParamAccessor,
            GetWebContextMenuResultAccessor,
            GetWebKeyboardControllerAccessor,
            GetWebResourceErrorAccessor,
            GetWebResourceRequestAccessor,
            GetWebResourceResponseAccessor,
            GetXComponentControllerAccessor,
            GetGlobalScopeAccessor,
        };
        return &accessorsImpl;
    }
    const GENERATED_ArkUIBasicNodeAPI* GENERATED_GetBasicAPI()
    {
        static const GENERATED_ArkUIBasicNodeAPI basicNodeAPIImpl = {
            GENERATED_ARKUI_BASIC_NODE_API_VERSION, // version
            OHOS::Ace::NG::GeneratedBridge::CreateNode,
            OHOS::Ace::NG::GeneratedApiImpl::GetNodeByViewStack,
            OHOS::Ace::NG::GeneratedApiImpl::DisposeNode,
            OHOS::Ace::NG::GeneratedApiImpl::DumpTreeNode,
            OHOS::Ace::NG::GeneratedApiImpl::AddChild,
            OHOS::Ace::NG::GeneratedApiImpl::RemoveChild,
            OHOS::Ace::NG::GeneratedApiImpl::InsertChildAfter,
            OHOS::Ace::NG::GeneratedApiImpl::InsertChildBefore,
            OHOS::Ace::NG::GeneratedApiImpl::InsertChildAt,
            OHOS::Ace::NG::GeneratedApiImpl::ApplyModifierFinish,
            OHOS::Ace::NG::GeneratedApiImpl::MarkDirty,
            OHOS::Ace::NG::GeneratedApiImpl::IsBuilderNode,
            OHOS::Ace::NG::GeneratedApiImpl::ConvertLengthMetricsUnit
        };
        return &basicNodeAPIImpl;
    }

    const GENERATED_ArkUIExtendedNodeAPI* GENERATED_GetExtendedAPI()
    {
        static const GENERATED_ArkUIExtendedNodeAPI extendedNodeAPIImpl = {
            GENERATED_ARKUI_EXTENDED_NODE_API_VERSION, // version
            OHOS::Ace::NG::GeneratedApiImpl::GetDensity,
            OHOS::Ace::NG::GeneratedApiImpl::GetFontScale,
            OHOS::Ace::NG::GeneratedApiImpl::GetDesignWidthScale,
            OHOS::Ace::NG::GeneratedApiImpl::SetCallbackMethod,
            OHOS::Ace::NG::GeneratedApiImpl::SetCustomMethodFlag,
            OHOS::Ace::NG::GeneratedApiImpl::GetCustomMethodFlag,
            OHOS::Ace::NG::GeneratedApiImpl::SetCustomCallback,
            OHOS::Ace::NG::GeneratedApiImpl::SetCustomNodeDestroyCallback,
            OHOS::Ace::NG::GeneratedApiImpl::MeasureLayoutAndDraw,
            OHOS::Ace::NG::GeneratedApiImpl::MeasureNode,
            OHOS::Ace::NG::GeneratedApiImpl::LayoutNode,
            OHOS::Ace::NG::GeneratedApiImpl::DrawNode,
            OHOS::Ace::NG::GeneratedApiImpl::SetAttachNodePtr,
            OHOS::Ace::NG::GeneratedApiImpl::GetAttachNodePtr,
            OHOS::Ace::NG::GeneratedApiImpl::SetMeasureWidth,
            OHOS::Ace::NG::GeneratedApiImpl::GetMeasureWidth,
            OHOS::Ace::NG::GeneratedApiImpl::SetMeasureHeight,
            OHOS::Ace::NG::GeneratedApiImpl::GetMeasureHeight,
            OHOS::Ace::NG::GeneratedApiImpl::SetX,
            OHOS::Ace::NG::GeneratedApiImpl::GetX,
            OHOS::Ace::NG::GeneratedApiImpl::SetY,
            OHOS::Ace::NG::GeneratedApiImpl::GetY,
            OHOS::Ace::NG::GeneratedApiImpl::GetLayoutConstraint,
            OHOS::Ace::NG::GeneratedApiImpl::SetAlignment,
            OHOS::Ace::NG::GeneratedApiImpl::GetAlignment,
            OHOS::Ace::NG::GeneratedApiImpl::IndexerChecker,
            OHOS::Ace::NG::GeneratedApiImpl::SetRangeUpdater,
            OHOS::Ace::NG::GeneratedApiImpl::SetLazyItemIndexer,
            OHOS::Ace::NG::GeneratedApiImpl::GetPipelineContext,
            OHOS::Ace::NG::GeneratedApiImpl::SetVsyncCallback,
            OHOS::Ace::NG::GeneratedApiImpl::SetChildTotalCount,
            OHOS::Ace::NG::GeneratedApiImpl::ShowCrash
        };
        return &extendedNodeAPIImpl;
    }

    // Improve: remove me!
    const GENERATED_ArkUIFullNodeAPI* GENERATED_GetFullAPI()
    {
        static const GENERATED_ArkUIFullNodeAPI fullAPIImpl = {
            GENERATED_ARKUI_FULL_API_VERSION, // version
            GENERATED_GetArkUINodeModifiers,
            GENERATED_GetArkUIAccessors,
        };
        return &fullAPIImpl;
    }

    void setLogger(const ServiceLogger* logger) {
        SetDummyLogger(reinterpret_cast<const GroupLogger*>(logger));
    }


    const GenericServiceAPI* GetServiceAPI()
    {
        static const GenericServiceAPI serviceAPIImpl = {
            GENERIC_SERVICE_API_VERSION, // version
            setLogger
        };
        return &serviceAPIImpl;
    }

    EXTERN_C IDLIZE_API_EXPORT const OH_AnyAPI* GENERATED_GetArkAnyAPI(
        GENERATED_Ark_APIVariantKind kind, int version)
    {
        switch (static_cast<int>(kind)) {
            case static_cast<int>(GENERATED_FULL):
                if (version == GENERATED_ARKUI_FULL_API_VERSION) {
                    return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetFullAPI());
                }
                break;
            case static_cast<int>(GENERATED_BASIC):
                if (version == GENERATED_ARKUI_BASIC_NODE_API_VERSION) {
                    return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetBasicAPI());
                }
                break;
            case static_cast<int>(GENERATED_EXTENDED):
                if (version == GENERATED_ARKUI_EXTENDED_NODE_API_VERSION) {
                    return reinterpret_cast<const OH_AnyAPI*>(GENERATED_GetExtendedAPI());
                }
                break;
            case static_cast<int>(GENERIC_SERVICE_API_KIND):
                if (version == GENERIC_SERVICE_API_VERSION) {
                    return reinterpret_cast<const OH_AnyAPI*>(GetServiceAPI());
                }
                break;
            default:
                break;
        }
        return nullptr;
    }

}
