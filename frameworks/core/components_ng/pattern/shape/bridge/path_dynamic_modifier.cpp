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

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/path_model_ng.h"
#include "core/components_ng/pattern/shape/bridge/path_model_impl.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::PathModelImpl* GetPathModelImpl()
{
    static Framework::PathModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

#ifndef CROSS_PLATFORM
void CreatePathImpl()
{
    GetPathModelImpl()->Create();
}
#endif

} // namespace

void CreatePath()
{
    PathModelNG model;
    model.Create();
}

void SetPathCommands(ArkUINodeHandle node, ArkUI_CharPtr commands, void* resObjPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto commandsVal = std::string(commands);
    PathModelNG::SetCommands(frameNode, commandsVal);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("PathCommands");
    if (SystemProperties::ConfigChangePerform() && resObjPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjPtr));
        PathModelNG::SetCommands(frameNode, resObj);
    }
}

void ResetPathCommands(ArkUINodeHandle node)
{
    std::string outCommands = "";
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PathModelNG::SetCommands(frameNode, outCommands);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("PathCommands");
}

#ifndef CROSS_PLATFORM
void SetPathCommandsImpl(ArkUINodeHandle node, ArkUI_CharPtr commands, void* resObjPtr)
{
    GetPathModelImpl()->SetCommands(std::string(commands));
}

void ResetPathCommandsImpl(ArkUINodeHandle node)
{
    GetPathModelImpl()->SetCommands("");
}
#endif

namespace NodeModifier {

const ArkUIPathModifier* GetPathDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIPathModifier modifier = {
            .createPath = CreatePathImpl,
            .setPathCommands = SetPathCommandsImpl,
            .resetPathCommands = ResetPathCommandsImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPathModifier modifier = {
        .createPath = CreatePath,
        .setPathCommands = SetPathCommands,
        .resetPathCommands = ResetPathCommands,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIPathModifier* GetCJUIPathModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPathModifier modifier = {
        .setPathCommands = SetPathCommands,
        .resetPathCommands = ResetPathCommands,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
