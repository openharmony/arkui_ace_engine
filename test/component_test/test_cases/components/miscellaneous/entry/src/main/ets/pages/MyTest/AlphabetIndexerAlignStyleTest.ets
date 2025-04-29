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

export default async function alphabetIndexerAlignStyleTest() {
  /*
* AlphabetIndexer组件  alignStyle属性
* 找到画面id为alphabetIndexerAlignStyle1,alphabetIndexerAlignStyle2,alphabetIndexerAlignStyle3,alphabetIndexerAlignStyle4,alphabetIndexerAlignStyle5的AlphabetIndexer组件
* 找到画面文本为AlphabetIndexerAlignStyle的button组件
* 获取alphabetIndexer1的alignStyle属性与期待值IndexerAlign.Right,$r('app.string.length')比对
* 获取alphabetIndexer2的alignStyle属性与期待值IndexerAlign.Left,60比对
* 获取alphabetIndexer3的alignStyle属性与期待值IndexerAlign.Left,10比对
* 获取alphabetIndexer4的alignStyle属性与期待值IndexerAlign.Left,100比对
* 获取alphabetIndexer5的alignStyle属性与期待值IndexerAlign.Left,10比对
* 点击button,变更alphabetIndexer1的alignStyle属性值为'100px'
* 获取alphabetIndexer1的alignStyle属性与期待值'100px'比对
*/
  defineTest('alphabetIndexerAlignStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alphabetIndexerAlignStyleTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexer1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle1').enabled(true))
    let alphabetIndexer2: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle2').enabled(true))
    let alphabetIndexer3: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle3').enabled(true))
    let alphabetIndexer4: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle4').enabled(true))
    let alphabetIndexer5: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerAlignStyle5').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('AlphabetIndexerAlignStyle').enabled(true))

    let alignStyle1: string = await alphabetIndexer2.getInspectorInfo()
    assertFalse(JSON.parse(alignStyle1).$attrs.alignStyle.value == undefined)
    assertEqual(JSON.parse(alignStyle1).$attrs.alignStyle.value, 'IndexerAlign.Right')
    assertEqual(JSON.parse(alignStyle1).$attrs.alignStyle.offset, $r('app.string.length'))
    let alignStyle2: string = await alphabetIndexer3.getInspectorInfo()
    assertEqual(JSON.parse(alignStyle2).$attrs.alignStyle.value, 'IndexerAlign.Left')
    assertEqual(JSON.parse(alignStyle2).$attrs.alignStyle.offset, 60)
    let alignStyle3: string = await alphabetIndexer4.getInspectorInfo()
    assertEqual(JSON.parse(alignStyle3).$attrs.alignStyle.value, 'IndexerAlign.Left')
    assertEqual(JSON.parse(alignStyle3).$attrs.alignStyle.offset, 10)
    let alignStyle4: string = await alphabetIndexer5.getInspectorInfo()
    assertEqual(JSON.parse(alignStyle4).$attrs.alignStyle.value, 'IndexerAlign.Left')
    assertEqual(JSON.parse(alignStyle4).$attrs.alignStyle.offset, 100)

    let alignStyle5: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(alignStyle5).$attrs.alignStyle.value, 'IndexerAlign.Left')
    assertEqual(JSON.parse(alignStyle5).$attrs.alignStyle.offset, 10)

    await button.tap()
    let alignStyle6: string = await alphabetIndexer1.getInspectorInfo()
    assertEqual(JSON.parse(alignStyle6).$attrs.alignStyle.value, 'IndexerAlign.Left')
    assertEqual(JSON.parse(alignStyle6).$attrs.alignStyle.offset, '100px')
  }, 0)
}