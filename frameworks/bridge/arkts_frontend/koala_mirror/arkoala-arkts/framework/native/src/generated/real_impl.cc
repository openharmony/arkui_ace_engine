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
        _logData.append("  Ark_NodeHandle peer" + std::to_string((uintptr_t)result) + " = GetBasicNodeApi()->createNode(GENERATED_Ark_NodeType("
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
    Ark_NodeHandle result = (Ark_NodeHandle) 234;
    if (needGroupedLog(2)) {
        std::string _logData;
        _logData.append("  Ark_NodeHandle peer" + std::to_string((uintptr_t)result) + " = GetBasicNodeApi()->getNodeByViewStack();\n");
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
        _logData.append("  GetBasicNodeApi()->disposeNode(peer" + std::to_string((uintptr_t)node) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->dumpTreeNode(peer" + std::to_string((uintptr_t)node) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->applyModifierFinish(peer" + std::to_string((uintptr_t)node) + ");\n");
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
        _logData.append("  GetBasicNodeApi()->markDirty(peer" + std::to_string((uintptr_t)node) + ", " + std::to_string(flag) + ");\n");
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
            + std::to_string((uintptr_t)node) + ");\n");
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
    return AsNode(node)->layout(vmContext, (Ark_Float32*)data);
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
    return (Ark_PipelineContext)42;
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

    namespace EventEmulatorAccessor {
    void EmitClickEventImpl(Ark_NativePointer node,
                            Ark_ClickEvent event)
    {
        auto frameNode = AsNode(node);
        frameNode->callClickEvent(event);
    }
    } // EventEmulatorAccessor
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
    void ColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void PopupColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void PopupBackgroundImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void PopupSelectedColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void PopupUnselectedColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
    {
    }
    void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                      const Opt_ResourceColor* value)
    {
    }
    void UsingPopupImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SelectedFontImpl(Ark_NativePointer node,
                          const Opt_Font* value)
    {
    }
    void PopupFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
    {
    }
    void PopupItemFontImpl(Ark_NativePointer node,
                           const Opt_Font* value)
    {
    }
    void ItemSizeImpl(Ark_NativePointer node,
                      const Opt_Union_String_Number* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Opt_OnAlphabetIndexerSelectCallback* value)
    {
    }
    void OnRequestPopupDataImpl(Ark_NativePointer node,
                                const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
    {
    }
    void OnPopupSelectImpl(Ark_NativePointer node,
                           const Opt_OnAlphabetIndexerPopupSelectCallback* value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void PopupPositionImpl(Ark_NativePointer node,
                           const Opt_Position* value)
    {
    }
    void AutoCollapseImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                                   const Opt_Number* value)
    {
    }
    void ItemBorderRadiusImpl(Ark_NativePointer node,
                              const Opt_Number* value)
    {
    }
    void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                      const Opt_BlurStyle* value)
    {
    }
    void PopupTitleBackgroundImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void AlignStyleImpl(Ark_NativePointer node,
                        const Opt_IndexerAlign* value,
                        const Opt_Length* offset)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Opt_Number_Void* callback_)
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
    void StateImpl(Ark_NativePointer node,
                   const Opt_AnimationStatus* value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void CurveImpl(Ark_NativePointer node,
                   const Opt_curves_Curve* value)
    {
    }
    void DelayImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void FillModeImpl(Ark_NativePointer node,
                      const Opt_FillMode* value)
    {
    }
    void IterationsImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void PlayModeImpl(Ark_NativePointer node,
                      const Opt_PlayMode* value)
    {
    }
    void MotionImpl(Ark_NativePointer node,
                    const Opt_Union_SpringMotion_FrictionMotion_ScrollMotion* value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnRepeatImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnCancelImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnFrameImpl(Ark_NativePointer node,
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
    void SetBadgeOptions0Impl(Ark_NativePointer node,
                              const Ark_BadgeParamWithNumber* value)
    {
    }
    void SetBadgeOptions1Impl(Ark_NativePointer node,
                              const Ark_BadgeParamWithString* value)
    {
    }
    } // BadgeInterfaceModifier
    namespace BaseSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void TextBackgroundStyleImpl(Ark_NativePointer node,
                                 const Opt_TextBackgroundStyle* value)
    {
    }
    void BaselineOffsetImpl(Ark_NativePointer node,
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
    void ColorImpl(Ark_NativePointer node,
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
    void SetButtonOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetButtonOptions1Impl(Ark_NativePointer node,
                               const Ark_ButtonOptions* options)
    {
    }
    void SetButtonOptions2Impl(Ark_NativePointer node,
                               const Ark_ResourceStr* label,
                               const Opt_ButtonOptions* options)
    {
    }
    } // ButtonInterfaceModifier
    namespace ButtonAttributeModifier {
    void TypeImpl(Ark_NativePointer node,
                  const Opt_ButtonType* value)
    {
    }
    void StateEffectImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void ButtonStyleImpl(Ark_NativePointer node,
                         const Opt_ButtonStyleMode* value)
    {
    }
    void ControlSizeImpl(Ark_NativePointer node,
                         const Opt_ControlSize* value)
    {
    }
    void RoleImpl(Ark_NativePointer node,
                  const Opt_ButtonRole* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void LabelStyleImpl(Ark_NativePointer node,
                        const Opt_ButtonLabelStyle* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
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
    void TextStyleImpl(Ark_NativePointer node,
                       const Opt_PickerTextStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Date_Void* value)
    {
    }
    void MarkTodayImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void EdgeAlignImpl(Ark_NativePointer node,
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
    void SetCanvasOptions0Impl(Ark_NativePointer node,
                               const Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext* context)
    {
    }
    void SetCanvasOptions1Impl(Ark_NativePointer node,
                               const Ark_Union_CanvasRenderingContext2D_DrawingRenderingContext* context,
                               const Ark_ImageAIOptions* imageAIOptions)
    {
    }
    } // CanvasInterfaceModifier
    namespace CanvasAttributeModifier {
    void OnReadyImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
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
    void SelectImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void ShapeImpl(Ark_NativePointer node,
                   const Opt_CheckBoxShape* value)
    {
    }
    void UnselectedColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void MarkImpl(Ark_NativePointer node,
                  const Opt_MarkStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnCheckboxChangeCallback* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void _onChangeEvent_selectImpl(Ark_NativePointer node,
                                   const Callback_Opt_Boolean_Void* callback_)
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
    void SelectAllImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void UnselectedColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void MarkImpl(Ark_NativePointer node,
                  const Opt_MarkStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnCheckboxGroupChangeCallback* value)
    {
    }
    void CheckboxShapeImpl(Ark_NativePointer node,
                           const Opt_CheckBoxShape* value)
    {
    }
    void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                      const Callback_Opt_Boolean_Void* callback_)
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
                              const Opt_CircleOptions* value)
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
    void AlignItemsImpl(Ark_NativePointer node,
                        const Opt_HorizontalAlign* value)
    {
    }
    void JustifyContentImpl(Ark_NativePointer node,
                            const Opt_FlexAlign* value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Opt_PointLightStyle* value)
    {
    }
    void ReverseImpl(Ark_NativePointer node,
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
    void ResizeableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
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
    void WidthImpl(Ark_NativePointer node,
                   const Opt_Union_Length_LayoutPolicy* value)
    {
    }
    void HeightImpl(Ark_NativePointer node,
                    const Opt_Union_Length_LayoutPolicy* value)
    {
    }
    void DrawModifierImpl(Ark_NativePointer node,
                          const Opt_DrawModifier* value)
    {
    }
    void ResponseRegionImpl(Ark_NativePointer node,
                            const Opt_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void MouseResponseRegionImpl(Ark_NativePointer node,
                                 const Opt_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void SizeImpl(Ark_NativePointer node,
                  const Opt_SizeOptions* value)
    {
    }
    void ConstraintSizeImpl(Ark_NativePointer node,
                            const Opt_ConstraintSizeOptions* value)
    {
    }
    void HitTestBehaviorImpl(Ark_NativePointer node,
                             const Opt_HitTestMode* value)
    {
    }
    void OnChildTouchTestImpl(Ark_NativePointer node,
                              const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
    {
    }
    void LayoutWeightImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String* value)
    {
    }
    void ChainWeightImpl(Ark_NativePointer node,
                         const Opt_ChainWeightOptions* value)
    {
    }
    void PaddingImpl(Ark_NativePointer node,
                     const Opt_Union_Padding_Length_LocalizedPadding* value)
    {
    }
    void SafeAreaPaddingImpl(Ark_NativePointer node,
                             const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
    {
    }
    void MarginImpl(Ark_NativePointer node,
                    const Opt_Union_Margin_Length_LocalizedMargin* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void PixelRoundImpl(Ark_NativePointer node,
                        const Opt_PixelRoundPolicy* value)
    {
    }
    void BackgroundImageSizeImpl(Ark_NativePointer node,
                                 const Opt_Union_SizeOptions_ImageSize* value)
    {
    }
    void BackgroundImagePositionImpl(Ark_NativePointer node,
                                     const Opt_Union_Position_Alignment* value)
    {
    }
    void BackgroundEffect0Impl(Ark_NativePointer node,
                               const Opt_BackgroundEffectOptions* value)
    {
    }
    void BackgroundImageResizableImpl(Ark_NativePointer node,
                                      const Opt_ResizableOptions* value)
    {
    }
    void ForegroundEffectImpl(Ark_NativePointer node,
                              const Opt_ForegroundEffectOptions* value)
    {
    }
    void VisualEffectImpl(Ark_NativePointer node,
                          const Opt_uiEffect_VisualEffect* value)
    {
    }
    void BackgroundFilterImpl(Ark_NativePointer node,
                              const Opt_uiEffect_Filter* value)
    {
    }
    void ForegroundFilterImpl(Ark_NativePointer node,
                              const Opt_uiEffect_Filter* value)
    {
    }
    void CompositingFilterImpl(Ark_NativePointer node,
                               const Opt_uiEffect_Filter* value)
    {
    }
    void OpacityImpl(Ark_NativePointer node,
                     const Opt_Union_Number_Resource* value)
    {
    }
    void BorderImpl(Ark_NativePointer node,
                    const Opt_BorderOptions* value)
    {
    }
    void BorderStyleImpl(Ark_NativePointer node,
                         const Opt_Union_BorderStyle_EdgeStyles* value)
    {
    }
    void BorderWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
    {
    }
    void BorderColorImpl(Ark_NativePointer node,
                         const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void BorderRadiusImpl(Ark_NativePointer node,
                          const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
    {
    }
    void BorderImageImpl(Ark_NativePointer node,
                         const Opt_BorderImageOption* value)
    {
    }
    void OutlineImpl(Ark_NativePointer node,
                     const Opt_OutlineOptions* value)
    {
    }
    void OutlineStyleImpl(Ark_NativePointer node,
                          const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
    {
    }
    void OutlineWidthImpl(Ark_NativePointer node,
                          const Opt_Union_Dimension_EdgeOutlineWidths* value)
    {
    }
    void OutlineColorImpl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void OutlineRadiusImpl(Ark_NativePointer node,
                           const Opt_Union_Dimension_OutlineRadiuses* value)
    {
    }
    void ForegroundColorImpl(Ark_NativePointer node,
                             const Opt_Union_ResourceColor_ColoringStrategy* value)
    {
    }
    void OnClick0Impl(Ark_NativePointer node,
                      const Opt_Callback_ClickEvent_Void* value)
    {
    }
    void OnHoverImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_HoverEvent_Void* value)
    {
    }
    void OnHoverMoveImpl(Ark_NativePointer node,
                         const Opt_Callback_HoverEvent_Void* value)
    {
    }
    void OnAccessibilityHoverImpl(Ark_NativePointer node,
                                  const Opt_AccessibilityCallback* value)
    {
    }
    void HoverEffectImpl(Ark_NativePointer node,
                         const Opt_HoverEffect* value)
    {
    }
    void OnMouseImpl(Ark_NativePointer node,
                     const Opt_Callback_MouseEvent_Void* value)
    {
    }
    void OnTouchImpl(Ark_NativePointer node,
                     const Opt_Callback_TouchEvent_Void* value)
    {
    }
    void OnKeyEventImpl(Ark_NativePointer node,
                        const Opt_Callback_KeyEvent_Void* value)
    {
    }
    void OnDigitalCrownImpl(Ark_NativePointer node,
                            const Opt_Callback_CrownEvent_Void* value)
    {
    }
    void OnKeyPreImeImpl(Ark_NativePointer node,
                         const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void OnKeyEventDispatchImpl(Ark_NativePointer node,
                                const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void OnFocusAxisEventImpl(Ark_NativePointer node,
                              const Opt_Callback_FocusAxisEvent_Void* value)
    {
    }
    void OnAxisEventImpl(Ark_NativePointer node,
                         const Opt_Callback_AxisEvent_Void* value)
    {
    }
    void FocusableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void NextFocusImpl(Ark_NativePointer node,
                       const Opt_FocusMovement* value)
    {
    }
    void TabStopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void OnFocusImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnBlurImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
    {
    }
    void TabIndexImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void DefaultFocusImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void GroupDefaultFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void FocusOnTouchImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void FocusBoxImpl(Ark_NativePointer node,
                      const Opt_FocusBoxStyle* value)
    {
    }
    void AnimationImpl(Ark_NativePointer node,
                       const Opt_AnimateParam* value)
    {
    }
    void Transition0Impl(Ark_NativePointer node,
                         const Opt_TransitionEffect* value)
    {
    }
    void MotionBlurImpl(Ark_NativePointer node,
                        const Opt_MotionBlurOptions* value)
    {
    }
    void BrightnessImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void ContrastImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void GrayscaleImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void ColorBlendImpl(Ark_NativePointer node,
                        const Opt_Union_Color_String_Resource* value)
    {
    }
    void SaturateImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void SepiaImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void InvertImpl(Ark_NativePointer node,
                    const Opt_Union_Number_InvertOptions* value)
    {
    }
    void HueRotateImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String* value)
    {
    }
    void UseShadowBatchingImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void UseEffect0Impl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void RenderGroupImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void FreezeImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
    {
    }
    void TranslateImpl(Ark_NativePointer node,
                       const Opt_TranslateOptions* value)
    {
    }
    void ScaleImpl(Ark_NativePointer node,
                   const Opt_ScaleOptions* value)
    {
    }
    void RotateImpl(Ark_NativePointer node,
                    const Opt_RotateOptions* value)
    {
    }
    void TransformImpl(Ark_NativePointer node,
                       const Opt_Object* value)
    {
    }
    void OnAppearImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnDisAppearImpl(Ark_NativePointer node,
                         const Opt_Callback_Void* value)
    {
    }
    void OnAttachImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
    {
    }
    void OnDetachImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
    {
    }
    void OnAreaChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Area_Area_Void* value)
    {
    }
    void VisibilityImpl(Ark_NativePointer node,
                        const Opt_Visibility* value)
    {
    }
    void FlexGrowImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void FlexShrinkImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void FlexBasisImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String* value)
    {
    }
    void AlignSelfImpl(Ark_NativePointer node,
                       const Opt_ItemAlign* value)
    {
    }
    void DisplayPriorityImpl(Ark_NativePointer node,
                             const Opt_Number* value)
    {
    }
    void ZIndexImpl(Ark_NativePointer node,
                    const Opt_Number* value)
    {
    }
    void DirectionImpl(Ark_NativePointer node,
                       const Opt_Direction* value)
    {
    }
    void AlignImpl(Ark_NativePointer node,
                   const Opt_Alignment* value)
    {
    }
    void PositionImpl(Ark_NativePointer node,
                      const Opt_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void MarkAnchorImpl(Ark_NativePointer node,
                        const Opt_Union_Position_LocalizedPosition* value)
    {
    }
    void OffsetImpl(Ark_NativePointer node,
                    const Opt_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void EnabledImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void AlignRules0Impl(Ark_NativePointer node,
                         const Opt_AlignRuleOption* value)
    {
    }
    void AlignRules1Impl(Ark_NativePointer node,
                         const Opt_LocalizedAlignRuleOptions* value)
    {
    }
    void AspectRatioImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void ClickEffectImpl(Ark_NativePointer node,
                         const Opt_ClickEffect* value)
    {
    }
    void OnDragStartImpl(Ark_NativePointer node,
                         const Opt_Type_CommonMethod_onDragStart* value)
    {
    }
    void OnDragEnterImpl(Ark_NativePointer node,
                         const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void OnDragMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void OnDragLeaveImpl(Ark_NativePointer node,
                         const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void OnDrop0Impl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void OnDragEndImpl(Ark_NativePointer node,
                       const Opt_Callback_DragEvent_Opt_String_Void* value)
    {
    }
    void AllowDropImpl(Ark_NativePointer node,
                       const Opt_Array_uniformTypeDescriptor_UniformDataType* value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void DragPreview0Impl(Ark_NativePointer node,
                          const Opt_Union_CustomBuilder_DragItemInfo_String* value)
    {
    }
    void OnPreDragImpl(Ark_NativePointer node,
                       const Opt_Callback_PreDragStatus_Void* value)
    {
    }
    void LinearGradientImpl(Ark_NativePointer node,
                            const Opt_LinearGradientOptions* value)
    {
    }
    void SweepGradientImpl(Ark_NativePointer node,
                           const Opt_SweepGradientOptions* value)
    {
    }
    void RadialGradientImpl(Ark_NativePointer node,
                            const Opt_RadialGradientOptions* value)
    {
    }
    void MotionPathImpl(Ark_NativePointer node,
                        const Opt_MotionPathOptions* value)
    {
    }
    void ShadowImpl(Ark_NativePointer node,
                    const Opt_Union_ShadowOptions_ShadowStyle* value)
    {
    }
    void ClipImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
    {
    }
    void ClipShapeImpl(Ark_NativePointer node,
                       const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void MaskImpl(Ark_NativePointer node,
                  const Opt_ProgressMask* value)
    {
    }
    void MaskShapeImpl(Ark_NativePointer node,
                       const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void KeyImpl(Ark_NativePointer node,
                 const Opt_String* value)
    {
    }
    void IdImpl(Ark_NativePointer node,
                const Opt_String* value)
    {
    }
    void GeometryTransition0Impl(Ark_NativePointer node,
                                 const Opt_String* value)
    {
    }
    void StateStylesImpl(Ark_NativePointer node,
                         const Opt_StateStyles* value)
    {
    }
    void RestoreIdImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void SphericalEffectImpl(Ark_NativePointer node,
                             const Opt_Number* value)
    {
    }
    void LightUpEffectImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void PixelStretchEffectImpl(Ark_NativePointer node,
                                const Opt_PixelStretchEffectOptions* value)
    {
    }
    void AccessibilityGroup0Impl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void AccessibilityText0Impl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    void AccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                      const Opt_String* value)
    {
    }
    void AccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void AccessibilityUseSamePageImpl(Ark_NativePointer node,
                                      const Opt_AccessibilitySamePageMode* value)
    {
    }
    void AccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                            const Opt_Boolean* value)
    {
    }
    void AccessibilityText1Impl(Ark_NativePointer node,
                                const Opt_Resource* value)
    {
    }
    void AccessibilityRoleImpl(Ark_NativePointer node,
                               const Opt_AccessibilityRoleType* value)
    {
    }
    void OnAccessibilityFocusImpl(Ark_NativePointer node,
                                  const Opt_AccessibilityFocusCallback* value)
    {
    }
    void AccessibilityTextHintImpl(Ark_NativePointer node,
                                   const Opt_String* value)
    {
    }
    void AccessibilityDescription0Impl(Ark_NativePointer node,
                                       const Opt_String* value)
    {
    }
    void AccessibilityDescription1Impl(Ark_NativePointer node,
                                       const Opt_Resource* value)
    {
    }
    void AccessibilityLevelImpl(Ark_NativePointer node,
                                const Opt_String* value)
    {
    }
    void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                      const Opt_CustomNodeBuilder* value)
    {
    }
    void AccessibilityCheckedImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void AccessibilitySelectedImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void ObscuredImpl(Ark_NativePointer node,
                      const Opt_Array_ObscuredReasons* value)
    {
    }
    void ReuseIdImpl(Ark_NativePointer node,
                     const Opt_String* value)
    {
    }
    void ReuseImpl(Ark_NativePointer node,
                   const Opt_ReuseOptions* value)
    {
    }
    void RenderFitImpl(Ark_NativePointer node,
                       const Opt_RenderFit* value)
    {
    }
    void GestureModifierImpl(Ark_NativePointer node,
                             const Opt_GestureModifier* value)
    {
    }
    void BackgroundBrightnessImpl(Ark_NativePointer node,
                                  const Opt_BackgroundBrightnessOptions* value)
    {
    }
    void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                                 const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
    {
    }
    void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                            const Opt_GestureRecognizerJudgeBeginCallback* value)
    {
    }
    void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                                 const Opt_ShouldBuiltInRecognizerParallelWithCallback* value)
    {
    }
    void MonopolizeEventsImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void OnTouchInterceptImpl(Ark_NativePointer node,
                              const Opt_Callback_TouchEvent_HitTestMode* value)
    {
    }
    void OnSizeChangeImpl(Ark_NativePointer node,
                          const Opt_SizeChangeCallback* value)
    {
    }
    void AccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                         const Opt_FocusDrawLevel* value)
    {
    }
    void CustomPropertyImpl(Ark_NativePointer node,
                            const Opt_String* name,
                            const Opt_Object* value)
    {
    }
    void ExpandSafeAreaImpl(Ark_NativePointer node,
                            const Opt_Array_SafeAreaType* types,
                            const Opt_Array_SafeAreaEdge* edges)
    {
    }
    void BackgroundImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* builder,
                        const Opt_BackgroundOptions* options)
    {
    }
    void BackgroundImage0Impl(Ark_NativePointer node,
                              const Opt_Union_ResourceStr_PixelMap* src,
                              const Opt_ImageRepeat* repeat)
    {
    }
    void BackgroundImage1Impl(Ark_NativePointer node,
                              const Opt_Union_ResourceStr_PixelMap* src,
                              const Opt_BackgroundImageOptions* options)
    {
    }
    void BackgroundBlurStyleImpl(Ark_NativePointer node,
                                 const Opt_BlurStyle* style,
                                 const Opt_BackgroundBlurStyleOptions* options,
                                 const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void BackgroundEffect1Impl(Ark_NativePointer node,
                               const Opt_BackgroundEffectOptions* options,
                               const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void ForegroundBlurStyleImpl(Ark_NativePointer node,
                                 const Opt_BlurStyle* style,
                                 const Opt_ForegroundBlurStyleOptions* options,
                                 const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void OnClick1Impl(Ark_NativePointer node,
                      const Opt_Callback_ClickEvent_Void* event,
                      const Opt_Number* distanceThreshold)
    {
    }
    void FocusScopeIdImpl(Ark_NativePointer node,
                          const Opt_String* id,
                          const Opt_Boolean* isGroup,
                          const Opt_Boolean* arrowStepOut)
    {
    }
    void FocusScopePriorityImpl(Ark_NativePointer node,
                                const Opt_String* scopeId,
                                const Opt_FocusPriority* priority)
    {
    }
    void Transition1Impl(Ark_NativePointer node,
                         const Opt_TransitionEffect* effect,
                         const Opt_TransitionFinishCallback* onFinish)
    {
    }
    void GestureImpl(Ark_NativePointer node,
                     const Opt_GestureType* gesture,
                     const Opt_GestureMask* mask)
    {
    }
    void PriorityGestureImpl(Ark_NativePointer node,
                             const Opt_GestureType* gesture,
                             const Opt_GestureMask* mask)
    {
    }
    void ParallelGestureImpl(Ark_NativePointer node,
                             const Opt_GestureType* gesture,
                             const Opt_GestureMask* mask)
    {
    }
    void BlurImpl(Ark_NativePointer node,
                  const Opt_Number* blurRadius,
                  const Opt_BlurOptions* options,
                  const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void LinearGradientBlurImpl(Ark_NativePointer node,
                                const Opt_Number* value,
                                const Opt_LinearGradientBlurOptions* options)
    {
    }
    void SystemBarEffectImpl(Ark_NativePointer node)
    {
    }
    void UseEffect1Impl(Ark_NativePointer node,
                        const Opt_Boolean* useEffect,
                        const Opt_EffectType* effectType)
    {
    }
    void BackdropBlurImpl(Ark_NativePointer node,
                          const Opt_Number* radius,
                          const Opt_BlurOptions* options,
                          const Opt_SystemAdaptiveOptions* sysOptions)
    {
    }
    void SharedTransitionImpl(Ark_NativePointer node,
                              const Opt_String* id,
                              const Opt_sharedTransitionOptions* options)
    {
    }
    void ChainModeImpl(Ark_NativePointer node,
                       const Opt_Axis* direction,
                       const Opt_ChainStyle* style)
    {
    }
    void OnDrop1Impl(Ark_NativePointer node,
                     const Opt_OnDragEventCallback* eventCallback,
                     const Opt_DropOptions* dropOptions)
    {
    }
    void DragPreview1Impl(Ark_NativePointer node,
                          const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                          const Opt_PreviewConfiguration* config)
    {
    }
    void DragPreviewOptionsImpl(Ark_NativePointer node,
                                const Opt_DragPreviewOptions* value,
                                const Opt_DragInteractionOptions* options)
    {
    }
    void OverlayImpl(Ark_NativePointer node,
                     const Opt_Union_String_CustomBuilder_ComponentContent* value,
                     const Opt_OverlayOptions* options)
    {
    }
    void BlendModeImpl(Ark_NativePointer node,
                       const Opt_BlendMode* value,
                       const Opt_BlendApplyType* type)
    {
    }
    void AdvancedBlendModeImpl(Ark_NativePointer node,
                               const Opt_Union_BlendMode_Blender* effect,
                               const Opt_BlendApplyType* type)
    {
    }
    void GeometryTransition1Impl(Ark_NativePointer node,
                                 const Opt_String* id,
                                 const Opt_GeometryTransitionOptions* options)
    {
    }
    void BindTipsImpl(Ark_NativePointer node,
                      const Opt_TipsMessageType* message,
                      const Opt_TipsOptions* options)
    {
    }
    void BindPopupImpl(Ark_NativePointer node,
                       const Opt_Boolean* show,
                       const Opt_Union_PopupOptions_CustomPopupOptions* popup)
    {
    }
    void BindMenu0Impl(Ark_NativePointer node,
                       const Opt_Union_Array_MenuElement_CustomBuilder* content,
                       const Opt_MenuOptions* options)
    {
    }
    void BindMenu1Impl(Ark_NativePointer node,
                       const Opt_Boolean* isShow,
                       const Opt_Union_Array_MenuElement_CustomBuilder* content,
                       const Opt_MenuOptions* options)
    {
    }
    void BindContextMenu0Impl(Ark_NativePointer node,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_ResponseType* responseType,
                              const Opt_ContextMenuOptions* options)
    {
    }
    void BindContextMenu1Impl(Ark_NativePointer node,
                              const Opt_Boolean* isShown,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_ContextMenuOptions* options)
    {
    }
    void BindContentCover0Impl(Ark_NativePointer node,
                               const Opt_Boolean* isShow,
                               const Opt_CustomNodeBuilder* builder,
                               const Opt_ModalTransition* type)
    {
    }
    void BindContentCover1Impl(Ark_NativePointer node,
                               const Opt_Boolean* isShow,
                               const Opt_CustomNodeBuilder* builder,
                               const Opt_ContentCoverOptions* options)
    {
    }
    void BindSheetImpl(Ark_NativePointer node,
                       const Opt_Boolean* isShow,
                       const Opt_CustomNodeBuilder* builder,
                       const Opt_SheetOptions* options)
    {
    }
    void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                                 const Opt_Array_Number* ratios,
                                 const Opt_VisibleAreaChangeCallback* event)
    {
    }
    void OnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                            const Opt_VisibleAreaEventOptions* options,
                                            const Opt_VisibleAreaChangeCallback* event)
    {
    }
    void KeyboardShortcutImpl(Ark_NativePointer node,
                              const Opt_Union_String_FunctionKey* value,
                              const Opt_Array_ModifierKey* keys,
                              const Opt_Callback_Void* action)
    {
    }
    void AccessibilityGroup1Impl(Ark_NativePointer node,
                                 const Opt_Boolean* isGroup,
                                 const Opt_AccessibilityOptions* accessibilityOptions)
    {
    }
    void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
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
    void StrokeImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
    {
    }
    void FillImpl(Ark_NativePointer node,
                  const Opt_ResourceColor* value)
    {
    }
    void StrokeDashOffsetImpl(Ark_NativePointer node,
                              const Opt_Union_Number_String* value)
    {
    }
    void StrokeLineCapImpl(Ark_NativePointer node,
                           const Opt_LineCapStyle* value)
    {
    }
    void StrokeLineJoinImpl(Ark_NativePointer node,
                            const Opt_LineJoinStyle* value)
    {
    }
    void StrokeMiterLimitImpl(Ark_NativePointer node,
                              const Opt_Union_Number_String* value)
    {
    }
    void StrokeOpacityImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String_Resource* value)
    {
    }
    void FillOpacityImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void AntiAliasImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void StrokeDashArrayImpl(Ark_NativePointer node,
                             const Opt_Array_Length* value)
    {
    }
    } // CommonShapeMethodModifier
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
    void TextBackgroundStyleImpl(Ark_NativePointer node,
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
    void OnIncImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
    {
    }
    void OnDecImpl(Ark_NativePointer node,
                   const Opt_VoidCallback* value)
    {
    }
    void EnableDecImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void EnableIncImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    } // CounterAttributeModifier
    namespace CustomLayoutRootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void SubscribeOnMeasureSizeImpl(Ark_NativePointer node,
                                    const Callback_onMeasureSize_SizeResult* value)
    {
    }
    void SubscribeOnPlaceChildrenImpl(Ark_NativePointer node,
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
    void CloseEffectImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void ValueColorsImpl(Ark_NativePointer node,
                         const Opt_Array_Union_ResourceColor_LinearGradient* value)
    {
    }
    void TrackBackgroundColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void TrackShadowImpl(Ark_NativePointer node,
                         const Opt_DataPanelShadowOptions* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
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
    void LunarImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Opt_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Opt_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
    {
    }
    void OnDateChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Date_Void* value)
    {
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Date_Void* callback_)
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
    void VerticalImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void ColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
    {
    }
    void LineCapImpl(Ark_NativePointer node,
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
                                         const Ark_Want* loader,
                                         Ark_EmbeddedType type)
    {
    }
    } // EmbeddedComponentInterfaceModifier
    namespace EmbeddedComponentAttributeModifier {
    void OnTerminatedImpl(Ark_NativePointer node,
                          const Opt_Callback_TerminationInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_ErrorCallback* value)
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
    namespace FlexAttributeModifier {
    void PointLightImpl(Ark_NativePointer node,
                        const Opt_PointLightStyle* value)
    {
    }
    } // FlexAttributeModifier
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
    void AlignContentImpl(Ark_NativePointer node,
                          const Opt_Alignment* value)
    {
    }
    void OnFolderStateChangeImpl(Ark_NativePointer node,
                                 const Opt_OnFoldStatusChangeCallback* value)
    {
    }
    void OnHoverStatusChangeImpl(Ark_NativePointer node,
                                 const Opt_OnHoverStatusChangeCallback* value)
    {
    }
    void EnableAnimationImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void AutoHalfFoldImpl(Ark_NativePointer node,
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
    void SizeImpl(Ark_NativePointer node,
                  const Opt_FormSize* value)
    {
    }
    void ModuleNameImpl(Ark_NativePointer node,
                        const Opt_String* value)
    {
    }
    void DimensionImpl(Ark_NativePointer node,
                       const Opt_FormDimension* value)
    {
    }
    void AllowUpdateImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void VisibilityImpl(Ark_NativePointer node,
                        const Opt_Visibility* value)
    {
    }
    void OnAcquiredImpl(Ark_NativePointer node,
                        const Opt_Callback_FormCallbackInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_Callback_ErrorInformation_Void* value)
    {
    }
    void OnRouterImpl(Ark_NativePointer node,
                      const Opt_Callback_Object_Void* value)
    {
    }
    void OnUninstallImpl(Ark_NativePointer node,
                         const Opt_Callback_FormCallbackInfo_Void* value)
    {
    }
    void OnLoadImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
    {
    }
    void OnUpdateImpl(Ark_NativePointer node,
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
    void ValueImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void StartAngleImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void EndAngleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void ColorsImpl(Ark_NativePointer node,
                    const Opt_Union_ResourceColor_LinearGradient_Array_Tuple_Union_ResourceColor_LinearGradient_Number* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void DescriptionImpl(Ark_NativePointer node,
                         const Opt_CustomNodeBuilder* value)
    {
    }
    void TrackShadowImpl(Ark_NativePointer node,
                         const Opt_GaugeShadowOptions* value)
    {
    }
    void IndicatorImpl(Ark_NativePointer node,
                       const Opt_GaugeIndicatorOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
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
    void ColumnsTemplateImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void RowsTemplateImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void ColumnsGapImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void RowsGapImpl(Ark_NativePointer node,
                     const Opt_Length* value)
    {
    }
    void OnScrollBarUpdateImpl(Ark_NativePointer node,
                               const Opt_Callback_Number_Number_ComputedBarAttribute* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_Void* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void EditModeImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void MultiSelectableImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void MaxCountImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void MinCountImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void CellLengthImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void LayoutDirectionImpl(Ark_NativePointer node,
                             const Opt_GridDirection* value)
    {
    }
    void SupportAnimationImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void OnItemDragStartImpl(Ark_NativePointer node,
                             const Opt_OnItemDragStartCallback* value)
    {
    }
    void OnItemDragEnterImpl(Ark_NativePointer node,
                             const Opt_Callback_ItemDragInfo_Void* value)
    {
    }
    void OnItemDragMoveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
    {
    }
    void OnItemDragLeaveImpl(Ark_NativePointer node,
                             const Opt_Callback_ItemDragInfo_Number_Void* value)
    {
    }
    void OnItemDropImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
    {
    }
    void AlignItemsImpl(Ark_NativePointer node,
                        const Opt_GridItemAlignment* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_OnWillScrollCallback* value)
    {
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const Opt_OnScrollCallback* value)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Opt_Number* count,
                          const Opt_Boolean* show)
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
    void SpanImpl(Ark_NativePointer node,
                  const Opt_Union_Number_GridColColumnOption* value)
    {
    }
    void GridColOffsetImpl(Ark_NativePointer node,
                           const Opt_Union_Number_GridColColumnOption* value)
    {
    }
    void OrderImpl(Ark_NativePointer node,
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
    void RowStartImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void RowEndImpl(Ark_NativePointer node,
                    const Opt_Number* value)
    {
    }
    void ColumnStartImpl(Ark_NativePointer node,
                         const Opt_Number* value)
    {
    }
    void ColumnEndImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void SelectableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Opt_Boolean_Void* callback_)
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
    void OnBreakpointChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_String_Void* value)
    {
    }
    void AlignItemsImpl(Ark_NativePointer node,
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
                                 const Ark_Union_String_Resource* address,
                                 const Opt_Union_String_Resource* content)
    {
    }
    } // HyperlinkInterfaceModifier
    namespace HyperlinkAttributeModifier {
    void ColorImpl(Ark_NativePointer node,
                   const Opt_Union_Color_Number_String_Resource* value)
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
    void SetImageOptions0Impl(Ark_NativePointer node,
                              const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src)
    {
    }
    void SetImageOptions1Impl(Ark_NativePointer node,
                              const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                              const Ark_ImageAIOptions* imageAIOptions)
    {
    }
    } // ImageInterfaceModifier
    namespace ImageAttributeModifier {
    void AltImpl(Ark_NativePointer node,
                 const Opt_Union_String_Resource_PixelMap* value)
    {
    }
    void MatchTextDirectionImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void FitOriginalSizeImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void FillColorImpl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_ColorContent_ColorMetrics* value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       const Opt_ImageFit* value)
    {
    }
    void ImageMatrixImpl(Ark_NativePointer node,
                         const Opt_matrix4_Matrix4Transit* value)
    {
    }
    void ObjectRepeatImpl(Ark_NativePointer node,
                          const Opt_ImageRepeat* value)
    {
    }
    void AutoResizeImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void RenderModeImpl(Ark_NativePointer node,
                        const Opt_ImageRenderMode* value)
    {
    }
    void DynamicRangeModeImpl(Ark_NativePointer node,
                              const Opt_DynamicRangeMode* value)
    {
    }
    void InterpolationImpl(Ark_NativePointer node,
                           const Opt_ImageInterpolation* value)
    {
    }
    void SourceSizeImpl(Ark_NativePointer node,
                        const Opt_ImageSourceSize* value)
    {
    }
    void SyncLoadImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void ColorFilterImpl(Ark_NativePointer node,
                         const Opt_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Opt_PointLightStyle* value)
    {
    }
    void EdgeAntialiasingImpl(Ark_NativePointer node,
                              const Opt_Number* value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
                        const Opt_ImageOnCompleteCallback* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_ImageErrorCallback* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void AnalyzerConfigImpl(Ark_NativePointer node,
                            const Opt_ImageAnalyzerConfig* value)
    {
    }
    void ResizableImpl(Ark_NativePointer node,
                       const Opt_ResizableOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void EnhancedImageQualityImpl(Ark_NativePointer node,
                                  const Opt_image_ResolutionQuality* value)
    {
    }
    void OrientationImpl(Ark_NativePointer node,
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
    void ImagesImpl(Ark_NativePointer node,
                    const Opt_Array_ImageFrameInfo* value)
    {
    }
    void StateImpl(Ark_NativePointer node,
                   const Opt_AnimationStatus* value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void ReverseImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void FixedSizeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void FillModeImpl(Ark_NativePointer node,
                      const Opt_FillMode* value)
    {
    }
    void IterationsImpl(Ark_NativePointer node,
                        const Opt_Number* value)
    {
    }
    void MonitorInvisibleAreaImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnRepeatImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnCancelImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
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
    void VerticalAlignImpl(Ark_NativePointer node,
                           const Opt_ImageSpanAlignment* value)
    {
    }
    void ColorFilterImpl(Ark_NativePointer node,
                         const Opt_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       const Opt_ImageFit* value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
                        const Opt_ImageCompleteCallback* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_ImageErrorCallback* value)
    {
    }
    void AltImpl(Ark_NativePointer node,
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
    void InitialIndexImpl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void CountImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Opt_Union_DotIndicator_DigitIndicator* value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
    {
    }
    void VerticalImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
    {
    }
    } // IndicatorComponentAttributeModifier
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
    void StartPointImpl(Ark_NativePointer node,
                        const Opt_ShapePoint* value)
    {
    }
    void EndPointImpl(Ark_NativePointer node,
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
    void IndicatorStyleImpl(Ark_NativePointer node,
                            const Opt_LinearIndicatorStyle* value)
    {
    }
    void IndicatorLoopImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
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
    void AlignListItemImpl(Ark_NativePointer node,
                           const Opt_ListItemAlign* value)
    {
    }
    void ListDirectionImpl(Ark_NativePointer node,
                           const Opt_Axis* value)
    {
    }
    void ContentStartOffsetImpl(Ark_NativePointer node,
                                const Opt_Number* value)
    {
    }
    void ContentEndOffsetImpl(Ark_NativePointer node,
                              const Opt_Number* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_ListDividerOptions* value)
    {
    }
    void MultiSelectableImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void ChainAnimationImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void ChainAnimationOptionsImpl(Ark_NativePointer node,
                                   const Opt_ChainAnimationOptions* value)
    {
    }
    void StickyImpl(Ark_NativePointer node,
                    const Opt_StickyStyle* value)
    {
    }
    void ScrollSnapAlignImpl(Ark_NativePointer node,
                             const Opt_ScrollSnapAlign* value)
    {
    }
    void ChildrenMainSizeImpl(Ark_NativePointer node,
                              const Opt_ChildrenMainSize* value)
    {
    }
    void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                            const Opt_Boolean* value)
    {
    }
    void StackFromEndImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_Number_Void* value)
    {
    }
    void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                          const Opt_OnScrollVisibleContentChangeCallback* value)
    {
    }
    void OnItemMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Number_Boolean* value)
    {
    }
    void OnItemDragStartImpl(Ark_NativePointer node,
                             const Opt_OnItemDragStartCallback* value)
    {
    }
    void OnItemDragEnterImpl(Ark_NativePointer node,
                             const Opt_Callback_ItemDragInfo_Void* value)
    {
    }
    void OnItemDragMoveImpl(Ark_NativePointer node,
                            const Opt_Callback_ItemDragInfo_Number_Number_Void* value)
    {
    }
    void OnItemDragLeaveImpl(Ark_NativePointer node,
                             const Opt_Callback_ItemDragInfo_Number_Void* value)
    {
    }
    void OnItemDropImpl(Ark_NativePointer node,
                        const Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_OnWillScrollCallback* value)
    {
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const Opt_OnScrollCallback* value)
    {
    }
    void LanesImpl(Ark_NativePointer node,
                   const Opt_Union_Number_LengthConstrain* value,
                   const Opt_Dimension* gutter)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Opt_Number* count,
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
    void SelectableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void SwipeActionImpl(Ark_NativePointer node,
                         const Opt_SwipeActionOptions* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Opt_Boolean_Void* callback_)
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
    void DividerImpl(Ark_NativePointer node,
                     const Opt_ListDividerOptions* value)
    {
    }
    void ChildrenMainSizeImpl(Ark_NativePointer node,
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
    void ColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
    {
    }
    void EnableLoadingImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
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
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void AllowScaleImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* value)
    {
    }
    void MarqueeUpdateStrategyImpl(Ark_NativePointer node,
                                   const Opt_MarqueeUpdateStrategy* value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnBounceImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
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
    void FontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void RadiusImpl(Ark_NativePointer node,
                    const Opt_Union_Dimension_BorderRadiuses* value)
    {
    }
    void MenuItemDividerImpl(Ark_NativePointer node,
                             const Opt_DividerStyleOptions* value)
    {
    }
    void MenuItemGroupDividerImpl(Ark_NativePointer node,
                                  const Opt_DividerStyleOptions* value)
    {
    }
    void SubMenuExpandingModeImpl(Ark_NativePointer node,
                                  const Opt_SubMenuExpandingMode* value)
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
    void SelectedImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void SelectIconImpl(Ark_NativePointer node,
                        const Opt_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void ContentFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
    {
    }
    void ContentFontColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void LabelFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
    {
    }
    void LabelFontColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Opt_Boolean_Void* callback_)
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
    void SetNavDestinationOptionsImpl(Ark_NativePointer node)
    {
    }
    } // NavDestinationInterfaceModifier
    namespace NavDestinationAttributeModifier {
    void HideTitleBar0Impl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void HideBackButtonImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void OnShownImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnHiddenImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnBackPressedImpl(Ark_NativePointer node,
                           const Opt_Callback_Boolean* value)
    {
    }
    void OnResultImpl(Ark_NativePointer node,
                      const Opt_Callback_Opt_Object_Void* value)
    {
    }
    void ModeImpl(Ark_NativePointer node,
                  const Opt_NavDestinationMode* value)
    {
    }
    void BackButtonIcon0Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
    {
    }
    void Menus0Impl(Ark_NativePointer node,
                    const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
    {
    }
    void OnReadyImpl(Ark_NativePointer node,
                     const Opt_Callback_NavDestinationContext_Void* value)
    {
    }
    void OnWillAppearImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
    {
    }
    void OnWillDisappearImpl(Ark_NativePointer node,
                             const Opt_Callback_Void* value)
    {
    }
    void OnWillShowImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void OnWillHideImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void SystemBarStyleImpl(Ark_NativePointer node,
                            const Opt_window_SystemBarStyle* value)
    {
    }
    void RecoverableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SystemTransitionImpl(Ark_NativePointer node,
                              const Opt_NavigationSystemTransitionType* value)
    {
    }
    void BindToScrollableImpl(Ark_NativePointer node,
                              const Opt_Array_Scroller* value)
    {
    }
    void BindToNestedScrollableImpl(Ark_NativePointer node,
                                    const Opt_Array_NestedScrollInfo* value)
    {
    }
    void OnActiveImpl(Ark_NativePointer node,
                      const Opt_Callback_NavDestinationActiveReason_Void* value)
    {
    }
    void OnInactiveImpl(Ark_NativePointer node,
                        const Opt_Callback_NavDestinationActiveReason_Void* value)
    {
    }
    void CustomTransitionImpl(Ark_NativePointer node,
                              const Opt_NavDestinationTransitionDelegate* value)
    {
    }
    void OnNewParamImpl(Ark_NativePointer node,
                        const Opt_Callback_Opt_Object_Void* value)
    {
    }
    void PreferredOrientationImpl(Ark_NativePointer node,
                                  const Opt_CustomObject* value)
    {
    }
    void EnableNavigationIndicatorImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void TitleImpl(Ark_NativePointer node,
                   const Opt_Union_String_CustomBuilder_NavDestinationCommonTitle_NavDestinationCustomTitle_Resource* value,
                   const Opt_NavigationTitleOptions* options)
    {
    }
    void HideTitleBar1Impl(Ark_NativePointer node,
                           const Opt_Boolean* hide,
                           const Opt_Boolean* animated)
    {
    }
    void BackButtonIcon1Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap_SymbolGlyphModifier* icon,
                             const Opt_ResourceStr* accessibilityText)
    {
    }
    void Menus1Impl(Ark_NativePointer node,
                    const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                    const Opt_NavigationMenuOptions* options)
    {
    }
    void ToolbarConfigurationImpl(Ark_NativePointer node,
                                  const Opt_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                                  const Opt_NavigationToolbarOptions* options)
    {
    }
    void HideToolBarImpl(Ark_NativePointer node,
                         const Opt_Boolean* hide,
                         const Opt_Boolean* animated)
    {
    }
    void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                  const Opt_Array_LayoutSafeAreaType* types,
                                  const Opt_Array_LayoutSafeAreaEdge* edges)
    {
    }
    void EnableStatusBarImpl(Ark_NativePointer node,
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
    void SetNavigationOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetNavigationOptions1Impl(Ark_NativePointer node,
                                   Ark_NavPathStack pathInfos)
    {
    }
    } // NavigationInterfaceModifier
    namespace NavigationAttributeModifier {
    void NavBarWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void NavBarPositionImpl(Ark_NativePointer node,
                            const Opt_NavBarPosition* value)
    {
    }
    void NavBarWidthRangeImpl(Ark_NativePointer node,
                              const Opt_Tuple_Dimension_Dimension* value)
    {
    }
    void MinContentWidthImpl(Ark_NativePointer node,
                             const Opt_Dimension* value)
    {
    }
    void ModeImpl(Ark_NativePointer node,
                  const Opt_NavigationMode* value)
    {
    }
    void BackButtonIcon0Impl(Ark_NativePointer node,
                             const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
    {
    }
    void HideNavBarImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void HideTitleBar0Impl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void HideBackButtonImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void TitleModeImpl(Ark_NativePointer node,
                       const Opt_NavigationTitleMode* value)
    {
    }
    void Menus0Impl(Ark_NativePointer node,
                    const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
    {
    }
    void HideToolBar0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void EnableToolBarAdaptationImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void OnTitleModeChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_NavigationTitleMode_Void* value)
    {
    }
    void OnNavBarStateChangeImpl(Ark_NativePointer node,
                                 const Opt_Callback_Boolean_Void* value)
    {
    }
    void OnNavigationModeChangeImpl(Ark_NativePointer node,
                                    const Opt_Callback_NavigationMode_Void* value)
    {
    }
    void NavDestinationImpl(Ark_NativePointer node,
                            const Opt_PageMapBuilder* value)
    {
    }
    void CustomNavContentTransitionImpl(Ark_NativePointer node,
                                        const Opt_Type_NavigationAttribute_customNavContentTransition* value)
    {
    }
    void SystemBarStyleImpl(Ark_NativePointer node,
                            const Opt_window_SystemBarStyle* value)
    {
    }
    void RecoverableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void EnableDragBarImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void EnableModeChangeAnimationImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void BackButtonIcon1Impl(Ark_NativePointer node,
                             const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                             const Opt_ResourceStr* accessibilityText)
    {
    }
    void TitleImpl(Ark_NativePointer node,
                   const Opt_Union_ResourceStr_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle* value,
                   const Opt_NavigationTitleOptions* options)
    {
    }
    void HideTitleBar1Impl(Ark_NativePointer node,
                           const Opt_Boolean* hide,
                           const Opt_Boolean* animated)
    {
    }
    void Menus1Impl(Ark_NativePointer node,
                    const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                    const Opt_NavigationMenuOptions* options)
    {
    }
    void ToolbarConfigurationImpl(Ark_NativePointer node,
                                  const Opt_Union_Array_ToolbarItem_CustomBuilder* value,
                                  const Opt_NavigationToolbarOptions* options)
    {
    }
    void HideToolBar1Impl(Ark_NativePointer node,
                          const Opt_Boolean* hide,
                          const Opt_Boolean* animated)
    {
    }
    void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
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
                                     const Ark_NodeController* controller)
    {
    }
    } // NodeContainerInterfaceModifier
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
    void SideLengthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void CircleRadiusImpl(Ark_NativePointer node,
                          const Opt_Length* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void RegularColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void ActiveColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
    {
    }
    void PathColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void PathStrokeWidthImpl(Ark_NativePointer node,
                             const Opt_Union_Number_String* value)
    {
    }
    void OnPatternCompleteImpl(Ark_NativePointer node,
                               const Opt_Callback_Array_Number_Void* value)
    {
    }
    void AutoResetImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void OnDotConnectImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Void* value)
    {
    }
    void ActivateCircleStyleImpl(Ark_NativePointer node,
                                 const Opt_CircleStyleOptions* value)
    {
    }
    void SkipUnselectedPointImpl(Ark_NativePointer node,
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
    void OnCompleteImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
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
    void PointsImpl(Ark_NativePointer node,
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
    void PointsImpl(Ark_NativePointer node,
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
    void ValueImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void ColorImpl(Ark_NativePointer node,
                   const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Opt_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
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
    void ColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void ContentOpacityImpl(Ark_NativePointer node,
                            const Opt_Union_Number_Resource* value)
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
    void CheckedImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnRadioChangeCallback* value)
    {
    }
    void RadioStyleImpl(Ark_NativePointer node,
                        const Opt_RadioStyle* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void _onChangeEvent_checkedImpl(Ark_NativePointer node,
                                    const Callback_Opt_Boolean_Void* callback_)
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
    void StarsImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void StepSizeImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void StarStyleImpl(Ark_NativePointer node,
                       const Opt_StarStyleOptions* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnRatingChangeCallback* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void _onChangeEvent_ratingImpl(Ark_NativePointer node,
                                   const Callback_Opt_Number_Void* callback_)
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
    void RadiusImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Array_Union_Number_String* value)
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
    void OnStateChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_RefreshStatus_Void* value)
    {
    }
    void OnRefreshingImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
    {
    }
    void RefreshOffsetImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void PullToRefreshImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void OnOffsetChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_Number_Void* value)
    {
    }
    void PullDownRatioImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void _onChangeEvent_refreshingImpl(Ark_NativePointer node,
                                       const Callback_Boolean_Void* callback_)
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
    void GuideLineImpl(Ark_NativePointer node,
                       const Opt_Array_GuideLineStyle* value)
    {
    }
    void BarrierImpl(Ark_NativePointer node,
                     const Opt_Array_BarrierStyle* value)
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
    void SetRichEditorOptions0Impl(Ark_NativePointer node,
                                   const Ark_RichEditorOptions* value)
    {
    }
    void SetRichEditorOptions1Impl(Ark_NativePointer node,
                                   const Ark_RichEditorStyledStringOptions* options)
    {
    }
    } // RichEditorInterfaceModifier
    namespace RichEditorAttributeModifier {
    void OnReadyImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Opt_Callback_RichEditorSelection_Void* value)
    {
    }
    void OnSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_RichEditorRange_Void* value)
    {
    }
    void AboutToIMEInputImpl(Ark_NativePointer node,
                             const Opt_Callback_RichEditorInsertValue_Boolean* value)
    {
    }
    void OnIMEInputCompleteImpl(Ark_NativePointer node,
                                const Opt_Callback_RichEditorTextSpanResult_Void* value)
    {
    }
    void OnDidIMEInputImpl(Ark_NativePointer node,
                           const Opt_Callback_TextRange_Void* value)
    {
    }
    void AboutToDeleteImpl(Ark_NativePointer node,
                           const Opt_Callback_RichEditorDeleteValue_Boolean* value)
    {
    }
    void OnDeleteCompleteImpl(Ark_NativePointer node,
                              const Opt_VoidCallback* value)
    {
    }
    void CopyOptionsImpl(Ark_NativePointer node,
                         const Opt_CopyOptions* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const Opt_PasteEventCallback* value)
    {
    }
    void EnableDataDetectorImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void DataDetectorConfigImpl(Ark_NativePointer node,
                                const Opt_TextDataDetectorConfig* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void OnEditingChangeImpl(Ark_NativePointer node,
                             const Opt_Callback_Boolean_Void* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          const Opt_EnterKeyType* value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const Opt_SubmitCallback* value)
    {
    }
    void OnWillChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_RichEditorChangeValue_Boolean* value)
    {
    }
    void OnDidChangeImpl(Ark_NativePointer node,
                         const Opt_OnDidChangeCallback* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Opt_Callback_CutEvent_Void* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Opt_Callback_CopyEvent_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void KeyboardAppearanceImpl(Ark_NativePointer node,
                                const Opt_KeyboardAppearance* value)
    {
    }
    void StopBackPressImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
                               const Opt_RichEditorSpanType* spanType,
                               const Opt_CustomNodeBuilder* content,
                               const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                               const Opt_SelectionMenuOptions* options)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const Opt_CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void PlaceholderImpl(Ark_NativePointer node,
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
                                const Ark_String* content)
    {
    }
    } // RichTextInterfaceModifier
    namespace RichTextAttributeModifier {
    void OnStartImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
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
    void AlignItemsImpl(Ark_NativePointer node,
                        const Opt_VerticalAlign* value)
    {
    }
    void JustifyContentImpl(Ark_NativePointer node,
                            const Opt_FlexAlign* value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Opt_PointLightStyle* value)
    {
    }
    void ReverseImpl(Ark_NativePointer node,
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
    void ResizeableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    } // RowSplitAttributeModifier
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
    void ScrollableImpl(Ark_NativePointer node,
                        const Opt_ScrollDirection* value)
    {
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_ScrollOnWillScrollCallback* value)
    {
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const Opt_ScrollOnScrollCallback* value)
    {
    }
    void OnScrollEdgeImpl(Ark_NativePointer node,
                          const Opt_OnScrollEdgeCallback* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Opt_VoidCallback* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Opt_VoidCallback* value)
    {
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       const Opt_BarState* value)
    {
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Opt_Union_Color_Number_String* value)
    {
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Opt_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
    {
    }
    void ScrollSnapImpl(Ark_NativePointer node,
                        const Opt_ScrollSnapOptions* value)
    {
    }
    void EnablePagingImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void InitialOffsetImpl(Ark_NativePointer node,
                           const Opt_OffsetOptions* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
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
    void ScrollBarImpl(Ark_NativePointer node,
                       const Opt_BarState* value)
    {
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Opt_Union_Color_Number_String* value)
    {
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Opt_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
    {
    }
    void OnReachStartImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
    {
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Opt_Callback_Void* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
    {
    }
    void FlingSpeedLimitImpl(Ark_NativePointer node,
                             const Opt_Number* value)
    {
    }
    void ClipContentImpl(Ark_NativePointer node,
                         const Opt_Union_ContentClipMode_RectShape* value)
    {
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* value)
    {
    }
    void BackToTopImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        const Opt_EdgeEffect* edgeEffect,
                        const Opt_EdgeEffectOptions* options)
    {
    }
    void FadingEdgeImpl(Ark_NativePointer node,
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
    void EnableNestedScrollImpl(Ark_NativePointer node,
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
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void SearchIconImpl(Ark_NativePointer node,
                        const Opt_Union_IconOptions_SymbolGlyphModifier* value)
    {
    }
    void CancelButtonImpl(Ark_NativePointer node,
                          const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Opt_Dimension* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Boolean_Void* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Opt_CaretStyle* value)
    {
    }
    void PlaceholderColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void PlaceholderFontImpl(Ark_NativePointer node,
                             const Opt_Font* value)
    {
    }
    void TextFontImpl(Ark_NativePointer node,
                      const Opt_Font* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          const Opt_EnterKeyType* value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const Opt_Union_Callback_String_Void_SearchSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Opt_OnTextSelectionChangeCallback* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const Opt_OnContentScrollCallback* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Opt_Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const Opt_OnPasteCallback* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       const Opt_TextAlign* value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Opt_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String_Resource* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  const Opt_SearchType* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                    const Opt_AutoCapitalizationMode* value)
    {
    }
    void HalfLeadingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void StopBackPressImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void OnWillChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void KeyboardAppearanceImpl(Ark_NativePointer node,
                                const Opt_KeyboardAppearance* value)
    {
    }
    void SearchButtonImpl(Ark_NativePointer node,
                          const Opt_ResourceStr* value,
                          const Opt_SearchButtonOptions* option)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Opt_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const Opt_CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_String_Void* callback_)
    {
    }
    } // SearchAttributeModifier
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
    void SelectedImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
    {
    }
    void ValueImpl(Ark_NativePointer node,
                   const Opt_Union_ResourceStr_String_Resource* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void SelectedOptionBgColorImpl(Ark_NativePointer node,
                                   const Opt_ResourceColor* value)
    {
    }
    void SelectedOptionFontImpl(Ark_NativePointer node,
                                const Opt_Font* value)
    {
    }
    void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void OptionBgColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void OptionFontImpl(Ark_NativePointer node,
                        const Opt_Font* value)
    {
    }
    void OptionFontColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Opt_OnSelectCallback* value)
    {
    }
    void SpaceImpl(Ark_NativePointer node,
                   const Opt_Length* value)
    {
    }
    void ArrowPositionImpl(Ark_NativePointer node,
                           const Opt_ArrowPosition* value)
    {
    }
    void OptionWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Dimension_OptionWidthMode* value)
    {
    }
    void OptionHeightImpl(Ark_NativePointer node,
                          const Opt_Dimension* value)
    {
    }
    void MenuBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
    {
    }
    void MenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                     const Opt_BlurStyle* value)
    {
    }
    void ControlSizeImpl(Ark_NativePointer node,
                         const Opt_ControlSize* value)
    {
    }
    void MenuItemContentModifierImpl(Ark_NativePointer node,
                                     const Opt_ContentModifier* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerOptions* value)
    {
    }
    void TextModifierImpl(Ark_NativePointer node,
                          const Opt_TextModifier* value)
    {
    }
    void ArrowModifierImpl(Ark_NativePointer node,
                           const Opt_SymbolGlyphModifier* value)
    {
    }
    void OptionTextModifierImpl(Ark_NativePointer node,
                                const Opt_TextModifier* value)
    {
    }
    void SelectedOptionTextModifierImpl(Ark_NativePointer node,
                                        const Opt_TextModifier* value)
    {
    }
    void DividerStyleImpl(Ark_NativePointer node,
                          const Opt_DividerStyleOptions* value)
    {
    }
    void AvoidanceImpl(Ark_NativePointer node,
                       const Opt_AvoidanceMode* value)
    {
    }
    void MenuOutlineImpl(Ark_NativePointer node,
                         const Opt_MenuOutlineOptions* value)
    {
    }
    void MenuAlignImpl(Ark_NativePointer node,
                       const Opt_MenuAlignType* alignType,
                       const Opt_Offset* offset)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Opt_Union_Number_Resource_Void* callback_)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_Opt_Union_ResourceStr_String_Resource_Void* callback_)
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
    void ViewPortImpl(Ark_NativePointer node,
                      const Opt_ViewportRect* value)
    {
    }
    void StrokeImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
    {
    }
    void FillImpl(Ark_NativePointer node,
                  const Opt_ResourceColor* value)
    {
    }
    void StrokeDashOffsetImpl(Ark_NativePointer node,
                              const Opt_Length* value)
    {
    }
    void StrokeDashArrayImpl(Ark_NativePointer node,
                             const Opt_Array_Length* value)
    {
    }
    void StrokeLineCapImpl(Ark_NativePointer node,
                           const Opt_LineCapStyle* value)
    {
    }
    void StrokeLineJoinImpl(Ark_NativePointer node,
                            const Opt_LineJoinStyle* value)
    {
    }
    void StrokeMiterLimitImpl(Ark_NativePointer node,
                              const Opt_Length* value)
    {
    }
    void StrokeOpacityImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String_Resource* value)
    {
    }
    void FillOpacityImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Opt_Length* value)
    {
    }
    void AntiAliasImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void MeshImpl(Ark_NativePointer node,
                  const Opt_Array_Number* value,
                  const Opt_Number* column,
                  const Opt_Number* row)
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
    void ShowSideBarImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void ControlButtonImpl(Ark_NativePointer node,
                           const Opt_ButtonStyle* value)
    {
    }
    void ShowControlButtonImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void SideBarWidth0Impl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void MinSideBarWidth0Impl(Ark_NativePointer node,
                              const Opt_Number* value)
    {
    }
    void MaxSideBarWidth0Impl(Ark_NativePointer node,
                              const Opt_Number* value)
    {
    }
    void SideBarWidth1Impl(Ark_NativePointer node,
                           const Opt_Length* value)
    {
    }
    void MinSideBarWidth1Impl(Ark_NativePointer node,
                              const Opt_Length* value)
    {
    }
    void MaxSideBarWidth1Impl(Ark_NativePointer node,
                              const Opt_Length* value)
    {
    }
    void AutoHideImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void SideBarPositionImpl(Ark_NativePointer node,
                             const Opt_SideBarPosition* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerStyle* value)
    {
    }
    void MinContentWidthImpl(Ark_NativePointer node,
                             const Opt_Dimension* value)
    {
    }
    void _onChangeEvent_showSideBarImpl(Ark_NativePointer node,
                                        const Callback_Opt_Boolean_Void* callback_)
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
    void BlockColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void TrackColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_Union_ResourceColor_LinearGradient* value)
    {
    }
    void ShowStepsImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void TrackThicknessImpl(Ark_NativePointer node,
                            const Opt_Length* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_SliderChangeMode_Void* value)
    {
    }
    void BlockBorderColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void BlockBorderWidthImpl(Ark_NativePointer node,
                              const Opt_Length* value)
    {
    }
    void StepColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void TrackBorderRadiusImpl(Ark_NativePointer node,
                               const Opt_Length* value)
    {
    }
    void SelectedBorderRadiusImpl(Ark_NativePointer node,
                                  const Opt_Dimension* value)
    {
    }
    void BlockSizeImpl(Ark_NativePointer node,
                       const Opt_SizeOptions* value)
    {
    }
    void BlockStyleImpl(Ark_NativePointer node,
                        const Opt_SliderBlockStyle* value)
    {
    }
    void StepSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void SliderInteractionModeImpl(Ark_NativePointer node,
                                   const Opt_SliderInteraction* value)
    {
    }
    void MinResponsiveDistanceImpl(Ark_NativePointer node,
                                   const Opt_Number* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void SlideRangeImpl(Ark_NativePointer node,
                        const Opt_SlideRange* value)
    {
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void ShowTipsImpl(Ark_NativePointer node,
                      const Opt_Boolean* value,
                      const Opt_ResourceStr* content)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_Opt_Number_Void* callback_)
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
    void FontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String_Resource* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Opt_DecorationStyleInterface* value)
    {
    }
    void TextCaseImpl(Ark_NativePointer node,
                      const Opt_TextCase* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
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
    void AlignContentImpl(Ark_NativePointer node,
                          const Opt_Alignment* value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Opt_PointLightStyle* value)
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
    void OnFinishImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
    {
    }
    void OnSkipImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Number_Void* value)
    {
    }
    void OnNextImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Number_Void* value)
    {
    }
    void OnPreviousImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Number_Void* value)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback_)
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
    void PrevLabelImpl(Ark_NativePointer node,
                       const Opt_String* value)
    {
    }
    void NextLabelImpl(Ark_NativePointer node,
                       const Opt_String* value)
    {
    }
    void StatusImpl(Ark_NativePointer node,
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
    void IndexImpl(Ark_NativePointer node,
                   const Opt_Number* value)
    {
    }
    void IntervalImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void IndicatorImpl(Ark_NativePointer node,
                       const Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean* value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void VerticalImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void ItemSpaceImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String* value)
    {
    }
    void DisplayModeImpl(Ark_NativePointer node,
                         const Opt_SwiperDisplayMode* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void EffectModeImpl(Ark_NativePointer node,
                        const Opt_EdgeEffect* value)
    {
    }
    void DisableSwipeImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void CurveImpl(Ark_NativePointer node,
                   const Opt_Union_Curve_String_ICurve* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
    {
    }
    void OnSelectedImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Void* value)
    {
    }
    void OnUnselectedImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Void* value)
    {
    }
    void OnAnimationStartImpl(Ark_NativePointer node,
                              const Opt_OnSwiperAnimationStartCallback* value)
    {
    }
    void OnAnimationEndImpl(Ark_NativePointer node,
                            const Opt_OnSwiperAnimationEndCallback* value)
    {
    }
    void OnGestureSwipeImpl(Ark_NativePointer node,
                            const Opt_OnSwiperGestureSwipeCallback* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Opt_SwiperNestedScrollMode* value)
    {
    }
    void CustomContentTransitionImpl(Ark_NativePointer node,
                                     const Opt_SwiperContentAnimatedTransition* value)
    {
    }
    void OnContentDidScrollImpl(Ark_NativePointer node,
                                const Opt_ContentDidScrollCallback* value)
    {
    }
    void IndicatorInteractiveImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void PageFlipModeImpl(Ark_NativePointer node,
                          const Opt_PageFlipMode* value)
    {
    }
    void OnContentWillScrollImpl(Ark_NativePointer node,
                                 const Opt_ContentWillScrollCallback* value)
    {
    }
    void AutoPlayImpl(Ark_NativePointer node,
                      const Opt_Boolean* autoPlay,
                      const Opt_AutoPlayOptions* options)
    {
    }
    void DisplayArrowImpl(Ark_NativePointer node,
                          const Opt_Union_ArrowStyle_Boolean* value,
                          const Opt_Boolean* isHoverShow)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Opt_Number* count,
                          const Opt_Boolean* isShown)
    {
    }
    void DisplayCountImpl(Ark_NativePointer node,
                          const Opt_Union_Number_String_SwiperAutoFill* value,
                          const Opt_Boolean* swipeByGroup)
    {
    }
    void PrevMarginImpl(Ark_NativePointer node,
                        const Opt_Length* value,
                        const Opt_Boolean* ignoreBlank)
    {
    }
    void NextMarginImpl(Ark_NativePointer node,
                        const Opt_Length* value,
                        const Opt_Boolean* ignoreBlank)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Opt_Number_Void* callback_)
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
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String_Resource* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_Array_ResourceColor* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* value)
    {
    }
    void EffectStrategyImpl(Ark_NativePointer node,
                            const Opt_SymbolEffectStrategy* value)
    {
    }
    void RenderingStrategyImpl(Ark_NativePointer node,
                               const Opt_SymbolRenderingStrategy* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void SymbolEffectImpl(Ark_NativePointer node,
                          const Opt_SymbolEffect* symbolEffect,
                          const Opt_Union_Boolean_Number* triggerValue)
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
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String_Resource* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_Array_ResourceColor* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* value)
    {
    }
    void EffectStrategyImpl(Ark_NativePointer node,
                            const Opt_SymbolEffectStrategy* value)
    {
    }
    void RenderingStrategyImpl(Ark_NativePointer node,
                               const Opt_SymbolRenderingStrategy* value)
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
    void TabBarImpl(Ark_NativePointer node,
                    const Opt_Union_ComponentContent_SubTabBarStyle_BottomTabBarStyle_String_Resource_CustomBuilder_TabBarOptions* value)
    {
    }
    void OnWillShowImpl(Ark_NativePointer node,
                        const Opt_VoidCallback* value)
    {
    }
    void OnWillHideImpl(Ark_NativePointer node,
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
    void VerticalImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void BarPositionImpl(Ark_NativePointer node,
                         const Opt_BarPosition* value)
    {
    }
    void ScrollableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void BarWidthImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void BarHeightImpl(Ark_NativePointer node,
                       const Opt_Length* value)
    {
    }
    void AnimationDurationImpl(Ark_NativePointer node,
                               const Opt_Number* value)
    {
    }
    void AnimationModeImpl(Ark_NativePointer node,
                           const Opt_AnimationMode* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        const Opt_EdgeEffect* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
    {
    }
    void OnSelectedImpl(Ark_NativePointer node,
                        const Opt_Callback_Number_Void* value)
    {
    }
    void OnTabBarClickImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Void* value)
    {
    }
    void OnUnselectedImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Void* value)
    {
    }
    void OnAnimationStartImpl(Ark_NativePointer node,
                              const Opt_OnTabsAnimationStartCallback* value)
    {
    }
    void OnAnimationEndImpl(Ark_NativePointer node,
                            const Opt_OnTabsAnimationEndCallback* value)
    {
    }
    void OnGestureSwipeImpl(Ark_NativePointer node,
                            const Opt_OnTabsGestureSwipeCallback* value)
    {
    }
    void FadingEdgeImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerStyle* value)
    {
    }
    void BarOverlapImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void BarBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
    {
    }
    void BarGridAlignImpl(Ark_NativePointer node,
                          const Opt_BarGridColumnOptions* value)
    {
    }
    void CustomContentTransitionImpl(Ark_NativePointer node,
                                     const Opt_TabsCustomContentTransitionCallback* value)
    {
    }
    void BarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                     const Opt_BlurStyle* value)
    {
    }
    void PageFlipModeImpl(Ark_NativePointer node,
                          const Opt_PageFlipMode* value)
    {
    }
    void BarBackgroundEffectImpl(Ark_NativePointer node,
                                 const Opt_BackgroundEffectOptions* value)
    {
    }
    void OnContentWillChangeImpl(Ark_NativePointer node,
                                 const Opt_OnTabsContentWillChangeCallback* value)
    {
    }
    void BarModeImpl(Ark_NativePointer node,
                     const Opt_BarMode* value,
                     const Opt_ScrollableBarModeOptions* options)
    {
    }
    void BarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                     const Opt_BlurStyle* style,
                                     const Opt_BackgroundBlurStyleOptions* options)
    {
    }
    void CachedMaxCountImpl(Ark_NativePointer node,
                            const Opt_Number* count,
                            const Opt_TabsCacheMode* mode)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback_)
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
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String_Resource* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void LineSpacingImpl(Ark_NativePointer node,
                         const Opt_LengthMetrics* value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       const Opt_TextAlign* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          const Opt_TextOverflowOptions* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Opt_DecorationStyleInterface* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String* value)
    {
    }
    void TextCaseImpl(Ark_NativePointer node,
                      const Opt_TextCase* value)
    {
    }
    void BaselineOffsetImpl(Ark_NativePointer node,
                            const Opt_Union_Number_String* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       const Opt_WordBreak* value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               const Opt_LineBreakStrategy* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Opt_Callback_String_Void* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void EllipsisModeImpl(Ark_NativePointer node,
                          const Opt_EllipsisMode* value)
    {
    }
    void EnableDataDetectorImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void DataDetectorConfigImpl(Ark_NativePointer node,
                                const Opt_TextDataDetectorConfig* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_Number_Number_Void* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    void MarqueeOptionsImpl(Ark_NativePointer node,
                            const Opt_TextMarqueeOptions* value)
    {
    }
    void OnMarqueeStateChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_MarqueeState_Void* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void TextSelectableImpl(Ark_NativePointer node,
                            const Opt_TextSelectableMode* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void HalfLeadingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Opt_Font* fontValue,
                  const Opt_FontSettingOptions* options)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* weight,
                        const Opt_FontSettingOptions* options)
    {
    }
    void SelectionImpl(Ark_NativePointer node,
                       const Opt_Number* selectionStart,
                       const Opt_Number* selectionEnd)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
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
    void PlaceholderColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void PlaceholderFontImpl(Ark_NativePointer node,
                             const Opt_Font* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          const Opt_EnterKeyType* value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       const Opt_TextAlign* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_ResourceStr* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          const Opt_TextOverflow* value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Opt_Dimension* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Opt_CaretStyle* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const Opt_Union_Callback_EnterKeyType_Void_TextAreaSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_Number_Number_Void* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const Opt_Callback_Number_Number_Void* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Boolean_Void* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Opt_Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const Opt_Callback_String_PasteEvent_Void* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Opt_TextContentStyle* value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       const Opt_WordBreak* value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               const Opt_LineBreakStrategy* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Opt_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String_Resource* value)
    {
    }
    void LineSpacingImpl(Ark_NativePointer node,
                         const Opt_LengthMetrics* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  const Opt_TextAreaType* value)
    {
    }
    void EnableAutoFillImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void ContentTypeImpl(Ark_NativePointer node,
                         const Opt_ContentType* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                    const Opt_AutoCapitalizationMode* value)
    {
    }
    void HalfLeadingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void EllipsisModeImpl(Ark_NativePointer node,
                          const Opt_EllipsisMode* value)
    {
    }
    void StopBackPressImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void OnWillChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void KeyboardAppearanceImpl(Ark_NativePointer node,
                                const Opt_KeyboardAppearance* value)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Opt_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void ShowCounterImpl(Ark_NativePointer node,
                         const Opt_Boolean* value,
                         const Opt_InputCounterOptions* options)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const Opt_CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void _onChangeEvent_textImpl(Ark_NativePointer node,
                                 const Callback_Union_ResourceStr_Resource_String_Void* callback_)
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
    void FormatImpl(Ark_NativePointer node,
                    const Opt_ResourceStr* value)
    {
    }
    void OnDateChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Number_Void* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void DateTimeOptionsImpl(Ark_NativePointer node,
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
    void TypeImpl(Ark_NativePointer node,
                  const Opt_InputType* value)
    {
    }
    void ContentTypeImpl(Ark_NativePointer node,
                         const Opt_ContentType* value)
    {
    }
    void PlaceholderColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          const Opt_TextOverflow* value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Opt_Dimension* value)
    {
    }
    void PlaceholderFontImpl(Ark_NativePointer node,
                             const Opt_Font* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          const Opt_EnterKeyType* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_Boolean_Void* value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const Opt_OnSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Opt_OnTextSelectionChangeCallback* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const Opt_OnContentScrollCallback* value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Opt_Number* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_ResourceStr* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Opt_Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const Opt_OnPasteCallback* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
    {
    }
    void ShowPasswordIconImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       const Opt_TextAlign* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Opt_Union_TextInputStyle_TextContentStyle* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Opt_CaretStyle* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
    {
    }
    void CaretPositionImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void PasswordIconImpl(Ark_NativePointer node,
                          const Opt_PasswordIcon* value)
    {
    }
    void ShowErrorImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
    {
    }
    void ShowUnitImpl(Ark_NativePointer node,
                      const Opt_CustomNodeBuilder* value)
    {
    }
    void ShowUnderlineImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void UnderlineColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_UnderlineColor* value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      const Opt_BarState* value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Opt_Number* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       const Opt_WordBreak* value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               const Opt_LineBreakStrategy* value)
    {
    }
    void CancelButtonImpl(Ark_NativePointer node,
                          const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
    {
    }
    void SelectAllImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_Resource* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Opt_Union_Number_Resource* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  const Opt_TextHeightAdaptivePolicy* value)
    {
    }
    void EnableAutoFillImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Opt_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Opt_Union_Number_String_Resource* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String_Resource* value)
    {
    }
    void PasswordRulesImpl(Ark_NativePointer node,
                           const Opt_String* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Opt_String* value)
    {
    }
    void ShowPasswordImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void OnSecurityStateChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_Boolean_Void* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Opt_Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                    const Opt_AutoCapitalizationMode* value)
    {
    }
    void HalfLeadingImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void EllipsisModeImpl(Ark_NativePointer node,
                          const Opt_EllipsisMode* value)
    {
    }
    void StopBackPressImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void OnWillChangeImpl(Ark_NativePointer node,
                          const Opt_Callback_EditableTextChangeValue_Boolean* value)
    {
    }
    void KeyboardAppearanceImpl(Ark_NativePointer node,
                                const Opt_KeyboardAppearance* value)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Opt_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const Opt_CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void ShowCounterImpl(Ark_NativePointer node,
                         const Opt_Boolean* value,
                         const Opt_InputCounterOptions* options)
    {
    }
    void _onChangeEvent_textImpl(Ark_NativePointer node,
                                 const Callback_Union_ResourceStr_Resource_String_Void* callback_)
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
    void DefaultPickerItemHeightImpl(Ark_NativePointer node,
                                     const Opt_Union_Number_String* value)
    {
    }
    void CanLoopImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Opt_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Opt_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
    {
    }
    void DisableTextStyleAnimationImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void DefaultTextStyleImpl(Ark_NativePointer node,
                              const Opt_TextPickerTextStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnTextPickerChangeCallback* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Opt_TextPickerScrollStopCallback* value)
    {
    }
    void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                                 const Opt_TextPickerEnterSelectedAreaCallback* value)
    {
    }
    void SelectedIndexImpl(Ark_NativePointer node,
                           const Opt_Union_Number_Array_Number* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerOptions* value)
    {
    }
    void GradientHeightImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Union_Number_Array_Number_Void* callback_)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_Union_ResourceStr_Array_ResourceStr_Void* callback_)
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
    void FormatImpl(Ark_NativePointer node,
                    const Opt_String* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Opt_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       const Opt_FontStyle* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Opt_Union_Number_FontWeight_ResourceStr* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value)
    {
    }
    void OnTimerImpl(Ark_NativePointer node,
                     const Opt_Callback_Number_Number_Void* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
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
    void UseMilitaryTimeImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Opt_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Opt_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
    {
    }
    void DateTimeOptionsImpl(Ark_NativePointer node,
                             const Opt_intl_DateTimeOptions* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_OnTimePickerChangeCallback* value)
    {
    }
    void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                                 const Opt_Callback_TimePickerResult_Void* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                     const Opt_CrownSensitivity* value)
    {
    }
    void EnableCascadeImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Date_Void* callback_)
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
    void OnChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Opt_ContentModifier* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Opt_ResourceColor* value)
    {
    }
    void SwitchPointColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
    {
    }
    void SwitchStyleImpl(Ark_NativePointer node,
                         const Opt_SwitchStyle* value)
    {
    }
    void _onChangeEvent_isOnImpl(Ark_NativePointer node,
                                 const Callback_Opt_Boolean_Void* callback_)
    {
    }
    } // ToggleAttributeModifier
    namespace UIExtensionComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // UIExtensionComponentModifier
    namespace UIExtensionComponentInterfaceModifier {
    void SetUIExtensionComponentOptionsImpl(Ark_NativePointer node,
                                            const Ark_Want* want,
                                            const Opt_UIExtensionOptions* options)
    {
    }
    } // UIExtensionComponentInterfaceModifier
    namespace UIExtensionComponentAttributeModifier {
    void OnRemoteReadyImpl(Ark_NativePointer node,
                           const Opt_Callback_UIExtensionProxy_Void* value)
    {
    }
    void OnReceiveImpl(Ark_NativePointer node,
                       const Opt_Callback_Map_String_Object_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_ErrorCallback* value)
    {
    }
    void OnTerminatedImpl(Ark_NativePointer node,
                          const Opt_Callback_TerminationInfo_Void* value)
    {
    }
    void OnDrawReadyImpl(Ark_NativePointer node,
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
    void MutedImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
    {
    }
    void AutoPlayImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void ControlsImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       const Opt_ImageFit* value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Opt_VoidCallback* value)
    {
    }
    void OnFullscreenChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_FullscreenInfo_Void* value)
    {
    }
    void OnPreparedImpl(Ark_NativePointer node,
                        const Opt_Callback_PreparedInfo_Void* value)
    {
    }
    void OnSeekingImpl(Ark_NativePointer node,
                       const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void OnSeekedImpl(Ark_NativePointer node,
                      const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void OnUpdateImpl(Ark_NativePointer node,
                      const Opt_Callback_PlaybackInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
    {
    }
    void OnStopImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void AnalyzerConfigImpl(Ark_NativePointer node,
                            const Opt_ImageAnalyzerConfig* value)
    {
    }
    void SurfaceBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ColorMetrics* value)
    {
    }
    void EnableShortcutKeyImpl(Ark_NativePointer node,
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
    void ColumnsTemplateImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void ItemConstraintSizeImpl(Ark_NativePointer node,
                                const Opt_ConstraintSizeOptions* value)
    {
    }
    void RowsTemplateImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void ColumnsGapImpl(Ark_NativePointer node,
                        const Opt_Length* value)
    {
    }
    void RowsGapImpl(Ark_NativePointer node,
                     const Opt_Length* value)
    {
    }
    void LayoutDirectionImpl(Ark_NativePointer node,
                             const Opt_FlexDirection* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Opt_OnScrollFrameBeginCallback* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Opt_Callback_Number_Number_Void* value)
    {
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_OnWillScrollCallback* value)
    {
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const Opt_OnScrollCallback* value)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Opt_Number* count,
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
    void JavaScriptAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void FileAccessImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void OnlineImageAccessImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void DomStorageAccessImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void ImageAccessImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void MixedModeImpl(Ark_NativePointer node,
                       const Opt_MixedMode* value)
    {
    }
    void ZoomAccessImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
    {
    }
    void GeolocationAccessImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void JavaScriptProxyImpl(Ark_NativePointer node,
                             const Opt_JavaScriptProxy* value)
    {
    }
    void CacheModeImpl(Ark_NativePointer node,
                       const Opt_CacheMode* value)
    {
    }
    void DarkModeImpl(Ark_NativePointer node,
                      const Opt_WebDarkMode* value)
    {
    }
    void ForceDarkAccessImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
    {
    }
    void MediaOptionsImpl(Ark_NativePointer node,
                          const Opt_WebMediaOptions* value)
    {
    }
    void OverviewModeAccessImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void OverScrollModeImpl(Ark_NativePointer node,
                            const Opt_OverScrollMode* value)
    {
    }
    void BlurOnKeyboardHideModeImpl(Ark_NativePointer node,
                                    const Opt_BlurOnKeyboardHideMode* value)
    {
    }
    void TextZoomRatioImpl(Ark_NativePointer node,
                           const Opt_Int32* value)
    {
    }
    void DatabaseAccessImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void InitialScaleImpl(Ark_NativePointer node,
                          const Opt_Float64* value)
    {
    }
    void MetaViewportImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void OnPageEndImpl(Ark_NativePointer node,
                       const Opt_Callback_OnPageEndEvent_Void* value)
    {
    }
    void OnPageBeginImpl(Ark_NativePointer node,
                         const Opt_Callback_OnPageBeginEvent_Void* value)
    {
    }
    void OnProgressChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_OnProgressChangeEvent_Void* value)
    {
    }
    void OnTitleReceiveImpl(Ark_NativePointer node,
                            const Opt_Callback_OnTitleReceiveEvent_Void* value)
    {
    }
    void OnGeolocationHideImpl(Ark_NativePointer node,
                               const Opt_Callback_Void* value)
    {
    }
    void OnGeolocationShowImpl(Ark_NativePointer node,
                               const Opt_Callback_OnGeolocationShowEvent_Void* value)
    {
    }
    void OnRequestSelectedImpl(Ark_NativePointer node,
                               const Opt_Callback_Void* value)
    {
    }
    void OnAlertImpl(Ark_NativePointer node,
                     const Opt_Callback_OnAlertEvent_Boolean* value)
    {
    }
    void OnBeforeUnloadImpl(Ark_NativePointer node,
                            const Opt_Callback_OnBeforeUnloadEvent_Boolean* value)
    {
    }
    void OnConfirmImpl(Ark_NativePointer node,
                       const Opt_Callback_OnConfirmEvent_Boolean* value)
    {
    }
    void OnPromptImpl(Ark_NativePointer node,
                      const Opt_Callback_OnPromptEvent_Boolean* value)
    {
    }
    void OnConsoleImpl(Ark_NativePointer node,
                       const Opt_Callback_OnConsoleEvent_Boolean* value)
    {
    }
    void OnErrorReceiveImpl(Ark_NativePointer node,
                            const Opt_Callback_OnErrorReceiveEvent_Void* value)
    {
    }
    void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                                const Opt_Callback_OnHttpErrorReceiveEvent_Void* value)
    {
    }
    void OnDownloadStartImpl(Ark_NativePointer node,
                             const Opt_Callback_OnDownloadStartEvent_Void* value)
    {
    }
    void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                      const Opt_Callback_OnRefreshAccessedHistoryEvent_Void* value)
    {
    }
    void OnRenderExitedImpl(Ark_NativePointer node,
                            const Opt_Callback_OnRenderExitedEvent_Void* value)
    {
    }
    void OnShowFileSelectorImpl(Ark_NativePointer node,
                                const Opt_Callback_OnShowFileSelectorEvent_Boolean* value)
    {
    }
    void OnResourceLoadImpl(Ark_NativePointer node,
                            const Opt_Callback_OnResourceLoadEvent_Void* value)
    {
    }
    void OnFullScreenExitImpl(Ark_NativePointer node,
                              const Opt_Callback_Void* value)
    {
    }
    void OnFullScreenEnterImpl(Ark_NativePointer node,
                               const Opt_OnFullScreenEnterCallback* value)
    {
    }
    void OnScaleChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_OnScaleChangeEvent_Void* value)
    {
    }
    void OnHttpAuthRequestImpl(Ark_NativePointer node,
                               const Opt_Callback_OnHttpAuthRequestEvent_Boolean* value)
    {
    }
    void OnInterceptRequestImpl(Ark_NativePointer node,
                                const Opt_Callback_OnInterceptRequestEvent_WebResourceResponse* value)
    {
    }
    void OnPermissionRequestImpl(Ark_NativePointer node,
                                 const Opt_Callback_OnPermissionRequestEvent_Void* value)
    {
    }
    void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnScreenCaptureRequestEvent_Void* value)
    {
    }
    void OnContextMenuShowImpl(Ark_NativePointer node,
                               const Opt_Callback_OnContextMenuShowEvent_Boolean* value)
    {
    }
    void OnContextMenuHideImpl(Ark_NativePointer node,
                               const Opt_OnContextMenuHideCallback* value)
    {
    }
    void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    void OnSearchResultReceiveImpl(Ark_NativePointer node,
                                   const Opt_Callback_OnSearchResultReceiveEvent_Void* value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Opt_Callback_OnScrollEvent_Void* value)
    {
    }
    void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnSslErrorEventReceiveEvent_Void* value)
    {
    }
    void OnSslErrorEventImpl(Ark_NativePointer node,
                             const Opt_OnSslErrorEventCallback* value)
    {
    }
    void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                           const Opt_Callback_OnClientAuthenticationEvent_Void* value)
    {
    }
    void OnWindowNewImpl(Ark_NativePointer node,
                         const Opt_Callback_OnWindowNewEvent_Void* value)
    {
    }
    void OnWindowExitImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
    {
    }
    void MultiWindowAccessImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
    {
    }
    void OnInterceptKeyEventImpl(Ark_NativePointer node,
                                 const Opt_Callback_KeyEvent_Boolean* value)
    {
    }
    void WebStandardFontImpl(Ark_NativePointer node,
                             const Opt_String* value)
    {
    }
    void WebSerifFontImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void WebSansSerifFontImpl(Ark_NativePointer node,
                              const Opt_String* value)
    {
    }
    void WebFixedFontImpl(Ark_NativePointer node,
                          const Opt_String* value)
    {
    }
    void WebFantasyFontImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void WebCursiveFontImpl(Ark_NativePointer node,
                            const Opt_String* value)
    {
    }
    void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                                  const Opt_Int32* value)
    {
    }
    void DefaultFontSizeImpl(Ark_NativePointer node,
                             const Opt_Int32* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Opt_Int32* value)
    {
    }
    void MinLogicalFontSizeImpl(Ark_NativePointer node,
                                const Opt_Int32* value)
    {
    }
    void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                       const Opt_String* value)
    {
    }
    void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void BlockNetworkImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
    {
    }
    void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                     const Opt_Boolean* value)
    {
    }
    void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnTouchIconUrlReceivedEvent_Void* value)
    {
    }
    void OnFaviconReceivedImpl(Ark_NativePointer node,
                               const Opt_Callback_OnFaviconReceivedEvent_Void* value)
    {
    }
    void OnPageVisibleImpl(Ark_NativePointer node,
                           const Opt_Callback_OnPageVisibleEvent_Void* value)
    {
    }
    void OnDataResubmittedImpl(Ark_NativePointer node,
                               const Opt_Callback_OnDataResubmittedEvent_Void* value)
    {
    }
    void PinchSmoothImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void OnAudioStateChangedImpl(Ark_NativePointer node,
                                 const Opt_Callback_OnAudioStateChangedEvent_Void* value)
    {
    }
    void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                    const Opt_Callback_OnFirstContentfulPaintEvent_Void* value)
    {
    }
    void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                    const Opt_OnFirstMeaningfulPaintCallback* value)
    {
    }
    void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                      const Opt_OnLargestContentfulPaintCallback* value)
    {
    }
    void OnLoadInterceptImpl(Ark_NativePointer node,
                             const Opt_Callback_OnLoadInterceptEvent_Boolean* value)
    {
    }
    void OnControllerAttachedImpl(Ark_NativePointer node,
                                  const Opt_Callback_Void* value)
    {
    }
    void OnOverScrollImpl(Ark_NativePointer node,
                          const Opt_Callback_OnOverScrollEvent_Void* value)
    {
    }
    void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                       const Opt_OnSafeBrowsingCheckResultCallback* value)
    {
    }
    void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                        const Opt_OnNavigationEntryCommittedCallback* value)
    {
    }
    void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                                   const Opt_OnIntelligentTrackingPreventionCallback* value)
    {
    }
    void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                       const Opt_Array_ScriptItem* value)
    {
    }
    void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                     const Opt_Array_ScriptItem* value)
    {
    }
    void LayoutModeImpl(Ark_NativePointer node,
                        const Opt_WebLayoutMode* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Opt_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
    {
    }
    void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
    {
    }
    void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                          const Opt_Callback_NativeEmbedDataInfo_Void* value)
    {
    }
    void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                           const Opt_OnNativeEmbedVisibilityChangeCallback* value)
    {
    }
    void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                       const Opt_Callback_NativeEmbedTouchInfo_Void* value)
    {
    }
    void CopyOptionsImpl(Ark_NativePointer node,
                         const Opt_CopyOptions* value)
    {
    }
    void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                                  const Opt_OnOverrideUrlLoadingCallback* value)
    {
    }
    void TextAutosizingImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                     const Opt_NativeMediaPlayerConfig* value)
    {
    }
    void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                          const Opt_OnRenderProcessNotRespondingCallback* value)
    {
    }
    void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                       const Opt_OnRenderProcessRespondingCallback* value)
    {
    }
    void OnViewportFitChangedImpl(Ark_NativePointer node,
                                  const Opt_OnViewportFitChangedCallback* value)
    {
    }
    void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                       const Opt_WebKeyboardCallback* value)
    {
    }
    void OnAdsBlockedImpl(Ark_NativePointer node,
                          const Opt_OnAdsBlockedCallback* value)
    {
    }
    void KeyboardAvoidModeImpl(Ark_NativePointer node,
                               const Opt_WebKeyboardAvoidMode* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             const Opt_EditMenuOptions* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void OptimizeParserBudgetImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
    {
    }
    void EnableFollowSystemFontWeightImpl(Ark_NativePointer node,
                                          const Opt_Boolean* value)
    {
    }
    void EnableWebAVSessionImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
    {
    }
    void RunJavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                          const Opt_Array_ScriptItem* value)
    {
    }
    void RunJavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                        const Opt_Array_ScriptItem* value)
    {
    }
    void RunJavaScriptOnHeadEndImpl(Ark_NativePointer node,
                                    const Opt_Array_ScriptItem* value)
    {
    }
    void NativeEmbedOptionsImpl(Ark_NativePointer node,
                                const Opt_EmbedOptions* value)
    {
    }
    void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                     const Opt_String* tag,
                                     const Opt_String* type)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
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
    void AttractionEffectImpl(Ark_NativePointer node,
                              const Opt_Position* destination,
                              const Opt_Number* fraction)
    {
    }
    } // WindowSceneAttributeModifier
    namespace XComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // XComponentModifier
    namespace XComponentInterfaceModifier {
    void SetXComponentOptions0Impl(Ark_NativePointer node,
                                   const Ark_XComponentParameter* value)
    {
    }
    void SetXComponentOptions1Impl(Ark_NativePointer node,
                                   const Ark_XComponentOptions* options)
    {
    }
    void SetXComponentOptions2Impl(Ark_NativePointer node,
                                   const Ark_NativeXComponentParameters* params)
    {
    }
    } // XComponentInterfaceModifier
    namespace XComponentAttributeModifier {
    void OnLoadImpl(Ark_NativePointer node,
                    const Opt_OnNativeLoadCallback* value)
    {
    }
    void OnDestroyImpl(Ark_NativePointer node,
                       const Opt_VoidCallback* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
    {
    }
    void EnableSecureImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
    {
    }
    void HdrBrightnessImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void EnableTransparentLayerImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
    {
    }
    } // XComponentAttributeModifier
    const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
    {
        static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
            AlphabetIndexerModifier::ConstructImpl,
            AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
            AlphabetIndexerAttributeModifier::ColorImpl,
            AlphabetIndexerAttributeModifier::SelectedColorImpl,
            AlphabetIndexerAttributeModifier::PopupColorImpl,
            AlphabetIndexerAttributeModifier::SelectedBackgroundColorImpl,
            AlphabetIndexerAttributeModifier::PopupBackgroundImpl,
            AlphabetIndexerAttributeModifier::PopupSelectedColorImpl,
            AlphabetIndexerAttributeModifier::PopupUnselectedColorImpl,
            AlphabetIndexerAttributeModifier::PopupItemBackgroundColorImpl,
            AlphabetIndexerAttributeModifier::UsingPopupImpl,
            AlphabetIndexerAttributeModifier::SelectedFontImpl,
            AlphabetIndexerAttributeModifier::PopupFontImpl,
            AlphabetIndexerAttributeModifier::PopupItemFontImpl,
            AlphabetIndexerAttributeModifier::ItemSizeImpl,
            AlphabetIndexerAttributeModifier::FontImpl,
            AlphabetIndexerAttributeModifier::OnSelectImpl,
            AlphabetIndexerAttributeModifier::OnRequestPopupDataImpl,
            AlphabetIndexerAttributeModifier::OnPopupSelectImpl,
            AlphabetIndexerAttributeModifier::SelectedImpl,
            AlphabetIndexerAttributeModifier::PopupPositionImpl,
            AlphabetIndexerAttributeModifier::AutoCollapseImpl,
            AlphabetIndexerAttributeModifier::PopupItemBorderRadiusImpl,
            AlphabetIndexerAttributeModifier::ItemBorderRadiusImpl,
            AlphabetIndexerAttributeModifier::PopupBackgroundBlurStyleImpl,
            AlphabetIndexerAttributeModifier::PopupTitleBackgroundImpl,
            AlphabetIndexerAttributeModifier::EnableHapticFeedbackImpl,
            AlphabetIndexerAttributeModifier::AlignStyleImpl,
            AlphabetIndexerAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUIAlphabetIndexerModifierImpl;
    }

    const GENERATED_ArkUIAnimatorModifier* GetAnimatorModifier()
    {
        static const GENERATED_ArkUIAnimatorModifier ArkUIAnimatorModifierImpl {
            AnimatorModifier::ConstructImpl,
            AnimatorInterfaceModifier::SetAnimatorOptionsImpl,
            AnimatorAttributeModifier::StateImpl,
            AnimatorAttributeModifier::DurationImpl,
            AnimatorAttributeModifier::CurveImpl,
            AnimatorAttributeModifier::DelayImpl,
            AnimatorAttributeModifier::FillModeImpl,
            AnimatorAttributeModifier::IterationsImpl,
            AnimatorAttributeModifier::PlayModeImpl,
            AnimatorAttributeModifier::MotionImpl,
            AnimatorAttributeModifier::OnStartImpl,
            AnimatorAttributeModifier::OnPauseImpl,
            AnimatorAttributeModifier::OnRepeatImpl,
            AnimatorAttributeModifier::OnCancelImpl,
            AnimatorAttributeModifier::OnFinishImpl,
            AnimatorAttributeModifier::OnFrameImpl,
        };
        return &ArkUIAnimatorModifierImpl;
    }

    const GENERATED_ArkUIBadgeModifier* GetBadgeModifier()
    {
        static const GENERATED_ArkUIBadgeModifier ArkUIBadgeModifierImpl {
            BadgeModifier::ConstructImpl,
            BadgeInterfaceModifier::SetBadgeOptions0Impl,
            BadgeInterfaceModifier::SetBadgeOptions1Impl,
        };
        return &ArkUIBadgeModifierImpl;
    }

    const GENERATED_ArkUIBaseSpanModifier* GetBaseSpanModifier()
    {
        static const GENERATED_ArkUIBaseSpanModifier ArkUIBaseSpanModifierImpl {
            BaseSpanModifier::ConstructImpl,
            BaseSpanModifier::TextBackgroundStyleImpl,
            BaseSpanModifier::BaselineOffsetImpl,
        };
        return &ArkUIBaseSpanModifierImpl;
    }

    const GENERATED_ArkUIBlankModifier* GetBlankModifier()
    {
        static const GENERATED_ArkUIBlankModifier ArkUIBlankModifierImpl {
            BlankModifier::ConstructImpl,
            BlankInterfaceModifier::SetBlankOptionsImpl,
            BlankAttributeModifier::ColorImpl,
        };
        return &ArkUIBlankModifierImpl;
    }

    const GENERATED_ArkUIButtonModifier* GetButtonModifier()
    {
        static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
            ButtonModifier::ConstructImpl,
            ButtonInterfaceModifier::SetButtonOptions0Impl,
            ButtonInterfaceModifier::SetButtonOptions1Impl,
            ButtonInterfaceModifier::SetButtonOptions2Impl,
            ButtonAttributeModifier::TypeImpl,
            ButtonAttributeModifier::StateEffectImpl,
            ButtonAttributeModifier::ButtonStyleImpl,
            ButtonAttributeModifier::ControlSizeImpl,
            ButtonAttributeModifier::RoleImpl,
            ButtonAttributeModifier::FontColorImpl,
            ButtonAttributeModifier::FontSizeImpl,
            ButtonAttributeModifier::FontWeightImpl,
            ButtonAttributeModifier::FontStyleImpl,
            ButtonAttributeModifier::FontFamilyImpl,
            ButtonAttributeModifier::ContentModifierImpl,
            ButtonAttributeModifier::LabelStyleImpl,
            ButtonAttributeModifier::MinFontScaleImpl,
            ButtonAttributeModifier::MaxFontScaleImpl,
        };
        return &ArkUIButtonModifierImpl;
    }

    const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier()
    {
        static const GENERATED_ArkUICalendarPickerModifier ArkUICalendarPickerModifierImpl {
            CalendarPickerModifier::ConstructImpl,
            CalendarPickerInterfaceModifier::SetCalendarPickerOptionsImpl,
            CalendarPickerAttributeModifier::TextStyleImpl,
            CalendarPickerAttributeModifier::OnChangeImpl,
            CalendarPickerAttributeModifier::MarkTodayImpl,
            CalendarPickerAttributeModifier::EdgeAlignImpl,
        };
        return &ArkUICalendarPickerModifierImpl;
    }

    const GENERATED_ArkUICanvasModifier* GetCanvasModifier()
    {
        static const GENERATED_ArkUICanvasModifier ArkUICanvasModifierImpl {
            CanvasModifier::ConstructImpl,
            CanvasInterfaceModifier::SetCanvasOptions0Impl,
            CanvasInterfaceModifier::SetCanvasOptions1Impl,
            CanvasAttributeModifier::OnReadyImpl,
            CanvasAttributeModifier::EnableAnalyzerImpl,
        };
        return &ArkUICanvasModifierImpl;
    }

    const GENERATED_ArkUICheckboxModifier* GetCheckboxModifier()
    {
        static const GENERATED_ArkUICheckboxModifier ArkUICheckboxModifierImpl {
            CheckboxModifier::ConstructImpl,
            CheckboxInterfaceModifier::SetCheckboxOptionsImpl,
            CheckboxAttributeModifier::SelectImpl,
            CheckboxAttributeModifier::SelectedColorImpl,
            CheckboxAttributeModifier::ShapeImpl,
            CheckboxAttributeModifier::UnselectedColorImpl,
            CheckboxAttributeModifier::MarkImpl,
            CheckboxAttributeModifier::OnChangeImpl,
            CheckboxAttributeModifier::ContentModifierImpl,
            CheckboxAttributeModifier::_onChangeEvent_selectImpl,
        };
        return &ArkUICheckboxModifierImpl;
    }

    const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupModifier()
    {
        static const GENERATED_ArkUICheckboxGroupModifier ArkUICheckboxGroupModifierImpl {
            CheckboxGroupModifier::ConstructImpl,
            CheckboxGroupInterfaceModifier::SetCheckboxGroupOptionsImpl,
            CheckboxGroupAttributeModifier::SelectAllImpl,
            CheckboxGroupAttributeModifier::SelectedColorImpl,
            CheckboxGroupAttributeModifier::UnselectedColorImpl,
            CheckboxGroupAttributeModifier::MarkImpl,
            CheckboxGroupAttributeModifier::OnChangeImpl,
            CheckboxGroupAttributeModifier::CheckboxShapeImpl,
            CheckboxGroupAttributeModifier::_onChangeEvent_selectAllImpl,
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
            ColumnAttributeModifier::AlignItemsImpl,
            ColumnAttributeModifier::JustifyContentImpl,
            ColumnAttributeModifier::PointLightImpl,
            ColumnAttributeModifier::ReverseImpl,
        };
        return &ArkUIColumnModifierImpl;
    }

    const GENERATED_ArkUIColumnSplitModifier* GetColumnSplitModifier()
    {
        static const GENERATED_ArkUIColumnSplitModifier ArkUIColumnSplitModifierImpl {
            ColumnSplitModifier::ConstructImpl,
            ColumnSplitInterfaceModifier::SetColumnSplitOptionsImpl,
            ColumnSplitAttributeModifier::ResizeableImpl,
            ColumnSplitAttributeModifier::DividerImpl,
        };
        return &ArkUIColumnSplitModifierImpl;
    }

    const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
    {
        static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
            CommonMethodModifier::ConstructImpl,
            CommonMethodModifier::WidthImpl,
            CommonMethodModifier::HeightImpl,
            CommonMethodModifier::DrawModifierImpl,
            CommonMethodModifier::ResponseRegionImpl,
            CommonMethodModifier::MouseResponseRegionImpl,
            CommonMethodModifier::SizeImpl,
            CommonMethodModifier::ConstraintSizeImpl,
            CommonMethodModifier::HitTestBehaviorImpl,
            CommonMethodModifier::OnChildTouchTestImpl,
            CommonMethodModifier::LayoutWeightImpl,
            CommonMethodModifier::ChainWeightImpl,
            CommonMethodModifier::PaddingImpl,
            CommonMethodModifier::SafeAreaPaddingImpl,
            CommonMethodModifier::MarginImpl,
            CommonMethodModifier::BackgroundColorImpl,
            CommonMethodModifier::PixelRoundImpl,
            CommonMethodModifier::BackgroundImageSizeImpl,
            CommonMethodModifier::BackgroundImagePositionImpl,
            CommonMethodModifier::BackgroundEffect0Impl,
            CommonMethodModifier::BackgroundImageResizableImpl,
            CommonMethodModifier::ForegroundEffectImpl,
            CommonMethodModifier::VisualEffectImpl,
            CommonMethodModifier::BackgroundFilterImpl,
            CommonMethodModifier::ForegroundFilterImpl,
            CommonMethodModifier::CompositingFilterImpl,
            CommonMethodModifier::OpacityImpl,
            CommonMethodModifier::BorderImpl,
            CommonMethodModifier::BorderStyleImpl,
            CommonMethodModifier::BorderWidthImpl,
            CommonMethodModifier::BorderColorImpl,
            CommonMethodModifier::BorderRadiusImpl,
            CommonMethodModifier::BorderImageImpl,
            CommonMethodModifier::OutlineImpl,
            CommonMethodModifier::OutlineStyleImpl,
            CommonMethodModifier::OutlineWidthImpl,
            CommonMethodModifier::OutlineColorImpl,
            CommonMethodModifier::OutlineRadiusImpl,
            CommonMethodModifier::ForegroundColorImpl,
            CommonMethodModifier::OnClick0Impl,
            CommonMethodModifier::OnHoverImpl,
            CommonMethodModifier::OnHoverMoveImpl,
            CommonMethodModifier::OnAccessibilityHoverImpl,
            CommonMethodModifier::HoverEffectImpl,
            CommonMethodModifier::OnMouseImpl,
            CommonMethodModifier::OnTouchImpl,
            CommonMethodModifier::OnKeyEventImpl,
            CommonMethodModifier::OnDigitalCrownImpl,
            CommonMethodModifier::OnKeyPreImeImpl,
            CommonMethodModifier::OnKeyEventDispatchImpl,
            CommonMethodModifier::OnFocusAxisEventImpl,
            CommonMethodModifier::OnAxisEventImpl,
            CommonMethodModifier::FocusableImpl,
            CommonMethodModifier::NextFocusImpl,
            CommonMethodModifier::TabStopImpl,
            CommonMethodModifier::OnFocusImpl,
            CommonMethodModifier::OnBlurImpl,
            CommonMethodModifier::TabIndexImpl,
            CommonMethodModifier::DefaultFocusImpl,
            CommonMethodModifier::GroupDefaultFocusImpl,
            CommonMethodModifier::FocusOnTouchImpl,
            CommonMethodModifier::FocusBoxImpl,
            CommonMethodModifier::AnimationImpl,
            CommonMethodModifier::Transition0Impl,
            CommonMethodModifier::MotionBlurImpl,
            CommonMethodModifier::BrightnessImpl,
            CommonMethodModifier::ContrastImpl,
            CommonMethodModifier::GrayscaleImpl,
            CommonMethodModifier::ColorBlendImpl,
            CommonMethodModifier::SaturateImpl,
            CommonMethodModifier::SepiaImpl,
            CommonMethodModifier::InvertImpl,
            CommonMethodModifier::HueRotateImpl,
            CommonMethodModifier::UseShadowBatchingImpl,
            CommonMethodModifier::UseEffect0Impl,
            CommonMethodModifier::RenderGroupImpl,
            CommonMethodModifier::FreezeImpl,
            CommonMethodModifier::TranslateImpl,
            CommonMethodModifier::ScaleImpl,
            CommonMethodModifier::RotateImpl,
            CommonMethodModifier::TransformImpl,
            CommonMethodModifier::OnAppearImpl,
            CommonMethodModifier::OnDisAppearImpl,
            CommonMethodModifier::OnAttachImpl,
            CommonMethodModifier::OnDetachImpl,
            CommonMethodModifier::OnAreaChangeImpl,
            CommonMethodModifier::VisibilityImpl,
            CommonMethodModifier::FlexGrowImpl,
            CommonMethodModifier::FlexShrinkImpl,
            CommonMethodModifier::FlexBasisImpl,
            CommonMethodModifier::AlignSelfImpl,
            CommonMethodModifier::DisplayPriorityImpl,
            CommonMethodModifier::ZIndexImpl,
            CommonMethodModifier::DirectionImpl,
            CommonMethodModifier::AlignImpl,
            CommonMethodModifier::PositionImpl,
            CommonMethodModifier::MarkAnchorImpl,
            CommonMethodModifier::OffsetImpl,
            CommonMethodModifier::EnabledImpl,
            CommonMethodModifier::AlignRules0Impl,
            CommonMethodModifier::AlignRules1Impl,
            CommonMethodModifier::AspectRatioImpl,
            CommonMethodModifier::ClickEffectImpl,
            CommonMethodModifier::OnDragStartImpl,
            CommonMethodModifier::OnDragEnterImpl,
            CommonMethodModifier::OnDragMoveImpl,
            CommonMethodModifier::OnDragLeaveImpl,
            CommonMethodModifier::OnDrop0Impl,
            CommonMethodModifier::OnDragEndImpl,
            CommonMethodModifier::AllowDropImpl,
            CommonMethodModifier::DraggableImpl,
            CommonMethodModifier::DragPreview0Impl,
            CommonMethodModifier::OnPreDragImpl,
            CommonMethodModifier::LinearGradientImpl,
            CommonMethodModifier::SweepGradientImpl,
            CommonMethodModifier::RadialGradientImpl,
            CommonMethodModifier::MotionPathImpl,
            CommonMethodModifier::ShadowImpl,
            CommonMethodModifier::ClipImpl,
            CommonMethodModifier::ClipShapeImpl,
            CommonMethodModifier::MaskImpl,
            CommonMethodModifier::MaskShapeImpl,
            CommonMethodModifier::KeyImpl,
            CommonMethodModifier::IdImpl,
            CommonMethodModifier::GeometryTransition0Impl,
            CommonMethodModifier::StateStylesImpl,
            CommonMethodModifier::RestoreIdImpl,
            CommonMethodModifier::SphericalEffectImpl,
            CommonMethodModifier::LightUpEffectImpl,
            CommonMethodModifier::PixelStretchEffectImpl,
            CommonMethodModifier::AccessibilityGroup0Impl,
            CommonMethodModifier::AccessibilityText0Impl,
            CommonMethodModifier::AccessibilityNextFocusIdImpl,
            CommonMethodModifier::AccessibilityDefaultFocusImpl,
            CommonMethodModifier::AccessibilityUseSamePageImpl,
            CommonMethodModifier::AccessibilityScrollTriggerableImpl,
            CommonMethodModifier::AccessibilityText1Impl,
            CommonMethodModifier::AccessibilityRoleImpl,
            CommonMethodModifier::OnAccessibilityFocusImpl,
            CommonMethodModifier::AccessibilityTextHintImpl,
            CommonMethodModifier::AccessibilityDescription0Impl,
            CommonMethodModifier::AccessibilityDescription1Impl,
            CommonMethodModifier::AccessibilityLevelImpl,
            CommonMethodModifier::AccessibilityVirtualNodeImpl,
            CommonMethodModifier::AccessibilityCheckedImpl,
            CommonMethodModifier::AccessibilitySelectedImpl,
            CommonMethodModifier::ObscuredImpl,
            CommonMethodModifier::ReuseIdImpl,
            CommonMethodModifier::ReuseImpl,
            CommonMethodModifier::RenderFitImpl,
            CommonMethodModifier::GestureModifierImpl,
            CommonMethodModifier::BackgroundBrightnessImpl,
            CommonMethodModifier::OnGestureJudgeBeginImpl,
            CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
            CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
            CommonMethodModifier::MonopolizeEventsImpl,
            CommonMethodModifier::OnTouchInterceptImpl,
            CommonMethodModifier::OnSizeChangeImpl,
            CommonMethodModifier::AccessibilityFocusDrawLevelImpl,
            CommonMethodModifier::CustomPropertyImpl,
            CommonMethodModifier::ExpandSafeAreaImpl,
            CommonMethodModifier::BackgroundImpl,
            CommonMethodModifier::BackgroundImage0Impl,
            CommonMethodModifier::BackgroundImage1Impl,
            CommonMethodModifier::BackgroundBlurStyleImpl,
            CommonMethodModifier::BackgroundEffect1Impl,
            CommonMethodModifier::ForegroundBlurStyleImpl,
            CommonMethodModifier::OnClick1Impl,
            CommonMethodModifier::FocusScopeIdImpl,
            CommonMethodModifier::FocusScopePriorityImpl,
            CommonMethodModifier::Transition1Impl,
            CommonMethodModifier::GestureImpl,
            CommonMethodModifier::PriorityGestureImpl,
            CommonMethodModifier::ParallelGestureImpl,
            CommonMethodModifier::BlurImpl,
            CommonMethodModifier::LinearGradientBlurImpl,
            CommonMethodModifier::SystemBarEffectImpl,
            CommonMethodModifier::UseEffect1Impl,
            CommonMethodModifier::BackdropBlurImpl,
            CommonMethodModifier::SharedTransitionImpl,
            CommonMethodModifier::ChainModeImpl,
            CommonMethodModifier::OnDrop1Impl,
            CommonMethodModifier::DragPreview1Impl,
            CommonMethodModifier::DragPreviewOptionsImpl,
            CommonMethodModifier::OverlayImpl,
            CommonMethodModifier::BlendModeImpl,
            CommonMethodModifier::AdvancedBlendModeImpl,
            CommonMethodModifier::GeometryTransition1Impl,
            CommonMethodModifier::BindTipsImpl,
            CommonMethodModifier::BindPopupImpl,
            CommonMethodModifier::BindMenu0Impl,
            CommonMethodModifier::BindMenu1Impl,
            CommonMethodModifier::BindContextMenu0Impl,
            CommonMethodModifier::BindContextMenu1Impl,
            CommonMethodModifier::BindContentCover0Impl,
            CommonMethodModifier::BindContentCover1Impl,
            CommonMethodModifier::BindSheetImpl,
            CommonMethodModifier::OnVisibleAreaChangeImpl,
            CommonMethodModifier::OnVisibleAreaApproximateChangeImpl,
            CommonMethodModifier::KeyboardShortcutImpl,
            CommonMethodModifier::AccessibilityGroup1Impl,
            CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
        };
        return &ArkUICommonMethodModifierImpl;
    }

    const GENERATED_ArkUICommonShapeMethodModifier* GetCommonShapeMethodModifier()
    {
        static const GENERATED_ArkUICommonShapeMethodModifier ArkUICommonShapeMethodModifierImpl {
            CommonShapeMethodModifier::ConstructImpl,
            CommonShapeMethodModifier::StrokeImpl,
            CommonShapeMethodModifier::FillImpl,
            CommonShapeMethodModifier::StrokeDashOffsetImpl,
            CommonShapeMethodModifier::StrokeLineCapImpl,
            CommonShapeMethodModifier::StrokeLineJoinImpl,
            CommonShapeMethodModifier::StrokeMiterLimitImpl,
            CommonShapeMethodModifier::StrokeOpacityImpl,
            CommonShapeMethodModifier::FillOpacityImpl,
            CommonShapeMethodModifier::StrokeWidthImpl,
            CommonShapeMethodModifier::AntiAliasImpl,
            CommonShapeMethodModifier::StrokeDashArrayImpl,
        };
        return &ArkUICommonShapeMethodModifierImpl;
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
            ContainerSpanAttributeModifier::TextBackgroundStyleImpl,
        };
        return &ArkUIContainerSpanModifierImpl;
    }

    const GENERATED_ArkUICounterModifier* GetCounterModifier()
    {
        static const GENERATED_ArkUICounterModifier ArkUICounterModifierImpl {
            CounterModifier::ConstructImpl,
            CounterInterfaceModifier::SetCounterOptionsImpl,
            CounterAttributeModifier::OnIncImpl,
            CounterAttributeModifier::OnDecImpl,
            CounterAttributeModifier::EnableDecImpl,
            CounterAttributeModifier::EnableIncImpl,
        };
        return &ArkUICounterModifierImpl;
    }

    const GENERATED_ArkUICustomLayoutRootModifier* GetCustomLayoutRootModifier()
    {
        static const GENERATED_ArkUICustomLayoutRootModifier ArkUICustomLayoutRootModifierImpl {
            CustomLayoutRootModifier::ConstructImpl,
            CustomLayoutRootModifier::SubscribeOnMeasureSizeImpl,
            CustomLayoutRootModifier::SubscribeOnPlaceChildrenImpl,
        };
        return &ArkUICustomLayoutRootModifierImpl;
    }

    const GENERATED_ArkUIDataPanelModifier* GetDataPanelModifier()
    {
        static const GENERATED_ArkUIDataPanelModifier ArkUIDataPanelModifierImpl {
            DataPanelModifier::ConstructImpl,
            DataPanelInterfaceModifier::SetDataPanelOptionsImpl,
            DataPanelAttributeModifier::CloseEffectImpl,
            DataPanelAttributeModifier::ValueColorsImpl,
            DataPanelAttributeModifier::TrackBackgroundColorImpl,
            DataPanelAttributeModifier::StrokeWidthImpl,
            DataPanelAttributeModifier::TrackShadowImpl,
            DataPanelAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIDataPanelModifierImpl;
    }

    const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
    {
        static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
            DatePickerModifier::ConstructImpl,
            DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
            DatePickerAttributeModifier::LunarImpl,
            DatePickerAttributeModifier::DisappearTextStyleImpl,
            DatePickerAttributeModifier::TextStyleImpl,
            DatePickerAttributeModifier::SelectedTextStyleImpl,
            DatePickerAttributeModifier::OnDateChangeImpl,
            DatePickerAttributeModifier::DigitalCrownSensitivityImpl,
            DatePickerAttributeModifier::EnableHapticFeedbackImpl,
            DatePickerAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUIDatePickerModifierImpl;
    }

    const GENERATED_ArkUIDividerModifier* GetDividerModifier()
    {
        static const GENERATED_ArkUIDividerModifier ArkUIDividerModifierImpl {
            DividerModifier::ConstructImpl,
            DividerInterfaceModifier::SetDividerOptionsImpl,
            DividerAttributeModifier::VerticalImpl,
            DividerAttributeModifier::ColorImpl,
            DividerAttributeModifier::StrokeWidthImpl,
            DividerAttributeModifier::LineCapImpl,
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
            EmbeddedComponentAttributeModifier::OnTerminatedImpl,
            EmbeddedComponentAttributeModifier::OnErrorImpl,
        };
        return &ArkUIEmbeddedComponentModifierImpl;
    }

    const GENERATED_ArkUIFlexModifier* GetFlexModifier()
    {
        static const GENERATED_ArkUIFlexModifier ArkUIFlexModifierImpl {
            FlexModifier::ConstructImpl,
            FlexInterfaceModifier::SetFlexOptionsImpl,
            FlexAttributeModifier::PointLightImpl,
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
            FolderStackAttributeModifier::AlignContentImpl,
            FolderStackAttributeModifier::OnFolderStateChangeImpl,
            FolderStackAttributeModifier::OnHoverStatusChangeImpl,
            FolderStackAttributeModifier::EnableAnimationImpl,
            FolderStackAttributeModifier::AutoHalfFoldImpl,
        };
        return &ArkUIFolderStackModifierImpl;
    }

    const GENERATED_ArkUIFormComponentModifier* GetFormComponentModifier()
    {
        static const GENERATED_ArkUIFormComponentModifier ArkUIFormComponentModifierImpl {
            FormComponentModifier::ConstructImpl,
            FormComponentInterfaceModifier::SetFormComponentOptionsImpl,
            FormComponentAttributeModifier::SizeImpl,
            FormComponentAttributeModifier::ModuleNameImpl,
            FormComponentAttributeModifier::DimensionImpl,
            FormComponentAttributeModifier::AllowUpdateImpl,
            FormComponentAttributeModifier::VisibilityImpl,
            FormComponentAttributeModifier::OnAcquiredImpl,
            FormComponentAttributeModifier::OnErrorImpl,
            FormComponentAttributeModifier::OnRouterImpl,
            FormComponentAttributeModifier::OnUninstallImpl,
            FormComponentAttributeModifier::OnLoadImpl,
            FormComponentAttributeModifier::OnUpdateImpl,
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
            GaugeAttributeModifier::ValueImpl,
            GaugeAttributeModifier::StartAngleImpl,
            GaugeAttributeModifier::EndAngleImpl,
            GaugeAttributeModifier::ColorsImpl,
            GaugeAttributeModifier::StrokeWidthImpl,
            GaugeAttributeModifier::DescriptionImpl,
            GaugeAttributeModifier::TrackShadowImpl,
            GaugeAttributeModifier::IndicatorImpl,
            GaugeAttributeModifier::PrivacySensitiveImpl,
            GaugeAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIGaugeModifierImpl;
    }

    const GENERATED_ArkUIGridModifier* GetGridModifier()
    {
        static const GENERATED_ArkUIGridModifier ArkUIGridModifierImpl {
            GridModifier::ConstructImpl,
            GridInterfaceModifier::SetGridOptionsImpl,
            GridAttributeModifier::ColumnsTemplateImpl,
            GridAttributeModifier::RowsTemplateImpl,
            GridAttributeModifier::ColumnsGapImpl,
            GridAttributeModifier::RowsGapImpl,
            GridAttributeModifier::OnScrollBarUpdateImpl,
            GridAttributeModifier::OnScrollIndexImpl,
            GridAttributeModifier::CachedCount0Impl,
            GridAttributeModifier::EditModeImpl,
            GridAttributeModifier::MultiSelectableImpl,
            GridAttributeModifier::MaxCountImpl,
            GridAttributeModifier::MinCountImpl,
            GridAttributeModifier::CellLengthImpl,
            GridAttributeModifier::LayoutDirectionImpl,
            GridAttributeModifier::SupportAnimationImpl,
            GridAttributeModifier::OnItemDragStartImpl,
            GridAttributeModifier::OnItemDragEnterImpl,
            GridAttributeModifier::OnItemDragMoveImpl,
            GridAttributeModifier::OnItemDragLeaveImpl,
            GridAttributeModifier::OnItemDropImpl,
            GridAttributeModifier::AlignItemsImpl,
            GridAttributeModifier::OnScrollFrameBeginImpl,
            GridAttributeModifier::OnWillScrollImpl,
            GridAttributeModifier::OnDidScrollImpl,
            GridAttributeModifier::CachedCount1Impl,
        };
        return &ArkUIGridModifierImpl;
    }

    const GENERATED_ArkUIGridColModifier* GetGridColModifier()
    {
        static const GENERATED_ArkUIGridColModifier ArkUIGridColModifierImpl {
            GridColModifier::ConstructImpl,
            GridColInterfaceModifier::SetGridColOptionsImpl,
            GridColAttributeModifier::SpanImpl,
            GridColAttributeModifier::GridColOffsetImpl,
            GridColAttributeModifier::OrderImpl,
        };
        return &ArkUIGridColModifierImpl;
    }

    const GENERATED_ArkUIGridItemModifier* GetGridItemModifier()
    {
        static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
            GridItemModifier::ConstructImpl,
            GridItemInterfaceModifier::SetGridItemOptionsImpl,
            GridItemAttributeModifier::RowStartImpl,
            GridItemAttributeModifier::RowEndImpl,
            GridItemAttributeModifier::ColumnStartImpl,
            GridItemAttributeModifier::ColumnEndImpl,
            GridItemAttributeModifier::SelectableImpl,
            GridItemAttributeModifier::SelectedImpl,
            GridItemAttributeModifier::OnSelectImpl,
            GridItemAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUIGridItemModifierImpl;
    }

    const GENERATED_ArkUIGridRowModifier* GetGridRowModifier()
    {
        static const GENERATED_ArkUIGridRowModifier ArkUIGridRowModifierImpl {
            GridRowModifier::ConstructImpl,
            GridRowInterfaceModifier::SetGridRowOptionsImpl,
            GridRowAttributeModifier::OnBreakpointChangeImpl,
            GridRowAttributeModifier::AlignItemsImpl,
        };
        return &ArkUIGridRowModifierImpl;
    }

    const GENERATED_ArkUIHyperlinkModifier* GetHyperlinkModifier()
    {
        static const GENERATED_ArkUIHyperlinkModifier ArkUIHyperlinkModifierImpl {
            HyperlinkModifier::ConstructImpl,
            HyperlinkInterfaceModifier::SetHyperlinkOptionsImpl,
            HyperlinkAttributeModifier::ColorImpl,
        };
        return &ArkUIHyperlinkModifierImpl;
    }

    const GENERATED_ArkUIImageModifier* GetImageModifier()
    {
        static const GENERATED_ArkUIImageModifier ArkUIImageModifierImpl {
            ImageModifier::ConstructImpl,
            ImageInterfaceModifier::SetImageOptions0Impl,
            ImageInterfaceModifier::SetImageOptions1Impl,
            ImageAttributeModifier::AltImpl,
            ImageAttributeModifier::MatchTextDirectionImpl,
            ImageAttributeModifier::FitOriginalSizeImpl,
            ImageAttributeModifier::FillColorImpl,
            ImageAttributeModifier::ObjectFitImpl,
            ImageAttributeModifier::ImageMatrixImpl,
            ImageAttributeModifier::ObjectRepeatImpl,
            ImageAttributeModifier::AutoResizeImpl,
            ImageAttributeModifier::RenderModeImpl,
            ImageAttributeModifier::DynamicRangeModeImpl,
            ImageAttributeModifier::InterpolationImpl,
            ImageAttributeModifier::SourceSizeImpl,
            ImageAttributeModifier::SyncLoadImpl,
            ImageAttributeModifier::ColorFilterImpl,
            ImageAttributeModifier::CopyOptionImpl,
            ImageAttributeModifier::DraggableImpl,
            ImageAttributeModifier::PointLightImpl,
            ImageAttributeModifier::EdgeAntialiasingImpl,
            ImageAttributeModifier::OnCompleteImpl,
            ImageAttributeModifier::OnErrorImpl,
            ImageAttributeModifier::OnFinishImpl,
            ImageAttributeModifier::EnableAnalyzerImpl,
            ImageAttributeModifier::AnalyzerConfigImpl,
            ImageAttributeModifier::ResizableImpl,
            ImageAttributeModifier::PrivacySensitiveImpl,
            ImageAttributeModifier::EnhancedImageQualityImpl,
            ImageAttributeModifier::OrientationImpl,
        };
        return &ArkUIImageModifierImpl;
    }

    const GENERATED_ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
    {
        static const GENERATED_ArkUIImageAnimatorModifier ArkUIImageAnimatorModifierImpl {
            ImageAnimatorModifier::ConstructImpl,
            ImageAnimatorInterfaceModifier::SetImageAnimatorOptionsImpl,
            ImageAnimatorAttributeModifier::ImagesImpl,
            ImageAnimatorAttributeModifier::StateImpl,
            ImageAnimatorAttributeModifier::DurationImpl,
            ImageAnimatorAttributeModifier::ReverseImpl,
            ImageAnimatorAttributeModifier::FixedSizeImpl,
            ImageAnimatorAttributeModifier::FillModeImpl,
            ImageAnimatorAttributeModifier::IterationsImpl,
            ImageAnimatorAttributeModifier::MonitorInvisibleAreaImpl,
            ImageAnimatorAttributeModifier::OnStartImpl,
            ImageAnimatorAttributeModifier::OnPauseImpl,
            ImageAnimatorAttributeModifier::OnRepeatImpl,
            ImageAnimatorAttributeModifier::OnCancelImpl,
            ImageAnimatorAttributeModifier::OnFinishImpl,
        };
        return &ArkUIImageAnimatorModifierImpl;
    }

    const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
    {
        static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
            ImageSpanModifier::ConstructImpl,
            ImageSpanInterfaceModifier::SetImageSpanOptionsImpl,
            ImageSpanAttributeModifier::VerticalAlignImpl,
            ImageSpanAttributeModifier::ColorFilterImpl,
            ImageSpanAttributeModifier::ObjectFitImpl,
            ImageSpanAttributeModifier::OnCompleteImpl,
            ImageSpanAttributeModifier::OnErrorImpl,
            ImageSpanAttributeModifier::AltImpl,
        };
        return &ArkUIImageSpanModifierImpl;
    }

    const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
    {
        static const GENERATED_ArkUIIndicatorComponentModifier ArkUIIndicatorComponentModifierImpl {
            IndicatorComponentModifier::ConstructImpl,
            IndicatorComponentInterfaceModifier::SetIndicatorComponentOptionsImpl,
            IndicatorComponentAttributeModifier::InitialIndexImpl,
            IndicatorComponentAttributeModifier::CountImpl,
            IndicatorComponentAttributeModifier::StyleImpl,
            IndicatorComponentAttributeModifier::LoopImpl,
            IndicatorComponentAttributeModifier::VerticalImpl,
            IndicatorComponentAttributeModifier::OnChangeImpl,
        };
        return &ArkUIIndicatorComponentModifierImpl;
    }

    const GENERATED_ArkUILineModifier* GetLineModifier()
    {
        static const GENERATED_ArkUILineModifier ArkUILineModifierImpl {
            LineModifier::ConstructImpl,
            LineInterfaceModifier::SetLineOptionsImpl,
            LineAttributeModifier::StartPointImpl,
            LineAttributeModifier::EndPointImpl,
        };
        return &ArkUILineModifierImpl;
    }

    const GENERATED_ArkUILinearIndicatorModifier* GetLinearIndicatorModifier()
    {
        static const GENERATED_ArkUILinearIndicatorModifier ArkUILinearIndicatorModifierImpl {
            LinearIndicatorModifier::ConstructImpl,
            LinearIndicatorInterfaceModifier::SetLinearIndicatorOptionsImpl,
            LinearIndicatorAttributeModifier::IndicatorStyleImpl,
            LinearIndicatorAttributeModifier::IndicatorLoopImpl,
            LinearIndicatorAttributeModifier::OnChangeImpl,
        };
        return &ArkUILinearIndicatorModifierImpl;
    }

    const GENERATED_ArkUIListModifier* GetListModifier()
    {
        static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
            ListModifier::ConstructImpl,
            ListInterfaceModifier::SetListOptionsImpl,
            ListAttributeModifier::AlignListItemImpl,
            ListAttributeModifier::ListDirectionImpl,
            ListAttributeModifier::ContentStartOffsetImpl,
            ListAttributeModifier::ContentEndOffsetImpl,
            ListAttributeModifier::DividerImpl,
            ListAttributeModifier::MultiSelectableImpl,
            ListAttributeModifier::CachedCount0Impl,
            ListAttributeModifier::ChainAnimationImpl,
            ListAttributeModifier::ChainAnimationOptionsImpl,
            ListAttributeModifier::StickyImpl,
            ListAttributeModifier::ScrollSnapAlignImpl,
            ListAttributeModifier::ChildrenMainSizeImpl,
            ListAttributeModifier::MaintainVisibleContentPositionImpl,
            ListAttributeModifier::StackFromEndImpl,
            ListAttributeModifier::OnScrollIndexImpl,
            ListAttributeModifier::OnScrollVisibleContentChangeImpl,
            ListAttributeModifier::OnItemMoveImpl,
            ListAttributeModifier::OnItemDragStartImpl,
            ListAttributeModifier::OnItemDragEnterImpl,
            ListAttributeModifier::OnItemDragMoveImpl,
            ListAttributeModifier::OnItemDragLeaveImpl,
            ListAttributeModifier::OnItemDropImpl,
            ListAttributeModifier::OnScrollFrameBeginImpl,
            ListAttributeModifier::OnWillScrollImpl,
            ListAttributeModifier::OnDidScrollImpl,
            ListAttributeModifier::LanesImpl,
            ListAttributeModifier::CachedCount1Impl,
        };
        return &ArkUIListModifierImpl;
    }

    const GENERATED_ArkUIListItemModifier* GetListItemModifier()
    {
        static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
            ListItemModifier::ConstructImpl,
            ListItemInterfaceModifier::SetListItemOptionsImpl,
            ListItemAttributeModifier::SelectableImpl,
            ListItemAttributeModifier::SelectedImpl,
            ListItemAttributeModifier::SwipeActionImpl,
            ListItemAttributeModifier::OnSelectImpl,
            ListItemAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUIListItemModifierImpl;
    }

    const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier()
    {
        static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
            ListItemGroupModifier::ConstructImpl,
            ListItemGroupInterfaceModifier::SetListItemGroupOptionsImpl,
            ListItemGroupAttributeModifier::DividerImpl,
            ListItemGroupAttributeModifier::ChildrenMainSizeImpl,
        };
        return &ArkUIListItemGroupModifierImpl;
    }

    const GENERATED_ArkUILoadingProgressModifier* GetLoadingProgressModifier()
    {
        static const GENERATED_ArkUILoadingProgressModifier ArkUILoadingProgressModifierImpl {
            LoadingProgressModifier::ConstructImpl,
            LoadingProgressInterfaceModifier::SetLoadingProgressOptionsImpl,
            LoadingProgressAttributeModifier::ColorImpl,
            LoadingProgressAttributeModifier::EnableLoadingImpl,
            LoadingProgressAttributeModifier::ContentModifierImpl,
        };
        return &ArkUILoadingProgressModifierImpl;
    }

    const GENERATED_ArkUIMarqueeModifier* GetMarqueeModifier()
    {
        static const GENERATED_ArkUIMarqueeModifier ArkUIMarqueeModifierImpl {
            MarqueeModifier::ConstructImpl,
            MarqueeInterfaceModifier::SetMarqueeOptionsImpl,
            MarqueeAttributeModifier::FontColorImpl,
            MarqueeAttributeModifier::FontSizeImpl,
            MarqueeAttributeModifier::AllowScaleImpl,
            MarqueeAttributeModifier::FontWeightImpl,
            MarqueeAttributeModifier::FontFamilyImpl,
            MarqueeAttributeModifier::MarqueeUpdateStrategyImpl,
            MarqueeAttributeModifier::OnStartImpl,
            MarqueeAttributeModifier::OnBounceImpl,
            MarqueeAttributeModifier::OnFinishImpl,
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
            MenuAttributeModifier::FontImpl,
            MenuAttributeModifier::FontColorImpl,
            MenuAttributeModifier::RadiusImpl,
            MenuAttributeModifier::MenuItemDividerImpl,
            MenuAttributeModifier::MenuItemGroupDividerImpl,
            MenuAttributeModifier::SubMenuExpandingModeImpl,
        };
        return &ArkUIMenuModifierImpl;
    }

    const GENERATED_ArkUIMenuItemModifier* GetMenuItemModifier()
    {
        static const GENERATED_ArkUIMenuItemModifier ArkUIMenuItemModifierImpl {
            MenuItemModifier::ConstructImpl,
            MenuItemInterfaceModifier::SetMenuItemOptionsImpl,
            MenuItemAttributeModifier::SelectedImpl,
            MenuItemAttributeModifier::SelectIconImpl,
            MenuItemAttributeModifier::OnChangeImpl,
            MenuItemAttributeModifier::ContentFontImpl,
            MenuItemAttributeModifier::ContentFontColorImpl,
            MenuItemAttributeModifier::LabelFontImpl,
            MenuItemAttributeModifier::LabelFontColorImpl,
            MenuItemAttributeModifier::_onChangeEvent_selectedImpl,
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
            NavDestinationAttributeModifier::HideTitleBar0Impl,
            NavDestinationAttributeModifier::HideBackButtonImpl,
            NavDestinationAttributeModifier::OnShownImpl,
            NavDestinationAttributeModifier::OnHiddenImpl,
            NavDestinationAttributeModifier::OnBackPressedImpl,
            NavDestinationAttributeModifier::OnResultImpl,
            NavDestinationAttributeModifier::ModeImpl,
            NavDestinationAttributeModifier::BackButtonIcon0Impl,
            NavDestinationAttributeModifier::Menus0Impl,
            NavDestinationAttributeModifier::OnReadyImpl,
            NavDestinationAttributeModifier::OnWillAppearImpl,
            NavDestinationAttributeModifier::OnWillDisappearImpl,
            NavDestinationAttributeModifier::OnWillShowImpl,
            NavDestinationAttributeModifier::OnWillHideImpl,
            NavDestinationAttributeModifier::SystemBarStyleImpl,
            NavDestinationAttributeModifier::RecoverableImpl,
            NavDestinationAttributeModifier::SystemTransitionImpl,
            NavDestinationAttributeModifier::BindToScrollableImpl,
            NavDestinationAttributeModifier::BindToNestedScrollableImpl,
            NavDestinationAttributeModifier::OnActiveImpl,
            NavDestinationAttributeModifier::OnInactiveImpl,
            NavDestinationAttributeModifier::CustomTransitionImpl,
            NavDestinationAttributeModifier::OnNewParamImpl,
            NavDestinationAttributeModifier::PreferredOrientationImpl,
            NavDestinationAttributeModifier::EnableNavigationIndicatorImpl,
            NavDestinationAttributeModifier::TitleImpl,
            NavDestinationAttributeModifier::HideTitleBar1Impl,
            NavDestinationAttributeModifier::BackButtonIcon1Impl,
            NavDestinationAttributeModifier::Menus1Impl,
            NavDestinationAttributeModifier::ToolbarConfigurationImpl,
            NavDestinationAttributeModifier::HideToolBarImpl,
            NavDestinationAttributeModifier::IgnoreLayoutSafeAreaImpl,
            NavDestinationAttributeModifier::EnableStatusBarImpl,
        };
        return &ArkUINavDestinationModifierImpl;
    }

    const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
    {
        static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
            NavigationModifier::ConstructImpl,
            NavigationInterfaceModifier::SetNavigationOptions0Impl,
            NavigationInterfaceModifier::SetNavigationOptions1Impl,
            NavigationAttributeModifier::NavBarWidthImpl,
            NavigationAttributeModifier::NavBarPositionImpl,
            NavigationAttributeModifier::NavBarWidthRangeImpl,
            NavigationAttributeModifier::MinContentWidthImpl,
            NavigationAttributeModifier::ModeImpl,
            NavigationAttributeModifier::BackButtonIcon0Impl,
            NavigationAttributeModifier::HideNavBarImpl,
            NavigationAttributeModifier::HideTitleBar0Impl,
            NavigationAttributeModifier::HideBackButtonImpl,
            NavigationAttributeModifier::TitleModeImpl,
            NavigationAttributeModifier::Menus0Impl,
            NavigationAttributeModifier::HideToolBar0Impl,
            NavigationAttributeModifier::EnableToolBarAdaptationImpl,
            NavigationAttributeModifier::OnTitleModeChangeImpl,
            NavigationAttributeModifier::OnNavBarStateChangeImpl,
            NavigationAttributeModifier::OnNavigationModeChangeImpl,
            NavigationAttributeModifier::NavDestinationImpl,
            NavigationAttributeModifier::CustomNavContentTransitionImpl,
            NavigationAttributeModifier::SystemBarStyleImpl,
            NavigationAttributeModifier::RecoverableImpl,
            NavigationAttributeModifier::EnableDragBarImpl,
            NavigationAttributeModifier::EnableModeChangeAnimationImpl,
            NavigationAttributeModifier::BackButtonIcon1Impl,
            NavigationAttributeModifier::TitleImpl,
            NavigationAttributeModifier::HideTitleBar1Impl,
            NavigationAttributeModifier::Menus1Impl,
            NavigationAttributeModifier::ToolbarConfigurationImpl,
            NavigationAttributeModifier::HideToolBar1Impl,
            NavigationAttributeModifier::IgnoreLayoutSafeAreaImpl,
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

    const GENERATED_ArkUIPathModifier* GetPathModifier()
    {
        static const GENERATED_ArkUIPathModifier ArkUIPathModifierImpl {
            PathModifier::ConstructImpl,
            PathInterfaceModifier::SetPathOptionsImpl,
        };
        return &ArkUIPathModifierImpl;
    }

    const GENERATED_ArkUIPatternLockModifier* GetPatternLockModifier()
    {
        static const GENERATED_ArkUIPatternLockModifier ArkUIPatternLockModifierImpl {
            PatternLockModifier::ConstructImpl,
            PatternLockInterfaceModifier::SetPatternLockOptionsImpl,
            PatternLockAttributeModifier::SideLengthImpl,
            PatternLockAttributeModifier::CircleRadiusImpl,
            PatternLockAttributeModifier::BackgroundColorImpl,
            PatternLockAttributeModifier::RegularColorImpl,
            PatternLockAttributeModifier::SelectedColorImpl,
            PatternLockAttributeModifier::ActiveColorImpl,
            PatternLockAttributeModifier::PathColorImpl,
            PatternLockAttributeModifier::PathStrokeWidthImpl,
            PatternLockAttributeModifier::OnPatternCompleteImpl,
            PatternLockAttributeModifier::AutoResetImpl,
            PatternLockAttributeModifier::OnDotConnectImpl,
            PatternLockAttributeModifier::ActivateCircleStyleImpl,
            PatternLockAttributeModifier::SkipUnselectedPointImpl,
        };
        return &ArkUIPatternLockModifierImpl;
    }

    const GENERATED_ArkUIPluginComponentModifier* GetPluginComponentModifier()
    {
        static const GENERATED_ArkUIPluginComponentModifier ArkUIPluginComponentModifierImpl {
            PluginComponentModifier::ConstructImpl,
            PluginComponentInterfaceModifier::SetPluginComponentOptionsImpl,
            PluginComponentAttributeModifier::OnCompleteImpl,
            PluginComponentAttributeModifier::OnErrorImpl,
        };
        return &ArkUIPluginComponentModifierImpl;
    }

    const GENERATED_ArkUIPolygonModifier* GetPolygonModifier()
    {
        static const GENERATED_ArkUIPolygonModifier ArkUIPolygonModifierImpl {
            PolygonModifier::ConstructImpl,
            PolygonInterfaceModifier::SetPolygonOptionsImpl,
            PolygonAttributeModifier::PointsImpl,
        };
        return &ArkUIPolygonModifierImpl;
    }

    const GENERATED_ArkUIPolylineModifier* GetPolylineModifier()
    {
        static const GENERATED_ArkUIPolylineModifier ArkUIPolylineModifierImpl {
            PolylineModifier::ConstructImpl,
            PolylineInterfaceModifier::SetPolylineOptionsImpl,
            PolylineAttributeModifier::PointsImpl,
        };
        return &ArkUIPolylineModifierImpl;
    }

    const GENERATED_ArkUIProgressModifier* GetProgressModifier()
    {
        static const GENERATED_ArkUIProgressModifier ArkUIProgressModifierImpl {
            ProgressModifier::ConstructImpl,
            ProgressInterfaceModifier::SetProgressOptionsImpl,
            ProgressAttributeModifier::ValueImpl,
            ProgressAttributeModifier::ColorImpl,
            ProgressAttributeModifier::StyleImpl,
            ProgressAttributeModifier::PrivacySensitiveImpl,
            ProgressAttributeModifier::ContentModifierImpl,
        };
        return &ArkUIProgressModifierImpl;
    }

    const GENERATED_ArkUIQRCodeModifier* GetQRCodeModifier()
    {
        static const GENERATED_ArkUIQRCodeModifier ArkUIQRCodeModifierImpl {
            QRCodeModifier::ConstructImpl,
            QRCodeInterfaceModifier::SetQRCodeOptionsImpl,
            QRCodeAttributeModifier::ColorImpl,
            QRCodeAttributeModifier::BackgroundColorImpl,
            QRCodeAttributeModifier::ContentOpacityImpl,
        };
        return &ArkUIQRCodeModifierImpl;
    }

    const GENERATED_ArkUIRadioModifier* GetRadioModifier()
    {
        static const GENERATED_ArkUIRadioModifier ArkUIRadioModifierImpl {
            RadioModifier::ConstructImpl,
            RadioInterfaceModifier::SetRadioOptionsImpl,
            RadioAttributeModifier::CheckedImpl,
            RadioAttributeModifier::OnChangeImpl,
            RadioAttributeModifier::RadioStyleImpl,
            RadioAttributeModifier::ContentModifierImpl,
            RadioAttributeModifier::_onChangeEvent_checkedImpl,
        };
        return &ArkUIRadioModifierImpl;
    }

    const GENERATED_ArkUIRatingModifier* GetRatingModifier()
    {
        static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
            RatingModifier::ConstructImpl,
            RatingInterfaceModifier::SetRatingOptionsImpl,
            RatingAttributeModifier::StarsImpl,
            RatingAttributeModifier::StepSizeImpl,
            RatingAttributeModifier::StarStyleImpl,
            RatingAttributeModifier::OnChangeImpl,
            RatingAttributeModifier::ContentModifierImpl,
            RatingAttributeModifier::_onChangeEvent_ratingImpl,
        };
        return &ArkUIRatingModifierImpl;
    }

    const GENERATED_ArkUIRectModifier* GetRectModifier()
    {
        static const GENERATED_ArkUIRectModifier ArkUIRectModifierImpl {
            RectModifier::ConstructImpl,
            RectInterfaceModifier::SetRectOptionsImpl,
            RectAttributeModifier::RadiusImpl,
        };
        return &ArkUIRectModifierImpl;
    }

    const GENERATED_ArkUIRefreshModifier* GetRefreshModifier()
    {
        static const GENERATED_ArkUIRefreshModifier ArkUIRefreshModifierImpl {
            RefreshModifier::ConstructImpl,
            RefreshInterfaceModifier::SetRefreshOptionsImpl,
            RefreshAttributeModifier::OnStateChangeImpl,
            RefreshAttributeModifier::OnRefreshingImpl,
            RefreshAttributeModifier::RefreshOffsetImpl,
            RefreshAttributeModifier::PullToRefreshImpl,
            RefreshAttributeModifier::OnOffsetChangeImpl,
            RefreshAttributeModifier::PullDownRatioImpl,
            RefreshAttributeModifier::_onChangeEvent_refreshingImpl,
        };
        return &ArkUIRefreshModifierImpl;
    }

    const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier()
    {
        static const GENERATED_ArkUIRelativeContainerModifier ArkUIRelativeContainerModifierImpl {
            RelativeContainerModifier::ConstructImpl,
            RelativeContainerInterfaceModifier::SetRelativeContainerOptionsImpl,
            RelativeContainerAttributeModifier::GuideLineImpl,
            RelativeContainerAttributeModifier::BarrierImpl,
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
            RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
            RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
            RichEditorAttributeModifier::OnReadyImpl,
            RichEditorAttributeModifier::OnSelectImpl,
            RichEditorAttributeModifier::OnSelectionChangeImpl,
            RichEditorAttributeModifier::AboutToIMEInputImpl,
            RichEditorAttributeModifier::OnIMEInputCompleteImpl,
            RichEditorAttributeModifier::OnDidIMEInputImpl,
            RichEditorAttributeModifier::AboutToDeleteImpl,
            RichEditorAttributeModifier::OnDeleteCompleteImpl,
            RichEditorAttributeModifier::CopyOptionsImpl,
            RichEditorAttributeModifier::OnPasteImpl,
            RichEditorAttributeModifier::EnableDataDetectorImpl,
            RichEditorAttributeModifier::EnablePreviewTextImpl,
            RichEditorAttributeModifier::DataDetectorConfigImpl,
            RichEditorAttributeModifier::CaretColorImpl,
            RichEditorAttributeModifier::SelectedBackgroundColorImpl,
            RichEditorAttributeModifier::OnEditingChangeImpl,
            RichEditorAttributeModifier::EnterKeyTypeImpl,
            RichEditorAttributeModifier::OnSubmitImpl,
            RichEditorAttributeModifier::OnWillChangeImpl,
            RichEditorAttributeModifier::OnDidChangeImpl,
            RichEditorAttributeModifier::OnCutImpl,
            RichEditorAttributeModifier::OnCopyImpl,
            RichEditorAttributeModifier::EditMenuOptionsImpl,
            RichEditorAttributeModifier::EnableKeyboardOnFocusImpl,
            RichEditorAttributeModifier::EnableHapticFeedbackImpl,
            RichEditorAttributeModifier::BarStateImpl,
            RichEditorAttributeModifier::MaxLengthImpl,
            RichEditorAttributeModifier::MaxLinesImpl,
            RichEditorAttributeModifier::KeyboardAppearanceImpl,
            RichEditorAttributeModifier::StopBackPressImpl,
            RichEditorAttributeModifier::BindSelectionMenuImpl,
            RichEditorAttributeModifier::CustomKeyboardImpl,
            RichEditorAttributeModifier::PlaceholderImpl,
        };
        return &ArkUIRichEditorModifierImpl;
    }

    const GENERATED_ArkUIRichTextModifier* GetRichTextModifier()
    {
        static const GENERATED_ArkUIRichTextModifier ArkUIRichTextModifierImpl {
            RichTextModifier::ConstructImpl,
            RichTextInterfaceModifier::SetRichTextOptionsImpl,
            RichTextAttributeModifier::OnStartImpl,
            RichTextAttributeModifier::OnCompleteImpl,
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
            RowAttributeModifier::AlignItemsImpl,
            RowAttributeModifier::JustifyContentImpl,
            RowAttributeModifier::PointLightImpl,
            RowAttributeModifier::ReverseImpl,
        };
        return &ArkUIRowModifierImpl;
    }

    const GENERATED_ArkUIRowSplitModifier* GetRowSplitModifier()
    {
        static const GENERATED_ArkUIRowSplitModifier ArkUIRowSplitModifierImpl {
            RowSplitModifier::ConstructImpl,
            RowSplitInterfaceModifier::SetRowSplitOptionsImpl,
            RowSplitAttributeModifier::ResizeableImpl,
        };
        return &ArkUIRowSplitModifierImpl;
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
            ScrollAttributeModifier::ScrollableImpl,
            ScrollAttributeModifier::OnWillScrollImpl,
            ScrollAttributeModifier::OnDidScrollImpl,
            ScrollAttributeModifier::OnScrollEdgeImpl,
            ScrollAttributeModifier::OnScrollStartImpl,
            ScrollAttributeModifier::OnScrollStopImpl,
            ScrollAttributeModifier::ScrollBarImpl,
            ScrollAttributeModifier::ScrollBarColorImpl,
            ScrollAttributeModifier::ScrollBarWidthImpl,
            ScrollAttributeModifier::OnScrollFrameBeginImpl,
            ScrollAttributeModifier::NestedScrollImpl,
            ScrollAttributeModifier::EnableScrollInteractionImpl,
            ScrollAttributeModifier::FrictionImpl,
            ScrollAttributeModifier::ScrollSnapImpl,
            ScrollAttributeModifier::EnablePagingImpl,
            ScrollAttributeModifier::InitialOffsetImpl,
            ScrollAttributeModifier::EdgeEffectImpl,
        };
        return &ArkUIScrollModifierImpl;
    }

    const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
    {
        static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
            ScrollableCommonMethodModifier::ConstructImpl,
            ScrollableCommonMethodModifier::ScrollBarImpl,
            ScrollableCommonMethodModifier::ScrollBarColorImpl,
            ScrollableCommonMethodModifier::ScrollBarWidthImpl,
            ScrollableCommonMethodModifier::NestedScrollImpl,
            ScrollableCommonMethodModifier::EnableScrollInteractionImpl,
            ScrollableCommonMethodModifier::FrictionImpl,
            ScrollableCommonMethodModifier::OnReachStartImpl,
            ScrollableCommonMethodModifier::OnReachEndImpl,
            ScrollableCommonMethodModifier::OnScrollStartImpl,
            ScrollableCommonMethodModifier::OnScrollStopImpl,
            ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
            ScrollableCommonMethodModifier::ClipContentImpl,
            ScrollableCommonMethodModifier::DigitalCrownSensitivityImpl,
            ScrollableCommonMethodModifier::BackToTopImpl,
            ScrollableCommonMethodModifier::EdgeEffectImpl,
            ScrollableCommonMethodModifier::FadingEdgeImpl,
        };
        return &ArkUIScrollableCommonMethodModifierImpl;
    }

    const GENERATED_ArkUIScrollBarModifier* GetScrollBarModifier()
    {
        static const GENERATED_ArkUIScrollBarModifier ArkUIScrollBarModifierImpl {
            ScrollBarModifier::ConstructImpl,
            ScrollBarInterfaceModifier::SetScrollBarOptionsImpl,
            ScrollBarAttributeModifier::EnableNestedScrollImpl,
        };
        return &ArkUIScrollBarModifierImpl;
    }

    const GENERATED_ArkUISearchModifier* GetSearchModifier()
    {
        static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
            SearchModifier::ConstructImpl,
            SearchInterfaceModifier::SetSearchOptionsImpl,
            SearchAttributeModifier::FontColorImpl,
            SearchAttributeModifier::SearchIconImpl,
            SearchAttributeModifier::CancelButtonImpl,
            SearchAttributeModifier::TextIndentImpl,
            SearchAttributeModifier::OnEditChangeImpl,
            SearchAttributeModifier::SelectedBackgroundColorImpl,
            SearchAttributeModifier::CaretStyleImpl,
            SearchAttributeModifier::PlaceholderColorImpl,
            SearchAttributeModifier::PlaceholderFontImpl,
            SearchAttributeModifier::TextFontImpl,
            SearchAttributeModifier::EnterKeyTypeImpl,
            SearchAttributeModifier::OnSubmitImpl,
            SearchAttributeModifier::OnChangeImpl,
            SearchAttributeModifier::OnTextSelectionChangeImpl,
            SearchAttributeModifier::OnContentScrollImpl,
            SearchAttributeModifier::OnCopyImpl,
            SearchAttributeModifier::OnCutImpl,
            SearchAttributeModifier::OnPasteImpl,
            SearchAttributeModifier::CopyOptionImpl,
            SearchAttributeModifier::MaxLengthImpl,
            SearchAttributeModifier::TextAlignImpl,
            SearchAttributeModifier::EnableKeyboardOnFocusImpl,
            SearchAttributeModifier::SelectionMenuHiddenImpl,
            SearchAttributeModifier::MinFontSizeImpl,
            SearchAttributeModifier::MaxFontSizeImpl,
            SearchAttributeModifier::MinFontScaleImpl,
            SearchAttributeModifier::MaxFontScaleImpl,
            SearchAttributeModifier::DecorationImpl,
            SearchAttributeModifier::LetterSpacingImpl,
            SearchAttributeModifier::LineHeightImpl,
            SearchAttributeModifier::TypeImpl,
            SearchAttributeModifier::FontFeatureImpl,
            SearchAttributeModifier::OnWillInsertImpl,
            SearchAttributeModifier::OnDidInsertImpl,
            SearchAttributeModifier::OnWillDeleteImpl,
            SearchAttributeModifier::OnDidDeleteImpl,
            SearchAttributeModifier::EditMenuOptionsImpl,
            SearchAttributeModifier::EnablePreviewTextImpl,
            SearchAttributeModifier::EnableHapticFeedbackImpl,
            SearchAttributeModifier::AutoCapitalizationModeImpl,
            SearchAttributeModifier::HalfLeadingImpl,
            SearchAttributeModifier::StopBackPressImpl,
            SearchAttributeModifier::OnWillChangeImpl,
            SearchAttributeModifier::KeyboardAppearanceImpl,
            SearchAttributeModifier::SearchButtonImpl,
            SearchAttributeModifier::InputFilterImpl,
            SearchAttributeModifier::CustomKeyboardImpl,
            SearchAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUISearchModifierImpl;
    }

    const GENERATED_ArkUISelectModifier* GetSelectModifier()
    {
        static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
            SelectModifier::ConstructImpl,
            SelectInterfaceModifier::SetSelectOptionsImpl,
            SelectAttributeModifier::SelectedImpl,
            SelectAttributeModifier::ValueImpl,
            SelectAttributeModifier::FontImpl,
            SelectAttributeModifier::FontColorImpl,
            SelectAttributeModifier::SelectedOptionBgColorImpl,
            SelectAttributeModifier::SelectedOptionFontImpl,
            SelectAttributeModifier::SelectedOptionFontColorImpl,
            SelectAttributeModifier::OptionBgColorImpl,
            SelectAttributeModifier::OptionFontImpl,
            SelectAttributeModifier::OptionFontColorImpl,
            SelectAttributeModifier::OnSelectImpl,
            SelectAttributeModifier::SpaceImpl,
            SelectAttributeModifier::ArrowPositionImpl,
            SelectAttributeModifier::OptionWidthImpl,
            SelectAttributeModifier::OptionHeightImpl,
            SelectAttributeModifier::MenuBackgroundColorImpl,
            SelectAttributeModifier::MenuBackgroundBlurStyleImpl,
            SelectAttributeModifier::ControlSizeImpl,
            SelectAttributeModifier::MenuItemContentModifierImpl,
            SelectAttributeModifier::DividerImpl,
            SelectAttributeModifier::TextModifierImpl,
            SelectAttributeModifier::ArrowModifierImpl,
            SelectAttributeModifier::OptionTextModifierImpl,
            SelectAttributeModifier::SelectedOptionTextModifierImpl,
            SelectAttributeModifier::DividerStyleImpl,
            SelectAttributeModifier::AvoidanceImpl,
            SelectAttributeModifier::MenuOutlineImpl,
            SelectAttributeModifier::MenuAlignImpl,
            SelectAttributeModifier::_onChangeEvent_selectedImpl,
            SelectAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUISelectModifierImpl;
    }

    const GENERATED_ArkUIShapeModifier* GetShapeModifier()
    {
        static const GENERATED_ArkUIShapeModifier ArkUIShapeModifierImpl {
            ShapeModifier::ConstructImpl,
            ShapeInterfaceModifier::SetShapeOptionsImpl,
            ShapeAttributeModifier::ViewPortImpl,
            ShapeAttributeModifier::StrokeImpl,
            ShapeAttributeModifier::FillImpl,
            ShapeAttributeModifier::StrokeDashOffsetImpl,
            ShapeAttributeModifier::StrokeDashArrayImpl,
            ShapeAttributeModifier::StrokeLineCapImpl,
            ShapeAttributeModifier::StrokeLineJoinImpl,
            ShapeAttributeModifier::StrokeMiterLimitImpl,
            ShapeAttributeModifier::StrokeOpacityImpl,
            ShapeAttributeModifier::FillOpacityImpl,
            ShapeAttributeModifier::StrokeWidthImpl,
            ShapeAttributeModifier::AntiAliasImpl,
            ShapeAttributeModifier::MeshImpl,
        };
        return &ArkUIShapeModifierImpl;
    }

    const GENERATED_ArkUISideBarContainerModifier* GetSideBarContainerModifier()
    {
        static const GENERATED_ArkUISideBarContainerModifier ArkUISideBarContainerModifierImpl {
            SideBarContainerModifier::ConstructImpl,
            SideBarContainerInterfaceModifier::SetSideBarContainerOptionsImpl,
            SideBarContainerAttributeModifier::ShowSideBarImpl,
            SideBarContainerAttributeModifier::ControlButtonImpl,
            SideBarContainerAttributeModifier::ShowControlButtonImpl,
            SideBarContainerAttributeModifier::OnChangeImpl,
            SideBarContainerAttributeModifier::SideBarWidth0Impl,
            SideBarContainerAttributeModifier::MinSideBarWidth0Impl,
            SideBarContainerAttributeModifier::MaxSideBarWidth0Impl,
            SideBarContainerAttributeModifier::SideBarWidth1Impl,
            SideBarContainerAttributeModifier::MinSideBarWidth1Impl,
            SideBarContainerAttributeModifier::MaxSideBarWidth1Impl,
            SideBarContainerAttributeModifier::AutoHideImpl,
            SideBarContainerAttributeModifier::SideBarPositionImpl,
            SideBarContainerAttributeModifier::DividerImpl,
            SideBarContainerAttributeModifier::MinContentWidthImpl,
            SideBarContainerAttributeModifier::_onChangeEvent_showSideBarImpl,
        };
        return &ArkUISideBarContainerModifierImpl;
    }

    const GENERATED_ArkUISliderModifier* GetSliderModifier()
    {
        static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
            SliderModifier::ConstructImpl,
            SliderInterfaceModifier::SetSliderOptionsImpl,
            SliderAttributeModifier::BlockColorImpl,
            SliderAttributeModifier::TrackColorImpl,
            SliderAttributeModifier::SelectedColorImpl,
            SliderAttributeModifier::ShowStepsImpl,
            SliderAttributeModifier::TrackThicknessImpl,
            SliderAttributeModifier::OnChangeImpl,
            SliderAttributeModifier::BlockBorderColorImpl,
            SliderAttributeModifier::BlockBorderWidthImpl,
            SliderAttributeModifier::StepColorImpl,
            SliderAttributeModifier::TrackBorderRadiusImpl,
            SliderAttributeModifier::SelectedBorderRadiusImpl,
            SliderAttributeModifier::BlockSizeImpl,
            SliderAttributeModifier::BlockStyleImpl,
            SliderAttributeModifier::StepSizeImpl,
            SliderAttributeModifier::SliderInteractionModeImpl,
            SliderAttributeModifier::MinResponsiveDistanceImpl,
            SliderAttributeModifier::ContentModifierImpl,
            SliderAttributeModifier::SlideRangeImpl,
            SliderAttributeModifier::DigitalCrownSensitivityImpl,
            SliderAttributeModifier::EnableHapticFeedbackImpl,
            SliderAttributeModifier::ShowTipsImpl,
            SliderAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUISliderModifierImpl;
    }

    const GENERATED_ArkUISpanModifier* GetSpanModifier()
    {
        static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
            SpanModifier::ConstructImpl,
            SpanInterfaceModifier::SetSpanOptionsImpl,
            SpanAttributeModifier::FontImpl,
            SpanAttributeModifier::FontColorImpl,
            SpanAttributeModifier::FontSizeImpl,
            SpanAttributeModifier::FontStyleImpl,
            SpanAttributeModifier::FontFamilyImpl,
            SpanAttributeModifier::DecorationImpl,
            SpanAttributeModifier::TextCaseImpl,
            SpanAttributeModifier::LineHeightImpl,
            SpanAttributeModifier::TextShadowImpl,
        };
        return &ArkUISpanModifierImpl;
    }

    const GENERATED_ArkUIStackModifier* GetStackModifier()
    {
        static const GENERATED_ArkUIStackModifier ArkUIStackModifierImpl {
            StackModifier::ConstructImpl,
            StackInterfaceModifier::SetStackOptionsImpl,
            StackAttributeModifier::AlignContentImpl,
            StackAttributeModifier::PointLightImpl,
        };
        return &ArkUIStackModifierImpl;
    }

    const GENERATED_ArkUIStepperModifier* GetStepperModifier()
    {
        static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
            StepperModifier::ConstructImpl,
            StepperInterfaceModifier::SetStepperOptionsImpl,
            StepperAttributeModifier::OnFinishImpl,
            StepperAttributeModifier::OnSkipImpl,
            StepperAttributeModifier::OnChangeImpl,
            StepperAttributeModifier::OnNextImpl,
            StepperAttributeModifier::OnPreviousImpl,
            StepperAttributeModifier::_onChangeEvent_indexImpl,
        };
        return &ArkUIStepperModifierImpl;
    }

    const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier()
    {
        static const GENERATED_ArkUIStepperItemModifier ArkUIStepperItemModifierImpl {
            StepperItemModifier::ConstructImpl,
            StepperItemInterfaceModifier::SetStepperItemOptionsImpl,
            StepperItemAttributeModifier::PrevLabelImpl,
            StepperItemAttributeModifier::NextLabelImpl,
            StepperItemAttributeModifier::StatusImpl,
        };
        return &ArkUIStepperItemModifierImpl;
    }

    const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
    {
        static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
            SwiperModifier::ConstructImpl,
            SwiperInterfaceModifier::SetSwiperOptionsImpl,
            SwiperAttributeModifier::IndexImpl,
            SwiperAttributeModifier::IntervalImpl,
            SwiperAttributeModifier::IndicatorImpl,
            SwiperAttributeModifier::LoopImpl,
            SwiperAttributeModifier::DurationImpl,
            SwiperAttributeModifier::VerticalImpl,
            SwiperAttributeModifier::ItemSpaceImpl,
            SwiperAttributeModifier::DisplayModeImpl,
            SwiperAttributeModifier::CachedCount0Impl,
            SwiperAttributeModifier::EffectModeImpl,
            SwiperAttributeModifier::DisableSwipeImpl,
            SwiperAttributeModifier::CurveImpl,
            SwiperAttributeModifier::OnChangeImpl,
            SwiperAttributeModifier::OnSelectedImpl,
            SwiperAttributeModifier::OnUnselectedImpl,
            SwiperAttributeModifier::OnAnimationStartImpl,
            SwiperAttributeModifier::OnAnimationEndImpl,
            SwiperAttributeModifier::OnGestureSwipeImpl,
            SwiperAttributeModifier::NestedScrollImpl,
            SwiperAttributeModifier::CustomContentTransitionImpl,
            SwiperAttributeModifier::OnContentDidScrollImpl,
            SwiperAttributeModifier::IndicatorInteractiveImpl,
            SwiperAttributeModifier::PageFlipModeImpl,
            SwiperAttributeModifier::OnContentWillScrollImpl,
            SwiperAttributeModifier::AutoPlayImpl,
            SwiperAttributeModifier::DisplayArrowImpl,
            SwiperAttributeModifier::CachedCount1Impl,
            SwiperAttributeModifier::DisplayCountImpl,
            SwiperAttributeModifier::PrevMarginImpl,
            SwiperAttributeModifier::NextMarginImpl,
            SwiperAttributeModifier::_onChangeEvent_indexImpl,
        };
        return &ArkUISwiperModifierImpl;
    }

    const GENERATED_ArkUISymbolGlyphModifier* GetSymbolGlyphModifier()
    {
        static const GENERATED_ArkUISymbolGlyphModifier ArkUISymbolGlyphModifierImpl {
            SymbolGlyphModifier::ConstructImpl,
            SymbolGlyphInterfaceModifier::SetSymbolGlyphOptionsImpl,
            SymbolGlyphAttributeModifier::FontSizeImpl,
            SymbolGlyphAttributeModifier::FontColorImpl,
            SymbolGlyphAttributeModifier::FontWeightImpl,
            SymbolGlyphAttributeModifier::EffectStrategyImpl,
            SymbolGlyphAttributeModifier::RenderingStrategyImpl,
            SymbolGlyphAttributeModifier::MinFontScaleImpl,
            SymbolGlyphAttributeModifier::MaxFontScaleImpl,
            SymbolGlyphAttributeModifier::SymbolEffectImpl,
        };
        return &ArkUISymbolGlyphModifierImpl;
    }

    const GENERATED_ArkUISymbolSpanModifier* GetSymbolSpanModifier()
    {
        static const GENERATED_ArkUISymbolSpanModifier ArkUISymbolSpanModifierImpl {
            SymbolSpanModifier::ConstructImpl,
            SymbolSpanInterfaceModifier::SetSymbolSpanOptionsImpl,
            SymbolSpanAttributeModifier::FontSizeImpl,
            SymbolSpanAttributeModifier::FontColorImpl,
            SymbolSpanAttributeModifier::FontWeightImpl,
            SymbolSpanAttributeModifier::EffectStrategyImpl,
            SymbolSpanAttributeModifier::RenderingStrategyImpl,
        };
        return &ArkUISymbolSpanModifierImpl;
    }

    const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
    {
        static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
            TabContentModifier::ConstructImpl,
            TabContentInterfaceModifier::SetTabContentOptionsImpl,
            TabContentAttributeModifier::TabBarImpl,
            TabContentAttributeModifier::OnWillShowImpl,
            TabContentAttributeModifier::OnWillHideImpl,
        };
        return &ArkUITabContentModifierImpl;
    }

    const GENERATED_ArkUITabsModifier* GetTabsModifier()
    {
        static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
            TabsModifier::ConstructImpl,
            TabsInterfaceModifier::SetTabsOptionsImpl,
            TabsAttributeModifier::VerticalImpl,
            TabsAttributeModifier::BarPositionImpl,
            TabsAttributeModifier::ScrollableImpl,
            TabsAttributeModifier::BarWidthImpl,
            TabsAttributeModifier::BarHeightImpl,
            TabsAttributeModifier::AnimationDurationImpl,
            TabsAttributeModifier::AnimationModeImpl,
            TabsAttributeModifier::EdgeEffectImpl,
            TabsAttributeModifier::OnChangeImpl,
            TabsAttributeModifier::OnSelectedImpl,
            TabsAttributeModifier::OnTabBarClickImpl,
            TabsAttributeModifier::OnUnselectedImpl,
            TabsAttributeModifier::OnAnimationStartImpl,
            TabsAttributeModifier::OnAnimationEndImpl,
            TabsAttributeModifier::OnGestureSwipeImpl,
            TabsAttributeModifier::FadingEdgeImpl,
            TabsAttributeModifier::DividerImpl,
            TabsAttributeModifier::BarOverlapImpl,
            TabsAttributeModifier::BarBackgroundColorImpl,
            TabsAttributeModifier::BarGridAlignImpl,
            TabsAttributeModifier::CustomContentTransitionImpl,
            TabsAttributeModifier::BarBackgroundBlurStyle0Impl,
            TabsAttributeModifier::PageFlipModeImpl,
            TabsAttributeModifier::BarBackgroundEffectImpl,
            TabsAttributeModifier::OnContentWillChangeImpl,
            TabsAttributeModifier::BarModeImpl,
            TabsAttributeModifier::BarBackgroundBlurStyle1Impl,
            TabsAttributeModifier::CachedMaxCountImpl,
            TabsAttributeModifier::_onChangeEvent_indexImpl,
        };
        return &ArkUITabsModifierImpl;
    }

    const GENERATED_ArkUITextModifier* GetTextModifier()
    {
        static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
            TextModifier::ConstructImpl,
            TextInterfaceModifier::SetTextOptionsImpl,
            TextAttributeModifier::FontColorImpl,
            TextAttributeModifier::FontSizeImpl,
            TextAttributeModifier::MinFontSizeImpl,
            TextAttributeModifier::MaxFontSizeImpl,
            TextAttributeModifier::MinFontScaleImpl,
            TextAttributeModifier::MaxFontScaleImpl,
            TextAttributeModifier::FontStyleImpl,
            TextAttributeModifier::LineSpacingImpl,
            TextAttributeModifier::TextAlignImpl,
            TextAttributeModifier::LineHeightImpl,
            TextAttributeModifier::TextOverflowImpl,
            TextAttributeModifier::FontFamilyImpl,
            TextAttributeModifier::MaxLinesImpl,
            TextAttributeModifier::DecorationImpl,
            TextAttributeModifier::LetterSpacingImpl,
            TextAttributeModifier::TextCaseImpl,
            TextAttributeModifier::BaselineOffsetImpl,
            TextAttributeModifier::CopyOptionImpl,
            TextAttributeModifier::DraggableImpl,
            TextAttributeModifier::TextShadowImpl,
            TextAttributeModifier::HeightAdaptivePolicyImpl,
            TextAttributeModifier::TextIndentImpl,
            TextAttributeModifier::WordBreakImpl,
            TextAttributeModifier::LineBreakStrategyImpl,
            TextAttributeModifier::OnCopyImpl,
            TextAttributeModifier::CaretColorImpl,
            TextAttributeModifier::SelectedBackgroundColorImpl,
            TextAttributeModifier::EllipsisModeImpl,
            TextAttributeModifier::EnableDataDetectorImpl,
            TextAttributeModifier::DataDetectorConfigImpl,
            TextAttributeModifier::OnTextSelectionChangeImpl,
            TextAttributeModifier::FontFeatureImpl,
            TextAttributeModifier::MarqueeOptionsImpl,
            TextAttributeModifier::OnMarqueeStateChangeImpl,
            TextAttributeModifier::PrivacySensitiveImpl,
            TextAttributeModifier::TextSelectableImpl,
            TextAttributeModifier::EditMenuOptionsImpl,
            TextAttributeModifier::HalfLeadingImpl,
            TextAttributeModifier::EnableHapticFeedbackImpl,
            TextAttributeModifier::FontImpl,
            TextAttributeModifier::FontWeightImpl,
            TextAttributeModifier::SelectionImpl,
            TextAttributeModifier::BindSelectionMenuImpl,
        };
        return &ArkUITextModifierImpl;
    }

    const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
    {
        static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
            TextAreaModifier::ConstructImpl,
            TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
            TextAreaAttributeModifier::PlaceholderColorImpl,
            TextAreaAttributeModifier::PlaceholderFontImpl,
            TextAreaAttributeModifier::EnterKeyTypeImpl,
            TextAreaAttributeModifier::TextAlignImpl,
            TextAreaAttributeModifier::CaretColorImpl,
            TextAreaAttributeModifier::FontColorImpl,
            TextAreaAttributeModifier::FontSizeImpl,
            TextAreaAttributeModifier::FontStyleImpl,
            TextAreaAttributeModifier::FontWeightImpl,
            TextAreaAttributeModifier::FontFamilyImpl,
            TextAreaAttributeModifier::TextOverflowImpl,
            TextAreaAttributeModifier::TextIndentImpl,
            TextAreaAttributeModifier::CaretStyleImpl,
            TextAreaAttributeModifier::SelectedBackgroundColorImpl,
            TextAreaAttributeModifier::OnSubmitImpl,
            TextAreaAttributeModifier::OnChangeImpl,
            TextAreaAttributeModifier::OnTextSelectionChangeImpl,
            TextAreaAttributeModifier::OnContentScrollImpl,
            TextAreaAttributeModifier::OnEditChangeImpl,
            TextAreaAttributeModifier::OnCopyImpl,
            TextAreaAttributeModifier::OnCutImpl,
            TextAreaAttributeModifier::OnPasteImpl,
            TextAreaAttributeModifier::CopyOptionImpl,
            TextAreaAttributeModifier::EnableKeyboardOnFocusImpl,
            TextAreaAttributeModifier::MaxLengthImpl,
            TextAreaAttributeModifier::StyleImpl,
            TextAreaAttributeModifier::BarStateImpl,
            TextAreaAttributeModifier::SelectionMenuHiddenImpl,
            TextAreaAttributeModifier::MinFontSizeImpl,
            TextAreaAttributeModifier::MaxFontSizeImpl,
            TextAreaAttributeModifier::MinFontScaleImpl,
            TextAreaAttributeModifier::MaxFontScaleImpl,
            TextAreaAttributeModifier::HeightAdaptivePolicyImpl,
            TextAreaAttributeModifier::MaxLinesImpl,
            TextAreaAttributeModifier::WordBreakImpl,
            TextAreaAttributeModifier::LineBreakStrategyImpl,
            TextAreaAttributeModifier::DecorationImpl,
            TextAreaAttributeModifier::LetterSpacingImpl,
            TextAreaAttributeModifier::LineSpacingImpl,
            TextAreaAttributeModifier::LineHeightImpl,
            TextAreaAttributeModifier::TypeImpl,
            TextAreaAttributeModifier::EnableAutoFillImpl,
            TextAreaAttributeModifier::ContentTypeImpl,
            TextAreaAttributeModifier::FontFeatureImpl,
            TextAreaAttributeModifier::OnWillInsertImpl,
            TextAreaAttributeModifier::OnDidInsertImpl,
            TextAreaAttributeModifier::OnWillDeleteImpl,
            TextAreaAttributeModifier::OnDidDeleteImpl,
            TextAreaAttributeModifier::EditMenuOptionsImpl,
            TextAreaAttributeModifier::EnablePreviewTextImpl,
            TextAreaAttributeModifier::EnableHapticFeedbackImpl,
            TextAreaAttributeModifier::AutoCapitalizationModeImpl,
            TextAreaAttributeModifier::HalfLeadingImpl,
            TextAreaAttributeModifier::EllipsisModeImpl,
            TextAreaAttributeModifier::StopBackPressImpl,
            TextAreaAttributeModifier::OnWillChangeImpl,
            TextAreaAttributeModifier::KeyboardAppearanceImpl,
            TextAreaAttributeModifier::InputFilterImpl,
            TextAreaAttributeModifier::ShowCounterImpl,
            TextAreaAttributeModifier::CustomKeyboardImpl,
            TextAreaAttributeModifier::_onChangeEvent_textImpl,
        };
        return &ArkUITextAreaModifierImpl;
    }

    const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
    {
        static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
            TextClockModifier::ConstructImpl,
            TextClockInterfaceModifier::SetTextClockOptionsImpl,
            TextClockAttributeModifier::FormatImpl,
            TextClockAttributeModifier::OnDateChangeImpl,
            TextClockAttributeModifier::FontColorImpl,
            TextClockAttributeModifier::FontSizeImpl,
            TextClockAttributeModifier::FontStyleImpl,
            TextClockAttributeModifier::FontWeightImpl,
            TextClockAttributeModifier::FontFamilyImpl,
            TextClockAttributeModifier::TextShadowImpl,
            TextClockAttributeModifier::FontFeatureImpl,
            TextClockAttributeModifier::ContentModifierImpl,
            TextClockAttributeModifier::DateTimeOptionsImpl,
        };
        return &ArkUITextClockModifierImpl;
    }

    const GENERATED_ArkUITextInputModifier* GetTextInputModifier()
    {
        static const GENERATED_ArkUITextInputModifier ArkUITextInputModifierImpl {
            TextInputModifier::ConstructImpl,
            TextInputInterfaceModifier::SetTextInputOptionsImpl,
            TextInputAttributeModifier::TypeImpl,
            TextInputAttributeModifier::ContentTypeImpl,
            TextInputAttributeModifier::PlaceholderColorImpl,
            TextInputAttributeModifier::TextOverflowImpl,
            TextInputAttributeModifier::TextIndentImpl,
            TextInputAttributeModifier::PlaceholderFontImpl,
            TextInputAttributeModifier::EnterKeyTypeImpl,
            TextInputAttributeModifier::CaretColorImpl,
            TextInputAttributeModifier::OnEditChangeImpl,
            TextInputAttributeModifier::OnSubmitImpl,
            TextInputAttributeModifier::OnChangeImpl,
            TextInputAttributeModifier::OnTextSelectionChangeImpl,
            TextInputAttributeModifier::OnContentScrollImpl,
            TextInputAttributeModifier::MaxLengthImpl,
            TextInputAttributeModifier::FontColorImpl,
            TextInputAttributeModifier::FontSizeImpl,
            TextInputAttributeModifier::FontStyleImpl,
            TextInputAttributeModifier::FontWeightImpl,
            TextInputAttributeModifier::FontFamilyImpl,
            TextInputAttributeModifier::OnCopyImpl,
            TextInputAttributeModifier::OnCutImpl,
            TextInputAttributeModifier::OnPasteImpl,
            TextInputAttributeModifier::CopyOptionImpl,
            TextInputAttributeModifier::ShowPasswordIconImpl,
            TextInputAttributeModifier::TextAlignImpl,
            TextInputAttributeModifier::StyleImpl,
            TextInputAttributeModifier::CaretStyleImpl,
            TextInputAttributeModifier::SelectedBackgroundColorImpl,
            TextInputAttributeModifier::CaretPositionImpl,
            TextInputAttributeModifier::EnableKeyboardOnFocusImpl,
            TextInputAttributeModifier::PasswordIconImpl,
            TextInputAttributeModifier::ShowErrorImpl,
            TextInputAttributeModifier::ShowUnitImpl,
            TextInputAttributeModifier::ShowUnderlineImpl,
            TextInputAttributeModifier::UnderlineColorImpl,
            TextInputAttributeModifier::SelectionMenuHiddenImpl,
            TextInputAttributeModifier::BarStateImpl,
            TextInputAttributeModifier::MaxLinesImpl,
            TextInputAttributeModifier::WordBreakImpl,
            TextInputAttributeModifier::LineBreakStrategyImpl,
            TextInputAttributeModifier::CancelButtonImpl,
            TextInputAttributeModifier::SelectAllImpl,
            TextInputAttributeModifier::MinFontSizeImpl,
            TextInputAttributeModifier::MaxFontSizeImpl,
            TextInputAttributeModifier::MinFontScaleImpl,
            TextInputAttributeModifier::MaxFontScaleImpl,
            TextInputAttributeModifier::HeightAdaptivePolicyImpl,
            TextInputAttributeModifier::EnableAutoFillImpl,
            TextInputAttributeModifier::DecorationImpl,
            TextInputAttributeModifier::LetterSpacingImpl,
            TextInputAttributeModifier::LineHeightImpl,
            TextInputAttributeModifier::PasswordRulesImpl,
            TextInputAttributeModifier::FontFeatureImpl,
            TextInputAttributeModifier::ShowPasswordImpl,
            TextInputAttributeModifier::OnSecurityStateChangeImpl,
            TextInputAttributeModifier::OnWillInsertImpl,
            TextInputAttributeModifier::OnDidInsertImpl,
            TextInputAttributeModifier::OnWillDeleteImpl,
            TextInputAttributeModifier::OnDidDeleteImpl,
            TextInputAttributeModifier::EditMenuOptionsImpl,
            TextInputAttributeModifier::EnablePreviewTextImpl,
            TextInputAttributeModifier::EnableHapticFeedbackImpl,
            TextInputAttributeModifier::AutoCapitalizationModeImpl,
            TextInputAttributeModifier::HalfLeadingImpl,
            TextInputAttributeModifier::EllipsisModeImpl,
            TextInputAttributeModifier::StopBackPressImpl,
            TextInputAttributeModifier::OnWillChangeImpl,
            TextInputAttributeModifier::KeyboardAppearanceImpl,
            TextInputAttributeModifier::InputFilterImpl,
            TextInputAttributeModifier::CustomKeyboardImpl,
            TextInputAttributeModifier::ShowCounterImpl,
            TextInputAttributeModifier::_onChangeEvent_textImpl,
        };
        return &ArkUITextInputModifierImpl;
    }

    const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
    {
        static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
            TextPickerModifier::ConstructImpl,
            TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
            TextPickerAttributeModifier::DefaultPickerItemHeightImpl,
            TextPickerAttributeModifier::CanLoopImpl,
            TextPickerAttributeModifier::DisappearTextStyleImpl,
            TextPickerAttributeModifier::TextStyleImpl,
            TextPickerAttributeModifier::SelectedTextStyleImpl,
            TextPickerAttributeModifier::DisableTextStyleAnimationImpl,
            TextPickerAttributeModifier::DefaultTextStyleImpl,
            TextPickerAttributeModifier::OnChangeImpl,
            TextPickerAttributeModifier::OnScrollStopImpl,
            TextPickerAttributeModifier::OnEnterSelectedAreaImpl,
            TextPickerAttributeModifier::SelectedIndexImpl,
            TextPickerAttributeModifier::DividerImpl,
            TextPickerAttributeModifier::GradientHeightImpl,
            TextPickerAttributeModifier::EnableHapticFeedbackImpl,
            TextPickerAttributeModifier::DigitalCrownSensitivityImpl,
            TextPickerAttributeModifier::_onChangeEvent_selectedImpl,
            TextPickerAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUITextPickerModifierImpl;
    }

    const GENERATED_ArkUITextTimerModifier* GetTextTimerModifier()
    {
        static const GENERATED_ArkUITextTimerModifier ArkUITextTimerModifierImpl {
            TextTimerModifier::ConstructImpl,
            TextTimerInterfaceModifier::SetTextTimerOptionsImpl,
            TextTimerAttributeModifier::FormatImpl,
            TextTimerAttributeModifier::FontColorImpl,
            TextTimerAttributeModifier::FontSizeImpl,
            TextTimerAttributeModifier::FontStyleImpl,
            TextTimerAttributeModifier::FontWeightImpl,
            TextTimerAttributeModifier::FontFamilyImpl,
            TextTimerAttributeModifier::OnTimerImpl,
            TextTimerAttributeModifier::TextShadowImpl,
            TextTimerAttributeModifier::ContentModifierImpl,
        };
        return &ArkUITextTimerModifierImpl;
    }

    const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
    {
        static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
            TimePickerModifier::ConstructImpl,
            TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
            TimePickerAttributeModifier::UseMilitaryTimeImpl,
            TimePickerAttributeModifier::LoopImpl,
            TimePickerAttributeModifier::DisappearTextStyleImpl,
            TimePickerAttributeModifier::TextStyleImpl,
            TimePickerAttributeModifier::SelectedTextStyleImpl,
            TimePickerAttributeModifier::DateTimeOptionsImpl,
            TimePickerAttributeModifier::OnChangeImpl,
            TimePickerAttributeModifier::OnEnterSelectedAreaImpl,
            TimePickerAttributeModifier::EnableHapticFeedbackImpl,
            TimePickerAttributeModifier::DigitalCrownSensitivityImpl,
            TimePickerAttributeModifier::EnableCascadeImpl,
            TimePickerAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUITimePickerModifierImpl;
    }

    const GENERATED_ArkUIToggleModifier* GetToggleModifier()
    {
        static const GENERATED_ArkUIToggleModifier ArkUIToggleModifierImpl {
            ToggleModifier::ConstructImpl,
            ToggleInterfaceModifier::SetToggleOptionsImpl,
            ToggleAttributeModifier::OnChangeImpl,
            ToggleAttributeModifier::ContentModifierImpl,
            ToggleAttributeModifier::SelectedColorImpl,
            ToggleAttributeModifier::SwitchPointColorImpl,
            ToggleAttributeModifier::SwitchStyleImpl,
            ToggleAttributeModifier::_onChangeEvent_isOnImpl,
        };
        return &ArkUIToggleModifierImpl;
    }

    const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
    {
        static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
            UIExtensionComponentModifier::ConstructImpl,
            UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
            UIExtensionComponentAttributeModifier::OnRemoteReadyImpl,
            UIExtensionComponentAttributeModifier::OnReceiveImpl,
            UIExtensionComponentAttributeModifier::OnErrorImpl,
            UIExtensionComponentAttributeModifier::OnTerminatedImpl,
            UIExtensionComponentAttributeModifier::OnDrawReadyImpl,
        };
        return &ArkUIUIExtensionComponentModifierImpl;
    }

    const GENERATED_ArkUIVideoModifier* GetVideoModifier()
    {
        static const GENERATED_ArkUIVideoModifier ArkUIVideoModifierImpl {
            VideoModifier::ConstructImpl,
            VideoInterfaceModifier::SetVideoOptionsImpl,
            VideoAttributeModifier::MutedImpl,
            VideoAttributeModifier::AutoPlayImpl,
            VideoAttributeModifier::ControlsImpl,
            VideoAttributeModifier::LoopImpl,
            VideoAttributeModifier::ObjectFitImpl,
            VideoAttributeModifier::OnStartImpl,
            VideoAttributeModifier::OnPauseImpl,
            VideoAttributeModifier::OnFinishImpl,
            VideoAttributeModifier::OnFullscreenChangeImpl,
            VideoAttributeModifier::OnPreparedImpl,
            VideoAttributeModifier::OnSeekingImpl,
            VideoAttributeModifier::OnSeekedImpl,
            VideoAttributeModifier::OnUpdateImpl,
            VideoAttributeModifier::OnErrorImpl,
            VideoAttributeModifier::OnStopImpl,
            VideoAttributeModifier::EnableAnalyzerImpl,
            VideoAttributeModifier::AnalyzerConfigImpl,
            VideoAttributeModifier::SurfaceBackgroundColorImpl,
            VideoAttributeModifier::EnableShortcutKeyImpl,
        };
        return &ArkUIVideoModifierImpl;
    }

    const GENERATED_ArkUIWaterFlowModifier* GetWaterFlowModifier()
    {
        static const GENERATED_ArkUIWaterFlowModifier ArkUIWaterFlowModifierImpl {
            WaterFlowModifier::ConstructImpl,
            WaterFlowInterfaceModifier::SetWaterFlowOptionsImpl,
            WaterFlowAttributeModifier::ColumnsTemplateImpl,
            WaterFlowAttributeModifier::ItemConstraintSizeImpl,
            WaterFlowAttributeModifier::RowsTemplateImpl,
            WaterFlowAttributeModifier::ColumnsGapImpl,
            WaterFlowAttributeModifier::RowsGapImpl,
            WaterFlowAttributeModifier::LayoutDirectionImpl,
            WaterFlowAttributeModifier::CachedCount0Impl,
            WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
            WaterFlowAttributeModifier::OnScrollIndexImpl,
            WaterFlowAttributeModifier::OnWillScrollImpl,
            WaterFlowAttributeModifier::OnDidScrollImpl,
            WaterFlowAttributeModifier::CachedCount1Impl,
        };
        return &ArkUIWaterFlowModifierImpl;
    }

    const GENERATED_ArkUIWebModifier* GetWebModifier()
    {
        static const GENERATED_ArkUIWebModifier ArkUIWebModifierImpl {
            WebModifier::ConstructImpl,
            WebInterfaceModifier::SetWebOptionsImpl,
            WebAttributeModifier::JavaScriptAccessImpl,
            WebAttributeModifier::FileAccessImpl,
            WebAttributeModifier::OnlineImageAccessImpl,
            WebAttributeModifier::DomStorageAccessImpl,
            WebAttributeModifier::ImageAccessImpl,
            WebAttributeModifier::MixedModeImpl,
            WebAttributeModifier::ZoomAccessImpl,
            WebAttributeModifier::GeolocationAccessImpl,
            WebAttributeModifier::JavaScriptProxyImpl,
            WebAttributeModifier::CacheModeImpl,
            WebAttributeModifier::DarkModeImpl,
            WebAttributeModifier::ForceDarkAccessImpl,
            WebAttributeModifier::MediaOptionsImpl,
            WebAttributeModifier::OverviewModeAccessImpl,
            WebAttributeModifier::OverScrollModeImpl,
            WebAttributeModifier::BlurOnKeyboardHideModeImpl,
            WebAttributeModifier::TextZoomRatioImpl,
            WebAttributeModifier::DatabaseAccessImpl,
            WebAttributeModifier::InitialScaleImpl,
            WebAttributeModifier::MetaViewportImpl,
            WebAttributeModifier::OnPageEndImpl,
            WebAttributeModifier::OnPageBeginImpl,
            WebAttributeModifier::OnProgressChangeImpl,
            WebAttributeModifier::OnTitleReceiveImpl,
            WebAttributeModifier::OnGeolocationHideImpl,
            WebAttributeModifier::OnGeolocationShowImpl,
            WebAttributeModifier::OnRequestSelectedImpl,
            WebAttributeModifier::OnAlertImpl,
            WebAttributeModifier::OnBeforeUnloadImpl,
            WebAttributeModifier::OnConfirmImpl,
            WebAttributeModifier::OnPromptImpl,
            WebAttributeModifier::OnConsoleImpl,
            WebAttributeModifier::OnErrorReceiveImpl,
            WebAttributeModifier::OnHttpErrorReceiveImpl,
            WebAttributeModifier::OnDownloadStartImpl,
            WebAttributeModifier::OnRefreshAccessedHistoryImpl,
            WebAttributeModifier::OnRenderExitedImpl,
            WebAttributeModifier::OnShowFileSelectorImpl,
            WebAttributeModifier::OnResourceLoadImpl,
            WebAttributeModifier::OnFullScreenExitImpl,
            WebAttributeModifier::OnFullScreenEnterImpl,
            WebAttributeModifier::OnScaleChangeImpl,
            WebAttributeModifier::OnHttpAuthRequestImpl,
            WebAttributeModifier::OnInterceptRequestImpl,
            WebAttributeModifier::OnPermissionRequestImpl,
            WebAttributeModifier::OnScreenCaptureRequestImpl,
            WebAttributeModifier::OnContextMenuShowImpl,
            WebAttributeModifier::OnContextMenuHideImpl,
            WebAttributeModifier::MediaPlayGestureAccessImpl,
            WebAttributeModifier::OnSearchResultReceiveImpl,
            WebAttributeModifier::OnScrollImpl,
            WebAttributeModifier::OnSslErrorEventReceiveImpl,
            WebAttributeModifier::OnSslErrorEventImpl,
            WebAttributeModifier::OnClientAuthenticationRequestImpl,
            WebAttributeModifier::OnWindowNewImpl,
            WebAttributeModifier::OnWindowExitImpl,
            WebAttributeModifier::MultiWindowAccessImpl,
            WebAttributeModifier::OnInterceptKeyEventImpl,
            WebAttributeModifier::WebStandardFontImpl,
            WebAttributeModifier::WebSerifFontImpl,
            WebAttributeModifier::WebSansSerifFontImpl,
            WebAttributeModifier::WebFixedFontImpl,
            WebAttributeModifier::WebFantasyFontImpl,
            WebAttributeModifier::WebCursiveFontImpl,
            WebAttributeModifier::DefaultFixedFontSizeImpl,
            WebAttributeModifier::DefaultFontSizeImpl,
            WebAttributeModifier::MinFontSizeImpl,
            WebAttributeModifier::MinLogicalFontSizeImpl,
            WebAttributeModifier::DefaultTextEncodingFormatImpl,
            WebAttributeModifier::ForceDisplayScrollBarImpl,
            WebAttributeModifier::BlockNetworkImpl,
            WebAttributeModifier::HorizontalScrollBarAccessImpl,
            WebAttributeModifier::VerticalScrollBarAccessImpl,
            WebAttributeModifier::OnTouchIconUrlReceivedImpl,
            WebAttributeModifier::OnFaviconReceivedImpl,
            WebAttributeModifier::OnPageVisibleImpl,
            WebAttributeModifier::OnDataResubmittedImpl,
            WebAttributeModifier::PinchSmoothImpl,
            WebAttributeModifier::AllowWindowOpenMethodImpl,
            WebAttributeModifier::OnAudioStateChangedImpl,
            WebAttributeModifier::OnFirstContentfulPaintImpl,
            WebAttributeModifier::OnFirstMeaningfulPaintImpl,
            WebAttributeModifier::OnLargestContentfulPaintImpl,
            WebAttributeModifier::OnLoadInterceptImpl,
            WebAttributeModifier::OnControllerAttachedImpl,
            WebAttributeModifier::OnOverScrollImpl,
            WebAttributeModifier::OnSafeBrowsingCheckResultImpl,
            WebAttributeModifier::OnNavigationEntryCommittedImpl,
            WebAttributeModifier::OnIntelligentTrackingPreventionResultImpl,
            WebAttributeModifier::JavaScriptOnDocumentStartImpl,
            WebAttributeModifier::JavaScriptOnDocumentEndImpl,
            WebAttributeModifier::LayoutModeImpl,
            WebAttributeModifier::NestedScrollImpl,
            WebAttributeModifier::EnableNativeEmbedModeImpl,
            WebAttributeModifier::OnNativeEmbedLifecycleChangeImpl,
            WebAttributeModifier::OnNativeEmbedVisibilityChangeImpl,
            WebAttributeModifier::OnNativeEmbedGestureEventImpl,
            WebAttributeModifier::CopyOptionsImpl,
            WebAttributeModifier::OnOverrideUrlLoadingImpl,
            WebAttributeModifier::TextAutosizingImpl,
            WebAttributeModifier::EnableNativeMediaPlayerImpl,
            WebAttributeModifier::OnRenderProcessNotRespondingImpl,
            WebAttributeModifier::OnRenderProcessRespondingImpl,
            WebAttributeModifier::OnViewportFitChangedImpl,
            WebAttributeModifier::OnInterceptKeyboardAttachImpl,
            WebAttributeModifier::OnAdsBlockedImpl,
            WebAttributeModifier::KeyboardAvoidModeImpl,
            WebAttributeModifier::EditMenuOptionsImpl,
            WebAttributeModifier::EnableHapticFeedbackImpl,
            WebAttributeModifier::OptimizeParserBudgetImpl,
            WebAttributeModifier::EnableFollowSystemFontWeightImpl,
            WebAttributeModifier::EnableWebAVSessionImpl,
            WebAttributeModifier::RunJavaScriptOnDocumentStartImpl,
            WebAttributeModifier::RunJavaScriptOnDocumentEndImpl,
            WebAttributeModifier::RunJavaScriptOnHeadEndImpl,
            WebAttributeModifier::NativeEmbedOptionsImpl,
            WebAttributeModifier::RegisterNativeEmbedRuleImpl,
            WebAttributeModifier::BindSelectionMenuImpl,
        };
        return &ArkUIWebModifierImpl;
    }

    const GENERATED_ArkUIWindowSceneModifier* GetWindowSceneModifier()
    {
        static const GENERATED_ArkUIWindowSceneModifier ArkUIWindowSceneModifierImpl {
            WindowSceneModifier::ConstructImpl,
            WindowSceneInterfaceModifier::SetWindowSceneOptionsImpl,
            WindowSceneAttributeModifier::AttractionEffectImpl,
        };
        return &ArkUIWindowSceneModifierImpl;
    }

    const GENERATED_ArkUIXComponentModifier* GetXComponentModifier()
    {
        static const GENERATED_ArkUIXComponentModifier ArkUIXComponentModifierImpl {
            XComponentModifier::ConstructImpl,
            XComponentInterfaceModifier::SetXComponentOptions0Impl,
            XComponentInterfaceModifier::SetXComponentOptions1Impl,
            XComponentInterfaceModifier::SetXComponentOptions2Impl,
            XComponentAttributeModifier::OnLoadImpl,
            XComponentAttributeModifier::OnDestroyImpl,
            XComponentAttributeModifier::EnableAnalyzerImpl,
            XComponentAttributeModifier::EnableSecureImpl,
            XComponentAttributeModifier::HdrBrightnessImpl,
            XComponentAttributeModifier::EnableTransparentLayerImpl,
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
            GetComponentRootModifier,
            GetContainerSpanModifier,
            GetCounterModifier,
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
            GetScreenModifier,
            GetScrollModifier,
            GetScrollableCommonMethodModifier,
            GetScrollBarModifier,
            GetSearchModifier,
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
            GetUIExtensionComponentModifier,
            GetVideoModifier,
            GetWaterFlowModifier,
            GetWebModifier,
            GetWindowSceneModifier,
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
    Ark_Number GetXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_AccessibilityHoverEvent peer,
                  const Ark_Number* x)
    {
    }
    Ark_Number GetYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_AccessibilityHoverEvent peer,
                  const Ark_Number* y)
    {
    }
    Ark_Number GetDisplayXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_AccessibilityHoverEvent peer,
                         const Ark_Number* displayX)
    {
    }
    Ark_Number GetDisplayYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_AccessibilityHoverEvent peer,
                         const Ark_Number* displayY)
    {
    }
    Ark_Number GetWindowXImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_AccessibilityHoverEvent peer,
                        const Ark_Number* windowX)
    {
    }
    Ark_Number GetWindowYImpl(Ark_AccessibilityHoverEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_AccessibilityHoverEvent peer,
                        const Ark_Number* windowY)
    {
    }
    } // AccessibilityHoverEventAccessor
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
    Ark_Number GetHorizontalAxisValueImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    Ark_Number GetVerticalAxisValueImpl(Ark_AxisEvent peer)
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
    Ark_Number GetDisplayXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_AxisEvent peer,
                         const Ark_Number* displayX)
    {
    }
    Ark_Number GetDisplayYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_AxisEvent peer,
                         const Ark_Number* displayY)
    {
    }
    Ark_Number GetWindowXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_AxisEvent peer,
                        const Ark_Number* windowX)
    {
    }
    Ark_Number GetWindowYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_AxisEvent peer,
                        const Ark_Number* windowY)
    {
    }
    Ark_Number GetXImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_AxisEvent peer,
                  const Ark_Number* x)
    {
    }
    Ark_Number GetYImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_AxisEvent peer,
                  const Ark_Number* y)
    {
    }
    Opt_Number GetScrollStepImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetScrollStepImpl(Ark_AxisEvent peer,
                           const Opt_Number* scrollStep)
    {
    }
    Callback_Void GetPropagationImpl(Ark_AxisEvent peer)
    {
        return {};
    }
    void SetPropagationImpl(Ark_AxisEvent peer,
                            const Callback_Void* propagation)
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
    namespace BaseContextAccessor {
    void DestroyPeerImpl(Ark_BaseContext peer)
    {
        auto peerImpl = reinterpret_cast<BaseContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseContext ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // BaseContextAccessor
    namespace BaseCustomDialogAccessor {
    void DestroyPeerImpl(Ark_BaseCustomDialog peer)
    {
        auto peerImpl = reinterpret_cast<BaseCustomDialogPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseCustomDialog ConstructImpl(const Opt_Boolean* useSharedStorage,
                                       const Opt_CustomObject* storage)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CustomObject $_instantiateImpl(const Callback_T* factory,
                                       const Opt_CustomObject* initializers,
                                       const Opt_Callback_Void* content)
    {
        return {};
    }
    } // BaseCustomDialogAccessor
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
    Ark_Number GetTimestampImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTimestampImpl(Ark_BaseEvent peer,
                          const Ark_Number* timestamp)
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
    Opt_Number GetAxisHorizontalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                               const Opt_Number* axisHorizontal)
    {
    }
    Opt_Number GetAxisVerticalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisVerticalImpl(Ark_BaseEvent peer,
                             const Opt_Number* axisVertical)
    {
    }
    Ark_Number GetPressureImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetPressureImpl(Ark_BaseEvent peer,
                         const Ark_Number* pressure)
    {
    }
    Ark_Number GetTiltXImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTiltXImpl(Ark_BaseEvent peer,
                      const Ark_Number* tiltX)
    {
    }
    Ark_Number GetTiltYImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTiltYImpl(Ark_BaseEvent peer,
                      const Ark_Number* tiltY)
    {
    }
    Opt_Number GetRollAngleImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetRollAngleImpl(Ark_BaseEvent peer,
                          const Opt_Number* rollAngle)
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
    Opt_Number GetDeviceIdImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetDeviceIdImpl(Ark_BaseEvent peer,
                         const Opt_Number* deviceId)
    {
    }
    Opt_Number GetTargetDisplayIdImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetTargetDisplayIdImpl(Ark_BaseEvent peer,
                                const Opt_Number* targetDisplayId)
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
    } // BaseGestureEventAccessor
    namespace BaselineOffsetStyleAccessor {
    void DestroyPeerImpl(Ark_BaselineOffsetStyle peer)
    {
        auto peerImpl = reinterpret_cast<BaselineOffsetStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaselineOffsetStyle ConstructImpl(Ark_LengthMetrics value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetBaselineOffsetImpl(Ark_BaselineOffsetStyle peer)
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
                          const Ark_Number* offset,
                          const Ark_String* color)
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
    Ark_Union_String_Number_CanvasGradient_CanvasPattern GetFillStyleImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetFillStyleImpl(Ark_CanvasRenderer peer,
                          const Ark_Union_String_Number_CanvasGradient_CanvasPattern* fillStyle)
    {
    }
    Ark_Union_String_Number_CanvasGradient_CanvasPattern GetStrokeStyleImpl(Ark_CanvasRenderer peer)
    {
        return {};
    }
    void SetStrokeStyleImpl(Ark_CanvasRenderer peer,
                            const Ark_Union_String_Number_CanvasGradient_CanvasPattern* strokeStyle)
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
    Ark_ChildrenMainSize ConstructImpl(const Ark_Number* childDefaultSize)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SpliceImpl(Ark_ChildrenMainSize peer,
                    const Ark_Number* start,
                    const Opt_Number* deleteCount,
                    const Opt_Array_Number* childrenSize)
    {
    }
    void UpdateImpl(Ark_ChildrenMainSize peer,
                    const Ark_Number* index,
                    const Ark_Number* childSize)
    {
    }
    Ark_Number GetChildDefaultSizeImpl(Ark_ChildrenMainSize peer)
    {
        return {};
    }
    void SetChildDefaultSizeImpl(Ark_ChildrenMainSize peer,
                                 const Ark_Number* childDefaultSize)
    {
    }
    } // ChildrenMainSizeAccessor
    namespace CircleShapeAccessor {
    void DestroyPeerImpl(Ark_CircleShape peer)
    {
        auto peerImpl = reinterpret_cast<CircleShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CircleShape ConstructImpl(const Opt_ShapeSize* options)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CircleShape OffsetImpl(Ark_CircleShape peer,
                               const Ark_Position* offset)
    {
        return {};
    }
    Ark_CircleShape FillImpl(Ark_CircleShape peer,
                             const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_CircleShape PositionImpl(Ark_CircleShape peer,
                                 const Ark_Position* position)
    {
        return {};
    }
    Ark_CircleShape WidthImpl(Ark_CircleShape peer,
                              const Ark_Length* width)
    {
        return {};
    }
    Ark_CircleShape HeightImpl(Ark_CircleShape peer,
                               const Ark_Length* height)
    {
        return {};
    }
    Ark_CircleShape SizeImpl(Ark_CircleShape peer,
                             const Ark_SizeOptions* size)
    {
        return {};
    }
    } // CircleShapeAccessor
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
    Ark_Number GetDisplayXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_ClickEvent peer,
                         const Ark_Number* displayX)
    {
    }
    Ark_Number GetDisplayYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_ClickEvent peer,
                         const Ark_Number* displayY)
    {
    }
    Ark_Number GetWindowXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_ClickEvent peer,
                        const Ark_Number* windowX)
    {
    }
    Ark_Number GetWindowYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_ClickEvent peer,
                        const Ark_Number* windowY)
    {
    }
    Ark_Number GetXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_ClickEvent peer,
                  const Ark_Number* x)
    {
    }
    Ark_Number GetYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_ClickEvent peer,
                  const Ark_Number* y)
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
    Callback_Void GetPreventDefaultImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetPreventDefaultImpl(Ark_ClickEvent peer,
                               const Callback_Void* preventDefault)
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
    namespace ColorMetricsAccessor {
    void DestroyPeerImpl(Ark_ColorMetrics peer)
    {
        auto peerImpl = reinterpret_cast<ColorMetricsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ColorMetrics ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_ColorMetrics NumericImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_ColorMetrics RgbaImpl(const Ark_Number* red,
                              const Ark_Number* green,
                              const Ark_Number* blue,
                              const Ark_Number* alpha)
    {
        return {};
    }
    Ark_ColorMetrics ResourceColorImpl(const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_ColorMetrics BlendColorImpl(Ark_ColorMetrics peer,
                                    Ark_ColorMetrics overlayColor)
    {
        return {};
    }
    Ark_String ColorImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number RedImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number GreenImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number BlueImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number AlphaImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    } // ColorMetricsAccessor
    namespace common_ContextAccessor {
    void DestroyPeerImpl(Ark_common_Context peer)
    {
        auto peerImpl = reinterpret_cast<common_ContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_common_Context ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_common_Context CreateBundleContextImpl(Ark_VMContext vmContext,
                                               Ark_common_Context peer,
                                               const Ark_String* bundleName)
    {
        return {};
    }
    Ark_common_Context CreateModuleContext0Impl(Ark_VMContext vmContext,
                                                Ark_common_Context peer,
                                                const Ark_String* moduleName)
    {
        return {};
    }
    Ark_common_Context CreateModuleContext1Impl(Ark_VMContext vmContext,
                                                Ark_common_Context peer,
                                                const Ark_String* bundleName,
                                                const Ark_String* moduleName)
    {
        return {};
    }
    void GetGroupDir0Impl(Ark_VMContext vmContext,
                          Ark_common_Context peer,
                          const Ark_String* dataGroupID,
                          const Context_getGroupDir_Callback* callback_)
    {
    }
    void GetGroupDir1Impl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_common_Context peer,
                          const Ark_String* dataGroupID,
                          const Callback_Opt_String_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    Ark_String GetCacheDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetCacheDirImpl(Ark_common_Context peer,
                         const Ark_String* cacheDir)
    {
    }
    Ark_String GetTempDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetTempDirImpl(Ark_common_Context peer,
                        const Ark_String* tempDir)
    {
    }
    Ark_String GetFilesDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetFilesDirImpl(Ark_common_Context peer,
                         const Ark_String* filesDir)
    {
    }
    Ark_String GetDatabaseDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetDatabaseDirImpl(Ark_common_Context peer,
                            const Ark_String* databaseDir)
    {
    }
    Ark_String GetPreferencesDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetPreferencesDirImpl(Ark_common_Context peer,
                               const Ark_String* preferencesDir)
    {
    }
    Ark_String GetBundleCodeDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetBundleCodeDirImpl(Ark_common_Context peer,
                              const Ark_String* bundleCodeDir)
    {
    }
    Ark_String GetDistributedFilesDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetDistributedFilesDirImpl(Ark_common_Context peer,
                                    const Ark_String* distributedFilesDir)
    {
    }
    Ark_String GetResourceDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetResourceDirImpl(Ark_common_Context peer,
                            const Ark_String* resourceDir)
    {
    }
    Ark_String GetCloudFileDirImpl(Ark_common_Context peer)
    {
        return {};
    }
    void SetCloudFileDirImpl(Ark_common_Context peer,
                             const Ark_String* cloudFileDir)
    {
    }
    } // common_ContextAccessor
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
    namespace ComponentContentAccessor {
    void DestroyPeerImpl(Ark_ComponentContent peer)
    {
        auto peerImpl = reinterpret_cast<ComponentContentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ComponentContent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void UpdateImpl(Ark_ComponentContent peer,
                    const Ark_Object* args)
    {
    }
    void ReuseImpl(Ark_ComponentContent peer,
                   const Opt_Object* param)
    {
    }
    void RecycleImpl(Ark_ComponentContent peer)
    {
    }
    void DisposeImpl(Ark_ComponentContent peer)
    {
    }
    void UpdateConfigurationImpl(Ark_ComponentContent peer)
    {
    }
    } // ComponentContentAccessor
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
    Ark_Number GetLineNumberImpl(Ark_ConsoleMessage peer)
    {
        return {};
    }
    Ark_MessageLevel GetMessageLevelImpl(Ark_ConsoleMessage peer)
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
    void ContentModifierCheckBoxImpl(Ark_NativePointer node,
                                     const Ark_Object* contentModifier,
                                     const CheckBoxModifierBuilder* builder)
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
    void ContentModifierGaugeImpl(Ark_NativePointer node,
                                  const Ark_Object* contentModifier,
                                  const GaugeModifierBuilder* builder)
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
    void ContentModifierProgressImpl(Ark_NativePointer node,
                                     const Ark_Object* contentModifier,
                                     const ProgressModifierBuilder* builder)
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
    void ContentModifierRatingImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const RatingModifierBuilder* builder)
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
    void ContentModifierSliderImpl(Ark_NativePointer node,
                                   const Ark_Object* contentModifier,
                                   const SliderModifierBuilder* builder)
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
    void ContentModifierTextTimerImpl(Ark_NativePointer node,
                                      const Ark_Object* contentModifier,
                                      const TextTimerModifierBuilder* builder)
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
    } // ContentModifierHelperAccessor
    namespace ContextAccessor {
    void DestroyPeerImpl(Ark_Context peer)
    {
        auto peerImpl = reinterpret_cast<ContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Context ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // ContextAccessor
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
    namespace curves_ICurveAccessor {
    void DestroyPeerImpl(Ark_curves_ICurve peer)
    {
        auto peerImpl = reinterpret_cast<curves_ICurvePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_curves_ICurve ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number InterpolateImpl(Ark_curves_ICurve peer,
                               const Ark_Number* fraction)
    {
        return {};
    }
    } // curves_ICurveAccessor
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
    } // CustomDialogControllerAccessor
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
    Callback_CustomSpanMeasureInfo_CustomSpanMetrics GetOnMeasureImpl(Ark_CustomSpan peer)
    {
        return {};
    }
    void SetOnMeasureImpl(Ark_CustomSpan peer,
                          const Callback_CustomSpanMeasureInfo_CustomSpanMetrics* onMeasure)
    {
    }
    Callback_DrawContext_CustomSpanDrawInfo_Void GetOnDrawImpl(Ark_CustomSpan peer)
    {
        return {};
    }
    void SetOnDrawImpl(Ark_CustomSpan peer,
                       const Callback_DrawContext_CustomSpanDrawInfo_Void* onDraw)
    {
    }
    } // CustomSpanAccessor
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
    Ark_Number GetDisplayXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetDisplayYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetWindowXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetWindowYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetDataImpl(Ark_DragEvent peer,
                     Ark_unifiedDataChannel_UnifiedData unifiedData)
    {
    }
    Ark_unifiedDataChannel_UnifiedData GetDataImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_unifiedDataChannel_Summary GetSummaryImpl(Ark_DragEvent peer)
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
    Ark_Number GetVelocityXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetVelocityYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetVelocityImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void ExecuteDropAnimationImpl(Ark_DragEvent peer,
                                  const Callback_Void* customDropAnimation)
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
    namespace DrawableDescriptorAccessor {
    void DestroyPeerImpl(Ark_DrawableDescriptor peer)
    {
        auto peerImpl = reinterpret_cast<DrawableDescriptorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawableDescriptor ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_image_PixelMap GetPixelMapImpl(Ark_DrawableDescriptor peer)
    {
        return {};
    }
    } // DrawableDescriptorAccessor
    namespace DrawContextAccessor {
    void DestroyPeerImpl(Ark_DrawContext peer)
    {
        auto peerImpl = reinterpret_cast<DrawContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawContext ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Size SizeImpl(Ark_DrawContext peer)
    {
        return {};
    }
    Ark_Size SizeInPixelImpl(Ark_DrawContext peer)
    {
        return {};
    }
    Ark_drawing_Canvas CanvasImpl(Ark_DrawContext peer)
    {
        return {};
    }
    } // DrawContextAccessor
    namespace drawing_BrushAccessor {
    void DestroyPeerImpl(Ark_drawing_Brush peer)
    {
        auto peerImpl = reinterpret_cast<drawing_BrushPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Brush Construct0Impl()
    {
        return {};
    }
    Ark_drawing_Brush Construct1Impl(Ark_drawing_Brush brush)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetColor0Impl(Ark_drawing_Brush peer,
                       const Ark_common2D_Color* color)
    {
    }
    void SetColor1Impl(Ark_drawing_Brush peer,
                       const Ark_Number* color)
    {
    }
    void SetColor2Impl(Ark_drawing_Brush peer,
                       const Ark_Number* alpha,
                       const Ark_Number* red,
                       const Ark_Number* green,
                       const Ark_Number* blue)
    {
    }
    Ark_common2D_Color GetColorImpl(Ark_drawing_Brush peer)
    {
        return {};
    }
    Ark_Number GetHexColorImpl(Ark_drawing_Brush peer)
    {
        return {};
    }
    void SetAntiAliasImpl(Ark_drawing_Brush peer,
                          Ark_Boolean aa)
    {
    }
    Ark_Boolean IsAntiAliasImpl(Ark_drawing_Brush peer)
    {
        return {};
    }
    void SetAlphaImpl(Ark_drawing_Brush peer,
                      const Ark_Number* alpha)
    {
    }
    Ark_Number GetAlphaImpl(Ark_drawing_Brush peer)
    {
        return {};
    }
    void SetColorFilterImpl(Ark_drawing_Brush peer,
                            Ark_drawing_ColorFilter filter)
    {
    }
    Ark_drawing_ColorFilter GetColorFilterImpl(Ark_drawing_Brush peer)
    {
        return {};
    }
    void SetImageFilterImpl(Ark_drawing_Brush peer,
                            const Opt_drawing_ImageFilter* filter)
    {
    }
    void SetMaskFilterImpl(Ark_drawing_Brush peer,
                           Ark_drawing_MaskFilter filter)
    {
    }
    void SetShadowLayerImpl(Ark_drawing_Brush peer,
                            Ark_drawing_ShadowLayer shadowLayer)
    {
    }
    void SetShaderEffectImpl(Ark_drawing_Brush peer,
                             Ark_drawing_ShaderEffect shaderEffect)
    {
    }
    void SetBlendModeImpl(Ark_drawing_Brush peer,
                          Ark_drawing_BlendMode mode)
    {
    }
    void ResetImpl(Ark_drawing_Brush peer)
    {
    }
    } // drawing_BrushAccessor
    namespace drawing_CanvasAccessor {
    void DestroyPeerImpl(Ark_drawing_Canvas peer)
    {
        auto peerImpl = reinterpret_cast<drawing_CanvasPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Canvas ConstructImpl(Ark_image_PixelMap pixelmap)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DrawRect0Impl(Ark_drawing_Canvas peer,
                       const Ark_common2D_Rect* rect)
    {
    }
    void DrawRect1Impl(Ark_drawing_Canvas peer,
                       const Ark_Number* left,
                       const Ark_Number* top,
                       const Ark_Number* right,
                       const Ark_Number* bottom)
    {
    }
    void DrawRoundRectImpl(Ark_drawing_Canvas peer,
                           Ark_drawing_RoundRect roundRect)
    {
    }
    void DrawNestedRoundRectImpl(Ark_drawing_Canvas peer,
                                 Ark_drawing_RoundRect outer,
                                 Ark_drawing_RoundRect inner)
    {
    }
    void DrawBackgroundImpl(Ark_drawing_Canvas peer,
                            Ark_drawing_Brush brush)
    {
    }
    void DrawShadow0Impl(Ark_drawing_Canvas peer,
                         Ark_drawing_Path path,
                         const Ark_common2D_Point3d* planeParams,
                         const Ark_common2D_Point3d* devLightPos,
                         const Ark_Number* lightRadius,
                         const Ark_common2D_Color* ambientColor,
                         const Ark_common2D_Color* spotColor,
                         Ark_drawing_ShadowFlag flag)
    {
    }
    void DrawShadow1Impl(Ark_drawing_Canvas peer,
                         Ark_drawing_Path path,
                         const Ark_common2D_Point3d* planeParams,
                         const Ark_common2D_Point3d* devLightPos,
                         const Ark_Number* lightRadius,
                         const Ark_Number* ambientColor,
                         const Ark_Number* spotColor,
                         Ark_drawing_ShadowFlag flag)
    {
    }
    void DrawCircleImpl(Ark_drawing_Canvas peer,
                        const Ark_Number* x,
                        const Ark_Number* y,
                        const Ark_Number* radius)
    {
    }
    void DrawImageImpl(Ark_drawing_Canvas peer,
                       Ark_image_PixelMap pixelmap,
                       const Ark_Number* left,
                       const Ark_Number* top,
                       Ark_drawing_SamplingOptions samplingOptions)
    {
    }
    void DrawImageRectImpl(Ark_drawing_Canvas peer,
                           Ark_image_PixelMap pixelmap,
                           const Ark_common2D_Rect* dstRect,
                           Ark_drawing_SamplingOptions samplingOptions)
    {
    }
    void DrawImageRectWithSrcImpl(Ark_drawing_Canvas peer,
                                  Ark_image_PixelMap pixelmap,
                                  const Ark_common2D_Rect* srcRect,
                                  const Ark_common2D_Rect* dstRect,
                                  Ark_drawing_SamplingOptions samplingOptions,
                                  Ark_drawing_SrcRectConstraint constraint)
    {
    }
    void DrawColor0Impl(Ark_drawing_Canvas peer,
                        const Ark_common2D_Color* color,
                        Ark_drawing_BlendMode blendMode)
    {
    }
    void DrawColor1Impl(Ark_drawing_Canvas peer,
                        const Ark_Number* color,
                        Ark_drawing_BlendMode blendMode)
    {
    }
    void DrawColor2Impl(Ark_drawing_Canvas peer,
                        const Ark_Number* alpha,
                        const Ark_Number* red,
                        const Ark_Number* green,
                        const Ark_Number* blue,
                        Ark_drawing_BlendMode blendMode)
    {
    }
    void DrawOvalImpl(Ark_drawing_Canvas peer,
                      const Ark_common2D_Rect* oval)
    {
    }
    void DrawArcImpl(Ark_drawing_Canvas peer,
                     const Ark_common2D_Rect* arc,
                     const Ark_Number* startAngle,
                     const Ark_Number* sweepAngle)
    {
    }
    void DrawPointImpl(Ark_drawing_Canvas peer,
                       const Ark_Number* x,
                       const Ark_Number* y)
    {
    }
    void DrawPointsImpl(Ark_drawing_Canvas peer,
                        const Array_common2D_Point* points,
                        Ark_drawing_PointMode mode)
    {
    }
    void DrawPathImpl(Ark_drawing_Canvas peer,
                      Ark_drawing_Path path)
    {
    }
    void DrawLineImpl(Ark_drawing_Canvas peer,
                      const Ark_Number* x0,
                      const Ark_Number* y0,
                      const Ark_Number* x1,
                      const Ark_Number* y1)
    {
    }
    void DrawSingleCharacterImpl(Ark_drawing_Canvas peer,
                                 const Ark_String* text,
                                 Ark_drawing_Font font,
                                 const Ark_Number* x,
                                 const Ark_Number* y)
    {
    }
    void DrawTextBlobImpl(Ark_drawing_Canvas peer,
                          Ark_drawing_TextBlob blob,
                          const Ark_Number* x,
                          const Ark_Number* y)
    {
    }
    void DrawPixelMapMeshImpl(Ark_drawing_Canvas peer,
                              Ark_image_PixelMap pixelmap,
                              const Ark_Number* meshWidth,
                              const Ark_Number* meshHeight,
                              const Array_Number* vertices,
                              const Ark_Number* vertOffset,
                              const Array_Number* colors,
                              const Ark_Number* colorOffset)
    {
    }
    void DrawRegionImpl(Ark_drawing_Canvas peer,
                        Ark_drawing_Region region)
    {
    }
    void AttachPenImpl(Ark_drawing_Canvas peer,
                       Ark_drawing_Pen pen)
    {
    }
    void AttachBrushImpl(Ark_drawing_Canvas peer,
                         Ark_drawing_Brush brush)
    {
    }
    void DetachPenImpl(Ark_drawing_Canvas peer)
    {
    }
    void DetachBrushImpl(Ark_drawing_Canvas peer)
    {
    }
    Ark_Number SaveImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    Ark_Number SaveLayerImpl(Ark_drawing_Canvas peer,
                             const Opt_common2D_Rect* rect,
                             const Opt_drawing_Brush* brush)
    {
        return {};
    }
    void Clear0Impl(Ark_drawing_Canvas peer,
                    const Ark_common2D_Color* color)
    {
    }
    void Clear1Impl(Ark_drawing_Canvas peer,
                    const Ark_Number* color)
    {
    }
    void RestoreImpl(Ark_drawing_Canvas peer)
    {
    }
    void RestoreToCountImpl(Ark_drawing_Canvas peer,
                            const Ark_Number* count)
    {
    }
    Ark_Number GetSaveCountImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    Ark_Number GetWidthImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    Ark_Number GetHeightImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    Ark_common2D_Rect GetLocalClipBoundsImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    Ark_drawing_Matrix GetTotalMatrixImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    void ScaleImpl(Ark_drawing_Canvas peer,
                   const Ark_Number* sx,
                   const Ark_Number* sy)
    {
    }
    void SkewImpl(Ark_drawing_Canvas peer,
                  const Ark_Number* sx,
                  const Ark_Number* sy)
    {
    }
    void RotateImpl(Ark_drawing_Canvas peer,
                    const Ark_Number* degrees,
                    const Ark_Number* sx,
                    const Ark_Number* sy)
    {
    }
    void TranslateImpl(Ark_drawing_Canvas peer,
                       const Ark_Number* dx,
                       const Ark_Number* dy)
    {
    }
    void ClipPathImpl(Ark_drawing_Canvas peer,
                      Ark_drawing_Path path,
                      Ark_drawing_ClipOp clipOp,
                      Ark_Boolean doAntiAlias)
    {
    }
    void ClipRectImpl(Ark_drawing_Canvas peer,
                      const Ark_common2D_Rect* rect,
                      Ark_drawing_ClipOp clipOp,
                      Ark_Boolean doAntiAlias)
    {
    }
    void ConcatMatrixImpl(Ark_drawing_Canvas peer,
                          Ark_drawing_Matrix matrix)
    {
    }
    void ClipRegionImpl(Ark_drawing_Canvas peer,
                        Ark_drawing_Region region,
                        Ark_drawing_ClipOp clipOp)
    {
    }
    void ClipRoundRectImpl(Ark_drawing_Canvas peer,
                           Ark_drawing_RoundRect roundRect,
                           Ark_drawing_ClipOp clipOp,
                           Ark_Boolean doAntiAlias)
    {
    }
    Ark_Boolean IsClipEmptyImpl(Ark_drawing_Canvas peer)
    {
        return {};
    }
    void SetMatrixImpl(Ark_drawing_Canvas peer,
                       Ark_drawing_Matrix matrix)
    {
    }
    void ResetMatrixImpl(Ark_drawing_Canvas peer)
    {
    }
    } // drawing_CanvasAccessor
    namespace drawing_ColorFilterAccessor {
    void DestroyPeerImpl(Ark_drawing_ColorFilter peer)
    {
        auto peerImpl = reinterpret_cast<drawing_ColorFilterPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_ColorFilter ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_ColorFilter CreateBlendModeColorFilter0Impl(const Ark_common2D_Color* color,
                                                            Ark_drawing_BlendMode mode)
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateBlendModeColorFilter1Impl(const Ark_Number* color,
                                                            Ark_drawing_BlendMode mode)
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateComposeColorFilterImpl(Ark_drawing_ColorFilter outer,
                                                         Ark_drawing_ColorFilter inner)
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateLinearToSRGBGammaImpl()
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateSRGBGammaToLinearImpl()
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateLumaColorFilterImpl()
    {
        return {};
    }
    Ark_drawing_ColorFilter CreateMatrixColorFilterImpl(const Array_Number* matrix)
    {
        return {};
    }
    } // drawing_ColorFilterAccessor
    namespace drawing_FontAccessor {
    void DestroyPeerImpl(Ark_drawing_Font peer)
    {
        auto peerImpl = reinterpret_cast<drawing_FontPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Font ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void EnableSubpixelImpl(Ark_drawing_Font peer,
                            Ark_Boolean isSubpixel)
    {
    }
    void EnableEmboldenImpl(Ark_drawing_Font peer,
                            Ark_Boolean isEmbolden)
    {
    }
    void EnableLinearMetricsImpl(Ark_drawing_Font peer,
                                 Ark_Boolean isLinearMetrics)
    {
    }
    void SetSizeImpl(Ark_drawing_Font peer,
                     const Ark_Number* textSize)
    {
    }
    Ark_Number GetSizeImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    void SetTypefaceImpl(Ark_drawing_Font peer,
                         Ark_drawing_Typeface typeface)
    {
    }
    Ark_drawing_Typeface GetTypefaceImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_drawing_FontMetrics GetMetricsImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_Number MeasureSingleCharacterImpl(Ark_drawing_Font peer,
                                          const Ark_String* text)
    {
        return {};
    }
    Ark_Number MeasureTextImpl(Ark_drawing_Font peer,
                               const Ark_String* text,
                               Ark_drawing_TextEncoding encoding)
    {
        return {};
    }
    void SetScaleXImpl(Ark_drawing_Font peer,
                       const Ark_Number* scaleX)
    {
    }
    void SetSkewXImpl(Ark_drawing_Font peer,
                      const Ark_Number* skewX)
    {
    }
    void SetEdgingImpl(Ark_drawing_Font peer,
                       Ark_drawing_FontEdging edging)
    {
    }
    void SetHintingImpl(Ark_drawing_Font peer,
                        Ark_drawing_FontHinting hinting)
    {
    }
    Ark_Number CountTextImpl(Ark_drawing_Font peer,
                             const Ark_String* text)
    {
        return {};
    }
    void SetBaselineSnapImpl(Ark_drawing_Font peer,
                             Ark_Boolean isBaselineSnap)
    {
    }
    Ark_Boolean IsBaselineSnapImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    void SetEmbeddedBitmapsImpl(Ark_drawing_Font peer,
                                Ark_Boolean isEmbeddedBitmaps)
    {
    }
    Ark_Boolean IsEmbeddedBitmapsImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    void SetForceAutoHintingImpl(Ark_drawing_Font peer,
                                 Ark_Boolean isForceAutoHinting)
    {
    }
    Ark_Boolean IsForceAutoHintingImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Array_Number GetWidthsImpl(Ark_drawing_Font peer,
                               const Array_Number* glyphs)
    {
        return {};
    }
    Array_Number TextToGlyphsImpl(Ark_drawing_Font peer,
                                  const Ark_String* text,
                                  const Ark_Number* glyphCount)
    {
        return {};
    }
    Ark_Boolean IsSubpixelImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_Boolean IsLinearMetricsImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_Number GetSkewXImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_Boolean IsEmboldenImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_Number GetScaleXImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_drawing_FontHinting GetHintingImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_drawing_FontEdging GetEdgingImpl(Ark_drawing_Font peer)
    {
        return {};
    }
    Ark_drawing_Path CreatePathForGlyphImpl(Ark_drawing_Font peer,
                                            const Ark_Number* index)
    {
        return {};
    }
    Array_common2D_Rect GetBoundsImpl(Ark_drawing_Font peer,
                                      const Array_Number* glyphs)
    {
        return {};
    }
    Ark_drawing_Path GetTextPathImpl(Ark_drawing_Font peer,
                                     const Ark_String* text,
                                     const Ark_Number* byteLength,
                                     const Ark_Number* x,
                                     const Ark_Number* y)
    {
        return {};
    }
    } // drawing_FontAccessor
    namespace drawing_ImageFilterAccessor {
    void DestroyPeerImpl(Ark_drawing_ImageFilter peer)
    {
        auto peerImpl = reinterpret_cast<drawing_ImageFilterPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_ImageFilter ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_ImageFilter CreateBlurImageFilterImpl(const Ark_Number* sigmaX,
                                                      const Ark_Number* sigmaY,
                                                      Ark_drawing_TileMode tileMode,
                                                      const Opt_drawing_ImageFilter* imageFilter)
    {
        return {};
    }
    Ark_drawing_ImageFilter CreateFromColorFilterImpl(Ark_drawing_ColorFilter colorFilter,
                                                      const Opt_drawing_ImageFilter* imageFilter)
    {
        return {};
    }
    } // drawing_ImageFilterAccessor
    namespace drawing_LatticeAccessor {
    void DestroyPeerImpl(Ark_drawing_Lattice peer)
    {
        auto peerImpl = reinterpret_cast<drawing_LatticePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Lattice ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_Lattice CreateImageLatticeImpl(const Array_Number* xDivs,
                                               const Array_Number* yDivs,
                                               const Ark_Number* fXCount,
                                               const Ark_Number* fYCount,
                                               const Opt_common2D_Rect* fBounds,
                                               const Opt_Array_drawing_RectType* fRectTypes,
                                               const Opt_Array_CustomObject* fColors)
    {
        return {};
    }
    } // drawing_LatticeAccessor
    namespace drawing_MaskFilterAccessor {
    void DestroyPeerImpl(Ark_drawing_MaskFilter peer)
    {
        auto peerImpl = reinterpret_cast<drawing_MaskFilterPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_MaskFilter ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_MaskFilter CreateBlurMaskFilterImpl(Ark_drawing_BlurType blurType,
                                                    const Ark_Number* sigma)
    {
        return {};
    }
    } // drawing_MaskFilterAccessor
    namespace drawing_MatrixAccessor {
    void DestroyPeerImpl(Ark_drawing_Matrix peer)
    {
        auto peerImpl = reinterpret_cast<drawing_MatrixPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Matrix ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetRotationImpl(Ark_drawing_Matrix peer,
                         const Ark_Number* degree,
                         const Ark_Number* px,
                         const Ark_Number* py)
    {
    }
    void SetScaleImpl(Ark_drawing_Matrix peer,
                      const Ark_Number* sx,
                      const Ark_Number* sy,
                      const Ark_Number* px,
                      const Ark_Number* py)
    {
    }
    void SetTranslationImpl(Ark_drawing_Matrix peer,
                            const Ark_Number* dx,
                            const Ark_Number* dy)
    {
    }
    void SetMatrixImpl(Ark_drawing_Matrix peer,
                       const Array_Number* values)
    {
    }
    void PreConcatImpl(Ark_drawing_Matrix peer,
                       Ark_drawing_Matrix matrix)
    {
    }
    Ark_Boolean IsEqualImpl(Ark_drawing_Matrix peer,
                            Ark_drawing_Matrix matrix)
    {
        return {};
    }
    Ark_Boolean InvertImpl(Ark_drawing_Matrix peer,
                           Ark_drawing_Matrix matrix)
    {
        return {};
    }
    Ark_Boolean IsIdentityImpl(Ark_drawing_Matrix peer)
    {
        return {};
    }
    Ark_Number GetValueImpl(Ark_drawing_Matrix peer,
                            const Ark_Number* index)
    {
        return {};
    }
    void PostRotateImpl(Ark_drawing_Matrix peer,
                        const Ark_Number* degree,
                        const Ark_Number* px,
                        const Ark_Number* py)
    {
    }
    void PostScaleImpl(Ark_drawing_Matrix peer,
                       const Ark_Number* sx,
                       const Ark_Number* sy,
                       const Ark_Number* px,
                       const Ark_Number* py)
    {
    }
    void PostTranslateImpl(Ark_drawing_Matrix peer,
                           const Ark_Number* dx,
                           const Ark_Number* dy)
    {
    }
    void PreRotateImpl(Ark_drawing_Matrix peer,
                       const Ark_Number* degree,
                       const Ark_Number* px,
                       const Ark_Number* py)
    {
    }
    void PreScaleImpl(Ark_drawing_Matrix peer,
                      const Ark_Number* sx,
                      const Ark_Number* sy,
                      const Ark_Number* px,
                      const Ark_Number* py)
    {
    }
    void PreTranslateImpl(Ark_drawing_Matrix peer,
                          const Ark_Number* dx,
                          const Ark_Number* dy)
    {
    }
    void ResetImpl(Ark_drawing_Matrix peer)
    {
    }
    Array_common2D_Point MapPointsImpl(Ark_drawing_Matrix peer,
                                       const Array_common2D_Point* src)
    {
        return {};
    }
    Array_Number GetAllImpl(Ark_drawing_Matrix peer)
    {
        return {};
    }
    Ark_Boolean MapRectImpl(Ark_drawing_Matrix peer,
                            const Ark_common2D_Rect* dst,
                            const Ark_common2D_Rect* src)
    {
        return {};
    }
    Ark_Boolean SetRectToRectImpl(Ark_drawing_Matrix peer,
                                  const Ark_common2D_Rect* src,
                                  const Ark_common2D_Rect* dst,
                                  Ark_drawing_ScaleToFit scaleToFit)
    {
        return {};
    }
    Ark_Boolean SetPolyToPolyImpl(Ark_drawing_Matrix peer,
                                  const Array_common2D_Point* src,
                                  const Array_common2D_Point* dst,
                                  const Ark_Number* count)
    {
        return {};
    }
    } // drawing_MatrixAccessor
    namespace drawing_PathAccessor {
    void DestroyPeerImpl(Ark_drawing_Path peer)
    {
        auto peerImpl = reinterpret_cast<drawing_PathPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Path Construct0Impl()
    {
        return {};
    }
    Ark_drawing_Path Construct1Impl(Ark_drawing_Path path)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void MoveToImpl(Ark_drawing_Path peer,
                    const Ark_Number* x,
                    const Ark_Number* y)
    {
    }
    void LineToImpl(Ark_drawing_Path peer,
                    const Ark_Number* x,
                    const Ark_Number* y)
    {
    }
    void ArcToImpl(Ark_drawing_Path peer,
                   const Ark_Number* x1,
                   const Ark_Number* y1,
                   const Ark_Number* x2,
                   const Ark_Number* y2,
                   const Ark_Number* startDeg,
                   const Ark_Number* sweepDeg)
    {
    }
    void QuadToImpl(Ark_drawing_Path peer,
                    const Ark_Number* ctrlX,
                    const Ark_Number* ctrlY,
                    const Ark_Number* endX,
                    const Ark_Number* endY)
    {
    }
    void ConicToImpl(Ark_drawing_Path peer,
                     const Ark_Number* ctrlX,
                     const Ark_Number* ctrlY,
                     const Ark_Number* endX,
                     const Ark_Number* endY,
                     const Ark_Number* weight)
    {
    }
    void CubicToImpl(Ark_drawing_Path peer,
                     const Ark_Number* ctrlX1,
                     const Ark_Number* ctrlY1,
                     const Ark_Number* ctrlX2,
                     const Ark_Number* ctrlY2,
                     const Ark_Number* endX,
                     const Ark_Number* endY)
    {
    }
    void RMoveToImpl(Ark_drawing_Path peer,
                     const Ark_Number* dx,
                     const Ark_Number* dy)
    {
    }
    void RLineToImpl(Ark_drawing_Path peer,
                     const Ark_Number* dx,
                     const Ark_Number* dy)
    {
    }
    void RQuadToImpl(Ark_drawing_Path peer,
                     const Ark_Number* dx1,
                     const Ark_Number* dy1,
                     const Ark_Number* dx2,
                     const Ark_Number* dy2)
    {
    }
    void RConicToImpl(Ark_drawing_Path peer,
                      const Ark_Number* ctrlX,
                      const Ark_Number* ctrlY,
                      const Ark_Number* endX,
                      const Ark_Number* endY,
                      const Ark_Number* weight)
    {
    }
    void RCubicToImpl(Ark_drawing_Path peer,
                      const Ark_Number* ctrlX1,
                      const Ark_Number* ctrlY1,
                      const Ark_Number* ctrlX2,
                      const Ark_Number* ctrlY2,
                      const Ark_Number* endX,
                      const Ark_Number* endY)
    {
    }
    void AddPolygonImpl(Ark_drawing_Path peer,
                        const Array_common2D_Point* points,
                        Ark_Boolean close)
    {
    }
    Ark_Boolean OpImpl(Ark_drawing_Path peer,
                       Ark_drawing_Path path,
                       Ark_drawing_PathOp pathOp)
    {
        return {};
    }
    void AddArcImpl(Ark_drawing_Path peer,
                    const Ark_common2D_Rect* rect,
                    const Ark_Number* startAngle,
                    const Ark_Number* sweepAngle)
    {
    }
    void AddCircleImpl(Ark_drawing_Path peer,
                       const Ark_Number* x,
                       const Ark_Number* y,
                       const Ark_Number* radius,
                       Ark_drawing_PathDirection pathDirection)
    {
    }
    void AddOvalImpl(Ark_drawing_Path peer,
                     const Ark_common2D_Rect* rect,
                     const Ark_Number* start,
                     Ark_drawing_PathDirection pathDirection)
    {
    }
    void AddRectImpl(Ark_drawing_Path peer,
                     const Ark_common2D_Rect* rect,
                     Ark_drawing_PathDirection pathDirection)
    {
    }
    void AddRoundRectImpl(Ark_drawing_Path peer,
                          Ark_drawing_RoundRect roundRect,
                          Ark_drawing_PathDirection pathDirection)
    {
    }
    void AddPathImpl(Ark_drawing_Path peer,
                     Ark_drawing_Path path,
                     const Opt_drawing_Matrix* matrix)
    {
    }
    void TransformImpl(Ark_drawing_Path peer,
                       Ark_drawing_Matrix matrix)
    {
    }
    Ark_Boolean ContainsImpl(Ark_drawing_Path peer,
                             const Ark_Number* x,
                             const Ark_Number* y)
    {
        return {};
    }
    void SetFillTypeImpl(Ark_drawing_Path peer,
                         Ark_drawing_PathFillType pathFillType)
    {
    }
    Ark_common2D_Rect GetBoundsImpl(Ark_drawing_Path peer)
    {
        return {};
    }
    void CloseImpl(Ark_drawing_Path peer)
    {
    }
    Ark_drawing_Path OffsetImpl(Ark_drawing_Path peer,
                                const Ark_Number* dx,
                                const Ark_Number* dy)
    {
        return {};
    }
    void ResetImpl(Ark_drawing_Path peer)
    {
    }
    Ark_Number GetLengthImpl(Ark_drawing_Path peer,
                             Ark_Boolean forceClosed)
    {
        return {};
    }
    Ark_Boolean GetPositionAndTangentImpl(Ark_drawing_Path peer,
                                          Ark_Boolean forceClosed,
                                          const Ark_Number* distance,
                                          const Ark_common2D_Point* position,
                                          const Ark_common2D_Point* tangent)
    {
        return {};
    }
    Ark_Boolean IsClosedImpl(Ark_drawing_Path peer)
    {
        return {};
    }
    Ark_Boolean GetMatrixImpl(Ark_drawing_Path peer,
                              Ark_Boolean forceClosed,
                              const Ark_Number* distance,
                              Ark_drawing_Matrix matrix,
                              Ark_drawing_PathMeasureMatrixFlags flags)
    {
        return {};
    }
    Ark_Boolean BuildFromSvgStringImpl(Ark_drawing_Path peer,
                                       const Ark_String* str)
    {
        return {};
    }
    } // drawing_PathAccessor
    namespace drawing_PathEffectAccessor {
    void DestroyPeerImpl(Ark_drawing_PathEffect peer)
    {
        auto peerImpl = reinterpret_cast<drawing_PathEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_PathEffect ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_PathEffect CreateDashPathEffectImpl(const Array_Number* intervals,
                                                    const Ark_Number* phase)
    {
        return {};
    }
    Ark_drawing_PathEffect CreateCornerPathEffectImpl(const Ark_Number* radius)
    {
        return {};
    }
    } // drawing_PathEffectAccessor
    namespace drawing_PenAccessor {
    void DestroyPeerImpl(Ark_drawing_Pen peer)
    {
        auto peerImpl = reinterpret_cast<drawing_PenPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Pen Construct0Impl()
    {
        return {};
    }
    Ark_drawing_Pen Construct1Impl(Ark_drawing_Pen pen)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetMiterLimitImpl(Ark_drawing_Pen peer,
                           const Ark_Number* miter)
    {
    }
    Ark_Number GetMiterLimitImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetShaderEffectImpl(Ark_drawing_Pen peer,
                             Ark_drawing_ShaderEffect shaderEffect)
    {
    }
    void SetColor0Impl(Ark_drawing_Pen peer,
                       const Ark_common2D_Color* color)
    {
    }
    void SetColor1Impl(Ark_drawing_Pen peer,
                       const Ark_Number* color)
    {
    }
    void SetColor2Impl(Ark_drawing_Pen peer,
                       const Ark_Number* alpha,
                       const Ark_Number* red,
                       const Ark_Number* green,
                       const Ark_Number* blue)
    {
    }
    Ark_common2D_Color GetColorImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    Ark_Number GetHexColorImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetStrokeWidthImpl(Ark_drawing_Pen peer,
                            const Ark_Number* width)
    {
    }
    Ark_Number GetWidthImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetAntiAliasImpl(Ark_drawing_Pen peer,
                          Ark_Boolean aa)
    {
    }
    Ark_Boolean IsAntiAliasImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetAlphaImpl(Ark_drawing_Pen peer,
                      const Ark_Number* alpha)
    {
    }
    Ark_Number GetAlphaImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetColorFilterImpl(Ark_drawing_Pen peer,
                            Ark_drawing_ColorFilter filter)
    {
    }
    Ark_drawing_ColorFilter GetColorFilterImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetImageFilterImpl(Ark_drawing_Pen peer,
                            const Opt_drawing_ImageFilter* filter)
    {
    }
    void SetMaskFilterImpl(Ark_drawing_Pen peer,
                           Ark_drawing_MaskFilter filter)
    {
    }
    void SetPathEffectImpl(Ark_drawing_Pen peer,
                           Ark_drawing_PathEffect effect)
    {
    }
    void SetShadowLayerImpl(Ark_drawing_Pen peer,
                            Ark_drawing_ShadowLayer shadowLayer)
    {
    }
    void SetBlendModeImpl(Ark_drawing_Pen peer,
                          Ark_drawing_BlendMode mode)
    {
    }
    void SetDitherImpl(Ark_drawing_Pen peer,
                       Ark_Boolean dither)
    {
    }
    void SetJoinStyleImpl(Ark_drawing_Pen peer,
                          Ark_drawing_JoinStyle style)
    {
    }
    Ark_drawing_JoinStyle GetJoinStyleImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void SetCapStyleImpl(Ark_drawing_Pen peer,
                         Ark_drawing_CapStyle style)
    {
    }
    Ark_drawing_CapStyle GetCapStyleImpl(Ark_drawing_Pen peer)
    {
        return {};
    }
    void ResetImpl(Ark_drawing_Pen peer)
    {
    }
    Ark_Boolean GetFillPathImpl(Ark_drawing_Pen peer,
                                Ark_drawing_Path src,
                                Ark_drawing_Path dst)
    {
        return {};
    }
    } // drawing_PenAccessor
    namespace drawing_RegionAccessor {
    void DestroyPeerImpl(Ark_drawing_Region peer)
    {
        auto peerImpl = reinterpret_cast<drawing_RegionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Region ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean IsPointContainedImpl(Ark_drawing_Region peer,
                                     const Ark_Number* x,
                                     const Ark_Number* y)
    {
        return {};
    }
    Ark_Boolean IsRegionContainedImpl(Ark_drawing_Region peer,
                                      Ark_drawing_Region other)
    {
        return {};
    }
    Ark_Boolean OpImpl(Ark_drawing_Region peer,
                       Ark_drawing_Region region,
                       Ark_drawing_RegionOp regionOp)
    {
        return {};
    }
    Ark_Boolean QuickRejectImpl(Ark_drawing_Region peer,
                                const Ark_Number* left,
                                const Ark_Number* top,
                                const Ark_Number* right,
                                const Ark_Number* bottom)
    {
        return {};
    }
    Ark_Boolean SetPathImpl(Ark_drawing_Region peer,
                            Ark_drawing_Path path,
                            Ark_drawing_Region clip)
    {
        return {};
    }
    Ark_Boolean SetRectImpl(Ark_drawing_Region peer,
                            const Ark_Number* left,
                            const Ark_Number* top,
                            const Ark_Number* right,
                            const Ark_Number* bottom)
    {
        return {};
    }
    } // drawing_RegionAccessor
    namespace drawing_RoundRectAccessor {
    void DestroyPeerImpl(Ark_drawing_RoundRect peer)
    {
        auto peerImpl = reinterpret_cast<drawing_RoundRectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_RoundRect ConstructImpl(const Ark_common2D_Rect* rect,
                                        const Ark_Number* xRadii,
                                        const Ark_Number* yRadii)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetCornerImpl(Ark_drawing_RoundRect peer,
                       Ark_drawing_CornerPos pos,
                       const Ark_Number* x,
                       const Ark_Number* y)
    {
    }
    Ark_common2D_Point GetCornerImpl(Ark_drawing_RoundRect peer,
                                     Ark_drawing_CornerPos pos)
    {
        return {};
    }
    void OffsetImpl(Ark_drawing_RoundRect peer,
                    const Ark_Number* dx,
                    const Ark_Number* dy)
    {
    }
    } // drawing_RoundRectAccessor
    namespace drawing_SamplingOptionsAccessor {
    void DestroyPeerImpl(Ark_drawing_SamplingOptions peer)
    {
        auto peerImpl = reinterpret_cast<drawing_SamplingOptionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_SamplingOptions Construct0Impl()
    {
        return {};
    }
    Ark_drawing_SamplingOptions Construct1Impl(Ark_drawing_FilterMode filterMode)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // drawing_SamplingOptionsAccessor
    namespace drawing_ShaderEffectAccessor {
    void DestroyPeerImpl(Ark_drawing_ShaderEffect peer)
    {
        auto peerImpl = reinterpret_cast<drawing_ShaderEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_ShaderEffect ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_ShaderEffect CreateColorShaderImpl(const Ark_Number* color)
    {
        return {};
    }
    Ark_drawing_ShaderEffect CreateLinearGradientImpl(const Ark_common2D_Point* startPt,
                                                      const Ark_common2D_Point* endPt,
                                                      const Array_Number* colors,
                                                      Ark_drawing_TileMode mode,
                                                      const Opt_Array_Number* pos,
                                                      const Opt_drawing_Matrix* matrix)
    {
        return {};
    }
    Ark_drawing_ShaderEffect CreateRadialGradientImpl(const Ark_common2D_Point* centerPt,
                                                      const Ark_Number* radius,
                                                      const Array_Number* colors,
                                                      Ark_drawing_TileMode mode,
                                                      const Opt_Array_Number* pos,
                                                      const Opt_drawing_Matrix* matrix)
    {
        return {};
    }
    Ark_drawing_ShaderEffect CreateSweepGradientImpl(const Ark_common2D_Point* centerPt,
                                                     const Array_Number* colors,
                                                     Ark_drawing_TileMode mode,
                                                     const Ark_Number* startAngle,
                                                     const Ark_Number* endAngle,
                                                     const Opt_Array_Number* pos,
                                                     const Opt_drawing_Matrix* matrix)
    {
        return {};
    }
    Ark_drawing_ShaderEffect CreateConicalGradientImpl(const Ark_common2D_Point* startPt,
                                                       const Ark_Number* startRadius,
                                                       const Ark_common2D_Point* endPt,
                                                       const Ark_Number* endRadius,
                                                       const Array_Number* colors,
                                                       Ark_drawing_TileMode mode,
                                                       const Opt_Array_Number* pos,
                                                       const Opt_drawing_Matrix* matrix)
    {
        return {};
    }
    } // drawing_ShaderEffectAccessor
    namespace drawing_ShadowLayerAccessor {
    void DestroyPeerImpl(Ark_drawing_ShadowLayer peer)
    {
        auto peerImpl = reinterpret_cast<drawing_ShadowLayerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_ShadowLayer ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_ShadowLayer Create0Impl(const Ark_Number* blurRadius,
                                        const Ark_Number* x,
                                        const Ark_Number* y,
                                        const Ark_common2D_Color* color)
    {
        return {};
    }
    Ark_drawing_ShadowLayer Create1Impl(const Ark_Number* blurRadius,
                                        const Ark_Number* x,
                                        const Ark_Number* y,
                                        const Ark_Number* color)
    {
        return {};
    }
    } // drawing_ShadowLayerAccessor
    namespace drawing_TextBlobAccessor {
    void DestroyPeerImpl(Ark_drawing_TextBlob peer)
    {
        auto peerImpl = reinterpret_cast<drawing_TextBlobPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_TextBlob ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_TextBlob MakeFromStringImpl(const Ark_String* text,
                                            Ark_drawing_Font font,
                                            Ark_drawing_TextEncoding encoding)
    {
        return {};
    }
    Ark_drawing_TextBlob MakeFromPosTextImpl(const Ark_String* text,
                                             const Ark_Number* len,
                                             const Array_common2D_Point* points,
                                             Ark_drawing_Font font)
    {
        return {};
    }
    Ark_drawing_TextBlob MakeFromRunBufferImpl(const Array_drawing_TextBlobRunBuffer* pos,
                                               Ark_drawing_Font font,
                                               const Ark_common2D_Rect* bounds)
    {
        return {};
    }
    Ark_common2D_Rect BoundsImpl(Ark_drawing_TextBlob peer)
    {
        return {};
    }
    Ark_Number UniqueIDImpl(Ark_drawing_TextBlob peer)
    {
        return {};
    }
    } // drawing_TextBlobAccessor
    namespace drawing_TypefaceAccessor {
    void DestroyPeerImpl(Ark_drawing_Typeface peer)
    {
        auto peerImpl = reinterpret_cast<drawing_TypefacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_drawing_Typeface ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetFamilyNameImpl(Ark_drawing_Typeface peer)
    {
        return {};
    }
    Ark_drawing_Typeface MakeFromFileImpl(const Ark_String* filePath)
    {
        return {};
    }
    } // drawing_TypefaceAccessor
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
    namespace DrawModifierAccessor {
    void DestroyPeerImpl(Ark_DrawModifier peer)
    {
        auto peerImpl = reinterpret_cast<DrawModifierPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawModifier ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InvalidateImpl(Ark_DrawModifier peer)
    {
    }
    Callback_DrawContext_Void GetDrawBehind_callbackImpl(Ark_DrawModifier peer)
    {
        return {};
    }
    void SetDrawBehind_callbackImpl(Ark_DrawModifier peer,
                                    const Callback_DrawContext_Void* drawBehind_callback)
    {
    }
    Callback_DrawContext_Void GetDrawContent_callbackImpl(Ark_DrawModifier peer)
    {
        return {};
    }
    void SetDrawContent_callbackImpl(Ark_DrawModifier peer,
                                     const Callback_DrawContext_Void* drawContent_callback)
    {
    }
    } // DrawModifierAccessor
    namespace EllipseShapeAccessor {
    void DestroyPeerImpl(Ark_EllipseShape peer)
    {
        auto peerImpl = reinterpret_cast<EllipseShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EllipseShape ConstructImpl(const Opt_ShapeSize* options)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EllipseShape OffsetImpl(Ark_EllipseShape peer,
                                const Ark_Position* offset)
    {
        return {};
    }
    Ark_EllipseShape FillImpl(Ark_EllipseShape peer,
                              const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_EllipseShape PositionImpl(Ark_EllipseShape peer,
                                  const Ark_Position* position)
    {
        return {};
    }
    Ark_EllipseShape WidthImpl(Ark_EllipseShape peer,
                               const Ark_Length* width)
    {
        return {};
    }
    Ark_EllipseShape HeightImpl(Ark_EllipseShape peer,
                                const Ark_Length* height)
    {
        return {};
    }
    Ark_EllipseShape SizeImpl(Ark_EllipseShape peer,
                              const Ark_SizeOptions* size)
    {
        return {};
    }
    } // EllipseShapeAccessor
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
    Map_AxisModel_Number GetAxisMapImpl(Ark_FocusAxisEvent peer)
    {
        return {};
    }
    void SetAxisMapImpl(Ark_FocusAxisEvent peer,
                        const Map_AxisModel_Number* axisMap)
    {
    }
    Callback_Void GetStopPropagationImpl(Ark_FocusAxisEvent peer)
    {
        return {};
    }
    void SetStopPropagationImpl(Ark_FocusAxisEvent peer,
                                const Callback_Void* stopPropagation)
    {
    }
    } // FocusAxisEventAccessor
    namespace FocusControllerAccessor {
    void RequestFocusImpl(const Ark_String* key)
    {
    }
    } // FocusControllerAccessor
    namespace FrameNodeAccessor {
    void DestroyPeerImpl(Ark_FrameNode peer)
    {
        auto peerImpl = reinterpret_cast<FrameNodePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FrameNode ConstructImpl(Ark_UIContext uiContext)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean IsModifiableImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void AppendChildImpl(Ark_FrameNode peer,
                         Ark_FrameNode node)
    {
    }
    void InsertChildAfterImpl(Ark_FrameNode peer,
                              Ark_FrameNode child,
                              Ark_FrameNode sibling)
    {
    }
    void RemoveChildImpl(Ark_FrameNode peer,
                         Ark_FrameNode node)
    {
    }
    void ClearChildrenImpl(Ark_FrameNode peer)
    {
    }
    Ark_FrameNode GetChildImpl(Ark_FrameNode peer,
                               const Ark_Number* index,
                               const Ark_Number* expandMode)
    {
        return {};
    }
    Ark_FrameNode GetFirstChildImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetNextSiblingImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetParentImpl(Ark_FrameNode peer)
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
    Ark_Object GetInspectorInfoImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void InvalidateImpl(Ark_FrameNode peer)
    {
    }
    void DisposeTreeImpl(Ark_FrameNode peer)
    {
    }
    void SetCrossLanguageOptionsImpl(Ark_FrameNode peer,
                                     const Ark_CrossLanguageOptions* options)
    {
    }
    Ark_CrossLanguageOptions GetCrossLanguageOptionsImpl(Ark_FrameNode peer)
    {
        return {};
    }
    void SetMeasuredSizeImpl(Ark_FrameNode peer,
                             const Ark_Size* size)
    {
    }
    void SetLayoutPositionImpl(Ark_FrameNode peer,
                               const Ark_Position* position)
    {
    }
    void MeasureImpl(Ark_FrameNode peer,
                     const Ark_LayoutConstraint* constraint)
    {
    }
    void LayoutImpl(Ark_FrameNode peer,
                    const Ark_Position* position)
    {
    }
    void SetNeedsLayoutImpl(Ark_FrameNode peer)
    {
    }
    Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
    {
        return {};
    }
    Ark_Number GetIdByFrameNodeImpl(Ark_FrameNode peer,
                                    Ark_FrameNode node)
    {
        return {};
    }
    void MoveToImpl(Ark_FrameNode peer,
                    Ark_FrameNode targetParent,
                    const Ark_Number* index)
    {
    }
    Ark_Number GetFirstChildIndexWithoutExpandImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_Number GetLastChildIndexWithoutExpandImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetAttachedFrameNodeByIdImpl(const Ark_String* id)
    {
        return {};
    }
    Ark_FrameNode GetFrameNodeByIdImpl(const Ark_Number* id)
    {
        return {};
    }
    Ark_FrameNode GetFrameNodeByUniqueIdImpl(const Ark_Number* id)
    {
        return {};
    }
    void ReuseImpl(Ark_FrameNode peer)
    {
    }
    void RecycleImpl(Ark_FrameNode peer)
    {
    }
    Ark_NativePointer GetFrameNodePtrImpl(Ark_FrameNode node)
    {
        return {};
    }
    Ark_FrameNode CreateTypedFrameNodeImpl(const Ark_String* type)
    {
        return {};
    }
    } // FrameNodeAccessor
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
    Ark_Number GetOffsetXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetOffsetXImpl(Ark_GestureEvent peer,
                        const Ark_Number* offsetX)
    {
    }
    Ark_Number GetOffsetYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetOffsetYImpl(Ark_GestureEvent peer,
                        const Ark_Number* offsetY)
    {
    }
    Ark_Number GetAngleImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_GestureEvent peer,
                      const Ark_Number* angle)
    {
    }
    Ark_Number GetSpeedImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetSpeedImpl(Ark_GestureEvent peer,
                      const Ark_Number* speed)
    {
    }
    Ark_Number GetScaleImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetScaleImpl(Ark_GestureEvent peer,
                      const Ark_Number* scale)
    {
    }
    Ark_Number GetPinchCenterXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterXImpl(Ark_GestureEvent peer,
                             const Ark_Number* pinchCenterX)
    {
    }
    Ark_Number GetPinchCenterYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterYImpl(Ark_GestureEvent peer,
                             const Ark_Number* pinchCenterY)
    {
    }
    Ark_Number GetVelocityXImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityXImpl(Ark_GestureEvent peer,
                          const Ark_Number* velocityX)
    {
    }
    Ark_Number GetVelocityYImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityYImpl(Ark_GestureEvent peer,
                          const Ark_Number* velocityY)
    {
    }
    Ark_Number GetVelocityImpl(Ark_GestureEvent peer)
    {
        return {};
    }
    void SetVelocityImpl(Ark_GestureEvent peer,
                         const Ark_Number* velocity)
    {
    }
    } // GestureEventAccessor
    namespace GestureGroupInterfaceAccessor {
    void DestroyPeerImpl(Ark_GestureGroupInterface peer)
    {
        auto peerImpl = reinterpret_cast<GestureGroupInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureGroupInterface ConstructImpl(Ark_GestureMode mode,
                                            const Array_GestureType* gesture)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_GestureGroupInterface OnCancelImpl(Ark_GestureGroupInterface peer,
                                           const Callback_Void* event)
    {
        return {};
    }
    } // GestureGroupInterfaceAccessor
    namespace GestureModifierAccessor {
    void DestroyPeerImpl(Ark_GestureModifier peer)
    {
        auto peerImpl = reinterpret_cast<GestureModifierPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureModifier ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ApplyGestureImpl(Ark_GestureModifier peer,
                          const Ark_UIGestureEvent* event)
    {
    }
    } // GestureModifierAccessor
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
    Ark_Number GetFingerCountImpl(Ark_GestureRecognizer peer)
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
    void RegisterFontImpl(const Ark_FontOptions* options)
    {
    }
    Array_String GetSystemFontListImpl()
    {
        return {};
    }
    Ark_FontInfo GetFontByNameImpl(const Ark_String* fontName)
    {
        return {};
    }
    } // GlobalScope_ohos_fontAccessor
    namespace GlobalScope_ohos_measure_utilsAccessor {
    Ark_Number MeasureTextImpl(const Ark_MeasureOptions* options)
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
    Opt_Number GetXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_HoverEvent peer,
                  const Opt_Number* x)
    {
    }
    Opt_Number GetYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_HoverEvent peer,
                  const Opt_Number* y)
    {
    }
    Opt_Number GetWindowXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_HoverEvent peer,
                        const Opt_Number* windowX)
    {
    }
    Opt_Number GetWindowYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_HoverEvent peer,
                        const Opt_Number* windowY)
    {
    }
    Opt_Number GetDisplayXImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_HoverEvent peer,
                         const Opt_Number* displayX)
    {
    }
    Opt_Number GetDisplayYImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_HoverEvent peer,
                         const Opt_Number* displayY)
    {
    }
    Callback_Void GetStopPropagationImpl(Ark_HoverEvent peer)
    {
        return {};
    }
    void SetStopPropagationImpl(Ark_HoverEvent peer,
                                const Callback_Void* stopPropagation)
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
    namespace image_PixelMapAccessor {
    void DestroyPeerImpl(Ark_image_PixelMap peer)
    {
        auto peerImpl = reinterpret_cast<image_PixelMapPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_image_PixelMap ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReadPixelsToBufferSyncImpl(Ark_image_PixelMap peer,
                                    const Ark_Buffer* dst)
    {
    }
    void WriteBufferToPixelsImpl(Ark_image_PixelMap peer,
                                 const Ark_Buffer* src)
    {
    }
    Ark_Boolean GetIsEditableImpl(Ark_image_PixelMap peer)
    {
        return {};
    }
    Ark_Boolean GetIsStrideAlignmentImpl(Ark_image_PixelMap peer)
    {
        return {};
    }
    } // image_PixelMapAccessor
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
    Ark_ImageAttachment ConstructImpl(const Ark_Union_ImageAttachmentInterface_Opt_AttachmentType* value)
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
    Ark_Number GetHeightImpl(Ark_ImageData peer)
    {
        return {};
    }
    void SetHeightImpl(Ark_ImageData peer,
                       const Ark_Number* height)
    {
    }
    Ark_Number GetWidthImpl(Ark_ImageData peer)
    {
        return {};
    }
    void SetWidthImpl(Ark_ImageData peer,
                      const Ark_Number* width)
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
    Ark_Number GetKeyCodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetKeyCodeImpl(Ark_KeyEvent peer,
                        const Ark_Number* keyCode)
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
    Ark_Number GetDeviceIdImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetDeviceIdImpl(Ark_KeyEvent peer,
                         const Ark_Number* deviceId)
    {
    }
    Ark_Number GetMetaKeyImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetMetaKeyImpl(Ark_KeyEvent peer,
                        const Ark_Number* metaKey)
    {
    }
    Ark_Number GetTimestampImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetTimestampImpl(Ark_KeyEvent peer,
                          const Ark_Number* timestamp)
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
    Opt_Number GetUnicodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetUnicodeImpl(Ark_KeyEvent peer,
                        const Opt_Number* unicode)
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
    Ark_DirectionalEdgesT GetMarginImpl(Ark_Layoutable peer)
    {
        return {};
    }
    Ark_DirectionalEdgesT GetPaddingImpl(Ark_Layoutable peer)
    {
        return {};
    }
    Ark_DirectionalEdgesT GetBorderWidthImpl(Ark_Layoutable peer)
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
    namespace LayoutCallbackAccessor {
    void DestroyPeerImpl(Ark_LayoutCallback peer)
    {
        auto peerImpl = reinterpret_cast<LayoutCallbackPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayoutCallback ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OnPlaceChildrenImpl(Ark_LayoutCallback peer,
                             const Ark_GeometryInfo* selfLayoutInfo,
                             const Array_Layoutable* children,
                             const Ark_ConstraintSizeOptions* constraint)
    {
    }
    Ark_SizeResult OnMeasureSizeImpl(Ark_LayoutCallback peer,
                                     const Ark_GeometryInfo* selfLayoutInfo,
                                     const Array_Measurable* children,
                                     const Ark_ConstraintSizeOptions* constraint)
    {
        return {};
    }
    } // LayoutCallbackAccessor
    namespace LayoutChildAccessor {
    void DestroyPeerImpl(Ark_LayoutChild peer)
    {
        auto peerImpl = reinterpret_cast<LayoutChildPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayoutChild ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void MeasureImpl(Ark_LayoutChild peer,
                     const Ark_ConstraintSizeOptions* childConstraint)
    {
    }
    Ark_String GetNameImpl(Ark_LayoutChild peer)
    {
        return {};
    }
    void SetNameImpl(Ark_LayoutChild peer,
                     const Ark_String* name)
    {
    }
    Ark_String GetIdImpl(Ark_LayoutChild peer)
    {
        return {};
    }
    void SetIdImpl(Ark_LayoutChild peer,
                   const Ark_String* id)
    {
    }
    Ark_Position GetPositionImpl(Ark_LayoutChild peer)
    {
        return {};
    }
    void SetPositionImpl(Ark_LayoutChild peer,
                         const Ark_Position* position)
    {
    }
    } // LayoutChildAccessor
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
    Ark_Number GetLineCountImpl(Ark_LayoutManager peer)
    {
        return {};
    }
    Ark_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_LayoutManager peer,
                                                              const Ark_Number* x,
                                                              const Ark_Number* y)
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
    } // LayoutPolicyAccessor
    namespace LazyForEachOpsAccessor {
    void SyncImpl(Ark_NativePointer node,
                  Ark_Int32 totalCount,
                  const Callback_CreateItem* creator,
                  const Callback_RangeUpdate* updater)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // LazyForEachOpsAccessor
    namespace LengthMetricsAccessor {
    void DestroyPeerImpl(Ark_LengthMetrics peer)
    {
        auto peerImpl = reinterpret_cast<LengthMetricsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LengthMetrics ConstructImpl(const Ark_Number* value,
                                    Ark_LengthUnit unit)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_LengthMetrics PxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_LengthMetrics VpImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_LengthMetrics FpImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_LengthMetrics PercentImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_LengthMetrics LpxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_LengthMetrics ResourceImpl(const Ark_Resource* value)
    {
        return {};
    }
    Ark_LengthUnit GetUnitImpl(Ark_LengthMetrics peer)
    {
        return {};
    }
    void SetUnitImpl(Ark_LengthMetrics peer,
                     Ark_LengthUnit unit)
    {
    }
    Ark_Number GetValueImpl(Ark_LengthMetrics peer)
    {
        return {};
    }
    void SetValueImpl(Ark_LengthMetrics peer,
                      const Ark_Number* value)
    {
    }
    } // LengthMetricsAccessor
    namespace LetterSpacingStyleAccessor {
    void DestroyPeerImpl(Ark_LetterSpacingStyle peer)
    {
        auto peerImpl = reinterpret_cast<LetterSpacingStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LetterSpacingStyle ConstructImpl(Ark_LengthMetrics value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetLetterSpacingImpl(Ark_LetterSpacingStyle peer)
    {
        return {};
    }
    } // LetterSpacingStyleAccessor
    namespace LevelOrderAccessor {
    void DestroyPeerImpl(Ark_LevelOrder peer)
    {
        auto peerImpl = reinterpret_cast<LevelOrderPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LevelOrder ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_LevelOrder ClampImpl(const Ark_Number* order)
    {
        return {};
    }
    Ark_Number GetOrderImpl(Ark_LevelOrder peer)
    {
        return {};
    }
    } // LevelOrderAccessor
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
    Ark_LineHeightStyle ConstructImpl(Ark_LengthMetrics lineHeight)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetLineHeightImpl(Ark_LineHeightStyle peer)
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
    Ark_RectResult GetItemRectInGroupImpl(Ark_ListScroller peer,
                                          const Ark_Number* index,
                                          const Ark_Number* indexInGroup)
    {
        return {};
    }
    void ScrollToItemInGroupImpl(Ark_ListScroller peer,
                                 const Ark_Number* index,
                                 const Ark_Number* indexInGroup,
                                 const Opt_Boolean* smooth,
                                 const Opt_ScrollAlign* align)
    {
    }
    void CloseAllSwipeActionsImpl(Ark_ListScroller peer,
                                  const Opt_CloseSwipeActionOptions* options)
    {
    }
    Ark_VisibleListContentInfo GetVisibleListContentInfoImpl(Ark_ListScroller peer,
                                                             const Ark_Number* x,
                                                             const Ark_Number* y)
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
    namespace LongPressGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_LongPressGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<LongPressGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LongPressGestureInterface ConstructImpl(const Ark_LongPressGestureInterface_Invoke_Literal* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_LongPressGestureInterface OnActionImpl(Ark_LongPressGestureInterface peer,
                                               const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_LongPressGestureInterface OnActionEndImpl(Ark_LongPressGestureInterface peer,
                                                  const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_LongPressGestureInterface OnActionCancel0Impl(Ark_LongPressGestureInterface peer,
                                                      const Callback_Void* event)
    {
        return {};
    }
    Ark_LongPressGestureInterface OnActionCancel1Impl(Ark_LongPressGestureInterface peer,
                                                      const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    } // LongPressGestureInterfaceAccessor
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
    Ark_Number GetDurationImpl(Ark_LongPressRecognizer peer)
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
    Opt_Number GetRotateYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetRotateYImpl(Ark_Matrix2D peer,
                        const Opt_Number* rotateY)
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
    Opt_Number GetScaleYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetScaleYImpl(Ark_Matrix2D peer,
                       const Opt_Number* scaleY)
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
    namespace matrix4_Matrix4TransitAccessor {
    void DestroyPeerImpl(Ark_matrix4_Matrix4Transit peer)
    {
        auto peerImpl = reinterpret_cast<matrix4_Matrix4TransitPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_matrix4_Matrix4Transit ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_matrix4_Matrix4Transit CopyImpl(Ark_matrix4_Matrix4Transit peer)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit InvertImpl(Ark_matrix4_Matrix4Transit peer)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit CombineImpl(Ark_matrix4_Matrix4Transit peer,
                                           Ark_matrix4_Matrix4Transit options)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit TranslateImpl(Ark_matrix4_Matrix4Transit peer,
                                             const Ark_TranslateOptions* options)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit ScaleImpl(Ark_matrix4_Matrix4Transit peer,
                                         const Ark_ScaleOptions* options)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit SkewImpl(Ark_matrix4_Matrix4Transit peer,
                                        const Ark_Number* x,
                                        const Ark_Number* y)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit RotateImpl(Ark_matrix4_Matrix4Transit peer,
                                          const Ark_RotateOptions* options)
    {
        return {};
    }
    Ark_matrix4_Matrix4TransformPoint TransformPointImpl(Ark_matrix4_Matrix4Transit peer,
                                                         const Ark_matrix4_Matrix4TransformPoint* options)
    {
        return {};
    }
    Ark_matrix4_Matrix4Transit SetPolyToPolyImpl(Ark_matrix4_Matrix4Transit peer,
                                                 const Ark_matrix4_PolyToPolyOptions* options)
    {
        return {};
    }
    } // matrix4_Matrix4TransitAccessor
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
    Ark_MeasureResult MeasureImpl(Ark_Measurable peer,
                                  const Ark_ConstraintSizeOptions* constraint)
    {
        return {};
    }
    Ark_DirectionalEdgesT GetMarginImpl(Ark_Measurable peer)
    {
        return {};
    }
    Ark_DirectionalEdgesT GetPaddingImpl(Ark_Measurable peer)
    {
        return {};
    }
    Ark_DirectionalEdgesT GetBorderWidthImpl(Ark_Measurable peer)
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
    Ark_Number GetDisplayXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetDisplayXImpl(Ark_MouseEvent peer,
                         const Ark_Number* displayX)
    {
    }
    Ark_Number GetDisplayYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetDisplayYImpl(Ark_MouseEvent peer,
                         const Ark_Number* displayY)
    {
    }
    Ark_Number GetWindowXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetWindowXImpl(Ark_MouseEvent peer,
                        const Ark_Number* windowX)
    {
    }
    Ark_Number GetWindowYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetWindowYImpl(Ark_MouseEvent peer,
                        const Ark_Number* windowY)
    {
    }
    Ark_Number GetXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetXImpl(Ark_MouseEvent peer,
                  const Ark_Number* x)
    {
    }
    Ark_Number GetYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetYImpl(Ark_MouseEvent peer,
                  const Ark_Number* y)
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
    Opt_Number GetRawDeltaXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetRawDeltaXImpl(Ark_MouseEvent peer,
                          const Opt_Number* rawDeltaX)
    {
    }
    Opt_Number GetRawDeltaYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetRawDeltaYImpl(Ark_MouseEvent peer,
                          const Opt_Number* rawDeltaY)
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
                           const Ark_Number* start,
                           const Ark_Number* length,
                           const Ark_String* other)
    {
    }
    void InsertStringImpl(Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_String* other)
    {
    }
    void RemoveStringImpl(Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_Number* length)
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
                         const Ark_Number* start,
                         const Ark_Number* length,
                         Ark_StyledStringKey styledKey)
    {
    }
    void RemoveStylesImpl(Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_Number* length)
    {
    }
    void ClearStylesImpl(Ark_MutableStyledString peer)
    {
    }
    void ReplaceStyledStringImpl(Ark_MutableStyledString peer,
                                 const Ark_Number* start,
                                 const Ark_Number* length,
                                 Ark_StyledString other)
    {
    }
    void InsertStyledStringImpl(Ark_MutableStyledString peer,
                                const Ark_Number* start,
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
    namespace NodeContentAccessor {
    void DestroyPeerImpl(Ark_NodeContent peer)
    {
        auto peerImpl = reinterpret_cast<NodeContentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NodeContent ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void AddFrameNodeImpl(Ark_NodeContent peer,
                          Ark_FrameNode node)
    {
    }
    void RemoveFrameNodeImpl(Ark_NodeContent peer,
                             Ark_FrameNode node)
    {
    }
    } // NodeContentAccessor
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
    namespace PageLifeCycleAccessor {
    void DestroyPeerImpl(Ark_PageLifeCycle peer)
    {
        auto peerImpl = reinterpret_cast<PageLifeCyclePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PageLifeCycle ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OnPageShowImpl(Ark_PageLifeCycle peer)
    {
    }
    void OnPageHideImpl(Ark_PageLifeCycle peer)
    {
    }
    Ark_Boolean OnBackPressImpl(Ark_PageLifeCycle peer)
    {
        return {};
    }
    void PageTransitionImpl(Ark_PageLifeCycle peer)
    {
    }
    void OnNewParamImpl(Ark_PageLifeCycle peer,
                        const Opt_Object* param)
    {
    }
    } // PageLifeCycleAccessor
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
    Ark_Number GetOffsetXImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetOffsetXImpl(Ark_PanGestureEvent peer,
                        const Ark_Number* offsetX)
    {
    }
    Ark_Number GetOffsetYImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetOffsetYImpl(Ark_PanGestureEvent peer,
                        const Ark_Number* offsetY)
    {
    }
    Ark_Number GetVelocityXImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityXImpl(Ark_PanGestureEvent peer,
                          const Ark_Number* velocityX)
    {
    }
    Ark_Number GetVelocityYImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityYImpl(Ark_PanGestureEvent peer,
                          const Ark_Number* velocityY)
    {
    }
    Ark_Number GetVelocityImpl(Ark_PanGestureEvent peer)
    {
        return {};
    }
    void SetVelocityImpl(Ark_PanGestureEvent peer,
                         const Ark_Number* velocity)
    {
    }
    } // PanGestureEventAccessor
    namespace PanGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_PanGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureInterface ConstructImpl(const Ark_Union_PanGestureInterface_Invoke_Literal_PanGestureOptions* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PanGestureInterface OnActionStartImpl(Ark_PanGestureInterface peer,
                                              const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PanGestureInterface OnActionUpdateImpl(Ark_PanGestureInterface peer,
                                               const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PanGestureInterface OnActionEndImpl(Ark_PanGestureInterface peer,
                                            const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PanGestureInterface OnActionCancel0Impl(Ark_PanGestureInterface peer,
                                                const Callback_Void* event)
    {
        return {};
    }
    Ark_PanGestureInterface OnActionCancel1Impl(Ark_PanGestureInterface peer,
                                                const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    } // PanGestureInterfaceAccessor
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
                         const Ark_Number* value)
    {
    }
    void SetFingersImpl(Ark_PanGestureOptions peer,
                        const Ark_Number* value)
    {
    }
    Ark_PanDirection GetDirectionImpl(Ark_PanGestureOptions peer)
    {
        return {};
    }
    Ark_Number GetDistanceImpl(Ark_PanGestureOptions peer)
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
    Opt_Number GetTextIndentImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Number GetMaxLinesImpl(Ark_ParagraphStyle peer)
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
    Opt_Union_Number_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Opt_Number GetParagraphSpacingImpl(Ark_ParagraphStyle peer)
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
    namespace PathShapeAccessor {
    void DestroyPeerImpl(Ark_PathShape peer)
    {
        auto peerImpl = reinterpret_cast<PathShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PathShape ConstructImpl(const Opt_PathShapeOptions* options)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PathShape OffsetImpl(Ark_PathShape peer,
                             const Ark_Position* offset)
    {
        return {};
    }
    Ark_PathShape FillImpl(Ark_PathShape peer,
                           const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_PathShape PositionImpl(Ark_PathShape peer,
                               const Ark_Position* position)
    {
        return {};
    }
    Ark_PathShape CommandsImpl(Ark_PathShape peer,
                               const Ark_String* commands)
    {
        return {};
    }
    } // PathShapeAccessor
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
    Ark_Number GetScaleImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetScaleImpl(Ark_PinchGestureEvent peer,
                      const Ark_Number* scale)
    {
    }
    Ark_Number GetPinchCenterXImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterXImpl(Ark_PinchGestureEvent peer,
                             const Ark_Number* pinchCenterX)
    {
    }
    Ark_Number GetPinchCenterYImpl(Ark_PinchGestureEvent peer)
    {
        return {};
    }
    void SetPinchCenterYImpl(Ark_PinchGestureEvent peer,
                             const Ark_Number* pinchCenterY)
    {
    }
    } // PinchGestureEventAccessor
    namespace PinchGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_PinchGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<PinchGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PinchGestureInterface ConstructImpl(const Ark_PinchGestureInterface_Invoke_Literal* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PinchGestureInterface OnActionStartImpl(Ark_PinchGestureInterface peer,
                                                const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PinchGestureInterface OnActionUpdateImpl(Ark_PinchGestureInterface peer,
                                                 const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PinchGestureInterface OnActionEndImpl(Ark_PinchGestureInterface peer,
                                              const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_PinchGestureInterface OnActionCancel0Impl(Ark_PinchGestureInterface peer,
                                                  const Callback_Void* event)
    {
        return {};
    }
    Ark_PinchGestureInterface OnActionCancel1Impl(Ark_PinchGestureInterface peer,
                                                  const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    } // PinchGestureInterfaceAccessor
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
    Ark_Number GetDistanceImpl(Ark_PinchRecognizer peer)
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
    Ark_ProgressMask ConstructImpl(const Ark_Number* value,
                                   const Ark_Number* total,
                                   const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void UpdateProgressImpl(Ark_ProgressMask peer,
                            const Ark_Number* value)
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
    namespace PromptActionAccessor {
    void DestroyPeerImpl(Ark_PromptAction peer)
    {
        auto peerImpl = reinterpret_cast<PromptActionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PromptAction ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OpenPopupImpl(Ark_VMContext vmContext,
                       Ark_AsyncWorkerPtr asyncWorker,
                       Ark_PromptAction peer,
                       Ark_ComponentContent content,
                       const Ark_TargetInfo* target,
                       const Opt_PopupCommonOptions* options,
                       const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpatePopupImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_PromptAction peer,
                        Ark_ComponentContent content,
                        const Ark_PopupCommonOptions* options,
                        const Opt_Boolean* partialUpdate,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ClosePopupImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_PromptAction peer,
                        Ark_ComponentContent content,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void OpenMenuImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_PromptAction peer,
                      Ark_ComponentContent content,
                      const Ark_TargetInfo* target,
                      const Opt_MenuOptions* options,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpdateMenuImpl(Ark_VMContext vmContext,
                        Ark_AsyncWorkerPtr asyncWorker,
                        Ark_PromptAction peer,
                        Ark_ComponentContent content,
                        const Ark_MenuOptions* options,
                        const Opt_Boolean* partialUpdate,
                        const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void CloseMenuImpl(Ark_VMContext vmContext,
                       Ark_AsyncWorkerPtr asyncWorker,
                       Ark_PromptAction peer,
                       Ark_ComponentContent content,
                       const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    } // PromptActionAccessor
    namespace RectShapeAccessor {
    void DestroyPeerImpl(Ark_RectShape peer)
    {
        auto peerImpl = reinterpret_cast<RectShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RectShape ConstructImpl(const Opt_Union_RectShapeOptions_RoundRectShapeOptions* options)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_RectShape OffsetImpl(Ark_RectShape peer,
                             const Ark_Position* offset)
    {
        return {};
    }
    Ark_RectShape FillImpl(Ark_RectShape peer,
                           const Ark_ResourceColor* color)
    {
        return {};
    }
    Ark_RectShape PositionImpl(Ark_RectShape peer,
                               const Ark_Position* position)
    {
        return {};
    }
    Ark_RectShape WidthImpl(Ark_RectShape peer,
                            const Ark_Length* width)
    {
        return {};
    }
    Ark_RectShape HeightImpl(Ark_RectShape peer,
                             const Ark_Length* height)
    {
        return {};
    }
    Ark_RectShape SizeImpl(Ark_RectShape peer,
                           const Ark_SizeOptions* size)
    {
        return {};
    }
    Ark_RectShape RadiusWidthImpl(Ark_RectShape peer,
                                  const Ark_Union_Number_String* rWidth)
    {
        return {};
    }
    Ark_RectShape RadiusHeightImpl(Ark_RectShape peer,
                                   const Ark_Union_Number_String* rHeight)
    {
        return {};
    }
    Ark_RectShape RadiusImpl(Ark_RectShape peer,
                             const Ark_Union_Number_String_Array_Union_Number_String* radius)
    {
        return {};
    }
    } // RectShapeAccessor
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
    namespace RenderNodeAccessor {
    void DestroyPeerImpl(Ark_RenderNode peer)
    {
        auto peerImpl = reinterpret_cast<RenderNodePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RenderNode ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void AppendChildImpl(Ark_RenderNode peer,
                         Ark_RenderNode node)
    {
    }
    void InsertChildAfterImpl(Ark_RenderNode peer,
                              Ark_RenderNode child,
                              const Opt_RenderNode* sibling)
    {
    }
    void RemoveChildImpl(Ark_RenderNode peer,
                         Ark_RenderNode node)
    {
    }
    void ClearChildrenImpl(Ark_RenderNode peer)
    {
    }
    Opt_RenderNode GetChildImpl(Ark_RenderNode peer,
                                const Ark_Number* index)
    {
        return {};
    }
    Opt_RenderNode GetFirstChildImpl(Ark_RenderNode peer)
    {
        return {};
    }
    Opt_RenderNode GetNextSiblingImpl(Ark_RenderNode peer)
    {
        return {};
    }
    Opt_RenderNode GetPreviousSiblingImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void DrawImpl(Ark_RenderNode peer,
                  Ark_DrawContext context)
    {
    }
    void InvalidateImpl(Ark_RenderNode peer)
    {
    }
    void DisposeImpl(Ark_RenderNode peer)
    {
    }
    Ark_Number GetBackgroundColorImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetBackgroundColorImpl(Ark_RenderNode peer,
                                const Ark_Number* backgroundColor)
    {
    }
    Ark_Boolean GetClipToFrameImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetClipToFrameImpl(Ark_RenderNode peer,
                            Ark_Boolean clipToFrame)
    {
    }
    Ark_Number GetOpacityImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetOpacityImpl(Ark_RenderNode peer,
                        const Ark_Number* opacity)
    {
    }
    Ark_Size GetSizeImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetSizeImpl(Ark_RenderNode peer,
                     const Ark_Size* size)
    {
    }
    Ark_Vector2 GetPositionImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetPositionImpl(Ark_RenderNode peer,
                         const Ark_Vector2* position)
    {
    }
    Ark_Frame GetFrameImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetFrameImpl(Ark_RenderNode peer,
                      const Ark_Frame* frame)
    {
    }
    Ark_Vector2 GetPivotImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetPivotImpl(Ark_RenderNode peer,
                      const Ark_Vector2* pivot)
    {
    }
    Ark_Vector2 GetScaleImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetScaleImpl(Ark_RenderNode peer,
                      const Ark_Vector2* scale)
    {
    }
    Ark_Vector2 GetTranslationImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetTranslationImpl(Ark_RenderNode peer,
                            const Ark_Vector2* translation)
    {
    }
    Ark_Vector3 GetRotationImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetRotationImpl(Ark_RenderNode peer,
                         const Ark_Vector3* rotation)
    {
    }
    Ark_Matrix4 GetTransformImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetTransformImpl(Ark_RenderNode peer,
                          const Ark_Matrix4* transform)
    {
    }
    Ark_Number GetShadowColorImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShadowColorImpl(Ark_RenderNode peer,
                            const Ark_Number* shadowColor)
    {
    }
    Ark_Vector2 GetShadowOffsetImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShadowOffsetImpl(Ark_RenderNode peer,
                             const Ark_Vector2* shadowOffset)
    {
    }
    Ark_String GetLabelImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetLabelImpl(Ark_RenderNode peer,
                      const Ark_String* label)
    {
    }
    Ark_Number GetShadowAlphaImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShadowAlphaImpl(Ark_RenderNode peer,
                            const Ark_Number* shadowAlpha)
    {
    }
    Ark_Number GetShadowElevationImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShadowElevationImpl(Ark_RenderNode peer,
                                const Ark_Number* shadowElevation)
    {
    }
    Ark_Number GetShadowRadiusImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShadowRadiusImpl(Ark_RenderNode peer,
                             const Ark_Number* shadowRadius)
    {
    }
    Ark_EdgeStyles GetBorderStyleImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetBorderStyleImpl(Ark_RenderNode peer,
                            const Ark_EdgeStyles* borderStyle)
    {
    }
    Ark_Edges GetBorderWidthImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetBorderWidthImpl(Ark_RenderNode peer,
                            const Ark_Edges* borderWidth)
    {
    }
    Ark_Edges GetBorderColorImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetBorderColorImpl(Ark_RenderNode peer,
                            const Ark_Edges* borderColor)
    {
    }
    Ark_BorderRadiuses_graphics GetBorderRadiusImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetBorderRadiusImpl(Ark_RenderNode peer,
                             const Ark_BorderRadiuses_graphics* borderRadius)
    {
    }
    Ark_ShapeMask GetShapeMaskImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShapeMaskImpl(Ark_RenderNode peer,
                          Ark_ShapeMask shapeMask)
    {
    }
    Ark_ShapeClip GetShapeClipImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetShapeClipImpl(Ark_RenderNode peer,
                          Ark_ShapeClip shapeClip)
    {
    }
    Ark_Boolean GetMarkNodeGroupImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetMarkNodeGroupImpl(Ark_RenderNode peer,
                              Ark_Boolean markNodeGroup)
    {
    }
    Ark_LengthMetricsUnit GetLengthMetricsUnitImpl(Ark_RenderNode peer)
    {
        return {};
    }
    void SetLengthMetricsUnitImpl(Ark_RenderNode peer,
                                  Ark_LengthMetricsUnit lengthMetricsUnit)
    {
    }
    } // RenderNodeAccessor
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
                const Ark_WorkerEventListener* listener)
    {
    }
    void OnceImpl(Ark_VMContext vmContext,
                  Ark_RestrictedWorker peer,
                  const Ark_String* Type,
                  const Ark_WorkerEventListener* listener)
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
                              const Ark_WorkerEventListener* listener)
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
    Ark_Number GetCaretOffsetImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Ark_Boolean SetCaretOffsetImpl(Ark_RichEditorBaseController peer,
                                   const Ark_Number* offset)
    {
        return {};
    }
    void CloseSelectionMenuImpl(Ark_RichEditorBaseController peer)
    {
    }
    Ark_RichEditorTextStyle GetTypingStyleImpl(Ark_RichEditorBaseController peer)
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
    Ark_Boolean IsEditingImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    void StopEditingImpl(Ark_RichEditorBaseController peer)
    {
    }
    Ark_LayoutManager GetLayoutManagerImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Ark_PreviewText GetPreviewTextImpl(Ark_RichEditorBaseController peer)
    {
        return {};
    }
    Opt_RectResult GetCaretRectImpl(Ark_RichEditorBaseController peer)
    {
        return {};
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
    Ark_Number AddTextSpanImpl(Ark_RichEditorController peer,
                               const Ark_ResourceStr* content,
                               const Opt_RichEditorTextSpanOptions* options)
    {
        return {};
    }
    Ark_Number AddImageSpanImpl(Ark_RichEditorController peer,
                                const Ark_Union_PixelMap_ResourceStr* value,
                                const Opt_RichEditorImageSpanOptions* options)
    {
        return {};
    }
    Ark_Number AddBuilderSpanImpl(Ark_RichEditorController peer,
                                  const CustomNodeBuilder* value,
                                  const Opt_RichEditorBuilderSpanOptions* options)
    {
        return {};
    }
    Ark_Number AddSymbolSpanImpl(Ark_RichEditorController peer,
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
    Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult GetSpansImpl(Ark_RichEditorController peer,
                                                                                const Opt_RichEditorRange* value)
    {
        return {};
    }
    Array_RichEditorParagraphResult GetParagraphsImpl(Ark_RichEditorController peer,
                                                      const Opt_RichEditorRange* value)
    {
        return {};
    }
    Ark_RichEditorSelection GetSelectionImpl(Ark_RichEditorController peer)
    {
        return {};
    }
    Array_RichEditorSpan FromStyledStringImpl(Ark_RichEditorController peer,
                                              Ark_StyledString value)
    {
        return {};
    }
    Ark_StyledString ToStyledStringImpl(Ark_RichEditorController peer,
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
    Ark_MutableStyledString GetStyledStringImpl(Ark_RichEditorStyledStringController peer)
    {
        return {};
    }
    Ark_RichEditorRange GetSelectionImpl(Ark_RichEditorStyledStringController peer)
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
    Ark_Number GetAngleImpl(Ark_RotationGestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_RotationGestureEvent peer,
                      const Ark_Number* angle)
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
    Ark_Number GetAngleImpl(Ark_RotationRecognizer peer)
    {
        return {};
    }
    } // RotationRecognizerAccessor
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
    namespace SceneAccessor {
    void DestroyPeerImpl(Ark_Scene peer)
    {
        auto peerImpl = reinterpret_cast<ScenePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Scene ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void LoadImpl(Ark_VMContext vmContext,
                  Ark_AsyncWorkerPtr asyncWorker,
                  const Opt_ResourceStr* uri,
                  const Callback_Opt_Scene_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void DestroyImpl(Ark_Scene peer)
    {
    }
    } // SceneAccessor
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
    void ScrollToImpl(Ark_Scroller peer,
                      const Ark_ScrollOptions* options)
    {
    }
    void ScrollEdgeImpl(Ark_Scroller peer,
                        Ark_Edge value,
                        const Opt_ScrollEdgeOptions* options)
    {
    }
    void FlingImpl(Ark_Scroller peer,
                   const Ark_Number* velocity)
    {
    }
    void ScrollPageImpl(Ark_Scroller peer,
                        const Ark_ScrollPageOptions* value)
    {
    }
    Ark_OffsetResult CurrentOffsetImpl(Ark_Scroller peer)
    {
        return {};
    }
    void ScrollToIndexImpl(Ark_Scroller peer,
                           const Ark_Number* value,
                           const Opt_Boolean* smooth,
                           const Opt_ScrollAlign* align,
                           const Opt_ScrollToIndexOptions* options)
    {
    }
    void ScrollByImpl(Ark_Scroller peer,
                      const Ark_Length* dx,
                      const Ark_Length* dy)
    {
    }
    Ark_Boolean IsAtEndImpl(Ark_Scroller peer)
    {
        return {};
    }
    Ark_RectResult GetItemRectImpl(Ark_Scroller peer,
                                   const Ark_Number* index)
    {
        return {};
    }
    Ark_Number GetItemIndexImpl(Ark_Scroller peer,
                                const Ark_Number* x,
                                const Ark_Number* y)
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
    Ark_Number GetOffsetRemainImpl(Ark_ScrollResult peer)
    {
        return {};
    }
    void SetOffsetRemainImpl(Ark_ScrollResult peer,
                             const Ark_Number* offsetRemain)
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
                           const Ark_Number* value)
    {
    }
    void StopEditingImpl(Ark_SearchController peer)
    {
    }
    void SetTextSelectionImpl(Ark_SearchController peer,
                              const Ark_Number* selectionStart,
                              const Ark_Number* selectionEnd,
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
    namespace ShapeClipAccessor {
    void DestroyPeerImpl(Ark_ShapeClip peer)
    {
        auto peerImpl = reinterpret_cast<ShapeClipPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ShapeClip ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetRectShapeImpl(Ark_ShapeClip peer,
                          const Ark_common2D_Rect* rect)
    {
    }
    void SetRoundRectShapeImpl(Ark_ShapeClip peer,
                               const Ark_RoundRect* roundRect)
    {
    }
    void SetCircleShapeImpl(Ark_ShapeClip peer,
                            const Ark_Circle* circle)
    {
    }
    void SetOvalShapeImpl(Ark_ShapeClip peer,
                          const Ark_common2D_Rect* oval)
    {
    }
    void SetCommandPathImpl(Ark_ShapeClip peer,
                            const Ark_CommandPath* path)
    {
    }
    } // ShapeClipAccessor
    namespace ShapeMaskAccessor {
    void DestroyPeerImpl(Ark_ShapeMask peer)
    {
        auto peerImpl = reinterpret_cast<ShapeMaskPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ShapeMask ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetRectShapeImpl(Ark_ShapeMask peer,
                          const Ark_common2D_Rect* rect)
    {
    }
    void SetRoundRectShapeImpl(Ark_ShapeMask peer,
                               const Ark_RoundRect* roundRect)
    {
    }
    void SetCircleShapeImpl(Ark_ShapeMask peer,
                            const Ark_Circle* circle)
    {
    }
    void SetOvalShapeImpl(Ark_ShapeMask peer,
                          const Ark_common2D_Rect* oval)
    {
    }
    void SetCommandPathImpl(Ark_ShapeMask peer,
                            const Ark_CommandPath* path)
    {
    }
    Ark_Number GetFillColorImpl(Ark_ShapeMask peer)
    {
        return {};
    }
    void SetFillColorImpl(Ark_ShapeMask peer,
                          const Ark_Number* fillColor)
    {
    }
    Ark_Number GetStrokeColorImpl(Ark_ShapeMask peer)
    {
        return {};
    }
    void SetStrokeColorImpl(Ark_ShapeMask peer,
                            const Ark_Number* strokeColor)
    {
    }
    Ark_Number GetStrokeWidthImpl(Ark_ShapeMask peer)
    {
        return {};
    }
    void SetStrokeWidthImpl(Ark_ShapeMask peer,
                            const Ark_Number* strokeWidth)
    {
    }
    } // ShapeMaskAccessor
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
    void HandleCancelImpl(Ark_SslErrorHandler peer)
    {
    }
    } // SslErrorHandlerAccessor
    namespace StateStylesOpsAccessor {
    void OnStateStyleChangeImpl(Ark_NativePointer node,
                                const Callback_StateStylesChange* stateStyleChange)
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
                                  const Ark_Number* start,
                                  const Ark_Number* length,
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
                                         const Ark_Number* start,
                                         const Opt_Number* length)
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
    Ark_Number GetLengthImpl(Ark_StyledString peer)
    {
        return {};
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
    Ark_MutableStyledString GetStyledStringImpl(Ark_StyledStringController peer)
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
    Ark_Number GetAngleImpl(Ark_SwipeGestureEvent peer)
    {
        return {};
    }
    void SetAngleImpl(Ark_SwipeGestureEvent peer,
                      const Ark_Number* angle)
    {
    }
    Ark_Number GetSpeedImpl(Ark_SwipeGestureEvent peer)
    {
        return {};
    }
    void SetSpeedImpl(Ark_SwipeGestureEvent peer,
                      const Ark_Number* speed)
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
    Ark_Number GetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetSelectedIndexImpl(Ark_SwiperContentTransitionProxy peer,
                              const Ark_Number* selectedIndex)
    {
    }
    Ark_Number GetIndexImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetIndexImpl(Ark_SwiperContentTransitionProxy peer,
                      const Ark_Number* index)
    {
    }
    Ark_Number GetPositionImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetPositionImpl(Ark_SwiperContentTransitionProxy peer,
                         const Ark_Number* position)
    {
    }
    Ark_Number GetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer)
    {
        return {};
    }
    void SetMainAxisLengthImpl(Ark_SwiperContentTransitionProxy peer,
                               const Ark_Number* mainAxisLength)
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
                         const Ark_Number* index,
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
    Ark_Number GetVelocityThresholdImpl(Ark_SwipeRecognizer peer)
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
                       const Ark_SymbolGlyphModifier* normal)
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
    Ark_Number GetFromImpl(Ark_TabContentTransitionProxy peer)
    {
        return {};
    }
    void SetFromImpl(Ark_TabContentTransitionProxy peer,
                     const Ark_Number* from)
    {
    }
    Ark_Number GetToImpl(Ark_TabContentTransitionProxy peer)
    {
        return {};
    }
    void SetToImpl(Ark_TabContentTransitionProxy peer,
                   const Ark_Number* to)
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
                         const Ark_Number* value)
    {
    }
    void PreloadItemsImpl(Ark_VMContext vmContext,
                          Ark_AsyncWorkerPtr asyncWorker,
                          Ark_TabsController peer,
                          const Opt_Array_Number* indices,
                          const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void SetTabBarTranslateImpl(Ark_TabsController peer,
                                const Ark_TranslateOptions* translate)
    {
    }
    void SetTabBarOpacityImpl(Ark_TabsController peer,
                              const Ark_Number* opacity)
    {
    }
    } // TabsControllerAccessor
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
    } // TapGestureEventAccessor
    namespace TapGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_TapGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<TapGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TapGestureInterface ConstructImpl(const Ark_TapGestureParameters* value)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TapGestureInterface OnActionImpl(Ark_TapGestureInterface peer,
                                         const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    } // TapGestureInterfaceAccessor
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
    Ark_Number GetTapCountImpl(Ark_TapRecognizer peer)
    {
        return {};
    }
    } // TapRecognizerAccessor
    namespace text_FontCollectionAccessor {
    void DestroyPeerImpl(Ark_text_FontCollection peer)
    {
        auto peerImpl = reinterpret_cast<text_FontCollectionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_FontCollection ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_text_FontCollection GetGlobalInstanceImpl()
    {
        return {};
    }
    void LoadFontSyncImpl(Ark_text_FontCollection peer,
                          const Ark_String* name,
                          const Ark_Union_String_Resource* path)
    {
    }
    void LoadFontImpl(Ark_VMContext vmContext,
                      Ark_AsyncWorkerPtr asyncWorker,
                      Ark_text_FontCollection peer,
                      const Ark_String* name,
                      const Ark_Union_String_Resource* path,
                      const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ClearCachesImpl(Ark_text_FontCollection peer)
    {
    }
    } // text_FontCollectionAccessor
    namespace text_LineTypesetAccessor {
    void DestroyPeerImpl(Ark_text_LineTypeset peer)
    {
        auto peerImpl = reinterpret_cast<text_LineTypesetPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_LineTypeset ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetLineBreakImpl(Ark_text_LineTypeset peer,
                                const Ark_Number* startIndex,
                                const Ark_Number* width)
    {
        return {};
    }
    Ark_text_TextLine CreateLineImpl(Ark_text_LineTypeset peer,
                                     const Ark_Number* startIndex,
                                     const Ark_Number* count)
    {
        return {};
    }
    } // text_LineTypesetAccessor
    namespace text_ParagraphAccessor {
    void DestroyPeerImpl(Ark_text_Paragraph peer)
    {
        auto peerImpl = reinterpret_cast<text_ParagraphPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_Paragraph ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void LayoutSyncImpl(Ark_text_Paragraph peer,
                        const Ark_Number* width)
    {
    }
    void LayoutImpl(Ark_VMContext vmContext,
                    Ark_AsyncWorkerPtr asyncWorker,
                    Ark_text_Paragraph peer,
                    const Ark_Number* width,
                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PaintImpl(Ark_text_Paragraph peer,
                   Ark_drawing_Canvas canvas,
                   const Ark_Number* x,
                   const Ark_Number* y)
    {
    }
    void PaintOnPathImpl(Ark_text_Paragraph peer,
                         Ark_drawing_Canvas canvas,
                         Ark_drawing_Path path,
                         const Ark_Number* hOffset,
                         const Ark_Number* vOffset)
    {
    }
    Ark_Number GetMaxWidthImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetHeightImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetLongestLineImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetLongestLineWithIndentImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetMinIntrinsicWidthImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetMaxIntrinsicWidthImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetAlphabeticBaselineImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetIdeographicBaselineImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Array_text_TextBox GetRectsForRangeImpl(Ark_text_Paragraph peer,
                                            const Ark_text_Range* range,
                                            Ark_text_RectWidthStyle widthStyle,
                                            Ark_text_RectHeightStyle heightStyle)
    {
        return {};
    }
    Array_text_TextBox GetRectsForPlaceholdersImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_text_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_text_Paragraph peer,
                                                                   const Ark_Number* x,
                                                                   const Ark_Number* y)
    {
        return {};
    }
    Ark_text_Range GetWordBoundaryImpl(Ark_text_Paragraph peer,
                                       const Ark_Number* offset)
    {
        return {};
    }
    Ark_Number GetLineCountImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_Number GetLineHeightImpl(Ark_text_Paragraph peer,
                                 const Ark_Number* line)
    {
        return {};
    }
    Ark_Number GetLineWidthImpl(Ark_text_Paragraph peer,
                                const Ark_Number* line)
    {
        return {};
    }
    Ark_Boolean DidExceedMaxLinesImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Array_text_TextLine GetTextLinesImpl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Ark_text_Range GetActualTextRangeImpl(Ark_text_Paragraph peer,
                                          const Ark_Number* lineNumber,
                                          Ark_Boolean includeSpaces)
    {
        return {};
    }
    Array_text_LineMetrics GetLineMetrics0Impl(Ark_text_Paragraph peer)
    {
        return {};
    }
    Opt_text_LineMetrics GetLineMetrics1Impl(Ark_text_Paragraph peer,
                                             const Ark_Number* lineNumber)
    {
        return {};
    }
    } // text_ParagraphAccessor
    namespace text_ParagraphBuilderAccessor {
    void DestroyPeerImpl(Ark_text_ParagraphBuilder peer)
    {
        auto peerImpl = reinterpret_cast<text_ParagraphBuilderPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_ParagraphBuilder ConstructImpl(const Ark_text_ParagraphStyle* paragraphStyle,
                                            Ark_text_FontCollection fontCollection)
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void PushStyleImpl(Ark_text_ParagraphBuilder peer,
                       const Ark_text_TextStyle* textStyle)
    {
    }
    void PopStyleImpl(Ark_text_ParagraphBuilder peer)
    {
    }
    void AddTextImpl(Ark_text_ParagraphBuilder peer,
                     const Ark_String* text)
    {
    }
    void AddPlaceholderImpl(Ark_text_ParagraphBuilder peer,
                            const Ark_text_PlaceholderSpan* placeholderSpan)
    {
    }
    Ark_text_Paragraph BuildImpl(Ark_text_ParagraphBuilder peer)
    {
        return {};
    }
    Ark_text_LineTypeset BuildLineTypesetImpl(Ark_text_ParagraphBuilder peer)
    {
        return {};
    }
    void AddSymbolImpl(Ark_text_ParagraphBuilder peer,
                       const Ark_Number* symbolId)
    {
    }
    } // text_ParagraphBuilderAccessor
    namespace text_RunAccessor {
    void DestroyPeerImpl(Ark_text_Run peer)
    {
        auto peerImpl = reinterpret_cast<text_RunPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_Run ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetGlyphCountImpl(Ark_text_Run peer)
    {
        return {};
    }
    Array_Number GetGlyphs0Impl(Ark_text_Run peer)
    {
        return {};
    }
    Array_Number GetGlyphs1Impl(Ark_text_Run peer,
                                const Ark_text_Range* range)
    {
        return {};
    }
    Array_common2D_Point GetPositions0Impl(Ark_text_Run peer)
    {
        return {};
    }
    Array_common2D_Point GetPositions1Impl(Ark_text_Run peer,
                                           const Ark_text_Range* range)
    {
        return {};
    }
    Array_common2D_Point GetOffsetsImpl(Ark_text_Run peer)
    {
        return {};
    }
    Ark_drawing_Font GetFontImpl(Ark_text_Run peer)
    {
        return {};
    }
    void PaintImpl(Ark_text_Run peer,
                   Ark_drawing_Canvas canvas,
                   const Ark_Number* x,
                   const Ark_Number* y)
    {
    }
    Array_Number GetStringIndicesImpl(Ark_text_Run peer,
                                      const Ark_text_Range* range)
    {
        return {};
    }
    Ark_text_Range GetStringRangeImpl(Ark_text_Run peer)
    {
        return {};
    }
    Ark_text_TypographicBounds GetTypographicBoundsImpl(Ark_text_Run peer)
    {
        return {};
    }
    Ark_common2D_Rect GetImageBoundsImpl(Ark_text_Run peer)
    {
        return {};
    }
    } // text_RunAccessor
    namespace text_TextLineAccessor {
    void DestroyPeerImpl(Ark_text_TextLine peer)
    {
        auto peerImpl = reinterpret_cast<text_TextLinePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_text_TextLine ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number GetGlyphCountImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    Ark_text_Range GetTextRangeImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    Array_text_Run GetGlyphRunsImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    void PaintImpl(Ark_text_TextLine peer,
                   Ark_drawing_Canvas canvas,
                   const Ark_Number* x,
                   const Ark_Number* y)
    {
    }
    Ark_text_TextLine CreateTruncatedLineImpl(Ark_text_TextLine peer,
                                              const Ark_Number* width,
                                              Ark_text_EllipsisMode ellipsisMode,
                                              const Ark_String* ellipsis)
    {
        return {};
    }
    Ark_text_TypographicBounds GetTypographicBoundsImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    Ark_common2D_Rect GetImageBoundsImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    Ark_Number GetTrailingSpaceWidthImpl(Ark_text_TextLine peer)
    {
        return {};
    }
    Ark_Number GetStringIndexForPositionImpl(Ark_text_TextLine peer,
                                             const Ark_common2D_Point* point)
    {
        return {};
    }
    Ark_Number GetOffsetForStringIndexImpl(Ark_text_TextLine peer,
                                           const Ark_Number* index)
    {
        return {};
    }
    void EnumerateCaretOffsetsImpl(Ark_text_TextLine peer,
                                   const text_Callback_Number_Number_Boolean_Boolean* callback_)
    {
    }
    Ark_Number GetAlignmentOffsetImpl(Ark_text_TextLine peer,
                                      const Ark_Number* alignmentFactor,
                                      const Ark_Number* alignmentWidth)
    {
        return {};
    }
    } // text_TextLineAccessor
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
                           const Ark_Number* value)
    {
    }
    void SetTextSelectionImpl(Ark_TextAreaController peer,
                              const Ark_Number* selectionStart,
                              const Ark_Number* selectionEnd,
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
    Ark_LayoutManager GetLayoutManagerImpl(Ark_TextBaseController peer)
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
    Ark_Number GetTextContentLineCountImpl(Ark_TextContentControllerBase peer)
    {
        return {};
    }
    Ark_Number AddTextImpl(Ark_TextContentControllerBase peer,
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
    Ark_Boolean IsEditingImpl(Ark_TextEditControllerEx peer)
    {
        return {};
    }
    void StopEditingImpl(Ark_TextEditControllerEx peer)
    {
    }
    Ark_Boolean SetCaretOffsetImpl(Ark_TextEditControllerEx peer,
                                   const Ark_Number* offset)
    {
        return {};
    }
    Ark_Number GetCaretOffsetImpl(Ark_TextEditControllerEx peer)
    {
        return {};
    }
    Ark_PreviewText GetPreviewTextImpl(Ark_TextEditControllerEx peer)
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
                           const Ark_Number* value)
    {
    }
    void SetTextSelectionImpl(Ark_TextInputController peer,
                              const Ark_Number* selectionStart,
                              const Ark_Number* selectionEnd,
                              const Opt_SelectionOptions* options)
    {
    }
    void StopEditingImpl(Ark_TextInputController peer)
    {
    }
    } // TextInputControllerAccessor
    namespace TextMenuControllerAccessor {
    void DestroyPeerImpl(Ark_TextMenuController peer)
    {
        auto peerImpl = reinterpret_cast<TextMenuControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextMenuController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetMenuOptionsImpl(Ark_TextMenuController peer,
                            const Ark_TextMenuOptions* options)
    {
    }
    } // TextMenuControllerAccessor
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
    Opt_Number GetFontSizeImpl(Ark_TextStyle peer)
    {
        return {};
    }
    Opt_Number GetFontWeightImpl(Ark_TextStyle peer)
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
    namespace ThemeControlAccessor {
    void DestroyPeerImpl(Ark_ThemeControl peer)
    {
        auto peerImpl = reinterpret_cast<ThemeControlPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ThemeControl ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetDefaultThemeImpl(const Ark_CustomTheme* theme)
    {
    }
    } // ThemeControlAccessor
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
    Array_HistoricalPoint GetHistoricalPointsImpl(Ark_TouchEvent peer)
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
    Callback_Void GetStopPropagationImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    void SetStopPropagationImpl(Ark_TouchEvent peer,
                                const Callback_Void* stopPropagation)
    {
    }
    Callback_Void GetPreventDefaultImpl(Ark_TouchEvent peer)
    {
        return {};
    }
    void SetPreventDefaultImpl(Ark_TouchEvent peer,
                               const Callback_Void* preventDefault)
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
    Ark_TransitionEffect Construct1Impl(const Ark_Number* effect)
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
    Ark_TransitionEffect OpacityImpl(const Ark_Number* alpha)
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
    Ark_TransitionEffect GetIDENTITYImpl(Ark_TransitionEffect peer)
    {
        return {};
    }
    void SetIDENTITYImpl(Ark_TransitionEffect peer,
                         Ark_TransitionEffect IDENTITY)
    {
    }
    Ark_TransitionEffect GetOPACITYImpl(Ark_TransitionEffect peer)
    {
        return {};
    }
    void SetOPACITYImpl(Ark_TransitionEffect peer,
                        Ark_TransitionEffect OPACITY)
    {
    }
    Ark_TransitionEffect GetSLIDEImpl(Ark_TransitionEffect peer)
    {
        return {};
    }
    void SetSLIDEImpl(Ark_TransitionEffect peer,
                      Ark_TransitionEffect SLIDE)
    {
    }
    Ark_TransitionEffect GetSLIDE_SWITCHImpl(Ark_TransitionEffect peer)
    {
        return {};
    }
    void SetSLIDE_SWITCHImpl(Ark_TransitionEffect peer,
                             Ark_TransitionEffect SLIDE_SWITCH)
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
    namespace UIContextAccessor {
    void DestroyPeerImpl(Ark_UIContext peer)
    {
        auto peerImpl = reinterpret_cast<UIContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UIContext ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_drawing_Font GetFontImpl(Ark_UIContext peer)
    {
        return {};
    }
    Ark_String GetFilteredInspectorTreeImpl(Ark_VMContext vmContext,
                                            Ark_UIContext peer,
                                            const Opt_Array_String* filters)
    {
        return {};
    }
    Ark_String GetFilteredInspectorTreeByIdImpl(Ark_VMContext vmContext,
                                                Ark_UIContext peer,
                                                const Ark_String* id,
                                                const Ark_Number* depth,
                                                const Opt_Array_String* filters)
    {
        return {};
    }
    void AnimateToImpl(Ark_UIContext peer,
                       const Ark_AnimateParam* value,
                       const Callback_Void* event)
    {
    }
    void ShowTextPickerDialogImpl(Ark_UIContext peer,
                                  const Ark_TextPickerDialogOptions* options)
    {
    }
    void RunScopedTaskImpl(Ark_UIContext peer,
                           const Callback_Void* callback_)
    {
    }
    void AnimateToImmediatelyImpl(Ark_UIContext peer,
                                  const Ark_AnimateParam* param,
                                  const Callback_Void* event)
    {
    }
    Opt_FrameNode GetFrameNodeByIdImpl(Ark_UIContext peer,
                                       const Ark_String* id)
    {
        return {};
    }
    Opt_FrameNode GetAttachedFrameNodeByIdImpl(Ark_UIContext peer,
                                               const Ark_String* id)
    {
        return {};
    }
    Opt_FrameNode GetFrameNodeByUniqueIdImpl(Ark_UIContext peer,
                                             const Ark_Number* id)
    {
        return {};
    }
    Ark_Number Vp2pxImpl(Ark_UIContext peer,
                         const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2vpImpl(Ark_UIContext peer,
                         const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Fp2pxImpl(Ark_UIContext peer,
                         const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2fpImpl(Ark_UIContext peer,
                         const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Lpx2pxImpl(Ark_UIContext peer,
                          const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2lpxImpl(Ark_UIContext peer,
                          const Ark_Number* value)
    {
        return {};
    }
    Opt_common_Context GetHostContextImpl(Ark_UIContext peer)
    {
        return {};
    }
    void SetDynamicDimmingImpl(Ark_UIContext peer,
                               const Ark_String* id,
                               const Ark_Number* value)
    {
    }
    Opt_String GetWindowNameImpl(Ark_UIContext peer)
    {
        return {};
    }
    Ark_WidthBreakpoint GetWindowWidthBreakpointImpl(Ark_UIContext peer)
    {
        return {};
    }
    Ark_HeightBreakpoint GetWindowHeightBreakpointImpl(Ark_UIContext peer)
    {
        return {};
    }
    void OpenBindSheetImpl(Ark_VMContext vmContext,
                           Ark_AsyncWorkerPtr asyncWorker,
                           Ark_UIContext peer,
                           Ark_ComponentContent bindSheetContent,
                           const Opt_SheetOptions* sheetOptions,
                           const Opt_Number* targetId,
                           const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void UpdateBindSheetImpl(Ark_VMContext vmContext,
                             Ark_AsyncWorkerPtr asyncWorker,
                             Ark_UIContext peer,
                             Ark_ComponentContent bindSheetContent,
                             const Ark_SheetOptions* sheetOptions,
                             const Opt_Boolean* partialUpdate,
                             const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void CloseBindSheetImpl(Ark_VMContext vmContext,
                            Ark_AsyncWorkerPtr asyncWorker,
                            Ark_UIContext peer,
                            Ark_ComponentContent bindSheetContent,
                            const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void ClearResourceCacheImpl(Ark_VMContext vmContext,
                                Ark_UIContext peer)
    {
    }
    Ark_Boolean IsFollowingSystemFontScaleImpl(Ark_UIContext peer)
    {
        return {};
    }
    Ark_Number GetMaxFontScaleImpl(Ark_UIContext peer)
    {
        return {};
    }
    } // UIContextAccessor
    namespace UIContextAtomicServiceBarAccessor {
    Ark_Frame GetBarRectImpl()
    {
        return {};
    }
    } // UIContextAtomicServiceBarAccessor
    namespace uiEffect_VisualEffectAccessor {
    void DestroyPeerImpl(Ark_uiEffect_VisualEffect peer)
    {
        auto peerImpl = reinterpret_cast<uiEffect_VisualEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_uiEffect_VisualEffect ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_uiEffect_VisualEffect BackgroundColorBlenderImpl(Ark_uiEffect_VisualEffect peer,
                                                         const Ark_uiEffect_BrightnessBlender* blender)
    {
        return {};
    }
    } // uiEffect_VisualEffectAccessor
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
                  const Map_String_Object* data)
    {
    }
    Map_String_Object SendSyncImpl(Ark_UIExtensionProxy peer,
                                   const Map_String_Object* data)
    {
        return {};
    }
    void OnAsyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                     const Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OnSyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                    const Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OffAsyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                      const Opt_Callback_UIExtensionProxy_Void* callback_)
    {
    }
    void OffSyncReceiverRegisterImpl(Ark_UIExtensionProxy peer,
                                     const Opt_Callback_UIExtensionProxy_Void* callback_)
    {
    }
    } // UIExtensionProxyAccessor
    namespace unifiedDataChannel_UnifiedDataAccessor {
    void DestroyPeerImpl(Ark_unifiedDataChannel_UnifiedData peer)
    {
        auto peerImpl = reinterpret_cast<unifiedDataChannel_UnifiedDataPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_unifiedDataChannel_UnifiedData ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean HasTypeImpl(Ark_unifiedDataChannel_UnifiedData peer,
                            const Ark_String* UnifiedData_type)
    {
        return {};
    }
    Array_String GetTypesImpl(Ark_unifiedDataChannel_UnifiedData peer)
    {
        return {};
    }
    } // unifiedDataChannel_UnifiedDataAccessor
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
    namespace UserDataSpanAccessor {
    void DestroyPeerImpl(Ark_UserDataSpan peer)
    {
        auto peerImpl = reinterpret_cast<UserDataSpanPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UserDataSpan ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // UserDataSpanAccessor
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
    void SetCurrentTime0Impl(Ark_VideoController peer,
                             const Ark_Number* value)
    {
    }
    void RequestFullscreenImpl(Ark_VideoController peer,
                               Ark_Boolean value)
    {
    }
    void ExitFullscreenImpl(Ark_VideoController peer)
    {
    }
    void SetCurrentTime1Impl(Ark_VideoController peer,
                             const Ark_Number* value,
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
                           const Ark_Number* start,
                           const Opt_Number* deleteCount,
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
                           const Ark_Number* sectionIndex,
                           const Ark_SectionOptions* section)
    {
        return {};
    }
    Array_SectionOptions ValuesImpl(Ark_WaterFlowSections peer)
    {
        return {};
    }
    Ark_Number LengthImpl(Ark_WaterFlowSections peer)
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
    } // WebContextMenuResultAccessor
    namespace WebCookieAccessor {
    void DestroyPeerImpl(Ark_WebCookie peer)
    {
        auto peerImpl = reinterpret_cast<WebCookiePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebCookie ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetCookieImpl(Ark_WebCookie peer)
    {
    }
    void SaveCookieImpl(Ark_WebCookie peer)
    {
    }
    } // WebCookieAccessor
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
    Ark_Number GetErrorCodeImpl(Ark_WebResourceError peer)
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
    Opt_Union_String_Number_Buffer_Resource GetResponseDataExImpl(Ark_WebResourceResponse peer)
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
    Ark_Number GetResponseCodeImpl(Ark_WebResourceResponse peer)
    {
        return {};
    }
    void SetResponseDataImpl(Ark_WebResourceResponse peer,
                             const Ark_Union_String_Number_Resource_Buffer* data)
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
                             const Ark_Number* code)
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
    namespace webview_WebviewControllerAccessor {
    void DestroyPeerImpl(Ark_webview_WebviewController peer)
    {
        auto peerImpl = reinterpret_cast<webview_WebviewControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_webview_WebviewController ConstructImpl()
    {
        return {};
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InitializeWebEngineImpl()
    {
    }
    void LoadUrlImpl(Ark_webview_WebviewController peer,
                     const Ark_Union_String_Resource* url,
                     const Opt_Array_webview_WebHeader* headers)
    {
    }
    } // webview_WebviewControllerAccessor
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
    Ark_Object GetXComponentContextImpl(Ark_XComponentController peer)
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
    Ark_CustomObject ApplyStylesImpl(const Ark_CustomObject* self,
                                     const CustomStyles* customStyles)
    {
        return {};
    }
    void BindCompatibleProvideCallbackImpl(Ark_ExtendableComponent component,
                                           const Ark_CustomObject* createCompatibleState,
                                           const Ark_CustomObject* setCallback,
                                           const Opt_CustomObject* compatibleComponent)
    {
    }
    Ark_BorderRadiuses BorderRadiusesImpl(const Ark_Number* all)
    {
        return {};
    }
    Ark_Edges BorderStylesImpl(Ark_BorderStyle all)
    {
        return {};
    }
    void CompatibleComponentImpl(const CompatibleInitCallback* init,
                                 const CompatibleUpdateCallback* update,
                                 const Opt_ExtendableComponent* component)
    {
    }
    void CompatibleWrappedBuilderImpl(const Ark_CustomObject* builder,
                                      const Ark_CustomObject* args)
    {
    }
    void CursorControl_restoreDefaultImpl()
    {
    }
    void CursorControl_setCursorImpl(Ark_pointer_PointerStyle value)
    {
    }
    Ark_Edges EdgeColorsImpl(const Ark_Number* all)
    {
        return {};
    }
    Ark_Edges EdgeWidthsImpl(const Ark_Number* all)
    {
        return {};
    }
    Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
    {
        return {};
    }
    Ark_font_UIFontConfig Font_getUIFontConfigImpl()
    {
        return {};
    }
    Ark_CustomObject GetCompatibleStateImpl(const Ark_CustomObject* state,
                                            const Ark_CustomObject* createCompatibleState)
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
    void Text_getFontDescriptorByFullNameImpl(Ark_VMContext vmContext,
                                              Ark_AsyncWorkerPtr asyncWorker,
                                              const Ark_String* fullName,
                                              Ark_text_SystemFontType fontType,
                                              const Callback_Opt_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void Text_getSystemFontFullNamesByTypeImpl(Ark_VMContext vmContext,
                                               Ark_AsyncWorkerPtr asyncWorker,
                                               Ark_text_SystemFontType fontType,
                                               const Callback_Opt_Array_String_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void Text_matchFontDescriptorsImpl(Ark_VMContext vmContext,
                                       Ark_AsyncWorkerPtr asyncWorker,
                                       const Ark_text_FontDescriptor* desc,
                                       const Callback_Opt_Array_FontDescriptor_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    Ark_uiEffect_BrightnessBlender UiEffect_createBrightnessBlenderImpl(const Ark_uiEffect_BrightnessBlenderParam* param)
    {
        return {};
    }
    Ark_uiEffect_VisualEffect UiEffect_createEffectImpl()
    {
        return {};
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
    const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
    {
        static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
            AnimationExtenderAccessor::SetClipRectImpl,
            AnimationExtenderAccessor::OpenImplicitAnimationImpl,
            AnimationExtenderAccessor::CloseImplicitAnimationImpl,
            AnimationExtenderAccessor::StartDoubleAnimationImpl,
            AnimationExtenderAccessor::AnimationTranslateImpl,
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
    const GENERATED_ArkUIAxisEventAccessor* GetAxisEventAccessor()
    {
        static const GENERATED_ArkUIAxisEventAccessor AxisEventAccessorImpl {
            AxisEventAccessor::DestroyPeerImpl,
            AxisEventAccessor::ConstructImpl,
            AxisEventAccessor::GetFinalizerImpl,
            AxisEventAccessor::GetHorizontalAxisValueImpl,
            AxisEventAccessor::GetVerticalAxisValueImpl,
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
            AxisEventAccessor::GetPropagationImpl,
            AxisEventAccessor::SetPropagationImpl,
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
    const GENERATED_ArkUIBaseContextAccessor* GetBaseContextAccessor()
    {
        static const GENERATED_ArkUIBaseContextAccessor BaseContextAccessorImpl {
            BaseContextAccessor::DestroyPeerImpl,
            BaseContextAccessor::ConstructImpl,
            BaseContextAccessor::GetFinalizerImpl,
        };
        return &BaseContextAccessorImpl;
    }

    struct BaseContextPeer {
        virtual ~BaseContextPeer() = default;
    };
    const GENERATED_ArkUIBaseCustomDialogAccessor* GetBaseCustomDialogAccessor()
    {
        static const GENERATED_ArkUIBaseCustomDialogAccessor BaseCustomDialogAccessorImpl {
            BaseCustomDialogAccessor::DestroyPeerImpl,
            BaseCustomDialogAccessor::ConstructImpl,
            BaseCustomDialogAccessor::GetFinalizerImpl,
            BaseCustomDialogAccessor::$_instantiateImpl,
        };
        return &BaseCustomDialogAccessorImpl;
    }

    struct BaseCustomDialogPeer {
        virtual ~BaseCustomDialogPeer() = default;
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
    const GENERATED_ArkUICircleShapeAccessor* GetCircleShapeAccessor()
    {
        static const GENERATED_ArkUICircleShapeAccessor CircleShapeAccessorImpl {
            CircleShapeAccessor::DestroyPeerImpl,
            CircleShapeAccessor::ConstructImpl,
            CircleShapeAccessor::GetFinalizerImpl,
            CircleShapeAccessor::OffsetImpl,
            CircleShapeAccessor::FillImpl,
            CircleShapeAccessor::PositionImpl,
            CircleShapeAccessor::WidthImpl,
            CircleShapeAccessor::HeightImpl,
            CircleShapeAccessor::SizeImpl,
        };
        return &CircleShapeAccessorImpl;
    }

    struct CircleShapePeer {
        virtual ~CircleShapePeer() = default;
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
            ClickEventAccessor::GetPreventDefaultImpl,
            ClickEventAccessor::SetPreventDefaultImpl,
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
    const GENERATED_ArkUIColorMetricsAccessor* GetColorMetricsAccessor()
    {
        static const GENERATED_ArkUIColorMetricsAccessor ColorMetricsAccessorImpl {
            ColorMetricsAccessor::DestroyPeerImpl,
            ColorMetricsAccessor::ConstructImpl,
            ColorMetricsAccessor::GetFinalizerImpl,
            ColorMetricsAccessor::NumericImpl,
            ColorMetricsAccessor::RgbaImpl,
            ColorMetricsAccessor::ResourceColorImpl,
            ColorMetricsAccessor::BlendColorImpl,
            ColorMetricsAccessor::ColorImpl,
            ColorMetricsAccessor::RedImpl,
            ColorMetricsAccessor::GreenImpl,
            ColorMetricsAccessor::BlueImpl,
            ColorMetricsAccessor::AlphaImpl,
        };
        return &ColorMetricsAccessorImpl;
    }

    struct ColorMetricsPeer {
        virtual ~ColorMetricsPeer() = default;
    };
    const GENERATED_ArkUICommon_ContextAccessor* GetCommon_ContextAccessor()
    {
        static const GENERATED_ArkUICommon_ContextAccessor Common_ContextAccessorImpl {
            common_ContextAccessor::DestroyPeerImpl,
            common_ContextAccessor::ConstructImpl,
            common_ContextAccessor::GetFinalizerImpl,
            common_ContextAccessor::CreateBundleContextImpl,
            common_ContextAccessor::CreateModuleContext0Impl,
            common_ContextAccessor::CreateModuleContext1Impl,
            common_ContextAccessor::GetGroupDir0Impl,
            common_ContextAccessor::GetGroupDir1Impl,
            common_ContextAccessor::GetCacheDirImpl,
            common_ContextAccessor::SetCacheDirImpl,
            common_ContextAccessor::GetTempDirImpl,
            common_ContextAccessor::SetTempDirImpl,
            common_ContextAccessor::GetFilesDirImpl,
            common_ContextAccessor::SetFilesDirImpl,
            common_ContextAccessor::GetDatabaseDirImpl,
            common_ContextAccessor::SetDatabaseDirImpl,
            common_ContextAccessor::GetPreferencesDirImpl,
            common_ContextAccessor::SetPreferencesDirImpl,
            common_ContextAccessor::GetBundleCodeDirImpl,
            common_ContextAccessor::SetBundleCodeDirImpl,
            common_ContextAccessor::GetDistributedFilesDirImpl,
            common_ContextAccessor::SetDistributedFilesDirImpl,
            common_ContextAccessor::GetResourceDirImpl,
            common_ContextAccessor::SetResourceDirImpl,
            common_ContextAccessor::GetCloudFileDirImpl,
            common_ContextAccessor::SetCloudFileDirImpl,
        };
        return &Common_ContextAccessorImpl;
    }

    struct Common_ContextPeer {
        virtual ~Common_ContextPeer() = default;
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
    const GENERATED_ArkUIComponentContentAccessor* GetComponentContentAccessor()
    {
        static const GENERATED_ArkUIComponentContentAccessor ComponentContentAccessorImpl {
            ComponentContentAccessor::DestroyPeerImpl,
            ComponentContentAccessor::ConstructImpl,
            ComponentContentAccessor::GetFinalizerImpl,
            ComponentContentAccessor::UpdateImpl,
            ComponentContentAccessor::ReuseImpl,
            ComponentContentAccessor::RecycleImpl,
            ComponentContentAccessor::DisposeImpl,
            ComponentContentAccessor::UpdateConfigurationImpl,
        };
        return &ComponentContentAccessorImpl;
    }

    struct ComponentContentPeer {
        virtual ~ComponentContentPeer() = default;
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
            ContentModifierHelperAccessor::ContentModifierCheckBoxImpl,
            ContentModifierHelperAccessor::ContentModifierDataPanelImpl,
            ContentModifierHelperAccessor::ContentModifierGaugeImpl,
            ContentModifierHelperAccessor::ContentModifierLoadingProgressImpl,
            ContentModifierHelperAccessor::ContentModifierProgressImpl,
            ContentModifierHelperAccessor::ContentModifierRadioImpl,
            ContentModifierHelperAccessor::ContentModifierRatingImpl,
            ContentModifierHelperAccessor::ContentModifierMenuItemImpl,
            ContentModifierHelperAccessor::ContentModifierSliderImpl,
            ContentModifierHelperAccessor::ContentModifierTextClockImpl,
            ContentModifierHelperAccessor::ContentModifierTextTimerImpl,
            ContentModifierHelperAccessor::ContentModifierToggleImpl,
        };
        return &ContentModifierHelperAccessorImpl;
    }

    const GENERATED_ArkUIContextAccessor* GetContextAccessor()
    {
        static const GENERATED_ArkUIContextAccessor ContextAccessorImpl {
            ContextAccessor::DestroyPeerImpl,
            ContextAccessor::ConstructImpl,
            ContextAccessor::GetFinalizerImpl,
        };
        return &ContextAccessorImpl;
    }

    struct ContextPeer {
        virtual ~ContextPeer() = default;
    };
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
    const GENERATED_ArkUICurves_ICurveAccessor* GetCurves_ICurveAccessor()
    {
        static const GENERATED_ArkUICurves_ICurveAccessor Curves_ICurveAccessorImpl {
            curves_ICurveAccessor::DestroyPeerImpl,
            curves_ICurveAccessor::ConstructImpl,
            curves_ICurveAccessor::GetFinalizerImpl,
            curves_ICurveAccessor::InterpolateImpl,
        };
        return &Curves_ICurveAccessorImpl;
    }

    struct Curves_ICurvePeer {
        virtual ~Curves_ICurvePeer() = default;
    };
    const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
    {
        static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
            CustomDialogControllerAccessor::DestroyPeerImpl,
            CustomDialogControllerAccessor::ConstructImpl,
            CustomDialogControllerAccessor::GetFinalizerImpl,
            CustomDialogControllerAccessor::OpenImpl,
            CustomDialogControllerAccessor::CloseImpl,
        };
        return &CustomDialogControllerAccessorImpl;
    }

    struct CustomDialogControllerPeer {
        virtual ~CustomDialogControllerPeer() = default;
    };
    const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
    {
        static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
            CustomSpanAccessor::DestroyPeerImpl,
            CustomSpanAccessor::ConstructImpl,
            CustomSpanAccessor::GetFinalizerImpl,
            CustomSpanAccessor::InvalidateImpl,
            CustomSpanAccessor::GetOnMeasureImpl,
            CustomSpanAccessor::SetOnMeasureImpl,
            CustomSpanAccessor::GetOnDrawImpl,
            CustomSpanAccessor::SetOnDrawImpl,
        };
        return &CustomSpanAccessorImpl;
    }

    struct CustomSpanPeer {
        virtual ~CustomSpanPeer() = default;
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
    const GENERATED_ArkUIDrawableDescriptorAccessor* GetDrawableDescriptorAccessor()
    {
        static const GENERATED_ArkUIDrawableDescriptorAccessor DrawableDescriptorAccessorImpl {
            DrawableDescriptorAccessor::DestroyPeerImpl,
            DrawableDescriptorAccessor::ConstructImpl,
            DrawableDescriptorAccessor::GetFinalizerImpl,
            DrawableDescriptorAccessor::GetPixelMapImpl,
        };
        return &DrawableDescriptorAccessorImpl;
    }

    struct DrawableDescriptorPeer {
        virtual ~DrawableDescriptorPeer() = default;
    };
    const GENERATED_ArkUIDrawContextAccessor* GetDrawContextAccessor()
    {
        static const GENERATED_ArkUIDrawContextAccessor DrawContextAccessorImpl {
            DrawContextAccessor::DestroyPeerImpl,
            DrawContextAccessor::ConstructImpl,
            DrawContextAccessor::GetFinalizerImpl,
            DrawContextAccessor::SizeImpl,
            DrawContextAccessor::SizeInPixelImpl,
            DrawContextAccessor::CanvasImpl,
        };
        return &DrawContextAccessorImpl;
    }

    struct DrawContextPeer {
        virtual ~DrawContextPeer() = default;
    };
    const GENERATED_ArkUIDrawing_BrushAccessor* GetDrawing_BrushAccessor()
    {
        static const GENERATED_ArkUIDrawing_BrushAccessor Drawing_BrushAccessorImpl {
            drawing_BrushAccessor::DestroyPeerImpl,
            drawing_BrushAccessor::Construct0Impl,
            drawing_BrushAccessor::Construct1Impl,
            drawing_BrushAccessor::GetFinalizerImpl,
            drawing_BrushAccessor::SetColor0Impl,
            drawing_BrushAccessor::SetColor1Impl,
            drawing_BrushAccessor::SetColor2Impl,
            drawing_BrushAccessor::GetColorImpl,
            drawing_BrushAccessor::GetHexColorImpl,
            drawing_BrushAccessor::SetAntiAliasImpl,
            drawing_BrushAccessor::IsAntiAliasImpl,
            drawing_BrushAccessor::SetAlphaImpl,
            drawing_BrushAccessor::GetAlphaImpl,
            drawing_BrushAccessor::SetColorFilterImpl,
            drawing_BrushAccessor::GetColorFilterImpl,
            drawing_BrushAccessor::SetImageFilterImpl,
            drawing_BrushAccessor::SetMaskFilterImpl,
            drawing_BrushAccessor::SetShadowLayerImpl,
            drawing_BrushAccessor::SetShaderEffectImpl,
            drawing_BrushAccessor::SetBlendModeImpl,
            drawing_BrushAccessor::ResetImpl,
        };
        return &Drawing_BrushAccessorImpl;
    }

    struct Drawing_BrushPeer {
        virtual ~Drawing_BrushPeer() = default;
    };
    const GENERATED_ArkUIDrawing_CanvasAccessor* GetDrawing_CanvasAccessor()
    {
        static const GENERATED_ArkUIDrawing_CanvasAccessor Drawing_CanvasAccessorImpl {
            drawing_CanvasAccessor::DestroyPeerImpl,
            drawing_CanvasAccessor::ConstructImpl,
            drawing_CanvasAccessor::GetFinalizerImpl,
            drawing_CanvasAccessor::DrawRect0Impl,
            drawing_CanvasAccessor::DrawRect1Impl,
            drawing_CanvasAccessor::DrawRoundRectImpl,
            drawing_CanvasAccessor::DrawNestedRoundRectImpl,
            drawing_CanvasAccessor::DrawBackgroundImpl,
            drawing_CanvasAccessor::DrawShadow0Impl,
            drawing_CanvasAccessor::DrawShadow1Impl,
            drawing_CanvasAccessor::DrawCircleImpl,
            drawing_CanvasAccessor::DrawImageImpl,
            drawing_CanvasAccessor::DrawImageRectImpl,
            drawing_CanvasAccessor::DrawImageRectWithSrcImpl,
            drawing_CanvasAccessor::DrawColor0Impl,
            drawing_CanvasAccessor::DrawColor1Impl,
            drawing_CanvasAccessor::DrawColor2Impl,
            drawing_CanvasAccessor::DrawOvalImpl,
            drawing_CanvasAccessor::DrawArcImpl,
            drawing_CanvasAccessor::DrawPointImpl,
            drawing_CanvasAccessor::DrawPointsImpl,
            drawing_CanvasAccessor::DrawPathImpl,
            drawing_CanvasAccessor::DrawLineImpl,
            drawing_CanvasAccessor::DrawSingleCharacterImpl,
            drawing_CanvasAccessor::DrawTextBlobImpl,
            drawing_CanvasAccessor::DrawPixelMapMeshImpl,
            drawing_CanvasAccessor::DrawRegionImpl,
            drawing_CanvasAccessor::AttachPenImpl,
            drawing_CanvasAccessor::AttachBrushImpl,
            drawing_CanvasAccessor::DetachPenImpl,
            drawing_CanvasAccessor::DetachBrushImpl,
            drawing_CanvasAccessor::SaveImpl,
            drawing_CanvasAccessor::SaveLayerImpl,
            drawing_CanvasAccessor::Clear0Impl,
            drawing_CanvasAccessor::Clear1Impl,
            drawing_CanvasAccessor::RestoreImpl,
            drawing_CanvasAccessor::RestoreToCountImpl,
            drawing_CanvasAccessor::GetSaveCountImpl,
            drawing_CanvasAccessor::GetWidthImpl,
            drawing_CanvasAccessor::GetHeightImpl,
            drawing_CanvasAccessor::GetLocalClipBoundsImpl,
            drawing_CanvasAccessor::GetTotalMatrixImpl,
            drawing_CanvasAccessor::ScaleImpl,
            drawing_CanvasAccessor::SkewImpl,
            drawing_CanvasAccessor::RotateImpl,
            drawing_CanvasAccessor::TranslateImpl,
            drawing_CanvasAccessor::ClipPathImpl,
            drawing_CanvasAccessor::ClipRectImpl,
            drawing_CanvasAccessor::ConcatMatrixImpl,
            drawing_CanvasAccessor::ClipRegionImpl,
            drawing_CanvasAccessor::ClipRoundRectImpl,
            drawing_CanvasAccessor::IsClipEmptyImpl,
            drawing_CanvasAccessor::SetMatrixImpl,
            drawing_CanvasAccessor::ResetMatrixImpl,
        };
        return &Drawing_CanvasAccessorImpl;
    }

    struct Drawing_CanvasPeer {
        virtual ~Drawing_CanvasPeer() = default;
    };
    const GENERATED_ArkUIDrawing_ColorFilterAccessor* GetDrawing_ColorFilterAccessor()
    {
        static const GENERATED_ArkUIDrawing_ColorFilterAccessor Drawing_ColorFilterAccessorImpl {
            drawing_ColorFilterAccessor::DestroyPeerImpl,
            drawing_ColorFilterAccessor::ConstructImpl,
            drawing_ColorFilterAccessor::GetFinalizerImpl,
            drawing_ColorFilterAccessor::CreateBlendModeColorFilter0Impl,
            drawing_ColorFilterAccessor::CreateBlendModeColorFilter1Impl,
            drawing_ColorFilterAccessor::CreateComposeColorFilterImpl,
            drawing_ColorFilterAccessor::CreateLinearToSRGBGammaImpl,
            drawing_ColorFilterAccessor::CreateSRGBGammaToLinearImpl,
            drawing_ColorFilterAccessor::CreateLumaColorFilterImpl,
            drawing_ColorFilterAccessor::CreateMatrixColorFilterImpl,
        };
        return &Drawing_ColorFilterAccessorImpl;
    }

    struct Drawing_ColorFilterPeer {
        virtual ~Drawing_ColorFilterPeer() = default;
    };
    const GENERATED_ArkUIDrawing_FontAccessor* GetDrawing_FontAccessor()
    {
        static const GENERATED_ArkUIDrawing_FontAccessor Drawing_FontAccessorImpl {
            drawing_FontAccessor::DestroyPeerImpl,
            drawing_FontAccessor::ConstructImpl,
            drawing_FontAccessor::GetFinalizerImpl,
            drawing_FontAccessor::EnableSubpixelImpl,
            drawing_FontAccessor::EnableEmboldenImpl,
            drawing_FontAccessor::EnableLinearMetricsImpl,
            drawing_FontAccessor::SetSizeImpl,
            drawing_FontAccessor::GetSizeImpl,
            drawing_FontAccessor::SetTypefaceImpl,
            drawing_FontAccessor::GetTypefaceImpl,
            drawing_FontAccessor::GetMetricsImpl,
            drawing_FontAccessor::MeasureSingleCharacterImpl,
            drawing_FontAccessor::MeasureTextImpl,
            drawing_FontAccessor::SetScaleXImpl,
            drawing_FontAccessor::SetSkewXImpl,
            drawing_FontAccessor::SetEdgingImpl,
            drawing_FontAccessor::SetHintingImpl,
            drawing_FontAccessor::CountTextImpl,
            drawing_FontAccessor::SetBaselineSnapImpl,
            drawing_FontAccessor::IsBaselineSnapImpl,
            drawing_FontAccessor::SetEmbeddedBitmapsImpl,
            drawing_FontAccessor::IsEmbeddedBitmapsImpl,
            drawing_FontAccessor::SetForceAutoHintingImpl,
            drawing_FontAccessor::IsForceAutoHintingImpl,
            drawing_FontAccessor::GetWidthsImpl,
            drawing_FontAccessor::TextToGlyphsImpl,
            drawing_FontAccessor::IsSubpixelImpl,
            drawing_FontAccessor::IsLinearMetricsImpl,
            drawing_FontAccessor::GetSkewXImpl,
            drawing_FontAccessor::IsEmboldenImpl,
            drawing_FontAccessor::GetScaleXImpl,
            drawing_FontAccessor::GetHintingImpl,
            drawing_FontAccessor::GetEdgingImpl,
            drawing_FontAccessor::CreatePathForGlyphImpl,
            drawing_FontAccessor::GetBoundsImpl,
            drawing_FontAccessor::GetTextPathImpl,
        };
        return &Drawing_FontAccessorImpl;
    }

    struct Drawing_FontPeer {
        virtual ~Drawing_FontPeer() = default;
    };
    const GENERATED_ArkUIDrawing_ImageFilterAccessor* GetDrawing_ImageFilterAccessor()
    {
        static const GENERATED_ArkUIDrawing_ImageFilterAccessor Drawing_ImageFilterAccessorImpl {
            drawing_ImageFilterAccessor::DestroyPeerImpl,
            drawing_ImageFilterAccessor::ConstructImpl,
            drawing_ImageFilterAccessor::GetFinalizerImpl,
            drawing_ImageFilterAccessor::CreateBlurImageFilterImpl,
            drawing_ImageFilterAccessor::CreateFromColorFilterImpl,
        };
        return &Drawing_ImageFilterAccessorImpl;
    }

    struct Drawing_ImageFilterPeer {
        virtual ~Drawing_ImageFilterPeer() = default;
    };
    const GENERATED_ArkUIDrawing_LatticeAccessor* GetDrawing_LatticeAccessor()
    {
        static const GENERATED_ArkUIDrawing_LatticeAccessor Drawing_LatticeAccessorImpl {
            drawing_LatticeAccessor::DestroyPeerImpl,
            drawing_LatticeAccessor::ConstructImpl,
            drawing_LatticeAccessor::GetFinalizerImpl,
            drawing_LatticeAccessor::CreateImageLatticeImpl,
        };
        return &Drawing_LatticeAccessorImpl;
    }

    struct Drawing_LatticePeer {
        virtual ~Drawing_LatticePeer() = default;
    };
    const GENERATED_ArkUIDrawing_MaskFilterAccessor* GetDrawing_MaskFilterAccessor()
    {
        static const GENERATED_ArkUIDrawing_MaskFilterAccessor Drawing_MaskFilterAccessorImpl {
            drawing_MaskFilterAccessor::DestroyPeerImpl,
            drawing_MaskFilterAccessor::ConstructImpl,
            drawing_MaskFilterAccessor::GetFinalizerImpl,
            drawing_MaskFilterAccessor::CreateBlurMaskFilterImpl,
        };
        return &Drawing_MaskFilterAccessorImpl;
    }

    struct Drawing_MaskFilterPeer {
        virtual ~Drawing_MaskFilterPeer() = default;
    };
    const GENERATED_ArkUIDrawing_MatrixAccessor* GetDrawing_MatrixAccessor()
    {
        static const GENERATED_ArkUIDrawing_MatrixAccessor Drawing_MatrixAccessorImpl {
            drawing_MatrixAccessor::DestroyPeerImpl,
            drawing_MatrixAccessor::ConstructImpl,
            drawing_MatrixAccessor::GetFinalizerImpl,
            drawing_MatrixAccessor::SetRotationImpl,
            drawing_MatrixAccessor::SetScaleImpl,
            drawing_MatrixAccessor::SetTranslationImpl,
            drawing_MatrixAccessor::SetMatrixImpl,
            drawing_MatrixAccessor::PreConcatImpl,
            drawing_MatrixAccessor::IsEqualImpl,
            drawing_MatrixAccessor::InvertImpl,
            drawing_MatrixAccessor::IsIdentityImpl,
            drawing_MatrixAccessor::GetValueImpl,
            drawing_MatrixAccessor::PostRotateImpl,
            drawing_MatrixAccessor::PostScaleImpl,
            drawing_MatrixAccessor::PostTranslateImpl,
            drawing_MatrixAccessor::PreRotateImpl,
            drawing_MatrixAccessor::PreScaleImpl,
            drawing_MatrixAccessor::PreTranslateImpl,
            drawing_MatrixAccessor::ResetImpl,
            drawing_MatrixAccessor::MapPointsImpl,
            drawing_MatrixAccessor::GetAllImpl,
            drawing_MatrixAccessor::MapRectImpl,
            drawing_MatrixAccessor::SetRectToRectImpl,
            drawing_MatrixAccessor::SetPolyToPolyImpl,
        };
        return &Drawing_MatrixAccessorImpl;
    }

    struct Drawing_MatrixPeer {
        virtual ~Drawing_MatrixPeer() = default;
    };
    const GENERATED_ArkUIDrawing_PathAccessor* GetDrawing_PathAccessor()
    {
        static const GENERATED_ArkUIDrawing_PathAccessor Drawing_PathAccessorImpl {
            drawing_PathAccessor::DestroyPeerImpl,
            drawing_PathAccessor::Construct0Impl,
            drawing_PathAccessor::Construct1Impl,
            drawing_PathAccessor::GetFinalizerImpl,
            drawing_PathAccessor::MoveToImpl,
            drawing_PathAccessor::LineToImpl,
            drawing_PathAccessor::ArcToImpl,
            drawing_PathAccessor::QuadToImpl,
            drawing_PathAccessor::ConicToImpl,
            drawing_PathAccessor::CubicToImpl,
            drawing_PathAccessor::RMoveToImpl,
            drawing_PathAccessor::RLineToImpl,
            drawing_PathAccessor::RQuadToImpl,
            drawing_PathAccessor::RConicToImpl,
            drawing_PathAccessor::RCubicToImpl,
            drawing_PathAccessor::AddPolygonImpl,
            drawing_PathAccessor::OpImpl,
            drawing_PathAccessor::AddArcImpl,
            drawing_PathAccessor::AddCircleImpl,
            drawing_PathAccessor::AddOvalImpl,
            drawing_PathAccessor::AddRectImpl,
            drawing_PathAccessor::AddRoundRectImpl,
            drawing_PathAccessor::AddPathImpl,
            drawing_PathAccessor::TransformImpl,
            drawing_PathAccessor::ContainsImpl,
            drawing_PathAccessor::SetFillTypeImpl,
            drawing_PathAccessor::GetBoundsImpl,
            drawing_PathAccessor::CloseImpl,
            drawing_PathAccessor::OffsetImpl,
            drawing_PathAccessor::ResetImpl,
            drawing_PathAccessor::GetLengthImpl,
            drawing_PathAccessor::GetPositionAndTangentImpl,
            drawing_PathAccessor::IsClosedImpl,
            drawing_PathAccessor::GetMatrixImpl,
            drawing_PathAccessor::BuildFromSvgStringImpl,
        };
        return &Drawing_PathAccessorImpl;
    }

    struct Drawing_PathPeer {
        virtual ~Drawing_PathPeer() = default;
    };
    const GENERATED_ArkUIDrawing_PathEffectAccessor* GetDrawing_PathEffectAccessor()
    {
        static const GENERATED_ArkUIDrawing_PathEffectAccessor Drawing_PathEffectAccessorImpl {
            drawing_PathEffectAccessor::DestroyPeerImpl,
            drawing_PathEffectAccessor::ConstructImpl,
            drawing_PathEffectAccessor::GetFinalizerImpl,
            drawing_PathEffectAccessor::CreateDashPathEffectImpl,
            drawing_PathEffectAccessor::CreateCornerPathEffectImpl,
        };
        return &Drawing_PathEffectAccessorImpl;
    }

    struct Drawing_PathEffectPeer {
        virtual ~Drawing_PathEffectPeer() = default;
    };
    const GENERATED_ArkUIDrawing_PenAccessor* GetDrawing_PenAccessor()
    {
        static const GENERATED_ArkUIDrawing_PenAccessor Drawing_PenAccessorImpl {
            drawing_PenAccessor::DestroyPeerImpl,
            drawing_PenAccessor::Construct0Impl,
            drawing_PenAccessor::Construct1Impl,
            drawing_PenAccessor::GetFinalizerImpl,
            drawing_PenAccessor::SetMiterLimitImpl,
            drawing_PenAccessor::GetMiterLimitImpl,
            drawing_PenAccessor::SetShaderEffectImpl,
            drawing_PenAccessor::SetColor0Impl,
            drawing_PenAccessor::SetColor1Impl,
            drawing_PenAccessor::SetColor2Impl,
            drawing_PenAccessor::GetColorImpl,
            drawing_PenAccessor::GetHexColorImpl,
            drawing_PenAccessor::SetStrokeWidthImpl,
            drawing_PenAccessor::GetWidthImpl,
            drawing_PenAccessor::SetAntiAliasImpl,
            drawing_PenAccessor::IsAntiAliasImpl,
            drawing_PenAccessor::SetAlphaImpl,
            drawing_PenAccessor::GetAlphaImpl,
            drawing_PenAccessor::SetColorFilterImpl,
            drawing_PenAccessor::GetColorFilterImpl,
            drawing_PenAccessor::SetImageFilterImpl,
            drawing_PenAccessor::SetMaskFilterImpl,
            drawing_PenAccessor::SetPathEffectImpl,
            drawing_PenAccessor::SetShadowLayerImpl,
            drawing_PenAccessor::SetBlendModeImpl,
            drawing_PenAccessor::SetDitherImpl,
            drawing_PenAccessor::SetJoinStyleImpl,
            drawing_PenAccessor::GetJoinStyleImpl,
            drawing_PenAccessor::SetCapStyleImpl,
            drawing_PenAccessor::GetCapStyleImpl,
            drawing_PenAccessor::ResetImpl,
            drawing_PenAccessor::GetFillPathImpl,
        };
        return &Drawing_PenAccessorImpl;
    }

    struct Drawing_PenPeer {
        virtual ~Drawing_PenPeer() = default;
    };
    const GENERATED_ArkUIDrawing_RegionAccessor* GetDrawing_RegionAccessor()
    {
        static const GENERATED_ArkUIDrawing_RegionAccessor Drawing_RegionAccessorImpl {
            drawing_RegionAccessor::DestroyPeerImpl,
            drawing_RegionAccessor::ConstructImpl,
            drawing_RegionAccessor::GetFinalizerImpl,
            drawing_RegionAccessor::IsPointContainedImpl,
            drawing_RegionAccessor::IsRegionContainedImpl,
            drawing_RegionAccessor::OpImpl,
            drawing_RegionAccessor::QuickRejectImpl,
            drawing_RegionAccessor::SetPathImpl,
            drawing_RegionAccessor::SetRectImpl,
        };
        return &Drawing_RegionAccessorImpl;
    }

    struct Drawing_RegionPeer {
        virtual ~Drawing_RegionPeer() = default;
    };
    const GENERATED_ArkUIDrawing_RoundRectAccessor* GetDrawing_RoundRectAccessor()
    {
        static const GENERATED_ArkUIDrawing_RoundRectAccessor Drawing_RoundRectAccessorImpl {
            drawing_RoundRectAccessor::DestroyPeerImpl,
            drawing_RoundRectAccessor::ConstructImpl,
            drawing_RoundRectAccessor::GetFinalizerImpl,
            drawing_RoundRectAccessor::SetCornerImpl,
            drawing_RoundRectAccessor::GetCornerImpl,
            drawing_RoundRectAccessor::OffsetImpl,
        };
        return &Drawing_RoundRectAccessorImpl;
    }

    struct Drawing_RoundRectPeer {
        virtual ~Drawing_RoundRectPeer() = default;
    };
    const GENERATED_ArkUIDrawing_SamplingOptionsAccessor* GetDrawing_SamplingOptionsAccessor()
    {
        static const GENERATED_ArkUIDrawing_SamplingOptionsAccessor Drawing_SamplingOptionsAccessorImpl {
            drawing_SamplingOptionsAccessor::DestroyPeerImpl,
            drawing_SamplingOptionsAccessor::Construct0Impl,
            drawing_SamplingOptionsAccessor::Construct1Impl,
            drawing_SamplingOptionsAccessor::GetFinalizerImpl,
        };
        return &Drawing_SamplingOptionsAccessorImpl;
    }

    struct Drawing_SamplingOptionsPeer {
        virtual ~Drawing_SamplingOptionsPeer() = default;
    };
    const GENERATED_ArkUIDrawing_ShaderEffectAccessor* GetDrawing_ShaderEffectAccessor()
    {
        static const GENERATED_ArkUIDrawing_ShaderEffectAccessor Drawing_ShaderEffectAccessorImpl {
            drawing_ShaderEffectAccessor::DestroyPeerImpl,
            drawing_ShaderEffectAccessor::ConstructImpl,
            drawing_ShaderEffectAccessor::GetFinalizerImpl,
            drawing_ShaderEffectAccessor::CreateColorShaderImpl,
            drawing_ShaderEffectAccessor::CreateLinearGradientImpl,
            drawing_ShaderEffectAccessor::CreateRadialGradientImpl,
            drawing_ShaderEffectAccessor::CreateSweepGradientImpl,
            drawing_ShaderEffectAccessor::CreateConicalGradientImpl,
        };
        return &Drawing_ShaderEffectAccessorImpl;
    }

    struct Drawing_ShaderEffectPeer {
        virtual ~Drawing_ShaderEffectPeer() = default;
    };
    const GENERATED_ArkUIDrawing_ShadowLayerAccessor* GetDrawing_ShadowLayerAccessor()
    {
        static const GENERATED_ArkUIDrawing_ShadowLayerAccessor Drawing_ShadowLayerAccessorImpl {
            drawing_ShadowLayerAccessor::DestroyPeerImpl,
            drawing_ShadowLayerAccessor::ConstructImpl,
            drawing_ShadowLayerAccessor::GetFinalizerImpl,
            drawing_ShadowLayerAccessor::Create0Impl,
            drawing_ShadowLayerAccessor::Create1Impl,
        };
        return &Drawing_ShadowLayerAccessorImpl;
    }

    struct Drawing_ShadowLayerPeer {
        virtual ~Drawing_ShadowLayerPeer() = default;
    };
    const GENERATED_ArkUIDrawing_TextBlobAccessor* GetDrawing_TextBlobAccessor()
    {
        static const GENERATED_ArkUIDrawing_TextBlobAccessor Drawing_TextBlobAccessorImpl {
            drawing_TextBlobAccessor::DestroyPeerImpl,
            drawing_TextBlobAccessor::ConstructImpl,
            drawing_TextBlobAccessor::GetFinalizerImpl,
            drawing_TextBlobAccessor::MakeFromStringImpl,
            drawing_TextBlobAccessor::MakeFromPosTextImpl,
            drawing_TextBlobAccessor::MakeFromRunBufferImpl,
            drawing_TextBlobAccessor::BoundsImpl,
            drawing_TextBlobAccessor::UniqueIDImpl,
        };
        return &Drawing_TextBlobAccessorImpl;
    }

    struct Drawing_TextBlobPeer {
        virtual ~Drawing_TextBlobPeer() = default;
    };
    const GENERATED_ArkUIDrawing_TypefaceAccessor* GetDrawing_TypefaceAccessor()
    {
        static const GENERATED_ArkUIDrawing_TypefaceAccessor Drawing_TypefaceAccessorImpl {
            drawing_TypefaceAccessor::DestroyPeerImpl,
            drawing_TypefaceAccessor::ConstructImpl,
            drawing_TypefaceAccessor::GetFinalizerImpl,
            drawing_TypefaceAccessor::GetFamilyNameImpl,
            drawing_TypefaceAccessor::MakeFromFileImpl,
        };
        return &Drawing_TypefaceAccessorImpl;
    }

    struct Drawing_TypefacePeer {
        virtual ~Drawing_TypefacePeer() = default;
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
        };
        return &DrawingRenderingContextAccessorImpl;
    }

    struct DrawingRenderingContextPeer {
        virtual ~DrawingRenderingContextPeer() = default;
    };
    const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor()
    {
        static const GENERATED_ArkUIDrawModifierAccessor DrawModifierAccessorImpl {
            DrawModifierAccessor::DestroyPeerImpl,
            DrawModifierAccessor::ConstructImpl,
            DrawModifierAccessor::GetFinalizerImpl,
            DrawModifierAccessor::InvalidateImpl,
            DrawModifierAccessor::GetDrawBehind_callbackImpl,
            DrawModifierAccessor::SetDrawBehind_callbackImpl,
            DrawModifierAccessor::GetDrawContent_callbackImpl,
            DrawModifierAccessor::SetDrawContent_callbackImpl,
        };
        return &DrawModifierAccessorImpl;
    }

    struct DrawModifierPeer {
        virtual ~DrawModifierPeer() = default;
    };
    const GENERATED_ArkUIEllipseShapeAccessor* GetEllipseShapeAccessor()
    {
        static const GENERATED_ArkUIEllipseShapeAccessor EllipseShapeAccessorImpl {
            EllipseShapeAccessor::DestroyPeerImpl,
            EllipseShapeAccessor::ConstructImpl,
            EllipseShapeAccessor::GetFinalizerImpl,
            EllipseShapeAccessor::OffsetImpl,
            EllipseShapeAccessor::FillImpl,
            EllipseShapeAccessor::PositionImpl,
            EllipseShapeAccessor::WidthImpl,
            EllipseShapeAccessor::HeightImpl,
            EllipseShapeAccessor::SizeImpl,
        };
        return &EllipseShapeAccessorImpl;
    }

    struct EllipseShapePeer {
        virtual ~EllipseShapePeer() = default;
    };
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
            FocusAxisEventAccessor::GetStopPropagationImpl,
            FocusAxisEventAccessor::SetStopPropagationImpl,
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

    const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
    {
        static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
            FrameNodeAccessor::DestroyPeerImpl,
            FrameNodeAccessor::ConstructImpl,
            FrameNodeAccessor::GetFinalizerImpl,
            FrameNodeAccessor::IsModifiableImpl,
            FrameNodeAccessor::AppendChildImpl,
            FrameNodeAccessor::InsertChildAfterImpl,
            FrameNodeAccessor::RemoveChildImpl,
            FrameNodeAccessor::ClearChildrenImpl,
            FrameNodeAccessor::GetChildImpl,
            FrameNodeAccessor::GetFirstChildImpl,
            FrameNodeAccessor::GetNextSiblingImpl,
            FrameNodeAccessor::GetPreviousSiblingImpl,
            FrameNodeAccessor::GetParentImpl,
            FrameNodeAccessor::GetChildrenCountImpl,
            FrameNodeAccessor::DisposeImpl,
            FrameNodeAccessor::GetIdImpl,
            FrameNodeAccessor::GetUniqueIdImpl,
            FrameNodeAccessor::GetNodeTypeImpl,
            FrameNodeAccessor::GetOpacityImpl,
            FrameNodeAccessor::IsVisibleImpl,
            FrameNodeAccessor::IsClipToFrameImpl,
            FrameNodeAccessor::IsAttachedImpl,
            FrameNodeAccessor::GetInspectorInfoImpl,
            FrameNodeAccessor::InvalidateImpl,
            FrameNodeAccessor::DisposeTreeImpl,
            FrameNodeAccessor::SetCrossLanguageOptionsImpl,
            FrameNodeAccessor::GetCrossLanguageOptionsImpl,
            FrameNodeAccessor::SetMeasuredSizeImpl,
            FrameNodeAccessor::SetLayoutPositionImpl,
            FrameNodeAccessor::MeasureImpl,
            FrameNodeAccessor::LayoutImpl,
            FrameNodeAccessor::SetNeedsLayoutImpl,
            FrameNodeAccessor::GetPositionToWindowWithTransformImpl,
            FrameNodeAccessor::GetFrameNodeByKeyImpl,
            FrameNodeAccessor::GetIdByFrameNodeImpl,
            FrameNodeAccessor::MoveToImpl,
            FrameNodeAccessor::GetFirstChildIndexWithoutExpandImpl,
            FrameNodeAccessor::GetLastChildIndexWithoutExpandImpl,
            FrameNodeAccessor::GetAttachedFrameNodeByIdImpl,
            FrameNodeAccessor::GetFrameNodeByIdImpl,
            FrameNodeAccessor::GetFrameNodeByUniqueIdImpl,
            FrameNodeAccessor::ReuseImpl,
            FrameNodeAccessor::RecycleImpl,
            FrameNodeAccessor::GetFrameNodePtrImpl,
            FrameNodeAccessor::CreateTypedFrameNodeImpl,
        };
        return &FrameNodeAccessorImpl;
    }

    struct FrameNodePeer {
        virtual ~FrameNodePeer() = default;
    };
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
        };
        return &GestureEventAccessorImpl;
    }

    struct GestureEventPeer {
        virtual ~GestureEventPeer() = default;
    };
    const GENERATED_ArkUIGestureGroupInterfaceAccessor* GetGestureGroupInterfaceAccessor()
    {
        static const GENERATED_ArkUIGestureGroupInterfaceAccessor GestureGroupInterfaceAccessorImpl {
            GestureGroupInterfaceAccessor::DestroyPeerImpl,
            GestureGroupInterfaceAccessor::ConstructImpl,
            GestureGroupInterfaceAccessor::GetFinalizerImpl,
            GestureGroupInterfaceAccessor::OnCancelImpl,
        };
        return &GestureGroupInterfaceAccessorImpl;
    }

    struct GestureGroupInterfacePeer {
        virtual ~GestureGroupInterfacePeer() = default;
    };
    const GENERATED_ArkUIGestureModifierAccessor* GetGestureModifierAccessor()
    {
        static const GENERATED_ArkUIGestureModifierAccessor GestureModifierAccessorImpl {
            GestureModifierAccessor::DestroyPeerImpl,
            GestureModifierAccessor::ConstructImpl,
            GestureModifierAccessor::GetFinalizerImpl,
            GestureModifierAccessor::ApplyGestureImpl,
        };
        return &GestureModifierAccessorImpl;
    }

    struct GestureModifierPeer {
        virtual ~GestureModifierPeer() = default;
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
            HoverEventAccessor::GetStopPropagationImpl,
            HoverEventAccessor::SetStopPropagationImpl,
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
    const GENERATED_ArkUIImage_PixelMapAccessor* GetImage_PixelMapAccessor()
    {
        static const GENERATED_ArkUIImage_PixelMapAccessor Image_PixelMapAccessorImpl {
            image_PixelMapAccessor::DestroyPeerImpl,
            image_PixelMapAccessor::ConstructImpl,
            image_PixelMapAccessor::GetFinalizerImpl,
            image_PixelMapAccessor::ReadPixelsToBufferSyncImpl,
            image_PixelMapAccessor::WriteBufferToPixelsImpl,
            image_PixelMapAccessor::GetIsEditableImpl,
            image_PixelMapAccessor::GetIsStrideAlignmentImpl,
        };
        return &Image_PixelMapAccessorImpl;
    }

    struct Image_PixelMapPeer {
        virtual ~Image_PixelMapPeer() = default;
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
    const GENERATED_ArkUILayoutCallbackAccessor* GetLayoutCallbackAccessor()
    {
        static const GENERATED_ArkUILayoutCallbackAccessor LayoutCallbackAccessorImpl {
            LayoutCallbackAccessor::DestroyPeerImpl,
            LayoutCallbackAccessor::ConstructImpl,
            LayoutCallbackAccessor::GetFinalizerImpl,
            LayoutCallbackAccessor::OnPlaceChildrenImpl,
            LayoutCallbackAccessor::OnMeasureSizeImpl,
        };
        return &LayoutCallbackAccessorImpl;
    }

    struct LayoutCallbackPeer {
        virtual ~LayoutCallbackPeer() = default;
    };
    const GENERATED_ArkUILayoutChildAccessor* GetLayoutChildAccessor()
    {
        static const GENERATED_ArkUILayoutChildAccessor LayoutChildAccessorImpl {
            LayoutChildAccessor::DestroyPeerImpl,
            LayoutChildAccessor::ConstructImpl,
            LayoutChildAccessor::GetFinalizerImpl,
            LayoutChildAccessor::MeasureImpl,
            LayoutChildAccessor::GetNameImpl,
            LayoutChildAccessor::SetNameImpl,
            LayoutChildAccessor::GetIdImpl,
            LayoutChildAccessor::SetIdImpl,
            LayoutChildAccessor::GetPositionImpl,
            LayoutChildAccessor::SetPositionImpl,
        };
        return &LayoutChildAccessorImpl;
    }

    struct LayoutChildPeer {
        virtual ~LayoutChildPeer() = default;
    };
    const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
    {
        static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
            LayoutManagerAccessor::DestroyPeerImpl,
            LayoutManagerAccessor::ConstructImpl,
            LayoutManagerAccessor::GetFinalizerImpl,
            LayoutManagerAccessor::GetLineCountImpl,
            LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
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
        };
        return &LayoutPolicyAccessorImpl;
    }

    struct LayoutPolicyPeer {
        virtual ~LayoutPolicyPeer() = default;
    };
    const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
    {
        static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
            LazyForEachOpsAccessor::SyncImpl,
        };
        return &LazyForEachOpsAccessorImpl;
    }

    const GENERATED_ArkUILengthMetricsAccessor* GetLengthMetricsAccessor()
    {
        static const GENERATED_ArkUILengthMetricsAccessor LengthMetricsAccessorImpl {
            LengthMetricsAccessor::DestroyPeerImpl,
            LengthMetricsAccessor::ConstructImpl,
            LengthMetricsAccessor::GetFinalizerImpl,
            LengthMetricsAccessor::PxImpl,
            LengthMetricsAccessor::VpImpl,
            LengthMetricsAccessor::FpImpl,
            LengthMetricsAccessor::PercentImpl,
            LengthMetricsAccessor::LpxImpl,
            LengthMetricsAccessor::ResourceImpl,
            LengthMetricsAccessor::GetUnitImpl,
            LengthMetricsAccessor::SetUnitImpl,
            LengthMetricsAccessor::GetValueImpl,
            LengthMetricsAccessor::SetValueImpl,
        };
        return &LengthMetricsAccessorImpl;
    }

    struct LengthMetricsPeer {
        virtual ~LengthMetricsPeer() = default;
    };
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
    const GENERATED_ArkUILevelOrderAccessor* GetLevelOrderAccessor()
    {
        static const GENERATED_ArkUILevelOrderAccessor LevelOrderAccessorImpl {
            LevelOrderAccessor::DestroyPeerImpl,
            LevelOrderAccessor::ConstructImpl,
            LevelOrderAccessor::GetFinalizerImpl,
            LevelOrderAccessor::ClampImpl,
            LevelOrderAccessor::GetOrderImpl,
        };
        return &LevelOrderAccessorImpl;
    }

    struct LevelOrderPeer {
        virtual ~LevelOrderPeer() = default;
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
    const GENERATED_ArkUILongPressGestureInterfaceAccessor* GetLongPressGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUILongPressGestureInterfaceAccessor LongPressGestureInterfaceAccessorImpl {
            LongPressGestureInterfaceAccessor::DestroyPeerImpl,
            LongPressGestureInterfaceAccessor::ConstructImpl,
            LongPressGestureInterfaceAccessor::GetFinalizerImpl,
            LongPressGestureInterfaceAccessor::OnActionImpl,
            LongPressGestureInterfaceAccessor::OnActionEndImpl,
            LongPressGestureInterfaceAccessor::OnActionCancel0Impl,
            LongPressGestureInterfaceAccessor::OnActionCancel1Impl,
        };
        return &LongPressGestureInterfaceAccessorImpl;
    }

    struct LongPressGestureInterfacePeer {
        virtual ~LongPressGestureInterfacePeer() = default;
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
            Matrix2DAccessor::GetRotateYImpl,
            Matrix2DAccessor::SetRotateYImpl,
            Matrix2DAccessor::GetRotateXImpl,
            Matrix2DAccessor::SetRotateXImpl,
            Matrix2DAccessor::GetScaleYImpl,
            Matrix2DAccessor::SetScaleYImpl,
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
    const GENERATED_ArkUIMatrix4_Matrix4TransitAccessor* GetMatrix4_Matrix4TransitAccessor()
    {
        static const GENERATED_ArkUIMatrix4_Matrix4TransitAccessor Matrix4_Matrix4TransitAccessorImpl {
            matrix4_Matrix4TransitAccessor::DestroyPeerImpl,
            matrix4_Matrix4TransitAccessor::ConstructImpl,
            matrix4_Matrix4TransitAccessor::GetFinalizerImpl,
            matrix4_Matrix4TransitAccessor::CopyImpl,
            matrix4_Matrix4TransitAccessor::InvertImpl,
            matrix4_Matrix4TransitAccessor::CombineImpl,
            matrix4_Matrix4TransitAccessor::TranslateImpl,
            matrix4_Matrix4TransitAccessor::ScaleImpl,
            matrix4_Matrix4TransitAccessor::SkewImpl,
            matrix4_Matrix4TransitAccessor::RotateImpl,
            matrix4_Matrix4TransitAccessor::TransformPointImpl,
            matrix4_Matrix4TransitAccessor::SetPolyToPolyImpl,
        };
        return &Matrix4_Matrix4TransitAccessorImpl;
    }

    struct Matrix4_Matrix4TransitPeer {
        virtual ~Matrix4_Matrix4TransitPeer() = default;
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
    const GENERATED_ArkUINodeContentAccessor* GetNodeContentAccessor()
    {
        static const GENERATED_ArkUINodeContentAccessor NodeContentAccessorImpl {
            NodeContentAccessor::DestroyPeerImpl,
            NodeContentAccessor::ConstructImpl,
            NodeContentAccessor::GetFinalizerImpl,
            NodeContentAccessor::AddFrameNodeImpl,
            NodeContentAccessor::RemoveFrameNodeImpl,
        };
        return &NodeContentAccessorImpl;
    }

    struct NodeContentPeer {
        virtual ~NodeContentPeer() = default;
    };
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
    const GENERATED_ArkUIPageLifeCycleAccessor* GetPageLifeCycleAccessor()
    {
        static const GENERATED_ArkUIPageLifeCycleAccessor PageLifeCycleAccessorImpl {
            PageLifeCycleAccessor::DestroyPeerImpl,
            PageLifeCycleAccessor::ConstructImpl,
            PageLifeCycleAccessor::GetFinalizerImpl,
            PageLifeCycleAccessor::OnPageShowImpl,
            PageLifeCycleAccessor::OnPageHideImpl,
            PageLifeCycleAccessor::OnBackPressImpl,
            PageLifeCycleAccessor::PageTransitionImpl,
            PageLifeCycleAccessor::OnNewParamImpl,
        };
        return &PageLifeCycleAccessorImpl;
    }

    struct PageLifeCyclePeer {
        virtual ~PageLifeCyclePeer() = default;
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
    const GENERATED_ArkUIPanGestureInterfaceAccessor* GetPanGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUIPanGestureInterfaceAccessor PanGestureInterfaceAccessorImpl {
            PanGestureInterfaceAccessor::DestroyPeerImpl,
            PanGestureInterfaceAccessor::ConstructImpl,
            PanGestureInterfaceAccessor::GetFinalizerImpl,
            PanGestureInterfaceAccessor::OnActionStartImpl,
            PanGestureInterfaceAccessor::OnActionUpdateImpl,
            PanGestureInterfaceAccessor::OnActionEndImpl,
            PanGestureInterfaceAccessor::OnActionCancel0Impl,
            PanGestureInterfaceAccessor::OnActionCancel1Impl,
        };
        return &PanGestureInterfaceAccessorImpl;
    }

    struct PanGestureInterfacePeer {
        virtual ~PanGestureInterfacePeer() = default;
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
    const GENERATED_ArkUIPathShapeAccessor* GetPathShapeAccessor()
    {
        static const GENERATED_ArkUIPathShapeAccessor PathShapeAccessorImpl {
            PathShapeAccessor::DestroyPeerImpl,
            PathShapeAccessor::ConstructImpl,
            PathShapeAccessor::GetFinalizerImpl,
            PathShapeAccessor::OffsetImpl,
            PathShapeAccessor::FillImpl,
            PathShapeAccessor::PositionImpl,
            PathShapeAccessor::CommandsImpl,
        };
        return &PathShapeAccessorImpl;
    }

    struct PathShapePeer {
        virtual ~PathShapePeer() = default;
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
    const GENERATED_ArkUIPinchGestureInterfaceAccessor* GetPinchGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUIPinchGestureInterfaceAccessor PinchGestureInterfaceAccessorImpl {
            PinchGestureInterfaceAccessor::DestroyPeerImpl,
            PinchGestureInterfaceAccessor::ConstructImpl,
            PinchGestureInterfaceAccessor::GetFinalizerImpl,
            PinchGestureInterfaceAccessor::OnActionStartImpl,
            PinchGestureInterfaceAccessor::OnActionUpdateImpl,
            PinchGestureInterfaceAccessor::OnActionEndImpl,
            PinchGestureInterfaceAccessor::OnActionCancel0Impl,
            PinchGestureInterfaceAccessor::OnActionCancel1Impl,
        };
        return &PinchGestureInterfaceAccessorImpl;
    }

    struct PinchGestureInterfacePeer {
        virtual ~PinchGestureInterfacePeer() = default;
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
    const GENERATED_ArkUIPromptActionAccessor* GetPromptActionAccessor()
    {
        static const GENERATED_ArkUIPromptActionAccessor PromptActionAccessorImpl {
            PromptActionAccessor::DestroyPeerImpl,
            PromptActionAccessor::ConstructImpl,
            PromptActionAccessor::GetFinalizerImpl,
            PromptActionAccessor::OpenPopupImpl,
            PromptActionAccessor::UpatePopupImpl,
            PromptActionAccessor::ClosePopupImpl,
            PromptActionAccessor::OpenMenuImpl,
            PromptActionAccessor::UpdateMenuImpl,
            PromptActionAccessor::CloseMenuImpl,
        };
        return &PromptActionAccessorImpl;
    }

    struct PromptActionPeer {
        virtual ~PromptActionPeer() = default;
    };
    const GENERATED_ArkUIRectShapeAccessor* GetRectShapeAccessor()
    {
        static const GENERATED_ArkUIRectShapeAccessor RectShapeAccessorImpl {
            RectShapeAccessor::DestroyPeerImpl,
            RectShapeAccessor::ConstructImpl,
            RectShapeAccessor::GetFinalizerImpl,
            RectShapeAccessor::OffsetImpl,
            RectShapeAccessor::FillImpl,
            RectShapeAccessor::PositionImpl,
            RectShapeAccessor::WidthImpl,
            RectShapeAccessor::HeightImpl,
            RectShapeAccessor::SizeImpl,
            RectShapeAccessor::RadiusWidthImpl,
            RectShapeAccessor::RadiusHeightImpl,
            RectShapeAccessor::RadiusImpl,
        };
        return &RectShapeAccessorImpl;
    }

    struct RectShapePeer {
        virtual ~RectShapePeer() = default;
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
    const GENERATED_ArkUIRenderNodeAccessor* GetRenderNodeAccessor()
    {
        static const GENERATED_ArkUIRenderNodeAccessor RenderNodeAccessorImpl {
            RenderNodeAccessor::DestroyPeerImpl,
            RenderNodeAccessor::ConstructImpl,
            RenderNodeAccessor::GetFinalizerImpl,
            RenderNodeAccessor::AppendChildImpl,
            RenderNodeAccessor::InsertChildAfterImpl,
            RenderNodeAccessor::RemoveChildImpl,
            RenderNodeAccessor::ClearChildrenImpl,
            RenderNodeAccessor::GetChildImpl,
            RenderNodeAccessor::GetFirstChildImpl,
            RenderNodeAccessor::GetNextSiblingImpl,
            RenderNodeAccessor::GetPreviousSiblingImpl,
            RenderNodeAccessor::DrawImpl,
            RenderNodeAccessor::InvalidateImpl,
            RenderNodeAccessor::DisposeImpl,
            RenderNodeAccessor::GetBackgroundColorImpl,
            RenderNodeAccessor::SetBackgroundColorImpl,
            RenderNodeAccessor::GetClipToFrameImpl,
            RenderNodeAccessor::SetClipToFrameImpl,
            RenderNodeAccessor::GetOpacityImpl,
            RenderNodeAccessor::SetOpacityImpl,
            RenderNodeAccessor::GetSizeImpl,
            RenderNodeAccessor::SetSizeImpl,
            RenderNodeAccessor::GetPositionImpl,
            RenderNodeAccessor::SetPositionImpl,
            RenderNodeAccessor::GetFrameImpl,
            RenderNodeAccessor::SetFrameImpl,
            RenderNodeAccessor::GetPivotImpl,
            RenderNodeAccessor::SetPivotImpl,
            RenderNodeAccessor::GetScaleImpl,
            RenderNodeAccessor::SetScaleImpl,
            RenderNodeAccessor::GetTranslationImpl,
            RenderNodeAccessor::SetTranslationImpl,
            RenderNodeAccessor::GetRotationImpl,
            RenderNodeAccessor::SetRotationImpl,
            RenderNodeAccessor::GetTransformImpl,
            RenderNodeAccessor::SetTransformImpl,
            RenderNodeAccessor::GetShadowColorImpl,
            RenderNodeAccessor::SetShadowColorImpl,
            RenderNodeAccessor::GetShadowOffsetImpl,
            RenderNodeAccessor::SetShadowOffsetImpl,
            RenderNodeAccessor::GetLabelImpl,
            RenderNodeAccessor::SetLabelImpl,
            RenderNodeAccessor::GetShadowAlphaImpl,
            RenderNodeAccessor::SetShadowAlphaImpl,
            RenderNodeAccessor::GetShadowElevationImpl,
            RenderNodeAccessor::SetShadowElevationImpl,
            RenderNodeAccessor::GetShadowRadiusImpl,
            RenderNodeAccessor::SetShadowRadiusImpl,
            RenderNodeAccessor::GetBorderStyleImpl,
            RenderNodeAccessor::SetBorderStyleImpl,
            RenderNodeAccessor::GetBorderWidthImpl,
            RenderNodeAccessor::SetBorderWidthImpl,
            RenderNodeAccessor::GetBorderColorImpl,
            RenderNodeAccessor::SetBorderColorImpl,
            RenderNodeAccessor::GetBorderRadiusImpl,
            RenderNodeAccessor::SetBorderRadiusImpl,
            RenderNodeAccessor::GetShapeMaskImpl,
            RenderNodeAccessor::SetShapeMaskImpl,
            RenderNodeAccessor::GetShapeClipImpl,
            RenderNodeAccessor::SetShapeClipImpl,
            RenderNodeAccessor::GetMarkNodeGroupImpl,
            RenderNodeAccessor::SetMarkNodeGroupImpl,
            RenderNodeAccessor::GetLengthMetricsUnitImpl,
            RenderNodeAccessor::SetLengthMetricsUnitImpl,
        };
        return &RenderNodeAccessorImpl;
    }

    struct RenderNodePeer {
        virtual ~RenderNodePeer() = default;
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
    const GENERATED_ArkUISceneAccessor* GetSceneAccessor()
    {
        static const GENERATED_ArkUISceneAccessor SceneAccessorImpl {
            SceneAccessor::DestroyPeerImpl,
            SceneAccessor::ConstructImpl,
            SceneAccessor::GetFinalizerImpl,
            SceneAccessor::LoadImpl,
            SceneAccessor::DestroyImpl,
        };
        return &SceneAccessorImpl;
    }

    struct ScenePeer {
        virtual ~ScenePeer() = default;
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

    const GENERATED_ArkUIShapeClipAccessor* GetShapeClipAccessor()
    {
        static const GENERATED_ArkUIShapeClipAccessor ShapeClipAccessorImpl {
            ShapeClipAccessor::DestroyPeerImpl,
            ShapeClipAccessor::ConstructImpl,
            ShapeClipAccessor::GetFinalizerImpl,
            ShapeClipAccessor::SetRectShapeImpl,
            ShapeClipAccessor::SetRoundRectShapeImpl,
            ShapeClipAccessor::SetCircleShapeImpl,
            ShapeClipAccessor::SetOvalShapeImpl,
            ShapeClipAccessor::SetCommandPathImpl,
        };
        return &ShapeClipAccessorImpl;
    }

    struct ShapeClipPeer {
        virtual ~ShapeClipPeer() = default;
    };
    const GENERATED_ArkUIShapeMaskAccessor* GetShapeMaskAccessor()
    {
        static const GENERATED_ArkUIShapeMaskAccessor ShapeMaskAccessorImpl {
            ShapeMaskAccessor::DestroyPeerImpl,
            ShapeMaskAccessor::ConstructImpl,
            ShapeMaskAccessor::GetFinalizerImpl,
            ShapeMaskAccessor::SetRectShapeImpl,
            ShapeMaskAccessor::SetRoundRectShapeImpl,
            ShapeMaskAccessor::SetCircleShapeImpl,
            ShapeMaskAccessor::SetOvalShapeImpl,
            ShapeMaskAccessor::SetCommandPathImpl,
            ShapeMaskAccessor::GetFillColorImpl,
            ShapeMaskAccessor::SetFillColorImpl,
            ShapeMaskAccessor::GetStrokeColorImpl,
            ShapeMaskAccessor::SetStrokeColorImpl,
            ShapeMaskAccessor::GetStrokeWidthImpl,
            ShapeMaskAccessor::SetStrokeWidthImpl,
        };
        return &ShapeMaskAccessorImpl;
    }

    struct ShapeMaskPeer {
        virtual ~ShapeMaskPeer() = default;
    };
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
            SslErrorHandlerAccessor::HandleCancelImpl,
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
    const GENERATED_ArkUITapGestureEventAccessor* GetTapGestureEventAccessor()
    {
        static const GENERATED_ArkUITapGestureEventAccessor TapGestureEventAccessorImpl {
            TapGestureEventAccessor::DestroyPeerImpl,
            TapGestureEventAccessor::ConstructImpl,
            TapGestureEventAccessor::GetFinalizerImpl,
        };
        return &TapGestureEventAccessorImpl;
    }

    struct TapGestureEventPeer {
        virtual ~TapGestureEventPeer() = default;
    };
    const GENERATED_ArkUITapGestureInterfaceAccessor* GetTapGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUITapGestureInterfaceAccessor TapGestureInterfaceAccessorImpl {
            TapGestureInterfaceAccessor::DestroyPeerImpl,
            TapGestureInterfaceAccessor::ConstructImpl,
            TapGestureInterfaceAccessor::GetFinalizerImpl,
            TapGestureInterfaceAccessor::OnActionImpl,
        };
        return &TapGestureInterfaceAccessorImpl;
    }

    struct TapGestureInterfacePeer {
        virtual ~TapGestureInterfacePeer() = default;
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
    const GENERATED_ArkUIText_FontCollectionAccessor* GetText_FontCollectionAccessor()
    {
        static const GENERATED_ArkUIText_FontCollectionAccessor Text_FontCollectionAccessorImpl {
            text_FontCollectionAccessor::DestroyPeerImpl,
            text_FontCollectionAccessor::ConstructImpl,
            text_FontCollectionAccessor::GetFinalizerImpl,
            text_FontCollectionAccessor::GetGlobalInstanceImpl,
            text_FontCollectionAccessor::LoadFontSyncImpl,
            text_FontCollectionAccessor::LoadFontImpl,
            text_FontCollectionAccessor::ClearCachesImpl,
        };
        return &Text_FontCollectionAccessorImpl;
    }

    struct Text_FontCollectionPeer {
        virtual ~Text_FontCollectionPeer() = default;
    };
    const GENERATED_ArkUIText_LineTypesetAccessor* GetText_LineTypesetAccessor()
    {
        static const GENERATED_ArkUIText_LineTypesetAccessor Text_LineTypesetAccessorImpl {
            text_LineTypesetAccessor::DestroyPeerImpl,
            text_LineTypesetAccessor::ConstructImpl,
            text_LineTypesetAccessor::GetFinalizerImpl,
            text_LineTypesetAccessor::GetLineBreakImpl,
            text_LineTypesetAccessor::CreateLineImpl,
        };
        return &Text_LineTypesetAccessorImpl;
    }

    struct Text_LineTypesetPeer {
        virtual ~Text_LineTypesetPeer() = default;
    };
    const GENERATED_ArkUIText_ParagraphAccessor* GetText_ParagraphAccessor()
    {
        static const GENERATED_ArkUIText_ParagraphAccessor Text_ParagraphAccessorImpl {
            text_ParagraphAccessor::DestroyPeerImpl,
            text_ParagraphAccessor::ConstructImpl,
            text_ParagraphAccessor::GetFinalizerImpl,
            text_ParagraphAccessor::LayoutSyncImpl,
            text_ParagraphAccessor::LayoutImpl,
            text_ParagraphAccessor::PaintImpl,
            text_ParagraphAccessor::PaintOnPathImpl,
            text_ParagraphAccessor::GetMaxWidthImpl,
            text_ParagraphAccessor::GetHeightImpl,
            text_ParagraphAccessor::GetLongestLineImpl,
            text_ParagraphAccessor::GetLongestLineWithIndentImpl,
            text_ParagraphAccessor::GetMinIntrinsicWidthImpl,
            text_ParagraphAccessor::GetMaxIntrinsicWidthImpl,
            text_ParagraphAccessor::GetAlphabeticBaselineImpl,
            text_ParagraphAccessor::GetIdeographicBaselineImpl,
            text_ParagraphAccessor::GetRectsForRangeImpl,
            text_ParagraphAccessor::GetRectsForPlaceholdersImpl,
            text_ParagraphAccessor::GetGlyphPositionAtCoordinateImpl,
            text_ParagraphAccessor::GetWordBoundaryImpl,
            text_ParagraphAccessor::GetLineCountImpl,
            text_ParagraphAccessor::GetLineHeightImpl,
            text_ParagraphAccessor::GetLineWidthImpl,
            text_ParagraphAccessor::DidExceedMaxLinesImpl,
            text_ParagraphAccessor::GetTextLinesImpl,
            text_ParagraphAccessor::GetActualTextRangeImpl,
            text_ParagraphAccessor::GetLineMetrics0Impl,
            text_ParagraphAccessor::GetLineMetrics1Impl,
        };
        return &Text_ParagraphAccessorImpl;
    }

    struct Text_ParagraphPeer {
        virtual ~Text_ParagraphPeer() = default;
    };
    const GENERATED_ArkUIText_ParagraphBuilderAccessor* GetText_ParagraphBuilderAccessor()
    {
        static const GENERATED_ArkUIText_ParagraphBuilderAccessor Text_ParagraphBuilderAccessorImpl {
            text_ParagraphBuilderAccessor::DestroyPeerImpl,
            text_ParagraphBuilderAccessor::ConstructImpl,
            text_ParagraphBuilderAccessor::GetFinalizerImpl,
            text_ParagraphBuilderAccessor::PushStyleImpl,
            text_ParagraphBuilderAccessor::PopStyleImpl,
            text_ParagraphBuilderAccessor::AddTextImpl,
            text_ParagraphBuilderAccessor::AddPlaceholderImpl,
            text_ParagraphBuilderAccessor::BuildImpl,
            text_ParagraphBuilderAccessor::BuildLineTypesetImpl,
            text_ParagraphBuilderAccessor::AddSymbolImpl,
        };
        return &Text_ParagraphBuilderAccessorImpl;
    }

    struct Text_ParagraphBuilderPeer {
        virtual ~Text_ParagraphBuilderPeer() = default;
    };
    const GENERATED_ArkUIText_RunAccessor* GetText_RunAccessor()
    {
        static const GENERATED_ArkUIText_RunAccessor Text_RunAccessorImpl {
            text_RunAccessor::DestroyPeerImpl,
            text_RunAccessor::ConstructImpl,
            text_RunAccessor::GetFinalizerImpl,
            text_RunAccessor::GetGlyphCountImpl,
            text_RunAccessor::GetGlyphs0Impl,
            text_RunAccessor::GetGlyphs1Impl,
            text_RunAccessor::GetPositions0Impl,
            text_RunAccessor::GetPositions1Impl,
            text_RunAccessor::GetOffsetsImpl,
            text_RunAccessor::GetFontImpl,
            text_RunAccessor::PaintImpl,
            text_RunAccessor::GetStringIndicesImpl,
            text_RunAccessor::GetStringRangeImpl,
            text_RunAccessor::GetTypographicBoundsImpl,
            text_RunAccessor::GetImageBoundsImpl,
        };
        return &Text_RunAccessorImpl;
    }

    struct Text_RunPeer {
        virtual ~Text_RunPeer() = default;
    };
    const GENERATED_ArkUIText_TextLineAccessor* GetText_TextLineAccessor()
    {
        static const GENERATED_ArkUIText_TextLineAccessor Text_TextLineAccessorImpl {
            text_TextLineAccessor::DestroyPeerImpl,
            text_TextLineAccessor::ConstructImpl,
            text_TextLineAccessor::GetFinalizerImpl,
            text_TextLineAccessor::GetGlyphCountImpl,
            text_TextLineAccessor::GetTextRangeImpl,
            text_TextLineAccessor::GetGlyphRunsImpl,
            text_TextLineAccessor::PaintImpl,
            text_TextLineAccessor::CreateTruncatedLineImpl,
            text_TextLineAccessor::GetTypographicBoundsImpl,
            text_TextLineAccessor::GetImageBoundsImpl,
            text_TextLineAccessor::GetTrailingSpaceWidthImpl,
            text_TextLineAccessor::GetStringIndexForPositionImpl,
            text_TextLineAccessor::GetOffsetForStringIndexImpl,
            text_TextLineAccessor::EnumerateCaretOffsetsImpl,
            text_TextLineAccessor::GetAlignmentOffsetImpl,
        };
        return &Text_TextLineAccessorImpl;
    }

    struct Text_TextLinePeer {
        virtual ~Text_TextLinePeer() = default;
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
    const GENERATED_ArkUITextMenuControllerAccessor* GetTextMenuControllerAccessor()
    {
        static const GENERATED_ArkUITextMenuControllerAccessor TextMenuControllerAccessorImpl {
            TextMenuControllerAccessor::DestroyPeerImpl,
            TextMenuControllerAccessor::ConstructImpl,
            TextMenuControllerAccessor::GetFinalizerImpl,
            TextMenuControllerAccessor::SetMenuOptionsImpl,
        };
        return &TextMenuControllerAccessorImpl;
    }

    struct TextMenuControllerPeer {
        virtual ~TextMenuControllerPeer() = default;
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
    const GENERATED_ArkUIThemeControlAccessor* GetThemeControlAccessor()
    {
        static const GENERATED_ArkUIThemeControlAccessor ThemeControlAccessorImpl {
            ThemeControlAccessor::DestroyPeerImpl,
            ThemeControlAccessor::ConstructImpl,
            ThemeControlAccessor::GetFinalizerImpl,
            ThemeControlAccessor::SetDefaultThemeImpl,
        };
        return &ThemeControlAccessorImpl;
    }

    struct ThemeControlPeer {
        virtual ~ThemeControlPeer() = default;
    };
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
            TouchEventAccessor::GetStopPropagationImpl,
            TouchEventAccessor::SetStopPropagationImpl,
            TouchEventAccessor::GetPreventDefaultImpl,
            TouchEventAccessor::SetPreventDefaultImpl,
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
    const GENERATED_ArkUIUIContextAccessor* GetUIContextAccessor()
    {
        static const GENERATED_ArkUIUIContextAccessor UIContextAccessorImpl {
            UIContextAccessor::DestroyPeerImpl,
            UIContextAccessor::ConstructImpl,
            UIContextAccessor::GetFinalizerImpl,
            UIContextAccessor::GetFontImpl,
            UIContextAccessor::GetFilteredInspectorTreeImpl,
            UIContextAccessor::GetFilteredInspectorTreeByIdImpl,
            UIContextAccessor::AnimateToImpl,
            UIContextAccessor::ShowTextPickerDialogImpl,
            UIContextAccessor::RunScopedTaskImpl,
            UIContextAccessor::AnimateToImmediatelyImpl,
            UIContextAccessor::GetFrameNodeByIdImpl,
            UIContextAccessor::GetAttachedFrameNodeByIdImpl,
            UIContextAccessor::GetFrameNodeByUniqueIdImpl,
            UIContextAccessor::Vp2pxImpl,
            UIContextAccessor::Px2vpImpl,
            UIContextAccessor::Fp2pxImpl,
            UIContextAccessor::Px2fpImpl,
            UIContextAccessor::Lpx2pxImpl,
            UIContextAccessor::Px2lpxImpl,
            UIContextAccessor::GetHostContextImpl,
            UIContextAccessor::SetDynamicDimmingImpl,
            UIContextAccessor::GetWindowNameImpl,
            UIContextAccessor::GetWindowWidthBreakpointImpl,
            UIContextAccessor::GetWindowHeightBreakpointImpl,
            UIContextAccessor::OpenBindSheetImpl,
            UIContextAccessor::UpdateBindSheetImpl,
            UIContextAccessor::CloseBindSheetImpl,
            UIContextAccessor::ClearResourceCacheImpl,
            UIContextAccessor::IsFollowingSystemFontScaleImpl,
            UIContextAccessor::GetMaxFontScaleImpl,
        };
        return &UIContextAccessorImpl;
    }

    struct UIContextPeer {
        virtual ~UIContextPeer() = default;
    };
    const GENERATED_ArkUIUIContextAtomicServiceBarAccessor* GetUIContextAtomicServiceBarAccessor()
    {
        static const GENERATED_ArkUIUIContextAtomicServiceBarAccessor UIContextAtomicServiceBarAccessorImpl {
            UIContextAtomicServiceBarAccessor::GetBarRectImpl,
        };
        return &UIContextAtomicServiceBarAccessorImpl;
    }

    const GENERATED_ArkUIUiEffect_VisualEffectAccessor* GetUiEffect_VisualEffectAccessor()
    {
        static const GENERATED_ArkUIUiEffect_VisualEffectAccessor UiEffect_VisualEffectAccessorImpl {
            uiEffect_VisualEffectAccessor::DestroyPeerImpl,
            uiEffect_VisualEffectAccessor::ConstructImpl,
            uiEffect_VisualEffectAccessor::GetFinalizerImpl,
            uiEffect_VisualEffectAccessor::BackgroundColorBlenderImpl,
        };
        return &UiEffect_VisualEffectAccessorImpl;
    }

    struct UiEffect_VisualEffectPeer {
        virtual ~UiEffect_VisualEffectPeer() = default;
    };
    const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor()
    {
        static const GENERATED_ArkUIUIExtensionProxyAccessor UIExtensionProxyAccessorImpl {
            UIExtensionProxyAccessor::DestroyPeerImpl,
            UIExtensionProxyAccessor::ConstructImpl,
            UIExtensionProxyAccessor::GetFinalizerImpl,
            UIExtensionProxyAccessor::SendImpl,
            UIExtensionProxyAccessor::SendSyncImpl,
            UIExtensionProxyAccessor::OnAsyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OnSyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OffAsyncReceiverRegisterImpl,
            UIExtensionProxyAccessor::OffSyncReceiverRegisterImpl,
        };
        return &UIExtensionProxyAccessorImpl;
    }

    struct UIExtensionProxyPeer {
        virtual ~UIExtensionProxyPeer() = default;
    };
    const GENERATED_ArkUIUnifiedDataChannel_UnifiedDataAccessor* GetUnifiedDataChannel_UnifiedDataAccessor()
    {
        static const GENERATED_ArkUIUnifiedDataChannel_UnifiedDataAccessor UnifiedDataChannel_UnifiedDataAccessorImpl {
            unifiedDataChannel_UnifiedDataAccessor::DestroyPeerImpl,
            unifiedDataChannel_UnifiedDataAccessor::ConstructImpl,
            unifiedDataChannel_UnifiedDataAccessor::GetFinalizerImpl,
            unifiedDataChannel_UnifiedDataAccessor::HasTypeImpl,
            unifiedDataChannel_UnifiedDataAccessor::GetTypesImpl,
        };
        return &UnifiedDataChannel_UnifiedDataAccessorImpl;
    }

    struct UnifiedDataChannel_UnifiedDataPeer {
        virtual ~UnifiedDataChannel_UnifiedDataPeer() = default;
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
    const GENERATED_ArkUIUserDataSpanAccessor* GetUserDataSpanAccessor()
    {
        static const GENERATED_ArkUIUserDataSpanAccessor UserDataSpanAccessorImpl {
            UserDataSpanAccessor::DestroyPeerImpl,
            UserDataSpanAccessor::ConstructImpl,
            UserDataSpanAccessor::GetFinalizerImpl,
        };
        return &UserDataSpanAccessorImpl;
    }

    struct UserDataSpanPeer {
        virtual ~UserDataSpanPeer() = default;
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
            VideoControllerAccessor::SetCurrentTime0Impl,
            VideoControllerAccessor::RequestFullscreenImpl,
            VideoControllerAccessor::ExitFullscreenImpl,
            VideoControllerAccessor::SetCurrentTime1Impl,
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
        };
        return &WebContextMenuResultAccessorImpl;
    }

    struct WebContextMenuResultPeer {
        virtual ~WebContextMenuResultPeer() = default;
    };
    const GENERATED_ArkUIWebCookieAccessor* GetWebCookieAccessor()
    {
        static const GENERATED_ArkUIWebCookieAccessor WebCookieAccessorImpl {
            WebCookieAccessor::DestroyPeerImpl,
            WebCookieAccessor::ConstructImpl,
            WebCookieAccessor::GetFinalizerImpl,
            WebCookieAccessor::SetCookieImpl,
            WebCookieAccessor::SaveCookieImpl,
        };
        return &WebCookieAccessorImpl;
    }

    struct WebCookiePeer {
        virtual ~WebCookiePeer() = default;
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
    const GENERATED_ArkUIWebview_WebviewControllerAccessor* GetWebview_WebviewControllerAccessor()
    {
        static const GENERATED_ArkUIWebview_WebviewControllerAccessor Webview_WebviewControllerAccessorImpl {
            webview_WebviewControllerAccessor::DestroyPeerImpl,
            webview_WebviewControllerAccessor::ConstructImpl,
            webview_WebviewControllerAccessor::GetFinalizerImpl,
            webview_WebviewControllerAccessor::InitializeWebEngineImpl,
            webview_WebviewControllerAccessor::LoadUrlImpl,
        };
        return &Webview_WebviewControllerAccessorImpl;
    }

    struct Webview_WebviewControllerPeer {
        virtual ~Webview_WebviewControllerPeer() = default;
    };
    const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
    {
        static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
            XComponentControllerAccessor::DestroyPeerImpl,
            XComponentControllerAccessor::ConstructImpl,
            XComponentControllerAccessor::GetFinalizerImpl,
            XComponentControllerAccessor::GetXComponentSurfaceIdImpl,
            XComponentControllerAccessor::GetXComponentContextImpl,
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
            GlobalScopeAccessor::ApplyStylesImpl,
            GlobalScopeAccessor::BindCompatibleProvideCallbackImpl,
            GlobalScopeAccessor::BorderRadiusesImpl,
            GlobalScopeAccessor::BorderStylesImpl,
            GlobalScopeAccessor::CompatibleComponentImpl,
            GlobalScopeAccessor::CompatibleWrappedBuilderImpl,
            GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
            GlobalScopeAccessor::CursorControl_setCursorImpl,
            GlobalScopeAccessor::EdgeColorsImpl,
            GlobalScopeAccessor::EdgeWidthsImpl,
            GlobalScopeAccessor::FocusControl_requestFocusImpl,
            GlobalScopeAccessor::Font_getUIFontConfigImpl,
            GlobalScopeAccessor::GetCompatibleStateImpl,
            GlobalScopeAccessor::GetRectangleByIdImpl,
            GlobalScopeAccessor::PostCardActionImpl,
            GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
            GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
            GlobalScopeAccessor::Px2vpImpl,
            GlobalScopeAccessor::SetAppBgColorImpl,
            GlobalScopeAccessor::Text_getFontDescriptorByFullNameImpl,
            GlobalScopeAccessor::Text_getSystemFontFullNamesByTypeImpl,
            GlobalScopeAccessor::Text_matchFontDescriptorsImpl,
            GlobalScopeAccessor::UiEffect_createBrightnessBlenderImpl,
            GlobalScopeAccessor::UiEffect_createEffectImpl,
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
            GetAnimationExtenderAccessor,
            GetAppearSymbolEffectAccessor,
            GetAxisEventAccessor,
            GetBackgroundColorStyleAccessor,
            GetBaseContextAccessor,
            GetBaseCustomDialogAccessor,
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
            GetCircleShapeAccessor,
            GetClickEventAccessor,
            GetClientAuthenticationHandlerAccessor,
            GetColorContentAccessor,
            GetColorFilterAccessor,
            GetColorMetricsAccessor,
            GetCommon_ContextAccessor,
            GetCommonShapeAccessor,
            GetComponentContentAccessor,
            GetConsoleMessageAccessor,
            GetContentModifierHelperAccessor,
            GetContextAccessor,
            GetControllerHandlerAccessor,
            GetCurves_ICurveAccessor,
            GetCustomDialogControllerAccessor,
            GetCustomSpanAccessor,
            GetDataResubmissionHandlerAccessor,
            GetDatePickerDialogAccessor,
            GetDecorationStyleAccessor,
            GetDisappearSymbolEffectAccessor,
            GetDismissDialogActionAccessor,
            GetDismissPopupActionAccessor,
            GetDragEventAccessor,
            GetDrawableDescriptorAccessor,
            GetDrawContextAccessor,
            GetDrawing_BrushAccessor,
            GetDrawing_CanvasAccessor,
            GetDrawing_ColorFilterAccessor,
            GetDrawing_FontAccessor,
            GetDrawing_ImageFilterAccessor,
            GetDrawing_LatticeAccessor,
            GetDrawing_MaskFilterAccessor,
            GetDrawing_MatrixAccessor,
            GetDrawing_PathAccessor,
            GetDrawing_PathEffectAccessor,
            GetDrawing_PenAccessor,
            GetDrawing_RegionAccessor,
            GetDrawing_RoundRectAccessor,
            GetDrawing_SamplingOptionsAccessor,
            GetDrawing_ShaderEffectAccessor,
            GetDrawing_ShadowLayerAccessor,
            GetDrawing_TextBlobAccessor,
            GetDrawing_TypefaceAccessor,
            GetDrawingRenderingContextAccessor,
            GetDrawModifierAccessor,
            GetEllipseShapeAccessor,
            GetEventEmulatorAccessor,
            GetEventResultAccessor,
            GetEventTargetInfoAccessor,
            GetExtendableComponentAccessor,
            GetFileSelectorParamAccessor,
            GetFileSelectorResultAccessor,
            GetFocusAxisEventAccessor,
            GetFocusControllerAccessor,
            GetFrameNodeAccessor,
            GetFrictionMotionAccessor,
            GetFullScreenExitHandlerAccessor,
            GetGestureAccessor,
            GetGestureEventAccessor,
            GetGestureGroupInterfaceAccessor,
            GetGestureModifierAccessor,
            GetGestureRecognizerAccessor,
            GetGestureStyleAccessor,
            GetGlobalScope_ohos_arkui_componentSnapshotAccessor,
            GetGlobalScope_ohos_arkui_performanceMonitorAccessor,
            GetGlobalScope_ohos_fontAccessor,
            GetGlobalScope_ohos_measure_utilsAccessor,
            GetHierarchicalSymbolEffectAccessor,
            GetHoverEventAccessor,
            GetHttpAuthHandlerAccessor,
            GetImage_PixelMapAccessor,
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
            GetLayoutCallbackAccessor,
            GetLayoutChildAccessor,
            GetLayoutManagerAccessor,
            GetLayoutPolicyAccessor,
            GetLazyForEachOpsAccessor,
            GetLengthMetricsAccessor,
            GetLetterSpacingStyleAccessor,
            GetLevelOrderAccessor,
            GetLifeCycleAccessor,
            GetLinearGradientAccessor,
            GetLinearIndicatorControllerAccessor,
            GetLineHeightStyleAccessor,
            GetListScrollerAccessor,
            GetLongPressGestureEventAccessor,
            GetLongPressGestureInterfaceAccessor,
            GetLongPressRecognizerAccessor,
            GetMatrix2DAccessor,
            GetMatrix4_Matrix4TransitAccessor,
            GetMeasurableAccessor,
            GetMouseEventAccessor,
            GetMutableStyledStringAccessor,
            GetNavDestinationContextAccessor,
            GetNavExtenderAccessor,
            GetNavigationTransitionProxyAccessor,
            GetNavPathInfoAccessor,
            GetNavPathStackAccessor,
            GetNodeContentAccessor,
            GetOffscreenCanvasAccessor,
            GetOffscreenCanvasRenderingContext2DAccessor,
            GetPageLifeCycleAccessor,
            GetPanGestureEventAccessor,
            GetPanGestureInterfaceAccessor,
            GetPanGestureOptionsAccessor,
            GetPanRecognizerAccessor,
            GetParagraphStyleAccessor,
            GetPath2DAccessor,
            GetPathShapeAccessor,
            GetPatternLockControllerAccessor,
            GetPermissionRequestAccessor,
            GetPinchGestureEventAccessor,
            GetPinchGestureInterfaceAccessor,
            GetPinchRecognizerAccessor,
            GetPixelMapMockAccessor,
            GetProgressMaskAccessor,
            GetPromptActionAccessor,
            GetRectShapeAccessor,
            GetRenderingContextSettingsAccessor,
            GetRenderNodeAccessor,
            GetRenderServiceNodeAccessor,
            GetReplaceSymbolEffectAccessor,
            GetRestrictedWorkerAccessor,
            GetRichEditorBaseControllerAccessor,
            GetRichEditorControllerAccessor,
            GetRichEditorStyledStringControllerAccessor,
            GetRotationGestureAccessor,
            GetRotationGestureEventAccessor,
            GetRotationRecognizerAccessor,
            GetScaleSymbolEffectAccessor,
            GetSceneAccessor,
            GetScreenCaptureHandlerAccessor,
            GetScrollableTargetInfoAccessor,
            GetScrollerAccessor,
            GetScrollMotionAccessor,
            GetScrollResultAccessor,
            GetSearchControllerAccessor,
            GetSearchOpsAccessor,
            GetShapeClipAccessor,
            GetShapeMaskAccessor,
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
            GetTapGestureEventAccessor,
            GetTapGestureInterfaceAccessor,
            GetTapRecognizerAccessor,
            GetText_FontCollectionAccessor,
            GetText_LineTypesetAccessor,
            GetText_ParagraphAccessor,
            GetText_ParagraphBuilderAccessor,
            GetText_RunAccessor,
            GetText_TextLineAccessor,
            GetTextAreaControllerAccessor,
            GetTextBaseControllerAccessor,
            GetTextClockControllerAccessor,
            GetTextContentControllerBaseAccessor,
            GetTextControllerAccessor,
            GetTextEditControllerExAccessor,
            GetTextFieldOpsAccessor,
            GetTextInputControllerAccessor,
            GetTextMenuControllerAccessor,
            GetTextMenuItemIdAccessor,
            GetTextPickerDialogAccessor,
            GetTextShadowStyleAccessor,
            GetTextStyleAccessor,
            GetTextTimerControllerAccessor,
            GetThemeControlAccessor,
            GetTimePickerDialogAccessor,
            GetTouchEventAccessor,
            GetTransitionEffectAccessor,
            GetUICommonEventAccessor,
            GetUIContextAccessor,
            GetUIContextAtomicServiceBarAccessor,
            GetUiEffect_VisualEffectAccessor,
            GetUIExtensionProxyAccessor,
            GetUnifiedDataChannel_UnifiedDataAccessor,
            GetUrlStyleAccessor,
            GetUserDataSpanAccessor,
            GetVideoControllerAccessor,
            GetWaterFlowSectionsAccessor,
            GetWebContextMenuParamAccessor,
            GetWebContextMenuResultAccessor,
            GetWebCookieAccessor,
            GetWebKeyboardControllerAccessor,
            GetWebResourceErrorAccessor,
            GetWebResourceRequestAccessor,
            GetWebResourceResponseAccessor,
            GetWebview_WebviewControllerAccessor,
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