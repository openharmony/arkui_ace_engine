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
import abilityDelegatorRegistry from '@ohos.app.ability.abilityDelegatorRegistry';
import { Driver, ON } from '@ohos.UiTest';
import { describe, expect, it } from '@ohos/hypium';
import Logger from '../utils/Logger';

const TAG = '[Sample_AccessibilityCustomCapi]';
const BUNDLE = 'MyApp_';
const DELAYMS_1S = 1000;
const DELAYMS_2S = 2000;

const bundleName = abilityDelegatorRegistry.getArguments().bundleName;

export default function abilityTest() {
  describe('abilityTest', () => {
    // Test to verify starting the EntryAbility within a specific bundle.
    // Logs test start/end and any startup errors. Signals completion.
    it(BUNDLE + 'StartAbility_001, begin', 0, async (done: Function) => {
      Logger.info(TAG, BUNDLE + 'StartAbility_001');
      let abilityDelegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
      try {
        await abilityDelegator.startAbility({
          bundleName: bundleName,
          abilityName: 'EntryAbility'
        });
      } catch (err) {
        Logger.info(TAG, `beforeAll exception = ${JSON.stringify(err)}`);
      }

      Logger.info(TAG, BUNDLE + 'StartAbility_001, end');
      done();
    });

    it('assertContain', 0, async () => {
      try {
        let driver = Driver.create();
        await driver.delayMs(DELAYMS_2S);
        await driver.assertComponentExist(ON.id('scene'));
        let sceneButton = await driver.findComponent(ON.id('scene'));
        await sceneButton.click();
        await driver.delayMs(DELAYMS_1S);
      } catch {
        expect().assertFail();
      }
    })
  });
}