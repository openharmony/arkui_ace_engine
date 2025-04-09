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

import { abilityDelegatorRegistry, Driver } from '@kit.TestKit';
import { Component, ON, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

const TAG = 'TextBootcamp'

export async function TextStart(done: Function) {
  console.info('beforeAll begin');
  try {
    await delegator.startAbility({
      bundleName: 'cn.ohos.components',
      abilityName: 'EntryAbility'
    });
    await driver.delayMs(1500);
    console.info(TAG + 'TextBootcamp001' + ' begin');
    let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
    let width0: Point = await ListItemGroups[0].getBoundsCenter()
    let width1: Point = await ListItemGroups[4].getBoundsCenter()
    await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
    await driver.delayMs(2000);

    let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
    await atomDisplays.click();
    await driver.delayMs(2000);

    let scrollSearch: Component = await driver.findComponent(ON.text('文本显示/Text'))
    await scrollSearch.click()
    await driver.delayMs(1000);

    let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
    await Buttons[1].click()
    await driver.delayMs(1000);

  } catch (err) {

    console.info(`beforeAll error: ${JSON.stringify(err)}`);

  }
  console.info(`beforeAll end`);
  done();
}