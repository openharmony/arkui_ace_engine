/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "water_flow_test_ng.h"

#include "frameworks/core/components_ng/pattern/waterflow/water_flow_sections.h"

namespace OHOS::Ace::NG {
namespace {
std::string GetDumpResult()
{
    std::string result;
    for (const auto& desc : DumpLog::GetInstance().description_) {
        result.append(desc);
    }
    return result;
}
} // namespace

class WaterFlowDumpTest : public WaterFlowTestNg {};

/**
 * @tc.name: DumpInfo_NoSections
 * @tc.desc: Test WaterFlowPattern::DumpInfo without sections.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpInfo_NoSections, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("WaterFlowCacheCount:"), std::string::npos);
    EXPECT_NE(result.find("WaterFlowLayoutMode:"), std::string::npos);
    EXPECT_NE(result.find("WaterFlowSections: NO"), std::string::npos);
}

/**
 * @tc.name: DumpInfo_WithSections
 * @tc.desc: Test WaterFlowPattern::DumpInfo with sections present.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpInfo_WithSections, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    auto sections = AceType::MakeRefPtr<WaterFlowSections>();
    std::vector<WaterFlowSections::Section> sectionVec = { { .itemsCount = 5, .crossCount = 2 } };
    sections->ChangeData(0, 0, sectionVec);
    pattern_->sections_ = sections;

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("WaterFlowSections: YES"), std::string::npos);
    EXPECT_NE(result.find("start print sections_"), std::string::npos);
    EXPECT_NE(result.find("[section:0]"), std::string::npos);
    EXPECT_NE(result.find("itemCount:5"), std::string::npos);
    EXPECT_NE(result.find("crossCount:2"), std::string::npos);
    EXPECT_NE(result.find("end print sections_"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_TopDown
 * @tc.desc: Test WaterFlowPattern::DumpAdvanceInfo in TOP_DOWN mode.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_TopDown, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("childrenCount:"), std::string::npos);
    EXPECT_NE(result.find("offset:"), std::string::npos);
    EXPECT_NE(result.find("prevOffset:"), std::string::npos);
    EXPECT_NE(result.find("lastMainSize:"), std::string::npos);
    EXPECT_NE(result.find("maxHeight:"), std::string::npos);
    EXPECT_NE(result.find("startIndex:"), std::string::npos);
    EXPECT_NE(result.find("endIndex:"), std::string::npos);
    EXPECT_NE(result.find("jumpIndex:"), std::string::npos);
    EXPECT_NE(result.find("Mode:TOP_DOWN"), std::string::npos);
    // Should NOT contain footerHeight (that's SLIDING_WINDOW only)
    EXPECT_EQ(result.find("footerHeight:"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_Templates
 * @tc.desc: Test RowsTemplate/ColumnsTemplate output with value_or("null").
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_Templates, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    // ColumnsTemplate is set, RowsTemplate is not set
    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("ColumnsTemplate:1fr 1fr"), std::string::npos);
    EXPECT_NE(result.find("RowsTemplate:null"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_ScrollAlign
 * @tc.desc: Test ScrollAlign enum mapping in DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_ScrollAlign, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    // Test CENTER
    pattern_->layoutInfo_->align_ = ScrollAlign::CENTER;
    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();
    EXPECT_NE(result.find("ScrollAlign:CENTER"), std::string::npos);

    // Test END
    pattern_->layoutInfo_->align_ = ScrollAlign::END;
    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    result = GetDumpResult();
    EXPECT_NE(result.find("ScrollAlign:END"), std::string::npos);

    // Test NONE
    pattern_->layoutInfo_->align_ = ScrollAlign::NONE;
    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    result = GetDumpResult();
    EXPECT_NE(result.find("ScrollAlign:NONE"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_BooleanFlags
 * @tc.desc: Test itemStart/itemEnd/offsetEnd boolean flags in DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_BooleanFlags, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    pattern_->layoutInfo_->itemStart_ = true;
    pattern_->layoutInfo_->itemEnd_ = true;
    pattern_->layoutInfo_->offsetEnd_ = true;

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("itemStart:true"), std::string::npos);
    EXPECT_NE(result.find("itemEnd:true"), std::string::npos);
    EXPECT_NE(result.find("offsetEnd:true"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_WithFooter
 * @tc.desc: Test footer:true in DumpAdvanceInfo when footer node is present.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_WithFooter, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    CreateWaterFlowItems();
    CreateDone();

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("footer:true"), std::string::npos);
}

/**
 * @tc.name: DumpAdvanceInfo_WithSections
 * @tc.desc: Test DumpAdvanceInfo with sections present.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, DumpAdvanceInfo_WithSections, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    auto sections = AceType::MakeRefPtr<WaterFlowSections>();
    std::vector<WaterFlowSections::Section> sectionVec = {
        { .itemsCount = 3, .crossCount = 2 },
        { .itemsCount = 7, .crossCount = 3 },
    };
    sections->ChangeData(0, 0, sectionVec);
    pattern_->sections_ = sections;

    DumpLog::GetInstance().description_.clear();
    pattern_->DumpAdvanceInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("start print sections_"), std::string::npos);
    EXPECT_NE(result.find("[section:0]"), std::string::npos);
    EXPECT_NE(result.find("itemCount:3"), std::string::npos);
    EXPECT_NE(result.find("[section:1]"), std::string::npos);
    EXPECT_NE(result.find("itemCount:7"), std::string::npos);
    EXPECT_NE(result.find("crossCount:3"), std::string::npos);
    EXPECT_NE(result.find("end print sections_"), std::string::npos);
}

/**
 * @tc.name: GetEventDumpInfo_NoCallbacks
 * @tc.desc: Test GetEventDumpInfo without any callbacks set.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, GetEventDumpInfo_NoCallbacks, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    DumpLog::GetInstance().description_.clear();
    pattern_->GetEventDumpInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("hasOnScrollIndex: false"), std::string::npos);
    EXPECT_NE(result.find("hasFrameNodeOnScrollIndex: false"), std::string::npos);
}

/**
 * @tc.name: GetEventDumpInfo_WithCallbacks
 * @tc.desc: Test GetEventDumpInfo with scroll index callbacks set.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowDumpTest, GetEventDumpInfo_WithCallbacks, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();

    eventHub_->SetOnScrollIndex([](int32_t, int32_t) {});
    eventHub_->SetJSFrameNodeOnWaterFlowScrollIndex([](int32_t, int32_t) {});

    DumpLog::GetInstance().description_.clear();
    pattern_->GetEventDumpInfo();
    std::string result = GetDumpResult();

    EXPECT_NE(result.find("hasOnScrollIndex: true"), std::string::npos);
    EXPECT_NE(result.find("hasFrameNodeOnScrollIndex: true"), std::string::npos);
}
} // namespace OHOS::Ace::NG
