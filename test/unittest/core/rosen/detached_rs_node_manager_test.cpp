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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "render_service_client/core/ui/rs_canvas_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/detached_rs_node_manager.h"

#undef private
#undef protected

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class DetachedRsNodeManagerTest : public testing::Test {};

/**
 * @tc.name: DetachedRsNodeManagerTest001
 * @tc.desc: Test the basic func.
 * @tc.type: FUNC
 */
HWTEST_F(DetachedRsNodeManagerTest, DetachedRsNodeManagerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the member of the DetachedRsNodeManager.
     *@tc.expected: step1. The member of the DetachedRsNodeManager works right;
     */
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    EXPECT_NE(DetachedRsNodeManager::GetInstance().taskExecutor_, nullptr);

    auto rsUIDirector = OHOS::Rosen::RSUIDirector::Create();
    rsUIDirector->Init(true, true,  std::make_shared<Rosen::RSUIContext>());
    auto rsContext = rsUIDirector->GetRSUIContext();
    EXPECT_NE(rsContext, nullptr);
    auto rsNode = Rosen::RSCanvasNode::Create(false, false, rsContext);

    DetachedRsNodeManager::GetInstance().rsUIContexts_.emplace(rsContext.get());
    EXPECT_FALSE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_FALSE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
    DetachedRsNodeManager::GetInstance().RemoveRSUIContext(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->AttachFromUI();
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    DetachedRsNodeManager::GetInstance().FlushImplicitTransaction(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->DetachFromUI();
    DetachedRsNodeManager::GetInstance().PostDestructorTask(rsNode);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    rsContext->rsTransactionHandler_ = nullptr;
    DetachedRsNodeManager::GetInstance().FlushImplicitTransaction(rsContext);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());

    DetachedRsNodeManager::GetInstance().PostDestructorTask(nullptr);
    EXPECT_TRUE(DetachedRsNodeManager::GetInstance().rsUIContexts_.empty());
}
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_ROSEN_ROSEN_RENDER_CONTEXT_TEST_H
