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

export default async function pathStrokeTest() {
  /*
   * Path组件 stroke属性
   * 找到画面id为pathStroke1,pathStroke2的Path组件
   * 找到画面文本为PathStroke1,PathStroke2的Button组件
   * 获取path1的stroke属性与期待值Color.Blue比对
   * 点击button1，变更path1的stroke属性值为'rgb(0,0,255)'
   * 获取path1的stroke属性与期待值'rgb(0,0,255)'比对
   * 获取path2的stroke属性与期待值0x0000ff比对
   * 点击button2，变更path2的stroke属性值为'#FF0000'
   * 获取path2的stroke属性与期待值'#FF0000'比对
   */
  defineTest('pathStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("pathStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let path1: Component = await driver.findComponent(Matcher.create().id('pathStroke1').enabled(true))
    let path2: Component = await driver.findComponent(Matcher.create().id('pathStroke2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PathStroke1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PathStroke2').enabled(true))

    let stroke1: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke.toLowerCase(), Color.Red)

    await button1.tap()
    let stroke2: string = await path1.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke, '#FF0000FF')

    let stroke3: string = await path2.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke, '#FF0000FF')

    await button2.tap()
    let stroke4: string = await path2.getInspectorInfo()
    assertEqual(JSON.parse(stroke4).$attrs.stroke, $r('app.color.color_red'))
  }, 0)
}