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

export default async function swiperDisplayModeTest() {
  /*
* Swiper组件 DisplayMode属性
* 找到画面id为swiperDisplayMode1，swiperDisplayMode2的Swiper组件
* 找到画面文本为SwiperDisplayMode1的Button组件
* 获取swiperDisplayMode1的DisplayMode属性与期待值SwiperDisplayMode.AUTO_LINEAR比对
* 获取swiperDisplayMode2的DisplayMode属性与期待值SwiperDisplayMode.AUTO_LINEAR比对
* 点击button，变更swiperDisplayMode1的DisplayMode属性值为SwiperDisplayMode.STRETCH，
* swiperDisplayMode2的属性DisplayMode属性值为SwiperDisplayMode.STRETCH
* 获取swiperDisplayMode1的DisplayMode属性与期待值SwiperDisplayMode.STRETCH比对
* 获取swiperDisplayMode2的DisplayMode属性与期待值SwiperDisplayMode.STRETCH比对
*/
  defineTest('swiperDisplayModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperDisplayModeTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperDisplayMode1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperDisplayMode2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperDisplayMode1').enabled(true))
    let displayMode1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(displayMode1).$attrs.displayMode, 'SwiperDisplayMode.AutoLinear')
    let displayMode2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(displayMode2).$attrs.displayMode, 'SwiperDisplayMode.AutoLinear')
    await button1.tap()
    let displayMode3: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(displayMode3).$attrs.displayMode, 'SwiperDisplayMode.Stretch')
    let displayMode4: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(displayMode4).$attrs.displayMode, 'SwiperDisplayMode.Stretch')
  }, 0)
}