/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/jsview/models/divider_model_impl.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
DividerModel* DividerModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::DividerModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::DividerModelNG instance;
        return &instance;
    } else {
        static Framework::DividerModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSDivider::Create()
{
    DividerModel::GetInstance()->Create();
}

void JSDivider::SetVertical(bool isVertical)
{
    DividerModel::GetInstance()->Vertical(isVertical);
}

void JSDivider::SetLineCap(int lineCap)
{
    auto lineCapStyle = LineCap::BUTT;

    if (static_cast<int>(LineCap::SQUARE) == lineCap) {
        lineCapStyle = LineCap::SQUARE;
    } else if (static_cast<int>(LineCap::ROUND) == lineCap) {
        lineCapStyle = LineCap::ROUND;
    } else {
        // default linecap of divider
        lineCapStyle = LineCap::BUTT;
    }
    DividerModel::GetInstance()->LineCap(lineCapStyle);
}

void JSDivider::SetDividerColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto theme = GetTheme<DividerTheme>();
    CHECK_NULL_VOID(theme);
    Color dividerColor = theme->GetColor();
    if (!ParseJsColor(info[0], dividerColor)) {
        DividerModel::GetInstance()->ResetDividerColor();
        return;
    }
    DividerModel::GetInstance()->DividerColor(dividerColor);
}

void JSDivider::SetStrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    auto theme = GetTheme<DividerTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension strokeWidth = theme->GetStokeWidth();
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        strokeWidth = 1.0_px;
    }
    if (!ParseJsDimensionVpNG(info[0], strokeWidth, false)) {
        strokeWidth = 1.0_px;
    }
    DividerModel::GetInstance()->StrokeWidth(strokeWidth);
}

void JSDivider::JSBind(BindingTarget globalObj)
{
    JSClass<JSDivider>::Declare("Divider");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSDivider>::StaticMethod("create", &JSDivider::Create, opt);
    JSClass<JSDivider>::StaticMethod("color", &JSDivider::SetDividerColor, opt);
    JSClass<JSDivider>::StaticMethod("vertical", &JSDivider::SetVertical, opt);
    JSClass<JSDivider>::StaticMethod("strokeWidth", &JSDivider::SetStrokeWidth, opt);
    JSClass<JSDivider>::StaticMethod("lineCap", &JSDivider::SetLineCap, opt);
    JSClass<JSDivider>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSDivider>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSDivider>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSDivider>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSDivider>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDivider>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSDivider>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSDivider>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSDivider>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDivider>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSDivider>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
