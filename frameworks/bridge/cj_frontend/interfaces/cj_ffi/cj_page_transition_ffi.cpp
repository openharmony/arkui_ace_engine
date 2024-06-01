/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "cj_page_transition_ffi.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/stage/page_transition_model_ng.h"
#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiPageTransitionEnterCreate(int type, int duration, char* curve, int delay)
{
    PageTransitionOption option = {(RouteType)type, duration, delay, Framework::CreateCurve(std::string(curve))};
    PageTransitionModel::GetInstance()->CreateTransition(PageTransitionType::ENTER, option);
}

void FfiPageTransitionExitCreate(int type, int duration, char* curve, int delay)
{
    PageTransitionOption option = {
        static_cast<RouteType>(type), duration, delay, Framework::CreateCurve(std::string(curve))};
    PageTransitionModel::GetInstance()->CreateTransition(PageTransitionType::EXIT, option);
}

void FfiPageTransitionSlideEffect(int slideEffect)
{
    if (slideEffect == 0) {
        return;
    }
    PageTransitionModel::GetInstance()->SetSlideEffect(static_cast<SlideEffect>(slideEffect));
}

void FfiPageTransitionTranslate(double x, double y, double z)
{
    LOGI("FfiPageTransitionTranslate called.");
    NG::TranslateOptions option;
    option.x = CalcDimension(x, DimensionUnit::VP);
    option.y = CalcDimension(y, DimensionUnit::VP);
    option.z = CalcDimension(z, DimensionUnit::VP);
    PageTransitionModel::GetInstance()->SetTranslateEffect(option);
}

void FfiPageTransitionScalePointer(double x, double y, double z, double centerX, double centerY)
{
    CalcDimension cX = CalcDimension(centerX, DimensionUnit::VP);
    CalcDimension cY = CalcDimension(centerY, DimensionUnit::VP);
    NG::ScaleOptions option(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), cX, cY);
    PageTransitionModel::GetInstance()->SetScaleEffect(option);
}

void FfiPageTransitionSetOpacity(double value)
{
    LOGI("FfiPageTransitionSetOpacity called.");
    PageTransitionModel::GetInstance()->SetOpacityEffect(static_cast<float>(value));
}

void FfiPageTransitionOnEnter(void (*callback)(int type, double progress))
{
    auto onEnterHandler = [ffiCallBack = CJLambda::Create(callback)](
                              RouteType type, float progress) { ffiCallBack(static_cast<int>(type), progress); };
    PageTransitionModel::GetInstance()->SetOnEnter(std::move(onEnterHandler));
}

void FfiPageTransitionOnExit(void (*callback)(int type, double progress))
{
    auto onExitHandler = [ffiCallBack = CJLambda::Create(callback)](
                             RouteType type, float progress) { ffiCallBack(static_cast<int>(type), progress); };
    PageTransitionModel::GetInstance()->SetOnExit(std::move(onExitHandler));
}
}