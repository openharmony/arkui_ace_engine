import { TextInputModifier } from '@kit.ArkUI';

type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class MyModifier extends TextInputModifier {
	count: number = 0
	fountSize:number = 10
	updateWidth(value: TextUnit) {
		this.width(value)
		this.count++
	}

	updateHeight(value: TextUnit) {
		this.height(value)
		this.count++
	}

	updateFontSize(value: number) {
		this.fountSize += value
		this.fontSize(this.fountSize)
	}
}

class TestCase {
	policyArray: Array<CaseItem> = [
		{
			name: '100vp',
			value: '100vp'
		},
		{
			name: '100%',
			value: '100%'
		},
		{
			name: 'wrapContent',
			value: LayoutPolicy.wrapContent
		},
		{
			name: 'matchParent',
			value: LayoutPolicy.matchParent
		},
		{
			name: 'fixAtIdealSize',
			value: LayoutPolicy.fixAtIdealSize
		},
		{
			name: 'auto',
			value: 'auto'
		}
	]
	unit: TextUnit = '100vp';
	caseNumber: number = 0
	listener: Function | undefined = undefined
	name: string = ""
	index: number = 0


	constructor(name: string, index: number, listener: Function) {
		this.name = name
		this.index = index
		this.listener = listener
		this.output(`${this.name}: ${this.policyArray[this.caseNumber].name}`, this.index)
	}

	switchCase() {
		this.caseNumber++
		if (this.caseNumber > this.policyArray.length - 1) {
			this.caseNumber = 0
		}
		this.unit = this.policyArray[this.caseNumber].value
		this.output(`${this.name}: ${this.policyArray[this.caseNumber].name}`, this.index)
	}

	output(str: string, index: number) {
		if (this.listener) {
			this.listener(index, str)
		}
	}
}

@Component
export struct TextInputLayoutPolicy {
	prefix: string = 'TextInput'
	@State msgArray: string[] = ["","","",""]
	@State msg: string = ""
	@State textWidth: TestCase = new TestCase(`${this.prefix}Width`, 0, this.recvMsg.bind(this))
	@State textHeight: TestCase = new TestCase(`${this.prefix}Height`, 1, this.recvMsg.bind(this))
	@State parentWidth: TestCase = new TestCase('ParentWidth', 2, this.recvMsg.bind(this))
	@State parentHeight: TestCase = new TestCase('ParentHeight', 3, this.recvMsg.bind(this))
	@State myModifier: MyModifier = new MyModifier()
	build() {
		Column() {
			Stack() {
				Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
					TextInput({text: "Hello World!", placeholder: "###########"})
						.borderWidth(1)
						.borderColor(Color.Blue)
						.fontSize(this.myModifier.fountSize)
						.constraintSize({
							minWidth: '200vp',
							maxWidth: '300vp',
							minHeight: '200vp',
							maxHeight: '300vp'
						})
						.type(InputType.Email)
						.attributeModifier(this.myModifier)
						.maxLength(100)
						.padding(0)
				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
			}.height('60%').width('100%')

			Text(this.msg)
				.width('100%')
				.height('20%').fontSize('20fp')
				.fontWeight(FontWeight.Bold).textAlign(TextAlign.Start)

			Scroll() {
				Row() {
					Button(`${this.prefix}切换宽"`).onClick(() => {
						this.textWidth.switchCase()
						this.myModifier.updateWidth(this.textWidth.unit)
						// this.myModifier.showUnit(this.itemEnd)
					})
					Button(`${this.prefix}切换高`).onClick(() => {
						this.textHeight.switchCase()
						this.myModifier.updateHeight(this.textHeight.unit)
					})
					Button(`${this.prefix}变大字体`).onClick(() => {
						this.myModifier.updateFontSize(5)
					})
					Button(`${this.prefix}变小字体`).onClick(() => {
						this.myModifier.updateFontSize(-5)
					})
					Button("父组件切换宽").onClick(() => {
						this.parentWidth.switchCase()
					})
					Button("父组件切换高").onClick(() => {
						this.parentHeight.switchCase()
					})
				}
			}.scrollable(ScrollDirection.Horizontal)
			.width('100%').height('20%')
		}
	}

	@Builder
	itemEnd() {
		Select([{ value: 'KB' },
			{ value: 'MB' },
			{ value: 'GB' },
			{ value: 'TB', }])
			.height("48vp")
			.borderRadius(0)
			.selected(2)
			.align(Alignment.Center)
			.value('MB')
			.font({ size: 20, weight: 500 })
			.fontColor('#182431')
			.selectedOptionFont({ size: 20, weight: 400 })
			.optionFont({ size: 20, weight: 400 })
			.backgroundColor(Color.Transparent)
			.responseRegion({
				height: "40vp",
				width: "80%",
				x: '10%',
				y: '6vp'
			})
			.onSelect((index: number) => {
				console.info('Select:' + index);
			})
	}

	aboutToAppear(): void {
	}

	recvMsg(index: number, str: string) {
		this.msgArray[index] = str
		this.msg = this.msgArray.join("\n")
	}
}