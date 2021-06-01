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

#include "core/components/foreach/foreach_component.h"
#include "core/components/wrap/wrap_component.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_flex.h"
#ifdef USE_QUICKJS_ENGINE
#include "frameworks/bridge/js_frontend/engine/quickjs/qjs_utils.h"
#endif

namespace OHOS::Ace::Framework {

namespace {

WrapAlignment FlexAlignToWrapAlign(FlexAlign flexAlign)
{
    switch (flexAlign) {
        case FlexAlign::AUTO:
        case FlexAlign::FLEX_START:
            return WrapAlignment::START;
        case FlexAlign::CENTER:
            return WrapAlignment::CENTER;
        case FlexAlign::FLEX_END:
            return WrapAlignment::END;
        case FlexAlign::STRETCH:
            return WrapAlignment::STRETCH;
        case FlexAlign::BASELINE:
            return WrapAlignment::END; // TODO: No actual mapping
        case FlexAlign::SPACE_BETWEEN:
            return WrapAlignment::SPACE_BETWEEN;
        case FlexAlign::SPACE_AROUND:
            return WrapAlignment::SPACE_AROUND;
        default:
            return WrapAlignment::CENTER;
    };
    return WrapAlignment::CENTER;
}

RefPtr<OHOS::Ace::Component> CreateWrapComponent(std::list<RefPtr<OHOS::Ace::Component>> componentChildren,
    WrapDirection direction, double spacing, double contentSpacing, FlexAlign const& mainAlignment,
    FlexAlign const& crossAlignment, WrapAlignment const& alignContent, bool dialogStretch)
{
    LOGD("Create component: Wrap");

    RefPtr<OHOS::Ace::WrapComponent> component =
        AceType::MakeRefPtr<WrapComponent>(spacing, contentSpacing, componentChildren);

    component->SetDirection(direction);
    component->SetMainAlignment(FlexAlignToWrapAlign(mainAlignment));
    component->SetCrossAlignment(FlexAlignToWrapAlign(crossAlignment));
    component->SetAlignment(alignContent);
    component->SetDialogStretch(dialogStretch);

    return component;
}

} // anonymous namespace

#ifdef USE_V8_ENGINE
template<class T>
JSFlex<T>::JSFlex(const std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>> jsChildren)
#else
template<class T>
JSFlex<T>::JSFlex(const std::list<JSViewAbstract*>& children, std::list<JSValue> jsChildren)
#endif
    : JSContainerBase(children, jsChildren), mainAxisAlign_(FlexAlign::FLEX_START),
      crossAxisAlign_(FlexAlign::FLEX_START), mainAxisSize_(MainAxisSize::MAX)

{
    LOGD("Flex(children: [%lu])", children_.size());
};

template<class T>
JSFlex<T>::~JSFlex()
{
    LOGD("Destroy: JSFlex");
};

template<class T>
RefPtr<OHOS::Ace::Component> JSFlex<T>::CreateSpecializedComponent()
{
    LOGD("Create components for %d children of Flex", (int)children_.size());
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;

    for (auto jsViewChild : children_) {
        auto component = jsViewChild->CreateComponent();
        if (AceType::TypeName<ForEachComponent>() == AceType::TypeName(component)) {
            auto children = AceType::DynamicCast<ForEachComponent>(component)->GetChildren();
            for (auto childComponent : children) {
                componentChildren.emplace_back(childComponent);
            }
        } else {
            componentChildren.emplace_back(component);
        }
    }

    double spacing = 0.0;
    double contentSpacing = 0.0;
    bool dialogStretch = false;

    RefPtr<Component> component;
    if (wrap_) {
        WrapDirection direction = IsHorizontal() ? WrapDirection::HORIZONTAL : WrapDirection::VERTICAL;

        component = CreateWrapComponent(componentChildren, direction, spacing, contentSpacing, mainAxisAlign_,
            crossAxisAlign_, alignContent_, dialogStretch);
    } else {
        LOGD("Create component: Flex");
        auto flexComponent = ComponentForType(mainAxisAlign_, crossAxisAlign_, componentChildren);
        flexComponent->SetMainAxisSize(mainAxisSize_);
        component = flexComponent;
    }

    return component;
}

template<class T>
std::vector<RefPtr<OHOS::Ace::SingleChild>> JSFlex<T>::CreateInteractableComponents()
{
    return JSInteractableView::CreateComponents();
}

template<class T>
void JSFlex<T>::SetFillParent()
{
    mainAxisSize_ = MainAxisSize::MAX;
}

template<class T>
void JSFlex<T>::SetWrapContent()
{
    mainAxisSize_ = MainAxisSize::MIN;
}

template<class T>
void JSFlex<T>::SetJustifyContent(int value)
{
    if ((value == static_cast<int>(FlexAlign::FLEX_START)) || (value == static_cast<int>(FlexAlign::FLEX_END)) ||
        (value == static_cast<int>(FlexAlign::CENTER)) || (value == static_cast<int>(FlexAlign::SPACE_AROUND)) ||
        (value == static_cast<int>(FlexAlign::SPACE_BETWEEN))) {
        mainAxisAlign_ = (FlexAlign)value;
    } else {
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
        LOGE("invalid value for justifyContent");
    }
}

template<class T>
void JSFlex<T>::SetAlignItems(int value)
{
    if ((value == static_cast<int>(FlexAlign::FLEX_START)) || (value == static_cast<int>(FlexAlign::FLEX_END)) ||
        (value == static_cast<int>(FlexAlign::CENTER)) || (value == static_cast<int>(FlexAlign::STRETCH))) {
        crossAxisAlign_ = (FlexAlign)value;
    } else {
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
        LOGE("invalid value for justifyContent");
    }
}

template<class T>
void JSFlex<T>::SetAlignContent(int value)
{
    if ((value == static_cast<int>(WrapAlignment::START)) || (value == static_cast<int>(WrapAlignment::CENTER)) ||
        (value == static_cast<int>(WrapAlignment::END)) || (value == static_cast<int>(WrapAlignment::SPACE_AROUND)) ||
        (value == static_cast<int>(WrapAlignment::SPACE_BETWEEN)) ||
        (value == static_cast<int>(WrapAlignment::STRETCH))) {
        alignContent_ = (WrapAlignment)value;
    } else {
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
        LOGE("invalid value for justifyContent");
    }
}

template<class T>
void JSFlex<T>::SetWrap(bool value)
{
    wrap_ = value;
}

#ifdef USE_QUICKJS_ENGINE

template<class T>
void JSFlex<T>::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSFlex => MarkGC: start");
    JSContainerBase::MarkGC(rt, markFunc);
    LOGD("JSFlex => MarkGC: end");
}

template<class T>
void JSFlex<T>::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSFlex => release: start");
    JSContainerBase::ReleaseRT(rt);
    LOGD("JSFlex => release: end");
}

template<class T>
template<typename U>
JSValue JSFlex<T>::JsFlexConstructorInternal(JSContext* ctx, JSValueConst new_target, int argc, JSValueConst* argv,
    std::function<U*(std::list<JSViewAbstract*>, std::list<JSValue>)> flex)
{
    ACE_SCOPED_TRACE("JSFlex::JsFlexConstructorInternal");
    QJSContext::Scope scope(ctx);

    U* value = nullptr;

    auto [children, jsChildren] = JsChildrenFromArgs(ctx, argc, argv);

    LOGD("JsFlexConstructorInternal -> Children created");

    value = flex(children, jsChildren);
    return Wrap<U>(new_target, value);
}
#endif // USE_QUICKJS_ENGINE

#ifdef USE_V8_ENGINE

template<class T>
void JSFlex<T>::V8FlexConstructorInternal(const v8::FunctionCallbackInfo<v8::Value>& args,
    std::list<JSViewAbstract*>& children,
    std::list<v8::Persistent<v8::Object, v8::CopyablePersistentTraits<v8::Object>>>& jsChildren)
{
    LOGD("V8FlexConstructorInternal");
    V8ChildrenFromArgs(args, children, jsChildren);
}
#endif

}; // namespace OHOS::Ace::Framework
