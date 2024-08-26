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

#include "adapter/ohos/osal/system_bar_style_ohos.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Rosen {
// defined in js_window_utils.cpp
void ConvertJSSystemBarStyleToSystemBarProperties(napi_env env, napi_value jsObject,
    std::map<WindowType, SystemBarProperty>& properties, std::map<WindowType, SystemBarPropertyFlag>& propertyFlags);
}

namespace {
std::string GetStatusBarContentColor(
    const std::map<OHOS::Rosen::WindowType, OHOS::Rosen::SystemBarProperty>& properties)
{
    auto it = properties.find(OHOS::Rosen::WindowType::WINDOW_TYPE_STATUS_BAR);
    if (it == properties.end()) {
        return "None";
    }
    return OHOS::Ace::Color(it->second.contentColor_).ToString();
}

std::string GetStatusBarContentColorFlag(
    const std::map<OHOS::Rosen::WindowType, OHOS::Rosen::SystemBarPropertyFlag>& propertyFlags)
{
    auto it = propertyFlags.find(OHOS::Rosen::WindowType::WINDOW_TYPE_STATUS_BAR);
    if (it == propertyFlags.end()) {
        return "None";
    }
    return it->second.contentColorFlag ? "true" : "false";
}
}

namespace OHOS::Ace {
RefPtr<SystemBarStyle> SystemBarStyle::CreateStyleFromJsObj(void* env, void* value)
{
    auto style = AceType::MakeRefPtr<SystemBarStyleOhos>();
    CHECK_NULL_RETURN(style, nullptr);
    Rosen::ConvertJSSystemBarStyleToSystemBarProperties(
        reinterpret_cast<napi_env>(env), reinterpret_cast<napi_value>(value),
        style->properties_, style->propertyFlags_);
    TAG_LOGD(AceLogTag::ACE_NAVIGATION, "style from JsObj, color: %{public}s, flag: %{public}s",
        GetStatusBarContentColor(style->properties_).c_str(),
        GetStatusBarContentColorFlag(style->propertyFlags_).c_str());
    return style;
}

RefPtr<SystemBarStyleOhos> SystemBarStyleOhos::GetCurrentSystemBarStyle(const sptr<Rosen::Window>& window)
{
    CHECK_NULL_RETURN(window, nullptr);
    auto style = AceType::MakeRefPtr<SystemBarStyleOhos>();
    CHECK_NULL_RETURN(style, nullptr);
    window->GetSystemBarProperties(style->properties_);
    Rosen::SystemBarPropertyFlag flag;
    flag.contentColorFlag = true;
    style->propertyFlags_.emplace(Rosen::WindowType::WINDOW_TYPE_STATUS_BAR, flag);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "current system bar style, color: %{public}s, flag: %{public}s",
        GetStatusBarContentColor(style->properties_).c_str(),
        GetStatusBarContentColorFlag(style->propertyFlags_).c_str());
    return style;
}

void SystemBarStyleOhos::SetSystemBarStyle(const sptr<Rosen::Window>& window, const RefPtr<SystemBarStyle>& style)
{
    CHECK_NULL_VOID(window);
    auto tempStyle = AceType::DynamicCast<SystemBarStyleOhos>(style);
    CHECK_NULL_VOID(tempStyle);
    window->SetSystemBarProperties(tempStyle->properties_, tempStyle->propertyFlags_);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "set system bar style, color: %{public}s, flag: %{public}s",
        GetStatusBarContentColor(tempStyle->properties_).c_str(),
        GetStatusBarContentColorFlag(tempStyle->propertyFlags_).c_str());
}
} // namespace OHOS::Ace