/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version  2.0 (the "License");
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

#include <deque>
#include <memory>
#include <vector>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/rosen/testing_canvas.h"
#include "test/mock/frameworks/core/rosen/testing_draw_cmd_list.h"
#include "test/mock/frameworks/core/rosen/testing_recording_canvas.h"

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/custom_paint_util.h"
#include "core/components_ng/render/render_context.h"

#undef private
#undef protected

#include "base/json/json_util.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_WIDTH = 100;
constexpr int32_t TEST_HEIGHT = 200;
constexpr size_t MAX_DUMP_SIZE = 10;
} // namespace

class CanvasModifierTestNg : public testing::Test {
public:
    static void SetUpTestCase() { MockContainer::SetUp(); }
    static void TearDownTestCase() { MockContainer::TearDown(); }
    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: CanvasModifierConstructorTest001
 * @tc.desc: Test CanvasModifier constructor initializes members correctly
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierConstructorTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // needRender_ should be created with value true
    ASSERT_NE(modifier->needRender_, nullptr);
    EXPECT_TRUE(modifier->needRender_->Get());
    // needResetSurface_ defaults to false
    EXPECT_FALSE(modifier->needResetSurface_);
    // rsRecordingCanvas_ defaults to nullptr
    EXPECT_EQ(modifier->rsRecordingCanvas_, nullptr);
    // dumpInfos_ defaults to empty
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
}

/**
 * @tc.name: CanvasModifierOnDrawTest001
 * @tc.desc: Test CanvasModifier::onDraw with null rsRecordingCanvas_ - CHECK_NULL_VOID branch
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierOnDrawTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // rsRecordingCanvas_ is null by default - CHECK_NULL_VOID returns early
    Testing::TestingRecordingCanvas recordingCanvas(TEST_WIDTH, TEST_HEIGHT);
    DrawingContext context { recordingCanvas, static_cast<float>(TEST_WIDTH), static_cast<float>(TEST_HEIGHT) };
    modifier->onDraw(context);
    // No crash means the early return worked
    SUCCEED();
}

/**
 * @tc.name: CanvasModifierOnDrawTest002
 * @tc.desc: Test CanvasModifier::onDraw with non-null rsRecordingCanvas_ but null drawCmdList
 *           - CHECK_NULL_VOID(drawCmdList) branch
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierOnDrawTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // Set rsRecordingCanvas_ to a valid TestingRecordingCanvas
    auto recordingCanvas = std::make_shared<Testing::TestingRecordingCanvas>(TEST_WIDTH, TEST_HEIGHT);
    modifier->UpdateCanvas(recordingCanvas);
    ASSERT_NE(modifier->rsRecordingCanvas_, nullptr);
    // GetDrawCmdList() returns nullptr in mock → CHECK_NULL_VOID returns early
    Testing::TestingRecordingCanvas drawCanvas(TEST_WIDTH, TEST_HEIGHT);
    DrawingContext context { drawCanvas, static_cast<float>(TEST_WIDTH), static_cast<float>(TEST_HEIGHT) };
    modifier->onDraw(context);
    // No crash means the drawCmdList null check worked
    SUCCEED();
}

/**
 * @tc.name: CanvasModifierResetSurfaceTest001
 * @tc.desc: Test CanvasModifier::ResetSurface with null renderContext - CHECK_NULL_VOID branch
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierResetSurfaceTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // renderContext_ is null by default - CHECK_NULL_VOID returns early
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    // Null renderContext: needResetSurface_ is left unchanged (false).
    EXPECT_FALSE(modifier->needResetSurface_);
}

/**
 * @tc.name: CanvasModifierResetSurfaceTest002
 * @tc.desc: Test CanvasModifier::ResetSurface with non-null renderContext and
 *           needResetSurface_ = false - CHECK_EQUAL_VOID branch
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierResetSurfaceTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    modifier->SetRenderContext(AceType::WeakClaim(AceType::RawPtr(renderContext)));
    // needResetSurface_ is false by default
    EXPECT_FALSE(modifier->needResetSurface_);
    // CHECK_EQUAL_VOID(needResetSurface_, false) → returns early because needResetSurface_ == false
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    // needResetSurface_ == false: early return leaves it unchanged.
    EXPECT_FALSE(modifier->needResetSurface_);
}

/**
 * @tc.name: CanvasModifierResetSurfaceTest003
 * @tc.desc: Test CanvasModifier::ResetSurface with non-null renderContext and
 *           needResetSurface_ = true - full execution path
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierResetSurfaceTest003, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    modifier->SetRenderContext(AceType::WeakClaim(AceType::RawPtr(renderContext)));
    modifier->SetNeedResetSurface();
    EXPECT_TRUE(modifier->needResetSurface_);
    // Full path: renderContext->ResetSurface() + needResetSurface_ = false
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_FALSE(modifier->needResetSurface_);
}

/**
 * @tc.name: CanvasModifierGetDumpInfoTest001
 * @tc.desc: Test CanvasModifier::GetDumpInfo with empty dumpInfos_ - loop body not executed
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetDumpInfoTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto result = modifier->GetDumpInfo();
    // Only the "DrawCmdInfo:" header should be present
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.front(), "DrawCmdInfo:");
    // dumpInfos_ should be cleared after GetDumpInfo
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
}

/**
 * @tc.name: CanvasModifierGetDumpInfoTest002
 * @tc.desc: Test CanvasModifier::GetDumpInfo with non-empty dumpInfos_ - loop body executed
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetDumpInfoTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);

    CanvasModifierDump dump1;
    dump1.timestamp = 1000;
    dump1.width = 100;
    dump1.height = 200;
    dump1.opItemSize = 5;
    modifier->dumpInfos_.push_back(dump1);

    CanvasModifierDump dump2;
    dump2.timestamp = 2000;
    dump2.width = 300;
    dump2.height = 400;
    dump2.opItemSize = 10;
    modifier->dumpInfos_.push_back(dump2);

    auto result = modifier->GetDumpInfo();
    // Header + 2 entries
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.front(), "DrawCmdInfo:");
    // dumpInfos_ should be cleared after GetDumpInfo
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
}

/**
 * @tc.name: CanvasModifierGetDumpInfoTest003
 * @tc.desc: Test CanvasModifier::GetDumpInfo verifies dump info content format
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetDumpInfoTest003, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);

    CanvasModifierDump dump;
    dump.timestamp = 0;
    dump.width = 50;
    dump.height = 60;
    dump.opItemSize = 3;
    modifier->dumpInfos_.push_back(dump);

    auto result = modifier->GetDumpInfo();
    EXPECT_EQ(result.size(), 2);
    // Verify second element contains width and height
    auto it = result.begin();
    ++it;
    EXPECT_NE(it->find("50"), std::string::npos);
    EXPECT_NE(it->find("60"), std::string::npos);
    EXPECT_NE(it->find("3"), std::string::npos);
}

/**
 * @tc.name: CanvasModifierGetSimplifyDumpInfoTest001
 * @tc.desc: Test CanvasModifier::GetSimplifyDumpInfo with empty dumpInfos_ - loop not executed
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetSimplifyDumpInfoTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto array = JsonUtil::Create();
    ASSERT_NE(array, nullptr);
    modifier->GetSimplifyDumpInfo(array);
    EXPECT_EQ(array->GetArraySize(), 0);
}

/**
 * @tc.name: CanvasModifierGetSimplifyDumpInfoTest002
 * @tc.desc: Test CanvasModifier::GetSimplifyDumpInfo with non-empty dumpInfos_ - loop executed
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetSimplifyDumpInfoTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);

    CanvasModifierDump dump1;
    dump1.timestamp = 1000;
    dump1.width = 100;
    dump1.height = 200;
    dump1.opItemSize = 5;
    modifier->dumpInfos_.push_back(dump1);

    CanvasModifierDump dump2;
    dump2.timestamp = 2000;
    dump2.width = 300;
    dump2.height = 400;
    dump2.opItemSize = 10;
    modifier->dumpInfos_.push_back(dump2);

    auto array = JsonUtil::Create();
    ASSERT_NE(array, nullptr);
    modifier->GetSimplifyDumpInfo(array);
    EXPECT_EQ(array->GetArraySize(), 2);
}

/**
 * @tc.name: CanvasModifierGetSimplifyDumpInfoTest003
 * @tc.desc: Test CanvasModifier::GetSimplifyDumpInfo verifies JSON content keys
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetSimplifyDumpInfoTest003, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);

    CanvasModifierDump dump;
    dump.timestamp = 5000;
    dump.width = 800;
    dump.height = 600;
    dump.opItemSize = 7;
    modifier->dumpInfos_.push_back(dump);

    auto array = JsonUtil::Create();
    ASSERT_NE(array, nullptr);
    modifier->GetSimplifyDumpInfo(array);
    EXPECT_EQ(array->GetArraySize(), 1);
    auto item = array->GetArrayItem(0);
    ASSERT_NE(item, nullptr);
    EXPECT_TRUE(item->Contains("Timestamp"));
    EXPECT_TRUE(item->Contains("CanvasSize"));
    EXPECT_TRUE(item->Contains("CommandSize"));
}

/**
 * @tc.name: CanvasModifierSetRenderContextTest001
 * @tc.desc: Test CanvasModifier::SetRenderContext sets renderContext_ correctly
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierSetRenderContextTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    auto rawPtr = AceType::RawPtr(renderContext);
    modifier->SetRenderContext(AceType::WeakClaim(rawPtr));
    auto upgraded = modifier->renderContext_.Upgrade();
    ASSERT_NE(upgraded, nullptr);
    EXPECT_EQ(AceType::RawPtr(upgraded), rawPtr);
}

/**
 * @tc.name: CanvasModifierSetNeedResetSurfaceTest001
 * @tc.desc: Test CanvasModifier::SetNeedResetSurface sets needResetSurface_ to true
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierSetNeedResetSurfaceTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    EXPECT_FALSE(modifier->needResetSurface_);
    modifier->SetNeedResetSurface();
    EXPECT_TRUE(modifier->needResetSurface_);
}

/**
 * @tc.name: CanvasModifierMarkModifierDirtyTest001
 * @tc.desc: Test CanvasModifier::MarkModifierDirty with non-null needRender_ - toggles value
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierMarkModifierDirtyTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    ASSERT_NE(modifier->needRender_, nullptr);
    bool initialValue = modifier->needRender_->Get();
    modifier->MarkModifierDirty();
    EXPECT_NE(modifier->needRender_->Get(), initialValue);
    EXPECT_EQ(modifier->needRender_->Get(), !initialValue);
    // Toggle again to verify it flips back
    modifier->MarkModifierDirty();
    EXPECT_EQ(modifier->needRender_->Get(), initialValue);
}

/**
 * @tc.name: CanvasModifierMarkModifierDirtyTest002
 * @tc.desc: Test CanvasModifier::MarkModifierDirty with null needRender_ - CHECK_NULL_VOID branch
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierMarkModifierDirtyTest002, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    modifier->needRender_ = nullptr;
    // CHECK_NULL_VOID(needRender_) → returns early without crash
    modifier->MarkModifierDirty();
    // Null needRender_: early return leaves it unchanged.
    EXPECT_EQ(modifier->needRender_, nullptr);
}

/**
 * @tc.name: CanvasModifierUpdateCanvasTest001
 * @tc.desc: Test CanvasModifier::UpdateCanvas sets rsRecordingCanvas_ correctly
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierUpdateCanvasTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    EXPECT_EQ(modifier->rsRecordingCanvas_, nullptr);
    auto recordingCanvas = std::make_shared<Testing::TestingRecordingCanvas>(TEST_WIDTH, TEST_HEIGHT);
    modifier->UpdateCanvas(recordingCanvas);
    EXPECT_EQ(modifier->rsRecordingCanvas_, recordingCanvas);
}

/**
 * @tc.name: CanvasModifierOnDrawTest003
 * @tc.desc: Test CanvasModifier::onDraw after UpdateCanvas - drawCmdList is always null in mock
 *           so CHECK_NULL_VOID(drawCmdList) returns early. Verify dumpInfos_ is not modified.
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierOnDrawTest003, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto recordingCanvas = std::make_shared<Testing::TestingRecordingCanvas>(TEST_WIDTH, TEST_HEIGHT);
    modifier->UpdateCanvas(recordingCanvas);
    // Pre-populate dumpInfos_ to verify onDraw does NOT add entries
    // (because drawCmdList is null, onDraw returns before the dump logic)
    CanvasModifierDump dump;
    dump.timestamp = 1000;
    dump.width = 50;
    dump.height = 60;
    dump.opItemSize = 3;
    modifier->dumpInfos_.push_back(dump);
    size_t initialSize = modifier->dumpInfos_.size();

    Testing::TestingRecordingCanvas drawCanvas(TEST_WIDTH, TEST_HEIGHT);
    DrawingContext context { drawCanvas, static_cast<float>(TEST_WIDTH), static_cast<float>(TEST_HEIGHT) };
    modifier->onDraw(context);
    // dumpInfos_ should remain unchanged because onDraw returned early
    EXPECT_EQ(modifier->dumpInfos_.size(), initialSize);
}

/**
 * @tc.name: CanvasModifierGetDumpInfoTest004
 * @tc.desc: Test CanvasModifier::GetDumpInfo with MAX_SIZE entries to verify loop handles
 *           multiple items correctly and clears dumpInfos_ afterward
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetDumpInfoTest004, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // Fill dumpInfos_ to exactly MAX_DUMP_SIZE entries
    for (size_t i = 0; i < MAX_DUMP_SIZE; ++i) {
        CanvasModifierDump dump;
        dump.timestamp = static_cast<int64_t>(i);
        dump.width = static_cast<double>(i * 10);
        dump.height = static_cast<double>(i * 20);
        dump.opItemSize = i;
        modifier->dumpInfos_.push_back(dump);
    }
    EXPECT_EQ(modifier->dumpInfos_.size(), MAX_DUMP_SIZE);
    auto result = modifier->GetDumpInfo();
    // Header + MAX_DUMP_SIZE entries
    EXPECT_EQ(result.size(), MAX_DUMP_SIZE + 1);
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
}

/**
 * @tc.name: CanvasModifierGetSimplifyDumpInfoTest004
 * @tc.desc: Test CanvasModifier::GetSimplifyDumpInfo with MAX_SIZE entries
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetSimplifyDumpInfoTest004, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    for (size_t i = 0; i < MAX_DUMP_SIZE; ++i) {
        CanvasModifierDump dump;
        dump.timestamp = static_cast<int64_t>(i);
        dump.width = static_cast<double>(i * 10);
        dump.height = static_cast<double>(i * 20);
        dump.opItemSize = i;
        modifier->dumpInfos_.push_back(dump);
    }
    auto array = JsonUtil::Create();
    ASSERT_NE(array, nullptr);
    modifier->GetSimplifyDumpInfo(array);
    EXPECT_EQ(array->GetArraySize(), MAX_DUMP_SIZE);
}

/**
 * @tc.name: CanvasModifierResetSurfaceTest004
 * @tc.desc: Test CanvasModifier::ResetSurface called multiple times after SetNeedResetSurface
 *           Second call with needResetSurface_ = false returns early via CHECK_EQUAL_VOID
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierResetSurfaceTest004, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    modifier->SetRenderContext(AceType::WeakClaim(AceType::RawPtr(renderContext)));

    // First call: needResetSurface_ = true → full path
    modifier->SetNeedResetSurface();
    EXPECT_TRUE(modifier->needResetSurface_);
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_FALSE(modifier->needResetSurface_);

    // Second call: needResetSurface_ = false → CHECK_EQUAL_VOID returns early
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_FALSE(modifier->needResetSurface_);
}

/**
 * @tc.name: CanvasModifierGetDumpInfoClearTest
 * @tc.desc: Test CanvasModifier::GetDumpInfo clears dumpInfos_ even when called on already-empty state
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierGetDumpInfoClearTest, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);
    // First call: empty dumpInfos_
    auto result1 = modifier->GetDumpInfo();
    EXPECT_EQ(result1.size(), 1);
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
    // Second call: still empty, should still work
    auto result2 = modifier->GetDumpInfo();
    EXPECT_EQ(result2.size(), 1);
}

/**
 * @tc.name: CanvasModifierIntegrationTest001
 * @tc.desc: Integration test: SetRenderContext + SetNeedResetSurface + ResetSurface + GetDumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTestNg, CanvasModifierIntegrationTest001, TestSize.Level1)
{
    auto modifier = AceType::MakeRefPtr<CanvasModifier>();
    ASSERT_NE(modifier, nullptr);

    // Set up render context
    auto renderContext = AceType::MakeRefPtr<RenderContext>();
    modifier->SetRenderContext(AceType::WeakClaim(AceType::RawPtr(renderContext)));

    // Set need reset surface and call ResetSurface
    modifier->SetNeedResetSurface();
    modifier->ResetSurface(TEST_WIDTH, TEST_HEIGHT);
    EXPECT_FALSE(modifier->needResetSurface_);

    // Update canvas
    auto recordingCanvas = std::make_shared<Testing::TestingRecordingCanvas>(TEST_WIDTH, TEST_HEIGHT);
    modifier->UpdateCanvas(recordingCanvas);
    ASSERT_NE(modifier->rsRecordingCanvas_, nullptr);

    // Mark modifier dirty
    bool initialValue = modifier->needRender_->Get();
    modifier->MarkModifierDirty();
    EXPECT_NE(modifier->needRender_->Get(), initialValue);

    // Get dump info (empty at this point)
    auto result = modifier->GetDumpInfo();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(modifier->dumpInfos_.size(), 0);
}
} // namespace OHOS::Ace::NG
