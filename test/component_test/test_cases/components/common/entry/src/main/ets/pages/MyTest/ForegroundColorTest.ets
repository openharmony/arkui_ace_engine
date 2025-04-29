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

export default async function foregroundColorTest() {
  /*
   * Row组件 ForegroundColor通用属性
   * 找到画面id为rowForegroundColor1，rowForegroundColor2的row组件
   * 找到text为 ButtonForegroundColor 的button组件
   * 获取rowForegroundColor1的foregroundColor属性与 '#FF483D8B' 比较
   * 获取rowForegroundColor2的foregroundColor属性与 ColoringStrategy.INVERT 比较
   * 点击button改变rowForegroundColor1的foregroundColor为 #FF528B8B，rowForegroundColor2的foregroundColor为 #FF000000
   * 获取rowForegroundColor1的foregroundColor属性与 #FF528B8B 比较，rowForegroundColor2的foregroundColor属性与 #FF000000 比较
   * 点击button改变rowForegroundColor1的foregroundColor为 #FFFF0000，rowForegroundColor2的foregroundColor为 ColoringStrategy.PRIMARY
   * 获取rowForegroundColor1的foregroundColor属性与 #FFFF0000 比较，rowForegroundColor2的foregroundColor属性与 ColoringStrategy.PRIMARY 比较
   * 点击button改变rowForegroundColor1的foregroundColor为
   * $r('sys.color.ohos_id_color_text_hyperlink')，rowForegroundColor2的foregroundColor为 ColoringStrategy.INVERT
   * 获取rowForegroundColor1的foregroundColor属性与
   * $r('sys.color.ohos_id_color_text_hyperlink') 比较，rowForegroundColor2的foregroundColor属性与 ColoringStrategy.INVERT 比较
   */
  defineTest('foregroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('foregroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let rowForegroundColor1: Component =
      await driver.findComponent(Matcher.create().id('rowForegroundColor1').enabled(true))
    let rowForegroundColor2: Component =
      await driver.findComponent(Matcher.create().id('rowForegroundColor2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonForegroundColor').enabled(true))
    let foregroundColor1: string = await rowForegroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor1).$attrs.foregroundColor, '#FF483D8B')
    let foregroundColor2: string = await rowForegroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor2).$attrs.foregroundColor, '#00000001')

    await button.tap()
    let foregroundColor3: string = await rowForegroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor3).$attrs.foregroundColor, '#FF528B8B')
    let foregroundColor4: string = await rowForegroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor4).$attrs.foregroundColor, '#FF000000')

    await button.tap()
    let foregroundColor5: string = await rowForegroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor5).$attrs.foregroundColor, '#FFFF0000')
    let foregroundColor6: string = await rowForegroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor6).$attrs.foregroundColor, '#FF000000')

    await button.tap()
    let foregroundColor7: string = await rowForegroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor7).$attrs.foregroundColor, $r('sys.color.ohos_id_color_text_hyperlink'))
    let foregroundColor8: string = await rowForegroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(foregroundColor8).$attrs.foregroundColor, '#00000001')
  }, 0)
}