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

export default async function lineStrokeTest() {
  /*
   * Line组件 stroke属性
   * 找到画面id为lineStroke1,lineStroke2的Line组件
   * 找到画面文本为LineStroke1,LineStroke2的Button组件
   * 获取line1的stroke属性与期待值'rgba(255, 100, 100)'比对
   * 点击button1，变更line1的stroke属性值为0xff0000
   * 获取line1的stroke属性与期待值0xff0000比对
   * 获取line2的stroke属性与期待值Color.Blue比对
   * 点击button2，变更line2的stroke属性值为$r('app.color.color_red')
   * 获取line2的stroke属性与期待值'#FF0000'比对
   */
  defineTest('lineStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("lineStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let line1: Component = await driver.findComponent(Matcher.create().id('lineStroke1').enabled(true))
    let line2: Component = await driver.findComponent(Matcher.create().id('lineStroke2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('LineStroke1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('LineStroke2').enabled(true))

    let stroke1: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke, '#FFFFFF00')
    await button1.tap()
    let stroke2: string = await line1.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke, '#FFFF0000')
    let stroke3: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke.toLowerCase(), Color.Blue)
    await button2.tap()
    let stroke4: string = await line2.getInspectorInfo()
    assertEqual(JSON.parse(stroke4).$attrs.stroke, $r('app.color.color_red'))
  }, 0)
}