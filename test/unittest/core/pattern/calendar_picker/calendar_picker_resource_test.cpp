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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/base/mock_system_properties.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar/calendar_pattern.h"
#include "core/common/resource/resource_object.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<CalendarPickerModel> CalendarPickerModel::instance_ = nullptr;

CalendarPickerModel* CalendarPickerModel::GetInstance()
{
    if (!instance_) {
        if (!instance_) {
            instance_.reset(new NG::CalendarPickerModelNG());
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class CalendarPickerResourceTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
    RefPtr<CalendarTheme> calendarTheme_;
};

void CalendarPickerResourceTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void CalendarPickerResourceTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void CalendarPickerResourceTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();
    calendarTheme_ = AceType::MakeRefPtr<CalendarTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void CalendarPickerResourceTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> CalendarPickerResourceTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else if (type == CalendarTheme::TypeId()) {
        return calendarTheme_;
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: CalendarPickerParseEdgeAlignResObj001
 * @tc.desc: Test ParseEdgeAlignResObj when ConfigChangePerform is not enabled.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerResourceTest, CalendarPickerParseEdgeAlignResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CalendarSettingData settingData;
    CalendarPickerModelNG calendarPickerModel;
    calendarPickerModel.Create(settingData);

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    EXPECT_EQ(element->GetTag(), V2::CALENDAR_PICKER_ETS_TAG);

    auto frameNode = AceType::DynamicCast<FrameNode>(element);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set CalendarPicker SetEdgeAlign.
     */
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset(10.0_vp, 10.0_vp);
    CalendarPickerModelNG::SetEdgeAlign(Referenced::RawPtr(frameNode), alignType, offset);
    DimensionOffset offsetResult = CalendarPickerModelNG::GetEdgeOffset(Referenced::RawPtr(frameNode));
    EXPECT_EQ(offsetResult, offset);

    /**
     * @tc.steps: step3. Call ParseEdgeAlignResObj to register the resourceObject callback function.
     */
    RefPtr<ResourceObject> dxResObj;
    RefPtr<ResourceObject> dyResObj;
    std::vector<RefPtr<ResourceObject>> resArray = { dxResObj, dyResObj };
    CalendarPickerModelNG::ParseEdgeAlignResObj(Referenced::RawPtr(frameNode), resArray);

    /**
     * @tc.steps: step4. Call the registered function through OnColorModeChange.
     * @tc.expected: Dut to ConfigChangePerform is not enabled, EdgeAlign will not be modified.
     */
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorModeChange(0);
    offsetResult = CalendarPickerModelNG::GetEdgeOffset(Referenced::RawPtr(frameNode));
    EXPECT_EQ(offsetResult, offset);
}

/**
 * @tc.name: CalendarPickerRemoveResObj001
 * @tc.desc: Test CalendarPickerRemoveResObj function.
 * @tc.type: FUNC
 */
HWTEST_F(CalendarPickerResourceTest, CalendarPickerRemoveResObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create CalendarPicker.
     */
    CalendarSettingData settingData;
    CalendarPickerModelNG::GetInstance()->Create(settingData);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set CalendarPicker SetEdgeAlign.
     */
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset(10.0_vp, 10.0_vp);
    CalendarPickerModelNG::GetInstance()->SetEdgeAlign(alignType, offset);

    /**
     * @tc.steps: step3. Set g_isConfigChangePerform to true.
     */
    g_isConfigChangePerform = true;
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->resourceMgr_ = AceType::MakeRefPtr<PatternResourceManager>();
    ASSERT_NE(pattern->resourceMgr_, nullptr);
    auto& resMap = pattern->resourceMgr_->resMap_;

    /**
     * @tc.steps: step4. Call ParseEdgeAlignResObj to register the resourceObject callback function.
     */
    RefPtr<ResourceObject> dxResObj;
    RefPtr<ResourceObject> dyResObj;
    std::vector<RefPtr<ResourceObject>> resArray = { dxResObj, dyResObj };
    CalendarPickerModelNG::GetInstance()->ParseEdgeAlignResObj(resArray);

    /**
     * @tc.steps: step5. Call CalendarPickerRemoveResObj to remove the resourceObject.
     */
    EXPECT_FALSE(resMap.find("CalendarPicker.EdgeAlign") == resMap.end());
    CalendarPickerModelNG::GetInstance()->CalendarPickerRemoveResObj("CalendarPicker.EdgeAlign");
    EXPECT_EQ(pattern->resourceMgr_, nullptr);
}

} // namespace OHOS::Ace::NG
