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
#include "core/components_ng/pattern/container_modal/static/container_modal_static_pattern.h"

#include <atomic>

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/device_config.h"
#include "base/utils/measure_util.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/xbar_proxy_wrapper.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/container_modal/container_modal_toolbar.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
inline std::string Bool2String(bool value)
{
    return value ? "true" : "false";
}
} // namespace

void ContainerModalStaticPattern::SetAppTitle(const std::string& title)
{
    auto customTitleNode = GetCustomTitle();
    CHECK_NULL_VOID(customTitleNode);
    customTitleNode->FireSetAppTitleFunc(title);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "SetAppTitle successfully");

    auto customFloatingTitleNode = GetCustomFloatingTitle();
    CHECK_NULL_VOID(customFloatingTitleNode);
    customFloatingTitleNode->FireSetAppTitleFunc(title);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "Floating SetAppTitle successfully");
}

void ContainerModalStaticPattern::SetAppIcon(const RefPtr<PixelMap>& icon)
{
    CHECK_NULL_VOID(icon);
    auto customTitleNode = GetCustomTitle();
    CHECK_NULL_VOID(customTitleNode);
    customTitleNode->FireSetSetAppIconFunc(icon);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "SetAppIcon successfully");

    auto customFloatingTitleNode = GetCustomFloatingTitle();
    CHECK_NULL_VOID(customFloatingTitleNode);
    customFloatingTitleNode->FireSetSetAppIconFunc(icon);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "Floating SetAppIcon successfully");
}

void ContainerModalStaticPattern::ChangeCustomTitle(bool isFocus)
{
    // update custom title label
    auto customTitleNode = GetCustomTitle();
    CHECK_NULL_VOID(customTitleNode);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticPattern::ChangeCustomTitle isFocus = %{public}d", isFocus);
    isFocus ? customTitleNode->FireWindowFocusedFunc() : customTitleNode->FireWindowUnFocusedFunc();
}

void ContainerModalStaticPattern::ChangeFloatingTitle(bool isFocus)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);

    if (windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FLOATING &&
        windowManager->GetWindowMode() != WindowMode::WINDOW_MODE_FULLSCREEN) {
        windowManager->SetCurrentWindowMaximizeMode(MaximizeMode::MODE_RECOVER);
    }

    auto floatingTitleRow = GetFloatingTitleRow();
    CHECK_NULL_VOID(floatingTitleRow);
    auto floatingContext = floatingTitleRow->GetRenderContext();
    CHECK_NULL_VOID(floatingContext);
    floatingContext->UpdateBackgroundColor(GetContainerColor(isFocus));
    // update floating custom title label
    auto customFloatingTitleNode = GetCustomFloatingTitle();
    CHECK_NULL_VOID(customFloatingTitleNode);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticPattern::ChangeFloatingTitle isFocus = %{public}d", isFocus);
    isFocus ? customFloatingTitleNode->FireWindowFocusedFunc() : customFloatingTitleNode->FireWindowUnFocusedFunc();
}

void ContainerModalStaticPattern::ChangeControlButtons(bool isFocus)
{
    auto controlButtonsNode = GetCustomButton();
    CHECK_NULL_VOID(controlButtonsNode);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "ContainerModalStaticPattern::ChangeControlButtons isFocus = %{public}d", isFocus);
    isFocus ? controlButtonsNode->FireWindowFocusedFunc() : controlButtonsNode->FireWindowUnFocusedFunc();
    SetMaximizeIconIsRecover();
}

void ContainerModalStaticPattern::CallMenuWidthChange(int32_t resId)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    std::string text = "";
    if (SystemProperties::GetResourceDecoupling()) {
        auto resAdapter = ResourceManager::GetInstance().GetResourceAdapter(context->GetInstanceId());
        text = resAdapter->GetString(resId);
    }
    if (text.empty()) {
        TAG_LOGW(AceLogTag::ACE_APPBAR, "text is empty");
        return;
    }

    MeasureContext textCtx;
    textCtx.textContent = text;
    textCtx.fontSize = TITLE_TEXT_FONT_SIZE;
    auto textSize = MeasureUtil::MeasureTextSize(textCtx);

    auto controlButtonsNode = GetCustomButton();
    CHECK_NULL_VOID(controlButtonsNode);
    CalcDimension widthDimension(textSize.Width(), DimensionUnit::PX);
    auto width = widthDimension.ConvertToVp();
    TAG_LOGI(AceLogTag::ACE_APPBAR, "GetMenuWidth width = %{public}f", width);
    controlButtonsNode->FireSetCustomCallbackFunc(EVENT_NAME_MENU_WIDTH_CHANGE, std::to_string(width));
}

void ContainerModalStaticPattern::SetContainerButtonHide(
    bool hideSplit, bool hideMaximize, bool hideMinimize, bool hideClose)
{
    auto controlButtonsNode = GetCustomButton();
    CHECK_NULL_VOID(controlButtonsNode);
    TAG_LOGI(AceLogTag::ACE_APPBAR,
        "SetContainerButtonHide hideSplit = %{public}d hideMaximize = %{public}d hideMinimize = %{public}d hideClose = "
        "%{public}d",
        hideSplit, hideMaximize, hideMinimize, hideClose);
    controlButtonsNode->FireSetCustomCallbackFunc(EVENT_NAME_HIDE_SPLIT, Bool2String(hideSplit));
    controlButtonsNode->FireSetCustomCallbackFunc(EVENT_NAME_MAXIMIZE_VISIBILITY, Bool2String(hideMaximize));
    controlButtonsNode->FireSetCustomCallbackFunc(EVENT_NAME_MINIMIZE_VISIBILITY, Bool2String(hideMinimize));
    controlButtonsNode->FireSetCustomCallbackFunc(EVENT_NAME_CLOSE_VISIBILITY, Bool2String(hideClose));
}

void ContainerModalStaticPattern::SetColorConfigurationUpdate()
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "SetColorConfigurationUpdate");
    auto customButtonNode = GetCustomButton();
    CHECK_NULL_VOID(customButtonNode);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto isDark = context->GetColorMode() == ColorMode::DARK;
    TAG_LOGI(AceLogTag::ACE_APPBAR, "SetColorConfigurationUpdate isDark = %{public}d", isDark);
    customButtonNode->FireSetCustomCallbackFunc(EVENT_NAME_COLOR_CONFIGURATION, Bool2String(isDark));
}

void ContainerModalStaticPattern::SetCloseButtonStatus(bool isEnabled)
{
    auto customNode = GetCustomButton();
    CHECK_NULL_VOID(customNode);
    TAG_LOGI(AceLogTag::ACE_APPBAR, "SetCloseButtonStatus isEnabled: %{public}d", isEnabled);
    customNode->FireSetCustomCallbackFunc(EVENT_NAME_CLOSE_STATUS, Bool2String(isEnabled));
}

void ContainerModalStaticPattern::SetMaximizeIconIsRecover()
{
    auto customNode = GetCustomButton();
    CHECK_NULL_VOID(customNode);

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto windowManager = pipeline->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    auto windowMode = windowManager->GetWindowMode();
    MaximizeMode mode = windowManager->GetCurrentWindowMaximizeMode();
    if (mode == MaximizeMode::MODE_AVOID_SYSTEM_BAR || windowMode == WindowMode::WINDOW_MODE_FULLSCREEN ||
        windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY || windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "SetMaximizeIconIsRecover");
        customNode->FireSetCustomCallbackFunc(EVENT_NAME_MAXIMIZE_IS_RECOVER, Bool2String(true));
    } else {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "SetMaximizeIconIsRecover else");
        customNode->FireSetCustomCallbackFunc(EVENT_NAME_MAXIMIZE_IS_RECOVER, Bool2String(false));
    }
}

void ContainerModalStaticPattern::OnContainerModalEvent(const std::string& name, const std::string& value)
{
    auto controlButtonsNode = GetCustomButton();
    CHECK_NULL_VOID(controlButtonsNode);
    TAG_LOGI(
        AceLogTag::ACE_APPBAR, "OnContainerModalEvent name: %{public}s value: %{public}s", name.c_str(), value.c_str());
    controlButtonsNode->FireSetCustomCallbackFunc(name, value);
}

} // namespace OHOS::Ace::NG
