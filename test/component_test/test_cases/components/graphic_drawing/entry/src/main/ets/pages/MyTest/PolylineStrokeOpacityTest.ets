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

export default async function polylineStrokeOpacityTest() {
  /*
   * Polyline组件 strokeOpacity属性
   * 找到画面id为polylineStrokeOpacity1,polylineStrokeOpacity2的Polyline组件
   * 找到画面文本为PolylineStrokeOpacity的Button组件
   * 获取polyline1的strokeOpacity属性与期待值0.0比对
   * 点击button,变更polyline1的strokeOpacity属性值为'10px'
   * 获取polyline1的strokeOpacity属性与期待值0.0比对
   * 获取polyline2的strokeOpacity属性与期待值'0.8'比对
   */
  defineTest('polylineStrokeOpacityTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeOpacityTestDemo running")
    let driver: Tester = Tester.create()
    let polyline1: Component = await driver.findComponent(Matcher.create().id('polylineStrokeOpacity1').enabled(true))
    let polyline2: Component = await driver.findComponent(Matcher.create().id('polylineStrokeOpacity2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineStrokeOpacity').enabled(true))

    let strokeOpacity1: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity1).$attrs.strokeOpacity, '0.000000')
    await button.tap()
    let strokeOpacity2: string = await polyline1.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity2).$attrs.strokeOpacity, '1.000000')
    let strokeOpacity3: string = await polyline2.getInspectorInfo()
    assertEqual(JSON.parse(strokeOpacity3).$attrs.strokeOpacity, $r('app.string.stroke_opacity'))
  }, 0)
}