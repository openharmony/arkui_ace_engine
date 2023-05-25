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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#include "core/components/form/resource/form_utils.h"
#include "core/pipeline/pipeline_base.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"

#include "core/common/ace_engine.h"
#include "core/common/form_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "core/components/form/sub_container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_event_hub.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/form/form_node.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/test/mock/render/mock_render_context.h"
#include "core/components_ng/test/pattern/form/mock/mock_form_utils.h"
#include "core/components_ng/test/pattern/form/mock/mock_sub_container.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr float NORMAL_LENGTH = 100.0f;
constexpr int64_t FORM_ID_OF_TDD = 123456;
RequestFormInfo formInfo;
DirtySwapConfig config;
FormModelNG formModelNG;
} // namespace

struct TestProperty {};

class FormPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateFromNode();
};

void FormPatternTestNg::SetUp()
{
    MockPipelineBase::SetUp();
    formInfo.id = 1;
    formInfo.cardName = "defalut";
    formInfo.bundleName = "bundle";
    formInfo.abilityName = "ability";
    formInfo.moduleName = "module";
    formInfo.allowUpdate = true;
}
void FormPatternTestNg::TearDown()
{
    MockPipelineBase::TearDown();
}

RefPtr<FrameNode> FormPatternTestNg::CreateFromNode()
{
    formModelNG.Create(formInfo);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    return frameNode;
}

/**
 * @tc.name: FormNodeTest001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormNodeTest001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FormNode::GetOrCreateFormNode(
        "FormComponent", stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: FormPatternTestNg001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap in Form Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, OnDirtyLayoutWrapperSwap, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));
    geometryNode->SetFrameOffset(OffsetF(0, 0));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();

    /**
     * @tc.steps: step2. Set call methods OnDirtyLayoutWrapperSwap when the config.skipMeasure and config.skipLayout
     *                   dose not same everty times
     * @tc.expected: Check the return value of  OnDirtyLayoutWrapperSwap
     */
    bool skipMeasures[2] = { false, true };
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            config.skipMeasure = skipMeasures[i];
            config.skipLayout = skipMeasures[j];
            auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, skipMeasures[i]);
            layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            ASSERT_EQ(isSwap, false);
        }
    }

    /**
     * @tc.steps: step3. Set call methods OnDirtyLayoutWrapperSwap when card info dose not change, but the value of
     *                   allowUpdate dose not equals.
     * @tc.expected: Check the cardInfo_.allowUpdate equals formInfo.allowUpdate.
     */
    config.skipMeasure = false;
    ASSERT_NE(pattern->formManagerBridge_, nullptr);
    pattern->cardInfo_.allowUpdate = !formInfo.allowUpdate;
    auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(pattern->cardInfo_.allowUpdate, formInfo.allowUpdate);
    ASSERT_EQ(isSwap, false);

    /**
     * @tc.steps: ste4. Set call methods OnDirtyLayoutWrapperSwap when card info dose not change , but the value of
     *                  allowUpdate dose not equals, and the formManagerBridge_ is nullptr.
     * @tc.expected: Check the cardInfo_.allowUpdate equals formInfo.allowUpdate.
     */
    config.skipMeasure = false;
    pattern->formManagerBridge_ = nullptr;
    pattern->cardInfo_.allowUpdate = !formInfo.allowUpdate;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(pattern->cardInfo_.allowUpdate, formInfo.allowUpdate);
    ASSERT_EQ(isSwap, false);

    /**
     * @tc.steps: step5. Set call methods OnDirtyLayoutWrapperSwap when card info dose not change , and the value of
     *                   allowUpdate is equals, and the formManagerBridge_ is nullptr.
     * @tc.expected: Check the cardInfo_.allowUpdate equals formInfo.allowUpdate.
     */
    pattern->formManagerBridge_ = nullptr;
    isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(pattern->cardInfo_.allowUpdate, formInfo.allowUpdate);
    ASSERT_EQ(isSwap, false);
}

/**
 * @tc.name: FormModelNGTest001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    FormModelNG formNG;
    formNG.Create(formInfo);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: Check the FormModelNG pattern value
     */
    formNG.SetDimension(1);
    formNG.AllowUpdate(false);
    formNG.SetVisibility(VisibleType(1));
    formNG.SetModuleName("test form");

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    ASSERT_NE(property, nullptr);
    auto formInfo = property->GetRequestFormInfoValue();
    ASSERT_EQ(formInfo.dimension, 1);
    EXPECT_FALSE(formInfo.allowUpdate);
    ASSERT_EQ(formInfo.moduleName, "test form");
}

/**
 * @tc.name: FormModelNGTest002
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FormModelNGTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    FormModelNG formNG;
    formNG.Create(formInfo);

    /**
     * @tc.steps: step2. Set call methods
     * @tc.expected: Check the FormModelNG pattern value
     */
    std::string onAcquiredValue;
    auto onAcquired = [&onAcquiredValue](const std::string& param) { onAcquiredValue = param; };
    formNG.SetOnAcquired(std::move(onAcquired));
    auto frameNodeonAcquired = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeonAcquired, nullptr);

    std::string onErrorValue;
    auto onError = [&onErrorValue](const std::string& param) { onErrorValue = param; };
    formNG.SetOnError(std::move(onError));
    auto frameNodeonError = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeonError, nullptr);

    std::string onUninstallValue;
    auto onUninstall = [&onUninstallValue](const std::string& param) { onUninstallValue = param; };
    formNG.SetOnUninstall(std::move(onUninstall));
    auto frameNodeonUninstall = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeonUninstall, nullptr);

    std::string onRouterValue;
    auto onRouter = [&onRouterValue](const std::string& param) { onRouterValue = param; };
    formNG.SetOnRouter(std::move(onRouter));
    auto frameNodeonRouter = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeonRouter, nullptr);

    std::string onLoadValue;
    auto onLoad = [&onLoadValue](const std::string& param) { onLoadValue = param; };
    formNG.SetOnLoad(std::move(onLoad));
    auto frameNodeonLoad = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNodeonLoad, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test OnDirtyLayoutWrapperSwap in Form Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameOffset(OffsetF(0, 0));
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    config.skipMeasure = false;
    config.skipLayout = false;
    frameNode->SetDraggable(true);
    pattern->formManagerBridge_ = nullptr;

    /**
     * @tc.steps: step2. Set different size of geometryNode and the cardInfo has changed.
     * @tc.expected: Only when the width and height of geometryNode both does not equal to zero, the cardInfo_ will be
     *               assigned to formInfo.
     */
    float length[2] = { 0, NORMAL_LENGTH };
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            pattern->cardInfo_.bundleName = "";
            geometryNode->SetFrameSize(SizeF(length[i], length[j]));
            RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
            auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, nullptr);
            ASSERT_NE(layoutWrapper, nullptr);
            auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
            layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            ASSERT_EQ(isSwap, false);
            if (i == 1 && j == 1) {
                ASSERT_EQ(pattern->cardInfo_.bundleName, formInfo.bundleName);
            } else {
                ASSERT_NE(pattern->cardInfo_.bundleName, formInfo.bundleName);
            }
        }
    }

    /**
     * @tc.steps: step3. Set different size of geometryNode but the cardInfo has not changed.
     * @tc.expected: the cardInfo_.width and cardInfo_.height will be changed equal to the size of geometryNode.
     */
    for (int32_t i = 0; i < 2; ++i) {
        for (int32_t j = 0; j < 2; ++j) {
            pattern->cardInfo_.width = Dimension(NORMAL_LENGTH);
            pattern->cardInfo_.height = Dimension(NORMAL_LENGTH);
            geometryNode->SetFrameSize(SizeF(length[i], length[j]));
            RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
            auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, nullptr);
            ASSERT_NE(layoutWrapper, nullptr);
            auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
            layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
            auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
            ASSERT_EQ(isSwap, false);
            ASSERT_EQ(pattern->cardInfo_.width, Dimension(length[i]));
            ASSERT_EQ(pattern->cardInfo_.height, Dimension(length[j]));
        }
    }
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test OnDirtyLayoutWrapperSwap in Form Pattern.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Init FormModelNG object
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    geometryNode->SetFrameOffset(OffsetF(0, 0));
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    pattern->OnAttachToFrameNode();
    config.skipMeasure = false;
    config.skipLayout = false;

    /**
     * @tc.steps: step2. set the cardInfo_ of pattern equal to formInfo with the allowUpdate does not same.And assumed
     *                   the card has been loaded.
     */
    pattern->cardInfo_.cardName = formInfo.cardName;
    pattern->cardInfo_.bundleName = formInfo.bundleName;
    pattern->cardInfo_.abilityName = formInfo.abilityName;
    pattern->cardInfo_.moduleName = formInfo.moduleName;
    pattern->cardInfo_.allowUpdate = false;
    pattern->subContainer_ = nullptr;
    pattern->isLoaded_ = true;

    geometryNode->SetFrameSize(SizeF(NORMAL_LENGTH, NORMAL_LENGTH));
    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    auto isSwap = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(isSwap, false);
    ASSERT_EQ(pattern->cardInfo_.allowUpdate, true);
    ASSERT_EQ(pattern->cardInfo_.width, Dimension(NORMAL_LENGTH));
    ASSERT_EQ(pattern->cardInfo_.height, Dimension(NORMAL_LENGTH));
}

/**
 * @tc.name: InitFormManagerDelegate001
 * @tc.desc: Verify the InitFormManagerDelegate Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, InitFormManagerDelegate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    auto formUtils = std::make_shared<MockFormUtils>();
    pattern->subContainer_ = subContainer;
    pattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. InitFormManagerDelegate when formUitls is nullptr.
     * @tc.expected: InitFormManagerDelegate success.
     */
    pattern->formManagerBridge_ = nullptr;
    pattern->InitFormManagerDelegate();
    ASSERT_EQ(pattern->formManagerBridge_->formUtils_, nullptr);

    /**
     * @tc.steps: step3. InitFormManagerDelegate when formManagerBridge has been created.
     * @tc.expected: InitFormManagerDelegate fail.
     */
    FormManager::GetInstance().SetFormUtils(formUtils);
    ASSERT_EQ(FormManager::GetInstance().GetFormUtils(), formUtils);
    pattern->InitFormManagerDelegate();
    ASSERT_EQ(pattern->formManagerBridge_->formUtils_, nullptr);

    /**
     * @tc.steps: step4. InitFormManagerDelegate when formUitls is not nullptr.
     * @tc.expected: InitFormManagerDelegate success.
     */
    pattern->formManagerBridge_ = nullptr;
    pattern->InitFormManagerDelegate();
    ASSERT_EQ(pattern->formManagerBridge_->formUtils_, formUtils);
}

/**
 * @tc.name: CreateCardContainer001
 * @tc.desc: Verify the CreateCardContainer Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, CreateCardContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineContext> context = WeakPtr<PipelineContext>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    auto formUtils = std::make_shared<MockFormUtils>();
    pattern->subContainer_ = subContainer;
    pattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. CreateCardContainer when subContainer is not nullptr.
     * @tc.expected: subContainer will change.
     */
    ASSERT_EQ(pattern->subContainer_, subContainer);
    pattern->CreateCardContainer();
    ASSERT_NE(pattern->subContainer_, subContainer);

    /**
     * @tc.steps: step3. CreateCardContainer when subContainer is nullptr.
     * @tc.expected: Create subContainer success.
     */
    pattern->subContainer_ = nullptr;
    pattern->CreateCardContainer();
    ASSERT_NE(pattern->subContainer_, nullptr);
}

/**
 * @tc.name: CreateCardContainer002
 * @tc.desc: Verify the CreateCardContainer Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, CreateCardContainer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineBase> context = WeakPtr<PipelineBase>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    subContainer->instanceId_ = 0;
    auto formUtils = std::make_shared<MockFormUtils>();
    pattern->subContainer_ = subContainer;
    pattern->frameNode_ = frameNode;
    pattern->cardInfo_.id = 1;
    auto mockContianer = AceType::MakeRefPtr<MockContainer>();
    AceEngine::Get().AddContainer(ContainerScope::CurrentId(), mockContianer);
    auto conainer = Container::Current();
    ASSERT_NE(conainer, nullptr);
    ASSERT_EQ(conainer, mockContianer);
    conainer->SetUseNewPipeline();
    ASSERT_EQ(Container::IsCurrentUseNewPipeline(), true);

    /**
     * @tc.steps: step2. CreateCardContainer when subContainer is not nullptr.
     * @tc.expected: subContainer will change .
     */
    ASSERT_EQ(pattern->subContainer_, subContainer);
    pattern->CreateCardContainer();
    ASSERT_NE(pattern->subContainer_, subContainer);

    /**
     * @tc.steps: step3. CreateCardContainer when subContainer has a cache in FormManager.
     * @tc.expected: subContainer in FormManager will been removed .
     */
    FormManager::GetInstance().AddSubContainer(1, subContainer);
    ASSERT_EQ(Container::IsCurrentUseNewPipeline(), true);
    ASSERT_EQ(frameNode->GetContext()->GetInstanceId(), FormManager::GetInstance().GetSubContainer(1)->GetInstanceId());
    pattern->CreateCardContainer();
    ASSERT_EQ(FormManager::GetInstance().GetSubContainer(1), nullptr);

    /**
     * @tc.steps: step4. CreateCardContainer when subContainer points to nullptr and the cache in FormManager does not
     *                   match the cardType whith this JS_CARD.
     * @tc.expected: Create subContainer success.
     */
    FormManager::GetInstance().AddSubContainer(1, subContainer);
    pattern->subContainer_ = nullptr;
    subContainer->cardType_ = FrontendType::ETS_CARD;
    pattern->CreateCardContainer();
    ASSERT_EQ(FormManager::GetInstance().GetSubContainer(1), subContainer);
    ASSERT_NE(pattern->subContainer_, nullptr);
    ASSERT_NE(pattern->subContainer_, subContainer);

    /**
     * @tc.steps: step5. CreateCardContainer when subContainer points to nullptr and the cache in FormManager does not
     *                   match the instanceId whith the form.
     * @tc.expected: Create subContainer success.
     */
    pattern->subContainer_ = nullptr;
    subContainer->cardType_ = FrontendType::JS_CARD;
    subContainer->instanceId_ = 2;
    pattern->CreateCardContainer();
    ASSERT_EQ(FormManager::GetInstance().GetSubContainer(1), subContainer);
    ASSERT_NE(pattern->subContainer_, nullptr);
    ASSERT_NE(pattern->subContainer_, subContainer);
}

/**
 * @tc.name: OnRebuildFrame
 * @tc.desc: Verify the OnRebuildFrame Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, OnRebuildFrame, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineBase> context = WeakPtr<PipelineBase>();
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    frameNode->renderContext_ = renderContext;
    pattern->frameNode_ = frameNode;
    EXPECT_CALL(*renderContext, AddChild(_, _)).Times(1);
    pattern->OnRebuildFrame();
}

/**
 * @tc.name: RemoveSubContainer
 * @tc.desc: Verify the RemoveSubContainer Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, RemoveSubContainer, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    frameNode->eventHub_ = nullptr;
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineBase> context = WeakPtr<PipelineBase>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);
    subContainer->instanceId_ = 0;
    pattern->subContainer_ = subContainer;
    pattern->RemoveSubContainer();
    ASSERT_EQ(pattern->subContainer_, nullptr);
}

/**
 * @tc.name: ISAllowUpdate
 * @tc.desc: Verify the ISAllowUpdate Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, ISAllowUpdate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and build a subContainer .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    WeakPtr<PipelineBase> context = WeakPtr<PipelineBase>();
    auto subContainer = AceType::MakeRefPtr<MockSubContainer>(context);

    /**
     * @tc.steps: step2.Get allowUpate by calling  ISAllowUpdate.
     * @tc.expected: Check thallowUpate value.
     */
    auto allowUpdate = pattern->ISAllowUpdate();
    ASSERT_EQ(allowUpdate, true);
}

/**
 * @tc.name: FireOnEvent
 * @tc.desc: Verify the FireOnEvent Interface of FormPattern work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(FormPatternTestNg, FireOnEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a FormPattern and get a FormEventHub .
     */
    RefPtr<FrameNode> frameNode = CreateFromNode();
    auto pattern = frameNode->GetPattern<FormPattern>();
    ASSERT_NE(pattern, nullptr);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);

    /**
     * @tc.steps: step2.Call SetOnError in FormEventHub.
     * @tc.expected:Call FireOnErrorEvent in FormPattern.
     */

    eventHub->SetOnError([](const std::string& string) {
        auto json = JsonUtil::Create(true);
        json->Put("errcode", "0");
        json->Put("msg", "msg");
        ASSERT_EQ(string, json->ToString());
    });
    pattern->FireOnErrorEvent("0", "msg");

    /**
     * @tc.steps: step3.Call SetOnUninstall in FormEventHub.
     * @tc.expected: Call FireOnUninstallEvent in FormPattern.
     */
    eventHub->SetOnUninstall([](const std::string& string) {
        auto json = JsonUtil::Create(true);
        json->Put("id", std::to_string(FORM_ID_OF_TDD).c_str());
        ASSERT_EQ(string, json->ToString());
    });
    pattern->FireOnUninstallEvent(FORM_ID_OF_TDD);

    /**
     * @tc.steps: step4.Call SetOnUninstall in FormEventHub.
     * @tc.expected: all FireOnUninstallEvent in FormPattern.
     */
    eventHub->SetOnUninstall([](const std::string& string) {
        auto json = JsonUtil::Create(true);
        json->Put("id", std::to_string(FORM_ID_OF_TDD).c_str());
        ASSERT_EQ(string, json->ToString());
    });
    pattern->FireOnUninstallEvent(FORM_ID_OF_TDD);

    /**
     * @tc.steps: step5.Call SetOnAcquired in FormEventHub.
     * @tc.expected: Call FireOnAcquiredEvent in FormPattern.
     */
    eventHub->SetOnAcquired([](const std::string& string) {
        auto json = JsonUtil::Create(true);
        json->Put("id", std::to_string(FORM_ID_OF_TDD).c_str());
        ASSERT_EQ(string, json->ToString());
    });
    pattern->FireOnAcquiredEvent(FORM_ID_OF_TDD);

    /**
     * @tc.steps: step6.Call SetOnAcquired in FormEventHub.
     * @tc.expected: Call FireOnAcquiredEvent in FormPattern.
     */
    eventHub->SetOnRouter([](const std::string& string) {
        auto json = JsonUtil::Create(true);
        json->Put("action", "message");
        auto actionJson = JsonUtil::Create(true);
        actionJson->Put("action", json);
        ASSERT_EQ(string, actionJson->ToString());
    });
    auto json = JsonUtil::Create(true);
    json->Put("action", "message");
    pattern->FireOnRouterEvent(json);

    /**
     * @tc.steps: step7.Call SetOnLoad in FormEventHub.
     * @tc.expected: Call FireOnLoadEvent in FormPattern.
     */
    eventHub->SetOnLoad([](const std::string& string) { ASSERT_EQ(string, ""); });
    pattern->FireOnLoadEvent();
}
} // namespace OHOS::Ace::NG
