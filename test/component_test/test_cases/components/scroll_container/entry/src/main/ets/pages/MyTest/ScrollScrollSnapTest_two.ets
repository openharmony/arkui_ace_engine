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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function scrollScrollSnapTest_two() {
  /*
* Scroll组件 ScrollSnap属性
* 找到画面id为scrollScrollSnap1,scrollScrollSnap2,scrollScrollSnap3,scrollScrollSnap4,scrollScrollSnap5,scrollScrollSnap6,scrollScrollSnap7,scrollScrollSnap8的Scroll组件
* 找到画面文本为ScrollScrollSnap_two的Button1组件
* 获取scrollScrollSnap1的{ scrollSnapAlign,SnapPagination,EnableSnapToStart }属性与期待值{ ScrollSnapAlign.NONE,Array(10,20,30),True }比对
* 获取scrollScrollSnap2的{ scrollSnapAlign,SnapPagination,EnableSnapToStart }属性与期待值{ ScrollSnapAlign.NONE,Array(10,20,30),False }比对
* 获取scrollScrollSnap3的{ scrollSnapAlign,SnapPagination,EnableSnapToEnd }属性与期待值{ ScrollSnapAlign.NONE,Array(10,20,30),True }比对
* 点击button，变更scrollScrollSnap3的ScrollSnap.EnableSnapToEnd属性值为False
* 获取scrollScrollSnap3的{ scrollSnapAlign,SnapPagination,EnableSnapToEnd }属性与期待值{ ScrollSnapAlign.NONE,Array(10,20,30),False }比对
* 获取scrollScrollSnap4的{ scrollSnapAlign,SnapPagination }属性与期待值{ ScrollSnapAlign.START,500 }比对
* 获取scrollScrollSnap5的{ scrollSnapAlign,SnapPagination }属性与期待值{ ScrollSnapAlign.START,0 }比对
* 获取scrollScrollSnap6的{ scrollSnapAlign,SnapPagination }属性与期待值{ ScrollSnapAlign.START,Array(100,200,300,400,500) }比对
* 获取scrollScrollSnap7的{ scrollSnapAlign,SnapPagination,EnableSnapToStart }属性与期待值{ ScrollSnapAlign.NONE,'200vp',True }比对
* 获取scrollScrollSnap8的{ scrollSnapAlign,SnapPagination,EnableSnapToEnd }属性与期待值{ ScrollSnapAlign.NONE,'200vp',True }比对
*/
  defineTest('scrollScrollSnapTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollScrollSnapTest_twoDemo running')
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
    let button: Component = await driver.findComponent(Matcher.create().text('ScrollScrollSnap_two').enabled(true))

    let scrollSnap1: string = await scrollScrollSnap1.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap1).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap1).$attrs.snapPagination, Array(10, 20, 30))
    assertTrue(JSON.parse(scrollSnap1).$attrs.enableSnapToStart)
    let scrollSnap2: string = await scrollScrollSnap2.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap2).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap2).$attrs.snapPagination, Array(10, 20, 30))
    assertFalse(JSON.parse(scrollSnap2).$attrs.enableSnapToStart)
    let scrollSnap3: string = await scrollScrollSnap3.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap3).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap3).$attrs.snapPagination, Array(10, 20, 30))
    assertTrue(JSON.parse(scrollSnap3).$attrs.enableSnapToEnd)
    await button.tap()
    let scrollSnap4: string = await scrollScrollSnap3.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap4).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap4).$attrs.snapPagination, Array(10, 20, 30))
    assertFalse(JSON.parse(scrollSnap4).$attrs.enableSnapToEnd)
    let scrollSnap5: string = await scrollScrollSnap4.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap5).$attrs.scrollSnapAlign, 'ScrollSnapAlign.START')
    assertEqual(JSON.parse(scrollSnap5).$attrs.snapPagination, '500.00')
    let scrollSnap6: string = await scrollScrollSnap5.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap6).$attrs.scrollSnapAlign, 'ScrollSnapAlign.START')
    assertEqual(JSON.parse(scrollSnap6).$attrs.snapPagination, 0)
    let scrollSnap7: string = await scrollScrollSnap6.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap7).$attrs.scrollSnapAlign, 'ScrollSnapAlign.START')
    assertEqual(JSON.parse(scrollSnap7).$attrs.snapPagination, Array(100, 200, 300, 400, 500))
    let scrollSnap8: string = await scrollScrollSnap7.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap8).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap8).$attrs.snapPagination, '200.00vp')
    assertTrue(JSON.parse(scrollSnap8).$attrs.enableSnapToStart)
    let scrollSnap9: string = await scrollScrollSnap8.getInspectorInfo()
    assertEqual(JSON.parse(scrollSnap9).$attrs.scrollSnapAlign, 'ScrollSnapAlign.NONE')
    assertEqual(JSON.parse(scrollSnap9).$attrs.snapPagination, '200.00vp')
    assertTrue(JSON.parse(scrollSnap9).$attrs.enableSnapToEnd)
  }, 0)
}