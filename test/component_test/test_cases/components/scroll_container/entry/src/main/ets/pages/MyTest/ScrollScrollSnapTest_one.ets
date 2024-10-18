/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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

export default async function scrollScrollSnapTest_one() {
  /*
* Scroll组件 ScrollSnap属性
* 找到画面id为scrollScrollSnap1,scrollScrollSnap2,scrollScrollSnap3,scrollScrollSnap4,scrollScrollSnap5,scrollScrollSnap6,scrollScrollSnap7,scrollScrollSnap8,scrollScrollSnap9的Scroll组件
* 找到画面文本为ScrollScrollSnap_one1的Button1组件
* 找到画面文本为ScrollScrollSnap_one2的Button2组件
* 获取scrollScrollSnap1的ScrollSnap.scrollSnapAlign属性与期待值ScrollSnapAlign.NONE比对
* 获取scrollScrollSnap2的ScrollSnap.scrollSnapAlign属性与期待值ScrollSnapAlign.START比对
* 获取scrollScrollSnap3的ScrollSnap.scrollSnapAlign属性与期待值ScrollSnapAlign.CENTER比对
* 点击button1，变更scrollScrollSnap3的ScrollSnap.scrollSnapAlign属性值为ScrollSnapAlign.END
* 获取scrollScrollSnap3的ScrollSnap.scrollSnapAlign属性与期待值ScrollSnapAlign.END比对
* 获取scrollScrollSnap4的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,'200px' }比对
* 获取scrollScrollSnap5的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,'200vp' }比对
* 获取scrollScrollSnap6的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,'200fp' }比对
* 获取scrollScrollSnap7的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,Array(200) }比对
* 获取scrollScrollSnap8的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,'200lpx' }比对
* 获取scrollScrollSnap9的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,'10%' }比对
* 点击button2，变更scrollScrollSnap9的snapPagination属性值为$r('app.string.length')
* 获取scrollScrollSnap9的{ scrollSnapAlign,snapPagination }属性与期待值{ ScrollSnapAlign.NONE,$r('app.string.length') }比对
*/
  defineTest('scrollScrollSnapTest_oneDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollSnapTest_oneDemo running')
    let driver: Tester = Tester.create()
    let scrollScrollSnap1: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap1').enabled(true))
    let scrollScrollSnap2: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap2').enabled(true))
    let scrollScrollSnap3: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap3').enabled(true))
    let scrollScrollSnap4: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap4').enabled(true))
    let scrollScrollSnap5: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap5').enabled(true))
    let scrollScrollSnap6: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap6').enabled(true))
    let scrollScrollSnap7: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap7').enabled(true))
    let scrollScrollSnap8: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap8').enabled(true))
    let scrollScrollSnap9: Component =
      await driver.findComponent(Matcher.create().id('scrollScrollSnap9').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ScrollScrollSnap_one1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ScrollScrollSnap_one2').enabled(true))

    let scrollSnap1: string = await scrollScrollSnap1.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap1).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    let scrollSnap2: string = await scrollScrollSnap2.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap2).$attrs.scrollSnapAlign, 'ScrollSnapAlign.START')
    let scrollSnap3: string = await scrollScrollSnap3.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap3).$attrs.scrollSnapAlign, 'ScrollSnapAlign::CENTER')
    await button1.tap()
    let scrollSnap4: string = await scrollScrollSnap3.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap4).$attrs.scrollSnapAlign, 'ScrollSnapAlign::END')
    let scrollSnap5: string = await scrollScrollSnap4.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap5).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap5).$attrs.snapPagination, '200.00px')
    let scrollSnap6: string = await scrollScrollSnap5.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap6).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap6).$attrs.snapPagination, '200.00vp')
    let scrollSnap7: string = await scrollScrollSnap6.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap7).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap7).$attrs.snapPagination, '200.00fp')
    let scrollSnap8: string = await scrollScrollSnap7.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap8).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap8).$attrs.snapPagination, Array(200))
    let scrollSnap9: string = await scrollScrollSnap8.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap9).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap9).$attrs.snapPagination, '200.00lpx')
    let scrollSnap10: string = await scrollScrollSnap9.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap10).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap10).$attrs.snapPagination, '10.00%')
    await button2.tap()
    let scrollSnap11: string = await scrollScrollSnap9.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap11).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap11).$attrs.scrollSnap.snapPagination, $r('app.string.length'))
  }, 0)
}