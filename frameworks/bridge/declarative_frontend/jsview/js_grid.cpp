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

#include "frameworks/bridge/declarative_frontend/jsview/js_grid.h"

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/core/components/foreach/foreach_component.h"

namespace OHOS::Ace::Framework {

#ifdef USE_QUICKJS_ENGINE
JSGrid::JSGrid(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("Grid(children: [%lu])", children_.size());
}
#else
JSGrid::JSGrid(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
    : JSContainerBase(children, jsChildren)
{
    LOGD("JSGrid(children: [%lu])", children_.size());
}
#endif

JSGrid::~JSGrid()
{
    LOGD("Destroy: JSGrid");
};

RefPtr<OHOS::Ace::Component> JSGrid::CreateSpecializedComponent()
{
    LOGD("Create component: Grid");
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    for (const auto& jsViewChild : children_) {
        if (!jsViewChild) {
            continue;
        }
        auto component = jsViewChild->CreateComponent();
        if (AceType::TypeName<ForEachComponent>() == AceType::TypeName(component)) {
            auto children = AceType::DynamicCast<ForEachComponent>(component)->GetChildren();
            for (const auto& childComponent : children) {
                componentChildren.emplace_back(childComponent);
            }
        } else {
            componentChildren.emplace_back(component);
        }
    }

    RefPtr<OHOS::Ace::GridLayoutComponent> gridComponent = AceType::MakeRefPtr<GridLayoutComponent>(componentChildren);
    gridComponent->SetColumnsArgs(columnsTemplate_);
    gridComponent->SetRowsArgs(rowsTemplate_);
    gridComponent->SetColumnGap(columnsGap_);
    gridComponent->SetRowGap(rowsGap_);

    return std::move(gridComponent);
}

std::vector<RefPtr<OHOS::Ace::SingleChild>> JSGrid::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

void JSGrid::SetColumnsTemplate(std::string value)
{
    columnsTemplate_ = value;
}

void JSGrid::SetRowsTemplate(std::string value)
{
    rowsTemplate_ = value;
}

void JSGrid::SetColumnsGap(double value)
{
    columnsGap_ = value;
}

void JSGrid::SetRowsGap(double value)
{
    rowsGap_ = value;
}

#ifdef USE_QUICKJS_ENGINE
void JSGrid::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSGrid => MarkGC: Mark value for GC start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSGrid => MarkGC: Mark value for GC end");
}

void JSGrid::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSGrid => release start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSGrid => release end");
}

// STATIC qjs_class_bindings
JSValue JSGrid::ConstructorCallback(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv)
{
    ACE_SCOPED_TRACE("JSGrid::ConstructorCallback");
    QJSContext::Scope scope(ctx);
    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);
    JSGrid* grid = new JSGrid(children, jsChildren);
    return Wrap<JSGrid>(new_target, grid);
}

void JSGrid::QjsDestructor(JSRuntime* rt, JSGrid* view)
{
    LOGD("JSGrid(QjsDestructor) start");

    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    view = nullptr;
    LOGD("JSGrid(QjsDestructor) end");
}

void JSGrid::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSGrid(QjsGcMark) start");

    JSGrid* grid = Unwrap<JSGrid>(val);
    if (!grid) {
        return;
    }

    grid->MarkGC(rt, markFunc);
    LOGD("JSGrid(QjsGcMark) end");
}

#endif // USE_QUICKJS_ENGINE

void JSGrid::JSBind(BindingTarget globalObj)
{
    LOGD("JSGrid:V8Bind");
    JSClass<JSGrid>::Declare("Grid");
    JSClass<JSGrid>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSGrid>::Method("columnsTemplate", &JSGrid::SetColumnsTemplate, opt);
    JSClass<JSGrid>::Method("rowsTemplate", &JSGrid::SetRowsTemplate, opt);
    JSClass<JSGrid>::Method("columnsGap", &JSGrid::SetColumnsGap, opt);
    JSClass<JSGrid>::Method("rowsGap", &JSGrid::SetRowsGap, opt);
    JSClass<JSGrid>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSGrid>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSGrid>::Bind(globalObj, ConstructorCallback);
}

#ifdef USE_V8_ENGINE
void JSGrid::ConstructorCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    LOGD("JSGrid:ConstructorCallback");
    std::list<JSViewAbstract*> children;
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren;
    V8ChildrenFromArgs(args, children, jsChildren);
    auto instance = V8Object<JSGrid>::New(args.This(), children, jsChildren);
    args.GetReturnValue().Set(instance->Get());
}
#endif // USE_V8_ENGINE

} // namespace OHOS::Ace::Framework
