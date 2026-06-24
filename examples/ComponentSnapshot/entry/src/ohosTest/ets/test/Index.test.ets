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

const TAG = '[Sample_ComponentSnapshot]';
const DOMAIN = 0xF811;
const BUNDLE = 'ComponentSnapshot_';
const ONE_SECONDS_TIME = 1000;
const FIVE_SECONDS_TIME = 5000;

function sleep(time: number) {
  return new Promise<void>((resolve: Function) => setTimeout(resolve, time));
}

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
    })

    /**
     * @tc.number: OneTapScreenshotTest_001
     * @tc.name: One tap screenshot
     * @tc.desc: Test one tap screenshot
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('OneTapScreenshotTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'OneTapScreenshotTest_001, begin');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('ScrollSnapshot', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('Scroll Screenshot', MatchPattern.CONTAINS));
      await button_list.click();
      let button_search = await driver.findComponent(ON.text('One-Tap Screenshot', MatchPattern.CONTAINS));
      await button_search.click();
      await driver.delayMs(FIVE_SECONDS_TIME);
      let button_scroll = await driver.findComponent(ON.type('Scroll'));
      await button_scroll.click();
      await driver.delayMs(ONE_SECONDS_TIME);
      let button_cancel = await driver.findComponent(ON.text('Cancel'));
      await button_cancel.click();
      await driver.pressBack();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + 'OneTapScreenshotTest_001, end');
      done()
    })

    /**
     * @tc.number: ScrollSnapshotTest_001
     * @tc.name: Scroll snapshot
     * @tc.desc: Test scroll snapshot
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('ScrollSnapshotTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'ScrollSnapshotTest_001, start');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(FIVE_SECONDS_TIME);
      let driver = Driver.create();
      let button_root = await driver.findComponent(ON.text('ScrollSnapshot', MatchPattern.CONTAINS));
      await button_root.click();
      let button_list = await driver.findComponent(ON.text('Scroll Screenshot', MatchPattern.CONTAINS));
      await button_list.click();
      await driver.pressBack();
      await driver.pressBack();
      await driver.delayMs(ONE_SECONDS_TIME);
      hilog.info(DOMAIN, TAG, BUNDLE + 'ScrollSnapshotTest_001, end');
      done()
    })

    /**
     * @tc.number: GlobalSnapshotTest_001
     * @tc.name: Global snapshot
     * @tc.desc: Test global snapshot
     * @tc.size: MediumTest
     * @tc.type: Function
     * @tc.level Level 1
     */
    it('GlobalSnapshotTest_001', TestType.FUNCTION | Size.MEDIUMTEST | Level.LEVEL1, async (done: Function) => {
      hilog.info(DOMAIN, TAG, BUNDLE + 'GlobalSnapshotTest_001, start');
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      await sleep(ONE_SECONDS_TIME);
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('GlobalSnapshot', MatchPattern.CONTAINS));
      await button.click();
      await driver.pressBack();
      hilog.info(DOMAIN, TAG, BUNDLE + 'GlobalSnapshotTest_001, end');
      done()
    })
  })
}