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

import { abilityDelegatorRegistry, Driver, ON } from '@kit.TestKit';
import { Point, Component } from '@ohos.UiTest';

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

const TAG = 'SelectBootcamp'

export async function SelectStart(done: Function) {
  console.info('beforeAll begin');
  try {
    await delegator.startAbility({
      bundleName: 'cn.ohos.components',
      abilityName: 'EntryAbility'
    });
    await driver.delayMs(1500);
    console.info(TAG + 'SelectBootcamp001' + ' begin');
    let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
    let width0: Point = await ListItemGroups[0].getBoundsCenter()
    let width1: Point = await ListItemGroups[2].getBoundsCenter()
    await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
    await driver.delayMs(2000);
    let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
    await atomDisplays.click();
    await driver.delayMs(1000);
    let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
    let width: Point = await ListItems[0].getBoundsCenter()
    let width2: Point = await ListItems[6].getBoundsCenter()
    await driver.swipe(width.x, width2.y, width.x, width.y, 500)
    await driver.delayMs(1500);

    let scrollSearch: Component = await driver.findComponent(ON.text('下拉按钮/Select'))
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