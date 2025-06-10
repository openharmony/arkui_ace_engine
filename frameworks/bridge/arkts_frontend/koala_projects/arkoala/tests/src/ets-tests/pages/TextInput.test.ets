@Entry
@Component
struct TextInputTest {
    options1: TextInputOptions = { }
    options2: TextInputOptions = { placeholder: "Placeholder" }
    options3: TextInputOptions = { text: "TextInput" }
    options4: TextInputOptions = { placeholder: "Placeholder", text: "TextInput" }
    caretStyle1: CaretStyle = { }
    caretStyle2: CaretStyle = { width: 10, color: Color.Blue }
    caretStyle3: CaretStyle = { width: "11px", color: Color.Red }
    caretStyle4: CaretStyle = { width: "12lpx", color: 333 }
    caretStyle5: CaretStyle = { width: "13vp", color: "#404040" }
    caretStyle6: CaretStyle = { width: "14fp"}
    caretStyle7: CaretStyle = { width: "15%"}
    passwordIcon1: PasswordIcon = { }
    passwordIcon2: PasswordIcon = { onIconSrc: "showIcon"}
    passwordIcon3: PasswordIcon = { offIconSrc: "hideIcon" }
    passwordIcon4: PasswordIcon = { onIconSrc: "showIcon", offIconSrc: "hideIcon"}
    iconOptions1: IconOptions = { }
    iconOptions2: IconOptions = { size: 10, color: Color.Blue, src: "source" }
    iconOptions3: IconOptions = { size: "11px", color: Color.Red }
    iconOptions4: IconOptions = { size: "12lpx", color: 333 }
    iconOptions5: IconOptions = { size: "13vp", color: "#404040" }
    iconOptions6: IconOptions = { size: "14fp"}
    iconOptions7: IconOptions = { size: "15%" }
    cancelButton1 = { style: CancelButtonStyle.CONSTANT, icon: this.iconOptions1 }
    cancelButton2 = { style: CancelButtonStyle.INVISIBLE, icon: this.iconOptions2 }
    cancelButton3 = { style: CancelButtonStyle.INPUT, icon: this.iconOptions3 }
    cancelButton4 = { icon: this.iconOptions4 }
    cancelButton5 = { icon: this.iconOptions5 }
    cancelButton6 = { icon: this.iconOptions6 }
    cancelButton7 = { icon: this.iconOptions7 }

    build() {
        TextInput(this.options1)
        .placeholderFont({size:30, weight: FontWeight.Lighter, family:"testFamily", style: FontStyle.Normal})
        .fontColor(Color.Blue)
        .placeholderColor(Color.Blue)
        .caretColor(Color.Blue)
        .textAlign(TextAlign.Center)
        .enterKeyType(EnterKeyType.Go)
        .showPasswordIcon(false)
        .caretStyle(this.caretStyle1)
        .selectedBackgroundColor(Color.Blue)
        .caretPosition(0)
        .showError()
        TextInput(this.options2)
        .placeholderFont({size:"20vp", weight: FontWeight.Normal, family:"testFamily", style:FontStyle.Italic})
        .fontColor(333)
        .placeholderColor(333)
        .caretColor(333)
        .textAlign(TextAlign.Start)
        .enterKeyType(EnterKeyType.Search)
        .showPasswordIcon(true)
        .caretStyle(this.caretStyle2)
        .selectedBackgroundColor(333)
        .caretPosition(1234)
        .showError("error")
        TextInput(this.options3)
        .placeholderFont({size:"40px", weight: FontWeight.Regular, family:"testFamily", style:FontStyle.Normal})
        .fontColor("#404040")
        .placeholderColor("#404040")
        .caretColor("#404040")
        .textAlign(TextAlign.End)
        .enterKeyType(EnterKeyType.Send)
        .caretStyle(this.caretStyle3)
        .selectedBackgroundColor("#404040")
        .showError("error")
        .showError()
        TextInput(this.options4)
        .placeholderFont({size:"25lpx", weight: FontWeight.Medium, family:"testFamily", style:FontStyle.Italic})
        .textAlign(TextAlign.JUSTIFY)
        .enterKeyType(EnterKeyType.Next)
        .caretStyle(this.caretStyle4)
        TextInput()
        .placeholderFont({size:"5%", weight: FontWeight.Bold, family:"testFamily", style:FontStyle.Normal})
        .enterKeyType(EnterKeyType.Done)
        .caretStyle(this.caretStyle5)
        TextInput()
        .placeholderFont({size:24, weight: FontWeight.Bolder, family:"testFamily", style:FontStyle.Italic})
        .caretStyle(this.caretStyle6)
        TextInput()
        .placeholderFont({size:"5%", weight: "Medium", family:"testFamily", style:FontStyle.Normal})
        .caretStyle(this.caretStyle7)
        TextInput()
        .placeholderFont({size:24, weight: 100, family:"testFamily", style:FontStyle.Italic})
        .showUnderline(false)
        TextInput()
        .placeholderFont({size:"5%", weight: "Lighter", family:"testFamily", style:FontStyle.Normal})
        .showUnderline(true)
        TextInput()
        .placeholderFont({size:24, weight: 900, family:"testFamily", style:FontStyle.Italic})
        .cancelButton(this.cancelButton1)
        TextInput()
        .placeholderFont({})
        .cancelButton(this.cancelButton2)
        TextInput()
        .maxLines(5)
        .fontSize(30)
        .fontFamily("Arial")
        .fontStyle(FontStyle.Normal)
        .fontWeight(FontWeight.Lighter)
        .cancelButton(this.cancelButton3)
        TextInput()
        .fontSize("20vp")
        .fontStyle(FontStyle.Italic)
        .fontWeight("Bolder")
        .copyOption(CopyOptions.None)
        .passwordIcon(this.passwordIcon1)
        .cancelButton(this.cancelButton4)
        TextInput()
        .fontSize("40px")
        .fontWeight(400)
        .barState(BarState.On)
        .copyOption(CopyOptions.InApp)
        .passwordIcon(this.passwordIcon2)
        .cancelButton(this.cancelButton5)
        TextInput()
        .fontSize("25lpx")
        .maxLength(20)
        .fontWeight(900)
        .barState(BarState.Auto)
        .copyOption(CopyOptions.LocalDevice)
        .selectionMenuHidden(true)
        .enableKeyboardOnFocus(false)
        .passwordIcon(this.passwordIcon3)
        .cancelButton(this.cancelButton6)
        TextInput()
        .fontSize("5%")
        .maxLength(200)
        .fontWeight(10)
        .barState(BarState.Off)
        .copyOption(CopyOptions.CROSS_DEVICE)
        .selectionMenuHidden(false)
        .enableKeyboardOnFocus(true)
        .passwordIcon(this.passwordIcon4)
        .cancelButton(this.cancelButton7)
    }
}
