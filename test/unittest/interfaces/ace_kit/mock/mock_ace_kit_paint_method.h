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

#ifndef TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_PAINT_METHOD_H
#define TEST_UNITTEST_INTERFACES_ACE_KIT_MOCK_MOCK_ACE_KIT_PAINT_METHOD_H

#include "ui/view/draw/node_paint_method.h"

namespace OHOS::Ace::Kit {
class MockAceKitPaintMethod final : public Ace::Kit::NodePaintMethod {
public:
    MockAceKitPaintMethod() = default;
    ~MockAceKitPaintMethod() override = default;

    RefPtr<ContentModifier> GetContentModifier() override;

private:
    RefPtr<ContentModifier> modifier_;
};
} // namespace OHOS::Ace::Kit

#endif
