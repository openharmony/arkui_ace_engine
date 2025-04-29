/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function StepperItemStatusTest() {
  /*
 * StepperItem组件 Status属性
 * 找到画面id为stepperItemStatus1的StepperItem组件
 * 找到画面文本为StepperItemStatus1,StepperItemStatus2、StepperItemStatus3的Button组件
 * 获取StepperItem1的status属性与期待值'ItemState.Normal'比对
 * 点击button1，变更StepperItem1的status属性值为'ItemState.Disabled'
 * 获取StepperItem1的status属性与期待值'ItemState.Disabled'比对
 * 点击button2，变更StepperItem2的status属性值为'ItemState.Skip'
 * 获取StepperItem2的status属性与期待值'ItemState.Skip'比对
 * 点击button3，变更StepperItem3的status属性值为'ItemState.Waiting'
 * 获取StepperItem3的status属性与期待值'ItemState.Waiting'比对
 */
  defineTest('NavRouterModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('NavRouterModeTestDemo running')
    let driver: Tester = Tester.create()
    let StepperItem1: Component = await driver.findComponent(Matcher.create().id('stepperItemStatus1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('StepperItemStatus1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('StepperItemStatus2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('StepperItemStatus3').enabled(true))
    let status1: string = await StepperItem1.getInspectorInfo()
    assertEqual(JSON.parse(status1).$attrs.status, 'ItemState.Normal')
    await button1.tap()
    let status2: string = await StepperItem1.getInspectorInfo()
    assertEqual(JSON.parse(status2).$attrs.status, 'ItemState.Disabled')
    await button2.tap()
    let status3: string = await StepperItem1.getInspectorInfo()
    assertEqual(JSON.parse(status3).$attrs.status, 'ItemState.Skip')
    await button3.tap()
    let status4: string = await StepperItem1.getInspectorInfo()
    assertEqual(JSON.parse(status4).$attrs.status, 'ItemState.Waiting')
  }, 0)
}