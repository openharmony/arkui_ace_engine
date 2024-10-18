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
} from '@ohos.arkui.componentTest'

export default async function alphabetIndexerSelectedFontTest() {
  /*
* AlphabetIndexer组件  selectedFont属性
* 找到画面id为alphabetIndexerSelectedFont1,alphabetIndexerSelectedFont2,alphabetIndexerSelectedFont3,alphabetIndexerSelectedFont4,alphabetIndexerSelectedFont5,alphabetIndexerSelectedFont6的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerSelectedFont1,AlphabetIndexerSelectedFont2的button组件
* 获取alphabetIndexer1的selectedFont属性与期待值'10.00fp','600','Arial',FontStyle::Normal比对
* 获取alphabetIndexer2的selectedFont属性与期待值$r('app.string.length'),FontWeight.Normal比对
* 获取alphabetIndexer3的selectedFont属性与期待值FontWeight.Lighter比对
* 获取alphabetIndexer4的selectedFont属性与期待值FontWeight.Medium比对
* 获取alphabetIndexer5的selectedFont属性与期待值FontWeight.Regular比对
* 获取alphabetIndexer6的selectedFont属性与期待值FontWeight.Bolder比对
* 点击button1，变更alphabetIndexer1的selectedFont属性值为'10.00px',"200",'TESTFONTRawFile',FontStyle.Italic
* 获取alphabetIndexer1的selectedFont属性与期待值'10.00px',"200",'TESTFONTRawFile',FontStyle::Italic比对
* 点击button2，变更alphabetIndexer1的selectedFont属性值为FontWeight.Bold
* 获取alphabetIndexer1的selectedFont属性与期待值FontWeight.Bold比对
*/
  defineTest('alphabetIndexerSelectedFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerSelectedFontTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont5').enabled(true))
    let alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerSelectedFont6').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerSelectedFont1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerSelectedFont2').enabled(true))

    let selectedFont1: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont1).$attrs.selectFont.fontSize, $r('app.string.font_size'))
    assertEqual(JSON.parse(selectedFont1).$attrs.selectFont.fontWeight, 'FontWeight.Normal')
    let selectedFont2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont2).$attrs.selectFont.fontWeight, 'FontWeight.Lighter')
    let selectedFont3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont3).$attrs.selectFont.fontWeight, 'FontWeight.Medium')
    let selectedFont4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont4).$attrs.selectFont.fontWeight, 'FontWeight.Regular')
    let selectedFont5: string = await alphabetIndexer6.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont5).$attrs.selectFont.fontWeight, 'FontWeight.Bolder')

    let selectedFont6: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont6).$attrs.selectFont.fontSize, '10.00fp')
    assertEqual(JSON.parse(selectedFont6).$attrs.selectFont.fontWeight, '600')
    assertEqual(JSON.parse(selectedFont6).$attrs.selectFont.fontFamily, 'Arial')
    assertEqual(JSON.parse(selectedFont6).$attrs.selectFont.fontStyle, 'FontStyle::NORMAL')

    await button1.tap()
    let selectedFont7: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont7).$attrs.selectFont.fontSize, '10.00px')
    assertEqual(JSON.parse(selectedFont7).$attrs.selectFont.fontWeight, "200")
    assertEqual(JSON.parse(selectedFont7).$attrs.selectFont.fontFamily, 'TESTFONTRawFile')
    assertEqual(JSON.parse(selectedFont7).$attrs.selectFont.fontStyle, 'FontStyle::ITALIC')

    await button2.tap()
    let selectedFont8: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(selectedFont8).$attrs.selectFont.fontWeight, 'FontWeight.Bold')
  }, 0)
}