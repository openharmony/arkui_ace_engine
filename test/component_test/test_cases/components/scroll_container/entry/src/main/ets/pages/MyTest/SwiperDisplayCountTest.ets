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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function swiperDisplayCountTest() {
  /*
* Swiper组件 DisplayCount属性
* 找到画面id为swiperDisplayCount1，swiperDisplayCount2,swiperDisplayCount3的Swiper组件
* 找到画面文本为SwiperDisplayCount1的Button组件
* 获取swiperDisplayCount1的DisplayCount属性与期待值{SwiperAutoFill:{ minSize:'60.00vp'},swipeByGroup:false}比对
* 获取swiperDisplayCount2的DisplayCount属性与期待值{SwiperAutoFill:{ minSize:'40.00vp'},swipeByGroup:true}比对
* 获取swiperDisplayCount3的DisplayCount属性与期待值{value:'SwiperDisplayMode.AUTO_LINEAR',swipeByGroup:true}比对
* 点击button，变更swiperDisplayCount3的displayCount属性{value:2,swipeByGroup:true}
* 获取swiperDisplayCount3的DisplayCount属性与期待值{value:2,swipeByGroup:true}比对
*/
  defineTest('swiperDisplayCountTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperDisplayCountTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperDisplayCount1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperDisplayCount2').enabled(true))
    let swiper3: Component = await driver.findComponent(Matcher.create().id('swiperDisplayCount3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperDisplayCount1').enabled(true))

    let displayCount1: string = await swiper1.getInspectorInfo()
    assertFalse(JSON.parse(displayCount1).$attrs.swipeByGroup == undefined)
    assertEqual(JSON.parse(displayCount1).$attrs.minSize, '60.00vp')
    assertFalse(JSON.parse(displayCount1).$attrs.swipeByGroup)
    let displayCount2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(displayCount2).$attrs.minSize, '40.00vp')
    assertTrue(JSON.parse(displayCount2).$attrs.displayCount.swipeByGroup)
    let displayCount3: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(displayCount3).$attrs.displayCount, SwiperDisplayMode.AUTO_LINEAR)
    assertTrue(JSON.parse(displayCount3).$attrs.swipeByGroup)
    await button1.tap()
    let displayCount4: string = await swiper3.getInspectorInfo()
    assertEqual(JSON.parse(displayCount4).$attrs.displayCount, 2)
    assertTrue(JSON.parse(displayCount4).$attrs.swipeByGroup)
  }, 0)
}