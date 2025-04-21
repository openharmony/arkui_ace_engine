import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import { radioClick, Slide, sliderDrag, ToggleClick, titleSearch, } from '../../utils';
import { Point } from '@ohos.UiTest';


const TAG = 'AdvancedCounterBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function AdvancedCounterBootcampTest() {
  describe('AdvancedCounterBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');


      await delegator.startAbility({
        bundleName: 'cn.ohos.components',
        abilityName: 'EntryAbility'
      });

      await driver.delayMs(5000);
      console.info(TAG + 'GaugeBootcamp001' + ' begin');

      let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
      console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
      let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
      let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
      await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
      await driver.delayMs(1000);


      let atomDisplays: Component = await driver.findComponent(ON.text('信息展示'));
      await atomDisplays.click();
      await driver.delayMs(1000);

      let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
      let width: Point = await ListItems[0].getBoundsCenter()
      let width2: Point = await ListItems[2].getBoundsCenter()
      await driver.swipe(width.x, width2.y, width.x, width.y, 3000)
      await driver.delayMs(1000);

      let scrollSearch: Component = await driver.findComponent(ON.text('计数器/AdvancedCounter'))
      await scrollSearch.click()
      await driver.delayMs(1000);

      let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
      await Buttons[1].click()
      await driver.delayMs(1000);

      console.info(`beforeAll end`);
      done();
    })

    // type
    it('ArkUI_AdvancedCounter_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_AdvancedCounter_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })

    it('ArkUI_AdvancedCounter_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 3,
      })

      done();

    })

    it('ArkUI_AdvancedCounter_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type')
      // 无法取到子组件状态
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // direction
    it('ArkUI_AdvancedCounter_005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      //无法获取参数
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_AdvancedCounter_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      //无法获取参数
      await radioClick({
        radioClickObj: 2,
      })

      done();

    })

    it('ArkUI_AdvancedCounter_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      //无法获取参数
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // focusable
    it('ArkUI_AdvancedCounter_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'focusable')
      //无法获取参数
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_AdvancedCounter_009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'focusable')
      //无法获取参数
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // value
    it('ArkUI_AdvancedCounter_010', 0, async (done: Function) => {

      await titleSearch('参数列表', 'value')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // min
    it('ArkUI_AdvancedCounter_011', 0, async (done: Function) => {

      await titleSearch('参数列表', 'min')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // max
    it('ArkUI_AdvancedCounter_012', 0, async (done: Function) => {

      await titleSearch('参数列表', 'max')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // step
    it('ArkUI_AdvancedCounter_013', 0, async (done: Function) => {

      await titleSearch('参数列表', 'step')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // textWidth
    it('ArkUI_AdvancedCounter_014', 0, async (done: Function) => {

      await titleSearch('参数列表', 'textWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // year
    it('ArkUI_AdvancedCounter_015', 0, async (done: Function) => {

      await titleSearch('参数列表', 'year')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'year'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'year'
        },
      })

      done();

    })

    // month
    it('ArkUI_AdvancedCounter_016', 0, async (done: Function) => {

      await titleSearch('参数列表', 'month')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'month'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'month'
        },
      })

      done();

    })

    // day
    it('ArkUI_AdvancedCounter_017', 0, async (done: Function) => {

      await titleSearch('参数列表', 'day')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'day'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'day'
        },
      })

      done();

    })


  })
}