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

#include "frameworks/bridge/declarative_frontend/jsview/js_symbol_span.h"

#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/span_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"
#include "bridge/declarative_frontend/jsview/js_text.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/text/symbol_span_model.h"
#include "core/components_ng/pattern/text/symbol_span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_model.h"

namespace OHOS::Ace {
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";

std::unique_ptr<SymbolSpanModel> SymbolSpanModel::instance_ = nullptr;
std::mutex SymbolSpanModel::mutex_;

SymbolSpanModel* SymbolSpanModel::GetInstance()
{
    static NG::SymbolSpanModelNG instance;
    return &instance;
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSSymbolSpan::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();

    RefPtr<ResourceObject> resObj;
    UnregisterSpanResource("fontSize");
    if (!ParseJsDimensionFpNG(info[0], fontSize, resObj, false)) {
        fontSize = theme->GetTextStyle().GetFontSize();
        SymbolSpanModel::GetInstance()->SetFontSize(fontSize);
        return;
    }
    if (SystemProperties::ConfigChangePerform() && resObj) {
        RegisterSpanResource<CalcDimension>("fontSize", resObj, fontSize);
    }
    if (fontSize.IsNegative()) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }

    SymbolSpanModel::GetInstance()->SetFontSize(fontSize);
}

void JSSymbolSpan::SetFontWeight(const std::string& value)
{
    SymbolSpanModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSSymbolSpan::SetFontColor(const JSCallbackInfo& info)
{
    std::vector<Color> symbolColor;
    if (SystemProperties::ConfigChangePerform()) {
        UnregisterSpanResource("symbolColor");
        std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
        bool ret = ParseJsSymbolColor(info[0], symbolColor, true, resObjArr);
        if (!resObjArr.empty()) {
            auto spanNode = AceType::DynamicCast<NG::SpanNode>(
                NG::ViewStackProcessor::GetInstance()->GetMainElementNode());
            CHECK_NULL_VOID(spanNode);
            spanNode->RegisterSymbolFontColorResource("symbolColor",
                symbolColor, resObjArr);
        }
        if (ret) {
            SymbolSpanModel::GetInstance()->SetFontColor(symbolColor);
        }
        return;
    }
    if (!ParseJsSymbolColor(info[0], symbolColor)) {
        return;
    }
    SymbolSpanModel::GetInstance()->SetFontColor(symbolColor);
}

void JSSymbolSpan::SetSymbolRenderingStrategy(const JSCallbackInfo& info)
{
    uint32_t strategy = 0;
    ParseJsInteger(info[0], strategy);
    SymbolSpanModel::GetInstance()->SetSymbolRenderingStrategy(strategy);
}

void JSSymbolSpan::SetSymbolEffect(const JSCallbackInfo& info)
{
    uint32_t strategy = 0;
    ParseJsInteger(info[0], strategy);
    SymbolSpanModel::GetInstance()->SetSymbolEffect(strategy);
}

void JSSymbolSpan::Create(const JSCallbackInfo& info)
{
    uint32_t symbolId = 0;
    RefPtr<ResourceObject> resourceObject;
    if (info.Length() > 0) {
        ParseJsSymbolId(info[0], symbolId, resourceObject);
    }

    SymbolSpanModel::GetInstance()->Create(symbolId);
    std::vector<std::string> familyNames;
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        ParseJsSymbolCustomFamilyNames(familyNames, info[0]);
        SymbolSpanModel::GetInstance()->SetFontFamilies(familyNames);
        SymbolSpanModel::GetInstance()->SetSymbolType(SymbolType::CUSTOM);
    } else {
        familyNames.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        SymbolSpanModel::GetInstance()->SetFontFamilies(familyNames);
        SymbolSpanModel::GetInstance()->SetSymbolType(SymbolType::SYSTEM);
    }
}

void JSSymbolSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSSymbolSpan>::Declare("SymbolSpan");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSymbolSpan>::StaticMethod("create", &JSSymbolSpan::Create, opt);
    JSClass<JSSymbolSpan>::StaticMethod("fontSize", &JSSymbolSpan::SetFontSize, opt);
    JSClass<JSSymbolSpan>::StaticMethod("fontWeight", &JSSymbolSpan::SetFontWeight, opt);
    JSClass<JSSymbolSpan>::StaticMethod("fontColor", &JSSymbolSpan::SetFontColor, opt);
    JSClass<JSSymbolSpan>::StaticMethod("renderingStrategy", &JSSymbolSpan::SetSymbolRenderingStrategy, opt);
    JSClass<JSSymbolSpan>::StaticMethod("effectStrategy", &JSSymbolSpan::SetSymbolEffect, opt);
    JSClass<JSSymbolSpan>::InheritAndBind<JSContainerBase>(globalObj);
}

template<typename T>
void JSSymbolSpan::RegisterSpanResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
{
    auto uiNode = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(uiNode);
    auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
    if (spanNode) {
        spanNode->RegisterResource<T>(key, resObj, value);
    }
}

void JSSymbolSpan::UnregisterSpanResource(const std::string& key)
{
    auto uiNode = NG::ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(uiNode);
    auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
    if (spanNode) {
        spanNode->UnregisterResource(key);
    }
}
} // namespace OHOS::Ace::Framework
