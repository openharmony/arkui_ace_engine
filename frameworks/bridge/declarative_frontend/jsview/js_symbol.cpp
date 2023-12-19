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
#include "frameworks/bridge/declarative_frontend/jsview/js_symbol.h"

#include "frameworks/bridge/declarative_frontend/engine/bindings.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<SymbolModel> SymbolModel::instance_ = nullptr;
std::mutex SymbolModel::mutex_;

SymbolModel* SymbolModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::SymbolModelNG());
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSSymbol::JSBind(BindingTarget globalObj)
{
    JSClass<JSSymbol>::Declare("SymbolGlyph");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSymbol>::StaticMethod("create", &JSSymbol::Create, opt);
    JSClass<JSSymbol>::StaticMethod("fontWeight", &JSSymbol::SetFontWeight, opt);
    JSClass<JSSymbol>::StaticMethod("fontSize", &JSSymbol::SetFontSize, opt);
    JSClass<JSSymbol>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSymbol::Create(const JSCallbackInfo& info)
{
    uint32_t symbolId;
    ParseJsSymbolId(info[0], symbolId);

    SymbolModel::GetInstance()->Create(symbolId);
}

void JSSymbol::SetFontSize(const JSCallbackInfo& info)
{
    CalcDimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    if (fontSize.IsNegative()) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    SymbolModel::GetInstance()->SetFontSize(fontSize);
}

void JSSymbol::SetFontWeight(const std::string& value)
{
    SymbolModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

} // namespace OHOS::Ace::Framework
