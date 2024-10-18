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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function bindContextMenuTest_two() {
  /*
   * bindContextMenu属性
   * 获取 id 为 symbolGlyphBindContextMenu4 的 symbolGlyph 组件
   * 获取文本为 bindContextMenu1 bindContextMenu2 bindContextMenu3
   * bindContextMenu4 bindContextMenu5 的 button 按钮
   * 获取文本为 TestMenuItem1 的 builder 与 'MenuBuilder' 对比
   * 获取 symbolGlyphBindContextMenu4 的属性
   * placement 与期望值 Placement.TopLeft 对比
   * backgroundBlurStyle 与期望值 BlurStyle.BACKGROUND_REGULAR 对比
   * 点击 bindContextMenu1 切换属性
   * placement 与期望值 Placement.TopRight 对比
   * backgroundBlurStyle 与期望值 BlurStyle.BACKGROUND_THICK 对比
   * 点击 bindContextMenu2 切换属性
   * placement 与期望值 Placement.BottomLeft 对比
   * backgroundBlurStyle 与期望值 BlurStyle.NONE 对比
   * 点击 bindContextMenu3 切换属性
   * placement 与期望值 Placement.BottomRight 对比
   * backgroundBlurStyle 与期望值 BlurStyle.COMPONENT_ULTRA_THIN 对比
   * 点击 bindContextMenu4 切换属性
   * placement 与期望值 Placement.LeftTop 对比
   * backgroundBlurStyle 与期望值 BlurStyle.COMPONENT_THIN 对比
   * 点击 bindContextMenu5 切换属性
   * placement 与期望值 Placement.LeftBottom 对比
   * backgroundBlurStyle 与期望值 BlurStyle.COMPONENT_REGULAR 对比
   * */
  defineTest('bindContextMenuTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("bindContextMenuTest_twoDemo running")
    let driver: Tester = Tester.create()
    let bindContextMenu4: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindContextMenu4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu3').enabled(true))
    let button4: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu4').enabled(true))
    let button5: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu5').enabled(true))
    let textBindContextMenu4: string = await bindContextMenu4.getInspectorInfo()

    assertFalse(JSON.parse(textBindContextMenu4).$attrs.bindContextMenu == undefined)
    assertEqual(JSON.parse(textBindContextMenu4).$attrs.bindContextMenu.placement, Placement.TopLeft)
    assertEqual(JSON.parse(textBindContextMenu4).$attrs.bindContextMenu.backgroundBlurStyle,
      BlurStyle.BACKGROUND_REGULAR)

    await button1.tap()
    let textBindContextMenu5: string = await bindContextMenu4.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu5).$attrs.bindContextMenu.placement, Placement.TopRight)
    assertEqual(JSON.parse(textBindContextMenu5).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.BACKGROUND_THICK)

    await button2.tap()
    let textBindContextMenu6: string = await bindContextMenu4.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu6).$attrs.bindContextMenu.placement, Placement.BottomLeft)
    assertEqual(JSON.parse(textBindContextMenu6).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.NONE)

    await button3.tap()
    let textBindContextMenu7: string = await bindContextMenu4.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu7).$attrs.bindContextMenu.placement, Placement.BottomRight)
    assertEqual(JSON.parse(textBindContextMenu7).$attrs.bindContextMenu.backgroundBlurStyle,
      BlurStyle.COMPONENT_ULTRA_THIN)

    await button4.tap()
    let textBindContextMenu8: string = await bindContextMenu4.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu8).$attrs.bindContextMenu.placement, Placement.LeftTop)
    assertEqual(JSON.parse(textBindContextMenu8).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.COMPONENT_THIN)

    await button5.tap()
    let textBindContextMenu9: string = await bindContextMenu4.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu9).$attrs.bindContextMenu.placement, Placement.LeftBottom)
    assertEqual(JSON.parse(textBindContextMenu9).$attrs.bindContextMenu.backgroundBlurStyle,
      BlurStyle.COMPONENT_REGULAR)
  }, 0)
}