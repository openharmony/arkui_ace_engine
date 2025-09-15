/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_picker/container_picker_pattern.h"

#include "base/log/dump_log.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<LayoutAlgorithm> ContainerPickerPattern::CreateLayoutAlgorithm()
{
    auto layoutAlgorithm = MakeRefPtr<ContainerPickerLayoutAlgorithm>();
    return layoutAlgorithm;
}

bool ContainerPickerPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }
    // To do
    return false;
}

ScrollResult ContainerPickerPattern::HandleScroll(float offset, int32_t source, NestedState state, float velocity)
{
    return { 0.0f, true };
}

bool ContainerPickerPattern::HandleScrollVelocity(float velocity, const RefPtr<NestableScrollContainer>& child)
{
    // To do
    return false;
}

void ContainerPickerPattern::OnScrollStartRecursive(
    WeakPtr<NestableScrollContainer> child, float position, float velocity)
{
    // To do
}
void ContainerPickerPattern::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    // To do
}
} // namespace OHOS::Ace::NG
