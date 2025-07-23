type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
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
export struct TextMarqueeLayoutPolicy {
	prefix: string = 'TextMarquee'
	@State msgArray: string[] = ["","","",""]
	@State msg: string = ""
	@State textWidth: TestCase = new TestCase(`${this.prefix}Width`, 0, this.recvMsg.bind(this))
	@State textHeight: TestCase = new TestCase(`${this.prefix}Height`, 1, this.recvMsg.bind(this))
	@State parentWidth: TestCase = new TestCase('ParentWidth', 2, this.recvMsg.bind(this))
	@State parentHeight: TestCase = new TestCase('ParentHeight', 3, this.recvMsg.bind(this))
	@State textAlign: TextAlign = TextAlign.Start

	textAligns: TextAlign[] = [
		TextAlign.Start,
		TextAlign.Center,
		TextAlign.End,
		TextAlign.JUSTIFY
	]

	@State textAlignIndex: number = 0

	build() {
		Column() {
			Stack() {
				Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
					Text($r('app.string.long_text'))
						.width(this.textWidth.unit)
						.height(this.textHeight.unit)
						.textOverflow({overflow: TextOverflow.MARQUEE})
						.borderWidth(1)
						.borderColor(Color.Blue)
						.textAlign(this.textAlign)
						.constraintSize({
							minWidth: '200vp',
							maxWidth: '300vp',
							minHeight: '200vp',
							maxHeight: '300vp'
						})
				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
				.padding('10vp')
			}.height('60%').width('100%')

			Text(this.msg)
				.width('100%')
				.height('20%').fontSize('20fp')
				.fontWeight(FontWeight.Bold).textAlign(TextAlign.Start)

			Scroll() {
				Row() {
					Button(`${this.prefix}宽`).onClick(() => {
						this.textWidth.switchCase()
					})
					Button(`${this.prefix}高`).onClick(() => {
						this.textHeight.switchCase()
					})
					Button("父组件宽").onClick(() => {
						this.parentWidth.switchCase()
					})
					Button("父组件高").onClick(() => {
						this.parentHeight.switchCase()
					})
					Button('TextAlign').onClick(()=> {
						this.textAlignIndex++
						if (this.textAlignIndex == this.textAligns.length) {
							this.textAlignIndex = 0
						}
						this.textAlign = this.textAligns[this.textAlignIndex]
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