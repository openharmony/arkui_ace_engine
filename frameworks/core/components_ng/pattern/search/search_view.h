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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_VIEW_H

#include <optional>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/text_field/text_field_controller.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchView {
public:
    static RefPtr<TextFieldController> Create(
        std::optional<std::string>& value, std::optional<std::string>& placeholder, std::optional<std::string>& icon);
    static void SetSearchButton(const std::string& text);
    static void SetPlaceholderColor(const Color& color);
    static void SetPlaceholderFont(const Font& font);
    static void SetTextFont(const Font& font);
    static void SetCopyOption(const CopyOptions& copyOptions);

    static void SetOnSubmit(ChangeAndSubmitEvent&& onSubmit);
    static void SetOnChange(ChangeAndSubmitEvent&& onChange);

    static void SetOnCopy(std::function<void(const std::string&)>&& func);
    static void SetOnCut(std::function<void(const std::string&)>&& func);
    static void SetOnPaste(std::function<void(const std::string&)>&& func);

private:
    static RefPtr<FrameNode> CreateTextField(const RefPtr<SearchNode>& parentNode,
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value);
    static RefPtr<FrameNode> CreateImage(const RefPtr<SearchNode>& parentNode, const std::string& src);
    static RefPtr<FrameNode> CreateButtonWithLabel(const RefPtr<SearchNode>& parentNode, const std::string& label);
    static RefPtr<SearchNode> GetOrCreateSearchNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_VIEW_H
