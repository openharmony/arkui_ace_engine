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

export default async function polylineAntiAliasTest() {
  /*
   * Polyline组件 antiAlias属性
   * 找到画面id为polylineAntiAlias的Polyline组件
   * 找到画面文本为PolylineAntiAlias的Button组件
   * 获取polyline的antiAlias属性与期待值判断是否为真
   * 点击button,变更polyline的antiAlias属性值为假
   * 获取polyline的antiAlias属性与期待值判断是否为假
   */
  defineTest('polylineAntiAliasTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("polylineAntiAliasTestDemo running")
    let driver: Tester = Tester.create()
    let polyline: Component = await driver.findComponent(Matcher.create().id('polylineAntiAlias').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PolylineAntiAlias').enabled(true))

    let antiAlias1: string = await polyline.getInspectorInfo()
    assertTrue(JSON.parse(antiAlias1).$attrs.antiAlias)

    await button.tap()
    let antiAlias2: string = await polyline.getInspectorInfo()
    assertFalse(JSON.parse(antiAlias2).$attrs.antiAlias)
  }, 0)
}