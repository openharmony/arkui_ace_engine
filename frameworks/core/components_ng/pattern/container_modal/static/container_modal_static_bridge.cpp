/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/container_modal/static/container_modal_static_bridge.h"

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/static/container_modal_static_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::string EVENT_NAME_CUSTOM_MAX_CLICK_STATIC = "arkui_custom_max_click";
const std::string EVENT_NAME_MIN_CLICK_STATIC = "arkui_custom_min_click";
const std::string EVENT_NAME_CLOSE_CLICK_STATIC = "arkui_custom_close_click";
const std::string EVENT_NAME_PAN_EVENT_STATIC = "arkui_custom_pan_event";
const std::string EVENT_NAME_LEFT_SPLIT_CLICK_STATIC = "arkui_custom_left_split_click";
const std::string EVENT_NAME_RIGHT_SPLIT_CLICK_STATIC = "arkui_custom_right_split_click";
const std::string EVENT_NAME_BUTTON_POINT_LIGHT_ANIM_STATIC = "arkui_custom_button_point_light_anim";
const std::string EVENT_NAME_BUTTON_RECT_CHANGE_STATIC = "arkui_custom_button_rect_change";
const std::string EVENT_NAME_MENU_WIDTH_CHANGE_STATIC = "arkui_custom_menu_width_change";

} // namespace

const std::map<std::string, std::function<void(const std::string& eventName, const std::string& param)>>
    ContainerModalStaticBridge::nativeFuncMap_ = {
        { EVENT_NAME_CUSTOM_MAX_CLICK_STATIC, ContainerModalStaticBridge::OnMaxBtnClick },
        { EVENT_NAME_MIN_CLICK_STATIC, ContainerModalStaticBridge::OnMinBtnClick },
        { EVENT_NAME_CLOSE_CLICK_STATIC, ContainerModalStaticBridge::OnCloseBtnClick },
        { EVENT_NAME_LEFT_SPLIT_CLICK_STATIC, ContainerModalStaticBridge::OnLeftSplitClick },
        { EVENT_NAME_RIGHT_SPLIT_CLICK_STATIC, ContainerModalStaticBridge::OnRightSplitClick },
        { EVENT_NAME_BUTTON_POINT_LIGHT_ANIM_STATIC, ContainerModalStaticBridge::AddButtonPointLightAnim },
        { EVENT_NAME_BUTTON_RECT_CHANGE_STATIC, ContainerModalStaticBridge::CallButtonsRectChange },
        { EVENT_NAME_MENU_WIDTH_CHANGE_STATIC, ContainerModalStaticBridge::CallMenuWidthChange },
    };

void ContainerModalStaticBridge::OnMaxBtnClick(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnMaxBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnMaxButtonClick();
}

void ContainerModalStaticBridge::OnMinBtnClick(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnMinBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnMinButtonClick();
}

void ContainerModalStaticBridge::OnCloseBtnClick(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "OnCloseBtnClick");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->OnCloseButtonClick();
}

void ContainerModalStaticBridge::OnLeftSplitClick(const std::string& eventName, const std::string& param)
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

void ContainerModalStaticBridge::OnRightSplitClick(const std::string& eventName, const std::string& param)
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

void ContainerModalStaticBridge::AddButtonPointLightAnim(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "AddButtonPointLightAnim");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
}

void ContainerModalStaticBridge::CallButtonsRectChange(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "CallButtonsRectChange");
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->CallButtonsRectChange();
    pattern->InitAllTitleRowLayoutProperty();
}

void ContainerModalStaticBridge::CallMenuWidthChange(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "CallMenuWidthChange");
    // second param is resource id
    int32_t resId = StringUtils::StringToInt(param);
    auto pattern = GetContainerModalPattern();
    CHECK_NULL_VOID(pattern);
    pattern->CallMenuWidthChange(resId);
}

RefPtr<NG::ContainerModalStaticPattern> ContainerModalStaticBridge::GetContainerModalPattern()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContextPtrSafely();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_RETURN(rootNode, nullptr);
    auto containerMode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildren().front());
    CHECK_NULL_RETURN(containerMode, nullptr);
    return containerMode->GetPattern<ContainerModalStaticPattern>();
}

void ContainerModalStaticBridge::CallWindowNative(const std::string& eventName, const std::string& param)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "CallWindowNative");
    auto pipelineContext = NG::PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto rootNode = pipelineContext->GetRootElement();
    CHECK_NULL_VOID(rootNode);
    auto containerMode = AceType::DynamicCast<NG::FrameNode>(rootNode->GetChildren().front());
    CHECK_NULL_VOID(containerMode);
    auto pattern = containerMode->GetPattern<ContainerModalStaticPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->CallContainerModalNative(eventName, param);
}

void ContainerModalStaticBridge::CallNative(const std::string& eventName, const std::string& param)
{
    if (eventName.length() == 0) {
        return;
    }
    if (eventName.rfind("arkui", 0) == 0) {
        auto it = nativeFuncMap_.find(eventName);
        if (it == nativeFuncMap_.end()) {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "Event not found: %{public}s", eventName.c_str());
            return;
        }
        it->second(eventName, param);
    } else {
        CallWindowNative(eventName, param);
    }
}

} // namespace OHOS::Ace::NG
