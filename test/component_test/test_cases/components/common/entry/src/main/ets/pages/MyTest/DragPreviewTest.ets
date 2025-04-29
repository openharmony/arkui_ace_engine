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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function dragPreviewTest() {
  /*
   * dragPreview 通用属性
   * 找到画面id为 imageDragPreview1 imageDragPreview2 imageDragPreview3 的三个 Image 组件
   * 长按 imageDragPreview1 切出 menu
   * 获取 text 为 "menu item 1" 的组件获取type与期望值 "Text" 比对
   * 点击画面外关闭menu
   * 长按 imageDragPreview2 切出 menu
   * 获取 text 为 "menu item 1" 的组件获取type与期望值 "Text" 比对
   * 点击画面外关闭menu
   * 长按 imageDragPreview3 切出 menu
   * 获取 text 为 "menu item 1" 的组件获取type与期望值 "Text" 比对
   * */
  defineTest('dragPreviewTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('dragPreviewTestDemo running')
    let driver: Tester = Tester.create()
    let imageDragPreview1: Component =
      await driver.findComponent(Matcher.create().id('imageDragPreview1').enabled(true))
    let imageDragPreview2: Component =
      await driver.findComponent(Matcher.create().id('imageDragPreview2').enabled(true))
    let imageDragPreview3: Component =
      await driver.findComponent(Matcher.create().id('imageDragPreview3').enabled(true))
    let dragPreview1: string = await imageDragPreview1.getInspectorInfo()
    assertFalse(JSON.parse(dragPreview1).$attrs.dragPreview == undefined)

    await imageDragPreview1.press()
    let findText1: Component = await driver.findComponent(Matcher.create().text("menu item 1"))
    let text1: string = await findText1.getType()
    assertTrue(text1 == "Text")

    await driver.tap(1, 1)
    await imageDragPreview2.press()
    let findText2: Component = await driver.findComponent(Matcher.create().text("menu item 1"))
    let text2: string = await findText2.getType()
    assertTrue(text2 == "Text")

    await driver.tap(1, 1)
    await imageDragPreview3.press()
    let findText3: Component = await driver.findComponent(Matcher.create().text("menu item 1"))
    let text3: string = await findText3.getType()
    assertTrue(text3 == "Text")
  }, 0)
}