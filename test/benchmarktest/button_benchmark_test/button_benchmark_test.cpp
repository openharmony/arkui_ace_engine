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

#include <benchmark/benchmark.h>
#include <iostream>

#include "arkoala_api_generated.h"
#include "benchmark_assert.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/color.h"
#include "core/components_ng/pattern/button/button_model_static.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace std;

namespace OHOS::Ace::NG {
extern "C" const OH_AnyAPI* GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind kind, int version);
namespace {
    // attrs
    const auto BUTTON_SIZE_ACE = Dimension(5);
    const auto BUTTON_BG_COLOR_ACE = Color::RED;
    const PaddingProperty BUTTON_MARGIN_ACE = {
        CalcLength(5.0f), CalcLength(5.0f), CalcLength(5.0f), CalcLength(5.0f) };
    const BorderWidthProperty BUTTON_BORDER_WIDTH_ACE = { 1.0_vp, 1.0_vp, 1.0_vp, 1.0_vp };
    const BorderColorProperty BUTTON_BORDER_COLOR_ACE = { Color::BLUE, Color::BLUE, Color::BLUE, Color::BLUE };
    const DimensionOffset BUTTON_PIVOT_ACE = DimensionOffset(Dimension(0), Dimension(0));
    const NG::Vector5F BUTTON_ROTATE_ACE = {0, 0, 1, 300, 0};
    const auto BUTTON_LABEL_ACE = "click";
    const auto BUTTON_TYPE_ACE = static_cast<int>(ButtonType::CIRCLE);
    
    const auto BUTTON_SIZE_CAPI = Converter::ArkValue<Opt_Length>(5.0_px);
    const auto BUTTON_BG_COLOR_CAPI = Converter::ArkValue<Opt_ResourceColor>(
        Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_RED));
    const auto BUTTON_MARGIN_CAPI =
        Converter::ArkUnion<Opt_Union_Margin_Length_LocalizedMargin, Ark_Length>(
            Converter::ArkValue<Ark_Length>(5.0_px));
    const auto BUTTON_BORDER_WIDTH_CAPI =
        Converter::ArkUnion<Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths, Ark_Length>(
            Converter::ArkValue<Ark_Length>(1.0_vp));
    const auto BUTTON_BORDER_COLOR_CAPI =
        Converter::ArkUnion<Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors, Ark_ResourceColor>(
            Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE));

    const Ark_RotateOptions BUTTON_PIVOT_ROTATE_CAPI_TMP = {
        Converter::ArkValue<Opt_Number>(0), //ROTATE - 1: x
        Converter::ArkValue<Opt_Number>(0), //ROTATE - 2: y
        Converter::ArkValue<Opt_Number>(1), //ROTATE - 3: z
        Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(0), //PIVOT: x
        Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(0), //PIVOT: y
        Converter::ArkValue<Opt_Number>(Ark_Empty()), //PIVOT: z
        Converter::ArkValue<Opt_Number>(0), //ROTATE 5: perspective
        Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(300) //ROTATE 4: angle
    };

    const auto BUTTON_ALIGN_CAPI = Converter::ArkValue<Opt_Alignment>(Ark_Alignment::ARK_ALIGNMENT_START);
    const auto BUTTON_PIVOT_ROTATE_CAPI = Converter::ArkValue<Opt_RotateOptions>(BUTTON_PIVOT_ROTATE_CAPI_TMP);
    const auto BUTTON_LABEL_CAPI = Converter::ArkUnion<Ark_ResourceStr, Ark_String>("click");
    const auto BUTTON_TYPE_CAPI = Converter::ArkValue<Opt_ButtonType>(Ark_ButtonType::ARK_BUTTON_TYPE_CIRCLE);
}

class BenchmarkButtonTest : public benchmark::Fixture {
public:
    BenchmarkButtonTest()
    {
        Iterations(iterations);
        Repetitions(repetitions);
        ReportAggregatesOnly(true);
    }

    ~BenchmarkButtonTest() override = default;
    Ark_NodeHandle node_ = nullptr;

    auto GetId()
    {
        return ElementRegister::GetInstance()->MakeUniqueId();
    }

    Ark_NodeHandle CreateNode()
    {
        return static_cast<Ark_NodeHandle>(CreateNodeImpl());
    }

    virtual void *CreateNodeImpl()
    {
        return (modifier_) ? modifier_->construct(GetId(), 0) : nullptr;
    }

    virtual void DisposeNode(Ark_NodeHandle &node)
    {
        if (basicAPI_) {
            basicAPI_->disposeNode(node);
        }
        node = nullptr;
    }

    void SetUp(const ::benchmark::State& state) override
    {
        MockPipelineContext::SetUp();

        themeManager_ = AceType::MakeRefPtr<::testing::NiceMock<MockThemeManager>>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        themeConstants_->LoadTheme(0);
        SetupTheme<ButtonTheme>();
        MockThemeStyle::GetInstance()->SetAttributes({});
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
    };

    void TearDown(const ::benchmark::State& state) override
    {
        MockPipelineContext::GetCurrent()->SetTaskExecutor(nullptr);
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        themeManager_ = nullptr;
        themeConstants_ = nullptr;
    }

    template<typename Theme>
    static void SetupTheme()
    {
        auto theme = typename Theme::Builder().Build(themeConstants_);
        ON_CALL(*themeManager_, GetTheme(Theme::TypeId())).WillByDefault(testing::Return(theme));
        ON_CALL(*themeManager_, GetTheme(Theme::TypeId(), testing::_)).WillByDefault(testing::Return(theme));
    }

protected:
    const int32_t repetitions = 3;
    const int32_t iterations = 1000;
    inline static RefPtr<::testing::NiceMock<MockThemeManager>> themeManager_;
    inline static RefPtr<ThemeConstants> themeConstants_;
    
    inline static const GENERATED_ArkUIBasicNodeAPI *basicAPI_
        = reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_BASIC,
            GENERATED_ARKUI_BASIC_NODE_API_VERSION)
        );
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL,
            GENERATED_ARKUI_FULL_API_VERSION)
        );
    const GENERATED_ArkUINodeModifiers *nodeModifiers_
        = fullAPI_ ? fullAPI_->getNodeModifiers() : nullptr;

    const GENERATED_ArkUIButtonModifier *modifier_
        = nodeModifiers_ && nodeModifiers_->getButtonModifier ? nodeModifiers_->getButtonModifier() : nullptr;

    const GENERATED_ArkUICommonMethodModifier *commonModifier_
        = nodeModifiers_ ? (nodeModifiers_->getCommonMethodModifier)() : nullptr;
};

/**
 * @tc.name: test_button_WARM_UP_CPU
 * @tc.desc: WARM_UP_CPU
 * @tc.type: FUNC
 */
BENCHMARK_F(BenchmarkButtonTest, test_button_WARM_UP_CPU)(benchmark::State& state)
{
    while (state.KeepRunning()) {
        auto frameNode = ButtonModelStatic::CreateFrameNode(GetId());
        AssertUnequal(frameNode, nullptr, "ButtonNode is nullptr.", state);
        ViewAbstractModelStatic::SetWidth(Referenced::RawPtr(frameNode), BUTTON_SIZE_ACE);
        ViewAbstractModelStatic::SetHeight(Referenced::RawPtr(frameNode), BUTTON_SIZE_ACE);
        ButtonModelStatic::BackgroundColor(Referenced::RawPtr(frameNode), BUTTON_BG_COLOR_ACE, true);
        ViewAbstractModelStatic::SetMargin(Referenced::RawPtr(frameNode), BUTTON_MARGIN_ACE);
        ViewAbstractModelStatic::SetBorderWidth(Referenced::RawPtr(frameNode), BUTTON_BORDER_WIDTH_ACE);
        ViewAbstractModelStatic::SetBorderColor(Referenced::RawPtr(frameNode), BUTTON_BORDER_COLOR_ACE);
        ViewAbstract::SetPivot(Referenced::RawPtr(frameNode), BUTTON_PIVOT_ACE);
        ViewAbstract::SetRotate(Referenced::RawPtr(frameNode), BUTTON_ROTATE_ACE);
        ViewAbstractModelStatic::SetAlign(Referenced::RawPtr(frameNode), Alignment::CENTER_LEFT);
        ButtonModelStatic::SetLabel(Referenced::RawPtr(frameNode), BUTTON_LABEL_ACE);
        ButtonModelStatic::SetType(Referenced::RawPtr(frameNode), BUTTON_TYPE_ACE);
        frameNode = nullptr;
    }
}

/**
 * @tc.name: test_button_ACE
 * @tc.desc: create, set attribute, destroy
 * @tc.type: FUNC
 */
BENCHMARK_F(BenchmarkButtonTest, test_button_ACE)(benchmark::State& state)
{
    while (state.KeepRunning()) {
        auto frameNode = ButtonModelStatic::CreateFrameNode(GetId());
        AssertUnequal(frameNode, nullptr, "ButtonNode is nullptr.", state);
        ViewAbstractModelStatic::SetWidth(Referenced::RawPtr(frameNode), BUTTON_SIZE_ACE);
        ViewAbstractModelStatic::SetHeight(Referenced::RawPtr(frameNode), BUTTON_SIZE_ACE);
        ButtonModelStatic::BackgroundColor(Referenced::RawPtr(frameNode), BUTTON_BG_COLOR_ACE, true);
        ViewAbstractModelStatic::SetMargin(Referenced::RawPtr(frameNode), BUTTON_MARGIN_ACE);
        ViewAbstractModelStatic::SetBorderWidth(Referenced::RawPtr(frameNode), BUTTON_BORDER_WIDTH_ACE);
        ViewAbstractModelStatic::SetBorderColor(Referenced::RawPtr(frameNode), BUTTON_BORDER_COLOR_ACE);
        ViewAbstract::SetPivot(Referenced::RawPtr(frameNode), BUTTON_PIVOT_ACE);
        ViewAbstract::SetRotate(Referenced::RawPtr(frameNode), BUTTON_ROTATE_ACE);
        ViewAbstractModelStatic::SetAlign(Referenced::RawPtr(frameNode), Alignment::CENTER_LEFT);
        ButtonModelStatic::SetLabel(Referenced::RawPtr(frameNode), BUTTON_LABEL_ACE);
        ButtonModelStatic::SetType(Referenced::RawPtr(frameNode), BUTTON_TYPE_ACE);
        frameNode = nullptr;
    }
}

/**
 * @tc.name: test_button_CAPI
 * @tc.desc: create, set attribute, destroy
 * @tc.type: FUNC
 */
BENCHMARK_F(BenchmarkButtonTest, test_button_CAPI)(benchmark::State& state)
{
    while (state.KeepRunning()) {
        node_ = CreateNode();
        AssertUnequal(node_, nullptr, "ButtonNode is nullptr.", state);
        AssertUnequal(commonModifier_, nullptr, "commonModifier_ is nullptr.", state);
        commonModifier_->setWidth0(node_, &BUTTON_SIZE_CAPI);
        commonModifier_->setHeight0(node_, &BUTTON_SIZE_CAPI);
        commonModifier_->setBackgroundColor0(node_, &BUTTON_BG_COLOR_CAPI);
        commonModifier_->setMargin(node_, &BUTTON_MARGIN_CAPI);
        commonModifier_->setBorderWidth(node_, &BUTTON_BORDER_WIDTH_CAPI);
        commonModifier_->setBorderColor(node_, &BUTTON_BORDER_COLOR_CAPI);
        commonModifier_->setRotate0(node_, &BUTTON_PIVOT_ROTATE_CAPI);
        commonModifier_->setAlign(node_, &BUTTON_ALIGN_CAPI);
        modifier_->setButtonOptions2(node_, &BUTTON_LABEL_CAPI, nullptr);
        modifier_->setType(node_, &BUTTON_TYPE_CAPI);

        DisposeNode(node_);
    }
}

}  // namespace OHOS::Ace::NG
// Run the benchmark
BENCHMARK_MAIN();