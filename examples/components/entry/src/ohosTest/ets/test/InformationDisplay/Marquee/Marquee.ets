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

const TAG = 'MarqueeBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function MarqueeStart(done: Function) {
  try {

    await delegator.startAbility({
      bundleName: 'cn.ohos.components',
      abilityName: 'EntryAbility'
    });

    await driver.delayMs(10000);
    console.info(TAG + 'MarqueeBootcamp' + ' begin');

    let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
    let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
    let ListItemGroup2: Point = await ListItemGroup[4].getBoundsCenter()
    await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 500)
    await driver.delayMs(1000);


    let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
    await atomDisplays.click();
    await driver.delayMs(1000);

    let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
    let ListItemsPoint: Point = await ListItems[0].getBoundsCenter()
    let ListItemsPoint2: Point = await ListItems[2].getBoundsCenter()
    await driver.swipe(ListItemsPoint.x, ListItemsPoint2.y, ListItemsPoint.x, ListItemsPoint.y, 500)
    await driver.delayMs(1000);

    for (let i = 1; i < 4; i++) {
      let ListItems2: Array<Component> = await driver.findComponents(ON.type('ListItem'))
      let ListItems2Point: Point = await ListItems2[0].getBoundsCenter()
      let ListItems2Point2: Point = await ListItems2[5].getBoundsCenter()
      await driver.swipe(ListItems2Point.x, ListItems2Point2.y, ListItems2Point.x, ListItems2Point.y, 500)
      await driver.delayMs(1000);
    }


    let scrollSearch: Component = await driver.findComponent(ON.text('跑马灯/Marquee'))
    await scrollSearch.click()
    await driver.delayMs(1000);

    let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
    await Buttons[1].click()
    await driver.delayMs(1000);

    done()
  } catch (err) {

    console.info(`beforeAll error: ${JSON.stringify(err)}`);

  }
  console.info(`beforeAll end`);
}