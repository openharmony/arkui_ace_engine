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

export default async function panelCustomHeightTest() {
  /*
   * Panel组件 CustomHeight属性
   * 找到画面id为panelCustomHeight1,panelCustomHeight2,panelCustomHeight3的Panel组件
   * 找到画面文本为PanelCustomHeight1,PanelCustomHeight2,PanelCustomHeight3,PanelCustomHeight4的Button组件
   * 获取panel1的CustomHeight属性与期待值'50.00px'比对
   * 获取panel2的CustomHeight属性与期待值'50.00fp'比对
   * 获取panel3的CustomHeight属性与期待值'50.00vp'比对
   * 点击button1，变更panel1的CustomHeight属性值为 $r('app.string.length')
   * 获取panel1的CustomHeight属性与期待值 $r('app.string.length')比对
   * 点击button2，变更panel1的CustomHeight属性值为PanelHeight.WRAP_CONTENT
   * 获取panel1的CustomHeight属性与期待值PanelHeight.WRAP_CONTENT比对
   * 点击button3，变更panel1的CustomHeight属性值为'50.00lpx'
   * 获取panel1的CustomHeight属性与期待值'50.00lpx'比对
   * 点击button4，变更panel1的CustomHeight属性值为'50%'
   * 获取panel1的CustomHeight属性与期待值'50%'比对
   */
  defineTest('panelCustomHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelCustomHeightTestDemo running')

    let driver: Tester = Tester.create()
    let panel1: Component = await driver.findComponent(Matcher.create().id('panelCustomHeight1').enabled(true))
    let panel2: Component = await driver.findComponent(Matcher.create().id('panelCustomHeight2').enabled(true))
    let panel3: Component = await driver.findComponent(Matcher.create().id('panelCustomHeight3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PanelCustomHeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PanelCustomHeight2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('PanelCustomHeight3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('PanelCustomHeight4').enabled(true))

    let customHeight1: string = await panel1.getInspectorInfo()
    assertEqual('需要将Type设置为PanelType.CUSTOM时使用,但设置tpye为PanelType.CUSTOM画面会立刻崩掉', 0)
    assertEqual(JSON.parse(customHeight1).$attrs.customHeight, '50.00px')

    let customHeight2: string = await panel2.getInspectorInfo()
    assertEqual(JSON.parse(customHeight2).$attrs.customHeight, '50.00fp')

    let customHeight3: string = await panel3.getInspectorInfo()
    assertEqual(JSON.parse(customHeight3).$attrs.customHeight, '50.00vp')

    await button1.tap()
    let customHeight4: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(customHeight4).$attrs.customHeight, $r('app.string.length'))

    await button2.tap()
    let customHeight5: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(customHeight5).$attrs.customHeight, PanelHeight.WRAP_CONTENT)

    await button3.tap()
    let customHeight6: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(customHeight6).$attrs.customHeight, '50.00lpx')

    await button4.tap()
    let customHeight7: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(customHeight7).$attrs.customHeight, '50.00%')
  }, 0)
}