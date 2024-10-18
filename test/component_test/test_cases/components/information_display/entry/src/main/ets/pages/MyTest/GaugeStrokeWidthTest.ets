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

export default async function gaugeStrokeWidthTest() {
  /*
   * Gauge组件 StrokeWidth属性
   * 找到画面id为gaugeStrokeWidth1,gaugeStrokeWidth2的Gauge组件
   * 找到画面文本为GaugeStrokeWidth1,GaugeStrokeWidth2的Button组件
   * 获取gauge1的strokeWidth属性与期待值50比对
   * 获取gauge2的strokeWidth属性与期待值"40px"比对
   * 点击button1，变更strokeWidth3的strokeWidth的属性值为$r('app.integer.data_panel_strokeWidth')
   * 获取gauge1的strokeWidth属性与期待值$r('app.integer.data_panel_strokeWidth')比对
   * 点击button2，变更strokeWidth4的strokeWidth的属性值为-10
   * 获取gauge1的strokeWidth属性与期待值4比对
   */
  defineTest('gaugeStrokeWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gaugeStrokeWidthTestDemo running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeStrokeWidth1').enabled(true))
    let gauge2: Component = await driver.findComponent(Matcher.create().id('gaugeStrokeWidth2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('GaugeStrokeWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('GaugeStrokeWidth2').enabled(true))
    let strokeWidth1: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth1).$attrs.strokeWidth, '50.00vp')
    let strokeWidth2: string = await gauge2.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth2).$attrs.strokeWidth, "40.00px")
    await button1.tap()
    let strokeWidth3: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth3).$attrs.strokeWidth, $r('app.string.data_panel_strokeWidth'))
    await button2.tap()
    let strokeWidth4: string = await gauge1.getInspectorInfo()
    assertEqual(JSON.parse(strokeWidth4).$attrs.strokeWidth, '-10.00vp')
  }, 0)
}