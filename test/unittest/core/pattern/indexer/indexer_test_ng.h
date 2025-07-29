/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_INDEXER_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_INDEXER_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#define protected public
#define private public
#include "core/components_ng/pattern/indexer/indexer_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
constexpr float INDEXER_HEIGHT = INDEXER_ITEM_SIZE * 26 + INDEXER_PADDING_TOP * 2;
constexpr float LONG_INDEXER_HEIGHT = INDEXER_ITEM_SIZE * INDEXER_THIRTEEN_CHARACTERS_CHECK + INDEXER_PADDING_TOP * 2;
constexpr float SHORT_INDEXER_HEIGHT = INDEXER_ITEM_SIZE * INDEXER_NINE_CHARACTERS_CHECK + INDEXER_PADDING_TOP * 2;

class IndexerTestNg : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void GetIndexer();

    IndexerModelNG CreateIndexer(std::vector<std::string> arrayValue, int32_t selected = 0);
    void OnPopupTouchDown(TouchType touchType);
    RefPtr<FrameNode> GetListItemNode(int32_t listItemIndex);
    void ListItemClick(int32_t clickIndex, TouchType touchType);

    std::vector<std::string> GetLongArrayValue()
    {
        return { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
            "U", "V", "W", "X", "Y", "Z" };
    }

    std::vector<std::string> GetMidArrayValue()
    {
        return { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M" };
    }

    std::vector<std::string> GetShortArrayValue()
    {
        return { "A", "B", "C", "D", "E", "F", "G", "H", "I" };
    }

    std::vector<std::string> GetAutoCollapseArrayValue()
    {
        return { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
    }

    std::vector<std::string> GetMidCollapseArrayValue()
    {
        return { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P" };
    }

    std::function<std::vector<std::string>(const int32_t selected)> GetPopupData()
    {
        return [](int32_t) -> std::vector<std::string> { return { "白", "别" }; };
    }

    std::function<std::vector<std::string>(const int32_t selected)> GetMorePopupData()
    {
        return [](int32_t) -> std::vector<std::string> { return { "白", "别", "吧", "不", "被" }; };
    }

    std::function<std::vector<std::string>(const int32_t selected)> GetMorePopupData2()
    {
        return [](int32_t) -> std::vector<std::string> { return { "白", "别", "吧", "不", "被", "包", "毕" }; };
    }

    RefPtr<FrameNode> frameNode_;
    RefPtr<IndexerPattern> pattern_;
    RefPtr<IndexerEventHub> eventHub_;
    RefPtr<IndexerLayoutProperty> layoutProperty_;
    RefPtr<IndexerPaintProperty> paintProperty_;
    RefPtr<IndexerAccessibilityProperty> accessibilityProperty_;
    RefPtr<IndexerTheme> indexerTheme_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_INDEXER_INDEXER_TEST_NG_H
