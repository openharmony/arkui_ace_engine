/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node_creator.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> FrameNodeCreator::GetOrCreateTypedFrameNode(int32_t nodeId, const std::string& type)
{
    LOGD("GetOrCreateTypedFrameNode %{public}d %{public}s", nodeId, type.c_str());
    static const std::unordered_map<std::string, std::function<RefPtr<FrameNode>(const std::string&, int32_t)>>
        nodeCreate {
            { V2::TEXT_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
                } },
            { V2::COLUMN_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
                } },
            { V2::ROW_ETS_TAG,
                [](const std::string& type, int32_t nodeId) {
                    return FrameNode::GetOrCreateFrameNode(
                        type, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
                } },
        };
    
    auto iter = nodeCreate.find(type);
    if (iter != nodeCreate.end()) {
        return iter->second(type, nodeId);
    }
    
    return nullptr;
}

} // namespace OHOS::Ace::NG
