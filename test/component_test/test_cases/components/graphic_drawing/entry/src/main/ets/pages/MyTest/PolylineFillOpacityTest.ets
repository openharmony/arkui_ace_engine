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

import { assertEqual, assertContain, assertFalse, assertTrue } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function polylineFillOpacityTest() {
  /*
   * Polyline组件 fillOpacity属性
   * 找到画面id为polylineFillOpacity1,polylineFillOpacity2的Polyline组件
   * 找到画面文本为PolylineFillOpacity的Button组件
   * 获取polyline1的fillOpacity属性与期待值0.0比对
   * 获取polyline2的fillOpacity属性与期待值'0.000000'比对
   * 点击button,变更polyline2的fillOpacity属性值为'10px'
   * 获取polyline2的fillOpacity属性与期待值'1.000000'比对
   */
  defineTest('polylineFillOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineFillOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let polyline1: Component = await driver.findComponent(Matcher.create().id('polylineFillOpacity1').enabled(true))
    let polyline2: Component = await driver.findComponent(Matcher.create().id('polylineFillOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineFillOpacity').enabled(true))

    let fillOpacity1: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity1).$attrs.fillOpacity, '0.000000')

    await button.tap()
    let fillOpacity3: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity3).$attrs.fillOpacity, '1.000000')

    let fillOpacity2: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(fillOpacity2).$attrs.fillOpacity, $r('app.string.fill_opacity'))
  }, 0)
}