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

import { Component, Driver, ON, Point } from '@ohos.UiTest';

import { abilityDelegatorRegistry } from '@kit.TestKit';

const TAG = 'TextAreaBootcamp'

export async function textAreaBeforeAll(done: Function,
  delegator: abilityDelegatorRegistry.AbilityDelegator, driver: Driver) {
  console.info('beforeAll begin');
  try {
    await delegator.startAbility({
      bundleName: 'cn.ohos.components',
      abilityName: 'EntryAbility'
    });
    await driver.delayMs(1500);
    console.info(TAG + 'TextAreaBootcamp001' + ' begin');

    let ListItemGroups: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
    let width0: Point = await ListItemGroups[0].getBoundsCenter()
    let width1: Point = await ListItemGroups[4].getBoundsCenter()
    await driver.swipe(width0.x, width1.y, width0.x, width0.y, 500)
    await driver.delayMs(2000);

    let atomDisplays: Component = await driver.findComponent(ON.text('文本与输入'));
    await atomDisplays.click();
    await driver.delayMs(2000);

    let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
    let width: Point = await ListItems[0].getBoundsCenter()
    let width2: Point = await ListItems[4].getBoundsCenter()
    await driver.swipe(width.x, width2.y, width.x, width.y, 500)
    await driver.delayMs(1000);

    let scrollSearch: Component = await driver.findComponent(ON.text('多行文本框/TextArea'))
    await scrollSearch.click()
    await driver.delayMs(1000);

    let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
    await Buttons[1].click()
    await driver.delayMs(5000);

  } catch (err) {

    console.info(`beforeAll error: ${JSON.stringify(err)}`);

  }
  console.info(`beforeAll end`);
  done();
}