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

#include "frameworks/bridge/js_frontend/engine/quickjs/component_api_bridge.h"

#include "frameworks/bridge/common/dom/dom_div.h"
#include "frameworks/bridge/common/dom/dom_list.h"
#include "frameworks/bridge/common/dom/dom_stack.h"

namespace OHOS::Ace::Framework {

JSValue CompoentApiBridge::JsGetScrollOffset(JSContext* ctx, NodeId nodeId)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        return JS_NULL;
    }
    auto page = instance->GetRunningPage();
    if (!page) {
        return JS_NULL;
    }
    Offset offset;
    auto task = [nodeId, page, &offset]() {
        auto domDoc = page->GetDomDocument();
        if (!domDoc) {
            return;
        }

        auto domNode = domDoc->GetDOMNodeById(nodeId);
        if (!domNode) {
            return;
        }
        auto domList = AceType::DynamicCast<DOMList>(domNode);
        if (domList) {
            offset = domList->GetCurrentOffset();
            return;
        }

        auto scrollComponent = domNode->GetScrollComponent();
        if (!scrollComponent) {
            return;
        }
        auto controller = scrollComponent->GetScrollPositionController();
        if (!controller) {
            return;
        }
        offset = controller->GetCurrentOffset();
    };
    auto delegate = instance->GetDelegate();
    if (!delegate) {
        return JS_NULL;
    }
    delegate->PostSyncTaskToPage(task);
    JSValue offsetContext = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, offsetContext, "x", JS_NewFloat64(ctx, offset.GetX()));
    JS_SetPropertyStr(ctx, offsetContext, "y", JS_NewFloat64(ctx, offset.GetY()));
    return offsetContext;
}

JSValue CompoentApiBridge::JsGetBoundingRect(JSContext* ctx, NodeId nodeId)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        return JS_NULL;
    }
    auto delegate = instance->GetDelegate();
    if (!delegate) {
        return JS_NULL;
    }
    Rect boundingRect = delegate->GetBoundingRectData(nodeId);
    JSValue rectContext = JS_NewObject(ctx);
    JS_SetPropertyStr(ctx, rectContext, "width", JS_NewFloat64(ctx, boundingRect.Width()));
    JS_SetPropertyStr(ctx, rectContext, "height", JS_NewFloat64(ctx, boundingRect.Height()));
    JS_SetPropertyStr(ctx, rectContext, "top", JS_NewFloat64(ctx, boundingRect.Top()));
    JS_SetPropertyStr(ctx, rectContext, "left", JS_NewFloat64(ctx, boundingRect.Left()));
    return rectContext;
}

} // namespace OHOS::Ace::Framework
