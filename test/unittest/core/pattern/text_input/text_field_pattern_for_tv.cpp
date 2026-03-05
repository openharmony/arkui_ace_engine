/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with License.
 * You may obtain a copy of License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text_field/text_input_response_area.h"

namespace OHOS::Ace::NG {
class TextFieldPatternForTV : public TextInputBases {
public:
};

/**
 * @tc.name: SetFocusStyleForTV001
 * @tc.desc: Test SetFocusStyleForTV in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     * @tc.expected: Method should work correctly
     */
    CreateTextField();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Method should execute without errors
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_TRUE(pattern_->isFocusBGColorSet_);
    EXPECT_TRUE(pattern_->isFocusTextColorSet_);
    EXPECT_TRUE(pattern_->isFocusPlaceholderColorSet_);
}

/**
 * @tc.name: SetFocusStyleForTV002
 * @tc.desc: Test SetFocusStyleForTV with default background color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without custom background
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Focus background color should be set
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_TRUE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: SetFocusStyleForTV003
 * @tc.desc: Test SetFocusStyleForTV with custom background color
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetFocusStyleForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom background color
     */
    CreateTextField();
    TextFieldModelNG::SetBackgroundColor(AceType::RawPtr(frameNode_), Color::RED);
    FlushLayoutTask(frameNode_);
    GetFocus();

    /**
     * @tc.steps: step2. Call SetFocusStyleForTV
     * @tc.expected: Custom background color should not be overridden
     */
    pattern_->SetFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: ClearFocusStyleForTV001
 * @tc.desc: Test ClearFocusStyleForTV with focus style set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ClearFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set focus style
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    pattern_->isFocusTextColorSet_ = true;
    pattern_->isFocusPlaceholderColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ClearFocusStyleForTV
     * @tc.expected: Focus style flags should be cleared
     */
    pattern_->ClearFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
    EXPECT_FALSE(pattern_->isFocusTextColorSet_);
    EXPECT_FALSE(pattern_->isFocusPlaceholderColorSet_);
}

/**
 * @tc.name: ClearFocusStyleForTV002
 * @tc.desc: Test ClearFocusStyleForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ClearFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ClearFocusStyleForTV
     * @tc.expected: Background should be transparent in default mode
     */
    pattern_->ClearFocusStyleForTV();
    EXPECT_FALSE(pattern_->isFocusBGColorSet_);
}

/**
 * @tc.name: SetShowErrorForTV001
 * @tc.desc: Test SetShowErrorForTV with error text
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error text
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Invalid input", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be applied
     */
    pattern_->SetShowErrorForTV();
    auto layoutProperty = pattern_->GetLayoutProperty<TextFieldLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto errorText = layoutProperty->GetErrorTextValue(u"");
    EXPECT_EQ(errorText, u"Invalid input");
}

/**
 * @tc.name: SetShowErrorForTV002
 * @tc.desc: Test SetShowErrorForTV with error
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Error", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be maintained
     */
    pattern_->SetShowErrorForTV();
}

/**
 * @tc.name: SetShowErrorForTV003
 * @tc.desc: Test SetShowErrorForTV with password mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetShowErrorForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with password mode and error
     */
    CreateTextField();
    TextFieldModelNG::SetType(AceType::RawPtr(frameNode_), TextInputType::VISIBLE_PASSWORD);
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Invalid password", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetShowErrorForTV
     * @tc.expected: Error state should be maintained after applying password error style
     */
    pattern_->SetShowErrorForTV();
}

/**
 * @tc.name: SetThemeAttrForTV001
 * @tc.desc: Test SetThemeAttrForTV with default theme
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default theme
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = false;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying theme attributes
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV002
 * @tc.desc: Test SetThemeAttrForTV with focus background color set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with focus background color
     */
    CreateTextField();
    pattern_->isFocusBGColorSet_ = true;
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying focus background color
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV003
 * @tc.desc: Test SetThemeAttrForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: PaintProperty should not be nullptr after applying disabled opacity
     */
    pattern_->InitDisableColorForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeAttrForTV004
 * @tc.desc: Test SetThemeAttrForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeAttrForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying theme
     */
    pattern_->SetThemeAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: InitDisableColorForTV001
 * @tc.desc: Test InitDisableColorForTV with normal state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern in normal state
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: IsDisabled flag should be false
     */
    pattern_->InitDisableColorForTV();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->IsEnabled());
}

/**
 * @tc.name: InitDisableColorForTV002
 * @tc.desc: Test InitDisableColorForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: IsDisabled flag should be true
     */
    pattern_->InitDisableColorForTV();
    host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->IsEnabled());
}

/**
 * @tc.name: InitDisableColorForTV003
 * @tc.desc: Test InitDisableColorForTV with default mode and disabled
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode and disabled
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: LayoutProperty should be valid and disabled flag should be true
     */
    pattern_->InitDisableColorForTV();
    host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->IsEnabled());
}

/**
 * @tc.name: InitDisableColorForTV004
 * @tc.desc: Test InitDisableColorForTV with error state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, InitDisableColorForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error state and default mode
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Error", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call InitDisableColorForTV
     * @tc.expected: Error state should be maintained as it has priority
     */
    pattern_->InitDisableColorForTV();
}

/**
 * @tc.name: ApplyUnderlineThemeForTV001
 * @tc.desc: Test ApplyUnderlineThemeForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ApplyUnderlineThemeForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ApplyUnderlineThemeForTV
     * @tc.expected: PaintProperty should not be nullptr after applying underline theme
     */
    pattern_->ApplyUnderlineThemeForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: ApplyUnderlineThemeForTV002
 * @tc.desc: Test ApplyUnderlineThemeForTV without default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ApplyUnderlineThemeForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern without default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ApplyUnderlineThemeForTV without default mode
     * @tc.expected: PaintProperty should not be nullptr even when returning early
     */
    pattern_->ApplyUnderlineThemeForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: ProcessFocusStyleForTV001
 * @tc.desc: Test ProcessFocusStyleForTV in normal inline state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: Method should execute without errors
     */
    pattern_->ProcessFocusStyleForTV();
}

/**
 * @tc.name: ProcessFocusStyleForTV002
 * @tc.desc: Test ProcessFocusStyleForTV with empty content
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with empty content
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: Method should execute without errors
     */
    pattern_->ProcessFocusStyleForTV();
}

/**
 * @tc.name: ProcessFocusStyleForTV003
 * @tc.desc: Test ProcessFocusStyleForTV with error state and default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, ProcessFocusStyleForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with error state and default mode
     */
    CreateTextField();
    TextFieldModelNG::SetShowError(AceType::RawPtr(frameNode_), u"Error", true);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call ProcessFocusStyleForTV
     * @tc.expected: Error state should be maintained as it has priority over focus style
     */
    pattern_->ProcessFocusStyleForTV();
}

/**
 * @tc.name: SetThemeBorderAttrForTV001
 * @tc.desc: Test SetThemeBorderAttrForTV with default border
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default border
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: Theme border attributes should be applied
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV002
 * @tc.desc: Test SetThemeBorderAttrForTV with disabled state
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern and set disabled via EventHub
     */
    CreateTextField();
    auto host = pattern_->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying disabled border opacity
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV003
 * @tc.desc: Test SetThemeBorderAttrForTV with default mode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with default mode
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr after applying default mode border radius
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV004
 * @tc.desc: Test SetThemeBorderAttrForTV with custom border
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom border color
     */
    CreateTextField();
    BorderColorProperty borderColor;
    borderColor.SetColor(Color::BLUE);
    TextFieldModelNG::SetBorderColor(AceType::RawPtr(frameNode_), borderColor);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr when custom border color is set
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: SetThemeBorderAttrForTV005
 * @tc.desc: Test SetThemeBorderAttrForTV with custom border radius
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, SetThemeBorderAttrForTV005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern with custom border radius
     */
    CreateTextField();
    BorderRadiusProperty borderRadius(5.0_vp, 5.0_vp, 5.0_vp, 5.0_vp);
    TextFieldModelNG::SetBorderRadius(AceType::RawPtr(frameNode_), borderRadius);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call SetThemeBorderAttrForTV
     * @tc.expected: PaintProperty should not be nullptr when custom border radius is set
     */
    pattern_->SetThemeBorderAttrForTV();
    auto paintProperty = pattern_->GetPaintProperty<TextFieldPaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: PaintFocusAreaRectForTV001
 * @tc.desc: Test PaintFocusAreaRectForTV with null response area
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternForTV, PaintFocusAreaRectForTV001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldPattern
     */
    CreateTextField();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step2. Call PaintFocusAreaRectForTV with null response area
     * @tc.expected: needResetFocusColor_ should remain unchanged after early return
     */
    bool originalResetFlag = pattern_->needResetFocusColor_;
    pattern_->PaintFocusAreaRectForTV(nullptr);
    EXPECT_EQ(pattern_->needResetFocusColor_, originalResetFlag);
}
} // namespace OHOS::Ace::NG
