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

export default async function textInputSelectedBackgroundColorTest() {
  /*
   * TextInput组件 SelectedBackgroundColor属性
   * 找到画面id为textInputSelectedBackgroundColor1,textInputSelectedBackgroundColor2的TextInput组件
   * 找到画面文本为TextInputSelectedBackgroundColor1,TextInputSelectedBackgroundColor2的Button组件
   * 获取textInput1的SelectedBackgroundColor属性与期待值'#33FFC0CB'比对
   * 获取textInput2的SelectedBackgroundColor属性与期待值'#33ffffff'比对
   * 点击button1，变更textInput2的SelectedBackgroundColor属性值为'rgb(255, 100, 255)'
   * 获取textInput2的SelectedBackgroundColor属性与期待值'#33FF64FF'比对
   * 点击button2，变更textInput2的SelectedBackgroundColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取textInput2的SelectedBackgroundColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textInputSelectedBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputSelectedBackgroundColorTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component =
      await driver.findComponent(Matcher.create().id('textInputSelectedBackgroundColor1').enabled(true))
    let textInput2: Component =
      await driver.findComponent(Matcher.create().id('textInputSelectedBackgroundColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextInputSelectedBackgroundColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextInputSelectedBackgroundColor2').enabled(true))

    let selectedBackgroundColor1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(selectedBackgroundColor1).$attrs.selectedBackgroundColor, '#33FFC0CB')

    let selectedBackgroundColor2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(selectedBackgroundColor2).$attrs.selectedBackgroundColor.toLowerCase(), '#33ffffff')

    await button1.tap()
    let selectedBackgroundColor3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(selectedBackgroundColor3).$attrs.selectedBackgroundColor, '#33FF64FF')

    await button2.tap()
    let selectedBackgroundColor4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(selectedBackgroundColor4).$attrs.selectedBackgroundColor,
      $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}