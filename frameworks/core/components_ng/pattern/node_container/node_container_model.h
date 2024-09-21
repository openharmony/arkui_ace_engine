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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_MODEL_H

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace {
class ACE_EXPORT NodeContainerModel {
public:
    static NodeContainerModel* GetInstance();
    virtual ~NodeContainerModel() = default;

    virtual void Create() = 0;
    virtual void SetMakeFunction(std::function<RefPtr<NG::UINode>(int32_t)>&& makeFunc) = 0;
    virtual void SetOnResize(std::function<void(const NG::SizeF& size)>&& resizeFunc) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnTouchEvent(TouchEventFunc &&touchEventFunc) = 0;
    virtual void BindController(std::function<void()>&& resetFunc) = 0;
    virtual void ResetController() = 0;
    virtual void FireMakeNode() = 0;

private:
    static std::unique_ptr<NodeContainerModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NODE_CONTAINER_NODE_CONTAINER_MODEL_H
