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

export default async function panelTypeTest() {
  /*
   * Panel组件 Type属性
   * 找到画面id为panelType1,panelType2的Panel组件
   * 找到画面文本为PanelType1,PanelType2的Button组件
   * 获取panel1的Type属性与期待值PanelType.CUSTOM比对
   * 获取panel2的Type属性与期待值PanelType.Minibar比对
   * 点击button1，变更panel1的Type属性值为PanelType.Foldable
   * 获取panel1的Type属性与期待值PanelType.Foldable比对
   * 点击button2，变更panel1的Type属性值为PanelType.Temporary
   * 获取panel1的Type属性与期待值PanelType.Temporary比对
   */
  defineTest('panelModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelModeTestDemo running')

    let driver: Tester = Tester.create()
    let panel1: Component = await driver.findComponent(Matcher.create().id('panelType1').enabled(true))
    let panel2: Component = await driver.findComponent(Matcher.create().id('panelType2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PanelType1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PanelType2').enabled(true))

    let type1: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'PanelType.CUSTOM')

    let type2: string = await panel2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'PanelType.Minibar')

    await button1.tap()
    let type3: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'PanelType.Foldable')

    await button2.tap()
    let type4: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(type4).$attrs.type, 'PanelType.Temporary')
  }, 0)
}