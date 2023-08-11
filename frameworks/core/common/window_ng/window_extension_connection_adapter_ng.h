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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H

#include <string>

#include "base/geometry/rect.h"
#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "core/components_ng/base/frame_node.h"
#include "session/host/include/extension_session.h"

namespace OHOS::Ace {
class ACE_EXPORT WindowExtensionConnectionAdapterNG : public AceType {
    DECLARE_ACE_TYPE(WindowExtensionConnectionAdapterNG, AceType);

public:
    virtual void Show() {}
    virtual void Hide() {}
    virtual void RequestFocus() {}
    virtual void ConnectExtension(const RefPtr<NG::FrameNode>& node, int32_t windowId) = 0;
    virtual void UpdateRect(const Rect& rect) = 0;
    virtual void RemoveExtension() = 0;
    void SetExtensionSession(sptr<Rosen::ExtensionSession>& extensionSession)
    {
        extensionSession_ = extensionSession;
    }

protected:
    sptr<Rosen::ExtensionSession> extensionSession_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_NG_H
