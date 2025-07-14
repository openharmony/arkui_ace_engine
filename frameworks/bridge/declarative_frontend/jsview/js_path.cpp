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

#include "frameworks/bridge/declarative_frontend/jsview/js_path.h"

#include "bridge/declarative_frontend/jsview/models/path_model_impl.h"
#include "core/common/container.h"
#include "core/components/shape/shape_component.h"
#include "core/components_ng/pattern/shape/path_model.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {
PathModel* PathModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::PathModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::PathModelNG instance;
        return &instance;
    } else {
        static Framework::PathModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSPath::Create(const JSCallbackInfo& info)
{
    PathModel::GetInstance()->Create();
    JSShapeAbstract::SetSize(info);
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> commands = obj->GetProperty("commands");
        std::string strRet;
        RefPtr<ResourceObject> commandsResObj;
        if (!ParseJsString(commands, strRet, commandsResObj)) {
            return;
        }
        UnRegisterResource("PathCommands");
        if (SystemProperties::ConfigChangePerform() && commandsResObj) {
            RegisterResource<std::string>("PathCommands", commandsResObj, strRet);
        }
        PathModel::GetInstance()->SetCommands(strRet);
    }
}

void JSPath::SetCommands(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    UnRegisterResource("PathCommands");
    if (info[0]->IsUndefined()) {
        PathModel::GetInstance()->SetCommands("undefined");
    } else if (info[0]->IsObject()) {
        JSRef<JSObject> commandsObj = JSRef<JSObject>::Cast(info[0]);
        std::string strRet;
        RefPtr<ResourceObject> commandsResObj;
        if (!ParseJsString(commandsObj, strRet, commandsResObj)) {
            return;
        }
        if (SystemProperties::ConfigChangePerform() && commandsResObj) {
            RegisterResource<std::string>("PathCommands", commandsResObj, strRet);
        }
        PathModel::GetInstance()->SetCommands(strRet);
    } else if (info[0]->IsString()) {
        PathModel::GetInstance()->SetCommands(info[0]->ToString());
    }
}

void JSPath::ObjectCommands(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && info[0]->IsString()) {
        auto path = AceType::DynamicCast<Path>(basicShape_);
        if (path) {
            path->SetValue(info[0]->ToString());
        }
    }
}

void JSPath::ConstructorCallback(const JSCallbackInfo& info)
{
    auto jsPath = AceType::MakeRefPtr<JSPath>();
    auto path = AceType::MakeRefPtr<Path>();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> params = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> commands = params->GetProperty("commands");
        if (commands->IsString()) {
            path->SetValue(commands->ToString());
        }
    }
    jsPath->SetBasicShape(path);
    jsPath->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(jsPath));
}

void JSPath::DestructorCallback(JSPath* jsPath)
{
    if (jsPath != nullptr) {
        jsPath->DecRefCount();
    }
}

void JSPath::JSBind(BindingTarget globalObj)
{
    JSClass<JSPath>::Declare("Path");
    JSClass<JSPath>::StaticMethod("create", &JSPath::Create);
    JSClass<JSPath>::StaticMethod("commands", &JSPath::SetCommands);

    JSClass<JSPath>::CustomMethod("commands", &JSPath::ObjectCommands);
    JSClass<JSPath>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSPath>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSPath>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSPath>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSPath>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSPath>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSPath>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSPath>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSPath>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSPath>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSPath::ConstructorCallback, JSPath::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
