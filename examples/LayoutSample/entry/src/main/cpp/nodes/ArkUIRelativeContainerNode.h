/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef MYAPPLICATION_ARKUIRELATIVECONTAINERNODE_H
#define MYAPPLICATION_ARKUIRELATIVECONTAINERNODE_H

#include "ArkUINode.h"
#include "nodes/ArkUIColumnNode.h"
#include "nodes/ArkUIRowNode.h"

namespace NativeModule {

class ArkUIRelativeContainerNode : public ArkUINode {
private:
    // 布局相关常量
    static constexpr float DEFAULT_BIAS_VALUE = 1.0f;           // 默认偏移值
    static constexpr int DEFAULT_GUIDELINE_COUNT = 2;           // 默认引导线数量
    static constexpr float DEFAULT_GUIDELINE_POSITION = 50.0f;  // 默认引导线位置
    
    // 引导线索引常量
    static constexpr int FIRST_GUIDELINE_INDEX = 0;             // 第一条引导线索引
    static constexpr int SECOND_GUIDELINE_INDEX = 1;            // 第二条引导线索引
    
    // 引导线ID常量
    static constexpr const char* VERTICAL_GUIDELINE_ID = "guideline1";    // 垂直引导线ID
    static constexpr const char* HORIZONTAL_GUIDELINE_ID = "guideline2";  // 水平引导线ID
    
    // 容器ID常量
    static constexpr const char* CONTAINER_ID = "__container__"; // 容器ID

public:
    ArkUIRelativeContainerNode()
        : ArkUINode(
              (NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_RELATIVE_CONTAINER)) {}

    ~ArkUIRelativeContainerNode() override {}

    void SetGuideline(void *guideline)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { .object = guideline };
        nativeModule_->setAttribute(handle_, NODE_RELATIVE_CONTAINER_GUIDE_LINE, &item);
    }

    std::string alignRuleOptionExample(std::shared_ptr<ArkUIColumnNode> child1,
                                       std::shared_ptr<ArkUIColumnNode> child2,
                                       std::shared_ptr<ArkUIColumnNode> child3)
    {
        assert(handle_);
        std::string rules;
        // Create alignRules and set its values.
        // child1对齐规则 在父容器中间偏离0.1 0.1
        auto alignRules1 = OH_ArkUI_AlignmentRuleOption_Create();
        OH_ArkUI_AlignmentRuleOption_SetStart(alignRules1, CONTAINER_ID,
                                              ArkUI_HorizontalAlignment::ARKUI_HORIZONTAL_ALIGNMENT_CENTER);
        OH_ArkUI_AlignmentRuleOption_SetTop(alignRules1, CONTAINER_ID,
                                            ArkUI_VerticalAlignment::ARKUI_VERTICAL_ALIGNMENT_CENTER);
        OH_ArkUI_AlignmentRuleOption_SetBiasHorizontal(alignRules1, DEFAULT_BIAS_VALUE);
        OH_ArkUI_AlignmentRuleOption_SetBiasVertical(alignRules1, DEFAULT_BIAS_VALUE);
        rules +=
            "child1 StartAlignment: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetStartAlignment(alignRules1));
        rules += "\n";
        rules += "child1 TopAlignment: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetTopAlignment(alignRules1));
        rules += "\n";
        rules +=
            "child1 BiasHorizontal: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetBiasHorizontal(alignRules1));
        rules += "\n";
        rules += "child1 BiasVertical: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetBiasVertical(alignRules1));
        child1->SetAlignRules(alignRules1);
        // Destroy alignRules.
        OH_ArkUI_AlignmentRuleOption_Dispose(alignRules1);

        // child2对齐规则  在child1上方
        auto alignRules2 = OH_ArkUI_AlignmentRuleOption_Create();
        OH_ArkUI_AlignmentRuleOption_SetEnd(alignRules2, child1->GetId(),
                                            ArkUI_HorizontalAlignment::ARKUI_HORIZONTAL_ALIGNMENT_END);
        OH_ArkUI_AlignmentRuleOption_SetBottom(alignRules2, child1->GetId(),
                                               ArkUI_VerticalAlignment::ARKUI_VERTICAL_ALIGNMENT_TOP);
        rules += "\n";
        rules += "child2 EndAlignment: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetEndAlignment(alignRules2));
        rules += "\n";
        rules +=
            "child2 BottomAlignment: " + std::to_string(OH_ArkUI_AlignmentRuleOption_GetBottomAlignment(alignRules2));
        child2->SetAlignRules(alignRules2);
        // Destroy alignRules.
        OH_ArkUI_AlignmentRuleOption_Dispose(alignRules2);

        // child3对齐规则 在child1的右下方
        auto alignRules3 = OH_ArkUI_AlignmentRuleOption_Create();
        OH_ArkUI_AlignmentRuleOption_SetCenterHorizontal(alignRules3, child1->GetId(),
                                                         ArkUI_HorizontalAlignment::ARKUI_HORIZONTAL_ALIGNMENT_END);
        OH_ArkUI_AlignmentRuleOption_SetCenterVertical(alignRules3, child1->GetId(),
                                                       ArkUI_VerticalAlignment::ARKUI_VERTICAL_ALIGNMENT_BOTTOM);
        rules += "\n";
        rules += "child3 CenterAlignmentHorizontal: " +
                 std::to_string(OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentHorizontal(alignRules3));
        rules += "\n";
        rules += "child3 CenterAlignmentVertical: " +
                 std::to_string(OH_ArkUI_AlignmentRuleOption_GetCenterAlignmentVertical(alignRules3));
        child3->SetAlignRules(alignRules3);
        // Destroy alignRules.
        OH_ArkUI_AlignmentRuleOption_Dispose(alignRules3);

        nativeModule_->measureNode(handle_, OH_ArkUI_LayoutConstraint_Create());
        return rules;
    }

    std::string guidelineOptionExample(std::shared_ptr<ArkUIRowNode> row)
    {
        assert(handle_);
        auto guideline = OH_ArkUI_GuidelineOption_Create(DEFAULT_GUIDELINE_COUNT);
        OH_ArkUI_GuidelineOption_SetId(guideline, VERTICAL_GUIDELINE_ID, FIRST_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetId(guideline, HORIZONTAL_GUIDELINE_ID, SECOND_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetDirection(guideline, ARKUI_AXIS_VERTICAL, FIRST_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetDirection(guideline, ARKUI_AXIS_HORIZONTAL, SECOND_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetPositionStart(guideline, DEFAULT_GUIDELINE_POSITION, FIRST_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetPositionStart(guideline, DEFAULT_GUIDELINE_POSITION, SECOND_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetPositionEnd(guideline, DEFAULT_GUIDELINE_POSITION, FIRST_GUIDELINE_INDEX);
        OH_ArkUI_GuidelineOption_SetPositionEnd(guideline, DEFAULT_GUIDELINE_POSITION, SECOND_GUIDELINE_INDEX);
        SetGuideline(guideline);

        auto alignRules = OH_ArkUI_AlignmentRuleOption_Create();
        OH_ArkUI_AlignmentRuleOption_SetStart(alignRules, VERTICAL_GUIDELINE_ID,
                                              ArkUI_HorizontalAlignment::ARKUI_HORIZONTAL_ALIGNMENT_END);
        OH_ArkUI_AlignmentRuleOption_SetTop(alignRules, HORIZONTAL_GUIDELINE_ID,
                                            ArkUI_VerticalAlignment::ARKUI_VERTICAL_ALIGNMENT_TOP);
        row->SetAlignRules(alignRules);
        OH_ArkUI_AlignmentRuleOption_Dispose(alignRules);
        std::string guidelineStyle = "";
        guidelineStyle += "Id:" + std::string(OH_ArkUI_GuidelineOption_GetId(guideline, SECOND_GUIDELINE_INDEX));
        guidelineStyle += "\n";
        guidelineStyle +=
            "Direction:" + std::to_string(OH_ArkUI_GuidelineOption_GetDirection(guideline, SECOND_GUIDELINE_INDEX));
        guidelineStyle += "\n";
        guidelineStyle += "PositionStart:" + std::to_string(
            OH_ArkUI_GuidelineOption_GetPositionStart(guideline, SECOND_GUIDELINE_INDEX));
        guidelineStyle += "PositionEnd:" + std::to_string(
            OH_ArkUI_GuidelineOption_GetPositionEnd(guideline, SECOND_GUIDELINE_INDEX));
        guidelineStyle += "\n";
        OH_ArkUI_GuidelineOption_Dispose(guideline);
        return guidelineStyle;
    }
};

} // namespace NativeModule

#endif