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

#include <gtest/gtest.h>

// NOLINTBEGIN
#define private public
#define protected public
#include "core/components_ng/pattern/smart_layout/smart_layout_engine_loader.h"
#undef protected
#undef private
// NOLINTEND

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SmartLayoutEngineLoaderFakeNode final : public ISmartLayoutNode {
public:
    void SetLayoutType(SmartLayoutType type) override {}
    SmartLayoutType GetLayoutType() const override
    {
        return SmartLayoutType::UNKNOWN;
    }
    void SetFixedSizeConstraints(double width, double height) override {}
    bool SolveLayout() override
    {
        return true;
    }
    void SyncData() override {}
    void CreateChildrenFromInfos(const std::vector<ChildLayoutInfo>& infos) override {}
    const std::vector<std::shared_ptr<ISmartLayoutNode>>& GetChildren() const override
    {
        return children_;
    }
    void ApplyColumnConstraints() override {}
    void ApplyRowConstraints() override {}
    void ApplyGeneralConstraints() override {}
    void SetBoundingBox(const SmartLayoutRect& box) override
    {
        boundingBox_ = box;
    }
    const SmartLayoutRect& GetBoundingBox() const override
    {
        return boundingBox_;
    }
    int64_t GetNodeId() const override
    {
        return 0;
    }
    const std::string& GetName() const override
    {
        return name_;
    }
    const NodePosition& GetPosition() const override
    {
        return position_;
    }
    const NodeSize& GetSize() const override
    {
        return size_;
    }
    const ScaleInfo& GetScaleInfo() const override
    {
        return scaleInfo_;
    }
    SmartLayoutRect GetChildrenBoundingBox() const override
    {
        return SmartLayoutRect();
    }
    void SetAvoidSafeArea(bool avoid) override {}
    LayoutContext& GetContext() override
    {
        return context_;
    }

private:
    std::string name_ = "fake";
    NodePosition position_ = {};
    NodeSize size_ = {};
    ScaleInfo scaleInfo_ = {};
    SmartLayoutRect boundingBox_ = {};
    LayoutContext context_;
    std::vector<std::shared_ptr<ISmartLayoutNode>> children_;
};

class SmartLayoutEngineLoaderFakeEngine final : public ISmartLayoutEngine {
public:
    std::shared_ptr<ISmartLayoutNode> CreateRootNode(const std::string& name = "root") override
    {
        return std::make_shared<SmartLayoutEngineLoaderFakeNode>();
    }
};

class SmartLayoutEngineLoaderTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: SmartLayoutEngineLoaderTest000
 * @tc.desc: Level0 sanity test for loader default availability.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest000, TestSize.Level0)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    EXPECT_FALSE(loader.IsEngineAvailable());
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest001
 * @tc.desc: Test GetInstance returns singleton reference
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest001, TestSize.Level1)
{
    auto& instanceA = SmartLayoutEngineLoader::GetInstance();
    auto& instanceB = SmartLayoutEngineLoader::GetInstance();
    EXPECT_EQ(&instanceA, &instanceB);
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest002
 * @tc.desc: Test IsEngineAvailable with nullptr engine
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest002, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    EXPECT_FALSE(loader.IsEngineAvailable());
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest003
 * @tc.desc: Test IsEngineAvailable with valid engine
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest003, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = new SmartLayoutEngineLoaderFakeEngine();
    EXPECT_TRUE(loader.IsEngineAvailable());
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest004
 * @tc.desc: Test GetEngine fast return when loadAttempted is true
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest004, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = new SmartLayoutEngineLoaderFakeEngine();
    loader.loadAttempted_.store(true, std::memory_order_release);

    auto* engine = loader.GetEngine();
#ifdef WINDOWS_PLATFORM
    EXPECT_EQ(engine, nullptr);
#else
    EXPECT_NE(engine, nullptr);
    EXPECT_EQ(engine, loader.engine_);
#endif
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest005
 * @tc.desc: Test GetEngine fast return nullptr when loadAttempted is true and engine is null
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest005, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    loader.loadAttempted_.store(true, std::memory_order_release);

    auto* engine = loader.GetEngine();
    EXPECT_EQ(engine, nullptr);
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest006
 * @tc.desc: Test GetEngine with loadAttempted false triggers load path
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest006, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    loader.loadAttempted_.store(false, std::memory_order_release);

    auto* engine = loader.GetEngine();
    EXPECT_EQ(engine, loader.engine_);
    if (engine != nullptr) {
        EXPECT_TRUE(loader.loadAttempted_.load(std::memory_order_acquire));
    } else {
        EXPECT_FALSE(loader.loadAttempted_.load(std::memory_order_acquire));
    }
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest009
 * @tc.desc: Test GetEngine fast return when engine_ already exists and loadAttempted is true
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest009, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = new SmartLayoutEngineLoaderFakeEngine();
    loader.loadAttempted_.store(true, std::memory_order_release);

    auto* engine = loader.GetEngine();
#ifdef WINDOWS_PLATFORM
    EXPECT_EQ(engine, nullptr);
    EXPECT_TRUE(loader.loadAttempted_.load(std::memory_order_acquire));
#else
    EXPECT_EQ(engine, loader.engine_);
    EXPECT_TRUE(loader.loadAttempted_.load(std::memory_order_acquire));
#endif
}

#ifndef WINDOWS_PLATFORM
/**
 * @tc.name: SmartLayoutEngineLoaderTest007
 * @tc.desc: Test LoadEngine direct call
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest007, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    loader.soHandle_ = nullptr;

    bool result = loader.LoadEngine();
    if (result) {
        EXPECT_NE(loader.engine_, nullptr);
        EXPECT_NE(loader.soHandle_, nullptr);
    } else {
        EXPECT_EQ(loader.engine_, nullptr);
        EXPECT_EQ(loader.soHandle_, nullptr);
    }
}

/**
 * @tc.name: SmartLayoutEngineLoaderTest008
 * @tc.desc: Test GetEngine fast return nullptr when loadAttempted is true and engine is null.
 * @tc.type: FUNC
 */
HWTEST_F(SmartLayoutEngineLoaderTest, SmartLayoutEngineLoaderTest008, TestSize.Level1)
{
    SmartLayoutEngineLoader loader;
    loader.engine_ = nullptr;
    loader.soHandle_ = nullptr;
    loader.loadAttempted_.store(true, std::memory_order_release);

    auto* engine = loader.GetEngine();
    EXPECT_EQ(engine, nullptr);
    EXPECT_TRUE(loader.loadAttempted_.load(std::memory_order_acquire));
    EXPECT_EQ(loader.soHandle_, nullptr);
}
#endif

} // namespace OHOS::Ace::NG
