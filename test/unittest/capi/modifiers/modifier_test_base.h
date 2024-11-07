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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_MODIFIER_TEST_BASE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_MODIFIER_TEST_BASE_H

#include <iostream>
#include <set>

#include "gtest/gtest.h"

#include "arkoala_api.h"
#include "arkoala_api_generated.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

extern "C" const ArkUIAnyAPI* GetArkUIAPI(ArkUIAPIVariantKind kind, ArkUI_Int32 version);

void DumpJsonToFile(ArkUINodeHandle node, int index = -1);

#ifdef CAPI_BACKTRACE
void ReportTheme(ThemeType type);
void ResetThemes();
#endif

inline RefPtr<Theme> CatchEmptyTheme(ThemeType type)
{
#ifdef CAPI_BACKTRACE
    ReportTheme(type);
#endif
    return nullptr;
}

template <typename Modifier, auto GetModifierFunc, GENERATED_Ark_NodeType NodeType>
class ModifierTestBase : public testing::Test {
public:
    ArkUINodeHandle node_ = nullptr;

    static ArkUINodeHandle CreateNode()
    {
        return basicAPI_ ? basicAPI_->createNode(NodeType, ARKUI_AUTO_GENERATE_NODE_ID, 0) : nullptr;
    }

    static void DisposeNode(ArkUINodeHandle &node)
    {
        if (basicAPI_) {
            basicAPI_->disposeNode(node);
        }
        node = nullptr;
    }

    static const GENERATED_ArkUINodeModifiers *GetNodeModifiers()
    {
        return nodeModifiers_;
    }

    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        themeManager_ = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);

        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        EXPECT_CALL(*themeManager_, GetTheme(testing::_)).WillRepeatedly(CatchEmptyTheme);

        themeConstants_->LoadTheme(0);
        MockThemeStyle::GetInstance()->SetAttributes({});

        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

        auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>(true);
        MockPipelineContext::GetCurrent()->SetTaskExecutor(taskExecutor);

#ifdef CAPI_BACKTRACE
        ResetThemes();
#endif
    }

    static void TearDownTestCase()
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
        EXPECT_CALL(*themeManager_, GetTheme(Theme::TypeId())).WillRepeatedly(testing::Return(theme));
    }

    static RefPtr<ThemeStyle> SetupThemeStyle(const std::string& pattern)
    {
        auto themeStyle = AceType::MakeRefPtr<ThemeStyle>();
        MockThemeStyle::GetInstance()->SetAttr(pattern, { .value = themeStyle });
        return themeStyle;
    }

    static void AddResource(std::string key, const ResRawValue& value)
    {
        ThemeConstantsType type = ThemeConstantsType::ERROR;
        if (std::holds_alternative<Color>(value)) {
            type = ThemeConstantsType::COLOR;
        } else if (std::holds_alternative<Dimension>(value)) {
            type = ThemeConstantsType::DIMENSION;
        } else if (std::holds_alternative<int32_t>(value)) {
            type = ThemeConstantsType::INT;
        } else if (std::holds_alternative<uint32_t>(value)) {
            type = ThemeConstantsType::INT;
        } else if (std::holds_alternative<double>(value)) {
            type = ThemeConstantsType::DOUBLE;
        } else if (std::holds_alternative<std::string>(value)) {
            type = ThemeConstantsType::STRING;
        }
        ASSERT_NE(type, ThemeConstantsType::ERROR);
        MockThemeStyle::GetInstance()->SetAttr(key, { .type = type, .value = value });
    }

    static void AddResource(uint32_t key, const ResRawValue& value)
    {
        AddResource(std::to_string(key), value);
    }

    template<typename T, typename U>
    static void AddResource(const std::tuple<T, U>& resId, const ResRawValue& value)
    {
        AddResource(std::get<0>(resId), value);
    }

    virtual void SetUp(void)
    {
        ASSERT_NE(modifier_, nullptr);
        node_ = CreateNode();
        ASSERT_NE(node_, nullptr);
    }

    virtual void TearDown(void)
    {
        DumpJsonToFile(node_);
        DisposeNode(node_);
    }

protected:
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

    inline static const Modifier *modifier_
        = nodeModifiers_ && GetModifierFunc ? (nodeModifiers_->*GetModifierFunc)() : nullptr;

    inline static const GENERATED_ArkUICommonMethodModifier *commonModifier_
        = nodeModifiers_ ? (nodeModifiers_->getCommonMethodModifier)() : nullptr;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_MODIFIER_TEST_BASE_H
