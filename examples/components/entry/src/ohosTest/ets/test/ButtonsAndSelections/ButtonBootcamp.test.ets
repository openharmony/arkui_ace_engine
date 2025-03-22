import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver } from '@kit.TestKit';
import { ON } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  JsonType, KeyStruct, radioClick, Search,
  searchParentBlock,
  searchToggle,
  Slide, sliderDrag, titleSearch, ToggleClick } from '../../utils';

const TAG = 'ButtonBootcamp'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();
export default function ButtonBootcampTest() {
  describe('ButtonBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'ButtonBootcamp' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('按钮与选择'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('按钮/Button'))
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
    })

    // buttonOptions.type
    it('ArkUI_Button_001', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.type')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonOptions.type'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ButtonType.Normal'
      })

      done();

    })

    it('ArkUI_Button_002', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.type')

      await radioClick({
        radioClickObj: 2,
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ButtonType.Circle'
      })

      done();

    })

    it('ArkUI_Button_003', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.type')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('type', JsonType.value),
        ],
        assertEqual: 'ButtonType.Capsule'
      })

      done();

    })

    // buttonOptions.buttonStyle
    it('ArkUI_Button_004', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.buttonStyle')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonOptions.buttonStyle'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('buttonStyle', JsonType.value),
        ],
        assertEqual: 'ButtonStyleMode.NORMAL'
      })

      done();

    })

    it('ArkUI_Button_005', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.buttonStyle')

      await radioClick({
        radioClickObj: 2,
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('buttonStyle', JsonType.value),
        ],
        assertEqual: 'ButtonStyleMode.TEXTUAL'
      })

      done();

    })

    it('ArkUI_Button_006', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.buttonStyle')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('buttonStyle', JsonType.value),
        ],
        assertEqual: 'ButtonStyleMode.EMPHASIZED'
      })

      done();

    })

    // buttonOptions.controlSize
    it('ArkUI_Button_007', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.controlSize')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonOptions.controlSize'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlSize', JsonType.value),
        ],
        assertEqual: 'ControlSize.SMALL'
      })

      done();

    })

    it('ArkUI_Button_008', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.controlSize')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('controlSize', JsonType.value),
        ],
        assertEqual: 'ControlSize.NORMAL'
      })

      done();

    })

    // buttonOptions.stateEffect
    it('ArkUI_Button_009', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.stateEffect')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonOptions.stateEffect'
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('stateEffect', JsonType.value),
        ],
        assertEqual: 'false'
      })

      done();

    })

    it('ArkUI_Button_010', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.stateEffect')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('stateEffect', JsonType.value),
        ],
        assertEqual: 'true'
      })

      done();

    })

    // labelStyle.overflow
    it('ArkUI_Button_011', 0, async (done: Function) => {

      await Search('参数列表', 'labelStyle.overflow')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'labelStyle.overflow'
        }
      })

      done();

    })

    it('ArkUI_Button_012', 0, async (done: Function) => {

      await Search('参数列表', 'labelStyle.overflow')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'labelStyle.overflow'
        }
      })

      done();

    })

    it('ArkUI_Button_013', 0, async (done: Function) => {

      await Search('参数列表', 'labelStyle.overflow')

      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickObj: 'labelStyle.overflow',
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // labelStyle.maxLines
    it('ArkUI_Button_014', 0, async (done: Function) => {

      await Search('参数列表', 'labelStyle.maxLines')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'labelStyle.maxLines'
        }
      })

      done();

    })

    it('ArkUI_Button_015', 0, async (done: Function) => {

      await Search('参数列表', 'labelStyle.maxLines')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'labelStyle.maxLines',
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // Label字数
    it('ArkUI_Button_016', 0, async (done: Function) => {
      // 无断言
      await Search('参数列表', 'Label字数')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickObj: 'Label字数'
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickObj: 'Label字数',
          toggleClickType: ToggleClick.Close
        }
      })

      done();

    })

    // buttonOptions.role
    it('ArkUI_Button_017', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.role')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj: 'buttonOptions.role',
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('role', JsonType.value),
        ],
        assertEqual: 'ButtonRole.ERROR'
      })

      done();

    })

    it('ArkUI_Button_018', 0, async (done: Function) => {

      await Search('参数列表', 'buttonOptions.role')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickObj: 'buttonOptions.role',
          toggleClickType: ToggleClick.Close
        },
        id: 'Button',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('role', JsonType.value),
        ],
        assertEqual: 'ButtonRole.NORMAL'
      })

      done();

    })
    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_Button_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0006', 0, async (done: Function) => {
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
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0007', 0, async (done: Function) => {
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
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0008', 0, async (done: Function) => {
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
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0009', 0, async (done: Function) => {
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
        id: 'Button',
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
        id: 'Button',
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
    it('ArkUI_Button_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0014', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_Button_Comp_0016', 0, async (done: Function) => {
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
  })
}