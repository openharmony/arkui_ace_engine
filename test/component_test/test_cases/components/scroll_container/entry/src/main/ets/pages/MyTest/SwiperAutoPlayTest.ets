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

export default async function swiperAutoPlayTest() {
  /*
 * Swiper组件 AutoPlay属性
 * 找到画面id为swiperAutoPlay1，swiperAutoPlay2的Swiper组件
 * 找到画面文本为SwiperAutoPlay1的Button组件
 * 获取swiperAutoPlay1的AutoPlay属性与期待值true比对
 * 获取swiperAutoPlay2的AutoPlay属性与期待值true比对
 * 点击button1，变更swiperAutoPlay2的AutoPlay属性值为true
 * 获取swiperAutoPlay2的AutoPlay属性与期待值false比对
 */
  defineTest('swiperAutoPlayTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperAutoPlayTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperAutoPlay1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperAutoPlay2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperAutoPlay1').enabled(true))
    let autoPlay1: string = await swiper1.getInspectorInfo()
    assertTrue(JSON.parse(autoPlay1).$attrs.autoPlay)
    let autoPlay2: string = await swiper2.getInspectorInfo()
    assertTrue(JSON.parse(autoPlay2).$attrs.autoPlay)
    await button1.tap()
    let autoPlay3: string = await swiper2.getInspectorInfo()
    assertFalse(JSON.parse(autoPlay3).$attrs.autoPlay)
  }, 0)
}