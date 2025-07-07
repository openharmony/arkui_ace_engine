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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "form_constants.h"
#include "form_info.h"
#include "core/components_ng/pattern/form/form_special_style.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class FormSpecialStyleTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
};

void FormSpecialStyleTest::SetUpTestSuite()
{}

void FormSpecialStyleTest::TearDownTestSuite()
{}

void FormSpecialStyleTest::SetUp()
{}

/**
 * @tc.name: FormSpecialStyleTest001
 * @tc.desc: create form node
 * @tc.type: FUNC
 */
HWTEST_F(FormSpecialStyleTest, FormSpecialStyleTest001, TestSize.Level1)
{
    FormSpecialStyle style;
    style.SetIsForbiddenByParentControl(true);
    ASSERT_EQ(style.IsForbidden(), true);
    ASSERT_EQ(style.GetFormStyleAttribution(), FormStyleAttribution::PARENT_CONTROL);

    AppExecFwk::FormInfo formInfo;
    formInfo.customizeDatas.emplace_back<AppExecFwk::FormCustomizeData>({
        .name = OHOS::AppExecFwk::Constants::IS_MULTI_APP_FORM,
        .value = OHOS::AppExecFwk::Constants::IS_MULTI_APP_FORM_TRUE
    });
    style.SetIsMultiAppForm(formInfo);
    ASSERT_EQ(style.IsForbidden(), true);
    ASSERT_EQ(style.GetFormStyleAttribution(), FormStyleAttribution::NORMAL);
}
} // namespace OHOS::Ace::NG
