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

#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/bridge/card_frontend/card_frontend_declarative.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_object_template.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register.h"
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
#include "frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.h"

namespace OHOS::Ace::Framework {

void UpdateRootComponent(const panda::Local<panda::ObjectRef>& obj)
{
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        LOGE("loadDocument: argument provided is not a View!");
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("loadDocument: Container is null");
        return;
    }

    RefPtr<NG::FrameNode> pageNode;
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (Container::CurrentId() >= MIN_PLUGIN_SUBCONTAINER_ID) {
        auto pluginContainer = PluginManager::GetInstance().GetPluginSubContainer(Container::CurrentId());
        CHECK_NULL_VOID(pluginContainer);
        pageNode = pluginContainer->GetPluginNode().Upgrade();
        CHECK_NULL_VOID(pageNode);
    } else
#endif
    {
        auto frontEnd = AceType::DynamicCast<DeclarativeFrontendNG>(container->GetFrontend());
        CHECK_NULL_VOID(frontEnd);
        auto pageRouterManager = frontEnd->GetPageRouterManager();
        CHECK_NULL_VOID(pageRouterManager);
        pageNode = pageRouterManager->GetCurrentPageNode();
        CHECK_NULL_VOID(pageNode);
    }
    Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());
    if (!pageNode->GetChildren().empty()) {
        LOGW("the page has already add node, clean");
        auto oldChild = AceType::DynamicCast<NG::CustomNode>(pageNode->GetChildren().front());
        if (oldChild) {
            oldChild->Reset();
        }
        pageNode->Clean();
    }
    auto pageRootNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode());
    CHECK_NULL_VOID(pageRootNode);
    pageRootNode->MountToParent(pageNode);
    // update page life cycle function.
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnPageShow([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnShow();
        }
    });
    pagePattern->SetOnPageHide([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnHide();
        }
    });
    pagePattern->SetOnBackPressed([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPress();
        }
        return false;
    });
    auto customNode = AceType::DynamicCast<NG::CustomNodeBase>(pageRootNode);
    pagePattern->SetPageTransitionFunc(
        [weakCustom = WeakPtr<NG::CustomNodeBase>(customNode), weakPage = WeakPtr<NG::FrameNode>(pageNode)]() {
            auto custom = weakCustom.Upgrade();
            auto page = weakPage.Upgrade();
            if (custom && page) {
                NG::ScopedViewStackProcessor scopedViewStackProcessor;
                NG::ViewStackProcessor::GetInstance()->SetPageNode(page);
                custom->CallPageTransitionFunction();
                NG::ViewStackProcessor::GetInstance()->SetPageNode(nullptr);
            }
        });
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

} // namespace OHOS::Ace::Framework
