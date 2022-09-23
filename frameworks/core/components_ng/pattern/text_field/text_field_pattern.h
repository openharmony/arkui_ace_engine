/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H

#include "core/common/ime/text_input_action.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class TextFieldPattern : public Pattern {
    DECLARE_ACE_TYPE(TextFieldPattern, Pattern);

public:
    TextFieldPattern() = default;
    ~TextFieldPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return nullptr;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<TextFieldLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<TextFieldPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TextFieldLayoutAlgorithm>();
    }

    void OnModifyDone() override;

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(TextInputAction, TextInputAction)

private:
    void OnTextInputActionUpdate(TextInputAction value);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    RectF textRect_;
    RectF imageRect_;
    std::shared_ptr<RSParagraph> paragraph_;

    // TODO: add password icon info.
    RefPtr<ImageLoadingContext> ShowPasswordImageLoadingCtx_;
    RefPtr<ImageLoadingContext> HidePasswordImageLoadingCtx_;

    RefPtr<CanvasImage> ShowPasswordImageCanvas_;
    RefPtr<CanvasImage> HidePasswordImageCanvas_;

    ACE_DISALLOW_COPY_AND_MOVE(TextFieldPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_PATTERN_H