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

#include "text_base.h"

#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {

class TextNullptrNg : public TextBases {
public:
};

/**
 * @tc.name: PipelineContextNullptr001
 * @tc.desc: test OnDetachFromFrameNode when pipelineContext is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TextNullptrNg, PipelineContextNullptr001, TestSize.Level0)
{
    /**
     * @tc.steps:
     * step1. mock pipeline context，return nullptr，call OnDetachFromFrameNode, not carsh
     * step2. call OnDetachFromFrameNode, not carsh
    */
    TextModelNG textModelNg;
    textModelNg.Create("123");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto textPattern = frameNode->GetPattern<TextPattern>();

    ASSERT_NE(textPattern, nullptr);
    textPattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
}

} // namespace OHOS::Ace::NG
