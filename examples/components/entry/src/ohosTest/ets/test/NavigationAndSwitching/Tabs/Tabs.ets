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
import { abilityDelegatorRegistry, Driver, Component } from '@kit.TestKit';
import { ON } from '@ohos.UiTest';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()
const driver = Driver.create();

export async function TabsStart(done: Function) {
  await delegator.startAbility({
    bundleName: 'cn.ohos.components',
    abilityName: 'EntryAbility'
  });
  await driver.delayMs(4500);

  let atomNavigates: Component = await driver.findComponent(ON.text('导航与切换'));
  await atomNavigates.click();
  await driver.delayMs(3500);

  let scrollSearch: Component = await driver.findComponent(ON.text('页签容器/Tabs'))
  await scrollSearch.click()
  await driver.delayMs(3500);

  let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
  await Buttons[1].click()
  await driver.delayMs(3500);
  done();
}