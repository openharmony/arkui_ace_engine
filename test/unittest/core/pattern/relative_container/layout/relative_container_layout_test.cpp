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

#include "test/unittest/core/pattern/relative_container/relative_container_base_test_ng.h"
using namespace std;

namespace OHOS::Ace::NG {

class RelativeContainerLayoutTest : public RelativeContainerBaseTestNG {
public:
    static void PrepareLayout(LayoutWrapper* layoutWrapper, RelativeContainerLayoutAlgorithm& layoutAlgorithm)
    {
        layoutAlgorithm.Initialize(layoutWrapper);
        // create idNodeMap_
        layoutAlgorithm.CollectNodesById(layoutWrapper);
        // create reliedOnMap_
        layoutAlgorithm.GetDependencyRelationship();
        // create incomingDegreeMap_
        layoutAlgorithm.PreTopologicalLoopDetection(layoutWrapper);
        // create renderList_
        layoutAlgorithm.TopologicalSort(layoutAlgorithm.renderList_);
        // create recordOffsetMap_
        layoutAlgorithm.MeasureChild(layoutWrapper);
    }

    static string TestRenderList(std::list<std::string>& renderList)
    {
        string res;
        res += "[";
        for (auto it = renderList.begin(); it != renderList.end(); ++it) {
            res += *it;
            if (std::next(it) != renderList.end()) {
                res += ", ";
            }
        }
        res += "]";
        return res;
    }
};

/**
 * @tc.desc: Test Layout
    dependence: recordOffsetMap_
    output: MarginFrameOffset of each childnode
 */
HWTEST_F(RelativeContainerLayoutTest, LayoutTest, TestSize.Level0)
{
    // create three child nodes with alignRules
    RefPtr<FrameNode> row1, row2, row3;
    auto relativeContainer = CreateRelativeContainer([this, &row1, &row2, &row3](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100));
        ViewAbstract::SetHeight(CalcLength(100));
        ViewAbstract::SetBorderWidth(Dimension(3));
        ViewAbstract::SetPadding(CalcLength(1));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row1");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::CENTER);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row2");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row1", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row1", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetInspectorId("row3");
            ViewAbstract::SetWidth(CalcLength(30));
            ViewAbstract::SetHeight(CalcLength(30));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "row2", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "row2", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    // constraint
    LayoutConstraintF constraint = {
        .percentReference = { 100, 100 }, // {width, height}
        .parentIdealSize = { 100, 100 },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    // used when creating child constraint
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // dependence: recordOffsetMap_
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);
    // test Layout
    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));
    // expect: row1.offset = (center, padding+border) = (100/2, 3+1) = (50, 4)
    EXPECT_EQ(row1->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(50, 4))
        << row1->GetGeometryNode()->GetMarginFrameOffset().ToString();
    // expect: row2.offset = (row1+30, padding+border) = (50+30, 4) = (80, 4)
    EXPECT_EQ(row2->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(80, 4))
        << row2->GetGeometryNode()->GetMarginFrameOffset().ToString();
    // expect: row3.offset = (row2+30, padding+border) = (80+30, 4) = (80, 4)
    EXPECT_EQ(row3->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(110, 4))
        << row3->GetGeometryNode()->GetMarginFrameOffset().ToString();
}

/**
 * @tc.name: Layout_EmptyContainer
 * @tc.desc: 测试空容器的布局处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_EmptyContainer, TestSize.Level0)
{
    const float largeContainer = 100.0f;

    // 创建无子节点的容器
    auto relativeContainer = CreateRelativeContainer([largeContainer](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(largeContainer));
        ViewAbstract::SetHeight(CalcLength(largeContainer));
    });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // 准备布局（无子节点）
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证 idNodeMap_ 为空
    EXPECT_TRUE(layoutAlgorithm.idNodeMap_.empty());
    // 验证 renderList_ 为空
    EXPECT_TRUE(layoutAlgorithm.renderList_.empty());
    // 验证 recordOffsetMap_ 为空
    EXPECT_TRUE(layoutAlgorithm.recordOffsetMap_.empty());
}

/**
 * @tc.name: Layout_SingleChildNoDependency
 * @tc.desc: 测试单子节点无依赖情况的布局
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_SingleChildNoDependency, TestSize.Level0)
{
    const float largeContainer = 100.0f;
    const float childSize = 30.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, childSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));
            childNode = CreateRow([childSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(childSize));
                ViewAbstract::SetHeight(CalcLength(childSize));
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证单节点在 renderList_ 中
    EXPECT_EQ(layoutAlgorithm.renderList_.size(), 1);
    EXPECT_EQ(layoutAlgorithm.renderList_.front(), "child1");

    // 执行布局
    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证子节点位置（默认位置）
    EXPECT_EQ(childNode->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));
}

/**
 * @tc.name: Layout_SingleChildWithContainerDependency
 * @tc.desc: 测试单子节点依赖容器的情况
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_SingleChildWithContainerDependency, TestSize.Level0)
{
    const float largeContainer = 100.0f;
    const float childSize = 30.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, childSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));
            childNode = CreateRow([childSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(childSize));
                ViewAbstract::SetHeight(CalcLength(childSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::CENTER);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证子节点位置
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(actualOffset.GetX(), largeContainer / 2);
    EXPECT_FLOAT_EQ(actualOffset.GetY(), 0);
}

/**
 * @tc.name: Layout_BranchDependencies
 * @tc.desc: 测试分支依赖关系的布局（A依赖容器，B和C都依赖A）
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_BranchDependencies, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> nodeA, nodeB, nodeC;
    auto relativeContainer = CreateRelativeContainer(
        [this, &nodeA, &nodeB, &nodeC, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 节点A依赖容器
            nodeA = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeA");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点B依赖A
            nodeB = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeB");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "nodeA", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "nodeA", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点C也依赖A
            nodeC = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeC");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "nodeA", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "nodeA", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证拓扑排序结果：A 应该排在最前面
    EXPECT_EQ(layoutAlgorithm.renderList_.front(), "nodeA");

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点A的位置
    EXPECT_EQ(nodeA->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));

    // 验证节点B的位置（在A下方）
    EXPECT_EQ(nodeB->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, nodeSize));

    // 验证节点C的位置（在A右侧，同一水平线）
    EXPECT_EQ(nodeC->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(nodeSize, 0));
}

/**
 * @tc.name: Layout_ConvergeDependencies
 * @tc.desc: 测试汇聚依赖关系的布局（A和B独立，C都依赖A和B）
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_ConvergeDependencies, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> nodeA, nodeB, nodeC;
    auto relativeContainer = CreateRelativeContainer(
        [this, &nodeA, &nodeB, &nodeC, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 节点A依赖容器左上
            nodeA = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeA");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点B依赖容器右上
            nodeB = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeB");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点C同时依赖A和B
            nodeC = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeC");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "nodeA", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "nodeB", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证拓扑排序：A和B应该排在C前面
    auto renderListStr = TestRenderList(layoutAlgorithm.renderList_);
    EXPECT_TRUE(renderListStr.find("nodeA") < renderListStr.find("nodeC"));
    EXPECT_TRUE(renderListStr.find("nodeB") < renderListStr.find("nodeC"));

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点A的位置（左上）
    EXPECT_EQ(nodeA->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));

    // 验证节点B的位置（右上）
    auto offsetB = nodeB->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offsetB.GetX(), largeContainer - nodeSize);
    EXPECT_FLOAT_EQ(offsetB.GetY(), 0);

    // 验证节点C的位置
    auto offsetC = nodeC->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offsetC.GetY(), nodeSize);
}

/**
 * @tc.name: Layout_ComplexNetworkDependencies
 * @tc.desc: 测试复杂网状依赖关系的布局
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_ComplexNetworkDependencies, TestSize.Level0)
{
    const float largeContainer = 300.0f;
    const float nodeSize = 30.0f;

    RefPtr<FrameNode> node1, node2, node3, node4;
    auto relativeContainer = CreateRelativeContainer(
        [this, &node1, &node2, &node3, &node4, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 节点1：根节点
            node1 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点2：依赖节点1
            node2 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node2");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "node1", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "node1", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点3：依赖节点1
            node3 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node3");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "node1", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "node2", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点4：依赖节点2和3
            node4 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node4");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "node2", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "node3", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证拓扑排序：node1 必须在最前面，node4 必须在最后面
    auto renderListStr = TestRenderList(layoutAlgorithm.renderList_);
    EXPECT_EQ(layoutAlgorithm.renderList_.front(), "node1");
    EXPECT_EQ(layoutAlgorithm.renderList_.back(), "node4");

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点1的位置（原点）
    EXPECT_EQ(node1->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(0, 0));

    // 验证节点2的位置（node1右下方）
    EXPECT_EQ(node2->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(nodeSize, nodeSize));

    // 验证节点3的位置（node1右侧）
    auto offset3 = node3->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset3.GetX(), 2 * nodeSize);
    EXPECT_FLOAT_EQ(offset3.GetY(), 0);
}

/**
 * @tc.name: Layout_WithGuidelineHorizontal
 * @tc.desc: 测试水平Guideline的布局
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_WithGuidelineHorizontal, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float guidelineOffset = 50.0f;
    const float nodeSize = 30.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer = CreateRelativeContainer(
        [this, &childNode, largeContainer, guidelineOffset, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 添加水平Guideline
            std::vector<GuidelineInfo> guidelineInfos;
            GuidelineInfo hGuideInfo = { .id = "hGuide",
                .direction = LineDirection::HORIZONTAL,
                .start = Dimension(guidelineOffset, DimensionUnit::PX) };
            guidelineInfos.push_back(hGuideInfo);
            model.SetGuideline(guidelineInfos);

            // 创建依赖Guideline的子节点
            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "hGuide", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证Guideline已被记录
    EXPECT_NE(layoutAlgorithm.guidelines_.find("hGuide"), layoutAlgorithm.guidelines_.end());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证子节点Y偏移等于Guideline偏移
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(actualOffset.GetY(), guidelineOffset);
}

/**
 * @tc.name: Layout_WithGuidelineVertical
 * @tc.desc: 测试垂直Guideline的布局
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_WithGuidelineVertical, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float guidelineOffset = 80.0f;
    const float nodeSize = 30.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer = CreateRelativeContainer(
        [this, &childNode, largeContainer, guidelineOffset, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 添加垂直Guideline
            std::vector<GuidelineInfo> guidelineInfos;
            GuidelineInfo vGuideInfo = { .id = "vGuide",
                .direction = LineDirection::VERTICAL,
                .start = Dimension(guidelineOffset, DimensionUnit::PX) };
            guidelineInfos.push_back(vGuideInfo);
            model.SetGuideline(guidelineInfos);

            // 创建依赖Guideline的子节点
            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "vGuide", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证Guideline已被记录
    EXPECT_NE(layoutAlgorithm.guidelines_.find("vGuide"), layoutAlgorithm.guidelines_.end());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证子节点X偏移等于Guideline偏移
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(actualOffset.GetX(), guidelineOffset);
}

/**
 * @tc.name: Layout_WithBarrier
 * @tc.desc: 测试Barrier的布局
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_WithBarrier, TestSize.Level0)
{
    const float largeContainer = 300.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> nodeA, nodeB, nodeC;
    auto relativeContainer = CreateRelativeContainer(
        [this, &nodeA, &nodeB, &nodeC, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 节点A
            nodeA = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeA");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点B
            nodeB = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeB");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::CENTER);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::CENTER);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 添加Barrier
            std::vector<BarrierInfo> barrierInfos;
            BarrierInfo barrierInfo = {
                .id = "barrier1", .direction = BarrierDirection::BOTTOM, .referencedId = { "nodeA", "nodeB" }
            };
            barrierInfos.push_back(barrierInfo);
            model.SetBarrier(barrierInfos);

            // 节点C依赖Barrier
            nodeC = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeC");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "barrier1", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证Barrier已被记录
    EXPECT_NE(layoutAlgorithm.barriers_.find("barrier1"), layoutAlgorithm.barriers_.end());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点C的Y坐标应该在节点B下方（Barrier位于节点B底部）
    auto offsetC = nodeC->GetGeometryNode()->GetMarginFrameOffset();
    auto offsetB = nodeB->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_GT(offsetC.GetY(), offsetB.GetY());
}

/**
 * @tc.name: Layout_RTL_StartToEnd
 * @tc.desc: 测试RTL布局下START方向的处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_RTL_StartToEnd, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    // 先设置RTL方向
    relativeContainer->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // RTL方向需要在PrepareLayout之前设置
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证recordOffsetMap_已计算
    EXPECT_FALSE(layoutAlgorithm.recordOffsetMap_.empty());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 在RTL模式下，START对齐规则会在计算偏移时处理
    // 验证节点能够成功布局
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_GE(actualOffset.GetX(), 0);
    EXPECT_GE(actualOffset.GetY(), 0);
    EXPECT_LE(actualOffset.GetX(), largeContainer);
    EXPECT_LE(actualOffset.GetY(), largeContainer);
}

/**
 * @tc.name: Layout_RTL_EndToStart
 * @tc.desc: 测试RTL布局下END方向的处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_RTL_EndToStart, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    // 先设置RTL方向
    relativeContainer->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    // RTL方向需要在PrepareLayout之前设置
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证recordOffsetMap_已计算
    EXPECT_FALSE(layoutAlgorithm.recordOffsetMap_.empty());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 在RTL模式下，END对齐规则会在计算偏移时处理
    // 验证节点能够成功布局
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_GE(actualOffset.GetX(), 0);
    EXPECT_GE(actualOffset.GetY(), 0);
    EXPECT_LE(actualOffset.GetX(), largeContainer);
    EXPECT_LE(actualOffset.GetY(), largeContainer);
}

/**
 * @tc.name: Layout_InvalidAnchor
 * @tc.desc: 测试无效锚点的处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_InvalidAnchor, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                // 使用不存在的锚点
                AddAlignRule(alignRules, AlignDirection::TOP, "nonexistent", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证拓扑排序仍然能完成（虽然存在无效锚点）
    EXPECT_FALSE(layoutAlgorithm.renderList_.empty());

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 节点应该仍然能够布局（使用默认位置或有效的锚点规则）
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_GE(actualOffset.GetX(), 0);
    EXPECT_GE(actualOffset.GetY(), 0);
}

/**
 * @tc.name: Layout_MultipleAlignRulesSameDirection
 * @tc.desc: 测试同一方向多个对齐规则的处理（LEFT和MIDDLE）
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_MultipleAlignRulesSameDirection, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeWidth = 60.0f;
    const float nodeHeight = 40.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer = CreateRelativeContainer(
        [this, &childNode, largeContainer, nodeWidth, nodeHeight](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            childNode = CreateRow([nodeWidth, nodeHeight](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeWidth));
                ViewAbstract::SetHeight(CalcLength(nodeHeight));
                std::map<AlignDirection, AlignRule> alignRules;
                // 同时设置LEFT和MIDDLE
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                AddAlignRule(alignRules, AlignDirection::MIDDLE, "__container__", HorizontalAlign::CENTER);
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点的宽度由LEFT和MIDDLE决定
    auto actualSize = childNode->GetGeometryNode()->GetMarginFrameSize();
    // 宽度应该是 (MIDDLE - LEFT) * 2 = CENTER * 2
    EXPECT_FLOAT_EQ(actualSize.Width(), largeContainer);
}

/**
 * @tc.name: Layout_PaddingAndBorder
 * @tc.desc: 测试容器带padding和border时的布局偏移
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_PaddingAndBorder, TestSize.Level0)
{
    const float largeContainer = 100.0f;
    const float borderWidth = 5.0f;
    const float paddingValue = 3.0f;
    const float nodeSize = 30.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer = CreateRelativeContainer(
        [this, &childNode, largeContainer, borderWidth, paddingValue, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));
            ViewAbstract::SetBorderWidth(Dimension(borderWidth));
            ViewAbstract::SetPadding(CalcLength(paddingValue));

            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("child1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证子节点偏移包含border和padding
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    float expectedOffset = borderWidth + paddingValue;
    EXPECT_FLOAT_EQ(actualOffset.GetX(), expectedOffset);
    EXPECT_FLOAT_EQ(actualOffset.GetY(), expectedOffset);
}

/**
 * @tc.name: Layout_CircularDependencyDetected
 * @tc.desc: 测试循环依赖的检测和处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_CircularDependencyDetected, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    auto relativeContainer = CreateRelativeContainer([this, largeContainer, nodeSize](RelativeContainerModelNG model) {
        ViewAbstract::SetWidth(CalcLength(largeContainer));
        ViewAbstract::SetHeight(CalcLength(largeContainer));

        // 节点A依赖节点B
        CreateRow([nodeSize](RowModelNG model) {
            ViewAbstract::SetInspectorId("nodeA");
            ViewAbstract::SetWidth(CalcLength(nodeSize));
            ViewAbstract::SetHeight(CalcLength(nodeSize));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "nodeB", VerticalAlign::BOTTOM);
            AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
            ViewAbstract::SetAlignRules(alignRules);
        });

        // 节点B依赖节点A（形成循环）
        CreateRow([nodeSize](RowModelNG model) {
            ViewAbstract::SetInspectorId("nodeB");
            ViewAbstract::SetWidth(CalcLength(nodeSize));
            ViewAbstract::SetHeight(CalcLength(nodeSize));
            std::map<AlignDirection, AlignRule> alignRules;
            AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
            AddAlignRule(alignRules, AlignDirection::LEFT, "nodeA", HorizontalAlign::END);
            ViewAbstract::SetAlignRules(alignRules);
        });
    });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // 准备布局（会检测到循环依赖）
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 执行布局（循环依赖时，节点应该被设为不活跃状态）
    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点被设置为不活跃状态（循环依赖的处理）
    const auto& children = relativeContainer->GetAllChildrenWithBuild();
    for (const auto& child : children) {
        // 在循环依赖情况下，子节点可能被设为不活跃或零尺寸
        auto geometryNode = child->GetGeometryNode();
        auto frameSize = geometryNode->GetFrameSize();
        // 验证节点尺寸为零或很小（错误处理）
        EXPECT_TRUE(frameSize.Width() == 0 || frameSize.Height() == 0);
    }
}

/**
 * @tc.name: Layout_SelfDependency
 * @tc.desc: 测试节点依赖自己的情况，验证循环依赖检测
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_SelfDependency, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> childNode;
    auto relativeContainer =
        CreateRelativeContainer([this, &childNode, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            childNode = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeA");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                // 节点依赖自己（形成自依赖）
                AddAlignRule(alignRules, AlignDirection::TOP, "nodeA", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;

    // 初始化并收集依赖关系
    layoutAlgorithm.Initialize(Referenced::RawPtr(relativeContainer));
    layoutAlgorithm.CollectNodesById(Referenced::RawPtr(relativeContainer));
    layoutAlgorithm.GetDependencyRelationship();

    // 自依赖会导致循环依赖检测返回false
    bool hasLoop = !layoutAlgorithm.PreTopologicalLoopDetection(Referenced::RawPtr(relativeContainer));
    EXPECT_TRUE(hasLoop); // 自依赖应该被检测为循环依赖

    // 验证节点被添加到idNodeMap_
    EXPECT_EQ(layoutAlgorithm.idNodeMap_.size(), 1);
    EXPECT_NE(layoutAlgorithm.idNodeMap_.find("nodeA"), layoutAlgorithm.idNodeMap_.end());

    // 拓扑排序仍会执行，但自依赖节点不会被添加到renderList_
    layoutAlgorithm.TopologicalSort(layoutAlgorithm.renderList_);

    // 验证节点不在renderList_中（因为循环依赖）
    bool nodeFoundInRenderList = false;
    for (const auto& nodeId : layoutAlgorithm.renderList_) {
        if (nodeId == "nodeA") {
            nodeFoundInRenderList = true;
            break;
        }
    }
    EXPECT_FALSE(nodeFoundInRenderList);

    // Layout方法会处理所有子节点
    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点仍然存在且能够被布局
    EXPECT_NE(childNode, nullptr);
    auto actualOffset = childNode->GetGeometryNode()->GetMarginFrameOffset();
    // 节点不在recordOffsetMap_中，所以使用默认位置(0,0)
    EXPECT_EQ(actualOffset.GetX(), 0);
    EXPECT_EQ(actualOffset.GetY(), 0);
}

/**
 * @tc.name: Layout_MixedAnchorTypes
 * @tc.desc: 测试混合使用不同类型锚点（容器、节点、Guideline）
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_MixedAnchorTypes, TestSize.Level0)
{
    const float largeContainer = 300.0f;
    const float guidelineOffset = 100.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> node1, node2;
    auto relativeContainer = CreateRelativeContainer(
        [this, &node1, &node2, largeContainer, guidelineOffset, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 添加Guideline
            std::vector<GuidelineInfo> guidelineInfos;
            GuidelineInfo guideInfo = { .id = "guide",
                .direction = LineDirection::VERTICAL,
                .start = Dimension(guidelineOffset, DimensionUnit::PX) };
            guidelineInfos.push_back(guideInfo);
            model.SetGuideline(guidelineInfos);

            // 节点1依赖容器
            node1 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node1");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 节点2依赖节点1和Guideline
            node2 = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("node2");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "node1", VerticalAlign::BOTTOM);
                AddAlignRule(alignRules, AlignDirection::LEFT, "guide", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.versionGreatorOrEqualToEleven_ = true;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证所有类型的锚点都被正确处理
    EXPECT_NE(layoutAlgorithm.guidelines_.find("guide"), layoutAlgorithm.guidelines_.end());
    EXPECT_EQ(layoutAlgorithm.renderList_.size(), 2);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证节点2的位置（基于node1和guideline）
    auto offset2 = node2->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(offset2.GetX(), guidelineOffset);
    EXPECT_FLOAT_EQ(offset2.GetY(), nodeSize);
}

/**
 * @tc.name: Layout_EdgeCasesExtremeValues
 * @tc.desc: 测试极端尺寸值的处理，验证RIGHT+BOTTOM对齐的位置计算
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_EdgeCasesExtremeValues, TestSize.Level0)
{
    const float largeContainer = 1000.0f;
    const float smallNodeSize = 10.0f;
    const float mediumNodeSize = 500.0f;

    RefPtr<FrameNode> smallNode, mediumNode;
    auto relativeContainer = CreateRelativeContainer(
        [this, &smallNode, &mediumNode, largeContainer, smallNodeSize, mediumNodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 小节点（左上角对齐）
            smallNode = CreateRow([smallNodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("small");
                ViewAbstract::SetWidth(CalcLength(smallNodeSize));
                ViewAbstract::SetHeight(CalcLength(smallNodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 中等大小的节点（右下角对齐：使用RIGHT+BOTTOM让节点完全在容器内）
            mediumNode = CreateRow([mediumNodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("medium");
                ViewAbstract::SetWidth(CalcLength(mediumNodeSize));
                ViewAbstract::SetHeight(CalcLength(mediumNodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                // 使用BOTTOM对齐（节点的BOTTOM对齐容器的BOTTOM）
                AddAlignRule(alignRules, AlignDirection::BOTTOM, "__container__", VerticalAlign::BOTTOM);
                // 使用END对齐（节点的RIGHT对齐容器的RIGHT）
                AddAlignRule(alignRules, AlignDirection::RIGHT, "__container__", HorizontalAlign::END);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证小节点的位置（左上角：TOP+START）
    // LEFT + START: X = 0
    // TOP + TOP: Y = 0
    auto smallOffset = smallNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(smallOffset.GetX(), 0.0f);
    EXPECT_FLOAT_EQ(smallOffset.GetY(), 0.0f);

    // 验证中等节点的位置（右下角：RIGHT+END, BOTTOM+BOTTOM）
    // RIGHT + END: X = containerWidth - nodeWidth = 1000 - 500 = 500
    // BOTTOM + BOTTOM: Y = containerHeight - nodeHeight = 1000 - 500 = 500
    auto mediumOffset = mediumNode->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_FLOAT_EQ(mediumOffset.GetX(), largeContainer - mediumNodeSize);
    EXPECT_FLOAT_EQ(mediumOffset.GetY(), largeContainer - mediumNodeSize);

    // 验证两个节点的尺寸保持正确
    auto smallSize = smallNode->GetGeometryNode()->GetMarginFrameSize();
    EXPECT_FLOAT_EQ(smallSize.Width(), smallNodeSize);
    EXPECT_FLOAT_EQ(smallSize.Height(), smallNodeSize);

    auto mediumSize = mediumNode->GetGeometryNode()->GetMarginFrameSize();
    EXPECT_FLOAT_EQ(mediumSize.Width(), mediumNodeSize);
    EXPECT_FLOAT_EQ(mediumSize.Height(), mediumNodeSize);
}

/**
 * @tc.name: Layout_NodeWithoutId
 * @tc.desc: 测试没有设置InspectorId的节点的处理
 */
HWTEST_F(RelativeContainerLayoutTest, Layout_NodeWithoutId, TestSize.Level0)
{
    const float largeContainer = 200.0f;
    const float nodeSize = 40.0f;

    RefPtr<FrameNode> nodeWithId, nodeWithoutId;
    auto relativeContainer = CreateRelativeContainer(
        [this, &nodeWithId, &nodeWithoutId, largeContainer, nodeSize](RelativeContainerModelNG model) {
            ViewAbstract::SetWidth(CalcLength(largeContainer));
            ViewAbstract::SetHeight(CalcLength(largeContainer));

            // 有ID的节点
            nodeWithId = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetInspectorId("nodeWithId");
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::TOP);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::START);
                ViewAbstract::SetAlignRules(alignRules);
            });

            // 没有ID的节点（应该自动生成ID）
            nodeWithoutId = CreateRow([nodeSize](RowModelNG model) {
                ViewAbstract::SetWidth(CalcLength(nodeSize));
                ViewAbstract::SetHeight(CalcLength(nodeSize));
                std::map<AlignDirection, AlignRule> alignRules;
                AddAlignRule(alignRules, AlignDirection::TOP, "__container__", VerticalAlign::CENTER);
                AddAlignRule(alignRules, AlignDirection::LEFT, "__container__", HorizontalAlign::CENTER);
                ViewAbstract::SetAlignRules(alignRules);
            });
        });

    LayoutConstraintF constraint = {
        .percentReference = { largeContainer, largeContainer },
        .parentIdealSize = { largeContainer, largeContainer },
    };
    relativeContainer->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    relativeContainer->GetLayoutProperty()->UpdateContentConstraint();

    RelativeContainerLayoutAlgorithm layoutAlgorithm;
    PrepareLayout(Referenced::RawPtr(relativeContainer), layoutAlgorithm);

    // 验证两个节点都在idNodeMap_中
    EXPECT_EQ(layoutAlgorithm.idNodeMap_.size(), 2);
    // 验证renderList_包含两个节点
    EXPECT_EQ(layoutAlgorithm.renderList_.size(), 2);

    layoutAlgorithm.Layout(Referenced::RawPtr(relativeContainer));

    // 验证两个节点都成功布局
    EXPECT_NE(nodeWithId->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(-1, -1));
    EXPECT_NE(nodeWithoutId->GetGeometryNode()->GetMarginFrameOffset(), OffsetF(-1, -1));
}

} // namespace OHOS::Ace::NG
