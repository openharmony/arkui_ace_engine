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

#include "bridge/declarative_frontend/jsview/js_scrollable_base.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::Framework {
void JSScrollableBase::JSFlingSpeedLimit(const JSCallbackInfo& info)
{
    double max = -1.0;
    if (!JSViewAbstract::ParseJsDouble(info[0], max)) {
        return;
    }
    double density = PipelineBase::GetCurrentDensity();
    NG::ScrollableModelNG::SetMaxFlingSpeed(max * density);
}

void JSScrollableBase::JSBind(BindingTarget globalObj)
{
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScrollableBase>::Declare("JSContainerBase");
    JSClass<JSScrollableBase>::StaticMethod("flingSpeedLimit", &JSScrollableBase::JSFlingSpeedLimit, opt);
    JSClass<JSScrollableBase>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
