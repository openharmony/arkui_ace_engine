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

#include "core/components_ng/pattern/xcomponent/xcomponent_model_static.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern_v2.h"
#include "base/display_manager/display_manager.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> XComponentModelStatic::CreateFrameNode(int32_t nodeId, const std::optional<std::string>& id,
    XComponentType type, const std::optional<std::string>& libraryname)
{
    std::shared_ptr<InnerXComponentController> controller = nullptr;
    auto frameNode = FrameNode::CreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, nodeId, AceType::MakeRefPtr<XComponentPattern>(id, type, libraryname, controller));
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    if (layoutProperty) {
        layoutProperty->UpdateXComponentType(type);
    }
    return frameNode;
}

void XComponentModelStatic::SetXComponentController(FrameNode* frameNode,
    std::shared_ptr<InnerXComponentController> controller)
{
    CHECK_NULL_VOID(frameNode);
    auto xcPattern = AceType::DynamicCast<XComponentPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
#ifdef ACE_STATIC
    xcPattern->SetXComponentController(controller);
#endif
}
} // namespace OHOS::Ace::NG
