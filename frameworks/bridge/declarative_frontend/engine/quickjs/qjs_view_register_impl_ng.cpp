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
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/qjs_view_register.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_environment.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_list_item.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_local_storage.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_persistent.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_context.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_register.h"
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"

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
    JSForEach::JSBind(globalObj);
    JSIfElse::JSBind(globalObj);
    JSTabs::JSBind(globalObj);
    //JSTabsController::JSBind(globalObj);
    JSTabContent::JSBind(globalObj);
}

void CreatePageRoot(RefPtr<JsAcePage>& page, JSView* view)
{
    CHECK_NULL_VOID(view);
    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
    CHECK_NULL_VOID(frontEnd);
    auto pageRouterManager = frontEnd->GetPageRouterManager();
    CHECK_NULL_VOID(pageRouterManager);
    auto pageNode = pageRouterManager->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pageRootNode = view->CreateUINode();
    CHECK_NULL_VOID(pageRootNode);
    pageRootNode->MountToParent(pageNode);
}

} // namespace OHOS::Ace::Framework
