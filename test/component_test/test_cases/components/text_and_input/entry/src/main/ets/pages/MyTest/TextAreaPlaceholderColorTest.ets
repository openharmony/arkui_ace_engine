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

export default async function textAreaPlaceholderColorTest() {
  /*
   * TextArea组件 PlaceholderColor属性
   * 找到画面id为textAreaPlaceholderColor1,textAreaPlaceholderColor2的TextArea组件
   * 找到画面文本为TextAreaPlaceholderColor1,TextAreaPlaceholderColor2的Button组件
   * 获取textArea1的PlaceholderColor属性与期待值Color.Blue比对
   * 获取textArea2的PlaceholderColor属性与期待值'#ffffffff'比对
   * 点击button1，变更textArea2的PlaceholderColor属性值为'#99182431'
   * 获取textArea2的PlaceholderColor属性与期待值'#99182431'比对
   * 点击button2，变更textArea2的PlaceholderColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取textArea2的PlaceholderColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textAreaPlaceholderColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaPlaceholderColorTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component =
      await driver.findComponent(Matcher.create().id('textAreaPlaceholderColor1').enabled(true))
    let textArea2: Component =
      await driver.findComponent(Matcher.create().id('textAreaPlaceholderColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextAreaPlaceholderColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextAreaPlaceholderColor2').enabled(true))

    let placeholderColor1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderColor1).$attrs.placeholderColor.toLowerCase(), Color.Blue)
    let placeholderColor2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(placeholderColor2).$attrs.placeholderColor.toLowerCase(), '#ffffffff')

    await button1.tap()
    let placeholderColor3: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(placeholderColor3).$attrs.placeholderColor, '#99182431')

    await button2.tap()
    let placeholderColor4: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(placeholderColor4).$attrs.placeholderColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}