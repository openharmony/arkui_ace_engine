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

export default async function alphabetIndexerFontTest() {
  /*
* AlphabetIndexer组件 font属性
* 找到画面id为alphabetIndexerFont1,alphabetIndexerFont2,alphabetIndexerFont3,alphabetIndexerFont4,
* alphabetIndexerFont5,alphabetIndexerFont6,alphabetIndexerFont7的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerFont1的button组件
* 获取alphabetIndexer1的font属性与期待值8.00fp,200,'Arial',FontStyle::Normal比对
* 获取alphabetIndexer2的font属性与期待值FontWeight.Normal比对
* 获取alphabetIndexer3的font属性与期待值$r('app.string.length'),FontWeight.Lighter比对
* 获取alphabetIndexer4的font属性与期待值FontWeight.Medium比对
* 获取alphabetIndexer5的font属性与期待值FontWeight.Bold比对
* 获取alphabetIndexer6的font属性与期待值FontWeight.Regular比对
* 获取alphabetIndexer7的font属性与期待值FontWeight.Bolder比对
* 点击button1，变更alphabetIndexer1的font属性值为'10px',"200",'TESTFONTRawFile',FontStyle.Italic
* 获取alphabetIndexer1的font属性与期待值'10.00px',"200",'TESTFONTRawFile',FontStyle::Italic比对
*/
  defineTest('alphabetIndexerFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerFontTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont5').enabled(true))
    let alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont6').enabled(true))
    let alphabetIndexer7: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerFont7').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerFont1').enabled(true))

    let font1: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(font1).$attrs.font.fontWeight, 'FontWeight.Normal')
    let font2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(font2).$attrs.font.fontSize, $r('app.string.font'))
    assertEqual(JSON.parse(font2).$attrs.font.fontWeight, 'FontWeight.Lighter')
    let font3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(font3).$attrs.font.fontWeight, 'FontWeight.Medium')
    let font4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(font4).$attrs.font.fontWeight, 'FontWeight.Bold')
    let font5: string = await alphabetIndexer6.getInspectorInfo()
    assertEqual(JSON.parse(font5).$attrs.font.fontWeight, 'FontWeight.Regular')
    let font6: string = await alphabetIndexer7.getInspectorInfo()
    assertEqual(JSON.parse(font6).$attrs.font.fontWeight, 'FontWeight.Bolder')

    let font7: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(font7).$attrs.font.fontSize, '8.00fp')
    assertEqual(JSON.parse(font7).$attrs.font.fontWeight, '200')
    assertEqual(JSON.parse(font7).$attrs.font.fontFamily, 'Arial')
    assertEqual(JSON.parse(font7).$attrs.font.fontStyle, 'FontStyle::NORMAL')

    await button1.tap()
    let font8: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(font8).$attrs.font.fontSize, '10.00px')
    assertEqual(JSON.parse(font8).$attrs.font.fontWeight, '200')
    assertEqual(JSON.parse(font8).$attrs.font.fontFamily, 'TESTFONTRawFile')
    assertEqual(JSON.parse(font8).$attrs.font.fontStyle, 'FontStyle::ITALIC')
  }, 0)
}