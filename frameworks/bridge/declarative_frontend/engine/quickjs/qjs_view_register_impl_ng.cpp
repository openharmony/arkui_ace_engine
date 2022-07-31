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

#include <cstdint>

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"

namespace OHOS::Ace::Framework {

JSValue JsGetInspectorTree(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    return JS_UNDEFINED;
}

JSValue JsGetInspectorByKey(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    return JS_UNDEFINED;
}

JSValue JsSendEventByKey(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    return JS_UNDEFINED;
}

JSValue JsSendKeyEvent(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    return JS_UNDEFINED;
}

void JsBindViews(BindingTarget globalObj)
{
    JSViewAbstract::JSBind();
    JSContainerBase::JSBind();
    JSView::JSBind(globalObj);
    JSText::JSBind(globalObj);
    JSColumn::JSBind(globalObj);
    JSRow::JSBind(globalObj);
    JSStack::JSBind(globalObj);
    JSImage::JSBind(globalObj);
    JSLazyForEach::JSBind(globalObj);
    JSList::JSBind(globalObj);
    JSListItem::JSBind(globalObj);
    JSLocalStorage::JSBind(globalObj);
    JSPersistent::JSBind(globalObj);
    JSEnvironment::JSBind(globalObj);
}

void CreatePageRoot(RefPtr<JsAcePage>& page, JSView* view)
{
    auto pageRootNode = view->CreateNode();
    page->SetRootNode(pageRootNode);
}

} // namespace OHOS::Ace::Framework
