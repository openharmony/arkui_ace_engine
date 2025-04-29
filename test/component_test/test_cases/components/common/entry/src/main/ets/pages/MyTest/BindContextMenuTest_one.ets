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

import {
  assertEqual,
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function bindContextMenuTest_one() {
  /*
   * bindContextMenu属性
   * 获取 id 为 textBindContextMenu1 的 Text 组件
   * 获取文本为 symbolGlyphBindContextMenu2 symbolGlyphBindContextMenu3 的 button 按钮
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
  defineTest('bindContextMenuTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("bindContextMenuTest_oneDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textBindContextMenu1').enabled(true))
    let symbolGlyph2: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindContextMenu2').enabled(true))
    let symbolGlyph3: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindContextMenu3').enabled(true))
    let bindContextMenuText1: Component =
      await driver.findComponent(Matcher.create().id('bindContextMenuText1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu3').enabled(true))
    let bindContextMenu1: string = await text1.getInspectorInfo()
    let textValue1: string = await bindContextMenuText1.getText()
    assertEqual(textValue1, 'message')
    assertFalse(JSON.parse(bindContextMenu1).$attrs.bindContextMenu == undefined)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.responseType, ResponseType.RightClick)
    assertEqual(JSON.parse(bindContextMenu1)
      .$attrs
      .bindContextMenu
      .options
      .x, 1)
    assertEqual(JSON.parse(bindContextMenu1)
      .$attrs
      .bindContextMenu
      .options
      .y, 2)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.placement, Placement.Left)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.arrowOffset, 100)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.preview, MenuPreviewMode.NONE)
    assertEqual(JSON.parse(bindContextMenu1)
      .$attrs
      .bindContextMenu
      .previewAnimationOptions
      .scale, [0.95, 1.1])
    assertTrue(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.enableArrow)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.backgroundColor, 0xffffff)
    assertEqual(JSON.parse(bindContextMenu1).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.Thin)
    let bindContextMenu2: string = await symbolGlyph2.getInspectorInfo()
    assertEqual(JSON.parse(bindContextMenu2)
      .$attrs
      .bindContextMenu
      .options
      .x, '10px')
    assertEqual(JSON.parse(bindContextMenu2)
      .$attrs
      .bindContextMenu
      .options
      .y, '10px')
    assertEqual(JSON.parse(bindContextMenu2).$attrs.bindContextMenu.placement, Placement.Right)
    assertEqual(JSON.parse(bindContextMenu2).$attrs.bindContextMenu.arrowOffset, '10px')
    assertEqual(JSON.parse(bindContextMenu2).$attrs.bindContextMenu.preview, MenuPreviewMode.NONE)
    let bindContextMenu3: string = await symbolGlyph3.getInspectorInfo()
    assertEqual(JSON.parse(bindContextMenu3).$attrs.bindContextMenu.responseType, ResponseType.LongPress)
    assertEqual(JSON.parse(bindContextMenu3).$attrs.bindContextMenu.backgroundColor, Color.Black)
    assertEqual(JSON.parse(bindContextMenu3).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.Regular)
    await button1.tap()
    let bindContextMenu4: string = await symbolGlyph2.getInspectorInfo()
    assertEqual(JSON.parse(bindContextMenu4)
      .$attrs
      .bindContextMenu
      .options
      .x, $r("app.string.any_length"))
    assertEqual(JSON.parse(bindContextMenu4)
      .$attrs
      .bindContextMenu
      .options
      .y, $r("app.string.any_length"))
    assertEqual(JSON.parse(bindContextMenu4).$attrs.bindContextMenu.placement, Placement.Top)
    assertEqual(JSON.parse(bindContextMenu4).$attrs.bindContextMenu.arrowOffset, $r("app.string.any_length"))
    await button2.tap()
    let bindContextMenu5: string = await symbolGlyph3.getInspectorInfo()
    assertEqual(JSON.parse(bindContextMenu5).$attrs.bindContextMenu.backgroundColor,
      $r('app.color.start_window_background'))
    assertEqual(JSON.parse(bindContextMenu5).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.Thick)
    await button3.tap()
    let bindContextMenu6: string = await symbolGlyph3.getInspectorInfo()
    assertEqual(JSON.parse(bindContextMenu6).$attrs.bindContextMenu.placement, Placement.Bottom)
    assertEqual(JSON.parse(bindContextMenu6).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.BACKGROUND_THIN)

    let testMenuItem1: Component = await driver.findComponent(Matcher.create().text('TestMenuItem1').enabled(true))
    let menuBuilder: string = await testMenuItem1.getType()
    assertEqual(menuBuilder, 'MenuBuilder')
  }, 0)
}