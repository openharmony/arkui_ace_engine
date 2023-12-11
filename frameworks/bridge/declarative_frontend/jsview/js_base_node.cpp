/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/js_base_node.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"

namespace OHOS::Ace::Framework {
namespace {
const char* DIRTY_FLAG[] = { "UPDATE_PROPERTY", "UPDATE_CONTENT" };
constexpr int32_t NUMBER_OF_PARAMETERS = 2;
}

void JSBaseNode::BuildNode(const JSCallbackInfo& info)
{
    if (info.Length() < NUMBER_OF_PARAMETERS || !info[0]->IsFunction() || !info[1]->IsObject()) {
        return;
    }
    auto builder = info[0];
    auto buildFunc = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(buildFunc);

    JSRef<JSVal> param = info[1];
    {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        NG::ViewStackProcessor::GetInstance()->SetIsBuilderNode(true);
        buildFunc->ExecuteJS(1, &param);
        viewNode_ = NG::ViewStackProcessor::GetInstance()->Finish();
    }
}

void JSBaseNode::ConstructorCallback(const JSCallbackInfo& info)
{
    auto instance = AceType::MakeRefPtr<JSBaseNode>();
    instance->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(instance));
}

void JSBaseNode::DestructorCallback(JSBaseNode* node)
{
    if (node != nullptr) {
        node->DecRefCount();
    }
}

void JSBaseNode::MarkDirty(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        return;
    }
    auto flag = info[0]->ToNumber<uint32_t>();
    LOGI("markDirty DirtyFlag.%{public}s", DIRTY_FLAG[flag]);
}

void JSBaseNode::FinishUpdateFunc(const JSCallbackInfo& info)
{
    NG::ViewStackProcessor::GetInstance()->FlushRerenderTask();
}

void JSBaseNode::JSBind(BindingTarget globalObj)
{
    JSClass<JSBaseNode>::Declare("__JSBaseNode__");

    JSClass<JSBaseNode>::CustomMethod("build", &JSBaseNode::BuildNode);
    JSClass<JSBaseNode>::CustomMethod("markDirty", &JSBaseNode::MarkDirty);
    JSClass<JSBaseNode>::CustomMethod("finishUpdateFunc", &JSBaseNode::FinishUpdateFunc);

    JSClass<JSBaseNode>::Bind(globalObj, JSBaseNode::ConstructorCallback, JSBaseNode::DestructorCallback);
}
} // namespace OHOS::Ace::Framework
