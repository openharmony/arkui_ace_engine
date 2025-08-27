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

void SetOnFolderStateChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFolderStateChange = reinterpret_cast<std::function<void(const NG::FolderEventInfo&)>*>(callback);
        FolderStackModelNG::SetOnFolderStateChange(frameNode, std::move(*onFolderStateChange));
    } else {
        FolderStackModelNG::SetOnFolderStateChange(frameNode, nullptr);
    }
}

void ResetOnFolderStateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetOnFolderStateChange(frameNode, nullptr);
}

void SetOnHoverStatusChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onHoverStatusChange = reinterpret_cast<std::function<void(const NG::FolderEventInfo&)>*>(callback);
        FolderStackModelNG::SetOnHoverStatusChange(frameNode, std::move(*onHoverStatusChange));
    } else {
        FolderStackModelNG::SetOnHoverStatusChange(frameNode, nullptr);
    }
}

void ResetOnHoverStatusChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetOnHoverStatusChange(frameNode, nullptr);
}
} // namespace
namespace NodeModifier {
const ArkUIFolderStackModifier* GetFolderStackModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIFolderStackModifier modifier = {
        .setEnableAnimation = SetEnableAnimation,
        .resetEnableAnimation = ResetEnableAnimation,
        .setAutoHalfFold = SetAutoHalfFold,
        .resetAutoHalfFold = ResetAutoHalfFold,
        .setOnFolderStateChange = SetOnFolderStateChange,
        .resetOnFolderStateChange = ResetOnFolderStateChange,
        .setOnHoverStatusChange = SetOnHoverStatusChange,
        .resetOnHoverStatusChange = ResetOnHoverStatusChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIFolderStackModifier* GetCJUIFolderStackModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIFolderStackModifier modifier = {
        .setEnableAnimation = SetEnableAnimation,
        .resetEnableAnimation = ResetEnableAnimation,
        .setAutoHalfFold = SetAutoHalfFold,
        .resetAutoHalfFold = ResetAutoHalfFold,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
