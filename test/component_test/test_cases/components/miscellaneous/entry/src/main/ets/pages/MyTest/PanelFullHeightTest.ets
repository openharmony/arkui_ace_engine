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

export default async function panelFullHeightTest() {
  /*
   * Panel组件 FullHeight属性
   * 找到画面id为panelFullHeight的Panel组件
   * 找到画面文本为PanelFullHeight的Button组件
   * 获取panel的FullHeight属性与期待值'100.00vp'比对
   * 点击button，变更panel的FullHeight属性值为'120'
   * 获取panel的FullHeight属性与期待值'120.00vp'比对
   */
  defineTest('panelFullHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelFullHeightTestDemo running')
    let driver: Tester = Tester.create()
    let panel: Component = await driver.findComponent(Matcher.create().id('panelFullHeight').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('PanelFullHeight').enabled(true))
    let fullHeight1: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(fullHeight1).$attrs.fullHeight, '100.00vp')

    await button.tap()
    let fullHeight2: string = await panel.getInspectorInfo()
    assertEqual(JSON.parse(fullHeight2).$attrs.fullHeight, '120.00vp')
  }, 0)
}