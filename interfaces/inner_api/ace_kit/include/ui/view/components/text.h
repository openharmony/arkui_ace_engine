/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_TEXT_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_TEXT_H

#include "ui/base/geometry/dimension.h"
#include "ui/base/macros.h"
#include "ui/base/referenced.h"
#include "ui/properties/color.h"
#include "ui/view/view.h"

namespace OHOS::Ace::Kit {

class FrameNode;

// paint x, paint y, component width, component height.
using DrawCallback = std::function<bool(float, float, float, float)>;

class ACE_FORCE_EXPORT Text : public View {
public:
    static RefPtr<Text> Create(const std::u16string& content);
    static RefPtr<Text> Create(const RefPtr<FrameNode>& node);
    Text(const std::u16string& content);
    Text(const RefPtr<FrameNode>& node);
    ~Text() override;

    void SetTextColor(const Color& value);
    void SetFontSize(const Dimension& value);
    std::optional<void*> GetParagraph();
    void SetDrawCallback(DrawCallback&& drawCallback);
    std::u16string GetContent();
    void MarkRedraw();
};

} // namespace OHOS::Ace::Kit
#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_TEXT_H
