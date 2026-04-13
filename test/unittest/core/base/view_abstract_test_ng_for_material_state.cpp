/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/unittest/core/base/view_abstract_test_ng.h"

#define private public
#define protected public

#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "core/common/ace_application_info.h"
#include "core/components/common/properties/ui_material.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

// ============================================================================
// MaterialUtils::ParseMaterialState 测试
// ============================================================================

/**
 * @tc.name: ParseMaterialState001
 * @tc.desc: Test ParseMaterialState with "enable" returns ENABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable" and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::ENABLE.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::ENABLE);
}

/**
 * @tc.name: ParseMaterialState002
 * @tc.desc: Test ParseMaterialState with "disable" returns DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "disable" and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::DISABLE.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::DISABLE);
}

/**
 * @tc.name: ParseMaterialState003
 * @tc.desc: Test ParseMaterialState with "default" returns DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "default" and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::DEFAULT.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("default");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::DEFAULT);
}

/**
 * @tc.name: ParseMaterialState004
 * @tc.desc: Test ParseMaterialState with empty string returns DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to empty string and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::DEFAULT.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::DEFAULT);
}

/**
 * @tc.name: ParseMaterialState005
 * @tc.desc: Test ParseMaterialState with invalid value returns DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to invalid value and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::DEFAULT.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("invalid_value");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::DEFAULT);
}

/**
 * @tc.name: ParseMaterialState006
 * @tc.desc: Test ParseMaterialState with uppercase "ENABLE" (case sensitive) returns DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialState006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "ENABLE" (uppercase) and get configured state.
     * @tc.expected: step1. GetConfiguredMaterialState returns MaterialState::DEFAULT (case sensitive).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("ENABLE");
    auto state = MaterialUtils::GetConfiguredMaterialState();
    EXPECT_EQ(state, MaterialState::DEFAULT);
}

// ============================================================================
// MaterialUtils::ParseMaterialType 测试
// ============================================================================

/**
 * @tc.name: ParseMaterialType001
 * @tc.desc: Test ParseMaterialType with "immersive" returns IMMERSIVE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialType to "immersive" and get configured type.
     * @tc.expected: step1. GetConfiguredMaterialType returns MaterialType::IMMERSIVE.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialType("immersive");
    auto type = MaterialUtils::GetConfiguredMaterialType();
    EXPECT_EQ(type, MaterialType::IMMERSIVE);
}

/**
 * @tc.name: ParseMaterialType002
 * @tc.desc: Test ParseMaterialType with empty string returns IMMERSIVE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialType to empty string and get configured type.
     * @tc.expected: step1. GetConfiguredMaterialType returns MaterialType::IMMERSIVE (default).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialType("");
    auto type = MaterialUtils::GetConfiguredMaterialType();
    EXPECT_EQ(type, MaterialType::IMMERSIVE);
}

/**
 * @tc.name: ParseMaterialType003
 * @tc.desc: Test ParseMaterialType with invalid value returns IMMERSIVE (fallback)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ParseMaterialType003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialType to "unknown_type" and get configured type.
     * @tc.expected: step1. GetConfiguredMaterialType returns MaterialType::IMMERSIVE (fallback).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialType("unknown_type");
    auto type = MaterialUtils::GetConfiguredMaterialType();
    EXPECT_EQ(type, MaterialType::IMMERSIVE);
}

// ============================================================================
// MaterialUtils::IsMaterialDisabled 测试
// ============================================================================

/**
 * @tc.name: IsMaterialDisabled001
 * @tc.desc: Test IsMaterialDisabled returns true when state is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialDisabled001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "disable".
     * @tc.expected: step1. IsMaterialDisabled returns true.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    EXPECT_TRUE(MaterialUtils::IsMaterialDisabled());
}

/**
 * @tc.name: IsMaterialDisabled002
 * @tc.desc: Test IsMaterialDisabled returns false when state is ENABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialDisabled002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable".
     * @tc.expected: step1. IsMaterialDisabled returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    EXPECT_FALSE(MaterialUtils::IsMaterialDisabled());
}

/**
 * @tc.name: IsMaterialDisabled003
 * @tc.desc: Test IsMaterialDisabled returns false when state is DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialDisabled003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "default".
     * @tc.expected: step1. IsMaterialDisabled returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("default");
    EXPECT_FALSE(MaterialUtils::IsMaterialDisabled());
}

/**
 * @tc.name: IsMaterialDisabled004
 * @tc.desc: Test IsMaterialDisabled returns false when state is not configured (empty)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialDisabled004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to empty string.
     * @tc.expected: step1. IsMaterialDisabled returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("");
    EXPECT_FALSE(MaterialUtils::IsMaterialDisabled());
}

// ============================================================================
// MaterialUtils::IsMaterialEnabled 测试
// ============================================================================

/**
 * @tc.name: IsMaterialEnabled001
 * @tc.desc: Test IsMaterialEnabled returns true when state is ENABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialEnabled001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable".
     * @tc.expected: step1. IsMaterialEnabled returns true.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    EXPECT_TRUE(MaterialUtils::IsMaterialEnabled());
}

/**
 * @tc.name: IsMaterialEnabled002
 * @tc.desc: Test IsMaterialEnabled returns false when state is DEFAULT
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialEnabled002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "default".
     * @tc.expected: step1. IsMaterialEnabled returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("default");
    EXPECT_FALSE(MaterialUtils::IsMaterialEnabled());
}

/**
 * @tc.name: IsMaterialEnabled003
 * @tc.desc: Test IsMaterialEnabled returns false when state is DISABLE
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsMaterialEnabled003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "disable".
     * @tc.expected: step1. IsMaterialEnabled returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    EXPECT_FALSE(MaterialUtils::IsMaterialEnabled());
}

// ============================================================================
// MaterialUtils::IsEmptyMaterial 测试
// ============================================================================

/**
 * @tc.name: IsEmptyMaterial001
 * @tc.desc: Test IsEmptyMaterial with empty material returns true
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEmptyMaterial001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a material and set it as empty.
     * @tc.expected: step1. IsEmptyMaterial returns true.
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetEmpty(true);
    EXPECT_TRUE(MaterialUtils::IsEmptyMaterial(material));
}

/**
 * @tc.name: IsEmptyMaterial002
 * @tc.desc: Test IsEmptyMaterial with non-empty material returns false
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEmptyMaterial002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a normal material (not empty).
     * @tc.expected: step1. IsEmptyMaterial returns false.
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_FALSE(MaterialUtils::IsEmptyMaterial(material));
}

/**
 * @tc.name: IsEmptyMaterial003
 * @tc.desc: Test IsEmptyMaterial with nullptr returns false
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEmptyMaterial003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass nullptr to IsEmptyMaterial.
     * @tc.expected: step1. IsEmptyMaterial returns false (CHECK_NULL_RETURN).
     */
    RefPtr<UiMaterial> material = nullptr;
    EXPECT_FALSE(MaterialUtils::IsEmptyMaterial(material));
}

// ============================================================================
// MaterialUtils::GetInitMaterial 测试
// ============================================================================

/**
 * @tc.name: GetInitMaterial001
 * @tc.desc: Test GetInitMaterial creates IMMERSIVE material with correct style
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetInitMaterial001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetInitMaterial with REGULAR style.
     * @tc.expected: step1. Material type is IMMERSIVE and style is REGULAR.
     */
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::REGULAR);
    ASSERT_NE(material, nullptr);
    EXPECT_EQ(material->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    ASSERT_NE(material->GetImmersiveOptions(), nullptr);
    EXPECT_EQ(material->GetImmersiveOptions()->style, UiMaterialStyle::REGULAR);
}

/**
 * @tc.name: GetInitMaterial002
 * @tc.desc: Test GetInitMaterial creates IMMERSIVE material with THICK style
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetInitMaterial002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetInitMaterial with THICK style.
     * @tc.expected: step1. Material type is IMMERSIVE and style is THICK.
     */
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::THICK);
    ASSERT_NE(material, nullptr);
    EXPECT_EQ(material->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
    ASSERT_NE(material->GetImmersiveOptions(), nullptr);
    EXPECT_EQ(material->GetImmersiveOptions()->style, UiMaterialStyle::THICK);
}

/**
 * @tc.name: GetInitMaterial003
 * @tc.desc: Test GetInitMaterial creates material that is not empty
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetInitMaterial003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call GetInitMaterial and check isEmpty flag.
     * @tc.expected: step1. Material is not empty.
     */
    auto material = MaterialUtils::GetInitMaterial(UiMaterialStyle::ULTRA_THIN);
    ASSERT_NE(material, nullptr);
    EXPECT_FALSE(material->IsEmpty());
}

// ============================================================================
// MaterialUtils::PreProcessMaterial 测试
// ============================================================================

/**
 * @tc.name: PreProcessMaterial001
 * @tc.desc: Test PreProcessMaterial with nullptr returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, PreProcessMaterial001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Pass nullptr to PreProcessMaterial.
     * @tc.expected: step1. Returns nullptr.
     */
    auto result = MaterialUtils::PreProcessMaterial(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: PreProcessMaterial002
 * @tc.desc: Test PreProcessMaterial with empty material returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, PreProcessMaterial002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create empty material and pass to PreProcessMaterial.
     * @tc.expected: step1. Returns nullptr (empty material filtered out).
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetEmpty(true);
    auto result = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: PreProcessMaterial003
 * @tc.desc: Test PreProcessMaterial with valid IMMERSIVE material returns the material
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, PreProcessMaterial003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create valid IMMERSIVE material and pass to PreProcessMaterial.
     * @tc.expected: step1. Returns the same material pointer.
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ImmersiveOptions options { .style = UiMaterialStyle::REGULAR };
    material->SetImmersiveOptions(options);
    auto result = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    EXPECT_EQ(result, AceType::RawPtr(material));
}

/**
 * @tc.name: PreProcessMaterial004
 * @tc.desc: Test PreProcessMaterial with SEMI_TRANSPARENT material returns the material
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, PreProcessMaterial004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create valid SEMI_TRANSPARENT material and pass to PreProcessMaterial.
     * @tc.expected: step1. Returns the same material pointer.
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT));
    auto result = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    EXPECT_EQ(result, AceType::RawPtr(material));
}

/**
 * @tc.name: PreProcessMaterial005
 * @tc.desc: Test PreProcessMaterial with invalid type (99) returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, PreProcessMaterial005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create material with invalid type 99 and pass to PreProcessMaterial.
     * @tc.expected: step1. Returns nullptr (invalid type filtered out).
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(99); // Invalid type
    auto result = MaterialUtils::PreProcessMaterial(AceType::RawPtr(material));
    EXPECT_EQ(result, nullptr);
}

// ============================================================================
// MaterialUtils::IsEnableMaterialParam 测试
// ============================================================================

/**
 * @tc.name: IsEnableMaterialParam001
 * @tc.desc: Test IsEnableMaterialParam returns false when material is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEnableMaterialParam001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to DISABLE, create valid material.
     * @tc.expected: step1. IsEnableMaterialParam returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_FALSE(MaterialUtils::IsEnableMaterialParam(material));
}

/**
 * @tc.name: IsEnableMaterialParam002
 * @tc.desc: Test IsEnableMaterialParam returns true with valid material in ENABLE state
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEnableMaterialParam002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to ENABLE, create valid material.
     * @tc.expected: step1. IsEnableMaterialParam returns true.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_TRUE(MaterialUtils::IsEnableMaterialParam(material));
}

/**
 * @tc.name: IsEnableMaterialParam003
 * @tc.desc: Test IsEnableMaterialParam returns false with empty material
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEnableMaterialParam003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to ENABLE, create empty material.
     * @tc.expected: step1. IsEnableMaterialParam returns false (empty material).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetEmpty(true);
    EXPECT_FALSE(MaterialUtils::IsEnableMaterialParam(material));
}

/**
 * @tc.name: IsEnableMaterialParam004
 * @tc.desc: Test IsEnableMaterialParam returns false with nullptr
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEnableMaterialParam004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to ENABLE, pass nullptr.
     * @tc.expected: step1. IsEnableMaterialParam returns false.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    RefPtr<UiMaterial> material = nullptr;
    EXPECT_FALSE(MaterialUtils::IsEnableMaterialParam(material));
}

/**
 * @tc.name: IsEnableMaterialParam005
 * @tc.desc: Test IsEnableMaterialParam returns true with valid material in DEFAULT state
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, IsEnableMaterialParam005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to DEFAULT, create valid material.
     * @tc.expected: step1. IsEnableMaterialParam returns true.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("default");
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_TRUE(MaterialUtils::IsEnableMaterialParam(material));
}

// ============================================================================
// UiMaterial::CreateEmpty / SetEmpty / IsEmpty 测试
// ============================================================================

/**
 * @tc.name: UiMaterialEmpty001
 * @tc.desc: Test CreateEmpty creates a material with IsEmpty() == true
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialEmpty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call UiMaterial::CreateEmpty().
     * @tc.expected: step1. Material is not nullptr and IsEmpty() returns true.
     */
    auto material = UiMaterial::CreateEmpty();
    ASSERT_NE(material, nullptr);
    EXPECT_TRUE(material->IsEmpty());
}

/**
 * @tc.name: UiMaterialEmpty002
 * @tc.desc: Test SetEmpty and IsEmpty round-trip
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialEmpty002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create material, set empty to true, then false.
     * @tc.expected: step1. IsEmpty follows SetEmpty value.
     */
    auto material = AceType::MakeRefPtr<UiMaterial>();
    EXPECT_FALSE(material->IsEmpty());
    material->SetEmpty(true);
    EXPECT_TRUE(material->IsEmpty());
    material->SetEmpty(false);
    EXPECT_FALSE(material->IsEmpty());
}

/**
 * @tc.name: UiMaterialEmpty003
 * @tc.desc: Test operator== considers isEmpty_ field
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialEmpty003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create two materials with same type but different isEmpty.
     * @tc.expected: step1. They are not equal.
     */
    auto mat1 = AceType::MakeRefPtr<UiMaterial>();
    auto mat2 = AceType::MakeRefPtr<UiMaterial>();
    mat1->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    mat2->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    EXPECT_TRUE(*mat1 == *mat2);
    mat2->SetEmpty(true);
    EXPECT_FALSE(*mat1 == *mat2);
}

/**
 * @tc.name: UiMaterialEmpty004
 * @tc.desc: Test CopyTo copies isEmpty_ field
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialEmpty004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create an empty material and copy it.
     * @tc.expected: step1. Copy has isEmpty_ == true.
     */
    auto original = AceType::MakeRefPtr<UiMaterial>();
    original->SetEmpty(true);
    original->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    auto copy = original->Copy();
    ASSERT_NE(copy, nullptr);
    EXPECT_TRUE(copy->IsEmpty());
    EXPECT_EQ(copy->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

// ============================================================================
// UiMaterial::GetConfiguredMaterialState / IsMaterialDisabled / IsMaterialEnabled（委托测试）
// ============================================================================

/**
 * @tc.name: UiMaterialStaticMethods001
 * @tc.desc: Test UiMaterial static methods delegate correctly to MaterialUtils
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialStaticMethods001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to "enable" and call UiMaterial static methods.
     * @tc.expected: step1. Delegation results match MaterialUtils results.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    EXPECT_EQ(UiMaterial::GetConfiguredMaterialState(), MaterialUtils::GetConfiguredMaterialState());
    EXPECT_EQ(UiMaterial::IsMaterialDisabled(), MaterialUtils::IsMaterialDisabled());
    EXPECT_EQ(UiMaterial::IsMaterialEnabled(), MaterialUtils::IsMaterialEnabled());
}

/**
 * @tc.name: UiMaterialStaticMethods002
 * @tc.desc: Test UiMaterial::IsMaterialDisabled delegates correctly for DISABLE state
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UiMaterialStaticMethods002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set state to "disable" and check UiMaterial::IsMaterialDisabled.
     * @tc.expected: step1. Returns true.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    EXPECT_TRUE(UiMaterial::IsMaterialDisabled());
    EXPECT_FALSE(UiMaterial::IsMaterialEnabled());
}

// ============================================================================
// ViewAbstract::SetSystemMaterial 与 disable 模式的集成测试
// ============================================================================

/**
 * @tc.name: SetSystemMaterialDisable001
 * @tc.desc: Test SetSystemMaterial does nothing when material is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSystemMaterialDisable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "disable".
     * @tc.steps: step2. Create a valid material and call SetSystemMaterial.
     * @tc.expected: step2. renderContext has no system material set (blocked by disable).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    auto node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(node), AceType::RawPtr(material));
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
}

/**
 * @tc.name: SetSystemMaterialDisable002
 * @tc.desc: Test SetSystemMaterial with nullptr when material is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSystemMaterialDisable002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "disable".
     * @tc.steps: step2. Call SetSystemMaterial with nullptr.
     * @tc.expected: step2. No crash, renderContext has no system material.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    auto node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(node), nullptr);
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
}

/**
 * @tc.name: SetSystemMaterialEnable001
 * @tc.desc: Test SetSystemMaterial works when material is enabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSystemMaterialEnable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable".
     * @tc.steps: step2. Create a valid material and call SetSystemMaterial.
     * @tc.expected: step2. renderContext has the system material set correctly.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(static_cast<int32_t>(MaterialType::IMMERSIVE));
    ImmersiveOptions options { .style = UiMaterialStyle::REGULAR };
    material->SetImmersiveOptions(options);
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(node), AceType::RawPtr(material));
    ASSERT_NE(renderContext->GetSystemMaterial(), nullptr);
    EXPECT_EQ(renderContext->GetSystemMaterial()->GetType(), static_cast<int32_t>(MaterialType::IMMERSIVE));
}

/**
 * @tc.name: SetSystemMaterialWithEmpty001
 * @tc.desc: Test SetSystemMaterial with empty material does not set renderContext
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSystemMaterialWithEmpty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable".
     * @tc.steps: step2. Create an empty material and call SetSystemMaterial.
     * @tc.expected: step2. renderContext has no system material (empty material filtered by PreProcessMaterial).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = UiMaterial::CreateEmpty();
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(node), AceType::RawPtr(material));
    // PreProcessMaterial returns nullptr for empty material
    // SetSystemMaterial stores nullptr copy
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
}

/**
 * @tc.name: SetSystemMaterialWithInvalidType001
 * @tc.desc: Test SetSystemMaterial with invalid material type
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSystemMaterialWithInvalidType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set UIMaterialState to "enable".
     * @tc.steps: step2. Create material with invalid type 99 and call SetSystemMaterial.
     * @tc.expected: step2. renderContext has no system material (invalid type filtered).
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    auto node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    auto renderContext = node->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto material = AceType::MakeRefPtr<UiMaterial>();
    material->SetType(99); // Invalid type
    ViewAbstract::SetSystemMaterial(AceType::RawPtr(node), AceType::RawPtr(material));
    EXPECT_EQ(renderContext->GetSystemMaterial(), nullptr);
}

// ============================================================================
// AceApplicationInfo 材质配置存取测试
// ============================================================================

/**
 * @tc.name: AceApplicationInfoMaterial001
 * @tc.desc: Test AceApplicationInfo material state getter/setter
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, AceApplicationInfoMaterial001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set and get UIMaterialState.
     * @tc.expected: step1. Getter returns the value set by setter.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialState("enable");
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetUIMaterialState(), "enable");
    AceApplicationInfo::GetInstance().SetUIMaterialState("disable");
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetUIMaterialState(), "disable");
    AceApplicationInfo::GetInstance().SetUIMaterialState("");
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetUIMaterialState(), "");
}

/**
 * @tc.name: AceApplicationInfoMaterial002
 * @tc.desc: Test AceApplicationInfo material type getter/setter
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, AceApplicationInfoMaterial002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set and get UIMaterialType.
     * @tc.expected: step1. Getter returns the value set by setter.
     */
    AceApplicationInfo::GetInstance().SetUIMaterialType("immersive");
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetUIMaterialType(), "immersive");
    AceApplicationInfo::GetInstance().SetUIMaterialType("");
    EXPECT_EQ(AceApplicationInfo::GetInstance().GetUIMaterialType(), "");
}

// ============================================================================
// MaterialState 枚举值测试
// ============================================================================

/**
 * @tc.name: MaterialStateEnum001
 * @tc.desc: Test MaterialState enum values match expected integers
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, MaterialStateEnum001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Verify MaterialState enum values.
     * @tc.expected: step1. DEFAULT=0, ENABLE=1, DISABLE=2.
     */
    EXPECT_EQ(static_cast<int32_t>(MaterialState::DEFAULT), 0);
    EXPECT_EQ(static_cast<int32_t>(MaterialState::ENABLE), 1);
    EXPECT_EQ(static_cast<int32_t>(MaterialState::DISABLE), 2);
}

/**
 * @tc.name: MaterialTypeEnum001
 * @tc.desc: Test MaterialType IMMERSIVE enum value is 2 (changed from 101)
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, MaterialTypeEnum001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Verify MaterialType IMMERSIVE value.
     * @tc.expected: step1. IMMERSIVE=2 (as per new design).
     */
    EXPECT_EQ(static_cast<int32_t>(MaterialType::IMMERSIVE), 2);
    EXPECT_EQ(static_cast<int32_t>(MaterialType::NONE), 0);
    EXPECT_EQ(static_cast<int32_t>(MaterialType::SEMI_TRANSPARENT), 1);
}

} // namespace OHOS::Ace::NG
