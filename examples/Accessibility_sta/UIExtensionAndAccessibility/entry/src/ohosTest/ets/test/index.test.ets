'use static';
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { describe, it, expect, beforeAll, Level } from '@ohos/hypium';
import UIAbility from '@ohos.app.ability.UIAbility';
import Want from '@ohos.app.ability.Want';
import abilityDelegatorRegistry from '@ohos.app.ability.abilityDelegatorRegistry';
import { Driver, ON, MatchPattern } from '@ohos.UiTest';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

function sleep(time: number) {
  return new Promise<void>((resolve: Function) => setTimeout(resolve, time))
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
     * @tc.number UiTest_001
     * @tc.name testUIExtensionComponent
     * @tc.desc 测试UIExtensionComponent
     * @tc.level: Level 1
     */
    it('testUIExtensionComponent', Level.LEVEL1, async (done: Function) => {
      console.info('uitest: testUIExtensionComponent begin');
      let driver = Driver.create();
      let buttonComponent = await driver.findComponent(ON.text('UIExtensionComponent', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      buttonComponent = await driver.findComponent(ON.text('使用 UIExtensionComponent 组件', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      await sleep(1000);
      let abilityComponent = await driver.findComponent(ON.text('UIExtensionAbility', MatchPattern.EQUALS));
      expect(abilityComponent === null).assertFalse();
      buttonComponent = await driver.findComponent(ON.text('terminate', MatchPattern.EQUALS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      await sleep(1000);
      abilityComponent = await driver.findComponent(ON.text('UIExtensionAbility', MatchPattern.EQUALS));
      expect(abilityComponent === null).assertTrue();

      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testUIExtensionComponent end');
      done();
    })

    /**
     * @tc.number UiTest_002
     * @tc.name testEmbeddedComponent
     * @tc.desc 测试EmbeddedComponent
     * @tc.level: Level 1
     */
    it('testEmbeddedComponent', Level.LEVEL1, async (done: Function) => {
      console.info('uitest: testEmbeddedComponent begin');
      let driver = Driver.create();
      let buttonComponent = await driver.findComponent(ON.text('EmbeddedComponent', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      buttonComponent = await driver.findComponent(ON.text('使用 EmbeddedComponent 组件', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();

      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testEmbeddedComponent end');
      done();
    })

    /**
     * @tc.number UiTest_003
     * @tc.name testIsolatedComponent
     * @tc.desc 测试IsolatedComponent
     * @tc.level: Level 1
     */
    it('testIsolatedComponent', Level.LEVEL1, async (done: Function) => {
      console.info('uitest: testIsolatedComponent begin');
      let driver = Driver.create();
      let buttonComponent = await driver.findComponent(ON.text('IsolatedComponent', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      buttonComponent = await driver.findComponent(ON.text('使用 IsolatedComponent 组件', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();

      await driver.pressBack();
      await driver.pressBack();
      console.info('uitest: testIsolatedComponent end');
      done();
    })

    /**
     * @tc.number UiTest_004
     * @tc.name testAccessibility
     * @tc.desc 测试无障碍
     * @tc.level: Level 1
     */
    it('testAccessibility', Level.LEVEL1, async (done: Function) => {
      console.info('uitest: testAccessibility begin');
      let driver = Driver.create();
      let buttonComponent = await driver.findComponent(ON.text('ArkUI 无障碍能力', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();

      buttonComponent = await driver.findComponent(ON.text('使用无障碍属性 1', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      await driver.pressBack();

      buttonComponent = await driver.findComponent(ON.text('使用无障碍属性 2', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      await driver.pressBack();

      buttonComponent = await driver.findComponent(ON.text('使用无障碍属性 3', MatchPattern.CONTAINS));
      expect(buttonComponent === null).assertFalse();
      await buttonComponent.click();
      await driver.pressBack();

      await driver.pressBack();
      console.info('uitest: testAccessibility end');
      done();
    })
  })
}