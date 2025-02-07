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

#include <memory>
#include <utility>

#include "foundation/graphic/graphic_utils_lite/interfaces/kits/gfx_utils/graphic_types.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_input_base.h"

#include "base/memory/ace_type.h"
#include "core/common/ime/text_input_type.h"
#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_select_overlay.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class TextFieldManagerTestNG : public TextInputBases {
public:
};

class MockTextBase : public TextFieldPattern {
public:
    MockTextBase() = default;
    ~MockTextBase() override = default;

    MOCK_METHOD1(BetweenSelectedPosition, bool(const Offset& globalOffset));
};

class MockBaseTextSelectOverlay : public BaseTextSelectOverlay {
public:
    explicit MockBaseTextSelectOverlay(const WeakPtr<TextBase>& textBase) : BaseTextSelectOverlay(textBase) {}
    ~MockBaseTextSelectOverlay() = default;

    MOCK_METHOD1(CheckHandleVisible, bool(const RectF& paintRect));
};

class MockUINode : public UINode {
public:
    MockUINode(const std::string& tag, int32_t nodeId, bool isRoot = false) : UINode(tag, nodeId) {}
    ~MockUINode() {};

    MOCK_CONST_METHOD0(IsAtomicNode, bool());
};

class MySelectContentOverlayManager : public SelectContentOverlayManager {
public:
    explicit MySelectContentOverlayManager(const RefPtr<FrameNode>& rootNode) : SelectContentOverlayManager(rootNode) {}
    ~MySelectContentOverlayManager() override = default;
};

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo001
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo001, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 0;
    int32_t nodeId = 0;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto map = text_field_manager.textFieldInfoMap_;
    EXPECT_EQ(map.find(autoFillContainerNodeId), map.end());
}

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo002
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo002, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 1;
    int32_t nodeId = 0;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto map = text_field_manager.textFieldInfoMap_;
    auto innerMap = map.find(autoFillContainerNodeId)->second;
    EXPECT_NE(map.find(autoFillContainerNodeId), map.end());
    EXPECT_EQ(innerMap.find(nodeId), innerMap.end());
}

/**
 * @tc.name: TextFieldManagerNG_RemoveTextFieldInfo003
 * @tc.desc: test RemoveTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveTextFieldInfo003, TestSize.Level1)
{
    TextFieldInfo info;
    TextFieldManagerNG text_field_manager;
    int32_t key = 1;
    int32_t autoFillContainerNodeId = 1;
    int32_t nodeId = 1;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { key, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(key, unmap));
    auto beforeMap = text_field_manager.textFieldInfoMap_;
    auto beforeInnerMap = beforeMap.find(autoFillContainerNodeId)->second;
    EXPECT_NE(beforeInnerMap.find(nodeId), beforeInnerMap.end());
    text_field_manager.RemoveTextFieldInfo(autoFillContainerNodeId, nodeId);
    auto afterMap = text_field_manager.textFieldInfoMap_;
    auto afterInnerMap = afterMap.find(autoFillContainerNodeId)->second;
    EXPECT_EQ(afterInnerMap.find(nodeId), afterInnerMap.end());
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo001
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo001, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = -1;
    info.autoFillContainerNodeId = -1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = -1;
    info_insert.autoFillContainerNodeId = -1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info_insert);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    auto inputType = innerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_NE(inputType, TextInputType::DATETIME);
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo002
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo002, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = -1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    EXPECT_NE(innerMap.end(), innerMap.find(info.nodeId));
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo003
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo003, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = 1;
    info_insert.autoFillContainerNodeId = 1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    text_field_manager.UpdateTextFieldInfo(info_insert);
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto innerMap = map->second;
    auto inputType = innerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_EQ(inputType, TextInputType::DATETIME);
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo004
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo004, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> textMap;
    textMap.emplace(info.nodeId, info);
    std::unordered_map<int32_t, std::unordered_map<int32_t, TextFieldInfo>> textFieldInfoMap_;
    textFieldInfoMap_.emplace(info.autoFillContainerNodeId + 1, textMap);
    text_field_manager.textFieldInfoMap_ = textFieldInfoMap_;
    EXPECT_EQ(text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId),
        text_field_manager.textFieldInfoMap_.end());
    text_field_manager.UpdateTextFieldInfo(info);
    EXPECT_NE(text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId),
        text_field_manager.textFieldInfoMap_.end());
}

/**
 * @tc.name: TextFieldManagerNG_UpdateTextFieldInfo005
 * @tc.desc: test UpdateTextFieldInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdateTextFieldInfo005, TestSize.Level1)
{
    TextFieldInfo info;
    info.nodeId = 2;
    info.autoFillContainerNodeId = 1;
    info.inputType = TextInputType::BEGIN;
    info.contentType = TextContentType::BEGIN;
    info.enableAutoFill = true;
    TextFieldInfo info_insert;
    info_insert.nodeId = 1;
    info_insert.autoFillContainerNodeId = 1;
    info_insert.inputType = TextInputType::DATETIME;
    info_insert.contentType = TextContentType::BEGIN;
    info_insert.enableAutoFill = true;
    TextFieldManagerNG text_field_manager;
    std::unordered_map<int32_t, TextFieldInfo> unmap = { { info.nodeId, info } };
    text_field_manager.textFieldInfoMap_.insert(std::make_pair(info.autoFillContainerNodeId, unmap));
    auto map = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    EXPECT_NE(map, text_field_manager.textFieldInfoMap_.end());
    auto innerMap = map->second;
    EXPECT_NE(innerMap.find(info.nodeId), innerMap.end());
    text_field_manager.UpdateTextFieldInfo(info_insert);
    EXPECT_EQ(text_field_manager.textFieldInfoMap_.find(info.nodeId), text_field_manager.textFieldInfoMap_.end());
    auto afterMap = text_field_manager.textFieldInfoMap_.find(info.autoFillContainerNodeId);
    auto afterInnerMap = afterMap->second;
    auto inputType = afterInnerMap.find(info_insert.nodeId)->second.inputType;
    EXPECT_NE(afterInnerMap.find(info.nodeId), afterInnerMap.end());
    EXPECT_EQ(inputType, TextInputType::DATETIME);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition001
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition001, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(10.0f, 10.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = false;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, false);
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition002
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition002, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(10.0f, 10.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = true;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, true);
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition003
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition003, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(10.0f, 10.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = false;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, true);
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition004
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition004, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(10.0f, 10.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = true;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, false);
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition005
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition005, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(100.0f, 100.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = false;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, false);
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition006
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition006, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(100.0f, 100.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = true;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, true);
    EXPECT_EQ(index, 5);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition007
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition007, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(100.0f, 100.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = false;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, true);
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextFieldSelectOverlay_GetTextInputCaretPosition008
 * @tc.desc: test GetTextInputCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_GetTextInputCaretPosition008, TestSize.Level1)
{
    auto refTextBase = AceType::MakeRefPtr<MockTextBase>();
    WeakPtr<TextBase> textBase = refTextBase;
    TextFieldSelectOverlay textFieldSelectOverlay = TextFieldSelectOverlay(textBase);
    OffsetF localOffset(100.0f, 100.0f);
    WeakPtr<TextBase> hostTextBase = refTextBase;
    MockBaseTextSelectOverlay mockbBaseTextSelectOverlay = MockBaseTextSelectOverlay(hostTextBase);
    refTextBase->contentRect_ = RectF(20.0f, 30.0f, 60.0f, 80.0f);
    auto refPattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> pattern = refPattern;
    auto contentController = AceType::MakeRefPtr<ContentController>(pattern);
    auto selectController = AceType::MakeRefPtr<TextSelectController>(pattern);
    refTextBase->contentController_ = contentController;
    refTextBase->selectController_ = selectController;
    refTextBase->contentController_->content_ = u"2";
    HandleInfoNG firstHandleInfo;
    firstHandleInfo.index = 4;
    HandleInfoNG secondHandleInfo;
    secondHandleInfo.index = 5;
    refTextBase->selectController_->firstHandleInfo_ = firstHandleInfo;
    refTextBase->selectController_->secondHandleInfo_ = secondHandleInfo;
    SelectOverlayHolder selectOverlayHolder;
    auto frameNode = FrameNode::CreateFrameNode("tag", 2, refPattern, false);
    auto mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    WeakPtr<UINode> parent = mockUINode;
    frameNode->parent_ = parent;
    WeakPtr<FrameNode> node(frameNode);
    auto manager = AceType::MakeRefPtr<MySelectContentOverlayManager>(frameNode);
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    shareOverlayInfo->handleReverse = true;
    shareOverlayInfo->enableHandleLevel = true;
    manager->shareOverlayInfo_ = shareOverlayInfo;
    manager->handleNode_ = node;
    WeakPtr<AceType> bindManager = manager;
    textFieldSelectOverlay.bindManager_ = bindManager;
    SelectContentOverlayManager selectContentOverlayManager(frameNode);
    selectContentOverlayManager.selectOverlayNode_ = frameNode;
    auto index = textFieldSelectOverlay.GetTextInputCaretPosition(localOffset, false);
    EXPECT_EQ(index, 4);
}

/**
 * @tc.name: TextFieldSelectOverlay_OnMenuItemAction
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_OnMenuItemAction, TestSize.Level1)
{
    /**
     * @tc.steps: step1. crate textfield node.
     * tc.expected: step2. Check if the value is created.
     */
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call selectoverlay OnMenuItemAction.
     * tc.expected: step2. no error.
     */
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::CUT, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::SELECT_ALL, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::PASTE, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::SEARCH, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::CAMERA_INPUT, OptionMenuType::TOUCH_MENU);
    pattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::AI_WRITE, OptionMenuType::TOUCH_MENU);
}

/**
 * @tc.name: TextFieldSelectOverlay_OnHandleLevelModeChanged
 * @tc.desc: test OnHandleLevelModeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldSelectOverlay_OnHandleLevelModeChanged, TestSize.Level1)
{
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
    pattern->selectOverlay_->OnAncestorNodeChanged(FRAME_NODE_CHANGE_INFO_NONE);

    pattern->selectOverlay_->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(pattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
    pattern->selectOverlay_->OnHandleLevelModeChanged(HandleLevelMode::EMBED);
    EXPECT_EQ(pattern->selectOverlay_->handleLevelMode_, HandleLevelMode::EMBED);
    pattern->selectOverlay_->OnHandleLevelModeChanged(HandleLevelMode::OVERLAY);
    EXPECT_EQ(pattern->selectOverlay_->handleLevelMode_, HandleLevelMode::OVERLAY);
}
} // namespace OHOS::Ace::NG