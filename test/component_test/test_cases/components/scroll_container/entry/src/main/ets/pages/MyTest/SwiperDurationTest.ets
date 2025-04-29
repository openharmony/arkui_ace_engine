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

export default async function swiperDurationTest() {
  /*
* Swiper组件 Duration属性
* 找到画面id为swiperDuration1的Swiper组件
* 找到画面文本为SwiperDuration1的Button组件
* 获取swiperDuration1的Duration属性与期待值600比对
* 点击button1，变更swiperDuration1的Duration属性值为200
* 获取swiperDuration1的Duration属性与期待值200比对
*/
  defineTest('swiperDurationTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperDurationTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperDuration1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperDuration1').enabled(true))
    let duration1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(duration1).$attrs.duration, '600')
    await button1.tap()
    let duration2: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(duration2).$attrs.duration, '200')
  }, 0)
}