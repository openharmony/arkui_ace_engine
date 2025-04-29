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

export default async function polylineStrokeDashArrayTest() {
  /*
   * Polyline组件 strokeDashArray属性
   * 找到画面id为polylineStrokeDashArray的Polyline组件
   * 找到画面文本为PolylineStrokeDashArray的Button组件
   * 获取polyline的strokeDashArray属性与期待值5比对
   * 点击button,变更polyline的strokeDashArray属性值为10
   * 获取polyline的strokeDashArray属性与期待值10比对
   */
  defineTest('polylineStrokeDashArrayTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeDashArrayTestDemo running")
    let driver: Tester = Tester.create()
    let polyline: Component = await driver.findComponent(Matcher.create().id('polylineStrokeDashArray').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineStrokeDashArray').enabled(true))

    let strokeDashArray1: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray1).$attrs.strokeDashArray[0], '5.00vp')

    await button.tap()
    let strokeDashArray2: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashArray2).$attrs.strokeDashArray[0], '10.00vp')
  }, 0)
}