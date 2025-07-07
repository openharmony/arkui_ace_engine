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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEXT_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEXT_EFFECT_H

#include <unordered_map>
#include <vector>

#include "ui/base/referenced.h"

#include "base/memory/ace_type.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
enum class TextEffectAttribute {
    FLIP_DIRECTION,
    BLUR_ENABLE,
};

class Paragraph;

class TextEffect : public virtual AceType {
    DECLARE_ACE_TYPE(NG::TextEffect, AceType);

public:
    static RefPtr<TextEffect> CreateTextEffect();

    virtual int UpdateEffectConfig(TextFlipDirection direction, bool enableBlur) = 0;
    virtual int AppendTypography(const std::vector<RefPtr<Paragraph>>& paragraphs) = 0;
    virtual void RemoveTypography(const std::vector<RefPtr<Paragraph>>& paragraphs) = 0;
    virtual int UpdateTypography(std::vector<std::pair<RefPtr<Paragraph>, RefPtr<Paragraph>>>& paragraphs) = 0;
    virtual void StartEffect(RSCanvas& canvas, double x, double y) = 0;
    virtual void StopEffect() = 0;
    virtual void NoEffect(RSCanvas& canvas, double x, double y) = 0;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEXT_EFFECT_H
