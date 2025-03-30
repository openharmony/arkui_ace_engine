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

#include <string>

#include "base/memory/referenced.h"
#include "core/components_ng/syntax/repeat_model_ng.h"
#include "bridge/declarative_frontend/jsview/js_repeat.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"


namespace OHOS::Ace {
RepeatModel* RepeatModel::GetInstance()
{
    static NG::RepeatModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace


namespace OHOS::Ace::Framework {

void JSRepeat::StartRender()
{
    RepeatModel::GetInstance()->StartRender();
}

void JSRepeat::FinishRender(const JSCallbackInfo& info)
{
    std::list<int32_t> removedElmtIds;

    if ((info.Length() != 1) || !info[0]->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for Repeat.FinishRender");
        return;
    }
    RepeatModel::GetInstance()->FinishRender(removedElmtIds);

    if (!removedElmtIds.size()) {
        return;
    }

    // convert list of removed elmtIds: std::list to JSArray<number>
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[0]);
    size_t index = jsArr->Length();
    for (const auto& rmElmtId : removedElmtIds) {
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(rmElmtId)));
    }
}

// signature is
// fromIndex: number
void JSRepeat::MoveChild(const JSCallbackInfo& info)
{
    if ((info.Length() != 1) || !info[0]->IsNumber()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for Repeat.MoveChild");
        return;
    }

    const auto fromIndex = info[0]->ToNumber<uint32_t>();
    RepeatModel::GetInstance()->MoveChild(fromIndex);
}

// signature is
// id: string
// parentView? : JSView
void JSRepeat::CreateNewChildStart(const JSCallbackInfo& info)
{
    if ((info.Length() < 1) || !info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for Repeat.CreateNewChildStart");
        return;
    }

    const auto key = info[0]->ToString();
    RepeatModel::GetInstance()->CreateNewChildStart(key);
}

// signature is
// id: string
// parentView? : JSView
void JSRepeat::CreateNewChildFinish(const JSCallbackInfo& info)
{
    if ((info.Length() < 1) || !info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_REPEAT, "Invalid arguments for Repeat.CreateNewChildFinish");
        return;
    }

    const auto key = info[0]->ToString();
    RepeatModel::GetInstance()->CreateNewChildFinish(key);
}

void JSRepeat::OnMove(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto onMove = [execCtx = info.GetExecutionContext(), func = JSRef<JSFunc>::Cast(info[0])]
            (int32_t from, int32_t to) {
                auto params = ConvertToJSValues(from, to);
                func->Call(JSRef<JSObject>(), params.size(), params.data());
            };
        RepeatModel::GetInstance()->OnMove(std::move(onMove));
    } else {
        RepeatModel::GetInstance()->OnMove(nullptr);
    }
}

void JSRepeat::JSBind(BindingTarget globalObj)
{
    JSClass<JSRepeat>::Declare("RepeatNative");
    JSClass<JSRepeat>::StaticMethod("startRender", &JSRepeat::StartRender);
    JSClass<JSRepeat>::StaticMethod("finishRender", &JSRepeat::FinishRender);
    JSClass<JSRepeat>::StaticMethod("moveChild", &JSRepeat::MoveChild);
    JSClass<JSRepeat>::StaticMethod("createNewChildStart", &JSRepeat::CreateNewChildStart);
    JSClass<JSRepeat>::StaticMethod("createNewChildFinish", &JSRepeat::CreateNewChildFinish);
    JSClass<JSRepeat>::StaticMethod("onMove", &JSRepeat::OnMove);
    JSClass<JSRepeat>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
