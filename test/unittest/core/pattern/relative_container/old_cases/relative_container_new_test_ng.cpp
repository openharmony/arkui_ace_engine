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
#include <optional>
#include <vector>

#include "gtest/gtest.h"
#define protected public
#define private public

#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/property/flex_property.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using UITreeCreaterFunction = std::function<void(RelativeContainerModelNG)>;
namespace {
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const std::string CONTAINER_ID = "__container__";

AlignDirection AlignDirectionRtl(const AlignDirection& direction)
{
    if (direction == AlignDirection::START) {
        return AlignDirection::LEFT;
    } else if (direction == AlignDirection::END) {
        return AlignDirection::RIGHT;
    } else {
        return direction;
    }
}

void AddAlignRule(const std::string& id, const AlignDirection& direction, const HorizontalAlign& horizontalRule,
    std::map<AlignDirection, AlignRule>& alignRules)
{
    auto alignDirection = AlignDirectionRtl(direction);
    AlignRule alignRule;
    alignRule.anchor = id;
    alignRule.horizontal = horizontalRule;
    alignRules[alignDirection] = alignRule;
}

void AddAlignRule(const std::string& id, const AlignDirection& direction, const VerticalAlign& verticalRule,
    std::map<AlignDirection, AlignRule>& alignRules)
{
    AlignRule alignRule;
    alignRule.anchor = id;
    alignRule.vertical = verticalRule;
    alignRules[direction] = alignRule;
}

bool ListsEqual(const std::list<std::string>& left, const std::list<std::string>& right)
{
    if (left.size() != right.size()) {
        return false;
    }
    if (left.empty()) {
        return true;
    }
    auto iter1 = left.begin();
    auto iter2 = right.begin();
    while (iter1 != left.end() && iter2 != right.end()) {
        if (*iter1 != *iter2) {
            return false;
        }
        iter1++;
        iter2++;
    }
    return true;
}
} // namespace
class RelativeContainerNewTestNG : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    void CreateInstance(const std::function<void(RelativeContainerModelNG)>& callback = nullptr);
    void SetComponentParam(TextModelNG& textModelNG, std::string id, float width, float height);
    void SetContainerParam(std::string id, float width, float height);
    static UITreeCreaterFunction GetBasicModel();
    static RefPtr<FrameNode> CreateText(const std::u16string& content,
        const std::function<void(TextModelNG)>& callback);
    static void CreateLayoutTask(const RefPtr<FrameNode>& frameNode);
    static RefPtr<FrameNode> CreateRelativeContainer(const std::function<void(RelativeContainerModelNG)>& callback);
};

void RelativeContainerNewTestNG::SetUp() {}

void RelativeContainerNewTestNG::TearDown() {}

void RelativeContainerNewTestNG::CreateLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->SetLayoutDirtyMarked(true);
    frameNode->CreateLayoutTask();
}

RefPtr<FrameNode> RelativeContainerNewTestNG::CreateRelativeContainer(
    const std::function<void(RelativeContainerModelNG)>& callback)
{
    RelativeContainerModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> RelativeContainerNewTestNG::CreateText(
    const std::u16string& content, const std::function<void(TextModelNG)>& callback)
{
    TextModelNG model;
    model.Create(content);
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->PopContainer();
    return AceType::DynamicCast<FrameNode>(element);
}

UITreeCreaterFunction RelativeContainerNewTestNG::GetBasicModel()
{
    /**
      corresponding ets code:
        @State rowWidth:number = 100
         RelativeContainer() {
          Text('row1')
          .width(this.rowWidth).height(100)
          .alignRules({
            top: {anchor: "__container__", align: VerticalAlign.Top},
            left: {anchor: "__container__", align: this.xalign}
          })
          .id("row1")

          Text('row2')
          .width(100).height(100)
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "__container__", align: VerticalAlign.Top},
            right: {anchor: "__container__", align: HorizontalAlign.End}
          })
          .id("row2")

          Text('row3')
          .height(100)
          .alignRules({
            top: {anchor: "row1", align: VerticalAlign.Bottom},
            left: {anchor: "row1", align: HorizontalAlign.End},
            right: {anchor: "row2", align: HorizontalAlign.Start}
          })
          .id("row3")

          Text('row4')
          .alignRules({
            top: {anchor: "row3", align: VerticalAlign.Bottom},
            bottom: {anchor: "__container__", align: VerticalAlign.Bottom},
            left: {anchor: "__container__", align: HorizontalAlign.Start},
            right: {anchor: "row1", align: HorizontalAlign.End}
          })
          .id("row4")

          Text('row5')
          .alignRules({
            top: {anchor: "row3", align: VerticalAlign.Bottom},
            bottom: {anchor: "__container__", align: VerticalAlign.Bottom},
            left: {anchor: "row2", align: HorizontalAlign.Start},
            right: {anchor: "__container__", align: HorizontalAlign.End}
          })
          .id("row5")
        }
      */
    auto createrFunction = [](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        auto text1 = CreateText(u"text1", [](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
        });
        auto text2 = CreateText(u"text2", [](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
            ViewAbstract::SetInspectorId("text2");
            std::map<AlignDirection, AlignRule> secondTextAlignRules;
            AddAlignRule("text1", AlignDirection::RIGHT, HorizontalAlign::END, secondTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, secondTextAlignRules);
            ViewAbstract::SetAlignRules(secondTextAlignRules);
        });
        auto text3 = CreateText(u"text3", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text3");
            ViewAbstract::SetHeight(CalcLength(100.0f));
            std::map<AlignDirection, AlignRule> thirdTextAlignRules;
            AddAlignRule("text1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
            AddAlignRule("text1", AlignDirection::TOP, VerticalAlign::TOP, thirdTextAlignRules);
            AddAlignRule("text2", AlignDirection::RIGHT, HorizontalAlign::END, thirdTextAlignRules);
            ViewAbstract::SetAlignRules(thirdTextAlignRules);
        });
        auto text4 = CreateText(u"text4", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text4");
            std::map<AlignDirection, AlignRule> forthTextAlignRules;
            AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, forthTextAlignRules);
            AddAlignRule("text1", AlignDirection::RIGHT, HorizontalAlign::END, forthTextAlignRules);
            AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::TOP, forthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, forthTextAlignRules);
            ViewAbstract::SetAlignRules(forthTextAlignRules);
        });
        auto text5 = CreateText(u"text5", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text5");
            std::map<AlignDirection, AlignRule> fifthTextAlignRules;
            AddAlignRule("text2", AlignDirection::LEFT, HorizontalAlign::START, fifthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, fifthTextAlignRules);
            AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::TOP, fifthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, fifthTextAlignRules);
            ViewAbstract::SetAlignRules(fifthTextAlignRules);
        });
    };
    return createrFunction;
}

/**
 * @tc.name: Example
 * @tc.desc: Test functionality of relativeContainer cache when alignRules not changed
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RenderListTest001, TestSize.Level0)
{
    auto frameNode = RelativeContainerNewTestNG::CreateRelativeContainer(RelativeContainerNewTestNG::GetBasicModel());
    ASSERT_EQ(frameNode->GetChildren().size(), 5);
    CreateLayoutTask(frameNode);
    auto pattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto resultList1 = pattern->GetTopologicalResultCacheCopy();
    EXPECT_TRUE(resultList1.has_value());
    auto resultList1Value = resultList1.value();
    auto text1 = frameNode->GetChildren().begin();
    EXPECT_NE(text1, frameNode->GetChildren().end());
    auto textNode1 = AceType::DynamicCast<FrameNode>(*text1);
    EXPECT_NE(textNode1, nullptr);
    auto textLayoutProperty1 = textNode1->GetLayoutProperty();
    EXPECT_NE(textLayoutProperty1, nullptr);
    textLayoutProperty1->UpdateUserDefinedIdealSize(NG::CalcSize(CalcLength(200), CalcLength(200)));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_FALSE(pattern->GetChildAlignRulesChanged());
    CreateLayoutTask(frameNode);
    auto resultList2 = pattern->GetTopologicalResultCacheCopy();
    EXPECT_TRUE(resultList2.has_value());
    auto resultList2Value = resultList2.value();
    EXPECT_EQ(resultList1Value.size(), resultList2Value.size());
    EXPECT_TRUE(ListsEqual(resultList1Value, resultList2Value));
}

/**
 * @tc.name: Example
 * @tc.desc: Test functionality of relativeContainer cache when alignRules changed
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, RenderListTest002, TestSize.Level0)
{
    auto frameNode = RelativeContainerNewTestNG::CreateRelativeContainer(RelativeContainerNewTestNG::GetBasicModel());
    ASSERT_EQ(frameNode->GetChildren().size(), 5);
    CreateLayoutTask(frameNode);
    auto pattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto resultList1 = pattern->GetTopologicalResultCacheCopy();
    EXPECT_TRUE(resultList1.has_value());
    auto resultList1Value = resultList1.value();
    auto text1 = frameNode->GetChildren().begin();
    EXPECT_NE(text1, frameNode->GetChildren().end());
    auto textNode1 = AceType::DynamicCast<FrameNode>(*text1);
    EXPECT_NE(textNode1, nullptr);
    auto textLayoutProperty1 = textNode1->GetLayoutProperty();
    EXPECT_NE(textLayoutProperty1, nullptr);
    std::map<AlignDirection, AlignRule> newAlignRules;
    AlignRule alignRule;
    alignRule.anchor = CONTAINER_ID;
    alignRule.horizontal = HorizontalAlign::END;
    newAlignRules[AlignDirection::LEFT] = alignRule;
    textLayoutProperty1->UpdateAlignRules(newAlignRules);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(pattern->GetChildAlignRulesChanged());
    CreateLayoutTask(frameNode);
    auto resultList2 = pattern->GetTopologicalResultCacheCopy();
    EXPECT_TRUE(resultList2.has_value());
    auto resultList2Value = resultList2.value();
    EXPECT_EQ(resultList1Value.size(), resultList2Value.size());
    EXPECT_TRUE(ListsEqual(resultList1Value, resultList2Value));
}

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case to test barrier.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, BarrierAttrTest001, TestSize.Level0)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(11);

    /**
    corresponding ets code:
       RelativeContainer(){
        Text('text1').width(100).height(50).id("text1")
          .alignRules({
            left: {anchor: "__container__", align: HorizontalAlign.Start},
          }).backgroundColor(Color.Green)
        Text('text2').width(100).height(50).id("text2")
          .alignRules({
            left: {anchor: "text1", align: HorizontalAlign.End},
          }).backgroundColor(Color.Green)

        Text('text3').width(100).height(50).id("text3")
          .alignRules({
            left: {anchor: "barrier1", align: HorizontalAlign.Start},
          }).backgroundColor(Color.Yellow)
      }.width(300).height(300).backgroundColor(Color.Red)
      .barrier([{id: "barrier1", direction: BarrierDirection.RIGHT, referencedId:["text1", "text2"]}])
    */
    auto frameNode = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        auto text1 = CreateText(u"text1", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
        });
        auto text2 = CreateText(u"text2", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text2");
            std::map<AlignDirection, AlignRule> secondTextAlignRules;
            AddAlignRule("text1", AlignDirection::LEFT, HorizontalAlign::END, secondTextAlignRules);
            ViewAbstract::SetAlignRules(secondTextAlignRules);
        });
        auto text3 = CreateText(u"text3", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(50.0f));
            ViewAbstract::SetInspectorId("text3");
            std::map<AlignDirection, AlignRule> thirdTextAlignRules;
            AddAlignRule("barrier1", AlignDirection::LEFT, HorizontalAlign::START, thirdTextAlignRules);
            ViewAbstract::SetAlignRules(thirdTextAlignRules);
        });
        BarrierInfo firstBarrierInfo;
        firstBarrierInfo.id = "barrier1";
        firstBarrierInfo.direction = BarrierDirection::RIGHT;
        firstBarrierInfo.referencedId = std::vector<std::string> { "text1", "text2" };
        model.SetBarrier(std::vector<BarrierInfo> { firstBarrierInfo });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 3);
    CreateLayoutTask(frameNode);

    // expect: text3 is next to the right of text2
    EXPECT_EQ(frameNode->GetChildByIndex(2)->GetGeometryNode()->GetFrameOffset().GetX(), 200.0f);
}

/**
 * @tc.name: Example
 * @tc.desc: Test functionality of relativeContainer when it has loop dependent nodes.
 * @tc.type: ETS
 */
HWTEST_F(RelativeContainerNewTestNG, LoopDependentTest001, TestSize.Level0)
{
    /**
      corresponding ets code:
         RelativeContainer() {
          Text('text1')
          .width(100).height(100)
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "__container__", align: VerticalAlign.Top},
            left: {anchor: "__container__", align: HorizontalAlign.Start}
          })
          .id("text1")

          Text('text2')
          .width(100).height(100)
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "__container__", align: VerticalAlign.Top},
            right: {anchor: "__container__", align: HorizontalAlign.End}
          })
          .id("text2")

          Text('text3')
          .height(100)
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "text1", align: VerticalAlign.Bottom},
            left: {anchor: "text1", align: HorizontalAlign.End},
            right: {anchor: "text2", align: HorizontalAlign.Start}
          })
          .id("text3")

          Text('text4')
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "text3", align: VerticalAlign.Bottom},
            bottom: {anchor: "__container__", align: VerticalAlign.Bottom},
            left: {anchor: "__container__", align: HorizontalAlign.Start},
            right: {anchor: "text5", align: HorizontalAlign.End}
          })
          .id("text4")

          Text('text5')
          .backgroundColor("#FFCC00")
          .alignRules({
            top: {anchor: "text3", align: VerticalAlign.Bottom},
            bottom: {anchor: "__container__", align: VerticalAlign.Bottom},
            left: {anchor: "text4", align: HorizontalAlign.Start},
            right: {anchor: "__container__", align: HorizontalAlign.End}
          })
          .id("text5")
        }
      */
    auto frameNode = CreateRelativeContainer([this](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(CONTAINER_WIDTH));
        ViewAbstract::SetHeight(CalcLength(CONTAINER_HEIGHT));
        ViewAbstract::SetInspectorId(CONTAINER_ID);
        auto text1 = CreateText(u"text1", [](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
            ViewAbstract::SetInspectorId("text1");
            std::map<AlignDirection, AlignRule> firstTextAlignRules;
            AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, firstTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, firstTextAlignRules);
            ViewAbstract::SetAlignRules(firstTextAlignRules);
        });
        auto text2 = CreateText(u"text2", [](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
            ViewAbstract::SetInspectorId("text2");
            std::map<AlignDirection, AlignRule> secondTextAlignRules;
            AddAlignRule(CONTAINER_ID, AlignDirection::TOP, VerticalAlign::TOP, secondTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, secondTextAlignRules);
            ViewAbstract::SetAlignRules(secondTextAlignRules);
        });
        auto text3 = CreateText(u"text3", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text3");
            ViewAbstract::SetHeight(CalcLength(100.0f));
            std::map<AlignDirection, AlignRule> thirdTextAlignRules;
            AddAlignRule("text1", AlignDirection::TOP, VerticalAlign::BOTTOM, thirdTextAlignRules);
            AddAlignRule("text1", AlignDirection::LEFT, HorizontalAlign::END, thirdTextAlignRules);
            AddAlignRule("text2", AlignDirection::RIGHT, HorizontalAlign::START, thirdTextAlignRules);
            ViewAbstract::SetAlignRules(thirdTextAlignRules);
        });
        auto text4 = CreateText(u"text4", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text4");
            std::map<AlignDirection, AlignRule> forthTextAlignRules;
            AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::BOTTOM, forthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, forthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, forthTextAlignRules);
            AddAlignRule("text5", AlignDirection::RIGHT, HorizontalAlign::END, forthTextAlignRules);
            ViewAbstract::SetAlignRules(forthTextAlignRules);
        });
        auto text5 = CreateText(u"text5", [](TextModelNG model) {
            ViewAbstract::SetInspectorId("text5");
            std::map<AlignDirection, AlignRule> fifthTextAlignRules;
            AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::BOTTOM, fifthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, fifthTextAlignRules);
            AddAlignRule("text4", AlignDirection::LEFT, HorizontalAlign::START, fifthTextAlignRules);
            AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, fifthTextAlignRules);
            ViewAbstract::SetAlignRules(fifthTextAlignRules);
        });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 5);
    CreateLayoutTask(frameNode);
    auto pattern = frameNode->GetPattern<RelativeContainerPattern>();
    EXPECT_NE(pattern, nullptr);
    auto loopDependentNodes1 = pattern->GetLoopDependentNodes();
    EXPECT_TRUE(loopDependentNodes1);
    auto text5 = frameNode->GetChildren().rbegin();
    EXPECT_NE(text5, frameNode->GetChildren().rend());
    auto textNode5 = AceType::DynamicCast<FrameNode>(*text5);
    EXPECT_NE(textNode5, nullptr);
    auto textLayoutProperty5 = textNode5->GetLayoutProperty();
    EXPECT_NE(textLayoutProperty5, nullptr);
    std::map<AlignDirection, AlignRule> fifthTextAlignRules;
    AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::BOTTOM, fifthTextAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, fifthTextAlignRules);
    AddAlignRule("text2", AlignDirection::LEFT, HorizontalAlign::START, fifthTextAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::RIGHT, HorizontalAlign::END, fifthTextAlignRules);
    textLayoutProperty5->UpdateAlignRules(fifthTextAlignRules);
    auto text4 = ++text5;
    EXPECT_NE(text4, frameNode->GetChildren().rend());
    auto textNode4 = AceType::DynamicCast<FrameNode>(*text4);
    EXPECT_NE(textNode4, nullptr);
    auto textLayoutProperty4 = textNode4->GetLayoutProperty();
    EXPECT_NE(textLayoutProperty4, nullptr);
    std::map<AlignDirection, AlignRule> forthTextAlignRules;
    AddAlignRule("text3", AlignDirection::TOP, VerticalAlign::BOTTOM, forthTextAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::BOTTOM, VerticalAlign::BOTTOM, forthTextAlignRules);
    AddAlignRule(CONTAINER_ID, AlignDirection::LEFT, HorizontalAlign::START, forthTextAlignRules);
    AddAlignRule("text1", AlignDirection::RIGHT, HorizontalAlign::END, forthTextAlignRules);
    textLayoutProperty4->UpdateAlignRules(forthTextAlignRules);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(pattern->GetChildAlignRulesChanged());
    frameNode->layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    CreateLayoutTask(frameNode);
    auto loopDependentNodes2 = pattern->GetLoopDependentNodes();
    EXPECT_FALSE(loopDependentNodes2);
}
} // namespace OHOS::Ace::NG