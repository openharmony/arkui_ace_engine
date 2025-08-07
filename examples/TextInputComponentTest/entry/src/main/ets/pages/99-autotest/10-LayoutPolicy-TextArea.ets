import { TextAreaModifier } from "@kit.ArkUI";

type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class MyModifier extends TextAreaModifier {
	count: number = 0
	updateWidth(value: TextUnit) {
		this.width(value)
		this.count++
	}

	updateHeight(value: TextUnit) {
		this.height(value)
		this.count++
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
export struct TextAreaLayoutPolicy {
	prefix: string = 'TextArea'
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
					TextArea({text: "Hello World!", placeholder: "###############"})
						.borderWidth(1)
						.borderColor(Color.Blue)
						.constraintSize({
							minWidth: '100vp',
							maxWidth: '200vp',
							minHeight: '100vp',
							maxHeight: '200vp'
						})
						.attributeModifier(this.myModifier)
						.textIndent('5vp')
						.showCounter(true)
						.maxLength(500)

				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
				.padding(1)
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
					})
					Button(`${this.prefix}切换高`).onClick(() => {
						this.textHeight.switchCase()
						this.myModifier.updateHeight(this.textHeight.unit)
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

	aboutToAppear(): void {

	}

	recvMsg(index: number, str: string) {
		this.msgArray[index] = str
		this.msg = this.msgArray.join("\n")
	}
}