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

/*
* Swiper组件 DisableSwipe属性
* 找到画面id为swiperDisableSwipe1的Swiper组件
* *找到画面文本为SwiperDisableSwipe1的Button组件
* 获取swiperDisableSwipe1的DisableSwipe属性与期待值true比对
* *点击button1，变更swiperDisableSwipe1属性值为false
* 获取swiperDisableSwipe1的DisableSwipe属性与期待值false比对
*/
export default async function swiperDisableSwipeTest() {
  defineTest('SwiperDisableSwipeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('SwiperDisableSwipeTestDemo running')
    let driver: Tester = Tester.create()
    let Swiper1: Component = await driver.findComponent(Matcher.create().id('swiperDisableSwipe1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperDisableSwipe1').enabled(true))
    let DisableSwipe1: string = await Swiper1.getInspectorInfo()
    assertTrue(JSON.parse(DisableSwipe1).$attrs.disableSwipe)
    await button1.tap()
    let DisableSwipe2: string = await Swiper1.getInspectorInfo()
    assertFalse(JSON.parse(DisableSwipe2).$attrs.disableSwipe)
  }, 0)
}