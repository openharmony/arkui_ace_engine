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

#include "test/unittest/core/pattern/test_ng.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SCROLLABLE_ITEM_POOL_MAX_SIZE = 10;
}

class ScrollableItemTestNg : public TestNG {};

/**
 * @tc.name: MaybeReleaseAfterDeleterDelete001
 * @tc.desc: Test MaybeRelease when ScrollableItemPool deallocates the item directly.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableItemTestNg, MaybeReleaseAfterDeleterDelete001, TestSize.Level1)
{
    auto enableScrollableItemPool = SystemProperties::enableScrollableItemPool_;
    SystemProperties::enableScrollableItemPool_ = true;
    auto& itemPool = ScrollableItemPool::GetInstance();
    const auto tag = "maybeReleaseAfterDeleterDelete";
    auto pattern = AceType::MakeRefPtr<Pattern>();

    for (int32_t index = 0; index < SCROLLABLE_ITEM_POOL_MAX_SIZE; ++index) {
        auto item = new ScrollableItem(tag, index, pattern, false);
        itemPool.Deallocate(item);
    }
    auto item = new ScrollableItem(tag, SCROLLABLE_ITEM_POOL_MAX_SIZE, pattern, false);
    item->SetMaybeRelease(false);
    item->SetCustomDeleter(ObjectPoolDeleter<ScrollableItem> { &itemPool });

    auto maybeRelease = item->MaybeRelease();

    EXPECT_FALSE(maybeRelease);
    SystemProperties::enableScrollableItemPool_ = enableScrollableItemPool;
}
} // namespace OHOS::Ace::NG
