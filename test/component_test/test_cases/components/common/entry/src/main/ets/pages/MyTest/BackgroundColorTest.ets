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

export default async function backgroundColorTest() {
  /*
  * Text组件 BackgroundColor属性
  * 找到画面id为textAreaBackgroundColor1,textAreaBackgroundColor2,textAreaBackgroundColor3的TextArea组件
  * 找到画面文本为ButtonBackgroundColor的Button组件
  * 获取textAreaBackgroundColor1的BackgroundColor属性与期待值Color.Blue比对
  * 获取textAreaBackgroundColor2的BackgroundColor属性与期待值'#FFF60000'比对
  * 获取textAreaBackgroundColor3的BackgroundColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
  * 点击button，变更textAreaBackgroundColor1的BackgroundColor属性值为0xAFEEEE
  * 获取textAreaBackgroundColor1的BackgroundColor属性与期待值'#FFAFEEEE'比对
  */
  defineTest('backgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let textAreaBackgroundColor1: Component =
      await driver.findComponent(Matcher.create().id('textAreaBackgroundColor1').enabled(true))
    let textAreaBackgroundColor2: Component =
      await driver.findComponent(Matcher.create().id('textAreaBackgroundColor2').enabled(true))
    let textAreaBackgroundColor3: Component =
      await driver.findComponent(Matcher.create().id('textAreaBackgroundColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonBackgroundColor').enabled(true))
    let backgroundColor1: string = await textAreaBackgroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor.toLowerCase(), Color.Blue)

    let backgroundColor2: string = await textAreaBackgroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, '#FFF60000')

    let backgroundColor3: string = await textAreaBackgroundColor3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, $r('sys.color.ohos_id_color_text_hyperlink'))

    await button.tap()
    let backgroundColor4: string = await textAreaBackgroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, '#FFAFEEEE')
  }, 0)
}