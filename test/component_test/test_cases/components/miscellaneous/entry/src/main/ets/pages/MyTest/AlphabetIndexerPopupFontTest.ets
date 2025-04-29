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

export default async function alphabetIndexerPopupFontTest() {
  /*
* AlphabetIndexer组件  popupFont属性
* 找到画面id为alphabetIndexerPopupFont1,alphabetIndexerPopupFont2,alphabetIndexerPopupFont3,alphabetIndexerPopupFont4,
* alphabetIndexerPopupFont5,alphabetIndexerPopupFont6,alphabetIndexerPopupFont6的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupFont1的button组件
* 获取alphabetIndexer1的popupFont属性与期待值8.00fp,200,'Arial',FontStyle::Normal比对
* 获取alphabetIndexer2的popupFont属性与期待值$r('app.string.length'),FontWeight.Lighter比对
* 获取alphabetIndexer3的popupFont属性与期待值FontWeight.Bold比对
* 获取alphabetIndexer4的popupFont属性与期待值FontWeight.Bolder比对
* 获取alphabetIndexer5的popupFont属性与期待值FontWeight.Regular比对
* 获取alphabetIndexer6的popupFont属性与期待值FontWeight.Medium比对
* 获取alphabetIndexer7的popupFont属性与期待值FontWeight.Normal比对
* 点击button1，变更alphabetIndexer1的popupFont属性值为'10px',"200",'TESTFONTRawFile',FontStyle.Italic
* 获取alphabetIndexer1的popupFont属性与期待值'10.00px',"200",'TESTFONTRawFile',FontStyle::Italic比对
*/
  defineTest('alphabetIndexerPopupFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupFontTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont5').enabled(true))
    let alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont6').enabled(true))
    let alphabetIndexer7: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupFont7').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupFont1').enabled(true))

    let popupFont1: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupFont1).$attrs.popupFont.fontSize, $r('app.string.font_size'))
    assertEqual(JSON.parse(popupFont1).$attrs.popupFont.fontWeight, 'FontWeight.Lighter')
    let popupFont2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(popupFont2).$attrs.popupFont.fontWeight, 'FontWeight.Bold')
    let popupFont3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(popupFont3).$attrs.popupFont.fontWeight, 'FontWeight.Bolder')
    let popupFont4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(popupFont4).$attrs.popupFont.fontWeight, 'FontWeight.Regular')
    let popupFont5: string = await alphabetIndexer6.getInspectorInfo()
    assertEqual(JSON.parse(popupFont5).$attrs.popupFont.fontWeight, 'FontWeight.Medium')
    let popupFont6: string = await alphabetIndexer7.getInspectorInfo()
    assertEqual(JSON.parse(popupFont6).$attrs.popupFont.fontWeight, 'FontWeight.Normal')
    let popupFont7: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupFont7).$attrs.popupFont.fontSize, '8.00fp')
    assertEqual(JSON.parse(popupFont7).$attrs.popupFont.fontWeight, '200')
    assertEqual(JSON.parse(popupFont7).$attrs.popupFont.fontFamily, 'Arial')
    assertEqual(JSON.parse(popupFont7).$attrs.popupFont.fontStyle, 'FontStyle::NORMAL')

    await button1.tap()
    let popupFont8: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupFont8).$attrs.popupFont.fontSize, '10.00px')
    assertEqual(JSON.parse(popupFont8).$attrs.popupFont.fontWeight, '200')
    assertEqual(JSON.parse(popupFont8).$attrs.popupFont.fontFamily, 'TESTFONTRawFile')
    assertEqual(JSON.parse(popupFont8).$attrs.popupFont.fontStyle, 'FontStyle::ITALIC')
  }, 0)
}