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

#include "accessor_test_base.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;
using namespace Converter;

class NavPathStackAccessorTest : public AccessorTestBase<GENERATED_ArkUINavPathStackAccessor,
    &GENERATED_ArkUIAccessors::getNavPathStackAccessor, NavPathStackPeer> {
public:
    Ark_NodeHandle node_ = nullptr;

    virtual Ark_NodeHandle CreateNode(GENERATED_Ark_NodeType realNode = GENERATED_Ark_NodeType())
    {
        return basicAPI_ ? basicAPI_->createNode(realNode, GENERATED_ARKUI_AUTO_GENERATE_NODE_ID, 0) : nullptr;
    }

    virtual void DisposeNode(Ark_NodeHandle &node)
    {
        if (basicAPI_) {
            basicAPI_->disposeNode(node);
        }
        node = nullptr;
    }

    static void SetUpTestCase()
    {
        AccessorTestBase::SetUpTestCase();

        AccessorTestBase::SetupTheme<NavigationBarTheme>();
        themeConstants_->LoadTheme(0);
        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
    }

    static void TearDownTestCase()
    {
        AccessorTestBase::TearDownTestCase();
        MockPipelineContext::GetCurrent()->SetTaskExecutor(nullptr);
    }

    virtual void SetUp(void)
    {
        AccessorTestBase::SetUp();

        // create the NavigationNode
        node_ = CreateNode(GENERATED_ARKUI_NAVIGATION);
        ASSERT_NE(node_, nullptr);
        // link peer to the node
        ASSERT_NE(modifier_, nullptr);
        ASSERT_NE(modifier_->setNavigationOptions1, nullptr);
        Ark_Materialized arkValue { .ptr = peer_ };
        modifier_->setNavigationOptions1(node_, &arkValue);
    }

    virtual void TearDown(void)
    {
        // unlink peer from node
        ASSERT_NE(modifier_, nullptr);
        ASSERT_NE(modifier_->setNavigationOptions1, nullptr);
        Ark_Materialized arkValue { .ptr = nullptr };
        modifier_->setNavigationOptions1(node_, &arkValue);
        // destroy node
        DisposeNode(node_);
    }

    inline static const GENERATED_ArkUIBasicNodeAPI *basicAPI_
        = reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_BASIC,
            GENERATED_ARKUI_BASIC_NODE_API_VERSION)
        );
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL, GENERATED_ARKUI_FULL_API_VERSION)
        );
    inline static const GENERATED_ArkUINodeModifiers *nodeModifiers_
        = fullAPI_ ? fullAPI_->getNodeModifiers() : nullptr;

    inline static const GENERATED_ArkUINavigationModifier *modifier_
        = nodeModifiers_ && nodeModifiers_->getNavigationModifier
            ? (*(nodeModifiers_->getNavigationModifier))() : nullptr;
};

/**
 * @tc.name: bothPushPath0Pop0Test
 * @tc.desc: Check the functionality of both NavPathStackAccessor::PushPath0Impl and Pop0Impl
 * @tc.type: FUNC
 */
HWTEST_F(NavPathStackAccessorTest, bothPushPath0Pop0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->pushPath0, nullptr);
    ASSERT_NE(accessor_->pop0, nullptr);
    ASSERT_NE(accessor_->size, nullptr);

    EXPECT_EQ(accessor_->size(peer_), 0);

    Ark_NavPathInfo path {
        .name = ArkValue<Ark_String>("aaaa"),
        .param = ArkValue<Opt_CustomObject>(),
        .onPop = ArkValue<Opt_Callback_PopInfo_Void>(),
        .isEntry = ArkValue<Opt_Boolean>()
    };
    Opt_Boolean animated = ArkValue<Opt_Boolean>();
    accessor_->pushPath0(peer_, &path, &animated);

    EXPECT_EQ(accessor_->size(peer_), 1);

    accessor_->pop0(peer_, &animated);

    EXPECT_EQ(accessor_->size(peer_), 0);
}

/**
 * @tc.name: pushPath1Test
 * @tc.desc: Check the functionality of  NavPathStackAccessor::PushPath1Impl
 * @tc.type: FUNC
 */
HWTEST_F(NavPathStackAccessorTest, pushPath1Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->pushPath1, nullptr);
    ASSERT_NE(accessor_->pop0, nullptr);
    ASSERT_NE(accessor_->size, nullptr);

    EXPECT_EQ(accessor_->size(peer_), 0);

    Ark_NavPathInfo path {
        .name = ArkValue<Ark_String>(""),
        .param = ArkValue<Opt_CustomObject>(),
        .onPop = ArkValue<Opt_Callback_PopInfo_Void>(),
        .isEntry = ArkValue<Opt_Boolean>()
    };
    auto pathA = path; pathA.name = ArkValue<Ark_String>("PathA");
    auto pathB = path; pathB.name = ArkValue<Ark_String>("PathB");
    auto pathC = path; pathC.name = ArkValue<Ark_String>("PathC");
    auto pathD = path; pathD.name = ArkValue<Ark_String>("PathD");

    auto options = ArkValue<Opt_NavigationOptions>(Ark_NavigationOptions{
        .launchMode = ArkValue<Opt_LaunchMode>(Ark_LaunchMode{ARK_LAUNCH_MODE_STANDARD}),
        .animated = ArkValue<Opt_Boolean>()
    });

    accessor_->pushPath1(peer_, &pathA, &options);
    accessor_->pushPath1(peer_, &pathB, &options);
    accessor_->pushPath1(peer_, &pathC, &options);
    accessor_->pushPath1(peer_, &pathD, &options);
    EXPECT_EQ(accessor_->size(peer_), 4);

    auto optionsMove = ArkValue<Opt_NavigationOptions>(Ark_NavigationOptions{
        .launchMode = ArkValue<Opt_LaunchMode>(Ark_LaunchMode{ARK_LAUNCH_MODE_MOVE_TO_TOP_SINGLETON}),
        .animated = ArkValue<Opt_Boolean>()
    });
    accessor_->pushPath1(peer_, &pathB, &optionsMove);
    EXPECT_EQ(accessor_->size(peer_), 4); // the size is same, but B ia at top and over of D, C, A

    auto optionsPop = ArkValue<Opt_NavigationOptions>(Ark_NavigationOptions{
        .launchMode = ArkValue<Opt_LaunchMode>(Ark_LaunchMode{ARK_LAUNCH_MODE_POP_TO_SINGLETON}),
        .animated = ArkValue<Opt_Boolean>()
    });
    accessor_->pushPath1(peer_, &pathC, &optionsPop);
    EXPECT_EQ(accessor_->size(peer_), 2); // the stack reduced to top page C

    Opt_Boolean animated = ArkValue<Opt_Boolean>();
    accessor_->pop0(peer_, &animated);
    accessor_->pop0(peer_, &animated);
    EXPECT_EQ(accessor_->size(peer_), 0);
}

/**
 * @tc.name: bothPushPath1Pop1Test
 * @tc.desc: Check the functionality of  NavPathStackAccessor::pushPath1Impl, ::pop1Impl
 * @tc.type: FUNC
 */
HWTEST_F(NavPathStackAccessorTest, bothPushPath1Pop1ParamCallbackTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->pushPath1, nullptr);
    ASSERT_NE(accessor_->pop1, nullptr);
    ASSERT_NE(accessor_->size, nullptr);

    EXPECT_EQ(accessor_->size(peer_), 0);

    static const std::string expectedName = "PageA";
    static const std::string expectedData = "smth custom data from developer";
    static const Ark_Int32 expectedResId = 123;
    static bool wasInvoke = false;
    auto checkFunc = [](const Ark_Int32 resourceId, const Ark_PopInfo parameter) {
        wasInvoke = true;
        EXPECT_EQ(expectedResId, resourceId);
        auto name = Convert<std::string>(parameter.info.name);
        EXPECT_EQ(expectedName, name);
        auto data = Convert<std::string>(parameter.result.string);
        EXPECT_EQ(expectedData, data);
    };

    Ark_NavPathInfo path {
        .name = ArkValue<Ark_String>(expectedName),
        .param = ArkValue<Opt_CustomObject>(),
        .onPop = ArkValue<Opt_Callback_PopInfo_Void>(ArkValue<Callback_PopInfo_Void>(checkFunc, expectedResId)),
        .isEntry = ArkValue<Opt_Boolean>()
    };

    auto optionsPush = ArkValue<Opt_NavigationOptions>(Ark_NavigationOptions{
        .launchMode = ArkValue<Opt_LaunchMode>(),
        .animated = ArkValue<Opt_Boolean>()
    });

    accessor_->pushPath1(peer_, &path, &optionsPush);
    EXPECT_EQ(accessor_->size(peer_), 1);

    EXPECT_FALSE(wasInvoke);
    Opt_Boolean animated = ArkValue<Opt_Boolean>();
    Ark_CustomObject result = {.string = ArkValue<Ark_String>(expectedData)};
    accessor_->pop1(peer_, &result, &animated);
    EXPECT_TRUE(wasInvoke);

    EXPECT_EQ(accessor_->size(peer_), 0);
}
} // namespace OHOS::Ace::NG
