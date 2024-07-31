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
#include "bridge/declarative_frontend/jsview/js_mock.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_bindings.h"

namespace OHOS::Ace::Framework {
void JSMockBaseNode::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockBaseNode>::Declare("__JSBaseNode__");

    JSClass<JSMockBaseNode>::CustomMethod("create", &JSMockBaseNode::Create);
    JSClass<JSMockBaseNode>::CustomMethod("finishUpdateFunc", &JSMockBaseNode::FinishUpdateFunc);
    JSClass<JSMockBaseNode>::CustomMethod("postTouchEvent", &JSMockBaseNode::PostTouchEvent);
    JSClass<JSMockBaseNode>::CustomMethod("disposeNode", &JSMockBaseNode::Dispose);
    JSClass<JSMockBaseNode>::CustomMethod("updateStart", &JSMockBaseNode::UpdateStart);
    JSClass<JSMockBaseNode>::CustomMethod("updateEnd", &JSMockBaseNode::UpdateEnd);

    JSClass<JSMockBaseNode>::Bind(globalObj, JSMockBaseNode::ConstructorCallback, JSMockBaseNode::DestructorCallback);
}

void JSMockViewPU::JSBind(BindingTarget globalObj, std::string name)
{
    JSClass<JSMockViewPU>::Declare(name.c_str());

    JSClass<JSMockViewPU>::CustomMethod("id__", &JSMockViewPU::Id);
    JSClass<JSMockViewPU>::CustomMethod("updateStateVars", &JSMockViewPU::UpdateStateVars);
    JSClass<JSMockViewPU>::CustomMethod("aboutToReuseInternal", &JSMockViewPU::AboutToReuseInternal);
    JSClass<JSMockViewPU>::CustomMethod("aboutToRecycleInternal", &JSMockViewPU::AboutToRecycleInternal);
    JSClass<JSMockViewPU>::CustomMethod("updateDirtyElements", &JSMockViewPU::UpdateDirtyElements);

    JSClass<JSMockViewPU>::Bind(globalObj);
}

void JSMockScopeUtil::JSBind(BindingTarget globalObj)
{
    JSClass<JSMockScopeUtil>::Declare("__JSScopeUtil__");
    JSClass<JSMockScopeUtil>::StaticMethod("syncInstanceId", &JSMockScopeUtil::SyncInstanceId);
    JSClass<JSMockScopeUtil>::StaticMethod("restoreInstanceId", &JSMockScopeUtil::RestoreInstanceId);

    JSClass<JSMockScopeUtil>::Bind(globalObj);
}

void MockCustomDialogController::JSBind(BindingTarget globalObj)
{
    JSClass<MockCustomDialogController>::Declare("CustomDialogController");

    JSClass<MockCustomDialogController>::CustomMethod("open", &MockCustomDialogController::Open);
    JSClass<MockCustomDialogController>::CustomMethod("close", &MockCustomDialogController::Close);

    JSClass<JSMockBaseNode>::Bind(globalObj);
}

void JSMock::JSBind(BindingTarget globalObj)
{
    JSMockBaseNode::JSBind(globalObj);
    JSMockViewPU::JSBind(globalObj, "ViewPU");
    JSMockViewPU::JSBind(globalObj, "PUV2ViewBase");
    JSMockScopeUtil::JSBind(globalObj);
    MockCustomDialogController::JSBind(globalObj);
}
} // namespace OHOS::Ace::Framework
