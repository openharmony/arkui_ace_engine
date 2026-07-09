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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "core/components_ng/manager/content_change_manager/content_change_manager.h"
#undef private
#undef protected

#include "core/components_ng/pattern/page_translate/page_translate_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"

#include <functional>
#include <string>
#include <utility>

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_TRANSLATE_NODE_ID = 300;
constexpr int32_t TEST_ANOTHER_TRANSLATE_NODE_ID = 301;
constexpr int32_t INVALID_TRANSLATE_NODE_ID = -1;
constexpr int64_t SNAPSHOT_TRANSLATE_VERSION = 0;
constexpr int64_t INVALID_TRANSLATE_VERSION = -1;
constexpr int64_t TEST_FIRST_VERSION = 1;
constexpr int64_t TEST_SECOND_VERSION = 2;
constexpr int64_t TEST_DUPLICATE_VERSION = -1;
constexpr char TEST_SOURCE_TEXT[] = "source text";
constexpr char TEST_CHANGED_SOURCE_TEXT[] = "changed source text";
constexpr char TEST_TRANSLATE_RESULT[] = "translate result";
constexpr char EMPTY_TRANSLATE_TEXT[] = "";

class TestPageTranslateNode : public PageTranslateNode {
    DECLARE_ACE_TYPE(TestPageTranslateNode, PageTranslateNode);

public:
    TestPageTranslateNode(int32_t nodeId, std::string text) : nodeId_(nodeId), text_(std::move(text)) {}
    ~TestPageTranslateNode() override = default;

    int32_t GetPageTranslateNodeId() const override
    {
        return nodeId_;
    }

    std::string GetPageTranslateTextForReport() const override
    {
        return text_;
    }

    bool ApplyPageTranslateResult(const std::string& result, int64_t version) override
    {
        ++applyCount_;
        lastResult_ = result;
        lastVersion_ = version;
        return applyResult_;
    }

    void ResetPageTranslate() override
    {
        ++resetCount_;
    }

    void SetText(std::string text)
    {
        text_ = std::move(text);
    }

    int32_t applyCount_ = 0;
    int32_t resetCount_ = 0;
    int64_t lastVersion_ = INVALID_TRANSLATE_VERSION;
    std::string lastResult_;
    bool applyResult_ = true;

private:
    int32_t nodeId_ = INVALID_TRANSLATE_NODE_ID;
    std::string text_;
};

class TestTranslatePattern : public Pattern, public PageTranslateNode {
    DECLARE_ACE_TYPE(TestTranslatePattern, Pattern, PageTranslateNode);

public:
    TestTranslatePattern(int32_t nodeId, std::string text) : nodeId_(nodeId), text_(std::move(text)) {}
    ~TestTranslatePattern() override = default;

    int32_t GetPageTranslateNodeId() const override
    {
        return nodeId_;
    }

    std::string GetPageTranslateTextForReport() const override
    {
        return text_;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return nullptr;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return nullptr;
    }

private:
    int32_t nodeId_ = INVALID_TRANSLATE_NODE_ID;
    std::string text_;
};

WeakPtr<PageTranslateNode> MakeWeakPageTranslateNode(const RefPtr<TestPageTranslateNode>& node)
{
    return WeakPtr<PageTranslateNode>(AceType::DynamicCast<PageTranslateNode>(node));
}

struct TranslateVersionTestData {
    const char* text;
    int64_t expectedVersion;
};

struct ApplyTranslateResultTestData {
    int32_t nodeId;
    const char* result;
    int64_t version;
};
} // namespace

class ContentChangeManagerTranslateTestNg : public testing::Test {};

/**
 * @tc.name: ContentChangeManagerTranslateTest001
 * @tc.desc: Test StartTextTranslateReport enables translate state and clears stale version cache.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest001, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    contentChangeMgr->textTranslateActive_ = false;
    contentChangeMgr->translateTextVersions_[TEST_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };

    contentChangeMgr->StartTextTranslateReport();

    EXPECT_TRUE(contentChangeMgr->IsTextTranslateActive());
    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());
}

/**
 * @tc.name: ContentChangeManagerTranslateTest002
 * @tc.desc: Test UpdateTranslateVersionIfNeeded keeps duplicate text stable and increments changed text.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest002, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    const TranslateVersionTestData testData[] = {
        { TEST_SOURCE_TEXT, TEST_FIRST_VERSION },
        { TEST_SOURCE_TEXT, TEST_DUPLICATE_VERSION },
        { TEST_CHANGED_SOURCE_TEXT, TEST_SECOND_VERSION },
        { TEST_CHANGED_SOURCE_TEXT, TEST_DUPLICATE_VERSION },
    };

    for (const auto& item : testData) {
        EXPECT_EQ(contentChangeMgr->UpdateTranslateVersionIfNeeded(TEST_TRANSLATE_NODE_ID, item.text),
            item.expectedVersion);
    }

    auto versionIter = contentChangeMgr->translateTextVersions_.find(TEST_TRANSLATE_NODE_ID);
    ASSERT_NE(versionIter, contentChangeMgr->translateTextVersions_.end());
    EXPECT_EQ(versionIter->second.second, TEST_SECOND_VERSION);
}

/**
 * @tc.name: ContentChangeManagerTranslateTest003
 * @tc.desc: Test StopTextTranslateReport disables translate state and clears caches.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest003, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    contentChangeMgr->textTranslateActive_ = true;
    contentChangeMgr->translateTextVersions_[TEST_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };
    contentChangeMgr->translateTextSnapshotVersions_[TEST_ANOTHER_TRANSLATE_NODE_ID] = { 0,
        SNAPSHOT_TRANSLATE_VERSION };

    contentChangeMgr->StopTextTranslateReport();

    EXPECT_FALSE(contentChangeMgr->IsTextTranslateActive());
    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotVersions_.empty());
}

/**
 * @tc.name: ContentChangeManagerTranslateTest004
 * @tc.desc: Test ReportTranslateTextNode ignores inactive translation and empty text.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest004, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    WeakPtr<PageTranslateNode> emptyNode;

    contentChangeMgr->ReportTranslateTextNode(emptyNode, TEST_SOURCE_TEXT);
    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());

    contentChangeMgr->StartTextTranslateReport();
    contentChangeMgr->ReportTranslateTextNode(emptyNode, EMPTY_TRANSLATE_TEXT);
    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());

    contentChangeMgr->ReportTranslateTextNode(emptyNode, TEST_SOURCE_TEXT);
    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());

    contentChangeMgr->ReportTranslateTextSnapshotNode(emptyNode, EMPTY_TRANSLATE_TEXT);
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotVersions_.empty());

    contentChangeMgr->ReportTranslateTextSnapshotNode(emptyNode, TEST_SOURCE_TEXT);
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotVersions_.empty());
}

/**
 * @tc.name: ContentChangeManagerTranslateTest005
 * @tc.desc: Test ApplyTranslateResult rejects invalid input and missing version cache.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest005, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    contentChangeMgr->translateTextVersions_[TEST_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };
    const ApplyTranslateResultTestData testData[] = {
        { INVALID_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT, TEST_FIRST_VERSION },
        { TEST_TRANSLATE_NODE_ID, EMPTY_TRANSLATE_TEXT, TEST_FIRST_VERSION },
        { TEST_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT, INVALID_TRANSLATE_VERSION },
        { TEST_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT, TEST_SECOND_VERSION },
        { TEST_ANOTHER_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT, TEST_FIRST_VERSION },
    };

    for (const auto& item : testData) {
        EXPECT_FALSE(contentChangeMgr->ApplyTranslateResult(item.nodeId, item.result, item.version));
    }

    EXPECT_FALSE(contentChangeMgr->ApplyTranslateResult(TEST_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT,
        TEST_FIRST_VERSION));
}

/**
 * @tc.name: ContentChangeManagerTranslateTest008
 * @tc.desc: Test ApplyTranslateResult applies cached snapshot result and rejects stale source text.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest008, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto translateNode = AceType::MakeRefPtr<TestPageTranslateNode>(TEST_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    contentChangeMgr->translateTextSnapshotNodes_.emplace(MakeWeakPageTranslateNode(translateNode));
    contentChangeMgr->translateTextSnapshotVersions_[TEST_TRANSLATE_NODE_ID] = {
        std::hash<std::string> {}(TEST_SOURCE_TEXT), TEST_FIRST_VERSION
    };

    EXPECT_TRUE(contentChangeMgr->ApplyTranslateResult(TEST_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT,
        TEST_FIRST_VERSION));
    EXPECT_EQ(translateNode->applyCount_, 1);
    EXPECT_EQ(translateNode->lastResult_, TEST_TRANSLATE_RESULT);
    EXPECT_EQ(translateNode->lastVersion_, TEST_FIRST_VERSION);

    translateNode->SetText(TEST_CHANGED_SOURCE_TEXT);
    EXPECT_FALSE(contentChangeMgr->ApplyTranslateResult(TEST_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT,
        TEST_FIRST_VERSION));
    EXPECT_EQ(translateNode->applyCount_, 1);

    auto continuousNode = AceType::MakeRefPtr<TestPageTranslateNode>(TEST_ANOTHER_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    contentChangeMgr->translateTextNodes_.emplace(MakeWeakPageTranslateNode(continuousNode));
    contentChangeMgr->translateTextVersions_[TEST_ANOTHER_TRANSLATE_NODE_ID] = {
        std::hash<std::string> {}(TEST_SOURCE_TEXT), TEST_SECOND_VERSION
    };

    EXPECT_TRUE(contentChangeMgr->ApplyTranslateResult(TEST_ANOTHER_TRANSLATE_NODE_ID, TEST_TRANSLATE_RESULT,
        TEST_SECOND_VERSION));
    EXPECT_EQ(continuousNode->applyCount_, 1);
    EXPECT_EQ(continuousNode->lastVersion_, TEST_SECOND_VERSION);
}

/**
 * @tc.name: ContentChangeManagerTranslateTest006
 * @tc.desc: Test ResetTranslateTextNode clears all versions or a selected version without registered nodes.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest006, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto translateNode = AceType::MakeRefPtr<TestPageTranslateNode>(TEST_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    auto snapshotNode = AceType::MakeRefPtr<TestPageTranslateNode>(TEST_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    auto anotherNode = AceType::MakeRefPtr<TestPageTranslateNode>(TEST_ANOTHER_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    contentChangeMgr->translateTextNodes_.emplace(MakeWeakPageTranslateNode(translateNode));
    contentChangeMgr->translateTextNodes_.emplace(MakeWeakPageTranslateNode(anotherNode));
    contentChangeMgr->translateTextSnapshotNodes_.emplace(MakeWeakPageTranslateNode(snapshotNode));
    contentChangeMgr->translateTextVersions_[TEST_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };
    contentChangeMgr->translateTextVersions_[TEST_ANOTHER_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };
    contentChangeMgr->translateTextSnapshotVersions_[TEST_TRANSLATE_NODE_ID] = { 0, SNAPSHOT_TRANSLATE_VERSION };
    contentChangeMgr->translateTextSnapshotVersions_[TEST_ANOTHER_TRANSLATE_NODE_ID] = { 0,
        SNAPSHOT_TRANSLATE_VERSION };

    contentChangeMgr->ResetTranslateTextNode(TEST_TRANSLATE_NODE_ID);

    EXPECT_EQ(contentChangeMgr->translateTextVersions_.count(TEST_TRANSLATE_NODE_ID), 0U);
    EXPECT_EQ(contentChangeMgr->translateTextVersions_.count(TEST_ANOTHER_TRANSLATE_NODE_ID), 1U);
    EXPECT_EQ(contentChangeMgr->translateTextSnapshotVersions_.count(TEST_TRANSLATE_NODE_ID), 0U);
    EXPECT_EQ(contentChangeMgr->translateTextSnapshotVersions_.count(TEST_ANOTHER_TRANSLATE_NODE_ID), 1U);
    EXPECT_EQ(translateNode->resetCount_, 1);
    EXPECT_EQ(snapshotNode->resetCount_, 1);
    EXPECT_EQ(anotherNode->resetCount_, 0);

    contentChangeMgr->ResetTranslateTextNode();

    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextVersions_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotNodes_.empty());
    EXPECT_TRUE(contentChangeMgr->translateTextSnapshotVersions_.empty());
    EXPECT_EQ(anotherNode->resetCount_, 1);
}

/**
 * @tc.name: ContentChangeManagerTranslateTest007
 * @tc.desc: Test ResetTranslateTextNode removes expired translate node records.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest007, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    WeakPtr<PageTranslateNode> emptyNode;
    contentChangeMgr->translateTextNodes_.emplace(emptyNode);
    contentChangeMgr->translateTextVersions_[TEST_TRANSLATE_NODE_ID] = { 0, TEST_FIRST_VERSION };

    contentChangeMgr->ResetTranslateTextNode(TEST_TRANSLATE_NODE_ID);

    EXPECT_TRUE(contentChangeMgr->translateTextNodes_.empty());
    EXPECT_EQ(contentChangeMgr->translateTextVersions_.count(TEST_TRANSLATE_NODE_ID), 0U);
}

/**
 * @tc.name: ContentChangeManagerTranslateTest009
 * @tc.desc: Test ReportTranslateTextFrameNode records a tracked frame node without global element scanning.
 * @tc.type: FUNC
 */
HWTEST_F(ContentChangeManagerTranslateTestNg, ContentChangeManagerTranslateTest009, TestSize.Level1)
{
    auto contentChangeMgr = AceType::MakeRefPtr<ContentChangeManager>();
    ASSERT_NE(contentChangeMgr, nullptr);
    auto pattern = AceType::MakeRefPtr<TestTranslatePattern>(TEST_TRANSLATE_NODE_ID, TEST_SOURCE_TEXT);
    auto frameNode = AceType::MakeRefPtr<FrameNode>("translateNode", TEST_TRANSLATE_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);

    contentChangeMgr->StartTextTranslateReport();
    contentChangeMgr->ReportTranslateTextFrameNode(WeakPtr<FrameNode>(frameNode));

    EXPECT_EQ(contentChangeMgr->translateTextNodes_.size(), 1U);
    auto versionIter = contentChangeMgr->translateTextVersions_.find(TEST_TRANSLATE_NODE_ID);
    ASSERT_NE(versionIter, contentChangeMgr->translateTextVersions_.end());
    EXPECT_EQ(versionIter->second.second, TEST_FIRST_VERSION);

    contentChangeMgr->StartTextTranslateSnapshotReport();
    contentChangeMgr->ReportTranslateTextFrameNode(WeakPtr<FrameNode>(frameNode), false);

    EXPECT_EQ(contentChangeMgr->translateTextSnapshotNodes_.size(), 1U);
    auto snapshotVersionIter = contentChangeMgr->translateTextSnapshotVersions_.find(TEST_TRANSLATE_NODE_ID);
    ASSERT_NE(snapshotVersionIter, contentChangeMgr->translateTextSnapshotVersions_.end());
    EXPECT_EQ(snapshotVersionIter->second.second, contentChangeMgr->translateTextSnapshotVersion_);
}
} // namespace OHOS::Ace::NG
