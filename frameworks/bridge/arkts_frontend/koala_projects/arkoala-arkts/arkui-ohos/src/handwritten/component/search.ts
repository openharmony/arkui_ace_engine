import { InteropNativeModule, RuntimeType } from "@koalaui/interop";
import { int32 } from "@koalaui/common";
import { ArkUIGeneratedNativeModule } from "#components";
import { SearchOpsHandWritten } from "./../handwritten"

function SearchOptionsValueIsBindable(value?: SearchOptions) : boolean {
    if ((RuntimeType.UNDEFINED) != runtimeType(value)) {
        const value_text  = value!.value;
        if ((RuntimeType.UNDEFINED) != (runtimeType(value_text))) {
            const value_text_value  = value_text!;
            return TypeChecker.isBindableString(value_text_value);
        }
    }
    return false;
}

function hookSetSearchOptions(searchComponent: ArkSearchComponent, options?: SearchOptions): void {
    const options_casted = options as (SearchOptions | undefined)
    searchComponent.getPeer()?.setSearchOptionsAttribute(options_casted)
    if (SearchOptionsValueIsBindable(options)) {
        SearchOpsHandWritten.hookSearchInputValueImpl(searchComponent.getPeer().getPeerPtr(),
        (options!.value as Bindable<string>));
    }
}
