import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, ON ,Component} from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import { buttonClick,
  getToggle,
  radioClick, Search, searchParentBlock,
  Slide,
  sliderDrag, titleSearch, ToggleClick } from '../utils';


const TAG = 'MenuItemGroupBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export default function MenuItemGroupBootcampTest() {
  describe('MenuItemGroupBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(3500);
        console.info(TAG + 'MenuItemGroupBootcamp001' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('菜单'));
        await atomDisplays.click();
        await driver.delayMs(4000);

        let ListItems: Component[] = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[1].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 500)
        await driver.delayMs(1000);


        let scrollSearch: Component = await driver.findComponent(ON.text('菜单分组/MenuItemGroup'))
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

    /**
     * 测试组件secondaryMenu支持是否允许显示二级菜单支持设置为允许
     */
    it('ArkUI_MenuItemGroup_001', 0, async (done: Function) => {
      // 无法取到属性值进行断言
     await Search('参数列表','secondaryMenu')
      await radioClick({
        radioClickObj: 0,
        toggleClick:{
          toggleClickObj:'secondaryMenu'
        }
      })
      done();
    })

    /**
     * 测试组件secondaryMenu支持是否允许显示二级菜单支持设置为禁止
     */
    it('ArkUI_MenuItemGroup_002', 0, async (done: Function) => {
      // 无法取到属性值进行断言
      await Search('参数列表', 'secondaryMenu')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickObj:'secondaryMenu',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标支持设置显示图标为1号
     */
    it('ArkUI_MenuItemGroup_003', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick:{
          toggleClickObj:'startIcon'
        }
      })
      done();
    })

    /**
     *测试组件是否显示前缀图标支持设置显示图标为2号
     */
    it('ArkUI_MenuItemGroup_004', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick:{
          toggleClickObj:'startIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标支持设置显示图标为3号
     */
    it('ArkUI_MenuItemGroup_005', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick:{
          toggleClickObj:'startIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标支持设置显示图标为4号
     */
    it('ArkUI_MenuItemGroup_006', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick:{
          toggleClickObj:'startIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标支持设置显示图标为5号
     */
    it('ArkUI_MenuItemGroup_007', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick:{
          toggleClickObj:'startIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示前缀图标支持设置显示图标为6号
     */
    it('ArkUI_MenuItemGroup_008', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'startIcon')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj:'startIcon',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标支持设置显示图标为1号
     */
    it('ArkUI_MenuItemGroup_009', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick:{
          toggleClickObj:'endIcon'
        }
      })
      done();
    })

    /**
     *测试组件是否显示后缀图标支持设置显示图标为2号
     */
    it('ArkUI_MenuItemGroup_010', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 1,
        toggleClick:{
          toggleClickObj:'endIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标支持设置显示图标为3号
     */
    it('ArkUI_MenuItemGroup_011', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 2,
        toggleClick:{
          toggleClickObj:'endIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标支持设置显示图标为4号
     */
    it('ArkUI_MenuItemGroup_012', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 3,
        toggleClick:{
          toggleClickObj:'endIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标支持设置显示图标为5号
     */
    it('ArkUI_MenuItemGroup_013', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 4,
        toggleClick:{
          toggleClickObj:'endIcon'
        }
      })
      done();
    })

    /**
     * 测试组件是否显示后缀图标支持设置显示图标为6号
     */
    it('ArkUI_MenuItemGroup_014', 0, async (done: Function)=> {
      // 无法取到属性值进行断言
      await Search('参数列表', 'endIcon')
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickObj:'endIcon',
          toggleClickType: ToggleClick.Close
        }
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0001', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'width');
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
     * 测试组件height且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0002', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'height');
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
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0003', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'padding');
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
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0004', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'margin');
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
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_MenuItemGroup_Comp_0005', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0006', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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

      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0007', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0008', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0009', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_MenuItemGroup_Comp_0010', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0011', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0012', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0013', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0014', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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
    it('ArkUI_MenuItemGroup_Comp_0015', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0016', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0017', 0, async (done: Function) => {
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
    it('ArkUI_MenuItemGroup_Comp_0018', 0, async (done: Function) => {
 // 无法取到属性值进行断言
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
     * 测试组件markAnchor.y且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0019', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'position');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'markAnchor.y');
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
     * 测试关闭markAnchor
     */
    it('ArkUI_MenuItemGroup_Comp_0020', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'markAnchor');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('markAnchor')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试开启offset
     */
    it('ArkUI_MenuItemGroup_Comp_0021', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      await toggle[0].click()
      await driver.delayMs(1000);
      done();
    })
    /**
     * 测试组件offset.x且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0022', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.x');
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
     * 测试组件offset.y且获取属性正确
     */
    it('ArkUI_MenuItemGroup_Comp_0023', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'offset');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'offset.y');
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
     * 测试关闭offset
     */
    it('ArkUI_MenuItemGroup_Comp_0024', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'offset');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('offset')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(1000);

      done();
    })
    /**
     * 测试组件borderStyle
     */
    it('ArkUI_MenuItemGroup_Comp_0025', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderStyle');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },


      })
      done();
    })
    it('ArkUI_MenuItemGroup_Comp_0026', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 1,

      })
      done();
    })
    it('ArkUI_MenuItemGroup_Comp_0027', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderStyle');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderStyle')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },


      })
      done();
    })
    /**
     * 测试组件borderWidth
     */
    it('ArkUI_MenuItemGroup_Comp_0028', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderWidth');
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
     * 测试组件borderColor
     */
    it('ArkUI_MenuItemGroup_Comp_0029', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },

      })

      done();

    })
    it('ArkUI_MenuItemGroup_Comp_0030', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 1,

      })

      done();

    })
    it('ArkUI_MenuItemGroup_Comp_0031', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 2,


      })

      done();
    })
    it('ArkUI_MenuItemGroup_Comp_0032', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 3,


      })

      done();

    })
    it('ArkUI_MenuItemGroup_Comp_0033', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 4,


      })

      done();

    })
    it('ArkUI_MenuItemGroup_Comp_0034', 0, async (done: Function) => {
 // 无法取到属性值进行断言
      await titleSearch('基础属性', 'borderColor');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('borderColor')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await buttonClick({
        buttonClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },


      })

      done();

    })

  })
}