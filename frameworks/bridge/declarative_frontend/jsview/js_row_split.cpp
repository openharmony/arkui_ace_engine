/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_row_split.h"

#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSRowSplit::Create()
{
    LinearSplitModel::GetInstance()->Create(NG::SplitType::ROW_SPLIT);
}

void JSRowSplit::JsResizable(bool resizable)
{
    LinearSplitModel::GetInstance()->SetResizable(NG::SplitType::ROW_SPLIT, resizable);
}

void JSRowSplit::JsClip(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(true);
        return;
    }
    if (info[0]->IsObject()) {
        JSShapeAbstract* clipShape = JSRef<JSObject>::Cast(info[0])->Unwrap<JSShapeAbstract>();
        if (clipShape == nullptr) {
            return;
        }
        ViewAbstractModel::GetInstance()->SetClipShape(clipShape->GetBasicShape());
    } else if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}

void JSRowSplit::JSBind(BindingTarget globalObj)
{
    JSClass<JSRowSplit>::Declare("RowSplit");
    JSClass<JSRowSplit>::StaticMethod("create", &JSRowSplit::Create, MethodOptions::NONE);
    JSClass<JSRowSplit>::StaticMethod("resizeable", &JSRowSplit::JsResizable, MethodOptions::NONE);
    JSClass<JSRowSplit>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRowSplit>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRowSplit>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRowSplit>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRowSplit>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRowSplit>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRowSplit>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRowSplit>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRowSplit>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRowSplit>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSRowSplit>::StaticMethod("clip", &JSRowSplit::JsClip);
    JSClass<JSRowSplit>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
