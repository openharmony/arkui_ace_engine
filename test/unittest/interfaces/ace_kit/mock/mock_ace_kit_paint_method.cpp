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

#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_paint_method.h"

#include "test/unittest/interfaces/ace_kit/mock/mock_ace_kit_content_modifier.h"

namespace OHOS::Ace::Kit {
RefPtr<ContentModifier> MockAceKitPaintMethod::GetContentModifier()
{
    if (!modifier_) {
        modifier_ = Ace::Referenced::MakeRefPtr<MockAceKitContentModifier>();
    }
    return modifier_;
}
} // namespace OHOS::Ace::Kit
