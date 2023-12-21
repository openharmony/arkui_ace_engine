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
#include "core/components_ng/pattern/app_bar/atomic_service_layout_algorithm.h"

#include "base/geometry/dimension.h"
#include "core/common/container.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_algorithm.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
void AtomicServiceLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto container = Container::Current();
    auto appBar = container->GetAppBar();
    Dimension rootWidthByPx(PipelineContext::GetCurrentRootWidth(), DimensionUnit::PX);
    Dimension rootWidthByVp(rootWidthByPx.ConvertToVp(), DimensionUnit::VP);
    appBar->SetRowWidth(rootWidthByVp);
    appBar->ReverseBackButton();
    LinearLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG
