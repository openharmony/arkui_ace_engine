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

#ifndef FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H
#define FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H

#include <singleton.h>

#include "iremote_object.h"
#include "ui_content_errors.h"
#include "ui_content_stub.h"

#include "base/utils/macros.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT UIContentServiceStubImpl : public UiContentStub {
public:
    int32_t Connect(const EventCallback& eventCallback) override
    {
        return 0;
    }
    int32_t GetInspectorTree(const std::function<void(std::string, int32_t, bool)>& eventCallback) override;
    int32_t RegisterClickEventCallback(const EventCallback& eventCallback) override;
    int32_t RegisterRouterChangeEventCallback(const EventCallback& eventCallback) override;
    int32_t RegisterSearchEventCallback(const EventCallback& eventCallback) override;
    int32_t RegisterComponentChangeEventCallback(const EventCallback& eventCallback) override;
    int32_t RegisterWebUnfocusEventCallback(
        const std::function<void(int64_t accessibilityId, const std::string& data)>& eventCallback) override;
    int32_t SendCommand(int32_t id, const std::string& command) override;
    int32_t SendCommandAsync(int32_t id, const std::string& command) override;
    int32_t UnregisterClickEventCallback() override;
    int32_t UnregisterSearchEventCallback() override;
    int32_t UnregisterRouterChangeEventCallback() override;
    int32_t UnregisterComponentChangeEventCallback() override;
    int32_t UnregisterWebUnfocusEventCallback() override;
    bool IsConnect() override;
    int32_t ResetTranslateTextAll() override;
    int32_t ResetTranslateText(int32_t nodeId) override;
    int32_t GetWebViewTranslateText(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) override;
    int32_t GetWebViewCurrentLanguage(const EventCallback& eventCallback) override;
    int32_t StartWebViewTranslate(
        const std::string& data, const std::function<void(int32_t, std::string)>& eventCallback) override;
    int32_t SendTranslateResult(int32_t nodeId, std::vector<std::string> results, std::vector<int32_t> ids) override;
    int32_t EndWebViewTranslate() override;
    int32_t GetCurrentPageName(const std::function<void(std::string)>& finishCallback) override;
    int32_t SendTranslateResult(int32_t nodeId, std::string result) override;
    int32_t GetCurrentImagesShowing(
        const std::function<void(std::vector<std::pair<int32_t, std::shared_ptr<Media::PixelMap>>>)>& finishCallback)
        override;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_INTERFACE_UI_CONTENT_STUB_IMPL_H
