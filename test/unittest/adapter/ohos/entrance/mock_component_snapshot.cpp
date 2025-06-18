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
#include <vector>

#include "core/components_ng/render/adapter/component_snapshot.h"


namespace OHOS::Ace::NG {
std::vector<std::pair<uint64_t, std::shared_ptr<Media::PixelMap>>> ComponentSnapshot::GetSoloNode(
    const RefPtr<FrameNode>& node)
{
    std::vector<std::pair<uint64_t, std::shared_ptr<Media::PixelMap>>> vec;
    return vec;
}
} // namespace OHOS::Ace::NG