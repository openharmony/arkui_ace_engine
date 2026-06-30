/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/grid_container_modifier.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid_container/grid_container_model.h"
#include "core/components_ng/pattern/grid_container/grid_container_model_ng.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
GridContainerModel* GetGridContainerModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("grid-container");
    static GridContainerModel* instance =
        loader ? reinterpret_cast<GridContainerModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
RefPtr<GridContainerInfo> GetContainerInfo(void* containerInfo)
{
    auto* parsedInfo = reinterpret_cast<RefPtr<GridContainerInfo>*>(containerInfo);
    return parsedInfo ? *parsedInfo : GridContainerInfo::Builder().Build();
}
} // namespace

void Create(void* containerInfo)
{
    static GridContainerModelNG model;
    model.Create(GetContainerInfo(containerInfo));
}

void Pop()
{
    GridContainerModelNG().Pop();
}

ArkUINodeHandle CreateGridContainerFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = GridContainerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

#ifndef CROSS_PLATFORM
void CreateImpl(void* containerInfo)
{
    auto* model = OHOS::Ace::GetGridContainerModelImpl();
    CHECK_NULL_VOID(model);
    model->Create(GetContainerInfo(containerInfo));
}

void PopImpl()
{
    auto* model = OHOS::Ace::GetGridContainerModelImpl();
    CHECK_NULL_VOID(model);
    model->Pop();
}
#endif

const ArkUIGridContainerModifier* GetGridContainerDynamicModifier()
{
#ifndef CROSS_PLATFORM
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIGridContainerModifier modifier = {
            .create = CreateImpl,
            .pop = PopImpl,
            .createFrameNode = CreateGridContainerFrameNode,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
#endif
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGridContainerModifier modifier = {
        .create = Create,
        .pop = Pop,
        .createFrameNode = CreateGridContainerFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG
