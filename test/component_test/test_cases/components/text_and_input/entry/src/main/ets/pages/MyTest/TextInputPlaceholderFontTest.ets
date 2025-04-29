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

export default async function textInputPlaceholderFontTest() {
  /*
   * TextInput组件 PlaceholderFont属性
   * 找到画面id为textInputPlaceholderFont1,textInputPlaceholderFont2,textInputPlaceholderFont3,textInputPlaceholderFont4,textInputPlaceholderFont5,textInputPlaceholderFont6的TextInput组件
   * 找到画面文本为TextInputPlaceholderFont1,TextInputPlaceholderFont2的Button组件
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.size与期待值'50.00px'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Lighter'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.fontFamily与期待值'Arial'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.style与期待值'FontStyle.Normal'比对
   * 获取textInput2的PlaceholderFont属性PlaceholderFont.size与期待值'10.00fp'比对
   * 获取textInput2的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Regular'比对
   * 获取textInput2的PlaceholderFont属性PlaceholderFont.fontFamily与期待值'sans-serif'比对
   * 获取textInput3的PlaceholderFont属性PlaceholderFont.size与期待值'-1.00px'比对
   * 获取textInput3的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Medium'比对
   * 获取textInput4的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Bold'比对
   * 获取textInput5的PlaceholderFont属性PlaceholderFont.fontWeight与期待值'FontWeight.Bolder'比对
   * 获取textInput6的PlaceholderFont属性PlaceholderFont.weight与期待值'100'比对
   * 点击button1，变更textInput1的PlaceholderFont属性PlaceholderFont.size值为40
   * 变更textInput1的PlaceholderFont属性PlaceholderFont.fontWeight值为FontWeight.Normal
   * 变更textInput1的PlaceholderFont属性PlaceholderFont.fontFamily值为'TESTFONTRawFile'
   * 变更textInput1的PlaceholderFont属性PlaceholderFont.style值为FontStyle.Italic
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.size与期待值'40.00fp'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.weight与期待值'FontWeight.Normal'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.fontFamily与期待值'TESTFONTRawFile'比对
   * 获取textInput1的PlaceholderFont属性PlaceholderFont.style与期待值'FontStyle.Italic'比对
   * 点击button2，变更textInput6的PlaceholderFont属性PlaceholderFont.weight值为"900"
   * 获取textInput6的PlaceholderFont属性PlaceholderFont.weight与期待值"900"比对
   */
  defineTest('textInputPlaceholderFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputPlaceholderFontTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont1').enabled(true))
    let textInput2: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont2').enabled(true))
    let textInput3: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont3').enabled(true))
    let textInput4: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont4').enabled(true))
    let textInput5: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont5').enabled(true))
    let textInput6: Component =
      await driver.findComponent(Matcher.create().id('textInputPlaceholderFont6').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextInputPlaceholderFont1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextInputPlaceholderFont2').enabled(true))

    let placeholderFont1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont1).$attrs.placeholderFont,
      '{"style":"FontStyle.Normal","size":"50.00px","fontWeight":"FontWeight.Lighter","fontFamily":"Arial"}')
    let placeholderFont2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont2).$attrs.placeholderFont).size, $r('app.string.fp_length'))
    assertEqual(JSON.parse(JSON.parse(placeholderFont2).$attrs.placeholderFont).fontWeight, 'FontWeight.Regular')
    assertEqual(JSON.parse(JSON.parse(placeholderFont2).$attrs.placeholderFont).fontFamily, 'sans-serif')
    let placeholderFont3: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont3).$attrs.placeholderFont).size, '-1.00px')
    assertEqual(JSON.parse(JSON.parse(placeholderFont3).$attrs.placeholderFont).fontWeight, 'FontWeight.Medium')
    let placeholderFont4: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont4).$attrs.placeholderFont).fontWeight, 'FontWeight.Bold')
    let placeholderFont5: string = await textInput5.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont5).$attrs.placeholderFont).fontWeight, 'FontWeight.Bolder')
    let placeholderFont6: string = await textInput6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont6).$attrs.placeholderFont).weight, '100')

    await button1.tap()
    let placeholderFont7: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(placeholderFont7).$attrs.placeholderFont,
      '{"style":"FontStyle.Italic","size":"40.00fp","fontWeight":"FontWeight.Normal","fontFamily":"TESTFONTRawFile"}')

    await button2.tap()
    let placeholderFont8: string = await textInput6.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(placeholderFont8).$attrs.placeholderFont).weight, '900')
  }, 0)
}