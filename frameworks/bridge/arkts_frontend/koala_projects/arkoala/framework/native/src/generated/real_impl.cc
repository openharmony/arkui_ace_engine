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
#include "arkoala_api_generated.h"
#include "securec.h"

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
    if (snprintf_s(hex, sizeof(hex), sizeof(hex) - 1, "0x%llx", (long long)ptr) < 0) {
        return;
    }
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
}

const int MAX_NODE_TYPE = 200;
std::array<Ark_Int64, MAX_NODE_TYPE> createNodeDelay = {};\
std::array<Ark_Int64, MAX_NODE_TYPE> measureNodeDelay = {};
std::array<Ark_Int64, MAX_NODE_TYPE> layoutNodeDelay = {};
std::array<Ark_Int64, MAX_NODE_TYPE> drawNodeDelay = {};

void CheckType(GENERATED_Ark_NodeType type) {
    if (type >= MAX_NODE_TYPE) {
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

void DumpTree(TreeNode *node, Ark_Int32 indent) {
    ARKOALA_LOG("%s[%s: %d]\n", string(indent * 2, ' ').c_str(), node->namePtr(), node->id());
    for (auto child: *node->children()) {
        if (child)
            DumpTree(child, indent + 1);
    }
}

// TODO: remove in favour of callbackCallerInstance!
GENERATED_Ark_APICallbackMethod *callbacks = nullptr;

int TreeNode::_globalId = 1;
string TreeNode::_noAttribute;

Ark_Float32 parseLength(Ark_Float32 parentValue, Ark_Float32 value, Ark_Int32 unit) {
    switch (unit) {
        //PX
        case 0: {
            const Ark_Float32 scale = 1; // TODO: need getting current device scale
            return value * scale;
        }
        //PERCENTAGE
        case 3: {
            return parentValue / 100 * value;
        }
        default:
            // VP, FP, LPX, UndefinedDimensionUnit: TODO: parse properly this units
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

    // TODO: use return flag for dirty bits propagation.
    return 0;
}

Ark_CanvasHandle getCanvas(TreeNode* node) {
    // TODO: real canvas.
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

    // TODO: use return flag for dirty bits propagation.
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

    // TODO: implement test
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
            std::this_thread::sleep_for(std::chrono::seconds(1));
            callback(pipelineContext);
        }
    });
    producer.detach();
}
void SetChildTotalCount(Ark_NodeHandle node, Ark_Int32 totalCount) {}
void ShowCrash(Ark_CharPtr message) {}
}

Ark_NativePointer NeedMoreElements(Ark_NativePointer node,
                                   Ark_NativePointer mark,
                                   Ark_Int32 direction) {
    return AsNode(node)->needMoreElements(mark, direction);
}

struct NodeData {
    Callback_RangeUpdate updater;
    NodeData(const Callback_RangeUpdate* updater): updater(*updater) {}
};
void OnRangeUpdate(Ark_NativePointer nodePtr,
                   Ark_Int32 totalCount,
                  const Callback_RangeUpdate* updater) {
    auto* node = AsNode(nodePtr);
    updater->resource.hold(updater->resource.resourceId);
    node->setCustomVoidData(new NodeData(updater));
}

void SetCurrentIndex(Ark_NativePointer nodePtr,
                     Ark_Int32 index) {
    auto* node = AsNode(nodePtr);
    Ark_NativePointer mark = (Ark_NativePointer)0x1;
    if (index >= 0 && index < (int)node->children()->size()) {
        mark = (*node->children())[index];
    }
    NodeData* data = (NodeData*)node->customVoidData();
    if (data) {
        data->updater.call(data->updater.resource.resourceId, index, mark, 1000);
    }
}
}

// handWritten implementations
namespace OHOS::Ace::NG::GeneratedModifier {
    namespace LazyForEachOpsAccessor {
    Ark_NativePointer NeedMoreElementsImpl(Ark_NativePointer node,
                                           Ark_NativePointer mark,
                                           Ark_Int32 direction)
    {
        if (!needGroupedLog(1))
            return (void*) 300;
        string out("NeedMoreElements(");
        WriteToString(&out, node);
        out.append(", ");
        WriteToString(&out, mark);
        out.append(", ");
        WriteToString(&out, direction);
        out.append(") \n");
        out.append("[return (void*) 300] \n");
        appendGroupedLog(1, out);
        return (void*) 300;
    }
    void OnRangeUpdateImpl(Ark_NativePointer node,
                           Ark_Int32 totalCount,
                           const Callback_RangeUpdate* updater)
    {
        if (!needGroupedLog(1))
            return;
        string out("OnRangeUpdate(");
        WriteToString(&out, node);
        out.append(", ");
        WriteToString(&out, totalCount);
        out.append(", ");
        WriteToString(&out, updater);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void SetCurrentIndexImpl(Ark_NativePointer node,
                             Ark_Int32 index)
    {
        if (!needGroupedLog(1))
            return;
        string out("SetCurrentIndex(");
        WriteToString(&out, node);
        out.append(", ");
        WriteToString(&out, index);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void PrepareImpl(Ark_NativePointer node, Ark_Int32 itemCount, Ark_Int32 offset)
    {
        if (!needGroupedLog(1))
            return;
        string out("Prepare(");
        WriteToString(&out, node);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void NotifyChangeImpl(Ark_NativePointer node, Ark_Int32 startIndex, Ark_Int32 endIndex, Ark_Int32 count)
    {
        if (!needGroupedLog(1))
            return;
        string out("NotifyChangeImpl(");
        WriteToString(&out, node);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    } // LazyForEachOpsAccessor

    namespace CommonMethodModifier {
        void OnClick0Impl(Ark_NativePointer node,
                      const Callback_ClickEvent_Void* value)
    {
        RegisterOnClick(node, value);
        if (!needGroupedLog(1))
            return;
        string out("onClick(");
        WriteToString(&out, value);
        out.append(") \n");
        appendGroupedLog(1, out);
    }
    void OnClick1Impl(Ark_NativePointer node,
                      const Callback_ClickEvent_Void* event,
                      const Ark_Number* distanceThreshold)
    {
        RegisterOnClick(node, event);
        if (!needGroupedLog(1))
            return;
        string out("onClick(");
        WriteToString(&out, event);
        out.append(", ");
        WriteToString(&out, distanceThreshold);
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
}

// end of handWritten implementations
namespace OHOS::Ace::NG::GeneratedModifier {
    namespace RootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // RootModifier
    namespace ComponentRootModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // ComponentRootModifier
    namespace AbilityComponentModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // AbilityComponentModifier
    namespace AbilityComponentInterfaceModifier {
    void SetAbilityComponentOptionsImpl(Ark_NativePointer node,
                                        const Ark_Literal_Want_want* value)
    {
    }
    } // AbilityComponentInterfaceModifier
    namespace AbilityComponentAttributeModifier {
    void OnConnectImpl(Ark_NativePointer node,
                       const Callback_Void* value)
    {
    }
    void OnDisconnectImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    } // AbilityComponentAttributeModifier
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
    void OnSelectedImpl(Ark_NativePointer node,
                        const Callback_Number_Void* value)
    {
    }
    void ColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void PopupColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void PopupBackgroundImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void PopupSelectedColorImpl(Ark_NativePointer node,
                                const Ark_ResourceColor* value)
    {
    }
    void PopupUnselectedColorImpl(Ark_NativePointer node,
                                  const Ark_ResourceColor* value)
    {
    }
    void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                      const Ark_ResourceColor* value)
    {
    }
    void UsingPopupImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void SelectedFontImpl(Ark_NativePointer node,
                          const Ark_Font* value)
    {
    }
    void PopupFontImpl(Ark_NativePointer node,
                       const Ark_Font* value)
    {
    }
    void PopupItemFontImpl(Ark_NativePointer node,
                           const Ark_Font* value)
    {
    }
    void ItemSizeImpl(Ark_NativePointer node,
                      const Ark_Union_String_Number* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Ark_Font* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const OnAlphabetIndexerSelectCallback* value)
    {
    }
    void OnRequestPopupDataImpl(Ark_NativePointer node,
                                const OnAlphabetIndexerRequestPopupDataCallback* value)
    {
    }
    void OnPopupSelectImpl(Ark_NativePointer node,
                           const OnAlphabetIndexerPopupSelectCallback* value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void PopupPositionImpl(Ark_NativePointer node,
                           const Ark_Position* value)
    {
    }
    void AutoCollapseImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                                   const Ark_Number* value)
    {
    }
    void ItemBorderRadiusImpl(Ark_NativePointer node,
                              const Ark_Number* value)
    {
    }
    void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                      Ark_BlurStyle value)
    {
    }
    void PopupTitleBackgroundImpl(Ark_NativePointer node,
                                  const Ark_ResourceColor* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void AlignStyleImpl(Ark_NativePointer node,
                        Ark_IndexerAlign value,
                        const Opt_Length* offset)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Number_Void* callback)
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
                   Ark_AnimationStatus value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void CurveImpl(Ark_NativePointer node,
                   Ark_Curve value)
    {
    }
    void DelayImpl(Ark_NativePointer node,
                   const Ark_Number* value)
    {
    }
    void FillModeImpl(Ark_NativePointer node,
                      Ark_FillMode value)
    {
    }
    void IterationsImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void PlayModeImpl(Ark_NativePointer node,
                      Ark_PlayMode value)
    {
    }
    void MotionImpl(Ark_NativePointer node,
                    Ark_SpringMotion value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnRepeatImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnCancelImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnFrameImpl(Ark_NativePointer node,
                     const Callback_Number_Void* value)
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
                   const Ark_ResourceColor* value)
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
                  Ark_ButtonType value)
    {
    }
    void StateEffectImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void ButtonStyleImpl(Ark_NativePointer node,
                         Ark_ButtonStyleMode value)
    {
    }
    void ControlSizeImpl(Ark_NativePointer node,
                         Ark_ControlSize value)
    {
    }
    void RoleImpl(Ark_NativePointer node,
                  Ark_ButtonRole value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void LabelStyleImpl(Ark_NativePointer node,
                        const Ark_LabelStyle* value)
    {
    }
    } // ButtonAttributeModifier
    namespace CalendarModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CalendarModifier
    namespace CalendarInterfaceModifier {
    void SetCalendarOptionsImpl(Ark_NativePointer node,
                                const Ark_Type_CalendarInterface_value* value)
    {
    }
    } // CalendarInterfaceModifier
    namespace CalendarAttributeModifier {
    void ShowLunarImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void ShowHolidayImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void NeedSlideImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void StartOfWeekImpl(Ark_NativePointer node,
                         const Ark_Number* value)
    {
    }
    void OffDaysImpl(Ark_NativePointer node,
                     const Ark_Number* value)
    {
    }
    void DirectionImpl(Ark_NativePointer node,
                       Ark_Axis value)
    {
    }
    void CurrentDayStyleImpl(Ark_NativePointer node,
                             const Ark_CurrentDayStyle* value)
    {
    }
    void NonCurrentDayStyleImpl(Ark_NativePointer node,
                                const Ark_NonCurrentDayStyle* value)
    {
    }
    void TodayStyleImpl(Ark_NativePointer node,
                        const Ark_TodayStyle* value)
    {
    }
    void WeekStyleImpl(Ark_NativePointer node,
                       const Ark_WeekStyle* value)
    {
    }
    void WorkStateStyleImpl(Ark_NativePointer node,
                            const Ark_WorkStateStyle* value)
    {
    }
    void OnSelectChangeImpl(Ark_NativePointer node,
                            const Callback_CalendarSelectedDate_Void* value)
    {
    }
    void OnRequestDataImpl(Ark_NativePointer node,
                           const Callback_CalendarRequestedData_Void* value)
    {
    }
    } // CalendarAttributeModifier
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
                       const Ark_PickerTextStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Date_Void* value)
    {
    }
    void EdgeAlignImpl(Ark_NativePointer node,
                       Ark_CalendarAlign alignType,
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
                     const VoidCallback* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            Ark_Boolean value)
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
                    Ark_Boolean value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void ShapeImpl(Ark_NativePointer node,
                   Ark_CheckBoxShape value)
    {
    }
    void UnselectedColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void MarkImpl(Ark_NativePointer node,
                  const Ark_MarkStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const OnCheckboxChangeCallback* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void _onChangeEvent_selectImpl(Ark_NativePointer node,
                                   const Callback_Boolean_Void* callback)
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
                       Ark_Boolean value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void UnselectedColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void MarkImpl(Ark_NativePointer node,
                  const Ark_MarkStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const OnCheckboxGroupChangeCallback* value)
    {
    }
    void CheckboxShapeImpl(Ark_NativePointer node,
                           Ark_CheckBoxShape value)
    {
    }
    void _onChangeEvent_selectAllImpl(Ark_NativePointer node,
                                      const Callback_Boolean_Void* callback)
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
                              const Opt_ColumnOptions* options)
    {
    }
    } // ColumnInterfaceModifier
    namespace ColumnAttributeModifier {
    void AlignItemsImpl(Ark_NativePointer node,
                        Ark_HorizontalAlign value)
    {
    }
    void JustifyContentImpl(Ark_NativePointer node,
                            Ark_FlexAlign value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Ark_PointLightStyle* value)
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
                        Ark_Boolean value)
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
                   const Ark_Length* value)
    {
    }
    void HeightImpl(Ark_NativePointer node,
                    const Ark_Length* value)
    {
    }
    void DrawModifierImpl(Ark_NativePointer node,
                          const Opt_DrawModifier* value)
    {
    }
    void ResponseRegionImpl(Ark_NativePointer node,
                            const Ark_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void MouseResponseRegionImpl(Ark_NativePointer node,
                                 const Ark_Union_Array_Rectangle_Rectangle* value)
    {
    }
    void SizeImpl(Ark_NativePointer node,
                  const Ark_SizeOptions* value)
    {
    }
    void ConstraintSizeImpl(Ark_NativePointer node,
                            const Ark_ConstraintSizeOptions* value)
    {
    }
    void TouchableImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void HitTestBehaviorImpl(Ark_NativePointer node,
                             Ark_HitTestMode value)
    {
    }
    void OnChildTouchTestImpl(Ark_NativePointer node,
                              const Callback_Array_TouchTestInfo_TouchResult* value)
    {
    }
    void LayoutWeightImpl(Ark_NativePointer node,
                          const Ark_Union_Number_String* value)
    {
    }
    void ChainWeightImpl(Ark_NativePointer node,
                         const Ark_ChainWeightOptions* value)
    {
    }
    void PaddingImpl(Ark_NativePointer node,
                     const Ark_Union_Padding_Length_LocalizedPadding* value)
    {
    }
    void SafeAreaPaddingImpl(Ark_NativePointer node,
                             const Ark_Union_Padding_LengthMetrics_LocalizedPadding* value)
    {
    }
    void MarginImpl(Ark_NativePointer node,
                    const Ark_Union_Margin_Length_LocalizedMargin* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void PixelRoundImpl(Ark_NativePointer node,
                        const Ark_PixelRoundPolicy* value)
    {
    }
    void BackgroundImageSizeImpl(Ark_NativePointer node,
                                 const Ark_Union_SizeOptions_ImageSize* value)
    {
    }
    void BackgroundImagePositionImpl(Ark_NativePointer node,
                                     const Ark_Union_Position_Alignment* value)
    {
    }
    void BackgroundEffectImpl(Ark_NativePointer node,
                              const Ark_BackgroundEffectOptions* value)
    {
    }
    void BackgroundImageResizableImpl(Ark_NativePointer node,
                                      const Ark_ResizableOptions* value)
    {
    }
    void ForegroundEffectImpl(Ark_NativePointer node,
                              const Ark_ForegroundEffectOptions* value)
    {
    }
    void VisualEffectImpl(Ark_NativePointer node,
                          const Ark_VisualEffect* value)
    {
    }
    void BackgroundFilterImpl(Ark_NativePointer node,
                              const Ark_Filter* value)
    {
    }
    void ForegroundFilterImpl(Ark_NativePointer node,
                              const Ark_Filter* value)
    {
    }
    void CompositingFilterImpl(Ark_NativePointer node,
                               const Ark_Filter* value)
    {
    }
    void OpacityImpl(Ark_NativePointer node,
                     const Ark_Union_Number_Resource* value)
    {
    }
    void BorderImpl(Ark_NativePointer node,
                    const Ark_BorderOptions* value)
    {
    }
    void BorderStyleImpl(Ark_NativePointer node,
                         const Ark_Union_BorderStyle_EdgeStyles* value)
    {
    }
    void BorderWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
    {
    }
    void BorderColorImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void BorderRadiusImpl(Ark_NativePointer node,
                          const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
    {
    }
    void BorderImageImpl(Ark_NativePointer node,
                         const Ark_BorderImageOption* value)
    {
    }
    void OutlineImpl(Ark_NativePointer node,
                     const Ark_OutlineOptions* value)
    {
    }
    void OutlineStyleImpl(Ark_NativePointer node,
                          const Ark_Union_OutlineStyle_EdgeOutlineStyles* value)
    {
    }
    void OutlineWidthImpl(Ark_NativePointer node,
                          const Ark_Union_Dimension_EdgeOutlineWidths* value)
    {
    }
    void OutlineColorImpl(Ark_NativePointer node,
                          const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
    {
    }
    void OutlineRadiusImpl(Ark_NativePointer node,
                           const Ark_Union_Dimension_OutlineRadiuses* value)
    {
    }
    void ForegroundColorImpl(Ark_NativePointer node,
                             const Ark_Union_ResourceColor_ColoringStrategy* value)
    {
    }
    void OnHoverImpl(Ark_NativePointer node,
                     const Callback_Boolean_HoverEvent_Void* value)
    {
    }
    void OnAccessibilityHoverImpl(Ark_NativePointer node,
                                  const AccessibilityCallback* value)
    {
    }
    void HoverEffectImpl(Ark_NativePointer node,
                         Ark_HoverEffect value)
    {
    }
    void OnMouseImpl(Ark_NativePointer node,
                     const Callback_MouseEvent_Void* value)
    {
    }
    void OnTouchImpl(Ark_NativePointer node,
                     const Callback_TouchEvent_Void* value)
    {
    }
    void OnKeyEventImpl(Ark_NativePointer node,
                        const Callback_KeyEvent_Void* value)
    {
    }
    void OnKeyPreImeImpl(Ark_NativePointer node,
                         const Callback_KeyEvent_Boolean* value)
    {
    }
    void FocusableImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void OnFocusImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnBlurImpl(Ark_NativePointer node,
                    const Callback_Void* value)
    {
    }
    void TabIndexImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void DefaultFocusImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void GroupDefaultFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void FocusOnTouchImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void FocusBoxImpl(Ark_NativePointer node,
                      const Ark_FocusBoxStyle* value)
    {
    }
    void AnimationImpl(Ark_NativePointer node,
                       const Ark_AnimateParam* value)
    {
    }
    void Transition0Impl(Ark_NativePointer node,
                         const Ark_Union_TransitionOptions_TransitionEffect* value)
    {
    }
    void Transition1Impl(Ark_NativePointer node,
                         Ark_TransitionEffect effect,
                         const Opt_TransitionFinishCallback* onFinish)
    {
    }
    void MotionBlurImpl(Ark_NativePointer node,
                        const Ark_MotionBlurOptions* value)
    {
    }
    void BrightnessImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void ContrastImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void GrayscaleImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void ColorBlendImpl(Ark_NativePointer node,
                        const Ark_Union_Color_String_Resource* value)
    {
    }
    void SaturateImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void SepiaImpl(Ark_NativePointer node,
                   const Ark_Number* value)
    {
    }
    void InvertImpl(Ark_NativePointer node,
                    const Ark_Union_Number_InvertOptions* value)
    {
    }
    void HueRotateImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
    {
    }
    void UseShadowBatchingImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void UseEffect0Impl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void UseEffect1Impl(Ark_NativePointer node,
                        Ark_Boolean useEffect,
                        Ark_EffectType effectType)
    {
    }
    void RenderGroupImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void FreezeImpl(Ark_NativePointer node,
                    Ark_Boolean value)
    {
    }
    void TranslateImpl(Ark_NativePointer node,
                       const Ark_TranslateOptions* value)
    {
    }
    void ScaleImpl(Ark_NativePointer node,
                   const Ark_ScaleOptions* value)
    {
    }
    void GridSpanImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void GridOffsetImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void RotateImpl(Ark_NativePointer node,
                    const Ark_RotateOptions* value)
    {
    }
    void TransformImpl(Ark_NativePointer node,
                       const Ark_CustomObject* value)
    {
    }
    void OnAppearImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnDisAppearImpl(Ark_NativePointer node,
                         const Callback_Void* value)
    {
    }
    void OnAttachImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnDetachImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnAreaChangeImpl(Ark_NativePointer node,
                          const Callback_Area_Area_Void* value)
    {
    }
    void VisibilityImpl(Ark_NativePointer node,
                        Ark_Visibility value)
    {
    }
    void FlexGrowImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void FlexShrinkImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void FlexBasisImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
    {
    }
    void AlignSelfImpl(Ark_NativePointer node,
                       Ark_ItemAlign value)
    {
    }
    void DisplayPriorityImpl(Ark_NativePointer node,
                             const Ark_Number* value)
    {
    }
    void ZIndexImpl(Ark_NativePointer node,
                    const Ark_Number* value)
    {
    }
    void DirectionImpl(Ark_NativePointer node,
                       Ark_Direction value)
    {
    }
    void AlignImpl(Ark_NativePointer node,
                   Ark_Alignment value)
    {
    }
    void PositionImpl(Ark_NativePointer node,
                      const Ark_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void MarkAnchorImpl(Ark_NativePointer node,
                        const Ark_Union_Position_LocalizedPosition* value)
    {
    }
    void OffsetImpl(Ark_NativePointer node,
                    const Ark_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void EnabledImpl(Ark_NativePointer node,
                     Ark_Boolean value)
    {
    }
    void UseSizeTypeImpl(Ark_NativePointer node,
                         const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
    {
    }
    void AlignRules0Impl(Ark_NativePointer node,
                         const Ark_AlignRuleOption* value)
    {
    }
    void AlignRules1Impl(Ark_NativePointer node,
                         const Ark_LocalizedAlignRuleOptions* value)
    {
    }
    void AspectRatioImpl(Ark_NativePointer node,
                         const Ark_Number* value)
    {
    }
    void ClickEffectImpl(Ark_NativePointer node,
                         const Opt_ClickEffect* value)
    {
    }
    void OnDragStartImpl(Ark_NativePointer node,
                         const Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
    {
    }
    void OnDragEnterImpl(Ark_NativePointer node,
                         const Callback_DragEvent_String_Void* value)
    {
    }
    void OnDragMoveImpl(Ark_NativePointer node,
                        const Callback_DragEvent_String_Void* value)
    {
    }
    void OnDragLeaveImpl(Ark_NativePointer node,
                         const Callback_DragEvent_String_Void* value)
    {
    }
    void OnDropImpl(Ark_NativePointer node,
                    const Callback_DragEvent_String_Void* value)
    {
    }
    void OnDragEndImpl(Ark_NativePointer node,
                       const Callback_DragEvent_String_Void* value)
    {
    }
    void AllowDropImpl(Ark_NativePointer node,
                       const Opt_Array_UniformDataType* value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void DragPreviewImpl(Ark_NativePointer node,
                         const Ark_Union_CustomBuilder_DragItemInfo_String* value)
    {
    }
    void OnPreDragImpl(Ark_NativePointer node,
                       const Callback_PreDragStatus_Void* value)
    {
    }
    void LinearGradientImpl(Ark_NativePointer node,
                            const Ark_Type_CommonMethod_linearGradient_value* value)
    {
    }
    void SweepGradientImpl(Ark_NativePointer node,
                           const Ark_Type_CommonMethod_sweepGradient_value* value)
    {
    }
    void RadialGradientImpl(Ark_NativePointer node,
                            const Ark_Type_CommonMethod_radialGradient_value* value)
    {
    }
    void MotionPathImpl(Ark_NativePointer node,
                        const Ark_MotionPathOptions* value)
    {
    }
    void ShadowImpl(Ark_NativePointer node,
                    const Ark_Union_ShadowOptions_ShadowStyle* value)
    {
    }
    void Clip0Impl(Ark_NativePointer node,
                   const Opt_Boolean* value)
    {
    }
    void Clip1Impl(Ark_NativePointer node,
                   const Opt_Boolean* value)
    {
    }
    void ClipShapeImpl(Ark_NativePointer node,
                       const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void Mask0Impl(Ark_NativePointer node,
                   const Opt_ProgressMask* value)
    {
    }
    void Mask1Impl(Ark_NativePointer node,
                   const Opt_ProgressMask* value)
    {
    }
    void MaskShapeImpl(Ark_NativePointer node,
                       const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
    {
    }
    void KeyImpl(Ark_NativePointer node,
                 const Ark_String* value)
    {
    }
    void IdImpl(Ark_NativePointer node,
                const Ark_String* value)
    {
    }
    void GeometryTransition0Impl(Ark_NativePointer node,
                                 const Ark_String* value)
    {
    }
    void GeometryTransition1Impl(Ark_NativePointer node,
                                 const Ark_String* id,
                                 const Opt_GeometryTransitionOptions* options)
    {
    }
    void StateStylesImpl(Ark_NativePointer node,
                         const Ark_StateStyles* value)
    {
    }
    void RestoreIdImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void SphericalEffectImpl(Ark_NativePointer node,
                             const Ark_Number* value)
    {
    }
    void LightUpEffectImpl(Ark_NativePointer node,
                           const Ark_Number* value)
    {
    }
    void PixelStretchEffectImpl(Ark_NativePointer node,
                                const Ark_PixelStretchEffectOptions* value)
    {
    }
    void AccessibilityGroup0Impl(Ark_NativePointer node,
                                 Ark_Boolean value)
    {
    }
    void AccessibilityGroup1Impl(Ark_NativePointer node,
                                 Ark_Boolean isGroup,
                                 const Ark_AccessibilityOptions* accessibilityOptions)
    {
    }
    void AccessibilityText0Impl(Ark_NativePointer node,
                                const Ark_String* value)
    {
    }
    void AccessibilityText1Impl(Ark_NativePointer node,
                                const Ark_Resource* value)
    {
    }
    void AccessibilityTextHintImpl(Ark_NativePointer node,
                                   const Ark_String* value)
    {
    }
    void AccessibilityDescription0Impl(Ark_NativePointer node,
                                       const Ark_String* value)
    {
    }
    void AccessibilityDescription1Impl(Ark_NativePointer node,
                                       const Ark_Resource* value)
    {
    }
    void AccessibilityLevelImpl(Ark_NativePointer node,
                                const Ark_String* value)
    {
    }
    void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                      const CustomNodeBuilder* value)
    {
    }
    void AccessibilityCheckedImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void AccessibilitySelectedImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void ObscuredImpl(Ark_NativePointer node,
                      const Array_ObscuredReasons* value)
    {
    }
    void ReuseIdImpl(Ark_NativePointer node,
                     const Ark_String* value)
    {
    }
    void RenderFitImpl(Ark_NativePointer node,
                       Ark_RenderFit value)
    {
    }
    void GestureModifierImpl(Ark_NativePointer node,
                             Ark_GestureModifier value)
    {
    }
    void BackgroundBrightnessImpl(Ark_NativePointer node,
                                  const Ark_BackgroundBrightnessOptions* value)
    {
    }
    void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                                 const Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
    {
    }
    void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                            const GestureRecognizerJudgeBeginCallback* value)
    {
    }
    void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                            const GestureRecognizerJudgeBeginCallback* callback_,
                                            Ark_Boolean exposeInnerGesture)
    {
    }
    void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                                 const ShouldBuiltInRecognizerParallelWithCallback* value)
    {
    }
    void MonopolizeEventsImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void OnTouchInterceptImpl(Ark_NativePointer node,
                              const Callback_TouchEvent_HitTestMode* value)
    {
    }
    void OnSizeChangeImpl(Ark_NativePointer node,
                          const SizeChangeCallback* value)
    {
    }
    void CustomPropertyImpl(Ark_NativePointer node,
                            const Ark_String* name,
                            const Opt_CustomObject* value)
    {
    }
    void ExpandSafeAreaImpl(Ark_NativePointer node,
                            const Opt_Array_SafeAreaType* types,
                            const Opt_Array_SafeAreaEdge* edges)
    {
    }
    void BackgroundImpl(Ark_NativePointer node,
                        const CustomNodeBuilder* builder,
                        const Opt_Literal_Alignment_align* options)
    {
    }
    void BackgroundImageImpl(Ark_NativePointer node,
                             const Ark_Union_ResourceStr_PixelMap* src,
                             const Opt_ImageRepeat* repeat)
    {
    }
    void BackgroundBlurStyleImpl(Ark_NativePointer node,
                                 Ark_BlurStyle value,
                                 const Opt_BackgroundBlurStyleOptions* options)
    {
    }
    void ForegroundBlurStyleImpl(Ark_NativePointer node,
                                 Ark_BlurStyle value,
                                 const Opt_ForegroundBlurStyleOptions* options)
    {
    }
    void FocusScopeId0Impl(Ark_NativePointer node,
                           const Ark_String* id,
                           const Opt_Boolean* isGroup)
    {
    }
    void FocusScopeId1Impl(Ark_NativePointer node,
                           const Ark_String* id,
                           const Opt_Boolean* isGroup,
                           const Opt_Boolean* arrowStepOut)
    {
    }
    void FocusScopePriorityImpl(Ark_NativePointer node,
                                const Ark_String* scopeId,
                                const Opt_FocusPriority* priority)
    {
    }
    void GestureImpl(Ark_NativePointer node,
                     const Ark_GestureType* gesture,
                     const Opt_GestureMask* mask)
    {
    }
    void PriorityGestureImpl(Ark_NativePointer node,
                             const Ark_GestureType* gesture,
                             const Opt_GestureMask* mask)
    {
    }
    void ParallelGestureImpl(Ark_NativePointer node,
                             const Ark_GestureType* gesture,
                             const Opt_GestureMask* mask)
    {
    }
    void BlurImpl(Ark_NativePointer node,
                  const Ark_Number* value,
                  const Opt_BlurOptions* options)
    {
    }
    void LinearGradientBlurImpl(Ark_NativePointer node,
                                const Ark_Number* value,
                                const Ark_LinearGradientBlurOptions* options)
    {
    }
    void SystemBarEffectImpl(Ark_NativePointer node)
    {
    }
    void BackdropBlurImpl(Ark_NativePointer node,
                          const Ark_Number* value,
                          const Opt_BlurOptions* options)
    {
    }
    void SharedTransitionImpl(Ark_NativePointer node,
                              const Ark_String* id,
                              const Opt_sharedTransitionOptions* options)
    {
    }
    void ChainModeImpl(Ark_NativePointer node,
                       Ark_Axis direction,
                       Ark_ChainStyle style)
    {
    }
    void DragPreviewOptionsImpl(Ark_NativePointer node,
                                const Ark_DragPreviewOptions* value,
                                const Opt_DragInteractionOptions* options)
    {
    }
    void OverlayImpl(Ark_NativePointer node,
                     const Ark_Union_String_CustomBuilder_ComponentContent* value,
                     const Opt_OverlayOptions* options)
    {
    }
    void BlendModeImpl(Ark_NativePointer node,
                       Ark_BlendMode value,
                       const Opt_BlendApplyType* type)
    {
    }
    void AdvancedBlendModeImpl(Ark_NativePointer node,
                               const Ark_Union_BlendMode_Blender* effect,
                               const Opt_BlendApplyType* type)
    {
    }
    void BindPopupImpl(Ark_NativePointer node,
                       Ark_Boolean show,
                       const Ark_Union_PopupOptions_CustomPopupOptions* popup)
    {
    }
    void BindMenu0Impl(Ark_NativePointer node,
                       const Ark_Union_Array_MenuElement_CustomBuilder* content,
                       const Opt_MenuOptions* options)
    {
    }
    void BindMenu1Impl(Ark_NativePointer node,
                       Ark_Boolean isShow,
                       const Ark_Union_Array_MenuElement_CustomBuilder* content,
                       const Opt_MenuOptions* options)
    {
    }
    void BindContextMenu0Impl(Ark_NativePointer node,
                              const CustomNodeBuilder* content,
                              Ark_ResponseType responseType,
                              const Opt_ContextMenuOptions* options)
    {
    }
    void BindContextMenu1Impl(Ark_NativePointer node,
                              Ark_Boolean isShown,
                              const CustomNodeBuilder* content,
                              const Opt_ContextMenuOptions* options)
    {
    }
    void BindContentCover0Impl(Ark_NativePointer node,
                               const Opt_Boolean* isShow,
                               const CustomNodeBuilder* builder,
                               const Opt_ModalTransition* type)
    {
    }
    void BindContentCover1Impl(Ark_NativePointer node,
                               const Opt_Boolean* isShow,
                               const CustomNodeBuilder* builder,
                               const Opt_ContentCoverOptions* options)
    {
    }
    void BindSheetImpl(Ark_NativePointer node,
                       const Opt_Boolean* isShow,
                       const CustomNodeBuilder* builder,
                       const Opt_SheetOptions* options)
    {
    }
    void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                                 const Array_Number* ratios,
                                 const VisibleAreaChangeCallback* event)
    {
    }
    void KeyboardShortcutImpl(Ark_NativePointer node,
                              const Ark_Union_String_FunctionKey* value,
                              const Array_ModifierKey* keys,
                              const Opt_Callback_Void* action)
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
                    const Ark_ResourceColor* value)
    {
    }
    void FillImpl(Ark_NativePointer node,
                  const Ark_ResourceColor* value)
    {
    }
    void StrokeDashOffsetImpl(Ark_NativePointer node,
                              const Ark_Union_Number_String* value)
    {
    }
    void StrokeLineCapImpl(Ark_NativePointer node,
                           Ark_LineCapStyle value)
    {
    }
    void StrokeLineJoinImpl(Ark_NativePointer node,
                            Ark_LineJoinStyle value)
    {
    }
    void StrokeMiterLimitImpl(Ark_NativePointer node,
                              const Ark_Union_Number_String* value)
    {
    }
    void StrokeOpacityImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String_Resource* value)
    {
    }
    void FillOpacityImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
    {
    }
    void AntiAliasImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void StrokeDashArrayImpl(Ark_NativePointer node,
                             const Array_Length* value)
    {
    }
    } // CommonShapeMethodModifier
    namespace CommonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // CommonModifier
    namespace CommonInterfaceModifier {
    void SetCommonOptionsImpl(Ark_NativePointer node)
    {
    }
    } // CommonInterfaceModifier
    namespace ScrollableCommonMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       Ark_BarState value)
    {
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Ark_Union_Color_Number_String* value)
    {
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Ark_Union_Number_String* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Callback_Number_Number_Void* value)
    {
    }
    void OnReachStartImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Callback_Void* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void FlingSpeedLimitImpl(Ark_NativePointer node,
                             const Ark_Number* value)
    {
    }
    void ClipContentImpl(Ark_NativePointer node,
                         const Ark_Union_ContentClipMode_RectShape* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        Ark_EdgeEffect edgeEffect,
                        const Opt_EdgeEffectOptions* options)
    {
    }
    void FadingEdgeImpl(Ark_NativePointer node,
                        const Opt_Boolean* enabled,
                        const Opt_FadingEdgeOptions* options)
    {
    }
    } // ScrollableCommonMethodModifier
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
    void EnvironmentImpl(Ark_NativePointer node,
                         const Ark_ResourceStr* value)
    {
    }
    void ShaderImpl(Ark_NativePointer node,
                    const Ark_ResourceStr* value)
    {
    }
    void ShaderImageTextureImpl(Ark_NativePointer node,
                                const Ark_ResourceStr* value)
    {
    }
    void ShaderInputBufferImpl(Ark_NativePointer node,
                               const Array_Number* value)
    {
    }
    void RenderWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
    {
    }
    void RenderHeightImpl(Ark_NativePointer node,
                          const Ark_Length* value)
    {
    }
    void CustomRenderImpl(Ark_NativePointer node,
                          const Ark_ResourceStr* uri,
                          Ark_Boolean selfRenderUpdate)
    {
    }
    } // Component3DAttributeModifier
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
                                 const Ark_TextBackgroundStyle* value)
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
                   const VoidCallback* value)
    {
    }
    void OnDecImpl(Ark_NativePointer node,
                   const VoidCallback* value)
    {
    }
    void EnableDecImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void EnableIncImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    } // CounterAttributeModifier
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
                         Ark_Boolean value)
    {
    }
    void ValueColorsImpl(Ark_NativePointer node,
                         const Array_Union_ResourceColor_LinearGradient* value)
    {
    }
    void TrackBackgroundColorImpl(Ark_NativePointer node,
                                  const Ark_ResourceColor* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
    {
    }
    void TrackShadowImpl(Ark_NativePointer node,
                         const Ark_DataPanelShadowOptions* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
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
                   Ark_Boolean value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Ark_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Ark_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Ark_PickerTextStyle* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_DatePickerResult_Void* value)
    {
    }
    void OnDateChangeImpl(Ark_NativePointer node,
                          const Callback_Date_Void* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Date_Void* callback)
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
                      Ark_Boolean value)
    {
    }
    void ColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String* value)
    {
    }
    void LineCapImpl(Ark_NativePointer node,
                     Ark_LineCapStyle value)
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
                          const Callback_TerminationInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const ErrorCallback* value)
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
                        const Ark_PointLightStyle* value)
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
                          Ark_Alignment value)
    {
    }
    void OnFolderStateChangeImpl(Ark_NativePointer node,
                                 const OnFoldStatusChangeCallback* value)
    {
    }
    void OnHoverStatusChangeImpl(Ark_NativePointer node,
                                 const OnHoverStatusChangeCallback* value)
    {
    }
    void EnableAnimationImpl(Ark_NativePointer node,
                             Ark_Boolean value)
    {
    }
    void AutoHalfFoldImpl(Ark_NativePointer node,
                          Ark_Boolean value)
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
                  const Ark_SizeOptions* value)
    {
    }
    void ModuleNameImpl(Ark_NativePointer node,
                        const Ark_String* value)
    {
    }
    void DimensionImpl(Ark_NativePointer node,
                       Ark_FormDimension value)
    {
    }
    void AllowUpdateImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void VisibilityImpl(Ark_NativePointer node,
                        Ark_Visibility value)
    {
    }
    void OnAcquiredImpl(Ark_NativePointer node,
                        const Callback_FormCallbackInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Callback_Literal_Number_errcode_String_msg_Void* value)
    {
    }
    void OnRouterImpl(Ark_NativePointer node,
                      const Callback_Any_Void* value)
    {
    }
    void OnUninstallImpl(Ark_NativePointer node,
                         const Callback_FormCallbackInfo_Void* value)
    {
    }
    void OnLoadImpl(Ark_NativePointer node,
                    const Callback_Void* value)
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
                   const Ark_Number* value)
    {
    }
    void StartAngleImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void EndAngleImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void ColorsImpl(Ark_NativePointer node,
                    const Ark_Type_GaugeAttribute_colors_colors* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
    {
    }
    void DescriptionImpl(Ark_NativePointer node,
                         const CustomNodeBuilder* value)
    {
    }
    void TrackShadowImpl(Ark_NativePointer node,
                         const Ark_GaugeShadowOptions* value)
    {
    }
    void IndicatorImpl(Ark_NativePointer node,
                       const Ark_GaugeIndicatorOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
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
                             const Ark_String* value)
    {
    }
    void RowsTemplateImpl(Ark_NativePointer node,
                          const Ark_String* value)
    {
    }
    void ColumnsGapImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void RowsGapImpl(Ark_NativePointer node,
                     const Ark_Length* value)
    {
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Ark_Union_Number_String* value)
    {
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Ark_Union_Color_Number_String* value)
    {
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       Ark_BarState value)
    {
    }
    void OnScrollBarUpdateImpl(Ark_NativePointer node,
                               const Callback_Number_Number_ComputedBarAttribute* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Callback_Number_Number_Void* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Ark_Number* count,
                          Ark_Boolean show)
    {
    }
    void EditModeImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void MultiSelectableImpl(Ark_NativePointer node,
                             Ark_Boolean value)
    {
    }
    void MaxCountImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void MinCountImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void CellLengthImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void LayoutDirectionImpl(Ark_NativePointer node,
                             Ark_GridDirection value)
    {
    }
    void SupportAnimationImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void OnItemDragStartImpl(Ark_NativePointer node,
                             const onItemDragStart_event_type* value)
    {
    }
    void OnItemDragEnterImpl(Ark_NativePointer node,
                             const Callback_ItemDragInfo_Void* value)
    {
    }
    void OnItemDragMoveImpl(Ark_NativePointer node,
                            const Callback_ItemDragInfo_Number_Number_Void* value)
    {
    }
    void OnItemDragLeaveImpl(Ark_NativePointer node,
                             const Callback_ItemDragInfo_Number_Void* value)
    {
    }
    void OnItemDropImpl(Ark_NativePointer node,
                        const Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void AlignItemsImpl(Ark_NativePointer node,
                        const Opt_GridItemAlignment* value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Callback_Number_Number_Void* value)
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
    void OnReachStartImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Callback_Void* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        Ark_EdgeEffect value,
                        const Opt_EdgeEffectOptions* options)
    {
    }
    } // GridAttributeModifier
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
                      const Ark_Number* value)
    {
    }
    void RowEndImpl(Ark_NativePointer node,
                    const Ark_Number* value)
    {
    }
    void ColumnStartImpl(Ark_NativePointer node,
                         const Ark_Number* value)
    {
    }
    void ColumnEndImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void ForceRebuildImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void SelectableImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Boolean_Void* callback)
    {
    }
    } // GridItemAttributeModifier
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
                  const Ark_Union_Number_GridColColumnOption* value)
    {
    }
    void GridColOffsetImpl(Ark_NativePointer node,
                           const Ark_Union_Number_GridColColumnOption* value)
    {
    }
    void OrderImpl(Ark_NativePointer node,
                   const Ark_Union_Number_GridColColumnOption* value)
    {
    }
    } // GridColAttributeModifier
    namespace GridContainerModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // GridContainerModifier
    namespace GridContainerInterfaceModifier {
    void SetGridContainerOptionsImpl(Ark_NativePointer node,
                                     const Opt_GridContainerOptions* value)
    {
    }
    } // GridContainerInterfaceModifier
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
                                const Callback_String_Void* value)
    {
    }
    void AlignItemsImpl(Ark_NativePointer node,
                        Ark_ItemAlign value)
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
                   const Ark_Union_Color_Number_String_Resource* value)
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
                              const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src)
    {
    }
    void SetImageOptions1Impl(Ark_NativePointer node,
                              const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ImageContent* src)
    {
    }
    void SetImageOptions2Impl(Ark_NativePointer node,
                              const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor* src,
                              const Ark_ImageAIOptions* imageAIOptions)
    {
    }
    } // ImageInterfaceModifier
    namespace ImageAttributeModifier {
    void AltImpl(Ark_NativePointer node,
                 const Ark_Union_String_Resource_PixelMap* value)
    {
    }
    void MatchTextDirectionImpl(Ark_NativePointer node,
                                Ark_Boolean value)
    {
    }
    void FitOriginalSizeImpl(Ark_NativePointer node,
                             Ark_Boolean value)
    {
    }
    void FillColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       Ark_ImageFit value)
    {
    }
    void ObjectRepeatImpl(Ark_NativePointer node,
                          Ark_ImageRepeat value)
    {
    }
    void AutoResizeImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void RenderModeImpl(Ark_NativePointer node,
                        Ark_ImageRenderMode value)
    {
    }
    void DynamicRangeModeImpl(Ark_NativePointer node,
                              Ark_DynamicRangeMode value)
    {
    }
    void InterpolationImpl(Ark_NativePointer node,
                           Ark_ImageInterpolation value)
    {
    }
    void SourceSizeImpl(Ark_NativePointer node,
                        const Ark_ImageSourceSize* value)
    {
    }
    void SyncLoadImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void ColorFilterImpl(Ark_NativePointer node,
                         const Ark_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        Ark_CopyOptions value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Ark_PointLightStyle* value)
    {
    }
    void EdgeAntialiasingImpl(Ark_NativePointer node,
                              const Ark_Number* value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
                        const Callback_Type_ImageAttribute_onComplete_callback_event_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const ImageErrorCallback* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void AnalyzerConfigImpl(Ark_NativePointer node,
                            const Ark_ImageAnalyzerConfig* value)
    {
    }
    void ResizableImpl(Ark_NativePointer node,
                       const Ark_ResizableOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void EnhancedImageQualityImpl(Ark_NativePointer node,
                                  const Ark_ResolutionQuality* value)
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
                    const Array_ImageFrameInfo* value)
    {
    }
    void StateImpl(Ark_NativePointer node,
                   Ark_AnimationStatus value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void ReverseImpl(Ark_NativePointer node,
                     Ark_Boolean value)
    {
    }
    void FixedSizeImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void PreDecodeImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void FillModeImpl(Ark_NativePointer node,
                      Ark_FillMode value)
    {
    }
    void IterationsImpl(Ark_NativePointer node,
                        const Ark_Number* value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnRepeatImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnCancelImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Callback_Void* value)
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
                           Ark_ImageSpanAlignment value)
    {
    }
    void ColorFilterImpl(Ark_NativePointer node,
                         const Ark_Union_ColorFilter_DrawingColorFilter* value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       Ark_ImageFit value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
                        const ImageCompleteCallback* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const ImageErrorCallback* value)
    {
    }
    void AltImpl(Ark_NativePointer node,
                 Ark_PixelMap value)
    {
    }
    } // ImageSpanAttributeModifier
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
                        const Array_Length* value)
    {
    }
    void EndPointImpl(Ark_NativePointer node,
                      const Array_Length* value)
    {
    }
    } // LineAttributeModifier
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
                           Ark_ListItemAlign value)
    {
    }
    void ListDirectionImpl(Ark_NativePointer node,
                           Ark_Axis value)
    {
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       Ark_BarState value)
    {
    }
    void ContentStartOffsetImpl(Ark_NativePointer node,
                                const Ark_Number* value)
    {
    }
    void ContentEndOffsetImpl(Ark_NativePointer node,
                              const Ark_Number* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_ListDividerOptions* value)
    {
    }
    void EditModeImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void MultiSelectableImpl(Ark_NativePointer node,
                             Ark_Boolean value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Ark_Number* count,
                          Ark_Boolean show)
    {
    }
    void ChainAnimationImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void ChainAnimationOptionsImpl(Ark_NativePointer node,
                                   const Ark_ChainAnimationOptions* value)
    {
    }
    void StickyImpl(Ark_NativePointer node,
                    Ark_StickyStyle value)
    {
    }
    void ScrollSnapAlignImpl(Ark_NativePointer node,
                             Ark_ScrollSnapAlign value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void ChildrenMainSizeImpl(Ark_NativePointer node,
                              Ark_ChildrenMainSize value)
    {
    }
    void MaintainVisibleContentPositionImpl(Ark_NativePointer node,
                                            Ark_Boolean value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Callback_Number_Number_Void* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Callback_Number_Number_Number_Void* value)
    {
    }
    void OnScrollVisibleContentChangeImpl(Ark_NativePointer node,
                                          const OnScrollVisibleContentChangeCallback* value)
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
    void OnReachStartImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const Callback_Void* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnItemDeleteImpl(Ark_NativePointer node,
                          const Callback_Number_Boolean* value)
    {
    }
    void OnItemMoveImpl(Ark_NativePointer node,
                        const Callback_Number_Number_Boolean* value)
    {
    }
    void OnItemDragStartImpl(Ark_NativePointer node,
                             const onItemDragStart_event_type* value)
    {
    }
    void OnItemDragEnterImpl(Ark_NativePointer node,
                             const Callback_ItemDragInfo_Void* value)
    {
    }
    void OnItemDragMoveImpl(Ark_NativePointer node,
                            const Callback_ItemDragInfo_Number_Number_Void* value)
    {
    }
    void OnItemDragLeaveImpl(Ark_NativePointer node,
                             const Callback_ItemDragInfo_Number_Void* value)
    {
    }
    void OnItemDropImpl(Ark_NativePointer node,
                        const Callback_ItemDragInfo_Number_Number_Boolean_Void* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
    {
    }
    void LanesImpl(Ark_NativePointer node,
                   const Ark_Union_Number_LengthConstrain* value,
                   const Opt_Length* gutter)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        Ark_EdgeEffect value,
                        const Opt_EdgeEffectOptions* options)
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
    void SetListItemOptions0Impl(Ark_NativePointer node,
                                 const Opt_ListItemOptions* value)
    {
    }
    void SetListItemOptions1Impl(Ark_NativePointer node,
                                 const Opt_String* value)
    {
    }
    } // ListItemInterfaceModifier
    namespace ListItemAttributeModifier {
    void StickyImpl(Ark_NativePointer node,
                    Ark_Sticky value)
    {
    }
    void EditableImpl(Ark_NativePointer node,
                      const Ark_Union_Boolean_EditMode* value)
    {
    }
    void SelectableImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void SelectedImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void SwipeActionImpl(Ark_NativePointer node,
                         const Ark_SwipeActionOptions* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Boolean_Void* callback)
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
                              Ark_ChildrenMainSize value)
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
                   const Ark_ResourceColor* value)
    {
    }
    void EnableLoadingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    } // LoadingProgressAttributeModifier
    namespace LocationButtonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // LocationButtonModifier
    namespace LocationButtonInterfaceModifier {
    void SetLocationButtonOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetLocationButtonOptions1Impl(Ark_NativePointer node,
                                       const Ark_LocationButtonOptions* options)
    {
    }
    } // LocationButtonInterfaceModifier
    namespace LocationButtonAttributeModifier {
    void OnClickImpl(Ark_NativePointer node,
                     const Callback_ClickEvent_LocationButtonOnClickResult_Void* value)
    {
    }
    } // LocationButtonAttributeModifier
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
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void AllowScaleImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
    {
    }
    void MarqueeUpdateStrategyImpl(Ark_NativePointer node,
                                   Ark_MarqueeUpdateStrategy value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnBounceImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const Callback_Void* value)
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
                                        const Ark_Union_PixelMap_ResourceStr_DrawableDescriptor_ASTCResource* src)
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
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Ark_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void RadiusImpl(Ark_NativePointer node,
                    const Ark_Union_Dimension_BorderRadiuses* value)
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
                                  Ark_SubMenuExpandingMode value)
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
                      Ark_Boolean value)
    {
    }
    void SelectIconImpl(Ark_NativePointer node,
                        const Ark_Union_Boolean_ResourceStr_SymbolGlyphModifier* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
    {
    }
    void ContentFontImpl(Ark_NativePointer node,
                         const Ark_Font* value)
    {
    }
    void ContentFontColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
    {
    }
    void LabelFontImpl(Ark_NativePointer node,
                       const Ark_Font* value)
    {
    }
    void LabelFontColorImpl(Ark_NativePointer node,
                            const Ark_ResourceColor* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Boolean_Void* callback)
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
                           Ark_Boolean value)
    {
    }
    void HideTitleBar1Impl(Ark_NativePointer node,
                           Ark_Boolean hide,
                           Ark_Boolean animated)
    {
    }
    void OnShownImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnHiddenImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnBackPressedImpl(Ark_NativePointer node,
                           const Callback_Boolean* value)
    {
    }
    void ModeImpl(Ark_NativePointer node,
                  Ark_NavDestinationMode value)
    {
    }
    void BackButtonIconImpl(Ark_NativePointer node,
                            const Ark_Union_ResourceStr_PixelMap_SymbolGlyphModifier* value)
    {
    }
    void MenusImpl(Ark_NativePointer node,
                   const Ark_Union_Array_NavigationMenuItem_CustomBuilder* value)
    {
    }
    void OnReadyImpl(Ark_NativePointer node,
                     const Callback_NavDestinationContext_Void* value)
    {
    }
    void OnWillAppearImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnWillDisappearImpl(Ark_NativePointer node,
                             const Callback_Void* value)
    {
    }
    void OnWillShowImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void OnWillHideImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void SystemBarStyleImpl(Ark_NativePointer node,
                            const Opt_SystemBarStyle* value)
    {
    }
    void RecoverableImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
    {
    }
    void SystemTransitionImpl(Ark_NativePointer node,
                              Ark_NavigationSystemTransitionType value)
    {
    }
    void TitleImpl(Ark_NativePointer node,
                   const Ark_Type_NavDestinationAttribute_title_value* value,
                   const Opt_NavigationTitleOptions* options)
    {
    }
    void ToolbarConfigurationImpl(Ark_NativePointer node,
                                  const Ark_Union_Array_ToolbarItem_CustomBuilder* toolbarParam,
                                  const Opt_NavigationToolbarOptions* options)
    {
    }
    void HideToolBarImpl(Ark_NativePointer node,
                         Ark_Boolean hide,
                         const Opt_Boolean* animated)
    {
    }
    void IgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                  const Opt_Array_LayoutSafeAreaType* types,
                                  const Opt_Array_LayoutSafeAreaEdge* edges)
    {
    }
    } // NavDestinationAttributeModifier
    namespace NavRouterModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // NavRouterModifier
    namespace NavRouterInterfaceModifier {
    void SetNavRouterOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetNavRouterOptions1Impl(Ark_NativePointer node,
                                  const Ark_RouteInfo* value)
    {
    }
    } // NavRouterInterfaceModifier
    namespace NavRouterAttributeModifier {
    void OnStateChangeImpl(Ark_NativePointer node,
                           const Callback_Boolean_Void* value)
    {
    }
    void ModeImpl(Ark_NativePointer node,
                  Ark_NavRouteMode value)
    {
    }
    } // NavRouterAttributeModifier
    namespace NavigatorModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // NavigatorModifier
    namespace NavigatorInterfaceModifier {
    void SetNavigatorOptions0Impl(Ark_NativePointer node,
                                  const Opt_Literal_String_target_NavigationType_type* value)
    {
    }
    void SetNavigatorOptions1Impl(Ark_NativePointer node)
    {
    }
    } // NavigatorInterfaceModifier
    namespace NavigatorAttributeModifier {
    void ActiveImpl(Ark_NativePointer node,
                    Ark_Boolean value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  Ark_NavigationType value)
    {
    }
    void TargetImpl(Ark_NativePointer node,
                    const Ark_String* value)
    {
    }
    void ParamsImpl(Ark_NativePointer node,
                    const Ark_CustomObject* value)
    {
    }
    } // NavigatorAttributeModifier
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
    namespace PanelModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PanelModifier
    namespace PanelInterfaceModifier {
    void SetPanelOptionsImpl(Ark_NativePointer node,
                             Ark_Boolean show)
    {
    }
    } // PanelInterfaceModifier
    namespace PanelAttributeModifier {
    void ModeImpl(Ark_NativePointer node,
                  Ark_PanelMode value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  Ark_PanelType value)
    {
    }
    void DragBarImpl(Ark_NativePointer node,
                     Ark_Boolean value)
    {
    }
    void CustomHeightImpl(Ark_NativePointer node,
                          const Ark_Union_Dimension_PanelHeight* value)
    {
    }
    void FullHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
    {
    }
    void HalfHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
    {
    }
    void MiniHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
    {
    }
    void ShowImpl(Ark_NativePointer node,
                  Ark_Boolean value)
    {
    }
    void BackgroundMaskImpl(Ark_NativePointer node,
                            const Ark_ResourceColor* value)
    {
    }
    void ShowCloseIconImpl(Ark_NativePointer node,
                           Ark_Boolean value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Number_PanelMode_Void* value)
    {
    }
    void OnHeightChangeImpl(Ark_NativePointer node,
                            const Callback_Number_Void* value)
    {
    }
    void _onChangeEvent_modeImpl(Ark_NativePointer node,
                                 const Callback_PanelMode_Void* callback)
    {
    }
    } // PanelAttributeModifier
    namespace PasteButtonModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    } // PasteButtonModifier
    namespace PasteButtonInterfaceModifier {
    void SetPasteButtonOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetPasteButtonOptions1Impl(Ark_NativePointer node,
                                    const Ark_PasteButtonOptions* options)
    {
    }
    } // PasteButtonInterfaceModifier
    namespace PasteButtonAttributeModifier {
    void OnClickImpl(Ark_NativePointer node,
                     const Callback_ClickEvent_PasteButtonOnClickResult_Void* value)
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
    void CommandsImpl(Ark_NativePointer node,
                      const Ark_String* value)
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
    void SideLengthImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void CircleRadiusImpl(Ark_NativePointer node,
                          const Ark_Length* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void RegularColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void ActiveColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
    {
    }
    void PathColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void PathStrokeWidthImpl(Ark_NativePointer node,
                             const Ark_Union_Number_String* value)
    {
    }
    void OnPatternCompleteImpl(Ark_NativePointer node,
                               const Callback_Array_Number_Void* value)
    {
    }
    void AutoResetImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void OnDotConnectImpl(Ark_NativePointer node,
                          const Callback_Number_Void* value)
    {
    }
    void ActivateCircleStyleImpl(Ark_NativePointer node,
                                 const Opt_CircleStyleOptions* value)
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
                        const VoidCallback* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const PluginErrorCallback* value)
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
                    const Array_Point* value)
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
                    const Array_Point* value)
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
                   const Ark_Number* value)
    {
    }
    void ColorImpl(Ark_NativePointer node,
                   const Ark_Union_ResourceColor_LinearGradient* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Ark_Union_LinearStyleOptions_RingStyleOptions_CapsuleStyleOptions_ProgressStyleOptions* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
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
                              const Ark_String* value)
    {
    }
    } // QRCodeInterfaceModifier
    namespace QRCodeAttributeModifier {
    void ColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void ContentOpacityImpl(Ark_NativePointer node,
                            const Ark_Union_Number_Resource* value)
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
                     Ark_Boolean value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
    {
    }
    void RadioStyleImpl(Ark_NativePointer node,
                        const Opt_RadioStyle* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void _onChangeEvent_checkedImpl(Ark_NativePointer node,
                                    const Callback_Boolean_Void* callback)
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
                   const Ark_Number* value)
    {
    }
    void StepSizeImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void StarStyleImpl(Ark_NativePointer node,
                       const Ark_StarStyleOptions* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Void* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void _onChangeEvent_ratingImpl(Ark_NativePointer node,
                                   const Callback_Number_Void* callback)
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
    void RadiusWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String* value)
    {
    }
    void RadiusHeightImpl(Ark_NativePointer node,
                          const Ark_Union_Number_String* value)
    {
    }
    void RadiusImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Array_Union_Number_String* value)
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
                           const Callback_RefreshStatus_Void* value)
    {
    }
    void OnRefreshingImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void RefreshOffsetImpl(Ark_NativePointer node,
                           const Ark_Number* value)
    {
    }
    void PullToRefreshImpl(Ark_NativePointer node,
                           Ark_Boolean value)
    {
    }
    void OnOffsetChangeImpl(Ark_NativePointer node,
                            const Callback_Number_Void* value)
    {
    }
    void PullDownRatioImpl(Ark_NativePointer node,
                           const Opt_Number* value)
    {
    }
    void _onChangeEvent_refreshingImpl(Ark_NativePointer node,
                                       const Callback_Boolean_Void* callback)
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
                       const Array_GuideLineStyle* value)
    {
    }
    void Barrier0Impl(Ark_NativePointer node,
                      const Array_BarrierStyle* value)
    {
    }
    void Barrier1Impl(Ark_NativePointer node,
                      const Array_LocalizedBarrierStyle* value)
    {
    }
    } // RelativeContainerAttributeModifier
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
                     const Callback_Void* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Callback_RichEditorSelection_Void* value)
    {
    }
    void OnSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_RichEditorRange_Void* value)
    {
    }
    void AboutToIMEInputImpl(Ark_NativePointer node,
                             const Callback_RichEditorInsertValue_Boolean* value)
    {
    }
    void OnIMEInputCompleteImpl(Ark_NativePointer node,
                                const Callback_RichEditorTextSpanResult_Void* value)
    {
    }
    void OnDidIMEInputImpl(Ark_NativePointer node,
                           const Callback_TextRange_Void* value)
    {
    }
    void AboutToDeleteImpl(Ark_NativePointer node,
                           const Callback_RichEditorDeleteValue_Boolean* value)
    {
    }
    void OnDeleteCompleteImpl(Ark_NativePointer node,
                              const Callback_Void* value)
    {
    }
    void CopyOptionsImpl(Ark_NativePointer node,
                         Ark_CopyOptions value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const PasteEventCallback* value)
    {
    }
    void EnableDataDetectorImpl(Ark_NativePointer node,
                                Ark_Boolean value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void DataDetectorConfigImpl(Ark_NativePointer node,
                                const Ark_TextDataDetectorConfig* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void OnEditingChangeImpl(Ark_NativePointer node,
                             const Callback_Boolean_Void* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          Ark_EnterKeyType value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const SubmitCallback* value)
    {
    }
    void OnWillChangeImpl(Ark_NativePointer node,
                          const Callback_RichEditorChangeValue_Boolean* value)
    {
    }
    void OnDidChangeImpl(Ark_NativePointer node,
                         const OnDidChangeCallback* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Callback_CutEvent_Void* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Callback_CopyEvent_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      Ark_BarState value)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
                               Ark_RichEditorSpanType spanType,
                               const CustomNodeBuilder* content,
                               const Ark_Union_ResponseType_RichEditorResponseType* responseType,
                               const Opt_SelectionMenuOptions* options)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void PlaceholderImpl(Ark_NativePointer node,
                         const Ark_ResourceStr* value,
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
                     const Callback_Void* value)
    {
    }
    void OnCompleteImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    } // RichTextAttributeModifier
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
                           const Opt_RowOptions* options)
    {
    }
    } // RowInterfaceModifier
    namespace RowAttributeModifier {
    void AlignItemsImpl(Ark_NativePointer node,
                        Ark_VerticalAlign value)
    {
    }
    void JustifyContentImpl(Ark_NativePointer node,
                            Ark_FlexAlign value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Ark_PointLightStyle* value)
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
                        Ark_Boolean value)
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
    void SetSaveButtonOptions0Impl(Ark_NativePointer node)
    {
    }
    void SetSaveButtonOptions1Impl(Ark_NativePointer node,
                                   const Ark_SaveButtonOptions* options)
    {
    }
    } // SaveButtonInterfaceModifier
    namespace SaveButtonAttributeModifier {
    void OnClickImpl(Ark_NativePointer node,
                     const Callback_ClickEvent_SaveButtonOnClickResult_Void* value)
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
    void ScrollableImpl(Ark_NativePointer node,
                        Ark_ScrollDirection value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Callback_Number_Number_Void* value)
    {
    }
    void OnWillScrollImpl(Ark_NativePointer node,
                          const Opt_ScrollOnWillScrollCallback* value)
    {
    }
    void OnDidScrollImpl(Ark_NativePointer node,
                         const ScrollOnScrollCallback* value)
    {
    }
    void OnScrollEdgeImpl(Ark_NativePointer node,
                          const OnScrollEdgeCallback* value)
    {
    }
    void OnScrollStartImpl(Ark_NativePointer node,
                           const VoidCallback* value)
    {
    }
    void OnScrollEndImpl(Ark_NativePointer node,
                         const Callback_Void* value)
    {
    }
    void OnScrollStopImpl(Ark_NativePointer node,
                          const VoidCallback* value)
    {
    }
    void ScrollBarImpl(Ark_NativePointer node,
                       Ark_BarState value)
    {
    }
    void ScrollBarColorImpl(Ark_NativePointer node,
                            const Ark_Union_Color_Number_String* value)
    {
    }
    void ScrollBarWidthImpl(Ark_NativePointer node,
                            const Ark_Union_Number_String* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const OnScrollFrameBeginCallback* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void ScrollSnapImpl(Ark_NativePointer node,
                        const Ark_ScrollSnapOptions* value)
    {
    }
    void EnablePagingImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void InitialOffsetImpl(Ark_NativePointer node,
                           const Ark_OffsetOptions* value)
    {
    }
    void EdgeEffectImpl(Ark_NativePointer node,
                        Ark_EdgeEffect edgeEffect,
                        const Opt_EdgeEffectOptions* options)
    {
    }
    } // ScrollAttributeModifier
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
                       const Ark_ResourceColor* value)
    {
    }
    void SearchIconImpl(Ark_NativePointer node,
                        const Ark_Union_IconOptions_SymbolGlyphModifier* value)
    {
    }
    void CancelButtonImpl(Ark_NativePointer node,
                          const Ark_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Callback_Boolean_Void* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Ark_CaretStyle* value)
    {
    }
    void PlaceholderColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
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
                          Ark_EnterKeyType value)
    {
    }
    void OnSubmit0Impl(Ark_NativePointer node,
                       const Callback_String_Void* value)
    {
    }
    void OnSubmit1Impl(Ark_NativePointer node,
                       const SearchSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const OnTextSelectionChangeCallback* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const OnContentScrollCallback* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const OnPasteCallback* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        Ark_CopyOptions value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       Ark_TextAlign value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Ark_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String_Resource* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String_Resource* value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  Ark_SearchType value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Ark_String* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void SearchButtonImpl(Ark_NativePointer node,
                          const Ark_String* value,
                          const Opt_SearchButtonOptions* option)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Ark_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_String_Void* callback)
    {
    }
    } // SearchAttributeModifier
    namespace SecurityComponentMethodModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void IconSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void LayoutDirectionImpl(Ark_NativePointer node,
                             Ark_SecurityComponentLayoutDirection value)
    {
    }
    void PositionImpl(Ark_NativePointer node,
                      const Ark_Position* value)
    {
    }
    void MarkAnchorImpl(Ark_NativePointer node,
                        const Ark_Position* value)
    {
    }
    void OffsetImpl(Ark_NativePointer node,
                    const Ark_Union_Position_Edges_LocalizedEdges* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void IconColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void BackgroundColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void BorderStyleImpl(Ark_NativePointer node,
                         Ark_BorderStyle value)
    {
    }
    void BorderWidthImpl(Ark_NativePointer node,
                         const Ark_Length* value)
    {
    }
    void BorderColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
    {
    }
    void BorderRadiusImpl(Ark_NativePointer node,
                          const Ark_Length* value)
    {
    }
    void PaddingImpl(Ark_NativePointer node,
                     const Ark_Union_Padding_Dimension* value)
    {
    }
    void TextIconSpaceImpl(Ark_NativePointer node,
                           const Ark_Length* value)
    {
    }
    void KeyImpl(Ark_NativePointer node,
                 const Ark_String* value)
    {
    }
    void WidthImpl(Ark_NativePointer node,
                   const Ark_Length* value)
    {
    }
    void HeightImpl(Ark_NativePointer node,
                    const Ark_Length* value)
    {
    }
    void SizeImpl(Ark_NativePointer node,
                  const Ark_SizeOptions* value)
    {
    }
    void ConstraintSizeImpl(Ark_NativePointer node,
                            const Ark_ConstraintSizeOptions* value)
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
    void SelectedImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void ValueImpl(Ark_NativePointer node,
                   const Ark_ResourceStr* value)
    {
    }
    void FontImpl(Ark_NativePointer node,
                  const Ark_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void SelectedOptionBgColorImpl(Ark_NativePointer node,
                                   const Ark_ResourceColor* value)
    {
    }
    void SelectedOptionFontImpl(Ark_NativePointer node,
                                const Ark_Font* value)
    {
    }
    void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void OptionBgColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void OptionFontImpl(Ark_NativePointer node,
                        const Ark_Font* value)
    {
    }
    void OptionFontColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
    {
    }
    void OnSelectImpl(Ark_NativePointer node,
                      const Callback_Number_String_Void* value)
    {
    }
    void SpaceImpl(Ark_NativePointer node,
                   const Ark_Length* value)
    {
    }
    void ArrowPositionImpl(Ark_NativePointer node,
                           Ark_ArrowPosition value)
    {
    }
    void OptionWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Dimension_OptionWidthMode* value)
    {
    }
    void OptionHeightImpl(Ark_NativePointer node,
                          const Ark_Length* value)
    {
    }
    void MenuBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
    {
    }
    void MenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                     Ark_BlurStyle value)
    {
    }
    void ControlSizeImpl(Ark_NativePointer node,
                         Ark_ControlSize value)
    {
    }
    void MenuItemContentModifierImpl(Ark_NativePointer node,
                                     const Ark_CustomObject* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerOptions* value)
    {
    }
    void MenuAlignImpl(Ark_NativePointer node,
                       Ark_MenuAlignType alignType,
                       const Opt_Offset* offset)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Union_Number_Resource_Void* callback)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_ResourceStr_Void* callback)
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
    void SetShapeOptions0Impl(Ark_NativePointer node,
                              Ark_PixelMap value)
    {
    }
    void SetShapeOptions1Impl(Ark_NativePointer node)
    {
    }
    } // ShapeInterfaceModifier
    namespace ShapeAttributeModifier {
    void ViewPortImpl(Ark_NativePointer node,
                      const Ark_ViewportRect* value)
    {
    }
    void StrokeImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
    {
    }
    void FillImpl(Ark_NativePointer node,
                  const Ark_ResourceColor* value)
    {
    }
    void StrokeDashOffsetImpl(Ark_NativePointer node,
                              const Ark_Union_Number_String* value)
    {
    }
    void StrokeDashArrayImpl(Ark_NativePointer node,
                             const Array_Length* value)
    {
    }
    void StrokeLineCapImpl(Ark_NativePointer node,
                           Ark_LineCapStyle value)
    {
    }
    void StrokeLineJoinImpl(Ark_NativePointer node,
                            Ark_LineJoinStyle value)
    {
    }
    void StrokeMiterLimitImpl(Ark_NativePointer node,
                              const Ark_Union_Number_String* value)
    {
    }
    void StrokeOpacityImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String_Resource* value)
    {
    }
    void FillOpacityImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void StrokeWidthImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String* value)
    {
    }
    void AntiAliasImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void MeshImpl(Ark_NativePointer node,
                  const Array_Number* value,
                  const Ark_Number* column,
                  const Ark_Number* row)
    {
    }
    } // ShapeAttributeModifier
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
                        const Ark_ResourceColor* value)
    {
    }
    void TrackColorImpl(Ark_NativePointer node,
                        const Ark_Union_ResourceColor_LinearGradient* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void MinLabelImpl(Ark_NativePointer node,
                      const Ark_String* value)
    {
    }
    void MaxLabelImpl(Ark_NativePointer node,
                      const Ark_String* value)
    {
    }
    void ShowStepsImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void TrackThicknessImpl(Ark_NativePointer node,
                            const Ark_Length* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_SliderChangeMode_Void* value)
    {
    }
    void BlockBorderColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
    {
    }
    void BlockBorderWidthImpl(Ark_NativePointer node,
                              const Ark_Length* value)
    {
    }
    void StepColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void TrackBorderRadiusImpl(Ark_NativePointer node,
                               const Ark_Length* value)
    {
    }
    void SelectedBorderRadiusImpl(Ark_NativePointer node,
                                  const Ark_Length* value)
    {
    }
    void BlockSizeImpl(Ark_NativePointer node,
                       const Ark_SizeOptions* value)
    {
    }
    void BlockStyleImpl(Ark_NativePointer node,
                        const Ark_SliderBlockStyle* value)
    {
    }
    void StepSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void SliderInteractionModeImpl(Ark_NativePointer node,
                                   Ark_SliderInteraction value)
    {
    }
    void MinResponsiveDistanceImpl(Ark_NativePointer node,
                                   const Ark_Number* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void SlideRangeImpl(Ark_NativePointer node,
                        const Ark_SlideRange* value)
    {
    }
    void ShowTipsImpl(Ark_NativePointer node,
                      Ark_Boolean value,
                      const Opt_ResourceStr* content)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback)
    {
    }
    } // SliderAttributeModifier
    namespace BaseSpanModifier {
    Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                    Ark_Int32 flags)
    {
        return {};
    }
    void TextBackgroundStyleImpl(Ark_NativePointer node,
                                 const Ark_TextBackgroundStyle* value)
    {
    }
    void BaselineOffsetImpl(Ark_NativePointer node,
                            Ark_LengthMetrics value)
    {
    }
    } // BaseSpanModifier
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
                  const Ark_Font* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String_Resource* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Ark_DecorationStyleInterface* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String* value)
    {
    }
    void TextCaseImpl(Ark_NativePointer node,
                      Ark_TextCase value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
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
                          Ark_Alignment value)
    {
    }
    void PointLightImpl(Ark_NativePointer node,
                        const Ark_PointLightStyle* value)
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
                               const Opt_Literal_Number_index* value)
    {
    }
    } // StepperInterfaceModifier
    namespace StepperAttributeModifier {
    void OnFinishImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnSkipImpl(Ark_NativePointer node,
                    const Callback_Void* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Number_Void* value)
    {
    }
    void OnNextImpl(Ark_NativePointer node,
                    const Callback_Number_Number_Void* value)
    {
    }
    void OnPreviousImpl(Ark_NativePointer node,
                        const Callback_Number_Number_Void* value)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback)
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
                       const Ark_String* value)
    {
    }
    void NextLabelImpl(Ark_NativePointer node,
                       const Ark_String* value)
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
                   const Ark_Number* value)
    {
    }
    void AutoPlayImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void IntervalImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void Indicator0Impl(Ark_NativePointer node,
                        const Ark_Union_DotIndicator_DigitIndicator_Boolean* value)
    {
    }
    void Indicator1Impl(Ark_NativePointer node,
                        Ark_IndicatorComponentController value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  Ark_Boolean value)
    {
    }
    void DurationImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void VerticalImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void ItemSpaceImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
    {
    }
    void DisplayModeImpl(Ark_NativePointer node,
                         Ark_SwiperDisplayMode value)
    {
    }
    void CachedCountImpl(Ark_NativePointer node,
                         const Ark_Number* value)
    {
    }
    void EffectModeImpl(Ark_NativePointer node,
                        Ark_EdgeEffect value)
    {
    }
    void DisableSwipeImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void CurveImpl(Ark_NativePointer node,
                   const Ark_Union_Curve_String_ICurve* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Void* value)
    {
    }
    void IndicatorStyleImpl(Ark_NativePointer node,
                            const Opt_IndicatorStyle* value)
    {
    }
    void OnAnimationStartImpl(Ark_NativePointer node,
                              const OnSwiperAnimationStartCallback* value)
    {
    }
    void OnAnimationEndImpl(Ark_NativePointer node,
                            const OnSwiperAnimationEndCallback* value)
    {
    }
    void OnGestureSwipeImpl(Ark_NativePointer node,
                            const OnSwiperGestureSwipeCallback* value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          Ark_SwiperNestedScrollMode value)
    {
    }
    void CustomContentTransitionImpl(Ark_NativePointer node,
                                     const Ark_SwiperContentAnimatedTransition* value)
    {
    }
    void OnContentDidScrollImpl(Ark_NativePointer node,
                                const ContentDidScrollCallback* value)
    {
    }
    void IndicatorInteractiveImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void DisplayArrowImpl(Ark_NativePointer node,
                          const Ark_Union_ArrowStyle_Boolean* value,
                          const Opt_Boolean* isHoverShow)
    {
    }
    void DisplayCountImpl(Ark_NativePointer node,
                          const Ark_Union_Number_String_SwiperAutoFill* value,
                          const Opt_Boolean* swipeByGroup)
    {
    }
    void PrevMarginImpl(Ark_NativePointer node,
                        const Ark_Length* value,
                        const Opt_Boolean* ignoreBlank)
    {
    }
    void NextMarginImpl(Ark_NativePointer node,
                        const Ark_Length* value,
                        const Opt_Boolean* ignoreBlank)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback)
    {
    }
    } // SwiperAttributeModifier
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
                          const Ark_Number* value)
    {
    }
    void CountImpl(Ark_NativePointer node,
                   const Ark_Number* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Ark_Union_DotIndicator_DigitIndicator* value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  Ark_Boolean value)
    {
    }
    void VerticalImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Void* value)
    {
    }
    } // IndicatorComponentAttributeModifier
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
                      const Ark_Union_Number_String_Resource* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Array_ResourceColor* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void EffectStrategyImpl(Ark_NativePointer node,
                            Ark_SymbolEffectStrategy value)
    {
    }
    void RenderingStrategyImpl(Ark_NativePointer node,
                               Ark_SymbolRenderingStrategy value)
    {
    }
    void SymbolEffect0Impl(Ark_NativePointer node,
                           Ark_SymbolEffect symbolEffect,
                           const Opt_Boolean* isActive)
    {
    }
    void SymbolEffect1Impl(Ark_NativePointer node,
                           Ark_SymbolEffect symbolEffect,
                           const Opt_Number* triggerValue)
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
                      const Ark_Union_Number_String_Resource* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Array_ResourceColor* value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void EffectStrategyImpl(Ark_NativePointer node,
                            Ark_SymbolEffectStrategy value)
    {
    }
    void RenderingStrategyImpl(Ark_NativePointer node,
                               Ark_SymbolRenderingStrategy value)
    {
    }
    } // SymbolSpanAttributeModifier
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
                      Ark_Boolean value)
    {
    }
    void BarPositionImpl(Ark_NativePointer node,
                         Ark_BarPosition value)
    {
    }
    void ScrollableImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void BarMode0Impl(Ark_NativePointer node,
                      Ark_BarMode value)
    {
    }
    void BarMode1Impl(Ark_NativePointer node,
                      Ark_BarMode value,
                      const Opt_ScrollableBarModeOptions* options)
    {
    }
    void BarWidthImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void BarHeightImpl(Ark_NativePointer node,
                       const Ark_Length* value)
    {
    }
    void AnimationDurationImpl(Ark_NativePointer node,
                               const Ark_Number* value)
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
                      const Callback_Number_Void* value)
    {
    }
    void OnTabBarClickImpl(Ark_NativePointer node,
                           const Callback_Number_Void* value)
    {
    }
    void OnAnimationStartImpl(Ark_NativePointer node,
                              const OnTabsAnimationStartCallback* value)
    {
    }
    void OnAnimationEndImpl(Ark_NativePointer node,
                            const OnTabsAnimationEndCallback* value)
    {
    }
    void OnGestureSwipeImpl(Ark_NativePointer node,
                            const OnTabsGestureSwipeCallback* value)
    {
    }
    void FadingEdgeImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerStyle* value)
    {
    }
    void BarOverlapImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void BarBackgroundColorImpl(Ark_NativePointer node,
                                const Ark_ResourceColor* value)
    {
    }
    void BarGridAlignImpl(Ark_NativePointer node,
                          const Ark_BarGridColumnOptions* value)
    {
    }
    void CustomContentTransitionImpl(Ark_NativePointer node,
                                     const TabsCustomContentTransitionCallback* value)
    {
    }
    void BarBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                     Ark_BlurStyle value)
    {
    }
    void BarBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                     Ark_BlurStyle style,
                                     const Ark_BackgroundBlurStyleOptions* options)
    {
    }
    void BarBackgroundEffectImpl(Ark_NativePointer node,
                                 const Ark_BackgroundEffectOptions* value)
    {
    }
    void OnContentWillChangeImpl(Ark_NativePointer node,
                                 const OnTabsContentWillChangeCallback* value)
    {
    }
    void BarModeScrollableImpl(Ark_NativePointer node,
                               const Ark_ScrollableBarModeOptions* options)
    {
    }
    void _onChangeEvent_indexImpl(Ark_NativePointer node,
                                  const Callback_Number_Void* callback)
    {
    }
    } // TabsAttributeModifier
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
    void TabBar0Impl(Ark_NativePointer node,
                     const Ark_Union_String_Resource_CustomBuilder_TabBarOptions* value)
    {
    }
    void TabBar1Impl(Ark_NativePointer node,
                     const Ark_Union_SubTabBarStyle_BottomTabBarStyle* value)
    {
    }
    void OnWillShowImpl(Ark_NativePointer node,
                        const VoidCallback* value)
    {
    }
    void OnWillHideImpl(Ark_NativePointer node,
                        const VoidCallback* value)
    {
    }
    } // TabContentAttributeModifier
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
    void Font0Impl(Ark_NativePointer node,
                   const Ark_Font* value)
    {
    }
    void Font1Impl(Ark_NativePointer node,
                   const Ark_Font* fontValue,
                   const Opt_FontSettingOptions* options)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String_Resource* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void MinFontScaleImpl(Ark_NativePointer node,
                          const Ark_Union_Number_Resource* value)
    {
    }
    void MaxFontScaleImpl(Ark_NativePointer node,
                          const Ark_Union_Number_Resource* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeight0Impl(Ark_NativePointer node,
                         const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontWeight1Impl(Ark_NativePointer node,
                         const Ark_Union_Number_FontWeight_String* weight,
                         const Opt_FontSettingOptions* options)
    {
    }
    void LineSpacingImpl(Ark_NativePointer node,
                         Ark_LengthMetrics value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       Ark_TextAlign value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String_Resource* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          const Ark_TextOverflowOptions* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Ark_DecorationStyleInterface* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String* value)
    {
    }
    void TextCaseImpl(Ark_NativePointer node,
                      Ark_TextCase value)
    {
    }
    void BaselineOffsetImpl(Ark_NativePointer node,
                            const Ark_Union_Number_String* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        Ark_CopyOptions value)
    {
    }
    void DraggableImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  Ark_TextHeightAdaptivePolicy value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       Ark_WordBreak value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               Ark_LineBreakStrategy value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Callback_String_Void* value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void EllipsisModeImpl(Ark_NativePointer node,
                          Ark_EllipsisMode value)
    {
    }
    void EnableDataDetectorImpl(Ark_NativePointer node,
                                Ark_Boolean value)
    {
    }
    void DataDetectorConfigImpl(Ark_NativePointer node,
                                const Ark_TextDataDetectorConfig* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Callback_Number_Number_Void* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Ark_String* value)
    {
    }
    void PrivacySensitiveImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void TextSelectableImpl(Ark_NativePointer node,
                            Ark_TextSelectableMode value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void HalfLeadingImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void SelectionImpl(Ark_NativePointer node,
                       const Ark_Number* selectionStart,
                       const Ark_Number* selectionEnd)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
                               Ark_TextSpanType spanType,
                               const CustomNodeBuilder* content,
                               Ark_TextResponseType responseType,
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
                              const Ark_ResourceColor* value)
    {
    }
    void PlaceholderFontImpl(Ark_NativePointer node,
                             const Ark_Font* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          Ark_EnterKeyType value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       Ark_TextAlign value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_ResourceStr* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          Ark_TextOverflow value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Ark_CaretStyle* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void OnSubmit0Impl(Ark_NativePointer node,
                       const Callback_EnterKeyType_Void* value)
    {
    }
    void OnSubmit1Impl(Ark_NativePointer node,
                       const TextAreaSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const Callback_Number_Number_Void* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const Callback_Number_Number_Void* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Callback_Boolean_Void* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const Callback_String_PasteEvent_Void* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        Ark_CopyOptions value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   Ark_TextContentStyle value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      Ark_BarState value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  Ark_TextHeightAdaptivePolicy value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       Ark_WordBreak value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               Ark_LineBreakStrategy value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Ark_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String_Resource* value)
    {
    }
    void LineSpacingImpl(Ark_NativePointer node,
                         Ark_LengthMetrics value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String_Resource* value)
    {
    }
    void TypeImpl(Ark_NativePointer node,
                  Ark_TextAreaType value)
    {
    }
    void EnableAutoFillImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void ContentTypeImpl(Ark_NativePointer node,
                         Ark_ContentType value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Ark_String* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Ark_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void ShowCounterImpl(Ark_NativePointer node,
                         Ark_Boolean value,
                         const Opt_InputCounterOptions* options)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void _onChangeEvent_textImpl(Ark_NativePointer node,
                                 const Callback_ResourceStr_Void* callback)
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
                    const Ark_String* value)
    {
    }
    void OnDateChangeImpl(Ark_NativePointer node,
                          const Callback_Number_Void* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_ResourceStr* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Ark_String* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void DateTimeOptionsImpl(Ark_NativePointer node,
                             const Opt_DateTimeOptions* value)
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
                  Ark_InputType value)
    {
    }
    void ContentTypeImpl(Ark_NativePointer node,
                         Ark_ContentType value)
    {
    }
    void PlaceholderColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
    {
    }
    void TextOverflowImpl(Ark_NativePointer node,
                          Ark_TextOverflow value)
    {
    }
    void TextIndentImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void PlaceholderFontImpl(Ark_NativePointer node,
                             const Opt_Font* value)
    {
    }
    void EnterKeyTypeImpl(Ark_NativePointer node,
                          Ark_EnterKeyType value)
    {
    }
    void CaretColorImpl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
    {
    }
    void OnEditChangedImpl(Ark_NativePointer node,
                           const Callback_Boolean_Void* value)
    {
    }
    void OnEditChangeImpl(Ark_NativePointer node,
                          const Callback_Boolean_Void* value)
    {
    }
    void OnSubmitImpl(Ark_NativePointer node,
                      const OnSubmitCallback* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const EditableTextOnChangeCallback* value)
    {
    }
    void OnTextSelectionChangeImpl(Ark_NativePointer node,
                                   const OnTextSelectionChangeCallback* value)
    {
    }
    void OnContentScrollImpl(Ark_NativePointer node,
                             const OnContentScrollCallback* value)
    {
    }
    void MaxLengthImpl(Ark_NativePointer node,
                       const Ark_Number* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_ResourceStr* value)
    {
    }
    void OnCopyImpl(Ark_NativePointer node,
                    const Callback_String_Void* value)
    {
    }
    void OnCutImpl(Ark_NativePointer node,
                   const Callback_String_Void* value)
    {
    }
    void OnPasteImpl(Ark_NativePointer node,
                     const OnPasteCallback* value)
    {
    }
    void CopyOptionImpl(Ark_NativePointer node,
                        Ark_CopyOptions value)
    {
    }
    void ShowPasswordIconImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void TextAlignImpl(Ark_NativePointer node,
                       Ark_TextAlign value)
    {
    }
    void StyleImpl(Ark_NativePointer node,
                   const Ark_Union_TextInputStyle_TextContentStyle* value)
    {
    }
    void CaretStyleImpl(Ark_NativePointer node,
                        const Ark_CaretStyle* value)
    {
    }
    void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                     const Ark_ResourceColor* value)
    {
    }
    void CaretPositionImpl(Ark_NativePointer node,
                           const Ark_Number* value)
    {
    }
    void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void PasswordIconImpl(Ark_NativePointer node,
                          const Ark_PasswordIcon* value)
    {
    }
    void ShowErrorImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
    {
    }
    void ShowUnitImpl(Ark_NativePointer node,
                      const CustomNodeBuilder* value)
    {
    }
    void ShowUnderlineImpl(Ark_NativePointer node,
                           Ark_Boolean value)
    {
    }
    void UnderlineColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_UnderlineColor* value)
    {
    }
    void SelectionMenuHiddenImpl(Ark_NativePointer node,
                                 Ark_Boolean value)
    {
    }
    void BarStateImpl(Ark_NativePointer node,
                      Ark_BarState value)
    {
    }
    void MaxLinesImpl(Ark_NativePointer node,
                      const Ark_Number* value)
    {
    }
    void WordBreakImpl(Ark_NativePointer node,
                       Ark_WordBreak value)
    {
    }
    void LineBreakStrategyImpl(Ark_NativePointer node,
                               Ark_LineBreakStrategy value)
    {
    }
    void CancelButton0Impl(Ark_NativePointer node,
                           const Ark_CancelButtonOptions* value)
    {
    }
    void CancelButton1Impl(Ark_NativePointer node,
                           const Ark_CancelButtonSymbolOptions* value)
    {
    }
    void SelectAllImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void MaxFontSizeImpl(Ark_NativePointer node,
                         const Ark_Union_Number_String_Resource* value)
    {
    }
    void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                                  Ark_TextHeightAdaptivePolicy value)
    {
    }
    void EnableAutoFillImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void DecorationImpl(Ark_NativePointer node,
                        const Ark_TextDecorationOptions* value)
    {
    }
    void LetterSpacingImpl(Ark_NativePointer node,
                           const Ark_Union_Number_String_Resource* value)
    {
    }
    void LineHeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String_Resource* value)
    {
    }
    void PasswordRulesImpl(Ark_NativePointer node,
                           const Ark_String* value)
    {
    }
    void FontFeatureImpl(Ark_NativePointer node,
                         const Ark_String* value)
    {
    }
    void ShowPasswordImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void OnSecurityStateChangeImpl(Ark_NativePointer node,
                                   const Callback_Boolean_Void* value)
    {
    }
    void OnWillInsertImpl(Ark_NativePointer node,
                          const Callback_InsertValue_Boolean* value)
    {
    }
    void OnDidInsertImpl(Ark_NativePointer node,
                         const Callback_InsertValue_Void* value)
    {
    }
    void OnWillDeleteImpl(Ark_NativePointer node,
                          const Callback_DeleteValue_Boolean* value)
    {
    }
    void OnDidDeleteImpl(Ark_NativePointer node,
                         const Callback_DeleteValue_Void* value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void EnablePreviewTextImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void InputFilterImpl(Ark_NativePointer node,
                         const Ark_ResourceStr* value,
                         const Opt_Callback_String_Void* error)
    {
    }
    void CustomKeyboardImpl(Ark_NativePointer node,
                            const CustomNodeBuilder* value,
                            const Opt_KeyboardOptions* options)
    {
    }
    void ShowCounterImpl(Ark_NativePointer node,
                         Ark_Boolean value,
                         const Opt_InputCounterOptions* options)
    {
    }
    void _onChangeEvent_textImpl(Ark_NativePointer node,
                                 const Callback_ResourceStr_Void* callback)
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
                                     const Ark_Union_Number_String* value)
    {
    }
    void CanLoopImpl(Ark_NativePointer node,
                     Ark_Boolean value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Ark_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Ark_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Ark_PickerTextStyle* value)
    {
    }
    void OnAcceptImpl(Ark_NativePointer node,
                      const Callback_String_Number_Void* value)
    {
    }
    void OnCancelImpl(Ark_NativePointer node,
                      const Callback_Void* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Type_TextPickerAttribute_onChange_callback* value)
    {
    }
    void SelectedIndexImpl(Ark_NativePointer node,
                           const Ark_Union_Number_Array_Number* value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerOptions* value)
    {
    }
    void GradientHeightImpl(Ark_NativePointer node,
                            const Ark_Length* value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Union_Number_Array_Number_Void* callback)
    {
    }
    void _onChangeEvent_valueImpl(Ark_NativePointer node,
                                  const Callback_Union_String_Array_String_Void* callback)
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
                    const Ark_String* value)
    {
    }
    void FontColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
    {
    }
    void FontSizeImpl(Ark_NativePointer node,
                      const Ark_Length* value)
    {
    }
    void FontStyleImpl(Ark_NativePointer node,
                       Ark_FontStyle value)
    {
    }
    void FontWeightImpl(Ark_NativePointer node,
                        const Ark_Union_Number_FontWeight_String* value)
    {
    }
    void FontFamilyImpl(Ark_NativePointer node,
                        const Ark_ResourceStr* value)
    {
    }
    void OnTimerImpl(Ark_NativePointer node,
                     const Callback_Number_Number_Void* value)
    {
    }
    void TextShadowImpl(Ark_NativePointer node,
                        const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
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
                             Ark_Boolean value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  Ark_Boolean value)
    {
    }
    void DisappearTextStyleImpl(Ark_NativePointer node,
                                const Ark_PickerTextStyle* value)
    {
    }
    void TextStyleImpl(Ark_NativePointer node,
                       const Ark_PickerTextStyle* value)
    {
    }
    void SelectedTextStyleImpl(Ark_NativePointer node,
                               const Ark_PickerTextStyle* value)
    {
    }
    void DateTimeOptionsImpl(Ark_NativePointer node,
                             const Ark_DateTimeOptions* value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_TimePickerResult_Void* value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                     const Callback_Date_Void* callback)
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
                      const Callback_Boolean_Void* value)
    {
    }
    void ContentModifierImpl(Ark_NativePointer node,
                             const Ark_CustomObject* value)
    {
    }
    void SelectedColorImpl(Ark_NativePointer node,
                           const Ark_ResourceColor* value)
    {
    }
    void SwitchPointColorImpl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
    {
    }
    void SwitchStyleImpl(Ark_NativePointer node,
                         const Ark_SwitchStyle* value)
    {
    }
    void _onChangeEvent_isOnImpl(Ark_NativePointer node,
                                 const Callback_Boolean_Void* callback)
    {
    }
    } // ToggleAttributeModifier
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
                   Ark_Boolean value)
    {
    }
    void AutoPlayImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void ControlsImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void LoopImpl(Ark_NativePointer node,
                  Ark_Boolean value)
    {
    }
    void ObjectFitImpl(Ark_NativePointer node,
                       Ark_ImageFit value)
    {
    }
    void OnStartImpl(Ark_NativePointer node,
                     const VoidCallback* value)
    {
    }
    void OnPauseImpl(Ark_NativePointer node,
                     const VoidCallback* value)
    {
    }
    void OnFinishImpl(Ark_NativePointer node,
                      const VoidCallback* value)
    {
    }
    void OnFullscreenChangeImpl(Ark_NativePointer node,
                                const Callback_FullscreenInfo_Void* value)
    {
    }
    void OnPreparedImpl(Ark_NativePointer node,
                        const Callback_PreparedInfo_Void* value)
    {
    }
    void OnSeekingImpl(Ark_NativePointer node,
                       const Callback_PlaybackInfo_Void* value)
    {
    }
    void OnSeekedImpl(Ark_NativePointer node,
                      const Callback_PlaybackInfo_Void* value)
    {
    }
    void OnUpdateImpl(Ark_NativePointer node,
                      const Callback_PlaybackInfo_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const Callback_Void* value)
    {
    }
    void OnStopImpl(Ark_NativePointer node,
                    const Callback_Void* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void AnalyzerConfigImpl(Ark_NativePointer node,
                            const Ark_ImageAnalyzerConfig* value)
    {
    }
    } // VideoAttributeModifier
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
                              Ark_Boolean value)
    {
    }
    void FileAccessImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void OnlineImageAccessImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void DomStorageAccessImpl(Ark_NativePointer node,
                              Ark_Boolean value)
    {
    }
    void ImageAccessImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void MixedModeImpl(Ark_NativePointer node,
                       Ark_MixedMode value)
    {
    }
    void ZoomAccessImpl(Ark_NativePointer node,
                        Ark_Boolean value)
    {
    }
    void GeolocationAccessImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void JavaScriptProxyImpl(Ark_NativePointer node,
                             const Ark_JavaScriptProxy* value)
    {
    }
    void PasswordImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void CacheModeImpl(Ark_NativePointer node,
                       Ark_CacheMode value)
    {
    }
    void DarkModeImpl(Ark_NativePointer node,
                      Ark_WebDarkMode value)
    {
    }
    void ForceDarkAccessImpl(Ark_NativePointer node,
                             Ark_Boolean value)
    {
    }
    void MediaOptionsImpl(Ark_NativePointer node,
                          const Ark_WebMediaOptions* value)
    {
    }
    void TableDataImpl(Ark_NativePointer node,
                       Ark_Boolean value)
    {
    }
    void WideViewModeAccessImpl(Ark_NativePointer node,
                                Ark_Boolean value)
    {
    }
    void OverviewModeAccessImpl(Ark_NativePointer node,
                                Ark_Boolean value)
    {
    }
    void OverScrollModeImpl(Ark_NativePointer node,
                            Ark_OverScrollMode value)
    {
    }
    void TextZoomAtioImpl(Ark_NativePointer node,
                          const Ark_Number* value)
    {
    }
    void TextZoomRatioImpl(Ark_NativePointer node,
                           const Ark_Number* value)
    {
    }
    void DatabaseAccessImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void InitialScaleImpl(Ark_NativePointer node,
                          const Ark_Number* value)
    {
    }
    void UserAgentImpl(Ark_NativePointer node,
                       const Ark_String* value)
    {
    }
    void MetaViewportImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void OnPageEndImpl(Ark_NativePointer node,
                       const Callback_OnPageEndEvent_Void* value)
    {
    }
    void OnPageBeginImpl(Ark_NativePointer node,
                         const Callback_OnPageBeginEvent_Void* value)
    {
    }
    void OnProgressChangeImpl(Ark_NativePointer node,
                              const Callback_OnProgressChangeEvent_Void* value)
    {
    }
    void OnTitleReceiveImpl(Ark_NativePointer node,
                            const Callback_OnTitleReceiveEvent_Void* value)
    {
    }
    void OnGeolocationHideImpl(Ark_NativePointer node,
                               const Callback_Void* value)
    {
    }
    void OnGeolocationShowImpl(Ark_NativePointer node,
                               const Callback_OnGeolocationShowEvent_Void* value)
    {
    }
    void OnRequestSelectedImpl(Ark_NativePointer node,
                               const Callback_Void* value)
    {
    }
    void OnAlertImpl(Ark_NativePointer node,
                     const Callback_OnAlertEvent_Boolean* value)
    {
    }
    void OnBeforeUnloadImpl(Ark_NativePointer node,
                            const Callback_OnBeforeUnloadEvent_Boolean* value)
    {
    }
    void OnConfirmImpl(Ark_NativePointer node,
                       const Callback_OnConfirmEvent_Boolean* value)
    {
    }
    void OnPromptImpl(Ark_NativePointer node,
                      const Callback_OnPromptEvent_Boolean* value)
    {
    }
    void OnConsoleImpl(Ark_NativePointer node,
                       const Callback_OnConsoleEvent_Boolean* value)
    {
    }
    void OnErrorReceiveImpl(Ark_NativePointer node,
                            const Callback_OnErrorReceiveEvent_Void* value)
    {
    }
    void OnHttpErrorReceiveImpl(Ark_NativePointer node,
                                const Callback_OnHttpErrorReceiveEvent_Void* value)
    {
    }
    void OnDownloadStartImpl(Ark_NativePointer node,
                             const Callback_OnDownloadStartEvent_Void* value)
    {
    }
    void OnRefreshAccessedHistoryImpl(Ark_NativePointer node,
                                      const Callback_OnRefreshAccessedHistoryEvent_Void* value)
    {
    }
    void OnUrlLoadInterceptImpl(Ark_NativePointer node,
                                const Type_WebAttribute_onUrlLoadIntercept_callback* value)
    {
    }
    void OnSslErrorReceiveImpl(Ark_NativePointer node,
                               const Callback_Literal_Function_handler_Object_error_Void* value)
    {
    }
    void OnRenderExited0Impl(Ark_NativePointer node,
                             const Callback_OnRenderExitedEvent_Void* value)
    {
    }
    void OnRenderExited1Impl(Ark_NativePointer node,
                             const Callback_Literal_Object_detail_Boolean* value)
    {
    }
    void OnShowFileSelectorImpl(Ark_NativePointer node,
                                const Callback_OnShowFileSelectorEvent_Boolean* value)
    {
    }
    void OnFileSelectorShowImpl(Ark_NativePointer node,
                                const Type_WebAttribute_onFileSelectorShow_callback* value)
    {
    }
    void OnResourceLoadImpl(Ark_NativePointer node,
                            const Callback_OnResourceLoadEvent_Void* value)
    {
    }
    void OnFullScreenExitImpl(Ark_NativePointer node,
                              const Callback_Void* value)
    {
    }
    void OnFullScreenEnterImpl(Ark_NativePointer node,
                               const OnFullScreenEnterCallback* value)
    {
    }
    void OnScaleChangeImpl(Ark_NativePointer node,
                           const Callback_OnScaleChangeEvent_Void* value)
    {
    }
    void OnHttpAuthRequestImpl(Ark_NativePointer node,
                               const Callback_OnHttpAuthRequestEvent_Boolean* value)
    {
    }
    void OnInterceptRequestImpl(Ark_NativePointer node,
                                const Callback_OnInterceptRequestEvent_WebResourceResponse* value)
    {
    }
    void OnPermissionRequestImpl(Ark_NativePointer node,
                                 const Callback_OnPermissionRequestEvent_Void* value)
    {
    }
    void OnScreenCaptureRequestImpl(Ark_NativePointer node,
                                    const Callback_OnScreenCaptureRequestEvent_Void* value)
    {
    }
    void OnContextMenuShowImpl(Ark_NativePointer node,
                               const Callback_OnContextMenuShowEvent_Boolean* value)
    {
    }
    void OnContextMenuHideImpl(Ark_NativePointer node,
                               const OnContextMenuHideCallback* value)
    {
    }
    void MediaPlayGestureAccessImpl(Ark_NativePointer node,
                                    Ark_Boolean value)
    {
    }
    void OnSearchResultReceiveImpl(Ark_NativePointer node,
                                   const Callback_OnSearchResultReceiveEvent_Void* value)
    {
    }
    void OnScrollImpl(Ark_NativePointer node,
                      const Callback_OnScrollEvent_Void* value)
    {
    }
    void OnSslErrorEventReceiveImpl(Ark_NativePointer node,
                                    const Callback_OnSslErrorEventReceiveEvent_Void* value)
    {
    }
    void OnSslErrorEventImpl(Ark_NativePointer node,
                             const OnSslErrorEventCallback* value)
    {
    }
    void OnClientAuthenticationRequestImpl(Ark_NativePointer node,
                                           const Callback_OnClientAuthenticationEvent_Void* value)
    {
    }
    void OnWindowNewImpl(Ark_NativePointer node,
                         const Callback_OnWindowNewEvent_Void* value)
    {
    }
    void OnWindowExitImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void MultiWindowAccessImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void OnInterceptKeyEventImpl(Ark_NativePointer node,
                                 const Callback_KeyEvent_Boolean* value)
    {
    }
    void WebStandardFontImpl(Ark_NativePointer node,
                             const Ark_String* value)
    {
    }
    void WebSerifFontImpl(Ark_NativePointer node,
                          const Ark_String* value)
    {
    }
    void WebSansSerifFontImpl(Ark_NativePointer node,
                              const Ark_String* value)
    {
    }
    void WebFixedFontImpl(Ark_NativePointer node,
                          const Ark_String* value)
    {
    }
    void WebFantasyFontImpl(Ark_NativePointer node,
                            const Ark_String* value)
    {
    }
    void WebCursiveFontImpl(Ark_NativePointer node,
                            const Ark_String* value)
    {
    }
    void DefaultFixedFontSizeImpl(Ark_NativePointer node,
                                  const Ark_Number* value)
    {
    }
    void DefaultFontSizeImpl(Ark_NativePointer node,
                             const Ark_Number* value)
    {
    }
    void MinFontSizeImpl(Ark_NativePointer node,
                         const Ark_Number* value)
    {
    }
    void MinLogicalFontSizeImpl(Ark_NativePointer node,
                                const Ark_Number* value)
    {
    }
    void DefaultTextEncodingFormatImpl(Ark_NativePointer node,
                                       const Ark_String* value)
    {
    }
    void ForceDisplayScrollBarImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void BlockNetworkImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    void HorizontalScrollBarAccessImpl(Ark_NativePointer node,
                                       Ark_Boolean value)
    {
    }
    void VerticalScrollBarAccessImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void OnTouchIconUrlReceivedImpl(Ark_NativePointer node,
                                    const Callback_OnTouchIconUrlReceivedEvent_Void* value)
    {
    }
    void OnFaviconReceivedImpl(Ark_NativePointer node,
                               const Callback_OnFaviconReceivedEvent_Void* value)
    {
    }
    void OnPageVisibleImpl(Ark_NativePointer node,
                           const Callback_OnPageVisibleEvent_Void* value)
    {
    }
    void OnDataResubmittedImpl(Ark_NativePointer node,
                               const Callback_OnDataResubmittedEvent_Void* value)
    {
    }
    void PinchSmoothImpl(Ark_NativePointer node,
                         Ark_Boolean value)
    {
    }
    void AllowWindowOpenMethodImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void OnAudioStateChangedImpl(Ark_NativePointer node,
                                 const Callback_OnAudioStateChangedEvent_Void* value)
    {
    }
    void OnFirstContentfulPaintImpl(Ark_NativePointer node,
                                    const Callback_OnFirstContentfulPaintEvent_Void* value)
    {
    }
    void OnFirstMeaningfulPaintImpl(Ark_NativePointer node,
                                    const OnFirstMeaningfulPaintCallback* value)
    {
    }
    void OnLargestContentfulPaintImpl(Ark_NativePointer node,
                                      const OnLargestContentfulPaintCallback* value)
    {
    }
    void OnLoadInterceptImpl(Ark_NativePointer node,
                             const Callback_OnLoadInterceptEvent_Boolean* value)
    {
    }
    void OnControllerAttachedImpl(Ark_NativePointer node,
                                  const Callback_Void* value)
    {
    }
    void OnOverScrollImpl(Ark_NativePointer node,
                          const Callback_OnOverScrollEvent_Void* value)
    {
    }
    void OnSafeBrowsingCheckResultImpl(Ark_NativePointer node,
                                       const OnSafeBrowsingCheckResultCallback* value)
    {
    }
    void OnNavigationEntryCommittedImpl(Ark_NativePointer node,
                                        const OnNavigationEntryCommittedCallback* value)
    {
    }
    void OnIntelligentTrackingPreventionResultImpl(Ark_NativePointer node,
                                                   const OnIntelligentTrackingPreventionCallback* value)
    {
    }
    void JavaScriptOnDocumentStartImpl(Ark_NativePointer node,
                                       const Array_ScriptItem* value)
    {
    }
    void JavaScriptOnDocumentEndImpl(Ark_NativePointer node,
                                     const Array_ScriptItem* value)
    {
    }
    void LayoutModeImpl(Ark_NativePointer node,
                        Ark_WebLayoutMode value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_Union_NestedScrollOptions_NestedScrollOptionsExt* value)
    {
    }
    void EnableNativeEmbedModeImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
    {
    }
    void OnNativeEmbedLifecycleChangeImpl(Ark_NativePointer node,
                                          const Callback_NativeEmbedDataInfo_Void* value)
    {
    }
    void OnNativeEmbedVisibilityChangeImpl(Ark_NativePointer node,
                                           const OnNativeEmbedVisibilityChangeCallback* value)
    {
    }
    void OnNativeEmbedGestureEventImpl(Ark_NativePointer node,
                                       const Callback_NativeEmbedTouchInfo_Void* value)
    {
    }
    void CopyOptionsImpl(Ark_NativePointer node,
                         Ark_CopyOptions value)
    {
    }
    void OnOverrideUrlLoadingImpl(Ark_NativePointer node,
                                  const OnOverrideUrlLoadingCallback* value)
    {
    }
    void TextAutosizingImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void EnableNativeMediaPlayerImpl(Ark_NativePointer node,
                                     const Ark_NativeMediaPlayerConfig* value)
    {
    }
    void EnableSmoothDragResizeImpl(Ark_NativePointer node,
                                    Ark_Boolean value)
    {
    }
    void OnRenderProcessNotRespondingImpl(Ark_NativePointer node,
                                          const OnRenderProcessNotRespondingCallback* value)
    {
    }
    void OnRenderProcessRespondingImpl(Ark_NativePointer node,
                                       const OnRenderProcessRespondingCallback* value)
    {
    }
    void SelectionMenuOptionsImpl(Ark_NativePointer node,
                                  const Array_ExpandedMenuItemOptions* value)
    {
    }
    void OnViewportFitChangedImpl(Ark_NativePointer node,
                                  const OnViewportFitChangedCallback* value)
    {
    }
    void OnInterceptKeyboardAttachImpl(Ark_NativePointer node,
                                       const WebKeyboardCallback* value)
    {
    }
    void OnAdsBlockedImpl(Ark_NativePointer node,
                          const OnAdsBlockedCallback* value)
    {
    }
    void KeyboardAvoidModeImpl(Ark_NativePointer node,
                               Ark_WebKeyboardAvoidMode value)
    {
    }
    void EditMenuOptionsImpl(Ark_NativePointer node,
                             Ark_EditMenuOptions value)
    {
    }
    void EnableHapticFeedbackImpl(Ark_NativePointer node,
                                  Ark_Boolean value)
    {
    }
    void RegisterNativeEmbedRuleImpl(Ark_NativePointer node,
                                     const Ark_String* tag,
                                     const Ark_String* type)
    {
    }
    void BindSelectionMenuImpl(Ark_NativePointer node,
                               Ark_WebElementType elementType,
                               const CustomNodeBuilder* content,
                               Ark_WebResponseType responseType,
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
                              const Ark_Position* destination,
                              const Ark_Number* fraction)
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
                                   const Ark_Type_XComponentInterface_value* value)
    {
    }
    void SetXComponentOptions1Impl(Ark_NativePointer node,
                                   const Ark_Type_XComponentInterface_value* value)
    {
    }
    void SetXComponentOptions2Impl(Ark_NativePointer node,
                                   const Ark_XComponentOptions* options)
    {
    }
    } // XComponentInterfaceModifier
    namespace XComponentAttributeModifier {
    void OnLoadImpl(Ark_NativePointer node,
                    const OnNativeLoadCallback* value)
    {
    }
    void OnDestroyImpl(Ark_NativePointer node,
                       const VoidCallback* value)
    {
    }
    void EnableAnalyzerImpl(Ark_NativePointer node,
                            Ark_Boolean value)
    {
    }
    void EnableSecureImpl(Ark_NativePointer node,
                          Ark_Boolean value)
    {
    }
    } // XComponentAttributeModifier
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
                         Ark_Boolean value)
    {
    }
    void ControlButtonImpl(Ark_NativePointer node,
                           const Ark_ButtonStyle* value)
    {
    }
    void ShowControlButtonImpl(Ark_NativePointer node,
                               Ark_Boolean value)
    {
    }
    void OnChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
    {
    }
    void SideBarWidth0Impl(Ark_NativePointer node,
                           const Ark_Number* value)
    {
    }
    void SideBarWidth1Impl(Ark_NativePointer node,
                           const Ark_Length* value)
    {
    }
    void MinSideBarWidth0Impl(Ark_NativePointer node,
                              const Ark_Number* value)
    {
    }
    void MinSideBarWidth1Impl(Ark_NativePointer node,
                              const Ark_Length* value)
    {
    }
    void MaxSideBarWidth0Impl(Ark_NativePointer node,
                              const Ark_Number* value)
    {
    }
    void MaxSideBarWidth1Impl(Ark_NativePointer node,
                              const Ark_Length* value)
    {
    }
    void AutoHideImpl(Ark_NativePointer node,
                      Ark_Boolean value)
    {
    }
    void SideBarPositionImpl(Ark_NativePointer node,
                             Ark_SideBarPosition value)
    {
    }
    void DividerImpl(Ark_NativePointer node,
                     const Opt_DividerStyle* value)
    {
    }
    void MinContentWidthImpl(Ark_NativePointer node,
                             const Ark_Length* value)
    {
    }
    void _onChangeEvent_showSideBarImpl(Ark_NativePointer node,
                                        const Callback_Boolean_Void* callback)
    {
    }
    } // SideBarContainerAttributeModifier
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
                             const Ark_String* value)
    {
    }
    void ItemConstraintSizeImpl(Ark_NativePointer node,
                                const Ark_ConstraintSizeOptions* value)
    {
    }
    void RowsTemplateImpl(Ark_NativePointer node,
                          const Ark_String* value)
    {
    }
    void ColumnsGapImpl(Ark_NativePointer node,
                        const Ark_Length* value)
    {
    }
    void RowsGapImpl(Ark_NativePointer node,
                     const Ark_Length* value)
    {
    }
    void LayoutDirectionImpl(Ark_NativePointer node,
                             Ark_FlexDirection value)
    {
    }
    void NestedScrollImpl(Ark_NativePointer node,
                          const Ark_NestedScrollOptions* value)
    {
    }
    void EnableScrollInteractionImpl(Ark_NativePointer node,
                                     Ark_Boolean value)
    {
    }
    void FrictionImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
    {
    }
    void CachedCount0Impl(Ark_NativePointer node,
                          const Ark_Number* value)
    {
    }
    void CachedCount1Impl(Ark_NativePointer node,
                          const Ark_Number* count,
                          Ark_Boolean show)
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
    void OnReachStartImpl(Ark_NativePointer node,
                          const Callback_Void* value)
    {
    }
    void OnReachEndImpl(Ark_NativePointer node,
                        const Callback_Void* value)
    {
    }
    void OnScrollFrameBeginImpl(Ark_NativePointer node,
                                const Callback_Number_ScrollState_Literal_Number_offsetRemain* value)
    {
    }
    void OnScrollIndexImpl(Ark_NativePointer node,
                           const Callback_Number_Number_Void* value)
    {
    }
    } // WaterFlowAttributeModifier
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
                           const Callback_UIExtensionProxy_Void* value)
    {
    }
    void OnReceiveImpl(Ark_NativePointer node,
                       const Ark_ReceiveCallback* value)
    {
    }
    void OnResultImpl(Ark_NativePointer node,
                      const Callback_Literal_Number_code_Want_want_Void* value)
    {
    }
    void OnReleaseImpl(Ark_NativePointer node,
                       const Callback_Number_Void* value)
    {
    }
    void OnErrorImpl(Ark_NativePointer node,
                     const ErrorCallback* value)
    {
    }
    void OnTerminatedImpl(Ark_NativePointer node,
                          const Callback_TerminationInfo_Void* value)
    {
    }
    } // UIExtensionComponentAttributeModifier
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

    namespace UIStateModifier {
    int64_t GetUIStateImpl(Ark_NativePointer node)
    {
        return 0;
    }
    } // namespace UIStateModifier
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
    const GENERATED_ArkUIRootModifier* GetRootModifier()
    {
        static const GENERATED_ArkUIRootModifier ArkUIRootModifierImpl {
            RootModifier::ConstructImpl,
        };
        return &ArkUIRootModifierImpl;
    }

    const GENERATED_ArkUIComponentRootModifier* GetComponentRootModifier()
    {
        static const GENERATED_ArkUIComponentRootModifier ArkUIComponentRootModifierImpl {
            ComponentRootModifier::ConstructImpl,
        };
        return &ArkUIComponentRootModifierImpl;
    }

    const GENERATED_ArkUIAbilityComponentModifier* GetAbilityComponentModifier()
    {
        static const GENERATED_ArkUIAbilityComponentModifier ArkUIAbilityComponentModifierImpl {
            AbilityComponentModifier::ConstructImpl,
            AbilityComponentInterfaceModifier::SetAbilityComponentOptionsImpl,
            AbilityComponentAttributeModifier::OnConnectImpl,
            AbilityComponentAttributeModifier::OnDisconnectImpl,
        };
        return &ArkUIAbilityComponentModifierImpl;
    }

    const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
    {
        static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
            AlphabetIndexerModifier::ConstructImpl,
            AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
            AlphabetIndexerAttributeModifier::OnSelectedImpl,
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
        };
        return &ArkUIButtonModifierImpl;
    }

    const GENERATED_ArkUICalendarModifier* GetCalendarModifier()
    {
        static const GENERATED_ArkUICalendarModifier ArkUICalendarModifierImpl {
            CalendarModifier::ConstructImpl,
            CalendarInterfaceModifier::SetCalendarOptionsImpl,
            CalendarAttributeModifier::ShowLunarImpl,
            CalendarAttributeModifier::ShowHolidayImpl,
            CalendarAttributeModifier::NeedSlideImpl,
            CalendarAttributeModifier::StartOfWeekImpl,
            CalendarAttributeModifier::OffDaysImpl,
            CalendarAttributeModifier::DirectionImpl,
            CalendarAttributeModifier::CurrentDayStyleImpl,
            CalendarAttributeModifier::NonCurrentDayStyleImpl,
            CalendarAttributeModifier::TodayStyleImpl,
            CalendarAttributeModifier::WeekStyleImpl,
            CalendarAttributeModifier::WorkStateStyleImpl,
            CalendarAttributeModifier::OnSelectChangeImpl,
            CalendarAttributeModifier::OnRequestDataImpl,
        };
        return &ArkUICalendarModifierImpl;
    }

    const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier()
    {
        static const GENERATED_ArkUICalendarPickerModifier ArkUICalendarPickerModifierImpl {
            CalendarPickerModifier::ConstructImpl,
            CalendarPickerInterfaceModifier::SetCalendarPickerOptionsImpl,
            CalendarPickerAttributeModifier::TextStyleImpl,
            CalendarPickerAttributeModifier::OnChangeImpl,
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
            CommonMethodModifier::TouchableImpl,
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
            CommonMethodModifier::BackgroundEffectImpl,
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
            CommonMethodModifier::OnClick1Impl,
            CommonMethodModifier::OnHoverImpl,
            CommonMethodModifier::OnAccessibilityHoverImpl,
            CommonMethodModifier::HoverEffectImpl,
            CommonMethodModifier::OnMouseImpl,
            CommonMethodModifier::OnTouchImpl,
            CommonMethodModifier::OnKeyEventImpl,
            CommonMethodModifier::OnKeyPreImeImpl,
            CommonMethodModifier::FocusableImpl,
            CommonMethodModifier::OnFocusImpl,
            CommonMethodModifier::OnBlurImpl,
            CommonMethodModifier::TabIndexImpl,
            CommonMethodModifier::DefaultFocusImpl,
            CommonMethodModifier::GroupDefaultFocusImpl,
            CommonMethodModifier::FocusOnTouchImpl,
            CommonMethodModifier::FocusBoxImpl,
            CommonMethodModifier::AnimationImpl,
            CommonMethodModifier::Transition0Impl,
            CommonMethodModifier::Transition1Impl,
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
            CommonMethodModifier::UseEffect1Impl,
            CommonMethodModifier::RenderGroupImpl,
            CommonMethodModifier::FreezeImpl,
            CommonMethodModifier::TranslateImpl,
            CommonMethodModifier::ScaleImpl,
            CommonMethodModifier::GridSpanImpl,
            CommonMethodModifier::GridOffsetImpl,
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
            CommonMethodModifier::UseSizeTypeImpl,
            CommonMethodModifier::AlignRules0Impl,
            CommonMethodModifier::AlignRules1Impl,
            CommonMethodModifier::AspectRatioImpl,
            CommonMethodModifier::ClickEffectImpl,
            CommonMethodModifier::OnDragStartImpl,
            CommonMethodModifier::OnDragEnterImpl,
            CommonMethodModifier::OnDragMoveImpl,
            CommonMethodModifier::OnDragLeaveImpl,
            CommonMethodModifier::OnDropImpl,
            CommonMethodModifier::OnDragEndImpl,
            CommonMethodModifier::AllowDropImpl,
            CommonMethodModifier::DraggableImpl,
            CommonMethodModifier::DragPreviewImpl,
            CommonMethodModifier::OnPreDragImpl,
            CommonMethodModifier::LinearGradientImpl,
            CommonMethodModifier::SweepGradientImpl,
            CommonMethodModifier::RadialGradientImpl,
            CommonMethodModifier::MotionPathImpl,
            CommonMethodModifier::ShadowImpl,
            CommonMethodModifier::Clip0Impl,
            CommonMethodModifier::Clip1Impl,
            CommonMethodModifier::ClipShapeImpl,
            CommonMethodModifier::Mask0Impl,
            CommonMethodModifier::Mask1Impl,
            CommonMethodModifier::MaskShapeImpl,
            CommonMethodModifier::KeyImpl,
            CommonMethodModifier::IdImpl,
            CommonMethodModifier::GeometryTransition0Impl,
            CommonMethodModifier::GeometryTransition1Impl,
            CommonMethodModifier::StateStylesImpl,
            CommonMethodModifier::RestoreIdImpl,
            CommonMethodModifier::SphericalEffectImpl,
            CommonMethodModifier::LightUpEffectImpl,
            CommonMethodModifier::PixelStretchEffectImpl,
            CommonMethodModifier::AccessibilityGroup0Impl,
            CommonMethodModifier::AccessibilityGroup1Impl,
            CommonMethodModifier::AccessibilityText0Impl,
            CommonMethodModifier::AccessibilityText1Impl,
            CommonMethodModifier::AccessibilityTextHintImpl,
            CommonMethodModifier::AccessibilityDescription0Impl,
            CommonMethodModifier::AccessibilityDescription1Impl,
            CommonMethodModifier::AccessibilityLevelImpl,
            CommonMethodModifier::AccessibilityVirtualNodeImpl,
            CommonMethodModifier::AccessibilityCheckedImpl,
            CommonMethodModifier::AccessibilitySelectedImpl,
            CommonMethodModifier::ObscuredImpl,
            CommonMethodModifier::ReuseIdImpl,
            CommonMethodModifier::RenderFitImpl,
            CommonMethodModifier::GestureModifierImpl,
            CommonMethodModifier::BackgroundBrightnessImpl,
            CommonMethodModifier::OnGestureJudgeBeginImpl,
            CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
            CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
            CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
            CommonMethodModifier::MonopolizeEventsImpl,
            CommonMethodModifier::OnTouchInterceptImpl,
            CommonMethodModifier::OnSizeChangeImpl,
            CommonMethodModifier::CustomPropertyImpl,
            CommonMethodModifier::ExpandSafeAreaImpl,
            CommonMethodModifier::BackgroundImpl,
            CommonMethodModifier::BackgroundImageImpl,
            CommonMethodModifier::BackgroundBlurStyleImpl,
            CommonMethodModifier::ForegroundBlurStyleImpl,
            CommonMethodModifier::FocusScopeId0Impl,
            CommonMethodModifier::FocusScopeId1Impl,
            CommonMethodModifier::FocusScopePriorityImpl,
            CommonMethodModifier::GestureImpl,
            CommonMethodModifier::PriorityGestureImpl,
            CommonMethodModifier::ParallelGestureImpl,
            CommonMethodModifier::BlurImpl,
            CommonMethodModifier::LinearGradientBlurImpl,
            CommonMethodModifier::SystemBarEffectImpl,
            CommonMethodModifier::BackdropBlurImpl,
            CommonMethodModifier::SharedTransitionImpl,
            CommonMethodModifier::ChainModeImpl,
            CommonMethodModifier::DragPreviewOptionsImpl,
            CommonMethodModifier::OverlayImpl,
            CommonMethodModifier::BlendModeImpl,
            CommonMethodModifier::AdvancedBlendModeImpl,
            CommonMethodModifier::BindPopupImpl,
            CommonMethodModifier::BindMenu0Impl,
            CommonMethodModifier::BindMenu1Impl,
            CommonMethodModifier::BindContextMenu0Impl,
            CommonMethodModifier::BindContextMenu1Impl,
            CommonMethodModifier::BindContentCover0Impl,
            CommonMethodModifier::BindContentCover1Impl,
            CommonMethodModifier::BindSheetImpl,
            CommonMethodModifier::OnVisibleAreaChangeImpl,
            CommonMethodModifier::KeyboardShortcutImpl,
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

    const GENERATED_ArkUICommonModifier* GetCommonModifier()
    {
        static const GENERATED_ArkUICommonModifier ArkUICommonModifierImpl {
            CommonModifier::ConstructImpl,
            CommonInterfaceModifier::SetCommonOptionsImpl,
        };
        return &ArkUICommonModifierImpl;
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
            ScrollableCommonMethodModifier::OnScrollImpl,
            ScrollableCommonMethodModifier::OnReachStartImpl,
            ScrollableCommonMethodModifier::OnReachEndImpl,
            ScrollableCommonMethodModifier::OnScrollStartImpl,
            ScrollableCommonMethodModifier::OnScrollStopImpl,
            ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
            ScrollableCommonMethodModifier::ClipContentImpl,
            ScrollableCommonMethodModifier::EdgeEffectImpl,
            ScrollableCommonMethodModifier::FadingEdgeImpl,
        };
        return &ArkUIScrollableCommonMethodModifierImpl;
    }

    const GENERATED_ArkUIComponent3DModifier* GetComponent3DModifier()
    {
        static const GENERATED_ArkUIComponent3DModifier ArkUIComponent3DModifierImpl {
            Component3DModifier::ConstructImpl,
            Component3DInterfaceModifier::SetComponent3DOptionsImpl,
            Component3DAttributeModifier::EnvironmentImpl,
            Component3DAttributeModifier::ShaderImpl,
            Component3DAttributeModifier::ShaderImageTextureImpl,
            Component3DAttributeModifier::ShaderInputBufferImpl,
            Component3DAttributeModifier::RenderWidthImpl,
            Component3DAttributeModifier::RenderHeightImpl,
            Component3DAttributeModifier::CustomRenderImpl,
        };
        return &ArkUIComponent3DModifierImpl;
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
            DatePickerAttributeModifier::OnChangeImpl,
            DatePickerAttributeModifier::OnDateChangeImpl,
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
            GridAttributeModifier::ScrollBarWidthImpl,
            GridAttributeModifier::ScrollBarColorImpl,
            GridAttributeModifier::ScrollBarImpl,
            GridAttributeModifier::OnScrollBarUpdateImpl,
            GridAttributeModifier::OnScrollIndexImpl,
            GridAttributeModifier::CachedCount0Impl,
            GridAttributeModifier::CachedCount1Impl,
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
            GridAttributeModifier::NestedScrollImpl,
            GridAttributeModifier::EnableScrollInteractionImpl,
            GridAttributeModifier::FrictionImpl,
            GridAttributeModifier::AlignItemsImpl,
            GridAttributeModifier::OnScrollImpl,
            GridAttributeModifier::OnWillScrollImpl,
            GridAttributeModifier::OnDidScrollImpl,
            GridAttributeModifier::OnReachStartImpl,
            GridAttributeModifier::OnReachEndImpl,
            GridAttributeModifier::OnScrollStartImpl,
            GridAttributeModifier::OnScrollStopImpl,
            GridAttributeModifier::OnScrollFrameBeginImpl,
            GridAttributeModifier::EdgeEffectImpl,
        };
        return &ArkUIGridModifierImpl;
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
            GridItemAttributeModifier::ForceRebuildImpl,
            GridItemAttributeModifier::SelectableImpl,
            GridItemAttributeModifier::SelectedImpl,
            GridItemAttributeModifier::OnSelectImpl,
            GridItemAttributeModifier::_onChangeEvent_selectedImpl,
        };
        return &ArkUIGridItemModifierImpl;
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

    const GENERATED_ArkUIGridContainerModifier* GetGridContainerModifier()
    {
        static const GENERATED_ArkUIGridContainerModifier ArkUIGridContainerModifierImpl {
            GridContainerModifier::ConstructImpl,
            GridContainerInterfaceModifier::SetGridContainerOptionsImpl,
        };
        return &ArkUIGridContainerModifierImpl;
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
            ImageInterfaceModifier::SetImageOptions2Impl,
            ImageAttributeModifier::AltImpl,
            ImageAttributeModifier::MatchTextDirectionImpl,
            ImageAttributeModifier::FitOriginalSizeImpl,
            ImageAttributeModifier::FillColorImpl,
            ImageAttributeModifier::ObjectFitImpl,
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
            ImageAnimatorAttributeModifier::PreDecodeImpl,
            ImageAnimatorAttributeModifier::FillModeImpl,
            ImageAnimatorAttributeModifier::IterationsImpl,
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

    const GENERATED_ArkUIListModifier* GetListModifier()
    {
        static const GENERATED_ArkUIListModifier ArkUIListModifierImpl {
            ListModifier::ConstructImpl,
            ListInterfaceModifier::SetListOptionsImpl,
            ListAttributeModifier::AlignListItemImpl,
            ListAttributeModifier::ListDirectionImpl,
            ListAttributeModifier::ScrollBarImpl,
            ListAttributeModifier::ContentStartOffsetImpl,
            ListAttributeModifier::ContentEndOffsetImpl,
            ListAttributeModifier::DividerImpl,
            ListAttributeModifier::EditModeImpl,
            ListAttributeModifier::MultiSelectableImpl,
            ListAttributeModifier::CachedCount0Impl,
            ListAttributeModifier::CachedCount1Impl,
            ListAttributeModifier::ChainAnimationImpl,
            ListAttributeModifier::ChainAnimationOptionsImpl,
            ListAttributeModifier::StickyImpl,
            ListAttributeModifier::ScrollSnapAlignImpl,
            ListAttributeModifier::NestedScrollImpl,
            ListAttributeModifier::EnableScrollInteractionImpl,
            ListAttributeModifier::FrictionImpl,
            ListAttributeModifier::ChildrenMainSizeImpl,
            ListAttributeModifier::MaintainVisibleContentPositionImpl,
            ListAttributeModifier::OnScrollImpl,
            ListAttributeModifier::OnScrollIndexImpl,
            ListAttributeModifier::OnScrollVisibleContentChangeImpl,
            ListAttributeModifier::OnWillScrollImpl,
            ListAttributeModifier::OnDidScrollImpl,
            ListAttributeModifier::OnReachStartImpl,
            ListAttributeModifier::OnReachEndImpl,
            ListAttributeModifier::OnScrollStartImpl,
            ListAttributeModifier::OnScrollStopImpl,
            ListAttributeModifier::OnItemDeleteImpl,
            ListAttributeModifier::OnItemMoveImpl,
            ListAttributeModifier::OnItemDragStartImpl,
            ListAttributeModifier::OnItemDragEnterImpl,
            ListAttributeModifier::OnItemDragMoveImpl,
            ListAttributeModifier::OnItemDragLeaveImpl,
            ListAttributeModifier::OnItemDropImpl,
            ListAttributeModifier::OnScrollFrameBeginImpl,
            ListAttributeModifier::LanesImpl,
            ListAttributeModifier::EdgeEffectImpl,
        };
        return &ArkUIListModifierImpl;
    }

    const GENERATED_ArkUIListItemModifier* GetListItemModifier()
    {
        static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
            ListItemModifier::ConstructImpl,
            ListItemInterfaceModifier::SetListItemOptions0Impl,
            ListItemInterfaceModifier::SetListItemOptions1Impl,
            ListItemAttributeModifier::StickyImpl,
            ListItemAttributeModifier::EditableImpl,
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

    const GENERATED_ArkUILocationButtonModifier* GetLocationButtonModifier()
    {
        static const GENERATED_ArkUILocationButtonModifier ArkUILocationButtonModifierImpl {
            LocationButtonModifier::ConstructImpl,
            LocationButtonInterfaceModifier::SetLocationButtonOptions0Impl,
            LocationButtonInterfaceModifier::SetLocationButtonOptions1Impl,
            LocationButtonAttributeModifier::OnClickImpl,
        };
        return &ArkUILocationButtonModifierImpl;
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
            MenuAttributeModifier::FontSizeImpl,
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
            NavDestinationAttributeModifier::HideTitleBar1Impl,
            NavDestinationAttributeModifier::OnShownImpl,
            NavDestinationAttributeModifier::OnHiddenImpl,
            NavDestinationAttributeModifier::OnBackPressedImpl,
            NavDestinationAttributeModifier::ModeImpl,
            NavDestinationAttributeModifier::BackButtonIconImpl,
            NavDestinationAttributeModifier::MenusImpl,
            NavDestinationAttributeModifier::OnReadyImpl,
            NavDestinationAttributeModifier::OnWillAppearImpl,
            NavDestinationAttributeModifier::OnWillDisappearImpl,
            NavDestinationAttributeModifier::OnWillShowImpl,
            NavDestinationAttributeModifier::OnWillHideImpl,
            NavDestinationAttributeModifier::SystemBarStyleImpl,
            NavDestinationAttributeModifier::RecoverableImpl,
            NavDestinationAttributeModifier::SystemTransitionImpl,
            NavDestinationAttributeModifier::TitleImpl,
            NavDestinationAttributeModifier::ToolbarConfigurationImpl,
            NavDestinationAttributeModifier::HideToolBarImpl,
            NavDestinationAttributeModifier::IgnoreLayoutSafeAreaImpl,
        };
        return &ArkUINavDestinationModifierImpl;
    }

    const GENERATED_ArkUINavRouterModifier* GetNavRouterModifier()
    {
        static const GENERATED_ArkUINavRouterModifier ArkUINavRouterModifierImpl {
            NavRouterModifier::ConstructImpl,
            NavRouterInterfaceModifier::SetNavRouterOptions0Impl,
            NavRouterInterfaceModifier::SetNavRouterOptions1Impl,
            NavRouterAttributeModifier::OnStateChangeImpl,
            NavRouterAttributeModifier::ModeImpl,
        };
        return &ArkUINavRouterModifierImpl;
    }

    const GENERATED_ArkUINavigatorModifier* GetNavigatorModifier()
    {
        static const GENERATED_ArkUINavigatorModifier ArkUINavigatorModifierImpl {
            NavigatorModifier::ConstructImpl,
            NavigatorInterfaceModifier::SetNavigatorOptions0Impl,
            NavigatorInterfaceModifier::SetNavigatorOptions1Impl,
            NavigatorAttributeModifier::ActiveImpl,
            NavigatorAttributeModifier::TypeImpl,
            NavigatorAttributeModifier::TargetImpl,
            NavigatorAttributeModifier::ParamsImpl,
        };
        return &ArkUINavigatorModifierImpl;
    }

    const GENERATED_ArkUINodeContainerModifier* GetNodeContainerModifier()
    {
        static const GENERATED_ArkUINodeContainerModifier ArkUINodeContainerModifierImpl {
            NodeContainerModifier::ConstructImpl,
            NodeContainerInterfaceModifier::SetNodeContainerOptionsImpl,
        };
        return &ArkUINodeContainerModifierImpl;
    }

    const GENERATED_ArkUIPanelModifier* GetPanelModifier()
    {
        static const GENERATED_ArkUIPanelModifier ArkUIPanelModifierImpl {
            PanelModifier::ConstructImpl,
            PanelInterfaceModifier::SetPanelOptionsImpl,
            PanelAttributeModifier::ModeImpl,
            PanelAttributeModifier::TypeImpl,
            PanelAttributeModifier::DragBarImpl,
            PanelAttributeModifier::CustomHeightImpl,
            PanelAttributeModifier::FullHeightImpl,
            PanelAttributeModifier::HalfHeightImpl,
            PanelAttributeModifier::MiniHeightImpl,
            PanelAttributeModifier::ShowImpl,
            PanelAttributeModifier::BackgroundMaskImpl,
            PanelAttributeModifier::ShowCloseIconImpl,
            PanelAttributeModifier::OnChangeImpl,
            PanelAttributeModifier::OnHeightChangeImpl,
            PanelAttributeModifier::_onChangeEvent_modeImpl,
        };
        return &ArkUIPanelModifierImpl;
    }

    const GENERATED_ArkUIPasteButtonModifier* GetPasteButtonModifier()
    {
        static const GENERATED_ArkUIPasteButtonModifier ArkUIPasteButtonModifierImpl {
            PasteButtonModifier::ConstructImpl,
            PasteButtonInterfaceModifier::SetPasteButtonOptions0Impl,
            PasteButtonInterfaceModifier::SetPasteButtonOptions1Impl,
            PasteButtonAttributeModifier::OnClickImpl,
        };
        return &ArkUIPasteButtonModifierImpl;
    }

    const GENERATED_ArkUIPathModifier* GetPathModifier()
    {
        static const GENERATED_ArkUIPathModifier ArkUIPathModifierImpl {
            PathModifier::ConstructImpl,
            PathInterfaceModifier::SetPathOptionsImpl,
            PathAttributeModifier::CommandsImpl,
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
            RectAttributeModifier::RadiusWidthImpl,
            RectAttributeModifier::RadiusHeightImpl,
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
            RelativeContainerAttributeModifier::Barrier0Impl,
            RelativeContainerAttributeModifier::Barrier1Impl,
        };
        return &ArkUIRelativeContainerModifierImpl;
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

    const GENERATED_ArkUISaveButtonModifier* GetSaveButtonModifier()
    {
        static const GENERATED_ArkUISaveButtonModifier ArkUISaveButtonModifierImpl {
            SaveButtonModifier::ConstructImpl,
            SaveButtonInterfaceModifier::SetSaveButtonOptions0Impl,
            SaveButtonInterfaceModifier::SetSaveButtonOptions1Impl,
            SaveButtonAttributeModifier::OnClickImpl,
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
            ScrollAttributeModifier::ScrollableImpl,
            ScrollAttributeModifier::OnScrollImpl,
            ScrollAttributeModifier::OnWillScrollImpl,
            ScrollAttributeModifier::OnDidScrollImpl,
            ScrollAttributeModifier::OnScrollEdgeImpl,
            ScrollAttributeModifier::OnScrollStartImpl,
            ScrollAttributeModifier::OnScrollEndImpl,
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
            SearchAttributeModifier::OnSubmit0Impl,
            SearchAttributeModifier::OnSubmit1Impl,
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
            SearchAttributeModifier::SearchButtonImpl,
            SearchAttributeModifier::InputFilterImpl,
            SearchAttributeModifier::CustomKeyboardImpl,
            SearchAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUISearchModifierImpl;
    }

    const GENERATED_ArkUISecurityComponentMethodModifier* GetSecurityComponentMethodModifier()
    {
        static const GENERATED_ArkUISecurityComponentMethodModifier ArkUISecurityComponentMethodModifierImpl {
            SecurityComponentMethodModifier::ConstructImpl,
            SecurityComponentMethodModifier::IconSizeImpl,
            SecurityComponentMethodModifier::LayoutDirectionImpl,
            SecurityComponentMethodModifier::PositionImpl,
            SecurityComponentMethodModifier::MarkAnchorImpl,
            SecurityComponentMethodModifier::OffsetImpl,
            SecurityComponentMethodModifier::FontSizeImpl,
            SecurityComponentMethodModifier::FontStyleImpl,
            SecurityComponentMethodModifier::FontWeightImpl,
            SecurityComponentMethodModifier::FontFamilyImpl,
            SecurityComponentMethodModifier::FontColorImpl,
            SecurityComponentMethodModifier::IconColorImpl,
            SecurityComponentMethodModifier::BackgroundColorImpl,
            SecurityComponentMethodModifier::BorderStyleImpl,
            SecurityComponentMethodModifier::BorderWidthImpl,
            SecurityComponentMethodModifier::BorderColorImpl,
            SecurityComponentMethodModifier::BorderRadiusImpl,
            SecurityComponentMethodModifier::PaddingImpl,
            SecurityComponentMethodModifier::TextIconSpaceImpl,
            SecurityComponentMethodModifier::KeyImpl,
            SecurityComponentMethodModifier::WidthImpl,
            SecurityComponentMethodModifier::HeightImpl,
            SecurityComponentMethodModifier::SizeImpl,
            SecurityComponentMethodModifier::ConstraintSizeImpl,
        };
        return &ArkUISecurityComponentMethodModifierImpl;
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
            ShapeInterfaceModifier::SetShapeOptions0Impl,
            ShapeInterfaceModifier::SetShapeOptions1Impl,
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

    const GENERATED_ArkUISliderModifier* GetSliderModifier()
    {
        static const GENERATED_ArkUISliderModifier ArkUISliderModifierImpl {
            SliderModifier::ConstructImpl,
            SliderInterfaceModifier::SetSliderOptionsImpl,
            SliderAttributeModifier::BlockColorImpl,
            SliderAttributeModifier::TrackColorImpl,
            SliderAttributeModifier::SelectedColorImpl,
            SliderAttributeModifier::MinLabelImpl,
            SliderAttributeModifier::MaxLabelImpl,
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
            SliderAttributeModifier::ShowTipsImpl,
            SliderAttributeModifier::_onChangeEvent_valueImpl,
        };
        return &ArkUISliderModifierImpl;
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

    const GENERATED_ArkUISpanModifier* GetSpanModifier()
    {
        static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
            SpanModifier::ConstructImpl,
            SpanInterfaceModifier::SetSpanOptionsImpl,
            SpanAttributeModifier::FontImpl,
            SpanAttributeModifier::FontColorImpl,
            SpanAttributeModifier::FontSizeImpl,
            SpanAttributeModifier::FontStyleImpl,
            SpanAttributeModifier::FontWeightImpl,
            SpanAttributeModifier::FontFamilyImpl,
            SpanAttributeModifier::DecorationImpl,
            SpanAttributeModifier::LetterSpacingImpl,
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
            SwiperAttributeModifier::AutoPlayImpl,
            SwiperAttributeModifier::IntervalImpl,
            SwiperAttributeModifier::Indicator0Impl,
            SwiperAttributeModifier::Indicator1Impl,
            SwiperAttributeModifier::LoopImpl,
            SwiperAttributeModifier::DurationImpl,
            SwiperAttributeModifier::VerticalImpl,
            SwiperAttributeModifier::ItemSpaceImpl,
            SwiperAttributeModifier::DisplayModeImpl,
            SwiperAttributeModifier::CachedCountImpl,
            SwiperAttributeModifier::EffectModeImpl,
            SwiperAttributeModifier::DisableSwipeImpl,
            SwiperAttributeModifier::CurveImpl,
            SwiperAttributeModifier::OnChangeImpl,
            SwiperAttributeModifier::IndicatorStyleImpl,
            SwiperAttributeModifier::OnAnimationStartImpl,
            SwiperAttributeModifier::OnAnimationEndImpl,
            SwiperAttributeModifier::OnGestureSwipeImpl,
            SwiperAttributeModifier::NestedScrollImpl,
            SwiperAttributeModifier::CustomContentTransitionImpl,
            SwiperAttributeModifier::OnContentDidScrollImpl,
            SwiperAttributeModifier::IndicatorInteractiveImpl,
            SwiperAttributeModifier::DisplayArrowImpl,
            SwiperAttributeModifier::DisplayCountImpl,
            SwiperAttributeModifier::PrevMarginImpl,
            SwiperAttributeModifier::NextMarginImpl,
            SwiperAttributeModifier::_onChangeEvent_indexImpl,
        };
        return &ArkUISwiperModifierImpl;
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
            SymbolGlyphAttributeModifier::SymbolEffect0Impl,
            SymbolGlyphAttributeModifier::SymbolEffect1Impl,
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

    const GENERATED_ArkUITabsModifier* GetTabsModifier()
    {
        static const GENERATED_ArkUITabsModifier ArkUITabsModifierImpl {
            TabsModifier::ConstructImpl,
            TabsInterfaceModifier::SetTabsOptionsImpl,
            TabsAttributeModifier::VerticalImpl,
            TabsAttributeModifier::BarPositionImpl,
            TabsAttributeModifier::ScrollableImpl,
            TabsAttributeModifier::BarMode0Impl,
            TabsAttributeModifier::BarMode1Impl,
            TabsAttributeModifier::BarWidthImpl,
            TabsAttributeModifier::BarHeightImpl,
            TabsAttributeModifier::AnimationDurationImpl,
            TabsAttributeModifier::AnimationModeImpl,
            TabsAttributeModifier::EdgeEffectImpl,
            TabsAttributeModifier::OnChangeImpl,
            TabsAttributeModifier::OnTabBarClickImpl,
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
            TabsAttributeModifier::BarBackgroundBlurStyle1Impl,
            TabsAttributeModifier::BarBackgroundEffectImpl,
            TabsAttributeModifier::OnContentWillChangeImpl,
            TabsAttributeModifier::BarModeScrollableImpl,
            TabsAttributeModifier::_onChangeEvent_indexImpl,
        };
        return &ArkUITabsModifierImpl;
    }

    const GENERATED_ArkUITabContentModifier* GetTabContentModifier()
    {
        static const GENERATED_ArkUITabContentModifier ArkUITabContentModifierImpl {
            TabContentModifier::ConstructImpl,
            TabContentInterfaceModifier::SetTabContentOptionsImpl,
            TabContentAttributeModifier::TabBar0Impl,
            TabContentAttributeModifier::TabBar1Impl,
            TabContentAttributeModifier::OnWillShowImpl,
            TabContentAttributeModifier::OnWillHideImpl,
        };
        return &ArkUITabContentModifierImpl;
    }

    const GENERATED_ArkUITextModifier* GetTextModifier()
    {
        static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
            TextModifier::ConstructImpl,
            TextInterfaceModifier::SetTextOptionsImpl,
            TextAttributeModifier::Font0Impl,
            TextAttributeModifier::Font1Impl,
            TextAttributeModifier::FontColorImpl,
            TextAttributeModifier::FontSizeImpl,
            TextAttributeModifier::MinFontSizeImpl,
            TextAttributeModifier::MaxFontSizeImpl,
            TextAttributeModifier::MinFontScaleImpl,
            TextAttributeModifier::MaxFontScaleImpl,
            TextAttributeModifier::FontStyleImpl,
            TextAttributeModifier::FontWeight0Impl,
            TextAttributeModifier::FontWeight1Impl,
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
            TextAttributeModifier::PrivacySensitiveImpl,
            TextAttributeModifier::TextSelectableImpl,
            TextAttributeModifier::EditMenuOptionsImpl,
            TextAttributeModifier::HalfLeadingImpl,
            TextAttributeModifier::EnableHapticFeedbackImpl,
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
            TextAreaAttributeModifier::OnSubmit0Impl,
            TextAreaAttributeModifier::OnSubmit1Impl,
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
            TextInputAttributeModifier::OnEditChangedImpl,
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
            TextInputAttributeModifier::CancelButton0Impl,
            TextInputAttributeModifier::CancelButton1Impl,
            TextInputAttributeModifier::SelectAllImpl,
            TextInputAttributeModifier::MinFontSizeImpl,
            TextInputAttributeModifier::MaxFontSizeImpl,
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
            TextPickerAttributeModifier::OnAcceptImpl,
            TextPickerAttributeModifier::OnCancelImpl,
            TextPickerAttributeModifier::OnChangeImpl,
            TextPickerAttributeModifier::SelectedIndexImpl,
            TextPickerAttributeModifier::DividerImpl,
            TextPickerAttributeModifier::GradientHeightImpl,
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
            TimePickerAttributeModifier::EnableHapticFeedbackImpl,
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
        };
        return &ArkUIVideoModifierImpl;
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
            WebAttributeModifier::PasswordImpl,
            WebAttributeModifier::CacheModeImpl,
            WebAttributeModifier::DarkModeImpl,
            WebAttributeModifier::ForceDarkAccessImpl,
            WebAttributeModifier::MediaOptionsImpl,
            WebAttributeModifier::TableDataImpl,
            WebAttributeModifier::WideViewModeAccessImpl,
            WebAttributeModifier::OverviewModeAccessImpl,
            WebAttributeModifier::OverScrollModeImpl,
            WebAttributeModifier::TextZoomAtioImpl,
            WebAttributeModifier::TextZoomRatioImpl,
            WebAttributeModifier::DatabaseAccessImpl,
            WebAttributeModifier::InitialScaleImpl,
            WebAttributeModifier::UserAgentImpl,
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
            WebAttributeModifier::OnUrlLoadInterceptImpl,
            WebAttributeModifier::OnSslErrorReceiveImpl,
            WebAttributeModifier::OnRenderExited0Impl,
            WebAttributeModifier::OnRenderExited1Impl,
            WebAttributeModifier::OnShowFileSelectorImpl,
            WebAttributeModifier::OnFileSelectorShowImpl,
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
            WebAttributeModifier::EnableSmoothDragResizeImpl,
            WebAttributeModifier::OnRenderProcessNotRespondingImpl,
            WebAttributeModifier::OnRenderProcessRespondingImpl,
            WebAttributeModifier::SelectionMenuOptionsImpl,
            WebAttributeModifier::OnViewportFitChangedImpl,
            WebAttributeModifier::OnInterceptKeyboardAttachImpl,
            WebAttributeModifier::OnAdsBlockedImpl,
            WebAttributeModifier::KeyboardAvoidModeImpl,
            WebAttributeModifier::EditMenuOptionsImpl,
            WebAttributeModifier::EnableHapticFeedbackImpl,
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
        };
        return &ArkUIXComponentModifierImpl;
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
            SideBarContainerAttributeModifier::SideBarWidth1Impl,
            SideBarContainerAttributeModifier::MinSideBarWidth0Impl,
            SideBarContainerAttributeModifier::MinSideBarWidth1Impl,
            SideBarContainerAttributeModifier::MaxSideBarWidth0Impl,
            SideBarContainerAttributeModifier::MaxSideBarWidth1Impl,
            SideBarContainerAttributeModifier::AutoHideImpl,
            SideBarContainerAttributeModifier::SideBarPositionImpl,
            SideBarContainerAttributeModifier::DividerImpl,
            SideBarContainerAttributeModifier::MinContentWidthImpl,
            SideBarContainerAttributeModifier::_onChangeEvent_showSideBarImpl,
        };
        return &ArkUISideBarContainerModifierImpl;
    }

    const GENERATED_ArkUIRemoteWindowModifier* GetRemoteWindowModifier()
    {
        static const GENERATED_ArkUIRemoteWindowModifier ArkUIRemoteWindowModifierImpl {
            RemoteWindowModifier::ConstructImpl,
            RemoteWindowInterfaceModifier::SetRemoteWindowOptionsImpl,
        };
        return &ArkUIRemoteWindowModifierImpl;
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
            WaterFlowAttributeModifier::NestedScrollImpl,
            WaterFlowAttributeModifier::EnableScrollInteractionImpl,
            WaterFlowAttributeModifier::FrictionImpl,
            WaterFlowAttributeModifier::CachedCount0Impl,
            WaterFlowAttributeModifier::CachedCount1Impl,
            WaterFlowAttributeModifier::OnWillScrollImpl,
            WaterFlowAttributeModifier::OnDidScrollImpl,
            WaterFlowAttributeModifier::OnReachStartImpl,
            WaterFlowAttributeModifier::OnReachEndImpl,
            WaterFlowAttributeModifier::OnScrollFrameBeginImpl,
            WaterFlowAttributeModifier::OnScrollIndexImpl,
        };
        return &ArkUIWaterFlowModifierImpl;
    }

    const GENERATED_ArkUIUIExtensionComponentModifier* GetUIExtensionComponentModifier()
    {
        static const GENERATED_ArkUIUIExtensionComponentModifier ArkUIUIExtensionComponentModifierImpl {
            UIExtensionComponentModifier::ConstructImpl,
            UIExtensionComponentInterfaceModifier::SetUIExtensionComponentOptionsImpl,
            UIExtensionComponentAttributeModifier::OnRemoteReadyImpl,
            UIExtensionComponentAttributeModifier::OnReceiveImpl,
            UIExtensionComponentAttributeModifier::OnResultImpl,
            UIExtensionComponentAttributeModifier::OnReleaseImpl,
            UIExtensionComponentAttributeModifier::OnErrorImpl,
            UIExtensionComponentAttributeModifier::OnTerminatedImpl,
        };
        return &ArkUIUIExtensionComponentModifierImpl;
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

    const GENERATED_ArkUIStateModifier* GetUIStateModifier()
    {
        static const GENERATED_ArkUIStateModifier arkUiuiStateModifierImpl {
            UIStateModifier::ConstructImpl,
            UIStateModifier::GetUIStateImpl,
        };
        return &arkUiuiStateModifierImpl;
    }

    const GENERATED_ArkUINodeModifiers* GENERATED_GetArkUINodeModifiers()
    {
        static const GENERATED_ArkUINodeModifiers modifiersImpl = {
            GetRootModifier,
            GetComponentRootModifier,
            GetAbilityComponentModifier,
            GetAlphabetIndexerModifier,
            GetAnimatorModifier,
            GetBadgeModifier,
            GetBlankModifier,
            GetButtonModifier,
            GetCalendarModifier,
            GetCalendarPickerModifier,
            GetCanvasModifier,
            GetCheckboxModifier,
            GetCheckboxGroupModifier,
            GetCircleModifier,
            GetColumnModifier,
            GetColumnSplitModifier,
            GetCommonMethodModifier,
            GetCommonShapeMethodModifier,
            GetCommonModifier,
            GetScrollableCommonMethodModifier,
            GetComponent3DModifier,
            GetContainerSpanModifier,
            GetCounterModifier,
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
            GetGridItemModifier,
            GetGridColModifier,
            GetGridContainerModifier,
            GetGridRowModifier,
            GetHyperlinkModifier,
            GetImageModifier,
            GetImageAnimatorModifier,
            GetImageSpanModifier,
            GetLineModifier,
            GetListModifier,
            GetListItemModifier,
            GetListItemGroupModifier,
            GetLoadingProgressModifier,
            GetLocationButtonModifier,
            GetMarqueeModifier,
            GetMediaCachedImageModifier,
            GetMenuModifier,
            GetMenuItemModifier,
            GetMenuItemGroupModifier,
            GetNavDestinationModifier,
            GetNavRouterModifier,
            GetNavigatorModifier,
            GetNodeContainerModifier,
            GetPanelModifier,
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
            GetRichEditorModifier,
            GetRichTextModifier,
            GetRootSceneModifier,
            GetRowModifier,
            GetRowSplitModifier,
            GetSaveButtonModifier,
            GetScreenModifier,
            GetScrollModifier,
            GetScrollBarModifier,
            GetSearchModifier,
            GetSecurityComponentMethodModifier,
            GetSelectModifier,
            GetShapeModifier,
            GetSliderModifier,
            GetBaseSpanModifier,
            GetSpanModifier,
            GetStackModifier,
            GetStepperModifier,
            GetStepperItemModifier,
            GetSwiperModifier,
            GetIndicatorComponentModifier,
            GetSymbolGlyphModifier,
            GetSymbolSpanModifier,
            GetTabsModifier,
            GetTabContentModifier,
            GetTextModifier,
            GetTextAreaModifier,
            GetTextClockModifier,
            GetTextInputModifier,
            GetTextPickerModifier,
            GetTextTimerModifier,
            GetTimePickerModifier,
            GetToggleModifier,
            GetVideoModifier,
            GetWebModifier,
            GetWindowSceneModifier,
            GetXComponentModifier,
            GetSideBarContainerModifier,
            GetRemoteWindowModifier,
            GetWaterFlowModifier,
            GetUIExtensionComponentModifier,
            GetLinearIndicatorModifier,
            GetUIStateModifier,
        };
        return &modifiersImpl;
    }
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
    namespace UnifiedDataAccessor {
    void DestroyPeerImpl(Ark_UnifiedData peer)
    {
        auto peerImpl = reinterpret_cast<UnifiedDataPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UnifiedData CtorImpl()
    {
        return new UnifiedDataPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean HasTypeImpl(Ark_UnifiedData peer,
                            const Ark_String* UnifiedData_type)
    {
        return {};
    }
    Array_String GetTypesImpl(Ark_UnifiedData peer)
    {
        return {};
    }
    } // UnifiedDataAccessor
    namespace LazyForEachOpsAccessor {
    } // LazyForEachOpsAccessor
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
    } // SystemOpsAccessor
    namespace FocusControllerAccessor {
    void RequestFocusImpl(const Ark_String* key)
    {
    }
    } // FocusControllerAccessor
    namespace DrawableDescriptorAccessor {
    void DestroyPeerImpl(Ark_DrawableDescriptor peer)
    {
        auto peerImpl = reinterpret_cast<DrawableDescriptorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawableDescriptor CtorImpl()
    {
        return new DrawableDescriptorPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PixelMap GetPixelMapImpl(Ark_DrawableDescriptor peer)
    {
        return {};
    }
    } // DrawableDescriptorAccessor
    namespace LayeredDrawableDescriptorAccessor {
    void DestroyPeerImpl(Ark_LayeredDrawableDescriptor peer)
    {
        auto peerImpl = reinterpret_cast<LayeredDrawableDescriptorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayeredDrawableDescriptor CtorImpl(const Opt_DrawableDescriptor* foreground,
                                           const Opt_DrawableDescriptor* background,
                                           const Opt_DrawableDescriptor* mask)
    {
        return new LayeredDrawableDescriptorPeer(foreground, background, mask);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_DrawableDescriptor GetForegroundImpl(Ark_LayeredDrawableDescriptor peer)
    {
        return {};
    }
    Ark_DrawableDescriptor GetBackgroundImpl(Ark_LayeredDrawableDescriptor peer)
    {
        return {};
    }
    Ark_DrawableDescriptor GetMaskImpl(Ark_LayeredDrawableDescriptor peer)
    {
        return {};
    }
    Ark_String GetMaskClipPathImpl()
    {
        return {};
    }
    } // LayeredDrawableDescriptorAccessor
    namespace PixelMapDrawableDescriptorAccessor {
    void DestroyPeerImpl(Ark_PixelMapDrawableDescriptor peer)
    {
        auto peerImpl = reinterpret_cast<PixelMapDrawableDescriptorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PixelMapDrawableDescriptor CtorImpl(const Opt_PixelMap* src)
    {
        return new PixelMapDrawableDescriptorPeer(src);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // PixelMapDrawableDescriptorAccessor
    namespace AnimatedDrawableDescriptorAccessor {
    void DestroyPeerImpl(Ark_AnimatedDrawableDescriptor peer)
    {
        auto peerImpl = reinterpret_cast<AnimatedDrawableDescriptorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AnimatedDrawableDescriptor CtorImpl(const Array_PixelMap* pixelMaps,
                                            const Opt_AnimationOptions* options)
    {
        return new AnimatedDrawableDescriptorPeer(pixelMaps, options);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // AnimatedDrawableDescriptorAccessor
    namespace DrawingCanvasAccessor {
    void DestroyPeerImpl(Ark_DrawingCanvas peer)
    {
        auto peerImpl = reinterpret_cast<DrawingCanvasPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawingCanvas CtorImpl(Ark_PixelMap pixelmap)
    {
        return new DrawingCanvasPeer(pixelmap);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DrawRectImpl(Ark_DrawingCanvas peer,
                      const Ark_Number* left,
                      const Ark_Number* top,
                      const Ark_Number* right,
                      const Ark_Number* bottom)
    {
    }
    } // DrawingCanvasAccessor
    namespace LengthMetricsAccessor {
    void DestroyPeerImpl(Ark_LengthMetrics peer)
    {
        auto peerImpl = reinterpret_cast<LengthMetricsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LengthMetrics CtorImpl()
    {
        return new LengthMetricsPeer();
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
    namespace ColorMetricsAccessor {
    void DestroyPeerImpl(Ark_ColorMetrics peer)
    {
        auto peerImpl = reinterpret_cast<ColorMetricsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ColorMetrics CtorImpl()
    {
        return new ColorMetricsPeer();
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
                              const Opt_Number* alpha)
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
    Ark_String GetColorImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number GetRedImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number GetGreenImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number GetBlueImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    Ark_Number GetAlphaImpl(Ark_ColorMetrics peer)
    {
        return {};
    }
    } // ColorMetricsAccessor
    namespace WebviewControllerAccessor {
    void DestroyPeerImpl(Ark_WebviewController peer)
    {
        auto peerImpl = reinterpret_cast<WebviewControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebviewController CtorImpl()
    {
        return new WebviewControllerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void InitializeWebEngineImpl()
    {
    }
    void LoadUrlImpl(Ark_WebviewController peer,
                     const Ark_Union_String_Resource* url,
                     const Opt_Array_WebHeader* headers)
    {
    }
    } // WebviewControllerAccessor
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
                                  const Ark_Number* time)
    {
    }
    } // GlobalScope_ohos_arkui_performanceMonitorAccessor
    namespace CommonShapeAccessor {
    void DestroyPeerImpl(Ark_CommonShape peer)
    {
        auto peerImpl = reinterpret_cast<CommonShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CommonShape CtorImpl()
    {
        return new CommonShapePeer();
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
    namespace BaseShapeAccessor {
    void DestroyPeerImpl(Ark_BaseShape peer)
    {
        auto peerImpl = reinterpret_cast<BaseShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseShape CtorImpl()
    {
        return new BaseShapePeer();
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
    namespace RectShapeAccessor {
    void DestroyPeerImpl(Ark_RectShape peer)
    {
        auto peerImpl = reinterpret_cast<RectShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RectShape CtorImpl(const Opt_Union_RectShapeOptions_RoundRectShapeOptions* options)
    {
        return new RectShapePeer(options);
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
    namespace CircleShapeAccessor {
    void DestroyPeerImpl(Ark_CircleShape peer)
    {
        auto peerImpl = reinterpret_cast<CircleShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CircleShape CtorImpl(const Opt_ShapeSize* options)
    {
        return new CircleShapePeer(options);
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
    namespace EllipseShapeAccessor {
    void DestroyPeerImpl(Ark_EllipseShape peer)
    {
        auto peerImpl = reinterpret_cast<EllipseShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EllipseShape CtorImpl(const Opt_ShapeSize* options)
    {
        return new EllipseShapePeer(options);
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
    namespace PathShapeAccessor {
    void DestroyPeerImpl(Ark_PathShape peer)
    {
        auto peerImpl = reinterpret_cast<PathShapePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PathShape CtorImpl(const Opt_PathShapeOptions* options)
    {
        return new PathShapePeer(options);
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
    namespace SymbolEffectAccessor {
    void DestroyPeerImpl(Ark_SymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<SymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SymbolEffect CtorImpl()
    {
        return new SymbolEffectPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DummyForAccessorGenerateImpl(Ark_SymbolEffect peer)
    {
    }
    } // SymbolEffectAccessor
    namespace ScaleSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_ScaleSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<ScaleSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScaleSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                                   const Opt_EffectDirection* direction)
    {
        return new ScaleSymbolEffectPeer(scope, direction);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectScope GetScopeImpl(Ark_ScaleSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_ScaleSymbolEffect peer,
                      Ark_EffectScope scope)
    {
    }
    Ark_EffectDirection GetDirectionImpl(Ark_ScaleSymbolEffect peer)
    {
        return {};
    }
    void SetDirectionImpl(Ark_ScaleSymbolEffect peer,
                          Ark_EffectDirection direction)
    {
    }
    } // ScaleSymbolEffectAccessor
    namespace ReplaceSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_ReplaceSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<ReplaceSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ReplaceSymbolEffect CtorImpl(const Opt_EffectScope* scope)
    {
        return new ReplaceSymbolEffectPeer(scope);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectScope GetScopeImpl(Ark_ReplaceSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_ReplaceSymbolEffect peer,
                      Ark_EffectScope scope)
    {
    }
    } // ReplaceSymbolEffectAccessor
    namespace FrameNodeAccessor {
    void DestroyPeerImpl(Ark_FrameNode peer)
    {
        auto peerImpl = reinterpret_cast<FrameNodePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FrameNode CtorImpl(const Ark_UIContext* uiContext)
    {
        return new FrameNodePeer(uiContext);
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
                               const Ark_Number* index)
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
    Ark_Number GetOpacityImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_GraphicsPosition GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
    {
        return {};
    }
    Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
    {
        return {};
    }
    } // FrameNodeAccessor
    namespace PixelMapAccessor {
    void DestroyPeerImpl(Ark_PixelMap peer)
    {
        auto peerImpl = reinterpret_cast<PixelMapPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PixelMap CtorImpl()
    {
        return new PixelMapPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReadPixelsToBufferSyncImpl(Ark_PixelMap peer,
                                    const Ark_Buffer* dst)
    {
    }
    void WriteBufferToPixelsImpl(Ark_PixelMap peer,
                                 const Ark_Buffer* src)
    {
    }
    Ark_Boolean GetIsEditableImpl(Ark_PixelMap peer)
    {
        return {};
    }
    Ark_Boolean GetIsStrideAlignmentImpl(Ark_PixelMap peer)
    {
        return {};
    }
    } // PixelMapAccessor
    namespace NavExtenderAccessor {
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
    Ark_NativePointer NavigationCreateImpl(Ark_Int32 peer,
                                           Ark_Int32 flag)
    {
        return {};
    }
    void SetNavigationOptionsImpl(Ark_NativePointer navigation,
                                  Ark_NavPathStack stack)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    void SetNavDestinationNodeImpl(Ark_NavPathStack peer,
                                   Ark_Int32 index,
                                   Ark_NativePointer node)
    {
    }
    } // NavExtenderAccessor
    namespace EventEmulatorAccessor {
    void EmitTextInputEventImpl(Ark_NativePointer node,
                                const Ark_String* text)
    {
        auto frameNode = reinterpret_cast<FrameNode *>(node);
        CHECK_NULL_VOID(frameNode);
    }
    } // EventEmulatorAccessor
    namespace ActionSheetAccessor {
    void ShowImpl(const Ark_ActionSheetOptions* value)
    {
    }
    } // ActionSheetAccessor
    namespace AlertDialogAccessor {
    void ShowImpl(const Ark_Type_AlertDialog_show_value* value)
    {
    }
    } // AlertDialogAccessor
    namespace SpringPropAccessor {
    void DestroyPeerImpl(Ark_SpringProp peer)
    {
        auto peerImpl = reinterpret_cast<SpringPropPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SpringProp CtorImpl(const Ark_Number* mass,
                            const Ark_Number* stiffness,
                            const Ark_Number* damping)
    {
        return new SpringPropPeer(mass, stiffness, damping);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // SpringPropAccessor
    namespace SpringMotionAccessor {
    void DestroyPeerImpl(Ark_SpringMotion peer)
    {
        auto peerImpl = reinterpret_cast<SpringMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SpringMotion CtorImpl(const Ark_Number* start,
                              const Ark_Number* end,
                              const Ark_Number* velocity,
                              Ark_SpringProp prop)
    {
        return new SpringMotionPeer(start, end, velocity, prop);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // SpringMotionAccessor
    namespace FrictionMotionAccessor {
    void DestroyPeerImpl(Ark_FrictionMotion peer)
    {
        auto peerImpl = reinterpret_cast<FrictionMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FrictionMotion CtorImpl(const Ark_Number* friction,
                                const Ark_Number* position,
                                const Ark_Number* velocity)
    {
        return new FrictionMotionPeer(friction, position, velocity);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // FrictionMotionAccessor
    namespace ScrollMotionAccessor {
    void DestroyPeerImpl(Ark_ScrollMotion peer)
    {
        auto peerImpl = reinterpret_cast<ScrollMotionPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScrollMotion CtorImpl(const Ark_Number* position,
                              const Ark_Number* velocity,
                              const Ark_Number* min,
                              const Ark_Number* max,
                              Ark_SpringProp prop)
    {
        return new ScrollMotionPeer(position, velocity, min, max, prop);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // ScrollMotionAccessor
    namespace CalendarControllerAccessor {
    void DestroyPeerImpl(Ark_CalendarController peer)
    {
        auto peerImpl = reinterpret_cast<CalendarControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CalendarController CtorImpl()
    {
        return new CalendarControllerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void BackToTodayImpl(Ark_CalendarController peer)
    {
    }
    void GoToImpl(Ark_CalendarController peer,
                  const Ark_Literal_Number_day_month_year* value)
    {
    }
    } // CalendarControllerAccessor
    namespace CalendarPickerDialogAccessor {
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
    Ark_CanvasGradient CtorImpl()
    {
        return new CanvasGradientPeer();
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
    Ark_CanvasPath CtorImpl()
    {
        return new CanvasPathPeer();
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
    namespace Path2DAccessor {
    void DestroyPeerImpl(Ark_Path2D peer)
    {
        auto peerImpl = reinterpret_cast<Path2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Path2D CtorImpl()
    {
        return new Path2DPeer();
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
    namespace CanvasPatternAccessor {
    void DestroyPeerImpl(Ark_CanvasPattern peer)
    {
        auto peerImpl = reinterpret_cast<CanvasPatternPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasPattern CtorImpl()
    {
        return new CanvasPatternPeer();
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
    namespace ImageBitmapAccessor {
    void DestroyPeerImpl(Ark_ImageBitmap peer)
    {
        auto peerImpl = reinterpret_cast<ImageBitmapPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageBitmap CtorImpl(const Ark_String* src)
    {
        return new ImageBitmapPeer(src);
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
    Ark_Number GetWidthImpl(Ark_ImageBitmap peer)
    {
        return {};
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
    Ark_ImageData CtorImpl(const Ark_Number* width,
                           const Ark_Number* height,
                           const Opt_Buffer* data)
    {
        return new ImageDataPeer(width, height, data);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Buffer GetDataImpl(Ark_ImageData peer)
    {
        return {};
    }
    Ark_Number GetHeightImpl(Ark_ImageData peer)
    {
        return {};
    }
    Ark_Number GetWidthImpl(Ark_ImageData peer)
    {
        return {};
    }
    } // ImageDataAccessor
    namespace RenderingContextSettingsAccessor {
    void DestroyPeerImpl(Ark_RenderingContextSettings peer)
    {
        auto peerImpl = reinterpret_cast<RenderingContextSettingsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RenderingContextSettings CtorImpl(const Opt_Boolean* antialias)
    {
        return new RenderingContextSettingsPeer(antialias);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean GetAntialiasImpl(Ark_RenderingContextSettings peer)
    {
        return {};
    }
    void SetAntialiasImpl(Ark_RenderingContextSettings peer,
                          Ark_Boolean antialias)
    {
    }
    } // RenderingContextSettingsAccessor
    namespace CanvasRendererAccessor {
    void DestroyPeerImpl(Ark_CanvasRenderer peer)
    {
        auto peerImpl = reinterpret_cast<CanvasRendererPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CanvasRenderer CtorImpl()
    {
        return new CanvasRendererPeer();
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
    void Stroke0Impl(Ark_CanvasRenderer peer)
    {
    }
    void Stroke1Impl(Ark_CanvasRenderer peer,
                     Ark_Path2D path)
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
    Ark_PixelMap GetPixelMapImpl(Ark_CanvasRenderer peer,
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
                         const Opt_PixelMap* value)
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
    Ark_CanvasRenderingContext2D CtorImpl(const Opt_RenderingContextSettings* settings)
    {
        return new CanvasRenderingContext2DPeer(settings);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String ToDataURLImpl(Ark_CanvasRenderingContext2D peer,
                             const Opt_String* type,
                             const Opt_Float32* quality)
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
    void OnOnDetachImpl(Ark_VMContext vmContext,
                        Ark_CanvasRenderingContext2D peer,
                        const Callback_Void* callback_)
    {
    }
    void OffOnDetachImpl(Ark_VMContext vmContext,
                         Ark_CanvasRenderingContext2D peer,
                         const Opt_Callback_Void* callback_)
    {
    }
    Ark_Number GetHeightImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    Ark_Number GetWidthImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    Ark_FrameNode GetCanvasImpl(Ark_CanvasRenderingContext2D peer)
    {
        return {};
    }
    } // CanvasRenderingContext2DAccessor
    namespace OffscreenCanvasRenderingContext2DAccessor {
    void DestroyPeerImpl(Ark_OffscreenCanvasRenderingContext2D peer)
    {
        auto peerImpl = reinterpret_cast<OffscreenCanvasRenderingContext2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_OffscreenCanvasRenderingContext2D CtorImpl(const Ark_Number* width,
                                                   const Ark_Number* height,
                                                   const Opt_RenderingContextSettings* settings)
    {
        return new OffscreenCanvasRenderingContext2DPeer(width, height, settings);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String ToDataURLImpl(Ark_OffscreenCanvasRenderingContext2D peer,
                             const Opt_String* type,
                             const Opt_Float32* quality)
    {
        return {};
    }
    Ark_ImageBitmap TransferToImageBitmapImpl(Ark_OffscreenCanvasRenderingContext2D peer)
    {
        return {};
    }
    } // OffscreenCanvasRenderingContext2DAccessor
    namespace OffscreenCanvasAccessor {
    void DestroyPeerImpl(Ark_OffscreenCanvas peer)
    {
        auto peerImpl = reinterpret_cast<OffscreenCanvasPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_OffscreenCanvas CtorImpl(const Ark_Number* width,
                                 const Ark_Number* height)
    {
        return new OffscreenCanvasPeer(width, height);
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
    namespace DrawingRenderingContextAccessor {
    void DestroyPeerImpl(Ark_DrawingRenderingContext peer)
    {
        auto peerImpl = reinterpret_cast<DrawingRenderingContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawingRenderingContext CtorImpl(const Opt_LengthMetricsUnit* unit)
    {
        return new DrawingRenderingContextPeer(unit);
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
    Ark_DrawingCanvas GetCanvasImpl(Ark_DrawingRenderingContext peer)
    {
        return {};
    }
    } // DrawingRenderingContextAccessor
    namespace ICurveAccessor {
    void DestroyPeerImpl(Ark_ICurve peer)
    {
        auto peerImpl = reinterpret_cast<ICurvePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ICurve CtorImpl()
    {
        return new ICurvePeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number InterpolateImpl(Ark_ICurve peer,
                               const Ark_Number* fraction)
    {
        return {};
    }
    } // ICurveAccessor
    namespace DrawModifierAccessor {
    void DestroyPeerImpl(Ark_DrawModifier peer)
    {
        auto peerImpl = reinterpret_cast<DrawModifierPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DrawModifier CtorImpl()
    {
        return new DrawModifierPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void DrawBehindImpl(Ark_DrawModifier peer,
                        const Ark_DrawContext* drawContext)
    {
    }
    void DrawContentImpl(Ark_DrawModifier peer,
                         const Ark_DrawContext* drawContext)
    {
    }
    void DrawFrontImpl(Ark_DrawModifier peer,
                       const Ark_DrawContext* drawContext)
    {
    }
    void InvalidateImpl(Ark_DrawModifier peer)
    {
    }
    } // DrawModifierAccessor
    namespace TransitionEffectAccessor {
    void DestroyPeerImpl(Ark_TransitionEffect peer)
    {
        auto peerImpl = reinterpret_cast<TransitionEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TransitionEffect CtorImpl(const Ark_String* type,
                                  const Ark_TransitionEffects* effect)
    {
        return new TransitionEffectPeer(type, effect);
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
    Ark_TransitionEffect GetIDENTITYImpl()
    {
        return {};
    }
    Ark_TransitionEffect GetOPACITYImpl()
    {
        return {};
    }
    Ark_TransitionEffect GetSLIDEImpl()
    {
        return {};
    }
    Ark_TransitionEffect GetSLIDE_SWITCHImpl()
    {
        return {};
    }
    } // TransitionEffectAccessor
    namespace BaseEventAccessor {
    void DestroyPeerImpl(Ark_BaseEvent peer)
    {
        auto peerImpl = reinterpret_cast<BaseEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseEvent CtorImpl()
    {
        return new BaseEventPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                        Ark_BaseEvent peer,
                                        const Array_String* keys)
    {
        return {};
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
    Ark_Number GetAxisHorizontalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                               const Ark_Number* axisHorizontal)
    {
    }
    Ark_Number GetAxisVerticalImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetAxisVerticalImpl(Ark_BaseEvent peer,
                             const Ark_Number* axisVertical)
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
    Ark_SourceTool GetSourceToolImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetSourceToolImpl(Ark_BaseEvent peer,
                           Ark_SourceTool sourceTool)
    {
    }
    Ark_Number GetDeviceIdImpl(Ark_BaseEvent peer)
    {
        return {};
    }
    void SetDeviceIdImpl(Ark_BaseEvent peer,
                         const Ark_Number* deviceId)
    {
    }
    } // BaseEventAccessor
    namespace ClickEventAccessor {
    void DestroyPeerImpl(Ark_ClickEvent peer)
    {
        auto peerImpl = reinterpret_cast<ClickEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ClickEvent CtorImpl()
    {
        return new ClickEventPeer();
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
    Ark_Number GetScreenXImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetScreenXImpl(Ark_ClickEvent peer,
                        const Ark_Number* screenX)
    {
    }
    Ark_Number GetScreenYImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetScreenYImpl(Ark_ClickEvent peer,
                        const Ark_Number* screenY)
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
    Callback_Void GetPreventDefaultImpl(Ark_ClickEvent peer)
    {
        return {};
    }
    void SetPreventDefaultImpl(Ark_ClickEvent peer,
                               const Callback_Void* preventDefault)
    {
    }
    } // ClickEventAccessor
    namespace HoverEventAccessor {
    void DestroyPeerImpl(Ark_HoverEvent peer)
    {
        auto peerImpl = reinterpret_cast<HoverEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HoverEvent CtorImpl()
    {
        return new HoverEventPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
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
    namespace MouseEventAccessor {
    void DestroyPeerImpl(Ark_MouseEvent peer)
    {
        auto peerImpl = reinterpret_cast<MouseEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_MouseEvent CtorImpl()
    {
        return new MouseEventPeer();
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
    Ark_Number GetScreenXImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetScreenXImpl(Ark_MouseEvent peer,
                        const Ark_Number* screenX)
    {
    }
    Ark_Number GetScreenYImpl(Ark_MouseEvent peer)
    {
        return {};
    }
    void SetScreenYImpl(Ark_MouseEvent peer,
                        const Ark_Number* screenY)
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
    } // MouseEventAccessor
    namespace AccessibilityHoverEventAccessor {
    void DestroyPeerImpl(Ark_AccessibilityHoverEvent peer)
    {
        auto peerImpl = reinterpret_cast<AccessibilityHoverEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AccessibilityHoverEvent CtorImpl()
    {
        return new AccessibilityHoverEventPeer();
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
    namespace TouchEventAccessor {
    void DestroyPeerImpl(Ark_TouchEvent peer)
    {
        auto peerImpl = reinterpret_cast<TouchEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TouchEvent CtorImpl()
    {
        return new TouchEventPeer();
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
    namespace PixelMapMockAccessor {
    void DestroyPeerImpl(Ark_PixelMapMock peer)
    {
        auto peerImpl = reinterpret_cast<PixelMapMockPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PixelMapMock CtorImpl()
    {
        return new PixelMapMockPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReleaseImpl(Ark_PixelMapMock peer)
    {
    }
    } // PixelMapMockAccessor
    namespace DragEventAccessor {
    void DestroyPeerImpl(Ark_DragEvent peer)
    {
        auto peerImpl = reinterpret_cast<DragEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DragEvent CtorImpl()
    {
        return new DragEventPeer();
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
    Ark_Number GetXImpl(Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Number GetYImpl(Ark_DragEvent peer)
    {
        return {};
    }
    void SetDataImpl(Ark_DragEvent peer,
                     Ark_UnifiedData unifiedData)
    {
    }
    Ark_UnifiedData GetDataImpl(Ark_VMContext vmContext,
                                Ark_DragEvent peer)
    {
        return {};
    }
    Ark_Summary GetSummaryImpl(Ark_DragEvent peer)
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
    Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                        Ark_DragEvent peer,
                                        const Array_String* keys)
    {
        return {};
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
    } // DragEventAccessor
    namespace KeyEventAccessor {
    void DestroyPeerImpl(Ark_KeyEvent peer)
    {
        auto peerImpl = reinterpret_cast<KeyEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_KeyEvent CtorImpl()
    {
        return new KeyEventPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Boolean GetModifierKeyStateImpl(Ark_VMContext vmContext,
                                        Ark_KeyEvent peer,
                                        const Array_String* keys)
    {
        return {};
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
                              const Ark_IntentionCode* intentionCode)
    {
    }
    Ark_Number GetUnicodeImpl(Ark_KeyEvent peer)
    {
        return {};
    }
    void SetUnicodeImpl(Ark_KeyEvent peer,
                        const Ark_Number* unicode)
    {
    }
    } // KeyEventAccessor
    namespace ProgressMaskAccessor {
    void DestroyPeerImpl(Ark_ProgressMask peer)
    {
        auto peerImpl = reinterpret_cast<ProgressMaskPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ProgressMask CtorImpl(const Ark_Number* value,
                              const Ark_Number* total,
                              const Ark_ResourceColor* color)
    {
        return new ProgressMaskPeer(value, total, color);
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
    namespace MeasurableAccessor {
    void DestroyPeerImpl(Ark_Measurable peer)
    {
        auto peerImpl = reinterpret_cast<MeasurablePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Measurable CtorImpl()
    {
        return new MeasurablePeer();
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
    } // MeasurableAccessor
    namespace ViewAccessor {
    void DestroyPeerImpl(Ark_View peer)
    {
        auto peerImpl = reinterpret_cast<ViewPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_View CtorImpl()
    {
        return new ViewPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CustomObject CreateImpl(Ark_View peer,
                                const Ark_CustomObject* value)
    {
        return {};
    }
    } // ViewAccessor
    namespace TextContentControllerBaseAccessor {
    void DestroyPeerImpl(Ark_TextContentControllerBase peer)
    {
        auto peerImpl = reinterpret_cast<TextContentControllerBasePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextContentControllerBase CtorImpl()
    {
        return new TextContentControllerBasePeer();
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
    } // TextContentControllerBaseAccessor
    namespace ChildrenMainSizeAccessor {
    void DestroyPeerImpl(Ark_ChildrenMainSize peer)
    {
        auto peerImpl = reinterpret_cast<ChildrenMainSizePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ChildrenMainSize CtorImpl(const Ark_Number* childDefaultSize)
    {
        return new ChildrenMainSizePeer(childDefaultSize);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SpliceImpl(Ark_VMContext vmContext,
                    Ark_ChildrenMainSize peer,
                    const Ark_Number* start,
                    const Opt_Number* deleteCount,
                    const Opt_Array_Number* childrenSize)
    {
    }
    void UpdateImpl(Ark_VMContext vmContext,
                    Ark_ChildrenMainSize peer,
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
    namespace UICommonEventAccessor {
    void DestroyPeerImpl(Ark_UICommonEvent peer)
    {
        auto peerImpl = reinterpret_cast<UICommonEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UICommonEvent CtorImpl()
    {
        return new UICommonEventPeer();
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
    namespace GestureModifierAccessor {
    void DestroyPeerImpl(Ark_GestureModifier peer)
    {
        auto peerImpl = reinterpret_cast<GestureModifierPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureModifier CtorImpl()
    {
        return new GestureModifierPeer();
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
    namespace ContextMenuAccessor {
    void CloseImpl()
    {
    }
    } // ContextMenuAccessor
    namespace CustomDialogControllerAccessor {
    void DestroyPeerImpl(Ark_CustomDialogController peer)
    {
        auto peerImpl = reinterpret_cast<CustomDialogControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CustomDialogController CtorImpl(const Ark_CustomDialogControllerOptions* value)
    {
        return new CustomDialogControllerPeer(value);
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
    namespace LinearGradientAccessor {
    void DestroyPeerImpl(Ark_LinearGradient peer)
    {
        auto peerImpl = reinterpret_cast<LinearGradientPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LinearGradient CtorImpl(const Array_ColorStop* colorStops)
    {
        return new LinearGradientPeer(colorStops);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // LinearGradientAccessor
    namespace DatePickerDialogAccessor {
    void ShowImpl(const Opt_DatePickerDialogOptions* options)
    {
    }
    } // DatePickerDialogAccessor
    namespace BaseGestureEventAccessor {
    void DestroyPeerImpl(Ark_BaseGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<BaseGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaseGestureEvent CtorImpl()
    {
        return new BaseGestureEventPeer();
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
    namespace TapGestureEventAccessor {
    void DestroyPeerImpl(Ark_TapGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<TapGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TapGestureEvent CtorImpl()
    {
        return new TapGestureEventPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // TapGestureEventAccessor
    namespace LongPressGestureEventAccessor {
    void DestroyPeerImpl(Ark_LongPressGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<LongPressGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LongPressGestureEvent CtorImpl()
    {
        return new LongPressGestureEventPeer();
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
    namespace PanGestureEventAccessor {
    void DestroyPeerImpl(Ark_PanGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureEvent CtorImpl()
    {
        return new PanGestureEventPeer();
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
    namespace PinchGestureEventAccessor {
    void DestroyPeerImpl(Ark_PinchGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<PinchGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PinchGestureEvent CtorImpl()
    {
        return new PinchGestureEventPeer();
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
    namespace RotationGestureEventAccessor {
    void DestroyPeerImpl(Ark_RotationGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<RotationGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RotationGestureEvent CtorImpl()
    {
        return new RotationGestureEventPeer();
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
    namespace SwipeGestureEventAccessor {
    void DestroyPeerImpl(Ark_SwipeGestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<SwipeGestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwipeGestureEvent CtorImpl()
    {
        return new SwipeGestureEventPeer();
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
    namespace GestureEventAccessor {
    void DestroyPeerImpl(Ark_GestureEvent peer)
    {
        auto peerImpl = reinterpret_cast<GestureEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureEvent CtorImpl()
    {
        return new GestureEventPeer();
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
    namespace TapGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_TapGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<TapGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TapGestureInterface CtorImpl()
    {
        return new TapGestureInterfacePeer();
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
    namespace LongPressGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_LongPressGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<LongPressGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LongPressGestureInterface CtorImpl()
    {
        return new LongPressGestureInterfacePeer();
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
    Ark_LongPressGestureInterface OnActionCancelImpl(Ark_LongPressGestureInterface peer,
                                                     const Callback_Void* event)
    {
        return {};
    }
    } // LongPressGestureInterfaceAccessor
    namespace PanGestureOptionsAccessor {
    void DestroyPeerImpl(Ark_PanGestureOptions peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureOptionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureOptions CtorImpl(const Opt_Literal_Number_distance_fingers_PanDirection_direction* value)
    {
        return new PanGestureOptionsPeer(value);
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
    } // PanGestureOptionsAccessor
    namespace PanGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_PanGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<PanGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanGestureInterface CtorImpl()
    {
        return new PanGestureInterfacePeer();
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
    Ark_PanGestureInterface OnActionCancelImpl(Ark_PanGestureInterface peer,
                                               const Callback_Void* event)
    {
        return {};
    }
    } // PanGestureInterfaceAccessor
    namespace SwipeGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_SwipeGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<SwipeGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwipeGestureInterface CtorImpl()
    {
        return new SwipeGestureInterfacePeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_SwipeGestureInterface OnActionImpl(Ark_SwipeGestureInterface peer,
                                           const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    } // SwipeGestureInterfaceAccessor
    namespace PinchGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_PinchGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<PinchGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PinchGestureInterface CtorImpl()
    {
        return new PinchGestureInterfacePeer();
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
    Ark_PinchGestureInterface OnActionCancelImpl(Ark_PinchGestureInterface peer,
                                                 const Callback_Void* event)
    {
        return {};
    }
    } // PinchGestureInterfaceAccessor
    namespace RotationGestureInterfaceAccessor {
    void DestroyPeerImpl(Ark_RotationGestureInterface peer)
    {
        auto peerImpl = reinterpret_cast<RotationGestureInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RotationGestureInterface CtorImpl()
    {
        return new RotationGestureInterfacePeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_RotationGestureInterface OnActionStartImpl(Ark_RotationGestureInterface peer,
                                                   const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_RotationGestureInterface OnActionUpdateImpl(Ark_RotationGestureInterface peer,
                                                    const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_RotationGestureInterface OnActionEndImpl(Ark_RotationGestureInterface peer,
                                                 const Callback_GestureEvent_Void* event)
    {
        return {};
    }
    Ark_RotationGestureInterface OnActionCancelImpl(Ark_RotationGestureInterface peer,
                                                    const Callback_Void* event)
    {
        return {};
    }
    } // RotationGestureInterfaceAccessor
    namespace GestureGroupInterfaceAccessor {
    void DestroyPeerImpl(Ark_GestureGroupInterface peer)
    {
        auto peerImpl = reinterpret_cast<GestureGroupInterfacePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureGroupInterface CtorImpl()
    {
        return new GestureGroupInterfacePeer();
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
    namespace ScrollableTargetInfoAccessor {
    void DestroyPeerImpl(Ark_ScrollableTargetInfo peer)
    {
        auto peerImpl = reinterpret_cast<ScrollableTargetInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScrollableTargetInfo CtorImpl()
    {
        return new ScrollableTargetInfoPeer();
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
    namespace EventTargetInfoAccessor {
    void DestroyPeerImpl(Ark_EventTargetInfo peer)
    {
        auto peerImpl = reinterpret_cast<EventTargetInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EventTargetInfo CtorImpl()
    {
        return new EventTargetInfoPeer();
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
    namespace GestureRecognizerAccessor {
    void DestroyPeerImpl(Ark_GestureRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<GestureRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureRecognizer CtorImpl()
    {
        return new GestureRecognizerPeer();
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
    } // GestureRecognizerAccessor
    namespace PanRecognizerAccessor {
    void DestroyPeerImpl(Ark_PanRecognizer peer)
    {
        auto peerImpl = reinterpret_cast<PanRecognizerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PanRecognizer CtorImpl()
    {
        return new PanRecognizerPeer();
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
    namespace ImageAnalyzerControllerAccessor {
    void DestroyPeerImpl(Ark_ImageAnalyzerController peer)
    {
        auto peerImpl = reinterpret_cast<ImageAnalyzerControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageAnalyzerController CtorImpl()
    {
        return new ImageAnalyzerControllerPeer();
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
    namespace ListScrollerAccessor {
    void DestroyPeerImpl(Ark_ListScroller peer)
    {
        auto peerImpl = reinterpret_cast<ListScrollerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ListScroller CtorImpl()
    {
        return new ListScrollerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_RectResult GetItemRectInGroupImpl(Ark_VMContext vmContext,
                                          Ark_ListScroller peer,
                                          const Ark_Number* index,
                                          const Ark_Number* indexInGroup)
    {
        return {};
    }
    void ScrollToItemInGroupImpl(Ark_VMContext vmContext,
                                 Ark_ListScroller peer,
                                 const Ark_Number* index,
                                 const Ark_Number* indexInGroup,
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
                                                             const Ark_Number* x,
                                                             const Ark_Number* y)
    {
        return {};
    }
    } // ListScrollerAccessor
    namespace Matrix2DAccessor {
    void DestroyPeerImpl(Ark_Matrix2D peer)
    {
        auto peerImpl = reinterpret_cast<Matrix2DPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Matrix2D CtorImpl()
    {
        return new Matrix2DPeer();
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
    Ark_Matrix2D MultiplyImpl(Ark_Matrix2D peer,
                              const Opt_Matrix2D* other)
    {
        return {};
    }
    Ark_Matrix2D Rotate0Impl(Ark_Matrix2D peer,
                             const Opt_Number* rx,
                             const Opt_Number* ry)
    {
        return {};
    }
    Ark_Matrix2D Rotate1Impl(Ark_Matrix2D peer,
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
    Ark_Number GetScaleXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetScaleXImpl(Ark_Matrix2D peer,
                       const Ark_Number* scaleX)
    {
    }
    Ark_Number GetRotateYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetRotateYImpl(Ark_Matrix2D peer,
                        const Ark_Number* rotateY)
    {
    }
    Ark_Number GetRotateXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetRotateXImpl(Ark_Matrix2D peer,
                        const Ark_Number* rotateX)
    {
    }
    Ark_Number GetScaleYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetScaleYImpl(Ark_Matrix2D peer,
                       const Ark_Number* scaleY)
    {
    }
    Ark_Number GetTranslateXImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetTranslateXImpl(Ark_Matrix2D peer,
                           const Ark_Number* translateX)
    {
    }
    Ark_Number GetTranslateYImpl(Ark_Matrix2D peer)
    {
        return {};
    }
    void SetTranslateYImpl(Ark_Matrix2D peer,
                           const Ark_Number* translateY)
    {
    }
    } // Matrix2DAccessor
    namespace NavDestinationContextAccessor {
    void DestroyPeerImpl(Ark_NavDestinationContext peer)
    {
        auto peerImpl = reinterpret_cast<NavDestinationContextPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavDestinationContext CtorImpl()
    {
        return new NavDestinationContextPeer();
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
    Ark_String GetNavDestinationIdImpl(Ark_NavDestinationContext peer)
    {
        return {};
    }
    void SetNavDestinationIdImpl(Ark_NavDestinationContext peer,
                                 const Ark_String* navDestinationId)
    {
    }
    } // NavDestinationContextAccessor
    namespace NavPathInfoAccessor {
    void DestroyPeerImpl(Ark_NavPathInfo peer)
    {
        auto peerImpl = reinterpret_cast<NavPathInfoPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavPathInfo CtorImpl(const Ark_String* name,
                             const Ark_CustomObject* param,
                             const Opt_Callback_PopInfo_Void* onPop,
                             const Opt_Boolean* isEntry)
    {
        return new NavPathInfoPeer(name, param, onPop, isEntry);
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
    Ark_CustomObject GetParamImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetParamImpl(Ark_NavPathInfo peer,
                      const Ark_CustomObject* param)
    {
    }
    Callback_PopInfo_Void GetOnPopImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetOnPopImpl(Ark_NavPathInfo peer,
                      const Callback_PopInfo_Void* onPop)
    {
    }
    Ark_Boolean GetIsEntryImpl(Ark_NavPathInfo peer)
    {
        return {};
    }
    void SetIsEntryImpl(Ark_NavPathInfo peer,
                        Ark_Boolean isEntry)
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
    Ark_NavPathStack CtorImpl()
    {
        return new NavPathStackPeer();
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
                             const Ark_CustomObject* param,
                             const Opt_Boolean* animated)
    {
    }
    void PushPathByName1Impl(Ark_NavPathStack peer,
                             const Ark_String* name,
                             const Ark_CustomObject* param,
                             const Callback_PopInfo_Void* onPop,
                             const Opt_Boolean* animated)
    {
    }
    void PushDestinationByName0Impl(Ark_VMContext vmContext,
                                    Ark_AsyncWorkerPtr asyncWorker,
                                    Ark_NavPathStack peer,
                                    const Ark_String* name,
                                    const Ark_CustomObject* param,
                                    const Opt_Boolean* animated,
                                    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
    {
    }
    void PushDestinationByName1Impl(Ark_VMContext vmContext,
                                    Ark_AsyncWorkerPtr asyncWorker,
                                    Ark_NavPathStack peer,
                                    const Ark_String* name,
                                    const Ark_CustomObject* param,
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
                               const Ark_CustomObject* param,
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
                             const Ark_CustomObject* result,
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
                              const Ark_CustomObject* result,
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
                         const Ark_CustomObject* result,
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
    Opt_CustomObject GetParamByIndexImpl(Ark_NavPathStack peer,
                                         const Ark_Number* index)
    {
        return {};
    }
    Array_CustomObject GetParamByNameImpl(Ark_NavPathStack peer,
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
    } // NavPathStackAccessor
    namespace NavigationTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_NavigationTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<NavigationTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_NavigationTransitionProxy CtorImpl()
    {
        return new NavigationTransitionProxyPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void FinishTransitionImpl(Ark_NavigationTransitionProxy peer)
    {
    }
    void CancelTransitionImpl(Ark_NavigationTransitionProxy peer)
    {
    }
    void UpdateTransitionImpl(Ark_NavigationTransitionProxy peer,
                              const Ark_Number* progress)
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
    Ark_Boolean GetIsInteractiveImpl(Ark_NavigationTransitionProxy peer)
    {
        return {};
    }
    void SetIsInteractiveImpl(Ark_NavigationTransitionProxy peer,
                              Ark_Boolean isInteractive)
    {
    }
    } // NavigationTransitionProxyAccessor
    namespace PatternLockControllerAccessor {
    void DestroyPeerImpl(Ark_PatternLockController peer)
    {
        auto peerImpl = reinterpret_cast<PatternLockControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PatternLockController CtorImpl()
    {
        return new PatternLockControllerPeer();
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
    namespace RichEditorBaseControllerAccessor {
    void DestroyPeerImpl(Ark_RichEditorBaseController peer)
    {
        auto peerImpl = reinterpret_cast<RichEditorBaseControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RichEditorBaseController CtorImpl()
    {
        return new RichEditorBaseControllerPeer();
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
    } // RichEditorBaseControllerAccessor
    namespace RichEditorControllerAccessor {
    void DestroyPeerImpl(Ark_RichEditorController peer)
    {
        auto peerImpl = reinterpret_cast<RichEditorControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_RichEditorController CtorImpl()
    {
        return new RichEditorControllerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number AddTextSpanImpl(Ark_RichEditorController peer,
                               const Ark_String* value,
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
                             const Ark_Type_RichEditorController_updateSpanStyle_value* value)
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
    Array_RichEditorSpan FromStyledStringImpl(Ark_VMContext vmContext,
                                              Ark_RichEditorController peer,
                                              Ark_StyledString value)
    {
        return {};
    }
    Ark_StyledString ToStyledStringImpl(Ark_VMContext vmContext,
                                        Ark_RichEditorController peer,
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
    Ark_RichEditorStyledStringController CtorImpl()
    {
        return new RichEditorStyledStringControllerPeer();
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
    namespace ScrollerAccessor {
    void DestroyPeerImpl(Ark_Scroller peer)
    {
        auto peerImpl = reinterpret_cast<ScrollerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_Scroller CtorImpl()
    {
        return new ScrollerPeer();
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
    void FlingImpl(Ark_VMContext vmContext,
                   Ark_Scroller peer,
                   const Ark_Number* velocity)
    {
    }
    void ScrollPage0Impl(Ark_Scroller peer,
                         const Ark_ScrollPageOptions* value)
    {
    }
    void ScrollPage1Impl(Ark_Scroller peer,
                         const Ark_Literal_Boolean_next_Axis_direction* value)
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
    Ark_RectResult GetItemRectImpl(Ark_VMContext vmContext,
                                   Ark_Scroller peer,
                                   const Ark_Number* index)
    {
        return {};
    }
    Ark_Number GetItemIndexImpl(Ark_VMContext vmContext,
                                Ark_Scroller peer,
                                const Ark_Number* x,
                                const Ark_Number* y)
    {
        return {};
    }
    } // ScrollerAccessor
    namespace SearchControllerAccessor {
    void DestroyPeerImpl(Ark_SearchController peer)
    {
        auto peerImpl = reinterpret_cast<SearchControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SearchController CtorImpl()
    {
        return new SearchControllerPeer();
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
    namespace SwiperControllerAccessor {
    void DestroyPeerImpl(Ark_SwiperController peer)
    {
        auto peerImpl = reinterpret_cast<SwiperControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwiperController CtorImpl()
    {
        return new SwiperControllerPeer();
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
                         const Opt_Boolean* useAnimation)
    {
    }
    void FinishAnimationImpl(Ark_SwiperController peer,
                             const Opt_VoidCallback* callback_)
    {
    }
    } // SwiperControllerAccessor
    namespace SwiperContentTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_SwiperContentTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<SwiperContentTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SwiperContentTransitionProxy CtorImpl()
    {
        return new SwiperContentTransitionProxyPeer();
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
    namespace IndicatorComponentControllerAccessor {
    void DestroyPeerImpl(Ark_IndicatorComponentController peer)
    {
        auto peerImpl = reinterpret_cast<IndicatorComponentControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_IndicatorComponentController CtorImpl()
    {
        return new IndicatorComponentControllerPeer();
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
    namespace HierarchicalSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_HierarchicalSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<HierarchicalSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HierarchicalSymbolEffect CtorImpl(const Opt_EffectFillStyle* fillStyle)
    {
        return new HierarchicalSymbolEffectPeer(fillStyle);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectFillStyle GetFillStyleImpl(Ark_HierarchicalSymbolEffect peer)
    {
        return {};
    }
    void SetFillStyleImpl(Ark_HierarchicalSymbolEffect peer,
                          Ark_EffectFillStyle fillStyle)
    {
    }
    } // HierarchicalSymbolEffectAccessor
    namespace AppearSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_AppearSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<AppearSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_AppearSymbolEffect CtorImpl(const Opt_EffectScope* scope)
    {
        return new AppearSymbolEffectPeer(scope);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectScope GetScopeImpl(Ark_AppearSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_AppearSymbolEffect peer,
                      Ark_EffectScope scope)
    {
    }
    } // AppearSymbolEffectAccessor
    namespace DisappearSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_DisappearSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<DisappearSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DisappearSymbolEffect CtorImpl(const Opt_EffectScope* scope)
    {
        return new DisappearSymbolEffectPeer(scope);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectScope GetScopeImpl(Ark_DisappearSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_DisappearSymbolEffect peer,
                      Ark_EffectScope scope)
    {
    }
    } // DisappearSymbolEffectAccessor
    namespace BounceSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_BounceSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<BounceSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BounceSymbolEffect CtorImpl(const Opt_EffectScope* scope,
                                    const Opt_EffectDirection* direction)
    {
        return new BounceSymbolEffectPeer(scope, direction);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_EffectScope GetScopeImpl(Ark_BounceSymbolEffect peer)
    {
        return {};
    }
    void SetScopeImpl(Ark_BounceSymbolEffect peer,
                      Ark_EffectScope scope)
    {
    }
    Ark_EffectDirection GetDirectionImpl(Ark_BounceSymbolEffect peer)
    {
        return {};
    }
    void SetDirectionImpl(Ark_BounceSymbolEffect peer,
                          Ark_EffectDirection direction)
    {
    }
    } // BounceSymbolEffectAccessor
    namespace PulseSymbolEffectAccessor {
    void DestroyPeerImpl(Ark_PulseSymbolEffect peer)
    {
        auto peerImpl = reinterpret_cast<PulseSymbolEffectPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PulseSymbolEffect CtorImpl()
    {
        return new PulseSymbolEffectPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // PulseSymbolEffectAccessor
    namespace TabsControllerAccessor {
    void DestroyPeerImpl(Ark_TabsController peer)
    {
        auto peerImpl = reinterpret_cast<TabsControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TabsController CtorImpl()
    {
        return new TabsControllerPeer();
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
    namespace TabContentTransitionProxyAccessor {
    void DestroyPeerImpl(Ark_TabContentTransitionProxy peer)
    {
        auto peerImpl = reinterpret_cast<TabContentTransitionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TabContentTransitionProxy CtorImpl()
    {
        return new TabContentTransitionProxyPeer();
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
    namespace TextControllerAccessor {
    void DestroyPeerImpl(Ark_TextController peer)
    {
        auto peerImpl = reinterpret_cast<TextControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextController CtorImpl()
    {
        return new TextControllerPeer();
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
    namespace TextAreaControllerAccessor {
    void DestroyPeerImpl(Ark_TextAreaController peer)
    {
        auto peerImpl = reinterpret_cast<TextAreaControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextAreaController CtorImpl()
    {
        return new TextAreaControllerPeer();
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
    namespace TextClockControllerAccessor {
    void DestroyPeerImpl(Ark_TextClockController peer)
    {
        auto peerImpl = reinterpret_cast<TextClockControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextClockController CtorImpl()
    {
        return new TextClockControllerPeer();
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
    namespace TextBaseControllerAccessor {
    void DestroyPeerImpl(Ark_TextBaseController peer)
    {
        auto peerImpl = reinterpret_cast<TextBaseControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextBaseController CtorImpl()
    {
        return new TextBaseControllerPeer();
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
    namespace TextEditControllerExAccessor {
    void DestroyPeerImpl(Ark_TextEditControllerEx peer)
    {
        auto peerImpl = reinterpret_cast<TextEditControllerExPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextEditControllerEx CtorImpl()
    {
        return new TextEditControllerExPeer();
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
    namespace StyledStringControllerAccessor {
    void DestroyPeerImpl(Ark_StyledStringController peer)
    {
        auto peerImpl = reinterpret_cast<StyledStringControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_StyledStringController CtorImpl()
    {
        return new StyledStringControllerPeer();
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
    namespace LayoutManagerAccessor {
    void DestroyPeerImpl(Ark_LayoutManager peer)
    {
        auto peerImpl = reinterpret_cast<LayoutManagerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LayoutManager CtorImpl()
    {
        return new LayoutManagerPeer();
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
    Ark_LineMetrics GetLineMetricsImpl(Ark_LayoutManager peer,
                                       const Ark_Number* lineNumber)
    {
        return {};
    }
    Array_TextBox GetRectsForRangeImpl(Ark_LayoutManager peer,
                                       const Ark_TextRange* range,
                                       Ark_RectWidthStyle widthStyle,
                                       Ark_RectHeightStyle heightStyle)
    {
        return {};
    }
    } // LayoutManagerAccessor
    namespace TextMenuItemIdAccessor {
    void DestroyPeerImpl(Ark_TextMenuItemId peer)
    {
        auto peerImpl = reinterpret_cast<TextMenuItemIdPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextMenuItemId CtorImpl()
    {
        return new TextMenuItemIdPeer();
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
    } // TextMenuItemIdAccessor
    namespace EditMenuOptionsAccessor {
    void DestroyPeerImpl(Ark_EditMenuOptions peer)
    {
        auto peerImpl = reinterpret_cast<EditMenuOptionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EditMenuOptions CtorImpl()
    {
        return new EditMenuOptionsPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Array_TextMenuItem OnCreateMenuImpl(Ark_EditMenuOptions peer,
                                        const Array_TextMenuItem* menuItems)
    {
        return {};
    }
    Ark_Boolean OnMenuItemClickImpl(Ark_EditMenuOptions peer,
                                    const Ark_TextMenuItem* menuItem,
                                    const Ark_TextRange* range)
    {
        return {};
    }
    } // EditMenuOptionsAccessor
    namespace SubmitEventAccessor {
    void DestroyPeerImpl(Ark_SubmitEvent peer)
    {
        auto peerImpl = reinterpret_cast<SubmitEventPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SubmitEvent CtorImpl()
    {
        return new SubmitEventPeer();
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
    namespace TextInputControllerAccessor {
    void DestroyPeerImpl(Ark_TextInputController peer)
    {
        auto peerImpl = reinterpret_cast<TextInputControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextInputController CtorImpl()
    {
        return new TextInputControllerPeer();
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
    namespace TextPickerDialogAccessor {
    void ShowImpl(const Opt_TextPickerDialogOptions* options)
    {
    }
    } // TextPickerDialogAccessor
    namespace TextTimerControllerAccessor {
    void DestroyPeerImpl(Ark_TextTimerController peer)
    {
        auto peerImpl = reinterpret_cast<TextTimerControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextTimerController CtorImpl()
    {
        return new TextTimerControllerPeer();
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
    namespace TimePickerDialogAccessor {
    void ShowImpl(const Opt_TimePickerDialogOptions* options)
    {
    }
    } // TimePickerDialogAccessor
    namespace ColorFilterAccessor {
    void DestroyPeerImpl(Ark_ColorFilter peer)
    {
        auto peerImpl = reinterpret_cast<ColorFilterPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ColorFilter CtorImpl(const Array_Number* value)
    {
        return new ColorFilterPeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // ColorFilterAccessor
    namespace VideoControllerAccessor {
    void DestroyPeerImpl(Ark_VideoController peer)
    {
        auto peerImpl = reinterpret_cast<VideoControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_VideoController CtorImpl()
    {
        return new VideoControllerPeer();
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
    namespace WebKeyboardControllerAccessor {
    void DestroyPeerImpl(Ark_WebKeyboardController peer)
    {
        auto peerImpl = reinterpret_cast<WebKeyboardControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebKeyboardController CtorImpl()
    {
        return new WebKeyboardControllerPeer();
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
                           const Ark_Number* length)
    {
    }
    void DeleteBackwardImpl(Ark_WebKeyboardController peer,
                            const Ark_Number* length)
    {
    }
    void SendFunctionKeyImpl(Ark_WebKeyboardController peer,
                             const Ark_Number* key)
    {
    }
    void CloseImpl(Ark_WebKeyboardController peer)
    {
    }
    } // WebKeyboardControllerAccessor
    namespace FullScreenExitHandlerAccessor {
    void DestroyPeerImpl(Ark_FullScreenExitHandler peer)
    {
        auto peerImpl = reinterpret_cast<FullScreenExitHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FullScreenExitHandler CtorImpl()
    {
        return new FullScreenExitHandlerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ExitFullScreenImpl(Ark_FullScreenExitHandler peer)
    {
    }
    } // FullScreenExitHandlerAccessor
    namespace FileSelectorParamAccessor {
    void DestroyPeerImpl(Ark_FileSelectorParam peer)
    {
        auto peerImpl = reinterpret_cast<FileSelectorParamPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FileSelectorParam CtorImpl()
    {
        return new FileSelectorParamPeer();
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
    } // FileSelectorParamAccessor
    namespace JsResultAccessor {
    void DestroyPeerImpl(Ark_JsResult peer)
    {
        auto peerImpl = reinterpret_cast<JsResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_JsResult CtorImpl()
    {
        return new JsResultPeer();
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
    namespace FileSelectorResultAccessor {
    void DestroyPeerImpl(Ark_FileSelectorResult peer)
    {
        auto peerImpl = reinterpret_cast<FileSelectorResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_FileSelectorResult CtorImpl()
    {
        return new FileSelectorResultPeer();
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
    namespace HttpAuthHandlerAccessor {
    void DestroyPeerImpl(Ark_HttpAuthHandler peer)
    {
        auto peerImpl = reinterpret_cast<HttpAuthHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_HttpAuthHandler CtorImpl()
    {
        return new HttpAuthHandlerPeer();
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
    namespace SslErrorHandlerAccessor {
    void DestroyPeerImpl(Ark_SslErrorHandler peer)
    {
        auto peerImpl = reinterpret_cast<SslErrorHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_SslErrorHandler CtorImpl()
    {
        return new SslErrorHandlerPeer();
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
    namespace ClientAuthenticationHandlerAccessor {
    void DestroyPeerImpl(Ark_ClientAuthenticationHandler peer)
    {
        auto peerImpl = reinterpret_cast<ClientAuthenticationHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ClientAuthenticationHandler CtorImpl()
    {
        return new ClientAuthenticationHandlerPeer();
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
    namespace PermissionRequestAccessor {
    void DestroyPeerImpl(Ark_PermissionRequest peer)
    {
        auto peerImpl = reinterpret_cast<PermissionRequestPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_PermissionRequest CtorImpl()
    {
        return new PermissionRequestPeer();
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
    namespace ScreenCaptureHandlerAccessor {
    void DestroyPeerImpl(Ark_ScreenCaptureHandler peer)
    {
        auto peerImpl = reinterpret_cast<ScreenCaptureHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ScreenCaptureHandler CtorImpl()
    {
        return new ScreenCaptureHandlerPeer();
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
    namespace DataResubmissionHandlerAccessor {
    void DestroyPeerImpl(Ark_DataResubmissionHandler peer)
    {
        auto peerImpl = reinterpret_cast<DataResubmissionHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DataResubmissionHandler CtorImpl()
    {
        return new DataResubmissionHandlerPeer();
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
    namespace ControllerHandlerAccessor {
    void DestroyPeerImpl(Ark_ControllerHandler peer)
    {
        auto peerImpl = reinterpret_cast<ControllerHandlerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ControllerHandler CtorImpl()
    {
        return new ControllerHandlerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetWebControllerImpl(Ark_ControllerHandler peer,
                              Ark_WebviewController controller)
    {
    }
    } // ControllerHandlerAccessor
    namespace WebContextMenuParamAccessor {
    void DestroyPeerImpl(Ark_WebContextMenuParam peer)
    {
        auto peerImpl = reinterpret_cast<WebContextMenuParamPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebContextMenuParam CtorImpl()
    {
        return new WebContextMenuParamPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_Number XImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Number YImpl(Ark_WebContextMenuParam peer)
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
    Ark_Number GetEditStateFlagsImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Number GetPreviewWidthImpl(Ark_WebContextMenuParam peer)
    {
        return {};
    }
    Ark_Number GetPreviewHeightImpl(Ark_WebContextMenuParam peer)
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
    Ark_WebContextMenuResult CtorImpl()
    {
        return new WebContextMenuResultPeer();
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
    namespace ConsoleMessageAccessor {
    void DestroyPeerImpl(Ark_ConsoleMessage peer)
    {
        auto peerImpl = reinterpret_cast<ConsoleMessagePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ConsoleMessage CtorImpl(const Ark_String* message,
                                const Ark_String* sourceId,
                                const Ark_Number* lineNumber,
                                Ark_MessageLevel messageLevel)
    {
        return new ConsoleMessagePeer(message, sourceId, lineNumber, messageLevel);
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
    namespace WebResourceRequestAccessor {
    void DestroyPeerImpl(Ark_WebResourceRequest peer)
    {
        auto peerImpl = reinterpret_cast<WebResourceRequestPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebResourceRequest CtorImpl()
    {
        return new WebResourceRequestPeer();
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
    Ark_WebResourceResponse CtorImpl()
    {
        return new WebResourceResponsePeer();
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
    namespace WebResourceErrorAccessor {
    void DestroyPeerImpl(Ark_WebResourceError peer)
    {
        auto peerImpl = reinterpret_cast<WebResourceErrorPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebResourceError CtorImpl()
    {
        return new WebResourceErrorPeer();
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
    namespace JsGeolocationAccessor {
    void DestroyPeerImpl(Ark_JsGeolocation peer)
    {
        auto peerImpl = reinterpret_cast<JsGeolocationPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_JsGeolocation CtorImpl()
    {
        return new JsGeolocationPeer();
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
    namespace WebCookieAccessor {
    void DestroyPeerImpl(Ark_WebCookie peer)
    {
        auto peerImpl = reinterpret_cast<WebCookiePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebCookie CtorImpl()
    {
        return new WebCookiePeer();
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
    namespace EventResultAccessor {
    void DestroyPeerImpl(Ark_EventResult peer)
    {
        auto peerImpl = reinterpret_cast<EventResultPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_EventResult CtorImpl()
    {
        return new EventResultPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SetGestureEventResultImpl(Ark_EventResult peer,
                                   Ark_Boolean result)
    {
    }
    } // EventResultAccessor
    namespace WebControllerAccessor {
    void DestroyPeerImpl(Ark_WebController peer)
    {
        auto peerImpl = reinterpret_cast<WebControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WebController CtorImpl()
    {
        return new WebControllerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void OnInactiveImpl(Ark_WebController peer)
    {
    }
    void OnActiveImpl(Ark_WebController peer)
    {
    }
    void ZoomImpl(Ark_WebController peer,
                  const Ark_Number* factor)
    {
    }
    void ClearHistoryImpl(Ark_WebController peer)
    {
    }
    void RunJavaScriptImpl(Ark_WebController peer,
                           const Ark_Literal_String_script_Callback_String_Void_callback_* options)
    {
    }
    void LoadDataImpl(Ark_WebController peer,
                      const Ark_Literal_String_baseUrl_data_encoding_historyUrl_mimeType* options)
    {
    }
    void LoadUrlImpl(Ark_WebController peer,
                     const Ark_Literal_Union_String_Resource_url_Array_Header_headers* options)
    {
    }
    void RefreshImpl(Ark_WebController peer)
    {
    }
    void StopImpl(Ark_WebController peer)
    {
    }
    void RegisterJavaScriptProxyImpl(Ark_WebController peer,
                                     const Ark_Literal_Object_object__String_name_Array_String_methodList* options)
    {
    }
    void DeleteJavaScriptRegisterImpl(Ark_WebController peer,
                                      const Ark_String* name)
    {
    }
    Ark_HitTestType GetHitTestImpl(Ark_WebController peer)
    {
        return {};
    }
    void RequestFocusImpl(Ark_WebController peer)
    {
    }
    Ark_Boolean AccessBackwardImpl(Ark_WebController peer)
    {
        return {};
    }
    Ark_Boolean AccessForwardImpl(Ark_WebController peer)
    {
        return {};
    }
    Ark_Boolean AccessStepImpl(Ark_WebController peer,
                               const Ark_Number* step)
    {
        return {};
    }
    void BackwardImpl(Ark_WebController peer)
    {
    }
    void ForwardImpl(Ark_WebController peer)
    {
    }
    Ark_WebCookie GetCookieManagerImpl(Ark_WebController peer)
    {
        return {};
    }
    } // WebControllerAccessor
    namespace XComponentControllerAccessor {
    void DestroyPeerImpl(Ark_XComponentController peer)
    {
        auto peerImpl = reinterpret_cast<XComponentControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_XComponentController CtorImpl()
    {
        return new XComponentControllerPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetXComponentSurfaceIdImpl(Ark_XComponentController peer)
    {
        return {};
    }
    Ark_CustomObject GetXComponentContextImpl(Ark_XComponentController peer)
    {
        return {};
    }
    void SetXComponentSurfaceSizeImpl(Ark_XComponentController peer,
                                      const Ark_Literal_Number_surfaceHeight_surfaceWidth* value)
    {
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
    void OnSurfaceCreatedImpl(Ark_XComponentController peer,
                              const Ark_String* surfaceId)
    {
    }
    void OnSurfaceChangedImpl(Ark_XComponentController peer,
                              const Ark_String* surfaceId,
                              const Ark_SurfaceRect* rect)
    {
    }
    void OnSurfaceDestroyedImpl(Ark_XComponentController peer,
                                const Ark_String* surfaceId)
    {
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
    } // XComponentControllerAccessor
    namespace WaterFlowSectionsAccessor {
    void DestroyPeerImpl(Ark_WaterFlowSections peer)
    {
        auto peerImpl = reinterpret_cast<WaterFlowSectionsPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_WaterFlowSections CtorImpl()
    {
        return new WaterFlowSectionsPeer();
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
    namespace UIExtensionProxyAccessor {
    void DestroyPeerImpl(Ark_UIExtensionProxy peer)
    {
        auto peerImpl = reinterpret_cast<UIExtensionProxyPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UIExtensionProxy CtorImpl()
    {
        return new UIExtensionProxyPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void SendImpl(Ark_UIExtensionProxy peer,
                  const Map_String_CustomObject* data)
    {
    }
    Map_String_CustomObject SendSyncImpl(Ark_VMContext vmContext,
                                         Ark_UIExtensionProxy peer,
                                         const Map_String_CustomObject* data)
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
    namespace StyledStringAccessor {
    void DestroyPeerImpl(Ark_StyledString peer)
    {
        auto peerImpl = reinterpret_cast<StyledStringPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_StyledString CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                              const Opt_Array_StyleOptions* styles)
    {
        return new StyledStringPeer(value, styles);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_String GetStringImpl(Ark_StyledString peer)
    {
        return {};
    }
    Array_SpanStyle GetStylesImpl(Ark_VMContext vmContext,
                                  Ark_StyledString peer,
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
    Ark_StyledString SubStyledStringImpl(Ark_VMContext vmContext,
                                         Ark_StyledString peer,
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
    Ark_String ToHtmlImpl(Ark_VMContext vmContext,
                          Ark_StyledString styledString)
    {
        return {};
    }
    Ark_Buffer MarshallingImpl(Ark_StyledString styledString)
    {
        return {};
    }
    void UnmarshallingImpl(Ark_VMContext vmContext,
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
    namespace TextStyle_styled_stringAccessor {
    void DestroyPeerImpl(Ark_TextStyle_styled_string peer)
    {
        auto peerImpl = reinterpret_cast<TextStyle_styled_stringPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextStyle_styled_string CtorImpl(const Opt_TextStyleInterface* value)
    {
        return new TextStyle_styled_stringPeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_ResourceColor GetFontColorImpl(Ark_TextStyle_styled_string peer)
    {
        return {};
    }
    Ark_String GetFontFamilyImpl(Ark_TextStyle_styled_string peer)
    {
        return {};
    }
    Ark_Number GetFontSizeImpl(Ark_TextStyle_styled_string peer)
    {
        return {};
    }
    Ark_Number GetFontWeightImpl(Ark_TextStyle_styled_string peer)
    {
        return {};
    }
    Ark_FontStyle GetFontStyleImpl(Ark_TextStyle_styled_string peer)
    {
        return {};
    }
    } // TextStyle_styled_stringAccessor
    namespace DecorationStyleAccessor {
    void DestroyPeerImpl(Ark_DecorationStyle peer)
    {
        auto peerImpl = reinterpret_cast<DecorationStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_DecorationStyle CtorImpl(const Ark_DecorationStyleInterface* value)
    {
        return new DecorationStylePeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TextDecorationType GetTypeImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    Ark_ResourceColor GetColorImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    Ark_TextDecorationStyle GetStyleImpl(Ark_DecorationStyle peer)
    {
        return {};
    }
    } // DecorationStyleAccessor
    namespace BaselineOffsetStyleAccessor {
    void DestroyPeerImpl(Ark_BaselineOffsetStyle peer)
    {
        auto peerImpl = reinterpret_cast<BaselineOffsetStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BaselineOffsetStyle CtorImpl(Ark_LengthMetrics value)
    {
        return new BaselineOffsetStylePeer(value);
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
    namespace LetterSpacingStyleAccessor {
    void DestroyPeerImpl(Ark_LetterSpacingStyle peer)
    {
        auto peerImpl = reinterpret_cast<LetterSpacingStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LetterSpacingStyle CtorImpl(Ark_LengthMetrics value)
    {
        return new LetterSpacingStylePeer(value);
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
    namespace TextShadowStyleAccessor {
    void DestroyPeerImpl(Ark_TextShadowStyle peer)
    {
        auto peerImpl = reinterpret_cast<TextShadowStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_TextShadowStyle CtorImpl(const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
    {
        return new TextShadowStylePeer(value);
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
    namespace BackgroundColorStyleAccessor {
    void DestroyPeerImpl(Ark_BackgroundColorStyle peer)
    {
        auto peerImpl = reinterpret_cast<BackgroundColorStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_BackgroundColorStyle CtorImpl(const Ark_TextBackgroundStyle* textBackgroundStyle)
    {
        return new BackgroundColorStylePeer(textBackgroundStyle);
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
    namespace GestureStyleAccessor {
    void DestroyPeerImpl(Ark_GestureStyle peer)
    {
        auto peerImpl = reinterpret_cast<GestureStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_GestureStyle CtorImpl(const Opt_GestureStyleInterface* value)
    {
        return new GestureStylePeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    } // GestureStyleAccessor
    namespace ParagraphStyleAccessor {
    void DestroyPeerImpl(Ark_ParagraphStyle peer)
    {
        auto peerImpl = reinterpret_cast<ParagraphStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ParagraphStyle CtorImpl(const Opt_ParagraphStyleInterface* value)
    {
        return new ParagraphStylePeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Ark_Number GetTextIndentImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Ark_Number GetMaxLinesImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Ark_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Ark_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    Ark_Union_Number_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
    {
        return {};
    }
    } // ParagraphStyleAccessor
    namespace LineHeightStyleAccessor {
    void DestroyPeerImpl(Ark_LineHeightStyle peer)
    {
        auto peerImpl = reinterpret_cast<LineHeightStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LineHeightStyle CtorImpl(Ark_LengthMetrics lineHeight)
    {
        return new LineHeightStylePeer(lineHeight);
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
    namespace UrlStyleAccessor {
    void DestroyPeerImpl(Ark_UrlStyle peer)
    {
        auto peerImpl = reinterpret_cast<UrlStylePeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_UrlStyle CtorImpl(const Ark_String* url)
    {
        return new UrlStylePeer(url);
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
    namespace MutableStyledStringAccessor {
    void DestroyPeerImpl(Ark_MutableStyledString peer)
    {
        auto peerImpl = reinterpret_cast<MutableStyledStringPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_MutableStyledString CtorImpl(const Ark_Union_String_ImageAttachment_CustomSpan* value,
                                     const Opt_Array_StyleOptions* styles)
    {
        return new MutableStyledStringPeer(value, styles);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    void ReplaceStringImpl(Ark_VMContext vmContext,
                           Ark_MutableStyledString peer,
                           const Ark_Number* start,
                           const Ark_Number* length,
                           const Ark_String* other)
    {
    }
    void InsertStringImpl(Ark_VMContext vmContext,
                          Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_String* other)
    {
    }
    void RemoveStringImpl(Ark_VMContext vmContext,
                          Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_Number* length)
    {
    }
    void ReplaceStyleImpl(Ark_VMContext vmContext,
                          Ark_MutableStyledString peer,
                          const Ark_SpanStyle* spanStyle)
    {
    }
    void SetStyleImpl(Ark_VMContext vmContext,
                      Ark_MutableStyledString peer,
                      const Ark_SpanStyle* spanStyle)
    {
    }
    void RemoveStyleImpl(Ark_VMContext vmContext,
                         Ark_MutableStyledString peer,
                         const Ark_Number* start,
                         const Ark_Number* length,
                         Ark_StyledStringKey styledKey)
    {
    }
    void RemoveStylesImpl(Ark_VMContext vmContext,
                          Ark_MutableStyledString peer,
                          const Ark_Number* start,
                          const Ark_Number* length)
    {
    }
    void ClearStylesImpl(Ark_MutableStyledString peer)
    {
    }
    void ReplaceStyledStringImpl(Ark_VMContext vmContext,
                                 Ark_MutableStyledString peer,
                                 const Ark_Number* start,
                                 const Ark_Number* length,
                                 Ark_StyledString other)
    {
    }
    void InsertStyledStringImpl(Ark_VMContext vmContext,
                                Ark_MutableStyledString peer,
                                const Ark_Number* start,
                                Ark_StyledString other)
    {
    }
    void AppendStyledStringImpl(Ark_MutableStyledString peer,
                                Ark_StyledString other)
    {
    }
    } // MutableStyledStringAccessor
    namespace ImageAttachmentAccessor {
    void DestroyPeerImpl(Ark_ImageAttachment peer)
    {
        auto peerImpl = reinterpret_cast<ImageAttachmentPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_ImageAttachment CtorImpl(const Ark_ImageAttachmentInterface* value)
    {
        return new ImageAttachmentPeer(value);
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_PixelMap GetValueImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Ark_SizeOptions GetSizeImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Ark_ImageSpanAlignment GetVerticalAlignImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Ark_ImageFit GetObjectFitImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    Ark_ImageAttachmentLayoutStyle GetLayoutStyleImpl(Ark_ImageAttachment peer)
    {
        return {};
    }
    } // ImageAttachmentAccessor
    namespace CustomSpanAccessor {
    void DestroyPeerImpl(Ark_CustomSpan peer)
    {
        auto peerImpl = reinterpret_cast<CustomSpanPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_CustomSpan CtorImpl()
    {
        return new CustomSpanPeer();
    }
    Ark_NativePointer GetFinalizerImpl()
    {
        return reinterpret_cast<void *>(&DestroyPeerImpl);
    }
    Ark_CustomSpanMetrics OnMeasureImpl(Ark_CustomSpan peer,
                                        const Ark_CustomSpanMeasureInfo* measureInfo)
    {
        return {};
    }
    void OnDrawImpl(Ark_CustomSpan peer,
                    const Ark_DrawContext* context,
                    const Ark_CustomSpanDrawInfo* drawInfo)
    {
    }
    void InvalidateImpl(Ark_CustomSpan peer)
    {
    }
    } // CustomSpanAccessor
    namespace LinearIndicatorControllerAccessor {
    void DestroyPeerImpl(Ark_LinearIndicatorController peer)
    {
        auto peerImpl = reinterpret_cast<LinearIndicatorControllerPeerImpl *>(peer);
        if (peerImpl) {
            delete peerImpl;
        }
    }
    Ark_LinearIndicatorController CtorImpl()
    {
        return new LinearIndicatorControllerPeer();
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
    namespace GlobalScopeAccessor {
    Ark_Context GetContextImpl(const Opt_CustomObject* component)
    {
        return {};
    }
    void PostCardActionImpl(const Ark_CustomObject* component,
                            const Ark_CustomObject* action)
    {
    }
    Ark_Resource Dollar_rImpl(const Ark_String* value,
                              const Array_CustomObject* params)
    {
        return {};
    }
    Ark_Resource Dollar_rawfileImpl(const Ark_String* value)
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
    Ark_Number Vp2pxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2vpImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Fp2pxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2fpImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Lpx2pxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_Number Px2lpxImpl(const Ark_Number* value)
    {
        return {};
    }
    Ark_CustomObject GetInspectorNodesImpl()
    {
        return {};
    }
    Ark_CustomObject GetInspectorNodeByIdImpl(const Ark_Number* id)
    {
        return {};
    }
    void SetAppBgColorImpl(const Ark_String* value)
    {
    }
    void Profiler_registerVsyncCallbackImpl(const Profiler_Callback_String_Void* callback_)
    {
    }
    void Profiler_unregisterVsyncCallbackImpl()
    {
    }
    void CursorControl_setCursorImpl(Ark_PointerStyle value)
    {
    }
    void CursorControl_restoreDefaultImpl()
    {
    }
    Ark_Boolean FocusControl_requestFocusImpl(const Ark_String* value)
    {
        return {};
    }
    } // GlobalScopeAccessor
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

    const GENERATED_ArkUIUnifiedDataAccessor* GetUnifiedDataAccessor()
    {
        static const GENERATED_ArkUIUnifiedDataAccessor UnifiedDataAccessorImpl {
            UnifiedDataAccessor::DestroyPeerImpl,
            UnifiedDataAccessor::CtorImpl,
            UnifiedDataAccessor::GetFinalizerImpl,
            UnifiedDataAccessor::HasTypeImpl,
            UnifiedDataAccessor::GetTypesImpl,
        };
        return &UnifiedDataAccessorImpl;
    }

    struct UnifiedDataPeer {
        virtual ~UnifiedDataPeer() = default;
    };
    const GENERATED_ArkUILazyForEachOpsAccessor* GetLazyForEachOpsAccessor()
    {
        static const GENERATED_ArkUILazyForEachOpsAccessor LazyForEachOpsAccessorImpl {
            LazyForEachOpsAccessor::NeedMoreElementsImpl,
            LazyForEachOpsAccessor::OnRangeUpdateImpl,
            LazyForEachOpsAccessor::SetCurrentIndexImpl,
            LazyForEachOpsAccessor::PrepareImpl,
            LazyForEachOpsAccessor::NotifyChangeImpl,
        };
        return &LazyForEachOpsAccessorImpl;
    }

    const GENERATED_ArkUISystemOpsAccessor* GetSystemOpsAccessor()
    {
        static const GENERATED_ArkUISystemOpsAccessor SystemOpsAccessorImpl {
            SystemOpsAccessor::StartFrameImpl,
            SystemOpsAccessor::EndFrameImpl,
            SystemOpsAccessor::SyncInstanceIdImpl,
            SystemOpsAccessor::RestoreInstanceIdImpl,
            SystemOpsAccessor::GetResourceIdImpl,
        };
        return &SystemOpsAccessorImpl;
    }

    const GENERATED_ArkUIFocusControllerAccessor* GetFocusControllerAccessor()
    {
        static const GENERATED_ArkUIFocusControllerAccessor FocusControllerAccessorImpl {
            FocusControllerAccessor::RequestFocusImpl,
        };
        return &FocusControllerAccessorImpl;
    }

    const GENERATED_ArkUIDrawableDescriptorAccessor* GetDrawableDescriptorAccessor()
    {
        static const GENERATED_ArkUIDrawableDescriptorAccessor DrawableDescriptorAccessorImpl {
            DrawableDescriptorAccessor::DestroyPeerImpl,
            DrawableDescriptorAccessor::CtorImpl,
            DrawableDescriptorAccessor::GetFinalizerImpl,
            DrawableDescriptorAccessor::GetPixelMapImpl,
        };
        return &DrawableDescriptorAccessorImpl;
    }

    struct DrawableDescriptorPeer {
        virtual ~DrawableDescriptorPeer() = default;
    };
    const GENERATED_ArkUILayeredDrawableDescriptorAccessor* GetLayeredDrawableDescriptorAccessor()
    {
        static const GENERATED_ArkUILayeredDrawableDescriptorAccessor LayeredDrawableDescriptorAccessorImpl {
            LayeredDrawableDescriptorAccessor::DestroyPeerImpl,
            LayeredDrawableDescriptorAccessor::CtorImpl,
            LayeredDrawableDescriptorAccessor::GetFinalizerImpl,
            LayeredDrawableDescriptorAccessor::GetForegroundImpl,
            LayeredDrawableDescriptorAccessor::GetBackgroundImpl,
            LayeredDrawableDescriptorAccessor::GetMaskImpl,
            LayeredDrawableDescriptorAccessor::GetMaskClipPathImpl,
        };
        return &LayeredDrawableDescriptorAccessorImpl;
    }

    struct LayeredDrawableDescriptorPeer {
        virtual ~LayeredDrawableDescriptorPeer() = default;
    };
    const GENERATED_ArkUIPixelMapDrawableDescriptorAccessor* GetPixelMapDrawableDescriptorAccessor()
    {
        static const GENERATED_ArkUIPixelMapDrawableDescriptorAccessor PixelMapDrawableDescriptorAccessorImpl {
            PixelMapDrawableDescriptorAccessor::DestroyPeerImpl,
            PixelMapDrawableDescriptorAccessor::CtorImpl,
            PixelMapDrawableDescriptorAccessor::GetFinalizerImpl,
        };
        return &PixelMapDrawableDescriptorAccessorImpl;
    }

    struct PixelMapDrawableDescriptorPeer {
        virtual ~PixelMapDrawableDescriptorPeer() = default;
    };
    const GENERATED_ArkUIAnimatedDrawableDescriptorAccessor* GetAnimatedDrawableDescriptorAccessor()
    {
        static const GENERATED_ArkUIAnimatedDrawableDescriptorAccessor AnimatedDrawableDescriptorAccessorImpl {
            AnimatedDrawableDescriptorAccessor::DestroyPeerImpl,
            AnimatedDrawableDescriptorAccessor::CtorImpl,
            AnimatedDrawableDescriptorAccessor::GetFinalizerImpl,
        };
        return &AnimatedDrawableDescriptorAccessorImpl;
    }

    struct AnimatedDrawableDescriptorPeer {
        virtual ~AnimatedDrawableDescriptorPeer() = default;
    };
    const GENERATED_ArkUIDrawingCanvasAccessor* GetDrawingCanvasAccessor()
    {
        static const GENERATED_ArkUIDrawingCanvasAccessor DrawingCanvasAccessorImpl {
            DrawingCanvasAccessor::DestroyPeerImpl,
            DrawingCanvasAccessor::CtorImpl,
            DrawingCanvasAccessor::GetFinalizerImpl,
            DrawingCanvasAccessor::DrawRectImpl,
        };
        return &DrawingCanvasAccessorImpl;
    }

    struct DrawingCanvasPeer {
        virtual ~DrawingCanvasPeer() = default;
    };
    const GENERATED_ArkUILengthMetricsAccessor* GetLengthMetricsAccessor()
    {
        static const GENERATED_ArkUILengthMetricsAccessor LengthMetricsAccessorImpl {
            LengthMetricsAccessor::DestroyPeerImpl,
            LengthMetricsAccessor::CtorImpl,
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
    const GENERATED_ArkUIColorMetricsAccessor* GetColorMetricsAccessor()
    {
        static const GENERATED_ArkUIColorMetricsAccessor ColorMetricsAccessorImpl {
            ColorMetricsAccessor::DestroyPeerImpl,
            ColorMetricsAccessor::CtorImpl,
            ColorMetricsAccessor::GetFinalizerImpl,
            ColorMetricsAccessor::NumericImpl,
            ColorMetricsAccessor::RgbaImpl,
            ColorMetricsAccessor::ResourceColorImpl,
            ColorMetricsAccessor::BlendColorImpl,
            ColorMetricsAccessor::GetColorImpl,
            ColorMetricsAccessor::GetRedImpl,
            ColorMetricsAccessor::GetGreenImpl,
            ColorMetricsAccessor::GetBlueImpl,
            ColorMetricsAccessor::GetAlphaImpl,
        };
        return &ColorMetricsAccessorImpl;
    }

    struct ColorMetricsPeer {
        virtual ~ColorMetricsPeer() = default;
    };
    const GENERATED_ArkUIWebviewControllerAccessor* GetWebviewControllerAccessor()
    {
        static const GENERATED_ArkUIWebviewControllerAccessor WebviewControllerAccessorImpl {
            WebviewControllerAccessor::DestroyPeerImpl,
            WebviewControllerAccessor::CtorImpl,
            WebviewControllerAccessor::GetFinalizerImpl,
            WebviewControllerAccessor::InitializeWebEngineImpl,
            WebviewControllerAccessor::LoadUrlImpl,
        };
        return &WebviewControllerAccessorImpl;
    }

    struct WebviewControllerPeer {
        virtual ~WebviewControllerPeer() = default;
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

    const GENERATED_ArkUICommonShapeAccessor* GetCommonShapeAccessor()
    {
        static const GENERATED_ArkUICommonShapeAccessor CommonShapeAccessorImpl {
            CommonShapeAccessor::DestroyPeerImpl,
            CommonShapeAccessor::CtorImpl,
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
    const GENERATED_ArkUIBaseShapeAccessor* GetBaseShapeAccessor()
    {
        static const GENERATED_ArkUIBaseShapeAccessor BaseShapeAccessorImpl {
            BaseShapeAccessor::DestroyPeerImpl,
            BaseShapeAccessor::CtorImpl,
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
    const GENERATED_ArkUIRectShapeAccessor* GetRectShapeAccessor()
    {
        static const GENERATED_ArkUIRectShapeAccessor RectShapeAccessorImpl {
            RectShapeAccessor::DestroyPeerImpl,
            RectShapeAccessor::CtorImpl,
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
    const GENERATED_ArkUICircleShapeAccessor* GetCircleShapeAccessor()
    {
        static const GENERATED_ArkUICircleShapeAccessor CircleShapeAccessorImpl {
            CircleShapeAccessor::DestroyPeerImpl,
            CircleShapeAccessor::CtorImpl,
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
    const GENERATED_ArkUIEllipseShapeAccessor* GetEllipseShapeAccessor()
    {
        static const GENERATED_ArkUIEllipseShapeAccessor EllipseShapeAccessorImpl {
            EllipseShapeAccessor::DestroyPeerImpl,
            EllipseShapeAccessor::CtorImpl,
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
    const GENERATED_ArkUIPathShapeAccessor* GetPathShapeAccessor()
    {
        static const GENERATED_ArkUIPathShapeAccessor PathShapeAccessorImpl {
            PathShapeAccessor::DestroyPeerImpl,
            PathShapeAccessor::CtorImpl,
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

    const GENERATED_ArkUISymbolEffectAccessor* GetSymbolEffectAccessor()
    {
        static const GENERATED_ArkUISymbolEffectAccessor SymbolEffectAccessorImpl {
            SymbolEffectAccessor::DestroyPeerImpl,
            SymbolEffectAccessor::CtorImpl,
            SymbolEffectAccessor::GetFinalizerImpl,
            SymbolEffectAccessor::DummyForAccessorGenerateImpl,
        };
        return &SymbolEffectAccessorImpl;
    }

    struct SymbolEffectPeer {
        virtual ~SymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIScaleSymbolEffectAccessor* GetScaleSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIScaleSymbolEffectAccessor ScaleSymbolEffectAccessorImpl {
            ScaleSymbolEffectAccessor::DestroyPeerImpl,
            ScaleSymbolEffectAccessor::CtorImpl,
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
    const GENERATED_ArkUIReplaceSymbolEffectAccessor* GetReplaceSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIReplaceSymbolEffectAccessor ReplaceSymbolEffectAccessorImpl {
            ReplaceSymbolEffectAccessor::DestroyPeerImpl,
            ReplaceSymbolEffectAccessor::CtorImpl,
            ReplaceSymbolEffectAccessor::GetFinalizerImpl,
            ReplaceSymbolEffectAccessor::GetScopeImpl,
            ReplaceSymbolEffectAccessor::SetScopeImpl,
        };
        return &ReplaceSymbolEffectAccessorImpl;
    }

    struct ReplaceSymbolEffectPeer {
        virtual ~ReplaceSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
    {
        static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
            FrameNodeAccessor::DestroyPeerImpl,
            FrameNodeAccessor::CtorImpl,
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
            FrameNodeAccessor::GetOpacityImpl,
            FrameNodeAccessor::GetPositionToWindowWithTransformImpl,
            FrameNodeAccessor::GetFrameNodeByKeyImpl,
        };
        return &FrameNodeAccessorImpl;
    }

    struct FrameNodePeer {
        virtual ~FrameNodePeer() = default;
    };
    const GENERATED_ArkUIPixelMapAccessor* GetPixelMapAccessor()
    {
        static const GENERATED_ArkUIPixelMapAccessor PixelMapAccessorImpl {
            PixelMapAccessor::DestroyPeerImpl,
            PixelMapAccessor::CtorImpl,
            PixelMapAccessor::GetFinalizerImpl,
            PixelMapAccessor::ReadPixelsToBufferSyncImpl,
            PixelMapAccessor::WriteBufferToPixelsImpl,
            PixelMapAccessor::GetIsEditableImpl,
            PixelMapAccessor::GetIsStrideAlignmentImpl,
        };
        return &PixelMapAccessorImpl;
    }

    struct PixelMapPeer {
        virtual ~PixelMapPeer() = default;
    };
    const GENERATED_ArkUINavExtenderAccessor* GetNavExtenderAccessor()
    {
        static const GENERATED_ArkUINavExtenderAccessor NavExtenderAccessorImpl {
            NavExtenderAccessor::SetUpdateStackCallbackImpl,
            NavExtenderAccessor::SyncStackImpl,
            NavExtenderAccessor::CheckNeedCreateImpl,
            NavExtenderAccessor::NavigationCreateImpl,
            NavExtenderAccessor::SetNavigationOptionsImpl,
            NavExtenderAccessor::SetNavDestinationNodeImpl,
        };
        return &NavExtenderAccessorImpl;
    }

    const GENERATED_ArkUIEventEmulatorAccessor* GetEventEmulatorAccessor()
    {
        static const GENERATED_ArkUIEventEmulatorAccessor EventEmulatorAccessorImpl {
            EventEmulatorAccessor::EmitClickEventImpl,
            EventEmulatorAccessor::EmitTextInputEventImpl,
        };
        return &EventEmulatorAccessorImpl;
    }

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

    const GENERATED_ArkUISpringPropAccessor* GetSpringPropAccessor()
    {
        static const GENERATED_ArkUISpringPropAccessor SpringPropAccessorImpl {
            SpringPropAccessor::DestroyPeerImpl,
            SpringPropAccessor::CtorImpl,
            SpringPropAccessor::GetFinalizerImpl,
        };
        return &SpringPropAccessorImpl;
    }

    struct SpringPropPeer {
        virtual ~SpringPropPeer() = default;
    };
    const GENERATED_ArkUISpringMotionAccessor* GetSpringMotionAccessor()
    {
        static const GENERATED_ArkUISpringMotionAccessor SpringMotionAccessorImpl {
            SpringMotionAccessor::DestroyPeerImpl,
            SpringMotionAccessor::CtorImpl,
            SpringMotionAccessor::GetFinalizerImpl,
        };
        return &SpringMotionAccessorImpl;
    }

    struct SpringMotionPeer {
        virtual ~SpringMotionPeer() = default;
    };
    const GENERATED_ArkUIFrictionMotionAccessor* GetFrictionMotionAccessor()
    {
        static const GENERATED_ArkUIFrictionMotionAccessor FrictionMotionAccessorImpl {
            FrictionMotionAccessor::DestroyPeerImpl,
            FrictionMotionAccessor::CtorImpl,
            FrictionMotionAccessor::GetFinalizerImpl,
        };
        return &FrictionMotionAccessorImpl;
    }

    struct FrictionMotionPeer {
        virtual ~FrictionMotionPeer() = default;
    };
    const GENERATED_ArkUIScrollMotionAccessor* GetScrollMotionAccessor()
    {
        static const GENERATED_ArkUIScrollMotionAccessor ScrollMotionAccessorImpl {
            ScrollMotionAccessor::DestroyPeerImpl,
            ScrollMotionAccessor::CtorImpl,
            ScrollMotionAccessor::GetFinalizerImpl,
        };
        return &ScrollMotionAccessorImpl;
    }

    struct ScrollMotionPeer {
        virtual ~ScrollMotionPeer() = default;
    };
    const GENERATED_ArkUICalendarControllerAccessor* GetCalendarControllerAccessor()
    {
        static const GENERATED_ArkUICalendarControllerAccessor CalendarControllerAccessorImpl {
            CalendarControllerAccessor::DestroyPeerImpl,
            CalendarControllerAccessor::CtorImpl,
            CalendarControllerAccessor::GetFinalizerImpl,
            CalendarControllerAccessor::BackToTodayImpl,
            CalendarControllerAccessor::GoToImpl,
        };
        return &CalendarControllerAccessorImpl;
    }

    struct CalendarControllerPeer {
        virtual ~CalendarControllerPeer() = default;
    };
    const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor()
    {
        static const GENERATED_ArkUICalendarPickerDialogAccessor CalendarPickerDialogAccessorImpl {
            CalendarPickerDialogAccessor::ShowImpl,
        };
        return &CalendarPickerDialogAccessorImpl;
    }

    const GENERATED_ArkUICanvasGradientAccessor* GetCanvasGradientAccessor()
    {
        static const GENERATED_ArkUICanvasGradientAccessor CanvasGradientAccessorImpl {
            CanvasGradientAccessor::DestroyPeerImpl,
            CanvasGradientAccessor::CtorImpl,
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
            CanvasPathAccessor::CtorImpl,
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
    const GENERATED_ArkUIPath2DAccessor* GetPath2DAccessor()
    {
        static const GENERATED_ArkUIPath2DAccessor Path2DAccessorImpl {
            Path2DAccessor::DestroyPeerImpl,
            Path2DAccessor::CtorImpl,
            Path2DAccessor::GetFinalizerImpl,
            Path2DAccessor::AddPathImpl,
        };
        return &Path2DAccessorImpl;
    }

    struct Path2DPeer {
        virtual ~Path2DPeer() = default;
    };
    const GENERATED_ArkUICanvasPatternAccessor* GetCanvasPatternAccessor()
    {
        static const GENERATED_ArkUICanvasPatternAccessor CanvasPatternAccessorImpl {
            CanvasPatternAccessor::DestroyPeerImpl,
            CanvasPatternAccessor::CtorImpl,
            CanvasPatternAccessor::GetFinalizerImpl,
            CanvasPatternAccessor::SetTransformImpl,
        };
        return &CanvasPatternAccessorImpl;
    }

    struct CanvasPatternPeer {
        virtual ~CanvasPatternPeer() = default;
    };
    const GENERATED_ArkUIImageBitmapAccessor* GetImageBitmapAccessor()
    {
        static const GENERATED_ArkUIImageBitmapAccessor ImageBitmapAccessorImpl {
            ImageBitmapAccessor::DestroyPeerImpl,
            ImageBitmapAccessor::CtorImpl,
            ImageBitmapAccessor::GetFinalizerImpl,
            ImageBitmapAccessor::CloseImpl,
            ImageBitmapAccessor::GetHeightImpl,
            ImageBitmapAccessor::GetWidthImpl,
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
            ImageDataAccessor::CtorImpl,
            ImageDataAccessor::GetFinalizerImpl,
            ImageDataAccessor::GetDataImpl,
            ImageDataAccessor::GetHeightImpl,
            ImageDataAccessor::GetWidthImpl,
        };
        return &ImageDataAccessorImpl;
    }

    struct ImageDataPeer {
        virtual ~ImageDataPeer() = default;
    };
    const GENERATED_ArkUIRenderingContextSettingsAccessor* GetRenderingContextSettingsAccessor()
    {
        static const GENERATED_ArkUIRenderingContextSettingsAccessor RenderingContextSettingsAccessorImpl {
            RenderingContextSettingsAccessor::DestroyPeerImpl,
            RenderingContextSettingsAccessor::CtorImpl,
            RenderingContextSettingsAccessor::GetFinalizerImpl,
            RenderingContextSettingsAccessor::GetAntialiasImpl,
            RenderingContextSettingsAccessor::SetAntialiasImpl,
        };
        return &RenderingContextSettingsAccessorImpl;
    }

    struct RenderingContextSettingsPeer {
        virtual ~RenderingContextSettingsPeer() = default;
    };
    const GENERATED_ArkUICanvasRendererAccessor* GetCanvasRendererAccessor()
    {
        static const GENERATED_ArkUICanvasRendererAccessor CanvasRendererAccessorImpl {
            CanvasRendererAccessor::DestroyPeerImpl,
            CanvasRendererAccessor::CtorImpl,
            CanvasRendererAccessor::GetFinalizerImpl,
            CanvasRendererAccessor::DrawImage0Impl,
            CanvasRendererAccessor::DrawImage1Impl,
            CanvasRendererAccessor::DrawImage2Impl,
            CanvasRendererAccessor::BeginPathImpl,
            CanvasRendererAccessor::Clip0Impl,
            CanvasRendererAccessor::Clip1Impl,
            CanvasRendererAccessor::Fill0Impl,
            CanvasRendererAccessor::Fill1Impl,
            CanvasRendererAccessor::Stroke0Impl,
            CanvasRendererAccessor::Stroke1Impl,
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
            CanvasRenderingContext2DAccessor::CtorImpl,
            CanvasRenderingContext2DAccessor::GetFinalizerImpl,
            CanvasRenderingContext2DAccessor::ToDataURLImpl,
            CanvasRenderingContext2DAccessor::StartImageAnalyzerImpl,
            CanvasRenderingContext2DAccessor::StopImageAnalyzerImpl,
            CanvasRenderingContext2DAccessor::OnOnAttachImpl,
            CanvasRenderingContext2DAccessor::OffOnAttachImpl,
            CanvasRenderingContext2DAccessor::OnOnDetachImpl,
            CanvasRenderingContext2DAccessor::OffOnDetachImpl,
            CanvasRenderingContext2DAccessor::GetHeightImpl,
            CanvasRenderingContext2DAccessor::GetWidthImpl,
            CanvasRenderingContext2DAccessor::GetCanvasImpl,
        };
        return &CanvasRenderingContext2DAccessorImpl;
    }

    struct CanvasRenderingContext2DPeer {
        virtual ~CanvasRenderingContext2DPeer() = default;
    };
    const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor* GetOffscreenCanvasRenderingContext2DAccessor()
    {
        static const GENERATED_ArkUIOffscreenCanvasRenderingContext2DAccessor OffscreenCanvasRenderingContext2DAccessorImpl {
            OffscreenCanvasRenderingContext2DAccessor::DestroyPeerImpl,
            OffscreenCanvasRenderingContext2DAccessor::CtorImpl,
            OffscreenCanvasRenderingContext2DAccessor::GetFinalizerImpl,
            OffscreenCanvasRenderingContext2DAccessor::ToDataURLImpl,
            OffscreenCanvasRenderingContext2DAccessor::TransferToImageBitmapImpl,
        };
        return &OffscreenCanvasRenderingContext2DAccessorImpl;
    }

    struct OffscreenCanvasRenderingContext2DPeer {
        virtual ~OffscreenCanvasRenderingContext2DPeer() = default;
    };
    const GENERATED_ArkUIOffscreenCanvasAccessor* GetOffscreenCanvasAccessor()
    {
        static const GENERATED_ArkUIOffscreenCanvasAccessor OffscreenCanvasAccessorImpl {
            OffscreenCanvasAccessor::DestroyPeerImpl,
            OffscreenCanvasAccessor::CtorImpl,
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
    const GENERATED_ArkUIDrawingRenderingContextAccessor* GetDrawingRenderingContextAccessor()
    {
        static const GENERATED_ArkUIDrawingRenderingContextAccessor DrawingRenderingContextAccessorImpl {
            DrawingRenderingContextAccessor::DestroyPeerImpl,
            DrawingRenderingContextAccessor::CtorImpl,
            DrawingRenderingContextAccessor::GetFinalizerImpl,
            DrawingRenderingContextAccessor::InvalidateImpl,
            DrawingRenderingContextAccessor::GetSizeImpl,
            DrawingRenderingContextAccessor::GetCanvasImpl,
        };
        return &DrawingRenderingContextAccessorImpl;
    }

    struct DrawingRenderingContextPeer {
        virtual ~DrawingRenderingContextPeer() = default;
    };
    const GENERATED_ArkUIICurveAccessor* GetICurveAccessor()
    {
        static const GENERATED_ArkUIICurveAccessor ICurveAccessorImpl {
            ICurveAccessor::DestroyPeerImpl,
            ICurveAccessor::CtorImpl,
            ICurveAccessor::GetFinalizerImpl,
            ICurveAccessor::InterpolateImpl,
        };
        return &ICurveAccessorImpl;
    }

    struct ICurvePeer {
        virtual ~ICurvePeer() = default;
    };
    const GENERATED_ArkUIDrawModifierAccessor* GetDrawModifierAccessor()
    {
        static const GENERATED_ArkUIDrawModifierAccessor DrawModifierAccessorImpl {
            DrawModifierAccessor::DestroyPeerImpl,
            DrawModifierAccessor::CtorImpl,
            DrawModifierAccessor::GetFinalizerImpl,
            DrawModifierAccessor::DrawBehindImpl,
            DrawModifierAccessor::DrawContentImpl,
            DrawModifierAccessor::DrawFrontImpl,
            DrawModifierAccessor::InvalidateImpl,
        };
        return &DrawModifierAccessorImpl;
    }

    struct DrawModifierPeer {
        virtual ~DrawModifierPeer() = default;
    };
    const GENERATED_ArkUITransitionEffectAccessor* GetTransitionEffectAccessor()
    {
        static const GENERATED_ArkUITransitionEffectAccessor TransitionEffectAccessorImpl {
            TransitionEffectAccessor::DestroyPeerImpl,
            TransitionEffectAccessor::CtorImpl,
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
            TransitionEffectAccessor::GetOPACITYImpl,
            TransitionEffectAccessor::GetSLIDEImpl,
            TransitionEffectAccessor::GetSLIDE_SWITCHImpl,
        };
        return &TransitionEffectAccessorImpl;
    }

    struct TransitionEffectPeer {
        virtual ~TransitionEffectPeer() = default;
    };
    const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
    {
        static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
            BaseEventAccessor::DestroyPeerImpl,
            BaseEventAccessor::CtorImpl,
            BaseEventAccessor::GetFinalizerImpl,
            BaseEventAccessor::GetModifierKeyStateImpl,
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
            BaseEventAccessor::GetSourceToolImpl,
            BaseEventAccessor::SetSourceToolImpl,
            BaseEventAccessor::GetDeviceIdImpl,
            BaseEventAccessor::SetDeviceIdImpl,
        };
        return &BaseEventAccessorImpl;
    }

    struct BaseEventPeer {
        virtual ~BaseEventPeer() = default;
    };
    const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor()
    {
        static const GENERATED_ArkUIClickEventAccessor ClickEventAccessorImpl {
            ClickEventAccessor::DestroyPeerImpl,
            ClickEventAccessor::CtorImpl,
            ClickEventAccessor::GetFinalizerImpl,
            ClickEventAccessor::GetDisplayXImpl,
            ClickEventAccessor::SetDisplayXImpl,
            ClickEventAccessor::GetDisplayYImpl,
            ClickEventAccessor::SetDisplayYImpl,
            ClickEventAccessor::GetWindowXImpl,
            ClickEventAccessor::SetWindowXImpl,
            ClickEventAccessor::GetWindowYImpl,
            ClickEventAccessor::SetWindowYImpl,
            ClickEventAccessor::GetScreenXImpl,
            ClickEventAccessor::SetScreenXImpl,
            ClickEventAccessor::GetScreenYImpl,
            ClickEventAccessor::SetScreenYImpl,
            ClickEventAccessor::GetXImpl,
            ClickEventAccessor::SetXImpl,
            ClickEventAccessor::GetYImpl,
            ClickEventAccessor::SetYImpl,
            ClickEventAccessor::GetPreventDefaultImpl,
            ClickEventAccessor::SetPreventDefaultImpl,
        };
        return &ClickEventAccessorImpl;
    }

    struct ClickEventPeer {
        virtual ~ClickEventPeer() = default;
    };
    const GENERATED_ArkUIHoverEventAccessor* GetHoverEventAccessor()
    {
        static const GENERATED_ArkUIHoverEventAccessor HoverEventAccessorImpl {
            HoverEventAccessor::DestroyPeerImpl,
            HoverEventAccessor::CtorImpl,
            HoverEventAccessor::GetFinalizerImpl,
            HoverEventAccessor::GetStopPropagationImpl,
            HoverEventAccessor::SetStopPropagationImpl,
        };
        return &HoverEventAccessorImpl;
    }

    struct HoverEventPeer {
        virtual ~HoverEventPeer() = default;
    };
    const GENERATED_ArkUIMouseEventAccessor* GetMouseEventAccessor()
    {
        static const GENERATED_ArkUIMouseEventAccessor MouseEventAccessorImpl {
            MouseEventAccessor::DestroyPeerImpl,
            MouseEventAccessor::CtorImpl,
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
            MouseEventAccessor::GetScreenXImpl,
            MouseEventAccessor::SetScreenXImpl,
            MouseEventAccessor::GetScreenYImpl,
            MouseEventAccessor::SetScreenYImpl,
            MouseEventAccessor::GetXImpl,
            MouseEventAccessor::SetXImpl,
            MouseEventAccessor::GetYImpl,
            MouseEventAccessor::SetYImpl,
            MouseEventAccessor::GetStopPropagationImpl,
            MouseEventAccessor::SetStopPropagationImpl,
        };
        return &MouseEventAccessorImpl;
    }

    struct MouseEventPeer {
        virtual ~MouseEventPeer() = default;
    };
    const GENERATED_ArkUIAccessibilityHoverEventAccessor* GetAccessibilityHoverEventAccessor()
    {
        static const GENERATED_ArkUIAccessibilityHoverEventAccessor AccessibilityHoverEventAccessorImpl {
            AccessibilityHoverEventAccessor::DestroyPeerImpl,
            AccessibilityHoverEventAccessor::CtorImpl,
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
    const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
    {
        static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
            TouchEventAccessor::DestroyPeerImpl,
            TouchEventAccessor::CtorImpl,
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
    const GENERATED_ArkUIPixelMapMockAccessor* GetPixelMapMockAccessor()
    {
        static const GENERATED_ArkUIPixelMapMockAccessor PixelMapMockAccessorImpl {
            PixelMapMockAccessor::DestroyPeerImpl,
            PixelMapMockAccessor::CtorImpl,
            PixelMapMockAccessor::GetFinalizerImpl,
            PixelMapMockAccessor::ReleaseImpl,
        };
        return &PixelMapMockAccessorImpl;
    }

    struct PixelMapMockPeer {
        virtual ~PixelMapMockPeer() = default;
    };
    const GENERATED_ArkUIDragEventAccessor* GetDragEventAccessor()
    {
        static const GENERATED_ArkUIDragEventAccessor DragEventAccessorImpl {
            DragEventAccessor::DestroyPeerImpl,
            DragEventAccessor::CtorImpl,
            DragEventAccessor::GetFinalizerImpl,
            DragEventAccessor::GetDisplayXImpl,
            DragEventAccessor::GetDisplayYImpl,
            DragEventAccessor::GetWindowXImpl,
            DragEventAccessor::GetWindowYImpl,
            DragEventAccessor::GetXImpl,
            DragEventAccessor::GetYImpl,
            DragEventAccessor::SetDataImpl,
            DragEventAccessor::GetDataImpl,
            DragEventAccessor::GetSummaryImpl,
            DragEventAccessor::SetResultImpl,
            DragEventAccessor::GetResultImpl,
            DragEventAccessor::GetPreviewRectImpl,
            DragEventAccessor::GetVelocityXImpl,
            DragEventAccessor::GetVelocityYImpl,
            DragEventAccessor::GetVelocityImpl,
            DragEventAccessor::GetModifierKeyStateImpl,
            DragEventAccessor::GetDragBehaviorImpl,
            DragEventAccessor::SetDragBehaviorImpl,
            DragEventAccessor::GetUseCustomDropAnimationImpl,
            DragEventAccessor::SetUseCustomDropAnimationImpl,
        };
        return &DragEventAccessorImpl;
    }

    struct DragEventPeer {
        virtual ~DragEventPeer() = default;
    };
    const GENERATED_ArkUIKeyEventAccessor* GetKeyEventAccessor()
    {
        static const GENERATED_ArkUIKeyEventAccessor KeyEventAccessorImpl {
            KeyEventAccessor::DestroyPeerImpl,
            KeyEventAccessor::CtorImpl,
            KeyEventAccessor::GetFinalizerImpl,
            KeyEventAccessor::GetModifierKeyStateImpl,
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
            KeyEventAccessor::GetUnicodeImpl,
            KeyEventAccessor::SetUnicodeImpl,
        };
        return &KeyEventAccessorImpl;
    }

    struct KeyEventPeer {
        virtual ~KeyEventPeer() = default;
    };
    const GENERATED_ArkUIProgressMaskAccessor* GetProgressMaskAccessor()
    {
        static const GENERATED_ArkUIProgressMaskAccessor ProgressMaskAccessorImpl {
            ProgressMaskAccessor::DestroyPeerImpl,
            ProgressMaskAccessor::CtorImpl,
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
    const GENERATED_ArkUIMeasurableAccessor* GetMeasurableAccessor()
    {
        static const GENERATED_ArkUIMeasurableAccessor MeasurableAccessorImpl {
            MeasurableAccessor::DestroyPeerImpl,
            MeasurableAccessor::CtorImpl,
            MeasurableAccessor::GetFinalizerImpl,
            MeasurableAccessor::MeasureImpl,
            MeasurableAccessor::GetMarginImpl,
            MeasurableAccessor::GetPaddingImpl,
            MeasurableAccessor::GetBorderWidthImpl,
        };
        return &MeasurableAccessorImpl;
    }

    struct MeasurablePeer {
        virtual ~MeasurablePeer() = default;
    };
    const GENERATED_ArkUIViewAccessor* GetViewAccessor()
    {
        static const GENERATED_ArkUIViewAccessor ViewAccessorImpl {
            ViewAccessor::DestroyPeerImpl,
            ViewAccessor::CtorImpl,
            ViewAccessor::GetFinalizerImpl,
            ViewAccessor::CreateImpl,
        };
        return &ViewAccessorImpl;
    }

    struct ViewPeer {
        virtual ~ViewPeer() = default;
    };
    const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor()
    {
        static const GENERATED_ArkUITextContentControllerBaseAccessor TextContentControllerBaseAccessorImpl {
            TextContentControllerBaseAccessor::DestroyPeerImpl,
            TextContentControllerBaseAccessor::CtorImpl,
            TextContentControllerBaseAccessor::GetFinalizerImpl,
            TextContentControllerBaseAccessor::GetCaretOffsetImpl,
            TextContentControllerBaseAccessor::GetTextContentRectImpl,
            TextContentControllerBaseAccessor::GetTextContentLineCountImpl,
        };
        return &TextContentControllerBaseAccessorImpl;
    }

    struct TextContentControllerBasePeer {
        virtual ~TextContentControllerBasePeer() = default;
    };
    const GENERATED_ArkUIChildrenMainSizeAccessor* GetChildrenMainSizeAccessor()
    {
        static const GENERATED_ArkUIChildrenMainSizeAccessor ChildrenMainSizeAccessorImpl {
            ChildrenMainSizeAccessor::DestroyPeerImpl,
            ChildrenMainSizeAccessor::CtorImpl,
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
    const GENERATED_ArkUIUICommonEventAccessor* GetUICommonEventAccessor()
    {
        static const GENERATED_ArkUIUICommonEventAccessor UICommonEventAccessorImpl {
            UICommonEventAccessor::DestroyPeerImpl,
            UICommonEventAccessor::CtorImpl,
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
    const GENERATED_ArkUIGestureModifierAccessor* GetGestureModifierAccessor()
    {
        static const GENERATED_ArkUIGestureModifierAccessor GestureModifierAccessorImpl {
            GestureModifierAccessor::DestroyPeerImpl,
            GestureModifierAccessor::CtorImpl,
            GestureModifierAccessor::GetFinalizerImpl,
            GestureModifierAccessor::ApplyGestureImpl,
        };
        return &GestureModifierAccessorImpl;
    }

    struct GestureModifierPeer {
        virtual ~GestureModifierPeer() = default;
    };
    const GENERATED_ArkUIContextMenuAccessor* GetContextMenuAccessor()
    {
        static const GENERATED_ArkUIContextMenuAccessor ContextMenuAccessorImpl {
            ContextMenuAccessor::CloseImpl,
        };
        return &ContextMenuAccessorImpl;
    }

    const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
    {
        static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
            CustomDialogControllerAccessor::DestroyPeerImpl,
            CustomDialogControllerAccessor::CtorImpl,
            CustomDialogControllerAccessor::GetFinalizerImpl,
            CustomDialogControllerAccessor::OpenImpl,
            CustomDialogControllerAccessor::CloseImpl,
        };
        return &CustomDialogControllerAccessorImpl;
    }

    struct CustomDialogControllerPeer {
        virtual ~CustomDialogControllerPeer() = default;
    };
    const GENERATED_ArkUILinearGradientAccessor* GetLinearGradientAccessor()
    {
        static const GENERATED_ArkUILinearGradientAccessor LinearGradientAccessorImpl {
            LinearGradientAccessor::DestroyPeerImpl,
            LinearGradientAccessor::CtorImpl,
            LinearGradientAccessor::GetFinalizerImpl,
        };
        return &LinearGradientAccessorImpl;
    }

    struct LinearGradientPeer {
        virtual ~LinearGradientPeer() = default;
    };
    const GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogAccessor()
    {
        static const GENERATED_ArkUIDatePickerDialogAccessor DatePickerDialogAccessorImpl {
            DatePickerDialogAccessor::ShowImpl,
        };
        return &DatePickerDialogAccessorImpl;
    }

    const GENERATED_ArkUIBaseGestureEventAccessor* GetBaseGestureEventAccessor()
    {
        static const GENERATED_ArkUIBaseGestureEventAccessor BaseGestureEventAccessorImpl {
            BaseGestureEventAccessor::DestroyPeerImpl,
            BaseGestureEventAccessor::CtorImpl,
            BaseGestureEventAccessor::GetFinalizerImpl,
            BaseGestureEventAccessor::GetFingerListImpl,
            BaseGestureEventAccessor::SetFingerListImpl,
        };
        return &BaseGestureEventAccessorImpl;
    }

    struct BaseGestureEventPeer {
        virtual ~BaseGestureEventPeer() = default;
    };
    const GENERATED_ArkUITapGestureEventAccessor* GetTapGestureEventAccessor()
    {
        static const GENERATED_ArkUITapGestureEventAccessor TapGestureEventAccessorImpl {
            TapGestureEventAccessor::DestroyPeerImpl,
            TapGestureEventAccessor::CtorImpl,
            TapGestureEventAccessor::GetFinalizerImpl,
        };
        return &TapGestureEventAccessorImpl;
    }

    struct TapGestureEventPeer {
        virtual ~TapGestureEventPeer() = default;
    };
    const GENERATED_ArkUILongPressGestureEventAccessor* GetLongPressGestureEventAccessor()
    {
        static const GENERATED_ArkUILongPressGestureEventAccessor LongPressGestureEventAccessorImpl {
            LongPressGestureEventAccessor::DestroyPeerImpl,
            LongPressGestureEventAccessor::CtorImpl,
            LongPressGestureEventAccessor::GetFinalizerImpl,
            LongPressGestureEventAccessor::GetRepeatImpl,
            LongPressGestureEventAccessor::SetRepeatImpl,
        };
        return &LongPressGestureEventAccessorImpl;
    }

    struct LongPressGestureEventPeer {
        virtual ~LongPressGestureEventPeer() = default;
    };
    const GENERATED_ArkUIPanGestureEventAccessor* GetPanGestureEventAccessor()
    {
        static const GENERATED_ArkUIPanGestureEventAccessor PanGestureEventAccessorImpl {
            PanGestureEventAccessor::DestroyPeerImpl,
            PanGestureEventAccessor::CtorImpl,
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
    const GENERATED_ArkUIPinchGestureEventAccessor* GetPinchGestureEventAccessor()
    {
        static const GENERATED_ArkUIPinchGestureEventAccessor PinchGestureEventAccessorImpl {
            PinchGestureEventAccessor::DestroyPeerImpl,
            PinchGestureEventAccessor::CtorImpl,
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
    const GENERATED_ArkUIRotationGestureEventAccessor* GetRotationGestureEventAccessor()
    {
        static const GENERATED_ArkUIRotationGestureEventAccessor RotationGestureEventAccessorImpl {
            RotationGestureEventAccessor::DestroyPeerImpl,
            RotationGestureEventAccessor::CtorImpl,
            RotationGestureEventAccessor::GetFinalizerImpl,
            RotationGestureEventAccessor::GetAngleImpl,
            RotationGestureEventAccessor::SetAngleImpl,
        };
        return &RotationGestureEventAccessorImpl;
    }

    struct RotationGestureEventPeer {
        virtual ~RotationGestureEventPeer() = default;
    };
    const GENERATED_ArkUISwipeGestureEventAccessor* GetSwipeGestureEventAccessor()
    {
        static const GENERATED_ArkUISwipeGestureEventAccessor SwipeGestureEventAccessorImpl {
            SwipeGestureEventAccessor::DestroyPeerImpl,
            SwipeGestureEventAccessor::CtorImpl,
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
    const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor()
    {
        static const GENERATED_ArkUIGestureEventAccessor GestureEventAccessorImpl {
            GestureEventAccessor::DestroyPeerImpl,
            GestureEventAccessor::CtorImpl,
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
    const GENERATED_ArkUITapGestureInterfaceAccessor* GetTapGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUITapGestureInterfaceAccessor TapGestureInterfaceAccessorImpl {
            TapGestureInterfaceAccessor::DestroyPeerImpl,
            TapGestureInterfaceAccessor::CtorImpl,
            TapGestureInterfaceAccessor::GetFinalizerImpl,
            TapGestureInterfaceAccessor::OnActionImpl,
        };
        return &TapGestureInterfaceAccessorImpl;
    }

    struct TapGestureInterfacePeer {
        virtual ~TapGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUILongPressGestureInterfaceAccessor* GetLongPressGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUILongPressGestureInterfaceAccessor LongPressGestureInterfaceAccessorImpl {
            LongPressGestureInterfaceAccessor::DestroyPeerImpl,
            LongPressGestureInterfaceAccessor::CtorImpl,
            LongPressGestureInterfaceAccessor::GetFinalizerImpl,
            LongPressGestureInterfaceAccessor::OnActionImpl,
            LongPressGestureInterfaceAccessor::OnActionEndImpl,
            LongPressGestureInterfaceAccessor::OnActionCancelImpl,
        };
        return &LongPressGestureInterfaceAccessorImpl;
    }

    struct LongPressGestureInterfacePeer {
        virtual ~LongPressGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor()
    {
        static const GENERATED_ArkUIPanGestureOptionsAccessor PanGestureOptionsAccessorImpl {
            PanGestureOptionsAccessor::DestroyPeerImpl,
            PanGestureOptionsAccessor::CtorImpl,
            PanGestureOptionsAccessor::GetFinalizerImpl,
            PanGestureOptionsAccessor::SetDirectionImpl,
            PanGestureOptionsAccessor::SetDistanceImpl,
            PanGestureOptionsAccessor::SetFingersImpl,
            PanGestureOptionsAccessor::GetDirectionImpl,
        };
        return &PanGestureOptionsAccessorImpl;
    }

    struct PanGestureOptionsPeer {
        virtual ~PanGestureOptionsPeer() = default;
    };
    const GENERATED_ArkUIPanGestureInterfaceAccessor* GetPanGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUIPanGestureInterfaceAccessor PanGestureInterfaceAccessorImpl {
            PanGestureInterfaceAccessor::DestroyPeerImpl,
            PanGestureInterfaceAccessor::CtorImpl,
            PanGestureInterfaceAccessor::GetFinalizerImpl,
            PanGestureInterfaceAccessor::OnActionStartImpl,
            PanGestureInterfaceAccessor::OnActionUpdateImpl,
            PanGestureInterfaceAccessor::OnActionEndImpl,
            PanGestureInterfaceAccessor::OnActionCancelImpl,
        };
        return &PanGestureInterfaceAccessorImpl;
    }

    struct PanGestureInterfacePeer {
        virtual ~PanGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUISwipeGestureInterfaceAccessor* GetSwipeGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUISwipeGestureInterfaceAccessor SwipeGestureInterfaceAccessorImpl {
            SwipeGestureInterfaceAccessor::DestroyPeerImpl,
            SwipeGestureInterfaceAccessor::CtorImpl,
            SwipeGestureInterfaceAccessor::GetFinalizerImpl,
            SwipeGestureInterfaceAccessor::OnActionImpl,
        };
        return &SwipeGestureInterfaceAccessorImpl;
    }

    struct SwipeGestureInterfacePeer {
        virtual ~SwipeGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUIPinchGestureInterfaceAccessor* GetPinchGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUIPinchGestureInterfaceAccessor PinchGestureInterfaceAccessorImpl {
            PinchGestureInterfaceAccessor::DestroyPeerImpl,
            PinchGestureInterfaceAccessor::CtorImpl,
            PinchGestureInterfaceAccessor::GetFinalizerImpl,
            PinchGestureInterfaceAccessor::OnActionStartImpl,
            PinchGestureInterfaceAccessor::OnActionUpdateImpl,
            PinchGestureInterfaceAccessor::OnActionEndImpl,
            PinchGestureInterfaceAccessor::OnActionCancelImpl,
        };
        return &PinchGestureInterfaceAccessorImpl;
    }

    struct PinchGestureInterfacePeer {
        virtual ~PinchGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUIRotationGestureInterfaceAccessor* GetRotationGestureInterfaceAccessor()
    {
        static const GENERATED_ArkUIRotationGestureInterfaceAccessor RotationGestureInterfaceAccessorImpl {
            RotationGestureInterfaceAccessor::DestroyPeerImpl,
            RotationGestureInterfaceAccessor::CtorImpl,
            RotationGestureInterfaceAccessor::GetFinalizerImpl,
            RotationGestureInterfaceAccessor::OnActionStartImpl,
            RotationGestureInterfaceAccessor::OnActionUpdateImpl,
            RotationGestureInterfaceAccessor::OnActionEndImpl,
            RotationGestureInterfaceAccessor::OnActionCancelImpl,
        };
        return &RotationGestureInterfaceAccessorImpl;
    }

    struct RotationGestureInterfacePeer {
        virtual ~RotationGestureInterfacePeer() = default;
    };
    const GENERATED_ArkUIGestureGroupInterfaceAccessor* GetGestureGroupInterfaceAccessor()
    {
        static const GENERATED_ArkUIGestureGroupInterfaceAccessor GestureGroupInterfaceAccessorImpl {
            GestureGroupInterfaceAccessor::DestroyPeerImpl,
            GestureGroupInterfaceAccessor::CtorImpl,
            GestureGroupInterfaceAccessor::GetFinalizerImpl,
            GestureGroupInterfaceAccessor::OnCancelImpl,
        };
        return &GestureGroupInterfaceAccessorImpl;
    }

    struct GestureGroupInterfacePeer {
        virtual ~GestureGroupInterfacePeer() = default;
    };
    const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor()
    {
        static const GENERATED_ArkUIScrollableTargetInfoAccessor ScrollableTargetInfoAccessorImpl {
            ScrollableTargetInfoAccessor::DestroyPeerImpl,
            ScrollableTargetInfoAccessor::CtorImpl,
            ScrollableTargetInfoAccessor::GetFinalizerImpl,
            ScrollableTargetInfoAccessor::IsBeginImpl,
            ScrollableTargetInfoAccessor::IsEndImpl,
        };
        return &ScrollableTargetInfoAccessorImpl;
    }

    struct ScrollableTargetInfoPeer {
        virtual ~ScrollableTargetInfoPeer() = default;
    };
    const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor()
    {
        static const GENERATED_ArkUIEventTargetInfoAccessor EventTargetInfoAccessorImpl {
            EventTargetInfoAccessor::DestroyPeerImpl,
            EventTargetInfoAccessor::CtorImpl,
            EventTargetInfoAccessor::GetFinalizerImpl,
            EventTargetInfoAccessor::GetIdImpl,
        };
        return &EventTargetInfoAccessorImpl;
    }

    struct EventTargetInfoPeer {
        virtual ~EventTargetInfoPeer() = default;
    };
    const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor()
    {
        static const GENERATED_ArkUIGestureRecognizerAccessor GestureRecognizerAccessorImpl {
            GestureRecognizerAccessor::DestroyPeerImpl,
            GestureRecognizerAccessor::CtorImpl,
            GestureRecognizerAccessor::GetFinalizerImpl,
            GestureRecognizerAccessor::GetTagImpl,
            GestureRecognizerAccessor::GetTypeImpl,
            GestureRecognizerAccessor::IsBuiltInImpl,
            GestureRecognizerAccessor::SetEnabledImpl,
            GestureRecognizerAccessor::IsEnabledImpl,
            GestureRecognizerAccessor::GetStateImpl,
            GestureRecognizerAccessor::GetEventTargetInfoImpl,
            GestureRecognizerAccessor::IsValidImpl,
        };
        return &GestureRecognizerAccessorImpl;
    }

    struct GestureRecognizerPeer {
        virtual ~GestureRecognizerPeer() = default;
    };
    const GENERATED_ArkUIPanRecognizerAccessor* GetPanRecognizerAccessor()
    {
        static const GENERATED_ArkUIPanRecognizerAccessor PanRecognizerAccessorImpl {
            PanRecognizerAccessor::DestroyPeerImpl,
            PanRecognizerAccessor::CtorImpl,
            PanRecognizerAccessor::GetFinalizerImpl,
            PanRecognizerAccessor::GetPanGestureOptionsImpl,
        };
        return &PanRecognizerAccessorImpl;
    }

    struct PanRecognizerPeer {
        virtual ~PanRecognizerPeer() = default;
    };
    const GENERATED_ArkUIImageAnalyzerControllerAccessor* GetImageAnalyzerControllerAccessor()
    {
        static const GENERATED_ArkUIImageAnalyzerControllerAccessor ImageAnalyzerControllerAccessorImpl {
            ImageAnalyzerControllerAccessor::DestroyPeerImpl,
            ImageAnalyzerControllerAccessor::CtorImpl,
            ImageAnalyzerControllerAccessor::GetFinalizerImpl,
            ImageAnalyzerControllerAccessor::GetImageAnalyzerSupportTypesImpl,
        };
        return &ImageAnalyzerControllerAccessorImpl;
    }

    struct ImageAnalyzerControllerPeer {
        virtual ~ImageAnalyzerControllerPeer() = default;
    };
    const GENERATED_ArkUIListScrollerAccessor* GetListScrollerAccessor()
    {
        static const GENERATED_ArkUIListScrollerAccessor ListScrollerAccessorImpl {
            ListScrollerAccessor::DestroyPeerImpl,
            ListScrollerAccessor::CtorImpl,
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
    const GENERATED_ArkUIMatrix2DAccessor* GetMatrix2DAccessor()
    {
        static const GENERATED_ArkUIMatrix2DAccessor Matrix2DAccessorImpl {
            Matrix2DAccessor::DestroyPeerImpl,
            Matrix2DAccessor::CtorImpl,
            Matrix2DAccessor::GetFinalizerImpl,
            Matrix2DAccessor::IdentityImpl,
            Matrix2DAccessor::InvertImpl,
            Matrix2DAccessor::MultiplyImpl,
            Matrix2DAccessor::Rotate0Impl,
            Matrix2DAccessor::Rotate1Impl,
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
    const GENERATED_ArkUINavDestinationContextAccessor* GetNavDestinationContextAccessor()
    {
        static const GENERATED_ArkUINavDestinationContextAccessor NavDestinationContextAccessorImpl {
            NavDestinationContextAccessor::DestroyPeerImpl,
            NavDestinationContextAccessor::CtorImpl,
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
    const GENERATED_ArkUINavPathInfoAccessor* GetNavPathInfoAccessor()
    {
        static const GENERATED_ArkUINavPathInfoAccessor NavPathInfoAccessorImpl {
            NavPathInfoAccessor::DestroyPeerImpl,
            NavPathInfoAccessor::CtorImpl,
            NavPathInfoAccessor::GetFinalizerImpl,
            NavPathInfoAccessor::GetNameImpl,
            NavPathInfoAccessor::SetNameImpl,
            NavPathInfoAccessor::GetParamImpl,
            NavPathInfoAccessor::SetParamImpl,
            NavPathInfoAccessor::GetOnPopImpl,
            NavPathInfoAccessor::SetOnPopImpl,
            NavPathInfoAccessor::GetIsEntryImpl,
            NavPathInfoAccessor::SetIsEntryImpl,
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
            NavPathStackAccessor::CtorImpl,
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
        };
        return &NavPathStackAccessorImpl;
    }

    struct NavPathStackPeer {
        virtual ~NavPathStackPeer() = default;
    };
    const GENERATED_ArkUINavigationTransitionProxyAccessor* GetNavigationTransitionProxyAccessor()
    {
        static const GENERATED_ArkUINavigationTransitionProxyAccessor NavigationTransitionProxyAccessorImpl {
            NavigationTransitionProxyAccessor::DestroyPeerImpl,
            NavigationTransitionProxyAccessor::CtorImpl,
            NavigationTransitionProxyAccessor::GetFinalizerImpl,
            NavigationTransitionProxyAccessor::FinishTransitionImpl,
            NavigationTransitionProxyAccessor::CancelTransitionImpl,
            NavigationTransitionProxyAccessor::UpdateTransitionImpl,
            NavigationTransitionProxyAccessor::GetFromImpl,
            NavigationTransitionProxyAccessor::SetFromImpl,
            NavigationTransitionProxyAccessor::GetToImpl,
            NavigationTransitionProxyAccessor::SetToImpl,
            NavigationTransitionProxyAccessor::GetIsInteractiveImpl,
            NavigationTransitionProxyAccessor::SetIsInteractiveImpl,
        };
        return &NavigationTransitionProxyAccessorImpl;
    }

    struct NavigationTransitionProxyPeer {
        virtual ~NavigationTransitionProxyPeer() = default;
    };
    const GENERATED_ArkUIPatternLockControllerAccessor* GetPatternLockControllerAccessor()
    {
        static const GENERATED_ArkUIPatternLockControllerAccessor PatternLockControllerAccessorImpl {
            PatternLockControllerAccessor::DestroyPeerImpl,
            PatternLockControllerAccessor::CtorImpl,
            PatternLockControllerAccessor::GetFinalizerImpl,
            PatternLockControllerAccessor::ResetImpl,
            PatternLockControllerAccessor::SetChallengeResultImpl,
        };
        return &PatternLockControllerAccessorImpl;
    }

    struct PatternLockControllerPeer {
        virtual ~PatternLockControllerPeer() = default;
    };
    const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
    {
        static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
            RichEditorBaseControllerAccessor::DestroyPeerImpl,
            RichEditorBaseControllerAccessor::CtorImpl,
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
            RichEditorControllerAccessor::CtorImpl,
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
            RichEditorStyledStringControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUIScrollerAccessor* GetScrollerAccessor()
    {
        static const GENERATED_ArkUIScrollerAccessor ScrollerAccessorImpl {
            ScrollerAccessor::DestroyPeerImpl,
            ScrollerAccessor::CtorImpl,
            ScrollerAccessor::GetFinalizerImpl,
            ScrollerAccessor::ScrollToImpl,
            ScrollerAccessor::ScrollEdgeImpl,
            ScrollerAccessor::FlingImpl,
            ScrollerAccessor::ScrollPage0Impl,
            ScrollerAccessor::ScrollPage1Impl,
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
    const GENERATED_ArkUISearchControllerAccessor* GetSearchControllerAccessor()
    {
        static const GENERATED_ArkUISearchControllerAccessor SearchControllerAccessorImpl {
            SearchControllerAccessor::DestroyPeerImpl,
            SearchControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUISwiperControllerAccessor* GetSwiperControllerAccessor()
    {
        static const GENERATED_ArkUISwiperControllerAccessor SwiperControllerAccessorImpl {
            SwiperControllerAccessor::DestroyPeerImpl,
            SwiperControllerAccessor::CtorImpl,
            SwiperControllerAccessor::GetFinalizerImpl,
            SwiperControllerAccessor::ShowNextImpl,
            SwiperControllerAccessor::ShowPreviousImpl,
            SwiperControllerAccessor::ChangeIndexImpl,
            SwiperControllerAccessor::FinishAnimationImpl,
        };
        return &SwiperControllerAccessorImpl;
    }

    struct SwiperControllerPeer {
        virtual ~SwiperControllerPeer() = default;
    };
    const GENERATED_ArkUISwiperContentTransitionProxyAccessor* GetSwiperContentTransitionProxyAccessor()
    {
        static const GENERATED_ArkUISwiperContentTransitionProxyAccessor SwiperContentTransitionProxyAccessorImpl {
            SwiperContentTransitionProxyAccessor::DestroyPeerImpl,
            SwiperContentTransitionProxyAccessor::CtorImpl,
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
    const GENERATED_ArkUIIndicatorComponentControllerAccessor* GetIndicatorComponentControllerAccessor()
    {
        static const GENERATED_ArkUIIndicatorComponentControllerAccessor IndicatorComponentControllerAccessorImpl {
            IndicatorComponentControllerAccessor::DestroyPeerImpl,
            IndicatorComponentControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUIHierarchicalSymbolEffectAccessor* GetHierarchicalSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIHierarchicalSymbolEffectAccessor HierarchicalSymbolEffectAccessorImpl {
            HierarchicalSymbolEffectAccessor::DestroyPeerImpl,
            HierarchicalSymbolEffectAccessor::CtorImpl,
            HierarchicalSymbolEffectAccessor::GetFinalizerImpl,
            HierarchicalSymbolEffectAccessor::GetFillStyleImpl,
            HierarchicalSymbolEffectAccessor::SetFillStyleImpl,
        };
        return &HierarchicalSymbolEffectAccessorImpl;
    }

    struct HierarchicalSymbolEffectPeer {
        virtual ~HierarchicalSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIAppearSymbolEffectAccessor* GetAppearSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIAppearSymbolEffectAccessor AppearSymbolEffectAccessorImpl {
            AppearSymbolEffectAccessor::DestroyPeerImpl,
            AppearSymbolEffectAccessor::CtorImpl,
            AppearSymbolEffectAccessor::GetFinalizerImpl,
            AppearSymbolEffectAccessor::GetScopeImpl,
            AppearSymbolEffectAccessor::SetScopeImpl,
        };
        return &AppearSymbolEffectAccessorImpl;
    }

    struct AppearSymbolEffectPeer {
        virtual ~AppearSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIDisappearSymbolEffectAccessor* GetDisappearSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIDisappearSymbolEffectAccessor DisappearSymbolEffectAccessorImpl {
            DisappearSymbolEffectAccessor::DestroyPeerImpl,
            DisappearSymbolEffectAccessor::CtorImpl,
            DisappearSymbolEffectAccessor::GetFinalizerImpl,
            DisappearSymbolEffectAccessor::GetScopeImpl,
            DisappearSymbolEffectAccessor::SetScopeImpl,
        };
        return &DisappearSymbolEffectAccessorImpl;
    }

    struct DisappearSymbolEffectPeer {
        virtual ~DisappearSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUIBounceSymbolEffectAccessor* GetBounceSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIBounceSymbolEffectAccessor BounceSymbolEffectAccessorImpl {
            BounceSymbolEffectAccessor::DestroyPeerImpl,
            BounceSymbolEffectAccessor::CtorImpl,
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
    const GENERATED_ArkUIPulseSymbolEffectAccessor* GetPulseSymbolEffectAccessor()
    {
        static const GENERATED_ArkUIPulseSymbolEffectAccessor PulseSymbolEffectAccessorImpl {
            PulseSymbolEffectAccessor::DestroyPeerImpl,
            PulseSymbolEffectAccessor::CtorImpl,
            PulseSymbolEffectAccessor::GetFinalizerImpl,
        };
        return &PulseSymbolEffectAccessorImpl;
    }

    struct PulseSymbolEffectPeer {
        virtual ~PulseSymbolEffectPeer() = default;
    };
    const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor()
    {
        static const GENERATED_ArkUITabsControllerAccessor TabsControllerAccessorImpl {
            TabsControllerAccessor::DestroyPeerImpl,
            TabsControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor()
    {
        static const GENERATED_ArkUITabContentTransitionProxyAccessor TabContentTransitionProxyAccessorImpl {
            TabContentTransitionProxyAccessor::DestroyPeerImpl,
            TabContentTransitionProxyAccessor::CtorImpl,
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
    const GENERATED_ArkUITextControllerAccessor* GetTextControllerAccessor()
    {
        static const GENERATED_ArkUITextControllerAccessor TextControllerAccessorImpl {
            TextControllerAccessor::DestroyPeerImpl,
            TextControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITextAreaControllerAccessor* GetTextAreaControllerAccessor()
    {
        static const GENERATED_ArkUITextAreaControllerAccessor TextAreaControllerAccessorImpl {
            TextAreaControllerAccessor::DestroyPeerImpl,
            TextAreaControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor()
    {
        static const GENERATED_ArkUITextClockControllerAccessor TextClockControllerAccessorImpl {
            TextClockControllerAccessor::DestroyPeerImpl,
            TextClockControllerAccessor::CtorImpl,
            TextClockControllerAccessor::GetFinalizerImpl,
            TextClockControllerAccessor::StartImpl,
            TextClockControllerAccessor::StopImpl,
        };
        return &TextClockControllerAccessorImpl;
    }

    struct TextClockControllerPeer {
        virtual ~TextClockControllerPeer() = default;
    };
    const GENERATED_ArkUITextBaseControllerAccessor* GetTextBaseControllerAccessor()
    {
        static const GENERATED_ArkUITextBaseControllerAccessor TextBaseControllerAccessorImpl {
            TextBaseControllerAccessor::DestroyPeerImpl,
            TextBaseControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITextEditControllerExAccessor* GetTextEditControllerExAccessor()
    {
        static const GENERATED_ArkUITextEditControllerExAccessor TextEditControllerExAccessorImpl {
            TextEditControllerExAccessor::DestroyPeerImpl,
            TextEditControllerExAccessor::CtorImpl,
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
    const GENERATED_ArkUIStyledStringControllerAccessor* GetStyledStringControllerAccessor()
    {
        static const GENERATED_ArkUIStyledStringControllerAccessor StyledStringControllerAccessorImpl {
            StyledStringControllerAccessor::DestroyPeerImpl,
            StyledStringControllerAccessor::CtorImpl,
            StyledStringControllerAccessor::GetFinalizerImpl,
            StyledStringControllerAccessor::SetStyledStringImpl,
            StyledStringControllerAccessor::GetStyledStringImpl,
        };
        return &StyledStringControllerAccessorImpl;
    }

    struct StyledStringControllerPeer {
        virtual ~StyledStringControllerPeer() = default;
    };
    const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
    {
        static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
            LayoutManagerAccessor::DestroyPeerImpl,
            LayoutManagerAccessor::CtorImpl,
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
    const GENERATED_ArkUITextMenuItemIdAccessor* GetTextMenuItemIdAccessor()
    {
        static const GENERATED_ArkUITextMenuItemIdAccessor TextMenuItemIdAccessorImpl {
            TextMenuItemIdAccessor::DestroyPeerImpl,
            TextMenuItemIdAccessor::CtorImpl,
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
        };
        return &TextMenuItemIdAccessorImpl;
    }

    struct TextMenuItemIdPeer {
        virtual ~TextMenuItemIdPeer() = default;
    };
    const GENERATED_ArkUIEditMenuOptionsAccessor* GetEditMenuOptionsAccessor()
    {
        static const GENERATED_ArkUIEditMenuOptionsAccessor EditMenuOptionsAccessorImpl {
            EditMenuOptionsAccessor::DestroyPeerImpl,
            EditMenuOptionsAccessor::CtorImpl,
            EditMenuOptionsAccessor::GetFinalizerImpl,
            EditMenuOptionsAccessor::OnCreateMenuImpl,
            EditMenuOptionsAccessor::OnMenuItemClickImpl,
        };
        return &EditMenuOptionsAccessorImpl;
    }

    struct EditMenuOptionsPeer {
        virtual ~EditMenuOptionsPeer() = default;
    };
    const GENERATED_ArkUISubmitEventAccessor* GetSubmitEventAccessor()
    {
        static const GENERATED_ArkUISubmitEventAccessor SubmitEventAccessorImpl {
            SubmitEventAccessor::DestroyPeerImpl,
            SubmitEventAccessor::CtorImpl,
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
    const GENERATED_ArkUITextInputControllerAccessor* GetTextInputControllerAccessor()
    {
        static const GENERATED_ArkUITextInputControllerAccessor TextInputControllerAccessorImpl {
            TextInputControllerAccessor::DestroyPeerImpl,
            TextInputControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITextPickerDialogAccessor* GetTextPickerDialogAccessor()
    {
        static const GENERATED_ArkUITextPickerDialogAccessor TextPickerDialogAccessorImpl {
            TextPickerDialogAccessor::ShowImpl,
        };
        return &TextPickerDialogAccessorImpl;
    }

    const GENERATED_ArkUITextTimerControllerAccessor* GetTextTimerControllerAccessor()
    {
        static const GENERATED_ArkUITextTimerControllerAccessor TextTimerControllerAccessorImpl {
            TextTimerControllerAccessor::DestroyPeerImpl,
            TextTimerControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor()
    {
        static const GENERATED_ArkUITimePickerDialogAccessor TimePickerDialogAccessorImpl {
            TimePickerDialogAccessor::ShowImpl,
        };
        return &TimePickerDialogAccessorImpl;
    }

    const GENERATED_ArkUIColorFilterAccessor* GetColorFilterAccessor()
    {
        static const GENERATED_ArkUIColorFilterAccessor ColorFilterAccessorImpl {
            ColorFilterAccessor::DestroyPeerImpl,
            ColorFilterAccessor::CtorImpl,
            ColorFilterAccessor::GetFinalizerImpl,
        };
        return &ColorFilterAccessorImpl;
    }

    struct ColorFilterPeer {
        virtual ~ColorFilterPeer() = default;
    };
    const GENERATED_ArkUIVideoControllerAccessor* GetVideoControllerAccessor()
    {
        static const GENERATED_ArkUIVideoControllerAccessor VideoControllerAccessorImpl {
            VideoControllerAccessor::DestroyPeerImpl,
            VideoControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUIWebKeyboardControllerAccessor* GetWebKeyboardControllerAccessor()
    {
        static const GENERATED_ArkUIWebKeyboardControllerAccessor WebKeyboardControllerAccessorImpl {
            WebKeyboardControllerAccessor::DestroyPeerImpl,
            WebKeyboardControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUIFullScreenExitHandlerAccessor* GetFullScreenExitHandlerAccessor()
    {
        static const GENERATED_ArkUIFullScreenExitHandlerAccessor FullScreenExitHandlerAccessorImpl {
            FullScreenExitHandlerAccessor::DestroyPeerImpl,
            FullScreenExitHandlerAccessor::CtorImpl,
            FullScreenExitHandlerAccessor::GetFinalizerImpl,
            FullScreenExitHandlerAccessor::ExitFullScreenImpl,
        };
        return &FullScreenExitHandlerAccessorImpl;
    }

    struct FullScreenExitHandlerPeer {
        virtual ~FullScreenExitHandlerPeer() = default;
    };
    const GENERATED_ArkUIFileSelectorParamAccessor* GetFileSelectorParamAccessor()
    {
        static const GENERATED_ArkUIFileSelectorParamAccessor FileSelectorParamAccessorImpl {
            FileSelectorParamAccessor::DestroyPeerImpl,
            FileSelectorParamAccessor::CtorImpl,
            FileSelectorParamAccessor::GetFinalizerImpl,
            FileSelectorParamAccessor::GetTitleImpl,
            FileSelectorParamAccessor::GetModeImpl,
            FileSelectorParamAccessor::GetAcceptTypeImpl,
            FileSelectorParamAccessor::IsCaptureImpl,
        };
        return &FileSelectorParamAccessorImpl;
    }

    struct FileSelectorParamPeer {
        virtual ~FileSelectorParamPeer() = default;
    };
    const GENERATED_ArkUIJsResultAccessor* GetJsResultAccessor()
    {
        static const GENERATED_ArkUIJsResultAccessor JsResultAccessorImpl {
            JsResultAccessor::DestroyPeerImpl,
            JsResultAccessor::CtorImpl,
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
    const GENERATED_ArkUIFileSelectorResultAccessor* GetFileSelectorResultAccessor()
    {
        static const GENERATED_ArkUIFileSelectorResultAccessor FileSelectorResultAccessorImpl {
            FileSelectorResultAccessor::DestroyPeerImpl,
            FileSelectorResultAccessor::CtorImpl,
            FileSelectorResultAccessor::GetFinalizerImpl,
            FileSelectorResultAccessor::HandleFileListImpl,
        };
        return &FileSelectorResultAccessorImpl;
    }

    struct FileSelectorResultPeer {
        virtual ~FileSelectorResultPeer() = default;
    };
    const GENERATED_ArkUIHttpAuthHandlerAccessor* GetHttpAuthHandlerAccessor()
    {
        static const GENERATED_ArkUIHttpAuthHandlerAccessor HttpAuthHandlerAccessorImpl {
            HttpAuthHandlerAccessor::DestroyPeerImpl,
            HttpAuthHandlerAccessor::CtorImpl,
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
    const GENERATED_ArkUISslErrorHandlerAccessor* GetSslErrorHandlerAccessor()
    {
        static const GENERATED_ArkUISslErrorHandlerAccessor SslErrorHandlerAccessorImpl {
            SslErrorHandlerAccessor::DestroyPeerImpl,
            SslErrorHandlerAccessor::CtorImpl,
            SslErrorHandlerAccessor::GetFinalizerImpl,
            SslErrorHandlerAccessor::HandleConfirmImpl,
            SslErrorHandlerAccessor::HandleCancelImpl,
        };
        return &SslErrorHandlerAccessorImpl;
    }

    struct SslErrorHandlerPeer {
        virtual ~SslErrorHandlerPeer() = default;
    };
    const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor()
    {
        static const GENERATED_ArkUIClientAuthenticationHandlerAccessor ClientAuthenticationHandlerAccessorImpl {
            ClientAuthenticationHandlerAccessor::DestroyPeerImpl,
            ClientAuthenticationHandlerAccessor::CtorImpl,
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
    const GENERATED_ArkUIPermissionRequestAccessor* GetPermissionRequestAccessor()
    {
        static const GENERATED_ArkUIPermissionRequestAccessor PermissionRequestAccessorImpl {
            PermissionRequestAccessor::DestroyPeerImpl,
            PermissionRequestAccessor::CtorImpl,
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
    const GENERATED_ArkUIScreenCaptureHandlerAccessor* GetScreenCaptureHandlerAccessor()
    {
        static const GENERATED_ArkUIScreenCaptureHandlerAccessor ScreenCaptureHandlerAccessorImpl {
            ScreenCaptureHandlerAccessor::DestroyPeerImpl,
            ScreenCaptureHandlerAccessor::CtorImpl,
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
    const GENERATED_ArkUIDataResubmissionHandlerAccessor* GetDataResubmissionHandlerAccessor()
    {
        static const GENERATED_ArkUIDataResubmissionHandlerAccessor DataResubmissionHandlerAccessorImpl {
            DataResubmissionHandlerAccessor::DestroyPeerImpl,
            DataResubmissionHandlerAccessor::CtorImpl,
            DataResubmissionHandlerAccessor::GetFinalizerImpl,
            DataResubmissionHandlerAccessor::ResendImpl,
            DataResubmissionHandlerAccessor::CancelImpl,
        };
        return &DataResubmissionHandlerAccessorImpl;
    }

    struct DataResubmissionHandlerPeer {
        virtual ~DataResubmissionHandlerPeer() = default;
    };
    const GENERATED_ArkUIControllerHandlerAccessor* GetControllerHandlerAccessor()
    {
        static const GENERATED_ArkUIControllerHandlerAccessor ControllerHandlerAccessorImpl {
            ControllerHandlerAccessor::DestroyPeerImpl,
            ControllerHandlerAccessor::CtorImpl,
            ControllerHandlerAccessor::GetFinalizerImpl,
            ControllerHandlerAccessor::SetWebControllerImpl,
        };
        return &ControllerHandlerAccessorImpl;
    }

    struct ControllerHandlerPeer {
        virtual ~ControllerHandlerPeer() = default;
    };
    const GENERATED_ArkUIWebContextMenuParamAccessor* GetWebContextMenuParamAccessor()
    {
        static const GENERATED_ArkUIWebContextMenuParamAccessor WebContextMenuParamAccessorImpl {
            WebContextMenuParamAccessor::DestroyPeerImpl,
            WebContextMenuParamAccessor::CtorImpl,
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
            WebContextMenuResultAccessor::CtorImpl,
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
    const GENERATED_ArkUIConsoleMessageAccessor* GetConsoleMessageAccessor()
    {
        static const GENERATED_ArkUIConsoleMessageAccessor ConsoleMessageAccessorImpl {
            ConsoleMessageAccessor::DestroyPeerImpl,
            ConsoleMessageAccessor::CtorImpl,
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
    const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor()
    {
        static const GENERATED_ArkUIWebResourceRequestAccessor WebResourceRequestAccessorImpl {
            WebResourceRequestAccessor::DestroyPeerImpl,
            WebResourceRequestAccessor::CtorImpl,
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
            WebResourceResponseAccessor::CtorImpl,
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
    const GENERATED_ArkUIWebResourceErrorAccessor* GetWebResourceErrorAccessor()
    {
        static const GENERATED_ArkUIWebResourceErrorAccessor WebResourceErrorAccessorImpl {
            WebResourceErrorAccessor::DestroyPeerImpl,
            WebResourceErrorAccessor::CtorImpl,
            WebResourceErrorAccessor::GetFinalizerImpl,
            WebResourceErrorAccessor::GetErrorInfoImpl,
            WebResourceErrorAccessor::GetErrorCodeImpl,
        };
        return &WebResourceErrorAccessorImpl;
    }

    struct WebResourceErrorPeer {
        virtual ~WebResourceErrorPeer() = default;
    };
    const GENERATED_ArkUIJsGeolocationAccessor* GetJsGeolocationAccessor()
    {
        static const GENERATED_ArkUIJsGeolocationAccessor JsGeolocationAccessorImpl {
            JsGeolocationAccessor::DestroyPeerImpl,
            JsGeolocationAccessor::CtorImpl,
            JsGeolocationAccessor::GetFinalizerImpl,
            JsGeolocationAccessor::InvokeImpl,
        };
        return &JsGeolocationAccessorImpl;
    }

    struct JsGeolocationPeer {
        virtual ~JsGeolocationPeer() = default;
    };
    const GENERATED_ArkUIWebCookieAccessor* GetWebCookieAccessor()
    {
        static const GENERATED_ArkUIWebCookieAccessor WebCookieAccessorImpl {
            WebCookieAccessor::DestroyPeerImpl,
            WebCookieAccessor::CtorImpl,
            WebCookieAccessor::GetFinalizerImpl,
            WebCookieAccessor::SetCookieImpl,
            WebCookieAccessor::SaveCookieImpl,
        };
        return &WebCookieAccessorImpl;
    }

    struct WebCookiePeer {
        virtual ~WebCookiePeer() = default;
    };
    const GENERATED_ArkUIEventResultAccessor* GetEventResultAccessor()
    {
        static const GENERATED_ArkUIEventResultAccessor EventResultAccessorImpl {
            EventResultAccessor::DestroyPeerImpl,
            EventResultAccessor::CtorImpl,
            EventResultAccessor::GetFinalizerImpl,
            EventResultAccessor::SetGestureEventResultImpl,
        };
        return &EventResultAccessorImpl;
    }

    struct EventResultPeer {
        virtual ~EventResultPeer() = default;
    };
    const GENERATED_ArkUIWebControllerAccessor* GetWebControllerAccessor()
    {
        static const GENERATED_ArkUIWebControllerAccessor WebControllerAccessorImpl {
            WebControllerAccessor::DestroyPeerImpl,
            WebControllerAccessor::CtorImpl,
            WebControllerAccessor::GetFinalizerImpl,
            WebControllerAccessor::OnInactiveImpl,
            WebControllerAccessor::OnActiveImpl,
            WebControllerAccessor::ZoomImpl,
            WebControllerAccessor::ClearHistoryImpl,
            WebControllerAccessor::RunJavaScriptImpl,
            WebControllerAccessor::LoadDataImpl,
            WebControllerAccessor::LoadUrlImpl,
            WebControllerAccessor::RefreshImpl,
            WebControllerAccessor::StopImpl,
            WebControllerAccessor::RegisterJavaScriptProxyImpl,
            WebControllerAccessor::DeleteJavaScriptRegisterImpl,
            WebControllerAccessor::GetHitTestImpl,
            WebControllerAccessor::RequestFocusImpl,
            WebControllerAccessor::AccessBackwardImpl,
            WebControllerAccessor::AccessForwardImpl,
            WebControllerAccessor::AccessStepImpl,
            WebControllerAccessor::BackwardImpl,
            WebControllerAccessor::ForwardImpl,
            WebControllerAccessor::GetCookieManagerImpl,
        };
        return &WebControllerAccessorImpl;
    }

    struct WebControllerPeer {
        virtual ~WebControllerPeer() = default;
    };
    const GENERATED_ArkUIXComponentControllerAccessor* GetXComponentControllerAccessor()
    {
        static const GENERATED_ArkUIXComponentControllerAccessor XComponentControllerAccessorImpl {
            XComponentControllerAccessor::DestroyPeerImpl,
            XComponentControllerAccessor::CtorImpl,
            XComponentControllerAccessor::GetFinalizerImpl,
            XComponentControllerAccessor::GetXComponentSurfaceIdImpl,
            XComponentControllerAccessor::GetXComponentContextImpl,
            XComponentControllerAccessor::SetXComponentSurfaceSizeImpl,
            XComponentControllerAccessor::SetXComponentSurfaceRectImpl,
            XComponentControllerAccessor::GetXComponentSurfaceRectImpl,
            XComponentControllerAccessor::SetXComponentSurfaceRotationImpl,
            XComponentControllerAccessor::GetXComponentSurfaceRotationImpl,
            XComponentControllerAccessor::OnSurfaceCreatedImpl,
            XComponentControllerAccessor::OnSurfaceChangedImpl,
            XComponentControllerAccessor::OnSurfaceDestroyedImpl,
            XComponentControllerAccessor::StartImageAnalyzerImpl,
            XComponentControllerAccessor::StopImageAnalyzerImpl,
        };
        return &XComponentControllerAccessorImpl;
    }

    struct XComponentControllerPeer {
        virtual ~XComponentControllerPeer() = default;
    };
    const GENERATED_ArkUIWaterFlowSectionsAccessor* GetWaterFlowSectionsAccessor()
    {
        static const GENERATED_ArkUIWaterFlowSectionsAccessor WaterFlowSectionsAccessorImpl {
            WaterFlowSectionsAccessor::DestroyPeerImpl,
            WaterFlowSectionsAccessor::CtorImpl,
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
    const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor()
    {
        static const GENERATED_ArkUIUIExtensionProxyAccessor UIExtensionProxyAccessorImpl {
            UIExtensionProxyAccessor::DestroyPeerImpl,
            UIExtensionProxyAccessor::CtorImpl,
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
    const GENERATED_ArkUIStyledStringAccessor* GetStyledStringAccessor()
    {
        static const GENERATED_ArkUIStyledStringAccessor StyledStringAccessorImpl {
            StyledStringAccessor::DestroyPeerImpl,
            StyledStringAccessor::CtorImpl,
            StyledStringAccessor::GetFinalizerImpl,
            StyledStringAccessor::GetStringImpl,
            StyledStringAccessor::GetStylesImpl,
            StyledStringAccessor::EqualsImpl,
            StyledStringAccessor::SubStyledStringImpl,
            StyledStringAccessor::FromHtmlImpl,
            StyledStringAccessor::ToHtmlImpl,
            StyledStringAccessor::MarshallingImpl,
            StyledStringAccessor::UnmarshallingImpl,
            StyledStringAccessor::GetLengthImpl,
        };
        return &StyledStringAccessorImpl;
    }

    struct StyledStringPeer {
        virtual ~StyledStringPeer() = default;
    };
    const GENERATED_ArkUITextStyle_styled_stringAccessor* GetTextStyle_styled_stringAccessor()
    {
        static const GENERATED_ArkUITextStyle_styled_stringAccessor TextStyle_styled_stringAccessorImpl {
            TextStyle_styled_stringAccessor::DestroyPeerImpl,
            TextStyle_styled_stringAccessor::CtorImpl,
            TextStyle_styled_stringAccessor::GetFinalizerImpl,
            TextStyle_styled_stringAccessor::GetFontColorImpl,
            TextStyle_styled_stringAccessor::GetFontFamilyImpl,
            TextStyle_styled_stringAccessor::GetFontSizeImpl,
            TextStyle_styled_stringAccessor::GetFontWeightImpl,
            TextStyle_styled_stringAccessor::GetFontStyleImpl,
        };
        return &TextStyle_styled_stringAccessorImpl;
    }

    struct TextStyle_styled_stringPeer {
        virtual ~TextStyle_styled_stringPeer() = default;
    };
    const GENERATED_ArkUIDecorationStyleAccessor* GetDecorationStyleAccessor()
    {
        static const GENERATED_ArkUIDecorationStyleAccessor DecorationStyleAccessorImpl {
            DecorationStyleAccessor::DestroyPeerImpl,
            DecorationStyleAccessor::CtorImpl,
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
    const GENERATED_ArkUIBaselineOffsetStyleAccessor* GetBaselineOffsetStyleAccessor()
    {
        static const GENERATED_ArkUIBaselineOffsetStyleAccessor BaselineOffsetStyleAccessorImpl {
            BaselineOffsetStyleAccessor::DestroyPeerImpl,
            BaselineOffsetStyleAccessor::CtorImpl,
            BaselineOffsetStyleAccessor::GetFinalizerImpl,
            BaselineOffsetStyleAccessor::GetBaselineOffsetImpl,
        };
        return &BaselineOffsetStyleAccessorImpl;
    }

    struct BaselineOffsetStylePeer {
        virtual ~BaselineOffsetStylePeer() = default;
    };
    const GENERATED_ArkUILetterSpacingStyleAccessor* GetLetterSpacingStyleAccessor()
    {
        static const GENERATED_ArkUILetterSpacingStyleAccessor LetterSpacingStyleAccessorImpl {
            LetterSpacingStyleAccessor::DestroyPeerImpl,
            LetterSpacingStyleAccessor::CtorImpl,
            LetterSpacingStyleAccessor::GetFinalizerImpl,
            LetterSpacingStyleAccessor::GetLetterSpacingImpl,
        };
        return &LetterSpacingStyleAccessorImpl;
    }

    struct LetterSpacingStylePeer {
        virtual ~LetterSpacingStylePeer() = default;
    };
    const GENERATED_ArkUITextShadowStyleAccessor* GetTextShadowStyleAccessor()
    {
        static const GENERATED_ArkUITextShadowStyleAccessor TextShadowStyleAccessorImpl {
            TextShadowStyleAccessor::DestroyPeerImpl,
            TextShadowStyleAccessor::CtorImpl,
            TextShadowStyleAccessor::GetFinalizerImpl,
            TextShadowStyleAccessor::GetTextShadowImpl,
        };
        return &TextShadowStyleAccessorImpl;
    }

    struct TextShadowStylePeer {
        virtual ~TextShadowStylePeer() = default;
    };
    const GENERATED_ArkUIBackgroundColorStyleAccessor* GetBackgroundColorStyleAccessor()
    {
        static const GENERATED_ArkUIBackgroundColorStyleAccessor BackgroundColorStyleAccessorImpl {
            BackgroundColorStyleAccessor::DestroyPeerImpl,
            BackgroundColorStyleAccessor::CtorImpl,
            BackgroundColorStyleAccessor::GetFinalizerImpl,
            BackgroundColorStyleAccessor::GetTextBackgroundStyleImpl,
        };
        return &BackgroundColorStyleAccessorImpl;
    }

    struct BackgroundColorStylePeer {
        virtual ~BackgroundColorStylePeer() = default;
    };
    const GENERATED_ArkUIGestureStyleAccessor* GetGestureStyleAccessor()
    {
        static const GENERATED_ArkUIGestureStyleAccessor GestureStyleAccessorImpl {
            GestureStyleAccessor::DestroyPeerImpl,
            GestureStyleAccessor::CtorImpl,
            GestureStyleAccessor::GetFinalizerImpl,
        };
        return &GestureStyleAccessorImpl;
    }

    struct GestureStylePeer {
        virtual ~GestureStylePeer() = default;
    };
    const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor()
    {
        static const GENERATED_ArkUIParagraphStyleAccessor ParagraphStyleAccessorImpl {
            ParagraphStyleAccessor::DestroyPeerImpl,
            ParagraphStyleAccessor::CtorImpl,
            ParagraphStyleAccessor::GetFinalizerImpl,
            ParagraphStyleAccessor::GetTextAlignImpl,
            ParagraphStyleAccessor::GetTextIndentImpl,
            ParagraphStyleAccessor::GetMaxLinesImpl,
            ParagraphStyleAccessor::GetOverflowImpl,
            ParagraphStyleAccessor::GetWordBreakImpl,
            ParagraphStyleAccessor::GetLeadingMarginImpl,
        };
        return &ParagraphStyleAccessorImpl;
    }

    struct ParagraphStylePeer {
        virtual ~ParagraphStylePeer() = default;
    };
    const GENERATED_ArkUILineHeightStyleAccessor* GetLineHeightStyleAccessor()
    {
        static const GENERATED_ArkUILineHeightStyleAccessor LineHeightStyleAccessorImpl {
            LineHeightStyleAccessor::DestroyPeerImpl,
            LineHeightStyleAccessor::CtorImpl,
            LineHeightStyleAccessor::GetFinalizerImpl,
            LineHeightStyleAccessor::GetLineHeightImpl,
        };
        return &LineHeightStyleAccessorImpl;
    }

    struct LineHeightStylePeer {
        virtual ~LineHeightStylePeer() = default;
    };
    const GENERATED_ArkUIUrlStyleAccessor* GetUrlStyleAccessor()
    {
        static const GENERATED_ArkUIUrlStyleAccessor UrlStyleAccessorImpl {
            UrlStyleAccessor::DestroyPeerImpl,
            UrlStyleAccessor::CtorImpl,
            UrlStyleAccessor::GetFinalizerImpl,
            UrlStyleAccessor::GetUrlImpl,
        };
        return &UrlStyleAccessorImpl;
    }

    struct UrlStylePeer {
        virtual ~UrlStylePeer() = default;
    };
    const GENERATED_ArkUIMutableStyledStringAccessor* GetMutableStyledStringAccessor()
    {
        static const GENERATED_ArkUIMutableStyledStringAccessor MutableStyledStringAccessorImpl {
            MutableStyledStringAccessor::DestroyPeerImpl,
            MutableStyledStringAccessor::CtorImpl,
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
    const GENERATED_ArkUIImageAttachmentAccessor* GetImageAttachmentAccessor()
    {
        static const GENERATED_ArkUIImageAttachmentAccessor ImageAttachmentAccessorImpl {
            ImageAttachmentAccessor::DestroyPeerImpl,
            ImageAttachmentAccessor::CtorImpl,
            ImageAttachmentAccessor::GetFinalizerImpl,
            ImageAttachmentAccessor::GetValueImpl,
            ImageAttachmentAccessor::GetSizeImpl,
            ImageAttachmentAccessor::GetVerticalAlignImpl,
            ImageAttachmentAccessor::GetObjectFitImpl,
            ImageAttachmentAccessor::GetLayoutStyleImpl,
        };
        return &ImageAttachmentAccessorImpl;
    }

    struct ImageAttachmentPeer {
        virtual ~ImageAttachmentPeer() = default;
    };
    const GENERATED_ArkUICustomSpanAccessor* GetCustomSpanAccessor()
    {
        static const GENERATED_ArkUICustomSpanAccessor CustomSpanAccessorImpl {
            CustomSpanAccessor::DestroyPeerImpl,
            CustomSpanAccessor::CtorImpl,
            CustomSpanAccessor::GetFinalizerImpl,
            CustomSpanAccessor::OnMeasureImpl,
            CustomSpanAccessor::OnDrawImpl,
            CustomSpanAccessor::InvalidateImpl,
        };
        return &CustomSpanAccessorImpl;
    }

    struct CustomSpanPeer {
        virtual ~CustomSpanPeer() = default;
    };
    const GENERATED_ArkUILinearIndicatorControllerAccessor* GetLinearIndicatorControllerAccessor()
    {
        static const GENERATED_ArkUILinearIndicatorControllerAccessor LinearIndicatorControllerAccessorImpl {
            LinearIndicatorControllerAccessor::DestroyPeerImpl,
            LinearIndicatorControllerAccessor::CtorImpl,
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
    const GENERATED_ArkUIGlobalScopeAccessor* GetGlobalScopeAccessor()
    {
        static const GENERATED_ArkUIGlobalScopeAccessor GlobalScopeAccessorImpl {
            GlobalScopeAccessor::GetContextImpl,
            GlobalScopeAccessor::PostCardActionImpl,
            GlobalScopeAccessor::Dollar_rImpl,
            GlobalScopeAccessor::Dollar_rawfileImpl,
            GlobalScopeAccessor::AnimateToImpl,
            GlobalScopeAccessor::AnimateToImmediatelyImpl,
            GlobalScopeAccessor::Vp2pxImpl,
            GlobalScopeAccessor::Px2vpImpl,
            GlobalScopeAccessor::Fp2pxImpl,
            GlobalScopeAccessor::Px2fpImpl,
            GlobalScopeAccessor::Lpx2pxImpl,
            GlobalScopeAccessor::Px2lpxImpl,
            GlobalScopeAccessor::GetInspectorNodesImpl,
            GlobalScopeAccessor::GetInspectorNodeByIdImpl,
            GlobalScopeAccessor::SetAppBgColorImpl,
            GlobalScopeAccessor::Profiler_registerVsyncCallbackImpl,
            GlobalScopeAccessor::Profiler_unregisterVsyncCallbackImpl,
            GlobalScopeAccessor::CursorControl_setCursorImpl,
            GlobalScopeAccessor::CursorControl_restoreDefaultImpl,
            GlobalScopeAccessor::FocusControl_requestFocusImpl,
        };
        return &GlobalScopeAccessorImpl;
    }

    struct GlobalScopePeer {
        virtual ~GlobalScopePeer() = default;
    };
    const GENERATED_ArkUIAccessors* GENERATED_GetArkUIAccessors()
    {
        static const GENERATED_ArkUIAccessors accessorsImpl = {
            GetAnimationExtenderAccessor,
            GetUnifiedDataAccessor,
            GetLazyForEachOpsAccessor,
            GetSystemOpsAccessor,
            GetFocusControllerAccessor,
            GetDrawableDescriptorAccessor,
            GetLayeredDrawableDescriptorAccessor,
            GetPixelMapDrawableDescriptorAccessor,
            GetAnimatedDrawableDescriptorAccessor,
            GetDrawingCanvasAccessor,
            GetLengthMetricsAccessor,
            GetColorMetricsAccessor,
            GetWebviewControllerAccessor,
            GetGlobalScope_ohos_arkui_componentSnapshotAccessor,
            GetGlobalScope_ohos_arkui_performanceMonitorAccessor,
            GetCommonShapeAccessor,
            GetBaseShapeAccessor,
            GetRectShapeAccessor,
            GetCircleShapeAccessor,
            GetEllipseShapeAccessor,
            GetPathShapeAccessor,
            GetGlobalScope_ohos_fontAccessor,
            GetGlobalScope_ohos_measure_utilsAccessor,
            GetSymbolEffectAccessor,
            GetScaleSymbolEffectAccessor,
            GetReplaceSymbolEffectAccessor,
            GetFrameNodeAccessor,
            GetPixelMapAccessor,
            GetNavExtenderAccessor,
            GetEventEmulatorAccessor,
            GetActionSheetAccessor,
            GetAlertDialogAccessor,
            GetSpringPropAccessor,
            GetSpringMotionAccessor,
            GetFrictionMotionAccessor,
            GetScrollMotionAccessor,
            GetCalendarControllerAccessor,
            GetCalendarPickerDialogAccessor,
            GetCanvasGradientAccessor,
            GetCanvasPathAccessor,
            GetPath2DAccessor,
            GetCanvasPatternAccessor,
            GetImageBitmapAccessor,
            GetImageDataAccessor,
            GetRenderingContextSettingsAccessor,
            GetCanvasRendererAccessor,
            GetCanvasRenderingContext2DAccessor,
            GetOffscreenCanvasRenderingContext2DAccessor,
            GetOffscreenCanvasAccessor,
            GetDrawingRenderingContextAccessor,
            GetICurveAccessor,
            GetDrawModifierAccessor,
            GetTransitionEffectAccessor,
            GetBaseEventAccessor,
            GetClickEventAccessor,
            GetHoverEventAccessor,
            GetMouseEventAccessor,
            GetAccessibilityHoverEventAccessor,
            GetTouchEventAccessor,
            GetPixelMapMockAccessor,
            GetDragEventAccessor,
            GetKeyEventAccessor,
            GetProgressMaskAccessor,
            GetMeasurableAccessor,
            GetViewAccessor,
            GetTextContentControllerBaseAccessor,
            GetChildrenMainSizeAccessor,
            GetUICommonEventAccessor,
            GetGestureModifierAccessor,
            GetContextMenuAccessor,
            GetCustomDialogControllerAccessor,
            GetLinearGradientAccessor,
            GetDatePickerDialogAccessor,
            GetBaseGestureEventAccessor,
            GetTapGestureEventAccessor,
            GetLongPressGestureEventAccessor,
            GetPanGestureEventAccessor,
            GetPinchGestureEventAccessor,
            GetRotationGestureEventAccessor,
            GetSwipeGestureEventAccessor,
            GetGestureEventAccessor,
            GetTapGestureInterfaceAccessor,
            GetLongPressGestureInterfaceAccessor,
            GetPanGestureOptionsAccessor,
            GetPanGestureInterfaceAccessor,
            GetSwipeGestureInterfaceAccessor,
            GetPinchGestureInterfaceAccessor,
            GetRotationGestureInterfaceAccessor,
            GetGestureGroupInterfaceAccessor,
            GetScrollableTargetInfoAccessor,
            GetEventTargetInfoAccessor,
            GetGestureRecognizerAccessor,
            GetPanRecognizerAccessor,
            GetImageAnalyzerControllerAccessor,
            GetListScrollerAccessor,
            GetMatrix2DAccessor,
            GetNavDestinationContextAccessor,
            GetNavPathInfoAccessor,
            GetNavPathStackAccessor,
            GetNavigationTransitionProxyAccessor,
            GetPatternLockControllerAccessor,
            GetRichEditorBaseControllerAccessor,
            GetRichEditorControllerAccessor,
            GetRichEditorStyledStringControllerAccessor,
            GetScrollerAccessor,
            GetSearchControllerAccessor,
            GetSwiperControllerAccessor,
            GetSwiperContentTransitionProxyAccessor,
            GetIndicatorComponentControllerAccessor,
            GetHierarchicalSymbolEffectAccessor,
            GetAppearSymbolEffectAccessor,
            GetDisappearSymbolEffectAccessor,
            GetBounceSymbolEffectAccessor,
            GetPulseSymbolEffectAccessor,
            GetTabsControllerAccessor,
            GetTabContentTransitionProxyAccessor,
            GetTextControllerAccessor,
            GetTextAreaControllerAccessor,
            GetTextClockControllerAccessor,
            GetTextBaseControllerAccessor,
            GetTextEditControllerExAccessor,
            GetStyledStringControllerAccessor,
            GetLayoutManagerAccessor,
            GetTextMenuItemIdAccessor,
            GetEditMenuOptionsAccessor,
            GetSubmitEventAccessor,
            GetTextInputControllerAccessor,
            GetTextPickerDialogAccessor,
            GetTextTimerControllerAccessor,
            GetTimePickerDialogAccessor,
            GetColorFilterAccessor,
            GetVideoControllerAccessor,
            GetWebKeyboardControllerAccessor,
            GetFullScreenExitHandlerAccessor,
            GetFileSelectorParamAccessor,
            GetJsResultAccessor,
            GetFileSelectorResultAccessor,
            GetHttpAuthHandlerAccessor,
            GetSslErrorHandlerAccessor,
            GetClientAuthenticationHandlerAccessor,
            GetPermissionRequestAccessor,
            GetScreenCaptureHandlerAccessor,
            GetDataResubmissionHandlerAccessor,
            GetControllerHandlerAccessor,
            GetWebContextMenuParamAccessor,
            GetWebContextMenuResultAccessor,
            GetConsoleMessageAccessor,
            GetWebResourceRequestAccessor,
            GetWebResourceResponseAccessor,
            GetWebResourceErrorAccessor,
            GetJsGeolocationAccessor,
            GetWebCookieAccessor,
            GetEventResultAccessor,
            GetWebControllerAccessor,
            GetXComponentControllerAccessor,
            GetWaterFlowSectionsAccessor,
            GetUIExtensionProxyAccessor,
            GetStyledStringAccessor,
            GetTextStyle_styled_stringAccessor,
            GetDecorationStyleAccessor,
            GetBaselineOffsetStyleAccessor,
            GetLetterSpacingStyleAccessor,
            GetTextShadowStyleAccessor,
            GetBackgroundColorStyleAccessor,
            GetGestureStyleAccessor,
            GetParagraphStyleAccessor,
            GetLineHeightStyleAccessor,
            GetUrlStyleAccessor,
            GetMutableStyledStringAccessor,
            GetImageAttachmentAccessor,
            GetCustomSpanAccessor,
            GetLinearIndicatorControllerAccessor,
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

    // TODO: remove me!
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

    EXTERN_C IDLIZE_API_EXPORT const GENERATED_ArkUIAnyAPI* GENERATED_GetArkAnyAPI(
        GENERATED_Ark_APIVariantKind kind, int version)
    {
        switch (kind) {
            case GENERATED_FULL:
                if (version == GENERATED_ARKUI_FULL_API_VERSION)   {
                    return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetFullAPI());
                }
                break;
            case GENERATED_BASIC:
                if (version == GENERATED_ARKUI_BASIC_NODE_API_VERSION)   {
                    return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetBasicAPI());
                }
                break;
            case GENERATED_EXTENDED:
                if (version == GENERATED_ARKUI_EXTENDED_NODE_API_VERSION)   {
                    return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GENERATED_GetExtendedAPI());
                }
                break;
            case GENERIC_SERVICE:
                if (version == GENERIC_SERVICE_API_VERSION)   {
                    return reinterpret_cast<const GENERATED_ArkUIAnyAPI*>(GetServiceAPI());
                }
                break;
            default:
                break;
        }
        return nullptr;
    }

}