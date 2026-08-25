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

#include <cmath>
#include <string>

#include "gtest/gtest.h"

#include "base/geometry/ng/rect_t.h"
#include "base/json/json_util.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/uisession_query/component_tree_query.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "interfaces/inner_api/ui_session/component_tree_query_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
// Minimal LazyForEachBuilder mock standing for a non dynamic-ArkTS frontend
// (static ArkTS / CJ / C-API): keeps the base data-extraction contract.
class MockUnsupportedFrontendBuilder : public LazyForEachBuilder {
    DECLARE_ACE_TYPE(MockUnsupportedFrontendBuilder, LazyForEachBuilder);

public:
    void ReleaseChildGroupById(const std::string& id) override {}
    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override {}
    void UnregisterDataChangeListener(V2::DataChangeListener* listener) override {}

protected:
    int32_t OnGetTotalCount() override
    {
        return 0;
    }
    std::pair<std::string, RefPtr<UINode>> OnGetChildByIndex(int32_t index,
        std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) override
    {
        return {};
    }
    std::pair<std::string, RefPtr<UINode>> OnGetChildByIndexNew(int32_t index,
        std::map<int32_t, LazyForEachChild>& cachedItems,
        std::unordered_map<std::string, LazyForEachCacheChild>& expiringItems) override
    {
        return {};
    }
    void OnExpandChildrenOnInitialInNG() override {}
    void NotifyDataChanged(size_t index, const RefPtr<UINode>& lazyForEachNode, bool isRebuild = true) override {}
    void NotifyDataDeleted(const RefPtr<UINode>& lazyForEachNode, size_t index, bool removeIds) override {}
    void NotifyDataAdded(size_t index) override {}
    void KeepRemovedItemInCache(LazyForEachChild node,
        std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) override {}
};

// Stands for the dynamic ArkTS JSLazyForEachBuilder contract.
class MockSupportedFrontendBuilder : public MockUnsupportedFrontendBuilder {
    DECLARE_ACE_TYPE(MockSupportedFrontendBuilder, MockUnsupportedFrontendBuilder);

public:
    bool IsDataExtractionSupported() const override
    {
        return true;
    }
    std::string GetDataByIndexAsJson(int32_t index, int32_t& errorCode) override
    {
        errorCode = static_cast<int32_t>(ComponentTreeQueryError::OK);
        return "{\"name\":\"item-" + std::to_string(index) + "\"}";
    }
};

int32_t QueryErrorCode(const std::string& resultJson)
{
    auto json = JsonUtil::ParseJsonString(resultJson);
    if (!json || !json->IsValid() || !json->Contains("errorCode")) {
        return -1;
    }
    return json->GetInt("errorCode");
}
} // namespace

class ComponentTreeQueryTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: ComponentTreeQueryCircleIntersection001
 * @tc.desc: FEAT-031 AC-4: circle/rect positive-area intersection semantics.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryCircleIntersection001, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 10.0f, 10.0f);
    // Circle center inside rect: positive-area overlap.
    EXPECT_TRUE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(5.0f, 5.0f, 1.0f, rect));
    // Circle center outside but overlapping.
    EXPECT_TRUE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(11.0f, 5.0f, 2.0f, rect));
    // Rect fully inside circle.
    EXPECT_TRUE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(5.0f, 5.0f, 20.0f, rect));
    // Tangent to an edge (distance == radius): not a hit.
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(13.0f, 5.0f, 3.0f, rect));
    // Tangent at a corner: not a hit.
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(-1.0f, -1.0f,
        std::sqrt(2.0f), rect));
    // Disjoint.
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(30.0f, 30.0f, 5.0f, rect));
    // Degenerate inputs.
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(5.0f, 5.0f, 0.0f, rect));
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(5.0f, 5.0f, -1.0f, rect));
    EXPECT_FALSE(ComponentTreeQuery::IsCircleIntersectRectPositiveArea(
        5.0f, 5.0f, 1.0f, RectF(0.0f, 0.0f, 0.0f, 10.0f)));
}

/**
 * @tc.name: ComponentTreeQueryRectIntersection002
 * @tc.desc: FEAT-031 AC-4: rect/rect positive-area intersection + normalization.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryRectIntersection002, TestSize.Level1)
{
    RectF query(0.0f, 0.0f, 10.0f, 10.0f);
    EXPECT_TRUE(ComponentTreeQuery::IsPositiveAreaRectIntersection(query, RectF(5.0f, 5.0f, 10.0f, 10.0f)));
    EXPECT_TRUE(ComponentTreeQuery::IsPositiveAreaRectIntersection(query, RectF(1.0f, 1.0f, 2.0f, 2.0f)));
    // Touching edges only: zero-area intersection, not a hit.
    EXPECT_FALSE(ComponentTreeQuery::IsPositiveAreaRectIntersection(query, RectF(10.0f, 0.0f, 5.0f, 5.0f)));
    EXPECT_FALSE(ComponentTreeQuery::IsPositiveAreaRectIntersection(query, RectF(20.0f, 20.0f, 5.0f, 5.0f)));

    // Diagonal point normalization.
    auto normalized = ComponentTreeQuery::NormalizeRect(10.0f, 10.0f, 0.0f, 4.0f);
    EXPECT_EQ(normalized.Left(), 0.0f);
    EXPECT_EQ(normalized.Top(), 4.0f);
    EXPECT_EQ(normalized.Right(), 10.0f);
    EXPECT_EQ(normalized.Bottom(), 10.0f);
}

/**
 * @tc.name: ComponentTreeQueryPointHit003
 * @tc.desc: FEAT-031 AC-1: point-in-rect with boundary inclusive + finite check.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryPointHit003, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 10.0f, 10.0f);
    EXPECT_TRUE(ComponentTreeQuery::IsPointInRectBoundaryInclusive(5.0f, 5.0f, rect));
    // Boundary points count as hit.
    EXPECT_TRUE(ComponentTreeQuery::IsPointInRectBoundaryInclusive(0.0f, 0.0f, rect));
    EXPECT_TRUE(ComponentTreeQuery::IsPointInRectBoundaryInclusive(10.0f, 10.0f, rect));
    EXPECT_FALSE(ComponentTreeQuery::IsPointInRectBoundaryInclusive(10.1f, 5.0f, rect));
    EXPECT_FALSE(ComponentTreeQuery::IsPointInRectBoundaryInclusive(-0.1f, 5.0f, rect));

    EXPECT_TRUE(ComponentTreeQuery::IsFinitePoint(1.0f, 2.0f));
    EXPECT_FALSE(ComponentTreeQuery::IsFinitePoint(std::nanf(""), 2.0f));
    EXPECT_FALSE(ComponentTreeQuery::IsFinitePoint(1.0f, HUGE_VALF));
}

/**
 * @tc.name: ComponentTreeQueryRegex004
 * @tc.desc: FEAT-031 AC-6/AC-8: regex validation and size limit.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryRegex004, TestSize.Level1)
{
    EXPECT_EQ(ComponentTreeQuery::CheckRegex("[a-z]+"),
        static_cast<int32_t>(ComponentTreeQueryError::OK));
    EXPECT_EQ(ComponentTreeQuery::CheckRegex(""), static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));
    EXPECT_EQ(ComponentTreeQuery::CheckRegex("[invalid"),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));
    EXPECT_EQ(ComponentTreeQuery::CheckRegex("*leading"),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));
    // Regex over 1024 bytes -> RESOURCE_LIMIT.
    std::string oversize(COMPONENT_TREE_QUERY_MAX_REGEX_BYTES + 1, 'a');
    EXPECT_EQ(ComponentTreeQuery::CheckRegex(oversize),
        static_cast<int32_t>(ComponentTreeQueryError::RESOURCE_LIMIT));
    // Exactly 1024 bytes of plain text is still a valid regex.
    std::string maxAllowed(COMPONENT_TREE_QUERY_MAX_REGEX_BYTES, 'a');
    EXPECT_EQ(ComponentTreeQuery::CheckRegex(maxAllowed),
        static_cast<int32_t>(ComponentTreeQueryError::OK));
}

/**
 * @tc.name: ComponentTreeQueryFrontend005
 * @tc.desc: FEAT-031 AC-2: builder frontend support contract. Base (static
 * ArkTS/CJ/C-API) builders report unsupported, dynamic ArkTS reports supported.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryFrontend005, TestSize.Level1)
{
    auto unsupported = AceType::MakeRefPtr<MockUnsupportedFrontendBuilder>();
    ASSERT_TRUE(unsupported);
    EXPECT_FALSE(unsupported->IsDataExtractionSupported());
    int32_t errorCode = 0;
    auto data = unsupported->GetDataByIndexAsJson(0, errorCode);
    EXPECT_TRUE(data.empty());
    EXPECT_EQ(errorCode, static_cast<int32_t>(ComponentTreeQueryError::UNSUPPORTED_FRONTEND));

    auto supported = AceType::MakeRefPtr<MockSupportedFrontendBuilder>();
    ASSERT_TRUE(supported);
    EXPECT_TRUE(supported->IsDataExtractionSupported());
    data = supported->GetDataByIndexAsJson(3, errorCode);
    EXPECT_EQ(errorCode, static_cast<int32_t>(ComponentTreeQueryError::OK));
    EXPECT_EQ(data, "{\"name\":\"item-3\"}");
}

/**
 * @tc.name: ComponentTreeQueryInvalidParams006
 * @tc.desc: FEAT-031 AC-6: invalid query parameters produce structured
 * INVALID_PARAMETER payloads before any tree access.
 */
HWTEST_F(ComponentTreeQueryTest, ComponentTreeQueryInvalidParams006, TestSize.Level1)
{
    ComponentTreeQueryRequest request;
    std::string resultJson;

    request.type = ComponentTreeQueryType::LAZY_FOREACH_DATA_BY_POINT;
    request.x = std::nanf("");
    request.y = 100.0f;
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));
    EXPECT_EQ(QueryErrorCode(resultJson), static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));

    request.type = ComponentTreeQueryType::NAVIGATION_CONTENT_BY_POINT;
    request.x = 10.0f;
    request.y = 10.0f;
    request.pattern = "[broken";
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));

    request.type = ComponentTreeQueryType::NODES_IN_CIRCLE;
    request.pattern.clear();
    request.radius = -1.0f;
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));

    request.type = ComponentTreeQueryType::NODES_IN_RECT;
    request.x = 0.0f;
    request.y = 0.0f;
    request.extraX = 0.0f;
    request.extraY = 10.0f; // zero width after normalization
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));

    request.extraX = 10.0f;
    request.extraY = std::nanf("");
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::INVALID_PARAMETER));

    // Oversize regex -> RESOURCE_LIMIT (AC-8).
    request.type = ComponentTreeQueryType::NAVIGATION_CONTENT_BY_POINT;
    request.extraY = 10.0f;
    request.pattern = std::string(COMPONENT_TREE_QUERY_MAX_REGEX_BYTES + 1, 'a');
    EXPECT_EQ(ComponentTreeQuery::Execute(request, resultJson),
        static_cast<int32_t>(ComponentTreeQueryError::RESOURCE_LIMIT));
}
} // namespace OHOS::Ace::NG
