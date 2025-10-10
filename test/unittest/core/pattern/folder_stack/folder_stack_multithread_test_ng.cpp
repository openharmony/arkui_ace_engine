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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <atomic>
#include <vector>
#include <future>

#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/folder_stack/folder_stack_test_ng.h"

#include "core/components_ng/pattern/folder_stack/folder_stack_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class FolderStackMultiThreadTestNg : public FolderStackTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    RefPtr<FolderStackPattern> CreateFolderStackPattern();
    RefPtr<MockPipelineContext> CreateMockPipelineContext();
    void SetupMockSystemProperties(bool isBigFold = false, bool isSmallFold = false);
    void ResetMockSystemProperties();
    
private:
    RefPtr<FolderStackPattern> pattern_;
    RefPtr<MockPipelineContext> mockPipelineContext_;
};

void FolderStackMultiThreadTestNg::SetUpTestSuite()
{
    FolderStackTestNg::SetUpTestSuite();
}

void FolderStackMultiThreadTestNg::TearDownTestSuite()
{
    FolderStackTestNg::TearDownTestSuite();
}

void FolderStackMultiThreadTestNg::SetUp()
{
    FolderStackTestNg::SetUp();
    pattern_ = CreateFolderStackPattern();
    mockPipelineContext_ = CreateMockPipelineContext();
}

void FolderStackMultiThreadTestNg::TearDown()
{
    pattern_ = nullptr;
    mockPipelineContext_ = nullptr;
    ResetMockSystemProperties();
    FolderStackTestNg::TearDown();
}

RefPtr<FolderStackPattern> FolderStackMultiThreadTestNg::CreateFolderStackPattern()
{
    auto folderStackNode = CreateFolder();
    EXPECT_NE(folderStackNode, nullptr);
    auto pattern = folderStackNode->GetPattern<FolderStackPattern>();
    EXPECT_NE(pattern, nullptr);
    return pattern;
}

RefPtr<MockPipelineContext> FolderStackMultiThreadTestNg::CreateMockPipelineContext()
{
    auto mockPipelineContext = AceType::MakeRefPtr<MockPipelineContext>();
    EXPECT_NE(mockPipelineContext, nullptr);
    return mockPipelineContext;
}

void FolderStackMultiThreadTestNg::SetupMockSystemProperties(bool isBigFold, bool isSmallFold)
{
    // Note: The current mock implementation always returns false for IsBigFoldProduct and IsSmallFoldProduct
    // This is a limitation of the current mock system, but we can still test the logic paths
}

void FolderStackMultiThreadTestNg::ResetMockSystemProperties()
{
    // Reset any mock system properties if needed
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread001
 * @tc.desc: Test OnAttachToMainTreeMultiThread with valid host and pipeline
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnAttachToMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with valid host and pipeline
     * @tc.expected: Pattern is created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    
    /**
     * @tc.steps: step2. Set up mock pipeline context
     * @tc.expected: Pipeline context is set successfully
     */
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step3. Set up expectation for callback registration
     * @tc.expected: RegisterFoldStatusChangedCallback is called once
     */
    const int32_t CALLBACK_ID_VALID = 123;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_VALID));
    
    pattern_->OnAttachToMainTreeMultiThread();
    
    /**
     * @tc.steps: step4. Verify callback ID is stored
     * @tc.expected: Callback ID is stored correctly
     */
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadWithNullHost001
 * @tc.desc: Test OnAttachToMainTreeMultiThread with null host
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnAttachToMainTreeMultiThreadWithNullHost001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and set host to null
     * @tc.expected: Pattern is created but host is null
     */
    auto folderStackNode = CreateFolder();
    ASSERT_NE(folderStackNode, nullptr);
    auto pattern = folderStackNode->GetPattern<FolderStackPattern>();
    ASSERT_NE(pattern, nullptr);
    
    // Simulate null host by creating a pattern without proper host setup
    auto emptyPattern = AceType::MakeRefPtr<FolderStackPattern>();
    
    /**
     * @tc.steps: step2. Call OnAttachToMainTreeMultiThread with null host
     * @tc.expected: Function returns early without crash
     */
    emptyPattern->OnAttachToMainTreeMultiThread();
    
    /**
     * @tc.steps: step3. Verify no callback ID is stored
     * @tc.expected: No callback ID is stored
     */
    EXPECT_FALSE(emptyPattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadWithNullPipeline001
 * @tc.desc: Test OnAttachToMainTreeMultiThread with null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnAttachToMainTreeMultiThreadWithNullPipeline001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with valid host but null pipeline
     * @tc.expected: Pattern and host are created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    
    /**
     * @tc.steps: step2. Set pipeline context to null
     * @tc.expected: Pipeline context is null
     */
    host->SetContext(nullptr);
    
    /**
     * @tc.steps: step3. Call OnAttachToMainTreeMultiThread
     * @tc.expected: Function returns early without crash
     */
    pattern_->OnAttachToMainTreeMultiThread();
    
    /**
     * @tc.steps: step4. Verify no callback ID is stored
     * @tc.expected: No callback ID is stored
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnAttachToMainTreeMultiThreadWithNonFoldDevice001
 * @tc.desc: Test OnAttachToMainTreeMultiThread with non-fold device
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnAttachToMainTreeMultiThreadWithNonFoldDevice001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with valid host and pipeline
     * @tc.expected: Pattern is created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Set up mock system properties for non-fold device
     * @tc.expected: Both IsBigFoldProduct and IsSmallFoldProduct return false
     */
    SetupMockSystemProperties(false, false);
    
    /**
     * @tc.steps: step3. Call OnAttachToMainTreeMultiThread
     * @tc.expected: Function returns early due to non-fold device check
     */
    pattern_->OnAttachToMainTreeMultiThread();
    
    /**
     * @tc.steps: step4. Verify no callback ID is stored
     * @tc.expected: No callback ID is stored for non-fold device
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread with valid callback ID
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Register callback first
     * @tc.expected: Callback is registered successfully
     */
    const int32_t CALLBACK_ID_VALID = 456;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_VALID));
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    
    /**
     * @tc.steps: step3. Set up expectation for callback unregistration
     * @tc.expected: UnRegisterFoldStatusChangedCallback is called once
     */
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(CALLBACK_ID_VALID))
        .Times(1);
    
    /**
     * @tc.steps: step4. Call OnDetachFromMainTreeMultiThread
     * @tc.expected: Callback is unregistered successfully
     */
    pattern_->OnDetachFromMainTreeMultiThread();
    
    /**
     * @tc.steps: step5. Verify callback ID is cleared
     * @tc.expected: Callback ID is cleared
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadWithNullHost001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread with null host
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromMainTreeMultiThreadWithNullHost001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with null host
     * @tc.expected: Pattern is created but host is null
     */
    auto emptyPattern = AceType::MakeRefPtr<FolderStackPattern>();
    
    /**
     * @tc.steps: step2. Call OnDetachFromMainTreeMultiThread with null host
     * @tc.expected: Function returns early without crash
     */
    emptyPattern->OnDetachFromMainTreeMultiThread();
    
    /**
     * @tc.steps: step3. Verify no callback operations are performed
     * @tc.expected: No callback operations are performed
     */
    EXPECT_FALSE(emptyPattern->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadWithNullPipeline001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread with null pipeline
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromMainTreeMultiThreadWithNullPipeline001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with valid host but null pipeline
     * @tc.expected: Pattern and host are created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(nullptr);
    
    /**
     * @tc.steps: step2. Call OnDetachFromMainTreeMultiThread
     * @tc.expected: Function returns early without crash
     */
    pattern_->OnDetachFromMainTreeMultiThread();
    
    /**
     * @tc.steps: step3. Verify no callback operations are performed
     * @tc.expected: No callback operations are performed
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThreadWithoutCallback001
 * @tc.desc: Test OnDetachFromMainTreeMultiThread without registered callback
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromMainTreeMultiThreadWithoutCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Verify no callback is registered initially
     * @tc.expected: No callback ID is stored
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
    
    /**
     * @tc.steps: step3. Call OnDetachFromMainTreeMultiThread without registered callback
     * @tc.expected: Function completes without attempting to unregister
     */
    pattern_->OnDetachFromMainTreeMultiThread();
    
    /**
     * @tc.steps: step4. Verify no callback operations are performed
     * @tc.expected: No callback operations are performed
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnAttachToFrameNodeMultiThread001
 * @tc.desc: Test OnAttachToFrameNodeMultiThread basic functionality
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnAttachToFrameNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     * @tc.expected: Pattern is created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    
    /**
     * @tc.steps: step2. Call OnAttachToFrameNodeMultiThread
     * @tc.expected: Function completes without crash (no-op function)
     */
    pattern_->OnAttachToFrameNodeMultiThread();
    
    /**
     * @tc.steps: step3. Verify function is thread-unsafe no-op
     * @tc.expected: No state changes occur
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread001
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread with valid node
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromFrameNodeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and frame node
     * @tc.expected: Pattern and frame node are created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto frameNode = CreateFolder();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Call OnDetachFromFrameNodeMultiThread with valid node
     * @tc.expected: Function completes without crash (no-op function)
     */
    pattern_->OnDetachFromFrameNodeMultiThread(frameNode.GetRawPtr());
    
    /**
     * @tc.steps: step3. Verify function is thread-unsafe no-op
     * @tc.expected: No state changes occur
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThreadWithNullptr001
 * @tc.desc: Test OnDetachFromFrameNodeMultiThread with nullptr
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, OnDetachFromFrameNodeMultiThreadWithNullptr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern
     * @tc.expected: Pattern is created successfully
     */
    ASSERT_NE(pattern_, nullptr);
    
    /**
     * @tc.steps: step2. Call OnDetachFromFrameNodeMultiThread with nullptr
     * @tc.expected: Function completes without crash (no-op function)
     */
    pattern_->OnDetachFromFrameNodeMultiThread(nullptr);
    
    /**
     * @tc.steps: step3. Verify function is thread-unsafe no-op
     * @tc.expected: No state changes occur
     */
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: RepeatedAttachToMainTreeMultiThread001
 * @tc.desc: Test repeated calls to OnAttachToMainTreeMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, RepeatedAttachToMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Set up expectations for multiple callback registrations
     * @tc.expected: RegisterFoldStatusChangedCallback is called multiple times
     */
    const int32_t CALLBACK_ID_1 = 111;
    const int32_t CALLBACK_ID_2 = 222;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_1))
        .WillOnce(Return(CALLBACK_ID_2));
    
    /**
     * @tc.steps: step3. Call OnAttachToMainTreeMultiThread multiple times
     * @tc.expected: Each call registers a new callback
     */
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: RepeatedDetachFromMainTreeMultiThread001
 * @tc.desc: Test repeated calls to OnDetachFromMainTreeMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, RepeatedDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern and register callback first
     * @tc.expected: Pattern is set up and callback is registered
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    const int32_t CALLBACK_ID_VALID = 333;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_VALID));
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    
    /**
     * @tc.steps: step2. Set up expectation for callback unregistration
     * @tc.expected: UnRegisterFoldStatusChangedCallback is called once
     */
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(CALLBACK_ID_VALID))
        .Times(1);
    
    /**
     * @tc.steps: step3. Call OnDetachFromMainTreeMultiThread multiple times
     * @tc.expected: First call unregisters callback, subsequent calls are no-ops
     */
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
    
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: DetachThenAttachMainTreeMultiThread001
 * @tc.desc: Test calling OnDetachFromMainTreeMultiThread then OnAttachToMainTreeMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, DetachThenAttachMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Call OnDetachFromMainTreeMultiThread first (without registered callback)
     * @tc.expected: Function completes without error
     */
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
    
    /**
     * @tc.steps: step3. Set up expectation for callback registration
     * @tc.expected: RegisterFoldStatusChangedCallback is called
     */
    const int32_t CALLBACK_ID_VALID = 444;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_VALID));
    
    /**
     * @tc.steps: step4. Call OnAttachToMainTreeMultiThread
     * @tc.expected: Callback is registered successfully
     */
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: AttachDetachCycleMainTreeMultiThread001
 * @tc.desc: Test multiple attach-detach cycles
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, AttachDetachCycleMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Set up expectations for multiple cycles
     * @tc.expected: RegisterFoldStatusChangedCallback and UnRegisterFoldStatusChangedCallback are called multiple times
     */
    const int32_t CALLBACK_ID_1 = 555;
    const int32_t CALLBACK_ID_2 = 666;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_1))
        .WillOnce(Return(CALLBACK_ID_2));
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(CALLBACK_ID_1))
        .Times(1);
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(CALLBACK_ID_2))
        .Times(1);
    
    /**
     * @tc.steps: step3. Perform multiple attach-detach cycles
     * @tc.expected: Each cycle works correctly
     */
    // First cycle
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
    
    // Second cycle
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: FrameNodeAttachDetachCombination001
 * @tc.desc: Test combination of frame node and main tree operations
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, FrameNodeAttachDetachCombination001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern and frame node
     * @tc.expected: Pattern and frame node are set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    auto frameNode = CreateFolder();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set up expectation for main tree callback registration
     * @tc.expected: RegisterFoldStatusChangedCallback is called
     */
    const int32_t CALLBACK_ID_VALID = 777;
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillOnce(Return(CALLBACK_ID_VALID));
    
    /**
     * @tc.steps: step3. Perform combination of operations
     * @tc.expected: All operations complete without interference
     */
    pattern_->OnAttachToFrameNodeMultiThread();
    pattern_->OnAttachToMainTreeMultiThread();
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId());
    
    pattern_->OnDetachFromFrameNodeMultiThread(frameNode.GetRawPtr());
    EXPECT_TRUE(pattern_->HasFoldStatusChangedCallbackId()); // Main tree callback still registered
    
    /**
     * @tc.steps: step4. Set up expectation for callback unregistration
     * @tc.expected: UnRegisterFoldStatusChangedCallback is called
     */
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(CALLBACK_ID_VALID))
        .Times(1);
    
    pattern_->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern_->HasFoldStatusChangedCallbackId());
}

/**
 * @tc.name: ConcurrentAttachDetachMainTreeMultiThread001
 * @tc.desc: Test concurrent calls to OnAttachToMainTreeMultiThread and OnDetachFromMainTreeMultiThread
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, ConcurrentAttachDetachMainTreeMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Set up expectations for concurrent operations
     * @tc.expected: RegisterFoldStatusChangedCallback may be called multiple times
     */
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return(888));
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return());
    
    /**
     * @tc.steps: step3. Launch concurrent operations
     * @tc.expected: Operations complete without deadlock or crash
     */
    std::atomic<bool> testCompleted{false};
    std::vector<std::future<void>> futures;
    
    // Launch multiple attach operations
    for (int i = 0; i < 5; ++i) {
        futures.push_back(std::async(std::launch::async, [this, &testCompleted]() {
            while (!testCompleted.load()) {
                pattern_->OnAttachToMainTreeMultiThread();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }));
    }
    
    // Launch multiple detach operations
    for (int i = 0; i < 5; ++i) {
        futures.push_back(std::async(std::launch::async, [this, &testCompleted]() {
            while (!testCompleted.load()) {
                pattern_->OnDetachFromMainTreeMultiThread();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }));
    }
    
    /**
     * @tc.steps: step4. Let operations run for a short time
     * @tc.expected: No crashes or deadlocks occur
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    testCompleted.store(true);
    
    /**
     * @tc.steps: step5. Wait for all operations to complete
     * @tc.expected: All operations complete successfully
     */
    for (auto& future : futures) {
        future.wait();
    }
}

/**
 * @tc.name: ConcurrentFrameNodeOperationsMultiThread001
 * @tc.desc: Test concurrent frame node operations
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, ConcurrentFrameNodeOperationsMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern and frame nodes
     * @tc.expected: Pattern and frame nodes are set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto frameNode1 = CreateFolder();
    auto frameNode2 = CreateFolder();
    ASSERT_NE(frameNode1, nullptr);
    ASSERT_NE(frameNode2, nullptr);
    
    /**
     * @tc.steps: step2. Launch concurrent frame node operations
     * @tc.expected: Operations complete without crash (no-op functions)
     */
    std::atomic<bool> testCompleted{false};
    std::vector<std::future<void>> futures;
    
    // Launch multiple attach operations
    for (int i = 0; i < 3; ++i) {
        futures.push_back(std::async(std::launch::async, [this, &testCompleted]() {
            while (!testCompleted.load()) {
                pattern_->OnAttachToFrameNodeMultiThread();
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }));
    }
    
    // Launch multiple detach operations with different nodes
    futures.push_back(std::async(std::launch::async, [this, frameNode1, &testCompleted]() {
        while (!testCompleted.load()) {
            pattern_->OnDetachFromFrameNodeMultiThread(frameNode1.GetRawPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }));
    
    futures.push_back(std::async(std::launch::async, [this, frameNode2, &testCompleted]() {
        while (!testCompleted.load()) {
            pattern_->OnDetachFromFrameNodeMultiThread(frameNode2.GetRawPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }));
    
    /**
     * @tc.steps: step3. Let operations run for a short time
     * @tc.expected: No crashes occur
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    testCompleted.store(true);
    
    /**
     * @tc.steps: step4. Wait for all operations to complete
     * @tc.expected: All operations complete successfully
     */
    for (auto& future : futures) {
        future.wait();
    }
}

/**
 * @tc.name: CallbackRegistrationThreadSafety001
 * @tc.desc: Test thread safety of callback registration and unregistration
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, CallbackRegistrationThreadSafety001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern with valid host and pipeline
     * @tc.expected: Pattern is set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    
    /**
     * @tc.steps: step2. Set up expectations for thread-safe operations
     * @tc.expected: Mock calls are configured for concurrent access
     */
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return(999));
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return());
    
    /**
     * @tc.steps: step3. Launch concurrent callback registration/unregistration
     * @tc.expected: Operations are thread-safe
     */
    std::atomic<int> attachCount{0};
    std::atomic<int> detachCount{0};
    std::atomic<bool> testCompleted{false};
    std::vector<std::future<void>> futures;
    
    // Launch attach operations
    for (int i = 0; i < 3; ++i) {
        futures.push_back(std::async(std::launch::async, [this, &attachCount, &testCompleted]() {
            while (!testCompleted.load()) {
                pattern_->OnAttachToMainTreeMultiThread();
                attachCount.fetch_add(1);
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        }));
    }
    
    // Launch detach operations
    for (int i = 0; i < 3; ++i) {
        futures.push_back(std::async(std::launch::async, [this, &detachCount, &testCompleted]() {
            while (!testCompleted.load()) {
                pattern_->OnDetachFromMainTreeMultiThread();
                detachCount.fetch_add(1);
                std::this_thread::sleep_for(std::chrono::milliseconds(2));
            }
        }));
    }
    
    /**
     * @tc.steps: step4. Let operations run and verify thread safety
     * @tc.expected: No crashes or data corruption occur
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    testCompleted.store(true);
    
    /**
     * @tc.steps: step5. Wait for all operations to complete
     * @tc.expected: All operations complete successfully
     */
    for (auto& future : futures) {
        future.wait();
    }
    
    /**
     * @tc.steps: step6. Verify operations were performed
     * @tc.expected: Both attach and detach operations were executed
     */
    EXPECT_GT(attachCount.load(), 0);
    EXPECT_GT(detachCount.load(), 0);
}

/**
 * @tc.name: MixedOperationsThreadSafety001
 * @tc.desc: Test thread safety of mixed main tree and frame node operations
 * @tc.type: FUNC
 */
HWTEST_F(FolderStackMultiThreadTestNg, MixedOperationsThreadSafety001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up pattern, host, pipeline, and frame nodes
     * @tc.expected: All components are set up successfully
     */
    ASSERT_NE(pattern_, nullptr);
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    host->SetContext(mockPipelineContext_);
    auto frameNode = CreateFolder();
    ASSERT_NE(frameNode, nullptr);
    
    /**
     * @tc.steps: step2. Set up expectations for mixed operations
     * @tc.expected: Mock calls are configured
     */
    EXPECT_CALL(*mockPipelineContext_, RegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return(1000));
    EXPECT_CALL(*mockPipelineContext_, UnRegisterFoldStatusChangedCallback(_))
        .WillRepeatedly(Return());
    
    /**
     * @tc.steps: step3. Launch mixed concurrent operations
     * @tc.expected: All types of operations run concurrently
     */
    std::atomic<bool> testCompleted{false};
    std::vector<std::future<void>> futures;
    
    // Main tree operations
    futures.push_back(std::async(std::launch::async, [this, &testCompleted]() {
        while (!testCompleted.load()) {
            pattern_->OnAttachToMainTreeMultiThread();
            pattern_->OnDetachFromMainTreeMultiThread();
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
    }));
    
    // Frame node operations
    futures.push_back(std::async(std::launch::async, [this, frameNode, &testCompleted]() {
        while (!testCompleted.load()) {
            pattern_->OnAttachToFrameNodeMultiThread();
            pattern_->OnDetachFromFrameNodeMultiThread(frameNode.GetRawPtr());
            std::this_thread::sleep_for(std::chrono::milliseconds(3));
        }
    }));
    
    // Mixed operations
    futures.push_back(std::async(std::launch::async, [this, frameNode, &testCompleted]() {
        while (!testCompleted.load()) {
            pattern_->OnAttachToMainTreeMultiThread();
            pattern_->OnAttachToFrameNodeMultiThread();
            pattern_->OnDetachFromFrameNodeMultiThread(frameNode.GetRawPtr());
            pattern_->OnDetachFromMainTreeMultiThread();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }));
    
    /**
     * @tc.steps: step4. Let mixed operations run
     * @tc.expected: No crashes or deadlocks occur
     */
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    testCompleted.store(true);
    
    /**
     * @tc.steps: step5. Wait for all operations to complete
     * @tc.expected: All operations complete successfully
     */
    for (auto& future : futures) {
        future.wait();
    }
}

} // namespace OHOS::Ace::NG
