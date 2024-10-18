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

export default async function polylineStrokeTest() {
  /*
   * Polyline组件 stroke属性
   * 找到画面id为polylineStroke1,polylineStroke2的Polyline组件
   * 找到画面文本为PolylineStroke1,PolylineStroke2的Button组件
   * 获取polyline1的stroke属性与期待值0x0000ff比对
   * 点击button1,变更polyline1的stroke属性值为Color.Red
   * 获取polyline2的stroke属性与期待值'rgb(0,0,255)'比对
   * 点击button2,变更polyline2的stroke属性值为'#FF0000'
   * 获取polyline2的stroke属性与期待值'#FF0000'比对
   */
  defineTest('polylineStrokeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeTestDemo running")
    let driver: Tester = Tester.create()
    let polyline1: Component = await driver.findComponent(Matcher.create().id('polylineStroke1').enabled(true))
    let polyline2: Component = await driver.findComponent(Matcher.create().id('polylineStroke2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PolylineStroke1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PolylineStroke2').enabled(true))

    let stroke1: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(stroke1).$attrs.stroke, '#FF0000FF')
    await button1.tap()
    let stroke2: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(stroke2).$attrs.stroke.toLowerCase(), Color.Red)
    let stroke3: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(stroke3).$attrs.stroke, '#FF0000FF')
    await button2.tap()
    let stroke4: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(stroke4).$attrs.stroke, $r('app.color.color_red'))
  }, 0)
}