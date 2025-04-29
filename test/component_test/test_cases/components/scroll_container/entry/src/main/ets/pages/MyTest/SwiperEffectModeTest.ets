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

export default async function swiperEffectModeTest() {
  /*
* Swiper组件 EffectMode属性
* 找到画面id为swiperEffectMode1，swiperEffectMode2的Swiper组件
* 找到画面文本为SwiperEffectMode1的Button组件
* 获取swiperEffectMode1的EffectMode属性与期待值EdgeEffect.Spring比对
* 获取swiperEffectMode2的EffectMode属性与期待值EdgeEffect.Fade比对
* 点击button1，变更swiperEffectMode2的EffectMode属性值为EdgeEffect.None
* 获取swiperEffectMode2的EffectMode属性与期待值EdgeEffect.None比对
*/
  defineTest('swiperEffectModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('swiperEffectModeTestDemo running')
    let driver: Tester = Tester.create()
    let swiper1: Component = await driver.findComponent(Matcher.create().id('swiperEffectMode1').enabled(true))
    let swiper2: Component = await driver.findComponent(Matcher.create().id('swiperEffectMode2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('SwiperEffectMode1').enabled(true))
    let effectMode1: string = await swiper1.getInspectorInfo()
    assertEqual(JSON.parse(effectMode1).$attrs.effectMode, 'EdgeEffect.Spring')
    let effectMode2: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(effectMode2).$attrs.effectMode, 'EdgeEffect.Fade')
    await button1.tap()
    let effectMode3: string = await swiper2.getInspectorInfo()
    assertEqual(JSON.parse(effectMode3).$attrs.effectMode, 'EdgeEffect.None')
  }, 0)
}