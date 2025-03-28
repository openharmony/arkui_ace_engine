import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  titleSearch,
  searchToggle,
  getToggle,
  searchParentBlock
} from '../../utils';
import { Point } from '@ohos.UiTest';


const TAG = 'DataPanelBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function DataPanelBootcampTest() {
  describe('DataPanelBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');
      
      await delegator.startAbility({
        bundleName: 'cn.ohos.components',
        abilityName: 'EntryAbility'
      });

      await driver.delayMs(5000);
      console.info(TAG + 'DataPanelBootcampTest' + ' begin');

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
      await driver.swipe(width.x, width2.y, width.x, width.y, 500)
      await driver.delayMs(1000);

      let scrollSearch: Component = await driver.findComponent(ON.text('数据面板/DataPanel'))
      await scrollSearch.click()
      await driver.delayMs(1000);

      let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
      await Buttons[1].click()
      await driver.delayMs(1000);


      console.info(`beforeAll end`);
      done();
    })

    // closeEffect
    it('ArkUI_DataPanel_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'closeEffect')
      // closeEffect 设置值无变化
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('closeEffect', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    it('ArkUI_DataPanel_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'closeEffect')
      // closeEffect 设置值无变化
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('closeEffect', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })

    // trackBackgroundColor
    it('ArkUI_DataPanel_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })

      done();

    })

    it('ArkUI_DataPanel_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 1,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })

      done();

    })

    it('ArkUI_DataPanel_005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 2,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })

      done();

    })

    it('ArkUI_DataPanel_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 3,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })

      done();

    })

    it('ArkUI_DataPanel_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 4,
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })

      done();

    })

    it('ArkUI_DataPanel_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'trackBackgroundColor')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackBackgroundColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })

      done();

    })

    // strokeWidth
    it('ArkUI_DataPanel_009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'strokeWidth')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '40.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('strokeWidth', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })

    // valueColors
    it('ArkUI_DataPanel_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      done();

    })

    it('ArkUI_DataPanel_011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 1,
      })

      done();

    })

    it('ArkUI_DataPanel_012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 2,
      })

      done();

    })

    it('ArkUI_DataPanel_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 3,
      })

      done();

    })

    it('ArkUI_DataPanel_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 4,
      })

      done();

    })

    it('ArkUI_DataPanel_015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'valueColors')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // dataPanelShadowOptions.MultiShadowOptions.Radius
    it('ArkUI_DataPanel_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'dataPanelShadowOptions.MultiShadowOptions.Radius')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('radius', JsonType.value),
        ],
        assertEqual: '20.000000'
      })

      done();

    })

    // dataPanelShadowOptions.MultiShadowOptions.OffsetX
    it('ArkUI_DataPanel_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'dataPanelShadowOptions.MultiShadowOptions.OffsetX')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'dataPanelShadowOptions.MultiShadowOptions.OffsetX'
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'dataPanelShadowOptions.MultiShadowOptions.OffsetX'
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetX', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    // dataPanelShadowOptions.MultiShadowOptions.OffsetY
    it('ArkUI_DataPanel_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'dataPanelShadowOptions.MultiShadowOptions.OffsetY')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'dataPanelShadowOptions.MultiShadowOptions.OffsetY'
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '100.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'dataPanelShadowOptions.MultiShadowOptions.OffsetY'
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('trackShadow', JsonType.obj),
          new KeyStruct('offsetY', JsonType.value),
        ],
        assertEqual: '0.000000'
      })

      done();

    })

    // colors
    it('ArkUI_DataPanel_019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'colors'
        }
      })

      done();

    })

    it('ArkUI_DataPanel_020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 1,
        toggleClick: {
          toggleClickObj: 'colors'
        }
      })

      done();

    })

    it('ArkUI_DataPanel_021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 2,
        toggleClick: {
          toggleClickObj: 'colors'
        }
      })

      done();

    })

    it('ArkUI_DataPanel_022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 3,
        toggleClick: {
          toggleClickObj: 'colors'
        }
      })

      done();

    })

    it('ArkUI_DataPanel_023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 4,
        toggleClick: {
          toggleClickObj: 'colors'
        }
      })

      done();

    })

    it('ArkUI_DataPanel_024', 0, async (done: Function) => {
      await titleSearch('参数列表', 'colors')

      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'colors'
        },
      })

      done();

    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        // id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_DataPanel_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })

      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })

      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_DataPanel_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启position
     */
    it('ArkUI_DataPanel_Comp_0011', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件position.top且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0012', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.top');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.bottom且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0013', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.bottom');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.left且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0014', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.left');
      //无值，只有xy的值
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试组件position.right且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0015', 0, async (done: Function) => {
      //无值，只有xy的值
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'position.right');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
      })

      done();
    })
    /**
     * 测试关闭position
     */
    it('ArkUI_DataPanel_Comp_0016', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'position');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('position')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启markAnchor
     */
    it('ArkUI_DataPanel_Comp_0017', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件markAnchor.x且获取属性正确
     */
    it('ArkUI_DataPanel_Comp_0018', 0, async (done: Function) => {
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.x');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'DataPanel',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('markAnchor', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })

      done();
    })

  })
}