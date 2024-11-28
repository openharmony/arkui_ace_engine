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
        return basicAPI_ ? basicAPI_->createNode(realNode, ARKUI_AUTO_GENERATE_NODE_ID, 0) : nullptr;
    }

    virtual void DisposeNode(Ark_NodeHandle &node)
    {
        if (basicAPI_) {
            basicAPI_->disposeNode(node);
        }
        node = nullptr;
    }

    template<typename Theme>
    static void SetupTheme()
    {
        auto theme = typename Theme::Builder().Build(themeConstants_);
        EXPECT_CALL(*themeManager_, GetTheme(Theme::TypeId())).WillRepeatedly(testing::Return(theme));
    }

    static void SetUpTestCase()
    {
        AccessorTestBase::SetUpTestCase();

        themeManager_ = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        SetupTheme<NavigationBarTheme>();
        themeConstants_->LoadTheme(0);
        MockThemeStyle::GetInstance()->SetAttributes({});
        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetTaskExecutor(nullptr);
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        themeManager_ = nullptr;
        themeConstants_ = nullptr;
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

private:
    inline static RefPtr<MockThemeManager> themeManager_;
    inline static RefPtr<ThemeConstants> themeConstants_;

    inline static const GENERATED_ArkUIBasicNodeAPI *basicAPI_
        = reinterpret_cast<const GENERATED_ArkUIBasicNodeAPI *>(
            GetArkUIAPI(static_cast<ArkUIAPIVariantKind>(GENERATED_Ark_APIVariantKind::GENERATED_BASIC),
            GENERATED_ARKUI_BASIC_NODE_API_VERSION)
        );
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GetArkUIAPI(static_cast<ArkUIAPIVariantKind>(GENERATED_Ark_APIVariantKind::GENERATED_FULL),
            GENERATED_ARKUI_FULL_API_VERSION)
        );
    inline static const GENERATED_ArkUINodeModifiers *nodeModifiers_
        = fullAPI_ ? fullAPI_->getNodeModifiers() : nullptr;

    inline static const GENERATED_ArkUINavigationModifier *modifier_
        = nodeModifiers_ && nodeModifiers_->getNavigationModifier
            ? (*(nodeModifiers_->getNavigationModifier))() : nullptr;
};

/**
 * @tc.name: pushPath0Test
 * @tc.desc: Check the functionality of  NavPathStackAccessor::pushPath0Impl
 * @tc.type: FUNC
 */
HWTEST_F(NavPathStackAccessorTest, pushPath0Test, TestSize.Level1)
{
    ASSERT_NE(accessor_->pushPath0, nullptr);
    ASSERT_NE(accessor_->size, nullptr);

    EXPECT_EQ(accessor_->size(peer_), 0);

    Ark_NavPathInfo arkNavPathInfo {
        .name = ArkValue<Ark_String>("aaaa"),
        .param = ArkValue<Opt_CustomObject>(),
        .onPop = ArkValue<Opt_Callback_PopInfo_Void>(),
        .isEntry = ArkValue<Opt_Boolean>()
    };
    Opt_Boolean animated = ArkValue<Opt_Boolean>();
    accessor_->pushPath0(peer_, &arkNavPathInfo, &animated);

    EXPECT_EQ(accessor_->size(peer_), 1);
}

} // namespace OHOS::Ace::NG
