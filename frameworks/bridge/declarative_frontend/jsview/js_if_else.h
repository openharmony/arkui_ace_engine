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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IF_ELSE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IF_ELSE_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/syntax/if_else_model.h"

namespace OHOS::Ace::Framework {

class JSIfElse {
public:
    static void JSBind(BindingTarget globalObj);

    static void Create()
    {
        IfElseModel::GetInstance()->Create();
    }

    static void Pop()
    {
        if (ViewStackModel::GetInstance()->IsPrebuilding()) {
            return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSIfElse][pop]", &JSIfElse::Pop);
        }
        IfElseModel::GetInstance()->Pop();
    }

    static void SetBranchId(const JSCallbackInfo& info);

    static int32_t GetBranchId()
    {
        return IfElseModel::GetInstance()->GetBranchId();
    }

    static void CanRetake(const JSCallbackInfo& info);

    static void GetRetakenElmtIds(const JSCallbackInfo& info);
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_IF_ELSE_H
