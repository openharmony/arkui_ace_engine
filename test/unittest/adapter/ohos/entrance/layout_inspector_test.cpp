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
#define protected public
#define private public
#include "core/common/layout_inspector.h"
#include <memory>
#include "pixel_map.h"
using namespace testing;
using namespace OHOS::Ace;
using namespace std;
using namespace testing::ext;

namespace Global::Resource {
class ResConfig;
}

namespace OHOS::Ace {
class LayoutInspectorTest : public testing::Test {
public:
};

/**
 * @tc.name: Filter3DSnapshot001
 * @tc.desc: Test cast to Filter3DSnapshot
 * @tc.type: FUNC
 */
HWTEST_F(LayoutInspectorTest, Filter3DSnapshot001, TestSize.Level1)
{
    std::vector<PixelMapPair> snapinfos;
    auto infos = LayoutInspector::Filter3DSnapshot(snapinfos);
    EXPECT_EQ(snapinfos.size(), 0);
    EXPECT_EQ(infos.size(), 0);

    snapinfos.emplace_back(1, nullptr);
    snapinfos.emplace_back(2, nullptr);
    snapinfos.emplace_back(3, std::make_shared<Media::PixelMap>());
    snapinfos.emplace_back(4, std::make_shared<Media::PixelMap>());
    snapinfos.emplace_back(5, nullptr);
    infos = LayoutInspector::Filter3DSnapshot(snapinfos);
    EXPECT_EQ(snapinfos.size(), 5);
    EXPECT_EQ(infos.size(), 2);
}

/**
 * @tc.name: ProcessMessagesTest
 * @tc.desc: Test cast to ProcessMessages
 * @tc.type: FUNC
 */
HWTEST_F(LayoutInspectorTest, ProcessMessagesTest, TestSize.Level1)
{
    // test1: empty msg
    std::string inspectorMsg = "";
    auto result = LayoutInspector::ProcessMessages(inspectorMsg);
    uint32_t windowId = result.first;
    int32_t methodNum = result.second;
    EXPECT_EQ(windowId, 0);
    EXPECT_EQ(methodNum, -1);
    
    // test2: invalid msg1, window id is corret, method is wrong
    inspectorMsg = "{\"method\":\"ArkUI.xxx\", \"params\":{\"windowId\":\"10\"}}";
    result = LayoutInspector::ProcessMessages(inspectorMsg);
    windowId = result.first;
    methodNum = result.second;
    EXPECT_EQ(windowId, 0);
    EXPECT_EQ(methodNum, -1);
    
    // test3: invalid msg2, window id is wrong, method is corret
    inspectorMsg = "{\"method\":\"ArkUI.tree\", \"params\":{\"windowId\":\"xxx\"}}";
    result = LayoutInspector::ProcessMessages(inspectorMsg);
    windowId = result.first;
    methodNum = result.second;
    EXPECT_EQ(windowId, 0);
    EXPECT_EQ(methodNum, 0);
    
    // test4: valid msg, window id is corret, method is ArkUI.tree
    inspectorMsg = "{\"method\":\"ArkUI.tree\", \"params\":{\"windowId\":\"11\"}}";
    result = LayoutInspector::ProcessMessages(inspectorMsg);
    windowId = result.first;
    methodNum = result.second;
    EXPECT_EQ(windowId, 11);
    EXPECT_EQ(methodNum, 0);
    
    // test5: valid msg, window id is corret, method is ArkUI.tree.3D
    inspectorMsg = "{\"method\":\"ArkUI.tree.3D\", \"params\":{\"windowId\":\"11\"}}";
    result = LayoutInspector::ProcessMessages(inspectorMsg);
    windowId = result.first;
    methodNum = result.second;
    EXPECT_EQ(windowId, 11);
    EXPECT_EQ(methodNum, 1);
    
    // test6: valid msg, window id is corret, method is ArkUI.queryAbilities
    inspectorMsg = "{\"method\":\"ArkUI.queryAbilities\", \"params\":{\"windowId\":\"11\"}}";
    result = LayoutInspector::ProcessMessages(inspectorMsg);
    windowId = result.first;
    methodNum = result.second;
    EXPECT_EQ(windowId, 11);
    EXPECT_EQ(methodNum, 2);
}

/**
 * @tc.name: EnableNodeTrace
 * @tc.desc: Test cast to EnableNodeTrace
 * @tc.type: FUNC
 */
HWTEST_F(LayoutInspectorTest, EnableNodeTrace, TestSize.Level1)
{
    // test1: enable node trace true
    LayoutInspector::SetEnableNodeTrace(true);
    auto res = LayoutInspector::GetEnableNodeTrace();
    EXPECT_EQ(res, true);

    // test1: enable node trace false
    LayoutInspector::SetEnableNodeTrace(false);
    res = LayoutInspector::GetEnableNodeTrace();
    EXPECT_EQ(res, false);
}
} // namespace OHOS::Ace::NG