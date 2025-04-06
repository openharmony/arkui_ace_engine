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

#ifndef TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_CONTENT_MODIFIER_H
#define TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_CONTENT_MODIFIER_H

#include <memory>
#include <optional>

#include "ui/base/geometry/dimension.h"
#include "ui/properties/linear_color.h"
#include "ui/rs_node.h"
#include "ui/view/draw/content_modifier.h"

namespace OHOS::Rosen {
template<typename T>
class RSProperty;
template<typename T>
class RSAnimatableProperty;
} // namespace OHOS::Rosen

namespace OHOS::Ace::Kit {
class MockAceKitContentModifier final : public ContentModifier {
    DECLARE_ACE_TYPE(MockAceKitContentModifier, ContentModifier);

public:
    MockAceKitContentModifier();
    ~MockAceKitContentModifier() = default;
    void OnDraw(const Ace::Kit::DrawingContext& context) override;
    void OnAttached() override;

    void SetFillColor(const Ace::Color& color);
    void SetRingWidth(const Ace::Dimension& width);

private:
    std::shared_ptr<Rosen::RSAnimatableProperty<Ace::LinearColor>> fillColor_;
    std::shared_ptr<Rosen::RSProperty<float>> ringWidth_;
    Ace::Color initialColor_;
    bool attached_ = false;
};
} // namespace OHOS::Customize

#endif
