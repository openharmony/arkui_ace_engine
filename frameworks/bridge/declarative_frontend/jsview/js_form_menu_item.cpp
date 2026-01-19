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

#include "bridge/declarative_frontend/jsview/js_form_menu_item.h"

#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "want.h"

#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_item_theme.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/models/form_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/menu_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_model.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<MenuItemModel> MenuItemModel::instance_ = nullptr;
std::mutex MenuItemModel::mutex_;

MenuItemModel* MenuItemModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::MenuItemModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::MenuItemModelNG());
            } else {
                instance_.reset(new Framework::MenuItemModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

std::unique_ptr<MenuModel> MenuModel::instance_ = nullptr;
std::mutex MenuModel::mutex_;

MenuModel* MenuModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::MenuModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::MenuModelNG());
            } else {
                instance_.reset(new Framework::MenuModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int NUM_WANT_1 = 0;
constexpr int NUM_DATA_2 = 1;
constexpr int NUM_FUN_3 = 2;
constexpr int NUM_CALLBACKNUM = 2;
}

void JSFormMenuItem::ParseMenuItemOptionsResource(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuItemObj, MenuItemProperties& menuItemProps)
{
    std::string startIconPath;
    std::string contentStr;
    std::string endIconPath;
    std::string labelStr;
    RefPtr<ResourceObject> contentStrObj;
    RefPtr<ResourceObject> labelStrObj;
    RefPtr<ResourceObject> startIconObj;
    RefPtr<ResourceObject> endIconObj;
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;

    auto startIcon = menuItemObj->GetProperty("startIcon");
    auto content = menuItemObj->GetProperty("content");
    auto endIcon = menuItemObj->GetProperty("endIcon");
    auto label = menuItemObj->GetProperty("labelInfo");
    auto symbolStart = menuItemObj->GetProperty("symbolStartIcon");
    auto symbolEnd = menuItemObj->GetProperty("symbolEndIcon");

    if (symbolStart->IsObject()) {
        JSViewAbstract::SetSymbolOptionApply(info, symbolApply, symbolStart);
        menuItemProps.startApply = symbolApply;
    } else if (ParseJsMedia(startIcon, startIconPath, startIconObj)) {
        std::string bundleName;
        std::string moduleName;
        GetJsMediaBundleInfo(startIcon, bundleName, moduleName);
        ImageSourceInfo imageSourceInfo(startIconPath, bundleName, moduleName);
        menuItemProps.startIcon = imageSourceInfo;
    }
    ParseJsString(content, contentStr, contentStrObj);
    menuItemProps.content = contentStr;
    if (symbolEnd->IsObject()) {
        JSViewAbstract::SetSymbolOptionApply(info, symbolApply, symbolEnd);
        menuItemProps.endApply = symbolApply;
    } else if (ParseJsMedia(endIcon, endIconPath, endIconObj)) {
        std::string bundleName;
        std::string moduleName;
        GetJsMediaBundleInfo(endIcon, bundleName, moduleName);
        ImageSourceInfo imageSourceInfo(endIconPath, bundleName, moduleName);
        menuItemProps.endIcon = imageSourceInfo;
    }
    if (ParseJsString(label, labelStr, labelStrObj)) {
        menuItemProps.labelInfo = labelStr;
    }
    if (SystemProperties::ConfigChangePerform()) {
        AddMenuItemOptionsResource(contentStrObj, labelStrObj, menuItemProps);
    }
}

void JSFormMenuItem::AddMenuItemOptionsResource(const RefPtr<ResourceObject>& contentStrObj,
    const RefPtr<ResourceObject>& labelStrObj, MenuItemProperties& menuItemProps)
{
    if (contentStrObj) {
        menuItemProps.AddResource(
            "MenuItem.Content", contentStrObj, [](const RefPtr<ResourceObject>& resObj, MenuItemProperties& props) {
                std::string contentStr;
                CHECK_NE_VOID(ResourceParseUtils::ParseResString(resObj, contentStr), true);
                props.content = contentStr;
            });
    }
    if (labelStrObj) {
        menuItemProps.AddResource(
            "MenuItem.Label", labelStrObj, [](const RefPtr<ResourceObject>& resObj, MenuItemProperties& props) {
                std::string labelInfoStr;
                CHECK_NE_VOID(ResourceParseUtils::ParseResString(resObj, labelInfoStr), true);
                props.labelInfo = labelInfoStr;
            });
    }
}

void JSFormMenuItem::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || (!info[0]->IsObject() && !info[0]->IsFunction())) {
        MenuItemModel::GetInstance()->Create(nullptr);
        return;
    }
    // custom menu item
    if (info[0]->IsFunction()) {
        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(info[0]));
        CHECK_NULL_VOID(builderFunc);
        RefPtr<NG::UINode> customNode;
        {
            ViewStackModel::GetInstance()->NewScope();
            builderFunc->Execute();
            customNode = AceType::DynamicCast<NG::UINode>(ViewStackModel::GetInstance()->Finish());
        }
        CHECK_NULL_VOID(customNode);
        MenuItemModel::GetInstance()->Create(customNode);
    } else {
        auto menuItemObj = JSRef<JSObject>::Cast(info[0]);
        MenuItemProperties menuItemProps;
        ParseMenuItemOptionsResource(info, menuItemObj, menuItemProps);
        auto builder = menuItemObj->GetProperty("builder");
        if (!builder.IsEmpty() && builder->IsFunction()) {
            auto subBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
            CHECK_NULL_VOID(subBuilderFunc);
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto subBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(subBuilderFunc),
                                    node = targetNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("MenuItem SubBuilder");
                PipelineContext::SetCallBackNode(node);
                func->ExecuteJS();
            };
            menuItemProps.buildFunc = std::move(subBuildFunc);
        }
        MenuItemModel::GetInstance()->Create(menuItemProps);
    }
    JSMenuItemTheme::ApplyTheme();
}

void JSFormMenuItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSFormMenuItem>::Declare("FormMenuItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSFormMenuItem>::StaticMethod("create", &JSFormMenuItem::Create, opt);
    JSClass<JSFormMenuItem>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSFormMenuItem>::StaticMethod("onRequestPublishFormWithSnapshot",
        &JSFormMenuItem::JsOnRequestPublishFormWithSnapshot);
    JSClass<JSFormMenuItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSFormMenuItem>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSFormMenuItem::RequestPublishFormWithSnapshot(JSRef<JSVal> wantValue,
    const std::string& formBindingDataStr, RefPtr<JsFunction> jsCBFunc)
{
    RefPtr<WantWrap> wantWrap = CreateWantWrapFromNapiValue(wantValue);
    if (!wantWrap) {
        TAG_LOGE(AceLogTag::ACE_FORM, "onTap wantWrap is NULL.");
        return;
    }

    int64_t formId = 0;
    AAFwk::Want& want = const_cast<AAFwk::Want&>(wantWrap->GetWant());
    if (!want.HasParameter("ohos.extra.param.key.add_form_to_host_snapshot") ||
        !want.HasParameter("ohos.extra.param.key.add_form_to_host_width") ||
        !want.HasParameter("ohos.extra.param.key.add_form_to_host_height") ||
        !want.HasParameter("ohos.extra.param.key.add_form_to_host_screenx") ||
        !want.HasParameter("ohos.extra.param.key.add_form_to_host_screeny")) {
        TAG_LOGE(AceLogTag::ACE_FORM, "want has no component snapshot info");
        return;
    }

    std::string errMsg;
    int32_t errCode = FormModel::GetInstance()->RequestPublishFormWithSnapshot(want, formBindingDataStr, formId,
                                                                               errMsg);
    if (!jsCBFunc) {
        TAG_LOGE(AceLogTag::ACE_FORM, "jsCBFunc is null");
        return;
    }

    JSRef<JSVal> params[NUM_CALLBACKNUM];
    JSRef<JSObject> errObj = JSRef<JSObject>::New();
    errObj->SetProperty<int32_t>("code", errCode);
    errObj->SetProperty<std::string>("message", errMsg);
    params[0] = errObj;
    params[1] = JSRef<JSVal>::Make(ToJSValue(std::to_string(formId)));
    jsCBFunc->ExecuteJS(NUM_CALLBACKNUM, params);
}

void JSFormMenuItem::JsOnRequestPublishFormWithSnapshot(const JSCallbackInfo& info)
{
    bool retFlag;
    OnClickParameterCheck(info, retFlag);
    if (retFlag) {
        return;
    }

    auto want = info[NUM_WANT_1];
    JSRef<JSVal> wantValue = JSRef<JSVal>::Cast(want);
    if (wantValue->IsNull()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "JsOnClick wantValue is null");
        return;
    }

    std::string formBindingDataStr;
    JSViewAbstract::ParseJsString(info[NUM_DATA_2], formBindingDataStr);
    if (formBindingDataStr.empty()) {
        TAG_LOGW(AceLogTag::ACE_FORM, "JsOnClick formBindingDataStr is empty");
    }

    RefPtr<JsFunction> jsCallBackFunc = nullptr;
    if (!info[NUM_FUN_3]->IsUndefined() && info[NUM_FUN_3]->IsFunction()) {
        jsCallBackFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[NUM_FUN_3]));
    }

    RequestPublishFormWithSnapshot(wantValue, formBindingDataStr, jsCallBackFunc);
}

void JSFormMenuItem::OnClickParameterCheck(const JSCallbackInfo& info, bool& retFlag)
{
    retFlag = true;

    if (info[NUM_WANT_1]->IsUndefined() || !info[NUM_WANT_1]->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "OnClickParameterCheck bad parameter info[1]");
        return;
    }
    retFlag = false;
}
} // namespace OHOS::Ace::Framework
