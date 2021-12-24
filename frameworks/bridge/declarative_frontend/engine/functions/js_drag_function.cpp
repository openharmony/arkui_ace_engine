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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

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

class JsItemDragInfo : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JsItemDragInfo>::Declare("ItemDragInfo");
        JSClass<JsItemDragInfo>::CustomMethod("getX", &JsItemDragInfo::GetX);
        JSClass<JsItemDragInfo>::CustomMethod("getY", &JsItemDragInfo::GetY);
        JSClass<JsItemDragInfo>::Bind(globalObj, &JsItemDragInfo::Constructor, &JsItemDragInfo::Destructor);
    }

    void GetX(const JSCallbackInfo& args)
    {
        auto xValue = JSVal(ToJSValue(itemDragInfo_->GetX()));
        auto xValueRef = JSRef<JSVal>::Make(xValue);
        args.SetReturnValue(xValueRef);
    }

    void GetY(const JSCallbackInfo& args)
    {
        auto yValue = JSVal(ToJSValue(itemDragInfo_->GetY()));
        auto yValueRef = JSRef<JSVal>::Make(yValue);
        args.SetReturnValue(yValueRef);
    }

    void SetItemDragInfo(const RefPtr<ItemDragInfo>& itemDragInfo)
    {
        itemDragInfo_ = itemDragInfo;
    }

    RefPtr<ItemDragInfo> GetItemDragInfo() const
    {
        return itemDragInfo_;
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto itemDragInfo = Referenced::MakeRefPtr<JsItemDragInfo>();
        itemDragInfo->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(itemDragInfo));
    }

    static void Destructor(JsItemDragInfo* itemDragInfo)
    {
        if (itemDragInfo != nullptr) {
            itemDragInfo->DecRefCount();
        }
    }

    RefPtr<ItemDragInfo> itemDragInfo_;
};

class JsDragEvent : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JsDragEvent>::Declare("DragEvent");
        JSClass<JsDragEvent>::CustomMethod("getPasteData", &JsDragEvent::GetJsPasteData);
        JSClass<JsDragEvent>::CustomMethod("getX", &JsDragEvent::GetX);
        JSClass<JsDragEvent>::CustomMethod("getY", &JsDragEvent::GetY);
        JSClass<JsDragEvent>::CustomMethod("getDescription", &JsDragEvent::GetDescription);
        JSClass<JsDragEvent>::CustomMethod("setDescription", &JsDragEvent::SetDescription);
        JSClass<JsDragEvent>::CustomMethod("setPixmap", &JsDragEvent::SetPixmap);
        JSClass<JsDragEvent>::Bind(globalObj, &JsDragEvent::Constructor, &JsDragEvent::Destructor);
    }

    void SetJsPasteData(const JSRef<JSObject>& jsPasteData)
    {
        jsPasteData_ = jsPasteData;
    }

    void GetJsPasteData(const JSCallbackInfo& args)
    {
        args.SetReturnValue(jsPasteData_);
    }

    void GetX(const JSCallbackInfo& args)
    {
        auto xValue = JSVal(ToJSValue(dragEvent_->GetX()));
        auto xValueRef = JSRef<JSVal>::Make(xValue);
        args.SetReturnValue(xValueRef);
    }

    void GetY(const JSCallbackInfo& args)
    {
        auto yValue = JSVal(ToJSValue(dragEvent_->GetY()));
        auto yValueRef = JSRef<JSVal>::Make(yValue);
        args.SetReturnValue(yValueRef);
    }

    void GetDescription(const JSCallbackInfo& args)
    {
        auto description = JSVal(ToJSValue(dragEvent_->GetDescription()));
        auto descriptionRef = JSRef<JSVal>::Make(description);
        args.SetReturnValue(descriptionRef);
    }

    void SetDescription(const JSCallbackInfo& args)
    {
        if (args[0]->IsString()) {
            dragEvent_->SetDescription(args[0]->ToString());
        }
    }

    void SetPixmap(const JSCallbackInfo& args)
    {
        if (args[0]->IsObject()) {
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
            dragEvent_->SetPixmap(CreatePixelMapFromNapiValue(args[0]));
#endif
        }
    }

    void SetDragEvent(const RefPtr<DragEvent>& dragEvent)
    {
        dragEvent_ = dragEvent;
    }

    RefPtr<DragEvent> GetDragEvent() const
    {
        return dragEvent_;
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto dragEvent = Referenced::MakeRefPtr<JsDragEvent>();
        dragEvent->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(dragEvent));
    }

    static void Destructor(JsDragEvent* dragEvent)
    {
        if (dragEvent != nullptr) {
            dragEvent->DecRefCount();
        }
    }

    RefPtr<DragEvent> dragEvent_;
    JSRef<JSObject> jsPasteData_;
};

void JsDragFunction::JSBind(BindingTarget globalObj)
{
    JsPasteData::JSBind(globalObj);
    JsDragEvent::JSBind(globalObj);
}

void JsDragFunction::Execute()
{
    JsFunction::Execute();
}

void JsDragFunction::Execute(const RefPtr<DragEvent>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param = obj;
    JsFunction::ExecuteJS(1, &param);
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

void JsGridDragFunction::JSBind(BindingTarget globalObj)
{
    JsPasteData::JSBind(globalObj);
    JsItemDragInfo::JSBind(globalObj);
}

JSRef<JSObject> JsGridDragFunction::CreateDragEvent(const RefPtr<ItemDragInfo>& info)
{
    JSRef<JSObject> dragObj = JSClass<JsItemDragInfo>::NewInstance();
    auto dragEvent = Referenced::Claim(dragObj->Unwrap<JsItemDragInfo>());
    dragEvent->SetItemDragInfo(info);
    return dragObj;
}

JSRef<JSObject> JsGridDragFunction::CreatePasteData(const RefPtr<PasteData>& info)
{
    JSRef<JSObject> pasteObj = JSClass<JsPasteData>::NewInstance();
    auto pasteData = Referenced::Claim(pasteObj->Unwrap<JsPasteData>());
    pasteData->SetPasteData(info);
    return pasteObj;
}

void JsGridDragFunction::ExecuteDragEnter(const RefPtr<ItemDragInfo>& info)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param = obj;
    JSRef<JSVal> jsRet = JsFunction::ExecuteJS(1, &param);
    if (jsRet->IsEmpty() && jsRet->IsBoolean()) {
        jsRet->ToBoolean();
    }
}

void JsGridDragFunction::ExecuteDragMove(const RefPtr<ItemDragInfo>& info, int32_t itemIndex, int32_t insertIndex)
{
    constexpr int32_t GRID_MOVE_PARAM_COUNT = 3;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param[GRID_MOVE_PARAM_COUNT];
    param[0] = obj;
    param[1] = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    param[GRID_MOVE_PARAM_COUNT - 1] = JSRef<JSVal>::Make(ToJSValue(insertIndex));
    JsFunction::ExecuteJS(GRID_MOVE_PARAM_COUNT, param);
}

void JsGridDragFunction::ExecuteDragLeave(const RefPtr<ItemDragInfo>& info, int32_t itemIndex)
{
    constexpr int32_t GRID_LEAVE_PARAM_COUNT = 2;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param[GRID_LEAVE_PARAM_COUNT];
    param[0] = obj;
    param[1] = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    JSRef<JSVal> jsRet = JsFunction::ExecuteJS(GRID_LEAVE_PARAM_COUNT, param);
    if (jsRet->IsEmpty() && jsRet->IsBoolean()) {
        jsRet->ToBoolean();
    }
}

JSRef<JSVal> JsGridDragFunction::ExecuteDragStart(const RefPtr<ItemDragInfo>& info, int32_t itemIndex)
{
    constexpr int32_t GRID_START_PARAM_COUNT = 2;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param[GRID_START_PARAM_COUNT];
    param[0] = obj;
    param[1] = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    return JsFunction::ExecuteJS(GRID_START_PARAM_COUNT, param);
}

void JsGridDragFunction::ExecuteDrop(
    const RefPtr<ItemDragInfo>& info, int32_t itemIndex, int32_t insertIndex, bool isSuccess)
{
    constexpr int32_t GRID_DROP_PARAM_COUNT = 4;
    int32_t index = 0;
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(CreateDragEvent(info));
    JSRef<JSVal> param[GRID_DROP_PARAM_COUNT];
    param[index++] = obj;
    param[index++] = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    param[index++] = JSRef<JSVal>::Make(ToJSValue(insertIndex));
    param[index] = JSRef<JSVal>::Make(ToJSValue(isSuccess));
    JsFunction::ExecuteJS(GRID_DROP_PARAM_COUNT, param);
}

} // namespace OHOS::Ace::Framework
