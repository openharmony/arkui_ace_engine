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

#include "frameworks/bridge/declarative_frontend/jsview/js_container_modal_view.h"
#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
const std::string EVENT_NAME_CUSTOM_MAX_CLICK = "arkui_custom_max_click";
const std::string EVENT_NAME_MIN_CLICK = "arkui_custom_min_click";
const std::string EVENT_NAME_CLOSE_CLICK = "arkui_custom_close_click";
const std::string EVENT_NAME_PAN_EVENT = "arkui_custom_pan_event";
const std::string EVENT_NAME_LEFT_SPLIT_CLICK = "arkui_custom_left_split_click";
const std::string EVENT_NAME_RIGHT_SPLIT_CLICK = "arkui_custom_right_split_click";
const std::string EVENT_NAME_BUTTON_POINT_LIGHT_ANIM = "arkui_custom_button_point_light_anim";
const std::string EVENT_NAME_BUTTON_RECT_CHANGE = "arkui_custom_button_rect_change";
const std::string EVENT_NAME_MENU_WIDTH_CHANGE = "arkui_custom_menu_width_change";

const int32_t EVENT_NAME_MENU_WIDTH_CHANGE_PARAM_COUNT = 2;

std::map<std::string, std::function<void(const JSCallbackInfo& info)>> nativeFucMap_;
} // namespace

void JSContainerModal::OnMaxBtnClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnMaxBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnMaxButtonClick();
}

void JSContainerModal::OnMinBtnClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnMinBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnMinButtonClick();
}

void JSContainerModal::OnCloseBtnClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnCloseBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnCloseButtonClick();
}

void JSContainerModal::OnLeftSplitClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnLeftSplitClick");
    auto pipelineContext = NG::PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto containerMode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildren().front());
    CHECK_NULL_VOID(containerMode);
    auto pattern = containerMode->GetPattern<NG::ContainerModalPatternEnhance>();
    CHECK_NULL_VOID(pattern);
    pattern->OnMenuItemClickGesture(true);
}

void JSContainerModal::OnRightSplitClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnRightSplitClick");
    auto pipelineContext = NG::PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto containerMode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildren().front());
    CHECK_NULL_VOID(containerMode);
    auto pattern = containerMode->GetPattern<NG::ContainerModalPatternEnhance>();
    CHECK_NULL_VOID(pattern);
    pattern->OnMenuItemClickGesture(false);
}

void JSContainerModal::AddButtonPointLightAnim(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "AddButtonPointLightAnim");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
}

void JSContainerModal::CallButtonsRectChange(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "CallButtonsRectChange");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->CallButtonsRectChange();
}

void JSContainerModal::CallMenuWidthChange(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "CallMenuWidthChange");
    // second param is resource id
    if (info.Length() < EVENT_NAME_MENU_WIDTH_CHANGE_PARAM_COUNT || !info[1]->IsString()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "CallMenuWidthChange param error");
        return;
    }
    int32_t resId;
    ConvertFromJSValue(info[1], resId);
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->CallMenuWidthChange(resId);
}

RefPtr<NG::ContainerModalPatternEnhance> JSContainerModal::GetContainerModalPattern()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContextPtrSafely();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto containerMode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildren().front());
    CHECK_NULL_RETURN(containerMode, nullptr);
    return containerMode->GetPattern<NG::ContainerModalPatternEnhance>();
}

void JSContainerModal::CallNative(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "callNative");
    if (info.Length() < 1) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "callNative param erro");
        return;
    }
    if (!info[0]->IsString()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "callNative first param erro");
        return;
    }
    std::string eventName = info[0]->ToString();
    auto it = nativeFucMap_.find(eventName);
    if (it == nativeFucMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "Event not found: %{public}s", eventName.c_str());
        return;
    }
    it->second(info);
}

void JSContainerModal::JSBind(BindingTarget globalObj)
{
    nativeFucMap_ = {
        { EVENT_NAME_CUSTOM_MAX_CLICK, JSContainerModal::OnMaxBtnClick },
        { EVENT_NAME_MIN_CLICK, JSContainerModal::OnMinBtnClick },
        { EVENT_NAME_CLOSE_CLICK, JSContainerModal::OnCloseBtnClick },
        { EVENT_NAME_LEFT_SPLIT_CLICK, JSContainerModal::OnLeftSplitClick },
        { EVENT_NAME_RIGHT_SPLIT_CLICK, JSContainerModal::OnRightSplitClick },
        { EVENT_NAME_BUTTON_POINT_LIGHT_ANIM, JSContainerModal::AddButtonPointLightAnim },
        { EVENT_NAME_BUTTON_RECT_CHANGE, JSContainerModal::CallButtonsRectChange },
        { EVENT_NAME_MENU_WIDTH_CHANGE, JSContainerModal::CallMenuWidthChange },
    };

    JSClass<JSContainerModal>::Declare("ContainerModal");
    JSClass<JSContainerModal>::StaticMethod("callNative", &JSContainerModal::CallNative);
    JSClass<JSContainerModal>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework
