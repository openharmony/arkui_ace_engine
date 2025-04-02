@Entry
@Component
struct TextPickerTest {
    font1: Font = { }
    font2: Font = { family: "Arial", style: FontStyle.Normal }
    font3: Font = { family: "Serif", style: FontStyle.Italic }
    font4: Font = { style: FontStyle.Normal }
    font5: Font = { family: "fontFamily" }
    textStyle1: PickerTextStyle = { }
    textStyle2: PickerTextStyle = { color: Color.Green, font: this.font1 }
    textStyle3: PickerTextStyle = { color: 333, font: this.font2 }
    textStyle4: PickerTextStyle = { color: "#404040", font: this.font3 }
    textStyle5: PickerTextStyle = { color: Color.Blue, font: this.font4 }
    textStyle6: PickerTextStyle = { font: this.font5 }
    value1: string = "value1"
    value2: string[] = [ "value1", "value2", "value3" ]
    selectedIndex1: number = 33
    selectedIndex2: number[] = [ 3, 5, 7, 9 ]
    range1: string[] = [ "string1", "string2", "string3" ]
    range2: TextPickerRangeContent[] = [ 
        { icon: "icon1", text: "text1" },
        { icon: "icon2", text: "text2" },
        { icon: "icon3", text: "text3" },
        { icon: "icon4", text: "text4" },
        { icon: "icon5", text: "text5" },
        { icon: "icon6", text: "text6" },
    ]
    options1: TextPickerOptions = { range: this.range1, value: this.value1, selected: this.selectedIndex1 }
    options2: TextPickerOptions = { range: this.range2, value: this.value2, selected: this.selectedIndex2 }
    options3: TextPickerOptions = { range: this.range1, value: this.value1 }
    options4: TextPickerOptions = { range: this.range2, selected: this.selectedIndex2 }
    options5: TextPickerOptions = { range: this.range1 }

    build() {
        TextPicker()
        .disappearTextStyle(this.textStyle1)
        .textStyle(this.textStyle2)
        .selectedTextStyle(this.textStyle3)
        .defaultPickerItemHeight(25)
        .canLoop(false)
        .selectedIndex(this.selectedIndex1)
        TextPicker()
        .disappearTextStyle(this.textStyle4)
        .textStyle(this.textStyle5)
        .selectedTextStyle(this.textStyle6)
        .defaultPickerItemHeight("26vp")
        .canLoop(true)
        .selectedIndex(this.selectedIndex2)
        TextPicker(this.options1)
        .defaultPickerItemHeight("27fp")
        TextPicker(this.options2)
        .defaultPickerItemHeight("28px")
        TextPicker(this.options3)
        .defaultPickerItemHeight("29lpx")
        TextPicker(this.options4)
        .defaultPickerItemHeight("30%")
        TextPicker(this.options5)
    }
}
