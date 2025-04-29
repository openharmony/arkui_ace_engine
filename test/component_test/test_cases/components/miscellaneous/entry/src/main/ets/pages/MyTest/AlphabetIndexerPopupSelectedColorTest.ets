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

export default async function alphabetIndexerPopupSelectedColorTest() {
  /*
* AlphabetIndexer组件  popupSelectedColor属性
* 找到画面id为alphabetIndexerPopupSelectedColor1,alphabetIndexerPopupSelectedColor2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupSelectedColor1,AlphabetIndexerPopupSelectedColor2的button组件
* 获取alphabetIndexer1的popupSelectedColor属性与期待值Color.Red比对
* 获取alphabetIndexer2的popupSelectedColor属性与期待值'#FFFF0000'比对
* 点击button1，变更alphabetIndexer2的popupSelectedColor属性值为'#ffa500'
* 获取alphabetIndexer2的popupSelectedColor属性与期待值'#FFFFA500'比对
* 点击button2，变更alphabetIndexer2的popupSelectedColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
* 获取alphabetIndexer2的popupSelectedColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
*/
  defineTest('alphabetIndexerPopupSelectedColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupSelectedColorTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupSelectedColor1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupSelectedColor2').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupSelectedColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupSelectedColor2').enabled(true))

    let popupSelectedColor1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupSelectedColor1).$attrs.popupSelectedColor.toLowerCase(), Color.Red)

    let popupSelectedColor2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupSelectedColor2).$attrs.popupSelectedColor, '#FFFF0000')

    await button1.tap()
    let popupSelectedColor3: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupSelectedColor3).$attrs.popupSelectedColor, '#FFFFA500')

    await button2.tap()
    let popupSelectedColor4: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupSelectedColor4).$attrs.popupSelectedColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}