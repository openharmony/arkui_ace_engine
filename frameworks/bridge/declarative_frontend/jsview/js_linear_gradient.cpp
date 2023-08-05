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

#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
void JSLinearGradient::JSBind(BindingTarget globalObj)
{
    JSClass<JSLinearGradient>::Declare("LinearGradient");
    JSClass<JSLinearGradient>::Bind(globalObj, JSLinearGradient::Constructor, JSLinearGradient::Destructor);
}

void JSLinearGradient::Constructor(const JSCallbackInfo& args)
{
    auto jsLinearGradientPtr = Referenced::MakeRefPtr<JSLinearGradient>();
    jsLinearGradientPtr->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsLinearGradientPtr));

    if (args.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!args[0]->IsArray()) {
        return;
    }

    auto paramArray = JSRef<JSArray>::Cast(args[0]);
    size_t length = paramArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = paramArray->GetValueAt(i);
        if (!item->IsObject()) {
            return;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        JSRef<JSVal> jsColor = itemObject->GetProperty("color");
        Color color;
        if (!JSViewAbstract::ParseJsColor(jsColor, color)) {
            return;
        }
        JSRef<JSVal> jsOffset = itemObject->GetProperty("offset");
        CalcDimension offset;
        if (!JSViewAbstract::ParseJsDimensionVp(jsOffset, offset)) {
            return;
        }

        if (Negative(offset.ConvertToVp())) {
            offset = Dimension(0.0, DimensionUnit::VP);
        }

        if (GreatNotEqual(offset.ConvertToVp(), 1.0)) {
            offset = Dimension(1.0, DimensionUnit::VP);
        }
        jsLinearGradientPtr->gradient_.push_back(std::make_pair(color, offset));
    }
}

void JSLinearGradient::Destructor(JSLinearGradient* jsLinearGradientPtr)
{
    if (jsLinearGradientPtr != nullptr) {
        jsLinearGradientPtr->DecRefCount();
    }
}
} // namespace OHOS::Ace::Framework
