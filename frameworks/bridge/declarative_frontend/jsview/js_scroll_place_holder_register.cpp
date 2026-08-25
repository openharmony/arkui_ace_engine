/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_scroll_place_holder_register.h"

#include <cinttypes>

#include "base/log/log.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_manager.h"
#include "core/components_ng/manager/scroll_placeholder/scroll_placeholder_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"

namespace OHOS::Ace::Framework {

void JSScrollPlaceHolderRegister::Register(const JSCallbackInfo& info)
{
    CHECK_JAVASCRIPT_SCOPE_AND_RETURN;
    if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsObject()) {
        TAG_LOGW(AceLogTag::ACE_SCROLL,
            "ScrollPlaceHolderRegister.register expects (id: string, wrapBuilder)");
        return;
    }
    std::string id = info[0]->ToString();
    JSRef<JSObject> wrapBuilder = JSRef<JSObject>::Cast(info[1]);
    auto builderProp = wrapBuilder->GetProperty("builder");
    if (!builderProp->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_SCROLL,
            "ScrollPlaceHolderRegister.register: wrapBuilder without builder function, id=%{public}s", id.c_str());
        return;
    }
    auto context = NG::PipelineContext::GetCurrentContext();
    if (!context) {
        TAG_LOGW(AceLogTag::ACE_SCROLL, "ScrollPlaceHolderRegister.register: no pipeline context");
        return;
    }
    auto manager = context->GetScrollPlaceholderManager();
    if (!manager) {
        return;
    }
    auto thisObj = JSRef<JSObject>::Cast(wrapBuilder);
    auto builderFunc = JSRef<JSFunc>::Cast(builderProp);
    // Placeholder templates are immutable static subtrees: invoking the wrapped
    // builder pushes the subtree onto the view stack; Finish() detaches it as
    // the snapshot for later placeholder creation. Runs on the UI thread only.
    NG::ScrollPlaceHolderBuilder builder = [thisObj, builderFunc]() -> RefPtr<NG::UINode> {
        JAVASCRIPT_EXECUTION_SCOPE_STATIC
        NG::ScopedViewStackProcessor scopedViewStackProcessor;
        auto* viewStack = NG::ViewStackProcessor::GetInstance();
        JSRef<JSVal> params[1];
        builderFunc->Call(thisObj, 0, params);
        return viewStack->Finish();
    };
    auto generation = manager->RegisterTemplate(id, std::move(builder));
    TAG_LOGI(AceLogTag::ACE_SCROLL,
        "ScrollPlaceHolderRegister.register id=%{public}s gen=%{public}" PRIu64, id.c_str(), generation);
}

void JSScrollPlaceHolderRegister::JSBind(BindingTarget globalObj)
{
    JSClass<JSScrollPlaceHolderRegister>::Declare("ScrollPlaceHolderRegister");
    JSClass<JSScrollPlaceHolderRegister>::StaticMethod("register", &JSScrollPlaceHolderRegister::Register);
    JSClass<JSScrollPlaceHolderRegister>::Bind(globalObj);
}

} // namespace OHOS::Ace::Framework
