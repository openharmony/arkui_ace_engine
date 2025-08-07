/*
 * Copyright (c) 2025 Hunan OpenValley Digital Industry Development Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';

const TAG = 'MarqueeBootcampTest';
const DELAY_SHORT = 1000; // 1秒延迟，用于等待页面加载或动画完成
const DELAY_LONG = 6000;  // 6秒延迟，用于等待较长时间的操作完成
/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function RelativeContainerStart(done: Function) {

  console.info('beforeAll begin');

  try {

    await delegator.startAbility({
      bundleName: 'cn.ohos.components',
      abilityName: 'EntryAbility'
    });

    await driver.delayMs(DELAY_LONG);

    let atomDisplays: Component = await driver.findComponent(ON.text('行列与堆叠'));
    await atomDisplays.click();
    await driver.delayMs(DELAY_SHORT);

    let scrollSearch: Component = await driver.findComponent(ON.text('相对布局/RelativeContainer'))
    await scrollSearch.click()
    await driver.delayMs(DELAY_SHORT);

    let buttons: Component[] = await driver.findComponents(ON.type('Button'));
    if (buttons.length < 2) {
      throw new Error('Not enough buttons found. Expected at least 2 buttons.');
    }

    if (!buttons[1]) {
      throw new Error('The second button (buttons[1]) is not available.');
    }
    await buttons[1].click()
    await driver.delayMs(DELAY_SHORT);

  } catch (err) {

    console.info(`beforeAll error: ${JSON.stringify(err)}`);

  }
  console.info(`beforeAll end`);

  done()
}
