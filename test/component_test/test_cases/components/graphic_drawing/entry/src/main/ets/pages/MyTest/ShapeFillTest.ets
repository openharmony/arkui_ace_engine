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

export default async function shapeFillTest() {
  /*
   * Shape组件 fill属性
   * 找到画面id为shapeFill1,shapeFill2,shapeFill3的Circle组件
   * 找到画面文本为ShapeFill的Button组件
   * 获取shape1的fill属性与期待值#FF317AF7比对
   * 点击button1,变更shape1的fill属性值为'rgb(0,255,0)'
   * 获取shape1的fill属性与期待值'#FF00FF00'比对
   * 获取shape2的fill属性与期待值Color.Blue比对
   * 获取shape3的fill属性与期待值$r('app.color.color_red')比对
   */
  defineTest('shapeFillTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("shapeFillTestDemo running")
    let driver: Tester = Tester.create()
    let shape1: Component = await driver.findComponent(Matcher.create().id('shapeFill1').enabled(true))
    let shape2: Component = await driver.findComponent(Matcher.create().id('shapeFill2').enabled(true))
    let shape3: Component = await driver.findComponent(Matcher.create().id('shapeFill3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ShapeFill').enabled(true))

    let fill1: string = await shape1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill, '#FF317AF7')

    await button.tap()
    let fill2: string = await shape1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill, '#FF00FF00')

    let fill3: string = await shape2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill.toLowerCase(), Color.Blue)

    let fill4: string = await shape3.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill, $r('app.color.color_red'))
  }, 0)
}