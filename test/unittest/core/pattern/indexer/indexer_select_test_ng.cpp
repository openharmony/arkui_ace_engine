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

#include "indexer_test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
class IndexerSelectTestNg : public IndexerTestNg {
public:
    void MoveIndex(GestureEvent gestureEvent)
    {
        auto start = pattern_->panEvent_->GetActionStartEventFunc();
        auto update = pattern_->panEvent_->GetActionUpdateEventFunc();
        start(gestureEvent);
        update(gestureEvent);
    }

    void Touch(TouchType touchType, float locationY)
    {
        float firstOffsetY = 0.f;
        if (pattern_->itemCount_ > 0) {
            firstOffsetY = GetChildY(frameNode_, 0);
        }
        TouchEventInfo touchEventInfo = CreateTouchEventInfo(touchType, Offset(0.f, locationY + firstOffsetY));
        auto touchFuc = pattern_->touchListener_->GetTouchEventCallback();
        touchFuc(touchEventInfo);
    }
};

/**
 * @tc.name: SelectByPanEvent001
 * @tc.desc: Test MoveIndexByStep, change selected by panEvent_
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent001, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::AXIS);

    /**
     * @tc.steps: step1. Not move
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetMainDelta(0.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. Move up
     * @tc.expected: Selected unchanged.
     */
    gestureEvent.SetMainDelta(1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. Move down
     * @tc.expected: Selected changed
     */
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step4. Select last index, than move down
     * @tc.expected: Selected unchanged.
     */
    const float lastIndex = pattern_->itemCount_ - 1;
    pattern_->selected_ = lastIndex;
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), lastIndex);

    /**
     * @tc.steps: step5. Move up
     * @tc.expected: Selected changed.
     */
    gestureEvent.SetMainDelta(1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), lastIndex - 1);
}

/**
 * @tc.name: SelectByPanEvent002
 * @tc.desc: Test MoveIndexByStep, trigger event
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent002, TestSize.Level1)
{
    int32_t selected = -1;
    int32_t changeSelected = -1;
    int32_t creatChangeSelected = -1;
    OnSelectedEvent onSelected = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    OnSelectedEvent changeEvent = [&changeSelected](int32_t selectedIndex) { changeSelected = selectedIndex; };
    OnSelectedEvent creatChangeEvent = [&creatChangeSelected](
                                           int32_t selectedIndex) { creatChangeSelected = selectedIndex; };
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetOnSelected(std::move(onSelected));
    model.SetChangeEvent(std::move(changeEvent));
    model.SetCreatChangeEvent(std::move(creatChangeEvent));
    CreateDone();

    /**
     * @tc.steps: step1. Move up
     * @tc.expected: Selected unchanged, not trigger event
     */
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    gestureEvent.SetMainDelta(1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(selected, -1);
    EXPECT_EQ(changeSelected, -1);
    EXPECT_EQ(creatChangeSelected, -1);

    /**
     * @tc.steps: step2. Move down
     * @tc.expected: Selected changed, trigger event
     */
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(selected, 1);
    EXPECT_EQ(changeSelected, 1);
    EXPECT_EQ(creatChangeSelected, 1);
}

/**
 * @tc.name: SelectByPanEvent003
 * @tc.desc: Test MoveIndexByStep, change selected by panEvent_ in Short fold
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    /**
     * @tc.steps: step1. Move down
     * @tc.expected: Selected changed
     */
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::AXIS);
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");

    /**
     * @tc.steps: step2. Move down
     * @tc.expected: Selected changed.
     */
    gestureEvent.SetMainDelta(-1.f);
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 2);
    EXPECT_EQ(accessibilityProperty_->GetText(), "G");
}

/**
 * @tc.name: SelectByPanEvent004
 * @tc.desc: Test MoveIndexByOffset
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent004, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);

    /**
     * @tc.steps: step1. Location at the a item
     * @tc.expected: Selected changed
     */
    float locationY = 50.f + GetChildY(frameNode_, 0);
    gestureEvent.SetLocalLocation(Offset(0.f, locationY));
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 3);

    /**
     * @tc.steps: step2. Location not change
     * @tc.expected: Selected unchanged
     */
    gestureEvent.SetLocalLocation(Offset(0.f, locationY));
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 3);

    /**
     * @tc.steps: step3. Location at the a another item
     * @tc.expected: Selected changed
     */
    gestureEvent.SetLocalLocation(Offset(0.f, locationY + 50.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 6);

    /**
     * @tc.steps: step4. Location at the out of indexer
     * @tc.expected: Selected unchanged
     */
    gestureEvent.SetLocalLocation(Offset(0.f, -1.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 6);
}

/**
 * @tc.name: SelectByPanEvent005
 * @tc.desc: Test MoveIndexByOffset with empty array
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test with empty array.
     * @tc.expected: Selected unchanged.
     */
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetUsingPopup(true);
    CreateDone();
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);
    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);
}

/**
 * @tc.name: SelectByPanEvent006
 * @tc.desc: Test MoveIndexByOffset, trigger event
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByPanEvent006, TestSize.Level1)
{
    int32_t selected = -1;
    int32_t changeSelected = -1;
    int32_t creatChangeSelected = -1;
    OnSelectedEvent onSelected = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    OnSelectedEvent changeEvent = [&changeSelected](int32_t selectedIndex) { changeSelected = selectedIndex; };
    OnSelectedEvent creatChangeEvent = [&creatChangeSelected](
                                           int32_t selectedIndex) { creatChangeSelected = selectedIndex; };
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetOnSelected(std::move(onSelected));
    model.SetChangeEvent(std::move(changeEvent));
    model.SetCreatChangeEvent(std::move(creatChangeEvent));
    CreateDone();

    /**
     * @tc.steps: step1. Location is at out
     * @tc.expected: Selected unchanged, not trigger event
     */
    GestureEvent gestureEvent;
    gestureEvent.SetInputEventType(InputEventType::KEYBOARD);
    gestureEvent.SetLocalLocation(Offset(0.f, -1.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(selected, -1);
    EXPECT_EQ(changeSelected, -1);
    EXPECT_EQ(creatChangeSelected, -1);

    /**
     * @tc.steps: step2. Location is at item
     * @tc.expected: Selected changed, trigger event
     */
    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(selected, 3);
    EXPECT_EQ(changeSelected, 3);
    EXPECT_EQ(creatChangeSelected, 3);

    /**
     * @tc.steps: step2. Location is at same item
     * @tc.expected: Selected unchanged, not trigger event
     */
    selected = -1;
    changeSelected = -1;
    creatChangeSelected = -1;
    gestureEvent.SetLocalLocation(Offset(0.f, 50.f));
    MoveIndex(gestureEvent);
    EXPECT_EQ(selected, -1);
    EXPECT_EQ(changeSelected, -1);
    EXPECT_EQ(creatChangeSelected, -1);
}

/**
 * @tc.name: Hover001
 * @tc.desc: Test Hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, Hover001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    /**
     * @tc.steps: step1. Enter indexer
     * @tc.expected: Trigger IndexerHoverInAnimation
     */
    pattern_->OnHover(true);
    EXPECT_TRUE(pattern_->isHover_);
    auto renderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), indexerTheme_->GetSlipHoverBackgroundColor());

    /**
     * @tc.steps: step2. Enter item(index:1)
     * @tc.expected: Show popup
     */
    pattern_->OnHover(true);
    pattern_->OnChildHover(1, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 1);
    EXPECT_NE(pattern_->popupNode_, nullptr);
    auto listUINode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
    EXPECT_EQ(listUINode->TotalChildCount(), 2);

    /**
     * @tc.steps: step3. Leave item(index:1), Enter item(index:2)
     * @tc.expected: Change popup listData by OnRequestPopupData
     */
    pattern_->OnHover(true);
    pattern_->OnChildHover(1, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    pattern_->OnHover(true);
    pattern_->OnChildHover(2, true);
    EXPECT_EQ(pattern_->childHoverIndex_, 2);
    EXPECT_NE(pattern_->popupNode_, nullptr);
    EXPECT_EQ(listUINode->TotalChildCount(), 2); // GetPopupData need return diff data

    /**
     * @tc.steps: step4. Leave indexer
     * @tc.expected: Trigger IndexerHoverOutAnimation
     */
    pattern_->OnHover(true);
    pattern_->OnChildHover(2, false);
    EXPECT_EQ(pattern_->childHoverIndex_, -1);
    pattern_->OnHover(false);
    EXPECT_FALSE(pattern_->isHover_);
    EXPECT_EQ(renderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
}

/**
 * @tc.name: Hover002
 * @tc.desc: Test Hover with empty arrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, Hover002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set empty arrayValue and trigger OnHover
     * @tc.expected: isHover_ is still be false
     */
    IndexerModelNG model = CreateIndexer(std::vector<std::string>(), 0);
    model.SetUsingPopup(true);
    CreateDone();
    pattern_->OnHover(true);
    EXPECT_FALSE(pattern_->isHover_);
}

/**
 * @tc.name: SelectByTouch001
 * @tc.desc: Test touchListener_ func with hover, hover than touch
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByTouch001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    /**
     * @tc.steps: step1. OnTouchDown item(index:3)
     * @tc.expected: Selected index is correct.
     */
    pattern_->OnHover(true);
    pattern_->OnChildHover(3, true);
    Touch(TouchType::DOWN, 50.f);
    EXPECT_EQ(pattern_->GetSelected(), 3);

    /**
     * @tc.steps: step2. Touch move to item(index:1)
     * @tc.expected: Selected index not change
     */
    pattern_->OnChildHover(3, false);
    pattern_->OnChildHover(1, true);
    Touch(TouchType::MOVE, 20.f);
    EXPECT_EQ(pattern_->GetSelected(), 3);

    /**
     * @tc.steps: step3. OnTouchUp
     * @tc.expected: Selected index is correct.
     */
    Touch(TouchType::UP, 20.f);
    EXPECT_EQ(pattern_->GetSelected(), 3);
}

/**
 * @tc.name: SelectByTouch002
 * @tc.desc: Test touchListener_ func without hover, only touch
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByTouch002, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();

    /**
     * @tc.steps: step1. OnTouchDown.
     * @tc.expected: Selected index is correct.
     */
    Touch(TouchType::DOWN, 50.f);
    EXPECT_EQ(pattern_->GetSelected(), 3);

    /**
     * @tc.steps: step2. OnTouchUp, same location.
     * @tc.expected: Selected index is correct.
     */
    Touch(TouchType::UP, 50.f);
    EXPECT_EQ(pattern_->GetSelected(), 3);
}

/**
 * @tc.name: SelectByTouch003
 * @tc.desc: Test touchListener_ func with other condition.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByTouch003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty array
     * @tc.expected: Selected unchanged.
     */
    CreateIndexer(std::vector<std::string>(), 0);
    CreateDone();
    Touch(TouchType::DOWN, 20.f);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    Touch(TouchType::UP, 20.f);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. Touch -1.f
     * @tc.expected: Selected index 0.
     */
    ClearOldNodes();
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    Touch(TouchType::DOWN, -1.f);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    Touch(TouchType::UP, -1.f);
    EXPECT_EQ(pattern_->GetSelected(), 0);
}

/**
 * @tc.name: SelectByKeyEvent001
 * @tc.desc: Test OnKeyEvent func about KeyIndexByStep.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByKeyEvent001, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();

    /**
     * @tc.steps: step1. UNKNOWN keyEvent.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. KEY_UNKNOWN from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. KEY_DPAD_UP from 0.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step4. KEY_DPAD_DOWN from 0.
     * @tc.expected: Selected += 1.
     */
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step5. KEY_DPAD_DOWN from itemCount_-1.
     * @tc.expected: Selected unchanged.
     */
    pattern_->selected_ = pattern_->itemCount_ - 1;
    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), pattern_->itemCount_ - 1);
}

/**
 * @tc.name: SelectByKeyEvent002
 * @tc.desc: Test OnKeyEvent func about MoveIndexBySearch.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, SelectByKeyEvent002, TestSize.Level1)
{
    CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();

    /**
     * @tc.steps: step1. IsCombinationKey && KEY_UNKNOWN.
     * @tc.expected: Selected unchanged.
     */
    KeyEvent keyEvent = KeyEvent();
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_UNKNOWN;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step2. IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = { KeyCode::KEY_A, KeyCode::KEY_B };
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step3. !IsCombinationKey && IsLetterKey.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_B;
    keyEvent.pressedCodes = {};
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step4. Move to KEY_B again.
     * @tc.expected: Selected unchanged.
     */
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 1);

    /**
     * @tc.steps: step5. Move to front Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_A;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 0);

    /**
     * @tc.steps: step6. Move to back Index.
     * @tc.expected: Selected changed.
     */
    keyEvent.code = KeyCode::KEY_C;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 2);

    /**
     * @tc.steps: step7. !IsCombinationKey && IsNumberKey.
     * @tc.expected: Selected unchanged.
     */
    keyEvent.code = KeyCode::KEY_5;
    pattern_->OnKeyEvent(keyEvent);
    EXPECT_EQ(pattern_->GetSelected(), 2);
}

/**
 * @tc.name: PopupSelectByClick001
 * @tc.desc: Test OnListItemClick, Selected index will change with click
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, PopupSelectByClick001, TestSize.Level1)
{
    int32_t selected = -1;
    OnPopupSelectedEvent event = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetOnPopupSelected(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Show popupNode_
     */
    pattern_->MoveIndexByStep(1);

    /**
     * @tc.steps: step2. Click popupNode_ first item
     * @tc.expected: The selected changed
     */
    float clickIndex = 0;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(selected, clickIndex);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(selected, clickIndex);

    /**
     * @tc.steps: step3. Click popupNode_ second item
     * @tc.expected: The selected changed
     */
    clickIndex = 1;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(selected, clickIndex);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(selected, clickIndex);
}

/**
 * @tc.name: PopupSelectByClick003
 * @tc.desc: Test OnListItemClick, when Popup is long that can scroll, scroll down than Selected by click
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, PopupSelectByClick003, TestSize.Level1)
{
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    int32_t selected = -1;
    OnPopupSelectedEvent event = [&selected](int32_t selectedIndex) { selected = selectedIndex; };
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetMorePopupData2());
    model.SetOnPopupSelected(std::move(event));
    CreateDone();

    /**
     * @tc.steps: step1. Show popupNode_
     */
    pattern_->MoveIndexByStep(1);

    /**
     * @tc.steps: step2. Click popupNode_ first item
     * @tc.expected: The selected changed
     */
    auto stackNode = AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetLastChild());
    auto listNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto listPattern = listNode->GetPattern<ListPattern>();
    float clickIndex = 0;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(selected, clickIndex);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(selected, clickIndex);

    /**
     * @tc.steps: step3. Scroll down and Click popupNode_ last item
     * @tc.expected: The selected changed
     */
    listPattern->ScrollTo(100);
    FlushUITasks();
    EXPECT_TRUE(listPattern->IsAtBottom());

    clickIndex = 6;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(selected, clickIndex);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(selected, clickIndex);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: PopupTouch001
 * @tc.desc: Test OnPopupTouchDown.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, PopupTouch001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    pattern_->MoveIndexByStep(1);

    /**
     * @tc.steps: step1. Touch down popup
     */
    OnPopupTouchDown(TouchType::DOWN); // trigger OnPopupTouchDown
    EXPECT_TRUE(pattern_->isTouch_);

    /**
     * @tc.steps: step2. Touch move popup
     */
    OnPopupTouchDown(TouchType::MOVE);
    EXPECT_TRUE(pattern_->isTouch_);

    /**
     * @tc.steps: step3. Touch up popup
     */
    OnPopupTouchDown(TouchType::UP);
    EXPECT_FALSE(pattern_->isTouch_);
}

/**
 * @tc.name: PopupTouch002
 * @tc.desc: Test OnPopupTouchDown with hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerSelectTestNg, PopupTouch002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    pattern_->MoveIndexByStep(1);

    /**
     * @tc.steps: step1. Hover and Touch down popup
     */
    pattern_->OnPopupHover(true);
    EXPECT_TRUE(pattern_->isPopupHover_);
    OnPopupTouchDown(TouchType::DOWN); // trigger OnPopupTouchDown
    EXPECT_TRUE(pattern_->isTouch_);

    /**
     * @tc.steps: step2. Touch cancel popup
     */
    OnPopupTouchDown(TouchType::CANCEL);
    EXPECT_FALSE(pattern_->isTouch_);
    pattern_->OnPopupHover(false);
    EXPECT_FALSE(pattern_->isPopupHover_);
}
} // namespace OHOS::Ace::NG
