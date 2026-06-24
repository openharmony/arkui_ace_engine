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
#include "base/utils/system_properties.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/select/bridge/select_custom_modifier.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/components_ng/pattern/select/select_pattern.h"
namespace OHOS::Ace::NG {

void SetChangeValue(FrameNode* frameNode, ArkUI_Int32 index, const std::string& convValue)
{
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetChangeValue(frameNode, index, convValue);
}

void UpdateSelectedOptionFontFromPattern(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    CHECK_NULL_VOID(host);
    selectPattern->UpdateSelectedOptionFontFromPattern(host);
}

void UpdateOptionFontFromPattern(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    CHECK_NULL_VOID(host);
    selectPattern->UpdateOptionFontFromPattern(host);
}

void ShowSelectMenu(const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto selectPattern = frameNode->GetPattern<SelectPattern>();
    CHECK_NULL_VOID(selectPattern);
    selectPattern->ShowSelectMenu();
}

void SetBuilderFunc(FrameNode* frameNode, SelectMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetBuilderFunc(frameNode, std::move(makeFunc));
}
namespace NodeModifier {

const ArkUISelectModifier* GetSelectDynamicModifier()
{
    static const ArkUISelectModifier modifier = {

    };
    return &modifier;
}

const ArkUISelectCustomModifier* GetSelectCustomModifier()
{
    static const ArkUISelectCustomModifier modifier = {
        .setChangeValue = SetChangeValue,
        .updateSelectedOptionFontFromPattern = UpdateSelectedOptionFontFromPattern,
        .updateOptionFontFromPattern = UpdateOptionFontFromPattern,
        .showSelectMenu = ShowSelectMenu,
        .setBuilderFunc = SetBuilderFunc,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
