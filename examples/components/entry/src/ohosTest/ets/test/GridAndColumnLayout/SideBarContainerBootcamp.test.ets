import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  Search,
  searchParentBlock,
  searchRadio,
  titleSearch,
  searchToggle,
  getToggle
} from '../../utils/index';
import { On, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function SideBarContainerBootcampTest() {
  describe('SideBarContainerBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('栅格与分栏'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('侧边栏容器/SideBarContainer'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(() => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    it('ArkUI_SideBarContainer_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'type'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SideBarContainerType.Embed'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'type'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SideBarContainerType.OVERLAY'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'type');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'type'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value)
        ],
        assertEqual: 'SideBarContainerType.OVERLAY'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'showSideBar');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'showSideBar'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showSideBar', JsonType.value)
        ],
        assertEqual: 'true'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'showSideBar');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'showSideBar'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showSideBar', JsonType.value)
        ],
        assertEqual: 'false'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.left');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'controlButton.left'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"40.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'controlButton.left',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"0.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'controlButton.top'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj),
        ],
        assertEqual: '{"left":"16.000000","top":"100.000000","width":"32.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'controlButton.top',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"0.000000","width":"32.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'controlButton.width'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"80.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'controlButton.width',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"0.000000","height":"32.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'controlButton.height'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"80.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'controlButton.height',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"0.000000","icon":{"shown":"","hidden":"","switching":""}}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.shown');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.shown'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554446.png","hidden":"","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.shown');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.shown'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554441.png","hidden":"","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.shown');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'controlButton.icons.shown'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.hidden');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.hidden'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554446.png","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.hidden');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.hidden'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554441.png","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.hidden');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'controlButton.icons.hidden'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554440.png","switching":""}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.switching');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.switching'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554440.png","switching":"resource:///33554446.png"}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.switching');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'controlButton.icons.switching'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554440.png","switching":"resource:///33554441.png"}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'controlButton.icons.switching');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'controlButton.icons.switching'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlButton', JsonType.obj)
        ],
        assertEqual: '{"left":"16.000000","top":"48.000000","width":"32.000000","height":"32.000000","icon":{"shown":"resource:///33554440.png","hidden":"resource:///33554440.png","switching":"resource:///33554440.png"}}'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'showControlButton');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'showControlButton'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showControlButton', JsonType.obj)
        ],
        assertEqual: 'true'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'showControlButton');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'showControlButton'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('showControlButton', JsonType.obj)
        ],
        assertEqual: 'false'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sideBarWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'sideBarWidth'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideBarWidth', JsonType.obj)
        ],
        assertEqual: '600.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'sideBarWidth',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideBarWidth', JsonType.obj)
        ],
        assertEqual: '100.000000'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'minSideBarWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'minSideBarWidth'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minSideBarWidth', JsonType.obj)
        ],
        assertEqual: '400.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'minSideBarWidth',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minSideBarWidth', JsonType.obj)
        ],
        assertEqual: '100.000000'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'maxSideBarWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'maxSideBarWidth'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxSideBarWidth', JsonType.obj)
        ],
        assertEqual: '600.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'SideBarContainer',
        toggleClick: {
          toggleClickObj: 'maxSideBarWidth',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('maxSideBarWidth', JsonType.obj)
        ],
        assertEqual: '200.000000'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0024', 0, async (done: Function) => {
      await titleSearch('参数列表', 'autoHide');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'autoHide'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoHide', JsonType.obj)
        ],
        assertEqual: 'true'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0025', 0, async (done: Function) => {
      await titleSearch('参数列表', 'autoHide');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'autoHide'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('autoHide', JsonType.obj)
        ],
        assertEqual: 'false'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0026', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sideBarPosition');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'sideBarPosition'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideBarPosition', JsonType.obj)
        ],
        assertEqual: 'SideBarPosition.Start'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0027', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sideBarPosition');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'sideBarPosition'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sideBarPosition', JsonType.obj)
        ],
        assertEqual: 'SideBarPosition.End'
      })
      done();
    })
    it('ArkUI_SideBarContainer_0028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.strokeWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.strokeWidth'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"10.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#08000000"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'divider.strokeWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"0.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#08000000"}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FF0A59F7"}'
      })

      done();

    })
    it('ArkUI_SideBarContainer_0030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('divider.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FF646AFD"}'
      })

      done();

    })
    it('ArkUI_SideBarContainer_0031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('divider.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FFFE7062"}'
      })

      done();
    })
    it('ArkUI_SideBarContainer_0032', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('divider.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FFE9E8ED"}'
      })

      done();

    })
    it('ArkUI_SideBarContainer_0033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('divider.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FF1C1C1C"}'
      })

      done();

    })
    it('ArkUI_SideBarContainer_0034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.color');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('divider.color')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#FFFFFFFF"}'
      })

      done();

    })
    it('ArkUI_SideBarContainer_0035', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.startMargin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.startMargin'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"100.00vp","endMargin":"0.00vp","color":"#08000000"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'divider.startMargin',
          toggleClickType: ToggleClick.Close
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj),
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#08000000"}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0036', 0, async (done: Function) => {
      await titleSearch('参数列表', 'divider.endMargin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'divider.endMargin'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"100.00vp","color":"#08000000"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'divider.endMargin',
          toggleClickType: ToggleClick.Close
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('divider', JsonType.obj)
        ],
        assertEqual: '{"strokeWidth":"1.00vp","startMargin":"0.00vp","endMargin":"0.00vp","color":"#08000000"}'
      })
      done();

    })
    it('ArkUI_SideBarContainer_0037', 0, async (done: Function) => {
      await titleSearch('参数列表', 'minContentWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'minContentWidth'
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minContentWidth', JsonType.value)
        ],
        assertEqual: '800.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'minContentWidth',
          toggleClickType: ToggleClick.Close
        },
        id: 'SideBarContainer',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('minContentWidth', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
  })
}