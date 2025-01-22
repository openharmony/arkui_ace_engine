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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_APP_BAR_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_APP_BAR_NODE_H

#include "core/components_ng/pattern/custom/custom_node.h"

namespace OHOS::Ace::NG {

const std::string ARKUI_APP_BAR_COLOR_CONFIGURATION = "arkui_app_bar_color_configuration";
const std::string ARKUI_APP_BAR_MENU_SAFE_AREA = "arkui_app_bar_menu_safe_area";
const std::string ARKUI_APP_BAR_CONTENT_SAFE_AREA = "arkui_app_bar_content_safe_area";
const std::string ARKUI_APP_BAR_BAR_INFO = "arkui_app_bar_info";
const std::string ARKUI_APP_BAR_SCREEN = "arkui_app_bar_screen";
const std::string ARKUI_APP_BG_COLOR = "arkui_app_bg_color";

class ACE_EXPORT CustomAppBarNode : public CustomNode {
    DECLARE_ACE_TYPE(CustomAppBarNode, CustomNode);

public:
    static RefPtr<CustomAppBarNode> CreateCustomAppBarNode(int32_t nodeId, const std::string& viewKey);

    CustomAppBarNode(int32_t nodeId, const std::string& viewKey);
    ~CustomAppBarNode() override = default;

    void SetCustomCallback(const std::function<void(const std::string& eventName, const std::string& param)>& callback)
    {
        customCallback_ = callback;
    }

    void FireCustomCallback(const std::string& eventName, const std::string& param)
    {
        if (customCallback_) {
            TAG_LOGI(AceLogTag::ACE_APPBAR, "app bar FireCustomCallback eventName =%{public}s, param = %{public}s",
                eventName.c_str(), param.c_str());
            customCallback_(eventName, param);
        }
    }

    void FireCustomCallback(const std::string& eventName, bool value)
    {
        if (customCallback_) {
            customCallback_(eventName, BoolToString(value));
        }
    }

    void SetAppIconCallback(const std::function<void(const RefPtr<PixelMap>&)>& callback)
    {
        appIconCallback_ = callback;
    }

    void FireAppIconCallback(const RefPtr<PixelMap>& icon)
    {
        if (appIconCallback_) {
            appIconCallback_(icon);
        }
    }

private:
    std::string BoolToString(bool value)
    {
        return value ? "true" : "false";
    }
    std::function<void(const std::string&, const std::string&)> customCallback_ = nullptr;
    std::function<void(const RefPtr<PixelMap>&)> appIconCallback_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_APP_BAR_NODE_H