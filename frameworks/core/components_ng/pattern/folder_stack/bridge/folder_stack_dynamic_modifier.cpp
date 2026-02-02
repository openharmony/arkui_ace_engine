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
#include "core/interfaces/native/node/node_folder_stack_modifier.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int NUM_8 = 8;
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

ArkUINodeHandle CreateFolderStackFrameNode(ArkUI_Uint32 nodeId)
{
    return nullptr;
}

void SetEnableAnimation(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetEnableAnimation(frameNode, static_cast<bool>(value));
}

void ResetEnableAnimation(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetEnableAnimation(frameNode, true);
}

void SetAutoHalfFold(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetAutoHalfFold(frameNode, static_cast<bool>(value));
}

void ResetAutoHalfFold(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetAutoHalfFold(frameNode, true);
}

void SetOnFolderStateChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetOnFolderStateChange(frameNode, nullptr);
}

void SetOnHoverStatusChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
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
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    FolderStackModelNG::SetOnHoverStatusChange(frameNode, nullptr);
}

void CreateFolderStack(ArkUI_Uint32 size, ArkUI_CharPtr* upperId)
{
    static FolderStackModelNG model;
    if (size == 0 || upperId == nullptr) {
        std::vector<std::string> itemId;
        model.Create(itemId);
    } else {
        std::vector<std::string> upperItems;
        for (uint32_t i = 0; i < size; i++) {
            const char* upper = *(upperId + i);
            if (upper != nullptr) {
                upperItems.emplace_back(std::string(upper));
            }
        }
        model.Create(upperItems);
    }
}

void SetJsAlignContent(ArkUINodeHandle node, ArkUI_Int32 align)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Alignment alignment = Alignment::CENTER;
    switch (align) {
        case NUM_0:
            alignment = Alignment::TOP_LEFT;
            break;
        case NUM_1:
            alignment = Alignment::TOP_CENTER;
            break;
        case NUM_2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case NUM_3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case NUM_4:
            alignment = Alignment::CENTER;
            break;
        case NUM_5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case NUM_6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case NUM_7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case NUM_8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            alignment = Alignment::CENTER;
    }
    FolderStackModelNG::SetAlignment(frameNode, alignment);
}
} // namespace
namespace NodeModifier {
const ArkUIFolderStackModifier* GetFolderStackDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIFolderStackModifier modifier = {
        .createFolderStack = CreateFolderStack,
        .createFolderStackFrameNode = CreateFolderStackFrameNode,
        .setEnableAnimation = SetEnableAnimation,
        .resetEnableAnimation = ResetEnableAnimation,
        .setAutoHalfFold = SetAutoHalfFold,
        .resetAutoHalfFold = ResetAutoHalfFold,
        .setOnFolderStateChange = SetOnFolderStateChange,
        .resetOnFolderStateChange = ResetOnFolderStateChange,
        .setOnHoverStatusChange = SetOnHoverStatusChange,
        .resetOnHoverStatusChange = ResetOnHoverStatusChange,
        .setJsAlignContent = SetJsAlignContent,
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
