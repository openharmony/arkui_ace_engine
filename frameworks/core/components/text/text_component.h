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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H

#include <string>

#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/text_style.h"
#include "core/pipeline/base/component_group.h"

namespace OHOS::Ace {

// A component can show text.
class ACE_EXPORT TextComponent : public ComponentGroup {
    DECLARE_ACE_TYPE(TextComponent, ComponentGroup);

public:
    explicit TextComponent(const std::string& data);
    ~TextComponent() override = default;

    RefPtr<RenderNode> CreateRenderNode() override;
    RefPtr<Element> CreateElement() override;

    const std::string& GetData() const
    {
        return data_;
    }

    void SetData(const std::string& data)
    {
        data_ = data;
    }

    const TextStyle& GetTextStyle() const
    {
        return textStyle_;
    }

    void SetTextStyle(const TextStyle& textStyle)
    {
        textStyle_ = textStyle;
    }

    void SetFocusColor(const Color& focusColor)
    {
        focusColor_ = focusColor;
    }

    const Color& GetFocusColor() const
    {
        return focusColor_;
    }

    void SetMaxWidthLayout(bool isMaxWidthLayout)
    {
        isMaxWidthLayout_ = isMaxWidthLayout;
    }

    bool GetMaxWidthLayout() const
    {
        return isMaxWidthLayout_;
    }

private:
    std::string data_;
    TextStyle textStyle_;
    Color focusColor_;
    bool isMaxWidthLayout_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_TEXT_COMPONENT_H
