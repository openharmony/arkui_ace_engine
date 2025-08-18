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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RICH_EDITOR_PARAGRAPH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RICH_EDITOR_PARAGRAPH_H

#include "core/components_ng/render/adapter/txt_font_collection.h"
#include "core/components_ng/render/adapter/txt_paragraph.h"

namespace OHOS::Ace::NG {

class RichEditorParagraph : public TxtParagraph {
    DECLARE_ACE_TYPE(RichEditorParagraph, TxtParagraph);

public:
    RichEditorParagraph(const ParagraphStyle& paraStyle, std::shared_ptr<RSFontCollection> fontCollection)
        : TxtParagraph(paraStyle, fontCollection) {}

    Rosen::TextRectHeightStyle GetHeightStyle(bool needLineHighest) override;
    void Layout(float width) override;
    void ReLayout(float width, const ParagraphStyle& paraStyle, const std::vector<TextStyle>& textStyles) override;
    float GetHeight() override;

private:
    float height_ = 0.0f;
    float layoutWidth_ = 0.0f;

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorParagraph);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RICH_EDITOR_PARAGRAPH_H
 