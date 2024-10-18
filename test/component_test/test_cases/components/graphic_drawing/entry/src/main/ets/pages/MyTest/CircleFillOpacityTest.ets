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

export default async function circleFillOpacityTest() {
  /*
   * Circle组件 FillOpacity属性
   * 找到画面id为circleFillOpacity1,circleFillOpacity2的Circle组件
   * 找到画面文本为CircleFill1,CircleFill2的Button组件
   * 获取circle1的fillOpacity属性与期待值0.000000比对
   * 点击button1，变更circle1的fillOpacity属性值为$r('app.string.fill_opacity')
   * 获取circle1的fillOpacity属性与期待值0.800000比对
   * 获取circle2的fillOpacity属性与期待值0.200000比对
   * 点击button2，变更circle2的fillOpacity属性值为'10px'
   * 获取circle2的fillOpacity属性与期待值1.000000比对
   */
  defineTest('circleFillOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("circleFillOpacityTestDemo running")

    let driver: Tester = Tester.create()
    let circle1: Component = await driver.findComponent(Matcher.create().id('circleFillOpacity1').enabled(true))
    let circle2: Component = await driver.findComponent(Matcher.create().id('circleFillOpacity2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('CircleFillOpacity1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('CircleFillOpacity2').enabled(true))

    let fillOpacity1: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '0.000000')
    await button1.tap()
    let fillOpacity2: string = await circle1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, $r('app.string.fill_opacity'))
    let fillOpacity3: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, '0.200000')
    await button2.tap()
    let fillOpacity4: string = await circle2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity4).$attrs.fillOpacity, '1.000000')
  }, 0)
}