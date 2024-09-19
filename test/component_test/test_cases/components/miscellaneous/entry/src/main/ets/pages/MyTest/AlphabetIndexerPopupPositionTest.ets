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

export default async function alphabetIndexerPopupPositionTest() {
  /*
* AlphabetIndexer组件 popupPosition属性
* 找到画面id为alphabetIndexerPopupPosition1,alphabetIndexerPopupPosition2的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerPopupPosition的button组件
* 获取alphabetIndexer1的popupPosition属性与期待值'30.0.0vp','24.00vp'比对
* 获取alphabetIndexer2的popupPosition属性与期待值$r('app.string.length'),$r('app.string.length')比对
* 点击button，变更alphabetIndexer2的popupPosition属性值为'15.00px','15.00px'
* 获取alphabetIndexer的popupPosition属性与期待值'15.00px','15.00px'比对
*/
  defineTest('alphabetIndexerPopupPositionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerPopupPositionTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupPosition1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerPopupPosition2').enabled(true))
    let button: Component =
      await driver.findComponent(Matcher.create().text('AlphabetIndexerPopupPosition').enabled(true))

    let popupPosition1: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupPosition1).$attrs.popupPosition.popupPositionX, '30.00vp')
    assertEqual(JSON.parse(popupPosition1).$attrs.popupPosition.popupPositionY, '24.00vp')

    let popupPosition2: string = await alphabetIndexer2.getInspectorInfo()
    assertEqual(JSON.parse(popupPosition2).$attrs.popupPosition.popupPositionX, $r('app.string.length'))
    assertEqual(JSON.parse(popupPosition2).$attrs.popupPosition.popupPositionY, $r('app.string.length'))

    await button.tap()
    let popupPosition3: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(popupPosition3).$attrs.popupPosition.popupPositionX, '15.00px')
    assertEqual(JSON.parse(popupPosition3).$attrs.popupPosition.popupPositionY, '15.00px')
  }, 0)
}