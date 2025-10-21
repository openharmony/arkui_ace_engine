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

#include <cstdint>

#include "gtest/gtest.h"
#include "search_base.h"

#include "core/components_ng/pattern/search/search_pattern.h"

namespace OHOS::Ace::NG {

class SearchTestThreeNg : public SearchBases {
public:
};

/**
 * @tc.name: ConvertCopyOptionsToString_None
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_None, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.None"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::None);
    EXPECT_EQ(result, "CopyOptions.None");
}

/**
 * @tc.name: ConvertCopyOptionsToString_InApp
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_InApp, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.InApp"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::InApp);
    EXPECT_EQ(result, "CopyOptions.InApp");
}

/**
 * @tc.name: ConvertCopyOptionsToString_Distributed
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_Distributed, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return "CopyOptions.Distributed"
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    auto result = pattern->ConvertCopyOptionsToString(CopyOptions::Distributed);
    EXPECT_EQ(result, "CopyOptions.Distributed");
}

/**
 * @tc.name: ConvertCopyOptionsToString_Default
 * @tc.desc: Test SearchPattern ConvertCopyOptionsToString
 * @tc.type: FUNC
 */
HWTEST_F(SearchTestThreeNg, ConvertCopyOptionsToString_Default, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Search node
     */
    SearchModelNG searchModelInstance;
    searchModelInstance.Create(DEFAULT_TEXT_U16, PLACEHOLDER_U16, SEARCH_SVG);
    auto searchNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(searchNode, nullptr);

    /**
     * @tc.steps: step2. Get SearchPattern and call ConvertCopyOptionsToString
     * @tc.expected: ConvertCopyOptionsToString return ""
     */
    auto pattern = searchNode->GetPattern<SearchPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t value = 10;
    auto result = pattern->ConvertCopyOptionsToString(static_cast<CopyOptions>(value));
    EXPECT_EQ(result, "");
}
} // namespace OHOS::Ace::NG