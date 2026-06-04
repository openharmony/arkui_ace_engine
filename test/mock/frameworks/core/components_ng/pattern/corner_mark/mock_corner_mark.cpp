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

#include "core/components_ng/pattern/corner_mark/corner_mark.h"

namespace OHOS::Ace::NG {
int32_t CornerMark::ResponseShowCornerMarkEvent(const RefPtr<NG::FrameNode>& node, const std::string& command)
{
    (void)node;
    (void)command;
    return -1;
}

int32_t CornerMark::AddCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index)
{
    (void)node;
    (void)index;
    return -1;
}

int32_t CornerMark::UpdateCornerMarkNode(const RefPtr<NG::FrameNode>& node, const std::string& index)
{
    (void)node;
    (void)index;
    return -1;
}

int32_t CornerMark::RemoveCornerMarkNode(const RefPtr<NG::FrameNode>& node)
{
    (void)node;
    return -1;
}

void CornerMark::UpdateCornerMarkNodeLanguage(const RefPtr<NG::FrameNode>& node)
{
    (void)node;
}

void CornerMark::UpdateCornerMarkNodeColorMode(const RefPtr<NG::FrameNode>& node)
{
    (void)node;
}

void CornerMark::UpdateCornerMarkNodePosition(const RefPtr<NG::FrameNode>& node)
{
    (void)node;
}
} // namespace OHOS::Ace
