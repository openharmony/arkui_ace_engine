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

#include "napi/native_api.h"

#include "image_animator_case_runner.h"

#include <arkui/drawable_descriptor.h>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {
constexpr int32_t TARGET_ON_START = 1;
constexpr int32_t TARGET_ON_PAUSE = 2;
constexpr int32_t TARGET_ON_REPEAT = 3;
constexpr int32_t TARGET_ON_CANCEL = 4;
constexpr int32_t TARGET_ON_FINISH = 5;
constexpr int32_t ATTRIBUTE_ITEM_SIZE = 1;
constexpr int32_t DEFAULT_ANIMATOR_WIDTH = 220;
constexpr int32_t DEFAULT_ANIMATOR_HEIGHT = 180;
constexpr int32_t DEFAULT_FRAME_WIDTH = 160;
constexpr int32_t DEFAULT_FRAME_HEIGHT = 130;
constexpr int32_t DEFAULT_FRAME_LEFT = 30;
constexpr int32_t DEFAULT_FRAME_TOP = 20;
constexpr int32_t DEFAULT_DURATION = 1200;
constexpr int32_t COVERAGE_DURATION = 1500;
constexpr int32_t DEFAULT_REVERSE = 0;
constexpr int32_t DEFAULT_FIXED_SIZE = 0;
constexpr int32_t DEFAULT_ITERATION = -1;
constexpr int32_t COVERAGE_ITERATION = 2;
constexpr int32_t BOOLEAN_TRUE = 1;
constexpr int32_t BOOLEAN_FALSE = 0;
constexpr int32_t INVALID_ATTRIBUTE_VALUE = -1;
constexpr int32_t COVERAGE_FRAME_LEFT = 1;
constexpr int32_t COVERAGE_FRAME_TOP = 2;
constexpr int32_t COVERAGE_FRAME_WIDTH = 3;
constexpr int32_t COVERAGE_FRAME_HEIGHT = 4;
constexpr int32_t COVERAGE_FRAME_DURATION = 5;
constexpr int32_t MODULE_VERSION = 1;
constexpr std::array<int32_t, 3> FRAME_DURATIONS = { 300, 420, 540 };

struct EventCounters {
    int32_t onStart = 0;
    int32_t onPause = 0;
    int32_t onRepeat = 0;
    int32_t onCancel = 0;
    int32_t onFinish = 0;
};

struct FrameSpec {
    int32_t left = DEFAULT_FRAME_LEFT;
    int32_t top = DEFAULT_FRAME_TOP;
    int32_t width = DEFAULT_FRAME_WIDTH;
    int32_t height = DEFAULT_FRAME_HEIGHT;
    int32_t duration = FRAME_DURATIONS.front();
};

struct AnimatorOptions {
    std::vector<std::string> sources;
    napi_value resourceArray = nullptr;
};

struct EventRegistration {
    ArkUI_NodeEventType eventType;
    int32_t targetId;
    const char* coverageName;
};

struct AttributeCheck {
    ArkUI_NodeAttributeType attribute;
    int32_t value;
    const char* coverageName;
};

struct ImageAnimatorSample {
    ArkUI_NodeContentHandle content = nullptr;
    ArkUI_NodeHandle animatorNode = nullptr;
    std::vector<std::vector<char>> sourceBuffers;
    std::vector<ArkUI_DrawableDescriptor*> drawables;
    std::vector<ArkUI_ImageAnimatorFrameInfo*> frames;
    EventCounters events;
    int32_t lastEventTargetId = 0;
};

constexpr std::array<EventRegistration, 5> EVENT_REGISTRATIONS = {{
    { NODE_IMAGE_ANIMATOR_EVENT_ON_START, TARGET_ON_START, "NODE_IMAGE_ANIMATOR_EVENT_ON_START" },
    { NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE, TARGET_ON_PAUSE, "NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE" },
    { NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT, TARGET_ON_REPEAT, "NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT" },
    { NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL, TARGET_ON_CANCEL, "NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL" },
    { NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH, TARGET_ON_FINISH, "NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH" },
}};

constexpr std::array<AttributeCheck, 6> ATTRIBUTE_CHECKS = {{
    { NODE_IMAGE_ANIMATOR_STATE, ARKUI_ANIMATION_STATUS_PAUSED,
        "NODE_IMAGE_ANIMATOR_STATE set/get/reset" },
    { NODE_IMAGE_ANIMATOR_DURATION, COVERAGE_DURATION,
        "NODE_IMAGE_ANIMATOR_DURATION set/get/reset" },
    { NODE_IMAGE_ANIMATOR_REVERSE, BOOLEAN_TRUE,
        "NODE_IMAGE_ANIMATOR_REVERSE set/get/reset" },
    { NODE_IMAGE_ANIMATOR_FIXED_SIZE, BOOLEAN_FALSE,
        "NODE_IMAGE_ANIMATOR_FIXED_SIZE set/get/reset" },
    { NODE_IMAGE_ANIMATOR_FILL_MODE, ARKUI_ANIMATION_FILL_MODE_BOTH,
        "NODE_IMAGE_ANIMATOR_FILL_MODE set/get/reset" },
    { NODE_IMAGE_ANIMATOR_ITERATION, COVERAGE_ITERATION,
        "NODE_IMAGE_ANIMATOR_ITERATION set/get/reset" },
}};

ArkUI_NativeNodeAPI_1* g_nodeApi = nullptr;

ArkUI_NativeNodeAPI_1* GetNodeApi()
{
    if (g_nodeApi != nullptr) {
        return g_nodeApi;
    }
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, g_nodeApi);
    return g_nodeApi;
}

std::vector<std::string> BuildDefaultFrameSources()
{
    return {
        "resource://media/foreground.png",
        "resource://media/background.png",
        "resource://media/startIcon.png",
    };
}

void IncreaseEventCounter(ImageAnimatorSample* sample, ArkUI_NodeEventType eventType)
{
    switch (eventType) {
        case NODE_IMAGE_ANIMATOR_EVENT_ON_START:
            sample->events.onStart += 1;
            break;
        case NODE_IMAGE_ANIMATOR_EVENT_ON_PAUSE:
            sample->events.onPause += 1;
            break;
        case NODE_IMAGE_ANIMATOR_EVENT_ON_REPEAT:
            sample->events.onRepeat += 1;
            break;
        case NODE_IMAGE_ANIMATOR_EVENT_ON_CANCEL:
            sample->events.onCancel += 1;
            break;
        case NODE_IMAGE_ANIMATOR_EVENT_ON_FINISH:
            sample->events.onFinish += 1;
            break;
        default:
            break;
    }
}

void EventReceiver(ArkUI_NodeEvent* event)
{
    auto* sample = static_cast<ImageAnimatorSample*>(OH_ArkUI_NodeEvent_GetUserData(event));
    if (sample == nullptr) {
        return;
    }

    sample->lastEventTargetId = OH_ArkUI_NodeEvent_GetTargetId(event);
    IncreaseEventCounter(sample, OH_ArkUI_NodeEvent_GetEventType(event));
}

std::string GetStringArg(napi_env env, napi_value value)
{
    size_t length = 0;
    napi_get_value_string_utf8(env, value, nullptr, 0, &length);
    std::string result(length + 1, '\0');
    size_t copied = 0;
    napi_get_value_string_utf8(env, value, &result[0], result.size(), &copied);
    result.resize(copied);
    return result;
}

int32_t GetInt32Arg(napi_env env, napi_value value, int32_t fallback)
{
    int32_t result = fallback;
    napi_get_value_int32(env, value, &result);
    return result;
}

void ThrowError(napi_env env, const std::string& message)
{
    napi_throw_error(env, nullptr, message.c_str());
}

napi_value CreateUndefined(napi_env env)
{
    napi_value value = nullptr;
    napi_get_undefined(env, &value);
    return value;
}

napi_value CreateBool(napi_env env, bool input)
{
    napi_value value = nullptr;
    napi_get_boolean(env, input, &value);
    return value;
}

napi_value CreateInt32(napi_env env, int32_t input)
{
    napi_value value = nullptr;
    napi_create_int32(env, input, &value);
    return value;
}

napi_value CreateString(napi_env env, const std::string& input)
{
    napi_value value = nullptr;
    napi_create_string_utf8(env, input.c_str(), input.size(), &value);
    return value;
}

void SetNamedBool(napi_env env, napi_value object, const char* name, bool value)
{
    napi_set_named_property(env, object, name, CreateBool(env, value));
}

void SetNamedInt(napi_env env, napi_value object, const char* name, int32_t value)
{
    napi_set_named_property(env, object, name, CreateInt32(env, value));
}

void SetNamedString(napi_env env, napi_value object, const char* name, const std::string& value)
{
    napi_set_named_property(env, object, name, CreateString(env, value));
}

void SetNamedValue(napi_env env, napi_value object, const char* name, napi_value value)
{
    napi_set_named_property(env, object, name, value);
}

void AddText(std::vector<std::string>& items, const std::string& name, bool ok)
{
    items.emplace_back(name + (ok ? ": OK" : ": FAILED"));
}

bool SetIntAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, int32_t value)
{
    auto* api = GetNodeApi();
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

bool SetFloatAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, float value)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr) {
        return false;
    }

    ArkUI_NumberValue number[ATTRIBUTE_ITEM_SIZE] = {};
    number[0].f32 = value;
    ArkUI_AttributeItem item = {};
    item.value = number;
    item.size = ATTRIBUTE_ITEM_SIZE;
    return api->setAttribute(node, attribute, &item) == ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t GetIntAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute, int32_t fallback)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr) {
        return fallback;
    }

    const ArkUI_AttributeItem* item = api->getAttribute(node, attribute);
    if (item == nullptr || item->value == nullptr || item->size <= 0) {
        return fallback;
    }
    return item->value[0].i32;
}

bool ResetAttribute(ArkUI_NodeHandle node, ArkUI_NodeAttributeType attribute)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr) {
        return false;
    }
    return api->resetAttribute(node, attribute) == ARKUI_ERROR_CODE_NO_ERROR;
}

bool GetNamedPropertyIfExists(napi_env env, napi_value object, const char* name, napi_value* value)
{
    bool exists = false;
    if (napi_has_named_property(env, object, name, &exists) != napi_ok || !exists) {
        return false;
    }
    return napi_get_named_property(env, object, name, value) == napi_ok;
}

bool IsObject(napi_env env, napi_value value)
{
    napi_valuetype type = napi_undefined;
    napi_typeof(env, value, &type);
    return type == napi_object;
}

std::vector<char> MakeMutableCString(const std::string& value)
{
    std::vector<char> buffer(value.begin(), value.end());
    buffer.push_back('\0');
    return buffer;
}

FrameSpec BuildDefaultFrameSpec(size_t index)
{
    FrameSpec spec;
    spec.duration = FRAME_DURATIONS[index % FRAME_DURATIONS.size()];
    return spec;
}

void ApplyFrameSpec(ArkUI_ImageAnimatorFrameInfo* frame, const FrameSpec& spec)
{
    OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(frame, spec.left);
    OH_ArkUI_ImageAnimatorFrameInfo_SetTop(frame, spec.top);
    OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(frame, spec.width);
    OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(frame, spec.height);
    OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(frame, spec.duration);
}

ArkUI_ImageAnimatorFrameInfo* CreateFrameFromStringBuffer(
    std::vector<char>& source, const FrameSpec& spec)
{
    auto* frame = OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(source.data());
    if (frame == nullptr) {
        return nullptr;
    }
    ApplyFrameSpec(frame, spec);
    return frame;
}

ArkUI_ImageAnimatorFrameInfo* CreateFrameFromDrawable(
    ArkUI_DrawableDescriptor* drawable, const FrameSpec& spec)
{
    auto* frame = OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(drawable);
    if (frame == nullptr) {
        return nullptr;
    }
    ApplyFrameSpec(frame, spec);
    return frame;
}

bool SetImagesAttribute(ArkUI_NodeHandle node, std::vector<ArkUI_ImageAnimatorFrameInfo*>& frames)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr || frames.empty()) {
        return false;
    }

    ArkUI_AttributeItem item = {};
    item.size = static_cast<int32_t>(frames.size());
    item.object = frames.data();
    return api->setAttribute(node, NODE_IMAGE_ANIMATOR_IMAGES, &item) == ARKUI_ERROR_CODE_NO_ERROR;
}

std::vector<std::string> ReadSourcesFromOptions(napi_env env, napi_value options)
{
    napi_value arrayValue = nullptr;
    if (!GetNamedPropertyIfExists(env, options, "sources", &arrayValue)) {
        return BuildDefaultFrameSources();
    }

    bool isArray = false;
    napi_is_array(env, arrayValue, &isArray);
    if (!isArray) {
        return BuildDefaultFrameSources();
    }

    std::vector<std::string> sources;
    uint32_t length = 0;
    napi_get_array_length(env, arrayValue, &length);
    for (uint32_t index = 0; index < length; ++index) {
        napi_value sourceValue = nullptr;
        napi_get_element(env, arrayValue, index, &sourceValue);
        napi_valuetype type = napi_undefined;
        napi_typeof(env, sourceValue, &type);
        if (type == napi_string) {
            sources.push_back(GetStringArg(env, sourceValue));
        }
    }
    return sources.empty() ? BuildDefaultFrameSources() : sources;
}

AnimatorOptions ReadAnimatorOptions(napi_env env, napi_value options)
{
    AnimatorOptions result;
    result.sources = BuildDefaultFrameSources();
    if (env == nullptr || options == nullptr || !IsObject(env, options)) {
        return result;
    }

    result.sources = ReadSourcesFromOptions(env, options);
    napi_value resources = nullptr;
    if (GetNamedPropertyIfExists(env, options, "resources", &resources)) {
        result.resourceArray = resources;
    }
    return result;
}

void AppendStringFrames(ImageAnimatorSample& sample, const std::vector<std::string>& sources)
{
    for (size_t index = 0; index < sources.size(); ++index) {
        sample.sourceBuffers.push_back(MakeMutableCString(sources[index]));
        auto* frame = CreateFrameFromStringBuffer(sample.sourceBuffers.back(), BuildDefaultFrameSpec(index));
        if (frame != nullptr) {
            sample.frames.push_back(frame);
            continue;
        }
        sample.sourceBuffers.pop_back();
    }
}

bool AppendResourceFrame(napi_env env, napi_value resource, size_t index, ImageAnimatorSample& sample)
{
    ArkUI_DrawableDescriptor* drawable = nullptr;
    if (OH_ArkUI_GetDrawableDescriptorFromResourceNapiValue(env, resource, &drawable) !=
        ARKUI_ERROR_CODE_NO_ERROR || drawable == nullptr) {
        return false;
    }

    auto* frame = CreateFrameFromDrawable(drawable, BuildDefaultFrameSpec(index));
    if (frame == nullptr) {
        OH_ArkUI_DrawableDescriptor_Dispose(drawable);
        return false;
    }

    sample.drawables.push_back(drawable);
    sample.frames.push_back(frame);
    return true;
}

bool AppendResourceFrames(napi_env env, napi_value resourceArray, ImageAnimatorSample& sample)
{
    if (env == nullptr || resourceArray == nullptr) {
        return false;
    }

    bool isArray = false;
    napi_is_array(env, resourceArray, &isArray);
    if (!isArray) {
        return false;
    }

    bool hasFrame = false;
    uint32_t length = 0;
    napi_get_array_length(env, resourceArray, &length);
    for (uint32_t index = 0; index < length; ++index) {
        napi_value resource = nullptr;
        napi_get_element(env, resourceArray, index, &resource);
        hasFrame = AppendResourceFrame(env, resource, index, sample) || hasFrame;
    }
    return hasFrame;
}

void InitializeAnimatorNode(ArkUI_NodeHandle node)
{
    SetFloatAttribute(node, NODE_WIDTH, static_cast<float>(DEFAULT_ANIMATOR_WIDTH));
    SetFloatAttribute(node, NODE_HEIGHT, static_cast<float>(DEFAULT_ANIMATOR_HEIGHT));
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_DURATION, DEFAULT_DURATION);
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_REVERSE, DEFAULT_REVERSE);
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_FIXED_SIZE, DEFAULT_FIXED_SIZE);
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_FILL_MODE, ARKUI_ANIMATION_FILL_MODE_FORWARDS);
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_ITERATION, DEFAULT_ITERATION);
    SetIntAttribute(node, NODE_IMAGE_ANIMATOR_STATE, ARKUI_ANIMATION_STATUS_RUNNING);
}

bool RegisterAnimatorEvents(ArkUI_NodeHandle node, ImageAnimatorSample* sample)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr || sample == nullptr) {
        return false;
    }

    bool registered = true;
    for (const auto& event : EVENT_REGISTRATIONS) {
        registered = api->registerNodeEvent(node, event.eventType, event.targetId, sample) ==
            ARKUI_ERROR_CODE_NO_ERROR && registered;
    }
    api->addNodeEventReceiver(node, EventReceiver);
    return registered;
}

void UnregisterAnimatorEvents(ArkUI_NodeHandle node)
{
    auto* api = GetNodeApi();
    if (api == nullptr || node == nullptr) {
        return;
    }

    api->removeNodeEventReceiver(node, EventReceiver);
    for (const auto& event : EVENT_REGISTRATIONS) {
        api->unregisterNodeEvent(node, event.eventType);
    }
}

std::unique_ptr<ImageAnimatorSample> CreateSample(napi_env env, const AnimatorOptions& options)
{
    auto* api = GetNodeApi();
    if (api == nullptr) {
        return nullptr;
    }

    auto sample = std::make_unique<ImageAnimatorSample>();
    sample->animatorNode = api->createNode(ARKUI_NODE_IMAGE_ANIMATOR);
    if (sample->animatorNode == nullptr) {
        return nullptr;
    }

    InitializeAnimatorNode(sample->animatorNode);
    if (!AppendResourceFrames(env, options.resourceArray, *sample)) {
        AppendStringFrames(*sample, options.sources);
    }
    SetImagesAttribute(sample->animatorNode, sample->frames);
    RegisterAnimatorEvents(sample->animatorNode, sample.get());
    return sample;
}

void DestroySample(ImageAnimatorSample* sample)
{
    if (sample == nullptr) {
        return;
    }

    auto* api = GetNodeApi();
    if (api != nullptr && sample->animatorNode != nullptr) {
        UnregisterAnimatorEvents(sample->animatorNode);
        if (sample->content != nullptr) {
            OH_ArkUI_NodeContent_RemoveNode(sample->content, sample->animatorNode);
        }
        api->disposeNode(sample->animatorNode);
        sample->animatorNode = nullptr;
    }

    for (auto* frame : sample->frames) {
        OH_ArkUI_ImageAnimatorFrameInfo_Dispose(frame);
    }
    for (auto* drawable : sample->drawables) {
        OH_ArkUI_DrawableDescriptor_Dispose(drawable);
    }
    delete sample;
}

ImageAnimatorSample* GetSampleFromContent(ArkUI_NodeContentHandle content)
{
    return static_cast<ImageAnimatorSample*>(OH_ArkUI_NodeContent_GetUserData(content));
}

napi_value BuildCoverageObject(napi_env env, const std::vector<std::string>& items)
{
    napi_value array = nullptr;
    napi_create_array_with_length(env, items.size(), &array);
    for (size_t index = 0; index < items.size(); ++index) {
        napi_set_element(env, array, static_cast<uint32_t>(index), CreateString(env, items[index]));
    }
    return array;
}

napi_value BuildCountersObject(napi_env env, const EventCounters& counters, int32_t lastEventTargetId)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    SetNamedInt(env, object, "onStart", counters.onStart);
    SetNamedInt(env, object, "onPause", counters.onPause);
    SetNamedInt(env, object, "onRepeat", counters.onRepeat);
    SetNamedInt(env, object, "onCancel", counters.onCancel);
    SetNamedInt(env, object, "onFinish", counters.onFinish);
    SetNamedInt(env, object, "lastEventTargetId", lastEventTargetId);
    return object;
}

napi_value BuildMetricCheckObject(napi_env env, const ImageAnimatorCaseRunner::MetricCheck& check)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    SetNamedString(env, object, "name", check.name);
    SetNamedInt(env, object, "expected", check.expected);
    SetNamedInt(env, object, "actual", check.actual);
    SetNamedBool(env, object, "passed", check.passed);
    return object;
}

napi_value BuildMetricChecksArray(
    napi_env env, const std::vector<ImageAnimatorCaseRunner::MetricCheck>& checks)
{
    napi_value array = nullptr;
    napi_create_array_with_length(env, checks.size(), &array);
    for (size_t index = 0; index < checks.size(); ++index) {
        napi_set_element(env, array, static_cast<uint32_t>(index), BuildMetricCheckObject(env, checks[index]));
    }
    return array;
}

napi_value BuildCaseResultObject(napi_env env, const ImageAnimatorCaseRunner::CaseResult& item)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    SetNamedString(env, object, "group", item.group);
    SetNamedString(env, object, "name", item.name);
    SetNamedString(env, object, "api", item.api);
    SetNamedString(env, object, "note", item.note);
    SetNamedBool(env, object, "passed", item.passed);
    SetNamedValue(env, object, "checks", BuildMetricChecksArray(env, item.checks));
    return object;
}

napi_value BuildCaseResultsArray(
    napi_env env, const std::vector<ImageAnimatorCaseRunner::CaseResult>& cases)
{
    napi_value array = nullptr;
    napi_create_array_with_length(env, cases.size(), &array);
    for (size_t index = 0; index < cases.size(); ++index) {
        napi_set_element(env, array, static_cast<uint32_t>(index), BuildCaseResultObject(env, cases[index]));
    }
    return array;
}

napi_value BuildFrameInfoCaseReportObject(
    napi_env env, const ImageAnimatorCaseRunner::CaseReport& report)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    SetNamedBool(env, object, "nodeApiAvailable", report.nodeApiAvailable);
    SetNamedInt(env, object, "totalCases", report.totalCases);
    SetNamedInt(env, object, "passedCases", report.passedCases);
    SetNamedInt(env, object, "failedCases", report.failedCases);
    SetNamedInt(env, object, "totalChecks", report.totalChecks);
    SetNamedInt(env, object, "passedChecks", report.passedChecks);
    SetNamedInt(env, object, "failedChecks", report.failedChecks);
    SetNamedValue(env, object, "cases", BuildCaseResultsArray(env, report.cases));
    return object;
}

napi_value BuildFrameObject(napi_env env, ArkUI_ImageAnimatorFrameInfo* frame)
{
    napi_value object = nullptr;
    napi_create_object(env, &object);
    SetNamedInt(env, object, "left", OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(frame));
    SetNamedInt(env, object, "top", OH_ArkUI_ImageAnimatorFrameInfo_GetTop(frame));
    SetNamedInt(env, object, "width", OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(frame));
    SetNamedInt(env, object, "height", OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(frame));
    SetNamedInt(env, object, "duration", OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(frame));
    return object;
}

napi_value BuildFramesArray(napi_env env, const std::vector<ArkUI_ImageAnimatorFrameInfo*>& frames)
{
    napi_value array = nullptr;
    napi_create_array_with_length(env, frames.size(), &array);
    for (size_t index = 0; index < frames.size(); ++index) {
        napi_set_element(env, array, static_cast<uint32_t>(index), BuildFrameObject(env, frames[index]));
    }
    return array;
}

void AddFrameApiCoverage(std::vector<std::string>& coverage, const std::vector<std::string>& sources)
{
    FrameSpec spec;
    spec.left = COVERAGE_FRAME_LEFT;
    spec.top = COVERAGE_FRAME_TOP;
    spec.width = COVERAGE_FRAME_WIDTH;
    spec.height = COVERAGE_FRAME_HEIGHT;
    spec.duration = COVERAGE_FRAME_DURATION;
    auto sourceBuffer = MakeMutableCString(sources.front());
    auto* stringFrame = CreateFrameFromStringBuffer(sourceBuffer, spec);
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString", stringFrame != nullptr);
    if (stringFrame != nullptr) {
        OH_ArkUI_ImageAnimatorFrameInfo_Dispose(stringFrame);
    }
}

void AddFrameGetterCoverage(std::vector<std::string>& coverage, ImageAnimatorSample& sample)
{
    if (sample.frames.empty()) {
        return;
    }

    auto* frame = sample.frames.front();
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_SetWidth/GetWidth",
        OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(frame) == DEFAULT_FRAME_WIDTH);
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_SetHeight/GetHeight",
        OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(frame) == DEFAULT_FRAME_HEIGHT);
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_SetTop/GetTop",
        OH_ArkUI_ImageAnimatorFrameInfo_GetTop(frame) == DEFAULT_FRAME_TOP);
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_SetLeft/GetLeft",
        OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(frame) == DEFAULT_FRAME_LEFT);
    AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_SetDuration/GetDuration",
        OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(frame) == FRAME_DURATIONS.front());
}

bool CheckAttributeRoundTrip(ArkUI_NodeHandle node, const AttributeCheck& check)
{
    return SetIntAttribute(node, check.attribute, check.value) &&
        GetIntAttribute(node, check.attribute, INVALID_ATTRIBUTE_VALUE) == check.value &&
        ResetAttribute(node, check.attribute);
}

void AddAttributeCoverage(std::vector<std::string>& coverage, ImageAnimatorSample& sample)
{
    auto* api = GetNodeApi();
    if (api == nullptr || sample.animatorNode == nullptr) {
        return;
    }

    bool imagesOk = SetImagesAttribute(sample.animatorNode, sample.frames) &&
        api->getAttribute(sample.animatorNode, NODE_IMAGE_ANIMATOR_IMAGES) != nullptr;
    AddText(coverage, "NODE_IMAGE_ANIMATOR_IMAGES set/get", imagesOk);
    for (const auto& check : ATTRIBUTE_CHECKS) {
        AddText(coverage, check.coverageName, CheckAttributeRoundTrip(sample.animatorNode, check));
    }
}

void AddEventCoverage(std::vector<std::string>& coverage, ImageAnimatorSample& sample)
{
    bool registered = RegisterAnimatorEvents(sample.animatorNode, &sample);
    for (const auto& event : EVENT_REGISTRATIONS) {
        AddText(coverage, event.coverageName, registered);
    }
}

napi_value BuildCoverageResult(
    napi_env env, const std::vector<std::string>& coverage, const ImageAnimatorSample* sample)
{
    napi_value result = nullptr;
    napi_create_object(env, &result);
    SetNamedBool(env, result, "nodeApiAvailable", GetNodeApi() != nullptr);
    napi_set_named_property(env, result, "items", BuildCoverageObject(env, coverage));
    if (sample != nullptr) {
        napi_set_named_property(env, result, "frames", BuildFramesArray(env, sample->frames));
    }
    SetNamedString(env, result, "note", "The report calls current ImageAnimator C APIs.");
    return result;
}

napi_value GetCoverageReport(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    AnimatorOptions options = argc > 0 ? ReadAnimatorOptions(env, argv[0]) : ReadAnimatorOptions(env, nullptr);

    std::vector<std::string> coverage;
    auto sample = CreateSample(env, options);
    bool nodeCreated = sample != nullptr && sample->animatorNode != nullptr;
    AddText(coverage, "Create ARKUI_NODE_IMAGE_ANIMATOR", nodeCreated);
    AddFrameApiCoverage(coverage, options.sources);

    if (sample != nullptr) {
        AddText(coverage, "OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor",
            !sample->drawables.empty());
        AddFrameGetterCoverage(coverage, *sample);
        AddAttributeCoverage(coverage, *sample);
        AddEventCoverage(coverage, *sample);
    }

    napi_value result = BuildCoverageResult(env, coverage, sample.get());
    DestroySample(sample.release());
    return result;
}

napi_value GetFrameInfoCaseReport(napi_env env, napi_callback_info info)
{
    auto report = ImageAnimatorCaseRunner::RunImageAnimatorFrameInfoCases();
    return BuildFrameInfoCaseReportObject(env, report);
}

bool GetNodeContentArg(napi_env env, napi_value value, ArkUI_NodeContentHandle* content)
{
    return OH_ArkUI_GetNodeContentFromNapiValue(env, value, content) == ARKUI_ERROR_CODE_NO_ERROR &&
        *content != nullptr;
}

napi_value AttachImageAnimator(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2] = { nullptr, nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 1) {
        ThrowError(env, "attachImageAnimator requires a NodeContent argument.");
        return CreateUndefined(env);
    }

    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentArg(env, argv[0], &content)) {
        ThrowError(env, "Failed to map NodeContent to ArkUI_NodeContentHandle.");
        return CreateUndefined(env);
    }

    auto* oldSample = GetSampleFromContent(content);
    if (oldSample != nullptr) {
        DestroySample(oldSample);
        OH_ArkUI_NodeContent_SetUserData(content, nullptr);
    }

    AnimatorOptions options = argc > 1 ? ReadAnimatorOptions(env, argv[1]) : ReadAnimatorOptions(env, nullptr);
    auto sample = CreateSample(env, options);
    if (sample == nullptr || sample->animatorNode == nullptr) {
        ThrowError(env, "Failed to create native ImageAnimator node.");
        return CreateUndefined(env);
    }

    sample->content = content;
    if (OH_ArkUI_NodeContent_AddNode(content, sample->animatorNode) != ARKUI_ERROR_CODE_NO_ERROR) {
        DestroySample(sample.release());
        ThrowError(env, "Failed to add native ImageAnimator node to NodeContent.");
        return CreateUndefined(env);
    }

    auto* rawSample = sample.release();
    OH_ArkUI_NodeContent_SetUserData(content, rawSample);

    napi_value result = nullptr;
    napi_create_object(env, &result);
    SetNamedBool(env, result, "attached", true);
    SetNamedInt(env, result, "frameCount", static_cast<int32_t>(rawSample->frames.size()));
    SetNamedString(env, result, "state", "running");
    return result;
}

ImageAnimatorSample* GetSampleFromContentArg(napi_env env, napi_value value)
{
    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentArg(env, value, &content)) {
        return nullptr;
    }
    return GetSampleFromContent(content);
}

napi_value SetAnimatorState(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2] = { nullptr, nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 2) {
        ThrowError(env, "setAnimatorState requires a NodeContent and an AnimationStatus value.");
        return CreateUndefined(env);
    }

    auto* sample = GetSampleFromContentArg(env, argv[0]);
    int32_t state = GetInt32Arg(env, argv[1], ARKUI_ANIMATION_STATUS_INITIAL);
    bool ok = sample != nullptr && SetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_STATE, state);
    return CreateBool(env, ok);
}

int32_t ReadBoolOption(napi_env env, napi_value object, const char* name, int32_t fallback)
{
    napi_value property = nullptr;
    if (!GetNamedPropertyIfExists(env, object, name, &property)) {
        return fallback;
    }
    bool boolValue = false;
    napi_get_value_bool(env, property, &boolValue);
    return boolValue ? BOOLEAN_TRUE : BOOLEAN_FALSE;
}

int32_t ReadIntOption(napi_env env, napi_value object, const char* name, int32_t fallback)
{
    napi_value property = nullptr;
    if (!GetNamedPropertyIfExists(env, object, name, &property)) {
        return fallback;
    }
    return GetInt32Arg(env, property, fallback);
}

bool ApplyAnimatorOptions(napi_env env, ArkUI_NodeHandle node, napi_value options)
{
    int32_t duration = ReadIntOption(env, options, "duration", DEFAULT_DURATION);
    int32_t reverse = ReadBoolOption(env, options, "reverse", DEFAULT_REVERSE);
    int32_t fixedSize = ReadBoolOption(env, options, "fixedSize", DEFAULT_FIXED_SIZE);
    int32_t fillMode = ReadIntOption(env, options, "fillMode", ARKUI_ANIMATION_FILL_MODE_FORWARDS);
    int32_t iteration = ReadIntOption(env, options, "iteration", DEFAULT_ITERATION);

    return SetIntAttribute(node, NODE_IMAGE_ANIMATOR_DURATION, duration) &&
        SetIntAttribute(node, NODE_IMAGE_ANIMATOR_REVERSE, reverse) &&
        SetIntAttribute(node, NODE_IMAGE_ANIMATOR_FIXED_SIZE, fixedSize) &&
        SetIntAttribute(node, NODE_IMAGE_ANIMATOR_FILL_MODE, fillMode) &&
        SetIntAttribute(node, NODE_IMAGE_ANIMATOR_ITERATION, iteration);
}

napi_value SetAnimatorOptions(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value argv[2] = { nullptr, nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 2) {
        ThrowError(env, "setAnimatorOptions requires a NodeContent and options.");
        return CreateUndefined(env);
    }

    auto* sample = GetSampleFromContentArg(env, argv[0]);
    if (sample == nullptr || !IsObject(env, argv[1])) {
        return CreateBool(env, false);
    }
    return CreateBool(env, ApplyAnimatorOptions(env, sample->animatorNode, argv[1]));
}

napi_value GetAnimatorSnapshot(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 1) {
        ThrowError(env, "getAnimatorSnapshot requires a NodeContent.");
        return CreateUndefined(env);
    }

    auto* sample = GetSampleFromContentArg(env, argv[0]);
    napi_value result = nullptr;
    napi_create_object(env, &result);
    if (sample == nullptr) {
        SetNamedBool(env, result, "attached", false);
        return result;
    }

    SetNamedBool(env, result, "attached", true);
    SetNamedInt(env, result, "state",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_STATE, INVALID_ATTRIBUTE_VALUE));
    SetNamedInt(env, result, "duration",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_DURATION, INVALID_ATTRIBUTE_VALUE));
    SetNamedInt(env, result, "reverse",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_REVERSE, INVALID_ATTRIBUTE_VALUE));
    SetNamedInt(env, result, "fixedSize",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_FIXED_SIZE, INVALID_ATTRIBUTE_VALUE));
    SetNamedInt(env, result, "fillMode",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_FILL_MODE, INVALID_ATTRIBUTE_VALUE));
    SetNamedInt(env, result, "iteration",
        GetIntAttribute(sample->animatorNode, NODE_IMAGE_ANIMATOR_ITERATION, INVALID_ATTRIBUTE_VALUE));
    napi_set_named_property(env, result, "events", BuildCountersObject(env, sample->events, sample->lastEventTargetId));
    napi_set_named_property(env, result, "frames", BuildFramesArray(env, sample->frames));
    return result;
}

napi_value DetachImageAnimator(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc < 1) {
        ThrowError(env, "detachImageAnimator requires a NodeContent argument.");
        return CreateUndefined(env);
    }

    ArkUI_NodeContentHandle content = nullptr;
    if (!GetNodeContentArg(env, argv[0], &content)) {
        return CreateBool(env, false);
    }

    auto* sample = GetSampleFromContent(content);
    if (sample == nullptr) {
        return CreateBool(env, true);
    }

    DestroySample(sample);
    OH_ArkUI_NodeContent_SetUserData(content, nullptr);
    return CreateBool(env, true);
}

napi_property_descriptor BuildMethodDescriptor(const char* name, napi_callback method)
{
    napi_property_descriptor descriptor = {};
    descriptor.utf8name = name;
    descriptor.method = method;
    descriptor.attributes = napi_default;
    return descriptor;
}

napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        BuildMethodDescriptor("getCoverageReport", GetCoverageReport),
        BuildMethodDescriptor("getFrameInfoCaseReport", GetFrameInfoCaseReport),
        BuildMethodDescriptor("attachImageAnimator", AttachImageAnimator),
        BuildMethodDescriptor("setAnimatorState", SetAnimatorState),
        BuildMethodDescriptor("setAnimatorOptions", SetAnimatorOptions),
        BuildMethodDescriptor("getAnimatorSnapshot", GetAnimatorSnapshot),
        BuildMethodDescriptor("detachImageAnimator", DetachImageAnimator),
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
} // namespace

static napi_module g_imageAnimatorModule = {};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    g_imageAnimatorModule.nm_version = MODULE_VERSION;
    g_imageAnimatorModule.nm_register_func = Init;
    g_imageAnimatorModule.nm_modname = "entry";
    napi_module_register(&g_imageAnimatorModule);
}
