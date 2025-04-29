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
import { assertEqual, assertTrue, assertFalse } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function linearGradientTest_one() {
  /*
  * 使用List组件 LinearGradient属性
  * 找到画面id为listLinearGradient1，listLinearGradient2 的List组件
  * 获取 listLinearGradient1 的 LinearGradient.angle 属性与期待值 '90.00px' 比对
  * 获取 listLinearGradient1 的 LinearGradient.repeating 属性与期待值 False 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[0][0] 属性与期待值 '#FFFF0000' 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[0][1] 属性与期待值 '0.200000' 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[1][0] 属性与期待值 '#FF0000FF' 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[1][1] 属性与期待值 '0.300000' 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[2][0] 属性与期待值
  * $r('sys.color.ohos_id_color_text_secondary_dark') 比对
  * 获取 listLinearGradient1 的 LinearGradient.colors[2][1] 属性与期待值 '0.500000' 比对
  * 获取 listLinearGradient2 的 LinearGradient.angle 属性与期待值 '180.00px' 比对
  * 获取 listLinearGradient2 的 LinearGradient.repeating 属性与期待值 true 比对
  * 获取 listLinearGradient2 的 LinearGradient.colors[0][0] 属性与期待值 Color.Red 比对
  * 获取 listLinearGradient2 的 LinearGradient.colors[0][1] 属性与期待值 '1.000000' 比对
  * 获取 listLinearGradient2 的 LinearGradient.direction 属性与期待值 'GradientDirection.Left' 比对
  */
  defineTest('linearGradientTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('linearGradientTest_oneDemo running')
    let driver: Tester = Tester.create()
    let listLinearGradient1: Component =
      await driver.findComponent(Matcher.create().id('listLinearGradient1').enabled(true))
    let listLinearGradient2: Component =
      await driver.findComponent(Matcher.create().id('listLinearGradient2').enabled(true))
    let linearGradient1: string = await listLinearGradient1.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.angle, '90.00px')
    assertFalse(JSON.parse(linearGradient1).$attrs.linearGradient.repeating)
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[0][0], '#FFFF0000')
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[0][1], '0.200000')
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[1][0], '#FF0000FF')
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[1][1], '0.300000')
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[2][0],
      $r('sys.color.ohos_id_color_text_secondary_dark'))
    assertEqual(JSON.parse(linearGradient1).$attrs.linearGradient.colors[2][1], '0.500000')

    let linearGradient2: string = await listLinearGradient2.getInspectorInfo()
    assertEqual(JSON.parse(linearGradient2).$attrs.linearGradient.angle, '180.00px')
    assertTrue(JSON.parse(linearGradient2).$attrs.linearGradient.repeating)
    assertEqual(JSON.parse(linearGradient2)
      .$attrs
      .linearGradient
      .colors[0][0]
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(linearGradient2).$attrs.linearGradient.colors[0][1], '1.000000')
    assertEqual(JSON.parse(linearGradient2).$attrs.linearGradient.direction, 'GradientDirection.Left')
  }, 0)
}