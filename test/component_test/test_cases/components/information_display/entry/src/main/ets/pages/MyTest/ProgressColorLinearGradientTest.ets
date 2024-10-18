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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function progressColorLinearGradientTest() {
  /*
* Progress组件 Color属性
* 找到画面id为progressColorLinearGradient1,progressColorLinearGradient2的Progress组件
* 找到画面文本为ProgressColorLinearGradient1组件
* 获取progress1的Color属性与期待值[{ color: "#FFFF00AA", offset: 0.1 },{ color: "#ff254ff7", offset: 0.5 }]
* 获取progress2的Color属性与期待值[{ color: $r("app.color.progress_linear_gradient_color1"),offset: 0.1 },{ color: $r("app.color.progress_linear_gradient_color2"), offset: 0.5 }]比对
* 点击button1，变更progress1的Color.ColorStop[0].color属性值为[{ color: 0x0000ff, offset: '10px' },{ color: 0xffffff, offset: '15px' }]
* 获取progress1的Color属性与期待值[{ color: 0x0000ff, offset: '10px' },{ color: 0xffffff, offset: '15px' }]比对
*/
  defineTest('progressColorLinearGradientTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("progressColorLinearGradientTestDemo running")
    let driver: Tester = Tester.create()
    let progress1: Component =
      await driver.findComponent(Matcher.create().id('progressColorLinearGradient1').enabled(true))
    let progress2: Component =
      await driver.findComponent(Matcher.create().id('progressColorLinearGradient2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ProgressColorLinearGradient1').enabled(true))
    let colorLinearGradient1: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(colorLinearGradient1)
      .$attrs.progressGradientColor,
      '[{"color":"#FFFF00AA","offset":"0.100000"},{"color":"#FF254FF7","offset":"0.500000"}]')
    let colorLinearGradient2: string = await progress2.getInspectorInfo()
    assertEqual(JSON.parse(colorLinearGradient2)
      .$attrs.progressGradientColor,
      '[{"color":"#65EEC9A3","offset":"0.100000"},{"color":"#FFEF629F","offset":"0.500000"}]')
    await button1.tap()
    let colorLinearGradient3: string = await progress1.getInspectorInfo()
    assertEqual(JSON.parse(colorLinearGradient3)
      .$attrs.progressGradientColor,
      '[{"color":"#FFFF00AA","offset":"0.100000"},{"color":"#FF254FF7","offset":"0.500000"}]')
  }, 0)
}