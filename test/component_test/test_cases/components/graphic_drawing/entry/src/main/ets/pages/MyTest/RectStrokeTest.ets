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

export default async function rectStrokeTest() {
  /*
   * Rect组件 stroke属性
   * 找到画面id为rectStroke1,rectStroke2的Rect组件
   * 找到画面文本为RectStroke1,RectStroke2的Button组件
   * 获取rect1的stroke属性与期待值Color.Red比对
   * 点击button1,变更rect1的stroke属性值为0xff0000
   * 获取rect1的stroke属性与期待值0xff0000比对
   * 获取rect2的stroke属性与期待值'rgb(255,0,0)'比对
   * 点击button2,变更rect2的stroke属性值为'#FF0000'
   * 获取rect2的stroke属性与期待值'#FF0000'比对
   */
  defineTest('rectStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rectStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let rect1: Component = await driver.findComponent(Matcher.create().id('rectStroke1').enabled(true))
    let rect2: Component = await driver.findComponent(Matcher.create().id('rectStroke2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('RectStroke1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('RectStroke2').enabled(true))

    let stroke1: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke.toLowerCase(), Color.Red)

    await button1.tap()
    let stroke2: string = await rect1.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke, '#FFFF0000')

    let stroke3: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke, '#FFFF0000')

    await button2.tap()
    let stroke4: string = await rect2.getInspectorInfo()
    assertEqual(JSON.parse(stroke4).$attrs.stroke, $r('app.color.color_red'))
  }, 0)
}