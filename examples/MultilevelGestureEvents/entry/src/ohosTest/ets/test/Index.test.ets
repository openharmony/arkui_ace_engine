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

const TAG = '[Sample_MultilevelGestureEvents]';
const DOMAIN = 0xF811;
const BUNDLE = 'MultilevelGestureEvents_';

function sleep(time: number) {
  return new Promise<void>((resolve: Function) => setTimeout(resolve, time));
}

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(1000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    /**
     * @tc.number: TouchEvent_001
     * @tc.name: Touch event
     * @tc.desc: Test touch event
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('TouchEvent_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'TouchEvent_001, begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('TouchEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.delayMs(1000);
      hilog.info(DOMAIN, TAG, BUNDLE + 'TouchEvent_001, end');
      done();
    })

    /**
     * @tc.number: GesturesEvents_001
     * @tc.name: Gestures events
     * @tc.desc: Test gestures events
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('GesturesEvents_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'GesturesEvents_001, begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('GesturesEvents', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.delayMs(1000);
      hilog.info(DOMAIN, TAG, BUNDLE + 'GesturesEvents_001, end');
      done();
    })

    /**
     * @tc.number: CustomEvent_001
     * @tc.name: Custom event
     * @tc.desc: Test custom event
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('CustomEvent_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'CustomEvent_001, begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('CustomEvent', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.delayMs(1000);
      hilog.info(DOMAIN, TAG, BUNDLE + 'CustomEvent_001, end');
      done();
    })

    /**
     * @tc.number: OverlayManager_001
     * @tc.name: Overlay manager
     * @tc.desc: Test overlay manager
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('OverlayManager_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'OverlayManager_001, begin');
      let driver = Driver.create();
      let button_list = await driver.findComponent(ON.text('OverlayManager', MatchPattern.CONTAINS));
      expect(button_list === null).assertFalse();
      await button_list.click();
      await driver.pressBack();
      await driver.delayMs(1000);
      hilog.info(DOMAIN, TAG, BUNDLE + 'OverlayManager_001, end');
      done();
    })
  })
}