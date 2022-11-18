/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_WINDOW_CONNECTION_WINDOW_EXTENSION_CONNECTION_OHOS_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_WINDOW_CONNECTION_WINDOW_EXTENSION_CONNECTION_OHOS_H

#include "window_extension_connection.h"

#include "core/common/window/window_extension_connection_adapter.h"

namespace OHOS::Ace {
class ACE_EXPORT WindowExtensionConnectionAdapterOhos : public WindowExtensionConnectionAdapter {
    DECLARE_ACE_TYPE(WindowExtensionConnectionAdapterOhos, WindowExtensionConnectionAdapter);

public:
    void ConnectExtension(
        const std::string& want, const Rect& rect, WeakPtr<RenderNode> node, int32_t windowId) override;
    void RemoveExtension() override;
    void UpdateRect(const Rect& rect) override;
    void Show() override;
    void Hide() override;

private:
    std::unique_ptr<Rosen::WindowExtensionConnection> windowExtension_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_WINDOW_CONNECTION_WINDOW_EXTENSION_CONNECTION_OHOS_H