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

export default async function polylineStrokeMiterLimitTest() {
  /*
   * Polyline组件 strokeMiterLimit属性
   * 找到画面id为polylineStrokeMiterLimit的Polyline组件
   * 找到画面文本为PolylineStrokeMiterLimit的Button组件
   * 获取polyline的strokeMiterLimit属性与期待值5比对
   * 点击button,变更polyline的strokeMiterLimit属性值为'4'
   * 获取polyline的strokeMiterLimit属性与期待值'4'比对
   */
  defineTest('polylineStrokeMiterLimitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineStrokeMiterLimitTestDemo running")
    let driver: Tester = Tester.create()
    let polyline: Component = await driver.findComponent(Matcher.create().id('polylineStrokeMiterLimit').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineStrokeMiterLimit').enabled(true))

    let strokeMiterLimit1: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit1).$attrs.strokeMiterLimit, '5.000000')

    await button.tap()
    let strokeMiterLimit2: string = await polyline.getInspectorInfo()
    assertEqual(JSON.parse(strokeMiterLimit2).$attrs.strokeMiterLimit, '4.000000')
  }, 0)
}