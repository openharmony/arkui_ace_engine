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

export default async function ellipseStrokeTest() {
  /*
   * Ellipse组件 stroke属性
   * 找到画面id为ellipseStroke1,ellipseStroke2的Ellipse组件
   * 找到画面文本为EllipseStroke1,EllipseStroke2的Button组件
   * 获取ellipse1的stroke属性与期待值Color.Red比对
   * 点击button1，变更ellipse1的stroke属性值为0x0000ff
   * 获取ellipse1的stroke属性与期待值0x0000ff比对
   * 获取ellipse2的stroke属性与期待值'#FF0000'比对
   * 点击button2，变更ellipse2的stroke属性值为'rgb(0,0,255)'
   * 获取ellipse2的stroke属性与期待值'rgb(0,0,255)'比对
   */
  defineTest('ellipseStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("ellipseStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let ellipse1: Component = await driver.findComponent(Matcher.create().id('ellipseStroke1').enabled(true))
    let ellipse2: Component = await driver.findComponent(Matcher.create().id('ellipseStroke2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('EllipseStroke1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('EllipseStroke2').enabled(true))

    let stroke1: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke.toLowerCase(), Color.Red)

    await button1.tap()
    let stroke2: string = await ellipse1.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke, '#FF0000FF')

    let stroke3: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke, $r('app.color.color_red'))

    await button2.tap()
    let stroke4: string = await ellipse2.getInspectorInfo()
    assertEqual(JSON.parse(stroke4).$attrs.stroke, '#FF0000FF')
  }, 0)
}