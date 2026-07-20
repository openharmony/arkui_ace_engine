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

import { describe, beforeAll, it, expect, Level, Size, TestType } from '@ohos/hypium'
// 导入测试依赖kit
import { abilityDelegatorRegistry, Driver, ON, MouseButton, Component, MatchPattern } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let abilityDelegator: abilityDelegatorRegistry.AbilityDelegator;
abilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
let want: Want;

const TAG = '[Sample_NdkAddInteractionEvent]';
const DOMAIN = 0xF811;
const BUNDLE = 'NdkAddInteractionEvent_';
const ONE_SECONDS_TIME = 1000;

function sleep(time: number) {
  return new Promise<void>((resolve: Function) => setTimeout(resolve, time));
}

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
    })

    /**
     * @tc.number: NormalTextListTest_001
     * @tc.name: Normal text list
     * @tc.desc: Test normal text list
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('NormalTextListTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'NormalTextListTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('NormalTextList', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'NormalTextListTest_001, end');
      done();
    })

    /**
     * @tc.number: BindGestureEventTest_001
     * @tc.name: Bind gesture event
     * @tc.desc: Test bind gesture event
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('BindGestureEventTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'BindGestureEventTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('BindGestureEvent', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'BindGestureEventTest_001, end');
      done();
    })

    /**
     * @tc.number: ComponentListenEventTest_001
     * @tc.name: Component listen event
     * @tc.desc: Test component listen event
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('ComponentListenEventTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'ComponentListenEventTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('ComponentListenEvent', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'ComponentListenEventTest_001, end');
      done();
    })

    /**
     * @tc.number: LongPressAndFlickTest_001
     * @tc.name: Long pressAnd flick
     * @tc.desc: Test long pressAnd flick
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('LongPressAndFlickTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'LongPressAndFlickTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('LongPressAndFlick', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'LongPressAndFlickTest_001, end');
      done();
    })

    /**
     * @tc.number: LongPressAndSwipeTest_001
     * @tc.name: Long press and swipe
     * @tc.desc: Test long press and swipe
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('LongPressAndSwipeTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'LongPressAndSwipeTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('LongPressAndSwipe', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'LongPressAndSwipeTest_001, end');
      done();
    })

    /**
     * @tc.number: SwipeAndPinchExclusiveTest_001
     * @tc.name: Swipe and pinch exclusive
     * @tc.desc: Test swipe and pinch exclusive
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('SwipeAndPinchExclusiveTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'SwipeAndPinchExclusiveTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('SwipeAndPinchExclusive', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('ShowNativeUI', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'SwipeAndPinchExclusiveTest_001, end');
      done();
    })
  })
}