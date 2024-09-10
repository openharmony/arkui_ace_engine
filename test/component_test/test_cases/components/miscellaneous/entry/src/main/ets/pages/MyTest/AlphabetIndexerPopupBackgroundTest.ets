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

export default async function alphabetIndexerPopupBackgroundTest() {
  /*
* AlphabetIndexer组件  popupBackground属性
* 找到画面id为alphabetIndexerPopupBackground1,alphabetIndexerPopupBackground2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupBackground1,AlphabetIndexerPopupBackground2的button组件
* 获取alphabetIndexer1的popupBackground属性与期待值Color.Red比对
* 获取alphabetIndexer2的popupBackground属性与期待值'#FF808080'比对
* 点击button1，变更alphabetIndexer2的popupBackground属性值为'#FFFFA500'
* 获取alphabetIndexer2的popupBackground属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的popupBackground属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的popupBackground属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerPopupBackgroundTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupBackgroundTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupBackground1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupBackground2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupBackground1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupBackground2').enabled(true))

    let popupBackground1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupBackground1).$attrs.popupBackground.toLowerCase(), Color.Red)

    let popupBackground2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupBackground2).$attrs.popupBackground, '#FF808080')

    await button1.tap()
    let popupBackground3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupBackground3).$attrs.popupBackground, '#FFFFA500')

    await button2.tap()
    let popupBackground4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupBackground4).$attrs.popupBackground, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}