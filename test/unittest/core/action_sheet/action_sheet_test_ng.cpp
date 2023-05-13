/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/action_sheet/action_sheet_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const DimensionOffset ACTION_SHEET_OFFSET_DEFAULT = DimensionOffset(0.0_vp, -40.0_vp);
}
class ActionSheetTestNg : public testing::Test {};

HWTEST_F(ActionSheetTestNg, ActionSheetTest001, TestSize.Level1)
{
    ActionSheetModelNG actionSheetModelNG;

    ActionSheetInfo sheetInfo;
    auto func = [](const GestureEvent&) {};
    actionSheetModelNG.SetAction(func, sheetInfo);
    EXPECT_EQ(sheetInfo.action, nullptr);

    DialogProperties properties {
        .type = DialogType::ACTION_SHEET, .alignment = DialogAlignment::BOTTOM, .offset = ACTION_SHEET_OFFSET_DEFAULT
    };
    auto eventFunc = []() {};

    actionSheetModelNG.SetCancel(eventFunc, properties);
    EXPECT_EQ(properties.onCancel, nullptr);

    std::string buttonValue = "";
    ButtonInfo buttonInfo = { .text = buttonValue, .textColor = "blue" };
    actionSheetModelNG.SetConfirm(func, eventFunc, buttonInfo, properties);
    EXPECT_EQ(buttonInfo.action, nullptr);

    actionSheetModelNG.ShowActionSheet(properties);
}
}