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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/text_span/render_text_span.h"
#include "core/components/text_span/text_span_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class TextComponent;

class RenderText : public RenderNode {
    DECLARE_ACE_TYPE(RenderText, RenderNode);

public:
    ~RenderText() override;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void OnStatusChanged(RenderStatus renderStatus) override;

    void OnPaintFinish() override;

    const std::string& GetTextData() const
    {
        return textData_;
    }

    void SetTextData(const std::string& textData)
    {
        textData_ = textData;
    }

    void SetTextStyle(const TextStyle& textStyle)
    {
        textStyle_ = textStyle;
    }

    void MarkNeedMeasure()
    {
        needMeasure_ = true;
    }

    virtual double GetTextWidth() = 0;

protected:
    virtual Size Measure() = 0;
    virtual uint32_t GetTextLines() = 0;
    void UpdateAccessibilityText();

    template<class T>
    void UpdateIfChanged(T& update, const T& val)
    {
        if (update != val) {
            needMeasure_ = true;
            update = val;
        }
    }

    void CheckIfNeedMeasure(const RefPtr<TextComponent>& text);
    void ClearRenderObject() override;
    std::string textData_;
    TextStyle textStyle_;
    TextDirection textDirection_ = TextDirection::LTR;
    Color focusColor_;
    Color lostFocusColor_;
    double fontScale_ = 1.0;
    double dipScale_ = 1.0;
    bool isFocus_ = false;
    bool isMaxWidthLayout_ = false;
    bool needMeasure_ = true;
    bool isCallbackCalled_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_RENDER_TEXT_H
