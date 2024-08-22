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

#include "animate_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "dialog_model.h"
#include "error_code.h"
#include "event_converter.h"
#include "gtest/gtest.h"
#include "native_animate.h"
#include "native_interface.h"
#include "native_node.h"
#include "node_extened.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::DialogModel;

class DialogModelTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

bool OnWillDismissEvent(int32_t reason)
{
    return true;
}

/**
 * @tc.name: DialogModelTest001
 * @tc.desc: Test Create function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest001, TestSize.Level1)
{
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_EQ(nativeDialogHandle, nullptr);

    Dispose(nativeDialogHandle);
}

/**
 * @tc.name: DialogModelTest002
 * @tc.desc: Test Create function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest002, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);

    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest003
 * @tc.desc: Test SetContent function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest003, TestSize.Level1)
{
    int32_t ret = SetContent(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest004
 * @tc.desc: Test SetContent function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest004, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    ArkUI_NodeHandle nodeHandle = new ArkUI_Node();
    int32_t ret = SetContent(nativeDialogHandle, nodeHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
    delete nodeHandle;
}

/**
 * @tc.name: DialogModelTest005
 * @tc.desc: Test RemoveContent function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest005, TestSize.Level1)
{
    int32_t ret = RemoveContent(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest006
 * @tc.desc: Test RemoveContent function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest006, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = RemoveContent(nativeDialogHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest007
 * @tc.desc: Test SetContentAlignment function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest007, TestSize.Level1)
{
    int32_t ret = SetContentAlignment(nullptr, 0, 0.0f, 0.0f);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest008
 * @tc.desc: Test SetContentAlignment function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest008, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetContentAlignment(nativeDialogHandle, 0, 0.0f, 0.0f);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest009
 * @tc.desc: Test ResetContentAlignment function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest009, TestSize.Level1)
{
    int32_t ret = ResetContentAlignment(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest010
 * @tc.desc: Test SetContentAlignment function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest010, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = ResetContentAlignment(nativeDialogHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest011
 * @tc.desc: Test SetModalMode function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest011, TestSize.Level1)
{
    int32_t ret = SetModalMode(nullptr, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest012
 * @tc.desc: Test SetModalMode function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest012, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetModalMode(nativeDialogHandle, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest013
 * @tc.desc: Test SetAutoCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest013, TestSize.Level1)
{
    int32_t ret = SetAutoCancel(nullptr, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest014
 * @tc.desc: Test SetAutoCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest014, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetAutoCancel(nativeDialogHandle, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest015
 * @tc.desc: Test SetMask function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest015, TestSize.Level1)
{
    int32_t ret = SetMask(nullptr, 0, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest016
 * @tc.desc: Test SetMask function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest016, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    ArkUI_Rect rect = {0.0f, 0.0f, 0.0f, 0.0f};
    int32_t ret = SetMask(nativeDialogHandle, 0, &rect);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest017
 * @tc.desc: Test SetMask function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest017, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetMask(nativeDialogHandle, 0, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest018
 * @tc.desc: Test SetBackgroundColor function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest018, TestSize.Level1)
{
    int32_t ret = SetBackgroundColor(nullptr, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest019
 * @tc.desc: Test SetBackgroundColor function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest019, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetBackgroundColor(nativeDialogHandle, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest020
 * @tc.desc: Test SetCornerRadius function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest020, TestSize.Level1)
{
    int32_t ret = SetCornerRadius(nullptr, 0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest021
 * @tc.desc: Test SetCornerRadius function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest021, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetCornerRadius(nativeDialogHandle, 0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest022
 * @tc.desc: Test SetGridColumnCount function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest022, TestSize.Level1)
{
    int32_t ret = SetGridColumnCount(nullptr, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest023
 * @tc.desc: Test SetGridColumnCount function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest023, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = SetGridColumnCount(nativeDialogHandle, 0);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest024
 * @tc.desc: Test EnableCustomStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest024, TestSize.Level1)
{
    int32_t ret = EnableCustomStyle(nullptr, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest025
 * @tc.desc: Test EnableCustomStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest025, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = EnableCustomStyle(nativeDialogHandle, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest026
 * @tc.desc: Test EnableCustomAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest026, TestSize.Level1)
{
    int32_t ret = EnableCustomAnimation(nullptr, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest027
 * @tc.desc: Test EnableCustomAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest027, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = EnableCustomAnimation(nativeDialogHandle, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest028
 * @tc.desc: Test Show function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest028, TestSize.Level1)
{
    int32_t ret = Show(nullptr, true);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest029
 * @tc.desc: Test Show function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest029, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = Show(nativeDialogHandle, false);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest030
 * @tc.desc: Test Close function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest030, TestSize.Level1)
{
    int32_t ret = Close(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest031
 * @tc.desc: Test Close function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest031, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    int32_t ret = Close(nativeDialogHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest032
 * @tc.desc: Test RegisterOnWillDismiss function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest032, TestSize.Level1)
{
    int32_t ret = RegisterOnWillDismiss(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: DialogModelTest033
 * @tc.desc: Test RegisterOnWillDismiss function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest033, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    ArkUI_OnWillDismissEvent eventHandler = OnWillDismissEvent;
    int32_t ret = RegisterOnWillDismiss(nativeDialogHandle, eventHandler);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest034
 * @tc.desc: Test RegisterOnWillDismissWithUserData function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest034, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_NativeDialogHandle nativeDialogHandle = Create();
    ASSERT_NE(nativeDialogHandle, nullptr);
    ArkUI_DialogDismissEvent nEvent;
    int32_t ret =
        RegisterOnWillDismissWithUserData(nativeDialogHandle, nEvent.userData, [](ArkUI_DialogDismissEvent* event) {});
    ASSERT_EQ(ret, 0);
    ret = RegisterOnWillDismissWithUserData(nullptr, nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    Dispose(nativeDialogHandle);
    nativeDialogHandle = nullptr;
}

/**
 * @tc.name: DialogModelTest035
 * @tc.desc: Test ArkUI_DialogDismissEvent_SetShouldBlockDismiss function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest035, TestSize.Level1)
{
    ArkUI_DialogDismissEvent* nEvent = new ArkUI_DialogDismissEvent({ nullptr, 0, false });
    OH_ArkUI_DialogDismissEvent_SetShouldBlockDismiss(nEvent, true);
    ASSERT_TRUE(nEvent->BlockDismiss);
    nEvent = nullptr;
    OH_ArkUI_DialogDismissEvent_SetShouldBlockDismiss(nEvent, true);
    ASSERT_TRUE(nEvent == nullptr);
}

/**
 * @tc.name: DialogModelTest036
 * @tc.desc: Test ArkUI_DialogDismissEvent_GetUserData function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest036, TestSize.Level1)
{
    struct ArkUICustomData {
        float id;
        int index;
    };
    auto customData = new ArkUICustomData { 12, 1 };
    ArkUI_DialogDismissEvent* nEvent = new ArkUI_DialogDismissEvent({ nullptr, 0, false });
    nEvent->userData = customData;
    void* ret = OH_ArkUI_DialogDismissEvent_GetUserData(nEvent);
    ASSERT_EQ(ret, nEvent->userData);
    nEvent = nullptr;
    ret = OH_ArkUI_DialogDismissEvent_GetUserData(nEvent);
    ASSERT_TRUE(ret == nullptr);
}

/**
 * @tc.name: DialogModelTest037
 * @tc.desc: Test ArkUI_DialogDismissEvent_GetUserData function.
 * @tc.type: FUNC
 */
HWTEST_F(DialogModelTest, DialogModelTest037, TestSize.Level1)
{
    ArkUI_DialogDismissEvent* nEvent = new ArkUI_DialogDismissEvent({ nullptr, 0, false });
    int32_t ret = OH_ArkUI_DialogDismissEvent_GetDismissReason(nEvent);
    ASSERT_EQ(ret, nEvent->reason);
    nEvent = nullptr;
    ret = OH_ArkUI_DialogDismissEvent_GetDismissReason(nEvent);
    ASSERT_EQ(ret, -1);
}