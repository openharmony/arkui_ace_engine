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

#include "gmock/gmock.h"

#include "accessor_test_base.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"


namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

class GlobalScopeOhosFontAccessorTest
    : public AccessorTestBase<GENERATED_ArkUIGlobalScope_ohos_fontAccessor,
          &GENERATED_ArkUIAccessors::getGlobalScope_ohos_fontAccessor,
          GlobalScope_ohos_fontPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
    }
    void TearDown() override
    {
        AccessorTestBase::TearDown();
    }
};

namespace {
    const std::string TEST_FONTNAME = "TestName";
    const std::string TEST_FONTSRC = "TestSrc";
}

/**
 * @tc.name: RegisterFontTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeOhosFontAccessorTest, RegisterFontTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->registerFont, nullptr);
    Ark_FontOptions options = {
        .familyName = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(TEST_FONTNAME),
        .familySrc = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(TEST_FONTSRC),
    };

    struct CheckEvent {
        bool result = false;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    ASSERT_NE(pipeline, nullptr);
    auto fontmanager = pipeline->GetFontManager();
    ASSERT_NE(fontmanager, nullptr);
    auto node = NG::FrameNode::CreateFrameNode("", -1, AceType::MakeRefPtr<NG::Pattern>());
    fontmanager->RegisterCallbackNG(node, TEST_FONTNAME, []() {
        checkEvent = { .result = true };
    });

    EXPECT_FALSE(checkEvent.has_value());
    accessor_->registerFont(&options);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_TRUE(checkEvent->result);
}

/**
 * @tc.name: GetSystemFontListTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GlobalScopeOhosFontAccessorTest, GetSystemFontListTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSystemFontList, nullptr);
    ASSERT_NE(accessor_->registerFont, nullptr);

    Ark_FontOptions options = {
        .familyName = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(TEST_FONTNAME),
        .familySrc = Converter::ArkUnion<Ark_Union_String_Resource, Ark_String>(TEST_FONTSRC),
    };
    accessor_->registerFont(&options);

    auto list = accessor_->getSystemFontList();
    auto result = Converter::Convert<std::string>(list);
    EXPECT_EQ(result, TEST_FONTNAME);
}
} // namespace OHOS::Ace::NG