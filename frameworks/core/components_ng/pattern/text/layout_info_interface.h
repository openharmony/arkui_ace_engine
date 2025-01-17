/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAYOUT_INFO_INTERFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAYOUT_INFO_INTERFACE_H
 
#include "core/components/common/properties/text_layout_info.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"

namespace OHOS::Ace::NG  {
class LayoutInfoInterface : public virtual AceType {
public:
    LayoutInfoInterface() = default;
    ~LayoutInfoInterface() = default;
    virtual WeakPtr<OHOS::Ace::NG::LayoutInfoInterface> GetLayoutInfoInterface()
    {
        return WeakClaim(this);
    }

    virtual size_t GetLineCount() const
    {
        return 0;
    }
 
    virtual bool DidExceedMaxLines() const
    {
        return false;
    }
 
    virtual TextLineMetrics GetLineMetrics(int32_t lineNumber)
    {
        return TextLineMetrics();
    }

    virtual std::vector<ParagraphManager::TextBox> GetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle)
    {
        return {};
    }

    virtual PositionWithAffinity GetGlyphPositionAtCoordinate(int32_t x, int32_t y)
    {
        PositionWithAffinity finalResult(0, TextAffinity::UPSTREAM);
        return finalResult;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_H