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

#include "frameworks/bridge/declarative_frontend/jsview/js_layoutable_view.h"

namespace OHOS::Ace::Framework {

constexpr float DEFAULT_LAYOUT_WEIGHT = 0.0f;

void JSLayoutableView::JsPixelRound(const JSCallbackInfo& info)
{
    uint16_t value = 0;
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return;
    }
    JSRef<JSObject> object = JSRef<JSObject>::Cast(arg);
    ParsePixelRoundOfStart(object, value);
    ParsePixelRoundOfTop(object, value);
    ParsePixelRoundOfEnd(object, value);
    ParsePixelRoundOfBottom(object, value);
    ViewAbstractModel::GetInstance()->SetPixelRound(value);
}

void JSLayoutableView::JsChainWeight(const JSCallbackInfo& info)
{
    NG::ChainWeightPair chainWeightPair(DEFAULT_LAYOUT_WEIGHT, DEFAULT_LAYOUT_WEIGHT);
    auto jsVal = info[0];
    if (jsVal->IsObject()) {
        JSRef<JSObject> val = JSRef<JSObject>::Cast(jsVal);
        auto weightX = val->GetProperty("horizontal");
        auto weightY = val->GetProperty("vertical");
        if (weightX->IsNumber()) {
            chainWeightPair.first = weightX->ToNumber<float>();
        }
        if (weightY->IsNumber()) {
            chainWeightPair.second = weightY->ToNumber<float>();
        }
    }
    ViewAbstractModel::GetInstance()->SetChainWeight(chainWeightPair);
}

void JSLayoutableView::ParsePixelRoundOfStart(const JSRef<JSObject>& object, uint16_t& value)
{
    JSRef<JSVal> jsStartValue = object->GetProperty("start");
    if (jsStartValue->IsNumber()) {
        int32_t startValue = jsStartValue->ToNumber<int32_t>();
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_START);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_START);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(startValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_START);
        }
    }
}

void JSLayoutableView::ParsePixelRoundOfTop(const JSRef<JSObject>& object, uint16_t& value)
{
    JSRef<JSVal> jsTopValue = object->GetProperty("top");
    if (jsTopValue->IsNumber()) {
        int32_t topValue = jsTopValue->ToNumber<int32_t>();
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_TOP);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_TOP);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(topValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_TOP);
        }
    }
}

void JSLayoutableView::ParsePixelRoundOfEnd(const JSRef<JSObject>& object, uint16_t& value)
{
    JSRef<JSVal> jsEndValue = object->GetProperty("end");
    if (jsEndValue->IsNumber()) {
        int32_t endValue = jsEndValue->ToNumber<int32_t>();
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_END);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_END);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(endValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_END);
        }
    }
}

void JSLayoutableView::ParsePixelRoundOfBottom(const JSRef<JSObject>& object, uint16_t& value)
{
    JSRef<JSVal> jsBottomValue = object->GetProperty("bottom");
    if (jsBottomValue->IsNumber()) {
        int32_t bottomValue = jsBottomValue->ToNumber<int32_t>();
        if (PixelRoundCalcPolicy::FORCE_CEIL == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_CEIL_BOTTOM);
        } else if (PixelRoundCalcPolicy::FORCE_FLOOR == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::FORCE_FLOOR_BOTTOM);
        } else if (PixelRoundCalcPolicy::NO_FORCE_ROUND == static_cast<PixelRoundCalcPolicy>(bottomValue)) {
            value |= static_cast<uint16_t>(PixelRoundPolicy::NO_FORCE_ROUND_BOTTOM);
        }
    }
}

} // namespace OHOS::Ace::Framework