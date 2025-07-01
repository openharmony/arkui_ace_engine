import { InteropNativeModule, RuntimeType } from "@koalaui/interop";
import { Serializer } from "./peers/Serializer";
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

function hookSetTextInputOptions(peer: ArkTextInputPeer, value?: TextInputOptions): void {
    const value_casted = value as (TextInputOptions | undefined)
    peer.setTextInputOptionsAttribute(value_casted)
    if (TextInputOptionsValueIsBindable(value)) {
        TextFieldOpsHandWritten.hookTextFieldInputValueImpl(peer.getPeerPtr(),
        (value!.text as Bindable<ResourceStr>));
    }
}
