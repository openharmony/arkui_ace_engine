/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"

#include "core/common/container.h"
#include "core/components_ng/syntax/if_else_model.h"
#include "core/components_ng/syntax/if_else_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/if_else_model_impl.h"

namespace OHOS::Ace {

std::unique_ptr<IfElseModel> IfElseModel::instance = nullptr;

IfElseModel* IfElseModel::GetInstance()
{
    if (!instance) {
        if (Container::IsCurrentUseNewPipeline()) {
            instance.reset(new NG::IfElseModelNG());
        } else {
            instance.reset(new Framework::IfElseModelImpl());
        }
    }
    return instance.get();
}
} // namespace OHOS::Ace


namespace OHOS::Ace::Framework {

void JSIfElse::JSBind(BindingTarget globalObj)
{
    JSClass<JSIfElse>::Declare("If");
    JSClass<JSIfElse>::StaticMethod("create", &JSIfElse::Create);
    JSClass<JSIfElse>::StaticMethod("pop", &JSIfElse::Pop);

    JSClass<JSIfElse>::StaticMethod("branchId", &JSIfElse::SetBranchId);
    JSClass<JSIfElse>::StaticMethod("getBranchId", &JSIfElse::GetBranchId);

    JSClass<JSIfElse>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
