/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/js_base_node.h"

#include <memory>
#include <queue>
#include <string>

#include "canvas_napi/js_canvas.h"
#include "jsnapi_expo.h"

#include "base/geometry/dimension.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
const std::unordered_set<std::string> EXPORT_TEXTURE_SUPPORT_TYPES = { V2::JS_VIEW_ETS_TAG, V2::COMMON_VIEW_ETS_TAG };
constexpr int32_t INFO_LENGTH_LIMIT = 2;
constexpr int32_t BUILD_PARAM_INDEX_TWO = 2;
constexpr int32_t BUILD_PARAM_INDEX_THREE = 3;
constexpr int32_t BUILD_PARAM_INDEX_FOUR = 4;
constexpr int32_t BUILD_PARAM_INDEX_THIS_OBJ = 5;
} // namespace

void JSBaseNode::BuildNode(const JSCallbackInfo& info)
{
    ACE_REUSE_DETECTION_SCOPED_TRACE("JSBaseNode:BuildNode");
    auto builder = info[0];
    CHECK_NULL_VOID(builder->IsFunction());
    auto buildFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builder));

    auto infoLen = info.Length();
    JSRef<JSVal> param;
    if (infoLen >= INFO_LENGTH_LIMIT && (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)
        || (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) && info[1]->IsObject()))) {
        param = info[1];
    }

    auto lazyBuilderFunc = [buildFunc, param, renderType = renderType_]() mutable {
        NG::ViewStackProcessor::GetInstance()->SetIsBuilderNode(true);
        NG::ViewStackProcessor::GetInstance()->SetIsExportTexture(renderType == NodeRenderType::RENDER_TYPE_TEXTURE);
        if (!param->IsEmpty()) {
            buildFunc->ExecuteJS(1, &param);
        } else {
            buildFunc->ExecuteJS();
        }
    };

    NG::ScopedViewStackProcessor builderViewStackProcessor;
    lazyBuilderFunc();
    auto parent = viewNode_ ? viewNode_->GetParent() : nullptr;
    auto newNode = NG::ViewStackProcessor::GetInstance()->Finish();
    realNode_ = newNode;
    if (newNode) {
        newNode->SetBuilderFunc(std::move(lazyBuilderFunc));
    }

    if (newNode && (infoLen >= BUILD_PARAM_INDEX_TWO + 1)) {
        auto updateTsNodeBuilder = info[BUILD_PARAM_INDEX_TWO];
        EcmaVM* vm = info.GetVm();
        auto updateTsFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(updateTsNodeBuilder));
        auto updateNodeFunc = [updateTsFunc, vm](int32_t instanceId, RefPtr<NG::UINode>& node) mutable {
            JSRef<JSVal> param[2];
            param[0] = JSRef<JSVal>::Make(ToJSValue(instanceId));
            param[1] = JSRef<JSVal>::Make(panda::NativePointerRef::New(vm, AceType::RawPtr(node)));
            updateTsFunc->ExecuteJS(2, param);
        };
        newNode->SetUpdateNodeFunc(std::move(updateNodeFunc));
    }

    bool isSupportLazyBuild = false;
    if (infoLen >= BUILD_PARAM_INDEX_FOUR + 1) {
        auto jsLazyBuildSupported = info[BUILD_PARAM_INDEX_FOUR];
        if (jsLazyBuildSupported->IsBoolean()) {
            isSupportLazyBuild = jsLazyBuildSupported->ToBoolean();
        }
    }

    // If the node is a UINode, amount it to a BuilderProxyNode if needProxy.
    auto flag = AceType::InstanceOf<NG::FrameNode>(newNode);
    auto isSupportExportTexture = newNode ? EXPORT_TEXTURE_SUPPORT_TYPES.count(newNode->GetTag()) > 0 : false;
    if (!flag && newNode) {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        auto proxyNode = NG::FrameNode::GetOrCreateFrameNode(
            "BuilderProxyNode", nodeId, []() { return AceType::MakeRefPtr<NG::StackPattern>(); });
        auto stackLayoutAlgorithm = proxyNode->GetLayoutProperty<NG::LayoutProperty>();
        stackLayoutAlgorithm->UpdateAlignment(Alignment::TOP_LEFT);
        proxyNode->AddChild(newNode);
        newNode = proxyNode;
    }

    if (newNode && (infoLen >= BUILD_PARAM_INDEX_THREE + 1)) {
        auto updateTsNodeConfig = info[BUILD_PARAM_INDEX_THREE];
        EcmaVM* vm = info.GetVm();
        auto updateTsConfig = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(updateTsNodeConfig));
        auto updateNodeConfig = [updateTsConfig, vm]() mutable {
            updateTsConfig->ExecuteJS();
        };
        newNode->SetUpdateNodeConfig(std::move(updateNodeConfig));
    }
    if (parent) {
        if (newNode) {
            parent->ReplaceChild(viewNode_, newNode);
            newNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        } else {
            parent->RemoveChild(viewNode_);
            parent->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        }
    }
    viewNode_ = newNode ? AceType::DynamicCast<NG::FrameNode>(newNode) : nullptr;
    CHECK_NULL_VOID(viewNode_);
    ProccessNode(isSupportExportTexture, isSupportLazyBuild);
    UpdateEnd(info);
    CHECK_NULL_VOID(viewNode_);

    JSRef<JSObject> thisObj = info[BUILD_PARAM_INDEX_THIS_OBJ];
    auto updateInstance = thisObj->GetProperty("updateInstance");
    if (!updateInstance->IsFunction()) {
        return;
    }
    EcmaVM* vm = info.GetVm();
    auto updateInstanceFunc = AceType::MakeRefPtr<JsFunction>(thisObj, JSRef<JSFunc>::Cast(updateInstance));
    CHECK_NULL_VOID(updateInstanceFunc);
    auto updateJSInstanceCallback = [updateInstanceFunc, vm](int32_t instanceId) {
        auto uiContext = NG::UIContextHelper::GetUIContext(vm, instanceId);
        auto jsVal = JSRef<JSVal>::Make(uiContext);
        updateInstanceFunc->ExecuteJS(1, &jsVal);
    };
    viewNode_->RegisterUpdateJSInstanceCallback(updateJSInstanceCallback);
}

void JSBaseNode::ProccessNode(bool isSupportExportTexture, bool isSupportLazyBuild)
{
    CHECK_NULL_VOID(viewNode_);
    CHECK_NULL_VOID(realNode_);
    viewNode_->SetIsRootBuilderNode(true);
    realNode_->SetJsBuilderNodeId(viewNode_->GetId());
    if (isSupportExportTexture) {
        viewNode_->CreateExportTextureInfoIfNeeded();
        auto exportTextureInfo = viewNode_->GetExportTextureInfo();
        CHECK_NULL_VOID(exportTextureInfo);
        exportTextureInfo->SetSurfaceId(surfaceId_);
        exportTextureInfo->SetCurrentRenderType(renderType_);
    }
    if (!isSupportLazyBuild) {
        viewNode_->Build(nullptr);
    }
}

void JSBaseNode::Create(const JSCallbackInfo& info)
{
    if (info.Length() >= 1 && !info[0]->IsFunction()) {
        return;
    }
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE) && info.Length() >= INFO_LENGTH_LIMIT
        && !(info[1]->IsObject() || info[1]->IsUndefined() || info[1]->IsNull())) {
        return;
    }
    BuildNode(info);
    EcmaVM* vm = info.GetVm();
    info.SetReturnValue(JSRef<JSVal>::Make(panda::NativePointerRef::New(vm, AceType::RawPtr(viewNode_))));
}

void JSBaseNode::ConstructorCallback(const JSCallbackInfo& info)
{
    std::string surfaceId;
    NodeRenderType renderType = NodeRenderType::RENDER_TYPE_DISPLAY;
    NG::OptionalSizeF selfIdealSize;
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto renderOption = JSRef<JSObject>::Cast(info[0]);
        auto size = renderOption->GetProperty("selfIdealSize");
        if (size->IsObject()) {
            auto sizeObj = JSRef<JSObject>::Cast(size);
            auto width = sizeObj->GetProperty("width");
            auto widthValue = width->IsNumber() ? width->ToNumber<float>() : 0.0f;
            widthValue = LessNotEqual(widthValue, 0.0f) ? 0.0f : widthValue;
            auto height = sizeObj->GetProperty("height");
            auto heightValue = height->IsNumber() ? height->ToNumber<float>() : 0.0f;
            heightValue = LessNotEqual(heightValue, 0.0f) ? 0.0f : heightValue;
            selfIdealSize.SetWidth(PipelineBase::Vp2PxWithCurrentDensity(widthValue));
            selfIdealSize.SetHeight(PipelineBase::Vp2PxWithCurrentDensity(heightValue));
        }
        auto type = renderOption->GetProperty("type");
        if (type->IsNumber()) {
            renderType = static_cast<NodeRenderType>(type->ToNumber<uint32_t>());
        }
        auto id = renderOption->GetProperty("surfaceId");
        if (id->IsString()) {
            surfaceId = id->ToString();
        }
    }
    auto instance = AceType::MakeRefPtr<JSBaseNode>(selfIdealSize, renderType, surfaceId);
    instance->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(instance));
}

void JSBaseNode::DestructorCallback(JSBaseNode* node)
{
    if (node != nullptr) {
        node->DecRefCount();
    }
}

void JSBaseNode::FinishUpdateFunc(const JSCallbackInfo& info)
{
    NG::ViewStackProcessor::GetInstance()->FlushRerenderTask();
}

void JSBaseNode::PostTouchEvent(const JSCallbackInfo& info)
{
    if (!viewNode_ || info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent params invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    TouchEvent touchEvent;
    if (InitTouchEvent(info, touchEvent, true)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent params invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent pipelineContext is invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto postEventManager = pipelineContext->GetPostEventManager();
    if (!postEventManager) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent postEventManager is invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto result = postEventManager->PostEvent(viewNode_, touchEvent);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSBaseNode::PostInputEvent(const JSCallbackInfo& info)
{
    if (!realNode_ || info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent params invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    if (!pipelineContext) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent pipelineContext is invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto postEventManager = pipelineContext->GetPostEventManager();
    if (!postEventManager) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent postEventManager is invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent params is invalid");
        return;
    }
    bool result = false;
    auto touchesJsVal = obj->GetProperty("touches");
    if (touchesJsVal->IsArray()) {
        TouchEvent touchEvent;
        if (!InitTouchEvent(info, touchEvent, false)) {
            info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
            return;
        }
        result = postEventManager->PostTouchEvent(realNode_, std::move(touchEvent));
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
        return;
    }
    auto scrollStep = obj->GetProperty("scrollStep");
    if (scrollStep->IsNumber()) {
        AxisEvent axisEvent;
        if (!InitAxisEvent(info, axisEvent)) {
            info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
            return;
        }
        result = postEventManager->PostAxisEvent(realNode_, std::move(axisEvent));
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
        return;
    }
    MouseEvent mouseEvent;
    if (!InitMouseEvent(info, mouseEvent)) {
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    result = postEventManager->PostMouseEvent(realNode_, std::move(mouseEvent));
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

bool JSBaseNode::GetTouches(const JSCallbackInfo& info, TouchEvent& touchEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto touchesJsVal = obj->GetProperty("touches");
    if (touchesJsVal->IsArray()) {
        JSRef<JSArray> touchesArray = JSRef<JSArray>::Cast(touchesJsVal);
        for (auto index = 0; index < static_cast<int32_t>(touchesArray->Length()); index++) {
            JSRef<JSVal> item = touchesArray->GetValueAt(index);
            if (!item->IsObject()) { continue; }
            JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
            TouchPoint point;
            point.id = itemObj->GetPropertyValue<int32_t>("id", 0);
            point.x = itemObj->GetPropertyValue<float>("x", 0.0f);
            point.y = itemObj->GetPropertyValue<float>("y", 0.0f);
            point.screenX = itemObj->GetPropertyValue<float>("screenX", 0.0f);
            point.screenY = itemObj->GetPropertyValue<float>("screenY", 0.0f);
            point.globalDisplayX = itemObj->GetPropertyValue<double>("globalDisplayX", 0.0);
            point.globalDisplayY = itemObj->GetPropertyValue<double>("globalDisplayY", 0.0);
            point.originalId = itemObj->GetPropertyValue<int32_t>("id", 0);
            touchEvent.pointers.emplace_back(point);
        }
    }
    auto changedTouchesJsVal = obj->GetProperty("changedTouches");
    if (changedTouchesJsVal->IsArray()) {
        JSRef<JSArray> changedTouchesArray = JSRef<JSArray>::Cast(changedTouchesJsVal);
        if (static_cast<int32_t>(changedTouchesArray->Length()) <= 0) {
            TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent event changedTouchesArray is invalid");
            info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
            return false;
        }
        JSRef<JSVal> item = changedTouchesArray->GetValueAt(0);
        if (!item->IsObject()) {
            TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostTouchEvent event changedTouchesArray item is not an object");
            info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
            return false;
        }
        JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
        touchEvent.id = itemObj->GetPropertyValue<int32_t>("id", 0);
        touchEvent.x = itemObj->GetPropertyValue<float>("x", 0.0f);
        touchEvent.y = itemObj->GetPropertyValue<float>("y", 0.0f);
        touchEvent.screenX = itemObj->GetPropertyValue<float>("screenX", 0.0f);
        touchEvent.screenY = itemObj->GetPropertyValue<float>("screenY", 0.0f);
        touchEvent.globalDisplayX = itemObj->GetPropertyValue<double>("globalDisplayX", 0.0);
        touchEvent.globalDisplayY = itemObj->GetPropertyValue<double>("globalDisplayY", 0.0);
        touchEvent.originalId = itemObj->GetPropertyValue<int32_t>("id", 0);
    }
    return true;
}

// only postInputEvent call this function
bool JSBaseNode::GetChangedTouches(const JSCallbackInfo& info, TouchEvent& touchEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto changedTouchesJsVal = obj->GetProperty("changedTouches");
    if (!changedTouchesJsVal->IsArray() || changedTouchesJsVal->IsEmpty()) {
        return false;
    }
    JSRef<JSArray> changedTouchesArray = JSRef<JSArray>::Cast(changedTouchesJsVal);
    if (static_cast<int32_t>(changedTouchesArray->Length()) <= 0) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent event changedTouchesArray is invalid");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return false;
    }
    JSRef<JSVal> item = changedTouchesArray->GetValueAt(0);
    if (!item->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "PostInputEvent event changedTouchesArray item is not an object");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return false;
    }
    JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
    touchEvent.id = itemObj->GetPropertyValue<int32_t>("id", 0);
    touchEvent.x = itemObj->GetPropertyValue<float>("windowX", 0.0f);
    touchEvent.y = itemObj->GetPropertyValue<float>("windowY", 0.0f);
    touchEvent.screenX = itemObj->GetPropertyValue<float>("displayX", 0.0f);
    touchEvent.screenY = itemObj->GetPropertyValue<float>("displayY", 0.0f);
    touchEvent.originalId = itemObj->GetPropertyValue<int32_t>("id", 0);
    touchEvent.width = itemObj->GetPropertyValue<float>("width", 0);
    touchEvent.height = itemObj->GetPropertyValue<float>("height", 0);
    touchEvent.globalDisplayX = itemObj->GetPropertyValue<double>("globalDisplayX", 0.0);
    touchEvent.globalDisplayY = itemObj->GetPropertyValue<double>("globalDisplayY", 0.0);
    auto pressedTimeJsVal = itemObj->GetProperty("pressedTime");
    if (pressedTimeJsVal->IsNumber()) {
        std::chrono::nanoseconds nanoseconds(static_cast<int64_t>(pressedTimeJsVal->ToNumber<double>()));
        TimeStamp time(nanoseconds);
        touchEvent.pressedTime = time;
    }
    auto handJsVal = itemObj->GetProperty("hand");
    if (handJsVal->IsNumber()) {
        touchEvent.operatingHand = handJsVal->ToNumber<int32_t>();
    }
    return true;
}

bool JSBaseNode::GetInputTouches(const JSCallbackInfo& info, TouchEvent& touchEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto touchesJsVal = obj->GetProperty("touches");
    if (!touchesJsVal->IsArray() || touchesJsVal->IsEmpty()) {
        return false;
    }
    JSRef<JSArray> touchesArray = JSRef<JSArray>::Cast(touchesJsVal);
    for (auto index = 0; index < static_cast<int32_t>(touchesArray->Length()); index++) {
        JSRef<JSVal> item = touchesArray->GetValueAt(index);
        if (!item->IsObject()) {
            continue;
        }
        JSRef<JSObject> itemObj = JSRef<JSObject>::Cast(item);
        TouchPoint point;
        point.id = itemObj->GetPropertyValue<int32_t>("id", 0);
        point.x = itemObj->GetPropertyValue<float>("windowX", 0.0f);
        point.y = itemObj->GetPropertyValue<float>("windowY", 0.0f);
        point.screenX = itemObj->GetPropertyValue<float>("displayX", 0.0f);
        point.screenY = itemObj->GetPropertyValue<float>("displayY", 0.0f);
        point.originalId = itemObj->GetPropertyValue<int32_t>("id", 0);
        point.force = itemObj->GetPropertyValue<float>("pressure", 0);
        point.width = itemObj->GetPropertyValue<float>("width", 0);
        point.height = itemObj->GetPropertyValue<float>("height", 0);
        point.operatingHand = itemObj->GetPropertyValue<int32_t>("hand", 0);
        point.globalDisplayX = itemObj->GetPropertyValue<double>("globalDisplayX", 0.0);
        point.globalDisplayY = itemObj->GetPropertyValue<double>("globalDisplayY", 0.0);
        auto pressedTimeJsVal = itemObj->GetProperty("pressedTime");
        if (pressedTimeJsVal->IsNumber()) {
            std::chrono::nanoseconds nanoseconds(static_cast<int64_t>(pressedTimeJsVal->ToNumber<double>()));
            TimeStamp time(nanoseconds);
            point.downTime = time;
        }
        touchEvent.pointers.emplace_back(point);
    }
    return true;
}

bool JSBaseNode::InitTouchEvent(const JSCallbackInfo& info, TouchEvent& touchEvent, bool isPostTouchEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto typeJsVal = obj->GetProperty("type");
    if (typeJsVal->IsNumber()) {
        touchEvent.type = static_cast<TouchType>(typeJsVal->ToNumber<int32_t>());
    }
    auto sourceJsVal = obj->GetProperty("source");
    if (sourceJsVal->IsNumber()) {
        touchEvent.sourceType = static_cast<SourceType>((sourceJsVal->ToNumber<int32_t>()));
    }
    auto sourceToolJsVal = obj->GetProperty("sourceTool");
    if (sourceToolJsVal->IsNumber()) {
        touchEvent.sourceTool = static_cast<SourceTool>((sourceToolJsVal->ToNumber<int32_t>()));
    }
    auto pressureJsVal = obj->GetProperty("pressure");
    if (pressureJsVal->IsNumber()) {
        touchEvent.force = pressureJsVal->ToNumber<float>();
    }
    auto timestampJsVal = obj->GetProperty("timestamp");
    if (timestampJsVal->IsNumber()) {
        std::chrono::nanoseconds nanoseconds(static_cast<int64_t>(timestampJsVal->ToNumber<double>()));
        TimeStamp time(nanoseconds);
        touchEvent.time = time;
    }
    auto deviceIdJsVal = obj->GetProperty("deviceId");
    if (deviceIdJsVal->IsNumber()) {
        touchEvent.deviceId = deviceIdJsVal->ToNumber<int32_t>();
    }
    auto targetDisplayIdJsVal = obj->GetProperty("targetDisplayId");
    if (targetDisplayIdJsVal->IsNumber()) {
        touchEvent.targetDisplayId = targetDisplayIdJsVal->ToNumber<int32_t>();
    }
    ParamTouchEvent(info, touchEvent);
    BaseEventInfo* baseEventInfo = obj->Unwrap<BaseEventInfo>();
    if (baseEventInfo) {
        touchEvent.SetPressedKeyCodes(baseEventInfo->GetPressedKeyCodes());
    }
    if (isPostTouchEvent) {
        return GetTouches(info, touchEvent);
    }
    // postInputEvent: x = windowX, y = windowY, screenX = displayX, sreenY = displayY
    if (!GetInputTouches(info, touchEvent)) {
        return false;
    }
    return GetChangedTouches(info, touchEvent);
}

bool JSBaseNode::ParamTouchEvent(const JSCallbackInfo& info, TouchEvent& touchEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "TouchEvent params invalid");
        return false;
    }
    auto titleXJsVal = obj->GetProperty("tiltX");
    if (titleXJsVal->IsNumber()) {
        touchEvent.tiltX = titleXJsVal->ToNumber<float>();
    }
    auto titleYJsVal = obj->GetProperty("tiltY");
    if (titleYJsVal->IsNumber()) {
        touchEvent.tiltY = titleYJsVal->ToNumber<float>();
    }
    auto rollAngleJsVal = obj->GetProperty("rollAngle");
    if (rollAngleJsVal->IsNumber()) {
        touchEvent.rollAngle = rollAngleJsVal->ToNumber<float>();
    }
    return true;
}

bool JSBaseNode::InitMouseEvent(const JSCallbackInfo& info, MouseEvent& mouseEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "MouseEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "MouseEvent params invalid");
        return false;
    }
    auto sourceJsVal = obj->GetProperty("source");
    if (sourceJsVal->IsNumber()) {
        mouseEvent.sourceType = static_cast<SourceType>((sourceJsVal->ToNumber<int32_t>()));
    }
    auto sourceToolJsVal = obj->GetProperty("sourceTool");
    if (sourceToolJsVal->IsNumber()) {
        mouseEvent.sourceTool = static_cast<SourceTool>((sourceToolJsVal->ToNumber<int32_t>()));
    }
    auto timestampJsVal = obj->GetProperty("timestamp");
    if (timestampJsVal->IsNumber()) {
        std::chrono::nanoseconds nanoseconds(static_cast<int64_t>(timestampJsVal->ToNumber<double>()));
        TimeStamp time(nanoseconds);
        mouseEvent.time = time;
    }
    auto deviceIdJsVal = obj->GetProperty("deviceId");
    if (deviceIdJsVal->IsNumber()) {
        mouseEvent.deviceId = deviceIdJsVal->ToNumber<int32_t>();
    }
    auto targetDisplayIdJsVal = obj->GetProperty("targetDisplayId");
    if (targetDisplayIdJsVal->IsNumber()) {
        mouseEvent.targetDisplayId = targetDisplayIdJsVal->ToNumber<int32_t>();
    }
    auto xJsVal = obj->GetProperty("windowX");
    if (xJsVal->IsNumber()) {
        mouseEvent.x = xJsVal->ToNumber<float>();
    }
    auto yJsVal = obj->GetProperty("windowY");
    if (yJsVal->IsNumber()) {
        mouseEvent.y = yJsVal->ToNumber<float>();
    }
    auto globalDisplayXJsVal = obj->GetProperty("globalDisplayX");
    if (globalDisplayXJsVal->IsNumber()) {
        mouseEvent.globalDisplayX = globalDisplayXJsVal->ToNumber<double>();
    }
    auto globalDisplayYJsVal = obj->GetProperty("globalDisplayY");
    if (globalDisplayYJsVal->IsNumber()) {
        mouseEvent.globalDisplayY = globalDisplayYJsVal->ToNumber<double>();
    }
    auto buttonJsVal = obj->GetProperty("button");
    if (buttonJsVal->IsNumber()) {
        mouseEvent.button = static_cast<MouseButton>(buttonJsVal->ToNumber<int32_t>());
    }
    auto actionJsVal = obj->GetProperty("action");
    if (actionJsVal->IsNumber()) {
        mouseEvent.action = static_cast<MouseAction>(actionJsVal->ToNumber<int32_t>());
    }
    if (!ParamMouseEvent(info, mouseEvent)) {
        return false;
    }
    return true;
}

bool JSBaseNode::ParamMouseEvent(const JSCallbackInfo& info, MouseEvent& mouseEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "MouseEevent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "MouseEvent params invalid");
        return false;
    }
    auto screenXJsVal = obj->GetProperty("displayX");
    if (screenXJsVal->IsNumber()) {
        mouseEvent.screenX = screenXJsVal->ToNumber<float>();
    }
    auto screenYJsVal = obj->GetProperty("displayY");
    if (screenYJsVal->IsNumber()) {
        mouseEvent.screenY = screenYJsVal->ToNumber<float>();
    }
    auto rawDeltaXJsVal = obj->GetProperty("rawDeltaX");
    if (rawDeltaXJsVal->IsNumber()) {
        mouseEvent.rawDeltaX = rawDeltaXJsVal->ToNumber<float>();
    }
    auto rawDeltaYJsVal = obj->GetProperty("rawDeltaY");
    if (rawDeltaYJsVal->IsNumber()) {
        mouseEvent.rawDeltaY = rawDeltaYJsVal->ToNumber<float>();
    }
    BaseEventInfo* baseEventInfo = obj->Unwrap<BaseEventInfo>();
    if (baseEventInfo) {
        mouseEvent.pressedKeyCodes_ = baseEventInfo->GetPressedKeyCodes();
    }
    auto pressedButtonsJsVal = obj->GetProperty("pressedButtons");
    if (pressedButtonsJsVal->IsArray()) {
        JSRef<JSArray> pressedButtonsArray = JSRef<JSArray>::Cast(pressedButtonsJsVal);
        for (auto index = 0; index < static_cast<int32_t>(pressedButtonsArray->Length()); index++) {
            JSRef<JSVal> item = pressedButtonsArray->GetValueAt(index);
            if (!item->IsNumber()) {
                continue;
            }
            auto pressedButton = item->ToNumber<int32_t>();
            mouseEvent.pressedButtonsArray.push_back(static_cast<MouseButton>(pressedButton));
        }
    }
    return true;
}

bool JSBaseNode::InitAxisEvent(const JSCallbackInfo& info, AxisEvent& axisEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "AxisEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "AxisEvent params invalid");
        return false;
    }
    auto sourceJsVal = obj->GetProperty("source");
    if (sourceJsVal->IsNumber()) {
        axisEvent.sourceType = static_cast<SourceType>((sourceJsVal->ToNumber<int32_t>()));
    }
    auto sourceToolJsVal = obj->GetProperty("sourceTool");
    if (sourceToolJsVal->IsNumber()) {
        axisEvent.sourceTool = static_cast<SourceTool>((sourceToolJsVal->ToNumber<int32_t>()));
    }
    auto timestampJsVal = obj->GetProperty("timestamp");
    if (timestampJsVal->IsNumber()) {
        std::chrono::nanoseconds nanoseconds(static_cast<int64_t>(timestampJsVal->ToNumber<double>()));
        TimeStamp time(nanoseconds);
        axisEvent.time = time;
    }
    auto deviceIdJsVal = obj->GetProperty("deviceId");
    if (deviceIdJsVal->IsNumber()) {
        axisEvent.deviceId = deviceIdJsVal->ToNumber<int32_t>();
    }
    auto targetDisplayIdJsVal = obj->GetProperty("targetDisplayId");
    if (targetDisplayIdJsVal->IsNumber()) {
        axisEvent.targetDisplayId = targetDisplayIdJsVal->ToNumber<int32_t>();
    }
    auto actionJsVal = obj->GetProperty("action");
    if (actionJsVal->IsNumber()) {
        axisEvent.action = static_cast<AxisAction>(actionJsVal->ToNumber<int32_t>());
    }
    auto xJsVal = obj->GetProperty("windowX");
    if (xJsVal->IsNumber()) {
        axisEvent.x = xJsVal->ToNumber<float>();
    }
    auto yJsVal = obj->GetProperty("windowY");
    if (yJsVal->IsNumber()) {
        axisEvent.y = yJsVal->ToNumber<float>();
    }
    auto screenXJsVal = obj->GetProperty("displayX");
    if (screenXJsVal->IsNumber()) {
        axisEvent.screenX = screenXJsVal->ToNumber<float>();
    }
    auto screenYJsVal = obj->GetProperty("displayY");
    if (screenYJsVal->IsNumber()) {
        axisEvent.screenY = screenYJsVal->ToNumber<float>();
    }
    auto globalDisplayXJsVal = obj->GetProperty("globalDisplayX");
    if (globalDisplayXJsVal->IsNumber()) {
        axisEvent.globalDisplayX = globalDisplayXJsVal->ToNumber<double>();
    }
    auto globalDisplayYJsVal = obj->GetProperty("globalDisplayY");
    if (globalDisplayYJsVal->IsNumber()) {
        axisEvent.globalDisplayY = globalDisplayYJsVal->ToNumber<double>();
    }

    AxisInfo* axisInfo = obj->Unwrap<AxisInfo>();
    auto pinchAxisScale = obj->GetProperty("pinchAxisScale");
    if (pinchAxisScale->IsNumber()) {
        axisEvent.pinchAxisScale = pinchAxisScale->ToNumber<float>();
    } else if (axisInfo) {
        axisEvent.pinchAxisScale = axisInfo->GetPinchAxisScale();
    }
    auto rotateAxisAngle = obj->GetProperty("rotateAxisAngle");
    if (rotateAxisAngle->IsNumber()) {
        axisEvent.rotateAxisAngle = rotateAxisAngle->ToNumber<float>();
    } else if (axisInfo) {
        axisEvent.rotateAxisAngle = axisInfo->GetRotateAxisAngle();
    }
    if (!ParamAxisEvent(info, axisEvent)) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "AxisEvent params invalid");
        return false;
    }
    return true;
}

bool JSBaseNode::ParamAxisEvent(const JSCallbackInfo& info, AxisEvent& axisEvent)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "AxisEvent params invalid");
        return false;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    if (obj->IsUndefined() || obj.IsEmpty()) {
        TAG_LOGW(AceLogTag::ACE_INPUTKEYFLOW, "AxisEvent params invalid");
        return false;
    }
    auto scrollStepJsVal = obj->GetProperty("scrollStep");
    if (scrollStepJsVal->IsNumber()) {
        axisEvent.scrollStep = scrollStepJsVal->ToNumber<int32_t>();
    }
    auto horizontalAxisJsVal = obj->GetProperty("axisHorizontal");
    if (horizontalAxisJsVal->IsNumber()) {
        axisEvent.horizontalAxis = horizontalAxisJsVal->ToNumber<float>();
    }
    auto verticalAxisJsVal = obj->GetProperty("axisVertical");
    if (verticalAxisJsVal->IsNumber()) {
        axisEvent.verticalAxis = verticalAxisJsVal->ToNumber<float>();
    }
    BaseEventInfo* baseEventInfo = obj->Unwrap<BaseEventInfo>();
    if (baseEventInfo) {
        axisEvent.pressedCodes = baseEventInfo->GetPressedKeyCodes();
    }
    return true;
}

void JSBaseNode::UpdateStart(const JSCallbackInfo& info)
{
    scopedViewStackProcessor_ = std::make_unique<NG::ScopedViewStackProcessor>();
}

void JSBaseNode::UpdateEnd(const JSCallbackInfo& info)
{
    scopedViewStackProcessor_ = nullptr;
    CHECK_NULL_VOID(viewNode_);
    if (size_.IsValid()) {
        viewNode_->SetParentLayoutConstraint(size_.ConvertToSizeT());
    }
}

void JSBaseNode::OnReuseWithBindThis(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(realNode_);
    std::queue<RefPtr<NG::UINode>> elements;
    elements.push(realNode_);
    void* data = static_cast<void*>(info.GetJsiRuntimeCallInfo());
    while (!elements.empty()) {
        auto currentNode = elements.front();
        elements.pop();
        if (!currentNode) {
            continue;
        }
        if (AceType::InstanceOf<NG::CustomNodeBase>(currentNode)) {
            auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(currentNode);
            customNode->FireOnReuseFunc(data);
        } else {
            for (const auto& child : currentNode->GetChildren()) {
                elements.push(child);
            }
        }
    }
}

void JSBaseNode::OnRecycleWithBindThis(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(realNode_);
    std::queue<RefPtr<NG::UINode>> elements;
    elements.push(realNode_);
    while (!elements.empty()) {
        auto currentNode = elements.front();
        elements.pop();
        if (!currentNode) {
            continue;
        }
        if (AceType::InstanceOf<NG::CustomNodeBase>(currentNode)) {
            auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(currentNode);
            customNode->FireOnRecycleFunc();
        } else {
            for (const auto& child : currentNode->GetChildren()) {
                elements.push(child);
            }
        }
    }
}

void JSBaseNode::JSBind(BindingTarget globalObj)
{
    JSClass<JSBaseNode>::Declare("__JSBaseNode__");

    JSClass<JSBaseNode>::CustomMethod("create", &JSBaseNode::Create);
    JSClass<JSBaseNode>::CustomMethod("finishUpdateFunc", &JSBaseNode::FinishUpdateFunc);
    JSClass<JSBaseNode>::CustomMethod("postTouchEvent", &JSBaseNode::PostTouchEvent);
    JSClass<JSBaseNode>::CustomMethod("disposeNode", &JSBaseNode::Dispose);
    JSClass<JSBaseNode>::CustomMethod("updateStart", &JSBaseNode::UpdateStart);
    JSClass<JSBaseNode>::CustomMethod("updateEnd", &JSBaseNode::UpdateEnd);
    JSClass<JSBaseNode>::CustomMethod("onReuseWithBindObject", &JSBaseNode::OnReuseWithBindThis);
    JSClass<JSBaseNode>::CustomMethod("onRecycleWithBindObject", &JSBaseNode::OnRecycleWithBindThis);
    JSClass<JSBaseNode>::CustomMethod("postInputEvent", &JSBaseNode::PostInputEvent);

    JSClass<JSBaseNode>::Bind(globalObj, JSBaseNode::ConstructorCallback, JSBaseNode::DestructorCallback);
}
} // namespace OHOS::Ace::Framework
