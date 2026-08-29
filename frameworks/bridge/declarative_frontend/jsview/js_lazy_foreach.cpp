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

#include "frameworks/bridge/declarative_frontend/jsview/js_lazy_foreach.h"

#include <functional>
#include <set>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_lazy_foreach_theme.h"
#include "bridge/declarative_frontend/engine/functions/js_callback_state.h"
#include "bridge/declarative_frontend/engine/js_object_template.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_actuator.h"
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_builder.h"
#ifndef NG_BUILD
#include "bridge/declarative_frontend/jsview/js_lazy_foreach_component.h"
#endif
#include "bridge/declarative_frontend/jsview/js_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/lazy_for_each_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_model_ng.h"

namespace OHOS::Ace {
LazyForEachModel* LazyForEachModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::LazyForEachModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::LazyForEachModelNG instance;
        return &instance;
    } else {
        static Framework::LazyForEachModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSDataChangeListener::JSBind(BindingTarget globalObj)
{
    JSClass<JSDataChangeListener>::Declare("__ohos_ace_inner_JSDataChangeListener__");
    // API7 onEditChanged deprecated
    JSClass<JSDataChangeListener>::CustomMethod("onDataReloaded", &JSDataChangeListener::OnDataReloaded);
    JSClass<JSDataChangeListener>::CustomMethod("onDataReload", &JSDataChangeListener::OnDataReloaded);
    // API7 onDataAdded deprecated
    JSClass<JSDataChangeListener>::CustomMethod("onDataAdded", &JSDataChangeListener::OnDataAdded);
    JSClass<JSDataChangeListener>::CustomMethod("onDataAdd", &JSDataChangeListener::OnDataAdded);
    // API7 onDataDeleted deprecated
    JSClass<JSDataChangeListener>::CustomMethod("onDataDeleted", &JSDataChangeListener::OnDataDeleted);
    JSClass<JSDataChangeListener>::CustomMethod("onDataDelete", &JSDataChangeListener::OnDataDeleted);
    // API7 onDataChanged deprecated
    JSClass<JSDataChangeListener>::CustomMethod("onDataChanged", &JSDataChangeListener::OnDataChanged);
    JSClass<JSDataChangeListener>::CustomMethod("onDataChange", &JSDataChangeListener::OnDataChanged);
    // API7 onDataMoved deprecated
    JSClass<JSDataChangeListener>::CustomMethod("onDataMoved", &JSDataChangeListener::OnDataMoved);
    JSClass<JSDataChangeListener>::CustomMethod("onDataMove", &JSDataChangeListener::OnDataMoved);
    // temporary interface
    JSClass<JSDataChangeListener>::CustomMethod("onDataBulkAdded", &JSDataChangeListener::OnDataBulkAdded);
    JSClass<JSDataChangeListener>::CustomMethod("onDataBulkAdd", &JSDataChangeListener::OnDataBulkAdded);
    JSClass<JSDataChangeListener>::CustomMethod("onDataBulkDeleted", &JSDataChangeListener::OnDataBulkDeleted);
    JSClass<JSDataChangeListener>::CustomMethod("onDataBulkDelete", &JSDataChangeListener::OnDataBulkDeleted);
    // API12 onDatasetChange
    JSClass<JSDataChangeListener>::CustomMethod("onDatasetChange", &JSDataChangeListener::OnDatasetChange);
    JSClass<JSDataChangeListener>::Bind(
        globalObj, &JSDataChangeListener::Constructor, &JSDataChangeListener::Destructor);
}

RefPtr<JSLazyForEachActuator> CreateActuator(const std::string& viewId)
{
#ifdef NG_BUILD
    return AceType::MakeRefPtr<JSLazyForEachBuilder>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        return AceType::MakeRefPtr<JSLazyForEachBuilder>();
    } else {
        return AceType::MakeRefPtr<JSLazyForEachComponent>(viewId);
    }
#endif
}

namespace {

// Strongly typed view of the create() arguments; optional members are undefined when absent.
struct LazyForEachCreateParams {
    JSRef<JSVal> viewId;
    JSRef<JSObject> parentView;
    JSRef<JSObject> dataSource;
    JSRef<JSFunc> itemGenerator;
    JSRef<JSVal> keyGenerator;
    JSRef<JSVal> options;
    bool updateChangedNode = false;
};

// LazyForEach.create() positional arguments as invoked by the compiled ArkTS glue:
//   0: viewId (string, required)
//   1: parentView (object, required)
//   2: dataSource (object, required)
//   3: itemGenerator (function, required)
//   4: keyGenerator (function, optional)
//   5: options (object, or legacy updateChangedNode boolean, optional)
//   6: updateChangedNode (boolean, optional)
bool ParseCreateParams(const JSCallbackInfo& info, LazyForEachCreateParams& params)
{
    if (info.Length() < 4) {
        return false;
    }
    if (!info[0]->IsString()) {
        return false;
    }
    if (!info[1]->IsObject()) {
        return false;
    }
    if (!info[2]->IsObject()) {
        return false;
    }
    if (!info[3]->IsFunction()) {
        return false;
    }
    if (info.Length() > 4 && !(info[4]->IsFunction() || info[4]->IsUndefined())) {
        return false;
    }
    if (info.Length() > 5 && !(info[5]->IsObject() || info[5]->IsBoolean())) {
        return false;
    }
    if (info.Length() > 6 && !info[6]->IsBoolean()) {
        return false;
    }

    params.viewId = info[0];
    params.parentView = JSRef<JSObject>::Cast(info[1]);
    params.dataSource = JSRef<JSObject>::Cast(info[2]);
    params.itemGenerator = JSRef<JSFunc>::Cast(info[3]);
    // Out-of-range operator[] yields undefined, so absent optionals read back as undefined.
    params.keyGenerator = info[4];
    params.options = info[5];

    // The options slot historically also carries the updateChangedNode boolean; the
    // trailing updateChangedNode argument wins when both are supplied.
    if (info[5]->IsBoolean()) {
        params.updateChangedNode = info[5]->ToBoolean();
    }
    if (info.Length() > 6) {
        params.updateChangedNode = info[6]->ToBoolean();
    }
    return true;
}

// Resolves a strategy option expressed either as its SDK numeric enum value or as the
// enum member name; table entries carry both spellings. Numeric strings such as "1"
// are accepted as well because they parse as numbers first.
template<typename T, size_t N>
T ParseEnumValue(const JSRef<JSVal>& value, const std::pair<const char*, T> (&table)[N], T defaultValue)
{
    std::string literal;
    int32_t number = 0;
    if (ConvertFromJSValue(value, number)) {
        literal = std::to_string(number);
    } else if (!ConvertFromJSValue(value, literal)) {
        return defaultValue;
    }
    for (const auto& entry : table) {
        if (literal == entry.first) {
            return entry.second;
        }
    }
    return defaultValue;
}

LazyForEachReleaseStrategy ParseReleaseStrategy(const JSRef<JSVal>& value)
{
    static constexpr std::pair<const char*, LazyForEachReleaseStrategy> TABLE[] = {
        { "0", LazyForEachReleaseStrategy::BATCH },
        { "BATCH", LazyForEachReleaseStrategy::BATCH },
        { "1", LazyForEachReleaseStrategy::PROGRESSIVE },
        { "PROGRESSIVE", LazyForEachReleaseStrategy::PROGRESSIVE },
    };
    return ParseEnumValue(value, TABLE, LazyForEachReleaseStrategy::BATCH);
}

LazyForEachCustomComponentFreezeMode ParseCustomComponentFreezeMode(const JSRef<JSVal>& value)
{
    static constexpr std::pair<const char*, LazyForEachCustomComponentFreezeMode> TABLE[] = {
        { "0", LazyForEachCustomComponentFreezeMode::AUTO },
        { "AUTO", LazyForEachCustomComponentFreezeMode::AUTO },
        { "1", LazyForEachCustomComponentFreezeMode::DISABLED },
        { "DISABLED", LazyForEachCustomComponentFreezeMode::DISABLED },
        { "2", LazyForEachCustomComponentFreezeMode::ENABLED },
        { "ENABLED", LazyForEachCustomComponentFreezeMode::ENABLED },
    };
    return ParseEnumValue(value, TABLE, LazyForEachCustomComponentFreezeMode::AUTO);
}

LazyForEachMemOptStrategy ParseMemOptStrategy(const JSRef<JSVal>& value)
{
    // Unlike the other options, an absent value keeps the three-state UNDEFINED marker
    // so downstream code can tell "not configured" apart from an explicit DEFAULT.
    if (value->IsUndefined() || value->IsNull()) {
        return LazyForEachMemOptStrategy::UNDEFINED;
    }
    static constexpr std::pair<const char*, LazyForEachMemOptStrategy> TABLE[] = {
        { "0", LazyForEachMemOptStrategy::DEFAULT },
        { "DEFAULT", LazyForEachMemOptStrategy::DEFAULT },
        { "1", LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION },
        { "ENABLE_AUTO_CACHE_OPTIMIZATION", LazyForEachMemOptStrategy::ENABLE_AUTO_CACHE_OPTIMIZATION },
    };
    return ParseEnumValue(value, TABLE, LazyForEachMemOptStrategy::DEFAULT);
}

LazyForEachOptions ParseOptions(const JSRef<JSVal>& optionsVal)
{
    LazyForEachOptions options;
    if (!optionsVal->IsObject()) {
        return options;
    }
    JSRef<JSObject> optionsObj = JSRef<JSObject>::Cast(optionsVal);
    options.enableCustomComponentFreeze =
        ParseCustomComponentFreezeMode(optionsObj->GetProperty("customComponentFreezeMode"));
    options.releaseStrategy = ParseReleaseStrategy(optionsObj->GetProperty("releaseStrategy"));
    options.memOptStrategy = ParseMemOptStrategy(optionsObj->GetProperty("memoryOptimizationStrategy"));
    return options;
}

} // namespace

namespace {
void CallJsFuncWithIndex(const JSRef<JSFunc>& func, int32_t index)
{
    auto params = ConvertToJSValues(index);
    func->Call(JSRef<JSObject>(), params.size(), params.data());
}

void CallJsFuncWithFromTo(const JSRef<JSFunc>& func, int32_t from, int32_t to)
{
    auto params = ConvertToJSValues(from, to);
    func->Call(JSRef<JSObject>(), params.size(), params.data());
}
} // namespace

void JSLazyForEach::JSBind(BindingTarget globalObj)
{
    JSClass<JSLazyForEach>::Declare("LazyForEach");
    JSClass<JSLazyForEach>::StaticMethod("create", &JSLazyForEach::Create);
    JSClass<JSLazyForEach>::StaticMethod("pop", &JSLazyForEach::Pop);
    JSClass<JSLazyForEach>::StaticMethod("onMove", &JSLazyForEach::OnMove);
    JSClass<JSLazyForEach>::Bind(globalObj);

    JSDataChangeListener::JSBind(globalObj);
}

void JSLazyForEach::Create(const JSCallbackInfo& info)
{
    LazyForEachCreateParams params;
    if (!ParseCreateParams(info, params)) {
        TAG_LOGW(AceLogTag::ACE_LAZY_FOREACH, "Invalid arguments for LazyForEach");
        return;
    }

    std::string viewId = ViewStackModel::GetInstance()->ProcessViewId(params.viewId->ToString());
    JSRef<JSObject> parentViewObj = params.parentView;

    // LazyForEach is not in observeComponentCreation, mark isDeleting_ here
    JSRef<JSVal> isDeleting = parentViewObj->GetProperty("isDeleting_");
    if (isDeleting->IsBoolean() && isDeleting->ToBoolean()) {
        return;
    }

    JSLazyForEachTheme::ObtainItemGeneratorForThemeSupport(info.GetVm(), params.itemGenerator);

    ItemKeyGenerator keyGenFunc;
    if (params.keyGenerator->IsFunction()) {
        keyGenFunc = [viewId, keyGenerator = JSRef<JSFunc>::Cast(params.keyGenerator)](
                         const JSRef<JSVal>& jsVal, size_t index) {
            JSRef<JSVal> args[] = { jsVal, JSRef<JSVal>::Make(ToJSValue(index)) };
            auto key = keyGenerator->Call(JSRef<JSObject>(), ArraySize(args), args);
            return viewId + "-" + (key->IsString() || key->IsNumber() ? key->ToString() : std::to_string(index));
        };
    } else {
        keyGenFunc = [viewId](const JSRef<JSVal>&, size_t index) { return viewId + "-" + std::to_string(index); };
    }

    const auto& actuator = CreateActuator(viewId);
    actuator->SetJSExecutionContext(info.GetExecutionContext());
    actuator->SetParentViewObj(parentViewObj);
    actuator->SetDataSourceObj(params.dataSource);
    actuator->SetItemGenerator(params.itemGenerator, std::move(keyGenFunc));
    actuator->SetUpdateChangedNodeFlag(params.updateChangedNode);
    actuator->SetOptions(ParseOptions(params.options));

    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        auto createFunc = [actuator]() {
            LazyForEachModel::GetInstance()->Create(actuator);
        };
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSLazyForEach][create]", createFunc);
    }
    LazyForEachModel::GetInstance()->Create(actuator);
}

void JSLazyForEach::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSLazyForEach][pop]", &JSLazyForEach::Pop);
    }
    auto* stack = NG::ViewStackProcessor::GetInstance();
    if (stack->GetMainFrameNode() && stack->GetMainFrameNode()->GetTag() == V2::TABS_ETS_TAG) {
        return;
    }
    ViewStackModel::GetInstance()->PopContainer();
}

void JSLazyForEach::OnMove(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto context = info.GetExecutionContext();
        auto onMove = JsCallbackWithoutNode<void(int32_t, int32_t)>(
            context, JSRef<JSFunc>::Cast(info[0]), &CallJsFuncWithFromTo);
        LazyForEachModel::GetInstance()->OnMove(std::move(onMove));
        if ((info.Length() > 1) && info[1]->IsObject()) {
            JsParseItemDragEventHandler(context, info[1]);
        } else {
            LazyForEachModel::GetInstance()->SetItemDragHandler(nullptr, nullptr, nullptr, nullptr);
        }
    } else {
        LazyForEachModel::GetInstance()->OnMove(nullptr);
        LazyForEachModel::GetInstance()->SetItemDragHandler(nullptr, nullptr, nullptr, nullptr);
    }
}

// NOTE: this function and its CallJsFuncWithIndex/CallJsFuncWithFromTo helpers are duplicated
// verbatim in js_foreach.cpp, js_repeat.cpp and js_repeat_virtual_scroll_2.cpp (the latter with
// an extra repeatElmtId parameter). Any change here must be mirrored there; consolidating them
// into js_view_common_def.h is the tracked follow-up.
void JSLazyForEach::JsParseItemDragEventHandler(
    const JsiExecutionContext& context, const JSRef<JSObject>& itemDragEventObj)
{
    auto onLongPress = itemDragEventObj->GetProperty("onLongPress");
    std::function<void(int32_t)> onLongPressCallback;
    if (onLongPress->IsFunction()) {
        onLongPressCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onLongPress), &CallJsFuncWithIndex);
    }

    auto onDragStart = itemDragEventObj->GetProperty("onDragStart");
    std::function<void(int32_t)> onDragStartCallback;
    if (onDragStart->IsFunction()) {
        onDragStartCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onDragStart), &CallJsFuncWithIndex);
    }

    auto onMoveThrough = itemDragEventObj->GetProperty("onMoveThrough");
    std::function<void(int32_t, int32_t)> onMoveThroughCallback;
    if (onMoveThrough->IsFunction()) {
        onMoveThroughCallback = JsCallbackWithoutNode<void(int32_t, int32_t)>(
            context, JSRef<JSFunc>::Cast(onMoveThrough), &CallJsFuncWithFromTo);
    }

    auto onDrop = itemDragEventObj->GetProperty("onDrop");
    std::function<void(int32_t)> onDropCallback;
    if (onDrop->IsFunction()) {
        onDropCallback = JsCallbackWithoutNode<void(int32_t)>(
            context, JSRef<JSFunc>::Cast(onDrop), &CallJsFuncWithIndex);
    }
    LazyForEachModel::GetInstance()->SetItemDragHandler(std::move(onLongPressCallback), std::move(onDragStartCallback),
        std::move(onMoveThroughCallback), std::move(onDropCallback));
}
} // namespace OHOS::Ace::Framework
