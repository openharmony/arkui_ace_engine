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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_H

#include "core/components_ng/pattern/search/search_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_controller.h"

namespace OHOS::Ace {

class SearchModel {
public:
    static SearchModel* GetInstance();
    virtual ~SearchModel() = default;

    virtual RefPtr<TextFieldControllerBase> Create(const std::optional<std::string>& value,
        const std::optional<std::string>& placeholder, const std::optional<std::string>& icon);
    virtual void SetSearchButton(const std::string& text);
    virtual void SetPlaceholderColor(const Color& color);
    virtual void SetPlaceholderFont(const Font& font);
    virtual void SetTextFont(const Font& font);
    virtual void SetTextAlign(const TextAlign& textAlign);
    virtual void SetCopyOption(const CopyOptions& copyOptions);
    virtual void SetOnSubmit(std::function<void(const std::string&)>&& onSubmit);
    virtual void SetOnChange(std::function<void(const std::string&)>&& onChange);
    virtual void SetOnCopy(std::function<void(const std::string&)>&& func);
    virtual void SetOnCut(std::function<void(const std::string&)>&& func);
    virtual void SetOnPaste(std::function<void(const std::string&)>&& func);

private:
    static std::unique_ptr<SearchModel> instance_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_H
