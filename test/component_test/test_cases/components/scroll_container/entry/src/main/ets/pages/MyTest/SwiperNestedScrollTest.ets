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

export default async function swiperNestedScrollTest() {
  /*
* Swiper组件 NestedScroll属性
* 找到画面id为swiperNestedScroll1,swiperNestedScroll2的Swiper组件
* 找到画面文本为SwiperNestedScroll1的Button组件
* 获取swiperNestedScroll1的NestedScroll属性与期待值SwiperNestedScrollMode.SELF_ONLY比对
* 获取swiperNestedScroll2的NestedScroll属性与期待值SwiperNestedScrollMode.SELF_ONLY比对
* 点击button1，变更swiperNestedScroll1的NestedScroll属性值为SwiperNestedScrollMode.SELF_FIRST
* 获取swiperNestedScroll1的NestedScroll属性与期待值SwiperNestedScrollMode.SELF_FIRST比对
* 点击button2，变更swiperNestedScroll2的NestedScroll属性值为SwiperNestedScrollMode.SELF_FIRST
* 获取swiperNestedScroll2的NestedScroll属性与期待值SwiperNestedScrollMode.SELF_FIRST比对
*/
  defineTest('swiperNestedScrollTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperNestedScrollTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperNestedScroll1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperNestedScroll2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperNestedScroll1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('SwiperNestedScroll2').enabled(true))
    let nestedScroll1: string = await swiper1.getInspectorInfo()
    assertFalse(JSON.parse(nestedScroll1).$attrs.nestedScroll == undefined)
    assertEqual(JSON.parse(nestedScroll1).$attrs.nestedScroll, SwiperNestedScrollMode.SELF_ONLY)
    let nestedScroll2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll2).$attrs.nestedScroll, SwiperNestedScrollMode.SELF_ONLY)
    await button1.tap()
    let nestedScroll3: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll3).$attrs.nestedScroll, SwiperNestedScrollMode.SELF_FIRST)
    await button2.tap()
    let nestedScroll4: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(nestedScroll4).$attrs.nestedScroll, SwiperNestedScrollMode.SELF_FIRST)
  }, 0)
}