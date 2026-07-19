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

#include "image_animator_case_runner.h"

#include <arkui/drawable_descriptor.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>

#include <memory>
#include <utility>

namespace ImageAnimatorCaseRunner {
namespace {
constexpr int32_t ATTRIBUTE_ITEM_SIZE = 1;
constexpr int32_t STRING_WIDTH = 96;
constexpr int32_t STRING_HEIGHT = 72;
constexpr int32_t STRING_TOP = 8;
constexpr int32_t STRING_LEFT = 12;
constexpr int32_t STRING_DURATION = 420;
constexpr int32_t UPDATE_WIDTH = 128;
constexpr int32_t UPDATE_HEIGHT = 88;
constexpr int32_t UPDATE_TOP = 18;
constexpr int32_t UPDATE_LEFT = 24;
constexpr int32_t UPDATE_DURATION = 640;
constexpr int32_t SINGLE_WIDTH = 33;
constexpr int32_t SINGLE_HEIGHT = 44;
constexpr int32_t SINGLE_TOP = 5;
constexpr int32_t SINGLE_LEFT = 6;
constexpr int32_t SINGLE_DURATION = 77;
constexpr int32_t PARTIAL_BASE_WIDTH = 200;
constexpr int32_t PARTIAL_BASE_HEIGHT = 160;
constexpr int32_t PARTIAL_BASE_TOP = 11;
constexpr int32_t PARTIAL_BASE_LEFT = 13;
constexpr int32_t PARTIAL_BASE_DURATION = 310;
constexpr int32_t PARTIAL_UPDATED_WIDTH = 240;
constexpr int32_t PARTIAL_UPDATED_TOP = 19;
constexpr int32_t PARTIAL_UPDATED_DURATION = 480;
constexpr int32_t NEGATIVE_WIDTH = -10;
constexpr int32_t NEGATIVE_HEIGHT = -20;
constexpr int32_t NEGATIVE_TOP = -3;
constexpr int32_t NEGATIVE_LEFT = -4;
constexpr int32_t NEGATIVE_DURATION = -100;
constexpr int32_t ZERO_VALUE = 0;
constexpr int32_t STRESS_FRAME_COUNT = 6;
constexpr int32_t STRESS_BASE_WIDTH = 40;
constexpr int32_t STRESS_BASE_HEIGHT = 50;
constexpr int32_t STRESS_BASE_TOP = 2;
constexpr int32_t STRESS_BASE_LEFT = 4;
constexpr int32_t STRESS_BASE_DURATION = 100;
constexpr int32_t STRESS_STEP = 7;
constexpr int32_t NODE_DURATION = 900;
constexpr int32_t NODE_ITERATION = 3;
constexpr int32_t BOOLEAN_TRUE = 1;
constexpr int32_t BOOLEAN_FALSE = 0;
constexpr int32_t INVALID_ATTRIBUTE_VALUE = -1;

struct FrameValues {
    int32_t width = 0;
    int32_t height = 0;
    int32_t top = 0;
    int32_t left = 0;
    int32_t duration = 0;
};

struct NativeNodeApiHolder {
    ArkUI_NativeNodeAPI_1* api = nullptr;
};

struct FieldCaseSpec {
    std::string field;
    FrameValues input;
    FrameValues expected;
};

struct StatusCaseSpec {
    std::string name;
    int32_t value = ARKUI_ANIMATION_STATUS_INITIAL;
};

using FramePtr = std::unique_ptr<ArkUI_ImageAnimatorFrameInfo, decltype(&OH_ArkUI_ImageAnimatorFrameInfo_Dispose)>;

NativeNodeApiHolder GetNodeApiHolder()
{
    NativeNodeApiHolder holder;
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, holder.api);
    return holder;
}

std::vector<char> MakeMutableCString(const std::string& value)
{
    std::vector<char> buffer(value.begin(), value.end());
    buffer.push_back('\0');
    return buffer;
}

FramePtr MakeFramePtr(ArkUI_ImageAnimatorFrameInfo* frame)
{
    return FramePtr(frame, OH_ArkUI_ImageAnimatorFrameInfo_Dispose);
}

FramePtr CreateStringFrame(const std::string& source, std::vector<char>& storage)
{
    storage = MakeMutableCString(source);
    return MakeFramePtr(OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(storage.data()));
}

void SetFrameValues(ArkUI_ImageAnimatorFrameInfo* frame, const FrameValues& values)
{
    OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(frame, values.width);
    OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(frame, values.height);
    OH_ArkUI_ImageAnimatorFrameInfo_SetTop(frame, values.top);
    OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(frame, values.left);
    OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(frame, values.duration);
}

FrameValues ReadFrameValues(ArkUI_ImageAnimatorFrameInfo* frame)
{
    FrameValues values;
    values.width = OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(frame);
    values.height = OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(frame);
    values.top = OH_ArkUI_ImageAnimatorFrameInfo_GetTop(frame);
    values.left = OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(frame);
    values.duration = OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(frame);
    return values;
}

void AddCheck(CaseResult& result, const std::string& name, int32_t expected, int32_t actual)
{
    MetricCheck check;
    check.name = name;
    check.expected = expected;
    check.actual = actual;
    check.passed = expected == actual;
    result.checks.emplace_back(check);
    result.passed = result.passed && check.passed;
}

CaseResult CreateCase(const std::string& group, const std::string& name, const std::string& api)
{
    CaseResult result;
    result.group = group;
    result.name = name;
    result.api = api;
    result.passed = true;
    return result;
}

void AddFrameValueChecks(CaseResult& result, const FrameValues& expected, const FrameValues& actual)
{
    AddCheck(result, "width", expected.width, actual.width);
    AddCheck(result, "height", expected.height, actual.height);
    AddCheck(result, "top", expected.top, actual.top);
    AddCheck(result, "left", expected.left, actual.left);
    AddCheck(result, "duration", expected.duration, actual.duration);
}

void AddConditionCheck(CaseResult& result, const std::string& name, bool condition)
{
    AddCheck(result, name, BOOLEAN_TRUE, condition ? BOOLEAN_TRUE : BOOLEAN_FALSE);
}

bool SetIntAttribute(
    ArkUI_NativeNodeAPI_1* api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, int32_t value)
{
    if (api == nullptr || node == nullptr) {
        return false;
    }
    ArkUI_NumberValue number[ATTRIBUTE_ITEM_SIZE] = {};
    number[0].i32 = value;
    ArkUI_AttributeItem item = {};
    item.value = number;
    item.size = ATTRIBUTE_ITEM_SIZE;
    return api->setAttribute(node, attribute, &item) == ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t GetIntAttribute(
    ArkUI_NativeNodeAPI_1* api, ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    if (api == nullptr || node == nullptr) {
        return INVALID_ATTRIBUTE_VALUE;
    }
    const ArkUI_AttributeItem* item = api->getAttribute(node, attribute);
    if (item == nullptr || item->value == nullptr || item->size <= 0) {
        return INVALID_ATTRIBUTE_VALUE;
    }
    return item->value[0].i32;
}

bool SetImagesAttribute(
    ArkUI_NativeNodeAPI_1* api, ArkUI_NodeHandle node, std::vector<ArkUI_ImageAnimatorFrameInfo*>& frames)
{
    if (api == nullptr || node == nullptr || frames.empty()) {
        return false;
    }
    ArkUI_AttributeItem item = {};
    item.object = frames.data();
    item.size = static_cast<int32_t>(frames.size());
    return api->setAttribute(node, NODE_IMAGE_ANIMATOR_IMAGES, &item) == ARKUI_ERROR_CODE_NO_ERROR;
}

CaseResult RunNullCreateCase()
{
    auto result = CreateCase(
        "creation", "null string source is rejected", "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString");
    auto* frame = OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(nullptr);
    AddConditionCheck(result, "frameIsNull", frame == nullptr);
    return result;
}

CaseResult RunNullDrawableCreateCase()
{
    auto result = CreateCase("creation", "null drawable is rejected",
        "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor");
    auto* frame = OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(nullptr);
    AddConditionCheck(result, "frameIsNull", frame == nullptr);
    return result;
}

CaseResult RunNullGetterCase()
{
    auto result = CreateCase("null safety", "getters return zero for null frame", "FrameInfo getters");
    FrameValues expected;
    FrameValues actual = ReadFrameValues(nullptr);
    AddFrameValueChecks(result, expected, actual);
    return result;
}

CaseResult RunNullSetterCase()
{
    auto result = CreateCase("null safety", "setters accept null frame", "FrameInfo setters");
    OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(nullptr, STRING_WIDTH);
    OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(nullptr, STRING_HEIGHT);
    OH_ArkUI_ImageAnimatorFrameInfo_SetTop(nullptr, STRING_TOP);
    OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(nullptr, STRING_LEFT);
    OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(nullptr, STRING_DURATION);
    AddCheck(result, "setterCallsCompleted", BOOLEAN_TRUE, BOOLEAN_TRUE);
    return result;
}

CaseResult RunStringFrameDefaultCase()
{
    auto result = CreateCase("creation", "string frame defaults are zero",
        "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/foreground.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    AddFrameValueChecks(result, FrameValues(), ReadFrameValues(frame.get()));
    return result;
}

CaseResult RunStringFrameSetGetCase()
{
    auto result = CreateCase("set get", "string frame stores all metrics", "FrameInfo setters/getters");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/background.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    FrameValues expected = { STRING_WIDTH, STRING_HEIGHT, STRING_TOP, STRING_LEFT, STRING_DURATION };
    SetFrameValues(frame.get(), expected);
    AddFrameValueChecks(result, expected, ReadFrameValues(frame.get()));
    return result;
}

CaseResult RunStringFrameOverwriteCase()
{
    auto result = CreateCase("set get", "later metric writes replace earlier values", "FrameInfo setters");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/startIcon.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    SetFrameValues(frame.get(), { STRING_WIDTH, STRING_HEIGHT, STRING_TOP, STRING_LEFT, STRING_DURATION });
    FrameValues expected = { UPDATE_WIDTH, UPDATE_HEIGHT, UPDATE_TOP, UPDATE_LEFT, UPDATE_DURATION };
    SetFrameValues(frame.get(), expected);
    AddFrameValueChecks(result, expected, ReadFrameValues(frame.get()));
    return result;
}

CaseResult RunEmptyStringFrameCase()
{
    auto result = CreateCase("creation", "empty string source creates a frame",
        "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString");
    std::vector<char> storage;
    auto frame = CreateStringFrame("", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    AddFrameValueChecks(result, FrameValues(), ReadFrameValues(frame.get()));
    return result;
}

std::vector<FieldCaseSpec> BuildSingleFieldSpecs()
{
    return {
        { "width", { SINGLE_WIDTH, 0, 0, 0, 0 }, { SINGLE_WIDTH, 0, 0, 0, 0 } },
        { "height", { 0, SINGLE_HEIGHT, 0, 0, 0 }, { 0, SINGLE_HEIGHT, 0, 0, 0 } },
        { "top", { 0, 0, SINGLE_TOP, 0, 0 }, { 0, 0, SINGLE_TOP, 0, 0 } },
        { "left", { 0, 0, 0, SINGLE_LEFT, 0 }, { 0, 0, 0, SINGLE_LEFT, 0 } },
        { "duration", { 0, 0, 0, 0, SINGLE_DURATION }, { 0, 0, 0, 0, SINGLE_DURATION } },
    };
}

CaseResult RunSingleFieldIsolationCase()
{
    auto result = CreateCase("set get", "each setter updates only its own metric", "FrameInfo setters/getters");
    for (const auto& spec : BuildSingleFieldSpecs()) {
        std::vector<char> storage;
        auto frame = CreateStringFrame("resource://media/foreground.png", storage);
        SetFrameValues(frame.get(), spec.input);
        AddFrameValueChecks(result, spec.expected, ReadFrameValues(frame.get()));
        AddConditionCheck(result, spec.field + "FrameCreated", frame != nullptr);
    }
    return result;
}

FrameValues BuildPartialBaseValues()
{
    FrameValues values;
    values.width = PARTIAL_BASE_WIDTH;
    values.height = PARTIAL_BASE_HEIGHT;
    values.top = PARTIAL_BASE_TOP;
    values.left = PARTIAL_BASE_LEFT;
    values.duration = PARTIAL_BASE_DURATION;
    return values;
}

FrameValues BuildPartialExpectedValues()
{
    FrameValues values = BuildPartialBaseValues();
    values.width = PARTIAL_UPDATED_WIDTH;
    values.top = PARTIAL_UPDATED_TOP;
    values.duration = PARTIAL_UPDATED_DURATION;
    return values;
}

CaseResult RunPartialUpdateCase()
{
    auto result = CreateCase("set get", "partial setter updates preserve other metrics", "FrameInfo setters");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/startIcon.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    SetFrameValues(frame.get(), BuildPartialBaseValues());
    OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(frame.get(), PARTIAL_UPDATED_WIDTH);
    OH_ArkUI_ImageAnimatorFrameInfo_SetTop(frame.get(), PARTIAL_UPDATED_TOP);
    OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(frame.get(), PARTIAL_UPDATED_DURATION);
    AddFrameValueChecks(result, BuildPartialExpectedValues(), ReadFrameValues(frame.get()));
    return result;
}

CaseResult RunDisposeNullCase()
{
    auto result = CreateCase("null safety", "dispose accepts null frame",
        "OH_ArkUI_ImageAnimatorFrameInfo_Dispose");
    OH_ArkUI_ImageAnimatorFrameInfo_Dispose(nullptr);
    AddCheck(result, "disposeNullCompleted", BOOLEAN_TRUE, BOOLEAN_TRUE);
    return result;
}

CaseResult RunZeroMetricCase()
{
    auto result = CreateCase("edge values", "zero metrics remain observable", "FrameInfo setters/getters");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/foreground.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    FrameValues expected = { ZERO_VALUE, ZERO_VALUE, ZERO_VALUE, ZERO_VALUE, ZERO_VALUE };
    SetFrameValues(frame.get(), expected);
    AddFrameValueChecks(result, expected, ReadFrameValues(frame.get()));
    return result;
}

CaseResult RunNegativeMetricCase()
{
    auto result = CreateCase("edge values", "negative metrics are stored as provided", "FrameInfo setters/getters");
    std::vector<char> storage;
    auto frame = CreateStringFrame("resource://media/background.png", storage);
    AddConditionCheck(result, "frameCreated", frame != nullptr);
    FrameValues expected = {
        NEGATIVE_WIDTH, NEGATIVE_HEIGHT, NEGATIVE_TOP, NEGATIVE_LEFT, NEGATIVE_DURATION,
    };
    SetFrameValues(frame.get(), expected);
    AddFrameValueChecks(result, expected, ReadFrameValues(frame.get()));
    return result;
}

FrameValues BuildStressValues(int32_t index)
{
    FrameValues values;
    values.width = STRESS_BASE_WIDTH + index * STRESS_STEP;
    values.height = STRESS_BASE_HEIGHT + index * STRESS_STEP;
    values.top = STRESS_BASE_TOP + index;
    values.left = STRESS_BASE_LEFT + index;
    values.duration = STRESS_BASE_DURATION + index * STRESS_STEP;
    return values;
}

CaseResult RunStressFrameCase()
{
    auto result = CreateCase("batch", "multiple frames keep independent values", "FrameInfo setters/getters");
    std::vector<std::vector<char>> storages;
    std::vector<FramePtr> frames;
    for (int32_t index = 0; index < STRESS_FRAME_COUNT; ++index) {
        storages.emplace_back();
        auto frame = CreateStringFrame("resource://media/foreground.png", storages.back());
        SetFrameValues(frame.get(), BuildStressValues(index));
        frames.emplace_back(std::move(frame));
    }
    for (int32_t index = 0; index < STRESS_FRAME_COUNT; ++index) {
        AddFrameValueChecks(result, BuildStressValues(index), ReadFrameValues(frames[index].get()));
    }
    return result;
}

CaseResult RunImageAttributeCase(ArkUI_NativeNodeAPI_1* api)
{
    auto result = CreateCase("node attribute", "frames can be assigned to image animator node",
        "NODE_IMAGE_ANIMATOR_IMAGES");
    if (api == nullptr) {
        result.passed = false;
        result.note = "Native node API is unavailable.";
        return result;
    }
    auto node = api->createNode(ARKUI_NODE_IMAGE_ANIMATOR);
    AddConditionCheck(result, "nodeCreated", node != nullptr);
    if (node == nullptr) {
        return result;
    }
    std::vector<std::vector<char>> storages(2);
    auto firstFrame = CreateStringFrame("resource://media/foreground.png", storages[0]);
    auto secondFrame = CreateStringFrame("resource://media/background.png", storages[1]);
    std::vector<ArkUI_ImageAnimatorFrameInfo*> frames = { firstFrame.get(), secondFrame.get() };
    bool imagesSet = SetImagesAttribute(api, node, frames);
    AddCheck(result, "setImages", BOOLEAN_TRUE, imagesSet ? BOOLEAN_TRUE : BOOLEAN_FALSE);
    const ArkUI_AttributeItem* item = api->getAttribute(node, NODE_IMAGE_ANIMATOR_IMAGES);
    AddConditionCheck(result, "imagesAttributeReadable", item != nullptr);
    AddCheck(result, "imageCount", static_cast<int32_t>(frames.size()), item == nullptr ? 0 : item->size);
    api->disposeNode(node);
    return result;
}

std::vector<StatusCaseSpec> BuildAnimationStatusSpecs()
{
    return {
        { "initial", ARKUI_ANIMATION_STATUS_INITIAL },
        { "running", ARKUI_ANIMATION_STATUS_RUNNING },
        { "paused", ARKUI_ANIMATION_STATUS_PAUSED },
        { "stopped", ARKUI_ANIMATION_STATUS_STOPPED },
    };
}

CaseResult RunAnimatorStateAttributeCase(ArkUI_NativeNodeAPI_1* api)
{
    auto result = CreateCase("node attribute", "animator state accepts enum values", "NODE_IMAGE_ANIMATOR_STATE");
    if (api == nullptr) {
        result.passed = false;
        result.note = "Native node API is unavailable.";
        return result;
    }
    auto node = api->createNode(ARKUI_NODE_IMAGE_ANIMATOR);
    AddConditionCheck(result, "nodeCreated", node != nullptr);
    if (node == nullptr) {
        return result;
    }
    for (const auto& status : BuildAnimationStatusSpecs()) {
        bool statusSet = SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_STATE, status.value);
        AddCheck(result, status.name + "Set", BOOLEAN_TRUE, statusSet ? BOOLEAN_TRUE : BOOLEAN_FALSE);
        AddCheck(result, status.name + "State", status.value, GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_STATE));
    }
    api->disposeNode(node);
    return result;
}

CaseResult RunAnimatorOptionAttributeCase(ArkUI_NativeNodeAPI_1* api)
{
    auto result = CreateCase("node attribute", "animator numeric options round trip", "NODE_IMAGE_ANIMATOR_* ");
    if (api == nullptr) {
        result.passed = false;
        result.note = "Native node API is unavailable.";
        return result;
    }
    auto node = api->createNode(ARKUI_NODE_IMAGE_ANIMATOR);
    AddConditionCheck(result, "nodeCreated", node != nullptr);
    if (node == nullptr) {
        return result;
    }
    AddCheck(result, "setDuration", BOOLEAN_TRUE,
        SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_DURATION, NODE_DURATION) ? BOOLEAN_TRUE : BOOLEAN_FALSE);
    AddCheck(result, "setReverse", BOOLEAN_TRUE,
        SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_REVERSE, BOOLEAN_TRUE) ? BOOLEAN_TRUE : BOOLEAN_FALSE);
    AddCheck(result, "setFixedSize", BOOLEAN_TRUE,
        SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_FIXED_SIZE, BOOLEAN_FALSE) ? BOOLEAN_TRUE : BOOLEAN_FALSE);
    AddCheck(result, "setFillMode", BOOLEAN_TRUE,
        SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_FILL_MODE, ARKUI_ANIMATION_FILL_MODE_BOTH) ?
            BOOLEAN_TRUE : BOOLEAN_FALSE);
    AddCheck(result, "setIteration", BOOLEAN_TRUE,
        SetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_ITERATION, NODE_ITERATION) ? BOOLEAN_TRUE : BOOLEAN_FALSE);
    AddCheck(result, "duration", NODE_DURATION, GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_DURATION));
    AddCheck(result, "reverse", BOOLEAN_TRUE, GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_REVERSE));
    AddCheck(result, "fixedSize", BOOLEAN_FALSE, GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_FIXED_SIZE));
    AddCheck(result, "fillMode", ARKUI_ANIMATION_FILL_MODE_BOTH,
        GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_FILL_MODE));
    AddCheck(result, "iteration", NODE_ITERATION, GetIntAttribute(api, node, NODE_IMAGE_ANIMATOR_ITERATION));
    api->disposeNode(node);
    return result;
}

void AddCase(CaseReport& report, CaseResult&& result)
{
    report.totalCases += 1;
    report.totalChecks += static_cast<int32_t>(result.checks.size());
    for (const auto& check : result.checks) {
        report.passedChecks += check.passed ? 1 : 0;
    }
    report.failedChecks = report.totalChecks - report.passedChecks;
    report.passedCases += result.passed ? 1 : 0;
    report.failedCases = report.totalCases - report.passedCases;
    report.cases.emplace_back(std::move(result));
}
} // namespace

CaseReport RunImageAnimatorFrameInfoCases()
{
    CaseReport report;
    auto apiHolder = GetNodeApiHolder();
    report.nodeApiAvailable = apiHolder.api != nullptr;
    AddCase(report, RunNullCreateCase());
    AddCase(report, RunNullDrawableCreateCase());
    AddCase(report, RunNullGetterCase());
    AddCase(report, RunNullSetterCase());
    AddCase(report, RunStringFrameDefaultCase());
    AddCase(report, RunStringFrameSetGetCase());
    AddCase(report, RunStringFrameOverwriteCase());
    AddCase(report, RunEmptyStringFrameCase());
    AddCase(report, RunSingleFieldIsolationCase());
    AddCase(report, RunPartialUpdateCase());
    AddCase(report, RunDisposeNullCase());
    AddCase(report, RunZeroMetricCase());
    AddCase(report, RunNegativeMetricCase());
    AddCase(report, RunStressFrameCase());
    AddCase(report, RunImageAttributeCase(apiHolder.api));
    AddCase(report, RunAnimatorStateAttributeCase(apiHolder.api));
    AddCase(report, RunAnimatorOptionAttributeCase(apiHolder.api));
    return report;
}
} // namespace ImageAnimatorCaseRunner
