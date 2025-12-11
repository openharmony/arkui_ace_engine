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

#include "core/interfaces/native/implementation/custom_dialog_controller_peer_impl.h"

#include "gmock/gmock.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "accessor_test_base.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

const auto DEFAULT_DIALOG_PROPERTIES = DialogProperties();

Ark_CustomDialogControllerOptions GetEmptyOptions()
{
    Ark_CustomDialogControllerOptions options;
    options.cancel = Converter::ArkValue<Opt_Callback_Void>(Ark_Empty());
    options.autoCancel = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.alignment = Converter::ArkValue<Opt_DialogAlignment>(Ark_Empty());
    options.offset = Converter::ArkValue<Opt_Offset>(Ark_Empty());
    options.customStyle = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.gridCount = Converter::ArkValue<Opt_Number>(Ark_Empty());
    options.maskColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
    options.maskRect = Converter::ArkValue<Opt_Rectangle>(Ark_Empty());
    options.openAnimation = Converter::ArkValue<Opt_AnimateParam>(Ark_Empty());
    options.closeAnimation = Converter::ArkValue<Opt_AnimateParam>(Ark_Empty());
    options.showInSubWindow = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.backgroundColor = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
    options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(Ark_Empty());
    options.isModal = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.onWillDismiss = Converter::ArkValue<Opt_Callback_DismissDialogAction_Void>(Ark_Empty());
    options.width = Converter::ArkValue<Opt_Dimension>(Ark_Empty());
    options.height = Converter::ArkValue<Opt_Dimension>(Ark_Empty());
    options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(Ark_Empty());
    options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(Ark_Empty());
    options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(Ark_Empty());
    options.shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(Ark_Empty());
    options.backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(Ark_Empty());
    options.keyboardAvoidMode = Converter::ArkValue<Opt_KeyboardAvoidMode>(Ark_Empty());
    options.enableHoverMode = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    options.hoverModeArea = Converter::ArkValue<Opt_HoverModeAreaType>(Ark_Empty());
    options.levelOrder = Converter::ArkValue<Opt_LevelOrder>(Ark_Empty());
    return options;
}

class CustomDialogControllerAccessorTest : public AccessorTestBaseParent<GENERATED_ArkUICustomDialogControllerAccessor,
    &GENERATED_ArkUIAccessors::getCustomDialogControllerAccessor, CustomDialogControllerPeer> {
public:
    void FinalizePeer()
    {
        if (peer_) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
            peer_ = nullptr;
        }
    }
};

/**
 * @tc.name: defaultOptionsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, defaultOptionsTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    auto peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    DialogProperties dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.autoCancel, DEFAULT_DIALOG_PROPERTIES.autoCancel);
    EXPECT_EQ(dialogProperties.alignment, DEFAULT_DIALOG_PROPERTIES.alignment);
    EXPECT_EQ(dialogProperties.offset, DEFAULT_DIALOG_PROPERTIES.offset);
    EXPECT_EQ(dialogProperties.customStyle, DEFAULT_DIALOG_PROPERTIES.customStyle);
    EXPECT_EQ(dialogProperties.gridCount, DEFAULT_DIALOG_PROPERTIES.gridCount);
    EXPECT_EQ(dialogProperties.maskColor.has_value(), false);
    EXPECT_EQ(dialogProperties.maskRect.has_value(), false);
    EXPECT_EQ(dialogProperties.openAnimation.has_value(), false);
    EXPECT_EQ(dialogProperties.closeAnimation.has_value(), false);
    EXPECT_EQ(dialogProperties.isShowInSubWindow, DEFAULT_DIALOG_PROPERTIES.isShowInSubWindow);
    EXPECT_EQ(dialogProperties.backgroundColor.has_value(), false);
    EXPECT_EQ(dialogProperties.borderRadius.has_value(), false);
    EXPECT_EQ(dialogProperties.isModal, DEFAULT_DIALOG_PROPERTIES.isModal);
    EXPECT_EQ(dialogProperties.width.has_value(), false);
    EXPECT_EQ(dialogProperties.height.has_value(), false);
    EXPECT_EQ(dialogProperties.borderWidth.has_value(), false);
    EXPECT_EQ(dialogProperties.borderColor.has_value(), false);
    EXPECT_EQ(dialogProperties.borderStyle.has_value(), false);
    EXPECT_EQ(dialogProperties.shadow.has_value(), false);
    EXPECT_EQ(dialogProperties.backgroundBlurStyle.has_value(), false);
    EXPECT_EQ(dialogProperties.keyboardAvoidMode, DEFAULT_DIALOG_PROPERTIES.keyboardAvoidMode);
    EXPECT_EQ(dialogProperties.enableHoverMode, DEFAULT_DIALOG_PROPERTIES.enableHoverMode);
    EXPECT_EQ(dialogProperties.hoverModeArea.has_value(), false);
}

/**
 * @tc.name: DISABLED_defaultBuilderOptionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_defaultBuilderOptionTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/**
 * @tc.name: DISABLED_defaultCancelOptionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_defaultCancelOptionTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/**
 * @tc.name: DISABLED_defaultOnWillDismissOptionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_defaultOnWillDismissOptionTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/**
 * @tc.name: autoCancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, autoCancelTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    // check false
    options.autoCancel = Converter::ArkValue<Opt_Boolean>(false);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.autoCancel, false);
    FinalizePeer();

    // check true
    options.autoCancel = Converter::ArkValue<Opt_Boolean>(true);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.autoCancel, true);
    FinalizePeer();
}

static const std::vector<std::pair<Ark_DialogAlignment, DialogAlignment>> ALIGNMENT_TEST_PLAN = {
    { ARK_DIALOG_ALIGNMENT_TOP, DialogAlignment::TOP },
    { ARK_DIALOG_ALIGNMENT_CENTER, DialogAlignment::CENTER },
    { ARK_DIALOG_ALIGNMENT_BOTTOM, DialogAlignment::BOTTOM },
    { ARK_DIALOG_ALIGNMENT_DEFAULT, DialogAlignment::DEFAULT },
    { ARK_DIALOG_ALIGNMENT_TOP_START, DialogAlignment::TOP_START },
    { ARK_DIALOG_ALIGNMENT_TOP_END, DialogAlignment::TOP_END },
    { ARK_DIALOG_ALIGNMENT_CENTER_START, DialogAlignment::CENTER_START },
    { ARK_DIALOG_ALIGNMENT_CENTER_END, DialogAlignment::CENTER_END },
    { ARK_DIALOG_ALIGNMENT_BOTTOM_START, DialogAlignment::BOTTOM_START },
    { ARK_DIALOG_ALIGNMENT_BOTTOM_END, DialogAlignment::BOTTOM_END }
};

/**
 * @tc.name: alignmentTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, alignmentTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : ALIGNMENT_TEST_PLAN) {
        options.alignment = Converter::ArkValue<Opt_DialogAlignment>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.alignment, expectVal);
        FinalizePeer();
    }
}

static const std::vector<std::pair<Ark_Length, Dimension>> OFFSET_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(2.5f), Dimension(2.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>(-2.5f), Dimension(-2.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("5.0px"), Dimension(5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("-5.0px"), Dimension(-5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("22.5px"), Dimension(22.5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("-22.5px"), Dimension(-22.5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("7.0vp"), Dimension(7, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("-7.0vp"), Dimension(-7, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("1.5vp"), Dimension(1.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("-1.5vp"), Dimension(-1.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("65.0fp"), Dimension(65, DimensionUnit::FP) },
    { Converter::ArkValue<Ark_Length>("-65.0fp"), Dimension(-65, DimensionUnit::FP) },
    { Converter::ArkValue<Ark_Length>("4.5fp"), Dimension(4.5, DimensionUnit::FP) },
    { Converter::ArkValue<Ark_Length>("-4.5fp"), Dimension(-4.5, DimensionUnit::FP) },
};

/**
 * @tc.name: offsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, offsetTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;
    Ark_Offset offset;

    for (const auto& [value, expectVal] : OFFSET_TEST_PLAN) {
        offset.dx = value;
        offset.dy = Converter::ArkValue<Ark_Length>("0px");
        options.offset = Converter::ArkValue<Opt_Offset>(offset);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.offset.GetX(), expectVal);
        EXPECT_EQ(dialogProperties.offset.GetY(), Dimension(0, DimensionUnit::PX));
        FinalizePeer();
    }

    for (const auto& [value, expectVal] : OFFSET_TEST_PLAN) {
        offset.dy = value;
        offset.dx = Converter::ArkValue<Ark_Length>("0px");
        options.offset = Converter::ArkValue<Opt_Offset>(offset);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.offset.GetY(), expectVal);
        EXPECT_EQ(dialogProperties.offset.GetX(), Dimension(0, DimensionUnit::PX));
        FinalizePeer();
    }
}

/**
 * @tc.name: customStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, customStyleTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    // check true
    options.customStyle = Converter::ArkValue<Opt_Boolean>(true);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.customStyle, true);
    FinalizePeer();

    // check false
    options.customStyle = Converter::ArkValue<Opt_Boolean>(false);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.customStyle, false);
    FinalizePeer();
}

static const std::vector<std::pair<Ark_Number, int32_t>> GRID_COUNT_TEST_PLAN = {
    { Converter::ArkValue<Ark_Number>(5), 5 },
    { Converter::ArkValue<Ark_Number>(2.4), 2 },
    { Converter::ArkValue<Ark_Number>(1), 1 },
    { Converter::ArkValue<Ark_Number>(0), 0 },
    { Converter::ArkValue<Ark_Number>(-1), -1 },
    { Converter::ArkValue<Ark_Number>(-2.4), -2 },
    { Converter::ArkValue<Ark_Number>(-5), -5 },
};

/**
 * @tc.name: gridCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, gridCountTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : GRID_COUNT_TEST_PLAN) {
        options.gridCount = Converter::ArkValue<Opt_Number>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.gridCount, expectVal);
        FinalizePeer();
    }
}

static const std::vector<std::pair<Ark_ResourceColor, std::string>> COLOR_TEST_PLAN = {
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(0x123456), "#FF123456" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#11223344"), "#11223344" },
    { Converter::ArkUnion<Ark_ResourceColor, Ark_String>("65535"), "#FF00FFFF" },
};

/**
 * @tc.name: maskColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, maskColorTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        options.maskColor = Converter::ArkValue<Opt_ResourceColor>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.maskColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.maskColor.value(), result);
        FinalizePeer();
    }
}

/**
 * @tc.name: DISABLED_maskRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_maskRectTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

/**
 * @tc.name: showInSubWindowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, showInSubWindowTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    // check true
    options.showInSubWindow = Converter::ArkValue<Opt_Boolean>(true);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.isShowInSubWindow, true);
    FinalizePeer();

    // check false
    options.showInSubWindow = Converter::ArkValue<Opt_Boolean>(false);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.isShowInSubWindow, false);
    FinalizePeer();
}

/**
 * @tc.name: backgroundColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, backgroundColorTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        options.backgroundColor = Converter::ArkValue<Opt_ResourceColor>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.backgroundColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.backgroundColor.value(), result);
        FinalizePeer();
    }
}

/**
 * @tc.name: isModalTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, isModalTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    // check false
    options.isModal = Converter::ArkValue<Opt_Boolean>(false);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.isModal, false);
    FinalizePeer();

    // check true
    options.isModal = Converter::ArkValue<Opt_Boolean>(true);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.isModal, true);
    FinalizePeer();
}

static const std::vector<std::pair<Ark_Length, Dimension>> SIZE_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(2.5f), Dimension(2.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("5.0px"), Dimension(5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("22.5px"), Dimension(22.5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Length>("7.0vp"), Dimension(7, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("1.5vp"), Dimension(1.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Length>("65.0fp"), Dimension(65, DimensionUnit::FP) },
    { Converter::ArkValue<Ark_Length>("4.5fp"), Dimension(4.5, DimensionUnit::FP) },
};

static const std::vector<Ark_Length> SIZE_INVALID_TEST_PLAN = {
    { Converter::ArkValue<Ark_Length>(-2.5f) },
    { Converter::ArkValue<Ark_Length>("-5.0px") },
    { Converter::ArkValue<Ark_Length>("-22.5px") },
    { Converter::ArkValue<Ark_Length>("-7.0vp") },
    { Converter::ArkValue<Ark_Length>("-1.5vp") },
    { Converter::ArkValue<Ark_Length>("-65.0fp") },
    { Converter::ArkValue<Ark_Length>("-4.5fp") },
};

static const std::vector<std::pair<Ark_Dimension, Dimension>> SIZE_TEST_PLAN_DIM = {
    { Converter::ArkValue<Ark_Dimension>(2.5f), Dimension(2.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Dimension>("5.0px"), Dimension(5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Dimension>("22.5px"), Dimension(22.5, DimensionUnit::PX) },
    { Converter::ArkValue<Ark_Dimension>("7.0vp"), Dimension(7, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Dimension>("1.5vp"), Dimension(1.5, DimensionUnit::VP) },
    { Converter::ArkValue<Ark_Dimension>("65.0fp"), Dimension(65, DimensionUnit::FP) },
    { Converter::ArkValue<Ark_Dimension>("4.5fp"), Dimension(4.5, DimensionUnit::FP) },
};

static const std::vector<Ark_Dimension> SIZE_INVALID_TEST_PLAN_DIM = {
    { Converter::ArkValue<Ark_Dimension>(-2.5f) },
    { Converter::ArkValue<Ark_Dimension>("-5.0px") },
    { Converter::ArkValue<Ark_Dimension>("-22.5px") },
    { Converter::ArkValue<Ark_Dimension>("-7.0vp") },
    { Converter::ArkValue<Ark_Dimension>("-1.5vp") },
    { Converter::ArkValue<Ark_Dimension>("-65.0fp") },
    { Converter::ArkValue<Ark_Dimension>("-4.5fp") },
};

/**
 * @tc.name: widthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_widthTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN_DIM) {
        options.width = Converter::ArkValue<Opt_Dimension>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.width.has_value(), true);
        EXPECT_EQ(dialogProperties.width.value(), expectVal);
        FinalizePeer();
    }
}

/**
 * @tc.name: widthInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, widthInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN_DIM) {
        options.width = Converter::ArkValue<Opt_Dimension>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.width.has_value(), false);
        FinalizePeer();
    }
}

/**
 * @tc.name: heightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_heightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN_DIM) {
        options.height = Converter::ArkValue<Opt_Dimension>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.height.has_value(), true);
        EXPECT_EQ(dialogProperties.height.value(), expectVal);
        FinalizePeer();
    }
}

/**
 * @tc.name: heightInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, heightInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN_DIM) {
        options.height = Converter::ArkValue<Opt_Dimension>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.height.has_value(), false);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_cornerRadiusTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN_DIM) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Dimension>(value);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_cornerRadiusInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN_DIM) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Dimension>(value);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusesInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, cornerRadiusesInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN) {
        Ark_BorderRadiuses borderRadiuses;
        borderRadiuses.topLeft = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.topRight = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.bottomLeft = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.bottomRight = Converter::ArkValue<Opt_Length>(value);
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(borderRadiuses);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusTopLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, cornerRadiusTopLeftTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_BorderRadiuses borderRadiuses;
        borderRadiuses.topLeft = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.topRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(borderRadiuses);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusTopRightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, cornerRadiusTopRightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_BorderRadiuses borderRadiuses;
        borderRadiuses.topRight = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.topLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(borderRadiuses);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusBottomLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, cornerRadiusBottomLeftTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_BorderRadiuses borderRadiuses;
        borderRadiuses.bottomLeft = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.topLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.topRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(borderRadiuses);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: cornerRadiusBottomRightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, cornerRadiusBottomRightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_BorderRadiuses borderRadiuses;
        borderRadiuses.bottomRight = Converter::ArkValue<Opt_Length>(value);
        borderRadiuses.topLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.topRight = Converter::ArkValue<Opt_Length>(Ark_Empty());
        borderRadiuses.bottomLeft = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_BorderRadiuses>(borderRadiuses);
        options.cornerRadius = Converter::ArkValue<Opt_Union_Dimension_BorderRadiuses>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderRadius.has_value(), true);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomRight, expectVal);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusTopRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().radiusBottomLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderRadius.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_borderWidthTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN_DIM) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_Dimension>(value);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN_DIM) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_Dimension>(value);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthsInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthsInvalidTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& value : SIZE_INVALID_TEST_PLAN) {
        Ark_EdgeWidths edgeWidths;
        edgeWidths.top = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.left = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.right = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.bottom = Converter::ArkValue<Opt_Length>(value);
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_EdgeWidths>(edgeWidths);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthLeftTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_EdgeWidths edgeWidths;
        edgeWidths.left = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_EdgeWidths>(edgeWidths);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthTopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthTopTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_EdgeWidths edgeWidths;
        edgeWidths.top = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_EdgeWidths>(edgeWidths);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthRightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthRightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_EdgeWidths edgeWidths;
        edgeWidths.right = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.bottom = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_EdgeWidths>(edgeWidths);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderWidthBottomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderWidthBottomTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : SIZE_TEST_PLAN) {
        Ark_EdgeWidths edgeWidths;
        edgeWidths.bottom = Converter::ArkValue<Opt_Length>(value);
        edgeWidths.left = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.right = Converter::ArkValue<Opt_Length>(Ark_Empty());
        edgeWidths.top = Converter::ArkValue<Opt_Length>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_Dimension_EdgeWidths, Ark_EdgeWidths>(edgeWidths);
        options.borderWidth = Converter::ArkValue<Opt_Union_Dimension_EdgeWidths>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderWidth.has_value(), true);
        EXPECT_EQ(dialogProperties.borderWidth.value().bottomDimen, expectVal);
        EXPECT_EQ(dialogProperties.borderWidth.value().leftDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().rightDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().topDimen.has_value(), false);
        EXPECT_EQ(dialogProperties.borderWidth.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderColorTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_ResourceColor_EdgeColors, Ark_ResourceColor>(value);
        options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.borderColor.value().leftColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().topColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().rightColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().bottomColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderColorLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderColorLeftTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        Ark_EdgeColors edgeColors;
        edgeColors.left = Converter::ArkValue<Opt_ResourceColor>(value);
        edgeColors.top = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.right = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.bottom = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_ResourceColor_EdgeColors, Ark_EdgeColors>(edgeColors);
        options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.borderColor.value().leftColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().topColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().rightColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().bottomColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderColorTopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderColorTopTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        Ark_EdgeColors edgeColors;
        edgeColors.top = Converter::ArkValue<Opt_ResourceColor>(value);
        edgeColors.left = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.right = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.bottom = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_ResourceColor_EdgeColors, Ark_EdgeColors>(edgeColors);
        options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.borderColor.value().topColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().leftColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().rightColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().bottomColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderColorRightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderColorRightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        Ark_EdgeColors edgeColors;
        edgeColors.right = Converter::ArkValue<Opt_ResourceColor>(value);
        edgeColors.top = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.left = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.bottom = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_ResourceColor_EdgeColors, Ark_EdgeColors>(edgeColors);
        options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.borderColor.value().rightColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().topColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().leftColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().bottomColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderColorBottomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderColorBottomTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : COLOR_TEST_PLAN) {
        Ark_EdgeColors edgeColors;
        edgeColors.bottom = Converter::ArkValue<Opt_ResourceColor>(value);
        edgeColors.top = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.right = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        edgeColors.left = Converter::ArkValue<Opt_ResourceColor>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_ResourceColor_EdgeColors, Ark_EdgeColors>(edgeColors);
        options.borderColor = Converter::ArkValue<Opt_Union_ResourceColor_EdgeColors>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderColor.has_value(), true);
        Color result;
        Color::ParseColorString(expectVal, result);
        EXPECT_EQ(dialogProperties.borderColor.value().bottomColor, result);
        EXPECT_EQ(dialogProperties.borderColor.value().topColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().rightColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().leftColor.has_value(), false);
        EXPECT_EQ(dialogProperties.borderColor.value().multiValued, true);
        FinalizePeer();
    }
}

static const std::vector<std::pair<Ark_BorderStyle, BorderStyle>> BORDER_STYLE_TEST_PLAN = {
    { ARK_BORDER_STYLE_DOTTED, BorderStyle::DOTTED },
    { ARK_BORDER_STYLE_DASHED, BorderStyle::DASHED },
    { ARK_BORDER_STYLE_SOLID, BorderStyle::SOLID },
};

/**
 * @tc.name: borderStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderStyleTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BORDER_STYLE_TEST_PLAN) {
        auto arkUnion = Converter::ArkUnion<Ark_Union_BorderStyle_EdgeStyles, Ark_BorderStyle>(value);
        options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleTop, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleRight, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleBottom, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().multiValued, false);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderStyleLeftTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderStyleLeftTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BORDER_STYLE_TEST_PLAN) {
        Ark_EdgeStyles edgeStyles;
        edgeStyles.left = Converter::ArkValue<Opt_BorderStyle>(value);
        edgeStyles.top = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.right = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.bottom = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_BorderStyle_EdgeStyles, Ark_EdgeStyles>(edgeStyles);
        options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleLeft, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleTop.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleBottom.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderStyleTopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderStyleTopTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BORDER_STYLE_TEST_PLAN) {
        Ark_EdgeStyles edgeStyles;
        edgeStyles.top = Converter::ArkValue<Opt_BorderStyle>(value);
        edgeStyles.left = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.right = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.bottom = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_BorderStyle_EdgeStyles, Ark_EdgeStyles>(edgeStyles);
        options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleTop, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleBottom.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderStyleRightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderStyleRightTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BORDER_STYLE_TEST_PLAN) {
        Ark_EdgeStyles edgeStyles;
        edgeStyles.right = Converter::ArkValue<Opt_BorderStyle>(value);
        edgeStyles.top = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.left = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.bottom = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_BorderStyle_EdgeStyles, Ark_EdgeStyles>(edgeStyles);
        options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleRight, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleTop.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleBottom.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: borderStyleBottomTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, borderStyleBottomTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BORDER_STYLE_TEST_PLAN) {
        Ark_EdgeStyles edgeStyles;
        edgeStyles.bottom = Converter::ArkValue<Opt_BorderStyle>(value);
        edgeStyles.top = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.right = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        edgeStyles.left = Converter::ArkValue<Opt_BorderStyle>(Ark_Empty());
        auto arkUnion = Converter::ArkUnion<Ark_Union_BorderStyle_EdgeStyles, Ark_EdgeStyles>(edgeStyles);
        options.borderStyle = Converter::ArkValue<Opt_Union_BorderStyle_EdgeStyles>(arkUnion);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.borderStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleBottom, expectVal);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleTop.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleRight.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().styleLeft.has_value(), false);
        EXPECT_EQ(dialogProperties.borderStyle.value().multiValued, true);
        FinalizePeer();
    }
}

/**
 * @tc.name: DISABLED_shadowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, DISABLED_shadowTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
}

static const std::vector<std::pair<Ark_BlurStyle, int32_t>> BKG_BLUR_STYLE_TEST_PLAN = {
    { ARK_BLUR_STYLE_THIN, static_cast<int32_t>(BlurStyle::THIN) },
    { ARK_BLUR_STYLE_REGULAR, static_cast<int32_t>(BlurStyle::REGULAR) },
    { ARK_BLUR_STYLE_THICK, static_cast<int32_t>(BlurStyle::THICK) },
    { ARK_BLUR_STYLE_BACKGROUND_THIN, static_cast<int32_t>(BlurStyle::BACKGROUND_THIN) },
    { ARK_BLUR_STYLE_BACKGROUND_REGULAR, static_cast<int32_t>(BlurStyle::BACKGROUND_REGULAR) },
    { ARK_BLUR_STYLE_BACKGROUND_THICK, static_cast<int32_t>(BlurStyle::BACKGROUND_THICK) },
    { ARK_BLUR_STYLE_BACKGROUND_ULTRA_THICK, static_cast<int32_t>(BlurStyle::BACKGROUND_ULTRA_THICK) },
    { ARK_BLUR_STYLE_NONE, static_cast<int32_t>(BlurStyle::NO_MATERIAL) },
    { ARK_BLUR_STYLE_COMPONENT_ULTRA_THIN, static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THIN) },
    { ARK_BLUR_STYLE_COMPONENT_THIN, static_cast<int32_t>(BlurStyle::COMPONENT_THIN) },
    { ARK_BLUR_STYLE_COMPONENT_REGULAR, static_cast<int32_t>(BlurStyle::COMPONENT_REGULAR) },
    { ARK_BLUR_STYLE_COMPONENT_THICK, static_cast<int32_t>(BlurStyle::COMPONENT_THICK) },
    { ARK_BLUR_STYLE_COMPONENT_ULTRA_THICK, static_cast<int32_t>(BlurStyle::COMPONENT_ULTRA_THICK) },
};

/**
 * @tc.name: backgroundBlurStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, backgroundBlurStyleTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : BKG_BLUR_STYLE_TEST_PLAN) {
        options.backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.backgroundBlurStyle.has_value(), true);
        EXPECT_EQ(dialogProperties.backgroundBlurStyle.value(), expectVal);
        FinalizePeer();
    }
}

static const std::vector<std::pair<Ark_KeyboardAvoidMode, KeyboardAvoidMode>> KEYBOARD_AVOID_MODE_TEST_PLAN = {
    { ARK_KEYBOARD_AVOID_MODE_DEFAULT, KeyboardAvoidMode::DEFAULT },
    { ARK_KEYBOARD_AVOID_MODE_NONE, KeyboardAvoidMode::NONE },
};

/**
 * @tc.name: keyboardAvoidModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, keyboardAvoidModeTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : KEYBOARD_AVOID_MODE_TEST_PLAN) {
        options.keyboardAvoidMode = Converter::ArkValue<Opt_KeyboardAvoidMode>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.keyboardAvoidMode, expectVal);
        FinalizePeer();
    }
}

/**
 * @tc.name: enableHoverModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, enableHoverModeTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    // check true
    options.enableHoverMode = Converter::ArkValue<Opt_Boolean>(true);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.enableHoverMode, true);
    FinalizePeer();

    // check false
    options.enableHoverMode = Converter::ArkValue<Opt_Boolean>(false);
    peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
    peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
    dialogProperties = peerImpl->GetDialogProperties();
    EXPECT_EQ(dialogProperties.enableHoverMode, false);
    FinalizePeer();
}

static const std::vector<std::pair<Ark_HoverModeAreaType, HoverModeAreaType>> HOWER_MODE_AREA_TYPE_TEST_PLAN = {
    { ARK_HOVER_MODE_AREA_TYPE_TOP_SCREEN, HoverModeAreaType::TOP_SCREEN },
    { ARK_HOVER_MODE_AREA_TYPE_BOTTOM_SCREEN, HoverModeAreaType::BOTTOM_SCREEN },
};

/**
 * @tc.name: hoverModeAreaTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CustomDialogControllerAccessorTest, hoverModeAreaTest, TestSize.Level1)
{
    Ark_CustomDialogControllerOptions options = GetEmptyOptions();
    DialogProperties dialogProperties;
    GeneratedModifier::CustomDialogControllerPeerImpl * peerImpl;

    for (const auto& [value, expectVal] : HOWER_MODE_AREA_TYPE_TEST_PLAN) {
        options.hoverModeArea = Converter::ArkValue<Opt_HoverModeAreaType>(value);
        peer_ = reinterpret_cast<CustomDialogControllerPeer *>(accessor_->construct(&options));
        peerImpl = reinterpret_cast<GeneratedModifier::CustomDialogControllerPeerImpl *>(peer_);
        dialogProperties = peerImpl->GetDialogProperties();
        EXPECT_EQ(dialogProperties.hoverModeArea.has_value(), true);
        EXPECT_EQ(dialogProperties.hoverModeArea.value(), expectVal);
        FinalizePeer();
    }
}

} // namespace OHOS::Ace::NG
