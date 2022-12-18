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

#define private public
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/dialog_event_hub.h"
#include "core/components_ng/pattern/dialog/dialog_layout_algorithm.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"

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
const int32_t buttonIdx = 1;
const double_t WIDTH_A = 32.0;
const double_t WIDTH_B = 48.0;
const double_t WIDTH_C = 64.0;
const double_t WIDTH_D = 80.0;
const double_t WIDTH_E = 112.0;
const double_t DIVISOR = 2.0;
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

    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    EXPECT_EQ(dialog == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator002
 * @tc.desc: Test ActionSheet dialog with alignment
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
        .type = DialogType::ALERT_DIALOG,
        .title = TITLE,
        .content = MESSAGE,
        .alignment = DialogAlignment::BOTTOM,
        .sheetsInfo = sheetItems,
    };

    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    EXPECT_EQ(dialog == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator003
 * @tc.desc: Test ActionSheet dialog with image icon (internal source)
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator003, TestSize.Level1)
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
        .type = DialogType::ACTION_SHEET,
        .title = TITLE,
        .content = MESSAGE,
        .sheetsInfo = sheetItems,
    };

    auto dialog = DialogView::CreateDialogNode(props, nullptr);
    EXPECT_EQ(dialog == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator004
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator004, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->onCancel_ = nullptr;
    dialogEventHub->FireCancelEvent();
    EXPECT_EQ(dialogEventHub->onCancel_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator005
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator005, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->FireCancelEvent();
    EXPECT_EQ(dialogEventHub->onCancel_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator006
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator006, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->onSuccess_ = nullptr;
    dialogEventHub->FireSuccessEvent(buttonIdx);
    EXPECT_EQ(dialogEventHub->onSuccess_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0007
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0007, TestSize.Level1)
{
    auto dialogEventHub = AceType::MakeRefPtr<DialogEventHub>();
    dialogEventHub->FireSuccessEvent(buttonIdx);
    EXPECT_EQ(dialogEventHub->onSuccess_ == nullptr, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0008
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0008, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::SM, DeviceType::WATCH);
    EXPECT_EQ(Width, WIDTH_A);
}

/**
 * @tc.name: DialogFrameNodeCreator0009
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0009, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::MD, DeviceType::WATCH);
    EXPECT_EQ(Width, WIDTH_B);
}

/**
 * @tc.name: DialogFrameNodeCreator0010
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0010, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::LG, DeviceType::WATCH);
    EXPECT_EQ(Width, WIDTH_C);
}

/**
 * @tc.name: DialogFrameNodeCreator0011
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0011, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width =
        dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::UNDEFINED, DeviceType::WATCH);
    EXPECT_EQ(Width, WIDTH_C);
}

/**
 * @tc.name: DialogFrameNodeCreator0012
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0012, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::SM, DeviceType::PHONE);
    EXPECT_EQ(Width, WIDTH_B);
}

/**
 * @tc.name: DialogFrameNodeCreator0013
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0013, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::MD, DeviceType::PHONE);
    EXPECT_EQ(Width, WIDTH_C);
}

/**
 * @tc.name: DialogFrameNodeCreator0014
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0014, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::LG, DeviceType::PHONE);
    EXPECT_EQ(Width, WIDTH_D);
}

/**
 * @tc.name: DialogFrameNodeCreator0015
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0015, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width =
        dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::UNDEFINED, DeviceType::PHONE);
    EXPECT_EQ(Width, WIDTH_D);
}

/**
 * @tc.name: DialogFrameNodeCreator0016
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0016, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::SM, DeviceType::CAR);
    EXPECT_EQ(Width, WIDTH_B);
}

/**
 * @tc.name: DialogFrameNodeCreator0017
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0017, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::MD, DeviceType::CAR);
    EXPECT_EQ(Width, WIDTH_D);
}

/**
 * @tc.name: DialogFrameNodeCreator0018
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0018, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width = dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::LG, DeviceType::CAR);
    EXPECT_EQ(Width, WIDTH_E);
}

/**
 * @tc.name: DialogFrameNodeCreator0019
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0019, TestSize.Level1)
{
    auto columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::CAR_DIALOG);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    auto Width =
        dialogLayoutAlgorithm->GetMaxWidthBasedOnGridType(columnInfo, GridSizeType::UNDEFINED, DeviceType::CAR);
    EXPECT_EQ(Width, WIDTH_E);
}

/**
 * @tc.name: DialogFrameNodeCreator0020
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0020, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::DEFAULT;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: DialogFrameNodeCreator0021
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0021, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::TOP;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0022
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0022, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::CENTER;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0023
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0023, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::BOTTOM;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0024
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0024, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::TOP_START;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0025
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0025, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::TOP_END;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0026
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0026, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::CENTER_START;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0027
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0027, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::CENTER_END;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0028
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0028, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::BOTTOM_START;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: DialogFrameNodeCreator0029
 * @tc.desc: Test AlertDialog with button color and text color
 * @tc.type: FUNC
 * @tc.author: zhoutianer
 */
HWTEST_F(DialogPatternTestNg, DialogFrameNodeCreator0029, TestSize.Level1)
{
    auto maxSize = SizeF(WIDTH_B, WIDTH_C);
    auto childSize = SizeF(WIDTH_D, WIDTH_E);
    auto dialogLayoutAlgorithm = AceType::MakeRefPtr<DialogLayoutAlgorithm>();
    OffsetF topLeftPoint =
        OffsetF(maxSize.Width() - childSize.Width(), maxSize.Height() - childSize.Height()) / DIVISOR;
    dialogLayoutAlgorithm->alignment_ = DialogAlignment::BOTTOM_END;
    auto result = dialogLayoutAlgorithm->SetAlignmentSwitch(maxSize, childSize, topLeftPoint);
    EXPECT_EQ(result, true);
}
} // namespace OHOS::Ace::NG