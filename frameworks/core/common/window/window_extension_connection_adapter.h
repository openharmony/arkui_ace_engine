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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_H

#include <string>

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/geometry/rect.h"
#include  "core/components_ng/base/frame_node.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {
class ACE_EXPORT WindowExtensionConnectionAdapter : public AceType {
    DECLARE_ACE_TYPE(WindowExtensionConnectionAdapter, AceType);

public:
    virtual void Show() {}
    virtual void Hide() {}
    virtual void RequestFocus() {}
    virtual void ConnectExtension(
        const std::string& want, const Rect& rect, WeakPtr<RenderNode> node, int32_t windowId) = 0;
    virtual void UpdateRect(const Rect& rect) = 0;
    virtual void RemoveExtension() = 0;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_WINDOW_EXTENSION_CONNECTION_ADAPTER_H
