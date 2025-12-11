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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_ACCESSOR_TEST_BASE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_ACCESSOR_TEST_BASE_H

#include <gtest/gtest.h>

#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using testing::NiceMock;

namespace OHOS::Ace {
inline void PrintTo(const Dimension& dim, std::ostream* os)
{
    *os << dim.ToString();
}
inline void PrintTo(const CalcDimension& dim, std::ostream* os)
{
    *os << dim.ToString();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

extern "C" const OH_AnyAPI* GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind kind, int version);

#ifdef CAPI_BACKTRACE
void ReportTheme(ThemeType type);
void ResetThemes();
#endif

inline RefPtr<Theme> CatchEmptyAccessorTheme1(ThemeType type)
{
#ifdef CAPI_BACKTRACE
    ReportTheme(type);
#endif
    return nullptr;
}
inline RefPtr<Theme> CatchEmptyAccessorTheme2(ThemeType type, uint32_t id)
{
#ifdef CAPI_BACKTRACE
    ReportTheme(type);
#endif
    return nullptr;
}

template<typename T, typename = void>
struct HasFinalizer : std::false_type {};

template<typename T>
struct HasFinalizer<T, std::void_t<decltype(T().getFinalizer)>> : std::true_type {};

template <typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestBaseParent : public testing::Test {
public:
    static void SetUpTestCase()
    {
        fullAPI_ = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GENERATED_GetArkAnyAPI(GENERATED_Ark_APIVariantKind::GENERATED_FULL, GENERATED_ARKUI_FULL_API_VERSION)
        );
        accessors_ = fullAPI_ ? fullAPI_->getAccessors() : nullptr;
        accessor_ = accessors_ ? (accessors_->*GetAccessorFunc)() : nullptr;
        MockPipelineContext::SetUp();

        g_isResourceDecoupling = false;
        themeManager_ = AceType::MakeRefPtr<NiceMock<MockThemeManager>>();
        ASSERT_TRUE(MockPipelineContext::GetCurrent());
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager_);
        // assume using of test/mock/core/common/mock_theme_constants.cpp in build
        themeConstants_ = AceType::MakeRefPtr<ThemeConstants>(nullptr);
        EXPECT_CALL(*themeManager_, GetThemeConstants(testing::_, testing::_))
            .WillRepeatedly(testing::Return(themeConstants_));
        ON_CALL(*themeManager_, GetTheme(testing::_)).WillByDefault(CatchEmptyAccessorTheme1);
        ON_CALL(*themeManager_, GetTheme(testing::_, testing::_)).WillByDefault(CatchEmptyAccessorTheme2);

        themeConstants_->LoadTheme(0);
        MockThemeStyle::GetInstance()->SetAttributes({});

        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        ASSERT_NE(accessor_, nullptr);
        if constexpr (HasFinalizer<AccessorType>::value) {
            ASSERT_NE(accessor_->getFinalizer, nullptr);
            finalyzer_ = reinterpret_cast<void (*)(PeerType *)>(accessor_->getFinalizer());
            ASSERT_NE(finalyzer_, nullptr);
        }

        MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        MockPipelineContext::GetCurrent()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

#ifdef CAPI_BACKTRACE
        ResetThemes();
#endif
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        finalyzer_ = nullptr;
        themeManager_ = nullptr;
        themeConstants_ = nullptr;
    }

    static void AddResource(const std::string& key, const ResRawValue& value)
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

    static void AddResource(int64_t key, const ResRawValue& value)
    {
        AddResource(std::to_string(key), value);
    }

    template<typename T, typename U>
    static void AddResource(const std::tuple<T, U>& resId, const ResRawValue& value)
    {
        AddResource(std::get<0>(resId), value);
    }

    virtual void TearDown(void)
    {
        if constexpr (HasFinalizer<AccessorType>::value) {
            ASSERT_NE(finalyzer_, nullptr);
            finalyzer_(peer_);
        }
        peer_ = nullptr;
        PeerUtils::ClearAllPeers();
    }

    template<typename Theme>
    static void SetupTheme()
    {
        auto theme = typename Theme::Builder().Build(themeConstants_);
        ON_CALL(*themeManager_, GetTheme(Theme::TypeId())).WillByDefault(testing::Return(theme));
        ON_CALL(*themeManager_, GetTheme(Theme::TypeId(), testing::_)).WillByDefault(testing::Return(theme));
    }

protected:
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_;
    inline static const GENERATED_ArkUIAccessors *accessors_;

    inline static RefPtr<MockThemeManager> themeManager_;
    inline static RefPtr<ThemeConstants> themeConstants_;

public:
    inline static const AccessorType *accessor_;
    inline static void (*finalyzer_)(PeerType *) = nullptr;
    PeerType *peer_ = nullptr;
};

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestBase : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        ASSERT_NE(this->accessor_->construct, nullptr);
        this->peer_ = static_cast<PeerType *>(this->accessor_->construct());
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }
};

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestBase0 : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        ASSERT_NE(this->accessor_->construct0, nullptr);
        this->peer_ = static_cast<PeerType *>(this->accessor_->construct0());
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }
};

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestCtorBase : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        this->peer_ = CreatePeer();
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }

    virtual void *CreatePeerInstance() = 0;

    PeerType *CreatePeer()
    {
        return static_cast<PeerType *>(CreatePeerInstance());
    }
};

template<typename AccessorType, auto GetAccessorFunc>
class StaticAccessorTest : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, void> {
};

MATCHER_P(CompareOptMarginsPaddings, expected, "Compare margins and paddings")
{
    auto optArg = Converter::OptConvert<MarginProperty>(arg);
    auto optExpected = Converter::OptConvert<MarginProperty>(expected);
    return optArg == optExpected;
}

MATCHER_P(CompareOptBorderRadius, expected, "Compare border radius")
{
    auto optArg = Converter::OptConvert<BorderRadiusProperty>(arg);
    auto optExpected = Converter::OptConvert<BorderRadiusProperty>(expected);
    return optArg == optExpected;
}

MATCHER_P(CompareArkSize, expected, "Compare size values")
{
    auto optArg = Converter::OptConvert<ImageSpanSize>(arg);
    auto optExpected = Converter::OptConvert<ImageSpanSize>(expected);
    return optArg == optExpected;
}

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_ACCESSOR_TEST_BASE_H
