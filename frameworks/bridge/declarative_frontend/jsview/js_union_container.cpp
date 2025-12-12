
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

#include "bridge/declarative_frontend/jsview/js_union_container.h"

#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "core/components_ng/pattern/union_container/union_container_model.h"
#include "core/components_ng/pattern/union_container/union_container_model_ng.h"
#include "core/components_ng/property/union_container_options.h"

namespace OHOS::Ace {
std::unique_ptr<UnionContainerModel> UnionContainerModel::instance_ = nullptr;
std::mutex UnionContainerModel::mutex_;

UnionContainerModel* UnionContainerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::UnionContainerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::UnionContainerModelNG());
            } else {
                // empty implementation
                instance_.reset(new UnionContainerModel());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSUnionContainer::Create(const JSCallbackInfo& info)
{
    NG::UnionContainerOptions options { .spacing = CalcDimension() };
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto spacingProperty = obj->GetProperty("spacing");
        if (spacingProperty->IsObject()) {
            auto spacingObj = JSRef<JSObject>::Cast(spacingProperty);
            if (!JSViewAbstract::ParseJsLengthMetricsVpWithResObj(spacingObj, options.spacing, options.spacingResObj)) {
                options.spacing.Reset();
            }
        }
    }
    UnionContainerModel::GetInstance()->Create(options);
}

void JSUnionContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSUnionContainer>::Declare("UnionContainer");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUnionContainer>::StaticMethod("create", &JSUnionContainer::Create, opt);

    JSClass<JSUnionContainer>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
