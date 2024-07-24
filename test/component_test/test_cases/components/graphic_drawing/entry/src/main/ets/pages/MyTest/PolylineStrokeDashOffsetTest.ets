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

export default async function polylineStrokeDashOffsetTest() {
  /*
   * Polyline组件 strokeDashOffset属性
   * 找到画面id为polylineStrokeDashOffset的Polyline组件
   * 找到画面文本为PolylineStrokeDashOffset的Button组件
   * 获取polyline的strokeDashOffset属性与期待值10.00vp比对
   * 点击button,变更polyline的strokeDashOffset属性值为'-5'
   * 获取polyline的strokeDashOffset属性与期待值'-5.00vp'比对
   */
  defineTest('polylineStrokeDashOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeDashOffsetTestDemo running")
    let driver: Tester = Tester.create()
    let polyline: Component = await driver.findComponent(Matcher.create().id('polylineStrokeDashOffset').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineStrokeDashOffset').enabled(true))

    let strokeDashOffset1: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset1).$attrs.strokeDashOffset, '10.00vp')

    await button.tap()
    let strokeDashOffset2: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeDashOffset2).$attrs.strokeDashOffset, '-5.00vp')
  }, 0)
}