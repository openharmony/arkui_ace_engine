/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include <optional>

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<DisplayMode> DISPLAY_MODE = { DisplayMode::OFF, DisplayMode::AUTO, DisplayMode::ON };

void ParsePreviewBadge(const JSRef<JSVal>& result, NG::PreviewBadge& badge)
{
    if (result->IsEmpty()) {
        return;
    }
    if (result->IsNumber()) {
        int64_t number = result->ToNumber<int64_t>();
        if (number < 0 || number > INT_MAX) {
            badge.mode = NG::PreviewBadgeMode::AUTO;
        } else {
            badge.mode = NG::PreviewBadgeMode::USER_SET;
            badge.count = result->ToNumber<int32_t>();
        }
    } else if (result->IsBoolean()) {
        badge.mode = result->ToBoolean() ? NG::PreviewBadgeMode::AUTO : NG::PreviewBadgeMode::NO_BADGE;
    }
}
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

EffectEdge JSScrollable::ParseEffectEdge(const JSRef<JSVal>& jsValue)
{
    auto effectEdge = static_cast<int32_t>(EffectEdge::ALL);
    if (jsValue->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> effectEdgedParam = paramObject->GetProperty("effectEdge");
        if (effectEdgedParam->IsNull() || effectEdgedParam->IsUndefined() ||
            !JSViewAbstract::ParseJsInt32(effectEdgedParam, effectEdge) ||
            effectEdge < static_cast<int32_t>(EffectEdge::START) ||
            effectEdge > static_cast<int32_t>(EffectEdge::END)) {
            effectEdge = static_cast<int32_t>(EffectEdge::ALL);
        }
    }
    return static_cast<EffectEdge>(effectEdge);
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

std::string JSScrollable::ParseBarColor(const JSCallbackInfo& info, RefPtr<ResourceObject>& resObj)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, "");
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_RETURN(theme, "");
    Color color(theme->GetForegroundColor());
    JSViewAbstract::ParseJsColor(info[0], color, resObj);
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

std::optional<PresetFillType> JSScrollable::ParsePresetFillType(const JSRef<JSVal>& jsValue)
{
    int32_t presetFillType = 0;
    if (JSViewAbstract::ParseJsInt32(jsValue, presetFillType) &&
        InRegion(static_cast<int32_t>(PresetFillType::BREAKPOINT_DEFAULT),
            static_cast<int32_t>(PresetFillType::BREAKPOINT_SM2MD3LG5), presetFillType)) {
        return static_cast<PresetFillType>(presetFillType);
    } else {
        return std::nullopt;
    }
}

void JSScrollable::ParseEditModeOptions(const JSCallbackInfo& info, NG::EditModeOptions& options)
{
    if (info.Length() < 1) {
        return;
    }
    auto value = info[0];
    if (value->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(value);
        auto gatherAnimation = obj->GetProperty("enableGatherSelectedItemsAnimation");
        if (gatherAnimation->IsBoolean()) {
            options.enableGatherSelectedItemsAnimation = gatherAnimation->ToBoolean();
        }

        auto getPreviewBadge = obj->GetProperty("onGetPreviewBadge");
        if (getPreviewBadge->IsFunction()) {
            WeakPtr<NG::FrameNode> targetNode =
                AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto onGetPreviewBadge =
                [execCtx = info.GetExecutionContext(),
                    func = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(getPreviewBadge)),
                    node = targetNode]() {
                    JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                    PipelineContext::SetCallBackNode(node);
                    NG::PreviewBadge badge;
                    auto result = func->ExecuteJS();
                    ParsePreviewBadge(result, badge);
                    return badge;
                };
            options.getPreviewBadge = std::move(onGetPreviewBadge);
        }
    }
}
} // namespace OHOS::Ace::Framework
