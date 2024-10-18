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

export default async function textAreaPlaceholderFontTest() {
  /*
   * TextArea组件 PlaceholderFont属性
   * 找到画面id为textAreaPlaceholderFont1,textAreaPlaceholderFont2,textAreaPlaceholderFont3,textAreaPlaceholderFont4,textAreaPlaceholderFont5,textAreaPlaceholderFont6的TextArea组件
   * 找到画面文本为TextAreaPlaceholderFont1,TextAreaPlaceholderFont2的Button组件
   * 获取textArea1的PlaceholderFont属性与期待值'{"style":"FontStyle.Normal","size":"50.00px","fontWeight":"FontWeight.Lighter","fontFamily":"Arial"}'比对
   * 获取textArea2的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Regular'比对
   * 获取textArea3的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Medium'比对
   * 获取textArea4的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Bold'比对
   * 获取textArea5的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Bolder'比对
   * 获取textArea6的PlaceholderFont属性PlaceholderFont.weight与期待值'100'比对
   * 点击button1，变更textArea5的PlaceholderFont属性值为{size:40,weight:FontWeight.Normal,family:'TESTFONTRawFile',style:FontStyle.Italic}
   * 获取textArea1的PlaceholderFont属性与期待值'{"style":"FontStyle.Italic","size":"40.00fp","fontWeight":"FontWeight.Normal","fontFamily":"TESTFONTRawFile"}'比对
   * 点击button2，变更textArea6的PlaceholderFont属性PlaceholderFont.weight值为900
   * 获取textArea6的PlaceholderFont属性PlaceholderFont.weight与期待值'900'比对
   */
  defineTest('textAreaPlaceholderFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaPlaceholderFontTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont2').enabled(true))
    let textArea3: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont3').enabled(true))
    let textArea4: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont4').enabled(true))
    let textArea5: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont5').enabled(true))
    let textArea6: Component = await driver.findComponent(Matcher.create().id('textAreaPlaceholderFont6').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextAreaPlaceholderFont1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextAreaPlaceholderFont2').enabled(true))

    let placeholderFont1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont1).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"50.00px","fontWeight":"FontWeight.Lighter","fontFamily":"Arial"}')
    let placeholderFont2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont2).$attrs.placeholderFont).fontWeight, 'FontWeight.Regular')
    let placeholderFont3: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont3).$attrs.placeholderFont).fontWeight, 'FontWeight.Medium')
    let placeholderFont4: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont4).$attrs.placeholderFont).fontWeight, 'FontWeight.Bold')
    let placeholderFont5: string = await textArea5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont5).$attrs.placeholderFont).fontWeight, 'FontWeight.Bolder')
    let placeholderFont6: string = await textArea6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont6).$attrs.placeholderFont).weight, '100')

    await button1.tap()
    let placeholderFont7: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont7).$attrs.placeholderFont,
      '{"style":"FontStyle.Italic","size":"40.00fp","fontWeight":"FontWeight.Normal","fontFamily":"TESTFONTRawFile"}')
    await button2.tap()
    let placeholderFont8: string = await textArea6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont8).$attrs.placeholderFont).weight, '900')
  }, 0)
}