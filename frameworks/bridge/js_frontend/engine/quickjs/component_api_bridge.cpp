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

#include "core/animation/curves.h"
#include "frameworks/bridge/common/dom/dom_list.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {

JSValue ComponentApiBridge::JsGetScrollOffset(JSContext* ctx, NodeId nodeId)
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

JSValue ComponentApiBridge::JsGetBoundingRect(JSContext* ctx, NodeId nodeId)
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

void ComponentApiBridge::JsScrollTo(JSContext* ctx, const std::string& args, NodeId nodeId)
{
    auto instance = static_cast<QjsEngineInstance*>(JS_GetContextOpaque(ctx));
    if (instance == nullptr) {
        LOGE("ComponentApiBridge::JsScrollTo instance is null");
        return;
    }
    auto page = instance->GetRunningPage();
    if (!page) {
        LOGE("ComponentApiBridge::JsScrollTo page is null");
        return;
    }

    auto task = [nodeId, page, args]() {
        auto domDoc = page->GetDomDocument();
        if (!domDoc) {
            LOGE("ComponentApiBridge::JsScrollTo dom document is null!");
            return;
        }

        auto domNode = domDoc->GetDOMNodeById(nodeId);
        if (!domNode) {
            LOGE("ComponentApiBridge::JsScrollTo node not exist!");
            return;
        }

        std::unique_ptr<JsonValue> argsValue = JsonUtil::ParseJsonString(args);
        if (!argsValue || !argsValue->IsArray() || argsValue->GetArraySize() < 1) {
            LOGE("parse args error");
            return;
        }
        std::unique_ptr<JsonValue> scrollToPara = argsValue->GetArrayItem(0);
        if (!scrollToPara->IsValid()) {
            return;
        }
        int32_t index = scrollToPara->GetInt("index", 0);
        auto domList = AceType::DynamicCast<DOMList>(domNode);
        if (domList) {
            // list has specialized scrollTo method.
            domList->ScrollToMethod(index);
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

        std::string id = scrollToPara->GetString("id", "");
        double position = scrollToPara->GetDouble("position", 0.0);
        double duration = scrollToPara->GetDouble("duration", 300.0); // Default duration is 300ms.
        std::string timingFunction = scrollToPara->GetString("timingFunction", "ease");
        std::string successId = scrollToPara->GetString("success", "");
        std::string failId = scrollToPara->GetString("fail", "");
        std::string completeId = scrollToPara->GetString("complete", "");
        auto context = domNode->GetPipelineContext();
        auto callback = [context, successId, completeId]() {
            auto refContext = context.Upgrade();
            if (refContext) {
                refContext->SendCallbackMessageToFrontend(successId, std::string("\"success\",null"));
                refContext->SendCallbackMessageToFrontend(completeId, std::string("\"complete\",null"));
            }
        };

        bool result = false;
        if (scrollToPara->Contains("position")) {
            result = controller->AnimateTo(position, duration, CreateCurve(timingFunction), false, callback);
        } else if (scrollToPara->Contains("id") && !id.empty()) {
            result = controller->AnimateToTarget(id, duration, CreateCurve(timingFunction), false, callback);
        } else {
            LOGW("ComponentApiBridge::JsScrollTo param not valid.");
        }
        if (!result) {
            auto refContext = context.Upgrade();
            if (refContext) {
                refContext->SendCallbackMessageToFrontend(failId, std::string("\"fail\",null"));
                refContext->SendCallbackMessageToFrontend(completeId, std::string("\"complete\",null"));
            }
        }
    };

    auto delegate = instance->GetDelegate();
    if (!delegate) {
        LOGE("ComponentApiBridge::JsScrollTo delegate is null");
        return;
    }
    delegate->PostSyncTaskToPage(task);
}

} // namespace OHOS::Ace::Framework
