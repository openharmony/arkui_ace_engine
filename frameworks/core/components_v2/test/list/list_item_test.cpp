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

#include <cstddef>
#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#include "core/components/box/render_box.h"
#include "core/components_v2/list/render_list_item.h"

namespace OHOS::Ace::V2 {
using namespace testing;
using namespace testing::ext;

class ListItemTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
};

void ListItemTest::SetUpTestCase() {}
void ListItemTest::TearDownTestCase() {}
void ListItemTest::SetUp() {}
void ListItemTest::TearDown() {}

/**
 * @tc.name: ListItemCreatorSwiper001
 * @tc.desc: Test ListItem Create and Get swipe start RenderNode and swipe end RenderNode.
 * @tc.type: FUNC
 * @tc.require: issueI5MX7J
 */
HWTEST_F(ListItemTest, ListItemCreatorSwiper001, TestSize.Level1)
{
    RefPtr<RenderNode> renderNode = RenderListItem::Create();
    auto renderListItem = AceType::DynamicCast<RenderListItem>(renderNode);
    EXPECT_NE(renderListItem, nullptr);
    renderListItem->RegisterGetChildCallback(
        [] (ListItemChildType type) -> RefPtr<RenderNode> {
            if (type == ListItemChildType::ITEM_CHILD) {
                return RenderBox::Create();
            }
            if (type == ListItemChildType::SWIPER_START) {
                return RenderBox::Create();
            }
            if (type == ListItemChildType::SWIPER_END) {
                return nullptr;
            }
            return nullptr;
        }
    );
    auto child = renderListItem->GetItemChildRenderNode();
    EXPECT_NE(child, nullptr);
    auto start = renderListItem->GetSwiperStartRenderNode();
    EXPECT_NE(start, nullptr);
    auto end = renderListItem->GetSwiperEndRenderNode();
    EXPECT_EQ(end, nullptr);
}
} // namespace OHOS::Ace::V2
