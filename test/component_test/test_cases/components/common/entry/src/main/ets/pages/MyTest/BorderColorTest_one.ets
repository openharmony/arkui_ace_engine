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

export default async function borderColorTest_one() {
  /*
   * GridItem组件 BorderColor属性
   * 找到画面id为gridItemBorderColor1的组件
   * 找到画面text为ButtonItemBorderColor1的button组件
   * 获取gridItemBorderColor1的BorderColor属性与期待值 '#FF1B00FF' 比较
   * 点击button，变更gridItemBorderColor1的BorderColor属性为 '#FF528B8B'
   * 获取gridItemBorderColor1的BorderColor属性中与期待值 '#FF528B8B' 比较
   * 点击button，变更gridItemBorderColor1的BorderColor属性为 Color.Red
   * 获取gridItemBorderColor1的BorderColor属性中与期待值 Color.Red 比较
   * 点击button，变更gridItemBorderColor1的BorderColor属性为 $r('sys.color.ohos_id_color_text_hyperlink'))
   * 获取gridItemBorderColor1的BorderColor属性中与期待值 $r('sys.color.ohos_id_color_text_hyperlink')) 比较
   */
  defineTest('borderColorTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('borderColorTest_oneDemo running')
    let driver: Tester = Tester.create()
    let gridItemBorderColor1: Component =
      await driver.findComponent(Matcher.create().id('gridItemBorderColor1').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonItemBorderColor1').enabled(true))

    let borderColor1: string = await gridItemBorderColor1.getInspectorInfo()
    assertEqual(JSON.parse(borderColor1).$attrs.borderColor, '#FF1B00FF')

    await button.tap()
    let borderColor2: string = await gridItemBorderColor1.getInspectorInfo()
    assertEqual(JSON.parse(borderColor2).$attrs.borderColor, '#FF528B8B')

    await button.tap()
    let borderColor3: string = await gridItemBorderColor1.getInspectorInfo()
    assertEqual(JSON.parse(borderColor3).$attrs.borderColor.toLowerCase(), Color.Red)

    await button.tap()
    let borderColor4: string = await gridItemBorderColor1.getInspectorInfo()
    assertEqual(JSON.parse(borderColor4).$attrs.borderColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}