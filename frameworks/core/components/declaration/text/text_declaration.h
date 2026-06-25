/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_DECLARATION_H

#include "core/components/declaration/common/declaration.h"

namespace OHOS::Ace {

// Forward declaration
class TextStyle;

class ACE_FORCE_EXPORT TextDeclaration : public Declaration {
    DECLARE_ACE_TYPE(TextDeclaration, Declaration);

public:
    TextDeclaration() = default;
    ~TextDeclaration() override = default;

    void InitializeStyle() override;

    const std::string& GetData() const;
    void SetData(const std::string& data);
    const TextStyle& GetTextStyle() const;
    void SetTextStyle(const TextStyle& textStyle);

    const Color& GetFocusColor() const;
    void SetFocusColor(const Color& focusColor);

    const CopyOptions& GetCopyOption() const;
    void SetCopyOption(const CopyOptions& copyOptions);

    bool IsMaxWidthLayout() const;
    void SetIsMaxWidthLayout(bool isMaxWidthLayout);

    bool GetAutoMaxLines() const;
    void SetAutoMaxLines(bool autoMaxLines);

    bool IsChanged() const;
    void SetIsChanged(bool isChanged);

    bool HasSetTextFontSize() const;
    bool HasSetTextColor() const;

    static std::vector<Shadow> ParseTextShadow(const std::string& val, TextDeclaration& declaration);

protected:
    void InitSpecialized() override;
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;

private:
    template<class T>
    void CheckIsChanged(const T& update, const T& val)
    {
        if (update != val) {
            isChanged_ = true;
        }
    }

    bool isChanged_ = false;
    bool hasSetTextColor_ = false;
    bool hasSetTextFontSize_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_TEXT_TEXT_DECLARATION_H
