type TextUnit = Length | LayoutPolicy
interface CaseItem {
	name: string;
	value: TextUnit;
}

class SymbolGlyphModifier implements AttributeModifier<SymbolGlyphAttribute> {
	heights : (string | LayoutPolicy)[] = ['100vp', '100%', LayoutPolicy.wrapContent, LayoutPolicy.matchParent, LayoutPolicy.fixAtIdealSize, 'auto']
	heightStr : string[] = ['100vp', '100%', 'wrapContent', 'matchParent', 'fixAtIdealSize', 'auto']
	heightIndex : number = 0
	widths : (string | LayoutPolicy)[] = ['100vp', '100%', LayoutPolicy.wrapContent, LayoutPolicy.matchParent, LayoutPolicy.fixAtIdealSize, 'auto']
	widthStr : string[] = ['100vp', '100%', 'wrapContent', 'matchParent', 'fixAtIdealSize', 'auto']
	widthIndex : number = 0
	applyNormalAttribute(instance: SymbolGlyphAttribute): void {
		instance
			.height(this.heights[this.heightIndex])
			.width(this.widths[this.widthIndex])
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
export struct SymbolGlyphLayoutPolicy {
	prefix: string = 'SymbolGlyph'
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
	@State textAlignStr: string[] = ['Start', 'Center', 'End', 'JUSTIFY']
	@State textAlignIndex: number = 0
	@State fontSize: number = 16
	@State myModifier : SymbolGlyphModifier = new SymbolGlyphModifier();


	build() {
		Column() {
			Stack() {
				Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center }) {
					SymbolGlyph($r('sys.symbol.magnifyingglass'))
						.borderWidth(1)
						.borderColor(Color.Blue)
						.fontSize(this.fontSize)
						.constraintSize({
							minWidth: '200vp',
							maxWidth: '300vp',
							minHeight: '200vp',
							maxHeight: '300vp'
						})
						.attributeModifier(this.myModifier)
				}.width(this.parentWidth.unit)
				.height(this.parentHeight.unit)
				.borderWidth(1)
				.borderColor(Color.Orange)
				// .padding('10vp')
			}.height('60%').width('100%')

			TextArea({text: this.msg})
				.width('100%')
				.height('20%').fontSize('20fp')
				.fontWeight(FontWeight.Bold).textAlign(TextAlign.Start)

			Scroll() {
				Row() {
					Button(`${this.prefix}切换宽"`).onClick(() => {
						this.textWidth.switchCase()
						this.myModifier.widthIndex = (this.myModifier.widthIndex + 1) % this.myModifier.widths.length
						console.log('wgl--width:' + this.myModifier.widthIndex)
					})
					Button(`${this.prefix}切换高`).onClick(() => {
						this.textHeight.switchCase()
						this.myModifier.heightIndex = (this.myModifier.heightIndex + 1) % this.myModifier.heights.length
					})
					Button("父组件切换宽").onClick(() => {
						this.parentWidth.switchCase()
					})
					Button("父组件切换高").onClick(() => {
						this.parentHeight.switchCase()
					})
					Button('TextAlign：' + this.textAlignStr[this.textAlignIndex]).onClick(()=> {
						this.textAlignIndex++
						if (this.textAlignIndex > this.textAligns.length - 1) {
							this.textAlignIndex = 0
						}
						this.textAlign = this.textAligns[this.textAlignIndex]
					})

					Button('fontSize++：' + this.fontSize).onClick(()=> {
						this.fontSize+=10
					})
					Button('fontSize--：' + this.fontSize).onClick(()=> {
						this.fontSize-=10
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