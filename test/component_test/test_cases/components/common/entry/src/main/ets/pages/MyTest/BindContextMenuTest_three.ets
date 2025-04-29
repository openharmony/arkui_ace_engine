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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function bindContextMenuTest_three() {
  /*
   * bindContextMenu属性
   * 获取 id 为symbolGlyphBindContextMenu5的symbolGlyph组件
   * 获取文本为 bindContextMenu1 的 button 按钮
   * 获取文本为 TestMenuItem1 的 builder 与 MenuBuilder对比
   * 获取 bindContextMenu5 的属性
   * placement 与期望值 Placement.RightTop 对比
   * backgroundBlurStyle 与期望值 BlurStyle.COMPONENT_THICK 对比
   * 点击 bindContextMenu1 切换属性
   * placement 与期望值 Placement.RightBottom 对比
   * backgroundBlurStyle 与期望值 BlurStyle.COMPONENT_ULTRA_THICK 对比
   * */
  defineTest('bindContextMenuTest_threeDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("bindContextMenuTest_threeDemo running")
    let driver: Tester = Tester.create()
    let bindContextMenu5: Component =
      await driver.findComponent(Matcher.create().id('symbolGlyphBindContextMenu5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindContextMenu1').enabled(true))

    let textBindContextMenu5: string = await bindContextMenu5.getInspectorInfo()
    assertFalse(JSON.parse(textBindContextMenu5).$attrs.bindContextMenu == undefined)
    assertEqual(JSON.parse(textBindContextMenu5).$attrs.bindContextMenu.placement, Placement.RightTop)
    assertEqual(JSON.parse(textBindContextMenu5).$attrs.bindContextMenu.backgroundBlurStyle, BlurStyle.COMPONENT_THICK)
    await button1.tap()
    let textBindContextMenu6: string = await bindContextMenu5.getInspectorInfo()
    assertEqual(JSON.parse(textBindContextMenu6).$attrs.bindContextMenu.placement, Placement.RightBottom)
    assertEqual(JSON.parse(textBindContextMenu6).$attrs.bindContextMenu.backgroundBlurStyle,
      BlurStyle.COMPONENT_ULTRA_THICK)
  }, 0)
}