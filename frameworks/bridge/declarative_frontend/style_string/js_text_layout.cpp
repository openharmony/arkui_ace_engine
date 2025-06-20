/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/style_string/js_text_layout.h"

#include <unordered_set>

#if !defined(PREVIEW) && defined (OHOS_STANDARD_SYSTEM)
#include "paragraph_napi/js_paragraph.h"
#include "core/components_ng/render/adapter/txt_paragraph.h"
#endif

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/style_string/js_span_object.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"
#include "core/components_ng/pattern/text/span/span_object.h"


namespace OHOS::Ace::Framework {
#if !defined(PREVIEW)
namespace {
constexpr int32_t CONST_NUM_TWO = 2;
}
#endif

CalcDimension JSTextLayout::ParseLengthMetrics(const JSRef<JSObject>& obj)
{
    CalcDimension size;
    auto value = 0.0;
    auto valueObj = obj->GetProperty("value");
    if (!valueObj->IsNull() && valueObj->IsNumber()) {
        value = valueObj->ToNumber<float>();
    }
    auto unit = DimensionUnit::VP;
    auto unitObj = obj->GetProperty("unit");
    if (!unitObj->IsNull() && unitObj->IsNumber()) {
        unit = static_cast<DimensionUnit>(unitObj->ToNumber<int32_t>());
    }
    if (value >= 0 && unit != DimensionUnit::PERCENT) {
        size = CalcDimension(value, unit);
    }
    return size;
}

void JSTextLayout::GetParagraphs(const JSCallbackInfo& info)
{
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
    if (info.Length() > CONST_NUM_TWO || !info[0]->IsObject()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto* spanString = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSpanString>();
    if (!spanString || !spanString->GetController()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Invalid styled string.");
        return;
    }
    auto spanStringController = spanString->GetController();

    std::optional<double> constraintWidth;
    if (info.Length() == CONST_NUM_TWO && info[1]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[1]);
        if (paramObject->HasProperty("constraintWidth")) {
            auto constraintWidthJSVal = paramObject->GetProperty("constraintWidth");
            if (!constraintWidthJSVal->IsNull() && constraintWidthJSVal->IsObject()) {
                constraintWidth = ParseLengthMetrics(constraintWidthJSVal).ConvertToPx();
            }
        }
    }
    auto engine = EngineHelper::GetCurrentEngineSafely();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scope(env);

    auto paraVec = SpanString::GetLayoutInfo(spanStringController, constraintWidth);
    JSRef<JSArray> paragraphJSArray = JSRef<JSArray>::New();
    uint32_t idx = 0;
    for (auto para : paraVec) {
        auto paragraph = AceType::DynamicCast<NG::TxtParagraph>(para);
        auto jsParagraph = OHOS::Rosen::JsParagraph::CreateJsTypography(env,
            paragraph->GetParagraphUniquePtr());
        JsiRef<JsiValue> jsParagraphVal = JsConverter::ConvertNapiValueToJsVal(jsParagraph);
        if (!jsParagraphVal->IsObject()) {
            continue;
        }
        paragraphJSArray->SetValueAt(idx++, JSRef<JSObject>::Cast(jsParagraphVal));
    }
    info.SetReturnValue(JSRef<JSVal>::Cast(paragraphJSArray));
#else
    JSRef<JSArray> paragraphJSArray = JSRef<JSArray>::New();
    info.SetReturnValue(JSRef<JSVal>::Cast(paragraphJSArray));
#endif
}

void JSTextLayout::JSBind(BindingTarget globalObj)
{
    JSClass<JSTextLayout>::Declare("TextLayout");
    JSClass<JSTextLayout>::StaticMethod("getParagraphs", &JSTextLayout::GetParagraphs);
    JSClass<JSTextLayout>::Bind(globalObj, JSTextLayout::Constructor, JSTextLayout::Destructor);
}
} // namespace OHOS::Ace::Framework