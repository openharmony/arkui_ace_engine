/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_engine.h"

#include <algorithm>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "third_party/quickjs/message_server.h"

#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"
#include "frameworks/bridge/common/dom/dom_type.h"
#include "frameworks/bridge/common/media_query/media_query_info.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/common/js_api_perf.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/bridge/js_frontend/engine/common/runtime_constants.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/badge_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/canvas_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/chart_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/clock_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/component_api_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/image_animator_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/intl/intl_support.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/list_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_group_js_bridge.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#include "frameworks/bridge/js_frontend/engine/quickjs/stepper_bridge.h"

extern const uint32_t js_framework_size;
extern const uint8_t js_framework[];

namespace OHOS::Ace::Framework {
namespace {

#ifndef ENABLE_JS_DEBUG
const char JS_MAIN_ENTRY[] = "___mainEntry___";
const char JS_EXT[] = ".js";
const char BIN_EXT[] = ".bin";
#endif
const char MAP_EXT[] = ".map";
constexpr int32_t CUSTOM_FULL_WINDOW_LENGTH = 3;
constexpr int32_t ARGS_FULL_WINDOW_LENGTH = 2;

int32_t CallEvalBuf(
    JSContext* ctx, const char* buf, size_t bufLen, const char* filename, int32_t evalFlags, int32_t instanceId)
{
    JSValue val = JS_Eval(ctx, buf, bufLen, filename, evalFlags);
    int32_t ret = JS_CALL_SUCCESS;
    if (JS_IsException(val)) {
        LOGE("[Qjs Native] EvalBuf failed!");
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::EVAL_BUFFER_ERROR, instanceId);
        ret = JS_CALL_FAIL;
    }
    JS_FreeValue(ctx, val);
    return ret;
}

JSValue CallReadObject(JSContext* ctx, const uint8_t* buf, size_t bufLen, bool persist = false, int32_t instanceId = 0,
    const char* pageUrl = nullptr)
{
    int32_t flags = persist ? (JS_READ_OBJ_ROM_DATA | JS_READ_OBJ_BYTECODE) : JS_READ_OBJ_BYTECODE;
    JSValue obj = JS_ReadObject(ctx, buf, bufLen, flags);
    if (JS_IsException(obj)) {
        LOGE("[Qjs Native] ReadObject failed!");
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::READ_OBJECT_ERROR, instanceId, pageUrl);
        return obj;
    }
    return JS_EvalFunction(ctx, obj);
}

RefPtr<JsAcePage> GetRunningPage(JSContext* ctx)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    ACE_DCHECK(instance);
    return instance->GetRunningPage();
}

RefPtr<JsAcePage> GetStagingPage(JSContext* ctx)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    ACE_DCHECK(instance);
    return instance->GetStagingPage();
}

void GetArrayValue(JSContext* ctx, JSValueConst arrayVal, std::string& result)
{
    int32_t length = QjsUtils::JsGetArrayLength(ctx, arrayVal);
    for (int32_t i = 0; i < length; ++i) {
        if (i != 0) {
            result.append(1, DOM_PICKER_SPLIT_ARRAY); // only need one char to split.
        }
        JSValue itemVal = JS_GetPropertyUint32(ctx, arrayVal, i);
        if (JS_IsString(itemVal) || JS_IsNumber(itemVal) || JS_IsBool(itemVal)) {
            ScopedString val(ctx, itemVal);
            const char* itemStr = val.get();
            result.append(itemStr);
            JS_FreeValue(ctx, itemVal);
            continue;
        }
        if (JS_IsArray(ctx, itemVal)) {
            int32_t subLength = QjsUtils::JsGetArrayLength(ctx, itemVal);
            for (int32_t j = 0; j < subLength; ++j) {
                if (j != 0) {
                    result.append(1, DOM_PICKER_SPLIT_ITEM); // only need one char to split
                }
                JSValue subItemVal = JS_GetPropertyUint32(ctx, itemVal, j);
                ScopedString subVal(ctx, subItemVal);
                const char* subItemStr = subVal.get();
                result.append(subItemStr);
                JS_FreeValue(ctx, subItemVal);
            }
            JS_FreeValue(ctx, itemVal);
            continue;
        }
        JS_FreeValue(ctx, itemVal);
    }
}

void GetAttrImage(JSContext* ctx, JSValueConst valObject, ImageProperties& imageProperties)
{
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (!CheckAndGetJsProperty(ctx, valObject, &pTab, &len)) {
        return;
    }
    for (uint32_t i = 0; i < len; ++i) {
        const char* key = JS_AtomToCString(ctx, pTab[i].atom);
        if (key == nullptr) {
            JS_FreeAtom(ctx, pTab[i].atom);
            LOGW("key is null. Ignoring!");
            continue;
        }
        JSValue valItem = JS_GetProperty(ctx, valObject, pTab[i].atom);
        if (JS_IsString(valItem) || JS_IsNumber(valItem) || JS_IsBool(valItem)) {
            ScopedString styleVal(ctx, valItem);
            const char* valStr = styleVal.get();
            if (strcmp(key, "src") == 0) {
                imageProperties.src = valStr;
            } else if (strcmp(key, "width") == 0) {
                imageProperties.width = valStr;
            } else if (strcmp(key, "height") == 0) {
                imageProperties.height = valStr;
            } else if (strcmp(key, "top") == 0) {
                imageProperties.top = valStr;
            } else if (strcmp(key, "left") == 0) {
                imageProperties.left = valStr;
            } else if (strcmp(key, "duration") == 0) {
                imageProperties.duration = valStr;
            } else {
                LOGD("key : %{public}s unsupported. Ignoring!", key);
            }
        } else {
            LOGD("value of unsupported type. Ignoring!");
        }
        JS_FreeAtom(ctx, pTab[i].atom);
        JS_FreeCString(ctx, key);
        JS_FreeValue(ctx, valItem);
    }
    js_free(ctx, pTab);
}

void GetAttrImages(JSContext* ctx, JSValueConst arrayVal, std::vector<ImageProperties>& images)
{
    int32_t length = QjsUtils::JsGetArrayLength(ctx, arrayVal);
    for (int32_t i = 0; i < length; ++i) {
        JSValue valArray = JS_GetPropertyUint32(ctx, arrayVal, i);
        ImageProperties imageProperties;
        if (JS_IsObject(valArray)) {
            GetAttrImage(ctx, valArray, imageProperties);
            images.push_back(imageProperties);
        }
        JS_FreeValue(ctx, valArray);
    }
}

bool SetDomAttributes(JSContext* ctx, JSValueConst fromMap, JsCommandDomElementOperator& command)
{
    ACE_SCOPED_TRACE("SetDomAttributes");

    bool hasShowAttr = false;
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (!CheckAndGetJsProperty(ctx, fromMap, &pTab, &len)) {
        return hasShowAttr;
    }

    std::vector<std::pair<std::string, std::string>> attrs;
    for (uint32_t i = 0; i < len; i++) {
        const char* key = JS_AtomToCString(ctx, pTab[i].atom);
        if (key == nullptr) {
            JS_FreeAtom(ctx, pTab[i].atom);
            LOGW("key is null. Ignoring!");
            continue;
        }
        JSValue val = JS_GetProperty(ctx, fromMap, pTab[i].atom);
        if (JS_IsString(val) || JS_IsNumber(val) || JS_IsBool(val)) {
            ScopedString styleVal(ctx, val);
            const char* valStr = styleVal.get();
            LOGD("SetDomAttributes: key: %{private}s, attr: %{private}s", key, valStr);
            if (strcmp(key, DOM_ID) == 0) {
                command.SetId(valStr);
            } else if (strcmp(key, DOM_TARGET) == 0) {
                command.SetTarget(valStr);
            } else if (strcmp(key, DOM_SHARE_ID) == 0) {
                command.SetShareId(valStr);
            }
            attrs.emplace_back(key, valStr);
            if (strcmp(key, DOM_SHOW) == 0) {
                hasShowAttr = true;
            }
        } else if (JS_IsArray(ctx, val)) {
            if (strcmp(key, "datasets") == 0) {
                auto chartBridge = AceType::MakeRefPtr<ChartBridge>();
                chartBridge->GetAttrDatasets(ctx, val);
                command.SetDatasets(chartBridge->GetDatasets());
            } else if (strcmp(key, "images") == 0) {
                std::vector<ImageProperties> images;
                GetAttrImages(ctx, val, images);
                command.SetImagesAttr(std::move(images));
            } else if (strcmp(key, "segments") == 0) {
                auto chartBridge = AceType::MakeRefPtr<ChartBridge>();
                chartBridge->ParseAttrSegmentArray(ctx, val);
                command.SetSegments(chartBridge->GetSegments());
            } else {
                std::string valStr;
                GetArrayValue(ctx, val, valStr);
                LOGD("SetDomAttributes: key: %{private}s, attr: %{private}s", key, valStr.c_str());
                attrs.emplace_back(key, valStr);
            }
        } else if (JS_IsObject(val)) {
            if (strcmp(key, "options") == 0) {
                auto chartBridge = AceType::MakeRefPtr<ChartBridge>();
                chartBridge->GetAttrOptionsObject(ctx, val);
                command.SetOptions(chartBridge->GetChartOptions());
            } else if (strcmp(key, "segments") == 0) {
                auto chartBridge = AceType::MakeRefPtr<ChartBridge>();
                chartBridge->ParseAttrSingleSegment(ctx, val);
                command.SetSegments(chartBridge->GetSegments());
            } else if (strcmp(key, DOM_CLOCK_CONFIG) == 0) {
                auto clockBridge = AceType::MakeRefPtr<ClockBridge>();
                clockBridge->ParseClockConfig(ctx, val);
                command.SetClockConfig(clockBridge->GetClockConfig());
            } else if (strcmp(key, DOM_NODE_TAG_LABEL) == 0) {
                auto stepperBridge = AceType::MakeRefPtr<StepperBridge>();
                StepperLabels label;
                stepperBridge->GetAttrLabel(ctx, val, label);
                command.SetStepperLabel(label);
            } else if (strcmp(key, DOM_BADGE_CONFIG) == 0) {
                auto badgeBridge = AceType::MakeRefPtr<BadgeBridge>();
                badgeBridge->ParseBadgeConfig(ctx, val);
                command.SetBadgeConfig(badgeBridge->GetBadgeConfig());
            } else {
                LOGD("key %{public}s unsupported. Ignoring!", key);
            }
        } else if (JS_IsUndefined(val)) {
            LOGE("value of key[%{private}s] is undefined. Ignoring!", key);
        } else {
            LOGE("value of key[%{private}s] of unsupported type. Ignoring!", key);
        }
        JS_FreeAtom(ctx, pTab[i].atom);
        JS_FreeCString(ctx, key);
        JS_FreeValue(ctx, val);
    }

    command.SetAttributes(std::move(attrs));
    js_free(ctx, pTab);
    return hasShowAttr;
}

void GetAndRegisterFamily(JSContext* ctx, JSValueConst valArray, std::string& familyStyle)
{
    JSPropertyEnum* tab = nullptr;
    uint32_t aLen = 0;
    JS_GetOwnPropertyNames(ctx, &tab, &aLen, valArray, JS_GPN_STRING_MASK);

    std::string familyVal;
    std::string srcVal;
    for (uint32_t j = 0; j < aLen; j++) {
        // ValObject is one row of family object
        JSValue valObject = JS_GetProperty(ctx, valArray, tab[j].atom);
        const char* keyObject = JS_AtomToCString(ctx, tab[j].atom);
        if (JS_IsString(valObject)) {
            ScopedString styleVal(ctx, valObject);
            const char* valStr = styleVal.get();
            auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
            ACE_DCHECK(instance);
            if (keyObject != nullptr && strcmp(keyObject, "fontFamily") == 0) {
                familyVal = valStr;
                if (!srcVal.empty()) {
                    instance->GetDelegate()->RegisterFont(familyVal, srcVal);
                    familyVal.erase();
                    srcVal.erase();
                }
                if (familyStyle.length() > 0) {
                    familyStyle.append(",");
                }
                familyStyle.append(valStr);
            } else if (keyObject != nullptr && strcmp(keyObject, "src") == 0) {
                srcVal = valStr;
                // The format of font src is: url("src"), here get the src.
                srcVal = srcVal.substr(5, srcVal.length() - 7);
                if (!familyVal.empty()) {
                    instance->GetDelegate()->RegisterFont(familyVal, srcVal);
                    familyVal.erase();
                    srcVal.erase();
                }
            }
        }
        JS_FreeAtom(ctx, tab[j].atom);
        JS_FreeCString(ctx, keyObject);
        JS_FreeValue(ctx, valObject);
    }
    js_free(ctx, tab);
}

void GetStyleFamilyValue(JSContext* ctx, JSValueConst arrayVal, std::string& familyStyle)
{
    int32_t length = QjsUtils::JsGetArrayLength(ctx, arrayVal);
    for (int32_t i = 0; i < length; ++i) {
        // ValArray is one row of family array
        JSValue valArray = JS_GetPropertyUint32(ctx, arrayVal, i);
        if (JS_IsObject(valArray)) {
            GetAndRegisterFamily(ctx, valArray, familyStyle);
        }
        JS_FreeValue(ctx, valArray);
    }
}

void GetStyleAnimationName(
    JSContext* ctx, JSValueConst arrayVal, std::vector<std::unordered_map<std::string, std::string>>& styleVec)
{
    int32_t length = QjsUtils::JsGetArrayLength(ctx, arrayVal);
    for (int32_t i = 0; i < length; ++i) {
        std::unordered_map<std::string, std::string> animationNameKeyFrame;
        JSValue valArray = JS_GetPropertyUint32(ctx, arrayVal, i);
        if (JS_IsObject(valArray)) {
            JSPropertyEnum* tab = nullptr;
            uint32_t anotherLen = 0;
            JS_GetOwnPropertyNames(ctx, &tab, &anotherLen, valArray, JS_GPN_STRING_MASK);
            for (uint32_t j = 0; j < anotherLen; ++j) {
                const char* key = JS_AtomToCString(ctx, tab[j].atom);
                if (key == nullptr) {
                    JS_FreeAtom(ctx, tab[j].atom);
                    JS_FreeValue(ctx, valArray);
                    LOGW("key is null. Ignoring!");
                    continue;
                }
                JSValue valObject = JS_GetProperty(ctx, valArray, tab[j].atom);
                if (JS_IsString(valObject) || JS_IsNumber(valObject)) {
                    ScopedString styleVal(ctx, valObject);
                    const char* valStr = styleVal.get();
                    animationNameKeyFrame.emplace(key, valStr);
                } else {
                    LOGD("GetStyleAnimationName: unsupported type :%{public}d", JS_VALUE_GET_TAG(valObject));
                }
                JS_FreeAtom(ctx, tab[j].atom);
                JS_FreeCString(ctx, key);
                JS_FreeValue(ctx, valObject);
            }
            js_free(ctx, tab);
        }
        if (animationNameKeyFrame.size() > 0) {
            styleVec.emplace_back(animationNameKeyFrame);
        }
        JS_FreeValue(ctx, valArray);
    }
}

void SetDomStyle(JSContext* ctx, JSValueConst fromMap, JsCommandDomElementOperator& command)
{
    ACE_SCOPED_TRACE("SetDomStyle");

    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (!CheckAndGetJsProperty(ctx, fromMap, &pTab, &len)) {
        return;
    }

    std::vector<std::pair<std::string, std::string>> styles;
    for (uint32_t i = 0; i < len; i++) {
        const char* key = JS_AtomToCString(ctx, pTab[i].atom);
        if (key == nullptr) {
            JS_FreeAtom(ctx, pTab[i].atom);
            LOGW("key is null. Ignoring!");
            continue;
        }
        JSValue val = JS_GetProperty(ctx, fromMap, pTab[i].atom);
        if (JS_IsString(val) || JS_IsNumber(val) || JS_IsBool(val)) {
            ScopedString styleVal(ctx, val);
            const char* valStr = styleVal.get();
            LOGD("SetDomStyle: key: %{private}s, style: %{private}s", key, valStr);
            styles.emplace_back(key, valStr);
        } else if (JS_IsArray(ctx, val)) {
            if (strcmp(key, DOM_TEXT_FONT_FAMILY) == 0) {
                // Deal with special case such as fontFamily, suppose all the keys in the array are the same.
                std::string familyStyle;
                GetStyleFamilyValue(ctx, val, familyStyle);
                styles.emplace_back(key, familyStyle);
            } else if (strcmp(key, DOM_ANIMATION_NAME) == 0) {
                // Deal with special case animationName, it different with fontfamily,
                // the keys in the array are different.
                std::vector<std::unordered_map<std::string, std::string>> animationStyles;
                GetStyleAnimationName(ctx, val, animationStyles);
                command.SetAnimationStyles(std::move(animationStyles));
            } else if (strcmp(key, DOM_TRANSITION_ENTER) == 0) {
                std::vector<std::unordered_map<std::string, std::string>> transitionEnter;
                GetStyleAnimationName(ctx, val, transitionEnter);
                command.SetTransitionEnter(std::move(transitionEnter));
            } else if (strcmp(key, DOM_TRANSITION_EXIT) == 0) {
                std::vector<std::unordered_map<std::string, std::string>> transitionExit;
                GetStyleAnimationName(ctx, val, transitionExit);
                command.SetTransitionExit(std::move(transitionExit));
            } else if (strcmp(key, DOM_SHARED_TRANSITION_NAME) == 0) {
                std::vector<std::unordered_map<std::string, std::string>> sharedTransitionName;
                GetStyleAnimationName(ctx, val, sharedTransitionName);
                command.SetSharedTransitionName(std::move(sharedTransitionName));
            } else {
                LOGD("value is array, key unsupported. Ignoring!");
            }
        } else if (JS_IsUndefined(val)) {
            LOGD("value is undefined. Ignoring!");
        } else {
            LOGD("value of unsupported type. Ignoring!");
        }
        JS_FreeAtom(ctx, pTab[i].atom);
        JS_FreeCString(ctx, key);
        JS_FreeValue(ctx, val);
    }

    QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    auto pipelineContext = instance->GetDelegate()->GetPipelineContext();
    command.SetPipelineContext(pipelineContext);
    command.SetStyles(std::move(styles));
    js_free(ctx, pTab);
}

void AddDomEvent(JSContext* ctx, JSValueConst fromArray, JsCommandDomElementOperator& command)
{
    ACE_SCOPED_TRACE("AddDomEvent");

    std::vector<std::string> eventsMap;
    int32_t length = QjsUtils::JsGetArrayLength(ctx, fromArray);
    for (int32_t i = 0; i < length; i++) {
        JSValue val = JS_GetPropertyUint32(ctx, fromArray, i);
        if (JS_IsString(val)) {
            ScopedString styleVal(ctx, val);
            const char* valStr = styleVal.get();
            eventsMap.emplace_back(valStr);
        } else {
            LOGW("value of unsupported type. Ignoring!");
        }
        JS_FreeValue(ctx, val);
    }
    command.AddEvents(std::move(eventsMap));
}

JSValue JsRemoveElement(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc != REMOVE_ELEMENT_ARGS_LEN)) {
        LOGE("JsRemoveElement: the arg is error when call removeElement");
        return JS_EXCEPTION;
    }

    auto page = GetRunningPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    int32_t instanceId = 0;
    JS_ToInt32(ctx, &instanceId, argv[REMOVE_ELEMENT_INSTANCE_ID]);
    if (page->GetPageId() != instanceId) {
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        page = instance->GetDelegate()->GetPage(instanceId);
        if (page == nullptr) {
            LOGE("JsRemoveElement fail to get page, pageId: %{public}d", instanceId);
            return JS_EXCEPTION;
        }
    }

    int32_t nodeId = 0;
    JS_ToInt32(ctx, &nodeId, argv[0]);
    nodeId = (nodeId == 0) ? DOM_ROOT_NODE_ID_BASE + page->GetPageId() : nodeId;
    page->PushCommand(Referenced::MakeRefPtr<JsCommandRemoveDomElement>(nodeId));
    return JS_NULL;
}

JSValue JsUpdateElementAttrs(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc != UPLOAD_ELEMENT_ARGS_LEN)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }

    auto page = GetRunningPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    int32_t instanceId = 0;
    JS_ToInt32(ctx, &instanceId, argv[UPLOAD_ELEMENT_INSTANCE_ID]);
    if (page->GetPageId() != instanceId) {
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        page = instance->GetDelegate()->GetPage(instanceId);
        if (page == nullptr) {
            LOGE("JsUpdateElementAttrs fail to get page, pageId :%{public}d", instanceId);
            return JS_EXCEPTION;
        }
    }

    int32_t nodeId = 0;
    JS_ToInt32(ctx, &nodeId, argv[0]);
    nodeId = (nodeId == 0) ? DOM_ROOT_NODE_ID_BASE + page->GetPageId() : nodeId;
    auto command = Referenced::MakeRefPtr<JsCommandUpdateDomElementAttrs>(nodeId);
    if (SetDomAttributes(ctx, argv[1], *command)) {
        page->ReserveShowCommand(command);
    }
    page->PushCommand(command);
    return JS_NULL;
}

JSValue JsUpdateElementStyles(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc != UPLOAD_ELEMENT_ARGS_LEN)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }

    auto page = GetRunningPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    int32_t instanceId = 0;
    JS_ToInt32(ctx, &instanceId, argv[UPLOAD_ELEMENT_INSTANCE_ID]);
    if (page->GetPageId() != instanceId) {
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        page = instance->GetDelegate()->GetPage(instanceId);
        if (page == nullptr) {
            LOGE("JsUpdateElementStyles fail to get page, pageId: %{public}d", instanceId);
            return JS_EXCEPTION;
        }
    }

    int32_t nodeId = 0;
    JS_ToInt32(ctx, &nodeId, argv[0]);
    nodeId = (nodeId == 0) ? DOM_ROOT_NODE_ID_BASE + page->GetPageId() : nodeId;
    auto command = Referenced::MakeRefPtr<JsCommandUpdateDomElementStyles>(nodeId);
    SetDomStyle(ctx, argv[1], *command);
    page->PushCommand(command);
    return JS_NULL;
}

JSValue JsDomCreateBody(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc != 5)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }

    auto page = GetStagingPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    int32_t nodeId = DOM_ROOT_NODE_ID_BASE + page->GetPageId();
    LOGD("JsDomCreateBody: pageId: %{private}d, nodeId: %{private}d:", page->GetPageId(), nodeId);

    ScopedString tag(ctx, argv[1]);
    auto command = Referenced::MakeRefPtr<JsCommandCreateDomBody>(tag.get(), nodeId);

    SetDomAttributes(ctx, argv[2], *command);
    SetDomStyle(ctx, argv[3], *command);
    AddDomEvent(ctx, argv[4], *command);
    page->PushCommand(command);
    return JS_NULL;
}

JSValue JsDomAddElement(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JsDomAddElement");

    if ((argv == nullptr) || (argc != ADD_ELEMENT_ARGS_LEN)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }

    auto page = GetStagingPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    int32_t instanceId = 0;
    JS_ToInt32(ctx, &instanceId, argv[ADD_ELEMENT_INSTANCE_ID]);
    if (page->GetPageId() != instanceId) {
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        page = instance->GetDelegate()->GetPage(instanceId);
        if (page == nullptr) {
            LOGE("JsDomAddElement fail to get page, pageId: %{public}d", instanceId);
            return JS_EXCEPTION;
        }
    }

    int32_t parentNodeId;
    JS_ToInt32(ctx, &parentNodeId, argv[0]);
    parentNodeId = parentNodeId ? parentNodeId : (DOM_ROOT_NODE_ID_BASE + page->GetPageId());

    int32_t nodeId;
    JS_ToInt32(ctx, &nodeId, argv[1]);
    ScopedString tag(ctx, argv[2]);
    LOGD("JsDomAddElement: pageId: %{private}d, parentNodeId: %{private}d, nodeId: %{private}d, tag: %{private}s",
        page->GetPageId(), parentNodeId, nodeId, tag.get());
    auto command = Referenced::MakeRefPtr<JsCommandAddDomElement>(tag.get(), nodeId, parentNodeId);
    SetDomAttributes(ctx, argv[3], *command);
    SetDomStyle(ctx, argv[4], *command);
    AddDomEvent(ctx, argv[5], *command);

    ScopedString customFlag(ctx, argv[6]);
    if (customFlag.get()) {
        std::unique_ptr<JsonValue> customPtr = JsonUtil::ParseJsonString(customFlag.get());
        if (customPtr && customPtr->IsBool()) {
            command->SetIsCustomComponent(customPtr->GetBool());
        }
    }
    int32_t itemIndex;
    JS_ToInt32(ctx, &itemIndex, argv[7]);
    command->SetForIndex(itemIndex);
    page->PushCommand(command);
    // Flush command as fragment immediately when pushed too many commands.
    if (!page->CheckPageCreated() && page->GetCommandSize() > FRAGMENT_SIZE) {
        page->FlushCommands();
    }
    return JS_NULL;
}

// JS Framework calls this function after initial loading of the page has been done.
JSValue JsOnCreateFinish(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    LOGD("JsOnCreateFinish");
    auto page = GetStagingPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }
    page->SetPageCreated();
    return JS_NULL;
}

// JS Framework calls this function after JS framework has finished processing an event.
JSValue JsOnUpdateFinish(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    LOGD("JsOnUpdateFinish");
    auto page = GetRunningPage(ctx);
    if (page == nullptr) {
        return JS_EXCEPTION;
    }

    if (page->CheckPageCreated()) {
        QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        instance->GetDelegate()->TriggerPageUpdate(page->GetPageId());
    }
    return JS_NULL;
}

std::string JsParseRouteUrl(JSContext* ctx, JSValueConst argv, const std::string& key)
{
    std::string pageRoute;
    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->GetValue(key) != nullptr && argsPtr->GetValue(key)->IsString()) {
        pageRoute = argsPtr->GetValue(key)->GetString();
    }
    LOGI("JsParseRouteUrl pageRoute = %{private}s", pageRoute.c_str());
    return pageRoute;
}

std::string JsParseRouteParams(JSContext* ctx, JSValueConst argv, const std::string& key)
{
    std::string params;
    ScopedString args(ctx, argv);

    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->Contains(key) && argsPtr->GetValue(key)->IsObject()) {
        params = argsPtr->GetValue(key)->ToString();
    }
    return params;
}

std::vector<std::pair<std::string, std::string>> JsParseDialogButtons(
    JSContext* ctx, JSValueConst argv, const std::string& key)
{
    std::vector<std::pair<std::string, std::string>> dialogButtons;
    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->GetValue(key) != nullptr && argsPtr->GetValue(key)->IsArray()) {
        for (int32_t i = 0; i < argsPtr->GetValue(key)->GetArraySize(); ++i) {
            auto button = argsPtr->GetValue(key)->GetArrayItem(i);
            if (!button) {
                continue;
            }
            std::string buttonText;
            std::string buttonColor;
            if (button->GetValue("text")) {
                buttonText = button->GetValue("text")->GetString();
            }
            if (button->GetValue("color")) {
                buttonColor = button->GetValue("color")->GetString();
            }
            dialogButtons.emplace_back(buttonText, buttonColor);
        }
    }
    return dialogButtons;
}

JSValue JsHandlePageRoute(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    std::string uri = JsParseRouteUrl(ctx, argv, ROUTE_KEY_URI);
    if (methodName == ROUTE_PAGE_BACK) {
        uri = JsParseRouteUrl(ctx, argv, ROUTE_KEY_PATH);
    }
    std::string params = JsParseRouteParams(ctx, argv, ROUTE_KEY_PARAMS);

    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    // Operator map for page route.
    static const LinearMapNode<JSValue (*)(const std::string&, const std::string&, QjsEngineInstance&)>
        pageRouteOperators[] = {
            { ROUTE_PAGE_BACK,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    LOGD("JsBackRoute uri = %{private}s", uri.c_str());
                    instance.GetDelegate()->Back(uri);
                    return JS_NULL;
                } },
            { ROUTE_PAGE_CLEAR,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    LOGD("Clear Page Route");
                    instance.GetDelegate()->Clear();
                    return JS_NULL;
                } },
            { ROUTE_PAGE_GET_LENGTH,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    int32_t routeLength = instance.GetDelegate()->GetStackSize();
                    std::string indexLength = std::to_string(routeLength);
                    LOGD("JsGetLengthRoute routeLength=%{private}s", indexLength.c_str());
                    auto ctx = instance.GetQjsContext();
                    return JS_NewString(ctx, indexLength.c_str());
                } },
            { ROUTE_PAGE_GET_STATE,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    int32_t routeIndex = 0;
                    std::string routeName;
                    std::string routePath;
                    instance.GetDelegate()->GetState(routeIndex, routeName, routePath);
                    LOGD("JsGetStateRoute index=%{private}d name=%{private}s path=%{private}s", routeIndex,
                        routeName.c_str(), routePath.c_str());

                    auto ctx = instance.GetQjsContext();
                    JSValue routeData = JS_NewObject(ctx);
                    JS_SetPropertyStr(ctx, routeData, "index", JS_NewInt32(ctx, routeIndex));
                    JS_SetPropertyStr(ctx, routeData, "name", JS_NewString(ctx, routeName.c_str()));
                    JS_SetPropertyStr(ctx, routeData, "path", JS_NewString(ctx, routePath.c_str()));
                    return routeData;
                } },
            { ROUTE_PAGE_PUSH,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    LOGD("JsPushRoute uri = %{private}s", uri.c_str());
                    instance.GetDelegate()->Push(uri, params);
                    return JS_NULL;
                } },
            { ROUTE_PAGE_REPLACE,
                [](const std::string& uri, const std::string& params, QjsEngineInstance& instance) {
                    LOGD("JsReplaceRoute uri = %{private}s", uri.c_str());
                    instance.GetDelegate()->Replace(uri, params);
                    return JS_NULL;
                } },
        };
    auto operatorIter = BinarySearchFindIndex(pageRouteOperators, ArraySize(pageRouteOperators), methodName.c_str());
    if (operatorIter != -1) {
        return pageRouteOperators[operatorIter].value(uri, params, *instance);
    } else {
        LOGW("system.router not support method = %{private}s", methodName.c_str());
    }
    return JS_NULL;
}

JSValue JsShowToast(JSContext* ctx, JSValueConst argv)
{
    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    std::string message;
    int32_t duration = 0;
    std::string bottom;
    if (argsPtr != nullptr) {
        if (argsPtr->GetValue(PROMPT_KEY_MESSAGE) != nullptr) {
            if (argsPtr->GetValue(PROMPT_KEY_MESSAGE)->IsString()) {
                message = argsPtr->GetValue(PROMPT_KEY_MESSAGE)->GetString();
            } else {
                message = argsPtr->GetValue(PROMPT_KEY_MESSAGE)->ToString();
            }
        }
        if (argsPtr->GetValue(PROMPT_KEY_DURATION) != nullptr && argsPtr->GetValue(PROMPT_KEY_DURATION)->IsNumber()) {
            duration = argsPtr->GetValue(PROMPT_KEY_DURATION)->GetInt();
        }
        if (argsPtr->GetValue(PROMPT_KEY_BOTTOM) != nullptr && argsPtr->GetValue(PROMPT_KEY_BOTTOM)->IsString()) {
            bottom = argsPtr->GetValue(PROMPT_KEY_BOTTOM)->GetString();
        }
    }
    LOGD("JsShowToast message = %{private}s duration = %{private}d bottom = %{private}s", message.c_str(), duration,
        bottom.c_str());
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    ACE_DCHECK(instance);
    instance->GetDelegate()->ShowToast(message, duration, bottom);
    return JS_NULL;
}

JSValue JsShowDialog(JSContext* ctx, JSValueConst argv)
{
    const std::string title = JsParseRouteUrl(ctx, argv, PROMPT_KEY_TITLE);
    const std::string message = JsParseRouteUrl(ctx, argv, PROMPT_KEY_MESSAGE);
    std::vector<std::pair<std::string, std::string>> buttons = JsParseDialogButtons(ctx, argv, PROMPT_KEY_BUTTONS);
    const std::string success = JsParseRouteUrl(ctx, argv, COMMON_SUCCESS);
    const std::string cancel = JsParseRouteUrl(ctx, argv, COMMON_CANCEL);
    const std::string complete = JsParseRouteUrl(ctx, argv, COMMON_COMPLETE);
    bool autoCancel = true;

    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->GetValue(PROMPT_DIALOG_AUTO_CANCEL) != nullptr &&
        argsPtr->GetValue(PROMPT_DIALOG_AUTO_CANCEL)->IsBool()) {
        autoCancel = argsPtr->GetValue(PROMPT_DIALOG_AUTO_CANCEL)->GetBool();
    }

    std::set<std::string> callbacks;
    if (!success.empty()) {
        callbacks.emplace(COMMON_SUCCESS);
    }
    if (!cancel.empty()) {
        callbacks.emplace(COMMON_CANCEL);
    }
    if (!complete.empty()) {
        callbacks.emplace(COMMON_COMPLETE);
    }

    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    auto callback = [instance, success, cancel, complete](int32_t callbackType, int32_t successType) {
        switch (callbackType) {
            case 0:
                instance->CallJs(success.c_str(),
                    std::string("{\"index\":").append(std::to_string(successType)).append("}").c_str(), false);
                break;
            case 1:
                instance->CallJs(cancel.c_str(), std::string("\"cancel\",null").c_str(), false);
                break;
            case 2:
                instance->CallJs(complete.c_str(), std::string("\"complete\",null").c_str(), false);
                break;
            default:
                break;
        }
    };
    instance->GetDelegate()->ShowDialog(title, message, buttons, autoCancel, std::move(callback), callbacks);
    return JS_NULL;
}

JSValue JsHandlePrompt(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    if (methodName == PROMPT_SHOW_TOAST) {
        return JsShowToast(ctx, argv);
    } else if (methodName == PROMPT_SHOW_DIALOG) {
        return JsShowDialog(ctx, argv);
    } else {
        LOGW("system.prompt not support method = %{private}s", methodName.c_str());
    }
    return JS_NULL;
}

JSValue JsHandleAnimationFrame(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        return JS_NULL;
    }
    const char* callbackIdJsStr = JS_ToCString(ctx, argv);
    if (callbackIdJsStr == nullptr) {
        LOGW("system animation callbackId is null");
        return JS_NULL;
    }
    if (methodName == ANIMATION_REQUEST_ANIMATION_FRAME) {
        instance->GetDelegate()->RequestAnimationFrame(std::string(callbackIdJsStr));
    } else if (methodName == ANIMATION_CANCEL_ANIMATION_FRAME) {
        instance->GetDelegate()->CancelAnimationFrame(std::string(callbackIdJsStr));
    } else {
        LOGW("animationFrame not support method = %{private}s", methodName.c_str());
    }
    JS_FreeCString(ctx, callbackIdJsStr);
    return JS_NULL;
}

JSValue JsAddListener(JSContext* ctx, JSValueConst argv)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        return JS_NULL;
    }
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (JS_IsObject(argv) && JS_IsArray(ctx, argv)) {
        JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
        if (len == 0) {
            js_free(ctx, pTab);
            return JS_NULL;
        }
        JSValue jsListenerId = JS_GetProperty(ctx, argv, pTab[0].atom);
        const char* listenerId = JS_ToCString(ctx, jsListenerId);
        auto mediaQuery = instance->GetDelegate()->GetMediaQueryInfoInstance();
        if (mediaQuery) {
            mediaQuery->SetListenerId(std::string(listenerId));
        }
        JS_FreeCString(ctx, listenerId);
        JS_FreeValue(ctx, jsListenerId);
        js_free(ctx, pTab);
    }
    return JS_NULL;
}

void JsParseCallbackResult(JSContext* ctx, JSValueConst jsResult, const std::string& key, std::string& result)
{
    ScopedString args(ctx, jsResult);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->GetValue(key) != nullptr) {
        if (argsPtr->GetValue(key)->IsString()) {
            result = argsPtr->GetValue(key)->GetString();
        } else if (argsPtr->GetValue(key)->IsNumber()) {
            result = argsPtr->GetValue(key)->ToString();
        }
    }
}

JSValue JsHandleCallback(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    if (methodName == CALLBACK_NATIVE) {
        if (JS_IsObject(argv) && JS_IsArray(ctx, argv)) {
            JSValue jsCallbackId = JS_GetPropertyUint32(ctx, argv, 0);
            JSValue jsResult = JS_GetPropertyUint32(ctx, argv, 1);
            const char* callbackId = JS_ToCString(ctx, jsCallbackId);
            std::string result = JS_ToCString(ctx, jsResult);
            JsParseCallbackResult(ctx, jsResult, KEY_STEPPER_PENDING_INDEX, result);
            auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
            ACE_DCHECK(instance);
            instance->GetDelegate()->SetCallBackResult(std::string(callbackId), result);

            JS_FreeCString(ctx, callbackId);
            JS_FreeValue(ctx, jsCallbackId);
            JS_FreeValue(ctx, jsResult);
        }
    } else if (methodName == APP_DESTROY_FINISH) {
        LOGD("JsHandleCallback: appDestroyFinish should release resource here");
    } else {
        LOGW("internal.jsResult not support method = %{private}s", methodName.c_str());
    }
    return JS_NULL;
}

JSValue JsHandleImage(JSContext* ctx, JSValueConst argv)
{
    auto src = JsParseRouteUrl(ctx, argv, "src");
    auto success = JsParseRouteUrl(ctx, argv, "success");
    auto fail = JsParseRouteUrl(ctx, argv, "fail");

    std::set<std::string> callbacks;
    if (!success.empty()) {
        callbacks.emplace("success");
    }
    if (!fail.empty()) {
        callbacks.emplace("fail");
    }

    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        return JS_NULL;
    }

    auto&& callback = [instance, success, fail](int32_t callbackType) {
        switch (callbackType) {
            case 0:
                instance->CallJs(success.c_str(), std::string("\"success\",null").c_str(), false);
                break;
            case 1:
                instance->CallJs(fail.c_str(), std::string("\"fail\",null").c_str(), false);
                break;
            default:
                break;
        }
    };
    instance->GetDelegate()->HandleImage(src, callback, callbacks);
    return JS_NULL;
}

void JsSetTimer(JSContext* ctx, JSValueConst argv, bool isInterval)
{
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (JS_IsObject(argv) && JS_IsArray(ctx, argv)) {
        JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
        if (len < 2) {
            LOGW("JsSetTimer: invalid callback value");
            return;
        }

        JSValue jsCallBackId = JS_GetProperty(ctx, argv, pTab[0].atom);
        JSValue jsDelay = JS_GetProperty(ctx, argv, pTab[1].atom);
        const char* callBackId = JS_ToCString(ctx, jsCallBackId);
        const char* delay = JS_ToCString(ctx, jsDelay);
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        LOGD("JsSetTimer callbackId: %{private}s, delay: %{private}s", callBackId, delay);
        instance->GetDelegate()->WaitTimer(std::string(callBackId), std::string(delay), isInterval, true);

        JS_FreeCString(ctx, callBackId);
        JS_FreeCString(ctx, delay);
        JS_FreeValue(ctx, jsCallBackId);
        JS_FreeValue(ctx, jsDelay);
        js_free(ctx, pTab);
    }
}

void JsClearTimeout(JSContext* ctx, JSValueConst argv)
{
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    if (JS_IsObject(argv) && JS_IsArray(ctx, argv)) {
        JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
        if (len < 1) {
            LOGW("JsClearTimeout: invalid callback value");
            return;
        }

        JSValue jsCallBackId = JS_GetProperty(ctx, argv, pTab[0].atom);
        const char* callBackId = JS_ToCString(ctx, jsCallBackId);
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        LOGD("ClearTimeOut callBackId: %{private}s", callBackId);
        instance->GetDelegate()->ClearTimer(std::string(callBackId));

        JS_FreeCString(ctx, callBackId);
        JS_FreeValue(ctx, jsCallBackId);
        js_free(ctx, pTab);
    }
}

JSValue JsSetLocale(JSContext* ctx, JSValueConst argv)
{
    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> localeJson = JsonUtil::ParseJsonString(args.get());
    if (localeJson) {
        std::string language;
        if (localeJson->GetValue(LOCALE_LANGUAGE) != nullptr && localeJson->GetValue(LOCALE_LANGUAGE)->IsString()) {
            language = localeJson->GetValue(LOCALE_LANGUAGE)->GetString();
        }
        std::string countryOrRegion;
        if (localeJson->GetValue(LOCALE_COUNTRY_OR_REGION) != nullptr &&
            localeJson->GetValue(LOCALE_COUNTRY_OR_REGION)->IsString()) {
            countryOrRegion = localeJson->GetValue(LOCALE_COUNTRY_OR_REGION)->GetString();
        }
        if (!countryOrRegion.empty() && !language.empty()) {
            auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
            ACE_DCHECK(instance);
            instance->ChangeLocale(language, countryOrRegion);
        }
    }
    return JS_NULL;
}

JSValue JsHandleSetTimeout(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    if (methodName == SET_TIMEOUT) {
        JsSetTimer(ctx, argv, false);
    } else if (methodName == CLEAR_TIMEOUT || methodName == CLEAR_INTERVAL) {
        JsClearTimeout(ctx, argv);
    } else if (methodName == SET_INTERVAL) {
        JsSetTimer(ctx, argv, true);
    } else {
        LOGW("Unsupported method for timer module!");
        return JS_NULL;
    }
    return JS_NULL;
}

JSValue JsHandleMediaQuery(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    if (methodName == ADD_LISTENER) {
        JsAddListener(ctx, argv);
    } else if (methodName == GET_DEVICE_TYPE) {
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        if (instance != nullptr) {
            auto mediaQuery = instance->GetDelegate()->GetMediaQueryInfoInstance();
            if (mediaQuery) {
                return JS_NewString(ctx, mediaQuery->GetDeviceType().c_str());
            }
        }
    } else {
        LOGW("system.meidaquery not support method = %{private}s", methodName.c_str());
    }
    return JS_NULL;
}

JSValue GetAppInfo(JSContext* ctx)
{
    QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    JSValue appName = JS_NewString(ctx, instance->GetDelegate()->GetAppName().c_str());
    JSValue versionName = JS_NewString(ctx, instance->GetDelegate()->GetVersionName().c_str());
    JSValue versionCode = JS_NewInt32(ctx, instance->GetDelegate()->GetVersionCode());

    JSValue resData = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, resData, "appName", appName);
    JS_SetPropertyStr(ctx, resData, "versionName", versionName);
    JS_SetPropertyStr(ctx, resData, "versionCode", versionCode);

    return resData;
}

JSValue Terminate(JSContext* ctx)
{
    QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    WeakPtr<PipelineContext> pipelineContextWeak = instance->GetDelegate()->GetPipelineContext();
    auto uiTaskExecutor = instance->GetDelegate()->GetUiTask();
    uiTaskExecutor.PostTask([pipelineContextWeak]() mutable {
        auto pipelineContext = pipelineContextWeak.Upgrade();
        if (pipelineContext) {
            pipelineContext->Finish();
        }
    });
    return JS_NULL;
}

void ParseFullWindowParams(JSContext* ctx, JSValue params, std::string& duration)
{
    JSPropertyEnum* tab = nullptr;
    uint32_t paramLen = 0;
    if (JS_IsObject(params)) {
        JS_GetOwnPropertyNames(ctx, &tab, &paramLen, params, JS_GPN_STRING_MASK);
        const char* jsDurationKey = JS_AtomToCString(ctx, tab[0].atom);
        if (jsDurationKey == nullptr) {
            JS_FreeAtom(ctx, tab[0].atom);
            js_free(ctx, tab);
            LOGE("jsDurationKey is null.");
            return;
        }
        if (std::strcmp(jsDurationKey, "duration") == 0) {
            JSValue valObject = JS_GetProperty(ctx, params, tab[0].atom);
            if (JS_IsString(valObject) || JS_IsNumber(valObject)) {
                ScopedString styleVal(ctx, valObject);
                const char* valDuration = styleVal.get();
                duration = valDuration;
            }
            JS_FreeValue(ctx, valObject);
        }
        JS_FreeAtom(ctx, tab[0].atom);
        JS_FreeCString(ctx, jsDurationKey);
    }
    js_free(ctx, tab);
}

JSValue RequestFullWindow(JSContext* ctx, JSValueConst argv)
{
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    int32_t duration = -1; // default scene
    if (JS_IsObject(argv) && JS_IsArray(ctx, argv)) {
        JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
        if (len < ARGS_FULL_WINDOW_LENGTH) {
            LOGW("RequestFullWindow: invalid callback value");
            js_free(ctx, pTab);
            return JS_NULL;
        }

        if (len == CUSTOM_FULL_WINDOW_LENGTH) {
            JSValue jsDuration = JS_GetProperty(ctx, argv, pTab[0].atom);
            std::string valDuration;
            ParseFullWindowParams(ctx, jsDuration, valDuration);
            if (!valDuration.empty()) {
                duration = StringToInt(valDuration);
            }
            if (duration < 0) {
                duration = -1; // default scene
            }
            JS_FreeValue(ctx, jsDuration);
        }
        js_free(ctx, pTab);
    }
    QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    WeakPtr<PipelineContext> pipelineContextWeak = instance->GetDelegate()->GetPipelineContext();
    auto uiTaskExecutor = instance->GetDelegate()->GetUiTask();
    uiTaskExecutor.PostTask([pipelineContextWeak, duration]() mutable {
        auto pipelineContext = pipelineContextWeak.Upgrade();
        if (pipelineContext) {
            pipelineContext->RequestFullWindow(duration);
        }
    });
    return JS_NULL;
}

void GetPackageInfoCallback(JSContext* ctx, JSValueConst jsMessage, const char* callbackId)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (!JS_IsObject(jsMessage)) {
        LOGE("GetPackageInfoCallback: jsMessage is not Object");
        instance->CallJs(
            callbackId, std::string("{\"arguments\":[\"jsMessage is not Object\",200],\"method\":\"fail\"}"), false);
        return;
    }
    JSValue jsPackageName = JS_GetPropertyStr(ctx, jsMessage, APP_PACKAGE_NAME);
    if (!JS_IsString(jsPackageName)) {
        LOGE("GetPackageInfoCallback: package name is not String");
        instance->CallJs(callbackId,
            std::string("{\"arguments\":[\"packageName is not available string\",202],\"method\":\"fail\"}"), false);
    } else {
        ScopedString packageName(ctx, jsPackageName);
        AceBundleInfo bundleInfo;
        if (AceApplicationInfo::GetInstance().GetBundleInfo(packageName.get(), bundleInfo)) {
            auto infoList = JsonUtil::Create(true);
            infoList->Put("versionName", bundleInfo.versionName.c_str());
            infoList->Put("versionCode", std::to_string(bundleInfo.versionCode).c_str());
            instance->CallJs(callbackId,
                std::string("{\"arguments\":[").append(infoList->ToString()).append("],\"method\":\"success\"}"),
                false);
        } else {
            LOGE("can not get info by GetBundleInfo");
            instance->CallJs(
                callbackId, std::string("{\"arguments\":[\"can not get info\",200],\"method\":\"fail\"}"), false);
        }
    }
    JS_FreeValue(ctx, jsPackageName);
}

JSValue GetPackageInfo(JSContext* ctx, JSValueConst argv)
{
    if (!JS_IsObject(argv)) {
        LOGE("GetPackageInfo: argv is not Object");
        return JS_NULL;
    }

    if (!JS_IsArray(ctx, argv)) {
        LOGE("GetPackageInfo: argv is not Array");
        return JS_NULL;
    }

    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;

    JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
    if (len < 2) {
        LOGE("GetPackageInfo: invalid callback value");
        js_free(ctx, pTab);
        return JS_EXCEPTION;
    }

    JSValue jsMessage = JS_GetProperty(ctx, argv, pTab[0].atom);
    JSValue jsCallbackId = JS_GetProperty(ctx, argv, pTab[1].atom);
    const char* callbackId = JS_ToCString(ctx, jsCallbackId);
    LOGD("system app getPackageInfo callBackID is %{public}s", callbackId);
    GetPackageInfoCallback(ctx, jsMessage, callbackId);

    JS_FreeCString(ctx, callbackId);
    JS_FreeValue(ctx, jsMessage);
    JS_FreeValue(ctx, jsCallbackId);
    js_free(ctx, pTab);

    return JS_NULL;
}

JSValue SetScreenOnVisible(JSContext* ctx, JSValueConst argv)
{
    if (!JS_IsObject(argv) || !JS_IsArray(ctx, argv)) {
        LOGE("SetScreenOnVisible: argv is not illegal");
        return JS_NULL;
    }
    JSPropertyEnum* pTab = nullptr;
    uint32_t len = 0;
    JS_GetOwnPropertyNames(ctx, &pTab, &len, argv, JS_GPN_STRING_MASK);
    if (len < 2) {
        LOGE("SetScreenOnVisible: invalid callback value");
        js_free(ctx, pTab);
        return JS_EXCEPTION;
    }
    JSValue jsObject = JS_GetProperty(ctx, argv, pTab[0].atom);
    std::string flag = "false";
    if (JS_IsObject(jsObject)) {
        JSValue flagValue = JS_GetPropertyStr(ctx, jsObject, APP_SCREEN_ON_VISIBLE_FLAG);
        if (JS_IsBool(flagValue)) {
            ScopedString flagValueStr(ctx, flagValue);
            flag = flagValueStr.get();
        }
    }
    JSValue jsCallbackId = JS_GetProperty(ctx, argv, pTab[1].atom);
    ScopedString callbackId(ctx, jsCallbackId);
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (StringToBool(flag)) {
        instance->CallJs(callbackId.get(), R"({"arguments":[], "method":"success"})");
    } else {
        instance->CallJs(
            callbackId.get(), R"({"arguments":["fail to set false flag in rich platform", 200],"method":"fail"})");
    }
    JS_FreeValue(ctx, jsObject);
    JS_FreeValue(ctx, jsCallbackId);
    js_free(ctx, pTab);
    return JS_NULL;
}

JSValue SetSwipeToDismiss(JSContext* ctx, JSValueConst argv)
{
    if (!JS_IsObject(argv) || !JS_IsArray(ctx, argv)) {
        LOGE("SetSwipeToDismiss: argv is not illegal");
        return JS_NULL;
    }
    bool forbideQuit = false;
    ScopedString args(ctx, argv);
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(args.get());
    if (argsPtr != nullptr && argsPtr->IsBool()) {
        forbideQuit = argsPtr->GetBool();
    }
    QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    WeakPtr<PipelineContext> pipelineContextWeak = instance->GetDelegate()->GetPipelineContext();
    auto uiTaskExecutor = instance->GetDelegate()->GetUiTask();
    uiTaskExecutor.PostTask([pipelineContextWeak, forbideQuit]() mutable {
        auto pipelineContext = pipelineContextWeak.Upgrade();
        if (pipelineContext) {
            pipelineContext->SetForbidePlatformQuit(forbideQuit);
        }
    });

    return JS_NULL;
}

JSValue JsHandleAppApi(JSContext* ctx, JSValueConst argv, const std::string& methodName)
{
    if (methodName == APP_GET_INFO) {
        return GetAppInfo(ctx);
    } else if (methodName == APP_TERMINATE) {
        return Terminate(ctx);
    } else if (methodName == APP_GET_PACKAGE_INFO) {
        return GetPackageInfo(ctx, argv);
    } else if (methodName == APP_REQUEST_FULL_WINDOW) {
        return RequestFullWindow(ctx, argv);
    } else if (methodName == APP_SCREEN_ON_VISIBLE) {
        return SetScreenOnVisible(ctx, argv);
    } else if (methodName == APP_SET_SWIPE_TO_DISMISS) {
        return SetSwipeToDismiss(ctx, argv);
    } else {
        return JS_NULL;
    }
}

void ProcessSystemParam(std::unique_ptr<JsonValue>& infoList)
{
    std::string tmp = SystemProperties::GetBrand();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("brand", tmp.c_str());
    }
    tmp = SystemProperties::GetManufacturer();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("manufacturer", tmp.c_str());
    }
    tmp = SystemProperties::GetModel();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("model", tmp.c_str());
    }
    tmp = SystemProperties::GetProduct();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("product", tmp.c_str());
    }
    tmp = SystemProperties::GetApiVersion();
    if (tmp != SystemProperties::INVALID_PARAM) {
        char* tmpEnd = nullptr;
        infoList->Put(
            "apiVersion", static_cast<int32_t>(std::strtol(SystemProperties::GetApiVersion().c_str(), &tmpEnd, 10)));
    }
    tmp = SystemProperties::GetReleaseType();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("releaseType", tmp.c_str());
    }
    tmp = SystemProperties::GetParamDeviceType();
    if (tmp != SystemProperties::INVALID_PARAM) {
        infoList->Put("deviceType", tmp.c_str());
    }
}

std::pair<std::string, bool> GetDeviceInfo()
{
    static constexpr uint8_t paramNumber = 13;
    auto infoList = JsonUtil::Create(true);
    ProcessSystemParam(infoList);

    if (!AceApplicationInfo::GetInstance().GetLanguage().empty()) {
        infoList->Put("language", AceApplicationInfo::GetInstance().GetLanguage().c_str());
    }
    if (!AceApplicationInfo::GetInstance().GetCountryOrRegion().empty()) {
        infoList->Put("region", AceApplicationInfo::GetInstance().GetCountryOrRegion().c_str());
    }

    int32_t width = SystemProperties::GetWidth();
    if (width != 0) {
        infoList->Put("windowWidth", width);
    }
    int32_t height = SystemProperties::GetHeight();
    if (height != 0) {
        infoList->Put("windowHeight", height);
    }
    infoList->Put("screenDensity", SystemProperties::GetResolution());

    bool isRound = SystemProperties::GetIsScreenRound();
    if (isRound) {
        infoList->Put("screenShape", "circle");
    } else {
        infoList->Put("screenShape", "rect");
    }

    bool isParamValid = false;
    uint8_t count = 0;
    auto child = infoList->GetChild();
    while (child->IsValid()) {
        child = child->GetNext();
        ++count;
    }
    if (count == paramNumber) {
        isParamValid = true;
    }
    return std::make_pair<std::string, bool>(infoList->ToString(), std::move(isParamValid));
}

JSValue JsGetDeviceInfo(JSContext* ctx, JSValueConst argv)
{
    const char* callbackId = JS_ToCString(ctx, argv);
    if (callbackId == nullptr) {
        LOGE("system device getInfo callBackID is null");
    } else {
        LOGD("system device getInfo callBackID = %{public}s", callbackId);
        auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        std::pair<std::string, bool> ret = GetDeviceInfo();
        if (ret.second) {
            instance->CallJs(callbackId,
                std::string("{\"arguments\":[").append(ret.first).append("],\"method\":\"success\"}"), false);
        } else {
            instance->CallJs(callbackId,
                std::string("{\"arguments\":[").append(ret.first).append(",200],\"method\":\"fail\"}"), false);
        }
        JS_FreeCString(ctx, callbackId);
    }

    return JS_NULL;
}

JSValue GetLocale(JSContext* ctx)
{
    JSValue language = JS_NewString(ctx, AceApplicationInfo::GetInstance().GetLanguage().c_str());
    JSValue countryOrRegion = JS_NewString(ctx, AceApplicationInfo::GetInstance().GetCountryOrRegion().c_str());
    JSValue dir = JS_NewString(
        ctx, AceApplicationInfo::GetInstance().IsRightToLeft() ? LOCALE_TEXT_DIR_RTL : LOCALE_TEXT_DIR_LTR);
    JSValue unicodeSetting = JS_NewString(ctx, AceApplicationInfo::GetInstance().GetUnicodeSetting().c_str());

    JSValue resData = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, resData, LOCALE_LANGUAGE, language);
    JS_SetPropertyStr(ctx, resData, LOCALE_COUNTRY_OR_REGION, countryOrRegion);
    JS_SetPropertyStr(ctx, resData, LOCALE_TEXT_DIR, dir);
    JS_SetPropertyStr(ctx, resData, LOCALE_UNICODE_SETTING, unicodeSetting);

    return resData;
}

JSValue JsCallComponent(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    if ((argv == nullptr) || (argc != 3)) {
        LOGE("argc error, argc = %{private}d", argc);
        return JS_NULL;
    }
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("JsCallComponent failed, instance is null.");
        return JS_NULL;
    }
    auto page = GetRunningPage(ctx);
    if (!page) {
        LOGE("JsCallComponent failed, page is null.");
        return JS_NULL;
    }
    int32_t nodeId;
    JS_ToInt32(ctx, &nodeId, argv[0]);
    nodeId = (nodeId == 0) ? DOM_ROOT_NODE_ID_BASE + page->GetPageId() : nodeId;
    ScopedString methodName(ctx, argv[1]);
    ScopedString args(ctx, argv[2]);
    LOGD("nodeId = %{private}d, methodName = %{private}s, args = %{private}s", nodeId, methodName.get(), args.get());
    // handle canvas getContext
    if (std::strcmp(methodName.get(), "getContext") == 0) {
        auto bridge = AceType::DynamicCast<CanvasBridge>(page->GetBridgeById(nodeId));
        if (bridge) {
            bridge->HandleJsContext(ctx, nodeId, args.get());
            return bridge->GetRenderContext();
        }
        return JS_NULL;
    } else if (std::strcmp(methodName.get(), "toDataURL") == 0) {
        auto bridge = AceType::DynamicCast<CanvasBridge>(page->GetBridgeById(nodeId));
        if (bridge) {
            bridge->HandleToDataURL(ctx, nodeId, args.get());
            return bridge->GetDataURL();
        }
        return JS_NULL;
    } else if (std::strcmp(methodName.get(), "getScrollOffset") == 0) {
        // handle getScrollOffset method of scroll view, like div, stack and list.
        return CompoentApiBridge::JsGetScrollOffset(ctx, nodeId);
    } else if (std::strcmp(methodName.get(), "getBoundingClientRect") == 0) {
        return CompoentApiBridge::JsGetBoundingRect(ctx, nodeId);
    }

    auto resultValue = JSValue();
    // handle animation animate method
    if (std::strcmp(methodName.get(), "animate") == 0) {
        resultValue = AnimationBridgeUtils::CreateAnimationContext(ctx, page->GetPageId(), nodeId);
        auto animationBridge = AceType::MakeRefPtr<AnimationBridge>(ctx, resultValue, nodeId);
        auto task = AceType::MakeRefPtr<AnimationBridgeTaskCreate>(animationBridge, args.get());
        instance->AddAnimationBridge(animationBridge);
        page->PushCommand(Referenced::MakeRefPtr<JsCommandAnimation>(nodeId, task));
    } else if (std::strcmp(methodName.get(), "currentOffset") == 0) {
        // handle list currentOffset method
        return ListBridge::JsGetCurrentOffset(ctx, nodeId);
    } else if (std::strcmp(methodName.get(), "getState") == 0) {
        // handle image animator getState method.
        return ImageAnimatorBridge::JsGetState(ctx, nodeId);
    } else {
        page->PushCommand(Referenced::MakeRefPtr<JsCommandCallDomElementMethod>(nodeId, methodName.get(), args.get()));
    }
    // focus method should delayed util show attribute update.
    if (page->CheckPageCreated() && strcmp(DOM_FOCUS, methodName.get()) != 0) {
        QjsEngineInstance* instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
        ACE_DCHECK(instance);
        instance->GetDelegate()->TriggerPageUpdate(page->GetPageId(), true);
    }
    return resultValue;
}

JSValue JsCallConfiguration(JSContext* ctx, const std::string& method, JSValueConst argv)
{
    if (CONFIGURATION_GET_LOCALE == method) {
        return GetLocale(ctx);
    } else if (CONFIGURATION_SET_LOCALE == method) {
        return JsSetLocale(ctx, argv);
    }
    return JS_NULL;
}

JSValue JsHandleModule(std::string moduleName, std::string methodName, JSContext* ctx, JSValueConst* argv)
{
    static const LinearMapNode<JSValue (*)(JSContext*, JSValueConst*, const std::string&)> jsHandleMap[] = {
        { "animation",
            [](JSContext* ctx, JSValueConst* argv, const std::string& methodName) {
                return JsHandleAnimationFrame(ctx, argv[1], methodName);
            } },
        { "internal.jsResult",
            [](JSContext* ctx, JSValueConst* argv, const std::string& methodName) {
                return JsHandleCallback(ctx, argv[1], methodName);
            } },
        { "system.app", [](JSContext* ctx, JSValueConst* argv,
                            const std::string& methodName) { return JsHandleAppApi(ctx, argv[1], methodName); } },
        { "system.configuration",
            [](JSContext* ctx, JSValueConst* argv, const std::string& methodName) {
                return JsCallConfiguration(ctx, methodName, argv[1]);
            } },
        { "system.device",
            [](JSContext* ctx, JSValueConst* argv, const std::string& methodName) {
                if (methodName == "getInfo") {
                    return JsGetDeviceInfo(ctx, argv[1]);
                } else {
                    return JS_NULL;
                }
            } },
        { "system.image", [](JSContext* ctx, JSValueConst* argv,
                              const std::string& methodName) { return JsHandleImage(ctx, argv[1]); } },
        { "system.mediaquery",
            [](JSContext* ctx, JSValueConst* argv, const std::string& methodName) {
                return JsHandleMediaQuery(ctx, argv[1], methodName);
            } },
        { "system.prompt", [](JSContext* ctx, JSValueConst* argv,
                               const std::string& methodName) { return JsHandlePrompt(ctx, argv[1], methodName); } },
        { "system.router", [](JSContext* ctx, JSValueConst* argv,
                               const std::string& methodName) { return JsHandlePageRoute(ctx, argv[1], methodName); } },
        { "timer", [](JSContext* ctx, JSValueConst* argv,
                       const std::string& methodName) { return JsHandleSetTimeout(ctx, argv[1], methodName); } },
    };

    auto jsHandleIter = BinarySearchFindIndex(jsHandleMap, ArraySize(jsHandleMap), moduleName.c_str());
    if (jsHandleIter != -1) {
        return jsHandleMap[jsHandleIter].value(ctx, argv, methodName);
    }

    return JS_NULL;
}

JSValue JsCallNative(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JsCallNative");

    if ((argv == nullptr) || (argc != 2)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }

    ScopedString moduleAndMethod(ctx, argv[0]);
    ScopedString args(ctx, argv[1]);
    LOGD("JsCallNative moduleAndMethod = %{private}s, args = %{private}s", moduleAndMethod.get(), args.get());

    std::unique_ptr<JsonValue> moduleAndMethodPtr = JsonUtil::ParseJsonString(moduleAndMethod.get());
    if (!moduleAndMethodPtr) {
        LOGE("Get moduleAndMethod from argv failed");
        return JS_NULL;
    }

    std::unique_ptr<JsonValue> modulePtr = moduleAndMethodPtr->GetValue("module");
    if (!modulePtr) {
        LOGE("Get module from moduleAndMethodPtr failed");
        return JS_NULL;
    }

    std::unique_ptr<JsonValue> methodPtr = moduleAndMethodPtr->GetValue("method");
    if (!methodPtr) {
        LOGE("Get method from moduleAndMethodPtr failed");
        return JS_NULL;
    }

    const std::string moduleName = modulePtr->GetString();
    const std::string methodName = methodPtr->GetString();

    return JsHandleModule(moduleName, methodName, ctx, argv);
}

#ifdef ENABLE_JS_DEBUG
JSValue JsCompileAndRunBundle(JSContext* ctx, JSValueConst thisVal, int argc, JSValueConst* argv)
{
    ScopedString str(ctx, argv[0]);
    ScopedString url(ctx, argv[1]);
    JSValue CppToJSRet = JS_Eval(ctx, str.get(), strlen(str.get()), url.get(), JS_EVAL_TYPE_GLOBAL);

    if (JS_IsException(CppToJSRet)) {
        LOGE("Qjs JsCompileAndRunBundle FAILED !!");
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::COMPILE_AND_RUN_BUNDLE_ERROR);
        return JS_NULL;
    }

    js_std_loop(ctx);
    return CppToJSRet;
}
#endif

JSValue AppLogPrint(JSContext* ctx, JsLogLevel level, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("AppLogPrint(level=%d)", static_cast<int32_t>(level));

    // Should have 1 parameters.
    if ((argv == nullptr) || (argc == 0)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }
    ScopedString printLog(ctx, argv[0]);

    switch (level) {
        case JsLogLevel::DEBUG:
            APP_LOGD("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::INFO:
            APP_LOGI("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::WARNING:
            APP_LOGW("app Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::ERROR:
            APP_LOGE("app Log: %{public}s", printLog.get());
            break;
        default:
            break;
    }

    return JS_NULL;
}

JSValue AppLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return AppLogPrint(ctx, JsLogLevel::DEBUG, value, argc, argv);
}

JSValue AppDebugLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return AppLogPrint(ctx, JsLogLevel::DEBUG, value, argc, argv);
}

JSValue AppInfoLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return AppLogPrint(ctx, JsLogLevel::INFO, value, argc, argv);
}

JSValue AppWarnLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return AppLogPrint(ctx, JsLogLevel::WARNING, value, argc, argv);
}

JSValue AppErrorLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return AppLogPrint(ctx, JsLogLevel::ERROR, value, argc, argv);
}

JSValue JsLogPrint(JSContext* ctx, JsLogLevel level, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JsLogPrint(level=%d)", static_cast<int32_t>(level));

    // Should have 1 parameters.
    if ((argv == nullptr) || (argc == 0)) {
        LOGE("the arg is error");
        return JS_EXCEPTION;
    }
    ScopedString printLog(ctx, argv[0]);

    switch (level) {
        case JsLogLevel::DEBUG:
            LOGD("ace Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::INFO:
            LOGI("ace Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::WARNING:
            LOGW("ace Log: %{public}s", printLog.get());
            break;
        case JsLogLevel::ERROR:
            LOGE("ace Log: %{public}s", printLog.get());
            break;
    }

    return JS_NULL;
}

JSValue JsLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return JsLogPrint(ctx, JsLogLevel::DEBUG, value, argc, argv);
}

JSValue JsDebugLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return JsLogPrint(ctx, JsLogLevel::DEBUG, value, argc, argv);
}

JSValue JsInfoLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return JsLogPrint(ctx, JsLogLevel::INFO, value, argc, argv);
}

JSValue JsWarnLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return JsLogPrint(ctx, JsLogLevel::WARNING, value, argc, argv);
}

JSValue JsErrorLogPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    return JsLogPrint(ctx, JsLogLevel::ERROR, value, argc, argv);
}

JSValue JsPerfPrint(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    std::string ret = JsApiPerf::GetInstance().PrintToLogs();

    JSValue retString = JS_NewString(ctx, ret.c_str());

    return retString;
}

JSValue JsPerfSleep(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    int32_t valInt = 0;
    JS_ToInt32(ctx, &valInt, argv[0]);

    usleep(valInt);

    return JS_NULL;
}

JSValue JsPerfBegin(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    int64_t currentTime = GetMicroTickCount();
    ScopedString functionName(ctx, argv[0]);

    JsApiPerf::GetInstance().InsertJsBeginLog(functionName.get(), currentTime);

    return JS_NULL;
}

JSValue JsPerfEnd(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    int64_t currentTime = GetMicroTickCount();
    ScopedString functionName(ctx, argv[0]);

    JsApiPerf::GetInstance().InsertJsEndLog(functionName.get(), currentTime);

    return JS_NULL;
}

JSValue JSHiViewReport(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    // Should have 2 parameters.
    if ((argv == nullptr) || (argc != 2)) {
        LOGE("the arg is error %{public}d", argc);
        return JS_EXCEPTION;
    }
    if (JS_IsInteger(argv[0]) && JS_IsString(argv[1])) {
        ScopedString eventId(ctx, argv[0]);
        ScopedString eventJsonStr(ctx, argv[1]);
        std::string jsonStr = eventJsonStr.get();
        EventReport::JsEventReport(StringToInt(eventId.get()), jsonStr);
        LOGD("JsEventReport success");
        return JS_NULL;
    } else {
        LOGE("parameter type error ");
        return JS_EXCEPTION;
    }
}

JSValue JsPluralRulesFormat(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    // Should have one parameters.
    if ((argv == nullptr) || (argc != 1)) {
        LOGE("the arg is error %{public}d", argc);
        return JS_NULL;
    }
    if (JS_IsInteger(argv[0])) {
        ScopedString choice(ctx, argv[0]);
        JSValue result =
            JS_NewString(ctx, Localization::GetInstance()->PluralRulesFormat(StringToDouble(choice.get())).c_str());
        return result;
    } else {
        LOGE("parameter type error ");
        return JS_NULL;
    }
}

JSValue JsLoadIntl(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("QjsEngine::LoadIntl");
    LOGI("JsLoadIntl");

    JSValue ret = CallReadObject(ctx, js_intl_support, js_intl_support_size, true);
    if (JS_IsException(ret)) {
        LOGE("JsLoadIntl failed!");
    }

    return ret;
}

JSValue JsLoadLocaleData(JSContext* ctx, JSValueConst value, int32_t argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("QjsEngine::LoadLocaleData");
    LOGI("Add LocaleData");

    ScopedString lib(ctx, argv[0]);    // select which lib(intl or intl-relative-time-format) to use
    ScopedString locale(ctx, argv[1]); // select locale

    std::string key;
    if (strcmp(lib.get(), "intl") == 0) {
        key.append("intl_");
    } else {
        key.append("intl_relative_");
    }
    key.append(locale.get());
    std::replace(key.begin(), key.end(), '-', '_');

    std::unordered_map<std::string, std::vector<const void*>> data = GetLocaleDatasMap();
    if (data.find(key) != data.end()) {
        std::vector<const void*> val = data[key];
        const uint32_t* len = static_cast<const uint32_t*>(val[0]);
        const uint8_t* data = static_cast<const uint8_t*>(val[1]);
        JSValue ret = CallReadObject(ctx, data, *len, true);
        LOGI("load data: %s", key.c_str());
        return ret;
    } else {
        LOGE("load data: %s not found!", key.c_str());
        return JS_NULL;
    }
}

// Follow definition in quickjs.
#define JS_CFUNC_DEF_CPP(name, length, func)                            \
    {                                                                   \
        name, JS_PROP_WRITABLE | JS_PROP_CONFIGURABLE, JS_DEF_CFUNC, 0, \
        {                                                               \
            {                                                           \
                length, JS_CFUNC_generic,                               \
                {                                                       \
                    func                                                \
                }                                                       \
            }                                                           \
        }                                                               \
    }

const JSCFunctionListEntry JS_ACE_FUNCS[] = {
    JS_CFUNC_DEF_CPP("domCreateBody", 5, JsDomCreateBody),
    JS_CFUNC_DEF_CPP("domAddElement", 9, JsDomAddElement),
    JS_CFUNC_DEF_CPP("updateElementAttrs", 3, JsUpdateElementAttrs),
    JS_CFUNC_DEF_CPP("updateElementStyles", 3, JsUpdateElementStyles),
    JS_CFUNC_DEF_CPP("onCreateFinish", 0, JsOnCreateFinish),
    JS_CFUNC_DEF_CPP("onUpdateFinish", 0, JsOnUpdateFinish),
    JS_CFUNC_DEF_CPP("removeElement", 2, JsRemoveElement),
    JS_CFUNC_DEF_CPP("callNative", 1, JsCallNative),
    JS_CFUNC_DEF_CPP("callComponent", 3, JsCallComponent),
    JS_CFUNC_DEF_CPP("loadIntl", 0, JsLoadIntl),
    JS_CFUNC_DEF_CPP("loadLocaleData", 0, JsLoadLocaleData),
#ifdef ENABLE_JS_DEBUG
    JS_CFUNC_DEF_CPP("compileAndRunBundle", 4, JsCompileAndRunBundle),
#endif
};

int32_t JsAceInit(JSContext* ctx, JSModuleDef* moduleDef)
{
    return JS_SetModuleExportList(ctx, moduleDef, JS_ACE_FUNCS, countof(JS_ACE_FUNCS));
}

JSModuleDef* InitAceModules(JSContext* ctx)
{
    LOGD("QjsEngine: InitAceModules");
    JSModuleDef* jsModule = JS_NewCModule(ctx, "ace", JsAceInit);
    if (jsModule == nullptr) {
        return nullptr;
    }
    JS_AddModuleExportList(ctx, jsModule, JS_ACE_FUNCS, countof(JS_ACE_FUNCS));
    return jsModule;
}

void InitJsConsoleObject(JSContext* ctx, const JSValue& globalObj)
{
    JSValue console, aceConsole;
    // app log method
    console = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, console, "log", JS_NewCFunction(ctx, AppLogPrint, "log", 1));
    JS_SetPropertyStr(ctx, console, "debug", JS_NewCFunction(ctx, AppDebugLogPrint, "debug", 1));
    JS_SetPropertyStr(ctx, console, "info", JS_NewCFunction(ctx, AppInfoLogPrint, "info", 1));
    JS_SetPropertyStr(ctx, console, "warn", JS_NewCFunction(ctx, AppWarnLogPrint, "warn", 1));
    JS_SetPropertyStr(ctx, console, "error", JS_NewCFunction(ctx, AppErrorLogPrint, "error", 1));
    JS_SetPropertyStr(ctx, globalObj, "console", console);

    // js framework log method
    aceConsole = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, aceConsole, "log", JS_NewCFunction(ctx, JsLogPrint, "log", 1));
    JS_SetPropertyStr(ctx, aceConsole, "debug", JS_NewCFunction(ctx, JsDebugLogPrint, "debug", 1));
    JS_SetPropertyStr(ctx, aceConsole, "info", JS_NewCFunction(ctx, JsInfoLogPrint, "info", 1));
    JS_SetPropertyStr(ctx, aceConsole, "warn", JS_NewCFunction(ctx, JsWarnLogPrint, "warn", 1));
    JS_SetPropertyStr(ctx, aceConsole, "error", JS_NewCFunction(ctx, JsErrorLogPrint, "error", 1));
    JS_SetPropertyStr(ctx, globalObj, "aceConsole", aceConsole);
}

bool InitJsContext(JSContext* ctx, size_t maxStackSize, int32_t instanceId, const QjsEngineInstance* qjsEngineInstance)
{
    LOGI("QjsEngine: InitJsContext");
    if (ctx == nullptr) {
        LOGE("Qjs cannot allocate JS context");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    // Note: default 256KB is not enough
    JS_SetMaxStackSize(ctx, maxStackSize);

    // Inject ace native functions module
    InitAceModules(ctx);

    JSValue globalObj, perfUtil;
    globalObj = JS_GetGlobalObject(ctx);
    perfUtil = JS_NewObject(ctx);

    InitJsConsoleObject(ctx, globalObj);

    JS_SetPropertyStr(ctx, perfUtil, "printlog", JS_NewCFunction(ctx, JsPerfPrint, "printlog", 0));
    JS_SetPropertyStr(ctx, perfUtil, "sleep", JS_NewCFunction(ctx, JsPerfSleep, "sleep", 1));
    JS_SetPropertyStr(ctx, perfUtil, "begin", JS_NewCFunction(ctx, JsPerfBegin, "begin", 1));
    JS_SetPropertyStr(ctx, perfUtil, "end", JS_NewCFunction(ctx, JsPerfEnd, "end", 1));
    JS_SetPropertyStr(ctx, globalObj, "perfutil", perfUtil);

    NativeObjectInfo* nativeObjectInfo = new NativeObjectInfo();
    nativeObjectInfo->nativeObject = qjsEngineInstance->GetDelegate()->GetAbility();
    JSValue abilityValue = JS_NewExternal(ctx, nativeObjectInfo, [](JSContext* ctx, void *data, void *hint) {
        NativeObjectInfo *info = (NativeObjectInfo *)data;
        if (info) {
            delete info;
        }
    }, nullptr);
    JS_SetPropertyStr(ctx, globalObj, "ability", abilityValue);

    JSValue hiView;
    hiView = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, hiView, "report", JS_NewCFunction(ctx, JSHiViewReport, "report", 2));
    JS_SetPropertyStr(ctx, globalObj, "hiView", hiView);

    JSValue i18nPluralRules;
    i18nPluralRules = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, i18nPluralRules, "select", JS_NewCFunction(ctx, JsPluralRulesFormat, "select", 1));
    JS_SetPropertyStr(ctx, globalObj, "i18nPluralRules", i18nPluralRules);

    const char* str = "import * as ace from 'ace';\n"
                      "var global = globalThis;\n"
                      "global.ace = ace;\n"
#ifdef ENABLE_JS_DEBUG
                      "global.compileAndRunBundle = ace.compileAndRunBundle;\n"
#endif
                      "global.callNative = ace.callNative;\n";

    if (JS_CALL_FAIL == CallEvalBuf(ctx, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE, instanceId)) {
        LOGW("Qjs created JS context but failed to init Ace modules!");
    }

    JS_FreeValue(ctx, globalObj);
    return true;
}

JSValue LoadJsFramework(JSContext* ctx, const uint8_t buf[], const uint32_t bufSize, int32_t instanceId)
{
    ACE_SCOPED_TRACE("LoadJsFramework");

    LOGI("Qjs loading JS framework");
    JSValue ret = CallReadObject(ctx, buf, bufSize, true, instanceId);
    if (JS_IsException(ret)) {
        LOGD("Qjs loading JSFramework failed!");
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::LOAD_JS_FRAMEWORK_ERROR, instanceId);
    }

    return ret;
}

} // namespace

// -----------------------
// Start QjsEngineInstance
// -----------------------
void QjsEngineInstance::FlushCommandBuffer(void* context, const std::string& command)
{
    LOGI("flush command buffer");
    auto ctx = static_cast<JSContext*>(context);
    int32_t result = CallEvalBuf(ctx, command.c_str(), command.size(), "<input>", JS_EVAL_TYPE_GLOBAL, instanceId_);
    if (JS_CALL_FAIL == result) {
        LOGE("failed to flush command buffer");
    }
}
bool QjsEngineInstance::InitJsEnv(JSRuntime* runtime, JSContext* context)
{
    LOGI("InitJsEnv");
    if (runtime == nullptr) {
        runtime = JS_NewRuntime();
    }
    if (runtime_ != nullptr) {
        JS_FreeRuntime(runtime_);
    }
    runtime_ = runtime;
    if (runtime_ == nullptr) {
        LOGE("Qjs cannot allocate JS runtime");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    if (context == nullptr) {
        context = JS_NewContext(runtime_);
    }
    if (context_ != nullptr) {
        JS_FreeContext(context_);
    }
    context_ = context;
    if (!InitJsContext(context_, MAX_STACK_SIZE, instanceId_, this)) {
        LOGE("Qjs cannot allocate JS context");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        JS_FreeRuntime(runtime_);
        return false;
    }

    auto groupJsBridge = AceType::DynamicCast<QuickJsGroupJsBridge>(frontendDelegate_->GetGroupJsBridge());
    if (!groupJsBridge || JS_CALL_FAIL == groupJsBridge->InitializeGroupJsBridge(context_)) {
        LOGE("Qjs Initialize GroupJsBridge failed!");
        EventReport::SendJsException(JsExcepType::JS_ENGINE_INIT_ERR);
        return false;
    }

    JSValue retVal = LoadJsFramework(GetQjsContext(), js_framework, js_framework_size, instanceId_);
    bool result = JS_IsException(retVal) ? false : true;
    if (context) {
        JS_FreeValue(context, retVal);
    }

    std::string intlHook("                                       \
        globalThis.Intl = {                                      \
            NumberFormat: function() {                           \
                delete globalThis.Intl;                          \
                ace.loadIntl();                                  \
                return Intl.NumberFormat(...arguments);          \
            },                                                   \
            DateTimeFormat: function() {                         \
               delete globalThis.Intl;                           \
               ace.loadIntl();                                   \
               return Intl.DateTimeFormat(...arguments);         \
            },                                                   \
            RelativeTimeFormat: function() {                     \
                delete globalThis.Intl;                          \
                ace.loadIntl();                                  \
                return new Intl.RelativeTimeFormat(...arguments);\
            }                                                    \
        }                                                        \
    ");

    if (JS_CALL_FAIL ==
        CallEvalBuf(context, intlHook.c_str(), intlHook.size(), "<input>", JS_EVAL_TYPE_GLOBAL, instanceId_)) {
        LOGE("Intl init failed!");
    }

    return result;
}

void QjsEngineInstance::AddAnimationBridge(const WeakPtr<AnimationBridge>& value)
{
    animations_.emplace_back(value);
}

void QjsEngineInstance::RemoveAnimationBridge()
{
    for (auto it = animations_.begin(); it != animations_.end();) {
        auto ref = it->Upgrade();
        if (!ref) {
            it = animations_.erase(it);
        } else {
            ++it;
        }
    }
}

void QjsEngineInstance::FreeGroupJsBridge()
{
    // free JSValue reference of channel bridge and animation bridge
    if (!frontendDelegate_) {
        LOGE("frontend delegate is null.");
        return;
    }

    auto groupJsBridge = AceType::DynamicCast<QuickJsGroupJsBridge>(frontendDelegate_->GetGroupJsBridge());
    if (!groupJsBridge) {
        LOGE("group js bridge is null.");
        return;
    }

    groupJsBridge->Uninitialize();
}

void QjsEngineInstance::FreeAnimationBridges()
{
    for (auto& weak : animations_) {
        auto ref = weak.Upgrade();
        if (!ref) {
            continue;
        }
        ref->Uninitialize();
    }
    animations_.clear();
}

QjsEngineInstance::~QjsEngineInstance()
{
    FreeGroupJsBridge();
    FreeAnimationBridges();

    if (context_) {
        JS_FreeContext(context_);
    }
    if (runtime_) {
        JS_FreeRuntime(runtime_);
    }
}

JSValue QjsEngineInstance::FireJsEvent(const std::string& param)
{
    LOGI("FireJsEvent");
    JSContext* ctx = GetQjsContext();
    ACE_DCHECK(ctx);
    QjsHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue callJsFunc = QjsUtils::GetPropertyStr(ctx, globalObj, "callJS");
    if (!JS_IsFunction(ctx, callJsFunc)) {
        LOGE("cannot find 'callJS' function from global object, this should not happen!");
        JS_FreeValue(ctx, globalObj);
        return JS_UNDEFINED;
    }

    if (!runningPage_) {
        LOGE("runningPage_ is null!");
        JS_FreeValue(ctx, globalObj);
        return JS_UNDEFINED;
    }
    JSValueConst argv[] = {
        QjsUtils::NewString(ctx, std::to_string(runningPage_->GetPageId()).c_str()),
        QjsUtils::ParseJSON(ctx, param.c_str(), param.size(), nullptr),
    };

    JSValue retVal = JS_Call(ctx, callJsFunc, JS_UNDEFINED, countof(argv), argv);

    JS_FreeValue(ctx, globalObj);

    // It is up to the caller to check this value. No exception checks here.
    return retVal;
}

void QjsEngineInstance::CallJs(const std::string& callbackId, const std::string& args, bool keepAlive, bool isGlobal)
{
    ACE_SCOPED_TRACE("QjsEngineInstance::CallJS");

    std::string keepAliveStr = keepAlive ? "true" : "false";
    std::string callBuff = std::string("[{\"args\": [\"")
                               .append(callbackId)
                               .append("\",")
                               .append(args)
                               .append(",")
                               .append(keepAliveStr)
                               .append("], \"method\":\"callback\"}]");
    LOGD("CallJs string: %{private}s", callBuff.c_str());

    JSContext* ctx = GetQjsContext();
    QjsHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue callJsFunc = QjsUtils::GetPropertyStr(ctx, globalObj, "callJS");
    if (!JS_IsFunction(ctx, callJsFunc)) {
        LOGE("cannot find 'callJS' function from global object, this should not happen!");
        JS_FreeValue(ctx, globalObj);
        return;
    }

    int32_t instanceId = isGlobal ? DEFAULT_APP_ID : stagingPage_->GetPageId();
    JSValueConst argv[] = {
        QjsUtils::NewString(ctx, std::to_string(instanceId).c_str()),
        QjsUtils::ParseJSON(ctx, callBuff.c_str(), callBuff.size(), nullptr),
    };
    QjsUtils::Call(ctx, callJsFunc, JS_UNDEFINED, countof(argv), argv);

    JS_FreeValue(ctx, globalObj);
}

void QjsEngineInstance::CallAnimationFinishJs(JSValue animationContext)
{
    JSContext* ctx = GetQjsContext();
    QjsHandleScope handleScope(ctx);
    auto proto = QjsUtils::GetPropertyStr(ctx, animationContext, "onfinish");
    if (!JS_IsFunction(ctx, proto)) {
        LOGD("cannot find 'CallAnimationFinishJs' function from global object, this should not happen!");
        return;
    }
    LOGD("animation onfinish event call");
    QjsUtils::Call(ctx, proto, animationContext, 0, {});
}

void QjsEngineInstance::CallAnimationCancelJs(JSValue animationContext)
{
    JSContext* ctx = GetQjsContext();
    QjsHandleScope handleScope(ctx);
    auto proto = QjsUtils::GetPropertyStr(ctx, animationContext, "oncancel");
    if (!JS_IsFunction(ctx, proto)) {
        return;
    }

    LOGD("animation oncancel event call");
    QjsUtils::Call(ctx, proto, animationContext, 0, {});
}

void QjsEngineInstance::CallAnimationRepeatJs(JSValue animationContext)
{
    JSContext* ctx = GetQjsContext();
    QjsHandleScope handleScope(ctx);
    auto proto = QjsUtils::GetPropertyStr(ctx, animationContext, "onrepeat");
    if (!JS_IsFunction(ctx, proto)) {
        return;
    }

    LOGD("animation onrepeat event call");
    QjsUtils::Call(ctx, proto, animationContext, 0, {});
}

// -----------------------
// Start QjsEngine
// -----------------------
bool QjsEngine::Initialize(const RefPtr<FrontendDelegate>& delegate)
{
    ACE_SCOPED_TRACE("QjsEngine::Initialize");
    LOGI("Initialize");

    JSRuntime* runtime = nullptr;
    JSContext* context = nullptr;

    // put JS_NewContext as early as possible to make stack_top in context
    // closer to the top stack frame pointer of JS thread.
    runtime = JS_NewRuntime();
    if (runtime != nullptr) {
        context = JS_NewContext(runtime);
    }

    LOGD("QjsEngine initialize");

#ifdef ENABLE_JS_DEBUG
    LOGI("QjsEngine debug mode");
    std::string instanceName = GetInstanceName();
    if (instanceName.empty()) {
        LOGE("GetInstanceName fail, %s", instanceName.c_str());
        return false;
    }
    constexpr int32_t COMPONENT_NAME_MAX_LEN = 100;
    char componentName[COMPONENT_NAME_MAX_LEN];
    if (!DBG_CopyComponentNameFromAce(instanceName.c_str(), componentName, COMPONENT_NAME_MAX_LEN)) {
        LOGE("GetInstanceName strcpy_s fail");
        return false;
    }
    DBG_SetComponentName(componentName, strlen(componentName));
#endif
    nativeEngine_ = new QuickJSNativeEngine(runtime, context);
    ACE_DCHECK(delegate);
    delegate->AddTaskObserver([nativeEngine = nativeEngine_](){
        nativeEngine->Loop();
    });

    engineInstance_ = AceType::MakeRefPtr<QjsEngineInstance>(delegate, instanceId_);
    return engineInstance_->InitJsEnv(runtime, context);
}

QjsEngine::~QjsEngine()
{
    engineInstance_->GetDelegate()->RemoveTaskObserver();
    if (nativeEngine_ != nullptr) {
        delete nativeEngine_;
    }
    ACE_DCHECK(engineInstance_);
    JS_RunGC(engineInstance_->GetQjsRuntime());
}

void QjsEngine::GetLoadOptions(std::string& optionStr, bool isMainPage, const RefPtr<JsAcePage>& page)
{
    auto renderOption = JsonUtil::Create(true);
    auto mediaQuery = engineInstance_->GetDelegate()->GetMediaQueryInfoInstance();
    if (mediaQuery) {
        int32_t width = SystemProperties::GetWidth();
        int32_t height = SystemProperties::GetHeight();
        double aspectRatio = (height != 0) ? (1.0 * width / height) : 1.0;
        renderOption->Put("width", width);
        renderOption->Put("height", height);
        renderOption->Put("aspectRatio", aspectRatio);
        renderOption->Put("isInit", mediaQuery->GetIsInit());
        renderOption->Put("deviceType", mediaQuery->GetDeviceType().c_str());
        renderOption->Put("deviceWidth", SystemProperties::GetDeviceWidth());
        renderOption->Put("deviceHeight", SystemProperties::GetDeviceHeight());
        renderOption->Put("orientation", mediaQuery->GetOrientation().c_str());
        renderOption->Put("roundScreen", SystemProperties::GetIsScreenRound());
        renderOption->Put("resolution", SystemProperties::GetResolution());
        renderOption->Put("bundleUrl", page->GetUrl().c_str());
    }
    renderOption->Put("appInstanceId", "10002");
    renderOption->Put("pcPreview", PC_PREVIEW);
    renderOption->Put("packageName", engineInstance_->GetDelegate()->GetAppID().c_str());

    // get resourceConfig
    engineInstance_->GetDelegate()->GetResourceConfiguration(renderOption);

    // get i18n message
    std::string language = AceApplicationInfo::GetInstance().GetLanguage();
    std::string region = AceApplicationInfo::GetInstance().GetCountryOrRegion();
    engineInstance_->GetDelegate()->GetI18nData(renderOption);
    std::string local = language + "_" + region;
    renderOption->Put("language", local.c_str());

    if (isMainPage) {
        std::string code;
        std::string appMap;
        if (engineInstance_->GetDelegate()->GetAssetContent("app.js.map", appMap)) {
            page->SetAppMap(appMap);
        } else {
            LOGW("sourceMap of app.js is missing!");
        }

        if (engineInstance_->GetDelegate()->GetAssetContent("app.js", code)) {
            renderOption->Put("appCreate", "true");
            renderOption->Put("appCode", code.c_str());
        } else {
            LOGE("app.js is missing!");
        }
    } else {
        renderOption->Put("appCreate", "false");
    }
    optionStr = renderOption->ToString();
}

void QjsEngine::LoadJs(const std::string& url, const RefPtr<JsAcePage>& page, bool isMainPage)
{
    LOGI("QjsEngine LoadJs");
    ACE_SCOPED_TRACE("QjsEngine::LoadJs");
    ACE_DCHECK(engineInstance_);

    engineInstance_->SetStagingPage(page);
    if (isMainPage) {
        ACE_DCHECK(!engineInstance_->GetRunningPage());
        engineInstance_->SetRunningPage(page);
    }
    JSContext* ctx = engineInstance_->GetQjsContext();

    // Create a stack-allocated handle scope.
    QjsHandleScope handleScope(ctx);

    // Memorize the context that this JSContext is working with.
    JS_SetContextOpaque(ctx, reinterpret_cast<void*>(AceType::RawPtr(engineInstance_)));

    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue createInstanceFunc = QjsUtils::GetPropertyStr(ctx, globalObj, "createInstance");
    if (!JS_IsFunction(ctx, createInstanceFunc)) {
        LOGD("createInstance is not found, cannot load js!");
        JS_FreeValue(ctx, globalObj);
        return;
    }
#ifdef ENABLE_JS_DEBUG
    std::string jsContent;
    if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
        LOGE("js file load failed!");
        JS_FreeValue(ctx, globalObj);
        return;
    }
#else
    JSValue jsCode = JS_UNDEFINED;
    auto pos = url.rfind(JS_EXT);
    if (pos != std::string::npos && pos == url.length() - (sizeof(JS_EXT) - 1)) {
        std::vector<uint8_t> binContent;
        if (engineInstance_->GetDelegate()->GetAssetContent(url.substr(0, pos) + BIN_EXT, binContent)) {
            jsCode =
                CallReadObject(ctx, binContent.data(), binContent.size(), false, instanceId_, page->GetUrl().c_str());
            if (!JS_IsException(jsCode)) {
                JS_FreeValue(ctx, jsCode);
                jsCode = QjsUtils::GetPropertyStr(ctx, globalObj, JS_MAIN_ENTRY);
                JS_SetPropertyStr(ctx, globalObj, JS_MAIN_ENTRY, JS_UNDEFINED);
            } else {
                QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::READ_OBJECT_ERROR, instanceId_, page->GetUrl().c_str(),
                    page);
            }
        }
    }

    if (JS_IsFunction(ctx, jsCode)) {
        LOGI("Using binary source code");
    } else {
        std::string jsContent;
        if (!engineInstance_->GetDelegate()->GetAssetContent(url, jsContent)) {
            LOGE("js file load failed!");
            JS_FreeValue(ctx, globalObj);
            return;
        }
        jsCode = QjsUtils::NewStringLen(ctx, jsContent.c_str(), jsContent.size());
    }
#endif
    std::string pageMap;
    if (engineInstance_->GetDelegate()->GetAssetContent(url + MAP_EXT, pageMap)) {
        page->SetPageMap(pageMap);
    } else {
        LOGW("source map of page load failed!");
    }
    std::string jsonData = page->GetPageParams();
    if (jsonData.empty()) {
        jsonData = "{}";
    }
    std::string optionStr;
    GetLoadOptions(optionStr, isMainPage, page);
    JSValue instanceId = QjsUtils::NewString(ctx, std::to_string(page->GetPageId()).c_str());
    JSValue renderOptions = QjsUtils::ParseJSON(ctx, optionStr.c_str(), optionStr.size(), nullptr);
    JSValue data = QjsUtils::ParseJSON(ctx, jsonData.c_str(), jsonData.size(), nullptr);
    JSValue info = QjsUtils::NewObject(ctx);
#ifdef ENABLE_JS_DEBUG
    JSValue jsSrc = QjsUtils::NewStringLen(ctx, jsContent.c_str(), jsContent.length());
    JSValueConst argv[] = { instanceId, jsSrc, renderOptions, data, info };
#else
    JSValueConst argv[] = { instanceId, jsCode, renderOptions, data, info };
#endif
    JSValue retVal = QjsUtils::Call(ctx, createInstanceFunc, JS_UNDEFINED, countof(argv), argv);

    if (JS_IsException(retVal)) {
        LOGE("JS framework load js bundle failed!");
        JS_FreeValue(ctx, globalObj);
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::LOAD_JS_BUNDLE_ERROR, instanceId_, page->GetUrl().c_str(), page);
        return;
    }

    JS_FreeValue(ctx, retVal);
    JS_FreeValue(ctx, globalObj);
    js_std_loop(ctx);
}

void QjsEngine::UpdateRunningPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetRunningPage(page);
}

void QjsEngine::UpdateStagingPage(const RefPtr<JsAcePage>& page)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetStagingPage(page);
}

void QjsEngine::ResetStagingPage()
{
    ACE_DCHECK(engineInstance_);
    auto runningPage = engineInstance_->GetRunningPage();
    engineInstance_->ResetStagingPage(runningPage);
}

void QjsEngine::DestroyPageInstance(int32_t pageId)
{
    LOGI("QjsEngine DestroyPageInstance");
    JSContext* ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QjsHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue destroyInstanceFunc = QjsUtils::GetPropertyStr(ctx, globalObj, "destroyInstance");
    if (!JS_IsFunction(ctx, destroyInstanceFunc)) {
        LOGE("destroyInstance is not found, cannot destroy page instance!");
        JS_FreeValue(ctx, globalObj);
        return;
    }

    JSValue instanceId = QjsUtils::NewString(ctx, std::to_string(pageId).c_str());
    JSValueConst argv[] = { instanceId };
    JSValue retVal = QjsUtils::Call(ctx, destroyInstanceFunc, JS_UNDEFINED, countof(argv), argv);

    if (JS_IsException(retVal)) {
        LOGE("Qjs DestroyPageInstance FAILED!");
        JS_FreeValue(ctx, globalObj);

        auto page = engineInstance_->GetDelegate()->GetPage(pageId);
        if (page) {
            QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::DESTROY_PAGE_ERROR, instanceId_, page->GetUrl().c_str(),
                page);
        } else {
            QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::DESTROY_PAGE_ERROR, instanceId_);
        }
        return;
    }

    RunGarbageCollection();
    JS_FreeValue(ctx, globalObj);
}

void QjsEngine::DestroyApplication(const std::string& packageName)
{
    LOGI("DestroyApplication: destroy app instance from jsfwk, packageName %{public}s", packageName.c_str());
    JSContext* ctx = engineInstance_->GetQjsContext();
    ACE_DCHECK(ctx);

    QjsHandleScope handleScope(ctx);
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue appDestroyFunc = QjsUtils::GetPropertyStr(ctx, globalObj, "appDestroy");
    if (!JS_IsFunction(ctx, appDestroyFunc)) {
        LOGE("appDestroyFunc is not found, cannot destroy page instance!");
        JS_FreeValue(ctx, globalObj);
        return;
    }

    JSValue name = QjsUtils::NewString(ctx, packageName.c_str());
    JSValueConst argv[] = { name };
    JSValue retVal = QjsUtils::Call(ctx, appDestroyFunc, JS_UNDEFINED, countof(argv), argv);

    if (JS_IsException(retVal)) {
        LOGE("Qjs appDestroyFunc FAILED!");
        QjsUtils::JsStdDumpErrorAce(ctx, JsErrorType::DESTROY_APP_ERROR, instanceId_, nullptr,
            engineInstance_->GetRunningPage());
    }

    JS_FreeValue(ctx, globalObj);
}

void QjsEngine::TimerCallback(const std::string& callbackId, const std::string& delay, bool isInterval)
{
    if (isInterval) {
        engineInstance_->CallJs(callbackId, std::string("{}"), true, true);
        engineInstance_->GetDelegate()->WaitTimer(callbackId, delay, isInterval, false);
    } else {
        engineInstance_->CallJs(callbackId, std::string("{}"), false, true);
        engineInstance_->GetDelegate()->ClearTimer(callbackId);
    }
}

void QjsEngine::MediaQueryCallback(const std::string& callbackId, const std::string& args)
{
    if (engineInstance_) {
        engineInstance_->CallJs(callbackId.c_str(), args.c_str(), true, false);
    }
}

void QjsEngine::RequestAnimationCallback(const std::string& callbackId, uint64_t timeStamp)
{
    if (engineInstance_) {
        engineInstance_->CallJs(callbackId.c_str(), std::to_string(timeStamp).c_str(), false, true);
        engineInstance_->GetDelegate()->CancelAnimationFrame(callbackId);
    }
}

void QjsEngine::JsCallback(const std::string& callbackId, const std::string& args)
{
    if (engineInstance_) {
        engineInstance_->CallJs(callbackId.c_str(), args.c_str(), true, false);
    }
}

void QjsEngine::FireAsyncEvent(const std::string& eventId, const std::string& param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEvent\"}]");
    LOGD("FireAsyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    JSValue cppToJsRet = engineInstance_->FireJsEvent(callBuf);
    if (JS_IsException(cppToJsRet)) {
        LOGE("Qjs FireAsyncEvent FAILED !! jsCall: %{private}s", callBuf.c_str());
        QjsUtils::JsStdDumpErrorAce(engineInstance_->GetQjsContext(), JsErrorType::FIRE_EVENT_ERROR, instanceId_,
            nullptr, engineInstance_->GetRunningPage());
    }
    JS_FreeValue(engineInstance_->GetQjsContext(), cppToJsRet);
}

void QjsEngine::FireSyncEvent(const std::string& eventId, const std::string& param)
{
    std::string callBuf = std::string("[{\"args\": [\"")
                              .append(eventId)
                              .append("\",")
                              .append(param)
                              .append("], \"method\":\"fireEventSync\"}]");
    LOGD("FireSyncEvent string: %{private}s", callBuf.c_str());

    ACE_DCHECK(engineInstance_);
    JSValue cppToJsRet = engineInstance_->FireJsEvent(callBuf.c_str());
    if (JS_IsException(cppToJsRet)) {
        LOGE("Qjs FireSyncEvent FAILED !! jsCall: %{private}s", callBuf.c_str());
        QjsUtils::JsStdDumpErrorAce(engineInstance_->GetQjsContext(), JsErrorType::FIRE_EVENT_ERROR, instanceId_,
            nullptr, engineInstance_->GetRunningPage());
    }
    JS_FreeValue(engineInstance_->GetQjsContext(), cppToJsRet);
}

void QjsEngine::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher)
{
    ACE_DCHECK(engineInstance_);
    engineInstance_->SetJsMessageDispatcher(dispatcher);
}

void QjsEngine::RunGarbageCollection()
{
    if (engineInstance_ && engineInstance_->GetQjsRuntime()) {
        JS_RunGC(engineInstance_->GetQjsRuntime());
    }
}

RefPtr<GroupJsBridge> QjsEngine::GetGroupJsBridge()
{
    return AceType::MakeRefPtr<QuickJsGroupJsBridge>();
}

} // namespace OHOS::Ace::Framework
