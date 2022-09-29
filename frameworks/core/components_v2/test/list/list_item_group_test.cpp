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
#include <vector>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/box/render_box.h"
#include "core/components_v2/list/list_item_generator.h"
#include "core/components_v2/list/render_list_item.h"
#include "core/components_v2/list/render_list_item_group.h"

namespace OHOS::Ace::V2 {
using namespace testing;
using namespace testing::ext;

class ListItemGroupTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
};

void ListItemGroupTest::SetUpTestCase() {}
void ListItemGroupTest::TearDownTestCase() {}
void ListItemGroupTest::SetUp() {}
void ListItemGroupTest::TearDown() {}

class ListItemGeneratorTest : public ListItemGenerator {
public:
    explicit ListItemGeneratorTest(size_t count) : totalCount_(count), items_(count)
    {
        for (size_t i = 0; i < count; i++) {
            items_[i] = AceType::DynamicCast<RenderListItem>(RenderListItem::Create());
        }
        header_ = RenderBox::Create();
        footer_ = RenderBox::Create();
    }
    RefPtr<RenderListItem> RequestListItem(size_t index) override
    {
        if (index >= totalCount_) {
            return nullptr;
        }
        return items_[index];
    }
    RefPtr<RenderNode> RequestListItemHeader() override
    {
        return header_;
    }
    RefPtr<RenderNode> RequestListItemFooter() override
    {
        return footer_;
    }
    void RecycleListItem(size_t index) override {}
    size_t TotalCount() override
    {
        return totalCount_;
    }
    size_t FindPreviousStickyListItem(size_t /* index */) override
    {
        return INVALID_INDEX;
    }

private:
    size_t totalCount_ = 0;
    std::vector<RefPtr<RenderListItem>> items_;
    RefPtr<RenderNode> header_;
    RefPtr<RenderNode> footer_;
};

/**
 * @tc.name: ListItemGroupItemGenerator001
 * @tc.desc: Test ListItemGroup Create and RequestListItem and RecycleListItem.
 * @tc.type: FUNC
 * @tc.require: issueI5NYZ3
 */
HWTEST_F(ListItemGroupTest, ListItemGroupItemGenerator001, TestSize.Level1)
{
    RefPtr<RenderNode> renderNode = RenderListItemGroup::Create();
    auto renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(renderNode);
    EXPECT_NE(renderListItemGroup, nullptr);
    auto generator = AceType::MakeRefPtr<ListItemGeneratorTest>(3);
    renderListItemGroup->RegisterItemGenerator(AceType::WeakClaim(AceType::RawPtr(generator)));
    auto item = renderListItemGroup->RequestListItem(0, false);
    EXPECT_NE(item, nullptr);
    item = renderListItemGroup->RequestListItem(4, false);
    EXPECT_EQ(item, nullptr);
    renderListItemGroup->RecycleListItem(1);
    size_t count = renderListItemGroup->TotalCount();
    EXPECT_EQ(count, 3);
}

/**
 * @tc.name: ListItemGroupSticky001
 * @tc.desc: Test ListItemGroup Create and RequestListItemHeader and RequestListItemFooter.
 * @tc.type: FUNC
 * @tc.require: issueI5NYYW
 */
HWTEST_F(ListItemGroupTest, ListItemGroupSticky001, TestSize.Level1)
{
    RefPtr<RenderNode> renderNode = RenderListItemGroup::Create();
    auto renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(renderNode);
    EXPECT_NE(renderListItemGroup, nullptr);
    auto generator = AceType::MakeRefPtr<ListItemGeneratorTest>(3);
    renderListItemGroup->RegisterItemGenerator(AceType::WeakClaim(AceType::RawPtr(generator)));
    auto header = renderListItemGroup->RequestListItemHeader();
    EXPECT_NE(header, nullptr);
    auto footer_ = renderListItemGroup->RequestListItemFooter();
    EXPECT_NE(footer_, nullptr);
}

} // namespace OHOS::Ace::V2
