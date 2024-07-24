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
  assertContain,
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function rectRadiusTest() {
  /*
   * Rect组件 radius属性
   * 找到画面id为Circle1,Circle2的Rect组件
   * 找到画面文本为CircleFill1,CircleFill2的Button组件
   * 获取rect1的radius属性与期待值20比对
   * 点击button1,变更rect1的radius属性值为'50'
   * 获取rect2的radius属性与期待值[['40', '40'], ['20', ' 20'], ['40', ' 40'], ['20', '20']]比对
   * 点击button1,变更rect1的radius属性值为[['40', '40'], ['20', ' 20'], ['40', ' 40'], ['20', '20']]
   * 获取rect3的radius属性与期待值[[40, 40], [20, 20], [40, 40], [20, 20]]比对
   */
  defineTest('rectRadiusTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectRadiusTestDemo running")
    let driver: Tester = Tester.create()
    let rect1: Component = await driver.findComponent(Matcher.create().id('rectRadius1').enabled(true))
    let rect2: Component = await driver.findComponent(Matcher.create().id('rectRadius2').enabled(true))
    let rect3: Component = await driver.findComponent(Matcher.create().id('rectRadius3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('RectRadius').enabled(true))

    let radius1: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(radius1).$attrs.radius, 20)

    await button.tap()
    let radius2: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(radius2).$attrs.radius, '50')

    let radius3: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(radius3).$attrs.radius, [['40', '40'], ['20', ' 20'], ['40', ' 40'], ['20', '20']])

    let radius4: string = await rect3.getInspectorInfo()
    assertEqual(JSON.parse(radius4).$attrs.radius, [[40, 40], [20, 20], [40, 40], [20, 20]])
  }, 0)
}