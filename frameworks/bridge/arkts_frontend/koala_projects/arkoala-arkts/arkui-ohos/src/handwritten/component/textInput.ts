import { InteropNativeModule, RuntimeType } from "@koalaui/interop";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { TextFieldOpsHandWritten } from "./../handwritten"

function TextInputOptionsValueIsBindable(value?: TextInputOptions) : boolean {
    if ((RuntimeType.UNDEFINED) != runtimeType(value)) {
        const value_text  = value!.text;
        if ((RuntimeType.UNDEFINED) != (runtimeType(value_text))) {
            const value_text_value  = value_text!;
            return TypeChecker.isBindableResourceStr(value_text_value)
        }
    }
    return false;
}

function hookSetTextInputOptions(textInputComponent: ArkTextInputComponent, value?: TextInputOptions): void {
    const value_casted = value as (TextInputOptions | undefined)
    textInputComponent.getPeer()?.setTextInputOptionsAttribute(value_casted)
    if (TextInputOptionsValueIsBindable(value)) {
        TextFieldOpsHandWritten.hookTextFieldInputValueImpl(textInputComponent.getPeer().getPeerPtr(),
        (value!.text as Bindable<ResourceStr>));
    }
}
