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

#include "text_input_base.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
namespace OHOS::Ace::NG {
class TextFieldPatternOnWillTest : public TextInputBases {
public:
};

/**
 * @tc.name: OnWillChange001
 * @tc.desc: Test TextPattern insert one number, the order of onWillEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternOnWillTest, OnWillChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    int triggerTime = 0;
    int orderWillInsert,orderWillChange,orderDidInsert,orderChange=0,0,0,0;
    auto callbackWillInsert = [&triggerTime, &orderWillInsert](const InsertValueInfo& info){ 
        triggerTime = triggerTime + 1;
        orderWillInsert = triggerTime
        return (triggerTime, orderWillInsert); 
        };
    auto callbackWillChange = [&triggerTime, &orderWillChange](const InsertValueInfo& info){ 
        triggerTime = triggerTime + 1;
        orderWillChange = triggerTime
        return (triggerTime, orderWillChange); 
    };
    auto callbackDidInsert = [&triggerTime, &orderDidInsert](const InsertValueInfo& info){ 
        triggerTime = triggerTime + 1;
        orderDidInsert = triggerTime
        return (triggerTime, orderDidInsert); 
    };
    auto callbackChange = [&triggerTime, &orderChange](const InsertValueInfo& info){ 
        triggerTime = triggerTime + 1;
        orderChange = triggerTime
        return (triggerTime, orderChange); 
    };
    CreateTextField("", "", [](TextFieldModelNG model) {
        model->SetOnWillInsertValueEvent(std::move(callbackWillInsert));
        model->SetOnWillInsertValueEvent(std::move(callbackWillChange));
        model->SetOnWillInsertValueEvent(std::move(callbackDidInsert));
        model->SetOnWillInsertValueEvent(std::move(callbackChange));
    });
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->Insert("1",0)
    FlushLayoutTask(textFieldNode);

    std::cout<<"triggerTime "<<triggerTime<<std::endl;
    
}

}