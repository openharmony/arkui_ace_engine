/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_plugin.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/plugin_model_impl.h"
#include "core/components_ng/pattern/plugin/plugin_model_ng.h"

namespace OHOS::Ace {
PluginModel* PluginModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::PluginModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::PluginModelNG instance;
        return &instance;
    } else {
        static Framework::PluginModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
void JSPlugin::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    // Parse template
    RequestPluginInfo pluginInfo;
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto templateObj = obj->GetProperty("template");
    if (templateObj->IsObject()) {
        auto jstemplateObj = JSRef<JSObject>::Cast(templateObj);
        auto sourceVal = jstemplateObj->GetProperty("source");
        if (sourceVal->IsString()) {
            pluginInfo.pluginName = sourceVal->ToString();
        }
        auto abilityVal = jstemplateObj->GetProperty("ability");
        if (!abilityVal->IsEmpty() && abilityVal->IsString()) {
            pluginInfo.bundleName = abilityVal->ToString();
        }

        auto bundleValue = jstemplateObj->GetProperty("bundleName");
        if (!bundleValue->IsEmpty() && bundleValue->IsString()) {
            pluginInfo.bundleName = bundleValue->ToString();
        }
    }
    if (pluginInfo.bundleName.size() > PATH_MAX || pluginInfo.pluginName.size() > PATH_MAX) {
        return;
    }
    // Parse data
    auto dataValue = obj->GetProperty("data");

    PluginModel::GetInstance()->Create(pluginInfo);
    if (dataValue->IsObject()) {
        PluginModel::GetInstance()->SetData(dataValue->ToString());
    }
}

void JSPlugin::JsSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> widthValue = sizeObj->GetProperty("width");
    CalcDimension width = 0.0_vp;
    if (!ParseJsDimensionVp(widthValue, width)) {
        return;
    }
    JSRef<JSVal> heightValue = sizeObj->GetProperty("height");
    CalcDimension height = 0.0_vp;
    if (!ParseJsDimensionVp(heightValue, height)) {
        return;
    }
    PluginModel::GetInstance()->SetPluginSize(width.IsValid() ? width : 0.0_vp, height.IsValid() ? height : 0.0_vp);
}

void JSPlugin::JsWidth(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    PluginModel::GetInstance()->SetWidth(value.IsValid() ? value : 0.0_vp);
}

void JSPlugin::JsHeight(const JSCallbackInfo& info)
{
    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }

    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    PluginModel::GetInstance()->SetHeight(value.IsValid() ? value : 0.0_vp);
}

void JSPlugin::JsOnComplete(const JSCallbackInfo& info)
{
#if defined(PLUGIN_COMPONENT_SUPPORTED)
    if (info[0]->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto OnComplete = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                                const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Plugin.OnComplete");
            PipelineContext::SetCallBackNode(node);
            func->ExecuteJSWithContext(0, nullptr, execCtx);
        };
        PluginModel::GetInstance()->SetOnComplete(std::move(OnComplete));
    }
#endif
}

void JSPlugin::JsOnError(const JSCallbackInfo& info)
{
#if defined(PLUGIN_COMPONENT_SUPPORTED)
    if (info[0]->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                            const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Plugin.OnComplete");
            std::vector<std::string> keys = { "errcode", "msg" };
            PipelineContext::SetCallBackNode(node);
            func->ExecuteWithContext(keys, param, execCtx);
        };
        PluginModel::GetInstance()->SetOnError(std::move(onError));
    }
#endif
}

void JSPlugin::JSBind(BindingTarget globalObj)
{
    JSClass<JSPlugin>::Declare("PluginComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPlugin>::StaticMethod("create", &JSPlugin::Create, opt);
    JSClass<JSPlugin>::StaticMethod("size", &JSPlugin::JsSize, opt);
    JSClass<JSPlugin>::StaticMethod("width", &JSPlugin::JsWidth);
    JSClass<JSPlugin>::StaticMethod("height", &JSPlugin::JsHeight);
    JSClass<JSPlugin>::StaticMethod("onComplete", &JSPlugin::JsOnComplete);
    JSClass<JSPlugin>::StaticMethod("onError", &JSPlugin::JsOnError);
    JSClass<JSPlugin>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSPlugin>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSPlugin>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSPlugin>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSPlugin>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSPlugin>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSPlugin>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSPlugin>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSPlugin>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
