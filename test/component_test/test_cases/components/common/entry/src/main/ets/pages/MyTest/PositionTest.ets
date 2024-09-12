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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function positionTest() {
  /*
* position 通用属性
* 找到画面id为 relativeContainerPosition1 的组件
* 找到画面文本为 ButtonPosition1 ButtonPosition2 按钮
* 获取 relativeContainerPosition1 的 position.x 属性与期望值 '1.00vp' 比对
* 获取 relativeContainerPosition1 的 position.y 属性与期望值 '1.00vp' 比对
* 点击 button1 变更 relativeContainerPosition1 的属性
* 获取 relativeContainerPosition1 的 position.x 属性与期望值 '2.00vp' 比对
* 获取 relativeContainerPosition1 的 position.y 属性与期望值 '2.00vp' 比对
* 点击 button2 变更 relativeContainerPosition1 的属性
* 获取 relativeContainerPosition1 的 position.x 属性与期望值 $r("app.string.common_value_one") 比对
* 获取 relativeContainerPosition1 的 position.y 属性与期望值 $r("app.string.common_value_one") 比对
* */
  defineTest('positionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('positionTestDemo running')
    let driver: Tester = Tester.create()
    let relativeContainerPosition1: Component =
      await driver.findComponent(Matcher.create().id('relativeContainerPosition1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ButtonPosition1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ButtonPosition2').enabled(true))
    let position1: string = await relativeContainerPosition1.getInspectorInfo()
    assertEqual(JSON.parse(position1)
      .$attrs
      .position
      .x, '1.00vp')
    assertEqual(JSON.parse(position1)
      .$attrs
      .position
      .y, '1.00vp')

    await button1.tap()
    let position2: string = await relativeContainerPosition1.getInspectorInfo()
    assertEqual(JSON.parse(position2)
      .$attrs
      .position
      .x, '2.00vp')
    assertEqual(JSON.parse(position2)
      .$attrs
      .position
      .y, '2.00vp')

    await button2.tap()
    let position3: string = await relativeContainerPosition1.getInspectorInfo()
    assertEqual(JSON.parse(position3)
      .$attrs
      .position
      .x, $r("app.string.common_value_one"))
    assertEqual(JSON.parse(position3)
      .$attrs
      .position
      .y, $r("app.string.common_value_one"))
  }, 0)
}