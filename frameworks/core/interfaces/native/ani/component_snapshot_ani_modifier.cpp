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

#include "component_snapshot_ani_modifier.h"

#include "base/log/log.h"
#include "core/common/ace_engine.h"
#include "frameworks/core/components_ng/render/adapter/component_snapshot.h"

namespace OHOS::Ace::NG {

int32_t GetCurrentIdSafely()
{
    return Ace::Container::CurrentIdSafely();
}

RefPtr<Container> GetContainer(int32_t instanceId)
{
    auto container = Ace::AceEngine::Get().GetContainer(instanceId);
    return container;
}

void CreateFromBuilder(ArkUINodeHandle node,
    std::function<void(std::shared_ptr<OHOS::Media::PixelMap>, int32_t, std::function<void()>)>&& callback,
    SnapshotParam param)
{
    if (!node || !callback) {
        return;
    }
    auto uinode = AceType::Claim(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(uinode);
#ifdef ENABLE_ROSEN_BACKEND
    ComponentSnapshot::Create(uinode, std::move(callback), true, param);
#endif
}

const ArkUIAniComponentSnapshotModifier* GetComponentSnapshotAniModifier()
{
    static const ArkUIAniComponentSnapshotModifier impl = {
        .getCurrentIdSafely = OHOS::Ace::NG::GetCurrentIdSafely,
        .getContainer = OHOS::Ace::NG::GetContainer,
        .createFromBuilder = OHOS::Ace::NG::CreateFromBuilder,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG