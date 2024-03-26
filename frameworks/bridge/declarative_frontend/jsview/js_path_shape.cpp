/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_path_shape.h"

namespace OHOS::Ace::Framework {

void JSPathShape::ConstructorCallback(const JSCallbackInfo& info)
{
    auto jsPath = AceType::MakeRefPtr<JSPathShape>();
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

void JSPathShape::DestructorCallback(JSPathShape* jsPathShape)
{
    if (jsPathShape != nullptr) {
        jsPathShape->DecRefCount();
    }
}

void JSPathShape::ObjectCommands(const JSCallbackInfo& info)
{
    info.ReturnSelf();
    if (info.Length() > 0 && info[0]->IsString()) {
        auto path = AceType::DynamicCast<Path>(basicShape_);
        if (path) {
            path->SetValue(info[0]->ToString());
        }
    }
}

void JSPathShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSPathShape>::Declare("__PathShape__");

    JSClass<JSPathShape>::CustomMethod("commands", &JSPathShape::ObjectCommands);
    JSClass<JSPathShape>::CustomMethod("offset", &JSShapeAbstract::ObjectOffset);
    JSClass<JSPathShape>::CustomMethod("fill", &JSShapeAbstract::ObjectFill);
    JSClass<JSPathShape>::CustomMethod("position", &JSShapeAbstract::ObjectPosition);

    JSClass<JSPathShape>::InheritAndBind<JSShapeAbstract>(
        globalObj, JSPathShape::ConstructorCallback, JSPathShape::DestructorCallback);
}

} // namespace OHOS::Ace::Framework
