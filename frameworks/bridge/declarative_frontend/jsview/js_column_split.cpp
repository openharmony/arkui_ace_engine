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

#include "frameworks/bridge/declarative_frontend/jsview/js_column_split.h"

#include "bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_linear_split.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSColumnSplit::Create()
{
    LinearSplitModel::GetInstance()->Create(NG::SplitType::COLUMN_SPLIT);
}

void JSColumnSplit::JsResizable(bool resizable)
{
    LinearSplitModel::GetInstance()->SetResizable(NG::SplitType::COLUMN_SPLIT, resizable);
}

void JSColumnSplit::JsDivider(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    NG::ItemDivider divider;
    RefPtr<ResourceObject> startResObj;
    RefPtr<ResourceObject> endResObj;
    ConvertFromJSValue(obj->GetProperty("startMargin"), divider.startMargin, startResObj);
    ConvertFromJSValue(obj->GetProperty("endMargin"), divider.endMargin, endResObj);
    if (SystemProperties::ConfigChangePerform() && startResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ItemDivider& divider) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            divider.startMargin = result;
        };
        divider.AddResource("ColumnSplit.divider.startMargin", startResObj, std::move(updateFunc));
    }
    if (SystemProperties::ConfigChangePerform() && endResObj) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::ItemDivider& divider) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVp(resObj, result);
            divider.endMargin = result;
        };
        divider.AddResource("ColumnSplit.divider.endMargin", endResObj, std::move(updateFunc));
    }
    LinearSplitModel::GetInstance()->SetDivider(NG::SplitType::COLUMN_SPLIT, divider);

    args.ReturnSelf();
}

void JSColumnSplit::JsClip(const JSCallbackInfo& info)
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

void JSColumnSplit::JSBind(BindingTarget globalObj)
{
    JSClass<JSColumnSplit>::Declare("ColumnSplit");
    JSClass<JSColumnSplit>::StaticMethod("create", &JSColumnSplit::Create, MethodOptions::NONE);
    JSClass<JSColumnSplit>::StaticMethod("resizeable", &JSColumnSplit::JsResizable, MethodOptions::NONE);
    JSClass<JSColumnSplit>::StaticMethod("divider", &JSColumnSplit::JsDivider, MethodOptions::NONE);
    JSClass<JSColumnSplit>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSColumnSplit>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSColumnSplit>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSColumnSplit>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSColumnSplit>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSColumnSplit>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSColumnSplit>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSColumnSplit>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSColumnSplit>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSColumnSplit>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSColumnSplit>::StaticMethod("clip", &JSColumnSplit::JsClip);
    JSClass<JSColumnSplit>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
