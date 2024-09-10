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

export default async function alphabetIndexerPopupUnselectedColorTest() {
  /*
* AlphabetIndexer组件  popupUnselectedColor属性
* 找到画面id为alphabetIndexerPopupUnselectedColor1,alphabetIndexerPopupUnselectedColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupUnselectedColor1,AlphabetIndexerPopupUnselectedColor2的button组件
* 获取alphabetIndexer1的popupUnselectedColor属性与期待值Color.Gray比对
* 获取alphabetIndexer2的popupUnselectedColor属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的popupUnselectedColor属性值为'#ffa500'
* 获取alphabetIndexer2的popupUnselectedColor属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的popupUnselectedColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的popupUnselectedColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerPopupUnselectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupUnselectedColorTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupUnselectedColor1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupUnselectedColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupUnselectedColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupUnselectedColor2').enabled(true))

    let popupUnselectedColor1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupUnselectedColor1).$attrs.popupUnselectedColor.toLowerCase(), Color.Gray)

    let popupUnselectedColor2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupUnselectedColor2).$attrs.popupUnselectedColor, '#FF808080')

    await button1.tap()
    let popupUnselectedColor3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupUnselectedColor3).$attrs.popupUnselectedColor, '#FFFFA500')

    await button2.tap()
    let popupUnselectedColor4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupUnselectedColor4).$attrs.popupUnselectedColor,
      $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}