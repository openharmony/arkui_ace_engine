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

#include "core/components_ng/pattern/navigation/title_bar_pattern.h"

#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"

namespace OHOS::Ace::NG {

namespace {

void MountBackButton(const RefPtr<TitleBarNode>& hostNode)
{
    auto titleBarLayoutProperty = hostNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    auto backButtonNode = AceType::DynamicCast<FrameNode>(hostNode->GetBackButton());
    CHECK_NULL_VOID(backButtonNode);
    auto backButtonLayoutProperty = backButtonNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(backButtonLayoutProperty);

    if (!titleBarLayoutProperty->HasNoPixMap()) {
        return;
    }
    backButtonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    if (titleBarLayoutProperty->HasImageSource()) {
        backButtonLayoutProperty->UpdateImageSourceInfo(titleBarLayoutProperty->GetImageSourceValue());
        backButtonNode->MarkModifyDone();
        return;
    }

    if (titleBarLayoutProperty->HasPixelMap()) {
        // TODO: use pixelMap
        backButtonNode->MarkModifyDone();
        return;
    }
}

}

void TitleBarPattern::OnModifyDone()
{
    auto hostNode = AceType::DynamicCast<TitleBarNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    MountBackButton(hostNode);
}

} // namespace OHOS::Ace::NG