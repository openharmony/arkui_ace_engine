import { InteropNativeModule, RuntimeType } from "@koalaui/interop";
import { Serializer } from "./peers/Serializer";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { TextFieldOpsHandWritten } from "./../handwritten"

function TextAreaOptionsValueIsBindable(value?: TextAreaOptions) : boolean {
    if ((RuntimeType.UNDEFINED) != runtimeType(value)) {
        const value_text  = value!.text;
        if ((RuntimeType.UNDEFINED) != (runtimeType(value_text))) {
            const value_text_value  = value_text!;
            return TypeChecker.isBindableResourceStr(value_text_value);
        }
    }
    return false;
}

function hookSetTextAreaOptions(peer: ArkTextAreaPeer, value?: TextAreaOptions): void {
    const value_casted = value as (TextAreaOptions | undefined)
    peer.setTextAreaOptionsAttribute(value_casted)
    if (TextAreaOptionsValueIsBindable(value)) {
        TextFieldOpsHandWritten.hookTextFieldInputValueImpl(peer.getPeerPtr(),
        (value!.text as Bindable<ResourceStr>));
    }
}
