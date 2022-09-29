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

#include "gtest/gtest.h"

#include "core/components_v2/list/list_component.h"
#include "core/components/box/render_box.h"
#include "core/components_v2/list/render_list.h"
#include "core/components_v2/list/render_list_item.h"
#include "core/components/test/unittest/mock/mock_render_common.h"
#include "core/components/theme/theme_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::V2 {
namespace {

const RefPtr<ThemeManager> THEME_MANAGER = AceType::MakeRefPtr<ThemeManager>();

} // namespace

class MockRenderListItem final : public RenderListItem {
    DECLARE_ACE_TYPE(MockRenderListItem, RenderListItem);

public:
    MockRenderListItem() = default;
    ~MockRenderListItem() override = default;

    void PerformLayout() override;
};

void MockRenderListItem::PerformLayout()
{
    RenderListItem::PerformLayout();
}

class MockRenderList final : public RenderList {
    DECLARE_ACE_TYPE(MockRenderList, RenderList);

public:
    MockRenderList() = default;
    ~MockRenderList() override = default;

    bool IsWatch() const
    {
        return SystemProperties::GetDeviceType() == DeviceType::WATCH;
    }

    bool IsTV() const
    {
        return SystemProperties::GetDeviceType() == DeviceType::TV;
    }

    double GetViewPortSize()
    {
        return GetMainSize(viewPort_);
    }

    bool IsRTL()
    {
        return isRightToLeft_;
    }

    void AddListItems()
    {
        for (int i = 0; i < 10; i++) {
            RefPtr<MockRenderListItem> listItem = AceType::MakeRefPtr<MockRenderListItem>();
            items_.emplace_back(listItem);
        }
    }
};

class RenderListTestV2 : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    RefPtr<PipelineContext> mockContext_;
    RefPtr<MockRenderList> renderList_;
    int32_t index_ = 0;
};

void RenderListTestV2::SetUpTestCase() {}
void RenderListTestV2::TearDownTestCase() {}

void RenderListTestV2::SetUp()
{
    mockContext_ = MockRenderCommon::GetMockContext();
    renderList_ = AceType::MakeRefPtr<MockRenderList>();
    renderList_->Attach(mockContext_);
    index_ = 0;
}

void RenderListTestV2::TearDown()
{
    mockContext_ = nullptr;
    renderList_ = nullptr;
}

/**
 * @tc.name: RenderListRTL001
 * @tc.desc: Test RTL of list component with vertical direction
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderListTestV2, RenderListRTL001, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderListTestV2 rtl001 start";

    /**
     * @tc.steps: step1. construct ListComponent and RenderList, set text direction.
     * @tc.expected: step1. The text direction is correct.
     */
    RefPtr<ListComponent> listComponent = AceType::MakeRefPtr<ListComponent>();
    listComponent->SetTextDirection(TextDirection::RTL);
    renderList_->Update(listComponent);
    renderList_->AddListItems();
    EXPECT_TRUE(renderList_->IsRTL());

    /**
     * @tc.steps: step2. trigger layout for render list.
     * @tc.expected: step2. List and children layout correct.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderList_->SetLayoutParam(layoutParam);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 1000.0));

    /**
     * @tc.steps: step3. Set lanes and trigger layout.
     * @tc.expected: step3. List and children layout correct.
     */
    listComponent->SetLanes(2);
    renderList_->Update(listComponent);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 1000.0));

    GTEST_LOG_(INFO) << "RenderListTestV2 rtl001 stop";
}

/**
 * @tc.name: RenderListRTL002
 * @tc.desc: Test LTR of list component with vertical direction
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderListTestV2, RenderListRTL002, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderListTestV2 rtl002 start";

    /**
     * @tc.steps: step1. construct ListComponent and RenderList, set text direction.
     * @tc.expected: step1. The text direction is correct.
     */
    RefPtr<ListComponent> listComponent = AceType::MakeRefPtr<ListComponent>();
    listComponent->SetTextDirection(TextDirection::LTR);
    renderList_->Update(listComponent);
    renderList_->AddListItems();
    EXPECT_FALSE(renderList_->IsRTL());

    /**
     * @tc.steps: step2. trigger layout for render list.
     * @tc.expected: step2. List and children layout correct.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderList_->SetLayoutParam(layoutParam);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 1000.0));

    /**
     * @tc.steps: step3. Set lanes and trigger layout.
     * @tc.expected: step3. List and children layout correct.
     */
    listComponent->SetLanes(2);
    renderList_->Update(listComponent);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 1000.0));

    GTEST_LOG_(INFO) << "RenderListTestV2 rtl002 stop";
}

/**
 * @tc.name: RenderListRTL003
 * @tc.desc: Test RTL of list component with horizontal direction
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderListTestV2, RenderListRTL003, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderListTestV2 rtl003 start";

    /**
     * @tc.steps: step1. construct ListComponent and RenderList, set text direction.
     * @tc.expected: step1. The text direction is correct.
     */
    RefPtr<ListComponent> listComponent = AceType::MakeRefPtr<ListComponent>();
    listComponent->SetTextDirection(TextDirection::RTL);
    listComponent->SetDirection(Axis::HORIZONTAL);
    renderList_->Update(listComponent);
    renderList_->AddListItems();
    EXPECT_TRUE(renderList_->IsRTL());

    /**
     * @tc.steps: step2. trigger layout for render list.
     * @tc.expected: step2. List and children layout correct.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderList_->SetLayoutParam(layoutParam);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 0));

    /**
     * @tc.steps: step3. Set lanes and trigger layout.
     * @tc.expected: step3. List and children layout correct.
     */
    listComponent->SetLanes(2);
    renderList_->Update(listComponent);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 0));

    GTEST_LOG_(INFO) << "RenderListTestV2 rtl003 stop";
}

/**
 * @tc.name: RenderListRTL004
 * @tc.desc: Test LTR of list component with horizontal direction
 * @tc.type: FUNC
 * @tc.require: issueI5NC7M
 */
HWTEST_F(RenderListTestV2, RenderListRTL004, TestSize.Level1)
{
    GTEST_LOG_(INFO) << "RenderListTestV2 rtl004 start";

    /**
     * @tc.steps: step1. construct ListComponent and RenderList, set text direction.
     * @tc.expected: step1. The text direction is correct.
     */
    RefPtr<ListComponent> listComponent = AceType::MakeRefPtr<ListComponent>();
    listComponent->SetTextDirection(TextDirection::LTR);
    listComponent->SetDirection(Axis::HORIZONTAL);
    renderList_->Update(listComponent);
    renderList_->AddListItems();
    EXPECT_FALSE(renderList_->IsRTL());

    /**
     * @tc.steps: step2. trigger layout for render list.
     * @tc.expected: step2. List and children layout correct.
     */
    LayoutParam layoutParam;
    layoutParam.SetMinSize(Size(0.0, 0.0));
    layoutParam.SetMaxSize(Size(1000.0, 1000.0));
    renderList_->SetLayoutParam(layoutParam);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 0));

    /**
     * @tc.steps: step3. Set lanes and trigger layout.
     * @tc.expected: step3. List and children layout correct.
     */
    listComponent->SetLanes(2);
    renderList_->Update(listComponent);
    renderList_->PerformLayout();
    EXPECT_TRUE(NearEqual(renderList_->GetLayoutSize().Width(), 0));

    GTEST_LOG_(INFO) << "RenderListTestV2 rtl004 stop";
}

} // namespace OHOS::Ace::V2
