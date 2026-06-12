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

#include "gtest/gtest.h"

#include "core/interfaces/arkoala/arkoala_api.h"
#include "interfaces/native/native_type.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
constexpr int32_t SINGLE_ELEMENT_SIZE = 1;
constexpr int32_t ARRAY_SIZE = 3;
}

class CapiTextPickerOptionTest : public testing::Test {
public:
    static void SetUpTestCase() {}
    static void TearDownTestCase() {}
};

/**
 * @tc.name: TextPickerRangeContentArrayCreateTestInvalidLength
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Create with invalid length
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayCreateTestInvalidLength, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_TextPickerRangeContentArray_Create(0), nullptr);
    EXPECT_EQ(OH_ArkUI_TextPickerRangeContentArray_Create(-1), nullptr);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestNullHandle
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy with null handle
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestNullHandle, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->rangeContentArraySize, SINGLE_ELEMENT_SIZE);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(nullptr);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestNullRangeContent
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy when rangeContent is null
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestNullRangeContent, TestSize.Level1)
{
    auto* handle = new ArkUI_TextPickerRangeContentArray;
    ASSERT_NE(handle, nullptr);
    handle->rangeContent = nullptr;
    handle->rangeContentArraySize = ARRAY_SIZE;
    EXPECT_EQ(handle->rangeContent, nullptr);
    EXPECT_EQ(handle->rangeContentArraySize, ARRAY_SIZE);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestEmptyContent
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy when icon and text are null
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestEmptyContent, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->rangeContent[0].icon, nullptr);
    EXPECT_EQ(handle->rangeContent[0].text, nullptr);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestIconOnly
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy when only icon is set
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestIconOnly, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);

    char icon[] = "icon";
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon, 0);

    EXPECT_STREQ(handle->rangeContent[0].icon, icon);
    EXPECT_EQ(handle->rangeContent[0].text, nullptr);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestTextOnly
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy when only text is set
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestTextOnly, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);

    char text[] = "text";
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, text, 0);

    EXPECT_EQ(handle->rangeContent[0].icon, nullptr);
    EXPECT_STREQ(handle->rangeContent[0].text, text);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextPickerRangeContentArrayDestroyTestMultiElement
 * @tc.desc: Test OH_ArkUI_TextPickerRangeContentArray_Destroy frees all elements
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArrayDestroyTestMultiElement, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(ARRAY_SIZE);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->rangeContentArraySize, ARRAY_SIZE);

    char icon0[] = "icon0";
    char icon1[] = "icon1";
    char icon2[] = "icon2";
    char text0[] = "text0";
    char text1[] = "text1";
    char text2[] = "text2";

    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon0, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon1, 1);
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon2, 2);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, text0, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, text1, 1);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, text2, 2);

    EXPECT_STREQ(handle->rangeContent[0].icon, icon0);
    EXPECT_STREQ(handle->rangeContent[1].icon, icon1);
    EXPECT_STREQ(handle->rangeContent[2].icon, icon2);
    EXPECT_STREQ(handle->rangeContent[0].text, text0);
    EXPECT_STREQ(handle->rangeContent[1].text, text1);
    EXPECT_STREQ(handle->rangeContent[2].text, text2);

    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextPickerRangeContentArraySetTestInvalidParams
 * @tc.desc: Test SetIconAtIndex and SetTextAtIndex with invalid parameters
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextPickerRangeContentArraySetTestInvalidParams, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextPickerRangeContentArray_Create(ARRAY_SIZE);
    ASSERT_NE(handle, nullptr);

    char icon[] = "icon";
    char text[] = "text";

    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(nullptr, icon, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(nullptr, text, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, nullptr, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, nullptr, 0);
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon, -1);
    OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(handle, text, ARRAY_SIZE);
    OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(handle, icon, ARRAY_SIZE);

    EXPECT_EQ(handle->rangeContent[0].icon, nullptr);
    EXPECT_EQ(handle->rangeContent[0].text, nullptr);

    OH_ArkUI_TextPickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestNullHandle
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy with null handle
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestNullHandle, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle->rangeContentArraySize, SINGLE_ELEMENT_SIZE);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(handle);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(nullptr);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestEmptyElement
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy when text and children are null
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestEmptyElement, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(handle[0].text, nullptr);
    EXPECT_EQ(handle[0].children, nullptr);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestTextOnly
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy when only text is set
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestTextOnly, TestSize.Level1)
{
    auto* handle = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(handle, nullptr);

    char text[] = "text";
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(handle, text, 0);

    EXPECT_STREQ(handle[0].text, text);
    EXPECT_EQ(handle[0].children, nullptr);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(handle);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestChildrenOnly
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy when only children is set
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestChildrenOnly, TestSize.Level1)
{
    auto* parent = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    auto* child = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);

    char childText[] = "child";
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child, childText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child, 0);

    EXPECT_EQ(parent[0].text, nullptr);
    EXPECT_NE(parent[0].children, nullptr);
    EXPECT_STREQ(parent[0].children[0].text, childText);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(parent);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestWithChildren
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy with nested children
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestWithChildren, TestSize.Level1)
{
    auto* parent = OH_ArkUI_TextCascadePickerRangeContentArray_Create(ARRAY_SIZE);
    ASSERT_NE(parent, nullptr);

    auto* child = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(child, nullptr);

    char text[] = "parent";
    char childText[] = "child";
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, text, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child, childText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child, 0);

    EXPECT_STREQ(parent[0].text, text);
    EXPECT_STREQ(parent[0].children[0].text, childText);

    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(parent);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestMultiElement
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy frees all elements
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestMultiElement, TestSize.Level1)
{
    auto* parent = OH_ArkUI_TextCascadePickerRangeContentArray_Create(ARRAY_SIZE);
    ASSERT_NE(parent, nullptr);

    auto* child0 = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    auto* child1 = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    auto* child2 = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(child0, nullptr);
    ASSERT_NE(child1, nullptr);
    ASSERT_NE(child2, nullptr);

    char text0[] = "text0";
    char text1[] = "text1";
    char text2[] = "text2";
    char childText0[] = "child0";
    char childText1[] = "child1";
    char childText2[] = "child2";

    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, text0, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, text1, 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, text2, 2);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child0, childText0, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child1, childText1, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child2, childText2, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child0, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child1, 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child2, 2);

    EXPECT_STREQ(parent[0].text, text0);
    EXPECT_STREQ(parent[1].text, text1);
    EXPECT_STREQ(parent[2].text, text2);
    EXPECT_STREQ(parent[0].children[0].text, childText0);
    EXPECT_STREQ(parent[1].children[0].text, childText1);
    EXPECT_STREQ(parent[2].children[0].text, childText2);

    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(parent);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestDeepNested
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy with multi-level children
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestDeepNested, TestSize.Level1)
{
    auto* root = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    auto* child = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    auto* grandchild = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(root, nullptr);
    ASSERT_NE(child, nullptr);
    ASSERT_NE(grandchild, nullptr);

    char rootText[] = "root";
    char childText[] = "child";
    char grandchildText[] = "grandchild";
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(root, rootText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child, childText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(grandchild, grandchildText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(child, grandchild, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(root, child, 0);

    EXPECT_STREQ(root[0].text, rootText);
    EXPECT_STREQ(root[0].children[0].text, childText);
    EXPECT_STREQ(root[0].children[0].children[0].text, grandchildText);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(root);
}

/**
 * @tc.name: TextCascadePickerRangeContentArrayDestroyTestMixedElements
 * @tc.desc: Test OH_ArkUI_TextCascadePickerRangeContentArray_Destroy with mixed text and children
 * @tc.type: FUNC
 */
HWTEST_F(CapiTextPickerOptionTest, TextCascadePickerRangeContentArrayDestroyTestMixedElements, TestSize.Level1)
{
    auto* parent = OH_ArkUI_TextCascadePickerRangeContentArray_Create(ARRAY_SIZE);
    auto* child = OH_ArkUI_TextCascadePickerRangeContentArray_Create(SINGLE_ELEMENT_SIZE);
    ASSERT_NE(parent, nullptr);
    ASSERT_NE(child, nullptr);

    char textOnly[] = "textOnly";
    char textWithChild[] = "textWithChild";
    char childText[] = "child";
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, textOnly, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(parent, textWithChild, 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(child, childText, 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(parent, child, 1);

    EXPECT_STREQ(parent[0].text, textOnly);
    EXPECT_EQ(parent[0].children, nullptr);
    EXPECT_STREQ(parent[1].text, textWithChild);
    EXPECT_STREQ(parent[1].children[0].text, childText);
    EXPECT_EQ(parent[2].text, nullptr);
    EXPECT_EQ(parent[2].children, nullptr);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(parent);
}
} // namespace OHOS::Ace
