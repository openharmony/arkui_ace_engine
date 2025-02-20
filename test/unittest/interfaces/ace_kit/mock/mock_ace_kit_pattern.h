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

#ifndef TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_PATTERN_H
#define TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_PATTERN_H

#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_paint_method.h"
#include "ui/base/referenced.h"
#include "ui/view/frame_node.h"
#include "ui/view/layout/layout_algorithm.h"
#include "ui/view/pattern.h"

namespace OHOS::Ace::Kit {
class MockAceKitPattern : public Pattern {
    DECLARE_ACE_TYPE(MockAceKitPattern, Pattern);

public:
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    RefPtr<NodePaintMethod> CreateNodePaintMethod() override;
    bool IsAtomicNode() const override;
    RefPtr<Property> CreateProperty() override;
    bool OnDirtyLayoutrSwap(const Ace::NG::DirtySwapConfig& config) override;
    void OnModifyDone() override;

private:
    RefPtr<MockAceKitPaintMethod> paintMethod_;
};
} // namespace OHOS::Ace::Kit

#endif
