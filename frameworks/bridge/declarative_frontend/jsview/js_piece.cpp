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

#include "frameworks/bridge/declarative_frontend/jsview/js_piece.h"

#include "core/components/piece/piece_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSPiece::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("piece create error, info is non-vaild");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto getContent = paramObject->GetProperty("content");
    auto getIcon = paramObject->GetProperty("icon");

    std::string content;
    std::string icon;
    if (getContent->IsString()) {
        content = getContent->ToString();
    }
    if (getIcon->IsString()) {
        icon = getIcon->ToString();
    }

    auto component = AceType::MakeRefPtr<PieceComponent>();
    component->SetContent(content);
    component->SetIcon(icon);
    ViewStackProcessor::GetInstance()->Push(component);
}

void JSPiece::JSBind(BindingTarget globalObj)
{
    JSClass<JSPiece>::Declare("Piece");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPiece>::StaticMethod("create", &JSPiece::Create, opt);
    JSClass<JSPiece>::StaticMethod("iconPosition", &JSPiece::SetIconPosition, opt);
    JSClass<JSPiece>::Inherit<JSViewAbstract>();
    JSClass<JSPiece>::Bind<>(globalObj);
}

void JSPiece::SetIconPosition(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    if (!info[0]->IsNumber()) {
        LOGE("arg is not number.");
        return;
    }

    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PieceComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("pieceComponent is null");
        return;
    }

    auto pieceIconPosition = static_cast<OHOS::Ace::IconPosition>(info[0]->ToNumber<int32_t>());
    component->SetIconPosition(pieceIconPosition);
}

} // namespace OHOS::Ace::Framework
