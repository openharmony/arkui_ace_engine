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
#include "accessor_test_base.h"
#include "accessor_test_utils.h"
#include "richeditor_accessor_test.h"
#include "core/interfaces/native/implementation/rich_editor_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "gmock/gmock.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace GeneratedModifier {
const GENERATED_ArkUIClickEventAccessor* GetClickEventAccessor();
const GENERATED_ArkUIGestureEventAccessor* GetGestureEventAccessor();
}

namespace {
UserGestureOptions g_gestureOptions;

class MockRichEditorController : public RichEditorController {
    public:
    MockRichEditorController() = default;
    ~MockRichEditorController() override = default;
    MOCK_METHOD(int32_t, AddSymbolSpan, (const SymbolSpanOptions&));
    MOCK_METHOD(int32_t, AddPlaceholderSpan, (const RefPtr<UINode>&, const SpanOptionBase&));
    MOCK_METHOD(void, UpdateSpanStyle, (int32_t, int32_t, TextStyle, ImageSpanAttribute));
    MOCK_METHOD(void, UpdateParagraphStyle, (int32_t, int32_t, const struct UpdateParagraphStyle&));
    MOCK_METHOD(void, DeleteSpans, (const RangeOptions&));
    MOCK_METHOD(SelectionInfo, GetSpansInfo, (int32_t start, int32_t end));
    MOCK_METHOD(std::vector<ParagraphInfo>, GetParagraphsInfo, (int32_t start, int32_t end));
    MOCK_METHOD(SelectionInfo, GetSelectionSpansInfo, ());
    MOCK_METHOD(RefPtr<SpanStringBase>, ToStyledString, (int32_t, int32_t));
    MOCK_METHOD(SelectionInfo, FromStyledString, (RefPtr<SpanStringBase>));

    int32_t AddImageSpan(const ImageSpanOptions& options) override
    {
        g_gestureOptions = options.userGestureOption;
        return 0;
    }

    int32_t AddTextSpan(const TextSpanOptions& options) override
    {
        g_gestureOptions = options.userGestureOption;
        return 0;
    }
};

Opt_RichEditorImageSpanOptions GetImageSpanOptions(const Ark_RichEditorGesture& gesture)
{
    Ark_RichEditorImageSpanOptions options = {
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>(gesture),
        .imageStyle = Converter::ArkValue<Opt_RichEditorImageSpanStyle>(),
        .offset = Converter::ArkValue<Opt_Number>(),
    };

    return Converter::ArkValue<Opt_RichEditorImageSpanOptions>(options);
}

Opt_RichEditorTextSpanOptions GetTextSpanOptions(const Ark_RichEditorGesture& gesture)
{
    Ark_RichEditorTextSpanOptions options = {
        .offset = Converter::ArkValue<Opt_Number>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>(gesture),
    };

    return Converter::ArkValue<Opt_RichEditorTextSpanOptions>(options);
}

struct CheckEvent {
    Ark_Int32 offsetX = -1;
    Ark_Int32 offsetY = -1;
};

const double OFFSET_X = 60.4f;
const double OFFSET_Y = 85.5f;
const int32_t RESOURCE_ID = 456;

const std::string STR_URL = "https://www.example.com/xxx.png";
const std::string TEXT_SPAN_VALUE = "test value";
} // namespace

class RichEditorControllerAccessorCallbackTest : public AccessorTestBase<GENERATED_ArkUIRichEditorControllerAccessor,
    &GENERATED_ArkUIAccessors::getRichEditorControllerAccessor, RichEditorControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        
        mockRichEditorController_ = new MockRichEditorController();
        mockRichEditorControllerKeeper_ = AceType::Claim(mockRichEditorController_);
        ASSERT_NE(mockRichEditorControllerKeeper_, nullptr);
        
        auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockRichEditorControllerKeeper_);
        
        ASSERT_NE(mockRichEditorController_, nullptr);
    }

    void TearDown() override
    {
        mockRichEditorControllerKeeper_ = nullptr;
        mockRichEditorController_ = nullptr;
    }

    MockRichEditorController *mockRichEditorController_ = nullptr;
    RefPtr<MockRichEditorController> mockRichEditorControllerKeeper_ = nullptr;
};

/**
 * @tc.name: addImageSpanTestGestureOnClick
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorCallbackTest, addImageSpanTestGestureOnClick, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent;
    auto onClick = [](Ark_VMContext, Ark_Int32 nodeId, const Ark_ClickEvent event) {
        auto peer = event;
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .offsetX = Converter::Convert<int32_t>(accessor->getX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getY(peer)),
        };
        accessor->destroyPeer(peer);
    };
    auto arkOnClick = Converter::ArkValue<Callback_ClickEvent_Void>(onClick, RESOURCE_ID);

    Ark_RichEditorGesture gesture = {
        .onClick = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(arkOnClick),
        .onLongPress = Converter::ArkValue<Opt_Callback_GestureEvent_Void>(),
    };

    auto optOptions = GetImageSpanOptions(gesture);

    auto resourceStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(STR_URL);
    auto value = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr, Ark_ResourceStr>(resourceStr);

    g_gestureOptions = UserGestureOptions();
    ASSERT_EQ(g_gestureOptions.onClick, nullptr);
    accessor_->addImageSpan(peer_, &value, &optOptions);
    ASSERT_NE(g_gestureOptions.onClick, nullptr);

    GestureEvent event;
    event.SetLocalLocation(Offset(OFFSET_X, OFFSET_Y));
    g_gestureOptions.onClick(event);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent.value().offsetY, static_cast<int32_t>(OFFSET_Y));
}

/**
 * @tc.name: addImageSpanTestGestureOnLongPress
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorCallbackTest, addImageSpanTestGestureOnLongPress, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent;
    auto onLongPress = [](Ark_VMContext, Ark_Int32 nodeId, const Ark_GestureEvent event) {
        auto peer = event;
        auto accessor = GeneratedModifier::GetGestureEventAccessor();
        checkEvent = {
            .offsetX = Converter::Convert<int32_t>(accessor->getOffsetX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getOffsetY(peer)),
        };
        accessor->destroyPeer(peer);
    };
    auto arkOnLongPress = Converter::ArkValue<Callback_GestureEvent_Void>(onLongPress, RESOURCE_ID);

    Ark_RichEditorGesture gesture = {
        .onClick = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(),
        .onLongPress = Converter::ArkValue<Opt_Callback_GestureEvent_Void>(arkOnLongPress),
    };

    auto optOptions = GetImageSpanOptions(gesture);

    auto resourceStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(STR_URL);
    auto value = Converter::ArkUnion<Ark_Union_PixelMap_ResourceStr, Ark_ResourceStr>(resourceStr);

    g_gestureOptions = UserGestureOptions();
    ASSERT_EQ(g_gestureOptions.onLongPress, nullptr);
    accessor_->addImageSpan(peer_, &value, &optOptions);
    ASSERT_NE(g_gestureOptions.onLongPress, nullptr);

    GestureEvent event;
    event.SetOffsetX(OFFSET_X);
    event.SetOffsetY(OFFSET_Y);
    g_gestureOptions.onLongPress(event);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent.value().offsetY, static_cast<int32_t>(OFFSET_Y));
}

/**
 * @tc.name: addTextSpanTestGestureOnClick
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorCallbackTest, addTextSpanTestGestureOnClick, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent;
    auto onClick = [](Ark_VMContext, Ark_Int32 nodeId, const Ark_ClickEvent event) {
        auto peer = event;
        auto accessor = GeneratedModifier::GetClickEventAccessor();
        checkEvent = {
            .offsetX = Converter::Convert<int32_t>(accessor->getX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getY(peer)),
        };
        accessor->destroyPeer(peer);
    };
    auto arkOnClick = Converter::ArkValue<Callback_ClickEvent_Void>(onClick, RESOURCE_ID);

    Ark_RichEditorGesture gesture = {
        .onClick = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(arkOnClick),
        .onLongPress = Converter::ArkValue<Opt_Callback_GestureEvent_Void>(),
    };

    auto optOptions = GetTextSpanOptions(gesture);

    Converter::ConvContext ctx;
    Ark_String value = Converter::ArkValue<Ark_String>(TEXT_SPAN_VALUE, &ctx);

    g_gestureOptions = UserGestureOptions();
    ASSERT_EQ(g_gestureOptions.onClick, nullptr);
    accessor_->addTextSpan(peer_, &value, &optOptions);
    ASSERT_NE(g_gestureOptions.onClick, nullptr);

    GestureEvent event;
    event.SetLocalLocation(Offset(OFFSET_X, OFFSET_Y));
    g_gestureOptions.onClick(event);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent.value().offsetY, static_cast<int32_t>(OFFSET_Y));
}

/**
 * @tc.name: addTextSpanTestGestureOnLongPress
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorCallbackTest, addTextSpanTestGestureOnLongPress, TestSize.Level1)
{
    static std::optional<CheckEvent> checkEvent;
    auto onLongPress = [](Ark_VMContext, Ark_Int32 nodeId, const Ark_GestureEvent event) {
        auto peer = event;
        auto accessor = GeneratedModifier::GetGestureEventAccessor();
        checkEvent = {
            .offsetX = Converter::Convert<int32_t>(accessor->getOffsetX(peer)),
            .offsetY = Converter::Convert<int32_t>(accessor->getOffsetY(peer)),
        };
        accessor->destroyPeer(peer);
    };
    auto arkOnLongPress = Converter::ArkValue<Callback_GestureEvent_Void>(onLongPress, RESOURCE_ID);

    Ark_RichEditorGesture gesture = {
        .onClick = Converter::ArkValue<Opt_Callback_ClickEvent_Void>(),
        .onLongPress = Converter::ArkValue<Opt_Callback_GestureEvent_Void>(arkOnLongPress),
    };

    auto optOptions = GetTextSpanOptions(gesture);

    Converter::ConvContext ctx;
    Ark_String value = Converter::ArkValue<Ark_String>(TEXT_SPAN_VALUE, &ctx);

    g_gestureOptions = UserGestureOptions();
    ASSERT_EQ(g_gestureOptions.onLongPress, nullptr);
    accessor_->addTextSpan(peer_, &value, &optOptions);
    ASSERT_NE(g_gestureOptions.onLongPress, nullptr);

    GestureEvent event;
    event.SetOffsetX(OFFSET_X);
    event.SetOffsetY(OFFSET_Y);
    g_gestureOptions.onLongPress(event);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().offsetX, static_cast<int32_t>(OFFSET_X));
    EXPECT_EQ(checkEvent.value().offsetY, static_cast<int32_t>(OFFSET_Y));
}
} // namespace OHOS::Ace::NG