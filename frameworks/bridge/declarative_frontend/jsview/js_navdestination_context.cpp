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

#include "bridge/declarative_frontend/jsview/js_navdestination_context.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"

namespace OHOS::Ace::Framework {
JSRef<JSObject> JSNavDestinationContext::CreateJSNavPathInfo() const
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    CHECK_NULL_RETURN(pathInfo_, obj);
    obj->SetProperty<std::string>("name", pathInfo_->GetName());
    auto jsInfo = AceType::DynamicCast<JSNavPathInfo>(pathInfo_);
    JSRef<JSVal> param;
    if (jsInfo) {
        param = jsInfo->GetParam();
    }
    if (!param->IsEmpty()) {
        obj->SetPropertyObject("param", param);
    }
    return obj;
}

JSRef<JSObject> JSNavDestinationContext::CreateJSNavPathStack() const
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    auto stack = navigationStack_.Upgrade();
    CHECK_NULL_RETURN(stack, obj);
    auto jsStack = AceType::DynamicCast<JSNavigationStack>(stack);
    CHECK_NULL_RETURN(jsStack, obj);
    auto navPathStackObj = jsStack->GetDataSourceObj();
    if (navPathStackObj->IsEmpty()) {
        return obj;
    }

    return navPathStackObj;
}

JSRef<JSObject> JSNavDestinationContext::CreateJSObject()
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetPropertyObject("pathInfo", CreateJSNavPathInfo());
    obj->SetPropertyObject("pathStack", CreateJSNavPathStack());
    return obj;
}
} // namespace OHOS::Ace::Framework
