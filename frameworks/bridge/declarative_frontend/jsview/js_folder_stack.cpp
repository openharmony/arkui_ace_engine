/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_folder_stack.h"

#include <algorithm>

#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "core/common/display_info.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_info.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/stack_model_impl.h"
#include "frameworks/core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"

namespace OHOS::Ace {
FolderStackModel* FolderStackModel::GetInstance()
{
    static NG::FolderStackModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
const static std::array<Alignment, 9> ALIGNMENT_ARR { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };

JSRef<JSVal> FolderStackEventToJSValue(const NG::FolderEventInfo& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("foldStatus", static_cast<int32_t>(eventInfo.GetFolderState()));
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> HoverStatusChangeEventToJSValue(const NG::FolderEventInfo& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("foldStatus", static_cast<int32_t>(eventInfo.GetFolderState()));
    obj->SetProperty("isHoverMode", static_cast<int32_t>(eventInfo.IsHoverMode()));
    obj->SetProperty("appRotation", static_cast<int32_t>(eventInfo.GetRotation()));
    obj->SetProperty("windowStatusType",
        static_cast<int32_t>(JSFolderStack::NotifyWindowStatusChange(eventInfo.GetWindowMode())));
    return JSRef<JSVal>::Cast(obj);
}

void JSFolderStack::Create(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSArray> params = JSRef<JSArray>::Cast(info[0]);
        auto upperId = params->GetProperty("upperItems");
        if (upperId->IsNull() || upperId->IsUndefined() || !upperId->IsArray()) {
            FolderStackModel::GetInstance()->Create();
            return;
        }
        auto upperIdParams = JSRef<JSArray>::Cast(upperId);
        auto upperItemLength = upperIdParams->Length();
        std::vector<std::string> upperItems(upperItemLength);
        if (upperId->IsArray()) {
            for (size_t i = 0; i < upperItemLength; i++) {
                upperItems[i] = upperIdParams->GetValueAt(i)->ToString();
            }
        }
        FolderStackModel::GetInstance()->Create(upperItems);
    } else {
        FolderStackModel::GetInstance()->Create();
    }
}

void JSFolderStack::SetAlignContent(const JSCallbackInfo& info)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        FolderStackModel::GetInstance()->SetAlignment(Alignment::CENTER);
        return;
    }
    auto value = info[0]->ToNumber<size_t>();
    if (value < 0 || static_cast<int32_t>(value) >= static_cast<int32_t>(ALIGNMENT_ARR.size())) {
        FolderStackModel::GetInstance()->SetAlignment(Alignment::CENTER);
        return;
    }
    FolderStackModel::GetInstance()->SetAlignment(ALIGNMENT_ARR[value]);
}

void JSFolderStack::JsEnableAnimation(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        FolderStackModel::GetInstance()->SetEnableAnimation(true);
        return;
    }
    auto isEnableAnimation = info[0]->ToBoolean();
    FolderStackModel::GetInstance()->SetEnableAnimation(isEnableAnimation);
}

WindowStatus JSFolderStack::NotifyWindowStatusChange(WindowMode mode)
{
    auto WindowStatus = WindowStatus::WINDOW_STATUS_UNDEFINED;
    if (mode == WindowMode::WINDOW_MODE_FLOATING) {
        WindowStatus = WindowStatus::WINDOW_STATUS_FLOATING;
    } else if (mode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY || mode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        WindowStatus = WindowStatus::WINDOW_STATUS_SPLITSCREEN;
    }
    if (mode == WindowMode::WINDOW_MODE_FULLSCREEN) {
        WindowStatus = WindowStatus::WINDOW_STATUS_FULLSCREEN;
    }
    return WindowStatus;
}

void JSFolderStack::SetAutoHalfFold(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        FolderStackModel::GetInstance()->SetAutoHalfFold(true);
        return;
    }
    auto IsAutoHalfFold = info[0]->ToBoolean();
    FolderStackModel::GetInstance()->SetAutoHalfFold(IsAutoHalfFold);
}

void JSFolderStack::JSOnFolderStateChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NG::FolderEventInfo, 1>>(
        JSRef<JSFunc>::Cast(info[0]), FolderStackEventToJSValue);
    auto onFolderStateChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                                   const NG::FolderEventInfo& value) {
        ACE_SCORING_EVENT("FolderStack.onFolderStateChange");
        func->Execute(value);
    };
    FolderStackModel::GetInstance()->SetOnFolderStateChange(std::move(onFolderStateChange));
}

void JSFolderStack::JSOnHoverStatusChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NG::FolderEventInfo, 1>>(
        JSRef<JSFunc>::Cast(info[0]), HoverStatusChangeEventToJSValue);
    auto onHoverStatusChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                                   const NG::FolderEventInfo& value) {
        ACE_SCORING_EVENT("FolderStack.onHoverStatusChange");
        func->Execute(value);
    };
    FolderStackModel::GetInstance()->SetOnHoverStatusChange(std::move(onHoverStatusChange));
}

void JSFolderStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSFolderStack>::Declare("FolderStack");
    JSClass<JSFolderStack>::StaticMethod("create", &JSFolderStack::Create);
    JSClass<JSFolderStack>::StaticMethod("alignContent", &JSFolderStack::SetAlignContent);
    JSClass<JSFolderStack>::StaticMethod("enableAnimation", &JSFolderStack::JsEnableAnimation);
    JSClass<JSFolderStack>::StaticMethod("autoHalfFold", &JSFolderStack::SetAutoHalfFold);
    JSClass<JSFolderStack>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSFolderStack>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSFolderStack>::StaticMethod("onFolderStateChange", &JSFolderStack::JSOnFolderStateChange);
    JSClass<JSFolderStack>::StaticMethod("onHoverStatusChange", &JSFolderStack::JSOnHoverStatusChange);
    JSClass<JSFolderStack>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
