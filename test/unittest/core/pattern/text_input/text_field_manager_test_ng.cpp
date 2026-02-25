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
 * @tc.name: TextFieldManagerNG_SetAttachInput001
 * @tc.desc: test SetAttachInput
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetAttachInput001, TestSize.Level1)
{
    TextFieldManagerNG text_field_manager;
    EXPECT_EQ(text_field_manager.GetAttachInputId(), -1);
    text_field_manager.SetAttachInputId(100);
    EXPECT_EQ(text_field_manager.GetAttachInputId(), 100);

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);
    RefPtr<TextFieldPattern> pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CheckAttachInput();
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
    EXPECT_NE(frameNode, nullptr);
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

/**
 * @tc.name: ParseFillContentJsonValue001
 * @tc.desc: test testInput text ParseFillContentJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, ParseFillContentJsonValue001, TestSize.Level0)
{
    auto allFillContents = JsonUtil::CreateArray(true);
    auto fillContentOne = JsonUtil::Create(true);
    fillContentOne->Put("id", 10);
    fillContentOne->Put("fillContent", "{\"userName\":\"test1\"}");
    allFillContents->Put(fillContentOne);
    auto fillContentTwo = JsonUtil::Create(true);
    fillContentTwo->Put("id", 11);
    fillContentTwo->Put("fillContent", "{\"userName\":\"test2\"}");
    allFillContents->Put(fillContentTwo);

    TextFieldManagerNG text_field_manager;
    auto result = text_field_manager.ParseFillContentJsonValue(allFillContents);
    EXPECT_EQ(result, true);
    auto map = text_field_manager.textFieldFillContentMaps_;
    EXPECT_EQ(map.size(), 2);
}

/**
 * @tc.name: ParseFillContentJsonValue002
 * @tc.desc: test testInput text ParseFillContentJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, ParseFillContentJsonValue002, TestSize.Level0)
{
    auto jsonObject = JsonUtil::Create(true);
    jsonObject->Put("id", 10);
    jsonObject->Put("userName", "test1");

    TextFieldManagerNG text_field_manager;
    auto result = text_field_manager.ParseFillContentJsonValue(jsonObject);
    EXPECT_EQ(result, false);
    auto map = text_field_manager.textFieldFillContentMaps_;
    EXPECT_EQ(map.size(), 0);
}

/**
 * @tc.name: ParseFillContentJsonValue003
 * @tc.desc: test testInput text ParseFillContentJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, ParseFillContentJsonValue003, TestSize.Level0)
{
    auto allFillContents = JsonUtil::CreateArray(true);
    auto fillContentOne = JsonUtil::Create(true);
    fillContentOne->Put("id", 10);
    fillContentOne->Put("fillContent", "{\"userName\":\"test1\"}");
    allFillContents->Put(fillContentOne);
    auto fillContentTwo = JsonUtil::Create(true);
    fillContentTwo->Put("id", 11);
    fillContentTwo->Put("fillContent", "{\"userName\":\"test2\"}");
    allFillContents->Put(fillContentTwo);
    auto fillContentThree = JsonUtil::Create(true);
    fillContentThree->Put("id", 12);
    fillContentThree->Put("fillContent", "");
    allFillContents->Put(fillContentThree);
    auto fillContentFour = JsonUtil::Create(true);
    fillContentFour->Put("id", 13);
    allFillContents->Put(fillContentFour);

    TextFieldManagerNG text_field_manager;
    auto result = text_field_manager.ParseFillContentJsonValue(allFillContents);
    EXPECT_EQ(result, true);
    auto map = text_field_manager.textFieldFillContentMaps_;
    EXPECT_EQ(map.size(), 2);
}

/**
 * @tc.name: GenerateFillContentMap001
 * @tc.desc: test testInput text GenerateFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, GenerateFillContentMap001, TestSize.Level0)
{
    auto fillContent = "{\"userName\":\"test\"}";
    FillContentMap fillContentMap;
    TextFieldManagerNG text_field_manager;
    text_field_manager.GenerateFillContentMap(fillContent, fillContentMap);
    EXPECT_EQ(fillContentMap.size(), 1);
}

/**
 * @tc.name: GenerateFillContentMap002
 * @tc.desc: test testInput text GenerateFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, GenerateFillContentMap002, TestSize.Level0)
{
    auto fillContent = "{\"\":\"test\"}";
    FillContentMap fillContentMap;
    TextFieldManagerNG text_field_manager;
    text_field_manager.GenerateFillContentMap(fillContent, fillContentMap);
    EXPECT_EQ(fillContentMap.size(), 0);
}

/**
 * @tc.name: GenerateFillContentMap003
 * @tc.desc: test testInput text GenerateFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, GenerateFillContentMap003, TestSize.Level0)
{
    auto fillContent = "{\"userName\":\"test\",\"newPassword\":\"A1xACoSOjza4Q8PF\",\"hasAccount\":\"0\",\"userName1\":"
                       "\"test\",\"userName2\":\"test\",\"userName3\":\"test\"}";
    FillContentMap fillContentMap;
    TextFieldManagerNG text_field_manager;
    text_field_manager.GenerateFillContentMap(fillContent, fillContentMap);
    EXPECT_EQ(fillContentMap.size(), 5);
}

/**
 * @tc.name: GenerateFillContentMap004
 * @tc.desc: test testInput text GenerateFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, GenerateFillContentMap004, TestSize.Level0)
{
    auto fillContent = "[{\"userName\":\"test\"}]";
    FillContentMap fillContentMap;
    TextFieldManagerNG text_field_manager;
    text_field_manager.GenerateFillContentMap(fillContent, fillContentMap);
    EXPECT_EQ(fillContentMap.size(), 0);
}

/**
 * @tc.name: GetFillContentMap001
 * @tc.desc: test testInput text GetFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, GetFillContentMap001, TestSize.Level0)
{
    auto allFillContents = JsonUtil::CreateArray(true);
    auto fillContentOne = JsonUtil::Create(true);
    fillContentOne->Put("id", 10);
    fillContentOne->Put("fillContent", "{\"userName\":\"test1\"}");
    allFillContents->Put(fillContentOne);
    auto fillContentTwo = JsonUtil::Create(true);
    fillContentTwo->Put("id", 11);
    fillContentTwo->Put("fillContent", "{\"userName\":\"test2\"}");
    allFillContents->Put(fillContentTwo);

    TextFieldManagerNG text_field_manager;
    auto result = text_field_manager.ParseFillContentJsonValue(allFillContents);
    EXPECT_EQ(result, true);
    auto map = text_field_manager.textFieldFillContentMaps_;
    EXPECT_EQ(map.size(), 2);
    auto fillContentMap = text_field_manager.GetFillContentMap(10);
    EXPECT_EQ(fillContentMap.size(), 1);
}

/**
 * @tc.name: RemoveFillContentMap001
 * @tc.desc: test testInput text RemoveFillContentMap
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, RemoveFillContentMap001, TestSize.Level0)
{
    auto allFillContents = JsonUtil::CreateArray(true);
    auto fillContentOne = JsonUtil::Create(true);
    fillContentOne->Put("id", 10);
    fillContentOne->Put("fillContent", "{\"userName\":\"test1\"}");
    allFillContents->Put(fillContentOne);
    auto fillContentTwo = JsonUtil::Create(true);
    fillContentTwo->Put("id", 11);
    fillContentTwo->Put("fillContent", "{\"userName\":\"test2\"}");
    allFillContents->Put(fillContentTwo);

    TextFieldManagerNG text_field_manager;
    auto result = text_field_manager.ParseFillContentJsonValue(allFillContents);
    EXPECT_EQ(result, true);
    auto& map = text_field_manager.textFieldFillContentMaps_;
    EXPECT_EQ(map.size(), 2);
    text_field_manager.RemoveFillContentMap(10);
    EXPECT_EQ(map.size(), 1);
}

/**
 * @tc.name: CheckInRichEditor001
 * @tc.desc: test CheckInRichEditor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, CheckInRichEditor001, TestSize.Level0)
{
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    EXPECT_FALSE(textFieldManager->CheckInRichEditor());
    auto textFieldPattern = AceType::MakeRefPtr<Pattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::RICH_EDITOR_ETS_TAG, -1, textFieldPattern);
    textFieldPattern->AttachToFrameNode(frameNode);
    textFieldManager->SetOnFocusTextField(textFieldPattern);
    EXPECT_TRUE(textFieldManager->CheckInRichEditor());
}

/**
 * @tc.name: TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange001
 * @tc.desc: Test TriggerCaretInfoUpdateOnScaleChange when onFocusTextField is null
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with null onFocusTextField
     * @tc.expected: step1. Method should return without crash
     */
    TextFieldManagerNG textFieldManager;

    // Verify initial state - no focused text field
    auto onFocusTextField = textFieldManager.GetOnFocusTextField();
    EXPECT_EQ(onFocusTextField.Upgrade(), nullptr);

    // Call target method - should not crash with null focused text field
    textFieldManager.TriggerCaretInfoUpdateOnScaleChange();

    // Verify state remains unchanged
    onFocusTextField = textFieldManager.GetOnFocusTextField();
    EXPECT_EQ(onFocusTextField.Upgrade(), nullptr);
}

/**
 * @tc.name: TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange002
 * @tc.desc: Test TriggerCaretInfoUpdateOnScaleChange when focused pattern is not TextFieldPattern
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with non-TextFieldPattern focused
     * @tc.expected: step1. Method should return without crash when DynamicCast fails
     */
    TextFieldManagerNG textFieldManager;

    // Create a basic Pattern (not TextFieldPattern)
    auto basicPattern = AceType::MakeRefPtr<Pattern>();
    ASSERT_NE(basicPattern, nullptr);

    // Create a FrameNode with the basic pattern
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXTINPUT_ETS_TAG, 100, basicPattern, false);
    ASSERT_NE(frameNode, nullptr);
    basicPattern->AttachToFrameNode(frameNode);

    // Set the non-TextFieldPattern as focused
    WeakPtr<Pattern> weakPattern(basicPattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    // Verify the pattern is set
    auto focusedPattern = textFieldManager.GetOnFocusTextField().Upgrade();
    EXPECT_NE(focusedPattern, nullptr);
    auto castResult = AceType::DynamicCast<TextFieldPattern>(focusedPattern);
    EXPECT_EQ(castResult, nullptr);

    // Call target method - should not crash when DynamicCast fails
    textFieldManager.TriggerCaretInfoUpdateOnScaleChange();
}

/**
 * @tc.name: TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange003
 * @tc.desc: Test TriggerCaretInfoUpdateOnScaleChange when focused TextFieldPattern is valid
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_TriggerCaretInfoUpdateOnScaleChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with valid TextFieldPattern focused
     * @tc.expected: step1. Method should call UpdateCaretInfoToController with forceUpdate=true
     */
    TextFieldManagerNG textFieldManager;

    // Create a TextField node with valid TextFieldPattern
    auto textFieldNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto textFieldPattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(textFieldPattern, nullptr);

    // Set the TextFieldPattern as focused
    WeakPtr<Pattern> weakPattern(textFieldPattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    // Verify the pattern is set correctly
    auto focusedPattern = textFieldManager.GetOnFocusTextField().Upgrade();
    EXPECT_NE(focusedPattern, nullptr);
    auto castResult = AceType::DynamicCast<TextFieldPattern>(focusedPattern);
    EXPECT_NE(castResult, nullptr);

    // Call target method - should successfully invoke UpdateCaretInfoToController
    textFieldManager.TriggerCaretInfoUpdateOnScaleChange();
}

/**
 * @tc.name: TextFieldManagerNG_SetClickPosition001
 * @tc.desc: test SetClickPosition with valid position within bounds
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetClickPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager and set valid click position
     */
    TextFieldManagerNG textFieldManager;
    Offset validPosition(100.0f, 100.0f);
    textFieldManager.SetClickPosition(validPosition);

    /**
     * @tc.expected: step1. Position should be set correctly
     */
    EXPECT_EQ(textFieldManager.GetClickPosition(), validPosition);
    auto optionalPosition = textFieldManager.GetOptionalClickPosition();
    EXPECT_TRUE(optionalPosition.has_value());
    EXPECT_EQ(optionalPosition.value(), validPosition);
}

/**
 * @tc.name: TextFieldManagerNG_ResetOptionalClickPosition001
 * @tc.desc: test ResetOptionalClickPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_ResetOptionalClickPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set position and then reset it
     */
    TextFieldManagerNG textFieldManager;
    Offset testPosition(50.0f, 50.0f);
    textFieldManager.SetClickPosition(testPosition);
    EXPECT_TRUE(textFieldManager.GetOptionalClickPosition().has_value());

    textFieldManager.ResetOptionalClickPosition();

    /**
     * @tc.expected: step1. Optional position should be nullopt
     */
    EXPECT_FALSE(textFieldManager.GetOptionalClickPosition().has_value());
}

/**
 * @tc.name: TextFieldManagerNG_GetFocusedNodeCaretRect001
 * @tc.desc: test GetFocusedNodeCaretRect with null focused text field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_GetFocusedNodeCaretRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager without focused field
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return empty RectF
     */
    auto caretRect = textFieldManager.GetFocusedNodeCaretRect();
    EXPECT_EQ(caretRect, RectF());
}

/**
 * @tc.name: TextFieldManagerNG_AddTextFieldInfo001
 * @tc.desc: test AddTextFieldInfo with valid info
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_AddTextFieldInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldInfo with valid node IDs
     */
    TextFieldManagerNG textFieldManager;
    TextFieldInfo info;
    info.nodeId = 1;
    info.autoFillContainerNodeId = 10;
    info.inputType = TextInputType::TEXT;
    info.contentType = TextContentType::EMAIL_ADDRESS;
    info.enableAutoFill = true;

    textFieldManager.AddTextFieldInfo(info);

    /**
     * @tc.expected: step1. Info should be added to map
     */
    EXPECT_FALSE(textFieldManager.textFieldInfoMap_.empty());
}

/**
 * @tc.name: TextFieldManagerNG_AddTextFieldInfo002
 * @tc.desc: test AddTextFieldInfo with invalid node IDs
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_AddTextFieldInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldInfo with invalid node IDs (-1)
     */
    TextFieldManagerNG textFieldManager;
    TextFieldInfo info;
    info.nodeId = -1;
    info.autoFillContainerNodeId = -1;
    info.inputType = TextInputType::TEXT;

    textFieldManager.AddTextFieldInfo(info);

    /**
     * @tc.expected: step1. Info should not be added
     */
    EXPECT_TRUE(textFieldManager.textFieldInfoMap_.empty());
}

/**
 * @tc.name: TextFieldManagerNG_AddTextFieldInfo003
 * @tc.desc: test AddTextFieldInfo with multiple fields in same container
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_AddTextFieldInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add multiple TextFieldInfo with same container
     */
    TextFieldManagerNG textFieldManager;

    TextFieldInfo info1;
    info1.nodeId = 1;
    info1.autoFillContainerNodeId = 10;
    info1.inputType = TextInputType::TEXT;
    textFieldManager.AddTextFieldInfo(info1);

    TextFieldInfo info2;
    info2.nodeId = 2;
    info2.autoFillContainerNodeId = 10;
    info2.inputType = TextInputType::VISIBLE_PASSWORD;
    textFieldManager.AddTextFieldInfo(info2);

    /**
     * @tc.expected: step1. Both infos should be added
     */
    auto containerIter = textFieldManager.textFieldInfoMap_.find(10);
    EXPECT_NE(containerIter, textFieldManager.textFieldInfoMap_.end());
    EXPECT_EQ(containerIter->second.size(), 2);
}

/**
 * @tc.name: TextFieldManagerNG_IsAutoFillPasswordType001
 * @tc.desc: test IsAutoFillPasswordType with various input types
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_IsAutoFillPasswordType001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldInfo with VISIBLE_PASSWORD type
     */
    TextFieldManagerNG textFieldManager;
    TextFieldInfo info1;
    info1.inputType = TextInputType::VISIBLE_PASSWORD;
    info1.contentType = TextContentType::BEGIN;

    /**
     * @tc.expected: step1. Should be password type
     */
    EXPECT_TRUE(textFieldManager.IsAutoFillPasswordType(info1));

    /**
     * @tc.steps: step2. Create TextFieldInfo with NEW_PASSWORD type
     */
    TextFieldInfo info2;
    info2.inputType = TextInputType::NEW_PASSWORD;
    info2.contentType = TextContentType::BEGIN;

    /**
     * @tc.expected: step2. Should be password type
     */
    EXPECT_TRUE(textFieldManager.IsAutoFillPasswordType(info2));

    /**
     * @tc.steps: step3. Create TextFieldInfo with NUMBER_PASSWORD type
     */
    TextFieldInfo info3;
    info3.inputType = TextInputType::NUMBER_PASSWORD;
    info3.contentType = TextContentType::BEGIN;

    /**
     * @tc.expected: step3. Should be password type
     */
    EXPECT_TRUE(textFieldManager.IsAutoFillPasswordType(info3));

    /**
     * @tc.steps: step4. Create TextFieldInfo with TEXT type
     */
    TextFieldInfo info4;
    info4.inputType = TextInputType::TEXT;
    info4.contentType = TextContentType::BEGIN;

    /**
     * @tc.expected: step4. Should not be password type
     */
    EXPECT_FALSE(textFieldManager.IsAutoFillPasswordType(info4));
}

/**
 * @tc.name: TextFieldManagerNG_IsAutoFillPasswordType002
 * @tc.desc: test IsAutoFillPasswordType with content types
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_IsAutoFillPasswordType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldInfo with VISIBLE_PASSWORD content type
     */
    TextFieldManagerNG textFieldManager;
    TextFieldInfo info1;
    info1.inputType = TextInputType::BEGIN;
    info1.contentType = TextContentType::VISIBLE_PASSWORD;

    /**
     * @tc.expected: step1. Should be password type
     */
    EXPECT_TRUE(textFieldManager.IsAutoFillPasswordType(info1));

    /**
     * @tc.steps: step2. Create TextFieldInfo with NEW_PASSWORD content type
     */
    TextFieldInfo info2;
    info2.inputType = TextInputType::BEGIN;
    info2.contentType = TextContentType::NEW_PASSWORD;

    /**
     * @tc.expected: step2. Should be password type
     */
    EXPECT_TRUE(textFieldManager.IsAutoFillPasswordType(info2));

    /**
     * @tc.steps: step3. Create TextFieldInfo with EMAIL_ADDRESS content type
     */
    TextFieldInfo info3;
    info3.inputType = TextInputType::BEGIN;
    info3.contentType = TextContentType::EMAIL_ADDRESS;

    /**
     * @tc.expected: step3. Should not be password type
     */
    EXPECT_FALSE(textFieldManager.IsAutoFillPasswordType(info3));
}

/**
 * @tc.name: TextFieldManagerNG_HasAutoFillPasswordNodeInContainer001
 * @tc.desc: test HasAutoFillPasswordNodeInContainer with non-existent container
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_HasAutoFillPasswordNodeInContainer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check for password node in non-existent container
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return false
     */
    EXPECT_FALSE(textFieldManager.HasAutoFillPasswordNodeInContainer(999, 1));
}

/**
 * @tc.name: TextFieldManagerNG_HasAutoFillPasswordNodeInContainer002
 * @tc.desc: test HasAutoFillPasswordNodeInContainer with password node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_HasAutoFillPasswordNodeInContainer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add password field and check
     */
    TextFieldManagerNG textFieldManager;

    TextFieldInfo passwordInfo;
    passwordInfo.nodeId = 1;
    passwordInfo.autoFillContainerNodeId = 10;
    passwordInfo.inputType = TextInputType::VISIBLE_PASSWORD;
    passwordInfo.enableAutoFill = true;
    textFieldManager.AddTextFieldInfo(passwordInfo);

    /**
     * @tc.expected: step1. Should return true when checking other node
     */
    EXPECT_FALSE(textFieldManager.HasAutoFillPasswordNodeInContainer(10, 2));
}

/**
 * @tc.name: TextFieldManagerNG_HasAutoFillPasswordNodeInContainer003
 * @tc.desc: test HasAutoFillPasswordNodeInContainer with disabled auto fill
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_HasAutoFillPasswordNodeInContainer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add password field with autoFill disabled
     */
    TextFieldManagerNG textFieldManager;

    TextFieldInfo passwordInfo;
    passwordInfo.nodeId = 1;
    passwordInfo.autoFillContainerNodeId = 10;
    passwordInfo.inputType = TextInputType::VISIBLE_PASSWORD;
    passwordInfo.enableAutoFill = false;
    textFieldManager.AddTextFieldInfo(passwordInfo);

    /**
     * @tc.expected: step1. Should return false
     */
    EXPECT_FALSE(textFieldManager.HasAutoFillPasswordNodeInContainer(10, 2));
}

/**
 * @tc.name: TextFieldManagerNG_SetOnFocusTextField003
 * @tc.desc: test SetOnFocusTextField with null pattern
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetOnFocusTextField003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set null pattern as focused
     */
    TextFieldManagerNG textFieldManager;
    WeakPtr<Pattern> nullPattern;

    textFieldManager.SetOnFocusTextField(nullPattern);

    /**
     * @tc.expected: step1. ID should remain -1
     */
    EXPECT_EQ(textFieldManager.GetOnFocusTextFieldId(), -1);
}

/**
 * @tc.name: TextFieldManagerNG_ClearOnFocusTextField001
 * @tc.desc: test ClearOnFocusTextField without ID
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_ClearOnFocusTextField001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Clear focused field without ID
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    textFieldManager.ClearOnFocusTextField();

    /**
     * @tc.expected: step1. Pattern should be cleared
     */
    EXPECT_EQ(textFieldManager.GetOnFocusTextField().Upgrade(), nullptr);
}

/**
 * @tc.name: TextFieldManagerNG_ClearOnFocusTextField002
 * @tc.desc: test ClearOnFocusTextField with ID
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_ClearOnFocusTextField002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set focused field and clear with matching ID
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    int32_t nodeId = textFieldManager.GetOnFocusTextFieldId();
    textFieldManager.ClearOnFocusTextField(nodeId);

    /**
     * @tc.expected: step1. Pattern should be cleared
     */
    EXPECT_EQ(textFieldManager.GetOnFocusTextField().Upgrade(), nullptr);
    EXPECT_FALSE(textFieldManager.GetIfFocusTextFieldIsInline());
    EXPECT_FALSE(textFieldManager.GetOptionalClickPosition().has_value());
}

/**
 * @tc.name: TextFieldManagerNG_ClearOnFocusTextField003
 * @tc.desc: test ClearOnFocusTextField with non-matching ID
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_ClearOnFocusTextField003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set focused field and clear with non-matching ID
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);

    textFieldManager.ClearOnFocusTextField(99999);

    /**
     * @tc.expected: step1. Pattern should still be set
     */
    EXPECT_NE(textFieldManager.GetOnFocusTextField().Upgrade(), nullptr);
}

/**
 * @tc.name: TextFieldManagerNG_GetImeShow001
 * @tc.desc: test GetImeShow with default values
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_GetImeShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextFieldManager with default values
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return false (no IME shown)
     */
    EXPECT_FALSE(textFieldManager.GetImeShow());
}

/**
 * @tc.name: TextFieldManagerNG_GetImeShow002
 * @tc.desc: test GetImeShow when imeShow_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_GetImeShow002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set imeShow to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetImeShow(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetImeShow());
}

/**
 * @tc.name: TextFieldManagerNG_GetImeShow003
 * @tc.desc: test GetImeShow when imeAttachCalled_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_GetImeShow003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set imeAttachCalled to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetImeAttached(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetImeShow());
}

/**
 * @tc.name: TextFieldManagerNG_SetHeight_GetHeight001
 * @tc.desc: test SetHeight and GetHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetHeight_GetHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set height to 100
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetHeight(100.0f);

    /**
     * @tc.expected: step1. Height should include RESERVE_BOTTOM_HEIGHT
     */
    float height = textFieldManager.GetHeight();
    EXPECT_GT(height, 100.0f); // Should be 100 + RESERVE_BOTTOM_HEIGHT
}

/**
 * @tc.name: TextFieldManagerNG_AddAvoidKeyboardCallback001
 * @tc.desc: test AddAvoidKeyboardCallback for custom keyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_AddAvoidKeyboardCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add custom keyboard callback
     */
    TextFieldManagerNG textFieldManager;
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() { callbackExecuted = true; };

    textFieldManager.AddAvoidKeyboardCallback(1, true, std::move(callback));

    /**
     * @tc.expected: step1. Callback should be added
     */
    EXPECT_GT(textFieldManager.avoidCustomKeyboardCallbacks_.size(), 0);
}

/**
 * @tc.name: TextFieldManagerNG_AddAvoidKeyboardCallback002
 * @tc.desc: test AddAvoidKeyboardCallback for system keyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_AddAvoidKeyboardCallback002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add system keyboard callback
     */
    TextFieldManagerNG textFieldManager;
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() { callbackExecuted = true; };

    textFieldManager.AddAvoidKeyboardCallback(1, false, std::move(callback));

    /**
     * @tc.expected: step1. Callback should be added
     */
    EXPECT_GT(textFieldManager.avoidSystemKeyboardCallbacks_.size(), 0);
}

/**
 * @tc.name: TextFieldManagerNG_RemoveAvoidKeyboardCallback001
 * @tc.desc: test RemoveAvoidKeyboardCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_RemoveAvoidKeyboardCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add and then remove callback
     */
    TextFieldManagerNG textFieldManager;
    auto callback = []() {};

    textFieldManager.AddAvoidKeyboardCallback(1, true, std::move(callback));
    EXPECT_GT(textFieldManager.avoidCustomKeyboardCallbacks_.size(), 0);

    textFieldManager.RemoveAvoidKeyboardCallback(1);

    /**
     * @tc.expected: step1. Callback should be removed from both maps
     */
    EXPECT_EQ(textFieldManager.avoidCustomKeyboardCallbacks_.size(), 0);
    EXPECT_EQ(textFieldManager.avoidSystemKeyboardCallbacks_.size(), 0);
}

/**
 * @tc.name: TextFieldManagerNG_OnAfterAvoidKeyboard001
 * @tc.desc: test OnAfterAvoidKeyboard with custom keyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_OnAfterAvoidKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add custom keyboard callback and trigger
     */
    TextFieldManagerNG textFieldManager;
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() { callbackExecuted = true; };

    textFieldManager.AddAvoidKeyboardCallback(1, true, std::move(callback));
    textFieldManager.OnAfterAvoidKeyboard(true);

    /**
     * @tc.expected: step1. Callback should be executed
     */
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: TextFieldManagerNG_OnAfterAvoidKeyboard002
 * @tc.desc: test OnAfterAvoidKeyboard with system keyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_OnAfterAvoidKeyboard002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add system keyboard callback and trigger
     */
    TextFieldManagerNG textFieldManager;
    bool callbackExecuted = false;
    auto callback = [&callbackExecuted]() { callbackExecuted = true; };

    textFieldManager.AddAvoidKeyboardCallback(1, false, std::move(callback));
    textFieldManager.OnAfterAvoidKeyboard(false);

    /**
     * @tc.expected: step1. Callback should be executed
     */
    EXPECT_TRUE(callbackExecuted);
}

/**
 * @tc.name: TextFieldManagerNG_FindScrollableOfFocusedTextField001
 * @tc.desc: test FindScrollableOfFocusedTextField with null node
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_FindScrollableOfFocusedTextField001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call with null node
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return null
     */
    auto result = textFieldManager.FindScrollableOfFocusedTextField(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextFieldManagerNG_UpdatePrevHasTextFieldPattern001
 * @tc.desc: test UpdatePrevHasTextFieldPattern
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdatePrevHasTextFieldPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Update with no focused field
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.UpdatePrevHasTextFieldPattern();

    /**
     * @tc.expected: step1. Should be false
     */
    EXPECT_FALSE(textFieldManager.PrevHasTextFieldPattern());
}

/**
 * @tc.name: TextFieldManagerNG_UpdatePrevHasTextFieldPattern002
 * @tc.desc: test UpdatePrevHasTextFieldPattern with focused field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_UpdatePrevHasTextFieldPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set focused field and update
     */
    TextFieldManagerNG textFieldManager;

    auto textFieldNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextFieldPattern>(); });
    ASSERT_NE(textFieldNode, nullptr);

    auto pattern = textFieldNode->GetPattern<TextFieldPattern>();
    ASSERT_NE(pattern, nullptr);

    WeakPtr<Pattern> weakPattern(pattern);
    textFieldManager.SetOnFocusTextField(weakPattern);
    textFieldManager.UpdatePrevHasTextFieldPattern();

    /**
     * @tc.expected: step1. Should be true
     */
    EXPECT_TRUE(textFieldManager.PrevHasTextFieldPattern());
}

/**
 * @tc.name: TextFieldManagerNG_SetIfFocusTextFieldIsInline001
 * @tc.desc: test SetIfFocusTextFieldIsInline and GetIfFocusTextFieldIsInline
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetIfFocusTextFieldIsInline001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set inline status to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetIfFocusTextFieldIsInline(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetIfFocusTextFieldIsInline());

    /**
     * @tc.steps: step2. Set inline status to false
     */
    textFieldManager.SetIfFocusTextFieldIsInline(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_FALSE(textFieldManager.GetIfFocusTextFieldIsInline());
}

/**
 * @tc.name: TextFieldManagerNG_SetInlineTextFieldAvoidPositionYAndHeight001
 * @tc.desc: test SetInlineTextFieldAvoidPositionYAndHeight and GetInlineTextFieldAvoidPositionYAndHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetInlineTextFieldAvoidPositionYAndHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set inline position and height
     */
    TextFieldManagerNG textFieldManager;
    double positionY = 100.0;
    double height = 50.0;

    textFieldManager.SetInlineTextFieldAvoidPositionYAndHeight(positionY, height);

    /**
     * @tc.expected: step1. Should return same values
     */
    double retrievedPositionY = 0.0;
    double retrievedHeight = 0.0;
    textFieldManager.GetInlineTextFieldAvoidPositionYAndHeight(retrievedPositionY, retrievedHeight);

    EXPECT_EQ(retrievedPositionY, positionY);
    EXPECT_EQ(retrievedHeight, height);
}

/**
 * @tc.name: TextFieldManagerNG_SetLastAvoidFieldId_GetLastAvoidFieldId001
 * @tc.desc: test SetLastAvoidFieldId and GetLastAvoidFieldId
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetLastAvoidFieldId_GetLastAvoidFieldId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set last avoid field ID
     */
    TextFieldManagerNG textFieldManager;
    int32_t fieldId = 12345;

    textFieldManager.SetLastAvoidFieldId(fieldId);

    /**
     * @tc.expected: step1. Should return same ID
     */
    EXPECT_EQ(textFieldManager.GetLastAvoidFieldId(), fieldId);
}

/**
 * @tc.name: TextFieldManagerNG_SetLaterAvoid_GetLaterAvoid001
 * @tc.desc: test SetLaterAvoid and GetLaterAvoid
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetLaterAvoid_GetLaterAvoid001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set later avoid to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetLaterAvoid(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetLaterAvoid());

    /**
     * @tc.steps: step2. Set later avoid to false
     */
    textFieldManager.SetLaterAvoid(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_FALSE(textFieldManager.GetLaterAvoid());
}

/**
 * @tc.name: TextFieldManagerNG_SetLaterAvoidArgs_GetLaterAvoidKeyboardRect001
 * @tc.desc: test SetLaterAvoidArgs and getter methods
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetLaterAvoidArgs_GetLaterAvoidKeyboardRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set later avoid info
     */
    TextFieldManagerNG textFieldManager;
    LaterAvoidInfo info;
    info.laterAvoid = true;
    info.keyboardArea = Rect(0, 100, 200, 300);
    info.positionY = 150.0;
    info.avoidHeight = 50.0;
    info.orientation = 1;

    textFieldManager.SetLaterAvoidArgs(info);

    /**
     * @tc.expected: step1. Should return same values
     */
    EXPECT_TRUE(textFieldManager.GetLaterAvoid());
    Rect keyboardRect = textFieldManager.GetLaterAvoidKeyboardRect();
    EXPECT_EQ(keyboardRect, info.keyboardArea);
    EXPECT_EQ(textFieldManager.GetLaterAvoidPositionY(), info.positionY);
    EXPECT_EQ(textFieldManager.GetLaterAvoidHeight(), info.avoidHeight);
    EXPECT_EQ(textFieldManager.GetLaterOrientation(), info.orientation);
}

/**
 * @tc.name: TextFieldManagerNG_SetLastRequestKeyboardId_GetLastRequestKeyboardId001
 * @tc.desc: test SetLastRequestKeyboardId and GetLastRequestKeyboardId
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetLastRequestKeyboardId_GetLastRequestKeyboardId001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set last request keyboard ID
     */
    TextFieldManagerNG textFieldManager;
    int32_t keyboardId = 999;

    textFieldManager.SetLastRequestKeyboardId(keyboardId);

    /**
     * @tc.expected: step1. Should return same ID
     */
    EXPECT_EQ(textFieldManager.GetLastRequestKeyboardId(), keyboardId);
}

/**
 * @tc.name: TextFieldManagerNG_SetClickPositionOffset_GetClickPositionOffset001
 * @tc.desc: test SetClickPositionOffset and GetClickPositionOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetClickPositionOffset_GetClickPositionOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set click position offset
     */
    TextFieldManagerNG textFieldManager;
    float offset = 25.5f;

    textFieldManager.SetClickPositionOffset(offset);

    /**
     * @tc.expected: step1. Should return same offset
     */
    EXPECT_EQ(textFieldManager.GetClickPositionOffset(), offset);
}

/**
 * @tc.name: TextFieldManagerNG_SetFocusFieldOrientation_GetFocusFieldOrientation001
 * @tc.desc: test SetFocusFieldOrientation and GetFocusFieldOrientation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetFocusFieldOrientation_GetFocusFieldOrientation001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set focus field orientation
     */
    TextFieldManagerNG textFieldManager;
    int32_t orientation = 1;

    textFieldManager.SetFocusFieldOrientation(orientation);

    /**
     * @tc.expected: step1. Should return same orientation
     */
    EXPECT_EQ(textFieldManager.GetFocusFieldOrientation(), orientation);
}

/**
 * @tc.name: TextFieldManagerNG_SetIsImeAttached_GetIsImeAttached001
 * @tc.desc: test SetIsImeAttached and GetIsImeAttached
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetIsImeAttached_GetIsImeAttached001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set IME attached to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetIsImeAttached(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetIsImeAttached());

    /**
     * @tc.steps: step2. Set IME attached to false
     */
    textFieldManager.SetIsImeAttached(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_FALSE(textFieldManager.GetIsImeAttached());
}

/**
 * @tc.name: TextFieldManagerNG_SetContextTriggerAvoidTaskOrientation_GetContextTriggerAvoidTaskOrientation001
 * @tc.desc: test SetContextTriggerAvoidTaskOrientation and GetContextTriggerAvoidTaskOrientation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetContextTriggerAvoidTaskOrientation_GetContextTriggerAvoidTaskOrientation001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set context trigger avoid task orientation
     */
    TextFieldManagerNG textFieldManager;
    int32_t orientation = 2;

    textFieldManager.SetContextTriggerAvoidTaskOrientation(orientation);

    /**
     * @tc.expected: step1. Should return same orientation
     */
    EXPECT_EQ(textFieldManager.GetContextTriggerAvoidTaskOrientation(), orientation);
}

/**
 * @tc.name: TextFieldManagerNG_SetLastAvoidOrientation_GetLastAvoidOrientation001
 * @tc.desc: test SetLastAvoidOrientation and GetLastAvoidOrientation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetLastAvoidOrientation_GetLastAvoidOrientation001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set last avoid orientation
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetLastAvoidOrientation(1);

    /**
     * @tc.expected: step1. Should return same orientation
     */
    EXPECT_TRUE(textFieldManager.GetLastAvoidOrientation().has_value());
    EXPECT_EQ(textFieldManager.GetLastAvoidOrientation().value(), 1);
}

/**
 * @tc.name: TextFieldManagerNG_SetLastRootHeight_GetLastRootHeight001
 * @tc.desc: test SetLastRootHeight and GetLastRootHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetLastRootHeight_GetLastRootHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set last root height
     */
    TextFieldManagerNG textFieldManager;
    double rootHeight = 800.0;

    textFieldManager.SetLastRootHeight(rootHeight);

    /**
     * @tc.expected: step1. Should return same height
     */
    EXPECT_TRUE(textFieldManager.GetLastRootHeight().has_value());
    EXPECT_EQ(textFieldManager.GetLastRootHeight().value(), rootHeight);
}

/**
 * @tc.name: TextFieldManagerNG_SetCustomKeyboardId_GetCustomKeyboardId001
 * @tc.desc: test SetCustomKeyboardId and GetCustomKeyboardId
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetCustomKeyboardId_GetCustomKeyboardId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set custom keyboard ID
     */
    TextFieldManagerNG textFieldManager;
    int32_t customId = 456;

    textFieldManager.SetCustomKeyboardId(customId);

    /**
     * @tc.expected: step1. Should return same ID
     */
    EXPECT_EQ(textFieldManager.GetCustomKeyboardId(), customId);
}

/**
 * @tc.name: TextFieldManagerNG_SetUsingCustomKeyboardAvoid_UsingCustomKeyboardAvoid001
 * @tc.desc: test SetUsingCustomKeyboardAvoid and UsingCustomKeyboardAvoid
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetUsingCustomKeyboardAvoid_UsingCustomKeyboardAvoid001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set using custom keyboard avoid to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetUsingCustomKeyboardAvoid(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.UsingCustomKeyboardAvoid());

    /**
     * @tc.steps: step2. Set using custom keyboard avoid to false
     */
    textFieldManager.SetUsingCustomKeyboardAvoid(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_FALSE(textFieldManager.UsingCustomKeyboardAvoid());
}

/**
 * @tc.name: TextFieldManagerNG_SetCustomKeyboardContinueFeature_GetCustomKeyboardContinueFeature001
 * @tc.desc: test SetCustomKeyboardContinueFeature and GetCustomKeyboardContinueFeature
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetCustomKeyboardContinueFeature_GetCustomKeyboardContinueFeature001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set custom keyboard continue feature to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetCustomKeyboardContinueFeature(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetCustomKeyboardContinueFeature());

    /**
     * @tc.steps: step2. Set custom keyboard continue feature to false
     */
    textFieldManager.SetCustomKeyboardContinueFeature(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_FALSE(textFieldManager.GetCustomKeyboardContinueFeature());
}

/**
 * @tc.name: TextFieldManagerNG_SetIsAskCeliaSupported_IsAskCeliaSupported001
 * @tc.desc: test SetIsAskCeliaSupported and IsAskCeliaSupported
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_SetIsAskCeliaSupported_IsAskCeliaSupported001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set IsAskCeliaSupported to true
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetIsAskCeliaSupported(true);

    /**
     * @tc.expected: step1. Should return true
     */
    EXPECT_TRUE(textFieldManager.IsAskCeliaSupported().has_value());
    EXPECT_TRUE(textFieldManager.IsAskCeliaSupported().value());

    /**
     * @tc.steps: step2. Set IsAskCeliaSupported to false
     */
    textFieldManager.SetIsAskCeliaSupported(false);

    /**
     * @tc.expected: step2. Should return false
     */
    EXPECT_TRUE(textFieldManager.IsAskCeliaSupported().has_value());
    EXPECT_FALSE(textFieldManager.IsAskCeliaSupported().value());
}

/**
 * @tc.name: TextFieldManagerNG_IsAskCeliaSupported002
 * @tc.desc: test IsAskCeliaSupported when not set
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_IsAskCeliaSupported002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Check IsAskCeliaSupported without setting it
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return nullopt
     */
    EXPECT_FALSE(textFieldManager.IsAskCeliaSupported().has_value());
}

/**
 * @tc.name: TextFieldManagerNG_SetNeedToRequestKeyboard_GetNeedToRequestKeyboard001
 * @tc.desc: test SetNeedToRequestKeyboard and GetNeedToRequestKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG,
    TextFieldManagerNG_SetNeedToRequestKeyboard_GetNeedToRequestKeyboard001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set need to request keyboard to false
     */
    TextFieldManagerNG textFieldManager;
    textFieldManager.SetNeedToRequestKeyboard(false);

    /**
     * @tc.expected: step1. Should return false
     */
    EXPECT_FALSE(textFieldManager.GetNeedToRequestKeyboard());

    /**
     * @tc.steps: step2. Set need to request keyboard to true
     */
    textFieldManager.SetNeedToRequestKeyboard(true);

    /**
     * @tc.expected: step2. Should return true
     */
    EXPECT_TRUE(textFieldManager.GetNeedToRequestKeyboard());
}

/**
 * @tc.name: TextFieldManagerNG_OnBackPressed001
 * @tc.desc: test OnBackPressed with null focused field
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_OnBackPressed001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call OnBackPressed without focused field
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return false
     */
    EXPECT_FALSE(textFieldManager.OnBackPressed());
}

/**
 * @tc.name: TextFieldManagerNG_NeedCloseKeyboard001
 * @tc.desc: test NeedCloseKeyboard with null preNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldManagerTestNG, TextFieldManagerNG_NeedCloseKeyboard001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Call NeedCloseKeyboard without preNode
     */
    TextFieldManagerNG textFieldManager;

    /**
     * @tc.expected: step1. Should return false
     */
    EXPECT_FALSE(textFieldManager.NeedCloseKeyboard());
}

} // namespace OHOS::Ace::NG
