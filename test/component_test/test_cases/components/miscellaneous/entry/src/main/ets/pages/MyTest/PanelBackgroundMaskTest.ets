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

export default async function panelBackgroundMaskTest() {
  /*
   * Panel组件 BackgroundMask属性
   * 找到画面id为panelBackgroundMask1,panelBackgroundMask2的Panel组件
   * 找到画面文本为PanelBackgroundMask1,PanelBackgroundMask2的Button组件
   * 获取panel1的BackgroundMask属性与期待值Color.Blue比对
   * 获取panel2的BackgroundMask属性与期待值0xff8000比对
   * 点击button1，变更panel1的Color属性值为'rgb(255, 100, 255)'
   * 获取panel1的Color属性与期待值'rgb(255, 100, 255)'比对
   * 点击button2，变更panel1的Color属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取panel1的Color属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('panelBackgroundMaskTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('panelBackgroundMaskTestDemo running')
    let driver: Tester = Tester.create()
    let panel1: Component = await driver.findComponent(Matcher.create().id('panelBackgroundMask1').enabled(true))
    let panel2: Component = await driver.findComponent(Matcher.create().id('panelBackgroundMask2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('PanelBackgroundMask1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('PanelBackgroundMask2').enabled(true))

    let backgroundMask1: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundMask1).$attrs.backgroundMask, Color.Blue)

    let backgroundMask2: string = await panel2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundMask2).$attrs.backgroundMask, 0xff8000)

    await button1.tap()
    let backgroundMask3: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundMask3).$attrs.backgroundMask, 'rgb(255, 100, 255)')

    await button2.tap()
    let backgroundMask4: string = await panel1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundMask4).$attrs.backgroundMask, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}