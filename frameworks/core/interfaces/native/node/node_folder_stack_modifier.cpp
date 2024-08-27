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
#include "core/interfaces/native/node/node_folder_stack_modifier.h"

#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
void SetEnableAnimation(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetEnableAnimation(frameNode, static_cast<bool>(value));
}

void ResetEnableAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetEnableAnimation(frameNode, true);
}

void SetAutoHalfFold(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetAutoHalfFold(frameNode, static_cast<bool>(value));
}

void ResetAutoHalfFold(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetAutoHalfFold(frameNode, true);
}
} // namespace
namespace NodeModifier {
const ArkUIFolderStackModifier* GetFolderStackModifier()
{
    static const ArkUIFolderStackModifier modifier = {
        SetEnableAnimation,
        ResetEnableAnimation,
        SetAutoHalfFold,
        ResetAutoHalfFold
    };
    return &modifier;
}

const CJUIFolderStackModifier* GetCJUIFolderStackModifier()
{
    static const CJUIFolderStackModifier modifier = {
        SetEnableAnimation,
        ResetEnableAnimation,
        SetAutoHalfFold,
        ResetAutoHalfFold
    };
    return &modifier;
}
}
}