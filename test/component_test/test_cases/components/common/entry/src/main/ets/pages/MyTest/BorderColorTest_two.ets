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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function borderColorTest_two() {
  /*
   * GridItem组件 BorderColor属性
   * 找到画面id为gridItemBorderColor2的组件
   * 找到画面text为ButtonItemBorderColor2的button组件
   * 获取gridItemBorderColor2的BorderColor属性与期待值
   * { left: Color.Red, right: Color.Blue, top: Color.Red, bottom: Color.Green } 比较
   * 点击button，变更gridItemBorderColor2的BorderColor属性中的与期待值
   * { left: '#FFE3BBBB', right: '#FFFFE4E1', top: '#FF00FF00', bottom: '#FFB658BB' } 比较
   * 点击button，变更gridItemBorderColor2的BorderColor属性中与期待值
   * { left: $r('sys.color.ohos_id_color_text_hyperlink'), right: $r('sys.color.ohos_id_color_text_hyperlink'),
         top: $r('sys.color.ohos_id_color_text_hyperlink'), bottom: $r('sys.color.ohos_id_color_text_hyperlink') } 比较
   * 点击button，变更gridItemBorderColor2的BorderColor属性与期待值
   * { left: '#FF000000', right: '#FF000000', top: '#FF000000', bottom: '#FF000000' } 比较
   */
  defineTest('borderColorTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderColorTest_twoDemo running')
    let driver: Tester = Tester.create()
    let gridItemBorderColor2: Component =
      await driver.findComponent(Matcher.create().id('gridItemBorderColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonItemBorderColor2').enabled(true))

    let borderColor1: string = await gridItemBorderColor2.getInspectorInfo()
    assertEqual(JSON.parse(borderColor1)
      .$attrs
      .borderColor
      .left
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(borderColor1)
      .$attrs
      .borderColor
      .right
      .toLowerCase(), Color.Blue)
    assertEqual(JSON.parse(borderColor1)
      .$attrs
      .borderColor
      .top
      .toLowerCase(), Color.Red)
    assertEqual(JSON.parse(borderColor1)
      .$attrs
      .borderColor
      .bottom
      .toLowerCase(), Color.Green)

    await button.tap()
    let borderColor2: string = await gridItemBorderColor2.getInspectorInfo()
    assertEqual(JSON.parse(borderColor2).$attrs.borderColor.left, '#FFE3BBBB')
    assertEqual(JSON.parse(borderColor2).$attrs.borderColor.right, '#FFFFE4E1')
    assertEqual(JSON.parse(borderColor2).$attrs.borderColor.top, '#FF00FF00')
    assertEqual(JSON.parse(borderColor2).$attrs.borderColor.bottom, '#FFB658BB')

    await button.tap()
    let borderColor3: string = await gridItemBorderColor2.getInspectorInfo()
    assertEqual(JSON.parse(borderColor3).$attrs.borderColor.left, $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(borderColor3).$attrs.borderColor.right, $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(borderColor3).$attrs.borderColor.top, $r('sys.color.ohos_id_color_text_hyperlink'))
    assertEqual(JSON.parse(borderColor3).$attrs.borderColor.bottom, $r('sys.color.ohos_id_color_text_hyperlink'))

    await button.tap()
    let borderColor4: string = await gridItemBorderColor2.getInspectorInfo()
    assertEqual(JSON.parse(borderColor4).$attrs.borderColor.left, '#FF000000')
    assertEqual(JSON.parse(borderColor4).$attrs.borderColor.right, '#FF000000')
    assertEqual(JSON.parse(borderColor4).$attrs.borderColor.top, '#FF000000')
    assertEqual(JSON.parse(borderColor4).$attrs.borderColor.bottom, '#FF000000')
  }, 0)
}