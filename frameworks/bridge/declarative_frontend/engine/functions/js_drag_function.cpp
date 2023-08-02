/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "js_native_api_types.h"
#include "napi/native_api.h"
#include "native_engine/native_engine.h"

#include "core/common/udmf/udmf_client.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"
#endif

namespace OHOS::Ace::Framework {
class JsPasteData : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JsPasteData>::Declare("PasteData");
        JSClass<JsPasteData>::CustomMethod("setPlainText", &JsPasteData::SetPlainText);
        JSClass<JsPasteData>::CustomMethod("getPlainText", &JsPasteData::GetPlainText);
        JSClass<JsPasteData>::Bind(globalObj, &JsPasteData::Constructor, &JsPasteData::Destructor);
    }

    void SetPlainText(const JSCallbackInfo& args)
    {
        if (args[0]->IsString()) {
            pasteData_->SetPlainText(args[0]->ToString());
        }
    }

    void GetPlainText(const JSCallbackInfo& args)
    {
        auto plainText = JSVal(ToJSValue(pasteData_->GetPlainText()));
        auto plainTextRef = JSRef<JSVal>::Make(plainText);
        args.SetReturnValue(plainTextRef);
    }

    void SetPasteData(const RefPtr<PasteData>& pasteData)
    {
        pasteData_ = pasteData;
    }

    RefPtr<PasteData> GetPasteData() const
    {
        return pasteData_;
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsPasteData = Referenced::MakeRefPtr<JsPasteData>();
        jsPasteData->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsPasteData));
    }

    static void Destructor(JsPasteData* jsPasteData)
    {
        if (jsPasteData != nullptr) {
            jsPasteData->DecRefCount();
        }
    }

    RefPtr<PasteData> pasteData_;
};

void JsDragEvent::JSBind(BindingTarget globalObj)
{
    JSClass<JsDragEvent>::Declare("DragEvent");
    JSClass<JsDragEvent>::CustomMethod("getPasteData", &JsDragEvent::GetJsPasteData);
    JSClass<JsDragEvent>::CustomMethod("getDisplayX", &JsDragEvent::GetScreenX);
    JSClass<JsDragEvent>::CustomMethod("getDisplayY", &JsDragEvent::GetScreenY);
    JSClass<JsDragEvent>::CustomMethod("getWindowX", &JsDragEvent::GetX);
    JSClass<JsDragEvent>::CustomMethod("getWindowY", &JsDragEvent::GetY);
    JSClass<JsDragEvent>::CustomMethod("getX", &JsDragEvent::GetX);
    JSClass<JsDragEvent>::CustomMethod("getY", &JsDragEvent::GetY);
    JSClass<JsDragEvent>::CustomMethod("getDescription", &JsDragEvent::GetDescription);
    JSClass<JsDragEvent>::CustomMethod("setDescription", &JsDragEvent::SetDescription);
#ifdef ENABLE_DRAG_FRAMEWORK
    JSClass<JsDragEvent>::CustomMethod("setData", &JsDragEvent::SetData);
    JSClass<JsDragEvent>::CustomMethod("getData", &JsDragEvent::GetData);
    JSClass<JsDragEvent>::CustomMethod("getSummary", &JsDragEvent::GetSummary);
    JSClass<JsDragEvent>::CustomMethod("setResult", &JsDragEvent::SetResult);
    JSClass<JsDragEvent>::CustomMethod("getResult", &JsDragEvent::GetResult);
    JSClass<JsDragEvent>::CustomMethod("getPreviewRect", &JsDragEvent::GetPreviewRect);
    JSClass<JsDragEvent>::CustomMethod("setDragInfo", &JsDragEvent::SetDragInfo);
    JSClass<JsDragEvent>::CustomMethod("getDragInfo", &JsDragEvent::GetDragInfo);
    JSClass<JsDragEvent>::CustomProperty(
        "useCustomDropAnimation", &JsDragEvent::GetUseCustomDropAnimation, &JsDragEvent::SetUseCustomDropAnimation);
    JSClass<JsDragEvent>::CustomProperty("dragBehavior", &JsDragEvent::GetDragBehavior, &JsDragEvent::SetDragBehavior);
#endif
    JSClass<JsDragEvent>::CustomMethod("getVelocityX", &JsDragEvent::GetVelocityX);
    JSClass<JsDragEvent>::CustomMethod("getVelocityY", &JsDragEvent::GetVelocityY);
    JSClass<JsDragEvent>::CustomMethod("getVelocity", &JsDragEvent::GetVelocity);
    JSClass<JsDragEvent>::Bind(globalObj, &JsDragEvent::Constructor, &JsDragEvent::Destructor);
}

void JsDragEvent::SetJsPasteData(const JSRef<JSObject>& jsPasteData)
{
    jsPasteData_ = jsPasteData;
}

void JsDragEvent::GetJsPasteData(const JSCallbackInfo& args)
{
    args.SetReturnValue(jsPasteData_);
}

void JsDragEvent::GetScreenX(const JSCallbackInfo& args)
{
    auto xValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetScreenX())));
    auto xValueRef = JSRef<JSVal>::Make(xValue);
    args.SetReturnValue(xValueRef);
}

void JsDragEvent::GetScreenY(const JSCallbackInfo& args)
{
    auto yValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetScreenY())));
    auto yValueRef = JSRef<JSVal>::Make(yValue);
    args.SetReturnValue(yValueRef);
}

void JsDragEvent::GetX(const JSCallbackInfo& args)
{
    auto xValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetX())));
    auto xValueRef = JSRef<JSVal>::Make(xValue);
    args.SetReturnValue(xValueRef);
}

void JsDragEvent::GetY(const JSCallbackInfo& args)
{
    auto yValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetY())));
    auto yValueRef = JSRef<JSVal>::Make(yValue);
    args.SetReturnValue(yValueRef);
}

void JsDragEvent::GetDescription(const JSCallbackInfo& args)
{
    auto description = JSVal(ToJSValue(dragEvent_->GetDescription()));
    auto descriptionRef = JSRef<JSVal>::Make(description);
    args.SetReturnValue(descriptionRef);
}

void JsDragEvent::SetDescription(const JSCallbackInfo& args)
{
    if (args[0]->IsString()) {
        dragEvent_->SetDescription(args[0]->ToString());
    }
}
#ifdef ENABLE_DRAG_FRAMEWORK
void JsDragEvent::SetData(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        LOGE("info[0] is not an object when try SetData");
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    panda::Local<JsiValue> value = args[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(nativeEngine->GetScopeManager());
    NativeValue* nativeValue = nativeEngine->ValueToNativeValue(valueWrapper);
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->TransformUnifiedData(nativeValue);
    CHECK_NULL_VOID(udData);
    dragEvent_->SetData(udData);
}

void JsDragEvent::GetData(const JSCallbackInfo& args)
{
    auto dragData = dragEvent_->GetData();
    if (!dragEvent_->IsGetDataSuccess()) {
        LOGE("UDMF GetData failed in first attempt");
        std::string udKey = dragEvent_->GetUdKey();
        if (udKey.empty()) {
            args.SetReturnValue(JSVal::Undefined());
            return;
        }
        int ret = UdmfClient::GetInstance()->GetData(dragData, udKey);
        if (ret != 0) {
            LOGW("UDMF GetData failed: %{public}d", ret);
            args.SetReturnValue(JSVal::Undefined());
            return;
        } else {
            dragEvent_->SetData(dragData);
            dragEvent_->SetIsGetDataSuccess(true);
        }
    }
    CHECK_NULL_VOID(dragData);
    NativeValue* nativeValue = UdmfClient::GetInstance()->TransformUdmfUnifiedData(dragData);
    CHECK_NULL_VOID(nativeValue);
    auto jsValue = JsConverter::ConvertNativeValueToJsVal(nativeValue);
    args.SetReturnValue(jsValue);
}

void JsDragEvent::GetSummary(const JSCallbackInfo& args)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    auto summary = dragEvent_->GetSummary();
    NativeValue* nativeValue = UdmfClient::GetInstance()->TransformSummary(summary);
    CHECK_NULL_VOID(nativeValue);
    auto jsValue = JsConverter::ConvertNativeValueToJsVal(nativeValue);
    args.SetReturnValue(jsValue);
}

void JsDragEvent::SetResult(const JSCallbackInfo& args)
{
    if (args[0]->IsNumber()) {
        auto dragRet = args[0]->ToNumber<int32_t>();
        dragEvent_->SetResult((DragRet)dragRet);
    }
}

void JsDragEvent::GetResult(const JSCallbackInfo& args)
{
    auto dragRet = JSVal(ToJSValue(static_cast<int32_t>(dragEvent_->GetResult())));
    auto dragRetRef = JSRef<JSVal>::Make(dragRet);
    args.SetReturnValue(dragRetRef);
}

void JsDragEvent::GetPreviewRect(const JSCallbackInfo& args)
{
    auto rectObj = CreateRectangle(dragEvent_->GetPreviewRect());
    JSRef<JSVal> previewRect = JSRef<JSObject>::Cast(rectObj);
    args.SetReturnValue(previewRect);
}

void JsDragEvent::SetDragInfo(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        LOGE("info[0] is not an object when try SetDragInfo");
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    panda::Local<JsiValue> value = args[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(nativeEngine->GetScopeManager());
    NativeValue* nativeValue = nativeEngine->ValueToNativeValue(valueWrapper);
    RefPtr<UnifiedData> udData = UdmfClient::GetInstance()->TransformUnifiedData(nativeValue);
    CHECK_NULL_VOID(udData);
    dragEvent_->SetData(udData);
}

void JsDragEvent::GetDragInfo(const JSCallbackInfo& args)
{
    auto dragData = dragEvent_->GetDragInfo();
    CHECK_NULL_VOID(dragData);
    NativeValue* nativeValue = UdmfClient::GetInstance()->TransformUdmfUnifiedData(dragData);
    CHECK_NULL_VOID(nativeValue);
    auto jsValue = JsConverter::ConvertNativeValueToJsVal(nativeValue);
    args.SetReturnValue(jsValue);
}

void JsDragEvent::SetUseCustomDropAnimation(const JSCallbackInfo& args)
{
    if (args[0]->IsBoolean()) {
        dragEvent_->UseCustomAnimation(args[0]->ToBoolean());
    }
}

void JsDragEvent::GetUseCustomDropAnimation(const JSCallbackInfo& args)
{
    auto useCustomAnimation = JSVal(ToJSValue(dragEvent_->IsUseCustomAnimation()));
    auto useCustomAnimationRef = JSRef<JSVal>::Make(useCustomAnimation);
    args.SetReturnValue(useCustomAnimationRef);
}

void JsDragEvent::SetDragBehavior(const JSCallbackInfo& args)
{
    if (args[0]->IsNumber()) {
        dragEvent_->SetCopy(!static_cast<bool>(args[0]->ToNumber<int32_t>()));
    }
}

void JsDragEvent::GetDragBehavior(const JSCallbackInfo& args)
{
    auto dragBehavior = JSVal(ToJSValue(static_cast<int32_t>(!dragEvent_->IsCopy())));
    auto dragBehaviorRef = JSRef<JSVal>::Make(dragBehavior);
    args.SetReturnValue(dragBehaviorRef);
}
#endif

void JsDragEvent::GetVelocityX(const JSCallbackInfo& args)
{
    auto jsValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetVelocity().GetVelocityX())));
    auto jsValueRef = JSRef<JSVal>::Make(jsValue);
    args.SetReturnValue(jsValueRef);
}

void JsDragEvent::GetVelocityY(const JSCallbackInfo& args)
{
    auto jsValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetVelocity().GetVelocityY())));
    auto jsValueRef = JSRef<JSVal>::Make(jsValue);
    args.SetReturnValue(jsValueRef);
}

void JsDragEvent::GetVelocity(const JSCallbackInfo& args)
{
    auto jsValue = JSVal(ToJSValue(SystemProperties::Px2Vp(dragEvent_->GetVelocity().GetVelocityValue())));
    auto jsValueRef = JSRef<JSVal>::Make(jsValue);
    args.SetReturnValue(jsValueRef);
}

void JsDragEvent::Constructor(const JSCallbackInfo& args)
{
    auto dragEvent = Referenced::MakeRefPtr<JsDragEvent>();
    dragEvent->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(dragEvent));
}

void JsDragEvent::Destructor(JsDragEvent* dragEvent)
{
    if (dragEvent != nullptr) {
        dragEvent->DecRefCount();
    }
}
#ifdef ENABLE_DRAG_FRAMEWORK
JSRef<JSObject> JsDragEvent::CreateRectangle(const Rect& info)
{
    JSRef<JSObject> rectObj = JSRef<JSObject>::New();
    rectObj->SetProperty<double>("x", SystemProperties::Px2Vp(info.Left()));
    rectObj->SetProperty<double>("y", SystemProperties::Px2Vp(info.Top()));
    rectObj->SetProperty<double>("width", SystemProperties::Px2Vp(info.Width()));
    rectObj->SetProperty<double>("height", SystemProperties::Px2Vp(info.Height()));
    return rectObj;
}
#endif

void JsDragFunction::JSBind(BindingTarget globalObj)
{
    JsPasteData::JSBind(globalObj);
    JsDragEvent::JSBind(globalObj);
}

void JsDragFunction::Execute()
{
    JsFunction::Execute();
}

JSRef<JSVal> JsDragFunction::Execute(const RefPtr<DragEvent>& info, const std::string& extraParams)
{
    JSRef<JSVal> dragInfo = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> jsonInfo = JSRef<JSVal>::Make(ToJSValue(extraParams));
    JSRef<JSVal> params[] = { dragInfo, jsonInfo };
    return JsFunction::ExecuteJS(2, params);
}

JSRef<JSVal> JsDragFunction::Execute(const RefPtr<DragEvent>& info)
{
    JSRef<JSVal> dragInfo = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> params[] = { dragInfo };
    return JsFunction::ExecuteJS(1, params);
}

JSRef<JSVal> JsDragFunction::ItemDragStartExecute(const ItemDragInfo& info, int32_t itemIndex)
{
    JSRef<JSVal> itemDragInfo = JSRef<JSObject>::Cast(CreateItemDragInfo(info));
    JSRef<JSVal> itemIndexParam = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    JSRef<JSVal> params[] = { itemDragInfo, itemIndexParam };
    return JsFunction::ExecuteJS(2, params);
}

void JsDragFunction::ItemDragEnterExecute(const ItemDragInfo& info)
{
    JSRef<JSObject> itemDragInfo = JSRef<JSObject>::Cast(CreateItemDragInfo(info));
    JSRef<JSVal> param = itemDragInfo;
    JsFunction::ExecuteJS(1, &param);
}

void JsDragFunction::ItemDragMoveExecute(const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex)
{
    JSRef<JSVal> itemDragInfo = JSRef<JSObject>::Cast(CreateItemDragInfo(info));
    JSRef<JSVal> itemIndexParam = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    JSRef<JSVal> insertIndexParam = JSRef<JSVal>::Make(ToJSValue(insertIndex));
    JSRef<JSVal> params[] = { itemDragInfo, itemIndexParam, insertIndexParam };
    JsFunction::ExecuteJS(3, params);
}

void JsDragFunction::ItemDragLeaveExecute(const ItemDragInfo& info, int32_t itemIndex)
{
    JSRef<JSVal> itemDragInfo = JSRef<JSObject>::Cast(CreateItemDragInfo(info));
    JSRef<JSVal> itemIndexParam = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    JSRef<JSVal> params[] = { itemDragInfo, itemIndexParam };
    JsFunction::ExecuteJS(2, params);
}

void JsDragFunction::ItemDropExecute(const ItemDragInfo& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess)
{
    JSRef<JSVal> itemDragInfo = JSRef<JSObject>::Cast(CreateItemDragInfo(info));
    JSRef<JSVal> itemIndexParam = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    JSRef<JSVal> insertIndexParam = JSRef<JSVal>::Make(ToJSValue(insertIndex));
    JSRef<JSVal> isSuccessParam = JSRef<JSVal>::Make(ToJSValue(isSuccess));
    JSRef<JSVal> params[] = { itemDragInfo, itemIndexParam, insertIndexParam, isSuccessParam };
    JsFunction::ExecuteJS(4, params);
}

JSRef<JSObject> JsDragFunction::CreateDragEvent(const RefPtr<DragEvent>& info)
{
    JSRef<JSObject> dragObj = JSClass<JsDragEvent>::NewInstance();
    auto dragEvent = Referenced::Claim(dragObj->Unwrap<JsDragEvent>());
    dragEvent->SetDragEvent(info);
    auto pasteDataInfo = dragEvent->GetDragEvent()->GetPasteData();
    JSRef<JSObject> pasteData = CreatePasteData(pasteDataInfo);
    dragEvent->SetJsPasteData(pasteData);
    return dragObj;
}

JSRef<JSObject> JsDragFunction::CreatePasteData(const RefPtr<PasteData>& info)
{
    JSRef<JSObject> pasteObj = JSClass<JsPasteData>::NewInstance();
    auto pasteData = Referenced::Claim(pasteObj->Unwrap<JsPasteData>());
    pasteData->SetPasteData(info);
    return pasteObj;
}

JSRef<JSObject> JsDragFunction::CreateItemDragInfo(const ItemDragInfo& info)
{
    JSRef<JSObject> itemDragInfoObj = JSRef<JSObject>::New();
    itemDragInfoObj->SetProperty<double>("x", SystemProperties::Px2Vp(info.GetX()));
    itemDragInfoObj->SetProperty<double>("y", SystemProperties::Px2Vp(info.GetY()));
    return itemDragInfoObj;
}

} // namespace OHOS::Ace::Framework
