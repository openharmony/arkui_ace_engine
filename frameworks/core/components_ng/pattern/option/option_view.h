/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_OPTION_VIEW_H

#include <string>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
struct OptionValueInfo {
    std::string value;
    bool isPasteOption = false;
};

class ACE_EXPORT OptionView {
public:
    static RefPtr<FrameNode> CreateMenuOption(bool optionsHasIcon, const OptionValueInfo& value,
        const std::function<void()>& onClickFunc, int32_t index, const std::string& icon = "");
    static RefPtr<FrameNode> CreateMenuOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index);

    static RefPtr<FrameNode> CreateSelectOption(const SelectParam& param, int32_t index);

    static RefPtr<FrameNode> CreateText(const std::string& value, const RefPtr<FrameNode>& parent);
    static RefPtr<FrameNode> CreateIcon(const std::string& icon, const RefPtr<FrameNode>& parent,
        const RefPtr<FrameNode>& child = nullptr);
    static void CreatePasteButton(bool optionsHasIcon, const RefPtr<FrameNode>& option, const RefPtr<FrameNode>& row,
        const std::function<void()>& onClickFunc, const std::string& icon = "");
    static RefPtr<FrameNode> CreateSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& symbol,
        const RefPtr<FrameNode>& parent, const RefPtr<FrameNode>& child = nullptr,
        const std::optional<Dimension>& symbolUserDefinedIdealFontSize = std::nullopt);
    static void CreateOption(bool optionsHasIcon, const std::string& value, const std::string& icon,
        const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option, const std::function<void()>& onClickFunc);
    static void CreateOption(bool optionsHasIcon, std::vector<OptionParam>& params, int32_t index,
        const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& option);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OPTION_VIEW_H
