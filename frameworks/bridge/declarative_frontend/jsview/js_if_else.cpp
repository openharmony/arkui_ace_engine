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

#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"

#include "core/common/container.h"
#include "core/components_ng/syntax/if_else_model.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/if_else_model_impl.h"

namespace OHOS::Ace {
IfElseModel* IfElseModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::IfElseModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::IfElseModelNG instance;
        return &instance;
    } else {
        static Framework::IfElseModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSIfElse::JSBind(BindingTarget globalObj)
{
    JSClass<JSIfElse>::Declare("If");
    JSClass<JSIfElse>::StaticMethod("create", &JSIfElse::Create);
    JSClass<JSIfElse>::StaticMethod("pop", &JSIfElse::Pop);

    JSClass<JSIfElse>::StaticMethod("branchId", &JSIfElse::SetBranchId);
    JSClass<JSIfElse>::StaticMethod("getBranchId", &JSIfElse::GetBranchId);
    JSClass<JSIfElse>::StaticMethod("canRetake", &JSIfElse::CanRetake);
    JSClass<JSIfElse>::StaticMethod("getRetakenElmtIds", &JSIfElse::GetRetakenElmtIds);

    JSClass<JSIfElse>::Bind<>(globalObj);
}

void JSIfElse::CanRetake(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        TAG_LOGW(AceLogTag::ACE_IF, "CanRetake needs only 1 param");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    if (!info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_IF, "CanRetake needs string param");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto id = info[0]->ToString();
    auto result = IfElseModel::GetInstance()->CanRetake(id);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
}

void JSIfElse::GetRetakenElmtIds(const JSCallbackInfo& info)
{
    if (info.Length() != 1) {
        TAG_LOGW(AceLogTag::ACE_IF, "GetRetakenElmtIds needs 1 param");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    if (!info[0]->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_IF, "GetRetakenElmtIds needs array param");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    std::list<int32_t> retakenElmtIds;
    auto result = IfElseModel::GetInstance()->GetRetakenElmtIds(retakenElmtIds);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));

    // convert list of retaken elmtIds: std::list to JSArray<number>
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[0]);
    size_t index = jsArr->Length();
    for (const auto& elmtId : retakenElmtIds) {
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(elmtId)));
    }
}

void JSIfElse::SetBranchId(const JSCallbackInfo& info)
{
    int32_t paramsLength = 3;
    if (!info[0]->IsNumber()) {
        return;
    }
    const int32_t branchid = info[0]->ToNumber<int32_t>();
    std::list<int32_t> removedElmtIds;
    std::list<int32_t> reservedElmtIds;
    IfElseModel::GetInstance()->SetBranchId(branchid, removedElmtIds, reservedElmtIds);

    if ((info.Length() < paramsLength) || (!info[0]->IsNumber()) || (!info[1]->IsArray()) || (!info[2]->IsArray())) {
        TAG_LOGD(AceLogTag::ACE_IF, "If Params is not expected, maybe use old SDK");
        return;
    }

    if (!removedElmtIds.size() && !reservedElmtIds.size()) {
        return;
    }
    // convert list of removed elmtIds: std::list to JSArray<number>
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[1]);
    size_t index = jsArr->Length();
    for (const auto& rmElmtId : removedElmtIds) {
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(rmElmtId)));
    }

    // convert list of reserved elmtIds: std::list to JSArray<number>
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(info[2]);
    size_t idx = jsArray->Length();
    for (const auto& rsElmtId : reservedElmtIds) {
        jsArray->SetValueAt(idx++, JSRef<JSVal>::Make(ToJSValue(rsElmtId)));
    }
}
} // namespace OHOS::Ace::Framework
