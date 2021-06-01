/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/test/unittest/mock/mock_render_common.h"

#include "adapter/ohos/osal/fake_asset_manager.h"
#include "adapter/ohos/osal/fake_task_executor.h"
#include "core/components/stage/stage_element.h"
#include "core/components/test/json/json_frontend.h"
#include "core/mock/mock_resource_register.h"

namespace OHOS::Ace {

RefPtr<PipelineContext> MockRenderCommon::GetMockContext()
{
    auto platformWindow = std::make_unique<MockWindow>(nullptr);
    auto window = std::make_unique<Window>(std::move(platformWindow));
    auto taskExecutor = Referenced::MakeRefPtr<FakeTaskExecutor>();
    auto assetManager = Referenced::MakeRefPtr<FakeAssetManager>();
    auto resRegister = Referenced::MakeRefPtr<MockResourceRegister>();
    auto fakeFrontend = Frontend::CreateDefault();

    auto pipelineContext = AceType::MakeRefPtr<PipelineContext>(
        std::move(window), taskExecutor, assetManager, resRegister, fakeFrontend, 0);
    pipelineContext->SetRootHeight(2049.0);
    pipelineContext->SetupRootElement();
    auto stageElement = pipelineContext->GetStageElement();
    if (!stageElement) {
        return pipelineContext;
    }
    auto renderStage = stageElement->GetRenderNode();
    if (!renderStage) {
        return pipelineContext;
    }
    renderStage->SetLayoutSize(Size(1080.0, 2049.0)); // same with root size.
    return pipelineContext;
}

} // namespace OHOS::Ace
