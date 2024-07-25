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

#include "bridge/declarative_frontend/jsview/js_scrollable.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };
} // namespace

EdgeEffect JSScrollable::ParseEdgeEffect(const JSRef<JSVal>& jsValue, EdgeEffect defaultValue)
{
    auto edgeEffect = static_cast<int32_t>(defaultValue);
    if (jsValue->IsNull() || jsValue->IsUndefined() || !JSViewAbstract::ParseJsInt32(jsValue, edgeEffect) ||
        edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(defaultValue);
    }
    return static_cast<EdgeEffect>(edgeEffect);
}

bool JSScrollable::ParseAlwaysEnable(const JSRef<JSVal>& jsValue, bool defaultValue)
{
    auto alwaysEnabled = defaultValue;
    if ((!(jsValue->IsNull() || jsValue->IsUndefined())) && jsValue->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> alwaysEnabledParam = paramObject->GetProperty("alwaysEnabled");
        alwaysEnabled = alwaysEnabledParam->IsBoolean() ? alwaysEnabledParam->ToBoolean() : defaultValue;
    }
    return alwaysEnabled;
}

DisplayMode JSScrollable::ParseDisplayMode(const JSCallbackInfo& info, DisplayMode defaultValue)
{
    if (info.Length() < 1) {
        return defaultValue;
    }
    auto displayMode = static_cast<int32_t>(defaultValue);
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        JSViewAbstract::ParseJsInt32(info[0], displayMode);
        if (displayMode < 0 || displayMode >= static_cast<int32_t>(DISPLAY_MODE.size())) {
            displayMode = static_cast<int32_t>(defaultValue);
        }
    }
    return static_cast<DisplayMode>(displayMode);
}

std::string JSScrollable::ParseBarColor(const JSCallbackInfo& info)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, "");
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_RETURN(theme, "");
    Color color(theme->GetForegroundColor());
    JSViewAbstract::ParseJsColor(info[0], color);
    return color.ColorToString();
}

std::string JSScrollable::ParseBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return "";
    }

    CalcDimension scrollBarWidth;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], scrollBarWidth) || info[0]->IsNull() || info[0]->IsUndefined() ||
        (info[0]->IsString() && info[0]->ToString().empty()) || LessNotEqual(scrollBarWidth.Value(), 0.0) ||
        scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, "");
        auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
        CHECK_NULL_RETURN(theme, "");
        scrollBarWidth = theme->GetNormalWidth();
    }
    return scrollBarWidth.ToString();
}

void JSScrollable::JsClip(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(true);
        return;
    }
    if (info[0]->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    } else if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}
} // namespace OHOS::Ace::Framework
