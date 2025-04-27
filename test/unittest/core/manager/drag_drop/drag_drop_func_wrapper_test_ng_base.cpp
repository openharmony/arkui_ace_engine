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

 #include <optional>

 #include "gtest/gtest.h"
 
 #include "test/mock/base/mock_drag_window.h"
 #include "test/mock/core/common/mock_container.h"
 #include "test/mock/core/common/mock_interaction_interface.h"
 #include "test/mock/core/pipeline/mock_pipeline_context.h"
 
 #include "base/image/pixel_map.h"
 #include "base/memory/ace_type.h"
 #include "base/memory/referenced.h"
 #include "base/subwindow/subwindow_manager.h"
 #include "core/common/interaction/interaction_interface.h"
 #include "core/components/common/layout/grid_system_manager.h"
 #include "core/components_ng/base/frame_node.h"
 #include "core/components_ng/base/geometry_node.h"
 #include "core/components_ng/base/ui_node.h"
 #include "core/components_ng/event/event_hub.h"
 #include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
 #include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
 #include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
 
 using namespace testing;
 using namespace testing::ext;
 namespace OHOS::Ace::NG {
 namespace {
 RefPtr<DragWindow> MOCK_DRAG_WINDOW;
 constexpr float DEFAULT_OPACITY = 0.95f;
 constexpr float PARA_OPACITY_VALUE_1 = 0.3f;
 constexpr float PARA_OPACITY_VALUE_2 = 0.0f;
 constexpr float PARA_OPACITY_VALUE_3 = 0.5f;
 constexpr float PARA_OPACITY_VALUE_4 = 0.7f;
 constexpr float PARA_OPACITY_VALUE_5 = 1.0f;
 constexpr float PARA_OPACITY_VALUE_6 = 10.0f;
 constexpr float PARA_OPACITY_VALUE_7 = 50.0f;
 constexpr float PARA_OPACITY_VALUE_8 = -50.0f;
 
 constexpr float PARA_OPACITY_VALUE_9 = 0.1f;
 constexpr float PARA_OPACITY_VALUE_10 = 0.2f;
 constexpr float PARA_OPACITY_VALUE_11 = 0.4f;
 constexpr float PARA_OPACITY_VALUE_12 = 0.6f;
 constexpr float PARA_OPACITY_VALUE_13 = 0.8f;
 constexpr float PARA_OPACITY_VALUE_14 = 0.9f;
 constexpr float PARA_OPACITY_VALUE_15 = 1.1f;
 constexpr float PARA_OPACITY_VALUE_16 = 1.2f;
 constexpr float PARA_OPACITY_VALUE_17 = 1.3f;
 constexpr float PARA_OPACITY_VALUE_18 = 1.4f;
 constexpr float PARA_OPACITY_VALUE_19 = 1.5f;
 constexpr float PARA_OPACITY_VALUE_20 = 1.6f;
 constexpr float PARA_OPACITY_VALUE_21 = 1.7f;
 constexpr float PARA_OPACITY_VALUE_22 = 1.8f;
 constexpr float PARA_OPACITY_VALUE_23 = 1.9f;
 constexpr float PARA_OPACITY_VALUE_24 = 2.0f;
 constexpr float PARA_OPACITY_VALUE_25 = 2.1f;
 constexpr float PARA_OPACITY_VALUE_26 = 2.2f;
 constexpr float PARA_OPACITY_VALUE_27 = 2.3f;
 constexpr float PARA_OPACITY_VALUE_28 = 2.4f;
 constexpr float PARA_OPACITY_VALUE_29 = 2.5f;
 constexpr float PARA_OPACITY_VALUE_30 = 2.6f;
 constexpr float PARA_OPACITY_VALUE_31 = 2.7f;
 constexpr float PARA_OPACITY_VALUE_32 = 2.8f;
 constexpr float PARA_OPACITY_VALUE_33 = 2.9f;
 constexpr float PARA_OPACITY_VALUE_34 = 3.0f;
 constexpr float PARA_OPACITY_VALUE_35 = 3.1f;
 constexpr float PARA_OPACITY_VALUE_36 = 3.2f;
 constexpr float PARA_OPACITY_VALUE_37 = 3.3f;
 constexpr float PARA_OPACITY_VALUE_38 = 3.4f;
 constexpr float PARA_OPACITY_VALUE_39 = 3.5f;
 constexpr float PARA_OPACITY_VALUE_40 = 3.6f;
 constexpr float PARA_OPACITY_VALUE_41 = 3.7f;
 constexpr float PARA_OPACITY_VALUE_42 = 3.8f;
 constexpr float PARA_OPACITY_VALUE_43 = 3.9f;
 constexpr float PARA_OPACITY_VALUE_44 = 4.0f;
 constexpr float PARA_OPACITY_VALUE_45 = 4.1f;
 constexpr float PARA_OPACITY_VALUE_46 = 4.2f;
 constexpr float PARA_OPACITY_VALUE_47 = 4.3f;
 constexpr float PARA_OPACITY_VALUE_48 = 4.4f;
 constexpr float PARA_OPACITY_VALUE_49 = 4.5f;
 constexpr float PARA_OPACITY_VALUE_50 = 4.6f;
 constexpr float PARA_OPACITY_VALUE_51 = 4.7f;
 constexpr float PARA_OPACITY_VALUE_52 = 4.8f;
 constexpr float PARA_OPACITY_VALUE_53 = 4.9f;
 constexpr float PARA_OPACITY_VALUE_54 = 5.0f;
 
 constexpr float MIN_OPACITY { 0.0f };
 constexpr float MAX_OPACITY { 1.0f };
 } // namespace
 
 class DragDropFuncWrapperTestNg : public testing::Test {
 public:
     static void SetUpTestCase();
     static void TearDownTestCase();
 };
 
 void DragDropFuncWrapperTestNg::SetUpTestCase()
 {
     MockPipelineContext::SetUp();
     MockContainer::SetUp();
     MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
 }
 
 void DragDropFuncWrapperTestNg::TearDownTestCase()
 {
     MockPipelineContext::TearDown();
     MockContainer::TearDown();
     MOCK_DRAG_WINDOW = nullptr;
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest001
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest001, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.3f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_1 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_1 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_1);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.3f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_1);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest002
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest002, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, don't set drag preview opacity
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {};
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest003
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest003, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_2 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_2 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_2);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest004
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest004, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.5f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_3 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_3 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_3);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.5f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_3);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest005
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest005, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.7f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_4 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_4 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_4);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.7f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_4);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest006
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest006, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_5 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_5 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_5);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 1.0f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_5);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest007
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest007, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 10.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_6 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_6 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_6);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest008
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest008, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 50.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_7 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_7 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_7);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest009
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest009, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is -50.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_8 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_8 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_8);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest010
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest010, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.1f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_9 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_9 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_9);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.1f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_9);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest011
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest011, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.2f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_10 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_10 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_10);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.2f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_10);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest012
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest012, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.4f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_11 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_11 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_11);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.4f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_11);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest013
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest013, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.6f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_12 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_12 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_12);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.6f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_12);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest014
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest014, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.8f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_13 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_13 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_13);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.8f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_13);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest015
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest015, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 0.9f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_14 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_14 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_14);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.9f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, PARA_OPACITY_VALUE_14);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest016
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest016, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.1f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_15 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_15 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_15);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest017
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest017, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.2f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_16 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_16 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_16);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest018
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest018, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.3f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_17 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_17 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_17);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest019
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest019, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.4f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_18 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_18 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_18);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest020
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest020, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.5f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_19 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_19 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_19);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest021
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest021, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.6f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_20 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_20 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_20);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest022
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest022, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.7f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_21 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_21 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_21);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest023
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest023, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.8f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_22 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_22 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_22);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest024
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest024, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 1.9f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_23 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_23 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_23);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest025
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest025, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_24 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_24 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_24);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest026
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest026, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.1f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_25 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_25 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_25);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest027
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest027, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.2f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_26 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_26 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_26);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest028
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest028, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.3f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_27 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_27 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_27);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest029
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest029, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.4f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_28 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_28 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_28);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest030
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest030, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.5f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_29 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_29 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_29);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest031
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest031, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.6f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_30 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_30 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_30);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest032
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest032, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.7f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_31 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_31 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_31);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest033
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest033, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.8f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_32 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_32 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_32);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest034
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest034, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 2.9f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_33 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_33 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_33);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest035
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest035, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_34 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_34 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_34);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest036
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest036, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.1f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_35 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_35 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_35);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest037
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest037, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.2f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_36 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_36 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_36);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest038
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest038, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.3f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_37 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_37 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_37);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest039
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest039, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.4f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_38 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_38 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_38);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest040
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest040, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.5f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_39 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_39 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_39);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest041
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest041, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.6f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_40 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_40 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_40);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest042
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest042, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.7f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_41 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_41 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_41);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest043
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest043, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.8f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_42 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_42 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_42);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest044
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest044, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 3.9f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_43 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_43 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_43);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest045
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest045, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_44 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_44 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_44);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest046
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest046, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.1f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_45 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_45 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_45);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest047
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest047, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.2f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_46 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_46 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_46);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest048
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest048, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.3f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_47 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_47 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_47);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest049
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest049, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.4f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_48 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_48 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_48);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest050
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest050, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.5f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_49 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_49 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_49);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest051
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest051, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.6f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_50 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_50 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_50);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest052
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest052, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.7f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_51 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_51 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_51);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest053
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest053, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.8f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_52 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_52 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_52);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest054
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest054, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 4.9f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_53 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_53 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_53);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 /**
  * @tc.name: DragDropFuncWrapperTest055
  * @tc.desc: Test UpdateDragPreviewOptionsFromModifier
  * @tc.type: FUNC
  * @tc.author:
  */
 HWTEST_F(DragDropFuncWrapperTestNg, DragDropFuncWrapperTest055, TestSize.Level1)
 {
     /**
      * @tc.steps: step1. construct a lambda function, set drag preview opacity is 5.0f
      */
     auto applyOnNodeSync = [](WeakPtr<NG::FrameNode> frameNode) {
         auto node = frameNode.Upgrade();
         CHECK_NULL_VOID(node);
         if ((PARA_OPACITY_VALUE_54 <= MAX_OPACITY) && (PARA_OPACITY_VALUE_54 > MIN_OPACITY)) {
             node->GetRenderContext()->UpdateOpacity(PARA_OPACITY_VALUE_54);
         } else {
             node->GetRenderContext()->UpdateOpacity(DEFAULT_OPACITY);
         }
     };
 
     /**
      * @tc.steps: step2. construct a DragPreviewOption object
      */
     NG::DragPreviewOption option;
 
     /**
      * @tc.steps: step3. call UpdateDragPreviewOptionsFromModifier
      * @tc.expected: step3. opacity in DragPreviewOption is equal to 0.95f.
      */
     NG::DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(applyOnNodeSync, option);
     EXPECT_EQ(option.options.opacity, DEFAULT_OPACITY);
 }
 
 } // namespace OHOS::Ace::NG
 