/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

import hilog from '@ohos.hilog';
import { afterAll, afterEach, beforeAll, beforeEach, describe, it } from '@ohos/hypium';
import AbilityDelegatorRegistry from '@ohos.app.ability.abilityDelegatorRegistry';
import { Driver, ON } from '@ohos.UiTest';

const driver = Driver.create();
let abilityDelegatorRegistry = AbilityDelegatorRegistry.getAbilityDelegator();

//通过id验证有没有这个组件 有的话点击一下
async function checkButtonAndClickWithID(text: string, delayTime: number = 3000) {
  let idName = text;
  await driver.assertComponentExist(ON.id(idName));
  let button = await driver.findComponent(ON.id(idName));
  await button.click();
  if (delayTime > 0) {
    await driver.delayMs(delayTime);
  }
}

async function pressBack() {
  await driver.pressBack();
  await driver.delayMs(3000);
}

export default function stateTest() {
  describe('StateTest', () => {
    beforeAll(() => {

    })
    beforeEach(() => {

    })
    afterEach(() => {

    })
    afterAll(() => {

    })
    /**
     * 拉起应用
     */
    it('Benchmark_StartAbility_001', 0, async (done: Function) => {
      hilog.info(0xF811, 'testTag', 'StartAbility_001 begin');
      try {
        await abilityDelegatorRegistry.startAbility({
          bundleName: 'cn.openharmony.benchmarksample',
          abilityName: 'EntryAbility'
        });
        done();
      } catch (err) {
        done();
      }
      hilog.info(0xF811, 'testTag', 'StartAbility_001 end');
    })
    // 点击首页@Track
    it('TrackBenchMarkTest', 0, async () => {
      await driver.delayMs(3000);
      await checkButtonAndClickWithID('@Track')
      //读写@Track装饰的string类型
      await checkButtonAndClickWithID('TrackStringSample');
      await checkButtonAndClickWithID('changeUITimeTaken');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      //读写@Track装饰的string[]类型
      await checkButtonAndClickWithID('TrackStringArrSample');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      //读写@Track装饰的number类型
      await checkButtonAndClickWithID('TrackNumberSample');
      await checkButtonAndClickWithID('changeUITimeTaken');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      //读写@Track装饰的number[]类型
      await checkButtonAndClickWithID('TrackNumberArrSample');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      //读写@Track装饰的boolean类型
      await checkButtonAndClickWithID('TrackBooleanSample');
      await checkButtonAndClickWithID('changeUITimeTaken');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      //读写@Track装饰的boolean[]类型
      await checkButtonAndClickWithID('TrackBooleanArrSample');
      await checkButtonAndClickWithID('getStateTimeTaken');
      await checkButtonAndClickWithID('setStateTimeTaken');
      await pressBack();
      await pressBack(); //返回首页
    })
  })
}