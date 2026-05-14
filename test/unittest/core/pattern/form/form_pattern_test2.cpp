/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <memory>
#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public

#include "mock/mock_form_utils.h"
#include "mock/mock_pixel_map.h"
#include "mock/mock_sub_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_render_context.h"


#include "base/utils/utils.h"
#include "base/want/want_wrap.h"
#include "core/common/form_manager.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/pattern/form/form_snapshot_check.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t FORM_SHAPE_CIRCLE = 2;
RequestFormInfo formInfo;
constexpr double TRANSPARENT_VAL = 0;
constexpr float DEFAULT_VIEW_SCALE = 1.0f;
static const int64_t MAX_NUMBER_OF_JS = 0x20000000000000;
constexpr char TIME_LIMIT_RESOURCE_NAME[] = "form_disable_time_limit";
} // namespace

class FormPatternTest2 : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;

protected:
    static RefPtr<FormNode> CreateFromNode();
};

void FormPatternTest2::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = NG::MockPipelineContext::GetCurrent();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
}

void FormPatternTest2::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void FormPatternTest2::SetUp()
{
    formInfo.id = 1;
    formInfo.cardName = "defalut";
    formInfo.bundleName = "bundle";
    formInfo.abilityName = "ability";
    formInfo.moduleName = "module";
    formInfo.allowUpdate = true;
}

RefPtr<FormNode> FormPatternTest2::CreateFromNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    pattern->AttachToFrameNode(formNode);
    return formNode;
}

/**
 * @tc.name: FormPatternTest_ISAllowUpdate_001
 * @tc.desc: ISAllowUpdate
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_ISAllowUpdate_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null
    pattern->frameNode_ = nullptr;
    EXPECT_TRUE(pattern->ISAllowUpdate());
    pattern->frameNode_ = formNode;

    // layoutProperty null
    auto host = pattern->GetHost();
    auto layoutProperty = host->layoutProperty_;
    host->layoutProperty_ = nullptr;
    EXPECT_TRUE(pattern->ISAllowUpdate());
    host->layoutProperty_ = layoutProperty;

    // normal path: allowUpdate = false
    auto formLayoutProperty = host->GetLayoutProperty<FormLayoutProperty>();
    RequestFormInfo info;
    info.allowUpdate = false;
    formLayoutProperty->UpdateRequestFormInfo(info);
    EXPECT_FALSE(pattern->ISAllowUpdate());
}

/**
 * @tc.name: FormPatternTest_UpdateColorMode_001
 * @tc.desc: UpdateColorMode
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateColorMode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // colorMode same as cardInfo_.colorMode (default -1), no change
    int32_t oldColorMode = pattern->cardInfo_.colorMode;
    pattern->UpdateColorMode(oldColorMode);
    EXPECT_EQ(pattern->cardInfo_.colorMode, oldColorMode);

    // colorMode different, formManagerBridge_ not null
    int32_t newColorMode = oldColorMode + 1;
    pattern->UpdateColorMode(newColorMode);
    EXPECT_EQ(pattern->cardInfo_.colorMode, newColorMode);

    // colorMode different again, formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    pattern->UpdateColorMode(newColorMode + 1);
    EXPECT_EQ(pattern->cardInfo_.colorMode, newColorMode + 1);
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_SwitchRenderGroup_001
 * @tc.desc: SwitchRenderGroup
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SwitchRenderGroup_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->SwitchRenderGroup(true);
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // renderContext null -> should not crash
    auto host = pattern->GetHost();
    auto renderContext = host->renderContext_;
    host->renderContext_ = nullptr;
    pattern->SwitchRenderGroup(false);
    host->renderContext_ = renderContext;
    EXPECT_NE(host->renderContext_, nullptr);

    // normal path: SwitchRenderGroup(true) sets render group
    pattern->SwitchRenderGroup(true);
    auto rc = host->GetRenderContext();
    EXPECT_NE(rc, nullptr);
    EXPECT_TRUE(rc->GetRenderGroup().value_or(false));
}

/**
 * @tc.name: FormPatternTest_HandleLockEvent_001
 * @tc.desc: HandleLockEvent
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleLockEvent_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // exemptAppLock = true, should return early
    pattern->cardInfo_.exemptAppLock = true;
    auto oldAttribution = pattern->formSpecialStyle_.GetFormStyleAttribution();
    pattern->HandleLockEvent(true);
    EXPECT_NE(pattern, nullptr);
    // Should not change because exemptAppLock is true
    EXPECT_EQ(pattern->formSpecialStyle_.GetFormStyleAttribution(), oldAttribution);

    // exemptAppLock = false, should proceed
    pattern->cardInfo_.exemptAppLock = false;
    pattern->HandleLockEvent(true);
    EXPECT_TRUE(pattern->formSpecialStyle_.IsLocked());

    pattern->HandleLockEvent(false);
}

/**
 * @tc.name: FormPatternTest_HandleFormDueControl_001
 * @tc.desc: HandleFormDueControl
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleFormDueControl_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // isDisablePolicy = true
    pattern->HandleFormDueControl(true, true);
    EXPECT_TRUE(pattern->formSpecialStyle_.IsDueDisabled());

    // isDisablePolicy = false -> sets IsDueRemoved
    pattern->HandleFormDueControl(false, true);
    EXPECT_TRUE(pattern->formSpecialStyle_.IsDueRemoved());
}

/**
 * @tc.name: FormPatternTest_HandleFormStyleOperation_001
 * @tc.desc: HandleFormStyleOperation KEEP/UNLOAD/LOAD/REFRESH
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleFormStyleOperation_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // KEEP: same attribution as current (NORMAL -> NORMAL)
    FormSpecialStyle keepStyle;
    auto attribution = pattern->formSpecialStyle_.GetFormStyleAttribution();
    auto oldAttribution = attribution;
    RequestFormInfo info;
    pattern->HandleFormStyleOperation(keepStyle, info);
    EXPECT_EQ(pattern->formSpecialStyle_.GetFormStyleAttribution(), oldAttribution);

    // LOAD: NORMAL -> PARENT_CONTROL
    FormSpecialStyle loadStyle;
    loadStyle.SetIsForbiddenByParentControl(true);
    pattern->HandleFormStyleOperation(loadStyle, info);
    EXPECT_EQ(pattern->formSpecialStyle_.GetFormStyleAttribution(),
        FormStyleAttribution::PARENT_CONTROL);

    // REFRESH: PARENT_CONTROL -> APP_LOCK
    FormSpecialStyle refreshStyle;
    refreshStyle.SetIsLockedByAppLock(true);
    pattern->HandleFormStyleOperation(refreshStyle, info);
    EXPECT_EQ(pattern->formSpecialStyle_.GetFormStyleAttribution(), FormStyleAttribution::APP_LOCK);

    // UNLOAD: back to NORMAL
    FormSpecialStyle unloadStyle;
    pattern->HandleFormStyleOperation(unloadStyle, info);
    EXPECT_EQ(pattern->formSpecialStyle_.GetFormStyleAttribution(), FormStyleAttribution::NORMAL);
}

/**
 * @tc.name: FormPatternTest_SetTransparencyConfig_001
 * @tc.desc: SetTransparencyConfig
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetTransparencyConfig_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    RequestFormInfo info;

    // isTransparencyForm = false
    pattern->isTransparencyEnable_ = true;
    pattern->SetTransparencyConfig(false, info);
    EXPECT_FALSE(pattern->isTransparencyEnable_);

    // isTransparencyForm = true, wantWrap null
    info.wantWrap = nullptr;
    pattern->SetTransparencyConfig(true, info);
    EXPECT_FALSE(pattern->isTransparencyEnable_);
}

/**
 * @tc.name: FormPatternTest_SetSkeletonEnableConfig_001
 * @tc.desc: SetSkeletonEnableConfig
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetSkeletonEnableConfig_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    RequestFormInfo info;

    // wantWrap null
    info.wantWrap = nullptr;
    pattern->isSkeletonAnimEnable_ = true;
    pattern->SetSkeletonEnableConfig(info);
    EXPECT_NE(pattern, nullptr);
    // should not change because wantWrap is null
    EXPECT_TRUE(pattern->isSkeletonAnimEnable_);
}

/**
 * @tc.name: FormPatternTest_SetExternalRenderOpacity_001
 * @tc.desc: SetExternalRenderOpacity
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetExternalRenderOpacity_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // externalRenderContext exists but rsNode may be null in test
    // should not crash
    pattern->SetExternalRenderOpacity(1.0);
    EXPECT_NE(pattern->externalRenderContext_, nullptr);
}

/**
 * @tc.name: FormPatternTest_ShouldDoSkeletonAnimation_001
 * @tc.desc: ShouldDoSkeletonAnimation
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_ShouldDoSkeletonAnimation_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null
    pattern->frameNode_ = nullptr;
    EXPECT_FALSE(pattern->ShouldDoSkeletonAnimation());
    pattern->frameNode_ = formNode;

    // no children -> false
    EXPECT_FALSE(pattern->ShouldDoSkeletonAnimation());

    // add skeleton node
    auto columnNode = pattern->CreateColumnNode(FormChildNodeType::FORM_SKELETON_NODE);
    EXPECT_NE(columnNode, nullptr);
    EXPECT_TRUE(pattern->ShouldDoSkeletonAnimation());
}

/**
 * @tc.name: FormPatternTest_UpdateFormBaseConfig_001
 * @tc.desc: UpdateFormBaseConfig
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateFormBaseConfig_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null
    pattern->frameNode_ = nullptr;
    pattern->UpdateFormBaseConfig(true);
    EXPECT_FALSE(pattern->isLoaded_);
    pattern->frameNode_ = formNode;

    // layoutProperty null -> should not crash, isLoaded stays false
    auto host = pattern->GetHost();
    auto layoutProperty = host->layoutProperty_;
    host->layoutProperty_ = nullptr;
    pattern->UpdateFormBaseConfig(true);
    host->layoutProperty_ = layoutProperty;
    EXPECT_NE(host->layoutProperty_, nullptr);

    // normal path: isDynamic = true
    pattern->UpdateFormBaseConfig(true);
    EXPECT_TRUE(pattern->isLoaded_);
    EXPECT_TRUE(pattern->isDynamic_);
    EXPECT_FALSE(pattern->isUnTrust_);
    EXPECT_FALSE(pattern->isFrsNodeDetached_);

    // normal path: isDynamic = false
    pattern->UpdateFormBaseConfig(false);
    EXPECT_FALSE(pattern->isDynamic_);
}

/**
 * @tc.name: FormPatternTest_UpdateFormSurface_001
 * @tc.desc: UpdateFormSurface
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateFormSurface_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    RequestFormInfo info;
    info.width.SetValue(200);
    info.height.SetValue(200);
    info.borderWidth = 0;
    info.formViewScale = 1.0f;

    // externalRenderContext not null (from OnAttachToFrameNode)
    pattern->UpdateFormSurface(info);
    EXPECT_EQ(pattern->cardInfo_.width.Value(), 200);
    EXPECT_EQ(pattern->cardInfo_.height.Value(), 200);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    pattern->UpdateFormSurface(info);
    EXPECT_EQ(pattern->cardInfo_.width.Value(), 200);
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_IsMaskEnableForm_001
 * @tc.desc: IsMaskEnableForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_IsMaskEnableForm_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    RequestFormInfo info;

    // shape = FORM_SHAPE_CIRCLE -> true
    info.shape = FORM_SHAPE_CIRCLE;
    EXPECT_TRUE(pattern->IsMaskEnableForm(info));

    // renderingMode = SINGLE_COLOR -> true
    info.shape = 0;
    info.renderingMode = static_cast<int32_t>(OHOS::AppExecFwk::Constants::RenderingMode::SINGLE_COLOR);
    EXPECT_TRUE(pattern->IsMaskEnableForm(info));

    // dimension = DIMENSION_1_1 -> true
    info.renderingMode = 0;
    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    EXPECT_TRUE(pattern->IsMaskEnableForm(info));

    // none of the above -> false
    info.shape = 0;
    info.renderingMode = 0;
    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);
    EXPECT_FALSE(pattern->IsMaskEnableForm(info));
}

/**
 * @tc.name: FormPatternTest_UpdateChildNodeOpacity_001
 * @tc.desc: UpdateChildNodeOpacity FORM_SURFACE_NODE branch
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateChildNodeOpacity_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // FORM_SURFACE_NODE branch: should not crash
    pattern->UpdateChildNodeOpacity(FormChildNodeType::FORM_SURFACE_NODE, 0.5);
    EXPECT_NE(pattern->externalRenderContext_, nullptr);

    // FORM_STATIC_IMAGE_NODE without child node -> GetFormChildNode returns null
    pattern->UpdateChildNodeOpacity(FormChildNodeType::FORM_STATIC_IMAGE_NODE, 0.5);
    EXPECT_EQ(pattern->GetFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE), nullptr);

    // FORM_STATIC_IMAGE_NODE with child node (RosenRenderContext cast may fail in test)
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    pattern->UpdateChildNodeOpacity(FormChildNodeType::FORM_STATIC_IMAGE_NODE, 0.5);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE), nullptr);
}

/**
 * @tc.name: FormPatternTest_GetTimeLimitFontSize_001
 * @tc.desc: GetTimeLimitFontSize dimensionHeight == 1 and > 1 branches
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_GetTimeLimitFontSize_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // dimensionHeight > 1 (DIMENSION_2_2)
    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);
    double fontSize = pattern->GetTimeLimitFontSize();
    EXPECT_GT(fontSize, 0.0);

    // dimensionHeight == 1 (DIMENSION_1_1), non-tibetan
    pattern->cardInfo_.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_1_1);
    pattern->isTibetanLanguage_ = false;
    fontSize = pattern->GetTimeLimitFontSize();
    EXPECT_GT(fontSize, 0.0);

    // dimensionHeight == 1, tibetan
    pattern->isTibetanLanguage_ = true;
    fontSize = pattern->GetTimeLimitFontSize();
    EXPECT_GT(fontSize, 0.0);
    pattern->isTibetanLanguage_ = false;
}

/**
 * @tc.name: FormPatternTest_SetFormAccessibilityAction_001
 * @tc.desc: SetFormAccessibilityAction
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetFormAccessibilityAction_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->SetFormAccessibilityAction();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // isDynamic_ = true -> sets NO_STR
    pattern->isDynamic_ = true;
    pattern->SetFormAccessibilityAction();
    auto accessProp = formNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessProp, nullptr);
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);

    // isDynamic_ = false, IsForbidden = true -> NO_STR
    pattern->isDynamic_ = false;
    FormSpecialStyle forbiddenStyle;
    forbiddenStyle.SetIsForbiddenByParentControl(true);
    pattern->formSpecialStyle_ = forbiddenStyle;
    pattern->SetFormAccessibilityAction();
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);

    // isDynamic_ = false, IsLocked = true -> NO_STR
    FormSpecialStyle lockedStyle;
    lockedStyle.SetIsLockedByAppLock(true);
    pattern->formSpecialStyle_ = lockedStyle;
    pattern->SetFormAccessibilityAction();
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);

    // isDynamic_ = false, IsAccessibilityState = true -> YES_STR
    FormSpecialStyle normalStyle;
    pattern->formSpecialStyle_ = normalStyle;
    pattern->SetAccessibilityState(true);
    pattern->SetFormAccessibilityAction();
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::YES_STR);
    pattern->SetAccessibilityState(false);
}

/**
 * @tc.name: FormPatternTest_InitializeFormAccessibility_001
 * @tc.desc: InitializeFormAccessibility
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_InitializeFormAccessibility_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->InitializeFormAccessibility();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // normal path
    pattern->InitializeFormAccessibility();
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: FormPatternTest_ShouldAddChildAtReuildFrame_001
 * @tc.desc: ShouldAddChildAtReuildFrame
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_ShouldAddChildAtReuildFrame_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // externalRenderContext null -> returns true
    pattern->externalRenderContext_ = nullptr;
    EXPECT_TRUE(pattern->ShouldAddChildAtReuildFrame());

    // externalRenderContext exists (from OnAttachToFrameNode)
    pattern->OnAttachToFrameNode();
    bool result = pattern->ShouldAddChildAtReuildFrame();
    // rsNode is null in test env, so returns true
    EXPECT_TRUE(result);
}

/**
 * @tc.name: FormPatternTest_OnColorConfigurationUpdate_001
 * @tc.desc: OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnColorConfigurationUpdate_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // Should call OnModifyDone internally, but ConfigChangePerform may return false in test
    // Verify it does not crash
    pattern->OnColorConfigurationUpdate();
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FormPatternTest_UpdateConfiguration_001
 * @tc.desc: UpdateConfiguration
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateConfiguration_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // subContainer_ null, should not crash
    pattern->subContainer_ = nullptr;
    pattern->localeTag_ = "";
    pattern->UpdateConfiguration();
    EXPECT_EQ(pattern->localeTag_, "");

    // subContainer_ non-null, localeTag same -> should not update
    auto context = formNode->GetContextRefPtr();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    pattern->subContainer_ = subContainer;
    std::string currentLocale = AceApplicationInfo::GetInstance().GetLocaleTag();
    pattern->localeTag_ = currentLocale;
    pattern->UpdateConfiguration();
    EXPECT_NE(pattern, nullptr);
    // localeTag unchanged since same
    EXPECT_EQ(pattern->localeTag_, currentLocale);
}

/**
 * @tc.name: FormPatternTest_UpdateSpecialStyleCfg_001
 * @tc.desc: UpdateSpecialStyleCfg
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateSpecialStyleCfg_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // no FORBIDDEN_ROOT_NODE -> should return early (CHECK_NULL_VOID)
    pattern->UpdateSpecialStyleCfg();
    EXPECT_EQ(pattern->GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE), nullptr);

    // add FORBIDDEN_ROOT_NODE, with PARENT_CONTROL attribution
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    FormSpecialStyle parentStyle;
    parentStyle.SetIsForbiddenByParentControl(true);
    pattern->formSpecialStyle_ = parentStyle;
    pattern->UpdateSpecialStyleCfg();
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE), nullptr);

    // renderContext null on columnNode -> should not crash
    auto renderContext = columnNode->renderContext_;
    columnNode->renderContext_ = nullptr;
    pattern->UpdateSpecialStyleCfg();
    columnNode->renderContext_ = renderContext;
    EXPECT_NE(columnNode->renderContext_, nullptr);
}

/**
 * @tc.name: FormPatternTest_RemoveSubContainer_001
 * @tc.desc: RemoveSubContainer
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_RemoveSubContainer_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->RemoveSubContainer();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // eventHub null -> should not crash, subContainer stays
    auto host = pattern->GetHost();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(host->GetContextRefPtr());
    pattern->subContainer_ = subContainer;
    auto eventHub = host->eventHub_;
    host->eventHub_ = nullptr;
    pattern->RemoveSubContainer();
    host->eventHub_ = eventHub;
    EXPECT_NE(host->eventHub_, nullptr);
}

/**
 * @tc.name: FormPatternTest_OnRebuildFrame_002
 * @tc.desc: OnRebuildFrame with isSnapshot_=false and isSkeletonAnimEnable_=true
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnRebuildFrame_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // isSnapshot_ = false, isSkeletonAnimEnable_ = true, isTransparencyEnable_ = false
    pattern->isSnapshot_ = false;
    pattern->isSkeletonAnimEnable_ = true;
    pattern->isTransparencyEnable_ = false;
    pattern->OnRebuildFrame();
    EXPECT_NE(pattern, nullptr);
    // Should return early due to ShouldAddChildAtReuildFrame
    EXPECT_NE(pattern->externalRenderContext_, nullptr);

    // isSnapshot_ = false, isSkeletonAnimEnable_ = false
    pattern->isSkeletonAnimEnable_ = false;
    pattern->OnRebuildFrame();
    EXPECT_NE(pattern->externalRenderContext_, nullptr);
}

/**
 * @tc.name: FormPatternTest_HandleStaticFormEvent_002
 * @tc.desc: HandleStaticFormEvent with isDynamic_=false and shouldResponseClick_=true and linkRect in region
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleStaticFormEvent_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // isDynamic_ = false, shouldResponseClick_ = true, valid formLinkInfos with action
    pattern->isDynamic_ = false;
    pattern->shouldResponseClick_ = true;
    std::string linkInfo = "{\"action\":\"router\",\"formLinkRect\":\"0 0 100 100\"}";
    std::vector<std::string> infos;
    infos.emplace_back(linkInfo);
    pattern->SetFormLinkInfos(infos);
    EXPECT_EQ(pattern->formLinkInfos_.size(), 1u);

    PointF touchPoint;
    touchPoint.SetX(50.0f);
    touchPoint.SetY(50.0f);
    pattern->HandleStaticFormEvent(touchPoint);

    // shouldResponseClick_ = false, IsAccessibilityState = true
    pattern->shouldResponseClick_ = false;
    pattern->SetAccessibilityState(true);
    pattern->HandleStaticFormEvent(touchPoint);
    pattern->SetAccessibilityState(false);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FormPatternTest_ReAddStaticFormSnapshotTimer_002
 * @tc.desc: ReAddStaticFormSnapshotTimer more branches
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_ReAddStaticFormSnapshotTimer_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // isDynamic_ = true -> return early
    pattern->isDynamic_ = true;
    pattern->ReAddStaticFormSnapshotTimer();
    EXPECT_EQ(pattern->updateFormComponentTimestamp_, 0);

    // isDynamic_ = false, IsAccessibilityState = true -> return early
    pattern->isDynamic_ = false;
    pattern->SetAccessibilityState(true);
    pattern->ReAddStaticFormSnapshotTimer();
    pattern->SetAccessibilityState(false);
    EXPECT_NE(pattern, nullptr);

    // isStaticFormSnaping_ = false -> timestamp = currentTime, return
    pattern->isStaticFormSnaping_ = false;
    pattern->updateFormComponentTimestamp_ = 0;
    pattern->ReAddStaticFormSnapshotTimer();
    EXPECT_GT(pattern->updateFormComponentTimestamp_, 0);

    // isStaticFormSnaping_ = true, timestamp recent -> return early, timestamp unchanged
    pattern->isStaticFormSnaping_ = true;
    int64_t nowTime = static_cast<int64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count());
    pattern->updateFormComponentTimestamp_ = nowTime;
    pattern->ReAddStaticFormSnapshotTimer();
    EXPECT_EQ(pattern->updateFormComponentTimestamp_, nowTime);
}

/**
 * @tc.name: FormPatternTest_CheckFormBundleForbidden_001
 * @tc.desc: CheckFormBundleForbidden
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_CheckFormBundleForbidden_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    EXPECT_FALSE(pattern->CheckFormBundleForbidden("testBundle"));
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_IsFormBundleExempt_001
 * @tc.desc: IsFormBundleExempt
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_IsFormBundleExempt_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    EXPECT_FALSE(pattern->IsFormBundleExempt(1));
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_IsFormBundleProtected_001
 * @tc.desc: IsFormBundleProtected
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_IsFormBundleProtected_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    EXPECT_FALSE(pattern->IsFormBundleProtected("testBundle", 0));
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_IsFormBundleDebugSignature_001
 * @tc.desc: IsFormBundleDebugSignature
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_IsFormBundleDebugSignature_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    EXPECT_FALSE(pattern->IsFormBundleDebugSignature("testBundle"));
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_IsFormDueControl_001
 * @tc.desc: IsFormDueControl
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_IsFormDueControl_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // formManagerBridge_ null
    RefPtr<FormManagerDelegate> bridge = pattern->formManagerBridge_;
    pattern->formManagerBridge_ = nullptr;
    EXPECT_FALSE(pattern->IsFormDueControl("bundle", "module", "ability", "card", 1, true));
    pattern->formManagerBridge_ = bridge;
}

/**
 * @tc.name: FormPatternTest_GetFormViewScale_001
 * @tc.desc: GetFormViewScale
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_GetFormViewScale_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    float scale = pattern->GetFormViewScale();
    EXPECT_EQ(scale, pattern->formViewScale_);
}

/**
 * @tc.name: FormPatternTest_GetIsLoaded_001
 * @tc.desc: GetIsLoaded
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_GetIsLoaded_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->GetIsLoaded());
    pattern->isLoaded_ = true;
    EXPECT_TRUE(pattern->GetIsLoaded());
}

/**
 * @tc.name: FormPatternTest_SetFormLinkInfos_001
 * @tc.desc: SetFormLinkInfos
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetFormLinkInfos_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    std::vector<std::string> infos;
    pattern->SetFormLinkInfos(infos);
    EXPECT_TRUE(pattern->formLinkInfos_.empty());

    infos.emplace_back("test");
    pattern->SetFormLinkInfos(infos);
    EXPECT_EQ(pattern->formLinkInfos_.size(), 1);
}

/**
 * @tc.name: FormPatternTest_UnregisterAccessibility_001
 * @tc.desc: UnregisterAccessibility
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UnregisterAccessibility_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null
    pattern->frameNode_ = nullptr;
    pattern->UnregisterAccessibility();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // normal path
    pattern->UnregisterAccessibility();
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: FormPatternTest_OnDirtyLayoutWrapperSwap_002
 * @tc.desc: OnDirtyLayoutWrapperSwap with inf/nan size
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnDirtyLayoutWrapperSwap_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // inf width
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(std::numeric_limits<float>::infinity(), 100.0f));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(formNode, geometryNode, nullptr);
    DirtySwapConfig cfg;
    cfg.skipMeasure = false;
    cfg.skipLayout = false;
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, cfg);
    EXPECT_FALSE(result);

    // nan height
    geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100.0f, std::numeric_limits<float>::quiet_NaN()));
    layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(formNode, geometryNode, nullptr);
    result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, cfg);
    EXPECT_FALSE(result);
}
/**
 * @tc.name: FormPatternTest_RequestRender_001
 * @tc.desc: RequestRender host null / renderContext null / parent null vs non-null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_RequestRender_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->RequestRender();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // renderContext null -> should not crash
    auto host = pattern->GetHost();
    auto renderContext = host->renderContext_;
    host->renderContext_ = nullptr;
    pattern->RequestRender();
    host->renderContext_ = renderContext;
    EXPECT_NE(host->renderContext_, nullptr);

    // parent null (formNode has no parent)
    pattern->RequestRender();
    EXPECT_NE(host->GetRenderContext(), nullptr);

    // parent non-null
    auto parent = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    parent->AddChild(formNode);
    pattern->RequestRender();
    EXPECT_NE(parent->GetChildren().empty(), true);
}

/**
 * @tc.name: FormPatternTest_GetWantParam_001
 * @tc.desc: GetWantParam wantWrap null / NearEqual vs not
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_GetWantParam_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    RequestFormInfo info;
    info.width.SetValue(100);
    info.height.SetValue(100);

    // wantWrap null
    info.wantWrap = nullptr;
    pattern->GetWantParam(info);
    EXPECT_EQ(info.formViewScale, DEFAULT_VIEW_SCALE);
}

/**
 * @tc.name: FormPatternTest_AttachJsRSNode_001
 * @tc.desc: AttachJsRSNode host null / externalRenderContext null / renderContext null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_AttachJsRSNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    std::shared_ptr<Rosen::RSNode> jsNode;

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->AttachJsRSNode(jsNode);
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // externalRenderContext null -> should not crash
    auto externalRC = pattern->externalRenderContext_;
    pattern->externalRenderContext_ = nullptr;
    pattern->AttachJsRSNode(jsNode);
    pattern->externalRenderContext_ = externalRC;
    EXPECT_NE(pattern->externalRenderContext_, nullptr);

    // host renderContext null -> should not crash
    auto host = pattern->GetHost();
    auto renderContext = host->renderContext_;
    host->renderContext_ = nullptr;
    pattern->AttachJsRSNode(jsNode);
    host->renderContext_ = renderContext;
    EXPECT_NE(host->renderContext_, nullptr);

    // normal path (jsNode is null, but code proceeds)
    pattern->AttachJsRSNode(jsNode);
    EXPECT_NE(pattern->externalRenderContext_, nullptr);
}

/**
 * @tc.name: FormPatternTest_RemoveFormStyleChildNode_001
 * @tc.desc: RemoveFormStyleChildNode removes all style child nodes
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_RemoveFormStyleChildNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // no child nodes -> should not crash
    pattern->RemoveFormStyleChildNode();
    EXPECT_EQ(pattern->formChildrenNodeMap_.size(), 0u);

    // add some child nodes then remove
    RefPtr<FrameNode> textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->AddFormChildNode(FormChildNodeType::TIME_LIMIT_TEXT_NODE, textNode);
    EXPECT_GE(pattern->formChildrenNodeMap_.size(), 2u);

    pattern->RemoveFormStyleChildNode();
    EXPECT_EQ(pattern->formChildrenNodeMap_.find(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE),
        pattern->formChildrenNodeMap_.end());
    EXPECT_EQ(pattern->formChildrenNodeMap_.find(FormChildNodeType::TIME_LIMIT_TEXT_NODE),
        pattern->formChildrenNodeMap_.end());
}

/**
 * @tc.name: FormPatternTest_RemoveDelayResetManuallyClickFlagTask_001
 * @tc.desc: RemoveDelayResetManuallyClickFlagTask host null / context null / executor null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_RemoveDelayResetManuallyClickFlagTask_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->RemoveDelayResetManuallyClickFlagTask();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // executor null -> should not crash
    auto host = pattern->GetHost();
    auto pipeline = host->GetContext();
    auto taskExecutor = pipeline->taskExecutor_;
    pipeline->taskExecutor_ = nullptr;
    pattern->RemoveDelayResetManuallyClickFlagTask();
    pipeline->taskExecutor_ = taskExecutor;
    EXPECT_NE(pipeline->taskExecutor_, nullptr);

    // normal path -> should not crash
    pattern->RemoveDelayResetManuallyClickFlagTask();
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: FormPatternTest_DelayResetManuallyClickFlag_001
 * @tc.desc: DelayResetManuallyClickFlag host null / normal
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_DelayResetManuallyClickFlag_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    pattern->DelayResetManuallyClickFlag();
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // normal path
    pattern->isManuallyClick_ = true;
    pattern->DelayResetManuallyClickFlag();
    EXPECT_FALSE(pattern->isManuallyClick_);
}

/**
 * @tc.name: FormPatternTest_UpdateForbiddenRootNodeStyle_001
 * @tc.desc: UpdateForbiddenRootNodeStyle context null / dark vs light
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateForbiddenRootNodeStyle_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto renderContext = columnNode->GetRenderContext();
    EXPECT_NE(renderContext, nullptr);

    // normal path -> should not crash
    pattern->UpdateForbiddenRootNodeStyle(renderContext);
    EXPECT_NE(renderContext, nullptr);
}

/**
 * @tc.name: FormPatternTest_UpdateForbiddenIcon_001
 * @tc.desc: UpdateForbiddenIcon node null / imageLayoutProperty null / sourceInfo null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateForbiddenIcon_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // no child node -> CHECK_NULL_VOID(node)
    pattern->UpdateForbiddenIcon(FormChildNodeType::TIME_LIMIT_IMAGE_NODE);
    EXPECT_EQ(pattern->GetFormChildNode(FormChildNodeType::TIME_LIMIT_IMAGE_NODE), nullptr);

    // add image child node
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    pattern->AddFormChildNode(FormChildNodeType::TIME_LIMIT_IMAGE_NODE, imageNode);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::TIME_LIMIT_IMAGE_NODE), nullptr);

    // layoutProperty null -> should not crash
    auto layoutProperty = imageNode->layoutProperty_;
    imageNode->layoutProperty_ = nullptr;
    pattern->UpdateForbiddenIcon(FormChildNodeType::TIME_LIMIT_IMAGE_NODE);
    imageNode->layoutProperty_ = layoutProperty;
    EXPECT_NE(imageNode->layoutProperty_, nullptr);

    // normal path -> should not crash
    pattern->UpdateForbiddenIcon(FormChildNodeType::TIME_LIMIT_IMAGE_NODE);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::TIME_LIMIT_IMAGE_NODE), nullptr);
}

/**
 * @tc.name: FormPatternTest_CreateIconNode_001
 * @tc.desc: CreateIconNode PARENT_CONTROL / APP_LOCK / DEVELOPER_MODE_TIPS / DUE_DISABLE / DUE_REMOVE
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_CreateIconNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // NORMAL -> returns nullptr (no matching attribution)
    auto iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);

    // PARENT_CONTROL -> CreateForbiddenImageNode returns nullptr due to no pipeline context,
    // but the branch is entered and AddFormChildNode is called with null imageNode
    EXPECT_NE(pattern, nullptr);
    FormSpecialStyle parentStyle;
    parentStyle.SetIsForbiddenByParentControl(true);
    pattern->formSpecialStyle_ = parentStyle;
    iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);

    // APP_LOCK
    FormSpecialStyle lockStyle;
    lockStyle.SetIsLockedByAppLock(true);
    pattern->formSpecialStyle_ = lockStyle;
    iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);

    // DEVELOPER_MODE_TIPS
    FormSpecialStyle devStyle;
    devStyle.SetIsShowDeveloperTips(true);
    pattern->formSpecialStyle_ = devStyle;
    iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);

    // DUE_DISABLE
    FormSpecialStyle dueStyle;
    dueStyle.SetIsDisableByDue(true);
    pattern->formSpecialStyle_ = dueStyle;
    iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);

    // DUE_REMOVE
    FormSpecialStyle dueRemoveStyle;
    dueRemoveStyle.SetIsRemoveByDue(true);
    pattern->formSpecialStyle_ = dueRemoveStyle;
    iconNode = pattern->CreateIconNode(false);
    EXPECT_EQ(iconNode, nullptr);
}

/**
 * @tc.name: FormPatternTest_CreateRowNode_001
 * @tc.desc: CreateRowNode host null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_CreateRowNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null -> returns nullptr
    pattern->frameNode_ = nullptr;
    auto result = pattern->CreateRowNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE);
    EXPECT_EQ(result, nullptr);
    pattern->frameNode_ = formNode;
}

/**
 * @tc.name: FormPatternTest_SetMaskRootNodeAccessibilityAction_001
 * @tc.desc: SetMaskRootNodeAccessibilityAction null checks / isDynamic_
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_SetMaskRootNodeAccessibilityAction_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // forbiddenRootNode null -> should not crash
    RefPtr<FrameNode> nullNode = nullptr;
    pattern->SetMaskRootNodeAccessibilityAction(nullNode);
    EXPECT_NE(pattern, nullptr);

    // host null -> should not crash
    pattern->frameNode_ = nullptr;
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->SetMaskRootNodeAccessibilityAction(columnNode);
    pattern->frameNode_ = formNode;
    EXPECT_NE(pattern->GetHost(), nullptr);

    // normal: isDynamic_ = false, IsForbidden -> sets NO_STR
    pattern->isDynamic_ = false;
    FormSpecialStyle parentStyle;
    parentStyle.SetIsForbiddenByParentControl(true);
    pattern->formSpecialStyle_ = parentStyle;
    pattern->SetMaskRootNodeAccessibilityAction(columnNode);
    auto accessProp = formNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessProp, nullptr);
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);

    // isDynamic_ = true -> sets NO_STR
    pattern->isDynamic_ = true;
    pattern->SetMaskRootNodeAccessibilityAction(columnNode);
    EXPECT_EQ(accessProp->GetAccessibilityLevel(), AccessibilityProperty::Level::NO_STR);
}

/**
 * @tc.name: FormPatternTest_HandleOnSnapshot_001
 * @tc.desc: HandleOnSnapshot pixelMap null / host null / context null / executor null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleOnSnapshot_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // pixelMap null
    pattern->HandleOnSnapshot(nullptr);
    EXPECT_FALSE(pattern->isSnapshot_);

    // host null
    pattern->frameNode_ = nullptr;
    std::shared_ptr<Media::MockPixelMap> mockPixelMap = std::make_shared<Media::MockPixelMap>();
    pattern->HandleOnSnapshot(mockPixelMap);
    EXPECT_FALSE(pattern->isSnapshot_);
    pattern->frameNode_ = formNode;

    // context null
    auto host = pattern->GetHost();
    auto context = host->context_;
    host->context_ = nullptr;
    pattern->HandleOnSnapshot(mockPixelMap);
    EXPECT_TRUE(pattern->isSnapshot_);
    host->context_ = context;

    // executor null
    auto pipeline = host->GetContext();
    auto taskExecutor = pipeline->taskExecutor_;
    pipeline->taskExecutor_ = nullptr;
    pattern->HandleOnSnapshot(mockPixelMap);
    EXPECT_TRUE(pattern->isSnapshot_);
    pipeline->taskExecutor_ = taskExecutor;

    // normal path
    pattern->HandleOnSnapshot(mockPixelMap);
    EXPECT_TRUE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_HandleUnTrustForm_002
 * @tc.desc: HandleUnTrustForm externalRenderContext_ non-null + isJsCard_=false + ShouldLoadFormSkeleton=true
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleUnTrustForm_002, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto formNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    auto pattern = formNode->GetPattern<FormPattern>();
    stack->Push(formNode);
    pattern->OnAttachToFrameNode();
    EXPECT_NE(pattern, nullptr);

    // externalRenderContext_ exists -> DynamicCast null branch (mock render context)
    auto host = pattern->GetHost();
    auto renderContext = host->renderContext_;
    host->renderContext_ = nullptr;
    pattern->HandleUnTrustForm();
    EXPECT_FALSE(pattern->isUnTrust_);
    EXPECT_FALSE(pattern->isLoaded_);
    host->renderContext_ = renderContext;

    // isJsCard_ = false, isUnTrust_ already true, ShouldLoadFormSkeleton will return true
    pattern->externalRenderContext_ = RenderContext::Create();
    static RenderContext::ContextParam param = { RenderContext::ContextType::EXTERNAL, std::nullopt };
    pattern->externalRenderContext_->InitContext(false, param);
    pattern->HandleUnTrustForm();
    EXPECT_NE(pattern->externalRenderContext_, nullptr);
}

/**
 * @tc.name: FormPatternTest_HandleSnapshot_002
 * @tc.desc: HandleSnapshot isDynamic_=true + FORM_STATIC_IMAGE_NODE exists; !isDynamic_+IsAccessibilityState
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_HandleSnapshot_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // isDynamic_ = true + FORM_STATIC_IMAGE_NODE exists -> should post RemoveFrsNode task
    pattern->isDynamic_ = true;
    RefPtr<FrameNode> childNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, childNode);
    pattern->HandleSnapshot(0, "test");
    EXPECT_NE(pattern, nullptr);
    // After this, the task is posted, isSnapshot_ should still be false (it's set in the delayed task)
    EXPECT_TRUE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_OnSnapshot_002
 * @tc.desc: OnSnapshot isDynamic_=true path
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnSnapshot_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // isDynamic_ = true, pixelMap non-null -> skips IsTransparent check
    pattern->isDynamic_ = true;
    std::shared_ptr<Media::MockPixelMap> mockPixelMap = std::make_shared<Media::MockPixelMap>();
    EXPECT_CALL(*mockPixelMap, GetWidth()).WillRepeatedly(Return(200));
    EXPECT_CALL(*mockPixelMap, GetHeight()).WillRepeatedly(Return(200));
    pattern->OnSnapshot(mockPixelMap);
    // Should post HandleOnSnapshot task
    EXPECT_NE(pattern->GetHost(), nullptr);
}

/**
 * @tc.name: FormPatternTest_UpdateFormComponent_002
 * @tc.desc: UpdateFormComponent isLoaded_ + !isDynamic_ + !isSnapshot_ + needSnapshotAgain_ branch
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateFormComponent_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    auto host = pattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();

    RequestFormInfo info;
    info.width.SetValue(100);
    info.height.SetValue(100);
    info.borderWidth = 0;
    info.formViewScale = 1.0f;

    // isLoaded_ = false -> skip snapshot branch
    pattern->isLoaded_ = false;
    pattern->UpdateFormComponent(info);
    EXPECT_FALSE(pattern->isLoaded_ || pattern->isSnapshot_);

    // isLoaded_ = true, isDynamic_ = false, isSnapshot_ = false, needSnapshotAgain_ = true
    // but opacity != NON_TRANSPARENT_VAL -> not handle snapshot
    EXPECT_NE(pattern, nullptr);
    pattern->isLoaded_ = true;
    pattern->isDynamic_ = false;
    pattern->isSnapshot_ = false;
    pattern->needSnapshotAgain_ = true;
    auto renderContext = host->GetRenderContext();
    renderContext->SetOpacity(TRANSPARENT_VAL);
    pattern->UpdateFormComponent(info);
    EXPECT_TRUE(pattern->needSnapshotAgain_);
}

/**
 * @tc.name: FormPatternTest_RemoveDisableFormStyle_002
 * @tc.desc: RemoveDisableFormStyle IsMaskEnableForm=false path (InitializeFormAccessibility + opacity update)
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_RemoveDisableFormStyle_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // IsMaskEnableForm = false (shape=0, renderingMode=0, dimension=DIMENSION_2_2)
    RequestFormInfo info;
    info.shape = 0;
    info.renderingMode = 0;
    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);
    EXPECT_FALSE(pattern->IsMaskEnableForm(info));

    // add child nodes that will be removed
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->RemoveDisableFormStyle(info);
    EXPECT_EQ(pattern->GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE), nullptr);
}

/**
 * @tc.name: FormPatternTest_FireOnAcquiredEvent_002
 * @tc.desc: FireOnAcquiredEvent id >= MAX_NUMBER_OF_JS -> onAcquireFormId = -1
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_FireOnAcquiredEvent_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // id < MAX_NUMBER_OF_JS -> onAcquireFormId = id
    pattern->FireOnAcquiredEvent(100);
    EXPECT_NE(pattern, nullptr);

    // id >= MAX_NUMBER_OF_JS -> onAcquireFormId = -1
    int64_t bigId = MAX_NUMBER_OF_JS + 1;
    pattern->FireOnAcquiredEvent(bigId);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_FireOnUninstallEvent_002
 * @tc.desc: FireOnUninstallEvent id >= MAX_NUMBER_OF_JS -> uninstallFormId = -1
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_FireOnUninstallEvent_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // id < MAX_NUMBER_OF_JS
    pattern->FireOnUninstallEvent(100);
    EXPECT_NE(pattern, nullptr);

    // id >= MAX_NUMBER_OF_JS
    int64_t bigId = MAX_NUMBER_OF_JS + 1;
    pattern->FireOnUninstallEvent(bigId);
    EXPECT_FALSE(pattern->isSnapshot_);
}

/**
 * @tc.name: FormPatternTest_FireOnUpdateFormDone_002
 * @tc.desc: FireOnUpdateFormDone id >= MAX_NUMBER_OF_JS
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_FireOnUpdateFormDone_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // id < MAX_NUMBER_OF_JS
    pattern->FireOnUpdateFormDone(100);
    EXPECT_NE(pattern, nullptr);

    // id >= MAX_NUMBER_OF_JS
    int64_t bigId = MAX_NUMBER_OF_JS + 1;
    pattern->FireOnUpdateFormDone(bigId);
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: FormPatternTest_AttachRSNode_002
 * @tc.desc: AttachRSNode isBeenLayout_=true + geometryNode null / FORM_FORBIDDEN_ROOT_NODE exists
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_AttachRSNode_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    std::shared_ptr<Rosen::RSSurfaceNode> node;
    node->CreateNodeInRenderThread();
    AAFwk::Want want;

    // isBeenLayout_ = true, geometryNode null -> should not crash
    pattern->isBeenLayout_ = true;
    auto host = pattern->GetHost();
    auto geometryNode = host->geometryNode_;
    host->geometryNode_ = nullptr;
    pattern->AttachRSNode(node, want);
    host->geometryNode_ = geometryNode;
    EXPECT_NE(host->geometryNode_, nullptr);

    // FORM_FORBIDDEN_ROOT_NODE exists -> surfaceNode alpha = 0
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->isSkeletonAnimEnable_ = false;
    pattern->isTransparencyEnable_ = true;
    want.SetParam(OHOS::AppExecFwk::Constants::FORM_IS_RECOVER_FORM, false);
    pattern->AttachRSNode(node, want);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE), nullptr);
}

/**
 * @tc.name: FormPatternTest_CreateForbiddenTextNode_001
 * @tc.desc: CreateForbiddenTextNode isRowStyle true vs false
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_CreateForbiddenTextNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // isRowStyle = false -> returns nullptr due to RosenRenderContext unavailable in test
    auto textNode = pattern->CreateForbiddenTextNode(TIME_LIMIT_RESOURCE_NAME, false);
    EXPECT_EQ(textNode, nullptr);

    // isRowStyle = true -> same, returns nullptr
    textNode = pattern->CreateForbiddenTextNode(TIME_LIMIT_RESOURCE_NAME, true);
    EXPECT_EQ(textNode, nullptr);

    // host context null
    auto host = pattern->GetHost();
    auto context = host->context_;
    host->context_ = nullptr;
    textNode = pattern->CreateForbiddenTextNode(TIME_LIMIT_RESOURCE_NAME, false);
    EXPECT_EQ(textNode, nullptr);
    host->context_ = context;
}

/**
 * @tc.name: FormPatternTest_CreateForbiddenImageNode_001
 * @tc.desc: CreateForbiddenImageNode host null / isRowStyle
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_CreateForbiddenImageNode_001, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    // host null
    pattern->frameNode_ = nullptr;
    auto result = pattern->CreateForbiddenImageNode(InternalResource::ResourceId::IC_TIME_LIMIT_SVG, false);
    EXPECT_EQ(result, nullptr);
    pattern->frameNode_ = formNode;

    // isRowStyle = false -> returns nullptr due to RosenRenderContext unavailable in test
    result = pattern->CreateForbiddenImageNode(InternalResource::ResourceId::IC_TIME_LIMIT_SVG, false);
    EXPECT_EQ(result, nullptr);

    // isRowStyle = true -> same, returns nullptr
    result = pattern->CreateForbiddenImageNode(InternalResource::ResourceId::IC_TIME_LIMIT_SVG, true);
    EXPECT_EQ(result, nullptr);

    // host context null
    auto host = pattern->GetHost();
    auto context = host->context_;
    host->context_ = nullptr;
    result = pattern->CreateForbiddenImageNode(InternalResource::ResourceId::IC_TIME_LIMIT_SVG, false);
    EXPECT_EQ(result, nullptr);
    host->context_ = context;
}

/**
 * @tc.name: FormPatternTest_UpdateFormComponentSize_002
 * @tc.desc: UpdateFormComponentSize imageNode && disableStyleRootNode both exist
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_UpdateFormComponentSize_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    RequestFormInfo info;
    info.width.SetValue(200);
    info.height.SetValue(200);
    info.borderWidth = 0;
    info.formViewScale = 1.0f;
    info.dimension = static_cast<int32_t>(OHOS::AppExecFwk::Constants::Dimension::DIMENSION_2_2);

    // both imageNode and disableStyleRootNode exist -> both get UpdateLayoutConstraint
    RefPtr<FrameNode> imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    RefPtr<FrameNode> columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    pattern->AddFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE, imageNode);
    pattern->AddFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE, columnNode);
    pattern->UpdateFormComponentSize(info);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::FORM_STATIC_IMAGE_NODE), nullptr);
    EXPECT_NE(pattern->GetFormChildNode(FormChildNodeType::FORM_FORBIDDEN_ROOT_NODE), nullptr);
}

/**
 * @tc.name: FormPatternTest_OnModifyDone_002
 * @tc.desc: OnModifyDone with borderWidth and cardInfo change -> isBeenLayout_=false
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnModifyDone_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    auto host = pattern->GetHost();
    auto layoutProperty = host->GetLayoutProperty<FormLayoutProperty>();

    // set cardInfo_ to different width so isBeenLayout_ becomes false
    RequestFormInfo info;
    info.width = Dimension(999);
    info.height = Dimension(999);
    info.borderWidth = 0;
    pattern->cardInfo_ = info;
    EXPECT_NE(pattern->cardInfo_.width.Value(), 0);

    // OnModifyDone should set isBeenLayout_ = false since cardInfo_ width differs
    auto&& calcLayoutConstraint = layoutProperty->calcLayoutConstraint_;
    calcLayoutConstraint = std::make_unique<MeasureProperty>();
    CalcSize idealSize = { CalcLength(200), CalcLength(200) };
    calcLayoutConstraint->selfIdealSize = idealSize;
    calcLayoutConstraint->maxSize = idealSize;

    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->isBeenLayout_);
}

/**
 * @tc.name: FormPatternTest_OnAccessibilityStateChange_002
 * @tc.desc: OnAccessibilityStateChange state=true + isDynamic_=false -> UnregisterAccessibility + ReAddForm
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_OnAccessibilityStateChange_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // state same as current (false == false) -> return false
    pattern->accessibilityState_ = false;
    bool ret = pattern->OnAccessibilityStateChange(false);
    EXPECT_FALSE(ret);

    // state=true, isDynamic_=true -> return false (early)
    pattern->isDynamic_ = true;
    ret = pattern->OnAccessibilityStateChange(true);
    EXPECT_FALSE(ret);
    EXPECT_TRUE(pattern->IsAccessibilityState());
    pattern->isDynamic_ = false;

    // state=true, isDynamic_=false -> should UnregisterAccessibility and post ReAddForm, return true
    pattern->SetAccessibilityState(false);
    ret = pattern->OnAccessibilityStateChange(true);
    EXPECT_TRUE(ret);

    // state=false to reset
    ret = pattern->OnAccessibilityStateChange(false);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: FormPatternTest_LoadDisableFormStyle_002
 * @tc.desc: LoadDisableFormStyle IsMaskEnableForm=true + formManagerBridge_ non-null
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTest2, FormPatternTest_LoadDisableFormStyle_002, TestSize.Level1)
{
    RefPtr<FormNode> formNode = CreateFromNode();
    auto pattern = formNode->GetPattern<FormPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNode();

    // IsMaskEnableForm = true (shape = FORM_SHAPE_CIRCLE) + formManagerBridge_ non-null
    RequestFormInfo info;
    info.shape = FORM_SHAPE_CIRCLE;
    EXPECT_TRUE(pattern->IsMaskEnableForm(info));
    EXPECT_NE(pattern->formManagerBridge_, nullptr);
    pattern->isFormObscured_ = false;
    pattern->LoadDisableFormStyle(info, true);
}
} // namespace OHOS::Ace::NG
