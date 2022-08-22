/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H

#include <optional>

#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_layout_algorithm.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_paint_method.h"
#include "core/components_ng/pattern/button/button_paint_property.h"
#include "core/components_ng/pattern/button/button_position_property.h"
#include "core/components_ng/pattern/pattern.h"
namespace OHOS::Ace::NG {
class ButtonPattern : public Pattern {
    DECLARE_ACE_TYPE(ButtonPattern, Pattern);

public:
    ButtonPattern() = default;

    explicit ButtonPattern(const std::string& label) : label_(label) {}

    ~ButtonPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ButtonLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ButtonLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ButtonPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<ButtonPaintMethod>();
    }

    void OnModifyDone() override;

private:
    WeakPtr<FrameNode> frameNode_;
    std::optional<std::string> label_;
    ButtonType GetButtonType() const;
    std::unique_ptr<ButtonPositionProperty> buttonPositionProperty_;
    void OnAttachToFrameNode() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;

    void OnTouchDown();
    void OnTouchUp();

    RefPtr<TouchEventImpl> touchListener_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_BUTTON_PATTERN_H
