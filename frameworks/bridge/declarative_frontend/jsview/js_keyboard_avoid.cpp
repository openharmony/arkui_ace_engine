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

#include "frameworks/bridge/declarative_frontend/jsview/js_keyboard_avoid.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
const std::vector<KeyBoardAvoidMode> KEYBOARD_AVOID_MODES = { KeyBoardAvoidMode::OFFSET, KeyBoardAvoidMode::RESIZE };

void JSKeyboardAvoid::SetKeyboardAvoidMode(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsNumber()) {
        pipeline->SetEnableKeyBoardAvoidMode(false);
        return;
    }
    auto index = info[0]->ToNumber<int32_t>();
    if (index < 0 || index >= static_cast<int32_t>(KEYBOARD_AVOID_MODES.size())) {
        return;
    }
    if (KEYBOARD_AVOID_MODES[index] == KeyBoardAvoidMode::RESIZE) {
        pipeline->SetEnableKeyBoardAvoidMode(true);
    } else {
        pipeline->SetEnableKeyBoardAvoidMode(false);
    }
}

void JSKeyboardAvoid::GetKeyboardAvoidMode(const JSCallbackInfo& info)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto obj = "KeyBoardAvoidMode.OFFSET";
    if (pipeline->IsEnableKeyBoardAvoidMode()) {
        obj =  "KeyBoardAvoidMode.RESIZE";
    }
    auto returnValue = JSVal(ToJSValue(obj));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSKeyboardAvoid::JSBind(BindingTarget globalObj)
{
    JSClass<JSKeyboardAvoid>::Declare("__KeyboardAvoid__");
    JSClass<JSKeyboardAvoid>::StaticMethod("setKeyboardAvoid", &JSKeyboardAvoid::SetKeyboardAvoidMode);
    JSClass<JSKeyboardAvoid>::StaticMethod("getKeyboardAvoid", &JSKeyboardAvoid::GetKeyboardAvoidMode);
    JSClass<JSKeyboardAvoid>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework