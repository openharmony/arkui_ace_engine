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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_PARTIAL_UPDATE_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_PARTIAL_UPDATE_MODEL_H

#include <functional>
#include <memory>
#include <mutex>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "frameworks/core/components_ng/pattern/custom/custom_node_base.h"

namespace OHOS::Ace {

struct NodeInfoPU {
    std::function<void()> appearFunc;
    std::function<void()> didBuildFunc;
    std::function<RefPtr<AceType>()> renderFunc;
    std::function<void()> updateFunc;
    std::function<void()> removeFunc;
    std::function<void(const RefPtr<AceType>&)> updateNodeFunc;
    std::function<void(const std::string&)> updateViewIdFunc;
    std::function<void()> pageTransitionFunc;
    std::function<void(NG::LayoutWrapper*)> measureFunc;
    std::function<void(NG::LayoutWrapper*)> measureSizeFunc;
    std::function<void(NG::LayoutWrapper*)> layoutFunc;
    std::function<void(NG::LayoutWrapper*)> placeChildrenFunc;
    std::function<void(bool)> reloadFunc;
    std::function<RefPtr<AceType>()> completeReloadFunc;
    std::function<void(int32_t)> nodeUpdateFunc;
    std::function<bool(int32_t)> hasNodeUpdateFunc;
    std::function<void(RefPtr<NG::CustomNodeBase>)> recycleCustomNodeFunc;
    std::function<void(bool)> setActiveFunc;
    std::function<void(const std::vector<std::string>&)> onDumpInfoFunc;
    std::function<std::string()> onDumpInspectorFunc;
    std::function<void*()> getThisFunc;

    bool hasMeasureOrLayout = false;
    bool isStatic = false;
    bool isCustomTitle = false;
    int32_t codeRow = -1;
    int32_t codeCol = -1;

    std::string jsViewName;
    bool isV2 = false;
    NG::ExtraInfo extraInfo;
};

using UpdateTask = std::tuple<int32_t, RefPtr<AceType>, RefPtr<AceType>>;

class ACE_FORCE_EXPORT ViewPartialUpdateModel {
public:
    static ViewPartialUpdateModel* GetInstance();
    virtual ~ViewPartialUpdateModel() = default;

    virtual RefPtr<AceType> CreateNode(NodeInfoPU&& info) = 0;
    virtual bool MarkNeedUpdate(const WeakPtr<AceType>& node) = 0;
    virtual void FlushUpdateTask(const UpdateTask& task) = 0;
    virtual void FinishUpdate(
        const WeakPtr<AceType>& viewNode, int32_t id, std::function<void(const UpdateTask&)>&& emplaceTaskFunc) = 0;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_PARTIAL_UPDATE_MODEL_H
