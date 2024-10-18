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
} from '@ohos.arkui.componentTest'

export default async function polylineFillTest() {
  /*
   * Polyline组件 fill属性
   * 找到画面id为polylineFill1,polylineFill2的Polyline组件
   * 找到画面文本为PolylineFill1,PolylineFill2的Button组件
   * 获取polyline1的fill属性与期待值0xff0000比对
   * 点击button1,变更polyline1的fill属性值为Color.Blue
   * 获取polyline1的fill属性与期待值Color.Blue比对
   * 获取polyline2的fill属性与期待值'rgba(0, 0,255)'比对
   * 点击button2,变更polyline2的fill属性值为'#FF0000'
   * 获取polyline2的fill属性与期待值'#FF0000'比对
   */
  defineTest('polylineFillTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineFillTestDemo running")
    let driver: Tester = Tester.create()
    let polyline1: Component = await driver.findComponent(Matcher.create().id('polylineFill1').enabled(true))
    let polyline2: Component = await driver.findComponent(Matcher.create().id('polylineFill2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PolylineFill1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PolylineFill2').enabled(true))

    let fill1: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(fill1).$attrs.fill, '#FFFF0000')

    await button1.tap()
    let fill2: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(fill2).$attrs.fill.toLowerCase(), Color.Blue)

    let fill3: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(fill3).$attrs.fill, '#FF000000')

    await button2.tap()
    let fill4: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(fill4).$attrs.fill, $r('app.color.color_red'))
  }, 0)
}