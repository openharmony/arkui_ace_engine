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

#include "gtest/gtest.h"

#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/node/view_model.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {

extern "C" const ArkUIAnyAPI* GetArkUIAPI(ArkUIAPIVariantKind kind, ArkUI_Int32 version);

template <typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestBaseParent : public testing::Test {
public:
    static void SetUpTestCase()
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp(MockPipelineContext::GetCurrent());
        ASSERT_NE(accessor_, nullptr);
        ASSERT_NE(accessor_->ctor, nullptr);
        ASSERT_NE(accessor_->getFinalizer, nullptr);
        finalyzer_ = reinterpret_cast<void (*)(PeerType *)>(accessor_->getFinalizer());
        ASSERT_NE(finalyzer_, nullptr);
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
        finalyzer_ = nullptr;
    }

    virtual void SetUp(void)
    {
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    };

    virtual void TearDown(void)
    {
        ASSERT_NE(finalyzer_, nullptr);
        finalyzer_(peer_);
        peer_ = nullptr;
    }

private:
    inline static const GENERATED_ArkUIFullNodeAPI *fullAPI_
        = reinterpret_cast<const GENERATED_ArkUIFullNodeAPI *>(
            GetArkUIAPI(static_cast<ArkUIAPIVariantKind>(GENERATED_Ark_APIVariantKind::GENERATED_FULL),
            GENERATED_ARKUI_FULL_API_VERSION)
        );
    inline static const GENERATED_ArkUIAccessors *accessors_
        = fullAPI_ ? fullAPI_->getAccessors() : nullptr;

public:
    inline static const AccessorType *accessor_ = accessors_ ? (accessors_->*GetAccessorFunc)() : nullptr;
    inline static void (*finalyzer_)(PeerType *) = nullptr;
    PeerType *peer_ = nullptr;
};

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestBase : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        ASSERT_NE(this->accessor_->ctor, nullptr);
        this->peer_ = reinterpret_cast<PeerType*>(this->accessor_->ctor());
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }
};

template<typename AccessorType, auto GetAccessorFunc, typename PeerType>
class AccessorTestCtorBase : public AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType> {
public:
    virtual void SetUp(void)
    {
        ASSERT_NE(this->accessor_->ctor, nullptr);
        this->peer_ = CreatePeerInstance();
        ASSERT_NE(this->peer_, nullptr);
        AccessorTestBaseParent<AccessorType, GetAccessorFunc, PeerType>::SetUp();
    }

    virtual PeerType* CreatePeerInstance() = 0;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_TEST_UNITTEST_CAPI_MODIFIERS_ACCESSOR_TEST_BASE_H