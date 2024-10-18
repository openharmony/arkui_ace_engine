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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function alphabetIndexerUsingPopupTest() {
  /*
* AlphabetIndexer组件  usingPopup属性
* 找到画面id为alphabetIndexerUsingPopup的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerUsingPopup的button组件
* 获取alphabetIndexer的usingPopup与期待值true比对
* 点击button，变更alphabetIndexer的usingPopup属性值为false
* 获取alphabetIndexer的usingPopup与期待值false比对
*/
  defineTest('alphabetIndexerUsingPopupTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerUsingPopupTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerUsingPopup').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerUsingPopup').enabled(true))

    let usingPopup1: string = await alphabetIndexer.getInspectorInfo()
    assertTrue(JSON.parse(usingPopup1).$attrs.usingPopup)

    await button.tap()
    let usingPopup2: string = await alphabetIndexer.getInspectorInfo()
    assertFalse(JSON.parse(usingPopup2).$attrs.usingPopup)
  }, 0)
}
