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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper/swiper_helper.h"

namespace OHOS::Ace::NG {
class SwiperHelperTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: DumpPanDirection001
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::NONE;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:NONE\n");
}

/**
 * @tc.name: DumpPanDirection002
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::LEFT;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:LEFT\n");
}

/**
 * @tc.name: DumpPanDirection003
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::RIGHT;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:RIGHT\n");
}

/**
 * @tc.name: DumpPanDirection004
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::HORIZONTAL;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:HORIZONTAL\n");
}

/**
 * @tc.name: DumpPanDirection005
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::UP;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:UP\n");
}

/**
 * @tc.name: DumpPanDirection006
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection006, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::DOWN;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:DOWN\n");
}

/**
 * @tc.name: DumpPanDirection007
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection007, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    PanDirection pan;
    pan.type = PanDirection::VERTICAL;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:VERTICAL\n");
}

/**
 * @tc.name: DumpPanDirection008
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection008, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:ALL\n");
}

/**
 * @tc.name: DumpPanDirection009
 * @tc.desc: Test SwiperHelper DumpPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpPanDirection009, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    uint32_t number = 6;
    PanDirection pan;
    pan.type = number;
    swiper.panDirection_ = pan;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "Axis:HORIZONTAL\n");
}

/**
 * @tc.name: DumpDirection001
 * @tc.desc: Test SwiperHelper DumpDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpDirection001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    Axis direction = Axis::NONE;
    swiper.direction_ = direction;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[49], "Axis:NONE\n");
}

/**
 * @tc.name: DumpDirection002
 * @tc.desc: Test SwiperHelper DumpDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpDirection002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[49], "Axis:HORIZONTAL\n");
}

/**
 * @tc.name: DumpDirection003
 * @tc.desc: Test SwiperHelper DumpDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpDirection003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    Axis direction = Axis::FREE;
    swiper.direction_ = direction;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[49], "Axis:FREE\n");
}

/**
 * @tc.name: DumpDirection004
 * @tc.desc: Test SwiperHelper DumpDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpDirection004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    Axis direction = Axis::VERTICAL;
    swiper.direction_ = direction;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[49], "Axis:VERTICAL\n");
}

/**
 * @tc.name: DumpDirection005
 * @tc.desc: Test SwiperHelper DumpDirection
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpDirection005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    int32_t number = 6;
    Axis direction = static_cast<Axis>(number);
    swiper.direction_ = direction;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[49], "disableSwipe:false\n");
}

/**
 * @tc.name: DumpIndicatorType001
 * @tc.desc: Test SwiperHelper DumpIndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpIndicatorType001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.lastSwiperIndicatorType_ = SwiperIndicatorType::DOT;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[34], "SwiperIndicatorType:DOT\n");
}

/**
 * @tc.name: DumpIndicatorType002
 * @tc.desc: Test SwiperHelper DumpIndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpIndicatorType002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.lastSwiperIndicatorType_ = SwiperIndicatorType::DIGIT;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[34], "SwiperIndicatorType:DIGIT\n");
}

/**
 * @tc.name: DumpIndicatorType003
 * @tc.desc: Test SwiperHelper DumpIndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpIndicatorType003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.lastSwiperIndicatorType_ = SwiperIndicatorType::ARC_DOT;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[34], "SwiperIndicatorType:ARC_DOT\n");
}

/**
 * @tc.name: DumpIndicatorType004
 * @tc.desc: Test SwiperHelper DumpIndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpIndicatorType004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    int32_t number = 6;
    swiper.lastSwiperIndicatorType_ = static_cast<SwiperIndicatorType>(number);
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[34], "isFinishAnimation:false\n");
}

/**
 * @tc.name: DumpIndicatorType005
 * @tc.desc: Test SwiperHelper DumpIndicatorType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpIndicatorType005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.lastSwiperIndicatorType_ = std::nullopt;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[34], "lastSwiperIndicatorType:null\n");
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: Test SwiperHelper DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpAdvanceInfo001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = 20.0f;
    info.endPos = 80.0f;
    itemPosition[1] = info;
    swiper.itemPosition_ = itemPosition;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "-----------start print itemPosition------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: Test SwiperHelper DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpAdvanceInfo002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:ALL\n");
}

/**
 * @tc.name: DumpAdvanceInfo003
 * @tc.desc: Test SwiperHelper DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpAdvanceInfo003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::map<int32_t, SwiperItemInfo> itemPositionInAnimation;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    itemPositionInAnimation[1] = info;
    swiper.itemPositionInAnimation_ = itemPositionInAnimation;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "-----------start print itemPositionInAnimation------------\n");
}

/**
 * @tc.name: DumpAdvanceInfo004
 * @tc.desc: Test SwiperHelper DumpAdvanceInfo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpAdvanceInfo004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    helper.DumpAdvanceInfo(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[48], "PanDirection:ALL\n");
}

/**
 * @tc.name: DumpInfoAddPositionDesc001
 * @tc.desc: Test SwiperHelper DumpInfoAddPositionDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddPositionDesc001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(1);
    swiper.uiCastJumpIndex_ = index;
    helper.DumpInfoAddPositionDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[1], "uiCastJumpIndex:1\n");
}

/**
 * @tc.name: DumpInfoAddPositionDesc002
 * @tc.desc: Test SwiperHelper DumpInfoAddPositionDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddPositionDesc002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(2);
    swiper.jumpIndex_ = index;
    helper.DumpInfoAddPositionDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[2], "jumpIndex:2\n");
}

/**
 * @tc.name: DumpInfoAddPositionDesc003
 * @tc.desc: Test SwiperHelper DumpInfoAddPositionDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddPositionDesc003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(3);
    swiper.targetIndex_ = index;
    helper.DumpInfoAddPositionDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[3], "targetIndex:3\n");
}

/**
 * @tc.name: DumpInfoAddPositionDesc004
 * @tc.desc: Test SwiperHelper DumpInfoAddPositionDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddPositionDesc004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(4);
    swiper.pauseTargetIndex_ = index;
    helper.DumpInfoAddPositionDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[4], "pauseTargetIndex:4\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc001
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.isVisible_ = false;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[4], "isVisible:false\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc002
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.isWindowShow_ = false;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[6], "isWindowShow:false\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc003
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.indicatorIsBoolean_ = false;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[8], "indicatorIsBoolean:false\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc004
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(1);
    swiper.indicatorId_ = index;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[14], "indicatorId:1\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc005
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(2);
    swiper.leftButtonId_ = index;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[15], "leftButtonId:2\n");
}

/**
 * @tc.name: DumpInfoAddGestureDesc006
 * @tc.desc: Test SwiperHelper DumpInfoAddGestureDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddGestureDesc006, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(3);
    swiper.rightButtonId_ = index;
    helper.DumpInfoAddGestureDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[16], "rightButtonId:3\n");
}

/**
 * @tc.name: DumpInfoAddAnimationDesc001
 * @tc.desc: Test SwiperHelper DumpInfoAddAnimationDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddAnimationDesc001, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.isUserFinish_ = false;
    helper.DumpInfoAddAnimationDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[3], "isUserFinish:false\n");
}

/**
 * @tc.name: DumpInfoAddAnimationDesc002
 * @tc.desc: Test SwiperHelper DumpInfoAddAnimationDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddAnimationDesc002, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    swiper.stopIndicatorAnimation_ = false;
    helper.DumpInfoAddAnimationDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[5], "stopIndicatorAnimation:false\n");
}

/**
 * @tc.name: DumpInfoAddAnimationDesc003
 * @tc.desc: Test SwiperHelper DumpInfoAddAnimationDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddAnimationDesc003, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<int32_t> index;
    index.emplace(3);
    swiper.surfaceChangedCallbackId_ = index;
    helper.DumpInfoAddAnimationDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[7], "surfaceChangedCallbackId:3\n");
}

/**
 * @tc.name: DumpInfoAddAnimationDesc004
 * @tc.desc: Test SwiperHelper DumpInfoAddAnimationDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddAnimationDesc004, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    std::optional<float> index;
    index.emplace(4.0f);
    swiper.velocity_ = index;
    helper.DumpInfoAddAnimationDesc(swiper);
    EXPECT_EQ(DumpLog::GetInstance().description_[8], "velocity:4.000000\n");
}

/**
 * @tc.name: DumpInfoAddAnimationDesc005
 * @tc.desc: Test SwiperHelper DumpInfoAddAnimationDesc
 * @tc.type: FUNC
 */
HWTEST_F(SwiperHelperTestNg, DumpInfoAddAnimationDesc005, TestSize.Level1)
{
    DumpLog::GetInstance().description_.clear();
    SwiperHelper helper;
    SwiperPattern swiper;
    RefPtr<SwiperPattern> swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    WeakPtr<SwiperPattern> pattern = swiperPattern;
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, 2, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PaintProperty> paintProperty = AceType::MakeRefPtr<SwiperPaintProperty>();
    frameNode->paintProperty_ = paintProperty;
    swiper.frameNode_ = frameNode;
    helper.DumpInfoAddAnimationDesc(swiper);
    EXPECT_NE(DumpLog::GetInstance().description_[9], "curve:null\n");
}
} // namespace OHOS::Ace::NG