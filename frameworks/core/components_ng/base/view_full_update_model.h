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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_FULL_UPDATE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_FULL_UPDATE_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

struct NodeInfo {
    std::string viewId;
    std::function<void()> appearFunc;
    std::function<RefPtr<AceType>()> renderFunc;
    std::function<void()> removeFunc;
    std::function<void(const RefPtr<AceType>&)> updateNodeFunc;
    std::function<void()> pageTransitionFunc;
    bool isStatic = false;
};

class ACE_EXPORT ViewFullUpdateModel {
public:
    static ViewFullUpdateModel* GetInstance();
    virtual ~ViewFullUpdateModel() = default;

    virtual RefPtr<AceType> CreateNode(NodeInfo&& info) = 0;
    virtual bool MarkNeedUpdate(const WeakPtr<AceType>& node) = 0;

private:
    static std::unique_ptr<ViewFullUpdateModel> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_FULL_UPDATE_MODEL_H
