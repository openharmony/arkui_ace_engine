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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium';
import { abilityDelegatorRegistry, Driver, ON, MatchPattern } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const DELEGATOR: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const TAG = '[Sample_Event]';
const DOMAIN: number = 0xF811;
const BUNDLE_NAME = abilityDelegatorRegistry.getArguments().bundleName;
const WANT: Want = {
  bundleName: BUNDLE_NAME,
  abilityName: 'EntryAbility'
}

function sleep(time: number) {
  return new Promise<void>((resolve: Function) => setTimeout(resolve, time))
}

export default function indexTest() {
  describe('IndexTest', () => {
    it('InjectTouchEventTest', 0, async () => {
      hilog.info(DOMAIN, TAG, BUNDLE_NAME + ' test, begin');
      await DELEGATOR.startAbility(WANT);
      await sleep(300);

      // 拉起应用
      await DELEGATOR.getCurrentTopAbility().then((Ability: UIAbility) => {
        hilog.info(DOMAIN, TAG, BUNDLE_NAME + 'NormalLayout_001, get top ability');
        expect(Ability.context.abilityInfo.name).assertEqual('EntryAbility');
      })

      // Driver 初始化
      let driver = Driver.create();
      await driver.delayMs(1000);

      // 寻找按钮
      expect(await driver.findComponent(ON.text('点击获取时间判断页面可以响应：')) != undefined);
      // 按钮元素
      let staticLayoutCreate = await driver.findComponent(ON.text('测试InjectEvent'));
      await staticLayoutCreate.click();
      await driver.delayMs(300);
      expect(await driver.findComponent(ON.text('点击获取时间判断页面可以响应：')) == undefined);
    });
  })
}