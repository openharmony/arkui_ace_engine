/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import window from '@ohos.window';
import { BusinessError } from '@kit.BasicServicesKit';
import { pageOneTmp } from './PageOne'
import { NavigationModifier } from '@ohos.arkui.modifier';

class MyNavigationModifier extends NavigationModifier {
	applyNavigatorAttribute(instance: NavigationAttribute): void {
		super.applyNormalAttribute?.(instance);
	}
}

@Entry
@Component
struct NavigationExample2 {
	@Provide('pageInfos') pageInfos: NavPathStack = new NavPathStack()
	@State barStyle: BarStyle = BarStyle.STANDARD
	@State hideNavBar:boolean=false
	@State hideTitleBar:boolean=false
	@State hideToolBar:boolean=false
	@State Click: ClickEffectLevel=ClickEffectLevel.HEAVY
	@State pathStack: NavPathStack = new NavPathStack();
	@State titleMode:NavigationTitleMode=NavigationTitleMode.Mini
	@State edge: Array<LayoutSafeAreaEdge> = [];
	@State type: Array<LayoutSafeAreaType> = [];
	@State mode:NavigationMode=	NavigationMode.Auto
	@State navBarPosition:NavBarPosition=NavBarPosition.Start
	@State navBarWidth:number=200
	@State top:number=0
	@State bottom:number=0
	@State left:number=0
	@State right:number=0

	@State type2: Array<SafeAreaType> = [SafeAreaType.SYSTEM, SafeAreaType.CUTOUT, SafeAreaType.KEYBOARD];
	@State edge2: Array<SafeAreaEdge> = [
		SafeAreaEdge.TOP,
		SafeAreaEdge.BOTTOM,
		SafeAreaEdge.START,
		SafeAreaEdge.END
	];

	@State marginValue:number = 0

	@State myModifier: NavigationModifier = new MyNavigationModifier().ignoreLayoutSafeArea(
		[LayoutSafeAreaType.SYSTEM],
		[LayoutSafeAreaEdge.TOP,LayoutSafeAreaEdge.BOTTOM])

	@Builder
	PageMap(name: string) {
		if (name === 'pageOne') {
			pageOneTmp({pageId: Date.now()})
		}
	}
	
	@Styles buttonStyles() {
		.margin(2)
		.padding(2)
		.height(25)
	}

	build() {
			Navigation(this.pageInfos) {
				Column() {
					Text('test Modifier').margin({bottom:10})
					Flex({wrap: FlexWrap.Wrap}) {
						Button('NavigationTitleMode.Mini')
							.buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Mini
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)
						Button('NavigationTitleMode.Free').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Free
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)
						Button('NavigationTitleMode.Full').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.titleMode = NavigationTitleMode.Full
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor(Color.Orange)
						Button('mode=NavigationMode.Auto').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.mode = NavigationMode.Auto
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('mode=NavigationMode.Stack').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.mode = NavigationMode.Stack
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('mode=NavigationMode.Split').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.mode = NavigationMode.Split
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#71B26C')
						Button('hideTitleBar=true').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideTitleBar = true
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideTitleBar=false').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideTitleBar = false
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')

						Button('hideNavBar=true').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideNavBar = true
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideNavBar=false').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideNavBar = false
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideToolBar=true').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideToolBar = true
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')
						Button('hideToolBar=false').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.hideToolBar = false
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#6CB2AC')

						Button('ExpandTop').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea(
									[LayoutSafeAreaType.SYSTEM],[LayoutSafeAreaEdge.TOP])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('ExpandBottom').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea(
									[LayoutSafeAreaType.SYSTEM],[LayoutSafeAreaEdge.BOTTOM])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('ExpandAll').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea(
									[LayoutSafeAreaType.SYSTEM],
									[LayoutSafeAreaEdge.TOP,LayoutSafeAreaEdge.BOTTOM])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('ExpandNone').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea([],[])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('ExpandTypeNone').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea([],[
									LayoutSafeAreaEdge.TOP,
									LayoutSafeAreaEdge.BOTTOM
								])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('ExpandEdgeNone').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								(this.myModifier as MyNavigationModifier).ignoreLayoutSafeArea([LayoutSafeAreaType.SYSTEM],[])
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#AD6CB2')

						Button('paddingTop++').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.top++
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#B2786C')
						Button('paddingBottom++').buttonStyles()
							.fontSize(12)
							.onClick(() => {
								this.bottom++
							}).clickEffect({ level: this.Click, scale: 0.8 }).backgroundColor('#B2786C')

						Button('set5')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								this.edge2 = []
							})

						Button('set safeAear CUTOUT')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								this.type2 = [SafeAreaType.CUTOUT]
							})

						Button('set safeAear KEYBOARD')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								this.type2 = [SafeAreaType.KEYBOARD]
							})


						Button('set layout Immersive')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								window.getLastWindow(getContext(this), (err, win)=>{
									win.setWindowLayoutFullScreen(true, (err: BusinessError) => {
										const errCode: number = err.code;
										if (errCode) {
											console.error(`Failed code: ${err.code}, message: ${err.message}`);
											return;
										}
										console.info('Succeeded in setting the window layout to full-screen mode.');
									});
								})
							})

						Button('set3')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								window.getLastWindow(getContext(this), (err, win)=>{
									win.setWindowLayoutFullScreen(false, (err: BusinessError) => {
										const errCode: number = err.code;
										if (errCode) {
											console.error(`Failed Cause code: ${err.code}, message: ${err.message}`);
											return;
										}
										console.info('Succeeded in setting the window layout to no-full-screen mode.');
									});
								})
							})

						Button('set1')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								window.getLastWindow(getContext(this), (err, win)=>{
									win.setWindowSystemBarEnable([], (err: BusinessError) => {
										const errCode: number = err.code;
										if (errCode) {
											console.error(`Failed code: ${err.code}, message: ${err.message}`);
											return;
										}
										console.info('Succeeded in setting the system bar to be invisible.');
									});
								})
							})

						Button('set2')
							.buttonStyles()
							.fontSize(12)
							.onClick(()=>{
								window.getLastWindow(getContext(this), (err, win)=>{
									win.setWindowSystemBarEnable(['status', 'navigation'], (err: BusinessError) => {
										const errCode: number = err.code;
										if (errCode) {
											console.error(`Failed code: ${err.code}, message: ${err.message}`);
											return;
										}
										console.info('Succeeded in setting the system bar to be visible.');
									});
								})
							})

						Button('margin++ :' + this.marginValue)
							.buttonStyles()
							.fontSize(12)
							.key('marginAdd')
							.onClick(()=>{
								this.marginValue += 10
							})
					}
				}
				.width('100%')
				.height('100%')
				.backgroundColor(Color.Red)
			}
			.attributeModifier(this.myModifier as MyNavigationModifier)
			.expandSafeArea(this.type2,this.edge2)
			.padding({top:this.top, bottom:this.bottom, left:this.left, right:this.right})
			.margin(this.marginValue)
			.titleMode(this.titleMode)
			.hideTitleBar(this.hideTitleBar)
			.navBarWidth(this.navBarWidth)
			.hideToolBar(this.hideToolBar)
			.navDestination(this.PageMap)
			.backgroundColor(Color.Green)
			.title('NavTitle', {
				backgroundColor: '#90121314',
				backgroundBlurStyle:BlurStyle.BACKGROUND_THIN,
				barStyle: this.barStyle,
			})
			.hideNavBar(this.hideNavBar)
			.mode(this.mode)
			.toolbarConfiguration([
				{value: 'a'},
				{value: 'b'},
				{value: 'c'},
			], {
				backgroundColor: '#38182431' ,
			})
		}
}
