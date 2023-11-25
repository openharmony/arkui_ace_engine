/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_TITLE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_TITLE_NODE_H

#include "core/components_ng/pattern/custom/custom_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT CustomTitleNode : public CustomNode {
    DECLARE_ACE_TYPE(CustomTitleNode, CustomNode);

public:
    static RefPtr<CustomTitleNode> CreateCustomTitleNode(int32_t nodeId, const std::string& viewKey);

    CustomTitleNode(int32_t nodeId, const std::string& viewKey);
    ~CustomTitleNode() override = default;

    void SetAppTitleCallback(const std::function<void(const std::string&)>& callback)
    {
        appTitleCallback_ = callback;
    }

    void FireAppTitleCallback(const std::string& title)
    {
        if (appTitleCallback_) {
            appTitleCallback_(title);
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

    void SetOnWindowFocusedCallback(const std::function<void()>& callback)
    {
        onWindowFocusedCallback_ = callback;
    }

    void FireOnWindowFocusedCallback()
    {
        if (onWindowFocusedCallback_) {
            onWindowFocusedCallback_();
        }
    }

    void SetOnWindowUnfocusedCallback(const std::function<void()>& callback)
    {
        onWindowUnfocusedCallback_ = callback;
    }

    void FireOnWindowUnfocusedCallback()
    {
        if (onWindowUnfocusedCallback_) {
            onWindowUnfocusedCallback_();
        }
    }

private:
    std::function<void(const std::string&)> appTitleCallback_ = nullptr;
    std::function<void(const RefPtr<PixelMap>&)> appIconCallback_ = nullptr;
    std::function<void()> onWindowFocusedCallback_ = nullptr;
    std::function<void()> onWindowUnfocusedCallback_ = nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_CUSTOM_NODE_H