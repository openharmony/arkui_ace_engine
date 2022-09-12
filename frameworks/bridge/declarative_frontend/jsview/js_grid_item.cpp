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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid_item.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/grid/grid_item_view.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_mouse_function.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/pipeline/base/element_register.h"

namespace OHOS::Ace::Framework {

void JSGridItem::Create(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        if (Container::IsCurrentUsePartialUpdate()) {
            CreateForNGPartialUpdate(args);
            return;
        }
        NG::GridItemView::Create();
        return;
    }
    auto container = Container::Current();
    if (!container) {
        LOGE("fail to get container");
        return;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        LOGE("fail to get context");
        return;
    }

    auto itemComponent = AceType::MakeRefPtr<GridLayoutItemComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(itemComponent);
    ViewStackProcessor::GetInstance()->Push(itemComponent);

    if (!Container::IsCurrentUsePartialUpdate()) {
        return;
    }

    // Partial update code path
    if (args.Length() < 2 || !args[0]->IsFunction()) {
        LOGE("Expected deep render function parameter");
        return;
    }
    RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));

    if (!args[1]->IsBoolean()) {
        LOGE("Expected isLazy parameter");
        return;
    }
    const bool isLazy = args[1]->ToBoolean();

    DeepRenderFunc gridItemDeepRenderFunc = [execCtx = args.GetExecutionContext(),
                                                jsDeepRenderFunc = std::move(jsDeepRender),
                                                elmtId = itemComponent->GetElementId()]() -> RefPtr<Component> {
        ACE_SCOPED_TRACE("JSGridItem::ExecuteDeepRender");

        LOGD("GridItem elmtId %{public}d DeepRender JS function execution start ....", elmtId);
        ACE_DCHECK(componentsStack_.empty());

        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        JSRef<JSVal> jsParams[2];
        jsParams[0] = JSRef<JSVal>::Make(ToJSValue(elmtId));
        jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
        jsDeepRenderFunc->ExecuteJS(2, jsParams);
        RefPtr<Component> component = ViewStackProcessor::GetInstance()->Finish();
        ACE_DCHECK(AceType::DynamicCast<V2::ListItemComponent>(component) != nullptr);
        LOGD("GridItem elmtId %{public}d DeepRender JS function execution - done ", elmtId);
        return component;
    }; // gridItemDeepRenderFunc lambda

    itemComponent->SetDeepRenderFunc(gridItemDeepRenderFunc);
    itemComponent->SetIsLazyCreating(isLazy);
}

void JSGridItem::CreateForNGPartialUpdate(const JSCallbackInfo& args)
{
    if (args.Length() < 2 || !args[0]->IsFunction()) {
        LOGE("Expected deep render function parameter");
        return;
    }
    if (!args[1]->IsBoolean()) {
        LOGE("Expected isLazy parameter");
        return;
    }
    const bool isLazy = args[1]->ToBoolean();
    if (!isLazy) {
        NG::GridItemView::Create();
    } else {
        RefPtr<JsFunction> jsDeepRender = AceType::MakeRefPtr<JsFunction>(args.This(), JSRef<JSFunc>::Cast(args[0]));
        auto gridItemDeepRenderFunc = [execCtx = args.GetExecutionContext(),
                                          jsDeepRenderFunc = std::move(jsDeepRender)](int32_t nodeId) {
            LOGD("GridItem elmtId %{public}d DeepRender JS function execution start ....", nodeId);
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            JSRef<JSVal> jsParams[2];
            jsParams[0] = JSRef<JSVal>::Make(ToJSValue(nodeId));
            jsParams[1] = JSRef<JSVal>::Make(ToJSValue(true));
            jsDeepRenderFunc->ExecuteJS(2, jsParams);
        }; // gridItemDeepRenderFunc lambda
        NG::GridItemView::Create(std::move(gridItemDeepRenderFunc));
    }
    args.ReturnSelf();
}

void JSGridItem::SetColumnStart(int32_t columnStart)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        auto columnStartValue = columnStart < 0 ? 0 : columnStart;
        gridItem->SetColumnIndex(columnStartValue);
    }
}

void JSGridItem::SetColumnEnd(int32_t columnEnd)
{
    // column end must be set after start. loader needs to make the method in order.
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        auto columnEndValue = columnEnd < 0 ? 0 : columnEnd;
        gridItem->SetColumnSpan(columnEndValue - gridItem->GetColumnIndex() + 1);
    }
}

void JSGridItem::SetRowStart(int32_t rowStart)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        auto rowStartValue = rowStart < 0 ? 0 : rowStart;
        gridItem->SetRowIndex(rowStartValue);
    }
}

void JSGridItem::SetRowEnd(int32_t rowEnd)
{
    // row end must be set after start. loader needs to make the method in order.
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        auto rowEndValue = rowEnd < 0 ? 0 : rowEnd;
        gridItem->SetRowSpan(rowEndValue - gridItem->GetRowIndex() + 1);
    }
}

void JSGridItem::ForceRebuild(bool forceRebuild)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        gridItem->SetForceRebuild(forceRebuild);
    }
}

void JSGridItem::JSBind(BindingTarget globalObj)
{
    LOGD("GridItem:JSBind");
    JSClass<JSGridItem>::Declare("GridItem");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSGridItem>::StaticMethod("create", &JSGridItem::Create, opt);
    JSClass<JSGridItem>::StaticMethod("columnStart", &JSGridItem::SetColumnStart, opt);
    JSClass<JSGridItem>::StaticMethod("columnEnd", &JSGridItem::SetColumnEnd, opt);
    JSClass<JSGridItem>::StaticMethod("rowStart", &JSGridItem::SetRowStart, opt);
    JSClass<JSGridItem>::StaticMethod("rowEnd", &JSGridItem::SetRowEnd, opt);
    JSClass<JSGridItem>::StaticMethod("forceRebuild", &JSGridItem::ForceRebuild, opt);
    JSClass<JSGridItem>::StaticMethod("selectable", &JSGridItem::SetSelectable, opt);
    JSClass<JSGridItem>::StaticMethod("onSelect", &JSGridItem::SelectCallback);
    JSClass<JSGridItem>::StaticMethod("width", &JSGridItem::SetGridItemWidth);
    JSClass<JSGridItem>::StaticMethod("height", &JSGridItem::SetGridItemHeight);
    JSClass<JSGridItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGridItem>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSGridItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSGridItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGridItem>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSGridItem>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSGridItem>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSGridItem>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSGridItem>::Inherit<JSContainerBase>();
    JSClass<JSGridItem>::Inherit<JSViewAbstract>();
    JSClass<JSGridItem>::Bind<>(globalObj);
}

void JSGridItem::SetSelectable(bool selectable)
{
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (gridItem) {
        gridItem->SetSelectable(selectable);
    }
}

void JSGridItem::SelectCallback(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        LOGE("fail to bind onSelect event due to info is not function");
        return;
    }

    RefPtr<JsMouseFunction> jsOnSelectFunc = AceType::MakeRefPtr<JsMouseFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onSelectId = [execCtx = args.GetExecutionContext(), func = std::move(jsOnSelectFunc)](bool isSelected) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->SelectExecute(isSelected);
    };
    auto gridItem =
        AceType::DynamicCast<GridLayoutItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!gridItem) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<GridLayoutItemComponent>());
        return;
    }
    gridItem->SetOnSelectId(onSelectId);
}

} // namespace OHOS::Ace::Framework
