/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_ERROR_DECORATOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_ERROR_DECORATOR_H

#include "core/components_ng/pattern/common_text/counter_decorator.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ErrorDecorator : public TextComponentDecorator {
    DECLARE_ACE_TYPE(ErrorDecorator, TextComponentDecorator);
public:
    explicit ErrorDecorator(const RefPtr<FrameNode>& decoratedNode): TextComponentDecorator(decoratedNode) {}
    ~ErrorDecorator() override = default;
    void UpdateTextFieldMargin() override;
    float MeasureDecorator(float contentWidth, const std::u16string& textContent, bool showPlaceHolder) override;
    void LayoutDecorator() override;
    float GetBoundHeight() const override;
private:
    void BeforeLayout();
    void UpdateLayoutProperty();
    void UpdateErrorStyle();
    float CalculateErrorLayoutWidth();

};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_ERROR_DECORATOR_H
