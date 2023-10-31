/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_LAYOUT_ALGORITHM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_LAYOUT_ALGORITHM_H

#include "core/components_ng/pattern/text_area/text_area_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
namespace OHOS::Ace::NG {
class TextAreaPattern : public TextFieldPattern {
    DECLARE_ACE_TYPE(TextAreaPattern, TextFieldPattern);

public:
    TextAreaPattern();
    ~TextAreaPattern() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TextAreaLayoutAlgorithm>();
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_AREA_TEXT_AREA_LAYOUT_ALGORITHM_H