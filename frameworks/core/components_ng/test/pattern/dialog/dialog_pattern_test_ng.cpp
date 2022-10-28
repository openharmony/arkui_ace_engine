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

#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string SHEET_TITLE = "sheet item";
const std::string SHEET_TITLE_2 = "sheet item 2";
const std::string SHEET_TITLE_3 = "sheet item 3";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";

const std::string TITLE = "This is title";
const std::string MESSAGE = "Message";

} // namespace

class DialogPatternTestNg : public testing::Test {
public:
protected:
    RefPtr<FrameNode> CreateDialog();
};

/**
 * @tc.name: DialogFrameNodeCreator001
 * @tc.desc: Test ActionSheet dialog with image icon (internal source)
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Dialog with properties
     */
    vector<ActionSheetInfo> sheetItems = {
        ActionSheetInfo {
            .title = SHEET_TITLE,
            .icon = INTERNAL_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_2,
            .icon = INTERNAL_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_3,
            .icon = INTERNAL_SOURCE,
        },
    };
    DialogProperties props = {
        .sheetsInfo = sheetItems,
    };

    DialogView::CreateDialogNode(props, nullptr);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
}

/**
 * @tc.name: DialogFrameNodeCreator002
 * @tc.desc: Test ActionSheet dialog with image icon (file source)
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Dialog with properties
     */
    vector<ActionSheetInfo> sheetItems = {
        ActionSheetInfo {
            .title = SHEET_TITLE,
            .icon = FILE_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_2,
            .icon = FILE_SOURCE,
        },
        ActionSheetInfo {
            .title = SHEET_TITLE_3,
            .icon = FILE_SOURCE,
        },
    };
    DialogProperties props = {
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .content = MESSAGE,
        .alignment = DialogAlignment::BOTTOM,
        .sheetsInfo = sheetItems,
    };

    DialogView::CreateDialogNode(props, nullptr);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    /**
     * @tc.steps: step2. check if properties are initiated correctly
     */
    EXPECT_EQ(frameNode == nullptr, false);
    auto pattern = frameNode->GetPattern<DialogPattern>();
    EXPECT_EQ(pattern->GetMessage(), MESSAGE);
    EXPECT_EQ(pattern->GetTitle(), TITLE);
}

} // namespace OHOS::Ace::NG
