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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H

#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchModelNG : public OHOS::Ace::SearchModel {
public:
    RefPtr<TextFieldControllerBase> Create(const std::optional<std::string>& value,
        const std::optional<std::string>& placeholder, const std::optional<std::string>& icon) override;
    void SetSearchButton(const std::string& text) override;
    void SetPlaceholderColor(const Color& color) override;
    void SetPlaceholderFont(const Font& font) override;
    void SetTextFont(const Font& font) override;
    void SetTextAlign(const TextAlign& textAlign) override;
    void SetCopyOption(const CopyOptions& copyOptions) override;
    void SetOnSubmit(std::function<void(const std::string&)>&& onSubmit) override;
    void SetOnChange(std::function<void(const std::string&)>&& onChange) override;
    void SetOnCopy(std::function<void(const std::string&)>&& func) override;
    void SetOnCut(std::function<void(const std::string&)>&& func) override;
    void SetOnPaste(std::function<void(const std::string&)>&& func) override;

private:
    RefPtr<FrameNode> CreateTextField(const RefPtr<SearchNode>& parentNode,
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value);
    RefPtr<FrameNode> CreateImage(const RefPtr<SearchNode>& parentNode, const std::string& src);
    RefPtr<FrameNode> CreateCancelImage(const RefPtr<SearchNode>& parentNode);
    RefPtr<FrameNode> CreateButton(const RefPtr<SearchNode>& parentNode);
    RefPtr<FrameNode> CreateCancelButton(const RefPtr<SearchNode>& parentNode);
    RefPtr<SearchNode> GetOrCreateSearchNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H
