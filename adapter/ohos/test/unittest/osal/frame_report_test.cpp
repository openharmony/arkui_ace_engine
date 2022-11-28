/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "adapter/ohos/test/unittest/mock/common.h"
#define private public
#define protected public
#include "base/log/frame_report.h"
#undef private
#undef protected

using namespace testing::ext;

namespace OHOS::Ace {
class FrameReportTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void FrameReportTest::SetUpTestCase() {}

void FrameReportTest::TearDownTestCase() {}

void FrameReportTest::SetUp() {}

void FrameReportTest::TearDown() {}

/**
 * @tc.name: FrameReportTest_LoadLibrary_001
 * @tc.desc: Verifying the loading library succeeded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_LoadLibrary_001, TestSize.Level1)
{
    auto result = FrameReport::GetInstance().LoadLibrary();
    EXPECT_TRUE(result);
    EXPECT_TRUE(FrameReport::GetInstance().frameSchedSoLoaded_);
    EXPECT_TRUE(FrameReport::GetInstance().frameSchedHandle_);
}

/**
 * @tc.name: FrameReportTest_CloseLibrary_001
 * @tc.desc: Verify that in the scenario of opening so, closing so is successful
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_CloseLibrary_001, TestSize.Level1)
{
    FrameReport::GetInstance().LoadLibrary();
    FrameReport::GetInstance().CloseLibrary();
    EXPECT_TRUE(!(FrameReport::GetInstance().frameSchedHandle_));
    EXPECT_FALSE(FrameReport::GetInstance().frameSchedSoLoaded_);
}

/**
 * @tc.name: FrameReportTest_CloseLibrary_002
 * @tc.desc: Verify that in the scenario where so is not opened, so is closed successfully
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_CloseLibrary_002, TestSize.Level2)
{
    FrameReport::GetInstance().CloseLibrary();
    EXPECT_TRUE(!(FrameReport::GetInstance().frameSchedHandle_));
    EXPECT_FALSE(FrameReport::GetInstance().frameSchedSoLoaded_);
}

/**
 * @tc.name: FrameReportTest_LoadSymbol_001
 * @tc.desc: Verify that the address information of the functions in the library is obtained when so is opened
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_LoadSymbol_001, TestSize.Level1)
{
    FrameReport::GetInstance().LoadLibrary();
    EXPECT_TRUE(FrameReport::GetInstance().frameSchedHandle_);
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("Init"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("GetSenseSchedEnable"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginFlushAnimation"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndFlushAnimation"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginFlushBuild"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndFlushBuild"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginFlushLayout"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndFlushLayout"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginFlushRender"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndFlushRender"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginFlushRenderFinish"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndFlushRenderFinish"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginProcessPostFlush"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("BeginListFling"));
    EXPECT_TRUE(FrameReport::GetInstance().LoadSymbol("EndListFling"));
    FrameReport::GetInstance().CloseLibrary();
}

/**
 * @tc.name: FrameReportTest_LoadSymbol_002
 * @tc.desc: Verify that the address information of non-existent functions in the library is obtained
 *           when so is opened
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_LoadSymbol_002, TestSize.Level2)
{
    FrameReport::GetInstance().LoadLibrary();
    EXPECT_TRUE(FrameReport::GetInstance().frameSchedHandle_);
    EXPECT_TRUE(!(FrameReport::GetInstance().LoadSymbol("NotExistFunc")));
    FrameReport::GetInstance().CloseLibrary();
}

/**
 * @tc.name: FrameReportTest_LoadSymbol_003
 * @tc.desc: Verify that the address information of the functions in the library is obtained
 *           when so is not opened
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_LoadSymbol_003, TestSize.Level2)
{
    EXPECT_FALSE(FrameReport::GetInstance().LoadSymbol("Init"));
}

/**
 * @tc.name: FrameReportTest_Init_001
 * @tc.desc: Verify that the initialization function is called to load the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_Init_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    EXPECT_TRUE(FrameReport::GetInstance().frameSchedHandle_);
}

/**
 * @tc.name: FrameReportTest_GetEnable_001
 * @tc.desc: Verify GetEnable function
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_GetEnable_001, TestSize.Level1)
{
    EXPECT_TRUE(static_cast<bool>(FrameReport::GetInstance().GetEnable()));
}

/**
 * @tc.name: FrameReportTest_GetFrameReportEnable_001
 * @tc.desc: Verify that the GetFrameReportEnable function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_GetFrameReportEnable_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().GetFrameReportEnable();
    EXPECT_TRUE(FrameReport::GetInstance().frameGetEnableFunc_);
    FrameReport::GetInstance().frameGetEnableFunc_ = nullptr;
    FrameReport::GetInstance().CloseLibrary();
}

/**
 * @tc.name: FrameReportTest_GetFrameReportEnable_002
 * @tc.desc: Verify that the GetFrameReportEnable function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_GetFrameReportEnable_002, TestSize.Level2)
{
    FrameReport::GetInstance().GetFrameReportEnable();
    EXPECT_FALSE(FrameReport::GetInstance().frameGetEnableFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginFlushAnimation_001
 * @tc.desc: Verify that the BeginFlushAnimation function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushAnimation_001, TestSize.Level2)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginFlushAnimation();
    EXPECT_TRUE(FrameReport::GetInstance().beginFlushAnimationFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginFlushAnimationFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginFlushAnimation_002
 * @tc.desc: Verify that the BeginFlushAnimation function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushAnimation_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginFlushAnimation();
    EXPECT_FALSE(FrameReport::GetInstance().beginFlushAnimationFunc_);
}

/**
 * @tc.name: FrameReportTest_EndFlushAnimation_001
 * @tc.desc: Verify that the EndFlushAnimation function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushAnimation_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndFlushAnimation();
    EXPECT_TRUE(FrameReport::GetInstance().endFlushAnimationFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endFlushAnimationFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndFlushAnimation_002
 * @tc.desc: Verify that the EndFlushAnimation function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushAnimation_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndFlushAnimation();
    EXPECT_FALSE(FrameReport::GetInstance().endFlushAnimationFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginFlushBuild_001
 * @tc.desc: Verify that the BeginFlushBuild function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushBuild_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginFlushBuild();
    EXPECT_TRUE(FrameReport::GetInstance().beginFlushBuildFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginFlushBuildFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginFlushBuild_002
 * @tc.desc: Verify that the BeginFlushBuild function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushBuild_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginFlushBuild();
    EXPECT_FALSE(FrameReport::GetInstance().beginFlushBuildFunc_);
}

/**
 * @tc.name: FrameReportTest_EndFlushBuild_001
 * @tc.desc: Verify that the EndFlushBuild function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushBuild_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndFlushBuild();
    EXPECT_TRUE(FrameReport::GetInstance().endFlushBuildFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endFlushBuildFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndFlushBuild_002
 * @tc.desc: Verify that the EndFlushBuild function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushBuild_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndFlushBuild();
    EXPECT_FALSE(FrameReport::GetInstance().endFlushBuildFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginFlushLayout_001
 * @tc.desc: Verify that the BeginFlushLayout function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushLayout_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginFlushLayout();
    EXPECT_TRUE(FrameReport::GetInstance().beginFlushLayoutFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginFlushLayoutFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginFlushLayout_002
 * @tc.desc: Verify that the BeginFlushLayout function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushLayout_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginFlushLayout();
    EXPECT_FALSE(FrameReport::GetInstance().beginFlushLayoutFunc_);
}

/**
 * @tc.name: FrameReportTest_EndFlushLayout_001
 * @tc.desc: Verify that the EndFlushLayout function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushLayout_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndFlushLayout();
    EXPECT_TRUE(FrameReport::GetInstance().endFlushLayoutFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endFlushLayoutFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndFlushLayout_002
 * @tc.desc: Verify that the EndFlushLayout function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushLayout_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndFlushLayout();
    EXPECT_FALSE(FrameReport::GetInstance().endFlushLayoutFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginFlushRender_001
 * @tc.desc: Verify that the BeginFlushRender function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushRender_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginFlushRender();
    EXPECT_TRUE(FrameReport::GetInstance().beginFlushRenderFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginFlushRenderFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginFlushRender_002
 * @tc.desc: Verify that the BeginFlushRender function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushRender_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginFlushRender();
    EXPECT_FALSE(FrameReport::GetInstance().beginFlushRenderFunc_);
}

/**
 * @tc.name: FrameReportTest_EndFlushRender_001
 * @tc.desc: Verify that the EndFlushRender function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushRender_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndFlushRender();
    EXPECT_TRUE(FrameReport::GetInstance().endFlushRenderFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endFlushRenderFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndFlushRender_002
 * @tc.desc: Verify that the EndFlushRender function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushRender_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndFlushRender();
    EXPECT_FALSE(FrameReport::GetInstance().endFlushRenderFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginFlushRenderFinish_001
 * @tc.desc: Verify that the BeginFlushRenderFinish function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushRenderFinish_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginFlushRenderFinish();
    EXPECT_TRUE(FrameReport::GetInstance().beginFlushRenderFinishFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginFlushRenderFinishFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginFlushRenderFinish_002
 * @tc.desc: Verify that the BeginFlushRenderFinish function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginFlushRenderFinish_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginFlushRenderFinish();
    EXPECT_FALSE(FrameReport::GetInstance().beginFlushRenderFinishFunc_);
}

/**
 * @tc.name: FrameReportTest_EndFlushRenderFinish_001
 * @tc.desc: Verify that the EndFlushRenderFinish function is called when the so library is loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushRenderFinish_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndFlushRenderFinish();
    EXPECT_TRUE(FrameReport::GetInstance().endFlushRenderFinishFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endFlushRenderFinishFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndFlushRenderFinish_002
 * @tc.desc: Verify that the EndFlushRenderFinish function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndFlushRenderFinish_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndFlushRenderFinish();
    EXPECT_FALSE(FrameReport::GetInstance().endFlushRenderFinishFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginProcessPostFlush_001
 * @tc.desc: Verify that the BeginProcessPostFlush function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginProcessPostFlush_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginProcessPostFlush();
    EXPECT_TRUE(FrameReport::GetInstance().beginProcessPostFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginProcessPostFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginProcessPostFlush_002
 * @tc.desc: Verify that the BeginProcessPostFlush function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginProcessPostFlush_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginProcessPostFlush();
    EXPECT_FALSE(FrameReport::GetInstance().beginProcessPostFunc_);
}

/**
 * @tc.name: FrameReportTest_BeginListFling_001
 * @tc.desc: Verify that the BeginListFling function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginListFling_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().BeginListFling();
    EXPECT_TRUE(FrameReport::GetInstance().beginListFlingFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().beginListFlingFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_BeginListFling_002
 * @tc.desc: Verify that the BeginListFling function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_BeginListFling_002, TestSize.Level2)
{
    FrameReport::GetInstance().BeginListFling();
    EXPECT_FALSE(FrameReport::GetInstance().endListFlingFunc_);
}

/**
 * @tc.name: FrameReportTest_EndListFling_001
 * @tc.desc: Verify that the EndListFling function is called in the scenario of loading the so library
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndListFling_001, TestSize.Level1)
{
    FrameReport::GetInstance().Init();
    FrameReport::GetInstance().EndListFling();
    EXPECT_TRUE(FrameReport::GetInstance().endListFlingFunc_);
    FrameReport::GetInstance().CloseLibrary();
    FrameReport::GetInstance().endListFlingFunc_ = nullptr;
}

/**
 * @tc.name: FrameReportTest_EndListFling_002
 * @tc.desc: Verify that the EndListFling function is called when the so library is not loaded
 * @tc.type: FUNC
 */
HWTEST_F(FrameReportTest, FrameReportTest_EndListFling_002, TestSize.Level2)
{
    FrameReport::GetInstance().EndListFling();
    EXPECT_FALSE(FrameReport::GetInstance().endListFlingFunc_);
}
} // namespace OHOS::Ace