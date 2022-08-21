/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_list_item.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/pattern/list/list_item_view.h"

namespace OHOS::Ace::Framework {

void JSListItem::Create(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGW("Expected deep render function parameter");
        NG::ListItemView::Create();
        return;
    }
    RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));
    auto listItemDeepRenderFunc = [execCtx = args.GetExecutionContext(), jsDeepRenderFunc = std::move(jsDeepRender)](
                                      int32_t nodeId) {
        ACE_SCOPED_TRACE("JSListItem::ExecuteDeepRender");
        LOGD("ListItem elmtId %{public}d DeepRender JS function execution start ....", nodeId);
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        JSRef<JSVal> jsParams[2];
        jsParams[0] = JSRef<JSVal>::Make(ToJSValue(nodeId));
        jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
        jsDeepRenderFunc->ExecuteJS(2, jsParams);
    }; // listItemDeepRenderFunc lambda

    NG::ListItemView::Create(std::move(listItemDeepRenderFunc));
    args.ReturnSelf();
}

void JSListItem::CreateForPartialUpdate(const JSCallbackInfo& args) {}

void JSListItem::SetSticky(int32_t sticky) {}

void JSListItem::SetEditable(const JSCallbackInfo& args) {}

void JSListItem::SetSelectable(bool selectable) {}

void JSListItem::SelectCallback(const JSCallbackInfo& args) {}

void JSListItem::JsBorderRadius(const JSCallbackInfo& info) {}

} // namespace OHOS::Ace::Framework
