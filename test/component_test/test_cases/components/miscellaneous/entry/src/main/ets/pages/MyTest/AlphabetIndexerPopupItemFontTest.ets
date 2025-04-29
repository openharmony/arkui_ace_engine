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

export default async function alphabetIndexerPopupItemFontTest() {
  /*
* AlphabetIndexer组件  popupItemFont属性
* 找到画面id为alphabetIndexerPopupItemFont1,alphabetIndexerPopupItemFont2,alphabetIndexerPopupItemFont3,alphabetIndexerPopupItemFont4,alphabetIndexerPopupItemFont5,alphabetIndexerPopupItemFont6的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupItemFont1,AlphabetIndexerPopupItemFont2的button组件
* 获取alphabetIndexer1的popupItemFont属性与期待值'8.00fp','200','Arial',FontStyle.Normal比对
* 获取alphabetIndexer2的popupItemFont属性与期待值$r('app.string.font_size'),FontWeight.Lighter比对
* 获取alphabetIndexer3的popupItemFont属性与期待值FontWeight.Medium比对
* 获取alphabetIndexer4的popupItemFont属性与期待值FontWeight.Normal比对
* 获取alphabetIndexer5的popupItemFont属性与期待值FontWeight.Bolder比对
* 获取alphabetIndexer6的popupItemFont属性与期待值FontWeight.Regular比对
* 点击button1，变更alphabetIndexer1的popupItemFont属性值为'10px',"200",'TESTFONTRawFile',FontStyle.Italic
* 获取alphabetIndexer1的popupItemFont属性与期待值'10.00px',"200",'TESTFONTRawFile',FontStyle.Italic比对
* 点击button2，变更alphabetIndexer1的popupItemFont属性值为FontWeight.Bold
* 获取alphabetIndexer1的popupItemFont属性与期待值FontWeight.Bold比对
*/
  defineTest('alphabetIndexerPopupItemFontTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupItemFontTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont5').enabled(true))
    let alphabetIndexer6: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupItemFont6').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupItemFont1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupItemFont2').enabled(true))

    let popupItemFont1: string = await alphabetIndexer2.getInspectorInfo()
    assertFalse(JSON.parse(popupItemFont1).$attrs.popupItemFont == undefined)
    assertEqual(JSON.parse(popupItemFont1).$attrs.popupItemFont.size, $r('app.string.font_size'))
    assertEqual(JSON.parse(popupItemFont1).$attrs.popupItemFont.weight, FontWeight.Lighter)
    let popupItemFont2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont2).$attrs.popupItemFont.weight, FontWeight.Medium)
    let popupItemFont3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont3).$attrs.popupItemFont.weight, FontWeight.Normal)
    let popupItemFont4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont4).$attrs.popupItemFont.weight, FontWeight.Bolder)
    let popupItemFont5: string = await alphabetIndexer6.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont5).$attrs.popupItemFont.weight, FontWeight.Regular)

    let popupItemFont6: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont6).$attrs.popupItemFont.size, '8.00fp')
    assertEqual(JSON.parse(popupItemFont6).$attrs.popupItemFont.weight, '200')
    assertEqual(JSON.parse(popupItemFont6).$attrs.popupItemFont.family, 'Arial')
    assertEqual(JSON.parse(popupItemFont6).$attrs.popupItemFont.style, 'FontStyle::Normal')

    await button1.tap()
    let popupItemFont7: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont7).$attrs.popupItemFont.size, '10.00px')
    assertEqual(JSON.parse(popupItemFont7).$attrs.popupItemFont.weight, "200")
    assertEqual(JSON.parse(popupItemFont7).$attrs.popupItemFont.family, 'TESTFONTRawFile')
    assertEqual(JSON.parse(popupItemFont7).$attrs.popupItemFont.style, 'FontStyle::Italic')

    await button2.tap()
    let popupItemFont8: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupItemFont8).$attrs.popupItemFont.weight, 'FontWeight.Bold')
  }, 0)
}